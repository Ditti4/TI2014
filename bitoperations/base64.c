#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char base64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

struct stringwrapper {
    char *string;
    int addedbytes;
};

void print(char *message) {
    int i;
    for(i = 0; message[i] != '\0'; i++)
        putchar(message[i]);
}

struct stringwrapper *b64prepare(char *message) {
    int len = strlen(message);
    char *preparedmessage;
    if(len % 3) {
        preparedmessage = malloc((len + 3 - (len % 3) + 1) * sizeof(char));
        
    } else {
        preparedmessage = malloc(len * sizeof(char));
    }
    strcpy(preparedmessage, message);
    if(len % 3) {
        int i;
        for(i = len; i < (len + 3 - (len % 3)); i++) {
            preparedmessage[i] = 0;
        }
    }
    struct stringwrapper *wrapper;
    wrapper = malloc(sizeof(struct stringwrapper));
    wrapper->string = preparedmessage;
    wrapper->addedbytes = (len % 3) ? 3 - (len % 3) : 0;
    return wrapper;
}

char *b64encode(struct stringwrapper *message) {
    if(!message)
        return NULL;
    int len = strlen(message->string) + message->addedbytes;
    char *preparedmessage = message->string;
    int i;
    char first, second, third, fourth;
    char *encodedmessage = malloc((len / 3) * 4 * sizeof(char));
    for(i = 0; i < len / 3; i++) {
        first = ((preparedmessage[i * 3] >> 2));
        second = ((preparedmessage[i * 3] & 3) << 4) | (preparedmessage[i * 3 + 1] >> 4);
        third = ((preparedmessage[i * 3 + 1] & 15) << 2) | (preparedmessage[i * 3 + 2] >> 6);
        fourth = (preparedmessage[i * 3 + 2] & 63);
        encodedmessage[i * 4] = base64chars[first];
        encodedmessage[i * 4 + 1] = base64chars[second];
        encodedmessage[i * 4 + 2] = base64chars[third];
        encodedmessage[i * 4 + 3] = base64chars[fourth];
    }
    switch(message->addedbytes) {
        case 1:
            encodedmessage[(len / 3 * 4) - 1] = '=';
            encodedmessage[(len / 3 * 4)] = '\0';
            break;
        case 2:
            encodedmessage[(len / 3 * 4) - 1] = '=';
            encodedmessage[(len / 3 * 4) - 2] = '=';
            encodedmessage[(len / 3 * 4)] = '\0';
            break;
    }
    return encodedmessage;
}

int main(int argc, char **argv) {
    char string[256];
    print("Zeichenkette zum Encoden eingeben: ");
    scanf("%s", string);
    print(b64encode(b64prepare(string)));
    putchar('\n');
    return 0;
}