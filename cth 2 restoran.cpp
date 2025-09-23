#include <stdio.h>
#include <string.h>

#define MAX_MENU 5
#define MAX_TABLE 10

// Struktur data menu
typedef struct {
    int id;
    char name[50];
    int price;
    int stock;
    int initialStock; // stok awal, dipakai untuk reset
} Menu;

Menu restaurant[MAX_MENU] = {
    {1, "Nasi Goreng", 20000, 10, 10},
    {2, "Mie Ayam",    15000, 8, 8},
    {3, "Sate Ayam",   25000, 12, 12},
    {4, "Es Teh",       5000, 20, 20},
    {5, "Jus Jeruk",   10000, 15, 15}
};

int tables = MAX_TABLE; // jumlah meja tersedia

// Fungsi
void displayMenu();     // tampilkan menu
void orderFood();       // pemesanan makanan
void reserveTable();    // reservasi meja
void resetStock();      // reset stok harian
void report();          // laporan stok & meja

int main() {
    int choice;
    do {
        printf("\n=== RESTAURANT SYSTEM ===\n");
        printf("1. Display Menu\n");
        printf("2. Order Food\n");
        printf("3. Reserve Table\n");
        printf("4. Report\n");
        printf("5. Reset Stock (Next Day)\n");
        printf("6. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: displayMenu(); break;
            case 2: orderFood(); break;
            case 3: reserveTable(); break;
            case 4: report(); break;
            case 5: resetStock(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 6);

    return 0;
}

// ====== TAMPILKAN MENU ======
void displayMenu() {
    printf("\n--- Restaurant Menu ---\n");
    for(int i=0;i<MAX_MENU;i++) {
        printf("%d | %s | Rp %d | Stock: %d\n", 
            restaurant[i].id, restaurant[i].name, 
            restaurant[i].price, restaurant[i].stock);
    }
}

// ====== ORDER FOOD ======
void orderFood() {
    int id, qty, found = -1, total = 0;
    displayMenu();

    printf("\nEnter Menu ID to order: ");
    scanf("%d", &id);

    for(int i=0; i<MAX_MENU; i++) {
        if(restaurant[i].id == id) {
            found = i;
            break;
        }
    }

    if(found == -1) {
        printf("Menu not found!\n");
        return;
    }

    printf("Enter Quantity: ");
    scanf("%d", &qty);

    if(qty > restaurant[found].stock) {
        printf("Not enough stock!\n");
        return;
    }

    restaurant[found].stock -= qty;
    total = qty * restaurant[found].price;

    printf("You ordered %d x %s = Rp %d\n", 
        qty, restaurant[found].name, total);
}

// ====== RESERVASI MEJA ======
void reserveTable() {
    int n;
    printf("Enter number of tables to reserve: ");
    scanf("%d", &n);

    if(n > tables) {
        printf("Not enough tables available! Remaining: %d\n", tables);
    } else {
        tables -= n;
        printf("Reservation successful! Tables left: %d\n", tables);
    }
}

// ====== RESET STOCK ======
void resetStock() {
    for(int i=0;i<MAX_MENU;i++) {
        restaurant[i].stock = restaurant[i].initialStock; // kembalikan ke stok awal
    }
    tables = MAX_TABLE; // reset meja juga
    printf("Stock and tables have been reset for the next day.\n");
}

// ====== REPORT ======
void report() {
    int totalStock = 0, totalValue = 0;
    printf("\n=== REPORT ===\n");
    displayMenu();
    printf("Remaining tables: %d\n", tables);

    for(int i=0;i<MAX_MENU;i++) {
        totalStock += restaurant[i].stock;
        totalValue += restaurant[i].stock * restaurant[i].price;
    }

    printf("Total stock left: %d | Potential value: Rp %d\n", 
        totalStock, totalValue);
}
