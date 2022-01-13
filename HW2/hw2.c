#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 12
#define MAT_SIZE 12

int mat1[MAT_SIZE][MAT_SIZE];
int mat2[MAT_SIZE][MAT_SIZE];
int ret[MAT_SIZE][MAT_SIZE];

void printAllMatrices();

//multiplication function
void *matrixMulter(void *params);

//information for matrices
struct ArgStructure {
	int rowNum;
	int *mat1Ptr;
	int *mat2Ptr;
	int *retPtr;
};

int main(int argc, char *argv[]) {
    /*
     Command prompt:
     ./hw2 mat1.txt mat2.txt
    */
    
	int x,y,i;
	if (argc != 3) {
        	fprintf(stderr, "Usage: ./filename <mat1> <mat2>\n");
        	return -1;
	}

	// Read matrices
	FILE *fp1 = fopen(argv[1], "r");
	printf("Read matrix_1:\nROW: %d, col: %d\n", MAT_SIZE, MAT_SIZE);
	FILE *fp2 = fopen(argv[2], "r");
	printf("Read matrix_2:\nROW: %d, col: %d\n", MAT_SIZE, MAT_SIZE);
	printf("\n");

	// Copy matrices
	for (x = 0; x < MAT_SIZE; x++) {
        	for (y = 0; y < MAT_SIZE; y++) {
			fscanf(fp1, "%d", &mat1[x][y]);
			// mat2 need to be flipped for multiply
			fscanf(fp2, "%d", &mat2[y][x]);
        	}
    	}
	// Close files
	fclose(fp1);
	fclose(fp2);

	// Thread generation
	printf("====== Thread Generation of %d Threads ======\n", NUM_THREADS);
	pthread_t tid[NUM_THREADS];
	//create threads 
	for (i = 0; i < NUM_THREADS; i++) {
        	struct ArgStructure *argStruct;
        	argStruct = (struct ArgStructure *) malloc(sizeof(struct ArgStructure));
        	(*argStruct).rowNum = i;
        	(*argStruct).mat1Ptr = *mat1;
        	(*argStruct).mat2Ptr = *mat2;
        	(*argStruct).retPtr = *ret;
        	pthread_create(&tid[i], NULL,  matrixMulter, (void *) argStruct);
	}
	// threads finished operating
	for (i = 0; i < NUM_THREADS; i++) {
        	pthread_join(tid[i], NULL);
	}
		printf("\n\n");
		printf("Matrix multiplication completed!\n\n");

		printAllMatrices();

		return 0;
}
//multiplication function
void *matrixMulter(void *arguments) {
	int col;
	int subCol;
	struct ArgStructure *args = (struct ArgStructure*)arguments;
	int rowNum = (*args).rowNum;
	int (*mat1Ptr) = (*args).mat1Ptr+(rowNum*MAT_SIZE);
	int (*mat2Ptr) = (*args).mat2Ptr;
	int (*retPtr) = (*args).retPtr+(rowNum*MAT_SIZE);
	printf("Creating thread no.%d\n", rowNum+1);

	for (col = 0; col < MAT_SIZE; col++) {

        	int multiplyResult = 0;
        	for (subCol = 0; subCol < MAT_SIZE; subCol++) {
            		int mat1Val = *(mat1Ptr+subCol);
            		int mat2Val = *(mat2Ptr+(col*MAT_SIZE)+subCol);
            		multiplyResult += (mat1Val * mat2Val);
        	}
        *(retPtr+col) = multiplyResult;
	}

	printf("Row %d calculation succeed!\n", rowNum+1);
	free(args);
	pthread_exit((void *) 0);
}
// print matrix function
void printAllMatrices() {
	int x,y;
	printf("Matrix_1 = \n");
	for (x = 0; x < MAT_SIZE; x++) {
        	for (y = 0; y < MAT_SIZE; y++) {
            		printf("%d ", mat1[x][y]);
        	}
        printf("\n");
    	}
    	printf("\n");

	printf("Matrix_2 = \n");
	for (x = 0; x < MAT_SIZE; x++) {
        	for (y = 0; y < MAT_SIZE; y++) {
        		printf("%d ", mat2[x][y]);
        	}
        printf("\n");
    	}
	printf("\n");

	printf("Matrix_1*Matrix_2 = \n");
	for (x = 0; x < MAT_SIZE; x++) {
        	for (y = 0; y < MAT_SIZE; y++) {
            		printf("%d ", ret[x][y]);
        	}
        printf("\n");
    	}
}
