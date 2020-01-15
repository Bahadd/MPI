/*
There are as many spanning trees as initiators
Each spanning tree has the id of its initiator

Idée : faire croître simultanément des arbres fragments de l’AC final.
Chaque fragment a une identité stockée sur chaque site dans la
variable id_frag.
Un site maintient un tableau de l’état de ses voisins : candidat, actif ,
inactif
Suivant l’état de ses voisins, un site est dans l’état ouvert, libre,
fermé, terminé.
Chaque fragment dispose d’un nœud privilégié : sa racine.
La racine d’un fragment est déplacée pour initialiser les tentatives de
rattachement de son fragment à un autre.
En plus de la création de l’AC on obtient une élection : la racine de
l’AC.
L’algo est conçu pour être non déterministe sur le choix de l’élu.

*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void reception(int typeOfMessage, char * voisin, char * id){}
void update_state(char * voisin, char * etat_message){}
int site_state(){}
int choice(){}
void sendId(){}
initiate_father(){}
sendEnd(){}
void res_connexion(){}

int int main(int argc, const *argv[]) {

  return 0;
}
