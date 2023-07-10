#!/usr/bin/env bash
#
# Restauration/sauvergarde sur ovh
# 1 - Operation: save|restore
# 2 - Environenment: test|prd
# 3 - Site: daldo|cuba|carracedo|staff|repetitor
# -------------
# 1.0 version initiale

source "${OVH_BIN}/inc/ovh_funct.sh"

Operation=$1
Environ=$2
Site=$3
Usage="Sauvegarde/Restauration à partir de $\nUsage : ${0} save|restore prd|test site"
Date=$(date "+%Y-%m-%d")
ici=${PWD}
Reps="public folenski tmp sqldb backend vendor"

Par=( $( deploy2ovh ${Environ} ${Site} ) )
Par_local=${Par[0]}
Par_target=${Par[1]}
Par_target_root=${Par[2]}

echo "> Présence du répertoire d'archivage - ${OVH_ARCHIVE} - ?"
[ ! -d ${OVH_ARCHIVE} ] && exit_script ">>> KO" 2
echo ">>> OK"

case ${Operation} in
    put)
        echo -e "Déploiement du site <${Site}> en <${Environ}> sur OVH\n"
        echo "> Connection en FTP sur le host ${OVH_HOST}"
        put2ovh ${Par_local} ${Par_target} "${Reps}" "${Fics}"
        ;;
    save)
        Fichier="${Site}_${Environ}_${Date}.tar.gz"
        rm -f ${Fichier}
        cd ${OVH_ARCHIVE}
       
        if [ -d ${OVH_ARCHIVE}/${Site} ]; then
            rm -rf ${OVH_ARCHIVE}/${Site}
        fi
        echo ">>> Création du répertoire ${OVH_ARCHIVE}/${Site}"
        mkdir ${OVH_ARCHIVE}/${Site}

        echo "> Connection en FTP sur le host ${OVH_HOST}"
        echo ">> Synchronisation du site ${Site} en local"
        lftp ${OVH_USER}:${OVH_PASSWD}@${OVH_HOST} -e "mirror ${Par_target} ; exit "
        echo ">>> OK"

        echo ">> Preparation de l'archive ${Fichier}"
        tar czf ${Fichier} ${Site}
        echo ">>> OK"
        echo "> La sauvegarde: $(stat --printf="%n taille: %s date:%x\n" ${Fichier})"
        ;;
    restore)
        cd ${OVH_ARCHIVE}
        Fichier=$( ls -rt "${${OVH_ARCHIVE}}/${Site}_${Environ}_"* 2>/dev/null | tail -1 )
        [ -z ${Fichier} ] && exit_script "${Usage}\n>>>Fichier non trouvé" 2
        
        echo -e "> Restauration site ${Site} en ${Environ} sur OVH à partir du fichier ${Fichier}\n"

        echo ">> Décompression de l'archive ${Fichier}"
        tar xzf ${Fichier} 
        echo ">>> OK"
        
        echo "> Connection en FTP sur le host ${OVH_HOST}"
        echo ">> Synchronisation du site ${Site} en local vers OVH"
        lftp ${OVH_USER}:${OVH_PASSWD}@${OVH_HOST} -e "cd ${Par_cible_root}; mirror -Re ${Site}; exit"
        echo ">>> OK"

        ;;
    *)
        exit_script "${Usage}" 2  ;;
esac

echo "> Nettoyage "
rm -rf ${OVH_ARCHIVE}/${Site}

cd ${Ici}
echo "Fin"
