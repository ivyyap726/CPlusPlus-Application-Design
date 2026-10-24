#include "BudgetTools.h"

double calculateTotal(double amounts[], int count) {
    double total = 0;
    for (int i = 0; i < count; i++) {
        total += amounts[i];
    }
    return total;
}
