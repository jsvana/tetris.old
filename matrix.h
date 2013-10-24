#ifndef __MATRIX_H
#define __MATRIX_H

typedef struct {
	int w;
	int h;
	double *data;
} Matrix;

Matrix *matrixCreate(int w, int h, double *data);

Matrix *identityMatrix4();

Matrix *rotationMatrix4(double angle, int x, int y, int z);
Matrix *translationMatrix4(int x, int y, int z);
Matrix *scaleMatrix4(double x, double y, double z);

Matrix *matrixMultiply(Matrix *a, Matrix *b);
Matrix *matrixTranspose(Matrix *m);

void matrixPrint(Matrix *m);

void matrixDestroy(Matrix *m);

#endif
