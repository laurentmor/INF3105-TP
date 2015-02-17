
/* 

 * The MIT License

 *

 * Copyright 2015 Laurent Morissette.

 *

 * Permission is hereby granted, free of charge, to any person obtaining a copy

 * of this software and associated documentation files (the "Software"), to deal

 * in the Software without restriction, including without limitation the rights

 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

 * copies of the Software, and to permit persons to whom the Software is

 * furnished to do so, subject to the following conditions:

 *

 * The above copyright notice and this permission notice shall be included in

 * all copies or substantial portions of the Software.

 *

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN

 * THE SOFTWARE.

 */

/**
 * Auteur: Laurent Morissette - Hiver 2015
 * Code permanent : MORL05058301
 * Cours INF3105 
 * Sujet: fréquencier est un programme  qui lit et tri des mots dans un fichier 
 *        passé en paramètre de 2 façons:
 *                                       par fréquence de mot dans le texte
 *                                       Par ordre alphabétique
 * 
 *       Si on ne fournit pas de fichier, on affiche une erreur puis l'usage
 *       Si on ne fournit pas (ou trop) de paramètre. c'est la même chose
 *       Si le fichier passé en paramètre est inexistant on avise l'usager
 *       S'il est impossible d'ouvrir le fichier, même chose   
 */
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <locale>
#include <vector>
#include <cstdlib>
#include<iomanip>


using namespace std;

/**
 * Les différents messages
 */
const string FICHIER_MANQUANT( "nom du fichier à traiter manquant");
const string NIVEAU_EXCEPTION_ERREUR = "[Erreur] ";
const string FICHIER_INEXISTANT = "fichier inexistant: ";
const string TROP_ARGUMENTS = "trop d\'arguments fournis au programme";
const string FICHIER_VIDE = "Fichier vide, rien \340 afficher";
const string OUVERTURE_IMPOSSIBLE = "impossible d'ouvrir le fichier: ";
const string VERIFIER = "V\351rifiez que vous disposez";
const string PERMISSIONS = " des permissions requises sur le fichier";

struct Couple {
    /**
     * Le mot dans le texte
     */
    string mot;
    /**
     * Le nombre de fois où on retrouve le mot dans le texte
     */
    int frequence;

};



/**
 * Afficher la manière d'utiliser le programme
 * @param nomExecutable le nom de l'exécutable à utiliser lors de l'appel
 */
void afficherUsage(const char* nomExecutable);
/**
 * Sert à vérifier qu'un fichier existe avant son ouverture
 * @param nomFichier le nom de fichier à vérifier
 * @return TRUE s'il existe 
 */
bool verifierExistanceFicher(const char* nomFichier);
/**
 * Sert à déterminer si le nombre d'arguments passés en ligne de commande 
 * est correct.
 * @param le nombre d'arguments
 * @return TRUE si c'est correct
 */
bool nombreArgumentsCorrect(int);
/**
 * sert à déterminer si toutes les conditions sont remplies pour continuer
 * le traitement :
 * 1- Le nombre de paramètres est correct
 * 2- Le fichier fourni en paramètre est existant sur le disque
 * @param le nombre de paramètres
 * @param le nom du fichier à vérifier
 * @return TRUE si si la ligne de commande est bien formée
 */
bool ligneDeCommandeCorrecte(int, char**);
/**
 * - Lire le fichier passé en paramètre à la ligne de commande
 * - Retourner l'ensemble des couples (mot, fréquence)
 * @param le nom du fichier à traiter 
 * @return un vecteur de couples
 * 
 */
vector<Couple> creerCouplesAPartirDuFichier(const char*);
/**
 * Ajouter un mot à la liste des couples
 * @param le mot à ajouter
 * @param le vecteur où l'ajouter 
 */
void ajouterMot(const string&, vector<Couple>&);
/**
 * Trier un vecteur donné par ordre de fréquence décroissante
 * @param le vecteur à trier
 */
void trierParFrequencesDecroissante(vector<Couple>&);
/**
 * Trier un vecteur donné par ordre de mots croissants
 * @param le vecteur à trier
 */
void trierParMots(vector<Couple>&);

void appliquerLesTris(vector<Couple>&);
/*
 * Afficher les résultats formatés
 * 
 **/
void afficherCouples(vector<Couple>&);

int main(int argc, char** argv) {
   
    try {
        vector<Couple> lesCouples;
        if (ligneDeCommandeCorrecte(argc, argv)) {
            lesCouples = creerCouplesAPartirDuFichier(argv[1]);
        }
        if (!lesCouples.empty()) {
            appliquerLesTris(lesCouples);
            afficherCouples(lesCouples);

        } else {
            cout << FICHIER_VIDE << endl;
        }

    } catch (runtime_error& e) {
        cout << argv[0] << " " << e.what() << endl;
        afficherUsage(argv[0]);
        exit(-1);
    } catch (ifstream::failure fail) {
        cout << argv[0] << " " <<fail.what() << endl;
        cout << VERIFIER << PERMISSIONS << endl;
    }
    exit(0);
}

void afficherUsage(const char* nomExecutable) {
    cout << "Usage: " << nomExecutable << " <fichier>" << endl;
}

bool ligneDeCommandeCorrecte(int argc, char** argv) {

    if (nombreArgumentsCorrect(argc) && verifierExistanceFicher(argv[1])) {
        return true;
    }
    return false;



}

bool verifierExistanceFicher(const char* nom) {
    ifstream fichier(nom);
    if (fichier) return true;
    else throw runtime_error(NIVEAU_EXCEPTION_ERREUR +
            FICHIER_INEXISTANT + nom);
}

void ajouterMot(const string& mot, vector<Couple>& vc) {
    Couple c;
    c.mot = mot;
    c.frequence = 1;
    vc.push_back(c);
}

bool nombreArgumentsCorrect(int argc) {
    if (argc < 2)throw runtime_error(NIVEAU_EXCEPTION_ERREUR + FICHIER_MANQUANT);
    else
        if (argc > 2) {
        throw runtime_error(NIVEAU_EXCEPTION_ERREUR + TROP_ARGUMENTS);
    } else return true;
}

void trierParFrequencesDecroissante(vector<Couple>& couples) {
    int j;
    Couple val;

    for (unsigned int i = 1; i < couples.size(); i++) {

        val = couples[i];
        j = i - 1;


        while (j >= 0 && couples[j].frequence < val.frequence) {

            couples[j + 1] = couples[j];

            j = j - 1;

        }


        couples[j + 1] = val;

    }

}

void trierParMots(vector<Couple>& couples) {
    int j;
    Couple val;

    for (unsigned int i = 1; i < couples.size(); i++) {

        val = couples[i];
        j = i - 1;


        while (j >= 0 && couples[j].mot > val.mot) {

            couples[j + 1] = couples[j];

            j = j - 1;

        }


        couples[j + 1] = val;

    }

}

void appliquerLesTris(vector<Couple>& vecteurATrier) {
    trierParMots(vecteurATrier);
    trierParFrequencesDecroissante(vecteurATrier);

}

void afficherCouples(vector<Couple>& couples) {
    for (vector<Couple>::iterator it = couples.begin();
            it != couples.end(); ++it) {
        cout << setw(10) << right << it->frequence << " "
                << left << it->mot << endl;
    }
}

vector<Couple>creerCouplesAPartirDuFichier(const char* nomFichier) {
    vector<Couple> lesCouples = vector<Couple>();
    ifstream fichier;
    fichier.open(nomFichier, ios::in);
    
    if (!fichier.is_open()) throw ifstream::failure(NIVEAU_EXCEPTION_ERREUR +
            OUVERTURE_IMPOSSIBLE + nomFichier);

    //on procède à la lecture caractère par caractère 
    //afin de ne pas inclure de caractères spéciaux comme é,! ou ?
    //dans la formation d'un mot
    char caractereCourant;
    string motLu;

    while (!fichier.eof()) {
        caractereCourant = fichier.get();

        if (isalnum(caractereCourant)) {
            motLu.push_back(caractereCourant);


        } else {

            //Si le mot est le premier mot et que ce n'est pas un mot vide,
            //On l'ajoute directement.
            if (lesCouples.empty() && motLu.size() > 0) {
                ajouterMot(motLu, lesCouples);
            }//S'il ne s'agit pas du premier mot, on le recherche et met à jour
                //la fréquence. 
            else if (motLu.size() > 0) {
                bool motDejaPresent = false;
                for (vector<Couple>::iterator it = lesCouples.begin();
                        it != lesCouples.end(); ++it) {
                    if (it->mot == motLu) {
                        motDejaPresent = true;
                        it->frequence++;
                    }


                }
                //Si le mot n'est pas trouvé, on l'ajoute
                if (!motDejaPresent) {

                    ajouterMot(motLu, lesCouples);

                }

            }

            // On "nettoie" le mot pour continuer la lecture du prochain mot 
            motLu.clear();
        }




    }

    fichier.close();
    return lesCouples;
}