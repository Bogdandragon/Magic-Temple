#include "utils.h"
#define N0 100
#define N1 1000
#define DS 26
#define T 10

char rotateChar(char caract, int key) {
    if (key == 0) {
        return caract;
    } else if (caract != '\0') {
            if (isdigit(caract)) {
                return (char)((caract - key % T) >= '0' ?
                    caract - key % T : '9' + (caract - key % T - '0' + 1));
            } else if (isalpha(caract)) {
                if (isupper(caract)) {
                    return (char)((caract - key % DS) >= 'A' ?
                        caract - (char) key % DS :
                        'Z' + (caract - (char) key % DS - 'A' + 1));
                } else {
                    return (char)((caract - key % DS) >= 'a' ?
                        caract - (char) key % DS :
                        'z' + (caract - (char) key % DS - 'a' + 1));
                }
            }
    } else {
        return caract;
    }
    return caract;
}

char* decryptCaesar(int key, char* code) {
    int n = (int) strlen(code), i = 0;
    for (; i < n; i++) {
        if (code[i] == '\n')
            code[i] = '\0';
        code[i] = rotateChar(code[i], key);
    }
    return code;
}

char* decryptVigenere(char* key, char* code) {
    int n = (int) strlen(code), i = 0, keyLen = (int) strlen(key);
    for (; i < n; i++) {
        code[i] = rotateChar(code[i], key[i % keyLen] - 'A');
    }
    return code;
}

char* addition(char* a1, char* a2) {
    int len1 = (int) strlen(a1), len2 = (int) strlen(a2);
    int i = 1, remember = 0, k = 0;
    char* sum = (char*) malloc((N1 + 2) * sizeof(char));
    sum[0] = '0';
    sum[len1 + 1] = sum[len2 + 1] = '\0';
    while (a1[0] == '0') {
            for (i = 0; i < len1; i++)
                a1[i] = a1[i + 1];
            len1 -= 1;
            a1[len1 + 1] = '\0';
    }
    while (a2[0] == '0') {
            for (i = 0; i < len2; i++)
                a2[i] = a2[i + 1];
            len2 -= 1;
            a2[len2 + 1] = '\0';
    }
    if (len1 < len2) {
        while (len1 < len2) {
            for (i = 1; i <= len1; i++)
                a1[i] = a1[i-1];
            len1 += 1;
            a1[0] = '0';
        }
    } else if (len1 > len2) {
        while (len2 < len1) {
            for (i = 1; i <= len2; i++)
                a2[i] = a2[i-1];
            len2 += 1;
            a2[0] = '0';
        }
    }
    i = 1;
    /*printf("%s\n", a1);
    printf("%s\n", a2);*/
    while (i <= len1 || i <= len2) {
        if (i > len1) {
            sum[i] = a2[i - 1];
        } else if (i > len2) {
            sum[i] = a1[i - 1];
        } else {
            sum[i] = (char)(a1[i - 1] + a2[i - 1] - (char) '0');
            if (sum[i] > '9') {
                remember = 1 + (sum[i] - (char) '9') / (T);
                sum[i] = (char)((char)'0' + (sum[i] - (char) '9') +
                    (char) ((T) * (remember - 1) - 1));
                k = i - 1;
                while (k >= 0 && remember != 0) {
                    sum[k] = (char)(sum[k] + (char)remember);
                    remember = 0;
                    if (sum[k] > '9') {
                        remember = 1 + (sum[k] - '9') / (T);
                        sum[k] = (char)((char)'0' + (sum[k] - (char)'9') +
                            (char)((T) * (remember - 1) - 1));
                    }
                    k -= 1;
                }
            }
        }
        // printf("%s\n", sum);
        i += 1;
    }
    while (sum[0] == '0') {
        for (i = 1; i <= strlen(sum); i++)
            sum[i - 1] = sum[i];
    }
    return sum;
}

char* superTrim(char* cuv) {
    int i = 0, j = 0;
    for (i = 0; i <= strlen(cuv); i++) {
        if (cuv[i] == ' ' || cuv[i] == '\n') {
            for (j = i + 1; j <= strlen(cuv); j++) {
                cuv[j - 1] = cuv[j];
            }
        }
    }
    return cuv;
}

void SolveTask2() {
    int key = 0, i = 0;
    /*char* code = 0;
    char* codeType = 0;
    char* charKey = 0;
    codeType = (char*) malloc(N0 * sizeof(char));
    code = (char*) malloc((N1 + 1) * sizeof(char));
    char* a1 = 0, *a2 = 0;
    charKey = (char*) malloc(N0 * sizeof(char));
    a1 = (char*) malloc((N1 + 1) * sizeof(char));
    a2 = (char*) malloc((N1 + 1) * sizeof(char));*/
    scanf("%d\n", &i);
    char code[N1 + 1] = {0};
    char codeType[N0] = {0};
    char charKey[N1] = {0};
    char a1[N1 + 1] = {0}, a2[N1 + 1] = {0};
    fgets(codeType, N0, stdin);
    switch (codeType[0]) {
        case 'c':
            scanf("%d\n", &key);
            fgets(code, N1, stdin);
            /*code = superTrim(code);
            code = decryptCaesar(key, code);*/
            strncpy(code, superTrim(code), N1 + 1);
            strncpy(code, decryptCaesar(key, code), N1 + 1);
            printf("%s\n", code);
            break;
        case 'v':
            fgets(charKey, N0, stdin);
            fgets(code, N1, stdin);
            /*charKey = superTrim(charKey);
            code = superTrim(code);
            code = decryptVigenere(charKey, code);*/
            strncpy(charKey, superTrim(charKey), N0);
            strncpy(code, superTrim(code), N1 + 1);
            strncpy(code, decryptVigenere(charKey, code), N1 + 1);
            printf("%s\n", code);
            break;
        case 'a':
            scanf("%d\n", &key);
            fgets(a1, N1 + 1, stdin);
            fgets(a2, N1 + 1, stdin);
            /*a1 = superTrim(a1);
            a2 = superTrim(a2);
            a1 = decryptCaesar(key, a1);
            a2 = decryptCaesar(key, a2);*/
            strncpy(a1, superTrim(a1), N1);
            strncpy(a2, superTrim(a2), N1);
            strncpy(a1, decryptCaesar(key, a1), N1);
            strncpy(a2, decryptCaesar(key, a2), N1);
            printf("%s\n", addition(a1, a2));
            break;
    }
    /*free(codeType);
    free(code);
    free(charKey);
    free(a1);
    free(a2);*/
}
