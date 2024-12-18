//Андріанова Маргарита Юріївна
//Комп'ютерна математика 2

/*
 * shop.c
 *
 * Основний модуль програми.
 * Реалізує функції для:
 * - Управління продуктами (додавання, оновлення, видалення, відображення).
 * - Управління працівниками (додавання, оновлення, видалення, відображення).
 * - Продажу продуктів, розрахунку прибутку, застосування знижок та поповнення запасів.
 * - Збереження та завантаження даних у файл.
 */

#include "shop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mainMenu(Store *store) {
    int choice;
    char name[50];
    double price, salary, discount;
    int quantity;
    char role[20];

    // Відкриття файлу для запису результатів
    FILE *outputFile = fopen("results.txt", "w");
    if (!outputFile) {
        perror("Error opening results file");
        return;
    }

    do {
        printf("\n========= MAIN MENU =========\n");
        printf("1. Add Product\n");
        printf("2. Update Product\n");
        printf("3. Remove Product\n");
        printf("4. Display Products\n");
        printf("5. Add Employee\n");
        printf("6. Update Employee\n");
        printf("7. Remove Employee\n");
        printf("8. Display Employees\n");
        printf("0. Exit\n");
        printf("=============================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Очищення буфера після вводу

        switch (choice) {
            case 1:
                printf("Enter product name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0'; // Видалення символа '\n'
                printf("Enter price: ");
                scanf("%lf", &price);
                printf("Enter quantity: ");
                scanf("%d", &quantity);
                addProduct(store, name, price, quantity);
                break;

            case 2:
                printf("Enter product name to update: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("Enter new price: ");
                scanf("%lf", &price);
                printf("Enter new quantity: ");
                scanf("%d", &quantity);
                updateProduct(store, name, price, quantity);
                break;

            case 3:
                printf("Enter product name to remove: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                removeProduct(store, name);
                break;

            case 4:
                displayProducts(store, outputFile);
                break;

            case 5:
                printf("Enter employee name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("Enter salary: ");
                scanf("%lf", &salary);
                printf("Enter role: ");
                getchar();
                fgets(role, sizeof(role), stdin);
                role[strcspn(role, "\n")] = '\0';
                addEmployee(store, name, salary, role);
                break;

            case 6:
                printf("Enter employee name to update: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("Enter new salary: ");
                scanf("%lf", &salary);
                updateEmployee(store, name, salary);
                break;

            case 7:
                printf("Enter employee name to remove: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                removeEmployee(store, name);
                break;

            case 8:
                displayEmployees(store, outputFile);
                break;

            case 0:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);

    // Закриття файлу після використання
    fclose(outputFile);
}

void addProduct(Store *store, const char *name, double price, int quantity) {
    store->products = realloc(store->products, (store->productCount + 1) * sizeof(Product));
    if (!store->products) {
        perror("Memory allocation failed");
        return;
    }
    strcpy(store->products[store->productCount].name, name);
    store->products[store->productCount].price = price;
    store->products[store->productCount].quantity = quantity;
    store->products[store->productCount].discount = 0.0; // За замовчуванням знижка відсутня
    store->productCount++;
}

// Оновлення продукту
void updateProduct(Store *store, const char *name, double price, int quantity) {
    for (int i = 0; i < store->productCount; i++) {
        if (strcmp(store->products[i].name, name) == 0) {
            store->products[i].price = price;
            store->products[i].quantity = quantity;
            return;
        }
    }
    printf("Product not found: %s\n", name);
}

// Видалення продукту
void removeProduct(Store *store, const char *name) {
    for (int i = 0; i < store->productCount; i++) {
        if (strcmp(store->products[i].name, name) == 0) {
            for (int j = i; j < store->productCount - 1; j++) {
                store->products[j] = store->products[j + 1];
            }
            store->productCount--;
            store->products = realloc(store->products, store->productCount * sizeof(Product));
            if (!store->products && store->productCount > 0) {
                perror("Memory allocation failed");
            }
            return;
        }
    }
    printf("Product not found: %s\n", name);
}

// Відображення продуктів
void displayProducts(const Store *store, FILE *outputFile) {
    if (store->productCount == 0) {
        fprintf(outputFile, "No products in store.\n");
        return;
    }
    fprintf(outputFile, "Products in store:\n");
    for (int i = 0; i < store->productCount; i++) {
        fprintf(outputFile, "Name: %s, Price: %.2f, Quantity: %d, Discount: %.2f%%\n",
                store->products[i].name,
                store->products[i].price,
                store->products[i].quantity,
                store->products[i].discount);
    }
}

// Додавання працівника
void addEmployee(Store *store, const char *name, double salary, const char *role) {
    store->employees = realloc(store->employees, (store->employeeCount + 1) * sizeof(Employee));
    if (!store->employees) {
        perror("Memory allocation failed");
        return;
    }
    strcpy(store->employees[store->employeeCount].name, name);
    store->employees[store->employeeCount].salary = salary;
    strcpy(store->employees[store->employeeCount].role, role);
    store->employees[store->employeeCount].totalSales = 0.0;
    store->employeeCount++;
}

// Оновлення працівника
void updateEmployee(Store *store, const char *name, double newSalary) {
    for (int i = 0; i < store->employeeCount; i++) {
        if (strcmp(store->employees[i].name, name) == 0) {
            store->employees[i].salary = newSalary;
            return;
        }
    }
    printf("Employee not found: %s\n", name);
}

// Видалення працівника
void removeEmployee(Store *store, const char *name) {
    for (int i = 0; i < store->employeeCount; i++) {
        if (strcmp(store->employees[i].name, name) == 0) {
            for (int j = i; j < store->employeeCount - 1; j++) {
                store->employees[j] = store->employees[j + 1];
            }
            store->employeeCount--;
            store->employees = realloc(store->employees, store->employeeCount * sizeof(Employee));
            if (!store->employees && store->employeeCount > 0) {
                perror("Memory allocation failed");
            }
            return;
        }
    }
    printf("Employee not found: %s\n", name);
}

// Відображення працівників
void displayEmployees(const Store *store, FILE *outputFile) {
    if (store->employeeCount == 0) {
        fprintf(outputFile, "No employees in store.\n");
        return;
    }
    fprintf(outputFile, "Employees in store:\n");
    for (int i = 0; i < store->employeeCount; i++) {
        fprintf(outputFile, "Name: %s, Salary: %.2f, Role: %s, Total Sales: %.2f\n",
                store->employees[i].name,
                store->employees[i].salary,
                store->employees[i].role,
                store->employees[i].totalSales);
    }
}

// Розрахунок зарплати працівників
void calculateEmployeeSalary(Store *store) {
    for (int i = 0; i < store->employeeCount; i++) {
        store->employees[i].salary += store->employees[i].totalSales * 0.1; // 10% від продажів
    }
}

// Продаж продукту
void sellProduct(Store *store, const char *productName, int quantity, const char *employeeName) {
    for (int i = 0; i < store->productCount; i++) {
        if (strcmp(store->products[i].name, productName) == 0) {
            if (store->products[i].quantity >= quantity) {
                double totalSale = quantity * store->products[i].price;

                // Застосування знижки, якщо вона є
                if (store->products[i].discount > 0) {
                    totalSale *= (1 - store->products[i].discount / 100);
                }

                store->products[i].quantity -= quantity;
                store->totalProfit += totalSale;

                // Оновлення продажів працівника
                for (int j = 0; j < store->employeeCount; j++) {
                    if (strcmp(store->employees[j].name, employeeName) == 0) {
                        store->employees[j].totalSales += totalSale;
                        printf("Employee %s made a sale of %.2f\n", employeeName, totalSale);

                        // Перевірка на закінчення товару
                        if (store->products[i].quantity == 0) {
                            printf("Product %s is out of stock. Please restock!\n", productName);
                        }
                        return;
                    }
                }

                printf("Employee %s not found.\n", employeeName);
                return;
            } else {
                printf("Not enough stock for product: %s\n", productName);
                return;
            }
        }
    }
    printf("Product not found: %s\n", productName);
}


void saveToFile(const Store *store, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file for writing");
        return;
    }
    fwrite(&store->productCount, sizeof(int), 1, file);
    fwrite(store->products, sizeof(Product), store->productCount, file);

    fwrite(&store->employeeCount, sizeof(int), 1, file);
    fwrite(store->employees, sizeof(Employee), store->employeeCount, file);

    fwrite(&store->totalProfit, sizeof(double), 1, file);
    fclose(file);
}


// Завантаження даних із файлу
void loadFromFile(Store *store, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file for reading");
        return;
    }
    fread(&store->productCount, sizeof(int), 1, file);
    store->products = malloc(store->productCount * sizeof(Product));
    fread(store->products, sizeof(Product), store->productCount, file);

    fread(&store->employeeCount, sizeof(int), 1, file);
    store->employees = malloc(store->employeeCount * sizeof(Employee));
    fread(store->employees, sizeof(Employee), store->employeeCount, file);

    fread(&store->totalProfit, sizeof(double), 1, file);
    fclose(file);
}

void restockProduct(Store *store, const char *productName, int quantity) {
    for (int i = 0; i < store->productCount; i++) {
        if (strcmp(store->products[i].name, productName) == 0) {
            store->products[i].quantity += quantity;
            return;
        }
    }
    printf("Product not found: %s\n", productName);
}
void autoRestock(Store *store, int restockQuantity) {
    printf("Automatically restocking out-of-stock products...\n");
    int restockedCount = 0;

    for (int i = 0; i < store->productCount; i++) {
        if (store->products[i].quantity == 0) {
            store->products[i].quantity += restockQuantity;
            printf("Restocked product: %s, Quantity added: %d\n", store->products[i].name, restockQuantity);
            restockedCount++;
        }
    }

    if (restockedCount == 0) {
        printf("No products needed restocking.\n");
    }
}

// Відображення прибутку
void displayProfit(const Store *store) {
    printf("Total profit: %.2f\n", store->totalProfit);
}

//Встановлення знижки
void setDiscount(Store* store, const char* productName, float discountPercentage) {
    if (discountPercentage < 0.0 || discountPercentage > 100.0) {
        printf("Invalid discount percentage. Must be between 0 and 100.\n");
        return;
    }

    for (int i = 0; i < store->productCount; i++) {
        if (strcmp(store->products[i].name, productName) == 0) {
            store->products[i].discount = discountPercentage;
            store->products[i].price *= (1 - discountPercentage / 100.0);
            printf("Discount of %.2f%% set for product: %s\n", discountPercentage, productName);
            return;
        }
    }
    printf("Product '%s' not found in store.\n", productName);
}

//Перевірка наявності продуктів
void displayOutOfStock(const Store *store) {
    int outOfStockCount = 0;
    printf("Out of stock products:\n");
    for (int i = 0; i < store->productCount; i++) {
        if (store->products[i].quantity == 0) {
            printf("- %s\n", store->products[i].name);
            outOfStockCount++;
        }
    }
    if (outOfStockCount == 0) {
        printf("No products are out of stock.\n");
    }
}