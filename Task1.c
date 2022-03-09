#include "utils.h"
#define N0 100
#define N1 1000
#define N2 100000

int prim(char *nrString) {
    int nr = atoi(nrString);
    int i = 0;
    if (nr < 2)
        return 0;
    for (i = 2; i < nr/2 ; i++) {
        if (nr % i == 0) {
            return 0;
        }
    }
    return 1;
}

int palindrom(char *nr) {
    int n = (int) strlen(nr), i = 0;
    for (i = 0; i < n; i++) {
        if (nr[i] != nr[n - i - 1]) {
            return 0;
        }
    }
    return 1;
}

void SolveTask1() {
    int i = 0, j = 0, k = 0, n = 0, m = 0;
    int nrCifre = 0, cifraMaxima = -1, pozMaxim = -1;
    int cifraCurenta = 0, xCrt = 0, yCrt = 0, sum = 0;
    int traseu[N0 + 1][N0 + 1] = {{0}};
    traseu[0][0] = 1;
    char *cuv = 0, *toateCuv = 0;
    cuv = (char*) malloc((N1 + 1) * sizeof(char));
    toateCuv = (char*) malloc((N2 + 2) * sizeof(char));
    scanf("%d", &n);
    scanf("%d\n", &m);
    fgets(toateCuv, N2 + 1, stdin);
    cuv = strtok(toateCuv, " ");
    while (cuv != NULL) {
        switch (cuv[0]) {
            case 'a':
            cifraMaxima = -1;
            pozMaxim = -1;
                for (i = 1; i <= 4; i++) {
                    cifraCurenta = cuv[i] - '0';
                    if (cifraCurenta > cifraMaxima) {
                        cifraMaxima = cifraCurenta;
                        pozMaxim = i;
                    }
                }
                switch (pozMaxim) {
                    case 1:
                        yCrt += 1;
                        traseu[xCrt][yCrt] = traseu[xCrt][yCrt - 1] + 1;
                        break;
                    case 2:
                        xCrt -= 1;
                        traseu[xCrt][yCrt] = traseu[xCrt + 1][yCrt] + 1;
                        break;
                    case 3:
                        yCrt -= 1;
                        traseu[xCrt][yCrt] = traseu[xCrt][yCrt + 1] + 1;
                        break;
                    case 4:
                        xCrt += 1;
                        traseu[xCrt][yCrt] = traseu[xCrt - 1][yCrt] + 1;
                        break;
                }
                break;
            case 'b':
                nrCifre = (int) strlen(cuv) - 1;
                if (palindrom(&cuv[1]) == 1) {
                    if (prim(&cuv[nrCifre - 1])) {
                        yCrt -= 1;
                        traseu[xCrt][yCrt] = traseu[xCrt][yCrt + 1] + 1;
                    } else {
                        yCrt += 1;
                        traseu[xCrt][yCrt] = traseu[xCrt][yCrt - 1] + 1;
                    }
                } else {
                    if (prim(&cuv[nrCifre - 1])) {
                        xCrt -= 1;
                        traseu[xCrt][yCrt] = traseu[xCrt + 1][yCrt] + 1;
                    } else {
                        xCrt += 1;
                        traseu[xCrt][yCrt] = traseu[xCrt - 1][yCrt] + 1;
                    }
                }
                break;
            case 'c':
                nrCifre = cuv[1] - '0';
                k = cuv[2] - '0';
                sum = 0;
                for (i = 1; i <= k; i++) {
                    sum += cuv[3 + (((i-1) * k) % nrCifre)] - '0';
                }
                switch (sum % 4) {
                    case 0:
                        yCrt -= 1;
                        traseu[xCrt][yCrt] = traseu[xCrt][yCrt + 1] + 1;
                        break;
                    case 1:
                        xCrt -= 1;
                        traseu[xCrt][yCrt] = traseu[xCrt + 1][yCrt] + 1;
                        break;
                    case 2:
                        yCrt += 1;
                        traseu[xCrt][yCrt] = traseu[xCrt][yCrt - 1] + 1;
                        break;
                    case 3:
                        xCrt += 1;
                        traseu[xCrt][yCrt] = traseu[xCrt - 1][yCrt] + 1;
                        break;
                }
                break;
        }
        cuv = strtok(NULL, " \r\n");
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            printf("%d ", traseu[i][j]);
        printf("\n");
    }
}
