#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct kontakt
{
    char imi�[20];
    char nazwisko[20];
    char numer[20];
    char grupa[20];

};
struct element {
    struct kontakt dane;
    struct element* poprzedni;
    struct element* nast�pny;
};

void push_back(struct element** g�ra, struct element** pocz�tek, struct kontakt temp)
{
    struct element* elem = malloc(sizeof(struct element));
    elem->poprzedni = NULL;
    elem->nast�pny = NULL;
    elem->dane = temp;

    if (*pocz�tek == NULL)
    {
        *pocz�tek = elem;
        *g�ra = elem;
    }
    else
    {
        elem->poprzedni = *g�ra;
        (*g�ra)->nast�pny = elem;
        *g�ra = elem;
    }
}

void odczyt(struct element** g�ra, struct element** pocz�tek)
{
 
    FILE* plik;
    //plik = fopen("prosta_lista.csv", "r");
    plik = fopen("kontakty.csv", "r");
    if (plik == NULL)
    {
        printf("Nie uda�o si� otworzy� pliku.");
        exit(1);
    }
    struct kontakt temp;
    while (fscanf(plik, "%[^;] ; %[^;] ; %[^;] ; %s\n", temp.imi�, temp.nazwisko, temp.numer, temp.grupa) != EOF)
    {
        push_back(g�ra, pocz�tek, temp);
    }
       
    fclose(plik);
}

void pop(struct element** g�ra, struct element** pocz�tek)
{
    if (*pocz�tek == NULL)
    {
        printf("Lista jest pusta.\n");
        return;
    }
    if (*g�ra == *pocz�tek)
    {
        free(*pocz�tek);
        *pocz�tek = NULL;
        *g�ra = NULL;
    }
    else
    {
        struct element* temp = *g�ra;
        *g�ra = (*g�ra)->poprzedni;
        (*g�ra)->nast�pny = NULL;
        free(temp);
    }
}


void wyswietl(struct kontakt* dane)
{

    printf("Imi�: %s\n", dane->imi�);
    printf("Nazwisko: %s\n", dane->nazwisko);
    printf("Numer: %s\n", dane->numer);
    printf("Grupa: %s\n", dane->grupa);

    printf("\n");
}

void show(struct element* pocz�tek)
{
    while (pocz�tek != NULL)
    {
        wyswietl(&pocz�tek->dane);

        pocz�tek = pocz�tek->nast�pny;
    }
    printf("\n");
}

int list_size(struct element* g�ra)
{
    int counter = 0;
    if (g�ra == NULL) return counter;
    else
    {
        struct element* kontakt = g�ra;
        do {
            counter++;
            kontakt = kontakt->nast�pny;
        } while (kontakt != NULL);
    }
    return counter;
}
void sortimie(struct element** pocz�tek, struct element** g�ra)
{
    int size = list_size(*pocz�tek);
    for (int i = 0; i < size - 1; i++)
    {
        struct element* current = *pocz�tek;
        while (current->nast�pny != NULL)
        {
            if (strcmp(current->dane.imi�, current->nast�pny->dane.imi�) > 0)
            {
                struct kontakt temp = current->dane;
                current->dane = current->nast�pny->dane;
                current->nast�pny->dane = temp;
            }
            current = current->nast�pny;
        }
    }
}
void sortnazwisko(struct element** pocz�tek, struct element** g�ra)
{
    int size = list_size(*pocz�tek);
    for (int i = 0; i < size - 1; i++)
    {
        struct element* current = *pocz�tek;
        while (current->nast�pny != NULL)
        {
            if (strcmp(current->dane.nazwisko, current->nast�pny->dane.nazwisko) > 0)
            {
                struct kontakt temp = current->dane;
                current->dane = current->nast�pny->dane;
                current->nast�pny->dane = temp;
            }
            current = current->nast�pny;
        }
    }
}
void sortgrupa(struct element** pocz�tek, struct element** g�ra)
{
    int size = list_size(*pocz�tek);
    for (int i = 0; i < size - 1; i++)
    {
        struct element* current = *pocz�tek;
        while (current->nast�pny != NULL)
        {
            if (strcmp(current->dane.grupa, current->nast�pny->dane.grupa) > 0)
            {
                struct kontakt temp = current->dane;
                current->dane = current->nast�pny->dane;
                current->nast�pny->dane = temp;
            }
            current = current->nast�pny;
        }
    }
}
void pushbetter(struct element** pocz�tek, struct element** g�ra)
{
    if (*pocz�tek == NULL)
    {
        printf("Lista jest pusta.\n");
        return;
    }
    struct element* nowy;
    nowy = (struct element*)malloc(sizeof(struct element));
    struct element* temp = (*pocz�tek);
    if (*pocz�tek == NULL)
    {
        *pocz�tek = nowy;
        *g�ra = nowy;
        return;
    }
    printf("Wpisz dane osoby\nImi�: ");
    scanf("%s", nowy->dane.imi�);
    printf("Nazwisko: ");
    scanf("%s", nowy->dane.nazwisko);
    printf("Numer: ");
    scanf("%s", nowy->dane.numer);
    printf("Grupa: ");
    scanf("%s", nowy->dane.grupa);


    while (strcmp(temp->dane.imi�, nowy->dane.imi�) < 0)
    {
        temp = temp->nast�pny;
    }
   
    nowy->poprzedni = temp->poprzedni;
    nowy->nast�pny = temp;
    temp = nowy;
    temp->poprzedni->nast�pny = nowy;
    
}








int main()
{
    setlocale(LC_ALL, "Polish");
    struct element* g�ra = NULL;
    struct element* pocz�tek = NULL;




    int wybor = -1;
    int numer = -1;
    int a = -1, k;
    char* litera;
    litera = malloc(5 * sizeof(char));

    while (wybor != 0)
    {

        system("cls");
        printf("\nAktualny stan listy: ");
        show(pocz�tek);

        
        printf("1 --> Wczytanie element�w z pliku\n");
        printf("2 --> Usuni�cie ostatniego elementu\n");
        printf("3 --> Posortowanie elemet�w alfabetyczenie\n");
        printf("4 --> Dodanie elementu do listy\n");
        printf("0 --> Zako�czenie programu\n");




        do
        {
            scanf("%s", litera);

            if ((isdigit(*litera)) == 0)
            {
                printf("Z�y numer!\n");
            }

        } while (isdigit(*litera) == 0);
        wybor = atoi(litera);

        switch (wybor)
        {
        case 0:
            return 0;
            break;

        case 1:
            odczyt(&g�ra, &pocz�tek);

            break;
        case 2:
            
            pop(&g�ra, &pocz�tek);

            break;
        case 3:

           
                printf("Sortuj wed�ug:\n");
                printf("1 --> imi�\n");
                printf("2 --> nazwisko\n");
                printf("3 --> grupa\n");
                
                do
                {
                    scanf("%s", litera);

                    if ((isdigit(*litera)) == 0)
                    {
                        printf("Z�y numer!\n");
                    }

                } while (isdigit(*litera) == 0);
                k = atoi(litera);



                switch (k)
                {
                case 1:

                    sortimie(&pocz�tek, &g�ra);

                    break;

                case 2:

                    sortnazwisko(&pocz�tek, &g�ra);

                    break;

                case 3:

                    sortgrupa(&pocz�tek, &g�ra);

                    break;

                }
            

                break;
        case 4:

            pushbetter(&pocz�tek, &g�ra);

            break;

            default:
            printf("Podaj wlasciwa opcje.");
            break;

            }


        }
return 0;
}


