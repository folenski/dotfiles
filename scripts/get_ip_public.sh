#!/usr/bin/env bash
# script to get public IP 
# 29/09/22 - v1

wget http://ippublique.fr -O - -o /dev/null | grep '</h1>' | sed -e 's#</h1.*## '
