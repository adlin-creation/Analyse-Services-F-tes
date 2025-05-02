/*  INF3105 - Structures de données et algorithmes
 *  UQAM / Département d'informatique
 *  http://ericbeaudry.uqam.ca/INF3105/tp3/
 *
 *	Identification.
 *		Nom et code permanent : LOUISAMA Adlin LOUA20309509
 *
 *		 
 */
#include "journal.h"

void Journal::enregistrerService(const Date& date, const string& nompersonne, const string& nomcocktail)
{
    int ordreService = compteurPersonne[nompersonne]++; 
    TraceCocktail serviceInfo = {date, nomcocktail, ordreService}; // trace a sauvegarder
    historiqueParPersonne[nompersonne].inserer(serviceInfo); // on ajoute dans l'historique
}

ArbreMap<string, int> Journal::requeteQui(const Date& debut, const Date& fin, const ArbreAVL<string>& cocktails) const
{
    ArbreMap<string, int> resultat;
    // Pour les client qui recoivent au moins 1 cocktail
    for (ArbreMap<string, ArbreAVL<TraceCocktail>>::IterateurConst 
        iter = historiqueParPersonne.debut(); iter; ++iter) {
        const string& nomPersonne = iter.cle();
        const ArbreAVL<TraceCocktail>& historique = iter.valeur();
        // Cocktail servis au client 
        for (ArbreAVL<TraceCocktail>::Iterateur iterCocktail = historique.debut(); iterCocktail; ++iterCocktail) {
            const TraceCocktail& service = *iterCocktail;
            if (!(service.date < debut) && !(fin < service.date)) { 
                if (cocktails.vide() || cocktails.rechercher(service.nomCocktail))
                    resultat[nomPersonne] += 1;
            }
        }
    }
    return resultat;
}

ArbreMap<string, int> Journal::requeteQuoi(const Date& debut, const Date& fin, const ArbreAVL<string>& buveurs) const
{
    ArbreMap<string, int> resultat;
    for (ArbreMap<string, ArbreAVL<TraceCocktail>>::IterateurConst iter = 
        historiqueParPersonne.debut(); iter; ++iter) {
        const string& nomPersonne = iter.cle();
        // Si la liste des buveurs est vide
        if (buveurs.vide() || buveurs.rechercher(nomPersonne)) {
            const ArbreAVL<TraceCocktail>& historique = iter.valeur();
            // Cocktail servis au client 
            for (ArbreAVL<TraceCocktail>::Iterateur iterCocktail = historique.debut(); iterCocktail; ++iterCocktail) {
                const TraceCocktail& service = *iterCocktail;
                if (!(service.date < debut) && !(fin < service.date)) {
                    resultat[service.nomCocktail] += 1;
                }
            }
        }
    }
    return resultat;
}


ArbreAVL<string> Journal::requetePresences(const Intervalle& i) const
{
    ArbreAVL<string> resultat;
    for (ArbreMap<string, ArbreAVL<TraceCocktail>>::IterateurConst iter = historiqueParPersonne.debut(); iter; ++iter)
    {   
        Date debutBloc, finBloc;
        bool premierBloc = true, estPresentDansIntervalle = false;
        const string& nomPersonne = iter.cle();
        const ArbreAVL<TraceCocktail>& historique = iter.valeur();

        for (ArbreAVL<TraceCocktail>::Iterateur iterCocktail = historique.debut(); iterCocktail; ++iterCocktail)
        {
            const TraceCocktail& service = *iterCocktail;
            const Date& momentService = service.date;
            // Nouveau bloc de présence
            if (premierBloc || momentService > finBloc) {
                // Verifier presence dans l'intervalle
                if (!premierBloc && !(finBloc < i.debut || i.fin < debutBloc))
                    estPresentDansIntervalle = true;
                debutBloc = momentService;
                finBloc = momentService + dureeCocktail;
                premierBloc = false;
            }
            else finBloc = finBloc + dureeCocktail;
        }
        if (!premierBloc && !(finBloc < i.debut || i.fin < debutBloc))
            estPresentDansIntervalle = true;
        if (estPresentDansIntervalle) resultat.inserer(nomPersonne);
    }

    return resultat;
}


