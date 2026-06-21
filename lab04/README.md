# Laboratório 04 - Descrição de Uso de Frame

Este diretório contém o compilador que gera a descrição de uso do Frame por Função e preenche o modo de acesso (`FrameAcesso`) para cada ocorrência de variável.

## Como Compilar

Para compilar o compilador, execute o seguinte comando no terminal:
```bash
make
```

## Como Executar

O compilador lê os tokens na sintaxe definida no laboratório a partir do *standard input* e aceita opcionalmente um arquivo de parâmetros como terceiro argumento.

Para executar o compilador com um dos casos de teste disponíveis no diretório `ins/`, utilize o comando:
```bash
./compilador gramatica-9/gramatica-9.site gramatica-9/tabela_lr1.conf ins/<nome_do_caso>.params < ins/<nome_do_caso>.tokens
```

### Exemplo de Execução
```bash
./compilador gramatica-9/gramatica-9.site gramatica-9/tabela_lr1.conf ins/caso01.params < ins/caso01.tokens
```
