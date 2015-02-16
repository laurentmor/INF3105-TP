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
#include<cstdlib>

using namespace std;


const string FICHIER_MANQUANT = "nom du fichier à traiter manquant";
const string NIVEAU_EXCEPTION_ERREUR = "[Erreur] ";
const string FICHIER_INEXISTANT = "fichier inexistant: ";
const string TROP_ARGUMENTS = "trop d'arguments fournis au programme";
const string FICHIER_VIDE = "Fichier vide, rien à afficher";

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
bool ligneDeCommandeCorrecte(int, char**);
vector<Couple> creerCouplesAPartirDuFichier(const char*);
void ajouterMot(const string&, vector<Couple>&);
void trierParInsertion(vector<Couple>&);
void afficherCouples(vector<Couple>&);

int main(int argc, char** argv) {
    try {
        vector<Couple> lesCouples;
        if (ligneDeCommandeCorrecte(argc, argv)) {
            lesCouples = creerCouplesAPartirDuFichier(argv[1]);
        }
        if (!lesCouples.empty()) {
            trierParInsertion(lesCouples);
            afficherCouples(lesCouples);
        } else {
            cout << FICHIER_VIDE << endl;
        }

    } catch (runtime_error& e) {
        cout << e.what() << endl;
        afficherUsage(argv[0]);
        exit(-1);
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
    else throw runtime_error(NIVEAU_EXCEPTION_ERREUR + FICHIER_INEXISTANT + nom);
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

void trierParInsertion(vector<Couple>& couples) {
    int j;
    Couple val;

    for (unsigned int i = 1; i < couples.size(); i++) {

        val = couples[i];
        j = i - 1;


        while (j >= 0 && couples[j].frequence > val.frequence) {

            couples[j + 1] = couples[j];

            j = j - 1;

        }

        couples[j + 1] = val;

    }

}

void afficherCouples(vector<Couple>& couples) {
    for (vector<Couple>::iterator it = couples.begin();
            it != couples.end(); ++it) {
        cout << it->mot << " " << it->frequence << endl;
    }
}

vector<Couple>creerCouplesAPartirDuFichier(const char* nomFichier) {
    vector<Couple> lesCouples = vector<Couple>();
    ifstream fichier;
    fichier.open(nomFichier, ios::in);

    if (!fichier.is_open()) return lesCouples;
    if(fichier.tellg()==0) return lesCouples;
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
                ajouterMot(motLu, lesCouples);
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
                    ajouterMot(motLu, lesCouples);

                }

            }


            motLu.clear();
        }




    }
    return lesCouples;
}