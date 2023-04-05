#ifndef __CONTACTOS_H__
#define __CONTACTOS_H__

#include <stdbool.h>
#include "slist.h"

contacto solicitarDatos();

void nuevoContacto (SList* lista);

int eliminarContactoNombre (SList* lista, char* busq);

bool eliminarTodosContactos (SList* lista);

void muestraContactos (SList lista);

void agenda_destruir_nodo (SNodo* nodoADestruir);

int contiene(char* dato, char* busqueda);

char* dato_nombre (SNodo* lista);

char* dato_telefono (SNodo* lista);

SList busqueda(SList lista, char* busq, char* (*parametro)());

SList buscarContactosNombre(SList lista, char* busq);

SList buscarContactosTelefono(SList lista, char* busq);

void destruir_agenda (SList* lista);

#endif  /* __CONTACTOS_H__ */