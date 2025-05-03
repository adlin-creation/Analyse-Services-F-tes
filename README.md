# Analyse des services de boissons lors des fêtes

## Objectifs

- Appliquer les arbres binaires de recherche à une problématique.
- Écrire un programme efficace en temps et en mémoire.

## Introduction

Ce programme C++ nommé traite et analyse un journal de services de boissons lors des fêtes.


### Syntaxe d'appel

Votre programme doit pouvoir être lancé en ligne de commande de ces deux façons :
```sh
./exec nomfichier

./exec < nomfichier
```
Si un nom de fichier est spécifié en argument (`argv[1]`), alors votre programme doit lire depuis ce fichier au moyen d'un flux de lecture C++ `std::ifstream`. 
Sinon, votre programme doit lire dans l'entrée standard (`stdin`) au moyen du flux d'entrée C++ `std::cin`. 
À noter que le squelette implémente déjà ce comportement.

Les résultats produits par votre programme doivent être écrits dans la sortie standard (`stdout`) à l'aide du flux de sortie C++ `std::cout`.

### Format d'entrée et de sortie

Le flux d'entrée est une suite de commandes. 
Chaque commande débute avec un mot clé spécifiant son type.

| Commande | **Syntaxe, description et exemples d'entrée et de sortie** |
|:--- |:--- |
| `service` | `service date_service nom : nom_cocktail ;`<br>Enregistre dans le journal le service de la liste de cocktails `nom_cocktail` à la personne `nom` au temps `date_service`. La commande `service` doit spécifier le service d'au moins un cocktail. Si un cocktail est servi `n` fois en même temps et à la même personne, alors il sera énuméré `n` fois dans la liste. La commande service affiche toujours `OK` sur une seule ligne. Attention, les commandes de type `service` peuvent être en désordre de dates.<br>Par exemple, l'entrée :<br>`service 0j_20h05m00s Alice : Eau ;`<br>`service 0j_20h15m00s Benoit : Jus_Orange ;`<br>`service 0j_20h40m00s Benoit : Daiquiri_Fraise ;`<br>`service 0j_20h45m00s Alice : Daiquiri_Framboise ;`<br>doit produire le résultat :<br>`OK`<br>`OK`<br>`OK`<br>`OK`<br> |
| `qui` | `qui [date1,date2] nom_cocktail ;`<br>Affiche le nom de toutes les personnes à qui on a servi au moins un cocktail énuméré dans la liste `nom_cocktail` dans l'intervalle `[date1,date2]`. Pour chaque personne, le nombre de cocktails reçus est affiché entre parenthèses. Si aucun nom de cocktail n'est spécifié, alors il faut considérer tous les cocktails. Les personnes doivent être affichées en ordre alphabétique selon l'opérateur `<` de `std::string`. Si une commande ne trouve aucune personne, il faut afficher deux tirets (`--`) afin de signaler l'absence de résultat. Le résultat de chaque commande doit être affiché sur une seule ligne.<br>Par exemple, l'entrée :<br>`qui [0j_00h00m00s,0j_23h59m59s] Eau ;`<br>`qui [0j_00h00m00s,0j_23h59m59s] Eau Daiquiri_Fraise ;`<br>`qui [0j_00h00m00s,0j_11h59m59s] ;`<br>doit produire le résultat :<br>`Alice (1)`<br>`Alice (1) Benoit (1)`<br>`--`<br> |
| `quoi` | `quoi [date1,date2] nom_personnes ;`<br>Affiche la compilation des cocktails servis au groupe de personnes `nom_personnes` dans l'intervalle `[date1,date2]`. Pour chaque type de cocktail, le nombre d'unités servis est affiché entre parenthèses. Si aucun nom de personne n'est spécifié, on analyse tous les cocktails servis. Les cocktails doivent être affichés en ordre alphabétique selon l'opérateur `<` de `std::string`. Si la commande ne produit aucun résultat, il faut afficher deux tirets (`--`). Le résultat de chaque commande doit être affiché sur une seule ligne.<br>Par exemple, l'entrée :<br>`quoi [0j_00h00m00s,0j_23h59m59s] Alice ;`<br>`quoi [0j_00h00m00s,0j_23h59m59s] Benoit ;`<br>`quoi [0j_00h00m00s,0j_23h59m59s] ;`<br>doit produire le résultat :<br>`Daiquiri_Framboise (1) Eau (1)`<br>`Daiquiri_Fraise (1) Jus_Orange (1)`<br>`Daiquiri_Fraise (1) Daiquiri_Framboise (1) Eau (1) Jus_Orange (1)`<br> |
| `presences` | `presences [date1,date2] ;`<br>Affiche les noms des personnes qui ont été présentes à au moins une fête entre `date1` et `date2`. Les noms doivent être triés en ordre alphabétique. Si la commande ne produit aucun résultat, il faut afficher deux tirets (`--`). Le résultat de chaque commande doit être affiché sur une seule ligne.<br>Par exemple, l'entrée suivante :<br>`presences [0j_20h30m00s,0j_20h31m00s] ;`<br>`presences [0j_20h30m01s,0j_20h31m00s] ;`<br>doit produire le résultat suivant :<br>`Benoit`<br>`--`<br>À noter qu'une personne peut être présente à une fête dans l'intervalle `[date1,date2]` même si on ne lui a pas servi de cocktail dans cet intervalle. Pour retourner un résultat correct, il faut considérer les règles d'interprétation à la Section **Règles d'interprétation et hypothèses**. |

Pour faciliter le _parsing_ au moyen de `std::cin >>`, des espaces blancs (espace, tabulation ou retour de ligne) sont utilisés.

### Format de dates

Toutes les dates sont spécifiées dans le format `0j_00h00m00s`. 
Afin de le simplifier, il n'y a ni mois, ni année. 

### Traitement séquentiel

Les commandes sont traitées de façon séquentielle, c'est-à-dire qu'il ne faut pas considérer les commandes futures dans l'entrée. 
De plus, il est interdit de lire toute l'entrée en mémoire puis de le traiter en différé. 
Le résultat d'une commande doit être affiché avant de lire la commande suivante.

### Règles d'interprétation et hypothèses

1. Tout le monde boit à une vitesse constante et universelle : 1 cocktail par 15 minutes.
2. Dès qu'une personne reçoit un cocktail, elle commence à le boire.
3. Une personne boit un seul cocktail à la fois. Si on lui sert plusieurs cocktails, elle les boit l'un à la suite de l'autre.
4. Une fête commence au moment précis où la première consommation est servie.
5. Une fête est réputée être en cours tant et aussi longtemps qu'au moins une personne a un verre non vide.
6. Une fête se termine au moment précis où la dernière personne ayant un verre non vide termine sa dernière consommation de la fête.
7. Une personne est réputée être arrivée au moment précis où on lui sert sa première consommation.
8. Une personne est réputée avoir quitté la fête au moment précis où elle termine sa dernière consommation de la fête.

### Exemple

Soit le fichier d'entrée [`exemple.txt`](/exemple.txt).

```
service 0j_20h05m00s Alice : Eau ;
service 0j_20h15m00s Benoit : Jus_Orange ;
service 0j_20h40m00s Benoit : Daiquiri_Fraise ;
service 0j_20h45m00s Alice : Daiquiri_Framboise ;
qui [0j_00h00m00s,0j_23h59m59s] Eau ;
qui [0j_00h00m00s,0j_23h59m59s] Eau Daiquiri_Fraise ;
qui [0j_00h00m00s,0j_11h59m59s] ;
quoi [0j_00h00m00s,0j_23h59m59s] Alice ;
quoi [0j_00h00m00s,0j_23h59m59s] Benoit ;
quoi [0j_00h00m00s,0j_23h59m59s] ;
presences [0j_20h30m00s,0j_20h31m00s] ;
presences [0j_20h30m01s,0j_20h31m00s] ;
service 0j_20h15m00s Celine : Daiquiri_Fraise ;
service 0j_20h16m00s Celine : Eau ;
presences [0j_20h30m00s,0j_20h31m00s] ;
presences [0j_21h01m00s,0j_21h02m00s] ;
service 0j_21h05m00s Denis : Margarita ;
service 0j_21h15m00s Celine : Eau Vodka_Canneberges Eau ;
service 0j_22h00m00s Benoit : Jus_Orange ;
service 0j_22h10m00s Denis : Jus_Orange ;
qui [0j_00h00m00s,0j_23h59m59s] Eau ;
qui [0j_00h00m00s,0j_23h59m59s] Eau Daiquiri_Fraise ;
qui [0j_00h00m00s,0j_11h59m59s] ;
quoi [0j_00h00m00s,0j_23h59m59s] Benoit ;
quoi [0j_00h00m00s,0j_23h59m59s] Benoit Celine ;
quoi [0j_00h00m00s,0j_23h59m59s] ;
presences [0j_21h01m00s,0j_21h02m00s] ;
presences [0j_21h30m00s,0j_22h05m00s] ;
```

Dans les illustrations qui suivent, les intervalles noirs indiquent les périodes pendant lesquelles les personnes boivent. 
Les pointillés verts indiquent les périodes pendant lesquelles les personnes sont présentes à la fête. 
En haut, les intervalles rouges indiquent les périodes pendant lesquelles il y a une fête en cours.

Après les 4 premières commandes service.

![](/exemple_04.png)

Après les 6 premières commandes service. 
À présent, on sait que `Céline` était présente de 20h15 à 20h45. 
La fête #1 a donc durée de 20h05 à 21h30.

![](/exemple_06.png)

Après toutes les (10) commandes `service`.

![](/exemple_10.png)

Le fichier de sortie : [`sortie.txt`](/sortie.txt).

```
OK
OK
OK
OK
Alice (1) 
Alice (1) Benoit (1) 
--
Daiquiri_Framboise (1) Eau (1) 
Daiquiri_Fraise (1) Jus_Orange (1) 
Daiquiri_Fraise (1) Daiquiri_Framboise (1) Eau (1) Jus_Orange (1) 
Benoit 
--
OK
OK
Alice Benoit Celine 
--
OK
OK
OK
OK
Alice (1) Celine (3) 
Alice (1) Benoit (1) Celine (4) 
--
Daiquiri_Fraise (1) Jus_Orange (2) 
Daiquiri_Fraise (2) Eau (3) Jus_Orange (2) Vodka_Canneberges (1) 
Daiquiri_Fraise (2) Daiquiri_Framboise (1) Eau (4) Jus_Orange (3) Margarita (1) Vodka_Canneberges (1) 
--
Benoit Celine Denis
```
