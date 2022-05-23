#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 27

// Debug defines to activate print on workers threads
//#define DEBUG_BOX
//#define DEBUG_ROW
//#define DEBUG_COL

int sudoku[9][9] = { 
    {6, 2, 4, 5, 3, 9, 1, 8, 7}, 
    {5, 1, 9, 7, 2, 8, 6, 3, 4}, 
    {8, 3, 7, 6, 1, 4, 2, 9, 5}, 
    {1, 4, 3, 8, 6, 5, 7, 2, 9}, 
    {9, 5, 8, 2, 4, 7, 3, 6, 1}, 
    {7, 6, 2, 3, 9, 1, 4, 5, 8}, 
    {3, 7, 1, 9, 5, 6, 8, 4, 2}, 
    {4, 9, 6, 1, 8, 2, 5, 7, 3},
    {2, 8, 5, 4, 7, 3, 9, 1, 6}
    };

int results[27] = {0};


typedef struct {
    int row;
    int column;
} parameters;

void *threadBox (void *id){
    parameters *box = (parameters *) id;
    int numeros[9] = {0};
    int boxNum = (box->row/3) + box->column; // 0 to 8 counting from top left
    results[boxNum] = 1;
    #ifdef DEBUG_BOX
    printf("Analyzing box row: %d, col: %d\n", box->row +1, box->column +1);
    #endif
    int i;

    for (i = 0; i < 9; i++) {
        #ifdef DEBUG_BOX
        printf("Number on row: %d, col: %d is : %d, numbers on: %d\n", box->row + i/3 +1, box->column + i%3 +1, sudoku[box->row + i/3][box->column + i%3], numeros[sudoku[box->row + i/3][box->column + i%3]-1]);
        #endif
         if (numeros[sudoku[box->row + i/3][box->column + i%3]-1] || sudoku[box->row + i/3][box->column + i%3] < 1 || sudoku[box->row + i/3][box->column + i%3] > 9) {
             //results[boxNum] = 0;
         } else {
             numeros[sudoku[box->row + i/3][box->column + i%3]-1]++;
         }
    }
    pthread_exit(NULL);

}

void *threadRow (void *id){
    long row = (long) id;
    int numeros[9] = {0};
    results[row+9] = 1;
    #ifdef DEBUG_ROW
    printf("Analyzing row number %d\n", row +1);
    #endif
    int i;
    for (i = 0; i < 9; i++) {
         if (numeros[sudoku[row][i]-1] || sudoku[row][i] < 1 || sudoku[row][i] > 9) {
             #ifdef DEBUG_ROW
             printf("Error on row: row: %d, col: %d\n", row+1, i+1);
             #endif
             results[row+9] = 0;
         } else {
             numeros[sudoku[row][i]-1]++;
         }
    }
    pthread_exit(NULL);

}

void *threadCol (void *id){
    long col = (long) id;
    int numeros[9] = {0};
    #ifdef DEBUG_COL
    printf("Analyzing col number %d\n", col +1);
    #endif
    int i;
    results[col+18] = 1;
    for (i = 0; i < 9; i++) {
         if (numeros[sudoku[i][col]-1] || sudoku[i][col] < 1 || sudoku[i][col] > 9) {
             #ifdef DEBUG_COL
             printf("Error on col: row: %d, col: %d\n", i+1, col+1);
             #endif
             results[col+18] = 0;
         } else {
             numeros[sudoku[i][col]-1]++;
         }
    }
    pthread_exit(NULL);

}


int main (int argc, char *argv[]){
    pthread_t thread [NUM_THREADS]; // array de threads
    pthread_attr_t attr; 
    parameters *data[9];
    long status;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE);


    // Threads start
    long i = 0;
    int rowBox;
    int colBox;
    for (i = 0; i < 9; i++) {
        rowBox = (i % 3) * 3; // Rows for 0, 3, 6, 0, 3, 6, 0, 3, 6
        colBox = i - (i % 3); // Column for 0, 0, 0, 3, 3, 3, 6, 6, 6
        data[i] = (parameters *) malloc(sizeof(parameters));
        data[i]->row = rowBox;
        data[i]->column = colBox;
        //thread for boxes verification
        status = pthread_create(&thread[i], &attr, threadBox, (void *) data[i]);
        if(status){
            perror("pthread_create");
            exit(1);
        }
        // thread for row verification
        status = pthread_create(&thread[i+9], &attr, threadRow, (void *) i); 
        if(status){
            perror("pthread_create");
            exit(1);
        }
        // thread for column verification
        status = pthread_create(&thread[i+18], &attr, threadCol, (void *) i); 
        if(status){
            perror("pthread_create");
            exit(1);
        }
    }

    // Threads finish and error checks
    int error = 0;
    for (i = 0; i < 27; i++) {
        status = pthread_join(thread[i], NULL);
        if (i < 9) {
            // free execution time allocation
            // no use because process will be finished after this
            // but is a good habit
            free(data[i]);
        }
        if(status){
            perror("pthread_join");
            exit(1);
        }
        if (results[i] == 0) {
            error = 1;
            if (i < 9) {
                printf("Error on box number %ld\n", i+1);
            } else if (i < 18) {
                printf("Error on row %ld\n", i-8);
            } else {
                printf("Error on collumn %ld\n", i-17);
            }
        } else {
            if (i < 9) {
                printf("Box number %ld ok\n", i+1);
            } else if (i < 18) {
                printf("Row %ld ok\n", i-8);
            } else {
                printf("Collumn %ld ok\n", i-17);
            }
        }
    }
    if (!error) {
        printf("Sudoku ok \n");
    }

    pthread_attr_destroy (&attr);
    pthread_exit(NULL);
}