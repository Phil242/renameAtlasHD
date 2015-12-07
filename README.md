**Introduction :**

Le récepteur Atlas HD 200 dispose d’une fonction d’enregistrement des programmes satellites sur une clé USB insérée en face avant de l’appareil. Si vous souhaitez regarder les programmes 
sur une autre récepteur, un lecteur multimédia ou même les archiver sur un serveur pour les regarder plus tard, le format de stockage sur la clé n’est pas vraiment sympa. Cette outil 
permet de renommer au mieux les fichiers afin de facilité le tri des programmes en se basant sur les informations présentes dans les fichiers non documentés « META.DAT ».
Ce programme fonctionne uniquement *sous Linux* mais j’ai inclus tous les détails techniques si d’aventure un développeur Windows souhaiterait réaliser le portage de l’application.


**Licence :**
Ce programme est diffusé sous licence MIT. Détail dans le fichier licence.txt (en bref : c’est du logiciel libre et c’est open source).


**Fonctionnement :**
La structure à la racine de la clé USB est toujours la même, à savoir un répertoire PVR avec autant de sous-répertoires REC_XXXX que de programmes enregistrés. Tous les fichiers .TS des 
sous-répertoires sont renommés avec la date, nom de la chaine, nom du programme (s’il est disponible dans le META.DAT) et la durée. Si l’émission est découpée en plusieurs fichiers, un 
numéro est ajouté à la fin de chaque fichier.


**Exemple :**

PVR/
├── REC_0001
│   ├── META.DAT
│   └── REC_00.TS
├── REC_0002
│   ├── META.DAT
│   └── REC_00.TS
├── REC_0003
│   ├── META.DAT
│   ├── REC_00.TS
│   └── REC_01.TS
├── REC_0004
│   ├── META.DAT
│   ├── REC_00.TS
│   └── REC_01.TS
├── REC_0005
│   ├── META.DAT
│   └── REC_00.TS
├── REC_0006
│   ├── META.DAT
│   └── REC_00.TS
├── REC_0007
│   ├── META.DAT
│   └── REC_00.TS
└── REC_0008
    ├── META.DAT
    ├── REC_00.TS
    └── REC_01.TS

Qui donne une fois remise en forme : 

PVR/
├── 2015-09-06 - Discovery hd - 0H48.ts
├── 2015-09-09 - Canal+ hd - 1H38.ts
├── 2015-09-13 - Discovery hd - 0H49.ts
├── 2015-09-20 - Discovery hd - 0H48.ts
├── 2015-09-22 - France 2 hd - 2H00.ts
├── 2015-09-27 - Discovery hd - 1H34 - 1.ts
├── 2015-09-27 - Discovery hd - 1H34 - 2.ts
├── 2015-10-04 - Discovery hd - 1H34 - 1.ts
├── 2015-10-04 - Discovery hd - 1H34 - 2.ts
├── 2015-10-11 - Discovery hd - 1H33 - 1.ts
└── 2015-10-11 - Discovery hd - 1H33 - 2.ts


**Installation :**

Les 3 fichiers exécutables sont à copier dans le répertoire /usr/local/bin et il faut autoriser leurs exécution : « sudo cp renameAtlasHD.sh nameMetaDat32 nameMetaDat64 /usr/local/bin/ » 
et « sudo chmod +x /usr/local/bin/renameAtlasHD.sh  /usr/local/bin/nameMetaDat32  /usr/local/bin/ nameMetaDat64»


**Utilisation :**

Monter la clé USB dans le répertoire de votre choix, placez-vous dans ce répertoire  et lancer la commande « renameAtlasHD.sh ».
La commande termine sans rien écrire à l’écran. Dans le dossier PVR on trouve alors tous les fichiers renommés et les sous-répertoires sont supprimés. En cas d’erreur le script sort et 
en affiche la raison.


**Compilation (optionnelle) :**

Les binaires exécutables 32 et 64 linkés statiquement sont fournis pour vous éviter de compiler si vous n’êtes pas familié avec tout ça. Cependant, comme il est toujours bon de 
recompiler soit même les programmes des inconnus dans la rue, vous pouvez le faire ainsi : « gcc nameMetaDat.c -o nameMetaDatXX » XX étant 32 ou 64 suivant si vous êtes en 32/64 bits.


**Reverse engineering du META.DAT :**

Voici le repérage des données que j’ai identifié :
Offset Longueur Description
0x015  (0x21)   Nom de la chaine
0x037  (0x21)   Nom du provider
0x0F9  (0x3F)   Nom de du programme EPG
0x138  (0x02)   Heure debut SAT/GMT
0x13C  (0x04)   Date annee(2 octets),mois,jour
0x148  (0x03)   Durée heure,min,sec

