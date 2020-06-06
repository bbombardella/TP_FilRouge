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

int correspondanceMotSecret(char motSecret[], char lettre, int trouvees[], int *nbTrouvees) {
    int result=0, i=0;
    while(motSecret[i]!='\0') {
        if(motSecret[i]==lettre || motSecret[i]==lettre-'a'+'A') {
            result=1;                           /* pas de return car plusieurs occurences possible */
            trouvees[i]=1;
            *nbTrouvees+=1;
        }
        i++;
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

void afficheMotSecret(char mot[], int trouvees[], int longueurMot) {
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

void indiceMotSecret() {
    printf("\n&&&& Indice: c'est un type de variable existant en langage C\n");
}

int main() {
    char AlphaTab[26], lettreCorresp, motSecret[]="INTEGER";
    int k=7, longueurMot=strlen(motSecret),corresAlphaTab, corresMotSecret, trouvees[longueurMot], nbTrouvees=0;
    remplitAlphaTab(AlphaTab);
    printf("----- Programme du pendu -----\n");
    while(k>0 && nbTrouvees<longueurMot) {
        afficheMotSecret(motSecret, trouvees, longueurMot);
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

    return 0;
}
