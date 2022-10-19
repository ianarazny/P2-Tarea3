/* 5147233 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/iterador.h"

struct nodo
{
    int elem;
    nodo *sig;
};

struct _rep_iterador
{
    nodo *principio;
    nodo *actual;
    nodo *ultimo;
};

TIterador crearIterador()
{
    TIterador nuevo = new _rep_iterador;
    nuevo->principio = NULL;
    nuevo->actual = NULL;
    nuevo->ultimo = NULL;
    return nuevo;
}

void liberarIterador(TIterador iter)
{
    if (iter->principio != NULL)
    {
        nodo *borrar = iter->principio;
        while (iter->principio != iter->ultimo)
        {
            iter->principio = iter->principio->sig;
            delete (borrar);
            borrar = iter->principio;
        }
        delete (borrar);
    }
    delete (iter);
}

bool estaDefinidaActual(TIterador iter)
{
    return iter->actual != NULL;
}

void agregarAIterador(nat elem, TIterador const iter)
{
    nodo *nuevo = new nodo;
    // Puede que necesite explicitar que apunta a..
    nuevo->elem = elem;
    nuevo->sig = NULL;
    if (iter->ultimo != NULL)
    {
        iter->ultimo->sig = nuevo;
        iter->ultimo = nuevo;
    }
    else
    {
        iter->principio = nuevo;
        iter->ultimo = nuevo;
    }
}

void reiniciarIterador(TIterador const iter)
{
    if (iter->ultimo != NULL)
        iter->actual = iter->principio;
}

void avanzarIterador(TIterador const iter)
{
    if (estaDefinidaActual(iter))
    {
        iter->actual = iter->actual->sig;
    }
}

nat actualEnIterador(TIterador iter)
{
    return iter->actual->elem;
}