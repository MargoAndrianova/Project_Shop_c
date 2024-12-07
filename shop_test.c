//Андріанова Маргарита Юріївна
//Комп'ютерна математика 2

/*
 * shop_test.c
 *
 * Тестовий модуль програми.
 * Містить функції для автоматизованого тестування всіх функцій модуля "shop".
 * - Виконує перевірку сценаріїв додавання, оновлення, видалення продуктів та працівників.
 * - Тестує функції продажів, знижок та поповнення запасів.
 * - Записує результати тестування у файл "test_results.txt".
 */

#include "shop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Оголошення функцій тестування
void runTests(Store *store, const char *testFileName, const char *resultFileName);
void loadTestDataFromFile(Store *store, const char *fileName);
void addTestProducts(Store *store);
void addTestEmployees(Store *store);
void testAllFunctions(Store *store, FILE *resultFile);

int main() {
    Store store = {NULL, NULL, 0, 0, 0.0};  // Ініціалізація магазину

    char testFileName[50];
    char resultFileName[50] = "test_results.txt";  // Результати збережуться тут

    printf("Enter the filename to load test data (or press Enter to use default tests): ");
    fgets(testFileName, sizeof(testFileName), stdin);
    testFileName[strcspn(testFileName, "\n")] = '\0'; // Видалення символу нового рядка

    printf("Running automated tests...\n");
    runTests(&store, testFileName[0] ? testFileName : NULL, resultFileName);
    printf("Test results saved to '%s'\n", resultFileName);

    // Очищення пам'яті
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

    fprintf(resultFile, "=== STARTING AUTOMATED TESTING ===\n");

    if (testFileName) {
        fprintf(resultFile, "Loading test data from file: %s\n", testFileName);
        loadTestDataFromFile(store, testFileName);
    } else {
        fprintf(resultFile, "Adding default test data...\n");
        addTestProducts(store);
        addTestEmployees(store);
    }

    testAllFunctions(store, resultFile);
    fprintf(resultFile, "=== AUTOMATED TESTING COMPLETED ===\n");

    fclose(resultFile);
}

void testAllFunctions(Store *store, FILE *resultFile) {
    // Тестування функцій
    fprintf(resultFile, "Testing addProduct...\n");
    addProduct(store, "Mouse", 25.0, 50);
    displayProducts(store, resultFile);

    fprintf(resultFile, "Testing updateProduct...\n");
    updateProduct(store, "Mouse", 30.0, 45);
    displayProducts(store, resultFile);

    fprintf(resultFile, "Testing removeProduct...\n");
    removeProduct(store, "Mouse");
    displayProducts(store, resultFile);

    fprintf(resultFile, "Testing addEmployee...\n");
    addEmployee(store, "Charlie", 2500.0, "Technician");
    displayEmployees(store, resultFile);

    fprintf(resultFile, "Testing updateEmployee...\n");
    updateEmployee(store, "Charlie", 2700.0);
    displayEmployees(store, resultFile);

    fprintf(resultFile, "Testing removeEmployee...\n");
    removeEmployee(store, "Charlie");
    displayEmployees(store, resultFile);

    fprintf(resultFile, "Testing sellProduct...\n");
    sellProduct(store, "Laptop", 2, "Alice");
    displayProducts(store, resultFile);
    displayEmployees(store, resultFile);

    fprintf(resultFile, "Testing setDiscount...\n");
    setDiscount(store, "Phone", 10.0);
    displayProducts(store, resultFile);

    fprintf(resultFile, "Testing autoRestock...\n");
    autoRestock(store, 20);
    displayProducts(store, resultFile);

    fprintf(resultFile, "Testing displayProfit...\n");
    displayProfit(store);
}

void loadTestDataFromFile(Store *store, const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (!file) {
        perror("Error opening file for reading");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char name[50];
        double price, salary;
        int quantity;
        char role[20];

        if (sscanf(line, "Product: %49[^,], Price: %lf, Quantity: %d", name, &price, &quantity) == 3) {
            addProduct(store, name, price, quantity);
        } else if (sscanf(line, "Employee: %49[^,], Salary: %lf, Role: %19s", name, &salary, role) == 3) {
            addEmployee(store, name, salary, role);
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
