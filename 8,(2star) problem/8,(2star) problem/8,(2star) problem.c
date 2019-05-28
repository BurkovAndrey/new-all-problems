#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Bits.h>
#pragma warning(disable : 4996)

typedef struct Matrix_N_M {
	int i;
	int j;
	int** arr;
}matrix;

matrix initArray(int N, int M) {
	matrix array;
	array.i = N;
	array.j = M;
	array.arr = (int**)malloc(array.i * sizeof(int*));
	for (int k = 0; k < array.i; k++) {
		array.arr[k] = (int*)malloc(array.j * sizeof(int));
	}
	return array;
}

matrix DynamicArrayFill(int N, int M, FILE *fl) {
	matrix array;
	array.i = N;
	array.j = M;
	array.arr = (int**)malloc(array.i * sizeof(int*));
	for (int k = 0; k < array.i; k++) {
		array.arr[k] = (int*)malloc(array.j * sizeof(int));
	}
	char mychar = 0;
	printf("how fill array\nR-Rundom nubder\nF-nubbrt of file\n");
	while (1) {
		mychar = getch();
		if (mychar > 96) mychar = mychar - 32;
		if (mychar == 'R') {
			int bottom_line, upper_bound, direction;
			printf("From: ");
			scanf_s("%d", &bottom_line);
			printf("Before: ");
			scanf_s("%d", &upper_bound);
			for (int x = 0; x < N; x++) {
				for (int y = 0; y < M; y++) {
					array.arr[x][y] = get_rand_range_int(bottom_line, upper_bound);
				}
			}
			return array;
		}
		if (mychar == 'F') {
			if (fl == 0) {
				printf("There is no such file\n");
				exit(1);
			}
			for (int x = 0; x < N; x++) {
				for (int y = 0; y < M; y++) {
					fscanf(fl, "%d", &array.arr[x][y]);
				}
			}
			return array;
		}
	}
	return array;
}

void DynamicArrayFree(matrix array)
{
	for (int k = 0; k < array.i; k++)
		free(array.arr[k]);
	free(array.arr);
}

void DynamicArrayPrint(matrix array) {
	for (int x = 0; x < array.i; x++) {
		for (int y = 0; y < array.j; y++) {
			printf("%d	", array.arr[x][y]);
		}
		printf("\n");
	}
}

int get_rand_range_int(const int min, const int max) {
	return rand() % (max - min + 1) + min;
}

//invers 
matrix MinorArray(matrix array, int x, int y) {
	int N = array.i - 1;
	int M = array.j - 1;
	matrix minorn = initArray(N, M);
	for (int i = 0, l = 0; i < array.i; ++i, ++l) {
		if (i == y) {
			--l;
			continue;
		}
		for (int j = 0, k = 0; j < array.j; ++j, ++k) {
			if (j == x) {
				--k;
				continue;
			}
			minorn.arr[l][k] = array.arr[i][j];
		}
	}
	return minorn;
}
matrix ArrayInvers(matrix array1) {
	matrix array2 = initArray(array1.i, array1.j);
	int sig = 1;
	for (int x = 0; x < array2.i; x++) {
		for (int y = 0; y < array2.j; y++) {
			matrix min = MinorArray(array1, x, y);
			array2.arr[x][y] = sig * ArrayDeterminant(min, array2.i - 1);
			sig *= -1;
			DynamicArrayFree(min);
		}
	}
	return array2;
}

//Determinant
int ArrayDeterminant(matrix array, int N) {
	if (N == 1)
		return array.arr[0][0];
	if (N == 2)
		return (array.arr[1][1] * array.arr[0][0]) - (array.arr[0][1] * array.arr[1][0]);
	int determinant = 0, sig = 1;
	for (int i = 0; i < N; ++i) {
		matrix min = MinorArray(array, i, 0);
		determinant += (sig * array.arr[0][i] * ArrayDeterminant(min, N - 1));
		sig *= -1;
		DynamicArrayFree(min);
	}
	return determinant;
}

//summ
matrix ArraySumm(matrix array1, matrix array2) {
	matrix array3 = initArray(array1.i, array1.j);
	for (int x = 0; x < array1.i; x++) {
		for (int y = 0; y < array1.j; y++) {
			array3.arr[x][y] = array1.arr[x][y] + array2.arr[x][y];
		}
	}
	return array3;
}
//Multiplication
matrix ArrayMultiplication(matrix array1, matrix array2) {
	matrix array3 = initArray(array1.i, array2.j);
	for (int x = 0; x < array3.i; x++) {
		for (int y = 0; y < array3.j; y++) {
			array3.arr[x][y] = 0;
			for (int z = 0; z < array1.j; z++) {
				array3.arr[x][y] = array3.arr[x][y] + array1.arr[x][z] * array2.arr[z][y];
			}
		}
	}
	return array3;
}

int main() {
	printf("This program calculates the determinant product of the sum of the matrix and the inverse of the matrix.");
	while (1) {
		printf("What do you want to do?\n Calculate the determinant - D. \n Calculate the inverse matrix - O. \n Calculate the multiplication of matrices - M. \n Calculate the sum of matrices - S.\n E-exet\n");
		while (1) {
			char MyChar = 0;
			int flag = 0;
			MyChar = getch();
			if (MyChar > 96) MyChar = MyChar - 32;
			if (MyChar == 'O') {
				system("cls");
				FILE *fl;
				int high = 1;
				printf("You want to find the inverse matrix, enter the dimensions of the matrix.\n");
				printf("high");
				scanf_s("%d", &high);
				fl = fopen("invers_matrix_fill.txt", "r");
				matrix array1 = DynamicArrayFill(high, high, fl);
				fclose(fl);
				matrix invers = ArrayInvers(array1);
				int determenant = ArrayDeterminant(array1, high);
				if (determenant == 0) {
					printf("not invers matrix");
				}
				else {
					system("cls");
					DynamicArrayPrint(array1);
					printf("\ndetermemamt array = %d\n", determenant);
					printf("invers:\n");
					DynamicArrayPrint(invers);
					DynamicArrayFree(array1);
				}
				fl = fopen("invers_matrix.txt", "w+");
				if (fl != NULL)
				{
					fputs("determinant=", fl);
					fprintf(fl, "%d\n", determenant);
					fprintf(fl, "\n");
					for (int x = 0; x < invers.i; x++) {
						for (int y = 0; y < invers.j; y++) {
							fprintf(fl, "%d  ", invers.arr[x][y]);
						}
						fprintf(fl, "\n");
					}
				}
				fclose(fl);
				DynamicArrayFree(invers);
				break;
			}
			if (MyChar == 'D') {
				system("cls");
				FILE *fl;
				int high = 0;
				printf("You want to find the determinant of the matrix enter the dimensions of the matrix.\n");
				printf("high");
				scanf_s("%d", &high);
				fl = fopen("determinant_matrix_fill.txt", "r");
				matrix array1 = DynamicArrayFill(high, high, fl);
				fclose(fl);
				int determenant = ArrayDeterminant(array1, high);
				system("cls");
				DynamicArrayPrint(array1);
				printf("\ndetermemamt array = %d", determenant);
				fl = fopen("determinant_matrix.txt", "w+");
				if (fl != NULL)
				{
					fputs("determinant=", fl);
					fprintf(fl, "%d", determenant);

				}
				fclose(fl);
				break;
			}
			if (MyChar == 'M') {
				system("cls");
				FILE *fl;
				int high1 = 1;
				int	width1 = 1;
				int high2 = 1;
				int	width2 = 1;
				printf("You want to find the matrix multiplication enter the matrix sizes.\n");
				printf("high1=");
				scanf_s("%d", &high1);
				printf("width1=");
				scanf_s("%d", &width1);
				printf("width2=");
				scanf_s("%d", &width2);
				high2 = width1;
				fl = fopen("multiplication_matrix_1_fill.txt", "r");
				matrix array1 = DynamicArrayFill(high1, width1, fl);
				fclose(fl);
				fl = fopen("multiplication_matrix_2_fill.txt", "r");
				matrix array2 = DynamicArrayFill(high2, width2, fl);
				fclose(fl);
				matrix array3 = ArrayMultiplication(array1, array2);
				system("cls");
				DynamicArrayPrint(array1);
				printf("*\n");
				DynamicArrayPrint(array2);
				printf("=\n");
				DynamicArrayPrint(array3);
				DynamicArrayFree(array1);
				DynamicArrayFree(array2);
				fl = fopen("multiplication_matrix.txt", "w+");
				if (fl != NULL)
				{
					for (int x = 0; x < array3.i; x++) {
						for (int y = 0; y < array3.j; y++) {
							fprintf(fl, "%d  ", array3.arr[x][y]);
						}
						fprintf(fl, "\n");
					}
				}
				fclose(fl);
				DynamicArrayFree(array3);
				break;
			}
			if (MyChar == 'S') {
				system("cls");
				FILE *fl;
				int high1 = 1;
				int	width1 = 1;
				printf("You want to find the sum of matrices enter the dimensions of the matrices.\n");
				printf("high=");
				scanf_s("%d", &high1);
				printf("width=");
				scanf_s("%d", &width1);
				fl = fopen("sum_matrix_1_fill.txt", "r");
				matrix array1 = DynamicArrayFill(high1, width1, fl);
				fclose(fl);
				fl = fopen("sum_matrix_2_fill.txt", "r");
				matrix array2 = DynamicArrayFill(high1, width1, fl);
				fclose(fl);
				matrix array3 = ArraySumm(array1, array2);
				system("cls");
				DynamicArrayPrint(array1);
				printf("+\n");
				DynamicArrayPrint(array2);
				printf("=\n");
				DynamicArrayPrint(array3);
				DynamicArrayFree(array1);
				DynamicArrayFree(array2);
				fl = fopen("sum_matrix.txt", "w+");
				if (fl != NULL)
				{
					for (int x = 0; x < array3.i; x++) {
						for (int y = 0; y < array3.j; y++) {
							fprintf(fl, "%d  ", array3.arr[x][y]);
						}
						fprintf(fl, "\n");
					}
				}
				fclose(fl);
				DynamicArrayFree(array3);
				break;
			}
			if (MyChar == 'E') {
				system("cls");
				printf("End work");
				return 0;
			}
		}
		printf("\nWould you like to repeat the calculation? \nEnter Y or N \n");
		char MyChar = 0;
		do {
			MyChar = getch();
			if (MyChar > 96) MyChar = MyChar - 32;
			if (MyChar == 'N') {
				system("cls");
				printf("End work");
				return 0;
			}
			if (MyChar == 'Y') {
				system("cls");
				break;
			}
		} while (1);
	}
	return 0;
}