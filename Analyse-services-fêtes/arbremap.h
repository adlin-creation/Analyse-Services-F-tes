/* Squelette pour classe générique ArbreMap<K, V>.
 * Lab8 -- Dictionnaires et Arbres binaires de recherche
 * UQAM / Département d'informatique
 * INF3105 - Structures de données et algorithmes
 * 
 * Louisama Adlin LOUA20309509
 */

#ifndef _ARBREMAP_H_
#define _ARBREMAP_H_

#include "arbreavl.h"

template<class K, class V>
class ArbreMap {
 public:
  bool contient(const K&) const;

  void enlever(const K&);
  void vider();
  bool vide() const;

  const V& operator[](const K&) const;
  V& operator[](const K&);

 private:
  struct Entree {
    Entree(const K& c): cle(c), valeur() {}
    K cle;
    V valeur;
    bool operator<(const Entree& e) const {return cle < e.cle; }
  };
  ArbreAVL<Entree> entrees;

  public:
  class Iterateur {
    public :
      Iterateur(ArbreMap& a): iter(a.entrees.debut()) {}
      Iterateur(typename ArbreAVL<Entree>::Iterateur& i) : iter(i) {}
      operator bool() const {return iter.operator bool(); }
      Iterateur operator++() {++iter; return *this; }
      const K& cle() const {return (*iter).cle; }
      const V& valeur() const {return (*iter).valeur; }

    private:
      typename ArbreAVL<Entree>::Iterateur iter;
  };

  Iterateur debut() {return Iterateur(*this);}
  Iterateur fin() {return Iterateur(entrees.fin());}
  Iterateur rechercher(const K& cle) {return Iterateur(entrees.rechercher(cle));}
  Iterateur rechercherEgalOuSuivant(const K& cle) {return Iterateur(entrees.rechercherEgalOuSuivant(cle));}
  Iterateur rechercherEgalOuPrecedent(const K& cle) {return Iterateur(entrees.rechercherEgalOuPrecedent(cle));}

  class IterateurConst {
    public:
      IterateurConst(const ArbreMap& a) : iter(a.entrees.debut()) {}
      IterateurConst(typename ArbreAVL<Entree>::Iterateur i) : iter(i) {}

      operator bool() const {return iter.operator bool();};
      IterateurConst& operator++() {++iter; return *this;}

      const K& cle() const {return (*iter).cle;}
      const V& valeur() const {return (*iter).valeur;}

    private:
      typename ArbreAVL<Entree>::Iterateur iter;
  };

  IterateurConst debut() const {
    return IterateurConst(entrees.debut());
  }
  IterateurConst fin() const {
    return IterateurConst(entrees.fin());
  }
  IterateurConst rechercher(const K& cle) const {
    return IterateurConst(entrees.rechercher(cle));
  }
  IterateurConst rechercherEgalOuSuivant(const K& cle) const {
    return IterateurConst(entrees.rechercherEgalOuSuivant(cle));
  }
  IterateurConst rechercherEgalOuPrecedent(const K& cle) const {
    return IterateurConst(entrees.rechercherEgalOuPrecedent(cle));
  }

  V& operator[](const Iterateur& iter) {return (V&) iter.valeur();}
  const V& operator[](const Iterateur& iter) const {return iter.valeur();}

};

template<class K, class V>
void ArbreMap<K, V>::vider() {
  entrees.vider();
}

template<class K, class V>
bool ArbreMap<K, V>::vide() const {
  return entrees.vide();
}

template<class K, class V>
void ArbreMap<K, V>::enlever(const K& c) {
  entrees.enlever(c);
}

template<class K, class V>
bool ArbreMap<K, V>::contient(const K& c) const {
  return entrees.contient(c);
}

template<class K, class V>
const V& ArbreMap<K, V>::operator[](const K& c) const {
  typename ArbreAVL<Entree>::Iterateur iter = entrees.rechercher(c);
  return entrees[iter].valeur;
}

template<class K, class V>
V& ArbreMap<K, V>::operator[](const K& c) {
  typename ArbreAVL<Entree>::Iterateur iter = entrees.rechercher(c);
  if (!iter) {
    entrees.inserer(c);
    iter = entrees.rechercher(c);
  }
  return entrees[iter].valeur;
}

#endif
