//Андріанова Маргарита Юріївна
//Комп'ютерна математика 2

#include "shop.h"

/*
 * main.c
 *
 * Основний файл програми.
 * Забезпечує взаємодію з користувачем через головне меню.
 * Викликає функції модуля "shop" для обробки даних магазину.
 */

int main() {
    Store store = {NULL, NULL, 0, 0, 0.0}; // Ініціалізація магазину
    mainMenu(&store);                     // Виклик головного меню
    return 0;
}
