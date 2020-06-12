/* Lien du depot GitLab sur Forge : https://forge.univ-lyon1.fr/p1935610/tpfilrouge/ ; il faut etre identifie.e pour voir le contenu */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remplitAlphaTab(char alphaTab[]) {             /* remplit le tableau en ajoutant l'alphabet */
    for(int i=0;i<26;i++) {
        alphaTab[i]='A'+i;
    }
}

void afficheAlphaTab(char alphaTab[]) {           /* permet d'afficher le tableau de l'alphabet */
    for(int i=0;i<26;i++) {
        if(i%6==0) {
            printf("\n");
        }
        printf("- %c -", alphaTab[i]);
    }
}

int correspondanceLettreAlphaTab(char alphaTab[], char lettre) {    /* permet de voir si la lettre saisie est bien dans l'alphabet */
    if(lettre==' ') {
        return 0;
    }
    for(int i=0;i<26;i++) {
        if(alphaTab[i]==lettre || alphaTab[i]==lettre-'a'+'A') {
            alphaTab[i]=' ';
            return 1;
        }
    }
    return 0;
}

int correspondanceMotSecret(char motSecret[], char lettre, int trouvees[], int *nbTrouvees) {       /* permet de chercher si la lettre saisie correspond au mot secret */
    int result=0, i=0;
    char lettreModifiee;
    if (lettre>='a' && lettre<='z') {
        lettreModifiee=lettre-'a'+'A';
    }
    else {
        lettreModifiee=lettre+'a'-'A';
    }
    while(motSecret[i]!='\0') {
        if(motSecret[i]==lettre || motSecret[i]==lettreModifiee) {
            result=1;                           /* pas de return car plusieurs occurences possible */
            trouvees[i]=1;
            *nbTrouvees+=1;
        }
        i++;
    }
    return(result);
}

char* saisieDynamique(int *pTaille) {
    char caractere, *c1, *c2;
    int nb=0;

    rewind(stdin);
    c1=malloc((nb+10)*sizeof(char));

    if(c1==NULL) {
        printf("\nProbleme d'allocation de memoire malloc !");
        exit(1);
    }
    scanf("%c", &c1[nb]);
    while(c1[nb]!='\n') {
        nb++;
        if(nb%10==0) {      /* on augmente la taille de la chaine de 10 caractères si nécessaire */
            c2=realloc(c1, (nb+10)*sizeof(char));
            if(c2==NULL) {
                printf("Probleme memoire realloc !");
                free(c1);
                exit(1);
            }
            c1=c2;
        }
        scanf("%c", &c1[nb]);
    }
    c1[nb]='\0';    /* on marque la fin de la chaine */
    *pTaille=nb;    /* on enregistre la taille de la chaine saisie */
    return c1;  /* retourne l'adresse de la chaine dans le TAS */
}

void afficheDecoration(int tailleMot) {     /* permet d'afficher la deco '&&&&' autour du mot secret */
    printf("\n");
    for(int i=0;i<tailleMot+3;i++) {
        printf("& ");
    }
    printf("\n");
}

void afficheMotSecret(char mot[], int trouvees[], int longueurMot) {    /* affiche le mot secret */
    int i=0;
    printf("\nLe mot a decouvrir :");
    afficheDecoration(longueurMot);
    printf("&  ");
    while(mot[i]!='\0') {
        if(trouvees[i]==1) {
            printf("%c ", mot[i]);
        }
        else {
            printf("* ");
        }
        i++;
    }
    printf(" &");
    afficheDecoration(longueurMot);
}

void remplitTabTrouvees(int trouvees[], int longueurMot) {    /* permet de remplir de la tableau trouvees de 0 apres malloc */
    for(int i=0;i<longueurMot;i++) {
        trouvees[i]=0;
    }

}

void indiceMotSecret(char indice[]) { /* affiche l'indice du mot secret */
    int i=0;
    printf("\n&&&& Indice: ");
    while(indice[i]!='\0') {
        printf("%c", indice[i]);
        i++;
    }
    printf(" &&&&\n");
}

int main() {
    char choixUser, AlphaTab[26], lettreCorresp, *motSecret=NULL, *indiceSecret=NULL;
    int k=7, longueurMot, longueurIndice, corresAlphaTab, corresMotSecret, *trouvees=NULL, nbTrouvees=0;
    remplitAlphaTab(AlphaTab);
    printf("----- Programme du pendu -----\n");
    do {
        printf("\nTaper D pour jouer a deux ou S pour jouer seul.e : ");
        scanf(" %c", &choixUser);
    } while(choixUser!='D' && choixUser!='S');
    if(choixUser=='D') {
        printf("\nLe mot a deviner ne peut pas etre compose et doit etre tape sans accent, de meme pour l'indice");
        printf("\nJoueur 'quiFaitDeviner', tapez le mot a deviner : ");
        motSecret=saisieDynamique(&longueurMot);
        printf("\nJoueur 'quiFaitDeviner', tapez l'indice : ");
        indiceSecret=saisieDynamique(&longueurIndice);
        printf("\nJoueur 'quiFaitDeviner', tapez une serie de retours a la ligne\npour effacer la console puis n'importe quelle lettre pour debuter le jeu pour Joueur 'quiDevine'");
        do {
            rewind(stdin);
            scanf(" %c", &choixUser);
        } while (choixUser<'a' && choixUser>'Z');
        printf("C'est parti pour Joueur 'quiDevine'\n");
    }
    else {
        motSecret="INTEGER";
        longueurMot=strlen(motSecret);
        indiceSecret="Type de variable en langage C";
        longueurIndice=strlen(indiceSecret);
    }
    trouvees=malloc(longueurMot*sizeof(int));
    if(trouvees==NULL) {
        printf("Probleme malloc de trouvees !");
        free(trouvees); free(motSecret); free(indiceSecret);
        exit(1);
    }
    remplitTabTrouvees(trouvees, longueurMot);
    while(k>0 && nbTrouvees<longueurMot) {
        afficheMotSecret(motSecret, trouvees, longueurMot);
        if(k==1) {
            printf("Il vous reste qu'une seule erreur possible\n");
            indiceMotSecret(indiceSecret);
        }
        else {
            printf("Il vous reste encore %d erreurs possibles\n", k);
        }
        printf("\nLes lettres encore disponibles :\n");
        afficheAlphaTab(AlphaTab);
        printf("\nChoisir une lettre : ");
        rewind(stdin);
        scanf("%c", &lettreCorresp);
        corresAlphaTab=correspondanceLettreAlphaTab(AlphaTab, lettreCorresp);
        while(corresAlphaTab==0) {
            printf("Vous devez taper une lettre de l'alphabet disponible : ");
            rewind(stdin);
            scanf("%c", &lettreCorresp);
            corresAlphaTab=correspondanceLettreAlphaTab(AlphaTab, lettreCorresp);
        }
        corresMotSecret=correspondanceMotSecret(motSecret, lettreCorresp, trouvees, &nbTrouvees);
        if(corresMotSecret==0) {
            k--;
        }
    }
    afficheMotSecret(motSecret, trouvees, longueurMot);
    if (nbTrouvees==longueurMot) {
        printf("\n&&&&&&&&&&&&& GAGNE !!! &&&&&&&&&&&&&");
    }
    else {
        printf("\n&&&&&&&&&&&&& PERDU :( &&&&&&&&&&&&&");
    }

    free(trouvees); free(motSecret); free(indiceSecret);
    return 0;
}
