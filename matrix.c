#include "matrix.h"

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define PI 3.1415926535

Matrix *matrixCreate(int w, int h, double *data) {
	size_t size = w * h * sizeof(double);
	Matrix *m = malloc(sizeof(Matrix));
	m->w = w;
	m->h = h;

	m->data = malloc(size);
	memcpy(m->data, data, size);

	return m;
}

Matrix *identityMatrix4() {
	double mat[] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	return matrixCreate(4, 4, mat);
}

Matrix *zeroMatrix4() {
	double mat[] = {
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0
	};

	return matrixCreate(4, 4, mat);
}

Matrix *rotationMatrix4(double a, int x, int y, int z) {
	a *= PI / 180;

	double xMat[] = {
		1, 0, 0, 0,
		0, cos(a), -sin(a), 0,
		0, sin(a), cos(a), 0,
		0, 0, 0, 1
	};
	double yMat[] = {
		cos(a), 0, sin(a), 0,
		0, 1, 0, 0,
		-sin(a), 0, cos(a), 0,
		0, 0, 0, 1
	};
	double zMat[] = {
		cos(a), -sin(a), 0, 0,
		sin(a), cos(a), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	if (x == 1) {
		return matrixCreate(4, 4, xMat);
	} else if (y == 1) {
		return matrixCreate(4, 4, yMat);
	} else {
		return matrixCreate(4, 4, zMat);
	}
}

Matrix *translationMatrix4(double x, double y, double z) {
	double transMat[] = {
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	};

	return matrixCreate(4, 4, transMat);
}

Matrix *scaleMatrix4(double x, double y, double z) {
	double scaleMat[] = {
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	};

	return matrixCreate(4, 4, scaleMat);
}

Matrix *matrixTranspose(Matrix *m) {
	Matrix *t = zeroMatrix4();
	int i, j;
	for (i = 0; i < m->h; i++) {
		for (j = 0; j < m->w; j++) {
			t->data[j * m->w + i] = m->data[i * m->w + j];
		}
	}
	return t;
}

Matrix *matrixMultiply(Matrix *a, Matrix *b) {
	if (a == NULL || b == NULL) {
		return NULL;
	}

	if (a->w != b->h) {
		return NULL;
	}

	Matrix *c = zeroMatrix4();

	gsl_matrix_view A = gsl_matrix_view_array(a->data, a->w, a->h);
	gsl_matrix_view B = gsl_matrix_view_array(b->data, b->w, b->h);
	gsl_matrix_view C = gsl_matrix_view_array(c->data, c->w, c->h);

	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, &A.matrix, &B.matrix, 0.0,
		&C.matrix);

	return c;
}

void matrixPrint(Matrix *m) {
	if (m == NULL) {
		return;
	}

	int i, j;
	for (i = 0; i < m->h; i++) {
		for (j = 0; j < m->w; j++) {
			printf("%6.2f", m->data[i * m->w + j]);
		}
		printf("\n");
	}
}

void matrixDestroy(Matrix *m) {
	if (m == NULL) {
		return;
	}

	free(m->data);
	free(m);
}
