#!/bin/bash

# Lista o conteúdo do diretório /etc
# Cria um diretório projetos
# Cria o arquivo exemplo.txt dentro de projetos
# Copia o arquivo para /tmp

echo "Listando conteúdo do diretório /etc"
echo ""

ls /etc

echo ""
echo "Criando um diretório chamado projetos no local de execução deste script"
echo ""

mkdir -p projetos

echo ""
echo "Criando o arquivo projetos/exemplo.txt"
echo ""

touch projetos/exemplo.txt

echo ""
echo "Copiando exemplo.txt para o diretório /tmp"
echo ""

cp projetos/exemplo.txt /tmp
