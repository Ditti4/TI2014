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
        preparedmessage = malloc((len + (3 - (len % 3))) * sizeof(char));
        
    } else {
        preparedmessage = malloc(len * sizeof(char));
    }
    strcpy(preparedmessage, message);
    int i;
    for(i = len; i < (len + (3 - (len % 3))); i++) {
        preparedmessage[i] = 0;
    }
    struct stringwrapper *wrapper;
    wrapper = malloc(sizeof(struct stringwrapper));
    wrapper->string = preparedmessage;
    wrapper->addedbytes = 3 - (len % 3);
    return wrapper;
}

char *b64encode(struct stringwrapper *message) {
    if(!message)
        return NULL;
    int len = strlen(message->string) + message->addedbytes;
    char *preparedmessage = message->string;
    int i;
    char first, second, third, fourth;
    char *encodedmessage = malloc(len * sizeof(char));
    for(i = 0; i < len / 3; i++) {
        first = ((preparedmessage[i * 3] >> 2));
        first = (first < 0) ? 128 + first : first;
        second = ((preparedmessage[i * 3] << 6) >> 2) | (preparedmessage[i * 3 + 1] >> 4);
        second = (second < 0) ? 128 + second : second;
        third = ((preparedmessage[i * 3 + 1] << 4) >> 2) | (preparedmessage[i * 3 + 2] >> 6);
        third = (third < 0) ? 128 + third : third;
        fourth = ((preparedmessage[i * 3 + 2] << 4) >> 2);
        fourth = (fourth < 0) ? 128 + fourth : fourth;
        printf("%d\n%d\n%d\n%d\n%d\n", first, second, third, fourth, len);
        encodedmessage[i * 4] = base64chars[first];
        encodedmessage[i * 4 + 1] = base64chars[second];
        encodedmessage[i * 4 + 2] = base64chars[third];
        encodedmessage[i * 4 + 3] = base64chars[fourth];
    }
//     putchar(encodedmessage[0]);
//     putchar('\n');
//     putchar(encodedmessage[1]);
//     putchar('\n');
    switch(message->addedbytes) {
        case 1:
            encodedmessage[len] = '=';
            break;
        case 2:
            encodedmessage[len - 1] = '=';
            encodedmessage[len] = '=';
            break;
    }
    return encodedmessage;
}

int main(int argc, char **argv) {
    printf(b64encode(b64prepare("test")));

    return 0;
}