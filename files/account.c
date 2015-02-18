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

struct transaction {
    int id;
    char name[129];
    int amount;
};

struct transactionwrapper {
    struct transaction *transactions;
    int elements;
};

struct transactionnamewrapper {
    char **transactionnames;
    int elements;
};

struct transactionitem {
    int id;
    int amount;
};

struct charwrapper {
    char **string;
    int elements;
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

struct transactionwrapper *rawToTransaction(struct datawrapper *inputdata) {
    if(!inputdata) {
        errid = ERROR_ARG_NULL_POINTER;
        return NULL;
    }
    if(!inputdata->elements) {
        errid = ERROR_ARG_EMPTY_WRAPPER;
        return NULL;
    }
    struct data *data = inputdata->data;
    struct transaction *transactions;
    if(!(transactions = malloc(inputdata->elements * 2 * sizeof(struct transaction)))) {
        errid = ERROR_MEM_MALLOC;
        return NULL;
    }
    int i = 0;
    for(i = 0; i < inputdata->elements; i++) {
        transactions[i * 2].id = data[i].id;
        transactions[i * 2 + 1].id = data[i].id;
        transactions[i * 2].amount = -data[i].amount;
        transactions[i * 2 + 1].amount = data[i].amount;
        strcpy(transactions[i * 2].name, data[i].activename);
        strcpy(transactions[i * 2 + 1].name, data[i].passivename);
    }
    struct transactionwrapper *wrapper;
    if(!(wrapper = malloc(sizeof(struct transactionwrapper)))) {
        errid = ERROR_MEM_MALLOC;
        return NULL;
    }
    wrapper->transactions = transactions;
    wrapper->elements = i * 2;
    return wrapper;
}

struct transactionwrapper *getTransactionsByName(struct transactionwrapper *inputdata, char *transactionname) {
    if(!inputdata || !transactionname) {
        errid = ERROR_ARG_NULL_POINTER;
        return NULL;
    }
    if(!inputdata->elements) {
        errid = ERROR_ARG_EMPTY_WRAPPER;
        return NULL;
    }
    struct transaction *inputtransactions = inputdata->transactions;
    struct transaction *outputtransactions;
    int i, j = 0;
    for(i = 0; i < inputdata->elements; i++) {
        if(!strcmp(transactionname, inputtransactions[i].name)) {
            if(!j) {
                if(!(outputtransactions = malloc(sizeof(struct transaction)))) {
                    errid = ERROR_MEM_MALLOC;
                    return NULL;
                }
            } else {
                if(!(outputtransactions = realloc(outputtransactions, (j + 1) * sizeof(struct transaction)))) {
                    errid = ERROR_MEM_MALLOC;
                    return NULL;
                }
            }
            outputtransactions[j].id = inputtransactions[i].id;
            strcpy(outputtransactions[j].name, inputtransactions[i].name);
            outputtransactions[j].amount = inputtransactions[i].amount;
            j++;
        }
    }
    if(!j) {
        errid = ERROR_UNKNOWN_ERROR;
        return NULL;
    }
    struct transactionwrapper *wrapper;
    if(!(wrapper = malloc(sizeof(struct transactionnamewrapper)))) {
        errid = ERROR_MEM_MALLOC;
        return NULL;
    }
    wrapper->transactions = outputtransactions;
    wrapper->elements = j;
    return wrapper;
}

struct transactionnamewrapper *getAllTransactionNamesFromTransactionData(struct transactionwrapper *inputdata) {
    if(!inputdata) {
        errid = ERROR_ARG_NULL_POINTER;
        return NULL;
    }
    if(!inputdata->elements) {
        errid = ERROR_ARG_EMPTY_WRAPPER;
        return NULL;
    }
    struct transaction *transactions = inputdata->transactions;
    int i, j = 0;
    char **transactionnames;
    for(i = 0; i < inputdata->elements; i++) {
        if(!i) {
            if(!(transactionnames = malloc(sizeof(char*)))) {
                errid = ERROR_MEM_MALLOC;
                return NULL;
            }
            if(!(transactionnames[j] = malloc(129 * sizeof(char)))) {
                errid = ERROR_MEM_MALLOC;
                return NULL;
            }
            strcpy(transactionnames[j], transactions->name);
            j++;
        } else {
            if(!(transactionnames = realloc(transactionnames, (j + 1) * sizeof(char*)))) {
                errid = ERROR_MEM_REALLOC;
                return NULL;
            }
            if(!(transactionnames[j] = malloc(129 * sizeof(char)))) {
                errid = ERROR_MEM_REALLOC;
                return NULL;
            }
            if(!isStringInArray(transactions[i].name, transactionnames, j + 1)) {
                strcpy(transactionnames[j], transactions[i].name);
                j++;
            }
        }
    }
    if(!transactionnames) {
        errid = ERROR_UNKNOWN_ERROR;
        return NULL;
    }
    struct transactionnamewrapper *wrapper;
    if(!(wrapper = malloc(sizeof(struct transactionnamewrapper)))) {
        errid = ERROR_MEM_MALLOC;
        return NULL;
    }
    wrapper->transactionnames = transactionnames;
    wrapper->elements = j;
    return wrapper;
}

struct charwrapper *accountToFormattedString(struct transactionwrapper *inputdata) {
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
        struct transactionwrapper *transactionwrapper;
        if(transactionwrapper = rawToTransaction(datawrapper)) {
            struct transactionnamewrapper *transactionnamewrapper;
            if(transactionnamewrapper = getAllTransactionNamesFromTransactionData(transactionwrapper)) {
                int i;
                struct transactionwrapper *currenttransactionwrapper;
                struct transaction *currenttransactions;
                for(i = 0; i < transactionnamewrapper->elements; i++) {
                    if(currenttransactionwrapper = getTransactionsByName(transactionwrapper, transactionnamewrapper->transactionnames[i])) {
                        currenttransactions = currenttransactionwrapper->transactions;
                        printf("%s\n", transactionnamewrapper->transactionnames[i]);
                        print("Soll      |      Haben\n");
                        print("----------+-----------\n");
                        int j;
                        struct transactionitem *credits, *targets;
                        int creditcount = 0, targetscount = 0;
                        for(j = 0; j < currenttransactionwrapper->elements; j++) {
                            if(currenttransactions[j].amount < 0) {
                                if(targetscount == 0) {
                                    targets = malloc(sizeof(struct transactionitem));
                                } else {
                                    targets = realloc(targets, (targetscount + 1) * sizeof(struct transactionitem));
                                }
                                targets[targetscount].amount = -currenttransactions[j].amount;
                                targets[targetscount].id = currenttransactions[j].id;
                                targetscount++;
                            } else {
                                if(creditcount == 0) {
                                    credits = malloc(sizeof(struct transactionitem));
                                } else {
                                    credits = realloc(credits, (creditcount + 1) * sizeof(struct transactionitem));
                                }
                                credits[creditcount].amount = currenttransactions[j].amount;
                                credits[creditcount].id = currenttransactions[j].id;
                                creditcount++;
                            }
                        }
                        for(j = 0; j < ((creditcount > targetscount ) ? creditcount : targetscount); j++) {
                            if(j < targetscount) {
                                printf("%d)%d", targets[j].id, targets[j].amount);
                            }
                            print("\t  |   ");
                            if(j < creditcount) {
                                printf("%d)%d", credits[j].id, credits[j].amount);
                            }
                            putchar('\n');
                        }
                        putchar('\n');
                    } else {
                        print("getTransactionsByName()\n");
                        except();
                    }
                }
            } else {
                print("getAllTransactionNamesFromTransactionData()\n");
                except();
            }
        } else {
            print("rawToTransaction()\n");
            except();
        }
        
    } else {
        print("readDataFromFile()\n");
        except();
    }
        
    return 0;
}