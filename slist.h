//Esto pregunta si está definida la librería, en caso de no
//estarlo la define
#ifndef __SLIST_H__
#define __SLIST_H__


typedef struct _Scontacto {
char *nombre, *direccion, *telefono, *mail, *aliasTelegram,
*usuarioInstagram ;
} contacto ;

//Esto está definiendo un nuevo tipo de dato, así como con typedef
//y struct ponemos un alias a una estructura como hemos visto en clase.
//Ahora, lo que estamos haciendo es llamar con el identificador 
//FuncionVisitante a cualquier función que tome un contacto y tenga tipo
//de retorno void 
typedef void (*FuncionVisitante) (contacto dato);

typedef struct _SNodo {
  contacto dato;
  struct _SNodo *sig;
} SNodo;

//Cuando usamos SList estamos representando un SNodo*
//es decir, usar SList sería lo mismo que usar: struct _SNodo *
typedef SNodo *SList;

/**
 * Devuelve una lista vacía.
 */
SList slist_crear();

/**
 * Destruccion de la lista.
 */
void slist_destruir(SList lista);

/**
 * Determina si la lista es vacía.
 */
int slist_vacia(SList lista);

/**
 * Agrega un elemento al final de la lista.
 */
SList slist_agregar_final(SList lista, contacto dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
SList slist_agregar_inicio(SList lista, contacto dato);


#endif /* __SLIST_H__ */
