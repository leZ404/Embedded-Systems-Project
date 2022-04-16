# Polytechnique Montréal

Département de génie informatique et génie logiciel

INF1900: Projet initial de système embarqué

# Grille de correction des programmes:

Identification:
+ Travail    : Mise en commun du code et formation de librairies
+ Section #  : 2
+ Équipe #   : 3544
+ Correcteur : Carl Hewett

# CODE

| Points importants                                        | Poids       |
| -------------------------------------------------------- | ----------- |
| La qualités et le choix de vos portions de code choisies | (4.0/5.0)      |
| * `debug.cpp` vide | |
| * Il manquerait les fonctions pour initialiser les Timer (à part Moteur) | |
| * Plusieurs lignes commentées un peu partout... | |
| La qualités de vos modifications aux Makefiles           | (3.5/5.0)      |
| * Il ne devrait pas avoir de `make install` dans le Makefile pour lib | |
| * Il manque `make debug` pour le Makefile de exec | |
| __Résultat partiel__                                     | __(7.5/10.0)__ |

# RAPPORT

| Points importants                                                           | Poids      |
| --------------------------------------------------------------------------- | ---------- |
| Explications cohérentes par rapport au code retenu pour former la librairie | (0.0/2.0)     |
| Explications cohérentes par rapport aux Makefiles modifiés                  | (0.0/2.0)     |
| Explications claires avec un bon niveau de détails                          | (0.0/2.0)     |
| Bon français                                                                | (0.0/1.0)     |
| __Résultat partiel__                                                        | __(0.0/7.0)__ |

# GÉNÉRALITÉS
## Bonne soumission de l'ensemble du code et du rapport selon le format demandé 

| Pénalité par erreur      | -0.5       |
| ------------------------ | ---------- |
| compilation sans erreurs |            |
| * C'est quoi `testpush`?                     |            |
| * Fichiers indésirables        |            |
| * Makefile exec ne compile pas: `debug.cpp` ne devrait pas être dans `PRJSRC` | |
| * Warning: `#warning "F_CPU not defined for <util/delay.h>"` | |
| * Warning: `control reaches end of non-void function` | |
| * Warning: `warning: "F_CPU" redefined` | |
| __Résultat partiel__     | __(1.0/3.0)__ |


# Résultat

__Total des points: 8.5/20__

# Commentaires du correcteur:



# Basé sur le commit suivant
```
commit ce4cd3a71a228cad5ecf6d079dd14731bc2026f6
Author: Zied Kaabi <zikaa@l3818-16.info.polymtl.ca>
Date:   Sun Mar 13 16:57:49 2022 -0400

    version final tp7/tp8
```

# Fichiers indésirables pertinents
```
tp/tp7/exec/Makefile~
tp/tp7/lib/Makefile~
```

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
tp/tp7/exec/Makefile~
tp/tp7/lib/Makefile~
```

# Sorties de `make` dans les sous-répertoires

## Sortie de `make` dans `tp/tp7/lib`
```
make: Entering directory '/home/gigl/inf1900/correction_tp7/3544/tp/tp7/lib'
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c Moteur.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c print.cpp
In file included from print.cpp:3:
/usr/avr/include/util/delay.h:92:3: warning: #warning "F_CPU not defined for <util/delay.h>" [-Wcpp]
   92 | # warning "F_CPU not defined for <util/delay.h>"
      |   ^~~~~~~
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c memoire_24.cpp
memoire_24.cpp:30:3: warning: #warning "F_CPU pas defini pour 'memoire_24.cpp'" [-Wcpp]
   30 | # warning "F_CPU pas defini pour 'memoire_24.cpp'"
      |   ^~~~~~~
In file included from memoire_24.cpp:34:
memoire_24.h:17:1: warning: "/*" within comment [-Wcomment]
   17 | /*                                                                            */
      |  
memoire_24.cpp: In member function 'uint8_t Memoire24CXXX::lecture(uint16_t, uint8_t*, uint8_t)':
memoire_24.cpp:280:7: warning: this 'while' clause does not guard... [-Wmisleading-indentation]
  280 |       while ((TWCR & _BV(TWINT)) == 0) ; // Attente de fin de transmission
      |       ^~~~~
memoire_24.cpp:281:10: note: ...this statement, but the latter is misleadingly indented as if it were guarded by the 'while'
  281 |          *donnee++ = TWDR;               // Lecture
      |          ^
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c can.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c bouton.cpp
bouton.cpp: In member function 'bool Bouton::appuiBouton(uint8_t)':
bouton.cpp:22:1: warning: control reaches end of non-void function [-Wreturn-type]
   22 | }
      | ^
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c DEL.cpp
avr-gcc -I. -I/usr/include/simavr  -MMD  -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c debug.cpp
In file included from ./print.h:3,
                 from ./debug.h:1,
                 from debug.cpp:2:
/usr/avr/include/util/delay.h:92:3: warning: #warning "F_CPU not defined for <util/delay.h>" [-Wcpp]
   92 | # warning "F_CPU not defined for <util/delay.h>"
      |   ^~~~~~~
avr-ar crs libtest.a  Moteur.o print.o memoire_24.o can.o bouton.o DEL.o debug.o
make: Leaving directory '/home/gigl/inf1900/correction_tp7/3544/tp/tp7/lib'

```

## Sortie de `make` dans `tp/tp7/exec`
```
make: Entering directory '/home/gigl/inf1900/correction_tp7/3544/tp/tp7/exec'
avr-gcc -I. -I/usr/include/simavr  -MMD -I../lib -g -mmcu=atmega324pa -Os -std=c++14 -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall                                         -fno-exceptions      -c exec.cpp
In file included from exec.cpp:9:
../lib/bouton.h:2: warning: "F_CPU" redefined
    2 | #define F_CPU 8000000U
      | 
In file included from exec.cpp:8:
../lib/DEL.h:1: note: this is the location of the previous definition
    1 | #define F_CPU 8000000UL
      | 
make: *** No rule to make target 'debug.o', needed by 'executable.elf'.  Stop.
make: Leaving directory '/home/gigl/inf1900/correction_tp7/3544/tp/tp7/exec'

```
