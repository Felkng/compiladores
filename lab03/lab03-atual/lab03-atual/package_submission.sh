#!/bin/bash
# =====================================================================
# Script de Empacotamento para Submissão - Lab 03 (Compiladores)
# =====================================================================

set -e

# Garante que o script roda no diretório correto
cd "$(dirname "$0")"

echo -e "\e[1;34m=== PREPARANDO SUBMISSÃO DO LAB 03 ===\e[0m"

# 1. Compila o compilador para poder gerar os testes
echo -e "\e[1;32m-> Compilando o interpretador...\e[0m"
make

# 2. Regenera os testes finais
echo -e "\e[1;32m-> 1/3: Rodando a suíte de testes (gerando X.rs, X.tokens, X.params, X.saida, X.err)...\e[0m"
rm -f ins/*.ling
python3 build_test_suite.py

# 2. Limpa os binários compilados
echo -e "\e[1;32m-> 2/3: Removendo arquivos compilados (.o e executáveis via make clean)...\e[0m"
make clean

# 3. Compacta o diretório para submissão
echo -e "\e[1;32m-> 3/3: Compactando o diretório com a solução e a pasta ins/...\e[0m"
cd ..
# Remove zip antigo se existir
rm -f lab03-entrega.zip

# Compacta desconsiderando arquivos indesejados e scripts auxiliares
zip -r lab03-entrega.zip lab03-atual -x "lab03-atual/.git/*" "lab03-atual/.DS_Store" "lab03-atual/__MACOSX/*" "lab03-atual/build_test_suite.py" "lab03-atual/package_submission.sh"

echo -e "\e[1;34m=== EMPACOTAMENTO CONCLUÍDO COM SUCESSO! ===\e[0m"
echo -e "\e[32mArquivo ZIP gerado pronto para submissão:\e[0m"
echo -e "\e[1;33m$(pwd)/lab03-entrega.zip\e[0m"
echo -e "\nVocê pode enviar diretamente este arquivo \e[1m_lab03-entrega.zip_\e[0m."
