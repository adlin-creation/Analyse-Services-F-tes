/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  http://ericbeaudry.uqam.ca/INF3105/tp3/
 */
#include <fstream>
#include <iostream>
#include "journal.h"

using namespace std;

int tp3(istream& entree);

int main(int argc, const char** argv){
    if (argc>1) {
        // Lecture depuis un fichier.
        std::ifstream entreefichier(argv[1]);
        if(entreefichier.fail()){
            cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'!" << std::endl;
            return 1;
        }
        return tp3(entreefichier);
    } else{
        // Lecture depuis stdin (console).
        return tp3(cin);
    }
}

int tp3(istream& entree)
{
    Journal journal;
    
    while(entree){
        string cmd;
        entree >> cmd;
        if(cmd=="") break;
        
        if(cmd=="service"){
            Date instant;
            char deuxpoints, pointvirgule;
            string nompersonne;
            entree >> instant >> nompersonne >> deuxpoints;
            while(entree){
                string nomcocktail;
                entree >> nomcocktail;
                if(nomcocktail == ";") break;
                journal.enregistrerService(instant, nompersonne, nomcocktail);
            }
            cout << "OK" << endl;
        }
        else if(cmd=="qui"){
            Intervalle intervalle;
            ArbreAVL<string> nomscocktails;
            entree >> intervalle;
            while(entree){
                string nomcocktail;
                entree >> nomcocktail;
                if(nomcocktail == ";") break;
                nomscocktails.inserer(nomcocktail);
            }
            ArbreMap<string, int> rapport = journal.requeteQui(intervalle.debut, intervalle.fin, nomscocktails);
            if(!rapport.vide()){
                for(ArbreMap<string, int>::Iterateur irapport=rapport.debut();irapport;++irapport)
                    cout << irapport.cle() << " (" << irapport.valeur() << ") ";
            }else
                cout << "--";
            cout << endl;
        }
        else if(cmd=="quoi"){
            Intervalle intervalle;
            ArbreAVL<string> nomspersonnes;
            entree >> intervalle;
            while(entree){
                string nompersonne;
                entree >> nompersonne;
                if(nompersonne == ";") break;
                nomspersonnes.inserer(nompersonne);
            }
            ArbreMap<string, int> rapport = journal.requeteQuoi(intervalle.debut, intervalle.fin, nomspersonnes);
            if(!rapport.vide()){
                for(ArbreMap<string, int>::Iterateur irapport=rapport.debut();irapport;++irapport)
                    cout << irapport.cle() << " (" << irapport.valeur() << ") ";
            } else
                cout << "--";
            cout << endl;
        }
	else if(cmd=="presences"){
            Intervalle intervalle;
            char pointvirgule;
            entree >> intervalle >> pointvirgule;
            ArbreAVL<string> listenoms = journal.requetePresences(intervalle);
            if(!listenoms.vide())
                for(ArbreAVL<string>::Iterateur i=listenoms.debut();i;++i)
                    cout << *i << " ";
            else
                cout << "--";
            cout << endl;
        }
        else{
            cout << "Commande invalidate : " << cmd << endl;
            return 1;
        }
    }
    return 0;
}
