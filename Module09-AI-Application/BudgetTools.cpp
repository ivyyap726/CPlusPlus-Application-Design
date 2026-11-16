#include "BudgetTools.h"

double calculateTotal(double amounts[], int size) {
      double total = 0;
    for (int i = 0; i < size; i++) {
        total += amounts[i];
    }
    return total;
}
