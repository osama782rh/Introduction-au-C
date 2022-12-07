#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/*  J'ai repris le TP-1 ou boolean était implémenter pour faire ce TP   */


/* -------------- Début TP 3 : Liste Chainées ------------*/
#define liste_vide NULL
#define typeElem int

typedef struct ll {
    typeElem e;
    struct ll *suiv;
}typeListe;

typedef typeListe *liste;

int est_vide(liste L){
    return L==liste_vide; 
}

liste cons(typeElem E , liste L) {
    liste tmp=(liste)malloc(sizeof(typeListe));
    tmp -> e=E;
    tmp -> suiv=L;
    return tmp;
}

liste suite( liste L) { return L->suiv; }
typeElem tete(liste L) { return L->e; }

typedef int bool;
#define true 1
#define false 0

int longueur(liste L){
    if(!L){
        printf("Erreur liste vide !");
        return 0;
    }
    int size = 1;
    while(L->suiv != NULL){
        L = L->suiv;
        size++;
    }
    return size;
}

void afficher(liste L){
    while(L != NULL){
        printf("%d  ",L->e);
        L=L->suiv;
    }
    return;
}

bool isLast(liste L){ return (L->suiv != NULL ? false : true);} // Si la valeur suivante est pas nul on renvoie false, sinon true

typeElem Last(liste L){
    while(L->suiv != NULL){
        L = L->suiv;
    }
    return L->e; 
}

typeElem maxL(liste L){
    typeElem max = L->e; // On initialise le max avec la première valeur de la liste
    while(L->suiv != NULL){
        if(max < L->e){
            max = L->e;
        }
        L = L->suiv;
    }
    if(max < L->e){
            max = L->e;
        }
    return max;
}

typeElem rec_maxL(liste L){
    if(L->suiv ==NULL)return L->e;
    if(rec_maxL(L->suiv) > L->e){
        return rec_maxL(L->suiv);
    }
    else {
        return L->e;
    }
}

bool recherche(typeElem X,liste L){
    while(L->suiv != NULL){
        if(X == L->e)return true;
        L = L->suiv;
    }
    return false;
}

int nb_Occu(typeElem X,liste L){
    int rep = 0;
    while(L->suiv != NULL){
        if(X == L->e)rep++;
        L = L->suiv;
    }
    return rep;
}

typeElem kieme(liste L,int k){
    while(L->suiv != NULL && k != 1){
        L=L->suiv;
        k--;
    }
    return (k == 1 ? L->e : -1); // Si k = 1 on a réussit a ramener le K element de la liste, sinon -1
}

int pos(liste L, typeElem E){
    int cpt = 0;// compteur
    while(L->suiv != NULL){
        cpt++;
        if(E == L->e){
            return cpt;
        }
        L = L->suiv;
    }
    return -1;
}

liste adr(liste L,typeElem E){
    while(L->suiv != NULL){
        if(E == L->e) return L;
        L = L->suiv;
    }
    return liste_vide;
}

void iter_inverse(liste *l){
    liste prev = NULL;
    liste current =NULL;

    if(l == NULL) return;

    current =  *l;
    liste next = NULL;
    while(current != NULL){
        next = current->suiv;

        current->suiv =  prev;

        prev = current;
        current = next;
    }
    *l = prev;
    return;
    }

void ajoutAuKieme(liste *L,int k, typeElem e){
    liste head = *L;
    while((*L)->suiv != NULL && k != 1){
        k--;
        (*L) = (*L)->suiv;
    }
    (*L)->e = e;
    *L = head;
}

void supprime_debut(liste *L){
    (*L)->e = 0;

    liste loc = *L;
    *L = (*L)->suiv;
    free(loc);
    // On libère le premier élement on renvoie le second
}

void ajout_fin(liste *L,typeElem X){
    if(*L == NULL){
        *L = (liste)malloc(sizeof(typeListe));
        (*L)->e = X;
        (*L)->suiv = NULL;
        return;
    }

    liste head = *L;
    while((*L)->suiv != NULL){
        (*L) = (*L)->suiv;
    }
    (*L)->suiv = (liste)malloc(sizeof(typeListe));
    (*L)->suiv->e = X;
    (*L)->suiv->suiv = NULL;
    *L = head;
}

void supprimeKieme(liste *L,int k){
    liste head = *L;
    liste prev;
    while((*L)->suiv != NULL && k != 1){
        k--;
        prev = (*L);
        (*L) = (*L)->suiv;

    }
    prev->suiv = (*L)->suiv;
    free(*L);
    *L=head;

}
/* On va aller au bout de la liste L1 pour ajouter le head de la liste L2 derière
    La fusion de la liste sera dans L1*/
void catenate(liste *L1,liste *L2){
    if(!(*L1) && (*L2)){// L1 vide
        (*L1) = (*L2);
        return;
    } 
    if((*L1) && !(*L2))return; // L2 vide 
    if(!(*L1) && !(*L2))return; // les deux vides
    
    liste head = *L1;
    /* On met les deux liste à la suite, si les deux listes sont égales alors ça renvoie la même liste mais en double */
    while((*L1)->suiv != NULL){
        (*L1) = (*L1)->suiv;
    }
    (*L1)->suiv = (*L2);
    *L1 = head;
    return;
}


void couper(liste *L1,liste *L2,liste *L3){
    while((*L3)->suiv != NULL){
        if((*L3)->e > 0){ // Positif
           ajout_fin((L1),(*L3)->e);
           (*L3) = (*L3)->suiv;
        }
        else if((*L3)->e < 0){ // Negatif
           ajout_fin((L2),(*L3)->e);
           (*L3) = (*L3)->suiv;
        }
        else{
            (*L3) = (*L3)->suiv;
        }
    }
}

void fusion(liste *L1,liste *L2,liste *L3){
    int f1= -1;
    int f2= -1;
    
    while((*L1)->suiv != NULL || (*L2)->suiv != NULL){
        if((*L1)->e > (*L2)->e && (*L2)->suiv != NULL){
            ajout_fin((L3),(*L2)->e);
            (*L2) = (*L2)->suiv;
        }
        else if ((*L1)->e < (*L2)->e && (*L1)->suiv != NULL){
            ajout_fin((L3),(*L1)->e);
            (*L1) = (*L1)->suiv;
        }
    }
    if((*L1)->e > (*L2)->e && f1 == -1){
        ajout_fin((L3),(*L2)->e);
        f1 = 0;
    }
    else if((*L1)->e < (*L2)->e && f2 == -1){
        ajout_fin((L3),(*L1)->e);
        f2 = 0;
    }
}

/*Bonus : Libération de la mémoire  */
void free_list(liste head){
    liste tmp;

    while(head != NULL){
        tmp = head;
        head = (head)->suiv;
        free(tmp);

    }
    return;
}

/* -------------- Fin TP 3 : Liste Chainées ------------*/



/* -------------- Début TP 1 : Bool ------------*/
bool not(bool x){ return (x == true ? false : true);} // if(x == true) return false else return true ( utilisation du ternaire )
bool and(bool x,bool y){ return (x == y ? true : false); }
bool or(bool x,bool y){ return ((x == 0) && (y == 0) ? false : true); }

int add(int x, int y){ return x + y; }
int subs(int x, int y){ return x-y; }
int mul(int x,int y){ return x*y; }
int divi(int x,int y){ return y == 0 ? printf("Erreur division par 0") : x/y ;}

int mod(int x,int y){ return x%y;}
//int puiss(int x,int y){ return y<0 ? printf("Erreur puissance négative") : pow(x,y);}
int pgcd (int x,int y){
    int pgcd;
    for(int i=1; i <= x && i <= y; ++i)
    {
        if(x%i==0 && y%i==0)
            pgcd = i;
    }
    return pgcd;
}
void test1(){
    // x & y valeurs arbitraire
    bool x = true;
    bool y = false;

    not(x) == false ? printf("Test validé \n") : printf("Test échoué \n");
    not(not(x)) == x ? printf("Test validé \n\n") : printf("Test échoué \n\n");

    and(true,x) == x ? printf("Test validé \n") : printf("Test échoué \n");
    and(false,x) == false ? printf("Test validé \n\n") : printf("Test échoué \n\n");

    or(true,x) == true ? printf("Test validé \n") : printf("Test échoué \n");
    or(false,x) == x ? printf("Test validé \n") : printf("Test échoué \n");
    or(x,y) == not(and(not(x),not(y))) ? printf("Test validé \n\n") : printf("Test échoué \n\n");

    return;
}

void test2(){
    not(or(true,false)) == or(false,false) ? printf("Test validé \n") : printf("Test échoué \n");
    not(or(true,false)) == false ? printf("Test validé \n") : printf("Test échoué \n");
    not(and(true,false)) == not(false) ? printf("Test validé \n") : printf("Test échoué \n");
    not(and(true,false)) == not(not(true)) ? printf("Test validé \n") : printf("Test échoué \n");
    not(and(true,false)) == true ? printf("Test validé \n") : printf("Test échoué \n");
    return;
}

void test3(){
    bool x = true;
    bool y = false; // valeur arbitraire

    not(or(x,y)) == and(not(x),not(y)) ? printf("Test validé \n") : printf("Test échoué \n");
    not(and(x,y)) == or(not(x),not(y)) ? printf("Test validé \n") : printf("Test échoué \n");
 
    return;
}

int succ(int x){return x++;}
int pred(int x){return x--;}

// On prend en entrée un tableau on cherche la plus grande valeur
int maxint(int *x){
    int max = x[0]; // on initialise le max avec la premiere valeur du tab
    int size = sizeof(x)/4 +1;// taille du tab (/4 car sizeof(int = 4))
    for(int i = 0;i <= size;i++){ // on parcours le tab
        if(x[i] > max) max = x[i];
    }
    return max;
}

int minint(int *x){
    int min = x[0]; // on initialise le min avec la premiere valeur du tab
    int size = sizeof(x)/4 +1;// taille du tab (/4 car sizeof(int = 4))
    for(int i = 0;i <=size;i++){ // on parcours le tab
        if(x[i] < min) min = x[i];
    }
    return min;
}
bool equal(int x,int y){ return x == y ? true : false; }

bool noequal(int x,int y){ return x != y ? true : false; }

bool LT(int x, int y){ return x < y ? true : false; }
bool LTE(int x, int y){ return x <= y ? true : false; }
bool GT(int x, int y) {return x > y ? true : false; }


/* -------------- Fin TP 1 : Bool ------------*/

int main() {
    /* On testera le programme sur une liste simple de taille 10, remplie de {0,1,2,3,4,5,6,7,8,9} */
    liste l1 = NULL;
    for(int i = 0;i<10;i++){
       ajout_fin(&l1,i);
    }
    printf("\n\n Voici la liste en entrée pour les tests : \n\n");
    afficher(l1);
    printf("\n");
        /* Partie 1 test */
    printf("Longueur : %d\n",longueur(l1));
    printf("IsLast : %d (0 = false, 1 = true)\n",isLast(l1));
    printf("Last : %d\n",Last(l1));
    printf("maxL : %d\n",maxL(l1));
    printf("rec_maxL : %d\n",rec_maxL(l1));
    printf("recherche de 3 : %d\n",recherche(3,l1));

    /* Partie 2 test */
    printf("nb_Occu de 1 : %d\n",nb_Occu(1,l1));
    printf("kieme de 4 : %d\n",kieme(l1,4));
    printf("pos de 7 : %d\n",pos(l1,7));
    printf("adresse de 3 : %p\n",adr(l1,3));

    /*Partie 3 test */
    // à Partir d'ici la liste est inversé
    printf("\n\n A partir d'ici la liste est inversé !\r\n");
    iter_inverse(&l1);
    printf("On remplace le 3ieme élément par 300 avec ajoutAuKieme\n" );
    ajoutAuKieme(&l1,3,300);
    printf("On ajoute 1986 à la fin avec ajout_fin\n");
    ajout_fin(&l1,1986);
    printf("On supprome le deuxieme élément de la liste (le 8) avec supprimeKieme");
    supprimeKieme(&l1,2);
    printf("Voici le résultat : \n");
    afficher(l1);
    printf("\n");


    /*Partie 4 test */
    printf("\n\nPour cette partie on aura deux liste \n\n");
    liste l2 = NULL;
    liste l3 = NULL;

    for(int i = 0;i<15;i++){
        ajout_fin(&l2,i*2);
        ajout_fin(&l3,-i);
    }
    printf("Liste 1 : ");
    afficher(l2);
    printf("\n");

    printf("Liste 3 : ");
    afficher(l3);
    printf("\n");

/* Test Catenate :*/
    printf("Test avec catenate : \n");
    catenate(&l2,&l3);

    printf("Liste fusionnée : ");
    afficher(l2);
    printf("\n");

 // La liste 2 contient bien tout les éléments de L2-L3

/* test couper :*/
    liste positif = NULL;
    liste negatif = NULL;
    printf("Test avec couper : \n");
    couper(&positif,&negatif,&l2);

    printf("Liste positif : ");
    afficher(positif);
    printf("\n");

    printf("Liste negatif : ");
    afficher(negatif);
    printf("\n");

/* test fusion */
    liste l4 = NULL;
    liste l5 = NULL;
    liste fus = NULL;

    for(int i = 0 ; i < 10;i++){
        ajout_fin(&l4,i*2);// 0 2 4 6
        ajout_fin(&l5,i*2+1);// 1 3 5 7
    }
    printf("\n\nIci on va tester la fonction fusion avec c'est liste \n\n");
    printf("Premiere liste : ");
    afficher(l4);
    printf("\n");
    printf("Seconde liste : ");
    afficher(l5);
    printf("\n");

    printf("\n\n fusion des deux liste :");
    fusion(&l4,&l5,&fus);

    printf("\n");
    afficher(fus);
    printf("\n");

    /* Libération mémoire :*/
    free_list(l1);
    free_list(l2);
    free_list(l3);
    free_list(l4);
    free_list(l5);

    return 0;
    }
