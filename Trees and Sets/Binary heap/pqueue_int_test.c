#include <stdio.h>
#include <stdlib.h>

#include "pqueue_int.h"

int compare(const void *a, const void *b) {
    return *((int *)a) - *((int *)b);
}

void sort(int v[], int n) {
    qsort(v, n, sizeof(int), compare);
}

void test(char o[], int v[], int s[], int m, char msg[]) {
    int i;

    for (i = 1; i < 2 * m - 2; i++) {
        int j, k, l;

        for (j = 0; j < m; j++) {
            s[j] = v[j];
        }

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
            sort(s, i);
            sort(s + 1, m - 1);
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
            sort(s, m - 1);
            sort(s + i - m + 2, 2 * m - i - 2);
        }

        pqueue_int *q = pqueue_int_new(m - 1);
        int size = 0;

        j = 0;
        k = 0;

        for (l = 0; l < 2 * m; l++) {
            int actual;
            int expected;

            if (o[l] == 'i') {
                pqueue_int_insert(q, v[j++]);
                size++;
            } else {
                actual = pqueue_int_remove(q);
                expected = s[k++];
                if (actual != expected) {
                    sprintf(msg, "REMOVED %d BUT EXPECTED %d", actual, expected);
                    break;
                }
                size--;
            }

            actual = pqueue_int_empty(q);
            expected = (size == 0);
            if (actual == 0 && expected == 1) {
                sprintf(msg, "GOT NOT EMPTY BUT EXPECTED EMPTY");
                break;
            }
            if (actual == 1 && expected == 0) {
                sprintf(msg, "GOT EMPTY BUT EXPECTED NOT EMPTY");
                break;
            }

            actual = pqueue_int_full(q);
            expected = (size == m - 1);
            if (actual == 0 && expected == 1) {
                sprintf(msg, "GOT NOT FULL BUT EXPECTED FULL");
                break;
            }
            if (actual == 1 && expected == 0) {
                sprintf(msg, "GOT FULL BUT EXPECTED NOT FULL");
                break;
            }
        }

        int last = l;
        pqueue_int_delete(&q);

        if (last < 2 * m) {
            FILE *file = fopen("pqueue_int_test.txt", "w");

            fprintf(file, "new(%d)\n", m - 1);

            j = 0;
            k = 0;
            for (l = 0; l < 2 * m; l++) {
                if (o[l] == 'i') {
                    fprintf(file, "insert(%d)\n", v[j++]);
                } else {
                    fprintf(file, "remove()\n");
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
    for (int i = 0; i < m; i++) {
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
