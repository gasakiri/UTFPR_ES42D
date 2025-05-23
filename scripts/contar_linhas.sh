#!/bin/bash

# Recebe um diretório como argumento
# Conta e exibe o número de linhas dos arquivos .txt contidos nele

space() {
	printf "\n\n"
}

conta_linhas() {
	cd $dir
	arquivos=$(find . -type f -name "*.txt" -printf "%P\n")

	for arquivo in $arquivos; do

		local linhas=0

		while read -r linha; do
			(( linhas++ ))
		done < "$arquivo"

		echo "$arquivo: $linhas linhas"
	done
}

clear
read -p "Entre um caminho de diretório: " dir

if [[ ! -d "$dir" ]]; then
    echo "Diretório não existe"
    exit 1
fi

conta_linhas
