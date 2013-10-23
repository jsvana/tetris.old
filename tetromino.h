#ifndef __TETROMINO_H
#define __TETROMINO_H

typedef struct {
} Tetromino;

Tetromino *createTetromino(int type);
void freeTetromino(Tetromino *t);

#endif
