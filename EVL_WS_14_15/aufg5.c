#include <stdio.h>

int main() {
	int input, position;
	
	printf("Zahl eingeben: ");
	scanf("%d", &input);
	printf("Zu pruefende Stelle angeben (mit 0 beginnend): ");
	scanf("%d", &position);
	
	if(input & (1 << position))
		printf("1 an Stelle %d gefunden.\n", position);
	else
		printf("0 an Stelle %d gefunden.\n", position);
}
