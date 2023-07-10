#!/usr/bin/env python3
# Script générique pour la lecture d'un menu passé en paramétre (fichier json)
#
import json, sys, os

class bcolors:
    OK = "\033[92m"  # GREEN
    WARNING = "\033[93m"  # YELLOW
    FAIL = "\033[91m"  # RED
    RESET = "\033[0m"  # RESET COLOR
    CLEAR = "\033c"  # CLS ECRAN
    UNDER = "\033[4m"

def affiche_menu(menu, est_racine=True):
    # Afficher un menu
    cpt = 1

    if "menu" not in menu:
        print(bcolors.Fail + "Erreur! pas de sous menu\n" + bcolors.RESET)
        return -1

    print(bcolors.CLEAR)
    print(bcolors.OK + menu["titre"])

    if "souligner" in menu and menu["souligner"]:
        print(("-" * len(menu["titre"])) + bcolors.RESET)
    print(bcolors.WARNING + menu["commentaire"] + "\n" + bcolors.RESET)

    for ligne in menu["menu"]:
        if "menu" in ligne:
            print(bcolors.FAIL + ">", end="")
        else:
            print(bcolors.FAIL + "?", end="")
        print(f"{bcolors.OK} {cpt} : {ligne['titre'].capitalize()}{bcolors.RESET}", end="")
        if "commentaire" in ligne:
            print(", " + ligne["commentaire"].capitalize())
        else:
            print("")
        cpt += 1

    print(bcolors.FAIL + "\n<" + bcolors.RESET, end="")
    if est_racine:
        print(f"{bcolors.OK} {cpt} : Sortir {bcolors.RESET}")
    else:
        print(f"{bcolors.OK} {cpt} : Retour au menu précédent {bcolors.RESET}")

    return cpt

##############################################################################
#                               MAIN
# lecture du fichier de configuration, valeur par défaut menu.json
##############################################################################
menu = []  # on stocke l'aborence 
fichier_json = "menu.json"; 

try:
    if len(sys.argv) == 2:
        fichier_json = sys.argv[1]

    with open(fichier_json) as json_data:
        data_menu = json.load(json_data)
except FileNotFoundError:
    sys.exit(f"Erreur! pendant la lecture du fichier {fichier_json} json")
finally:
    json_data.close()

menu.append(data_menu)
menu_lvl = 0

# On boucle sur les menus
while True:
    nbr = affiche_menu(menu[menu_lvl], menu_lvl == 0)

    if nbr <-1:
        exit(0)

    print("\033[s")
    # On boucle sur le choix
    while True:
        choix_inp = input("$ ")
        if choix_inp.isnumeric():
            choix = int(choix_inp) - 1
            if 0 <= choix < nbr:
                break
        print(bcolors.FAIL + "[Choix invalide]" + bcolors.RESET)
        print("\033[u")

    # On gère le dernier choix de la liste ( sortir ou retour)
    if choix == nbr - 1:
        if menu_lvl == 0:
            print("Au revoir...")
            exit(0)
        else:
            menu_lvl -= 1
            menu.pop()
            continue

    if "menu" in menu[menu_lvl]["menu"][choix]:
        menu.append(menu[menu_lvl]["menu"][choix])
        menu_lvl += 1
        continue

    if "commande" in menu[menu_lvl]["menu"][choix]:
        os.system(menu[menu_lvl]["menu"][choix]["commande"])
    else:
        print(f"{bcolors.FAIL}Erreur! Pas de commande {bcolors.RESET}")
    exit(0)

print("Fin")
