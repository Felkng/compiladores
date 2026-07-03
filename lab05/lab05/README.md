# Laboratório 05 - Conversão para Representação Intermediária (IR)

Este diretório contém o compilador estendido que converte a AST de uma função (Gramática 9, subconjunto de Rust) para a Árvore de Representação Intermediária (IR) descrita no Capítulo 7 de Andrew Appel (com comparadores booleanos substituídos por expressões booleanas).

O compilador imprime na saída padrão a lista de comandos IR linearizados (um por linha).

## Como Compilar

Para compilar o compilador, execute o seguinte comando no terminal:
```bash
make
```

## Como Executar

O compilador lê o fluxo de tokens a partir da entrada padrão (`cin`) e aceita as tabelas da gramática como argumentos opcionais.

Para executar o compilador com um caso de teste do diretório `ins/`:
```bash
./compilador gramatica-9/gramatica-9.site gramatica-9/tabela_lr1.conf < ins/<nome_do_caso>.in
```

### Exemplo
```bash
./compilador gramatica-9/gramatica-9.site gramatica-9/tabela_lr1.conf < ins/1.in
```
