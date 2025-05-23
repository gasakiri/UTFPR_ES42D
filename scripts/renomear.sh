#!/bin/bash

# Renomeia todos os arquivos .jpg em um diretório adicionando _backup antes da extensão

space() {
	printf "\n\n"
}

renomeia() {
    cd $dir
    arquivos=$(find . -type f -name "*.jpg" -printf "%P\n")

    for arquivo in $arquivos; do

        mv $arquivo ${arquivo%".jpg"}_backup.jpg

    done
}

clear
read -p "Entre um caminho de diretório: " dir

if [[ ! -d "$dir" ]]; then
    echo "Diretório não existe"
    exit 1
fi

renomeia
