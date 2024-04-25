#define _GNU_SOURCE
#include "liste_noeud.h"
#include <stdlib.h>
#include <math.h>

struct liste_noeud_t{
    _cellule* debut;
};

liste_noeud_t* creer_liste(){
    liste_noeud_t* liste = (liste_noeud_t*) malloc(sizeof(liste_noeud_t));
    liste->debut = NULL;
    return liste;
}

void detruire_liste(liste_noeud_t** liste_ptr){
    if(liste_ptr != NULL){
        liste_noeud_t* liste = *liste_ptr;
        _cellule* curseur = liste->debut;
        _cellule* a_detruire;
        while (curseur != NULL){
            a_detruire = curseur;
            curseur = curseur->suivante;
            free(a_detruire);
        }
        liste->debut = NULL;
        *liste_ptr = NULL;
    }
}

bool est_vide_liste(const liste_noeud_t* liste){
    return liste->debut == NULL;
}

bool contient_noeud_liste(const liste_noeud_t* liste, noeud_id_t noeud){
    _cellule* curseur = liste->debut;
    while (curseur != NULL)
    {
        if (curseur->noeud == noeud)
        {
            return true;
        }
        curseur = curseur->suivante;
    }
    return false;
}

bool contient_arrete_liste(const liste_noeud_t* liste, noeud_id_t source, noeud_id_t destination){
    _cellule* curseur = liste->debut;
    while (curseur != NULL)
    {
        if (curseur->noeud == destination && curseur->precedent == source)
        {
            return true;
        }
        curseur = curseur->suivante;
    }
    return false;
}

float distance_noeud_liste(const liste_noeud_t* liste, noeud_id_t noeud){
    _cellule* curseur = liste->debut;
    while (curseur != NULL)
    {
        if (curseur->noeud == noeud)
        {
            return curseur->distance;
        }
        curseur = curseur->suivante;
    }
    return INFINITY;
}

noeud_id_t precedent_noeud_liste(const liste_noeud_t* liste, noeud_id_t noeud){
    _cellule* curseur = liste->debut;
    while (curseur != NULL)
    {
        if (curseur->noeud == noeud)
        {
            return curseur->precedent;
        }
        curseur = curseur->suivante;
    }
    return NO_ID;
}

noeud_id_t min_noeud_liste(const liste_noeud_t* liste){
    _cellule* curseur = liste->debut;
    float distance_min = INFINITY;
    float noeud_min = NO_ID;
    while (curseur != NULL)
    {
        if (curseur->distance < distance_min)
        {
            distance_min = curseur->distance;
            noeud_min = curseur->noeud;
        }
        curseur = curseur->suivante;
    }
    return noeud_min;
}

void inserer_noeud_liste(liste_noeud_t* liste, noeud_id_t noeud, noeud_id_t precedent, float distance){
    _cellule* nouveau_noeud = (_cellule*) malloc(sizeof(_cellule));
    nouveau_noeud->noeud = noeud;
    nouveau_noeud->distance = distance;
    nouveau_noeud->precedent = precedent;
    nouveau_noeud->suivante = liste->debut;

    liste->debut = nouveau_noeud;
}

void changer_noeud_liste(liste_noeud_t* liste, noeud_id_t noeud, noeud_id_t precedent, float distance){
    _cellule* curseur = liste->debut;

    if(curseur == NULL){
        _cellule* nouveau_noeud = (_cellule*) malloc(sizeof(_cellule));
        nouveau_noeud->noeud = noeud;
        nouveau_noeud->distance = distance;
        nouveau_noeud->precedent = precedent;
        nouveau_noeud->suivante = NULL;
        liste->debut = nouveau_noeud;
    } else {
        _cellule* previous = curseur;
        bool found = false;
        while (curseur != NULL)
        {
            if (curseur->noeud == noeud){
                curseur->precedent = precedent;
                curseur->distance = distance;
                found = true;
            }
            previous = curseur;
            curseur = curseur->suivante;
        }
        if(!found){
            _cellule* nouveau_noeud = (_cellule*) malloc(sizeof(_cellule));
            nouveau_noeud->noeud = noeud;
            nouveau_noeud->distance = distance;
            nouveau_noeud->precedent = precedent;
            nouveau_noeud->suivante = NULL;
            previous->suivante = nouveau_noeud;
        } 
    }  
    
} 

void supprimer_noeud_liste(liste_noeud_t* liste, noeud_id_t noeud){
    _cellule* curseur = liste->debut;

    _cellule* previous = NULL;
    _cellule* adetruire;
    bool found = false;
    while (curseur != NULL && !found)
    {
        if (curseur->noeud == noeud){
            adetruire = curseur;
            found = true;
            if (previous)
            {
                previous->suivante = curseur->suivante;
            } else{
                liste->debut = curseur->suivante;
            }
        }
        previous = curseur;
        curseur = curseur->suivante;
    }
    if(found){
        free(adetruire);
    } 
} 