#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
    int opt, limite=10, min=0, max=2, seed=5, range, i;

   while ((opt = getopt(argc, argv, "s:a:b:c:")) != -1) {
       switch (opt) {
       case 's':
           /* semilla */
           seed = atoi(optarg);
           break;
       case 'a':
           /* minimo */
           min = atoi(optarg);
           break;
       case 'b':
           /* maximo */
           max = atoi(optarg);
           break;
       case 'c':
           /* cantidad de aleatorios */
           limite = atoi(optarg);
           break;
       default: /* '?' */
           fprintf(stderr, "Usage: %s <-s seed> <-a min> <-b max> <-c limite>\n", argv[0]);
           exit(EXIT_FAILURE);
       }
   }

    srand(seed);
    range = max - min;

    for(i=0; i<limite; i++ ) {
        printf("%d\n", min+rand()%range);
    }
    printf("\n");
}
