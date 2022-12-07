#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define arbre_vide   NULL    /* pour déclarer arbre vide */
#define   typeElem   int    /* à déclarer avant la structure */
#define   booleen   int    /* on définit le type booléen  */
#define    faux     0  
#define    vrai     1

typedef struct aa {
    typeElem valeur ;
    struct aa  *g ;
    struct aa   *d;
} typeArbre ;

typedef typeArbre *arbre; 

//Fonction qui permet de cree un arbre
arbre cree_arbre( typeElem E , arbre g , arbre  d) {
    arbre tmp= (arbre)malloc(sizeof (typeArbre)) ;
    tmp->valeur = E ;
    tmp->g = g ;
    tmp->d = d;
    return  tmp ;
}

//Fonction qui verifie si un arbre est bien NULL
booleen est_vide(arbre a)
{ 	return a == arbre_vide;} 

// Écrire une fonction (récursive) detruit_arbre() qui libère la mémoire occupée par
// tous les n÷uds d'un arbre binaire.

void detruit_arbre(arbre a){
    if (a == NULL) return;
    detruit_arbre(a->g);
    detruit_arbre(a->d);
    free(a);
}

arbre gauche(arbre a ) {
    if(!est_vide(a)) return a->g;
}
int racine(arbre a) {
    if(!est_vide(a)) return a->valeur;
}

arbre droit(arbre a) {
    if(!est_vide(a))return a->d;
}
/*    les parcours   */
void prefixe (arbre a) {
    if (!est_vide(a)) {	
        printf ("%d", racine(a) );
        prefixe(gauche(a)) ;
        prefixe(droit (a) ) ;}
}

void infixe (arbre a) {
    if ( !est_vide(a)) {
        infixe( gauche(a)) ;
        printf ("%d", racine(a) ) ;
        infixe(droit(a)) ;
    }
}

void postfixe( arbre a) {
    if(!est_vide(a)) {
        postfixe(a->g) ;
        postfixe( a->d) ; 
        printf ( "%d  " , racine(a) ) ;
    }
}

arbre insere(arbre a, int valeur){
    if(a == NULL) return cree_arbre(valeur, NULL, NULL);
    else{
        if(valeur < a->valeur)
            a->g = insere(a->g, valeur);
        else  //valeur >= arbre−>valeur //
            a->d = insere(a->d, valeur);
    }
    return a;
}
arbre inserer1(int x, arbre a) {
    if (est_vide(a))
        return  consa( x,arbre_vide,  arbre_vide); 
    if (x <=racine(a))   
        a->g = inserer1(x, gauche(a));
    else 
        a->d = inserer1(x, droit(a));
    return a;
}

arbre inserer2(int x, arbre a) {
    if (est_vide(a))
        return  consa( x,arbre_vide,  arbre_vide);
    if (x <=racine(a))  {
        arbre b = inserer2(x, gauche(a));
        return consa( racine(a), b,  droit(a));
    }
    else if (x >racine(a)) {
        arbre b = inserer2(x, droit(a));
        return consa( racine(a), gauche(a),b);
    }
    return a;
}
booleen recherche (int X, arbre a) {
	if (est_vide(a))  return faux;
    if ( X == racine(a))
        return vrai;
    if (X < racine(a))
       return recherche (X, gauche(a));
    else
       return recherche (X,  droit(a));
}

int nbTotalNoeuds(arbre a){
    return (a != NULL) ? nbTotalNoeuds(a->d) + nbTotalNoeuds(a->g) + 1 : 0;
}

int nbTotalNoeudsBinaire(arbre a){
    return (a != NULL) && (a->d && a->g) ? nbTotalNoeudsBinaire(a->d) + a->g + 1: 0;
}

int hauteur(arbre a){
    if (a != NULL){
        return 1 + hauteur(a->d) + hauteur(a->g);
    }
    else return 0;
}

booleen recherche_noeud(int e, arbre a){
    if (a != NULL) return 0;
    if(e == a->valeur){

    }
    else if(e < a->valeur){
      
    }else if(e > a->valeur){
        
    }
}

int nbNoeuds(arbre a){
    if (a != NULL) return 0;
    if (!a->d && a->g) return nbNoeuds(a->g);
    else if (a->d && !a->g) return nbNoeuds(a->d);
}

void affiche_arbre_rec ( arbre a) {
    if(a!= NULL) {
        affiche_arbre_rec(a->g);
        if(a->g != NULL)
            printf(",");
        printf("%d", a->valeur);
        if(a->d != NULL)
            printf(",");
        affiche_arbre_rec(a->d);
    }
}

void affiche_arbre(arbre a){
    affiche_arbre_rec(a);
    printf("\n");
}

void affiche_arbre2_rec(arbre a){
    if(a == NULL) printf("arbre vide");
    else {
        printf("{");
        affiche_arbre2_rec(a->g);
        printf(",%d", a->valeur);
        affiche_arbre2_rec(a->d);
        printf("}");
    }
}
void affiche_arbre2(arbre a){
    affiche_arbre2_rec(a);
    printf("\n");
}

int compare(arbre a1, arbre a2){
    if(a1 == NULL) return a2;
    else if (a2 == NULL) return a1;
    else 
        return ((a1->valeur != a2->valeur) || compare(a1->g, a2->g) || compare(a1->d, a2->d));
}
int tri_rec(arbre a, int i, int *tableau){
    int j = 0;
    if (a == NULL) return j;
    j = tri_rec(a->g, i, tableau);
    tableau[i + j] = a->valeur;
    j++;
    j+= tri_rec(a->d, i + j, tableau);
    return j;
}

void tri(int taille, int *tableau){
    arbre a = NULL;
    for(int i=0 ; i < taille; i++){
        a = inserer(a, tableau[i]);
        tri_rec(a, 0, tableau);
        detruit_arbre(a);
    }
}
int main(){
 
    /*  Exemple dutilisation  de TAD arbre 
    arbre   a1 =cree_arbre(11 ,arbre_vide, arbre_vide) ;
    arbre   a2 =  cree_arbre(22 ,arbre_vide, arbre_vide) ; ;
    arbre   a3 =cree_arbre(33,arbre_vide, arbre_vide) ;
    arbre   a4 =  cree_arbre(44 ,arbre_vide, arbre_vide) ; ;

    arbre   a5 =cree_arbre(55, a1,a2);

    arbre   a6 =cree_arbre(66, a3,a4);
    arbre   a7 =cree_arbre(77, a5,a6);

    postfixe(a7) ;

    printf("\n");
    prefixe(a7) ;
    printf("\n");
    infixe(a7) ;
    printf("\n");
    */
    arbre  abr= arbre_vide;
    abr = inserer2(12,abr);
    abr = inserer2(20,abr);
    abr = inserer2(14,abr);
    abr = inserer2(8,abr);
    abr = inserer2(16,abr);
    abr = inserer2(21,abr);
    abr = inserer2(17,abr);
    abr = inserer2(10,abr);
    abr = inserer2(13,abr);
    infixe (abr);
    printf("\n***  %d\n",recherche(21,abr));
    printf("\n****   %d\n",recherche(44,abr));
    return 0;
}
