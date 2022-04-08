#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#pragma warning (disable:4996)

#define maxTournois 10  // Nb maximum de tournois
#define nbMatchTournoi 127  // Nb de matchs par tournois
#define nbJoueusesTournoi 128  // Nb de joueuses par tournois
#define lgMot 30  // Longueur max d'un mot

//Définition des structures
typedef struct {
    char nom[lgMot + 1];
    unsigned int points;
}Joueuse;
typedef struct {
    unsigned int idxGagnante; //index de la gagnante
    unsigned int idxPerdante; //index de la perdante
}Match;
typedef struct {
    char nom[lgMot];
    char date[lgMot];
    Match dataMatch[nbMatchTournoi];
}Tournoi;
typedef struct {
    Tournoi dataTournois[maxTournois];
    Joueuse dataJoueuses[maxTournois * nbJoueusesTournoi];
    int nbTournois, idxT, idxJ;
}TournoiWTA;

//Prototypes des fonctions
int indexTournoiLibre(TournoiWTA* j);
int definir_nombre_tournois(const TournoiWTA* j);
void enregistrement_tournoi(TournoiWTA* j);
void affichage_matchs_tournoi(TournoiWTA* j);
void afficher_matchs_joueuse(TournoiWTA* j);
void affichage_joueuses_tournoi(TournoiWTA* j);
void afficher_classement(TournoiWTA* j);

//Fonction principale
int main() {
    char mot[lgMot];
    TournoiWTA j;
    while (1) {
        scanf("%s", mot);
        if (strcmp(mot, "definir_nombre_tournois") == 0) {
            definir_nombre_tournois(&j);
        }
        if (strcmp(mot, "enregistrement_tournoi") == 0) {
            enregistrement_tournoi(&j);
        }
        if (strcmp(mot, "affichage_matchs_tournoi") == 0) {
            affichage_matchs_tournoi(&j);
        }
        if (strcmp(mot, "afficher_matchs_joueuse") == 0) {
            afficher_matchs_joueuse(&j);
        }
        if (strcmp(mot, "affichage_joueuses_tournoi") == 0) {
            affichage_joueuses_tournoi(&j);
        }
        if (strcmp(mot, "afficher_classement") == 0) {
            afficher_classement(&j);
        }
        if (strcmp(mot, "exit") == 0) {
            exit(0);
        }
    }
    //systeme("pause"); 
    return 0;
}


/**
 * Permet d'enregistrer le nombre de tournois et vérifie si c'est bien compris entre 1 et 10.
 * Définie le nombre de tournois.
 * Verifie la validité du nombre avec assert.
 * @param pointeur j de type TournoiWTA
 */
int definir_nombre_tournois(const TournoiWTA* j) {
    scanf("%d", &j->nbTournois);
    assert(j->nbTournois > 0 && j->nbTournois <= maxTournois);
    return j->nbTournois;
}

/**
 * Permet de renvoyer un index de tournoi libre.
 * Recherche d'une case du tableau dataTournoi vide.
 * @param pointeur j de type TournoiWTA.
 * @return l'index pour y enregistrer un nouveau tournoi.
 */
int indexTournoiLibre(TournoiWTA* j) {
    for (int r = 0; r < maxTournois; r++) {
        if (j->dataTournois[r].date[0] != '2') {
            return r;
        }
    }
    return -1;
}

/**
 * Enregistre toutes les joueuses d'un tournoi.
 * @param pointeur j de type TournoiWTA.
 */
void enregistrement_tournoi(TournoiWTA* j) {
    j->idxT = indexTournoiLibre(j);
    int base = 0;
    base = j->idxT * nbJoueusesTournoi; // sert de palier pour enregistrer les joueuses d'un tournoi dans la bonne case
    scanf("%s", &j->dataTournois[j->idxT].nom); // enregistrement du nom du tournoi
    scanf("%s", &j->dataTournois[j->idxT].date); // enregistrement de la date du tournoi
    int c = 0;
    //référencement dans les structures le nom de chaque joueuse
    //+ de leur index au 1er tour (64emes de finale)
    for (int t = 0; t < (nbJoueusesTournoi / 2); ++t) {
        scanf("%s", j->dataJoueuses[base + c].nom);
        j->dataTournois[j->idxT].dataMatch[t].idxGagnante = base + c;
        scanf("%s", j->dataJoueuses[base + (c + 1)].nom);
        j->dataTournois[j->idxT].dataMatch[t].idxPerdante = base + (c + 1);
        j->dataJoueuses[base + (c + 1)].points = 10; //attribution points pour les 64 premieres perdantes
        c += 2;
    }
    char nom1[lgMot];
    char nom2[lgMot];
    int u = 0, r = 64, points = 45; // a partir du 2eme tour (32eme de finales), le perdants remporte 45 points
    //enregistrement de la gagnante et de la perdante
    //pour les autres tours : 32emes de finale -> finale
    while (u < 126) {
        int gagnant1 = 0, gagnant2 = 0, gagnante = 0;
        scanf("%s", nom1);
        scanf("%s", nom2);
        gagnant1 = (j->dataTournois[j->idxT].dataMatch[u].idxGagnante);
        gagnant2 = (j->dataTournois[j->idxT].dataMatch[u + 1].idxGagnante);
        //comparaison entre les noms des gagnantes du tour précedent et celle du tour suivant
        if (strcmp(nom1, j->dataJoueuses[gagnant1].nom) == 0) {
            j->dataTournois[j->idxT].dataMatch[r].idxGagnante = gagnant1;
            j->dataJoueuses[gagnant1].points = points; // attribution des points
            j->dataTournois[j->idxT].dataMatch[r].idxPerdante = gagnant2;
            j->dataJoueuses[gagnant2].points = points; // attribution des points
        }
        if (strcmp(nom1, j->dataJoueuses[gagnant2].nom) == 0) {
            j->dataTournois[j->idxT].dataMatch[r].idxGagnante = gagnant2;
            j->dataJoueuses[gagnant2].points = points; // attribution des points
            j->dataTournois[j->idxT].dataMatch[r].idxPerdante = gagnant1;
            j->dataJoueuses[gagnant1].points = points; // attribution des points
        }

        u += 2;
        switch (u) {
        case 64:
        case 96:
        case 112:
        case 120:
            points *= 2;
            break;
        case 124:
            points = 1200;
            break;
        case 126:
            points = 2000;
            gagnante = (j->dataTournois[j->idxT].dataMatch[r].idxGagnante);
            j->dataJoueuses[gagnante].points = points;
            break;
        }
        r += 1;
    }
}

/**
 * Affiche tous les matches pour un tournoi donné.
 * @param pointeur j de type TournoiWTA.
 */
void affichage_matchs_tournoi(TournoiWTA* j) {
    int compteurTours = (nbJoueusesTournoi / 2), g = 0, p = 0;
    char nom[lgMot];
    char annee[lgMot];
    scanf("%s", nom); // enregistrement du nom du tournoi
    scanf("%s", annee); // enregistrement de la date du tournoi
    // recherche du bon tournoi à afficher
    for (int i = 0; i < maxTournois; ++i) {
        if ((strcmp(nom, j->dataTournois[i].nom) == 0) && (strcmp(annee, j->dataTournois[i].date) == 0)) {
            j->idxT = i;
            break;
        }
    }
    printf("%s ", j->dataTournois[j->idxT].nom); //affichage nom du Tournoi
    printf("%s\n", j->dataTournois[j->idxT].date); //affichage date du Tournoi

    //affichage des noms des 64emes de finale
    printf("%demes de finale\n", compteurTours);
    for (int l = 0; l < 64; ++l) {
        g = j->dataTournois[j->idxT].dataMatch[l].idxGagnante;
        printf("%s ", j->dataJoueuses[g].nom);
        p = j->dataTournois[j->idxT].dataMatch[l].idxPerdante;
        printf("%s\n", j->dataJoueuses[p].nom);
    }
    compteurTours /= 2;

    //affichage des noms des 32emes de finale
    printf("%demes de finale\n", compteurTours);
    for (int l = 64; l < 96; ++l) {
        g = j->dataTournois[j->idxT].dataMatch[l].idxGagnante;
        printf("%s ", j->dataJoueuses[g].nom);
        p = j->dataTournois[j->idxT].dataMatch[l].idxPerdante;
        printf("%s\n", j->dataJoueuses[p].nom);
    }
    compteurTours /= 2;

    //affichage des noms des 16emes de finale
    printf("%demes de finale\n", compteurTours);
    for (int l = 96; l < 112; ++l) {
        g = j->dataTournois[j->idxT].dataMatch[l].idxGagnante;
        printf("%s ", j->dataJoueuses[g].nom);
        p = j->dataTournois[j->idxT].dataMatch[l].idxPerdante;
        printf("%s\n", j->dataJoueuses[p].nom);
    }
    compteurTours /= 2;

    //affichage des noms des 8emes de finale
    printf("%demes de finale\n", compteurTours);
    for (int l = 112; l < 120; ++l) {
        g = j->dataTournois[j->idxT].dataMatch[l].idxGagnante;
        printf("%s ", j->dataJoueuses[g].nom);
        p = j->dataTournois[j->idxT].dataMatch[l].idxPerdante;
        printf("%s\n", j->dataJoueuses[p].nom);
    }
    compteurTours /= 2;

    //affichage des noms des quarts de finale
    printf("quarts de finale\n");
    for (int l = 120; l < 124; ++l) {
        g = j->dataTournois[j->idxT].dataMatch[l].idxGagnante;
        printf("%s ", j->dataJoueuses[g].nom);
        p = j->dataTournois[j->idxT].dataMatch[l].idxPerdante;
        printf("%s\n", j->dataJoueuses[p].nom);
    }
    compteurTours /= 2;

    //affichage des noms des demi-finale
    printf("demi-finales\n");
    for (int l = 124; l < 126; ++l) {
        g = j->dataTournois[j->idxT].dataMatch[l].idxGagnante;
        printf("%s ", j->dataJoueuses[g].nom);
        p = j->dataTournois[j->idxT].dataMatch[l].idxPerdante;
        printf("%s\n", j->dataJoueuses[p].nom);
    }
    compteurTours /= 2;

    //affichage des noms de la finale
    printf("finale\n");
    for (int l = 126; l < 127; ++l) {
        g = j->dataTournois[j->idxT].dataMatch[l].idxGagnante;
        printf("%s ", j->dataJoueuses[g].nom);
        p = j->dataTournois[j->idxT].dataMatch[l].idxPerdante;
        printf("%s\n", j->dataJoueuses[p].nom);
    }
}

/**
 * Affiche tous les matches d'une joueuse donnée pour un tournoi donné.
 * @param pointeur j de type TournoiWTA.
 */
void afficher_matchs_joueuse(TournoiWTA* j) {
    char nomJoueuse[lgMot + 1];
    unsigned int indiceJoueuse = 0, g = 0, p = 0;
    char nom[lgMot];
    char annee[lgMot];
    scanf("%s", nom); // enregistrement du nom du tournoi
    scanf("%s", annee); // enregistrement de la date du tournoi
    // recherche du bon tournoi à afficher
    for (int i = 0; i < maxTournois; ++i) {
        if ((strcmp(nom, j->dataTournois[i].nom) == 0) && (strcmp(annee, j->dataTournois[i].date) == 0)) {
            j->idxT = i;
            break;
        }
    }
    int base = 0; //base à partir de laquelle les joueuses appartiennent au tournoi correspondant
    base = j->idxT * nbJoueusesTournoi;
    scanf("%s", nomJoueuse);
    //recherche par indice des matchs de la joueuse donnée
    for (int i = base; i < nbJoueusesTournoi+base; ++i) {
        if (strcmp(nomJoueuse, j->dataJoueuses[i].nom) == 0) {
            indiceJoueuse = i;
            for (int k = 0; k < nbMatchTournoi; ++k) {
                if ((j->dataTournois[j->idxT].dataMatch[k].idxGagnante == indiceJoueuse) || (j->dataTournois[j->idxT].dataMatch[k].idxPerdante == indiceJoueuse)) { 
                    g = j->dataTournois[j->idxT].dataMatch[k].idxGagnante;
                    p = j->dataTournois[j->idxT].dataMatch[k].idxPerdante;
                    printf("%s ", j->dataJoueuses[g].nom);
                    printf("%s\n", j->dataJoueuses[p].nom);
                }
            }
        }
    }
}

/**
 * Affiche toutes les joueuses et leur score pour un tournoi donné dans l'ordre alphabétique.
 * @param pointeur j de type TournoiWTA.
 */
void affichage_joueuses_tournoi(TournoiWTA* j) {
    char name[lgMot];
    char annee[lgMot];
    scanf("%s", name); // enregistrement du nom du tournoi
    scanf("%s", annee); // enregistrement de la date du tournoi
    // recherche du bon tournoi à afficher
    for (int i = 0; i < maxTournois; ++i) {
        if ((strcmp(name, j->dataTournois[i].nom) == 0) && (strcmp(annee, j->dataTournois[i].date) == 0)) {
            j->idxT = i;
            break;
        }
    }
    printf("%s ", j->dataTournois[j->idxT].nom); //affichage nom du Tournoi
    printf("%s\n", j->dataTournois[j->idxT].date); //affichage date du Tournoi
    int inter = 0, a = 0, b = 0, nom = 0, base=0;
    base = j->idxT * nbJoueusesTournoi; //base à partir de laquelle les joueuses appartiennent au tournoi correspondant
    int listeIndexJoueuses[nbJoueusesTournoi];
    //creation d'une liste d'indice de Joueuses
    for (int m = 0; m < nbJoueusesTournoi; ++m) { 
        listeIndexJoueuses[m] = m + base;
    }
    //tri de la liste d'indice en fonction du nom de la joueuse correspondante
    for (int i = 0; i < nbJoueusesTournoi; ++i) {
        for (int k = nbJoueusesTournoi - 1; k >= i; --k) {
            a = listeIndexJoueuses[i];
            b = listeIndexJoueuses[k];
            if (strcmp(j->dataJoueuses[a].nom, j->dataJoueuses[b].nom) > 0) { 
                inter = listeIndexJoueuses[i];
                listeIndexJoueuses[i] = listeIndexJoueuses[k];
                listeIndexJoueuses[k] = inter;
            }
        }
    }
    //affichage de la liste d'indices triée
    for (int r = 0; r < nbJoueusesTournoi; ++r) { 
        nom = listeIndexJoueuses[r];
        printf("%s ", j->dataJoueuses[nom].nom);
        printf("%d\n", j->dataJoueuses[nom].points);
    }
}

/**
 * Affiche l'indice du dernier tournoi enregistré.
 * @param pointeur j de type TournoiWTA.
 */
int dernier_tournoi(TournoiWTA* j) {
    for (int r = maxTournois-1; r > 0; --r) {
        if (j->dataTournois[r].date[0] == '2') {
            return r;
        }
    }
}

/**
 * Affiche le classement des joueuses et leur score cumulé dans l'ordre de points.
 * @param pointeur j de type TournoiWTA.
 */
void afficher_classement(TournoiWTA* j) {
    enum {tournoimax = 4};
    Joueuse listeJoueuses[nbJoueusesTournoi * tournoimax]; 
    int dernierT = dernier_tournoi(j); //indice du 4eme tournoi du classement affiché
    int base = 0, premierT = 0, boucle = 0; 
    if (dernierT > 3) {
        premierT = dernierT - (tournoimax - 1); //indice du 1er tournoi du classement affiché
        base = (premierT * nbJoueusesTournoi);
    }
    boucle = base;
    //base = (nbJoueusesTournoi * tournoimax) + (premierT * nbJoueusesTournoi);
    //creation d'une liste de type joueuse qui va référencer toutes les joueuses sans doublons
    for (int i = 0; i < nbJoueusesTournoi * tournoimax; ++i) {
        //remplissage des 128 premieres cases = toutes les joueuses du tournoi numéro 1
        if (i < nbJoueusesTournoi) {
            listeJoueuses[i] = j->dataJoueuses[boucle];
            listeJoueuses[i].points = 0;
            ++boucle;
            continue;
        }
        //remplissage sans référencer les joueuses déjà dans la liste pour les autres tournois
        for (int k = 0; k <= i; ++k) {
            if (strcmp(j->dataJoueuses[boucle].nom, listeJoueuses[k].nom) == 0) {
                break;
            }
            if (listeJoueuses[k].nom[0] == '\xcc') {
                listeJoueuses[k] = j->dataJoueuses[boucle];
                listeJoueuses[k].points = 0;
                break;
            }
        }
        ++boucle;
        
    }
    //attribution du total de points pour chaque joueuse
    for (int i = 0; i < nbJoueusesTournoi * tournoimax; ++i) {
        for (int k = base; k < nbJoueusesTournoi * tournoimax + base; ++k) {
            if (strcmp(listeJoueuses[i].nom, j->dataJoueuses[k].nom) == 0) {
                listeJoueuses[i].points += j->dataJoueuses[k].points;
            }
        }
    }

    //tri par points de la liste des joueuses
    int inter = 0, a = 0, b = 0, nom = 0;
    int listePtsJoueuses[nbJoueusesTournoi * tournoimax];
    int listeIndexJoueuses[nbJoueusesTournoi * tournoimax];
    for (int m = 0; m < nbJoueusesTournoi * tournoimax; ++m) {
        listePtsJoueuses[m] = listeJoueuses[m].points;
        listeIndexJoueuses[m] = m;
    }
    int s = nbJoueusesTournoi * tournoimax - 1;
    for (int i = 0; i < nbJoueusesTournoi * tournoimax; ++i) {
        while (listeJoueuses[s].nom[0] == '\xcc') {
            --s;
        }
        for (int k = s; k >= i; --k) {
            a = listeIndexJoueuses[i];
            b = listeIndexJoueuses[k];

            if (listeJoueuses[a].points < listeJoueuses[b].points) {
                inter = listePtsJoueuses[i];
                listePtsJoueuses[i] = listePtsJoueuses[k];
                listePtsJoueuses[k] = inter;
                inter = listeIndexJoueuses[i];
                listeIndexJoueuses[i] = listeIndexJoueuses[k];
                listeIndexJoueuses[k] = inter;
            }
            else if (listeJoueuses[a].points == listeJoueuses[b].points) {
                if (strcmp(listeJoueuses[a].nom, listeJoueuses[b].nom) > 0) {
                    inter = listePtsJoueuses[i];
                    listePtsJoueuses[i] = listePtsJoueuses[k];
                    listePtsJoueuses[k] = inter;
                    inter = listeIndexJoueuses[i];
                    listeIndexJoueuses[i] = listeIndexJoueuses[k];
                    listeIndexJoueuses[k] = inter;
                }
            }
        }
    }

    //affichage de la liste des joueuses trié par points 
    for (int r = 0; r < nbJoueusesTournoi * tournoimax; ++r) {
        if (listeJoueuses[r].nom[0] == '\xcc') {
            break;
        }
        nom = listeIndexJoueuses[r];
        printf("%s ", listeJoueuses[nom].nom);
        printf("%d\n", listePtsJoueuses[r]);

    }
}
