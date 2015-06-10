#include "tier.h"
#include "vogel.h"
#include "fisch.h"

int main(int argc, char **argv) {
    CTier *currentanimal = new CFisch("Fisch");
    currentanimal->KannEtwas();
    ((CVogel *)currentanimal)->KannEtwas();
    delete currentanimal;
    currentanimal = new CVogel("Vogel");
    currentanimal->KannEtwas();
    ((CFisch *)currentanimal)->KannEtwas();
    delete currentanimal;
    return 0;
}