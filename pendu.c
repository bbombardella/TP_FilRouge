#include <stdio.h>

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

void remplitAlphaTab (char alphaTab[]) {
    for(int i=0;i<26;i++) {
        alphaTab[i]='A'+i;
    }
}

void afficheAlphaTab (char alphaTab[]) {
    for(int i=0;i<26;i++) {
        if(i%6==0) {
            printf("\n");
        }
        printf("- %c -", alphaTab[i]);
    }
}

int main() {
    char AlphaTab[26], lettreCorresp;
    int corres;
    remplitAlphaTab(AlphaTab);
    printf("----- Programme du pendu -----\n");
    for(int k=1;k<=7;k++) {
        printf("\nLes lettres encore disponibles pour l'essai numero %d \n", k);
        afficheAlphaTab(AlphaTab);
        printf("\nChoisir une lettre : ");
        rewind(stdin);
        scanf("%c", &lettreCorresp);
        corres=correspondanceLettreAlphaTab(AlphaTab, lettreCorresp);
        while(corres==0) {
            printf("Vous devez taper une lettre de l'alphabet disponible : ");
            rewind(stdin);
            scanf("%c", &lettreCorresp);
            corres=correspondanceLettreAlphaTab(AlphaTab, lettreCorresp);
        }
    }
    return 0;
}
