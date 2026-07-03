#!/bin/bash
# =====================================================================
# Script de Empacotamento para Submissão - Lab 05 (Compiladores)
# =====================================================================

set -e

# Garante que o script roda no diretório correto (lab05/lab05)
cd "$(dirname "$0")"

echo -e "\e[1;34m=== PREPARANDO SUBMISSÃO DO LAB 05 ===\e[0m"

# 1. Compila o compilador para poder gerar os testes
echo -e "\e[1;32m-> Compilando o compilador...\e[0m"
make

# 2. Regenera os testes finais
echo -e "\e[1;32m-> 1/3: Rodando a suíte de testes (gerando X.rs, X.in)...\e[0m"
python3 build_test_suite_lab05.py

# 3. Limpa os binários compilados
echo -e "\e[1;32m-> 2/3: Removendo arquivos compilados (.o e executáveis via make clean)...\e[0m"
make clean

# 4. Compacta o diretório para submissão
echo -e "\e[1;32m-> 3/3: Compactando o diretório lab05/lab05...\e[0m"
cd ../..
# Remove zip antigo se existir
rm -f compil-lab5-felipe-rodrigues-de-sousa-ferreira.zip

# Compacta desconsiderando arquivos indesejados
zip -r compil-lab5-felipe-rodrigues-de-sousa-ferreira.zip lab05/lab05 -x "lab05/lab05/.git/*" "lab05/lab05/.DS_Store" "lab05/lab05/__MACOSX/*" "lab05/lab05/lab05.pdf" "lab05/lab05/lab05.pages" "lab05/lab05/*.py" "lab05/lab05/package_submission_lab05.sh" "lab05/lab05/ins/*.err" "lab05/lab05/ins/*.saida"

echo -e "\e[1;34m=== EMPACOTAMENTO CONCLUÍDO COM SUCESSO! ===\e[0m"
echo -e "\e[32mArquivo ZIP gerado pronto para submissão:\e[0m"
echo -e "\e[1;33m$(pwd)/compil-lab5-felipe-rodrigues-de-sousa-ferreira.zip\e[0m"
