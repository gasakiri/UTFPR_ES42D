#!/bin/bash

# Gera senhas aleatórias de 12 caracteres (com letras, números e símbolos)
# A quantidade de senhas deve ser passada como argumento

space() {
	printf "\n\n"
}

gerar_senha_fixed() {
    local quantidade=$1
    local caracteres=( {a..z} {A..Z} {0..9} "!" "@" "#" "$" "%" "^" "&" "*" "(" ")" "_" "+" )
    local conjunto=${#caracteres[@]}

    for (( i=0; i<quantidade; i++ )); do
        local senha=""
        for (( j=0; j<12; j++ )); do
            local random_index=$(( RANDOM % conjunto ))
            senha+="${caracteres[$random_index]}"
        done
        echo "$senha"
    done
}

clear
echo "Gerador de senhas"
read -p "Digite a quantidade de senhas para serem geradas: " quantidade
gerar_senha_fixed $quantidade

space
