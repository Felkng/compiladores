import os
import re
import subprocess
import glob

os.makedirs('ins', exist_ok=True)

# Map types to Rust
type_map = {
    'int': 'i32',
    'float': 'f32',
    'boolean': 'bool',
    'bool': 'bool'
}

def translate_c_to_rust(c_code):
    # Strip single line comments
    c_code = re.sub(r'//.*$', '', c_code, flags=re.MULTILINE)
    # Strip block comments
    c_code = re.sub(r'/\*.*?\*/', '', c_code, flags=re.DOTALL)
    
    lines = c_code.split('\n')
    rust_lines = []
    for line in lines:
        l = line.strip()
        if not l:
            continue
            
        # Function declaration
        # float media(float a, float b) {
        m = re.match(r'^\s*(int|float|boolean|bool)\s+([a-zA-Z_0-9]+)\s*\((.*?)\)\s*\{', line)
        if m:
            ret_type = type_map.get(m.group(1), m.group(1))
            name = m.group(2)
            params_str = m.group(3)
            rust_params = []
            if params_str.strip():
                params = params_str.split(',')
                for p in params:
                    p = p.strip()
                    ptype, pname = p.split()
                    rust_params.append(f"{pname}: {type_map.get(ptype, ptype)}")
            rust_lines.append(f"fn {name}({', '.join(rust_params)}) -> {ret_type} {{")
            continue
            
        # Variable declaration
        # float m; or float m = 0;
        m = re.match(r'^\s*(int|float|boolean|bool)\s+([a-zA-Z_0-9]+)\s*(?:=\s*(.*?))?;', line)
        if m:
            vtype = type_map.get(m.group(1), m.group(1))
            vname = m.group(2)
            init = m.group(3)
            if init:
                rust_lines.append(f"    let mut {vname}: {vtype} = {init};")
            else:
                rust_lines.append(f"    let mut {vname}: {vtype};")
            continue
            
        # Just copy other lines as they are largely compatible (if, while, return, assignment)
        rust_lines.append(line)
        
    return '\n'.join(rust_lines)

def infer_params(rust_code):
    m = re.search(r'fn\s+[a-zA-Z_0-9]+\s*\((.*?)\)', rust_code)
    params = []
    if m:
        pstr = m.group(1)
        if pstr.strip():
            for p in pstr.split(','):
                p = p.strip()
                pname, ptype = p.split(':')
                ptype = ptype.strip()
                if ptype == 'i32':
                    params.append("INT 10")
                elif ptype == 'f32':
                    params.append("FLOAT 10.5")
                elif ptype == 'bool':
                    params.append("BOOL true")
    return params

c_files = glob.glob('exemplos/*.c')

for c_file in c_files:
    basename = os.path.basename(c_file).replace('.c', '')
    
    with open(c_file, 'r') as f:
        c_code = f.read()
        
    rust_code = translate_c_to_rust(c_code)
    ling_path = f'ins/{basename}.ling'
    with open(ling_path, 'w') as f:
        f.write(rust_code)
        
    # Run Lexer
    lexer_cmd = f"cd /home/felkng/Documents/faculdade/compiladores/lab01 && java RustLexer /home/felkng/Documents/faculdade/compiladores/lab03/lab03-atual/lab03-atual/{ling_path}"
    res = subprocess.run(lexer_cmd, shell=True, capture_output=True, text=True)
    
    tokens = res.stdout.strip()
    # Map KW_TRUE and KW_FALSE to ID to match the lab02 grammar
    tokens = tokens.replace("KW_TRUE", "ID").replace("KW_FALSE", "ID")
    
    # Filter out COMMENT_LINE and COMMENT_BLOCK tokens
    token_lines = [t for t in tokens.split('\n') if t.strip() and not t.startswith("COMMENT_LINE") and not t.startswith("COMMENT_BLOCK")]
    tokens = '\n'.join(token_lines)
    
    tokens += "\n$ $"
    
    tokens_path = f'ins/{basename}.tokens'
    with open(tokens_path, 'w') as f:
        f.write(tokens)
        
    # Params
    params = infer_params(rust_code)
    params_path = f'ins/{basename}.params'
    with open(params_path, 'w') as f:
        f.write('\n'.join(params))
        
    # Run Compiler
    comp_cmd = f"./compilador gramatica-9/gramatica-9.site gramatica-9/tabela_lr1.conf {params_path} < {tokens_path} > ins/{basename}.saida 2> ins/{basename}.err"
    subprocess.run(comp_cmd, shell=True)
    
print("Done processing tests!")
