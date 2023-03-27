#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct kontakt
{
    char imiê[20];
    char nazwisko[20];
    char numer[20];
    char grupa[20];

};
struct element {
    struct kontakt dane;
    struct element* poprzedni;
    struct element* nastêpny;
};

void push_back(struct element** góra, struct element** pocz¹tek, struct kontakt temp)
{
    struct element* elem = malloc(sizeof(struct element));
    elem->poprzedni = NULL;
    elem->nastêpny = NULL;
    elem->dane = temp;

    if (*pocz¹tek == NULL)
    {
        *pocz¹tek = elem;
        *góra = elem;
    }
    else
    {
        elem->poprzedni = *góra;
        (*góra)->nastêpny = elem;
        *góra = elem;
    }
}

void odczyt(struct element** góra, struct element** pocz¹tek)
{
 
    FILE* plik;
    //plik = fopen("prosta_lista.csv", "r");
    plik = fopen("kontakty.csv", "r");
    if (plik == NULL)
    {
        printf("Nie uda³o siê otworzyæ pliku.");
        exit(1);
    }
    struct kontakt temp;
    while (fscanf(plik, "%[^;] ; %[^;] ; %[^;] ; %s\n", temp.imiê, temp.nazwisko, temp.numer, temp.grupa) != EOF)
    {
        push_back(góra, pocz¹tek, temp);
    }
       
    fclose(plik);
}

void pop(struct element** góra, struct element** pocz¹tek)
{
    if (*pocz¹tek == NULL)
    {
        printf("Lista jest pusta.\n");
        return;
    }
    if (*góra == *pocz¹tek)
    {
        free(*pocz¹tek);
        *pocz¹tek = NULL;
        *góra = NULL;
    }
    else
    {
        struct element* temp = *góra;
        *góra = (*góra)->poprzedni;
        (*góra)->nastêpny = NULL;
        free(temp);
    }
}


void wyswietl(struct kontakt* dane)
{

    printf("Imiê: %s\n", dane->imiê);
    printf("Nazwisko: %s\n", dane->nazwisko);
    printf("Numer: %s\n", dane->numer);
    printf("Grupa: %s\n", dane->grupa);

    printf("\n");
}

void show(struct element* pocz¹tek)
{
    while (pocz¹tek != NULL)
    {
        wyswietl(&pocz¹tek->dane);

        pocz¹tek = pocz¹tek->nastêpny;
    }
    printf("\n");
}

int list_size(struct element* góra)
{
    int counter = 0;
    if (góra == NULL) return counter;
    else
    {
        struct element* kontakt = góra;
        do {
            counter++;
            kontakt = kontakt->nastêpny;
        } while (kontakt != NULL);
    }
    return counter;
}
void sortimie(struct element** pocz¹tek, struct element** góra)
{
    int size = list_size(*pocz¹tek);
    for (int i = 0; i < size - 1; i++)
    {
        struct element* current = *pocz¹tek;
        while (current->nastêpny != NULL)
        {
            if (strcmp(current->dane.imiê, current->nastêpny->dane.imiê) > 0)
            {
                struct kontakt temp = current->dane;
                current->dane = current->nastêpny->dane;
                current->nastêpny->dane = temp;
            }
            current = current->nastêpny;
        }
    }
}
void sortnazwisko(struct element** pocz¹tek, struct element** góra)
{
    int size = list_size(*pocz¹tek);
    for (int i = 0; i < size - 1; i++)
    {
        struct element* current = *pocz¹tek;
        while (current->nastêpny != NULL)
        {
            if (strcmp(current->dane.nazwisko, current->nastêpny->dane.nazwisko) > 0)
            {
                struct kontakt temp = current->dane;
                current->dane = current->nastêpny->dane;
                current->nastêpny->dane = temp;
            }
            current = current->nastêpny;
        }
    }
}
void sortgrupa(struct element** pocz¹tek, struct element** góra)
{
    int size = list_size(*pocz¹tek);
    for (int i = 0; i < size - 1; i++)
    {
        struct element* current = *pocz¹tek;
        while (current->nastêpny != NULL)
        {
            if (strcmp(current->dane.grupa, current->nastêpny->dane.grupa) > 0)
            {
                struct kontakt temp = current->dane;
                current->dane = current->nastêpny->dane;
                current->nastêpny->dane = temp;
            }
            current = current->nastêpny;
        }
    }
}
void pushbetter(struct element** pocz¹tek, struct element** góra)
{
    if (*pocz¹tek == NULL)
    {
        printf("Lista jest pusta.\n");
        return;
    }
    struct element* nowy;
    nowy = (struct element*)malloc(sizeof(struct element));
    struct element* temp = (*pocz¹tek);
    if (*pocz¹tek == NULL)
    {
        *pocz¹tek = nowy;
        *góra = nowy;
        return;
    }
    printf("Wpisz dane osoby\nImiê: ");
    scanf("%s", nowy->dane.imiê);
    printf("Nazwisko: ");
    scanf("%s", nowy->dane.nazwisko);
    printf("Numer: ");
    scanf("%s", nowy->dane.numer);
    printf("Grupa: ");
    scanf("%s", nowy->dane.grupa);


    while (strcmp(temp->dane.imiê, nowy->dane.imiê) < 0)
    {
        temp = temp->nastêpny;
    }
   
    nowy->poprzedni = temp->poprzedni;
    nowy->nastêpny = temp;
    temp = nowy;
    temp->poprzedni->nastêpny = nowy;
    
}








int main()
{
    setlocale(LC_ALL, "Polish");
    struct element* góra = NULL;
    struct element* pocz¹tek = NULL;




    int wybor = -1;
    int numer = -1;
    int a = -1, k;
    char* litera;
    litera = malloc(5 * sizeof(char));

    while (wybor != 0)
    {

        system("cls");
        printf("\nAktualny stan listy: ");
        show(pocz¹tek);

        
        printf("1 --> Wczytanie elementów z pliku\n");
        printf("2 --> Usuniêcie ostatniego elementu\n");
        printf("3 --> Posortowanie elemetów alfabetyczenie\n");
        printf("4 --> Dodanie elementu do listy\n");
        printf("0 --> Zakoñczenie programu\n");




        do
        {
            scanf("%s", litera);

            if ((isdigit(*litera)) == 0)
            {
                printf("Z³y numer!\n");
            }

        } while (isdigit(*litera) == 0);
        wybor = atoi(litera);

        switch (wybor)
        {
        case 0:
            return 0;
            break;

        case 1:
            odczyt(&góra, &pocz¹tek);

            break;
        case 2:
            
            pop(&góra, &pocz¹tek);

            break;
        case 3:

           
                printf("Sortuj wed³ug:\n");
                printf("1 --> imiê\n");
                printf("2 --> nazwisko\n");
                printf("3 --> grupa\n");
                
                do
                {
                    scanf("%s", litera);

                    if ((isdigit(*litera)) == 0)
                    {
                        printf("Z³y numer!\n");
                    }

                } while (isdigit(*litera) == 0);
                k = atoi(litera);



                switch (k)
                {
                case 1:

                    sortimie(&pocz¹tek, &góra);

                    break;

                case 2:

                    sortnazwisko(&pocz¹tek, &góra);

                    break;

                case 3:

                    sortgrupa(&pocz¹tek, &góra);

                    break;

                }
            

                break;
        case 4:

            pushbetter(&pocz¹tek, &góra);

            break;

            default:
            printf("Podaj wlasciwa opcje.");
            break;

            }


        }
return 0;
}


