#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int errid = 0;

enum ERROR {
    ERROR_FILE_OPEN = 64,
    ERROR_FILE_READ,
    ERROR_MEM_MALLOC,
    ERROR_MEM_REALLOC,
    ERROR_ARG_NULL_POINTER,
    ERROR_ARG_EMPTY_WRAPPER,
    ERROR_UNKNOWN_ERROR,
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
    int id;
    char name[129];
    int amount;
};

struct accountwrapper {
    struct account *accounts;
    int elements;
};

struct accountnamewrapper {
    char **accountnames;
    int elements;
};

struct charwrapper {
    char **string;
    int elements;
};

struct accountitem {
    int id;
    int amount;
};

void print(char *message) {
    int i = 0;
    while(message[i] != '\0') {
        putchar(message[i]);
        i++;
    }
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

void except() {
    switch(errid) {
        case ERROR_FILE_OPEN:
            print("Fehler beim Oeffnen der Datei zum Lesen. Existiert die Datei \"data\"? (Errorcode ERROR_FILE_OPEN)\n");
            errid = 0;
            break;
        case ERROR_FILE_READ:
            print("Fehler beim Lesen der Datei. Ist die Datei mit Daten im richtigen Format gefuellt? (Errorcode ERROR_FILE_READ)\n");
            errid = 0;
            break;
        case ERROR_MEM_MALLOC:
            print("Fehler beim Zuweisen von Speicher. Ist der Arbeitsspeicher voll? (Errorcode ERROR_MEM_MALLOC)\n");
            errid = 0;
            break;
        case ERROR_MEM_REALLOC:
            print("Fehler beim Zuweisen von Speicher. Ist der Arbeitsspeicher voll? (Errorcode ERROR_MEM_REALLOC)\n");
            errid = 0;
            break;
        case ERROR_ARG_EMPTY_WRAPPER:
            print("Interner Fehler bei der Parameteruebergabe. (Errorcode ERROR_ARG_EMPTY_WRAPPER)\n");
            errid = 0;
            break;
        case ERROR_ARG_NULL_POINTER:
            print("Interner Fehler bei der Parameteruebergabe. (Errorcode ERROR_ARG_NULL_POINTER)\n");
            errid = 0;
            break;
        case ERROR_UNKNOWN_ERROR:
            print("Unbekannte Fehler. (Errorcode ERROR_UNKNOWN_ERROR)\n");
            errid = 0;
            break;
        case 0:
            print("Eigentlich kein Fehler, keine Ahnung, was schief ging.\n");
            errid = 0;
            break;
        default:
            print("Unbekannter Fehler. (kein Errorcode)\n");
            errid = 0;
            break;
    }
}

int isStringInArray(char *string, char **array, int arraysize) {
    int i;
    for(i = 0; i < arraysize; i++) {
        if(!strcmp(string, array[i]))
            return 1;
    }
    return 0;
}

struct datawrapper *readDataFromFile(char *filename) {
    FILE *fp;
    if(fp = fopen(filename, "r")) {
        char line[257];
        int i = 0;
        struct data *read = NULL;
        while(fgets(line, 1024, fp)) {
            i++;
            if(i == 1) {
                if(!(read = malloc(sizeof(struct data)))) {
                    errid = ERROR_MEM_MALLOC;
                    return NULL;
                }
            } else {
                if(!(read = realloc(read, i * sizeof(struct data)))) {
                    errid = ERROR_MEM_REALLOC;
                    return NULL;
                }
            }
            sscanf(line, "%d %s %s %d", &read[i - 1].id, read[i - 1].activename, read[i - 1].passivename, &read[i - 1].amount);
        }
        if(i == 0 || !read) {
            errid = ERROR_FILE_READ;
            return NULL;
        }
        struct datawrapper *wrapper;
        if(!(wrapper = malloc(sizeof(struct datawrapper)))) {
            errid = ERROR_MEM_MALLOC;
            return NULL;
        };
        wrapper->elements = i;
        wrapper->data = read;
        return wrapper;
    } else {
        errid = ERROR_FILE_OPEN;
        return NULL;
    }
}

struct accountwrapper *rawToAccount(struct datawrapper *inputdata) {
    if(!inputdata) {
        errid = ERROR_ARG_NULL_POINTER;
        return NULL;
    }
    if(!inputdata->elements) {
        errid = ERROR_ARG_EMPTY_WRAPPER;
        return NULL;
    }
    struct data *data = inputdata->data;
    struct account *accounts;
    if(!(accounts = malloc(inputdata->elements * 2 * sizeof(struct account)))) {
        errid = ERROR_MEM_MALLOC;
        return NULL;
    }
    int i = 0;
    for(i = 0; i < inputdata->elements; i++) {
        accounts[i * 2].id = data[i].id;
        accounts[i * 2 + 1].id = data[i].id;
        accounts[i * 2].amount = -data[i].amount;
        accounts[i * 2 + 1].amount = data[i].amount;
        strcpy(accounts[i * 2].name, data[i].activename);
        strcpy(accounts[i * 2 + 1].name, data[i].passivename);
    }
    struct accountwrapper *wrapper;
    if(!(wrapper = malloc(sizeof(struct accountwrapper)))) {
        errid = ERROR_MEM_MALLOC;
        return NULL;
    }
    wrapper->accounts = accounts;
    wrapper->elements = i * 2;
    return wrapper;
}

struct accountwrapper *getAccountsByName(struct accountwrapper *inputdata, char *accountname) {
    if(!inputdata || !accountname) {
        errid = ERROR_ARG_NULL_POINTER;
        return NULL;
    }
    if(!inputdata->elements) {
        errid = ERROR_ARG_EMPTY_WRAPPER;
        return NULL;
    }
    struct account *inputaccounts = inputdata->accounts;
    struct account *outputaccounts;
    int i, j = 0;
    for(i = 0; i < inputdata->elements; i++) {
        if(!strcmp(accountname, inputaccounts[i].name)) {
            if(!j) {
                if(!(outputaccounts = malloc(sizeof(struct account)))) {
                    errid = ERROR_MEM_MALLOC;
                    return NULL;
                }
            } else {
                if(!(outputaccounts = realloc(outputaccounts, (j + 1) * sizeof(struct account)))) {
                    errid = ERROR_MEM_MALLOC;
                    return NULL;
                }
            }
            outputaccounts[j].id = inputaccounts[i].id;
            strcpy(outputaccounts[j].name, inputaccounts[i].name);
            outputaccounts[j].amount = inputaccounts[i].amount;
            j++;
        }
    }
    if(!j) {
        errid = ERROR_UNKNOWN_ERROR;
        return NULL;
    }
    struct accountwrapper *wrapper;
    if(!(wrapper = malloc(sizeof(struct accountnamewrapper)))) {
        errid = ERROR_MEM_MALLOC;
        return NULL;
    }
    wrapper->accounts = outputaccounts;
    wrapper->elements = j;
    return wrapper;
}

struct accountnamewrapper *getAllAccountNamesFromAccountData(struct accountwrapper *inputdata) {
    if(!inputdata) {
        errid = ERROR_ARG_NULL_POINTER;
        return NULL;
    }
    if(!inputdata->elements) {
        errid = ERROR_ARG_EMPTY_WRAPPER;
        return NULL;
    }
    struct account *accounts = inputdata->accounts;
    int i, j = 0;
    char **accountnames;
    for(i = 0; i < inputdata->elements; i++) {
        if(!i) {
            if(!(accountnames = malloc(sizeof(char*)))) {
                errid = ERROR_MEM_MALLOC;
                return NULL;
            }
            if(!(accountnames[j] = malloc(129 * sizeof(char)))) {
                errid = ERROR_MEM_MALLOC;
                return NULL;
            }
            strcpy(accountnames[j], accounts->name);
            j++;
        } else {
            if(!(accountnames = realloc(accountnames, (j + 1) * sizeof(char*)))) {
                errid = ERROR_MEM_REALLOC;
                return NULL;
            }
            if(!(accountnames[j] = malloc(129 * sizeof(char)))) {
                errid = ERROR_MEM_REALLOC;
                return NULL;
            }
            if(!isStringInArray(accounts[i].name, accountnames, j + 1)) {
                strcpy(accountnames[j], accounts[i].name);
                j++;
            }
        }
    }
    if(!accountnames) {
        errid = ERROR_UNKNOWN_ERROR;
        return NULL;
    }
    struct accountnamewrapper *wrapper;
    if(!(wrapper = malloc(sizeof(struct accountnamewrapper)))) {
        errid = ERROR_MEM_MALLOC;
        return NULL;
    }
    wrapper->accountnames = accountnames;
    wrapper->elements = j;
    return wrapper;
}

struct charwrapper *accountToFormattedString(struct accountwrapper *inputdata) {
    if(!inputdata) {
        errid = ERROR_ARG_NULL_POINTER;
        return NULL;
    }
    if(!inputdata->elements) {
        errid = ERROR_ARG_EMPTY_WRAPPER;
        return NULL;
    }
    int i;
    char **formattedstring;
    for(i = 0; i < inputdata->elements; i++) {
        
    }
    struct charwrapper *wrapper;
    if(!(wrapper = malloc(sizeof(struct charwrapper)))) {
        errid = ERROR_MEM_MALLOC;
        return NULL;
    };
    return wrapper;
};

int main() {
    struct datawrapper *datawrapper;
    if(datawrapper = readDataFromFile("data")) {
        struct data *data = datawrapper->data;
        struct accountwrapper *accountwrapper;
        if(accountwrapper = rawToAccount(datawrapper)) {
            struct accountnamewrapper *accountnamewrapper;
            if(accountnamewrapper = getAllAccountNamesFromAccountData(accountwrapper)) {
                int i;
                struct accountwrapper *currentaccountwrapper;
                struct account *currentaccounts;
                for(i = 0; i < accountnamewrapper->elements; i++) {
                    if(currentaccountwrapper = getAccountsByName(accountwrapper, accountnamewrapper->accountnames[i])) {
                        currentaccounts = currentaccountwrapper->accounts;
                        printf("%s\n", accountnamewrapper->accountnames[i]);
                        print("Soll      |      Haben\n");
                        print("----------+-----------\n");
                        int j;
                        struct accountitem *has, *should;
                        int hascount = 0, shouldcount = 0;
                        for(j = 0; j < currentaccountwrapper->elements; j++) {
                            if(currentaccounts[j].amount < 0) {
                                if(shouldcount == 0) {
                                    should = malloc(sizeof(struct accountitem));
                                } else {
                                    should = realloc(should, (shouldcount + 1) * sizeof(struct accountitem));
                                }
                                should[shouldcount].amount = -currentaccounts[j].amount;
                                should[shouldcount].id = currentaccounts[j].id;
                                shouldcount++;
                            } else {
                                if(hascount == 0) {
                                    has = malloc(sizeof(struct accountitem));
                                } else {
                                    has = realloc(has, (hascount + 1) * sizeof(struct accountitem));
                                }
                                has[hascount].amount = currentaccounts[j].amount;
                                has[hascount].id = currentaccounts[j].id;
                                hascount++;
                            }
                        }
                        for(j = 0; j < ((hascount > shouldcount ) ? hascount : shouldcount); j++) {
                            if(j < shouldcount) {
                                printf("%d)%d", should[j].id, should[j].amount);
                            }
                            print("\t  |   ");
                            if(j < hascount) {
                                printf("%d)%d", has[j].id, has[j].amount);
                            }
                            putchar('\n');
                        }
                        putchar('\n');
                    } else {
                        print("getAccountsByName()\n");
                        except();
                    }
                }
            } else {
                print("getAllAccountNamesFromAccountData()\n");
                except();
            }
        } else {
            print("rawToAccount()\n");
            except();
        }
        
    } else {
        print("readDataFromFile()\n");
        except();
    }
        
    return 0;
}