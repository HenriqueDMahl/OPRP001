#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "matrix.h"
#include <math.h>

matrix_t *matrix_create_block(int rows, int cols) {
	matrix_t* matrix = NULL;

	matrix = malloc(sizeof(matrix_t));
	double* bloco = malloc(sizeof(double) * rows * cols);
	matrix->data = malloc(sizeof(double*) * rows);
	matrix->rows = rows;
	matrix->cols = cols;
	for(int i = 0; i <= rows; i++) {
		matrix->data[i] = bloco+i*cols;
	}

	return matrix;
}

matrix_t *matrix_create_pointers(int rows, int cols) {
	matrix_t* matrix = NULL;
	matrix = malloc(sizeof(matrix_t));
	matrix->data = malloc(sizeof(double)*rows);
	matrix->rows = rows;
	matrix->cols = cols;

	for(int i = 0; i <= rows; i++) {
		matrix->data[i] = malloc(sizeof(double)*cols);
	}
	return matrix;
}

void matrix_destroy_pointers(matrix_t *m) {
	for(int i = 0; i <= sizeof(m->data[0]); i++) {
		for(int j = 0; j <= sizeof(m->data[0][0]); j++) {
			free(&m->data[i][j]);
		}
	}
	free(m->data);
	free(m);
}

void matrix_destroy_block(matrix_t *m) {
	free(m->data[0]);
	free(m->data);
	free(m);
}

void matrix_randfill(matrix_t *m) {
	int i, j;

	for (i = 0; i < m->rows; i++) {
		for (j = 0; j < m->cols; j++) {
			m->data[i][j] = random();
		}
	}
}

void matrix_fill(matrix_t *m, double val) {
	int i, j;
	for (i = 0; i < m->rows; i++) {
		for (j = 0; j < m->cols; j++) {
			m->data[i][j] = val;
		}
	}
}

matrix_t *matrix_multiply(matrix_t *A, matrix_t *B, matrix_t *(*p) (int, int)) {

		matrix_t *g = p(A->rows,B->cols);

		for (int i = 0; i < A->rows; i++) {
		for (int j = 0; j < B->cols; j++) {
			g->data[i][j] =  A->data[i][j] * B->data[i][j];
		}
	}
	return g;
}

void matrix_print(matrix_t *m) {
	int i, j;
	for (i = 0; i < m->rows; i++) {
		for (j = 0; j < m->cols; j++) {
			printf("%.17f ", m->data[i][j]);
		}
		printf("\n");
	}
	fflush(stdout);
}

int matrix_equal(matrix_t*A, matrix_t *B) {
	int i, j;

	if (A->rows != B->rows || A->cols != B->cols)
		return 0;

	for (i = 0; i < A->rows; i++) {
		for (j = 0; j < A->cols; j++) {
			if (A->data[i][j] != B->data[i][j])
				return 0;
		}
	}
	return 1;
}

matrix_t *matrix_sum(matrix_t *A, matrix_t *B, matrix_t *(*p) (int, int)) {

	matrix_t *g = p(A->rows,B->cols);

	for (int i = 0; i < A->rows; i++) {
		for (int j = 0; j < B->cols; j++) {
			g->data[i][j] =  A->data[i][j] + B->data[i][j];
		}
	}

	return g;
}

matrix_t *matrix_inversion(matrix_t *A, matrix_t *(*p) (int, int)) {

	matrix_t *g = p(A->rows,A->cols);

	matrix_t *aux = matrix_transpose(A,p);

	for (int i = 0; i < A->rows; i++) {
		for (int j = 0; j < A->cols; j++) {
			g->data[i][j] =  A->data[i][j] * aux->data[i][j];
		}
	}

	return g;
}

matrix_t *matrix_transpose(matrix_t *A, matrix_t *(*p) (int, int)) {

	matrix_t *g = p(A->rows,A->cols);

	for (int i = 0; i < A->rows; i++) {
		for (int j = 0; j < A->cols; j++) {
			g->data[i][j] =  A->data[j][i];
		}
	}

	return g;
}

int matrix_determinant(matrix_t *A) {
		int n = A->rows;
		if(n == 1){
        return a[0][0];
    }else{
      int det = 0;
      int i, row, col, j_aux, i_aux;

      //Escolhe a primeira linha para calcular os cofatores
      for(i = 0; i < n; i++){
          //ignora os zeros (zero vezes qualquer número é igual zero)
          if (A->data[0][i] != 0) {
							matrix_t A->dado[][]
              double aux[n - 1][n - 1];
              i_aux = 0;
              j_aux = 0;
              //Gera as matrizes para calcular os cofatores
              for(row = 1; row < n; row++){
                  for(col = 0; col < n; col++){
                      if(col != i){
                          aux[i_aux][j_aux] = a[row][col];
                          j_aux++;
                      }
                  }
                  i_aux++;
                  j_aux = 0;
              }
              double factor = (i % 2 == 0)? a[0][i] : -a[0][i];
              det = det + factor * detLaplace(n - 1, Aaux);
          }
      }
      return det;
}
