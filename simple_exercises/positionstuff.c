#include <stdio.h>

typedef struct {
	int posx;
	int posy;
	int sizex;
	int sizey;
} square_t;

int is_pos_on_square_edge(int posx, int posy, square_t square) {
	if(posx < square.posx || posx > (square.posx + square.sizex) || posy < square.posy || posy > (square.posy + square.sizey)) {
		return 0;
	} else if((posx == square.posx || posx == (square.posx + square.sizex)) && (posy >= square.posy && posy <= (square.posy + square.sizey))) {
		return 1;
	} else if((posy == square.posy || posy == (square.posy + square.sizey)) && (posx >= square.posx && posx <= (square.posx + square.sizex))) {
		return 1;
	} else {
		return 0;
	}
}

int main(int argc, char **argv) {
	square_t square;
	square.posx = 10;
	square.posy = 15; // ignored when drawn because it wastes space
	square.sizex = 30;
	square.sizey = 40;

	int i, j;
	for(i = square.posy; i <= (square.posy + square.sizey); i++) {
		for(j = square.posx; j <= (square.posx + square.sizex); j++) {
			if(i == square.posy || i == (square.posy + square.sizey)) {
				putchar('#');
			} else if(j == square.posx || j == (square.posx + square.sizex)) {
				putchar('#');
			} else {
				putchar(' ');
			}
		}
		putchar('\n');
	}

	printf("Top left corner: (%d|%d)\n", square.posx, square.posy);
	printf("Top right corner: (%d|%d)\n", square.posx + square.sizex, square.posy);
	printf("Bottom left corner: (%d|%d)\n", square.posx, square.posy + square.sizey);
	printf("Bottom right corner: (%d|%d)\n", square.posx + square.sizex, square.posy + square.sizey);

	printf("Click on 10|10 (outside of the square) returns %d\n", is_pos_on_square_edge(10, 10, square)); // out of square
	printf("Click on 10|15 (top left corner) returns %d\n", is_pos_on_square_edge(10, 15, square)); // top left corner
	printf("Click on 20|20 (inside of the square) returns %d\n", is_pos_on_square_edge(20, 20, square)); // somewhere inside of the square
	printf("Click on 40|30 (right edge) returns %d\n", is_pos_on_square_edge(40, 30, square)); // somewhere on the right edge

	return 0;
}
