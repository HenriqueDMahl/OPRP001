#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "matrix.h"
#include "thread.h"

double wtime() {

	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + t.tv_usec / 1000000.0;
}

int main(int argc, char **argv) {

	double start_time, end_time;
	int nrows, ncols, nthreads;

	if ((argc != 4)) {
		printf("Uso: %s <rows> <cols> <nthreads>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	nrows = atoi(argv[1]);
	ncols = atoi(argv[2]);
	nthreads = atoi(argv[3]);

	DadosThread *dt = NULL;
	pthread_t *threads = NULL;

	if (!(dt = (DadosThread *) malloc(sizeof(DadosThread) * nthreads))) {
		 printf("Erro ao alocar memória\n");
		 exit(EXIT_FAILURE);
	}

	if (!(threads = (pthread_t *) malloc(sizeof(pthread_t) * nthreads))) {
		 printf("Erro ao alocar memória\n");
     exit(EXIT_FAILURE);
	}

	start_time = wtime();

	matrix_t *A = matrix_create_block(nrows,ncols);
	matrix_t *B = matrix_create_block(nrows,ncols);
	matrix_t *R = matrix_create_block(nrows,ncols);

	/*A->data[0][0] = 2;
		A->data[0][1] = 1;
			A->data[1][0] = 1;
				A->data[1][1] = 2;*/
	matrix_randfill(A);
	matrix_print(A);
	printf("\n");
	matrix_randfill(B);
	matrix_print(B);
	printf("\n");

	//   R = matrix_multiply(A,B,matrix_create_block);
	//   R = matrix_sum(A,B,matrix_create_block);
	//   R = matrix_inversion(A,matrix_create_block);
	//   R = matrix_transpose(A,matrix_create_block);


	for (int i = 0; i < nthreads; i++) {
		dt[i].id = i;
		pthread_create(&threads[i], NULL, call_matrix_sum_thread, (void *) (dt + i));
	}

	for (int i = 0; i < nthreads; i++) {
		pthread_join(threads[i], NULL);
	}
	free(dt);
	free(threads);

	int det = 0, ig = 0;
	matrix_print(R);
	det = matrix_determinant(A, matrix_create_block);

	ig = matrix_equal(A,B);

	printf("%d\n", det);
	printf("%d \n", ig);

	matrix_destroy_block(A);
	matrix_destroy_block(B);
	matrix_destroy_block(R);

	end_time = wtime();

	printf("%d %d %f\n", nrows, ncols, end_time - start_time);
	fflush(stdout);

	return EXIT_SUCCESS;
}
