#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "slist.h"
#include "contactos.c"
#define MaxBufferDef 256
#define CLEAR "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
#define ENCABEZADO "[Trabajo Practico 1: Agenda Personal IPS 2021 5to Informatica]\n\n\n\n"

//Trabajo Practico N° 1: Agenda Personal. Grupo: Eugenia Aguirre Damonte y Agustin Tomas Blando

void exportar_agenda(SList agenda, FILE* archivo){
    for (SNodo *nodo = agenda; nodo != NULL; nodo = nodo->sig)
        fprintf(archivo, "%s,%s,%s,%s,%s,%s\n", nodo->dato.nombre, nodo->dato.direccion, nodo->dato.telefono, nodo->dato.mail, nodo->dato.aliasTelegram, nodo->dato.usuarioInstagram);
}

void importar_agenda(SList agenda, FILE* archivo){
    char buffer[MaxBufferDef];
    for (SNodo *nodo = agenda; nodo != NULL; nodo = nodo->sig){
        nodo->dato.nombre = strtok(buffer,",");
        nodo->dato.direccion = strtok(NULL,",");
        nodo->dato.telefono = strtok(NULL,",");
        nodo->dato.mail = strtok(NULL,",");
        nodo->dato.aliasTelegram = strtok(NULL,",");
        nodo->dato.usuarioInstagram = strtok(NULL,",");
    }
}

void destruir_agenda (SList* lista){
    SNodo *aux, *temp = *lista;
    while(temp != NULL){
        aux = temp;
        temp = temp->sig;
        agenda_destruir_nodo(aux) ;
    }
    *lista = NULL;
}

bool eliminarTodosContactos (SList* lista){ 
	char respuesta[2];
	printf("\n"CLEAR"Desea eliminar todos los contactos? Ingrese 'si', en caso afirmativo o 'no', en el caso contrario. Su respuesta: ");
	scanf("%[^\n]", respuesta);
  getchar() ;

  if(!strcmp(respuesta,"si")){
    destruir_agenda(lista);
    return 1 ;
  }
  return 0 ;
}

void comando_ayuda () {
  printf(""CLEAR""ENCABEZADO"") ;
  printf("Lista de comandos:\nAyuda: Muestra esta lista.\n") ;
  printf("Contacto: Muestra las opciones del comando contacto.\n") ;
  printf("Buscar: Muestra las opciones del comando buscar\n") ;
  printf("Salir: Finaliza el programa.\n\n") ;
}

void comando_contacto (SList* agenda) {
  printf(""CLEAR""ENCABEZADO"") ;
  printf("Opciones del comando contacto: \n\t\t\t\t[c] Crear un contacto.\n") ;
  printf("\t\t\t\t[e] Elimina el o los contactos que contengan el nombre ingresado.\n") ;
  printf("\t\t\t\t[l] Muestra una lista de todos los contactos.\n") ;
  printf("\t\t\t\t[x] Elimina TODOS los contactos.\n") ;
  printf("\t\t\t\t[v] Vuelve al menu principal.\n") ;
  printf("Ingrese la opcion que desee ejecutar:\n:: ") ;
 
  char opcion ;
  char temp[MaxBufferDef] ; //String temporal para guardar las entradas del usuario de manera dinámica
  char *cadenaBuscada ;
  scanf("%c", &opcion) ;
  getchar() ;
  
  bool bandOpcionX = 0 ; //Para identificar si se solicitó la función "eliminarTodosContactos"
  bool bandOpcionL = 0 ; //Para identificar si se solicitó la función "muestraContactos" (no la ejecutamos dentro del switch)
  bool bandOpcionE = 0 ; //Para identificar si se solicitó la función "EliminarContactoNombre"

  int contactosEliminados = 0 ;   
  switch(opcion){
    //Opcion c "Crear un contacto".
    case 'c':
      nuevoContacto(agenda) ;
      break ;

    //Opcion e "Eliminar por nombre".
    case 'e':
      bandOpcionE = 1 ;
      printf(""CLEAR"Eliminar contactos: Se eliminaran todos los contactos con el nombre que se ingrese.\n") ;
      printf("Ingrese el nombre a eliminar: " ) ;
      scanf("%[^\n]", temp)  ;
      getchar() ; 
      cadenaBuscada = malloc(sizeof(char) * (strlen(temp) + 1)) ;
      strcpy(cadenaBuscada,temp) ;
      contactosEliminados = eliminarContactoNombre(agenda, cadenaBuscada) ;
      free(cadenaBuscada) ;
      break ;

    //Opcion l "Mostrar todos los contactos".
    case 'l':
      bandOpcionL = 1 ;
      break ;

    //Opcion x "Eliminar todos los contactos".
    case 'x':
      bandOpcionX = eliminarTodosContactos(agenda) ;
      break ;

    //Opcion v "Volver al menu".
    case 'v':
      break ;
    default:
      printf("Opcion invalida.") ;
  }

  printf(""CLEAR""ENCABEZADO"%s", bandOpcionX ? "Se han eliminado todos los contactos.\n\n" : "") ;
  
  if(bandOpcionE){
    if (contactosEliminados){
      printf("Se %s eliminado ", contactosEliminados == 1 ? "ha" : "han") ;
      printf("%d %s\n\n", contactosEliminados, contactosEliminados == 1 ? "contacto." : "contactos.") ;
    }
    else printf("No hay contactos para eliminar\n\n") ;
    }

  if (bandOpcionL) muestraContactos(*agenda) ;
  printf("\n\t...Volviendo al menu principal... \n") ;
}


void comando_buscar (SList* agenda) {
  SList resultado = NULL ;
  bool bandOpcionDef = 0 ; //Para identificar si la opción es inválida
  bool bandOpcionNT = 0 ; //Para identificar si se utilizó alguna de las funciones de búsqueda y así decidir si mostrar o no la lista resultado

  printf(""CLEAR""ENCABEZADO"") ;
  printf("Opciones del comando buscar: \n\t\t\t\t[n] Buscar un contacto por su nombre.\n") ;
  printf("\t\t\t\t[t] Buscar un contacto por su telefono.\n") ;
  printf("\t\t\t\t[v] Vuelve al menu principal.\n") ;
  printf("Ingrese la opcion que desee ejecutar:\n:: ") ;
  
  char opcion ;
  char temp[MaxBufferDef] ; //String temporal para guardar las entradas del usuario de manera dinámica
  char* cadenaBuscada ;
  scanf("%c", &opcion) ;
  getchar() ;

  switch(opcion){
    //Caso n "Buscar un contacto por nombre".
    case 'n': 
      printf("Ingrese el nombre a buscar: ") ;
      scanf("%[^\n]", temp)  ;
      getchar() ;
      cadenaBuscada = malloc(sizeof(char) * (strlen(temp) + 1)) ;
      strcpy(cadenaBuscada,temp) ;
      resultado = buscarContactosNombre(*agenda, cadenaBuscada) ;
      free(cadenaBuscada) ;
      bandOpcionNT = 1;
      break ;

    //Caso t "Buscar un contacto por telefono".
    case 't': ;
      printf("Ingrese el telefono a buscar: ") ;
      scanf("%[^\n]", temp)  ;
      getchar() ; 
      cadenaBuscada = malloc(sizeof(char) * (strlen(temp) + 1)) ;
      strcpy(cadenaBuscada,temp) ;
      resultado = buscarContactosTelefono(*agenda, cadenaBuscada) ;
      free(cadenaBuscada) ;
      bandOpcionNT = 1;
      break ;

    //Caso v "Volver al menu".
    case 'v':
      break ;
    default:
      bandOpcionDef = 1;
  }
  printf(""CLEAR""ENCABEZADO"") ;

  if(bandOpcionNT) muestraContactos(resultado) ;
  slist_destruir(resultado) ;

  printf("%s", bandOpcionDef ? "Opcion invalida" : "") ;
  printf("\n\t...Volviendo al menu principal... \n") ;
}

void comando_salir(){
  printf(""CLEAR""ENCABEZADO"") ;
}

//Ya que se hizo esto, no se puede construir de otra manera esta relación entre cadena y función?
//A qué se refiere con esto?
void* leer_comando (char* comando){

  if (!strcmp(comando, "ayuda"))
    return &comando_ayuda ;
  if (!strcmp(comando, "contacto"))
    return &comando_contacto ;
  if (!strcmp(comando, "buscar"))
    return &comando_buscar ; 
  if(!strcmp(comando, "salir"))
    return &comando_salir ;
  return NULL ;
}

bool menu (SList* agenda, bool* banderaPrimerLoop){
  if (*banderaPrimerLoop){
    printf(""CLEAR""ENCABEZADO"") ;
    *banderaPrimerLoop = 0 ;
  }
  printf("Ingrese un comando (ayuda para la lista de comandos) \n:: ") ;
  char *comando = malloc(sizeof(char) * MaxBufferDef) ;
  scanf("%[^ \n]", comando) ;
  getchar() ;
  for (char* p = comando; *p; p++) *p = tolower(*p) ; 
  void (*ejecutar_comando)() = leer_comando(comando) ;
  
  while(ejecutar_comando == NULL){
    printf(""CLEAR"Comando invalido. Por favor, vuelva a ingresar un comando. (El comando ""Ayuda"" muestra la lista de comandos).\n:: ") ;
    gets(comando) ;
    for (char* p = comando; *p; p++) *p = tolower(*p) ;

    ejecutar_comando = leer_comando(comando) ;
  }

  ejecutar_comando(agenda) ;
  free(comando) ;
  
  if (ejecutar_comando == comando_salir) return 1;
  return 0;
}

int main() {
  FILE* archivo_agenda;
  archivo_agenda = fopen("agenda.txt","a+");
  SList agenda = NULL ;

  //acá va la función para importar y convertirla en lista

  bool flagEND = 0 ;
  bool banderaPrimerLoop = true ;
  importar_agenda(agenda, archivo_agenda) ;
  while(!flagEND)
    flagEND = menu(&agenda, &banderaPrimerLoop) ;
  
  exportar_agenda(agenda, archivo_agenda);
  fclose(archivo_agenda);
  destruir_agenda(&agenda);
  return 0;
}