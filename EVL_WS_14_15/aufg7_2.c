#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../errors.h"
#include "../result.h"

// global struct definitions

// global typedefs for struct

typedef struct __album album_t;
typedef struct __artist artist_t;

// global typedefs for struct end

struct __album {
    char name[100];
    artist_t *artist;
    album_t *next;
};

struct __artist {
    char name[100];
    album_t *albumtree;
    artist_t *next;
};

// global struct definitions end

// global enum definitions

enum EXTRA_ERRORS {
    ERROR_EMPTY_HEAD = -128,
    ERROR_ARTIST_NOT_FOUND,
    ERROR_ALBUM_NOT_FOUND,
};

// global enum definitions end

// global variable definitions

artist_t *HEAD = NULL;

// global variable definitions end

// global function definitions

// global function prototypes

result *add_artist(char *name);
int remove_artist(char *name);
result *find_artist(char *name);
result *add_album(char *name, char *artist);
int remove_album(char *name);
result *find_album(char *name);

// global function prototypes end

result *add_artist(char *name) {
    if(!name || !strlen(name)) {
        RETURN_ERROR(ERROR_EMPTY_STRING);
    }
    artist_t *new_artist = NULL;
    if(!(new_artist = malloc(sizeof(artist_t)))) {
        RETURN_ERROR(ERROR_MEM_MALLOC);
    }
    strcpy(new_artist->name, name);
    new_artist->next = HEAD;
    new_artist->albumtree = NULL;
    HEAD = new_artist;
    RETURN_RESULT(new_artist);
}

int remove_artist(char *name) {
    if(!name || !strlen(name)) {
        return ERROR_EMPTY_STRING;
    }
    if(!HEAD) {
        return ERROR_EMPTY_HEAD;
    }
    artist_t *current_artist = HEAD;
    artist_t *next_artist = current_artist->next;
    album_t *current_album = NULL;
    album_t *next_album = NULL;
    if(strcmp(HEAD->name, name) == 0) {
        HEAD = next_artist;
        current_album = current_artist->albumtree;
        while(current_album) {
            next_album = current_album->next;
            free(current_album);
            current_album = next_album;
        }
        free(current_artist);
        return ERROR_NONE;
    } else {
        while(current_artist && next_artist) {
            if(strcmp(next_artist->name, name) == 0) {
                current_artist->next = next_artist->next;
                current_album = next_artist->albumtree;
                while(current_album) {
                    next_album = current_album->next;
                    free(current_album);
                    current_album = next_album;
                }
                free(next_artist);
                return ERROR_NONE;
            }
            current_artist = next_artist;
            next_artist = next_artist->next;
        }
    }
    return ERROR_ARTIST_NOT_FOUND;
}

result *find_artist(char *name) {
    if(!name || !strlen(name)) {
        RETURN_ERROR(ERROR_EMPTY_STRING);
    }
    if(!HEAD) {
        RETURN_ERROR(ERROR_EMPTY_HEAD);
    }
    artist_t *current_artist = HEAD;
    while(current_artist) {
        if(strcmp(current_artist->name, name) == 0) {
            RETURN_RESULT(current_artist);
        }
        current_artist = current_artist->next;
    }
    RETURN_ERROR(ERROR_ARTIST_NOT_FOUND);
}

result *add_album(char *name, char *artist) {
    if(!name || !artist || !strlen(name) || !strlen(artist)) {
        RETURN_ERROR(ERROR_EMPTY_STRING);
    }
    if(!HEAD) {
        RETURN_ERROR(ERROR_EMPTY_HEAD);
    }
    artist_t *current_artist = NULL;
    album_t *new_album = NULL;
    if(!(new_album = malloc(sizeof(album_t)))) {
        RETURN_ERROR(ERROR_MEM_MALLOC);
    }
    result *artist_result = find_artist(artist);
    if(artist_result->errid) {
        RETURN_ERROR(artist_result->errid);
    }
    current_artist = artist_result->result;
    strcpy(new_album->name, name);
    new_album->artist = current_artist;
    new_album->next = current_artist->albumtree;
    current_artist->albumtree = new_album;
    RETURN_RESULT(new_album);
}

int remove_album(char *name) {
    if(!name || !strlen(name)) {
        return ERROR_EMPTY_STRING;
    }
    if(!HEAD) {
        return ERROR_EMPTY_HEAD;
    }
    artist_t *current_artist = HEAD;
    album_t *current_album;
    album_t *next_album;
    while(current_artist) {
        current_album = current_artist->albumtree;
        next_album = current_album->next;
        if(strcmp(current_artist->albumtree->name, name) == 0) {
            current_artist->albumtree = current_album->next;
            free(current_album);
            return ERROR_NONE;
        }
        while(next_album) {
            if(strcmp(next_album->name, name) == 0) {
                current_album->next = next_album->next;
                free(next_album);
                return ERROR_NONE;
            }
            current_album = next_album;
            next_album = next_album->next;
        }
        current_artist = current_artist->next;
    }
    return ERROR_ALBUM_NOT_FOUND;
}

result *find_album(char *name) {
    if(!name || !strlen(name)) {
        RETURN_ERROR(ERROR_EMPTY_STRING);
    }
    if(!HEAD) {
        RETURN_ERROR(ERROR_EMPTY_HEAD);
    }
    artist_t *current_artist = HEAD;
    album_t *current_album = current_artist->albumtree;
    while(current_artist) {
        current_album = current_artist->albumtree;
        while(current_album) {
            if(strcmp(current_album->name, name) == 0) {
                RETURN_RESULT(current_album);
            }
            current_album = current_album->next;
        }
        current_artist = current_artist->next;
    }
    RETURN_ERROR(ERROR_ALBUM_NOT_FOUND);
}

// global function definitions end

// main method

int main(int argc, char **argv) {
    char menu, artist_name[100], album_name[100];
    result *resultpointer;
    artist_t *artist;
    album_t *album;
    int errid;
    
    do {
        printf("Interpret/Album (h)inzufuegen, (a)nzeigen, (e)ntfernen, (g)esamte Sammlung ausgeben, andere Taste zum Beenden: ");
        scanf(" %c", &menu);
        switch(menu) {
            case 'H':
            case 'h':
                printf("(I)nterpret/(A)lbum hinzufuegen: ");
                scanf(" %c", &menu);
                switch(menu) {
                    case 'I':
                    case 'i':
                        printf("Name des Interpreten angeben: ");
                        scanf(" %99[^\n]s", artist_name);
                        resultpointer = add_artist(artist_name);
                        if(resultpointer->errid) {
                            printf("Fehler beim Hinzufuegen des Interpreten. (Fehlercode %d)\n", resultpointer->errid);
                        } else {
                            artist = resultpointer->result;
                            printf("Interpret \"%s\" erfolgreich hinzugefuegt.\n", artist->name);
                        }
                        break;
                    case 'A':
                    case 'a':
                        printf("Name des Albums angeben: ");
                        scanf(" %99[^\n]s", album_name);
                        printf("Name des Interpreten angeben: ");
                        scanf(" %99[^\n]s", artist_name);
                        resultpointer = add_album(album_name, artist_name);
                        if(resultpointer->errid) {
                            printf("Fehler beim Hinzufuegen des Albums. (Fehlercode %d)\n", resultpointer->errid);
                        } else {
                            album = resultpointer->result;
                            printf("Album \"%s\" erfolgreich hinzugefuegt.\n", album->name);
                        }
                        break;
                }
                menu = 'h';
                break;
            case 'A':
            case 'a':
                printf("(I)nterpret/(A)lbum anzeigen: ");
                scanf(" %c", &menu);
                switch(menu) {
                    case 'I':
                    case 'i':
                        printf("Name des Interpreten angeben: ");
                        scanf(" %99[^\n]s", artist_name);
                        resultpointer = find_artist(artist_name);
                        if(resultpointer->errid) {
                            printf("Fehler beim Suchen des Interpreten. (Fehlercode %d)\n", resultpointer->errid);
                        } else {
                            artist = resultpointer->result;
                            printf("Interpret: \"%s\", Alben: \n", artist->name);
                            album = artist->albumtree;
                            while(album) {
                                printf("\t%s\n", album->name);
                                album = album->next;
                            }
                        }
                        break;
                    case 'A':
                    case 'a':
                        printf("Name des Albums angeben: ");
                        scanf(" %99[^\n]s", album_name);
                        resultpointer = find_album(album_name);
                        if(resultpointer->errid) {
                            printf("Fehler beim Suchen des Albums. (Fehlercode %d)\n", resultpointer->errid);
                        } else {
                            album = resultpointer->result;
                            artist = album->artist;
                            printf("Album: \"%s\" von \"%s\".\n", album->name, artist->name);
                        }
                        break;
                }
                menu = 'a';
                break;
            case 'G':
            case 'g':
                artist = HEAD;
                if(!HEAD) {
                    printf("Sammlung ist leer.\n");
                    break;
                }
                while(artist) {
                    printf("Interpret: \"%s\", Alben: \n", artist->name);
                    album = artist->albumtree;
                    while(album) {
                        printf("\t%s\n", album->name);
                        album = album->next;
                    }
                    artist = artist->next;
                }
                break;
            case 'E':
            case 'e':
                printf("(I)nterpret/(A)lbum anzeigen: ");
                scanf(" %c", &menu);
                switch(menu) {
                    case 'I':
                    case 'i':
                        printf("Name des Interpreten angeben: ");
                        scanf(" %99[^\n]s", artist_name);
                        errid = remove_artist(artist_name);
                        if(errid) {
                            printf("Fehler beim Entfernen des Interpreten. (Fehlercode %d)\n", errid);
                        } else {
                            printf("Interpret \"%s\" erfolgreich entfernt.\n", artist_name);
                        }
                        break;
                    case 'A':
                    case 'a':
                        printf("Name des Albums angeben: ");
                        scanf(" %99[^\n]s", album_name);
                        errid = remove_album(album_name);
                        if(errid) {
                            printf("Fehler beim Entfernen des Albums. (Fehlercode %d)\n", errid);
                        } else {
                            printf("Album \"%s\" erfolgreich entfernt.\n", album_name);
                        }
                        break;
                }
                menu = 'e';
                break;
            default:
                artist = HEAD;
                while(artist) {
                    album = artist->albumtree;
                    while(album) {
                        artist->albumtree = album->next;
                        free(album);
                        album = artist->albumtree;
                    }
                    HEAD = artist->next;
                    free(artist);
                    artist = HEAD;
                }
                break;
        }
    } while(menu == 'H' || menu == 'h' || menu == 'A' || menu == 'a' || menu == 'E' || menu == 'e' || menu == 'G' || menu == 'g');
    
    return 0;
}

// main method end
