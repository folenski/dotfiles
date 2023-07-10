# v1.0 version initiale

exit_script()
# exit script
# $1 = Message 
# $2 = Valeur exit
{
    msg=${1:-"Bye..."}
    cr=${2:-0}

    if [ ${cr} -eq 1 ]; then printf "[Error] "; fi
    printf "${msg}\n" 
    exit ${cr}
}

deploy2ovh()
# $1 = prd ou test
# $2 = site à deployer
# retourne un tableau avec :
# repertoire local
# repertoire cible
# la racine cible
{
    env=$1
    site=$2
    rep_local=${OVH_LOCAL_DIR}
    site_local=${site/staff/staffkiev}
  
    ( [ ${env} != prd ] && [ ${env} != test ]  && exit_script "internal error, unknown ${env}" 1 )

    case ${site} in
        daldo|cuba|carracedo|staff|repetitor)
            echo "${rep_local}/www${site_local} www${env}/${site} www${env}"
            ;;
        *)
            exit_script "internal error, unknown ${site}" 1 ;;
    esac
} 

put2ovh()
{
    source=$1
    target=$2
    repertoires=( $3 )
    fichiers=( $4 )

    if [ ${#repertoires[@]} -ne 0 ]; then
        for rep in ${repertoires[*]}
        do
            echo ">> Synchronisation du répertoire ${rep}"
            lftp ${OVH_USER}:${OVH_PASSWD}@${OVH_HOST} -e "mirror -R ${source}/${rep} /${target}/${rep} ; exit "
            echo ">>> OK"
        done
    fi

    if [ ${#fichiers[@]} -ne 0 ]; then
        for fic in ${fichiers[*]}
        do
            echo ">> Synchronisation des fichiers  ${fic}"
            lftp ${Compte}:${Pass}@${Host} -e "cd ${Target}; mput ${Source}/${fic}; exit "
            echo ">>> OK"
        done
    fi
}
