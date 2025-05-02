#include "date.h"
#include <cstdio>
#include <iomanip>
#include <assert.h>

Date::Date(int nbsecondes_)
 : nbsecondes(nbsecondes_)
{
}

Date::Date(int j, int h, int m, int s)
{
  nbsecondes = j;
  nbsecondes *= 24;
  nbsecondes += h;
  nbsecondes *= 60;
  nbsecondes += m;
  nbsecondes *= 60;
  nbsecondes += s;
}

bool Date::operator <(const Date& d) const{
    return nbsecondes < d.nbsecondes;
}
bool Date::operator <=(const Date& d) const{
    return nbsecondes <= d.nbsecondes;
}
bool Date::operator ==(const Date& d) const{
    return nbsecondes == d.nbsecondes;
}
bool Date::operator >(const Date& d) const{
    return nbsecondes > d.nbsecondes;
}

const Date& Date::operator +=(const Date& d){
    nbsecondes += d.nbsecondes;
    return *this;
}

Date Date::operator +(const Date& d) const{
    return Date(nbsecondes + d.nbsecondes);
}

const Date& Date::operator *=(int f){
    nbsecondes *= f;
    return *this;
}

Date Date::operator *(int f) const{
    return Date(nbsecondes * f);
}

std::ostream& operator << (std::ostream& os, const Date& d){
    int jours, heures, minutes, secondes;
    int s = d.nbsecondes;
    secondes = s % 60;
    s /= 60;
    minutes = s % 60;
    s /= 60;
    heures = s % 24;
    s /= 24;
    jours = s;
    char chaine[40];
    sprintf(chaine, "%dj_%02dh%02dm%02ds", jours, heures, minutes, secondes);
    os << chaine;
    return os;
}

std::istream& operator >> (std::istream& is, Date& d){
    int jours, heures, minutes, secondes;
    char j, m, h, s, underscore;
    is >> jours >> j >> underscore >> heures >> h >> minutes >> m >> secondes >> s;
    assert(j=='j' && underscore=='_');
    assert(h=='h' && m=='m' && s=='s');
    d.nbsecondes = jours;
    d.nbsecondes *= 24;
    d.nbsecondes += heures;
    d.nbsecondes *= 60;
    d.nbsecondes += minutes;
    d.nbsecondes *= 60;
    d.nbsecondes += secondes;
    return is;
}

Intervalle::Intervalle(){
}

Intervalle::Intervalle(const Date& d, const Date& f)
 : debut(d), fin(f)
{
}

bool Intervalle::overlaps(const Intervalle& o) const{
    return o.debut<=fin && debut <= o.fin;
}

std::istream& operator >> (std::istream& is, Intervalle& intervalle)
{
    char crochetgauche, crochetdroit, virgule;
    is >> crochetgauche >> intervalle.debut >> virgule >> intervalle.fin >> crochetdroit;
    assert(crochetgauche=='[' && virgule==',' && crochetdroit==']');
    return is;
}

std::ostream& operator << (std::ostream& os, const Intervalle& intervalle)
{
    os << '[' << intervalle.debut << ',' << intervalle.fin << ']';
    return os;
}


