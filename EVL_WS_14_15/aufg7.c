#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addInterpret(int key, char *name);
void addAlbum(int key, char *name, int interpretKey, int *titleKeys, char (*titleNames)[50], int titleCount);
struct album * getAlbum(int key);
struct interpret * getInterpret(int key);
struct interpret * getInterpretByAlbumKey(int key);
int removeInterpret(int key);
int removeAlbum(int key);
struct album * findAlbum(char *name);
struct interpret * findInterpret(char *name);

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

struct interpret {
    int key;
    char name[50];
    struct album *alben;
    struct interpret *next;
};

struct interpret *head;

void addInterpret(int key, char *name) {
    struct interpret *tmp;
    tmp = malloc(sizeof(struct interpret));
    tmp->key = key;
    strcpy(tmp->name, name);
    tmp->alben = NULL;
    tmp->next = head;
    head = tmp;
}

void addAlbum(int key, char *name, int interpretKey, int *titleKeys, char (*titleNames)[50], int titleCount) {
    struct album *tmpAlbum;
    struct title *tmpTitle;
    struct interpret *tmpInterpret = head;
    int i;
    
    tmpInterpret = getInterpret(interpretKey);
    if(!tmpInterpret) {
        printf("Interpret nicht gefunden. Hinzufuegen wurde abgebrochen.");
        return;
    }
    
    tmpAlbum = malloc(sizeof(struct album));
    tmpAlbum->key = key;
    strcpy(tmpAlbum->name, name);
    tmpAlbum->next = tmpInterpret->alben;
    tmpInterpret->alben = tmpAlbum;
    
    for(i = 0; i <= titleCount; i++) {
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

struct album * getAlbum(int key) {
    struct interpret *tmpInterpret = head;
    struct album *tmpAlbum = tmpInterpret->alben;
    while(tmpInterpret != NULL) {
        while(tmpAlbum != NULL) {
            if(tmpAlbum->key == key)
                break;
            else
                tmpAlbum = tmpAlbum->next;
        }
        if(tmpAlbum->key == key)
            break;
        else
            tmpInterpret = tmpInterpret->next;
    }
    if(tmpAlbum->key == key)
        return tmpAlbum;
    else
        return NULL;
}

struct interpret * getInterpret(int key) {
    struct interpret *tmpInterpret = head;
    while(tmpInterpret != NULL) {
        if(tmpInterpret->key == key)
            break;
        else
            tmpInterpret = tmpInterpret->next;
    }
    if(tmpInterpret->key == key)
        return tmpInterpret;
    else
        return NULL;
}

struct interpret * getInterpretByAlbumKey(int key) {
    struct interpret *tmpInterpret = head;
    struct album *tmpAlbum = tmpInterpret->alben;
    while(tmpInterpret != NULL) {
        while(tmpAlbum != NULL) {
            if(tmpAlbum->key == key)
                break;
            else
                tmpAlbum = tmpAlbum->next;
        }
        if(tmpAlbum->key == key)
            break;
        else
            tmpInterpret = tmpInterpret->next;
    }
    if(tmpAlbum->key == key)
        return tmpInterpret;
    else
        return NULL;
}

int removeInterpret(int key) {
    struct interpret *tmpInterpret = head;
    if(tmpInterpret == NULL)
        return 1;
    if(tmpInterpret->key == key) {
        head = tmpInterpret->next;
        return 0;
    }
    while(tmpInterpret->next != NULL) {
        if(tmpInterpret->next->key == key) {
            tmpInterpret->next = tmpInterpret->next->next;
            return 0;
        } else
            tmpInterpret = tmpInterpret->next;
    }
    return 2;
}

int removeAlbum(int key) {
    struct interpret *tmpInterpret = getInterpretByAlbumKey(key);
    struct album *tmpAlbum;
    if(tmpInterpret == NULL)
        return 1;
    if((tmpAlbum = tmpInterpret->alben)) {
        if(tmpAlbum->key == key) {
            tmpInterpret->alben = tmpAlbum->next;
            return 0;
        }
        while(tmpAlbum->next != NULL) {
            if(tmpAlbum->next->key == key) {
                tmpAlbum->next = tmpAlbum->next->next;
                return 0;
            }
        }
        return 42;
    } else
        return 42;
}

struct interpret * findInterpret(char *name) {
    struct interpret *tmpInterpret = head;
    while(tmpInterpret != NULL) {
        if(strstr(tmpInterpret->name, name))
            break;
        else
            tmpInterpret = tmpInterpret->next;
    }
    if(strstr(tmpInterpret->name, name))
        return tmpInterpret;
    else
        return NULL;
}

struct album * findAlbum(char *name) {
    struct interpret *tmpInterpret = head;
    struct album *tmpAlbum = tmpInterpret->alben;
    while(tmpInterpret != NULL) {
        while(tmpAlbum != NULL) {
            if(strstr(tmpAlbum->name, name))
                break;
            else
                tmpAlbum = tmpAlbum->next;
        }
        if(strstr(tmpAlbum->name, name))
            break;
        else
            tmpInterpret = tmpInterpret->next;
    }
    if(strstr(tmpAlbum->name, name))
        return tmpAlbum;
    else
        return NULL;
}

int main() {
    char menu;
    char interpretName[50], albumName[50], titleNames[50][50];
    int interpretKey, albumKey;
    int i, titleKeys[50];
    struct interpret *tmpInterpret;
    struct album *tmpAlbum;
    struct title *tmpTitle;
    
    head = NULL;
    
    do {
        printf("Interpret/Album (h)inzufuegen, (a)nzeigen (mittels Key), (e)ntfernen, (s)uchen (mittels Name), (I)nfo, beenden mit #: ");
        menu = getchar();
        fflush(stdin);
        
        switch(menu) {
            case 'H':
            case 'h':
                printf("(I)nterpret, (A)lbum hinzufuegen, jedes andere Zeichen, um zum Hauptmenue zurueckzukehren: ");
                menu = getchar();
                if(menu == 'I' || menu == 'i') {
                    printf("Interpreten-Key angeben: ");
                    scanf("%d", &interpretKey);
                    printf("Interpreten-Name angeben (maximal 50 Zeichen): ");
                    scanf("%50s", interpretName);
                    addInterpret(interpretKey, interpretName);
                } else if(menu == 'A' || menu == 'a') {
                    printf("Album-Key angeben: ");
                    scanf("%d", &albumKey);
                    printf("Album-Name angeben (maximal 50 Zeichen): ");
                    scanf("%50s", albumName);
                    printf("Interpret-Key angeben: ");
                    scanf("%d", &interpretKey);
                    i = 0;
                    do {
                        printf("Titelnummer angeben (0 zum fertigstellen): ");
                        scanf("%d", &titleKeys[i]);
                        if(!titleKeys[i]) {
                            i--;
                            break;
                        }
                        printf("Titelname angeben (maximal 50 Zeichen): ");
                        scanf("%50s", titleNames[i]);
                        i++;
                    } while(i && i < 50);
                    addAlbum(albumKey, albumName, interpretKey, titleKeys, titleNames, i);
                }
                break;
            case 'A':
            case 'a':
                printf("(I)nterpret, (A)lbum anzeigen, jedes andere Zeichen, um zum Hauptmenue zurueckzukehren: ");
                menu = getchar();
                if(menu == 'I' || menu == 'i') {
                    printf("Interpreten-Key angeben: ");
                    scanf("%d", &interpretKey);
                    if((tmpInterpret = getInterpret(interpretKey))) {
                        printf("Infos zum Interpret:\nKey:\t%d\nName:\t%s\nAlben:\n", tmpInterpret->key, tmpInterpret->name);
                        if(!tmpInterpret->alben)
                            printf("\tKeine.");
                        else {
                            tmpAlbum = tmpInterpret->alben;
                            while(tmpAlbum != NULL) {
                                printf("%d\t%s\n", tmpAlbum->key, tmpAlbum->name);
                                tmpAlbum = tmpAlbum->next;
                            }
                        }
                    } else {
                        printf("Kein Interpret mit dieser ID gefunden. Schon mal die Suche verwendet? Vielleicht hilft die weiter.\n");
                    }
                } else if(menu == 'A' || menu == 'a') {
                    printf("Album-Key angeben: ");
                    scanf("%d", &albumKey);
                    if((tmpAlbum = getAlbum(albumKey))) {
                        tmpInterpret = getInterpretByAlbumKey(albumKey);
                        printf("Infos zum Album:\nKey:\t%d\nName:\t%s\nInterpret:\t%s\nTitel:\n", tmpAlbum->key, tmpAlbum->name, ((tmpInterpret->name) ? tmpInterpret->name : "Keiner (wat?)"));
                        if(!tmpAlbum->titles)
                            printf("\tKeine.");
                        else {
                            tmpTitle = tmpAlbum->titles;
                            while(tmpTitle != NULL) {
                                printf("%d\t%s\n", tmpTitle->key, tmpTitle->name);
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
                menu = getchar();
                if(menu == 'I' || menu == 'i') {
                    printf("Interpreten-Key angeben: ");
                    scanf("%d", &interpretKey);
                    switch(removeInterpret(interpretKey)) {
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
                menu = getchar();
                if(menu == 'I' || menu == 'i') {
                    printf("Interpreten-Name angeben (maximal 50 Zeichen): ");
                    scanf("%50s", interpretName);
                    if((tmpInterpret = getInterpret(interpretKey))) {
                        printf("Infos zum Interpret:\nKey:\t%d\nName:\t%s\nAlben:\n", tmpInterpret->key, tmpInterpret->name);
                        if(!tmpInterpret->alben)
                            printf("\tKeine.");
                        else {
                            tmpAlbum = tmpInterpret->alben;
                            while(tmpAlbum != NULL) {
                                printf("%d\t%s\n", tmpAlbum->key, tmpAlbum->name);
                                tmpAlbum = tmpAlbum->next;
                            }
                        }
                    } else {
                        printf("Keinen Interpreten gefunden, der diesen Name hat oder ihn enthaelt. Sicher, dass er in der Datenbank vorhanden ist?\n");
                    }
                } else if(menu == 'A' || menu == 'a') {
                    printf("Album-Name angeben (maximal 50 Zeichen): ");
                    scanf("%50s", albumName);
                    if((tmpAlbum = getAlbum(albumKey))) {
                        tmpInterpret = getInterpretByAlbumKey(albumKey);
                        printf("Infos zum Album:\nKey:\t%d\nName:\t%s\nInterpret:\t%s\nTitel:\n", tmpAlbum->key, tmpAlbum->name, ((tmpInterpret->name) ? tmpInterpret->name : "Keiner (wat?)"));
                        if(!tmpAlbum->titles)
                            printf("\tKeine.");
                        else {
                            tmpTitle = tmpAlbum->titles;
                            while(tmpTitle != NULL) {
                                printf("%d\t%s\n", tmpTitle->key, tmpTitle->name);
                                tmpTitle = tmpTitle->next;
                            }
                        }
                    } else {
                        printf("Kein Album gefunden, der diesen Name hat oder ihn enthaelt. Sicher, dass es in der Datenbank vorhanden ist?\n");
                    }
                }
                break;
            case 'I':
            case 'i':
                printf("Bevor ein Album hinzugefuegt werden kann, muss erst der Interpret angelegt werden. Das Album wird dem Interpreten dann mittels seines eindeutigen Key zugewiesen.\n");
                break;
            case '#':
                break;
        }
        putchar('\n');
    } while(menu != '#');
    
    return 0;
}
