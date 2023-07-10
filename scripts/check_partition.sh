#!/usr/bin/env bash
# Script pour vérifier l'occupation des partitions'
# 

Seuil=80
for alerte in $(df -h | awk '{ print $5 }' | grep '%' | sed -e 's#%##') 
do
    if [ $alerte -gt ${Seuil} ]; then
        echo "Occupation d'une partition à ${Seuil}%!! >>>  df -h"
	    exit 1
    fi
done
echo "Controle OK"
exit 0