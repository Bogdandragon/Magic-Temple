#include "utils.h"
#define N0 100
#define N1 1000
#define N2 10000
#define N3 100000

void SolveTask3() {
    char *p = (char*) malloc(N3 * sizeof(char));
    char cuv[N2][N0] = {{0}}, *cuvCrt = 0;
    char legatura1[N2][N0] = {{0}}, legatura2[N2][N0] = {{0}};
    int legaturaCount[N1] = {0};
    int nrCuv = 0, i = 0, j = 0, legaturi = 0, exista = 0;
    while (fgets(p, N3 - 1, stdin)) {
        cuvCrt = strtok(p, " .,!;\r\n");
        while (cuvCrt != NULL) {
            strncpy(cuv[nrCuv], cuvCrt, N0);
            nrCuv += 1;
            cuvCrt = strtok(NULL, " .,!;\r\n");
        }
    }
    for (i = 1; i < nrCuv; i++) {
        exista = 0;
        for (j = 0; j < legaturi; j++) {
            if (strcmp(legatura1[j], cuv[i - 1]) == 0 &&
                strcmp(legatura2[j], cuv[i]) == 0) {
                exista = 1;
                legaturaCount[j] += 1;
                break;
            }
        }
        if (exista == 0) {
            strncpy(legatura1[legaturi], cuv[i - 1], N0);
            strncpy(legatura2[legaturi], cuv[i], N0);
            legaturaCount[legaturi] += 1;
            legaturi += 1;
        }
    }
    printf("%d\n", legaturi);
    for (i = 0; i < legaturi; i++) {
        printf("%s %s %d\n", legatura1[i], legatura2[i], legaturaCount[i]);
    }
    free(p);
}
