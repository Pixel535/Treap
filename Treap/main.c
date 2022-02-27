#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define COUNT 10

typedef struct drzewo
{
    int numer;
    double prio;
    struct drzewo *lwezel;
    struct drzewo *pwezel;
    int wysokosc;
}drzewo;

int minValueNode(drzewo **bst)
{
    drzewo* current = (*bst);
    while (current && current->lwezel != NULL)
        current = current->lwezel;

    return current;
}

int losuj(int min, int max)
{
	return (rand()%(max-min+1)+min);
}

int height(drzewo **bst)
{
    if ((*bst) == NULL)
        return 0;
    else {
        return (*bst)->wysokosc;
    }
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

int Del(drzewo **bst, int numer)
{
    if ((*bst) == NULL)
        return (*bst);

    if (numer < (*bst)->numer)
        (*bst)->lwezel = Del(&(*bst)->lwezel, numer);
    else if (numer > (*bst)->numer)
        (*bst)->pwezel = Del(&(*bst)->pwezel, numer);


    else if ((*bst)->lwezel == NULL)
    {
        drzewo *temp = (*bst)->pwezel;
        free((*bst));
        (*bst) = temp;
    }


    else if ((*bst)->pwezel == NULL)
    {
        drzewo *temp = (*bst)->lwezel;
        free((*bst));
        (*bst) = temp;
    }

    else if ((*bst)->lwezel->prio < (*bst)->pwezel->prio)
    {
        (*bst) = LR(&(*bst));
        (*bst)->lwezel = Del(&(*bst)->lwezel, numer);
    }
    else
    {
        (*bst) = RR(&(*bst));
        (*bst)->pwezel = Del(&(*bst)->pwezel, numer);
    }

    return (*bst);
}

int Add(drzewo **bst, int n)
{
    if((*bst) == NULL)
    {
        drzewo *nowe;
        nowe = (drzewo*)malloc(sizeof(drzewo));
        nowe -> numer = n;
        nowe -> prio = losuj(1,100)/100.0;
        nowe -> lwezel = NULL;
        nowe -> pwezel = NULL;
        nowe ->wysokosc = 1;
       *bst = nowe;
    }
    else
    {
        if ((*bst)->numer > n)
        {
            (*bst)->lwezel = Add(&((*bst)->lwezel), n);
            if ((*bst)->lwezel->prio > (*bst)->prio)
            {
                return RR(&(*bst));
            }
        }
        else if((*bst)->numer < n)
        {
            (*bst)->pwezel = Add(&(*bst)->pwezel, n);
            if ((*bst)->pwezel->prio > (*bst)->prio)
            {
                return LR(&(*bst));
            }

        }
        else
        {
            printf("\nWartosc juz istnieje\n");
        }
    }

    return (*bst);
}

void LR(drzewo **x)
{
    drzewo *y = (*x)->pwezel;
    drzewo *T2 = y->lwezel;

    y->lwezel = (*x);
    (*x)->pwezel = T2;

    (*x)->wysokosc = max(height(&((*x)->lwezel)), height(&((*x)->pwezel)))+1;
    y->wysokosc = max(height(&(y->lwezel)), height(&(y->pwezel)))+1;

    return y;
}

void RR(drzewo **y)
{
    drzewo *x = (*y)->lwezel;
    drzewo *T2 = x->pwezel;

    x->pwezel = (*y);
    (*y)->lwezel = T2;

    (*y)->wysokosc = max(height(&((*y)->lwezel)), height(&((*y)->pwezel)))+1;
    x->wysokosc = max(height(&(x->lwezel)), height(&(x->pwezel)))+1;

    return x;
}

void Show(drzewo *bst, int space)
{
    space += COUNT;
    if ((bst) == NULL)
    {
         return;
    }
    else
    {
        Show(bst->pwezel, space);
        printf("\n");
        for (int i = COUNT; i < space; i++)
        {
            printf(" ");
        }
        printf("%d [%.2f]\n", bst->numer, bst->prio);
        Show(bst->lwezel, space);
    }

}

void ShowLVR(drzewo **bst)
{
    if((*bst) == NULL)
    {
        printf("Drzewo jest puste\n");
    }
    else{
    if ((*bst)->lwezel != NULL)
    {
        ShowLVR(&((*bst)->lwezel));
    }
    printf("%d [%.2f] ",(*bst)->numer, (*bst)->prio);
    if ((*bst)->pwezel != NULL)
    {
        ShowLVR(&((*bst)->pwezel));
    }
    }
}

void ShowVLR(drzewo **bst)
{
     if((*bst) == NULL)
     {
        printf("Drzewo jest puste\n");
     }
     else{
     printf("%d [%.2f] ",(*bst)->numer, (*bst)->prio);
     if ((*bst)->lwezel != NULL)
     {
        ShowVLR(&((*bst)->lwezel));
     }
     if ((*bst)->pwezel != NULL)
     {
        ShowVLR(&((*bst)->pwezel));
     }
     }
}

void ShowLRV(drzewo **bst)
{
     if((*bst) == NULL)
     {
        printf("Drzewo jest puste\n");
     }
     else{
     if ((*bst)->lwezel != NULL)
     {
        ShowLRV(&((*bst)->lwezel));
     }
     if ((*bst)->pwezel != NULL)
     {
        ShowLRV(&((*bst)->pwezel));
     }
     printf("%d [%.2f] ",(*bst)->numer, (*bst)->prio);
     }
}
void ShowLVO(drzewo **bst)
{
    if((*bst) == NULL)
     {
        printf("Drzewo jest puste\n");
     }
     else{
    int h = height(&(*bst));
    h--;
    int i;
    for (i = 0; i <= h; i++)
        printCurrentLevel(&(*bst), i);
     }
}
void printCurrentLevel(drzewo **bst, int level)
{
    if ((*bst) == NULL)
        return;
    if (level == 0)
        printf("%d [%.2f] ", (*bst)->numer, (*bst)->prio);
    else if (level > 0) {
        printCurrentLevel(&(*bst)->lwezel, level - 1);
        printCurrentLevel(&(*bst)->pwezel, level - 1);
    }
}

int main()
{
    srand(time(NULL));
    drzewo *bst = NULL;
    int komenda;
    int n,k;

    while(1)
    {
        printf("Program Treap\n");
        printf("----------------------------------------------\n");
        printf("[0] Wyjscie z programu\n");
        printf("[1] Dodaj wezel\n");
        printf("[2] Usun wezel\n");
        printf("[3] Wyswietl drzewo - graficznie\n");
        printf("[4] Inorder - LVR\n");
        printf("[5] Preorder - VLR\n");
        printf("[6] Postorder - LRV\n");
        printf("[7] Level order\n");
        printf("----------------------------------------------\n\n");
		printf("\nWybrana komenda: ");
		scanf("%d", &komenda);
		printf("\n");
		switch (komenda)
		{
			case 0: return 0; break;
            case 1:
			    {
			        printf("Podaj ile liczb chesz dodac: ");
			        scanf("%d", &k);
			        for(int i = 0; i<k; i++)
                    {
                        n = losuj(1,100);
                        bst = Add(&bst, n);
                        Show(bst, 10);
                        printf("########################################################\n\n");
                        printf("LVR: ");
                        ShowLVR(&bst);
                        printf("\n");
                        printf("VLR: ");
                        ShowVLR(&bst);
                        printf("\n");
                        printf("LRV: ");
                        ShowLRV(&bst);
                        printf("\n");
                        printf("LVO: ");
                        ShowLVO(&bst);
                        printf("\n");
                        system("pause");
                        system("cls");
                    }
                    system("pause");
                    system("cls");
			        break;
			    }
            case 2:
			    {

			        printf("Podaj wartosc jaka chcesz usunac: ");
                    scanf("%d", &n);
                    printf("----------------------------------------------\n\n");
                    printf("Drzewo przed usunieciem:\n\n");
                    Show(bst, 10);
                    printf("########################################################\n\n");
                    Del(&bst, n);
                    printf("########################################################\n\n");
                    printf("Drzewo po usunieciu:\n\n");
                    Show(bst, 10);
                    printf("----------------------------------------------\n\n");
			        system("pause");
                    system("cls");
			        break;
			    }
            case 3:
			    {
			        Show(bst, 10);
			        printf("\n");
			        system("pause");
                    system("cls");
			        break;
			    }
            case 4:
                {
			        ShowLVR(&bst);
			        printf("\n");
			        system("pause");
                    system("cls");
                    break;
			    }
            case 5:
			    {
			        ShowVLR(&bst);
			        printf("\n");
			        system("pause");
                    system("cls");
                    break;
			    }
            case 6:
			    {
			        ShowLRV(&bst);
			        printf("\n");
			        system("pause");
                    system("cls");
                    break;
			    }
            case 7:
			    {
			        ShowLVO(&bst);
			        printf("\n");
			        system("pause");
                    system("cls");
                    break;
			    }
		}
    }
    return 0;
}
