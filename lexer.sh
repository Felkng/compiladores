#!/bin/bash

# Uso: ./lexer.sh <arquivo.rs>
# Compila o lexer JavaCC e executa a análise léxica,
# salvando o resultado em out.txt

if [ -z "$1" ]; then
    echo "Uso: $0 <arquivo.rs>"
    exit 1
fi

if [ ! -f "$1" ]; then
    echo "Erro: arquivo '$1' nao encontrado."
    exit 1
fi

# Caminho absoluto do arquivo de entrada
INPUT_FILE="$(realpath "$1")"

# Diretório do lexer
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
LEXER_DIR="$SCRIPT_DIR/lab01"

cd "$LEXER_DIR" || exit 1

# Compila o lexer (só se necessário ou se lexer.jj mudou)
if [ ! -f "RustLexer.class" ] || [ "lexer.jj" -nt "RustLexer.class" ]; then
    echo "Compilando o lexer..."
    javacc lexer.jj && javac RustLexer.java
    if [ $? -ne 0 ]; then
        echo "Erro na compilacao do lexer."
        exit 1
    fi
    echo "Lexer compilado com sucesso."
else
    echo "Lexer ja esta compilado e atualizado."
fi

# Executa a análise léxica e salva em out.txt
echo "Analisando: $INPUT_FILE"
java RustLexer "$INPUT_FILE" > "$SCRIPT_DIR/out.txt" 2>/dev/null

echo "Resultado salvo em: $SCRIPT_DIR/out.txt"
