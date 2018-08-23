#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

typedef struct {
	int id;
	matrix_t *A;
	matrix_t *B;
	matrix_t *R;
} DadosThread;
