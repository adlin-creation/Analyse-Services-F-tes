/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  http://ericbeaudry.uqam.ca/INF3105/tp3/
 *
 *  	Identification.
 *    Nom et code permanent : LOUISAMA Adlin LOUA20309509
 *
 *
 */
#if !defined(__JOURNAL_H__)
#define __JOURNAL_H__

#include <string>
#include "arbremap.h"
#include "date.h"

using namespace std;

class Journal{
  public:
    void                  enregistrerService(const Date& date, const string& nompersonne, const string& nomcocktail);
    ArbreMap<string, int> requeteQui(const Date& debut, const Date& fin, const ArbreAVL<string>& cocktails) const;
    ArbreMap<string, int> requeteQuoi(const Date& debut, const Date& fin, const ArbreAVL<string>& buveurs) const;
    ArbreAVL<string>  	  requetePresences(const Intervalle& i) const;


  private:
    struct TraceCocktail {
      Date date;
      string nomCocktail;
      int ordreDeService; // pour diferencier les doublons en cas de deux cocktails identiques servis au meme moment

      bool operator<(const TraceCocktail& autre) const {
          if (date < autre.date) return true;
          if (autre.date < date) return false;
          if (nomCocktail < autre.nomCocktail) return true;
          if (autre.nomCocktail < nomCocktail) return false;
          return ordreDeService < autre.ordreDeService;
      }
    };

   // Arbre de cocktails servis pour chaque client (trie par date)
   ArbreMap<string, ArbreAVL<TraceCocktail>> historiqueParPersonne;
   static const int dureeCocktail = 15 * 60; // 15 min en seconde
   ArbreMap<string, int> compteurPersonne; // pour les cocktails servis a chaque personne

};

#endif
