/* 
 * File:   frequencier.cpp
 * Author: laurent
 *
 * Created on 8 février 2015, 14:42
 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <locale>
#include <vector>

using namespace std;

ifstream fichier;
const string FICHIER_MANQUANT = "nom du fichier à traiter manquant";
const string NIVEAU_EXCEPTION_ERREUR = "[Erreur] ";
const string FICHIER_INEXISTANT = "fichier inexistant: ";
const string TROP_ARGUMENTS = "trop d'arguments fournis au programme";

struct Couple {
    string mot;
    int frequence;
};
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
        vector<Couple> v;
        Couple c=Couple();
        c.mot = "test";
        c.frequence = 12;
        v.push_back(c);
        for (vector<Couple>::iterator it=v.begin();it!=v.end(); ++it) {
           cout<<it->mot;
           cout<<it->frequence;
           if(it->mot=="test"){
               it->frequence++;
           }
           cout<<it->frequence;
           

        }

       
        //traiterLigneCommande(argc, argv);
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
            string motLu = "";
            while (!fichier.eof()) {
                caractereCourant = fichier.get();

                if (isalnum(caractereCourant)) {
                    motLu.push_back(caractereCourant);


                } else {

                    Couple c;
                    c.mot = motLu;
                    cout << c.mot;
                    motLu.clear();
                }




            }
        }
    }
}

bool verifierExistanceFicher(const char* nom) {
    ifstream fichier(nom);
    if (fichier) return true;
    else throw runtime_error(NIVEAU_EXCEPTION_ERREUR + FICHIER_INEXISTANT + nom);
}