#include "contactos.h"
#include "slist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define MaxBufferDef 256


contacto solicitarDatos() {
  char temp[MaxBufferDef] ; //String temporal para guardar las entradas del usuario de manera dinámica
  contacto datosContactoNuevo ;
  
  printf("Ingrese el nombre del contacto: ") ;
  scanf("%[^\n]", temp)  ; 
  getchar() ;
  datosContactoNuevo.nombre = malloc(sizeof(char) * (strlen(temp) + 1)) ;
  strcpy(datosContactoNuevo.nombre, temp)  ; 

  printf("Ingrese la direccion del contacto: ") ;
  scanf("%[^\n]", temp)  ; 
  getchar() ;
  datosContactoNuevo.direccion = malloc(sizeof(char) * (strlen(temp) + 1)) ;
  strcpy(datosContactoNuevo.direccion, temp)  ;

  printf("Ingrese el telefono del contacto: ") ;
  scanf("%[^\n]", temp)  ; 
  getchar() ;
  datosContactoNuevo.telefono = malloc(sizeof(char) * (strlen(temp) + 1)) ;
  strcpy(datosContactoNuevo.telefono, temp)  ;

  printf("Ingrese el mail del contacto: ") ;
  scanf("%[^\n]", temp)  ; 
  getchar() ;
  datosContactoNuevo.mail = malloc(sizeof(char) * (strlen(temp) + 1)) ;
  strcpy(datosContactoNuevo.mail, temp)  ;

  printf("Ingrese el alias de Telegram del contacto: ") ;
  scanf("%[^\n]", temp)  ; 
  getchar() ;
  datosContactoNuevo.aliasTelegram = malloc(sizeof(char) * (strlen(temp) + 1)) ;
  strcpy(datosContactoNuevo.aliasTelegram, temp)  ;

  printf("Ingrese el usuario de Instagram del contacto: ") ;
  scanf("%[^\n]", temp)  ; 
  getchar() ;
  datosContactoNuevo.usuarioInstagram = malloc(sizeof(char) * (strlen(temp) + 1)) ;
  strcpy(datosContactoNuevo.usuarioInstagram, temp)  ;

  return datosContactoNuevo ;
}

void nuevoContacto (SList* lista) {
  *lista = slist_agregar_inicio(*lista, solicitarDatos()) ;
}

int eliminarContactoNombre (SList* lista, char* busq) {
  int contactosEliminados = 0 ;

  for(SNodo *nodo = *lista, *ant = NULL, *nodoADestruir; nodo; ){
    if(!strcmp(nodo->dato.nombre, busq)){
      if (ant == NULL) *lista = nodo->sig ;
      else ant->sig = nodo->sig ;
      nodoADestruir = nodo ;
      nodo = nodo->sig ;
      agenda_destruir_nodo(nodoADestruir) ;
      contactosEliminados++ ;
    }
    else {
      ant = nodo ;
      nodo = nodo->sig ;
    }
  }
  return contactosEliminados ;
}

void muestraContactos (SList lista){
  printf("%s", lista == NULL ? "   No hay contactos para mostrar.\n" : "   Lista de contactos encontrados:\n") ;
	for(SNodo* temp = lista; temp != NULL; temp = temp->sig){
		printf("\n\tNombre: %s", temp->dato.nombre);
		printf("\n\tDireccion: %s", temp->dato.direccion);	
		printf("\n\tTelefono: %s", temp->dato.telefono);
		printf("\n\tMail: %s", temp->dato.mail);
		printf("\n\tAlias Telegram: %s", temp->dato.aliasTelegram);
		printf("\n\tUsuario en Instagram: %s\n", temp->dato.usuarioInstagram);
  }
}

void agenda_destruir_nodo (SNodo* nodoADestruir) {  //Como que a este no lo debería dejar acá, porque no es específicamente de contactos, es de la agenda
                                                    // Pero como eliminarContactoNombre la usa, debería dejarlo acá o ponerlo en slist o algo ((?))
                                                    // En conclusión, no sé qué hacer aa
  free(nodoADestruir->dato.nombre);
  free(nodoADestruir->dato.direccion);
  free(nodoADestruir->dato.telefono);
  free(nodoADestruir->dato.mail);
  free(nodoADestruir->dato.aliasTelegram);
  free(nodoADestruir->dato.usuarioInstagram);
  free(nodoADestruir);
}


int contiene(char* dato, char* busqueda){
  int contb = 0, contd = 0;  //contb = posicion en busqueda, contd = posicion en dato
  
  while(*(dato + contd) && *(busqueda + contb)){
    if(tolower(*(busqueda + contb)) == tolower(*(dato + contd))){
      contb++;
      contd++;
    } else{
      contd = (contd - contb) + 1;
      contb = 0;
    }
  }

  if(! *(busqueda + contb)) return 1;
  else return 0;
}

char* dato_nombre (SNodo* lista){
  return lista->dato.nombre;
}

char* dato_telefono (SNodo* lista){
  return lista->dato.telefono;
}

SList busqueda(SList lista, char* busq, char* (*parametro)()){
  SList resultado = NULL;
  for(; lista; lista = lista->sig){
    if(contiene(parametro(lista), busq))
      resultado = slist_agregar_inicio(resultado, lista->dato);
  }
  return resultado;
}

SList buscarContactosNombre(SList lista, char* busq){
  return busqueda(lista, busq, dato_nombre);
}

SList buscarContactosTelefono(SList lista, char* busq){
  return busqueda(lista, busq, &dato_telefono);
}
