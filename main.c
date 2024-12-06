#include "shop.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Store store = {NULL, 0, NULL, 0, 0.0};
    mainMenu(&store);

    // Очищення пам'яті
    free(store.products);
    free(store.employees);

    return 0;
}
