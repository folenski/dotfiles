doubleval(){
        # Alias de la fonction floatval
        # 
        # EXECUTION
        # =========
        # doubleval "$var"
        #
        # RETOUR
        # ======
        # Retourne la valeur flottante de la variable donnÃ©e ou 0 en cas d'erreur
        # 
	floatval "$1"
}

empty(){
        # DÃ©termine si une variable est vide
        # 
        # EXECUTION
        # =========
        # empty "$var"
        #
        # RETOUR
        # ======
        # Code retour 0 en cas de succÃ¨s et 1 en cas d'erreur.
        # 
        typeset VAR=$(sed "s/ //g" <<< "$1")
        ( [ -z "$VAR" ] || grep -E -q '^0*.?0+$' <<< "$VAR" ) && return 0 || return 1
}

floatval(){
        # Convertit une chaine en nombre Ã  virgule flottante
        # Une donnÃ©e numÃ©rique valide est un signe optionnel, suivi par un ou plusieurs
        # chiffres, suivi par un point dÃ©cimal optionnel, suivi par un ou plusieurs
        # chiffres optionnels,  suivi par un exposant optionnel.
        # Un exposant est reprÃ©sentÃ© par la lettre 'e' ou 'E', suivi d'un signe optionnel, 
        # suivi d'un ou plusieurs chiffres.
        # 10 / 10.5 / -5.7 / 10. / 4e5 / 5.6E7
        #
        # EXECUTION
        # =========
        # floatval "$var"
        #
        # RETOUR
        # ======
        # Retourne la valeur flottante de la variable donnÃ©e ou 0 en cas d'erreur
        #
	typeset VAR=$(grep -E -o '^-?[0-9]*\.?[0-9]+((e|E)-?[0-9]+)?' <<< "$1")
	if [ -n "$VAR" ]; then
		VAR=$(sed -r 's/(e|E)/\*10\^/g' <<< "$VAR")
		calcul "1*$VAR"
		return 0
	fi
	echo 0 && return 1
}

intval(){
        # Retourne la valeur numÃ©rique entiÃ¨re Ã©quivalente d'une variable
        #
        # EXECUTION
        # =========
        # intval "$var"
        #
        # RETOUR
        # ======
        # Retourne une valeur de type entier en cas de succÃ¨s ou 0 en cas d'erreur.
        # 
        typeset VAR=$(grep -E -o '^-?[0-9]+' <<< "$1")
        if [ -n "$VAR" ]; then
                calcul "1*$VAR"
                return 0
        fi
        echo 0 && return 1
}

is_array(){
        # DÃ©termine si la variable donnÃ©e est un tableau.
        #
        # EXECUTION
        # =========
        # array=(a b c d e f)
        # is_array "${array[@]}"
        #
        # RETOUR
        # ======
        # Code retour 0 en cas de succÃ¨s et 1 en cas d'erreur.
        # 
        typeset VAR=("$@")
        if empty ${VAR[*]}; then
                return 1 
        elif [ ${#VAR[*]} -gt 1 ]; then
                return 0
        else
                return 1
        fi                        
}

is_bool(){
	# DÃ©termine si la variable est un boolÃ©en
	#
        # EXECUTION
        # =========
        # is_bool "$var"
        #
        # RETOUR
        # ======
        # Code retour 0 en cas de succÃ¨s et 1 en cas d'erreur.
        #
	grep -E -q -i '^(true|false|1|0)$' <<< "$1" && return 0 || return 1
}

is_callable(){
	# DÃ©termine si la variable est une commande
        #
        # EXECUTION
        # =========
        # is_callable "$var"
        #
        # RETOUR
        # ======
        # Code retour 0 en cas de succÃ¨s et 1 en cas d'erreur.
        #
	type $1 >/dev/null 2>&1 && return 0 || return 1
}

is_double(){
        # Alias de la fonction is_float
        #
        # EXECUTION
        # =========
        # is_double "$var"
        #
        # RETOUR
        # ======
        # Code retour 0 en cas de succÃ¨s et 1 en cas d'erreur.
        #
        is_float "$1"
}

is_float(){
        # DÃ©termine si une variable est de type nombre dÃ©cimal
        #
        # EXECUTION
        # =========
        # is_float "$var"
        #
        # RETOUR
        # ======
        # Code retour 0 en cas de succÃ¨s et 1 en cas d'erreur.
        #
        grep -E -q '^-?[0-9]*\.[0-9]+((e|E)-?[0-9]+)?$' <<< "$1" && return 0 || return 1
}

is_int(){
        # DÃ©termine si une variable est de type nombre entier.
        #
        # EXECUTION
        # =========
        # is_int "$var"
        #
        # RETOUR
        # ======
        # Code retour 0 en cas de succÃ¨s et 1 en cas d'erreur.
        #
        grep -E -q '^-?[0-9]+$' <<< "$1" && return 0 || return 1
}

is_integer(){
        # Alias de la fonction is_int
        #
        # EXECUTION
        # =========
        # is_integer "$var"
        #
        # RETOUR
        # ======
        # Code retour 0 en cas de succÃ¨s et 1 en cas d'erreur.
        #
	is_int "$1"
}

is_long(){
        # Alias de la fonction is_int
        #
        # EXECUTION
        # =========
        # is_long "$var"
        #
        # RETOUR
        # ======
        # Code retour 0 en cas de succÃ¨s et 1 en cas d'erreur.
        #
        is_int "$1"
}

is_numeric(){
        # DÃ©termine si une variable est un type numÃ©rique
        #
        # EXECUTION
        # =========
        # is_numeric "$var"
        #
        # RETOUR
        # ======
        # Code retour 0 en cas de succÃ¨s et 1 en cas d'erreur.
        # 
        grep -E -q '^(\+|-)?[0-9]*\.?[0-9]+((e|E)-?[0-9]+)?$' <<< "$1" && return 0 || return 1
}

is_real(){
        # Alias de la fonction is_float
        # 
        # EXECUTION
        # =========
        # is_real "$var"
        #
        # RETOUR
        # ======
        # Code retour 0 en cas de succÃ¨s et 1 en cas d'erreur.
        # 
        is_float "$1"
}

calcul(){
        # Calcul le rÃ©sultat de l'opÃ©ration passÃ©e en paramÃ¨tre 
        # Ã  l'aide de la commande bc
        # Pour installer la commande bc : sudo apt-get install bc
        #
        # EXECUTION
        # =========
        # calcul "5*4"
        # calcul "(5*4/20)*2"
        # var=$(calcul "5*4")
        #
        # RETOUR
        # ======
        # Retourne le rÃ©sultat de l'opÃ©ration ou le code retour 1 en cas d'Ã©chec
        #
	( echo "$1" | bc -l ) && return 0 || return 1
}

getdecsep(){
        # Retourne le sÃ©parateur dÃ©cimal paramÃ©trÃ© sur le sytÃ¨me
        # en fonction de la variable locale installÃ©e et dÃ©finie par dÃ©faut.
        #
        # EXECUTION
        # =========
        # getdecsep
        # var=$(getdecsep)
        #
        # RETOUR
        # ======
        # Retourne un point '.' ou une virgule ','
        # 
	( printf "%1.1f" 1 | sed "s/[0-9]//g" ) && return 0 || return 1
}

commatodot(){
        # Remplace la virgule ',' par le point '.' dans les 
        # variables reprÃ©sentant des valeurs dÃ©cimales.
        # 10,5 --> 10.5
        #
        # EXECUTION
        # =========
        # commatodot "$var"
        # var=$(commatodot "$var")
        #
        # RETOUR
        # ======
        # Retourne la valeur remplacÃ©e en cas de succÃ¨s ou le code erreur 1 en cas d'Ã©chec.
        #
        typeset VAR=$(sed "s/,/\./" <<< "$1")
	is_float "$VAR" && ( echo "$VAR" && return 0 ) || return 1 
}

dottocomma(){
        # Remplace le point '.' par la virgule ',' dans les 
        # variables reprÃ©sentant des valeurs dÃ©cimales.
        # 10.5 --> 10,5
        #
        # EXECUTION
        # =========
        # dottocomma "$var"
        # var=$(dottocomma "$var")
        #
        # RETOUR
        # ======
        # Retourne la valeur remplacÃ©e en cas de succÃ¨s ou le code erreur 1 en cas d'Ã©chec.
        #
	is_float "$(commatodot "$1")" && ( sed "s/\./,/" <<< "$1" && return 0 ) || return 1
}

tolocaldecsep(){
        # Remplace le point '.' par le sÃ©parateur dÃ©cimal
        # paramÃ©trÃ© sur le systÃ¨me dans les variables 
        # reprÃ©sentant des valeurs dÃ©cimales.
        #
        # EXECUTION
        # =========
        # tolocaldecsep "$var"
        # var=$(tolocaldecsep "$var")
        #
        # RETOUR
        # ======
        # Retourne la valeur remplacÃ©e en cas de succÃ¨s.
        # La valeur 0 en cas d'erreur et le code retour 1.
        # 
	if is_float "$(commatodot "$1")"; then
	        sed "s/\./$(getdecsep)/" <<< "$1" && return 0
        else
                echo 0 && return 1
        fi
}

prerequis(){
        # Test si la ou les commandes passÃ©es
        # en paramÃ¨tres sont bien installÃ©es
        # sur le systÃ¨me.
        #
        # EXECUTION
        # =========
        # prerequis vim grep ...
        # if prerequis vim >/dev/null; then ...; fi
        # prerequis vim >/dev/null && ... || ...
        #
        # RETOUR
        # ======
        # Code retour 0 en cas de succÃ¨s et 1 en cas d'erreur ainsi qu'un message explicatif.
        # 
        typeset VAR
        for VAR in "$@"; do
                which "$VAR" >/dev/null || ( echo -e "Le programme '$VAR' n'est pas encore installÃ©.\n\
Vous pouvez l'installer en tapantÂ : \n\
sudo apt-get install $VAR" && return 1 )
        done
}

getipv4(){
	# Extrait une ou plusieurs adresses IPV4 
	# d'une chaine de caractÃ¨res passÃ©e en paramÃ¨tre.
	#
	# EXECUTION
	# =========
	# RET=$(getipv4 "$VAR")
	#
	# RETOUR
	# ======
	# Retourne une chaine contenant toutes
	# les adresses IPV4 extraites de la chaine
	# sÃ©parÃ©es par un espace.
	#
	typeset VAR=$(grep -E -o '([0-9]{1,3}\.){3}[0-9]{1,3}' <<< "$1")
	typeset ADRIPV4=""
	while read IPV4; do
		ADRIPV4="$ADRIPV4 $IPV4"
	done <<< "$VAR"
	ADRIPV4=$(sed "s/^ //" <<< "$ADRIPV4")
	echo "$ADRIPV4" && return 0
}

ltrim(){
	# Supprime tous les espaces Ã  gauche 
        #
        # EXECUTION
        # =========
        # ltrim "$var"
        #
        # RETOUR
        # ======
        # Retourne la valeur sans les espaces Ã  gauche et le code retour 0.
        #
	typeset VAR=$(sed "s/^ *//g" <<< "$1")
	echo "$VAR" && return 0
}

rtrim(){
	# Supprime tous les espaces Ã  droite
        #
        # EXECUTION
        # =========
        # rtrim "$var"
        #
        # RETOUR
        # ======
        # Retourne la valeur sans les espaces Ã  droite et le code retour 0.
        #
	typeset VAR=$(sed "s/ *$//g" <<< "$1")
	echo "$VAR" && return 0
}

trim(){
	# Supprime tous les espaces Ã  gauche et Ã  droite
        #
        # EXECUTION
        # =========
        # trim "$var"
        #
        # RETOUR
        # ======
        # Retourne la valeur sans les espaces Ã  gauche et Ã  droite et le code retour 0.
        #
	typeset VAR="$1"
	VAR=$(ltrim "$VAR")
	VAR=$(rtrim "$VAR")
	echo "$VAR" && return 0
}

gettype(){
	# Retourne le type de la variable.
	#
	# Les typespouvant Ãªtre retournÃ©s (Par ordre de dÃ©termination)
	# 0 - empty
	# 1 - boolÃ©en
	# 2 - integer
	# 3 - double
	# 4 - array
	# 5 - string
        #
        # EXECUTION
        # =========
        # gettype "$var"
        #
        # RETOUR
        # ======
        # Retourne le type de la variable et le code retour 0.
        #
	if empty "$1"; then
		echo "empty"
	elif is_bool "$1"; then
		echo "boolean"
	elif is_int "$1"; then
		echo "integer"
	elif is_float "$1"; then
		echo "double"
	elif is_array "$@"; then
		echo "array"
	else
		echo "string"
	fi
	return 0
}

abs(){
	# Retourne la valeur absolue du nombre "$var".
        #
	# EXECUTION
        # =========
        # abs "$var"
        #
        # RETOUR
        # ======
        # Retourne la valeur absolue et le code retour 0.
	# Ou 0 et le code retour 1 en cas d'erreur
        #
	if is_numeric "$1"; then
		typeset VAR=$(sed "s/^-//g" <<< "$1")
		echo "$VAR" && return 0
	fi
	echo 0 && return 1
}

ceil(){
	# Retourne la valeur arrondie Ã  l'entier supÃ©rieur
	#
	# EXECUTION
        # =========
        # ceil "$var"
        #
        # RETOUR
        # ======
        # Retourne la valeur arrondie Ã  l'entier supÃ©rieur et le code retour 0.
	# Ou 0 et le code retour 1 en cas d'erreur
        #
	if is_numeric "$1"; then
		typeset VAR=$(sed "s/\.0*$//g" <<< "$1")
		typeset ENT=$(intval "$VAR")
		if [ $(calcul "$VAR<0") -eq 1 ]; then
			VAR="$ENT"
		fi
		if is_float "$VAR"; then
			VAR=$(calcul "$ENT+1")
		fi
		echo "$VAR"
		return 0
	fi
	echo 0 && return 1
}

floor(){
	# Retourne la valeur arrondie Ã  l'entier infÃ©rieur
        #
	# EXECUTION
        # =========
        # floor "$num"
        #
        # RETOUR
        # ======
        # Retourne la valeur arrondie Ã  l'entier infÃ©rieur et le code retour 0.
        # Ou 0 et le code retour 1 en cas d'erreur
        #
        if is_numeric "$1"; then
                typeset VAR=$(sed "s/\.0*$//g" <<< "$1")
                typeset ENT=$(intval "$VAR")
                if [ $(calcul "$VAR<0") -eq 1 ]; then
                        VAR=$(calcul "$ENT-1")
                fi
                if is_float "$VAR"; then
                        VAR="$ENT"
                fi
                echo "$VAR"
                return 0
        fi
        echo 0 && return 1
}

fmod(){
	# Retourne le reste de la division
	#
	# EXECUTION
        # =========
        # fmod "$num1" "$num2"
        #
        # RETOUR
        # ======
        # Retourne le reste de la division et le code retour 0.
        # Ou 0 et le code retour 1 en cas d'erreur
        #
	if is_numeric "$1" && is_numeric "$2"; then
		calcul "scale=0; $1%$2"
		return 0
	fi
	echo 0 && return 1
}
