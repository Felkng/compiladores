# Compilador para a Linguagem Rust

Projeto acadêmico da disciplina de **Compiladores** que implementa, de forma incremental, um compilador para a linguagem [Rust](https://www.rust-lang.org/) utilizando a ferramenta [JavaCC](https://javacc.github.io/javacc/) (Java Compiler Compiler).

## Referência

- [Rust Reference — Tokens](https://doc.rust-lang.org/stable/reference/tokens.html)
- [Rust Reference — Keywords](https://doc.rust-lang.org/stable/reference/keywords.html)
- [Rust Reference — Identifiers](https://doc.rust-lang.org/stable/reference/identifiers.html)

## Estrutura do Projeto

```
compiladores/
├── README.md
├── lexer.sh            # Script para compilar e executar o lexer
├── out.txt             # Saída da última análise léxica
├── .gitignore
└── lab01/
    ├── lexer.jj        # Gramática JavaCC do analisador léxico
    ├── test.rs          # Arquivo Rust de teste
    └── *.java / *.class # Arquivos gerados pelo JavaCC e javac
```

## Pré-requisitos

- **Java JDK** 11 ou superior
- **JavaCC** 7.x ([instalação](https://javacc.github.io/javacc/))

## Lab 01 — Analisador Léxico

O primeiro módulo do compilador realiza a **análise léxica** de programas Rust, identificando e classificando todos os tokens da linguagem.

### Como Executar

```bash
# 1. Compilar e executar em um só passo (via script)
./lexer.sh lab01/test.rs

# A saída é salva em out.txt

# 2. Ou manualmente
cd lab01
javacc lexer.jj
javac --release 11 RustLexer.java
java RustLexer test.rs
```

### Formato da Saída

Uma linha por token, no formato:

```
CLASSE lexema
```

Exemplo de saída para o trecho `fn main() {`:

```
KW_FN fn
ID main
LPAREN (
RPAREN )
LBRACE {
```

## Licença

Projeto acadêmico — uso educacional.
