
# ClassementWTA - Félix LIBURSKI (septembre - octobre 2021)
## <center>Table of Contents </center>

* [Présentation du projet](#chapter1)
* [Organisation des tests de l'application](#chapter2)
* [Bilan de validation des sprints](#chapter3)
    * [Sprint#1](#section3_1)
    * [Sprint#2](#section3_2) 
    * [Sprint#3](#section3_3)
    * [Sprint#4 & Sprint#5](#section3_4)
* [Bilan de projet](#chapter4)

## Présentation du projet <a class="anchor" id="chapter1"></a>
<div align="justify">L’application a pour but de créer un classement des joueuses de tennis des 4 grands tournois du Grand Chelem : l’Open d’Australie à Melbourne, le tournois de Wimbledon à Londres, l’US Open à New-York et les Internationaux de France à Paris. Elle construit un classement général basé sur les points cumulés des joueuses lors des 4 derniers tournois (au plus) en date. Les entrées dans l’application sont les données de 10 tournois reprenant tous les matchs (des 64èemes de finales à la finale) et en indiquant le vainqueur et le perdant de ces matchs. Différentes commandes sont accessibles en fonction de l’information demandée.

<div align="justify">L’utilisateur peut en effet connaitre à l’aide de la commande <strong>affichage_matchs_tournoi</strong> et en spécifiant le lieu du tournoi et sa date, tous les matchs joués lors de ce tournoi.</div>

<div align="justify">L’utilisateur peut aussi connaitre à l’aide de la commande <strong>afficher_matchs_joueuses</strong> et en spécifiant le lieu du tournoi, sa date et le nom d’une joueuse, tous les matchs joués par cette joueuse lors de ce tournoi.</div>

<div align="justify">L’utilisateur peut ensuite connaitre à l’aide de la commande <strong>affichage_joueuses_tournoi</strong> et en spécifiant le lieu du tournoi et sa date, le classement des joueuses du tournoi (ordonné dans l’ordre alphabétique).</div>

<div align="justify">L’utilisateur peut enfin connaitre à l’aide de la commande <strong>afficher_classement</strong>, le classement général des joueuses des 4 derniers tournois enregistrés (ordonné dans l’ordre des points).</div>

## Organisation des tests de l'application <a class="anchor" id="chapter2"></a>
<div align="justify">Nous avons développé chaque sprint un à un en prenant soin de bien les valider comme préconisé avec les inSp.txt et les outSp.txt fournis.</div>

Ensuite, nous avons en plus testé notre application avec les entrées des recettes. Nous avons donc fait au total 20 tests : 5 tests par jeu de données. Un exemple de recette est disponibles dans la rubrique du Sprint# concerné. Il y a un fichier in et le fichier out associé.</div>

## Bilan de validation des sprints <a class="anchor" id="chapter3"></a>
### Sprint 1 <a class="anchor" id="section3_1"></a> 
<div align="justify">Pour le sprint 1 nous devions référencer chaque matchs du tournoi avec la commande <strong>afficher_classement</strong> suivit du nom et de la date du tournoi. Chaque tour devait être affiché ainsi que les matchs formé à gauche du nom de du vainqueur et à droite du nom de la perdante.  </div>

Dans la fonction <strong>afficher_classement</strong> nous avons affiché dans un premier temps le nom et la date du tournoi correspondant, puis chaque tour (64èmes, 32èmes, 16èmes, 8èmes, Quarts, Demies, Finale) suivit à chaque fois de nom de la vainqueur et de la perdante pour le tour correspondant.</div>

### Sprint 2 <a class="anchor" id="section3_2"></a> 
<div align="justify">Pour le sprint 2 nous devions référencer chaque matchs joué d’une joueuse lors d’un tournoi avec la commande <strong>afficher_matchs_joueuse</strong> suivit du nom et de la date du tournoi ainsi que la joueuse recherchée. Uniquement les matchs de la joueuse doivent être affiché formé à gauche du nom de du vainqueur et à droite du nom de la perdante, l’une des deux sera forcément le nom de la joueuse spécifiée.  

Dans la fonction <strong>afficher_matchs_joueuse</strong>, on cherche le nom et la date du tournoi spécifié. Ensuite on regarde parmi les 128 joueuses du tournoi la joueuse recherchée pour récupérer son indice. Enfin on regarde pour chaque match du tournoi si son nom apparait. Ainsi on affiche tous ses matchs joués lors de ce tournoi.</div>

### Sprint 3 <a class="anchor" id="section3_3"></a> 
<div align="justify">Pour le sprint 3, nous devions afficher le classement (nom et points) des joueuses qui ont participé à un même tournoi précisé par l’utilisateur avec la commande <strong>affichage_joueuses_tournoi</strong> suivit du nom et de la date du tournoi.
Dans la fonction <strong>affichage_jousues_tournoi</strong>, on recherche l’indice du tournoi demandé. Ensuite, on a crée une liste de nombre qui référence tous les indices des joueuses listeIndexJoueuses qui participent à ce tournoi. Puis on compare chaque nom correspondant aux indices pour trié ce tableau dans 6 l’ordre alphabétique. Enfin, on affiche le nom correspondant à chaque indice du tableau trié listeIndexJoueuses. </div>

### Sprint 4 et 5 <a class="anchor" id="section3_4"></a>
<div align="justify">Les sprint 4 et 5 ont les mêmes objectifs : pour ces sprints, nous devions afficher le classement général (nom et points cumulés) des 4 derniers tournois enregistrés.  </div>

<div align="justify">Dans la fonction <strong>afficher_classement</strong>, on encadre d’abord les tournois qu’on doit afficher, c’est-à-dire en enregistrant les indices des 4 tournois (au plus) à afficher donc l’indice du 1er tournoi et l’indice du dernier tournoi à afficher. Ensuite, on a crée un tableau de type Joueuse appelé listeJoueuses pour y référencer sans doublons toutes les joueuses qu’on veut afficher. Puis, on a comparé chaque nom de joueuse du tableau listeJoueuses avec le nom des joueuses des tournois pour leur attribué leur points respectif. Ensuite, on a trié par points ce tableau listeJoueuses. Enfin, on a affiché le nom et les points de chaque joueuse du tableau listeJoueuses trié.</div>

## Bilan de projet <a class="anchor" id="chapter4"></a>
Les résultats des tests sont valides. Nous sommes satisfaits d’avoir réussi à finalisé le projet et accomplit tous les sprints.
La compréhension de chaque objectif des sprints ainsi que leur réalisation était une tâche complexe et longue. Malgré la validation des Sprints fournis, les recettes étaient beaucoup plus conséquentes et quelques bugs se sont révélés. On a su s’adapter et modifier notre code et corriger nos erreurs.
Nos fonctions pourraient être plus optimisées notamment la fonction <strong>afficher_classement</strong>. On pourrait diviser nos fonctions en sous-fonctions ou bien les référencer sur un autre fichier « .h ».
