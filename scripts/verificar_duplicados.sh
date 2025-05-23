#!/bin/bash

# Recebe um diretório como argumento
# Identifica arquivos duplicados com md5sum ou sha256sum

space() {
	printf "\n\n"
}

verificar_duplicados() {
    local dir=$1

    echo "Verificando arquivos duplicados no diretório: $dir"
    
    find "$dir" -type f ! -empty -exec sha256sum {} + | sort | uniq -w64 -dD
}

clear
read -p "Entre um caminho de diretório para verificar duplicados: " dir

if [[ ! -d "$dir" ]]; then
    echo "Diretório não existe"
    exit 1
fi

verificar_duplicados "$dir"

space