//Андріанова Маргарита Юріївна
//Комп'ютерна математика 2

#ifndef SHOP_H
#define SHOP_H
#include <stdio.h>

// Структура товару
typedef struct {
    char name[50];
    float price;
    int quantity;
    float discountPercentage;
} Product;


// Структура працівника
typedef struct {
    char name[50];
    double salary;
    char role[20];
    double totalSales; // Загальний обсяг продажів працівника
} Employee;

// Структура магазину
typedef struct {
    Product *products;
    int productCount;

    Employee *employees;
    int employeeCount;

    double totalProfit;
} Store;


// Функції для роботи з продуктами
void addProduct(Store *store, const char *name, double price, int quantity);
void updateProduct(Store *store, const char *name, double price, int quantity);
void removeProduct(Store *store, const char *name);
void displayProducts(const Store *store, FILE *outputFile);


// Функції для роботи з працівниками
void addEmployee(Store *store, const char *name, double salary, const char *role);
void updateEmployee(Store *store, const char *name, double newSalary);
void removeEmployee(Store *store, const char *name);
void displayEmployees(const Store *store, FILE *outputFile);
void calculateEmployeeSalary(Store *store);

// Функції для продажів і прибутку
void sellProduct(Store *store, const char *productName, int quantity, const char *employeeName);
void restockProduct(Store *store, const char *productName, int quantity);
void autoRestock(Store *store, int restockQuantity);
void displayProfit(const Store *store);
void displayOutOfStock(const Store *store);


// Функції для роботи з файлами
void saveToFile(const Store *store, const char *filename);
void loadFromFile(Store *store, const char *filename);

void setDiscount(Store *store, const char *productName, float discountPercentage);
void mainMenu(Store *store);

#endif