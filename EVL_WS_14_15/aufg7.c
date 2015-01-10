#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addArtist(int key, char *name);
void addAlbum(int key, char *name, int artistKey, int *titleKeys, char (*titleNames)[50], int titleCount);
struct artist * getArtist(int key);
struct album * getAlbum(int key);
struct artist * getArtistByAlbumKey(int key);
int removeArtist(int key);
int removeAlbum(int key);
struct artist * findArtist(char *name);
struct album * findAlbum(char *name);

struct title {
    int key;
    char name[50];
    struct title *next;
};

struct album {
    int key;
    char name[50];
    struct title *titles;
    struct album *next;
};

struct artist {
    int key;
    char name[50];
    struct album *albums;
    struct artist *next;
};

struct artist *head;

void addArtist(int key, char *name) {
    struct artist *tmp;
    tmp = malloc(sizeof(struct artist));
    tmp->key = key;
    strcpy(tmp->name, name);
    tmp->albums = NULL;
    tmp->next = head;
    head = tmp;
}

void addAlbum(int key, char *name, int artistKey, int *titleKeys, char (*titleNames)[50], int titleCount) {
    struct album *tmpAlbum;
    struct title *tmpTitle;
    struct artist *tmpArtist;
    int i;
    
    tmpArtist = getArtist(artistKey);
    if(!tmpArtist) {
        printf("Artist nicht gefunden. Hinzufuegen wurde abgebrochen.");
        return;
    }
    
    tmpAlbum = malloc(sizeof(struct album));
    tmpAlbum->key = key;
    strcpy(tmpAlbum->name, name);
    tmpAlbum->next = tmpArtist->albums;
    tmpArtist->albums = tmpAlbum;
    
    for(i = 0; i < titleCount; i++) {
        tmpTitle = malloc(sizeof(struct title));
        if(!i)
            tmpTitle->next = NULL;
        else
            tmpTitle->next = tmpAlbum->titles;
        tmpTitle->key = titleKeys[i];
        strcpy(tmpTitle->name, titleNames[i]);
        tmpAlbum->titles = tmpTitle;
    }
}

struct artist * getArtist(int key) {
    if(head == NULL)
        return NULL;
    struct artist *tmpArtist = head;
    while(tmpArtist != NULL) {
        if(tmpArtist->key == key)
            break;
        else
            tmpArtist = tmpArtist->next;
    }
    return tmpArtist;
}

struct album * getAlbum(int key) {
    if(head == NULL)
        return NULL;
    struct artist *tmpArtist = head;
    if(tmpArtist->albums == NULL)
        return NULL;
    struct album *tmpAlbum;
    while(tmpArtist != NULL) {
        tmpAlbum = tmpArtist->albums;
        while(tmpAlbum != NULL) {
            if(tmpAlbum->key == key)
                break;
            else
                tmpAlbum = tmpAlbum->next;
        }
        if(tmpAlbum != NULL)
            break;
        else
            tmpArtist = tmpArtist->next;
    }
    return tmpAlbum;
}

struct artist * getArtistByAlbumKey(int key) {
    if(head == NULL)
        return NULL;
    struct artist *tmpArtist = head;
    if(tmpArtist->albums == NULL)
        return NULL;
    struct album *tmpAlbum = tmpArtist->albums;
    while(tmpArtist != NULL) {
        while(tmpAlbum != NULL) {
            if(tmpAlbum->key == key)
                break;
            else
                tmpAlbum = tmpAlbum->next;
        }
        if(tmpAlbum != NULL)
            break;
        else
            tmpArtist = tmpArtist->next;
    }
    if(tmpAlbum->key == key)
        return tmpArtist;
    else
        return NULL;
}

int removeArtist(int key) {
    if(head == NULL)
        return 1;
    struct artist *tmpArtist = head, *tmpNext;
    if(tmpArtist->key == key) {
        head = tmpArtist->next;
        free(tmpArtist);
        return 0;
    }
    while(tmpArtist->next != NULL) {
        if(tmpArtist->next->key == key) {
            tmpNext = tmpArtist->next;
            tmpArtist->next = tmpArtist->next->next;
            free(tmpNext);
            return 0;
        } else
            tmpArtist = tmpArtist->next;
    }
    return 2;
}

int removeAlbum(int key) {
    struct artist *tmpArtist = getArtistByAlbumKey(key);
    if(tmpArtist == NULL)
        return 1;
    struct album *tmpAlbum, *tmpNext;
    if((tmpAlbum = tmpArtist->albums)) {
        if(tmpAlbum->key == key) {
            tmpNext = tmpArtist->albums;
            tmpArtist->albums = tmpAlbum->next;
            free(tmpNext);
            return 0;
        }
        while(tmpAlbum->next != NULL) {
            if(tmpAlbum->next->key == key) {
                tmpNext = tmpAlbum->next;
                tmpAlbum->next = tmpAlbum->next->next;
                free(tmpNext);
                return 0;
            }
        }
        return 42;
    } else
        return 42;
}

struct artist * findArtist(char *name) {
    if(head == NULL)
        return NULL;
    struct artist *tmpArtist = head;
    while(tmpArtist != NULL) {
        if(strstr(tmpArtist->name, name))
            break;
        else
            tmpArtist = tmpArtist->next;
    }
    return tmpArtist;
}

struct album * findAlbum(char *name) {
    if(head == NULL)
        return NULL;
    struct artist *tmpArtist = head;
    if(tmpArtist->albums == NULL)
        return NULL;
    struct album *tmpAlbum;
    while(tmpArtist != NULL) {
        tmpAlbum = tmpArtist->albums;
        while(tmpAlbum != NULL) {
            if(strstr(tmpAlbum->name, name))
                break;
            else
                tmpAlbum = tmpAlbum->next;
        }
        if(tmpAlbum != NULL)
            break;
        else
            tmpArtist = tmpArtist->next;
    }
    if(strstr(tmpAlbum->name, name))
        return tmpAlbum;
    else
        return NULL;
}

int main() {
    char menu;
    char artistName[50], albumName[50], titleNames[50][50];
    int artistKey, albumKey;
    int i, titleKeys[50];
    struct artist *tmpArtist, *tmpArtistFree;
    struct album *tmpAlbum, *tmpAlbumFree;
    struct title *tmpTitle, *tmpTitleFree;
    
    head = NULL;
    
    do {
        printf("Interpret/Album (h)inzufuegen, (a)nzeigen (mittels Key), (e)ntfernen, (s)uchen (mittels Name), (I)nfo, # zum Beenden: ");
        scanf(" %c", &menu);
        
        switch(menu) {
            case 'H':
            case 'h':
                printf("(I)nterpret, (A)lbum hinzufuegen, jedes andere Zeichen, um zum Hauptmenue zurueckzukehren: ");
                scanf(" %c", &menu);
                if(menu == 'I' || menu == 'i') {
                    printf("Interpreten-Key angeben: ");
                    scanf("%d", &artistKey);
                    printf("Interpreten-Name angeben (maximal 50 Zeichen): ");
                    scanf(" %50[^\n]s", artistName);
                    addArtist(artistKey, artistName);
                } else if(menu == 'A' || menu == 'a') {
                    printf("Album-Key angeben: ");
                    scanf("%d", &albumKey);
                    printf("Album-Name angeben (maximal 50 Zeichen): ");
                    scanf(" %50[^\n]s", albumName);
                    printf("Interpreten-Key angeben: ");
                    scanf("%d", &artistKey);
                    i = 0;
                    do {
                        printf("Titelnummer angeben (0 zum fertigstellen): ");
                        scanf("%d", &titleKeys[i]);
                        if(!titleKeys[i]) {
                            i--;
                            break;
                        }
                        printf("Titelname angeben (maximal 50 Zeichen): ");
                        scanf(" %50[^\n]s", titleNames[i]);
                        i++;
                    } while(i && i < 50);
                    addAlbum(albumKey, albumName, artistKey, titleKeys, titleNames, i+1);
                }
                break;
            case 'A':
            case 'a':
                printf("(I)nterpret, (A)lbum anzeigen, jedes andere Zeichen, um zum Hauptmenue zurueckzukehren: ");
                scanf(" %c", &menu);
                if(menu == 'I' || menu == 'i') {
                    printf("Interpreten-Key angeben: ");
                    scanf("%d", &artistKey);
                    if((tmpArtist = getArtist(artistKey))) {
                        printf("Infos zum Interpreten:\nKey:\t\t%d\nName:\t\t%s\nalbums:\n", tmpArtist->key, tmpArtist->name);
                        if(!tmpArtist->albums)
                            printf("\t\tKeine.");
                        else {
                            tmpAlbum = tmpArtist->albums;
                            while(tmpAlbum != NULL) {
                                printf("\t%d\t%s\n", tmpAlbum->key, tmpAlbum->name);
                                tmpAlbum = tmpAlbum->next;
                            }
                        }
                    } else {
                        printf("Kein Artist mit dieser ID gefunden. Schon mal die Suche verwendet? Vielleicht hilft die weiter.\n");
                    }
                } else if(menu == 'A' || menu == 'a') {
                    printf("Album-Key angeben: ");
                    scanf("%d", &albumKey);
                    if((tmpAlbum = getAlbum(albumKey))) {
                        tmpArtist = getArtistByAlbumKey(albumKey);
                        printf("Infos zum Album:\nKey:\t\t%d\nName:\t\t%s\nArtist:\t%s\nTitel:\n", tmpAlbum->key, tmpAlbum->name, ((tmpArtist->name) ? tmpArtist->name : "Keiner (wat?)"));
                        if(!tmpAlbum->titles)
                            printf("\t\tKeine.");
                        else {
                            tmpTitle = tmpAlbum->titles;
                            while(tmpTitle != NULL) {
                                printf("\t%d\t%s\n", tmpTitle->key, tmpTitle->name);
                                tmpTitle = tmpTitle->next;
                            }
                        }
                    } else {
                        printf("Kein Album mit dieser ID gefunden. Schon mal die Suche verwendet? Vielleicht hilft die weiter.\n");
                    }
                }
                break;
            case 'E':
            case 'e':
                printf("(I)nterpret, (A)lbum entfernen, jedes andere Zeichen, um zum Hauptmenue zurueckzukehren: ");
                scanf(" %c", &menu);
                if(menu == 'I' || menu == 'i') {
                    printf("Interpreten-Key angeben: ");
                    scanf("%d", &artistKey);
                    switch(removeArtist(artistKey)) {
                        case 0:
                            printf("Interpret erfolgreich entfernt.");
                            break;
                        case 1:
                            printf("Kein Interpret vorhanden.");
                            break;
                        case 2:
                            printf("Interpret mit diesem Key nicht gefunden.");
                            break;
                    }
                } else if(menu == 'A' || menu == 'a') {
                    printf("Album-Key angeben: ");
                    scanf("%d", &albumKey);
                    switch(removeAlbum(albumKey)) {
                        case 0:
                            printf("Album erfolgreich entfernt.");
                            break;
                        case 1:
                            printf("Album existiert nicht.");
                            break;
                        case 42:
                            printf("This wasn't supposed to happen.");
                            break;
                    }
                }
                break;
            case 'S':
            case 's':
                printf("(I)nterpret, (A)lbum suchen, jedes andere Zeichen, um zum Hauptmenue zurueckzukehren");
                scanf(" %c", &menu);
                if(menu == 'I' || menu == 'i') {
                    printf("Interpreten-Name angeben (maximal 50 Zeichen): ");
                    scanf(" %50[^\n]s", artistName);
                    if((tmpArtist = getArtist(artistKey))) {
                        printf("Infos zum Interpret:\nKey:\t\t%d\nName:\t\t%s\nalbums:\n", tmpArtist->key, tmpArtist->name);
                        if(!tmpArtist->albums)
                            printf("\t\tKeine.");
                        else {
                            tmpAlbum = tmpArtist->albums;
                            while(tmpAlbum != NULL) {
                                printf("\t%d\t%s\n", tmpAlbum->key, tmpAlbum->name);
                                tmpAlbum = tmpAlbum->next;
                            }
                        }
                    } else {
                        printf("Keinen Interpreten gefunden, der diesen Name hat oder ihn enthaelt. Sicher, dass er in der Datenbank vorhanden ist?\n");
                    }
                } else if(menu == 'A' || menu == 'a') {
                    printf("Album-Name angeben (maximal 50 Zeichen): ");
                    scanf(" %50[^\n]s", albumName);
                    if((tmpAlbum = getAlbum(albumKey))) {
                        tmpArtist = getArtistByAlbumKey(albumKey);
                        printf("Infos zum Album:\nKey:\t\t%d\nName:\t\t%s\nInterpret:\t%s\nTitel:\n", tmpAlbum->key, tmpAlbum->name, ((tmpArtist->name) ? tmpArtist->name : "Keiner (wat?)"));
                        if(!tmpAlbum->titles)
                            printf("\t\tKeine.");
                        else {
                            tmpTitle = tmpAlbum->titles;
                            while(tmpTitle != NULL) {
                                printf("\t%d\t%s\n", tmpTitle->key, tmpTitle->name);
                                tmpTitle = tmpTitle->next;
                            }
                        }
                    } else {
                        printf("Kein Album gefunden, das diesen Name hat oder ihn enthaelt. Sicher, dass es in der Datenbank vorhanden ist?\n");
                    }
                }
                break;
            case 'I':
            case 'i':
                printf("Bevor ein Album hinzugefuegt werden kann, muss erst der Artist angelegt werden. Das Album wird dem Artisten dann mittels seines eindeutigen Key zugewiesen.\n");
                break;
            case '#':
                //TODO: free memory
                tmpArtist = head;
                while(tmpArtist != NULL) {
                    tmpAlbum = tmpArtist->albums;
                    while(tmpAlbum != NULL) {
                        tmpTitle = tmpAlbum->titles;
                        while(tmpTitle != NULL) {
                            tmpTitleFree = tmpTitle;
                            tmpTitle = tmpTitle->next;
                            free(tmpTitleFree);
                        }
                        tmpAlbumFree = tmpAlbum;
                        tmpAlbum = tmpAlbum->next;
                        free(tmpAlbumFree);
                    }
                    tmpArtistFree = tmpArtist;
                    tmpArtist = tmpArtist->next;
                    free(tmpArtistFree);
                }
                break;
        }
        putchar('\n');
    } while(menu != '#');
    
    return 0;
}
