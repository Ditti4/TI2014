#include <stdio.h>
#include <stdlib.h>

#define print(__string) for(__i=0; __string[__i] != '\0'; __i++) putchar(__string[__i]);
int __i;

struct person {
	char name[20];
	int age;
	int id;
};

void writetofile(struct person people) {
	FILE *fp;
	fopen_s(&fp, "test.txt", "w+");
	fprintf(fp, "%s %d %d\n", people.name, people.age, people.id);
	fclose(fp);
}

struct person* getfromfile() {
	FILE *fp;
	struct person *people = malloc(sizeof(struct person));
	if (fopen_s(&fp, "test.txt", "r")) return NULL;
	fscanf_s(fp, "%s %d %d", people->name, 20, people->age, people->id);
	fclose(fp);
	return people;
}

int main() {
	char next;
	struct person people;
	struct person *pp = &people;
	do {
		print("(w)rite to file, (g)et from file: ");
		fflush(stdin);
		next = getchar();
		switch (next) {
		case 'W':
			next = 'w';
		case 'w':
			print("Name: ");
			scanf("%s", people.name, 20);
			print("Alter: ");
			scanf("%d", &(people.age));
			print("Matrikelnummer: ");
			scanf("%d", &(people.id));
			writetofile(people);
			break;
		case 'G':
			next = 'g';
		case 'g':
			pp = getfromfile();
			if (pp) {
				printf("Name: %s\nAlter: %d\nMatrikelnummer: %d\n", people.name, people.age, people.id);
			}
			else
				print("Fehler beim Oeffnen der Datei.\n");
			break;
		}
	} while (next == 'w' || next == 'g');


	return 0;
}
