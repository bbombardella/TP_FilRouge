/* Lien du depot GitLab sur Forge : https://forge.univ-lyon1.fr/p1935610/tpfilrouge/ ; il faut etre identifie.e pour voir le contenu */

#include <stdio.h>
#include <string.h>

int correspondanceLettreAlphaTab(char alphaTab[], char lettre) {
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

int correspondanceMotSecret(char motSecret[], char lettre, int indices[], int *nbIndices) {
    int result=0;
    for(int i=0;i<strlen(motSecret);i++) {
        if(motSecret[i]==lettre || motSecret[i]==lettre-'a'+'A') {
            result=1;                           /* pas de return car plusieurs occurences possible */
            indices[*nbIndices]=i;
            *nbIndices+=1;
        }
    }
    return(result);
}

void remplitAlphaTab(char alphaTab[]) {
    for(int i=0;i<26;i++) {
        alphaTab[i]='A'+i;
    }
}

void afficheAlphaTab(char alphaTab[]) {
    for(int i=0;i<26;i++) {
        if(i%6==0) {
            printf("\n");
        }
        printf("- %c -", alphaTab[i]);
    }
}

void afficheDecoration(int tailleMot) {
    printf("\n");
    for(int i=0;i<tailleMot+3;i++) {
        printf("& ");
    }
    printf("\n");
}

int presenceTab(int tab[], int comparant, int taille) {
    for(int i=0;i<taille;i++) {
        if(comparant==tab[i]) {
            return 1;
        }
    }
    return 0;
}

void afficheMotSecret(char mot[], int indices[], int *nbIndices) {
    printf("\nLe mot a decouvrir :");
    afficheDecoration(strlen(mot));
    printf("&  ");
    for(int i=0;i<strlen(mot);i++) {
        if(presenceTab(indices, i, *nbIndices)==1) {
            printf("%c ", mot[i]);
        }
        else {
            printf("* ");
        }
    }
    printf(" &");
    afficheDecoration(strlen(mot));
}

void indiceMotSecret() {
    printf("\n&&&& Indice: c'est un type de variable existant en langage C\n");
}

int main() {
    char AlphaTab[26], lettreCorresp, motSecret[]="INTEGER";
    int k=7, corresAlphaTab, corresMotSecret, indices[strlen(motSecret)], nbIndices=0;
    remplitAlphaTab(AlphaTab);
    printf("----- Programme du pendu -----\n");
    while(k>0 && nbIndices<strlen(motSecret)) {
        afficheMotSecret(motSecret, indices, &nbIndices);
        if(k==1) {
            printf("Il vous reste qu'une seule erreur possible\n");
            indiceMotSecret();
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
        corresMotSecret=correspondanceMotSecret(motSecret, lettreCorresp, indices, &nbIndices);
        if(corresMotSecret==0) {
            k--;
        }
    }
    afficheMotSecret(motSecret, indices, &nbIndices);
    if (nbIndices==strlen(motSecret)) {
        printf("\n&&&&&&&&&&&&& GAGNE !!! &&&&&&&&&&&&&");
    }
    else {
        printf("\n&&&&&&&&&&&&& PERDU :( &&&&&&&&&&&&&");
    }
    return 0;
}
