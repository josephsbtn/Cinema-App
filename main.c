#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

typedef struct film
{
    char kode_film[5];
    char nama_film[50];
    int durasi_film;
    int studio_bioskop;
    float harga_tiket;
    struct film *next;
} film;

typedef struct user
{
    char kode_user[5];
    char username[50];
    char password[50];
    struct user *next;
} user;

typedef struct receipt
{
    char nama_film[50];
    float harga_tiket;
    float totalHarga;
    char seatNumber[3];
    int jumlahTicket;
    struct receipt *next;
} receipt;

receipt *createReceipt(char namaFilm[], float hargaTicket, float totalHarga, char seatNumber[], int jumlahTicket)
{
    receipt *new = (receipt *)malloc(sizeof(receipt));
    strcpy(new->nama_film, namaFilm);
    new->harga_tiket = hargaTicket;
    new->totalHarga = totalHarga;
    strcpy(new->seatNumber, seatNumber);
    new->jumlahTicket = jumlahTicket;
    new->next = NULL;
    return new;
}

film *create_link(char kode_film[], char nama_film[], int durasi_film, int studio_bioskop, float harga_tiket)
{
    film *new = (film *)malloc(sizeof(film));
    strcpy(new->kode_film, kode_film);
    strcpy(new->nama_film, nama_film);
    new->durasi_film = durasi_film;
    new->studio_bioskop = studio_bioskop;
    new->harga_tiket = harga_tiket;
    new->next = NULL;
    return new;
}

void generate_random_code(char *code, int length)
{
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < length; ++i)
    {
        code[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    code[length] = '\0';
}

user *create_user(char username[], char password[])
{
    user *new_user = (user *)malloc(sizeof(user));
    generate_random_code(new_user->kode_user, 4); // Generate a random 4-character code.
    strcpy(new_user->username, username);
    strcpy(new_user->password, password);
    new_user->next = NULL;
    return new_user;
}

void add_user(user **head, char username[], char password[])
{
    user *new_user = create_user(username, password);
    if (*head == NULL)
    {
        *head = new_user;
    }
    else
    {
        user *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_user;
    }
}

user *find_user(user *head, char username[], char password[])
{
    user *current = head;
    while (current != NULL)
    {
        if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
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
    film *new = create_link(kode_film, nama_film, durasi_film, studio_bioskop, harga_tiket);
    if (*head == NULL)
    {
        *head = new;
    }
    else
    {
        film *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new;
    }
}

void addReceipt(receipt **head, char namaFilm[], float hargaTicket, float totalHarga, char seatNumber[], int jumlahTicket)
{
    receipt *new = createReceipt(namaFilm, hargaTicket, totalHarga, seatNumber, jumlahTicket);
    if (*head == NULL)
    {
        *head = new;
    }
    else
    {
        receipt *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new;
    }
}

void display_data(film *head)
{
    film *current = head;
    while (current != NULL)
    {
        printf("Kode film: %s\n", current->kode_film);
        printf("Nama film: %s\n", current->nama_film);
        printf("Durasi film: %d Minutes\n", current->durasi_film);
        printf("Nomor Studio: %d\n", current->studio_bioskop);
        printf("Harga Tiket: %.2f\n", current->harga_tiket);
        printf("--------------------\n");
        current = current->next;
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

film *search_dataName(film *head, char nama_film[])
{
    film *current = head;
    while (current != NULL)
    {
        if (strcmp(current->nama_film, nama_film) == 0)
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

void save_data(film *head, char dataFilm[])
{
    FILE *file = fopen(dataFilm, "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    film *current = head;
    while (current != NULL)
    {
        fprintf(file, "%s;%s;%d;%d;%.2f\n", current->kode_film, current->nama_film, current->durasi_film, current->studio_bioskop, current->harga_tiket);
        current = current->next;
    }
    fclose(file);
}

void save_users(char filename[], user *head)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    user *current = head;
    while (current != NULL)
    {
        fprintf(file, "%s;%s;%s\n", current->kode_user, current->username, current->password);
        current = current->next;
    }
    fclose(file);
}

void saveReceipt(char filename[], receipt *head)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    receipt *current = head;
    while (current != NULL)
    {
        fprintf(file, "%s;%s;%s;\n", current->nama_film, current->harga_tiket, current->totalHarga, current->seatNumber, current->jumlahTicket);
        current = current->next;
    }
    fclose(file);
}

film *load_data(char dataFilm[])
{
    FILE *file = fopen(dataFilm, "r");
    if (file == NULL)
    {
        printf("File not found.\n");
        return NULL;
    }

    film *head = NULL;
    char kode_film[5];
    char nama_film[50];
    int durasi_film;
    int studio_bioskop;
    float harga_tiket;
    while (fscanf(file, "%[^;];%[^;];%d;%d;%f\n", kode_film, nama_film, &durasi_film, &studio_bioskop, &harga_tiket) == 5)
    {
        add_link(&head, kode_film, nama_film, durasi_film, studio_bioskop, harga_tiket);
    }
    fclose(file);
    return head;
}

user *load_users(char filename[])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File not found.\n");
        return;
    }

    char kode_user[5];
    char username[50];
    char password[50];
    char line[100];

    while (fgets(line, sizeof(line), file))
    {
    }

    fclose(file);
}

int buttonHandler(int *posisi)
{
    int button = getch();

    if (button == 80)
    { // 80 = arrow down
        (*posisi)++;
    }
    else if (button == 72)
    { // 72 = arrow up
        (*posisi)--;
    }
    return button;
}

void sortDatabyName(film **head)
{
    if (*head == NULL)
    {
        printf("FILE IS EMPTY!!\n");
        getch();
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
                // Swap the names
                char tempName[50];
                strcpy(tempName, ptr1->nama_film);
                strcpy(ptr1->nama_film, ptr1->next->nama_film);
                strcpy(ptr1->next->nama_film, tempName);

                // Swap the price
                float tempPrice;
                tempPrice = ptr1->harga_tiket;
                ptr1->harga_tiket = ptr1->next->harga_tiket;
                ptr1->next->harga_tiket = tempPrice;

                // Swap film code
                char tempCode[5];
                strcpy(tempCode, ptr1->kode_film);
                strcpy(ptr1->kode_film, ptr1->next->kode_film);
                strcpy(ptr1->next->kode_film, tempCode);

                // Swap film duration
                int tempDuration;
                tempDuration = ptr1->durasi_film;
                ptr1->durasi_film = ptr1->next->durasi_film;
                ptr1->next->durasi_film = tempDuration;

                // Swap studio
                int tempStudio;
                tempStudio = ptr1->studio_bioskop;
                ptr1->studio_bioskop = ptr1->next->studio_bioskop;
                ptr1->next->studio_bioskop = tempStudio;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    system("cls");
    printf("SORTED DATA\n");
    display_data(*head);
    getch();
}

void inputData(film **head)
{
    char kode_film[5], nama_film[50];
    int durasi_film;
    int studio_bioskop;
    float harga_tiket;
    printf("Tambah data film\n");
    printf("Kode film: ");
    scanf("%s", kode_film);
    printf("Nama film: ");
    scanf(" %[^\n]s", nama_film);
    printf("Durasi film: ");
    scanf("%d", &durasi_film);
    printf("Nomor Studio: ");
    scanf("%d", &studio_bioskop);
    printf("Harga Tiket: ");
    scanf("%f", &harga_tiket);
    add_link(head, kode_film, nama_film, durasi_film, studio_bioskop, harga_tiket);
}

void findData(film *head)
{
    char kode_film[5];
    printf("Cari data film\n");
    printf("Kode film: ");
    scanf("%s", kode_film);
    film *found = search_data(head, kode_film);
    if (found != NULL)
    {
        printf("Data ditemukan\n");
        printf("Kode film: %s\n", found->kode_film);
        printf("Nama film: %s\n", found->nama_film);
        printf("Durasi film: %d Minutes\n", found->durasi_film);
        printf("Nomor Studio: %d\n", found->studio_bioskop);
        printf("Harga Tiket: %.2f\n", found->harga_tiket);
    }
    else
    {
        printf("Data tidak ditemukan\n");
    }
}

void updateFilmData(film *head)
{
    char kode_film[5], nama_film[50];
    int durasi_film;
    int studio_bioskop;
    float harga_tiket;
    printf("Update data film\n");
    printf("Kode film: ");
    scanf("%s", kode_film);
    printf("Nama film: ");
    scanf(" %[^\n]s", nama_film);
    printf("Durasi film: ");
    scanf("%d", &durasi_film);
    printf("Nomor Studio: ");
    scanf("%d", &studio_bioskop);
    printf("Harga Tiket: ");
    scanf("%f", &harga_tiket);
    update_data(head, kode_film, nama_film, durasi_film, studio_bioskop, harga_tiket);
}

void deleteFilmData(film **head)
{
    char kode_film[5];
    printf("Hapus data film\n");
    printf("Kode film: ");
    scanf("%s", kode_film);
    delete_data(head, kode_film);
}

void sortDatabyDuration(film **head)
{
    if (*head == NULL)
    {
        printf("FILE IS EMPTY!!\n");
        getch();
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
            printf("posisi %d", posisi);
            printf("tombol = %d \n", button);
            printf("Sort by :\n");
            arrow(posisi, 1);
            printf("1. Sort list based on name\n");
            arrow(posisi, 2);
            printf("2. Sort list based on duration\n");
            arrow(posisi, 3);
            printf("3. Log Out\n");

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
            break;
        case 2:
            sortDatabyDuration(head);
            break;
        default:
            break;
        }
    } while (posisi != 3);
}

void buyTicket(film *filmList, receipt *receiptHead)
{
    char kode_film[5];
    int jumlahTicket;
    char seatNumber[3];

    display_data(filmList);
    printf("Enter the film code you want to buy: ");
    scanf("%s", kode_film);

    film *selectedFilm = search_data(filmList, kode_film);
    if (selectedFilm != NULL)
    {
        printf("Enter the number of tickets: ");
        scanf("%d", &jumlahTicket);
        printf("Enter the seat number: ");
        scanf("%s", seatNumber);

        float totalPrice = jumlahTicket * selectedFilm->harga_tiket;
        printf("Total price: %.2f\n", totalPrice);
        printf("Purchase successful!\n");

        // Create and add the receipt
        addReceipt(&receiptHead, selectedFilm->nama_film, selectedFilm->harga_tiket, totalPrice, seatNumber, jumlahTicket);
    }
    else
    {
        printf("Film not found!\n");
    }
}

void menuUser(user **userHead, film **head, receipt **receiptHead)
{
    int posisi = 1;
    int button;
    do
    {
        button = 0;
        while (button != 13)
        {
            system("cls");
            printf("posisi %d", posisi);
            printf("tombol = %d \n", button);
            printf("CINEMA XII\n");
            arrow(posisi, 1);
            printf("1. List Movie\n");
            arrow(posisi, 2);
            printf("2. Buy Ticket\n");
            arrow(posisi, 3);
            printf("3. Receipt Ticket\n");
            arrow(posisi, 4);
            printf("4. Log Out\n");

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
            system("cls");
            display_data(*head);
            getch();
            break;
        case 2:
            system("cls");
            buyTicket(*head, *receiptHead);
            getch();
        case 3:
            system("cls");
            receiptTicket();
            getch();
        default:
            break;
        }
    } while (posisi != 4);
}

void menuAdmin(film **head)
{
    int posisi = 1;
    int button;
    do
    {
        button = 0;
        while (button != 13)
        {
            system("cls");
            printf("posisi %d", posisi);
            printf("tombol = %d \n", button);
            printf("CINEMA MANAGEMENT APP\n");
            arrow(posisi, 1);
            printf("1. Add New Movie\n");
            arrow(posisi, 2);
            printf("2. Show All Movies\n");
            arrow(posisi, 3);
            printf("3. Find Movie\n");
            arrow(posisi, 4);
            printf("4. Update Movie Data\n");
            arrow(posisi, 5);
            printf("5. Delete Movie Data\n");
            arrow(posisi, 6);
            printf("6. Save All Data to File\n");
            arrow(posisi, 7);
            printf("7. Sort Data \n");
            arrow(posisi, 8);
            printf("8. Log Out\n");

            button = buttonHandler(&posisi);
            if (posisi > 8)
            {
                posisi = 1;
            }
            else if (posisi < 1)
            {
                posisi = 8;
            }
        }

        switch (posisi)
        {
        case 1:
            system("cls");
            inputData(head);
            break;
        case 2:
            system("cls");
            display_data(*head);
            getch();
            break;
        case 3:
            system("cls");
            findData(*head);
            getch();
            break;
        case 4:
            system("cls");
            updateFilmData(*head);
            break;
        case 5:
            system("cls");
            deleteFilmData(head);
            break;
        case 6:
            system("cls");
            save_data(*head, "data.txt");
            printf("Data saved to file.\n");
            getch();
            break;
        case 7:
            system("cls");
            menuSortData(head);
            break;
        }
    } while (posisi != 8);
}

void login(user **headUser, film **headFilm, receipt **headReceipt)
{
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    user *found_user = find_user(*headUser, username, password);
    if (found_user != NULL)
    {
        system("cls");
        printf("Login successful!\n");
        getch();
        menuUser(*headUser, *headFilm, *headReceipt);
    }
    else if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0)
    {
        system("cls");
        printf("WELCOME ADMIN!\n");
        menuAdmin(*headFilm);
    }

    else
    {
        printf("Login failed! Incorrect username or password.\n");
        getch();
    }
}

void regUser(user **head)
{
    char username[50];
    char password[50];
    char passwordUlan[10];
    system("cls");
    printf("REGISTRATION ACCOUNT\n");
    printf("Enter username: ");
    scanf("%s", username);
    do
    {
        printf("Enter password: ");
        scanf("%s", password);
        printf("Reapeat Password:");
        scanf("%s", passwordUlan);
    } while (strcmp(password, passwordUlan) != 0);

    add_user(head, username, password);
    printf("Registration successful!\n");
    getch();
}

int main()
{
    srand(time(0));
    film *head = NULL;
    user *head_user = NULL;
    receipt *head_receipt = NULL;

    char dataFilm[] = "dataFilm.txt";
    char userFile[] = "user.txt";
    char receiptFile[] = "receipt.txt";

    head_user = load_users(userFile);
    head = load_data(dataFilm);

    int posisi = 1;
    int button;
    do
    {
        button = 0;
        while (button != 13)
        {
            system("cls");
            printf("posisi %d", posisi);
            printf("tombol = %d \n", button);
            printf("WELCOME TO XXI APPS:\n");
            arrow(posisi, 1);
            printf("1. LOGIN\n");
            arrow(posisi, 2);
            printf("2. REGISTER ACCOUNT\n");
            arrow(posisi, 3);
            printf("3. EXIT\n");

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
            login(&head_user, &head, &head_receipt);
            break;
        case 2:
            regUser(&head_user);
            save_users(userFile, head_user);
            saveReceipt(receiptFile, head_receipt);
            break;
        case 3:
            save_data(head, dataFilm);
            break;
        default:
            break;
        }
    } while (posisi != 3);

    return 0;
}
