//Андріанова Маргарита Юріївна
//Комп'ютерна математика 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shop.h"

void logToFileAndConsole(FILE *file, const char *message) {
    if (file) {
        fprintf(file, "%s\n", message); // Запис у файл
    }
    printf("%s\n", message); // Вивід на консоль
}

void runTests(Store *store) {
    FILE *outputFile = fopen("test_output.txt", "w");
    if (!outputFile) {
        perror("Error opening test output file");
        return;
    }

    fprintf(outputFile, "=== Running Tests ===\n");

    addProduct(store, "Laptop", 1500.0, 5);
    addProduct(store, "Phone", 800.0, 10);
    displayProducts(store, outputFile);

    updateProduct(store, "Laptop", 1400.0, 7);
    displayProducts(store, outputFile);

    removeProduct(store, "Phone");
    displayProducts(store, outputFile);

    addEmployee(store, "Alice", 3000.0, "Manager");
    addEmployee(store, "Bob", 2000.0, "Cashier");
    displayEmployees(store, outputFile);

    setDiscount(store, "Laptop", 10.0);
    displayProducts(store, outputFile);

    fclose(outputFile);
}


void loadFromFileTest(Store *store, const char *filename) {
    printf("\nLoading test data from file '%s'...\n", filename);
    loadFromFile(store, filename);
    displayProducts(store, outputFile);
    displayEmployees(store, outputFile);
}

void saveTestResults(Store *store, const char *filename) {
    printf("\nSaving test results to file '%s'...\n", filename);
    saveToFile(store, filename);
    printf("Test results saved successfully.\n");
}


int main() {
    Store store = {NULL, 0, NULL, 0, 0.0};

    printf("Select input mode:\n");
    printf("1. Manual input\n");
    printf("2. Load data from file\n");
    int choice;
    scanf("%d", &choice);
    getchar(); // Clear newline character

    if (choice == 1) {
        printf("Manual input selected.\n");
        mainMenu(&store);
    } else if (choice == 2) {
        char filename[50];
        printf("Enter the filename to load test data (e.g., shop_test.dat): ");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = '\0'; // Remove newline
        loadFromFileTest(&store, filename);
    } else {
        printf("Invalid choice. Exiting...\n");
        return 1;
    }

    // Run automated tests
    runTests(&store);

    // Save test results
    char saveFilename[50];
    printf("\nEnter filename to save test results (e.g., results.dat): ");
    fgets(saveFilename, sizeof(saveFilename), stdin);
    saveFilename[strcspn(saveFilename, "\n")] = '\0'; // Remove newline
    saveTestResults(&store, saveFilename);

    // Clean up memory
    free(store.products);
    free(store.employees);

    return 0;
}
