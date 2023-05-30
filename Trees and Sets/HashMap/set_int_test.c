#include <stdio.h>
#include <stdlib.h>

#include "set_int.h"

void test(char o[], int v[], int s[], int m, char msg[]) {
    int i;

    for (i = 1; i < 2 * m - 2; i++) {
        int j, k, l;

        if (i < m - 1) {
            j = 0;
            while (j < i) {
                o[j++] = 'i';
            }
            o[j++] = 'r';
            o[j++] = 'i';
            while (j < m + 1) {
                o[j++] = 'i';
            }
            while (j < 2 * m) {
                o[j++] = 'r';
            }
        } else {
            j = 0;
            while (j < m - 1) {
                o[j++] = 'i';
            }
            while (j < i) {
                o[j++] = 'r';
            }
            o[j++] = 'r';
            o[j++] = 'i';
            while (j < 2 * m) {
                o[j++] = 'r';
            }
        }

        set_int *q = set_int_new(16, 0.75);

        j = 0;
        k = 0;

        for (l = 0; l < 2 * m; l++) {
            int value;

            if (o[l] == 'i') {
                value = v[j++];
                set_int_insert(q, value);
                if (!set_int_has(q, value)) {
                    sprintf(msg, "DOES NOT HAVE %d AFTER INSERTING", value);
                    break;
                }
            } else {
                value = s[k++];
                set_int_remove(q, value);
                if (set_int_has(q, value)) {
                    sprintf(msg, "STILL HAS %d AFTER REMOVING", value);
                    break;
                }
            }
        }

        int last = l;
        set_int_delete(&q);

        if (last < 2 * m) {
            FILE *file = fopen("set_int_test.txt", "w");

            fprintf(file, "new(%d)\n", m - 1);

            j = 0;
            k = 0;
            for (l = 0; l < 2 * m; l++) {
                if (o[l] == 'i') {
                    fprintf(file, "insert(%d)\n", v[j++]);
                } else {
                    fprintf(file, "remove(%d)\n", s[k++]);
                }
                if (l == last) {
                    fprintf(file, "%s\n", msg);
                    break;
                }
            }

            fclose(file);

            printf("test failed, see txt\n");
            exit(EXIT_FAILURE);
        }
    }
}

void perm_test(char o[], int v[], int p[], int s[], int m, char msg[]) {
    int i;
    for (i = 0; i < m; i++) {
        s[i] = v[i];
    }
    for (i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            p[j] = v[(j + i) % m];
        }
        test(o, p, s, m, msg);
    }
}

int main(void) {
    char c;
    int i, m;

    do {
        printf("numero de insercoes: ");
        i = scanf("%d", &m);
        do {
            c = getchar();
        } while (c != '\n');
    } while (i != 1 || m < 2);

    char o[2 * m], msg[50];
    int v[m], p[m], s[m];

    for (i = 0; i < m; i++) {
        v[i] = i + 1;
    }
    perm_test(o, v, p, s, m, msg);

    for (i = 0; i < m; i++) {
        v[i] = m - i;
    }
    perm_test(o, v, p, s, m, msg);

    for (int t = 0; t < 8; t++) {
        for (i = 0; i < m; i++) {
            v[i] = (float)rand() / RAND_MAX * m;
            if (v[i] == m) {
                v[i]--;
            }
            v[i]++;
        }
        perm_test(o, v, p, s, m, msg);
    }

    return EXIT_SUCCESS;
}
