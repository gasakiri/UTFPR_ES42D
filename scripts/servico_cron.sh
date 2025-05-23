#!/bin/bash

# Verifica o status do serviço cron
# Reinicia o serviço
# Verifica o status novamente

function space() {
	printf "\n\n"
}

clear
echo "Verificando status do serviço cron"
echo -e "$(systemctl status cron.service)"

space
echo "Reiniciando serviço cron"
sudo systemctl restart cron.service

space
echo -e "$(systemctl status cron.service)"
