#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MESE 100
#define FISIER "mese.txt"

typedef struct {
    int id;
    int capacitate;
    int rezervata;
    char data[20];
    char interval_orar[10];
} Masa;

Masa mese[MAX_MESE];
int nr_mese = 0;

void incarca_datele() {
    FILE *file = fopen(FISIER, "r");
    if (!file) return;
    nr_mese = 0;
    while (fscanf(file, "%d %d %d %s %s", &mese[nr_mese].id, &mese[nr_mese].capacitate, &mese[nr_mese].rezervata, mese[nr_mese].data, mese[nr_mese].interval_orar) == 5) {
        nr_mese++;
    }
    fclose(file);
}

void salveaza_datele() {
    FILE *file = fopen(FISIER, "w");
    if (!file) return;
    for (int i = 0; i < nr_mese; i++) {
        fprintf(file, "%d %d %d %s %s\n", mese[i].id, mese[i].capacitate, mese[i].rezervata, mese[i].data, mese[i].interval_orar);
    }
    fclose(file);
}

void afiseaza_mese() {
    for (int i = 0; i < nr_mese; i++) {
        printf("Masa %d - Capacitate: %d - %s - %s\n", mese[i].id, mese[i].capacitate,
               mese[i].rezervata ? "Rezervata" : "Disponibila", mese[i].data);
    }
}

void adauga_masa(int id, int capacitate) {
    mese[nr_mese].id = id;
    mese[nr_mese].capacitate = capacitate;
    mese[nr_mese].rezervata = 0;
    strcpy(mese[nr_mese].data, "-");
    strcpy(mese[nr_mese].interval_orar, "-");
    nr_mese++;
    salveaza_datele();
}

void sterge_masa(int id) {
    for (int i = 0; i < nr_mese; i++) {
        if (mese[i].id == id) {
            for (int j = i; j < nr_mese - 1; j++) {
                mese[j] = mese[j + 1];
            }
            nr_mese--;
            salveaza_datele();
            return;
        }
    }
    printf("Masa nu a fost gasita!\n");
}

void rezerva_masa(int id, char *data, char *interval) {
    for (int i = 0; i < nr_mese; i++) {
        if (mese[i].id == id && !mese[i].rezervata) {
            mese[i].rezervata = 1;
            strcpy(mese[i].data, data);
            strcpy(mese[i].interval_orar, interval);
            salveaza_datele();
            return;
        }
    }
    printf("Masa nu poate fi rezervata!\n");
}

void anuleaza_rezervare(int id) {
    for (int i = 0; i < nr_mese; i++) {
        if (mese[i].id == id && mese[i].rezervata) {
            mese[i].rezervata = 0;
            strcpy(mese[i].data, "-");
            strcpy(mese[i].interval_orar, "-");
            salveaza_datele();
            return;
        }
    }
    printf("Rezervarea nu a fost gasita!\n");
}

int main() {
    int optiune, id, capacitate;
    char data[20], interval[10];
    incarca_datele();
    do {
        printf("\n1. Afiseaza mese\n2. Adauga masa\n3. Sterge masa\n4. Rezerva masa\n5. Anuleaza rezervare\n0. Iesire\nOptiune: ");
        scanf("%d", &optiune);
        switch (optiune) {
            case 1:
                afiseaza_mese();
                break;
            case 2:
                printf("ID Masa: ");
                scanf("%d", &id);
                printf("Capacitate: ");
                scanf("%d", &capacitate);
                adauga_masa(id, capacitate);
                break;
            case 3:
                printf("ID Masa: ");
                scanf("%d", &id);
                sterge_masa(id);
                break;
            case 4:
                printf("ID Masa: ");
                scanf("%d", &id);
                printf("Data (YYYY-MM-DD): ");
                scanf("%s", data);
                printf("Interval orar (HH:MM-HH:MM): ");
                scanf("%s", interval);
                rezerva_masa(id, data, interval);
                break;
            case 5:
                printf("ID Masa: ");
                scanf("%d", &id);
                anuleaza_rezervare(id);
                break;
        }
    } while (optiune != 0);
    return 0;
}
