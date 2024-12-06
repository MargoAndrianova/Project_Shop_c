#include "shop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void runTests(Store *store, const char *testFileName, const char *resultFileName);
void loadTestDataFromFile(Store *store, const char *fileName);
void addTestProducts(Store *store);
void addTestEmployees(Store *store);

int main() {
    // Ініціалізація структури Store
    Store store = {NULL, NULL, 0, 0, 0.0};

    int inputMode;
    char testFileName[50];
    char resultFileName[50] = "test_results.txt"; // Ім'я файлу з результатами тестування

    printf("Select input mode:\n");
    printf("1. Manual input\n");
    printf("2. Load data from file\n");
    printf("Enter your choice: ");
    scanf("%d", &inputMode);
    getchar(); // Очищення буфера

    if (inputMode == 1) {
        printf("Manual input selected. Running manual tests...\n");
        runTests(&store, NULL, resultFileName);
    } else if (inputMode == 2) {
        printf("Enter the filename to load test data (e.g., shop_test.dat): ");
        fgets(testFileName, sizeof(testFileName), stdin);
        testFileName[strcspn(testFileName, "\n")] = '\0'; // Видалення символа '\n'
        printf("Loading test data from file '%s'...\n", testFileName);
        runTests(&store, testFileName, resultFileName);
    } else {
        printf("Invalid choice. Exiting.\n");
        return 1;
    }

    printf("Test results saved to '%s'\n", resultFileName);

    // Очистка пам'яті
    free(store.products);
    free(store.employees);

    return 0;
}

void runTests(Store *store, const char *testFileName, const char *resultFileName) {
    FILE *resultFile = fopen(resultFileName, "w");
    if (!resultFile) {
        perror("Error opening result file for writing");
        return;
    }

    if (testFileName != NULL) {
        loadTestDataFromFile(store, testFileName);
    } else {
        addTestProducts(store);
        addTestEmployees(store);
    }

    // Тестові кейси
    fprintf(resultFile, "=== Running Tests ===\n");

    // Додавання продукту
    addProduct(store, "Tablet", 1200.0, 15);
    fprintf(resultFile, "Added product: Tablet\n");

    // Оновлення продукту
    updateProduct(store, "Laptop", 1400.0, 7);
    fprintf(resultFile, "Updated product: Laptop\n");

    // Видалення продукту
    removeProduct(store, "Phone");
    fprintf(resultFile, "Removed product: Phone\n");

    // Продаж продукту
    sellProduct(store, "Headphones", 2, "Alice");
    fprintf(resultFile, "Sold 2 Headphones by Alice\n");

    // Встановлення знижки
    setDiscount(store, "Laptop", 10.0);
    fprintf(resultFile, "Set 10%% discount on Laptop\n");

    // Автоматичне поповнення запасів
    autoRestock(store, 10);
    fprintf(resultFile, "Auto restocked products\n");

    fprintf(resultFile, "=== Tests Completed ===\n");

    // Виведення результатів
    fprintf(resultFile, "=== Final State ===\n");
    fprintf(resultFile, "Products:\n");
    displayProducts(store, resultFile);
    fprintf(resultFile, "Employees:\n");
    displayEmployees(store, resultFile);

    fclose(resultFile);
}

void loadTestDataFromFile(Store *store, const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (!file) {
        perror("Error opening file for reading");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char type[20], name[50];
        double price, salary;
        int quantity;
        char role[20];

        if (sscanf(line, "Product: %49[^,], Price: %lf, Quantity: %d", name, &price, &quantity) == 3) {
            addProduct(store, name, price, quantity);
        } else if (sscanf(line, "Employee: %49[^,], Salary: %lf, Role: %19s", name, &salary, role) == 3) {
            addEmployee(store, name, salary, role);
        } else {
            printf("Invalid line in test file: %s", line);
        }
    }
    fclose(file);
}

void addTestProducts(Store *store) {
    addProduct(store, "Laptop", 1500.0, 5);
    addProduct(store, "Phone", 800.0, 10);
    addProduct(store, "Headphones", 150.0, 20);
}

void addTestEmployees(Store *store) {
    addEmployee(store, "Alice", 3000.0, "Manager");
    addEmployee(store, "Bob", 2000.0, "Cashier");
}
