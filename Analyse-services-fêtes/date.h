#if !defined(__DATE_H__)
#define __DATE_H__

#include <iostream>

class Date{
  public:
    Date(int nbsecondes_=0);
    Date(int j, int h, int m, int s);
    
    bool operator <(const Date& date) const;
    bool operator <=(const Date& date) const;
    bool operator ==(const Date& date) const;
    bool operator >(const Date& date) const;

    const Date& operator +=(const Date& date);
    Date operator +(const Date& date) const;
    
    const Date& operator -=(const Date& date);
    Date operator -(const Date& date) const;
    
    const Date& operator *=(int facteur);
    Date operator *(int facteur) const;
    
    int getEnSecondes() const {return nbsecondes;}
    
  private:
    int nbsecondes;
    
  friend std::ostream& operator << (std::ostream&, const Date& date);
  friend std::istream& operator >> (std::istream&, Date& date);
};

struct Intervalle{
    Intervalle();
    Intervalle(const Date& d, const Date& f);
    Date debut, 
         fin;
    bool overlaps(const Intervalle& o) const;
    
    friend std::istream& operator >> (std::istream& is, Intervalle& itervale);
    friend std::ostream& operator << (std::ostream& os, const Intervalle& itervale);
};

#endif
