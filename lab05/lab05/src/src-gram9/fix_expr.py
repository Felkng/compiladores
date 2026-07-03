import re

with open('Expressao.cpp', 'r') as f:
    content = f.read()

def replace_case(match):
    num = int(match.group(1))
    return f"case {num-1}:"

content = re.sub(r'case\s+(\d+):', replace_case, content)

with open('Expressao.cpp', 'w') as f:
    f.write(content)
