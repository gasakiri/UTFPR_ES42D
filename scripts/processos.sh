#!/bin/bash

# Lista todos os processos em execução
# Mostra o processo que mais consome CPU
# Finaliza esse processo

function space() {
	printf "\n\n"
}

clear

echo "Listando processos do sistema"
ps -aux

space
echo "Processo que utiliza mais CPU"
ps -aux --sort=-pcpu | head -n 2
processo=$(ps -eo comm --sort=-pcpu | head -n 2 | tail -n 1)
m_pid=$(ps -eo pid --sort=-pcpu | head -n 2 | tail -n 1 | awk {'print $1'})

space
echo "Finalizando $processo PID $m_pid"
kill $m_pid


