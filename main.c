//Андріанова Маргарита Юріївна
//Комп'ютерна математика 2

#include "shop.h"

int main() {
    Store store = {NULL, NULL, 0, 0, 0.0}; // Ініціалізація магазину
    mainMenu(&store);                     // Виклик головного меню
    return 0;
}
