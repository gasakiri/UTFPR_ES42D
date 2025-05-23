#!/bin/bash

# Recebe um número e informa se é primo ou não

space() {
    printf "\n\n"
}

primo() {

    if (( num <= 1)); then
        echo "$num não é primo"
        exit
    fi

    for ((i=2; i<=num-1; i++)); do
        if [ $((num % i)) -eq 0 ]; then
            echo "$num não é primo"
            return
        fi
    done
    echo "$num é primo"
    return
}

clear
space
read -p "Digite um número: " num
primo