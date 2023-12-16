#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VECTOR_SIZE 50000
#define POSITIVE_VEC 100
#define NEGATIVE_VEC 100
#define TRAIN_VEC 80
#define TEST_VEC 20

int main(void)
{
    FILE *hotvectorfile, *hotv_trainfile, *hotv_testfile;
    hotvectorfile = fopen("hotvectors.txt", "r");
    hotv_trainfile = fopen("hotv_train.txt", "w+");
    hotv_testfile = fopen("hotv_test.txt", "w+");

    int **positive_hotvector, **negative_hotvector;
    positive_hotvector = (int **)malloc(POSITIVE_VEC * sizeof(int *));
    negative_hotvector = (int **)malloc(NEGATIVE_VEC * sizeof(int *));
    for (int i = 0; i < POSITIVE_VEC; i++)
        positive_hotvector[i] = (int *)malloc(VECTOR_SIZE * sizeof(int));
    for (int i = 0; i < NEGATIVE_VEC; i++)
        negative_hotvector[i] = (int *)malloc(VECTOR_SIZE * sizeof(int));

    //first 100 vectors are positive
    for (int i = 0; i < POSITIVE_VEC; i++)
    {
        for (int j = 0; j < VECTOR_SIZE; j++)
        {
            fscanf(hotvectorfile, "%d", &positive_hotvector[i][j]);
        }
    }
    //next 100 vectors are negative
    for (int i = 0; i < NEGATIVE_VEC; i++)
    {
        for (int j = 0; j < VECTOR_SIZE; j++)
        {
            fscanf(hotvectorfile, "%d", &negative_hotvector[i][j]);
        }
    }

    //shuffle positive vectors
    for (int i = 0; i < POSITIVE_VEC; i++)
    {
        int r = rand() % POSITIVE_VEC;
        int *temp = positive_hotvector[i];
        positive_hotvector[i] = positive_hotvector[r];
        positive_hotvector[r] = temp;
    }
    //shuffle negative vectors
    for (int i = 0; i < NEGATIVE_VEC; i++)
    {
        int r = rand() % NEGATIVE_VEC;
        int *temp = negative_hotvector[i];
        negative_hotvector[i] = negative_hotvector[r];
        negative_hotvector[r] = temp;
    }

    //write 80 positive vectors to train file
    for (int i = 0; i < TRAIN_VEC; i++)
    {
        for (int j = 0; j < VECTOR_SIZE; j++)
        {
            fprintf(hotv_trainfile, "%d ", positive_hotvector[i][j]);
        }
        fprintf(hotv_trainfile, "\n");
    }
    //write 20 positive vectors to test file
    for (int i = TRAIN_VEC; i < POSITIVE_VEC; i++)
    {
        for (int j = 0; j < VECTOR_SIZE; j++)
        {
            fprintf(hotv_testfile, "%d ", positive_hotvector[i][j]);
        }
        fprintf(hotv_testfile, "\n");
    }
    //write 80 negative vectors to train file
    for (int i = 0; i < TRAIN_VEC; i++)
    {
        for (int j = 0; j < VECTOR_SIZE; j++)
        {
            fprintf(hotv_trainfile, "%d ", negative_hotvector[i][j]);
        }
        fprintf(hotv_trainfile, "\n");
    }
    //write 20 negative vectors to test file
    for (int i = TRAIN_VEC; i < NEGATIVE_VEC; i++)
    {
        for (int j = 0; j < VECTOR_SIZE; j++)
        {
            fprintf(hotv_testfile, "%d ", negative_hotvector[i][j]);
        }
        fprintf(hotv_testfile, "\n");
    }

    free(positive_hotvector);
    free(negative_hotvector);

    fclose(hotvectorfile);
    fclose(hotv_trainfile);
    fclose(hotv_testfile);
    
    return 0;
}
