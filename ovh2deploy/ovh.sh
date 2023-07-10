#!/usr/bin/env bash
# Lancement du menu de déploiement, les variables suivantes doivent être définis dans l'environnement :
# OVH_USER, OVH_HOST, OVH_PASSWD
# v1.0 version initiale
# v1.1 maj variable script
# v1.2 on retire les variables de connexions à OVH

Function="${OVH_BIN}/inc/ovh_funct.sh"

( [ ! -f ${Function} ]  && echo -e "Error file ${Function} not exist" ) && exit 1
source ${Function}

[[ -z ${OVH_USER} || -z ${OVH_HOST} || -z ${OVH_PASSWD} ]] && exit_script "Please set variables OVH..." 1

${OVH_BIN}/menu.py ${OVH_BIN}/inc/ovh.json

exit_script