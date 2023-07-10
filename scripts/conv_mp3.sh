#!/usr/bin/env bash
# Permet d'extraire le son d'une video, basé sur ffmpeg

fichier=$1
codec=${2-"aac"}

( [ -z ${fichier} ] && echo "Usage $0 video [son]" ) && exit 1
( [ ! -f ${fichier} ]  && echo "Le fichier $fichier n'existe pas" ) && exit 1

echo Convertion du fichier : ${fichier}
echo Le fichier son est    : ${codec}
ffmpeg -i "${fichier}" -vn -acodec copy "${codec}"
