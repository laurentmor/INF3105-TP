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
vector <Couple> lesCouples;
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
bool nombreArgumentsCorrect(int);
void ajouterMot(const string&);
void trierParInsertion(vector<Couple>&);
void afficherCouples(const vector<Couple>&);

int main(int argc, char** argv) {
    try {
        vector<Couple> v;
        trierParInsertion(v);
        afficherCouples(v);

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

    if (nombreArgumentsCorrect(argc) && verifierExistanceFicher(argv[1])) {

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


                if (lesCouples.empty()) {
                    ajouterMot(motLu);
                } else {
                    bool motDejaPresent = false;
                    for (vector<Couple>::iterator it = lesCouples.begin();
                            it != lesCouples.end(); ++it) {
                        if (it->mot == motLu) {
                            motDejaPresent = true;
                            it->frequence++;
                        }


                    }
                    if (!motDejaPresent) {
                        //déclare un nouveau couple dans un des cas suivants
                        //- Si le mot lu n'est pas dans le Vecteur
                        //- Si c'est le premier mot complet lu
                        // Question d'éviter de créer un couple
                        // pour un mot existant
                        ajouterMot(motLu);

                    }

                }


                motLu.clear();
            }




        }
    }
}

bool verifierExistanceFicher(const char* nom) {
    ifstream fichier(nom);
    if (fichier) return true;
    else throw runtime_error(NIVEAU_EXCEPTION_ERREUR + FICHIER_INEXISTANT + nom);
}

void ajouterMot(const string& mot) {
    Couple c;
    c.mot = mot;
    c.frequence = 1;
    lesCouples.push_back(c);
}

bool nombreArgumentsCorrect(int argc) {
    if (argc < 2)throw runtime_error(NIVEAU_EXCEPTION_ERREUR + FICHIER_MANQUANT);
    else
        if (argc > 2) {
        throw runtime_error(NIVEAU_EXCEPTION_ERREUR + TROP_ARGUMENTS);
    } else return true;
}

void trierParInsertion(vector<Couple>& couples) {
    unsigned int j;
    Couple val;

    for (int i = 1; i < couples.size(); i++) {

        val = couples[i];
        j = i - 1;


        while (j >= 0 && couples[j].frequence > val.frequence) {

            couples[j + 1] = couples[j];

            j = j - 1;

        }

        couples[j + 1] = val;

    }

}

void afficherCouples(const vector<Couple>& couples) {
}