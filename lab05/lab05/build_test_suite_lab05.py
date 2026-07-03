import os
import re
import subprocess
import glob

os.makedirs('ins', exist_ok=True)

# Map types to Rust/Gramática 9
type_map = {
    'int': 'i32',
    'float': 'f32',
    'boolean': 'bool',
    'bool': 'bool'
}

def translate_c_to_rust(c_code):
    # Strip block comments
    c_code = re.sub(r'/\*.*?\*/', '', c_code, flags=re.DOTALL)
    # Strip single line comments
    c_code = re.sub(r'//.*$', '', c_code, flags=re.MULTILINE)
    
    lines = c_code.split('\n')
    rust_lines = []
    stack = []
    recording_do = False
    do_accumulator = []

    for line in lines:
        l = line.strip()
        if not l:
            continue
            
        # Function declaration
        # int f() {
        # void F4() {
        m = re.match(r'^\s*(int|void|float|boolean|bool)\s+([a-zA-Z_0-9]+)\s*\((.*?)\)\s*\{', line)
        if m:
            ret_raw = m.group(1)
            name = m.group(2)
            params_str = m.group(3)
            rust_params = []
            if params_str.strip():
                params = params_str.split(',')
                for p in params:
                    p = p.strip()
                    ptype, pname = p.split()
                    rust_params.append(f"{pname}: {type_map.get(ptype, ptype)}")
            
            if ret_raw == 'void':
                rust_lines.append(f"fn {name}({', '.join(rust_params)}) {{")
            else:
                rust_lines.append(f"fn {name}({', '.join(rust_params)}) -> {type_map.get(ret_raw, ret_raw)} {{")
            
            stack.append(('block', None))
            continue
            
        # Variable declaration
        # int a; or int a = 10;
        m = re.match(r'^\s*(int|float|boolean|bool)\s+([a-zA-Z_0-9]+)\s*(?:=\s*(.*?))?;', line)
        if m:
            vtype = type_map.get(m.group(1), m.group(1))
            vname = m.group(2)
            init = m.group(3)
            if init:
                newline = f"    let mut {vname}: {vtype} = {init};"
            else:
                newline = f"    let mut {vname}: {vtype};"
            
            if recording_do:
                do_accumulator.append(newline)
            else:
                rust_lines.append(newline)
            continue

        # For loop
        # for (i = 0; i < 4; i = i + 1) {
        m = re.match(r'^\s*for\s*\(\s*(.*?);\s*(.*?);\s*(.*?)\)\s*\{', line)
        if m:
            init = m.group(1)
            cond = m.group(2)
            step = m.group(3)
            
            init_line = f"    {init};"
            cond_line = f"    while ({cond}) {{"
            
            if recording_do:
                do_accumulator.append(init_line)
                do_accumulator.append(cond_line)
            else:
                rust_lines.append(init_line)
                rust_lines.append(cond_line)
            
            stack.append(('for', step))
            continue

        # Do-while loop start
        if l.startswith("do {") or l == "do":
            recording_do = True
            do_accumulator = []
            stack.append(('do', None))
            continue

        # Do-while loop end
        # } while (i < times);
        m = re.match(r'^\s*\}\s*while\s*\((.*?)\)\s*;', line)
        if m:
            cond = m.group(1)
            # Stop recording do
            recording_do = False
            stack.pop() # pop 'do'
            
            # Output do body once
            for dl in do_accumulator:
                rust_lines.append(dl)
            
            # Output while loop
            rust_lines.append(f"    while ({cond}) {{")
            for dl in do_accumulator:
                rust_lines.append(dl)
            rust_lines.append("    }")
            continue

        # Bare opening brace or other control structures opening brace
        if l.endswith("{"):
            stack.append(('block', None))
            if recording_do:
                do_accumulator.append(line)
            else:
                rust_lines.append(line)
            continue

        # Closing brace
        if l == "}":
            if stack:
                btype, step = stack.pop()
                if btype == 'for':
                    # Append the loop step before closing the while loop
                    step_line = f"        {step};"
                    if recording_do:
                        do_accumulator.append(step_line)
                        do_accumulator.append(line)
                    else:
                        rust_lines.append(step_line)
                        rust_lines.append(line)
                    continue
            
            if recording_do:
                do_accumulator.append(line)
            else:
                rust_lines.append(line)
            continue

        # Replace True/False with true/false
        line = re.sub(r'\bTrue\b', 'true', line)
        line = re.sub(r'\bFalse\b', 'false', line)

        if recording_do:
            do_accumulator.append(line)
        else:
            rust_lines.append(line)
            
    return '\n'.join(rust_lines)

print("Compiling project...")
subprocess.run("make clean && make", shell=True)

c_files = glob.glob('ins/*.c')
c_files = sorted(c_files, key=lambda x: int(re.search(r'\d+', x).group()) if re.search(r'\d+', x) else 999)

for c_file in c_files:
    basename = os.path.basename(c_file).replace('.c', '')
    if basename == "tudo":
        continue # Skip everything in one file for separate tests

    print(f"Processing {basename}.c ...")
    
    with open(c_file, 'r') as f:
        c_code = f.read()
        
    rust_code = translate_c_to_rust(c_code)
    ling_path = f'ins/{basename}.rs'
    with open(ling_path, 'w') as f:
        f.write(rust_code)
        
    # Run Lexer
    lexer_cmd = f"cd /home/felkng/Documents/faculdade/compiladores/lab01 && java RustLexer /home/felkng/Documents/faculdade/compiladores/lab05/lab05/{ling_path}"
    res = subprocess.run(lexer_cmd, shell=True, capture_output=True, text=True)
    
    tokens = res.stdout.strip()
    # Map KW_TRUE and KW_FALSE to ID to match grammar-9
    tokens = tokens.replace("KW_TRUE", "ID").replace("KW_FALSE", "ID").replace("KW_LOOP", "ID")
    
    # Filter out COMMENT_LINE and COMMENT_BLOCK tokens
    token_lines = [t for t in tokens.split('\n') if t.strip() and not t.startswith("COMMENT_LINE") and not t.startswith("COMMENT_BLOCK")]
    tokens = '\n'.join(token_lines)
    
    tokens += "\n$ $"
    
    in_path = f'ins/{basename}.in'
    with open(in_path, 'w') as f:
        f.write(tokens)
        
    # Run Compiler
    comp_cmd = f"./compilador gramatica-9/gramatica-9.site gramatica-9/tabela_lr1.conf < {in_path} > ins/{basename}.saida 2> ins/{basename}.err"
    subprocess.run(comp_cmd, shell=True)
    
    # Print the output to verify
    print(f"--- Output for {basename} ---")
    with open(f"ins/{basename}.saida", "r") as sf:
        print(sf.read().strip())
    print("----------------------------\n")

print("Done processing tests!")
