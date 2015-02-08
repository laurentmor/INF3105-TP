/* 
 * File:   frequencier.cpp
 * Author: laurent
 *
 * Created on 8 février 2015, 14:42
 */

#include <iostream>
#include <stdexcept>

using namespace std;
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
void afficherUsage(char* nomExecutable);

int main(int argc, char** argv) {
    try {
        traiterLigneCommande(argc,argv);
    } catch (runtime_error& e) {
        cout<<e.what()<<endl;
        afficherUsage(argv[0]);
        return -1;
    }
    return 0;
}

void afficherUsage(char* nomExecutable) {
    cout << "Usage: " << nomExecutable << " <fichier>" << endl;
}

void traiterLigneCommande(int argc, char** argv) {
    if (argc != 2)throw runtime_error("[Erreur] nom du fichier à traiter "
            "manquant");
    else{
    }
}
