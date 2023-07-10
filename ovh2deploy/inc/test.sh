#!/usr/bin/env bash

source ./ovh_funct.sh

OVH_LOCAL_DIR=~/perso

echo -e "prd staff \n$( deploy2ovh prd staff )"
echo -e "test cuba \n$( deploy2ovh test cuba )"
echo -e "prd staff \n$( deploy2ovh prd2 staff )"

ret=( $( deploy2ovh prd staff ) )
chp1=${ret[0]}
chp2=${ret[1]}
echo -e "champ1=${chp1} \nchamp2=${chp2}"