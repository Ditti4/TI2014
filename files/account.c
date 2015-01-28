#include <stdio.h>
#include <stdlib.h>

int errid = 0;

enum ERROR {
    ERROR_FILE_OPEN = 64,
    ERROR_FILE_READ
};

struct data {
    int id;
    char activename[129];
    char passivename[129];
    int amount;
};

struct datawrapper {
    struct data *data;
    int elements;
};

struct account {
    int key;
    char name[129];
    int hasamount;
    int shouldamount;
};

void print(char *message) {
    int i = 0;
    while(message[i] != '\0')
        putchar(message[i]);
}

void repeatString(char *string, int count) {
    int i;
    for(i = 0; i < count; i++) {
        print(string);
    }
}

void repeatChar(char character, int count) {
    int i;
    for(i = 0; i < count; i++) {
        putchar(character);
    }
}

struct datawrapper *readDataFromFile(char *filename) {
    FILE *fp;
    if(fp = fopen("data", "r")) {
        char line[257];
        int i = 0;
        struct datawrapper *wrapper = malloc(sizeof(struct datawrapper));
        struct data *read = malloc(sizeof(struct data));
        while(fgets(line, 1024, fp)) {
            i++;
            read = realloc(read, i * sizeof(struct data));
            sscanf(line, "%d %s %s %d", &read[i - 1].id, read[i - 1].activename, read[i - 1].passivename, &read[i - 1].amount);
        }
        if(i == 0) {
            errid = ERROR_FILE_READ;
            return NULL;
        }
        wrapper->elements = i;
        wrapper->data = read;
        return wrapper;
    } else {
        errid = ERROR_FILE_OPEN;
        return NULL;
    }
}

int main() {
    struct datawrapper *wrapper;
    if(wrapper = readDataFromFile("data")) {
        int i;
        struct data *data = wrapper->data;
        for(i = 0; i < wrapper->elements; i++) {
            // Aktiv = Soll
            // Passiv = Haben
            printf("Aktivname: %s\nPassivname: %s\nID: %d\nGuthaben: %d\n\n", data[i].activename, data[i].passivename, data[i].id, data[i].amount);
            
        }
    } else {
        switch(errid) {
            case ERROR_FILE_OPEN:
                print("Fehler beim Oeffnen der Datei.\n");
                break;
            case ERROR_FILE_READ:
                print("Fehler beim Lesen der Datei.\n");
                break;
            default:
                print("Unbekannter Fehler.\n");
                break;
        }
        printf("");
    }
        
    return 0;
}