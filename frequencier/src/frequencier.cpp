/* 
 * File:   frequencier.cpp
 * Author: laurent
 *
 * Created on 8 février 2015, 14:42
 */

#include <iostream>
#include <stdexcept>
#include <string>
#include<fstream>
#include <locale> 

using namespace std;
ifstream fichier;
const string FICHIER_MANQUANT = "nom du fichier à traiter manquant";
const string NIVEAU_EXCEPTION_ERREUR = "[Erreur] ";
const string FICHIER_INEXISTANT = "fichier inexistant: ";
const string TROP_ARGUMENTS = "trop d'arguments fournis au programme";

/**
 * Analyser la ligne de commande qui doit être comme suite pour être conforme :
 * freqencier (ou nom de l'exécutable) <nomFichier>
 * @param argc nombre d'arguments
 * @param argv les arguments à traiter
 */
void traiterLigneCommande(int argc, char** argv);
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

int main(int argc, char** argv) {
    try {
        traiterLigneCommande(argc, argv);
    } catch (runtime_error& e) {
        cout << e.what() << endl;
        afficherUsage(argv[0]);
        return -1;
    }
    return 0;
}

void afficherUsage(const char* nomExecutable) {
    cout << "Usage: " << nomExecutable << " <fichier>" << endl;
}

void traiterLigneCommande(int argc, char** argv) {
    if (argc < 2)throw runtime_error(NIVEAU_EXCEPTION_ERREUR + FICHIER_MANQUANT);
    else {
        if (argc > 2) {
            throw runtime_error(NIVEAU_EXCEPTION_ERREUR + TROP_ARGUMENTS);
        } else if (verifierExistanceFicher(argv[1])) {

            fichier.open(argv[1], ios::in);
            if (!fichier.is_open()) return;
            //on procède à la lecture caractère par caractère 
            //afin de ne pas inclure de caractères spéciaux comme é,! ou ?
            //dans la formation d'un mot
            char caractereCourant;
            string motLu;
            int nbMots = 0;


            while (fichier >> caractereCourant) {
                //Si ce n'est pas un caractère alphanumérique,
                //sautons-le et considérons qu'on commence un nouveau mot
                //Il faut aussi ajouter une vérification de plus
                //afin de s'assurer qu'un mot "vide" n'est pas considéré
                if (!isalnum(caractereCourant)) {
                    if (motLu.size() > 0) {
                        nbMots++;
                        cout << caractereCourant ;
                        cout<<motLu;
                        motLu.clear();
                    }
                    
                } else motLu.push_back(caractereCourant);
                



            }
        }
    }
}

bool verifierExistanceFicher(const char* nom) {
    ifstream fichier(nom);
    if (fichier) return true;
    else throw runtime_error(NIVEAU_EXCEPTION_ERREUR + FICHIER_INEXISTANT + nom);
}