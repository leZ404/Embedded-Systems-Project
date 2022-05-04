# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Epreuve Finale
+ Section #  : 2
+ Équipe #   : 3544
+ Correcteur : Marianne P-B

# LISIBILITÉ
## En-têtes en début de programme   

| Pénalité par erreur                          | -1.5       |
| -------------------------------------------- | ---------- |
| Noms des auteurs                             |            |
| Description du programme                     |            |
| Identifications matérielles (Broches I/O)    |            |
| Table des états ou autres s'il y a lieu      |            |
| __Résultat partiel__                         | __(1.5/1.5)__ |

## Identificateurs significatifs (Autodocumentation)

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de *chiffres magiques*               | (0/0.5)     |
| Noms de variables décrivent l'intention      | (0.5/0.5)     |
| Noms de fonctions décrivent l'intention      | (0.5/0.5)     |
| __Résultat partiel__                         | __(1.0/1.5)__ |

## Commentaires pertinents

Bonnes raisons d'un commentaire
 + Explication d'un algorithme 
 + Procédure peu évidente (ou *hack*)
 + Référence d'extraits de code copiés d'Internet
 + Détail du POURQUOI d'un extrait de code

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| __Résultat partiel__                         | __(1.0/1.0)__ |


## Indentation   

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Indentation structurée                       | (0.5/0.5)     |
| Indentation uniforme dans le programme       | (0.5/0.5)     |
| __Résultat partiel__                         | __(1.0/1.0)__ |


# MODULARITÉ ET COMPRÉHENSION
## Fonctions bien définies

| Pénalité par erreur                          | -0.5       |
| -------------------------------------------- | ---------- |
| Responsabilité unique d'une fonction         |            |
| Maximum de 4 paramètres                      |            |
| Absence de code dupliqué                     |            |
| etc                                          |            |
| __Résultat partiel__                         | __(1.0/1.0)__ |


## Bonne application des concepts de programmation et systèmes embarqués

| Pénalité par erreur                          | -1.0       |
| -------------------------------------------- | ---------- |
| Utilisation appropriée des registres         |            |
| Machine à états codée clairement             |            |
| Délais et minuteries utilisés judicieusement |            |
| PWM bien établi                              |            |
| Scrutation et interruptions bien utilisées   |            |
| etc                                          |            |
| __Résultat partiel__                         | __(4.0/4.0)__ |

# FONCTIONNALITÉS
## Git

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Fichiers aux bons endroits                   | (0/1.5)     |
| Absence de fichiers inutiles                 | (0/1.5)     |
| __Résultat partiel__                         | __(0/3.0)__ |


## Compilation    

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Absence de messages d'erreurs de compilation | (1.5/1.5)     |
| Absence de messages d'attention (*warning*)  | (0.5/0.5)     |
| __Résultat partiel__                         | __(2.0/2.0)__ |
   

## Évaluation boîte noire  

| Points importants                            | Poids      |
| -------------------------------------------- | ---------- |
| Cas normal de fonctionnement                 | (2.5/2.5)     |
| Cas limites observables                      | (2.5/2.5)     |
| __Résultat partiel__                         | __(5.0/5.0)__ |

# Résultat

__Total des points: 16.5/20__

# Commentaires du correcteur:

Fichier pas au bon endroit, repertoire contient fichier inutiles


# Basé sur le commit suivant
```
commit ef7501b5fff1219d083ee4347ac243f689bf2610
Author: Ashveer Golam <ashveer-kumar.golam@polymtl.ca>
Date:   Wed Apr 20 07:57:08 2022 -0400

    projet final 4.0
```

# Fichiers indésirables pertinents
_delay_ms(1000); - chiffre magique, notamment dans le tour

# Tous les fichiers indésirables
```
TP -Equipe 35/tp3/pb1/pb1.cpp.elf
TP -Equipe 35/tp3/pb1/pb1.cpp.elf.map
TP -Equipe 35/tp3/pb1/pb1.cpp.hex
TP -Equipe 35/tp3/pb1/pb1.d
TP -Equipe 35/tp3/pb1/pb1.o
TP -Equipe 35/tp4-Exemple prof/TP1.elf
TP -Equipe 35/tp4-Exemple prof/TP1.elf.map
TP -Equipe 35/tp4-Exemple prof/TP1.hex
TP -Equipe 35/tp4-Exemple prof/main.d
TP -Equipe 35/tp4-Exemple prof/main.o
TP -Equipe 35/tp6/pb2/can.d
TP -Equipe 35/tp6/pb2/can.o
TP -Equipe 35/tp6/pb2/pb2.cpp.elf
TP -Equipe 35/tp6/pb2/pb2.cpp.elf.map
TP -Equipe 35/tp6/pb2/pb2.cpp.hex
TP -Equipe 35/tp6/pb2/pb2.d
TP -Equipe 35/tp6/pb2/pb2.o
tp/projetFinal/exec/executable2.elf.map
tp/projetFinal/exec/main.o
tp/projetFinal/lib/Makefile~
tp/tp9/lib/DEL.d
tp/tp9/lib/DEL.o
tp/tp9/lib/Makefile~
tp/tp9/lib/Moteur.d
tp/tp9/lib/Moteur.o
tp/tp9/lib/bouton.d
tp/tp9/lib/bouton.o
tp/tp9/lib/can.d
tp/tp9/lib/can.o
tp/tp9/lib/debug.d
tp/tp9/lib/debug.o
tp/tp9/lib/libtest.a
tp/tp9/lib/memoire_24.d
tp/tp9/lib/memoire_24.o
tp/tp9/lib/print.d
tp/tp9/lib/print.o
tp/tp9/lib/sonorite.d
tp/tp9/lib/sonorite.o
tp/tp9/src prog 1/executable.elf
tp/tp9/src prog 1/executable.elf.map
tp/tp9/src prog 1/executable.hex
tp/tp9/src prog 1/main.d
tp/tp9/src prog 1/main.o
tp/tp9/src prog 2 /executable2.elf
tp/tp9/src prog 2 /executable2.elf.map
tp/tp9/src prog 2 /executable2.hex
tp/tp9/src prog 2 /main2.d
tp/tp9/src prog 2 /main2.o
```

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `projet/lib`
```
make: *** correction_final/3544/projet/lib : Aucun fichier ou dossier de ce type. Arrêt.

```

## Sortie de `make` dans `projet/app`
```
make: *** correction_final/3544/projet/app : Aucun fichier ou dossier de ce type. Arrêt.

```
