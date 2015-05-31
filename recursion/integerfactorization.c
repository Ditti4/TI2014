#include <stdio.h>
#include <stdlib.h>

void print_fact(int input) {
    int i;
    // Schleife beginnt bei 2 - 1 ist automatisch durch den kleinen Hack in main() abgedeckt
    // Ende der Schleife bei der Eingabezahl an sich - ist diese erreicht, hat die Eingabezahl nur sich selbst und 1 als Primfaktoren
    for(i = 2; i <= input; i++) {
        // Input restlos durch i teilbar? Wenn ja, ist i ein Primfaktor von input
        // Notiz am Rande: i muss ein Primfaktor sein, ganz einfach aus dem Grund, dass wir "unten" anfange und
        // uns dann durcharbeiten - wir arbeiten also erst alle Primzahlen und dann ihre Vielfache ab
        // -> ist input nicht durch 2 teilbar, ist es auch nicht durch 4 oder 8 teilbar
        // -> ist input aber durch 2 teilbar, wäre es eventuell auch durch 4 oder 8 teilbar - eine Annäherung von oben würde hier also möglicherweise 4 oder 8 als Primfaktoren ausspucken
        if(input % i == 0) {
            printf(" * %d", i);
            // erneuter Aufruf der Funktion (yay, Rekursion) mit der der durch i geteilten Eingabezahl, danach Ende der Schleife dank return
            return print_fact(input / i);
        }
    }
}

int main(int argc, char **argv) {
    if(argc <= 1) {
        printf("usage: %s numer_to_process\n", argv[0]);
        return 1;
    }
    // Eingabezahl von der Konsole holen
    int input = atoi(argv[1]);
    int i;
    // Kleiner Hack, damit ich mich nicht großartig um das *-Zeichen kümmern muss
    putchar('1');
    print_fact(input);
    putchar('\n');
    return 0;
}

/*
Kleines Beispiel, wie sich das Programm verhält am Beispiel der Zahl 52 (2*2*13):
1. Einstieg in die Funktion mit der Zahl 52
2. Beginn der Schleife mit 2
3. 52 ist restlos durch 2 teilbar -> 2 ausgeben, mit 52/2, also 26, die Funktion erneut aufrufen
4. Einstieg in die Funktion mit 26
5. Beginn der Schleife mit 2
6. 26 ist restlos durch 2 teilbar -> 2 ausgeben, mit 26/2, also 13, die Funktion erneut aufrufen
7. Einstieg in die Funktion mit 13
8. Beginn der Schleife mit 2, erhöhen der Laufvariable, da 13 nicht durch 2 teilbar ist
9. i = 3 -> 13 ist nicht durch 3 teilbar -> erhöhen von i
10. …
11. i = 13 -> i ist nun genau so groß wie input, wir erreichen also das Ende der Schleife, 13 ist aber auch restlos durch 13 teilbar, also 13 ausgeben und mit 13/13 die Funktion erneut aufrufen
12. Einstieg in die Funktion mit 1
13. Beginn der Schleife mit 2
14. Prüfung im Schleifenkopf (i <= input) schlägt schon vor dem ersten Durchlauf fehl, da 2 nicht kleiner oder gleich 1 ist
15. Ende der Funktion aus 12.
16. Ende der Funktion aus 7.
17. Ende der Funktion aus 4.
18. Ende der Funktion aus 1.
19. Fertsch.
*/
