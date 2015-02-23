#include <stdio.h>

int isBitSet(int input, int bitpos) {
    return ((input & (1 << bitpos)) ? 1 : 0);
}

int main() {
    int input, position;
    
    printf("Zahl eingeben: ");
    scanf("%d", &input);
    printf("Zu pruefende Stelle angeben (mit 0 beginnend): ");
    scanf("%d", &position);
    printf("%d an Stelle %d gefunden.\n", isBitSet(input, position), position);
}
