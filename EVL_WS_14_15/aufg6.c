#include <stdio.h>

double volumeBall(double r) {
    return ((4.0/3.0)*3.14159265359*r*r*r);
}

double volumeCuboid(double a, double b, double c) {
    return (a*b*c);
}

double volumePyramid(double a, double b, double height) {
    return ((1.0/3.0)*a*b*height);
}

int main() {
    double data[3];
    char menu;

    printf("Volumen einer (K)ugel, eines (Q)uaders, einer (P)yramide berechnen: ");
    menu = getchar();
    fflush(stdin);

    switch(menu) {
        case 'K':
        case 'k':
            printf("Radius angeben: ");
            scanf("%lf", &data[0]);
            printf("Volumen der Kugel: %f\n", volumeBall(data[0]));
            break;
        case 'Q':
        case 'q':
            printf("a, b, c angeben: ");
            scanf("%lf%lf%lf", &data[0], &data[1], &data[2]);
            printf("Volumen des Quaders: %f\n", volumeCuboid(data[0], data[1], data[2]));
            break;
        case 'P':
        case 'p':
            printf("a, b angeben: ");
            scanf("%lf%lf", &data[0], &data[1]);
            printf("Hoehe angeben: ");
            scanf("%lf", &data[2]);
            printf("Volumen der Pyramide: %f\n", volumePyramid(data[0], data[1], data[2]));
            break;
    }
}
