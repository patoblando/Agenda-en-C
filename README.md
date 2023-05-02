# Agenda-en-C

Una agenda de contatcos programada en C con listas simplemente enlazadas como parte de un trabajo practico para la tecnicatura en informática del IPS. 

<img src='https://gcdnb.pbrd.co/images/H4pkHCZLpJo1.png' width=800>

## Prerrequisitos

- GCC (https://gcc.gnu.org/)
- git (https://git-scm.com/)

## Clonar repositorio  

  Para clonar el repositorio, ejecute el siguiente comando:
  
  ```sh
  git clone https://github.com/patoblando/Agenda-en-C/
  ```
  
## Como compilar

Para compilar, ejecute los siguientes comandos en el orden dado:

```sh
gcc -c slist.c
gcc -c contactos.c
gcc -Wall -o agenda main.c slist.o
```
## Como usar la agenda

Para empezar, ejecuta el comando ayuda para ver una lista de comandos.
```sh
[Trabajo Practico 1: Agenda Personal IPS 2021 5to Informatica]



Lista de comandos:
Ayuda: Muestra esta lista.
Contacto: Muestra las opciones del comando contacto.
Buscar: Muestra las opciones del comando buscar
Salir: Finaliza el programa.

Ingrese un comando (ayuda para la lista de comandos)
::
```
### Agenda de ejemplo
Podes crear una simple agenda rapidamente para probar las funcionalidades utilizando la siguiente secuencia de comandos:

```sh
contacto
c
coba
si
8888
coba@coba.com
coba
cobaInsta

contacto
c
euge
canuto
9999
euge@euge.com
euge
eugeInsta

contacto
c
pato
micasa
1111
pato@pato.com
pato
patoInsta
```
  
  
