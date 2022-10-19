/* 5147233 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
#include "../include/cadena.h"
#include <string.h>
#include <math.h>

void cargarCadena(TAbb abb, TCadena &cad){
  if(!esVacioAbb(abb)){
    
    if(!esVacioAbb(derecho(abb)) ){
      cargarCadena(derecho(abb), cad);
    } 
    cad = insertarAlInicio(natInfo(raiz(abb)),realInfo(raiz(abb)),cad);
    if(!esVacioAbb(izquierdo(abb)) ){
      cargarCadena(izquierdo(abb), cad);
    }
  }
}

TCadena linealizacion(TAbb abb) { 
  TCadena lista= crearCadena();
  cargarCadena(abb, lista);
  return lista; 
}

void imprimirNodoYGuion(TAbb abb, int cont){
  if(!esVacioAbb(abb)){
 
  int altura = cont;
  cont++;
  if(!esVacioAbb(derecho(abb))){
    imprimirNodoYGuion(derecho(abb),cont);
  }
  //lo hago con una auxiliar para que cont no quede indefinida
  for(int i=0; i<altura;i++)
    printf("-");

  imprimirInfo(raiz(abb));
  printf("\n");
  
  if(!esVacioAbb(izquierdo(abb))){
    imprimirNodoYGuion(izquierdo(abb),cont);
  }
  }
}
void imprimirAbb(TAbb abb) {
  //Imprimo de derecha a izquierda.
  //Tal vez debo contar la cantidad de elementos para así
  //Imprimir esa cantidad de guiones antes.
  if(!esVacioAbb(abb)){
    int cant=0;
    imprimirNodoYGuion(abb,cant);
    // printf("\n");
  }
}

int max(int a, int b)
{
  if (a > b)
  {
    return a;
  }
  else
  {
    return b;
  }
}

int prof(TAbb abb)
{
  if (esVacioAbb(abb))
  {
    return 0;
  }
  else
  return 1+max(prof(izquierdo(abb)), prof(derecho(abb)));
}

int numNodos(TAbb b)
{
  if (esVacioAbb(b))
  {
    return 0;
  }
  else
  {
    return 1 + numNodos(derecho(b)) + numNodos(izquierdo(b));
  }
}

bool esPerfecto(TAbb abb)
{
  return numNodos(abb) == pow(2, prof(abb)) - 1;
}

TAbb menores(double limite, TAbb abb)
{
  TAbb res;
  if(esVacioAbb(abb)){
    return res= NULL ;
  } else {
    TAbb izq = menores(limite, izquierdo(abb));
    TAbb der = menores(limite, derecho(abb));


    if(realInfo(raiz(abb)) < limite){
      TInfo root= copiaInfo(raiz(abb));
      res = consAbb(root, izq, der);
    } else if(esVacioAbb(der)){
      res = izq;
    } else if(esVacioAbb(izq)){
      res = der;
    } else {
      TInfo mayor = copiaInfo(mayorEnAbb(izq));
      res = consAbb(mayor,izq, der);
      res = removerDeAbb(natInfo(mayor),res);
    }
  }
  return res;
}

void cantIterAux(TIterador iter,nat &contador){
  if(estaDefinidaActual(iter)){
    contador++;
    avanzarIterador(iter);
    cantIterAux(iter,contador);
  }
}
nat cantIter(TIterador iter){
  nat contador = 0;
  reiniciarIterador(iter);
  cantIterAux(iter, contador);
  return contador;
}

void caminoAscAux(nat clave, nat k, TAbb abb, TIterador &iter){
  if(!esVacioAbb(abb)){
  if(clave < natInfo(raiz(abb))){
    caminoAscAux(clave, k, izquierdo(abb),iter);

    if (cantIter(iter) < k){

      agregarAIterador(natInfo(raiz(abb)), iter);
    
    }
  } else if(clave > natInfo(raiz(abb))){
    caminoAscAux(clave, k, derecho(abb),iter);

    if (cantIter(iter) < k){

       agregarAIterador(natInfo(raiz(abb)), iter);
     
     }
  } else {
    if(k>0){
    agregarAIterador(natInfo(raiz(abb)), iter);
    }
  }
  }
}
TIterador caminoAscendente(nat clave, nat k, TAbb abb) { 
  TIterador iter = crearIterador();
  //Primero busco la clave
  //No tengo por qué chequear si es vacio desde el vamos pues prec: está la clave
  //nat rec=0;
  if(!esVacioAbb(abb) && k>0){
  caminoAscAux(clave,k,abb,iter);
  }
  return iter; 
}

void impPalCortasAux(ArregloChars prefijo, nat largoAct, TPalabras palabras, nat lim){
  //Así imprimiré todas las letras.
  //Para imprimir las de largo menor a limite chequeo que 
  //el arreglo que vengo imprimiendo no tenga mas caracteres que lim
  
    if ((letra(palabras) == '\0')){
        prefijo[largoAct] = '\0';
        printf("%s\n", prefijo);
    } else {
    if (largoAct < lim){
      prefijo[largoAct] = letra(palabras);
      impPalCortasAux(prefijo, largoAct + 1, subarboles(palabras), lim);
    }
    }
    if (siguientes(palabras) != NULL)
      impPalCortasAux(prefijo, largoAct, siguientes(palabras),lim);
}

void imprimirPalabrasCortas(nat k, TPalabras palabras)
{
  ArregloChars arrChars= new char[k+1];
  
  impPalCortasAux(arrChars,0,subarboles(palabras),k);

  delete[] arrChars;
}

// void bfpaux(int largo, int numRecor, TPalabras pal, ArregloChars pref, TPalabras &aux){
//   if(numRecor< largo){
//     //Si todavía no recorrí todo el arreglo de caracteres, no puedo saber si encontré el prefijo
//     //luego, mi cb es que la cantidad de veces que hago la funcion no sea mayor al largo de palabras.

//     if(pref[numRecor]==letra(pal)){
//       //Si encontré que la letra del prefijo coincide con la letra que apunto con pal
      
//       aux = subarboles(pal);
//       bfpaux(largo,numRecor+1,subarboles(pal),pref,aux);
//       if(siguientes(pal)!=NULL){
//         bfpaux(largo, numRecor+1, siguientes(pal), pref, aux);
//       }
//     // } else {

//     //   bfpaux(largo,numRecor,siguiente(pal),pref,aux);
//     // }
//     if (siguientes(pal) != NULL){
//       bfpaux(largo, numRecor, siguientes(pal), pref, aux);
//     }
//   } else {
//     aux=NULL;
//   }
// }



// if (subarboles(pal) == '\0')
// {
//   bfpaux(largo, numRecor + 1, pref, siguientes(pal));
// }
// else if (subarboles(pal) != '\0' && siguientes(pal) == NULL)
// {
//   bfpaux(largo, numRecor + 1, pref, subarboles(pal));
// }

void bfpaux(int largoPref, int numRecur, ArregloChars pref, TPalabras pal, TPalabras &aux)
{
  aux=pal;
  if(letra(pal)==pref[numRecur]){
    if(largoPref != numRecur) {
      //Es porque coincidí con la letra y todavía no estoy en la última
      //posicion del pref
      bfpaux(largoPref, numRecur+1, pref, subarboles(pal), aux);
    } else {
      //Estoy en el caso en el que coincida la letras hasta la ultima
      aux=pal;
    } 
  } else {
    //Si mi letra no está en el prefijo
    //Debo seguir buscando en el resto del arbol
    //Llamo la func si: el hijo no es \0 ó siguiente es null
    if(siguientes(pal)!=NULL){
      bfpaux(largoPref, numRecur,pref, siguientes(pal), aux);
    }
    //  else if(siguientes(pal)!=NULL && subarboles(pal)=="\0"){}
    else {
      //No encontré, no está
      aux=NULL;
    }
  }
}

TPalabras buscarFinPrefijo(ArregloChars prefijo, TPalabras palabras)
{
  int largoPref = strlen(prefijo)-1;
  //Porque arranca en 0
  
  //palabras=subarboles(palabras);
  TPalabras aux= NULL;

  bfpaux(largoPref, 0, prefijo, subarboles(palabras), aux);

  return aux;
}
