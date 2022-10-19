/* 5147233 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/abb.h"

struct _rep_abb {
    TInfo elem;
    _rep_abb *izq, *der;
};

TAbb crearAbb() { 
    TAbb nuevo = NULL;
    return nuevo; 
}

void liberarAbb(TAbb abb) {
    if(abb != NULL){
        if(abb->izq== NULL && abb->der== NULL){
            liberarInfo(abb->elem);
            delete(abb);
        }else{
        liberarAbb(abb->izq);
        liberarAbb(abb->der);
        liberarInfo(abb->elem);
        delete(abb);
        }
    }
}

bool esVacioAbb(TAbb abb) { 
    return (abb== NULL); 
}

TAbb buscarSubarbol(nat clave, TAbb abb) { 
    if(esVacioAbb(abb)){
        return NULL;
    } else {
        if (clave < natInfo(abb->elem))
        {
            return abb = buscarSubarbol(clave, abb->izq);
        }
        else if (clave > natInfo(abb->elem))
        {
            return abb = buscarSubarbol(clave, abb->der);
        }
        else
        {
            return abb;
        }
    }
}

TInfo raiz(TAbb abb) { 
    return abb->elem; 
}

TAbb izquierdo(TAbb abb) { 
    return abb->izq;
}

TAbb derecho(TAbb abb) { 
    return abb->der; 
}
 
TInfo menorEnAbb(TAbb abb) { 
    while(abb->izq!=NULL){
        abb= abb->izq;
    }
    return abb->elem;
}

TInfo mayorEnAbb(TAbb abb) {
    while(abb->der!=NULL){
        abb= abb->der;
    }
    return abb->elem;
}

TAbb consAbb(TInfo dato, TAbb izq, TAbb der) { 
    TAbb nuevo = new _rep_abb;
    nuevo->elem = dato;
    nuevo->izq = izq;
    nuevo->der = der;
    return nuevo;
}

TAbb insertarEnAbb(TInfo dato, TAbb abb) {
    if(esVacioAbb(abb)){
        TAbb abb = new _rep_abb;
        abb->elem= dato;
        abb->izq= NULL;
        abb->der=NULL;
        return abb;
    } else if(natInfo(dato)< natInfo(abb->elem)){
        abb->izq= insertarEnAbb(dato, abb->izq);
    } else {
        abb->der= insertarEnAbb(dato, abb->der);
    }
    return abb; 
}

void removerMaxAbb(TAbb &abb){
    if(abb!=NULL){
        if(natInfo(abb->elem) < natInfo(mayorEnAbb(abb)))
            removerMaxAbb(abb->der);
        else {
                TAbb aux = abb;
                abb = abb->izq;
                liberarInfo(aux->elem);
                delete(aux);
            }
    }
}


TAbb removerDeAbb(nat clave, TAbb abb){
    if (esVacioAbb(abb))
    {
        return abb;
    } else if (natInfo(abb->elem) == clave)
    {
        TAbb aux = abb;
        
        // if (aux->izq == NULL && aux->der == NULL)
        // {
        //     liberarInfo(aux->elem);
        //     delete (aux);
        //     return NULL;
        // }
        // else 
        if (aux->izq == NULL)
        {
            liberarInfo(aux->elem);
            abb = abb->der;
            delete (aux);
        }
        else if (aux->der == NULL)
        {
            liberarInfo(aux->elem);
            abb = abb->izq;
            delete (aux);
        }
        else
        {
            liberarInfo(aux->elem);
            aux->elem = copiaInfo(mayorEnAbb(aux->izq));
            removerMaxAbb(aux->izq);
            //aux->izq= removerDeAbb(natInfo(mayorEnAbb(aux->izq)),aux);
        }
    }
    else if (natInfo(abb->elem) > clave)
    {
        abb->izq= removerDeAbb(clave, abb->izq);
    }
    else
    {
        abb->der= removerDeAbb(clave, abb->der);
    }
    return abb;
}

TAbb copiaAbb(TAbb abb) {
    if(abb==NULL){
        return NULL;
    } else {
        TAbb copia = new _rep_abb;
        copia->elem = copiaInfo(abb->elem);
        copia->izq= copiaAbb(abb->izq);
        copia->der= copiaAbb(abb->der);
        return copia;
    }
}
