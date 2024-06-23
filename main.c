#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

typedef struct film
{
    char kode_film[5];
    char nama_film[50];
    int durasi_film;
    int studio_bioskop;
    float harga_tiket;
    struct film *next;
} film;

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int buttonHandler(int *posisi)
{
    int button = getch();

    if (button == 80)
    {
        (*posisi)++;
    }
    else if (button == 72)
    {
        (*posisi)--;
    }
    return button;
}

void arrow(int posisi, int nomor)
{
    if (posisi == nomor)
    {
        printf("> ");
    }
    else
    {
        printf("  ");
    }
}

void add_link(film **head, char kode_film[], char nama_film[], int durasi_film, int studio_bioskop, float harga_tiket)
{
    film *new_film = (film *)malloc(sizeof(film));
    if (new_film == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    strcpy(new_film->kode_film, kode_film);
    strcpy(new_film->nama_film, nama_film);
    new_film->durasi_film = durasi_film;
    new_film->studio_bioskop = studio_bioskop;
    new_film->harga_tiket = harga_tiket;
    new_film->next = NULL;

    if (*head == NULL)
    {
        *head = new_film;
    }
    else
    {
        film *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_film;
    }
}

film *load_data(char filename[])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open file %s.\n", filename);
        return NULL;
    }

    film *head = NULL;
    char kode_film[6];
    char nama_film[51];
    int durasi_film;
    int studio_bioskop;
    float harga_tiket;

    while (fscanf(file, "%5[^;];%50[^;];%d;%d;%f\n", kode_film, nama_film, &durasi_film, &studio_bioskop, &harga_tiket) == 5)
    {
        add_link(&head, kode_film, nama_film, durasi_film, studio_bioskop, harga_tiket);
    }

    fclose(file);
    return head;
}

// Function to display films from linked list
void display_data(film *head)
{
    film *current = head;

    if (current == NULL)
    {
        printf("DATA IS EMPTY!!\n");
        return;
    }
    int y = 4;
    while (current != NULL)
    {
        gotoxy(65, y);
        printf("Kode film: %s", current->kode_film);
        gotoxy(65, y + 1);
        printf("Nama film: %s", current->nama_film);
        gotoxy(65, y + 2);
        printf("Durasi film: %d Minutes", current->durasi_film);
        gotoxy(65, y + 3);
        printf("Nomor Studio: %d", current->studio_bioskop);
        gotoxy(65, y + 4);
        printf("Harga Tiket: %.2f", current->harga_tiket);
        gotoxy(65, y + 5);
        printf("--------------------");

        y += 7; // Move to the next set of lines for the next film

        current = current->next;
    }
    getch();
}

void free_list(film *head)
{
    film *current = head;
    while (current != NULL)
    {
        film *temp = current;
        current = current->next;
        free(temp);
    }
}

film *search_data(film *head, char kode_film[])
{
    film *current = head;
    while (current != NULL)
    {
        if (strcmp(current->kode_film, kode_film) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void update_data(film *head, char kode_film[], char nama_film[], int durasi_film, int studio_bioskop, float harga_tiket)
{
    film *current = search_data(head, kode_film);
    if (current != NULL)
    {
        strcpy(current->nama_film, nama_film);
        current->durasi_film = durasi_film;
        current->studio_bioskop = studio_bioskop;
        current->harga_tiket = harga_tiket;
    }
}

void delete_data(film **head, char kode_film[])
{
    film *current = *head;
    film *previous = NULL;
    while (current != NULL)
    {
        if (strcmp(current->kode_film, kode_film) == 0)
        {
            if (previous == NULL)
            {
                *head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void save_data(film *head, char filename[])
{
    FILE *file = fopen(filename, "w");
    film *current = head;
    while (current != NULL)
    {
        fprintf(file, "%s;%s;%d;%d;%.2f\n", current->kode_film, current->nama_film, current->durasi_film, current->studio_bioskop, current->harga_tiket);
        current = current->next;
    }
    fclose(file);
}

void sortDatabyName(film **head)
{
    if (*head == NULL)
    {
        printf("FILE IS EMPTY!!\n");
        return;
    }
    int swapped;
    film *ptr1;
    film *lptr = NULL;

    // Bubble Sort for linked list
    do
    {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr)
        {
            if (strcmp(ptr1->nama_film, ptr1->next->nama_film) > 0)
            {
                // Swap the data of the two nodes
                char kode_film[5];
                char nama_film[50];
                int durasi_film;
                int studio_bioskop;
                float harga_tiket;

                strcpy(kode_film, ptr1->kode_film);
                strcpy(nama_film, ptr1->nama_film);
                durasi_film = ptr1->durasi_film;
                studio_bioskop = ptr1->studio_bioskop;
                harga_tiket = ptr1->harga_tiket;

                strcpy(ptr1->kode_film, ptr1->next->kode_film);
                strcpy(ptr1->nama_film, ptr1->next->nama_film);
                ptr1->durasi_film = ptr1->next->durasi_film;
                ptr1->studio_bioskop = ptr1->next->studio_bioskop;
                ptr1->harga_tiket = ptr1->next->harga_tiket;

                strcpy(ptr1->next->kode_film, kode_film);
                strcpy(ptr1->next->nama_film, nama_film);
                ptr1->next->durasi_film = durasi_film;
                ptr1->next->studio_bioskop = studio_bioskop;
                ptr1->next->harga_tiket = harga_tiket;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void sortDatabyDuration(film **head)
{
    if (*head == NULL)
    {
        printf("FILE IS EMPTY!!\n");
        return;
    }

    int swapped;
    film *ptr1;
    film *lptr = NULL;

    // Bubble Sort for linked list
    do
    {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr)
        {
            if (ptr1->durasi_film > ptr1->next->durasi_film)
            {
                // Swap the data of the two nodes
                char kode_film[5];
                char nama_film[50];
                int durasi_film;
                int studio_bioskop;
                float harga_tiket;

                strcpy(kode_film, ptr1->kode_film);
                strcpy(nama_film, ptr1->nama_film);
                durasi_film = ptr1->durasi_film;
                studio_bioskop = ptr1->studio_bioskop;
                harga_tiket = ptr1->harga_tiket;

                strcpy(ptr1->kode_film, ptr1->next->kode_film);
                strcpy(ptr1->nama_film, ptr1->next->nama_film);
                ptr1->durasi_film = ptr1->next->durasi_film;
                ptr1->studio_bioskop = ptr1->next->studio_bioskop;
                ptr1->harga_tiket = ptr1->next->harga_tiket;

                strcpy(ptr1->next->kode_film, kode_film);
                strcpy(ptr1->next->nama_film, nama_film);
                ptr1->next->durasi_film = durasi_film;
                ptr1->next->studio_bioskop = studio_bioskop;
                ptr1->next->harga_tiket = harga_tiket;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

int login(char username[], char password[])
{
    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0)
    {
        return 1;
    }
    return 0;
}

void menuSortData(film **head)
{
    int posisi = 1;
    int button;
    do
    {
        button = 0;
        while (button != 13)
        {
            system("cls");
            gotoxy(2, 10);
            printf("Sort by :\n");
            gotoxy(2, 12);
            arrow(posisi, 1);
            gotoxy(3, 12);
            printf("1. Sort list based on name\n");

            gotoxy(2, 14);
            arrow(posisi, 2);
            gotoxy(3, 14);
            printf("2. Sort list based on duration\n");

            gotoxy(2, 16);
            arrow(posisi, 3);
            gotoxy(3, 16);
            printf("3. Exit\n");
            button = buttonHandler(&posisi);
            if (posisi > 3)
            {
                posisi = 1;
            }
            else if (posisi < 1)
            {
                posisi = 3;
            }
        }

        switch (posisi)
        {
        case 1:
            sortDatabyName(head);
            gotoxy(62, 2);
            printf("Sorted by name.\n");
            gotoxy(62, 4);
            display_data(*head);
            break;
        case 2:
            sortDatabyDuration(head);
            gotoxy(62, 2);
            printf("Sorted by duration.\n");
            gotoxy(62, 4);
            display_data(*head);
            break;
        case 3:
            return;
        default:
            printf("Invalid choice.\n");
        }
    } while (posisi != 3);
}

int main()
{
    int button;
    int posisi = 1;
    int choice;
    char kode_film[5];
    char nama_film[50];
    int durasi_film;
    int studio_bioskop;
    float harga_tiket;
    char username[50];
    char password[50];
    int checkLogin;
    film *head = NULL;
    char filename[] = "data.txt";
    head = load_data(filename);

    do
    {
        system("cls");
        gotoxy(62, 10);
        printf("=====ADMINISTRATOR XXI MOVIE=====\n");
        gotoxy(75, 12);
        printf("LOGIN\n");
        gotoxy(62, 14);
        printf("Username: ");
        scanf("%s", username);
        gotoxy(62, 16);
        printf("Password: ");
        scanf("%s", password);
        checkLogin = login(username, password);
        if (checkLogin == 0)
        {
            gotoxy(68, 18);
            printf("WRONG USERNAME OR PASSWORD\n");
            gotoxy(75, 20);
            printf("TRY AGAIN");
            getch();
        }
    } while (checkLogin == 0);

    do
    {
        button = 0;
        while (button != 13)
        {
            system("cls");
            gotoxy(62, 10);
            printf("=====  CINEMA MANAGEMENT APP  =====\n\n");
            gotoxy(62, 11);
            arrow(posisi, 1);
            gotoxy(65, 11);
            printf("1. Add New Movie\n\n");
            gotoxy(62, 13);
            arrow(posisi, 2);
            gotoxy(65, 13);
            printf("2. Show All Movies\n\n");
            gotoxy(62, 15);
            arrow(posisi, 3);
            gotoxy(65, 15);
            printf("3. Find Movie\n\n");
            gotoxy(62, 17);
            arrow(posisi, 4);
            gotoxy(65, 17);
            printf("4. Update Movie Data\n\n");
            gotoxy(62, 19);
            arrow(posisi, 5);
            gotoxy(65, 19);
            printf("5. Delete Movie Data\n\n");
            gotoxy(62, 21);
            arrow(posisi, 6);
            gotoxy(65, 21);
            printf("6. Sort Data \n\n");
            gotoxy(62, 23);
            arrow(posisi, 7);
            gotoxy(65, 23);
            printf("7. Log Out\n\n");

            button = buttonHandler(&posisi);
            if (posisi > 7)
            {
                posisi = 1;
            }
            else if (posisi < 1)
            {
                posisi = 7;
            }
        }
        int checkCode;

        switch (posisi)
        {
        case 1:
            system("cls");

            do
            {
                system("cls");
                gotoxy(62, 10);
                printf("----- ADD MOVIE -----\n");
                gotoxy(62, 12);
                printf("Movie Code (max 5 elements): ");
                scanf("%s", kode_film);
                checkCode = strlen(kode_film);
                if (checkCode > 5)
                {
                    gotoxy(62, 14);
                    printf("-----WRONG INPUT CODE!!-----");
                    getch();
                }

            } while (checkCode > 5);

            gotoxy(62, 14);
            printf("Movie Title: ");
            scanf(" %[^\n]s", nama_film);
            gotoxy(62, 16);
            printf("Movie Duration: ");
            scanf("%d", &durasi_film);
            gotoxy(62, 18);
            printf("Studio: ");
            scanf("%d", &studio_bioskop);
            gotoxy(62, 20);
            printf("Ticket Price: ");
            scanf("%f", &harga_tiket);
            add_link(&head, kode_film, nama_film, durasi_film, studio_bioskop, harga_tiket);
            save_data(head, filename);
            break;
        case 2:
            system("cls");
            gotoxy(62, 2);
            printf("=====LIST MOVIE=====\n");
            gotoxy(62, 4);
            display_data(head);
            break;
        case 3:
            system("cls");
            gotoxy(62, 10);
            printf("=====SEARCH DATA=====\n");
            gotoxy(62, 12);
            printf("Movie Code: ");
            scanf("%s", kode_film);
            film *found = search_data(head, kode_film);
            if (found != NULL)
            {
                gotoxy(62, 14);
                printf("===== DATA HAS FOUND =====\n");
                gotoxy(62, 16);
                printf("Movie Code: %s\n", found->kode_film);
                gotoxy(62, 18);
                printf("Movie Title %s\n", found->nama_film);
                gotoxy(62, 20);
                printf("Movie Duration: %d Minutes\n", found->durasi_film);
                gotoxy(62, 22);
                printf("Studio: %d\n", found->studio_bioskop);
                gotoxy(62, 24);
                printf("Ticket Price: %.2f\n", found->harga_tiket);
            }
            else
            {
                gotoxy(62, 14);
                printf("===== DATA NOT FOUND =====\n");
            }
            getch();
            break;
        case 4:

            system("cls");
            gotoxy(62, 10);
            printf("=====UPDATE DATA=====\n");
            gotoxy(62, 12);
            printf("Movie Code: ");
            scanf("%s", kode_film);
            film *update = search_data(head, kode_film);
            if (update != NULL)
            {
                gotoxy(62, 14);
                printf("Movie Title: ");
                scanf(" %[^\n]s", nama_film);
                gotoxy(62, 16);
                printf("Movie Duration: ");
                scanf("%d", &durasi_film);
                gotoxy(62, 18);
                printf("Studio: ");
                scanf("%d", &studio_bioskop);
                gotoxy(62, 20);
                printf("Ticket Price : ");
                scanf("%f", &harga_tiket);
                update_data(head, kode_film, nama_film, durasi_film, studio_bioskop, harga_tiket);
                save_data(head, filename);
            }
            else
            {
                gotoxy(62, 14);
                printf("===== DATA NOT FOUND =====\n");
                getch();
            }

            break;
        case 5:
            system("cls");
            gotoxy(62, 10);
            printf("===== DELETE MOVIE DATA =====\n");
            gotoxy(62, 12);
            printf("Code Movie: ");
            scanf("%s", kode_film);
            film *delete = search_data(head, kode_film);
            if (delete != NULL)
            {
                delete_data(&head, kode_film);
                save_data(head, filename);
                gotoxy(62, 14);
                printf("DATA HAS DELETED!\n");
                getch();
            }
            else
            {
                gotoxy(62, 14);
                printf("===== DATA NOT FOUND =====\n");
                getch();
            }

            break;
        case 6:
            system("cls");
            menuSortData(&head);
            break;
        case 7:
            system("cls");
            gotoxy(62, 14);
            printf("===== ADIOSS =====\n");
            free_list(head);
            return 0;
        default:
            printf("Pilihan tidak valid\n");
        }
    } while (posisi != 8);

    return 0;
}
