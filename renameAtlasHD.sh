#!/bin/bash

# Auteur : Philippe Paget
# Lience : MIT

IFS='ù'

check_errs()
{
        if [ "${1}" -ne "0" ]; then
                echo "ERREUR # ${1} : ${2}" 
                exit ${1}
        fi
}

MACHINE_TYPE=`uname -m`
if [ ${MACHINE_TYPE} == 'x86_64' ]; then
        renExec=nameMetaDat64
else
        renExec=nameMetaDat32
fi


for i in ./PVR/*
do
	curName=`$renExec $i/META.DAT`
	check_errs $? "Fichier $i/META.DAT au mauvais format ou manquant, arrêt du script"

	nbr=$(ls -1 $i/REC_??.TS | wc -l)
	if [ $nbr -eq 1 ]
	then
		mv "$i/REC_00.TS" "./PVR/$curName.ts"
		check_errs $? "Erreur lors du déplacement du fichier $i/REC_00.TS vers ./PVR/$curName.ts, arrêt du script"
	else
		numb=1
		for j in $i/REC_??.TS
		do
			mv "$j" "./PVR/$curName - $numb.ts"
			check_errs $? "Erreur lors du déplacement du fichier $j vers ./PVR/$curName - $numb.ts, arrêt du script"
			numb=$(($numb + 1))
		done
	fi
	rm -f "$i/META.DAT"
	rm -rf "$i/"
done
