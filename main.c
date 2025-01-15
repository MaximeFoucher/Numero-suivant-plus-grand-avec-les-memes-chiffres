#include <stdio.h>
#include <stdlib.h>

int taille_tab(int nombre){ //avoir la longueur du nombre
    int temp = nombre;
    int taille = 0;
    while (temp > 0) {
        taille++;
        temp /= 10;
    };
    return taille;
}

int verif_ordre_croissant(int *tab, int taille){

    for (int i = 0; i < taille-1; ++i) {
        if(tab[i+1]>tab[i]){
            //pas le maximum
            return 0;
        }
    }
    return 1;
}

int compare_deux_dernier(int *tab, int taille){
    int taille_tab_2 = 2;
    int *tabtemp = (int *)malloc(taille_tab_2* sizeof(int)); //choisit les deux derniers
    int *tabtemp_inverse = (int *)malloc(taille_tab_2* sizeof(int));
    int j=1;
    for (int i = taille -1; i > taille-3 ; i--) {
        tabtemp[j]=tab[i];
        j--;
    }

    for (int i = 0; i < taille_tab_2; ++i) {
        tabtemp_inverse[i]=tab[taille-1-i];
    }

    int nb_comparatif=0;
    for (int i = 0; i < taille_tab_2; i++) {
        nb_comparatif = nb_comparatif * 10 + tabtemp_inverse[i];
    }
    free(tabtemp);
    free(tabtemp_inverse);
    return nb_comparatif;
}

// Trie un tableau dans l'ordre croissant
void tri_plus_petit(int *tab, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tab[j] > tab[j + 1]) {
                int temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
        }
    }
}

// Trouve le prochain arrangement possible
int trouve_le_suivant(int *tab, int taille, int n) {
    int *tableau_temp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        tableau_temp[i] = tab[taille - n + i];
    }

    int premier = tableau_temp[0];
    int save_place = -1, save_nb = -1;

    // Trouver le plus petit chiffre plus grand que le premier
    for (int i = 1; i < n; i++) {
        if (tableau_temp[i] > premier && (save_nb == -1 || tableau_temp[i] < save_nb)) {
            save_nb = tableau_temp[i];
            save_place = i;
        }
    }

    if (save_nb == -1) {
        free(tableau_temp);
        return 1; // Aucun élément plus grand trouvé
    }

    // Échanger le premier chiffre avec le suivant plus grand
    tableau_temp[save_place] = premier;
    tableau_temp[0] = save_nb;

    // Trier les éléments restants dans l'ordre croissant
    tri_plus_petit(tableau_temp + 1, n - 1);

    // Mettre à jour le tableau original
    for (int i = 0; i < n; i++) {
        tab[taille - n + i] = tableau_temp[i];
    }

    free(tableau_temp);
    return 0;
}

int main() {
    int nombre;
    printf("Entrez un nombre : \n");
    scanf("%d", &nombre);

    int nbtemp = nombre;
    int taille = taille_tab(nombre);

    if (taille <= 1) { // Aucun arrangement possible
        printf("Aucun arrangement possible\n");
        return -1;
    }

    int *tab = (int *)malloc(taille * sizeof(int));
    for (int i = taille - 1; i >= 0; i--) {
        tab[i] = nbtemp % 10;
        nbtemp /= 10;
    }

    if (verif_ordre_croissant(tab, taille)) {
        printf("Le numero est le plus grand possible\n");
        free(tab);
        return -1;
    }

    // Vérifie si les deux derniers chiffres peuvent être inversés
    int result = compare_deux_dernier(tab, taille);
    if (result > (nombre % 100)) {
        int temp = tab[taille - 1];
        tab[taille - 1] = tab[taille - 2];
        tab[taille - 2] = temp;

        printf("La reponse est : ");
        for (int i = 0; i < taille; ++i) {
            printf("%d", tab[i]);
        }
        printf("\n");
    } else {
        // Cas général pour n > 2
        int n = 2;
        int solution;
        do {
            n++;
            solution = trouve_le_suivant(tab, taille, n);
        } while (solution == 1);

        printf("La reponse est : ");
        for (int i = 0; i < taille; ++i) {
            printf("%d", tab[i]);
        }
        printf("\n");
    }

    free(tab);
    return 0;
}

// 2017 ==> 2071 ==> 2107 ==> 2170 ==> 2701 ==> 2710 ==> 7012