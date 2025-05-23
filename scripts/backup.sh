#!/bin/bash

# Copia o diretório projetos para /tmp/backup
# Mostra mensagens de início e fim do processo

space() {
	printf "\n\n"
}


clear

space
echo "Criando um backup do diretório projetos em /tmp/backup"
echo "Iniciando..."
cp projetos ../../tmp/backup
echo "Finalizado."

