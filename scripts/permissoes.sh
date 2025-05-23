#!/bin/bash

# Cria o arquivo segredo.txt
# Define permissões de leitura e execução para o grupo e nenhuma para outros
# Exibe as permissões

space() {
	printf "\n\n"
}

clear

space
echo "Criando arquivo segredo.txt"
touch segredo.txt

space
echo "Configurando permissão de leitura e execução apenas ao grupo"
chmod g=rx,o= segredo.txt

space
echo "Verificando permissões"
ls -l segredo.txt

space
