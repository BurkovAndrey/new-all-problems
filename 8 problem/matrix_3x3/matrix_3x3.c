#include <stdio.h>
#include <math.h>
#include <string.h>
#pragma warning(disable : 4996)


typedef struct Matrix_3x3 {
float data[3][3];
} matrix;

int get_rand_range_int(const int min, const int max) {
	return rand() % (max - min + 1) + min;
}

matrix InitArray(FILE *fl) {
	matrix array;
	char mychar = 0;
	printf("how fill array\nR-Rundom numbers\nF-numbers of file\nM-My nambers\n");
	while (1) {
		mychar = getch();
		if (mychar > 96) mychar = mychar - 32;
		if (mychar == 'R') {
			int bottom_line=0, upper_bound=0;
			printf("From: ");
			scanf_s("%d", &bottom_line);
			printf("Before: ");
			scanf_s("%d", &upper_bound);
			for (int x = 0; x < 3; x++) {
				for (int y = 0; y < 3; y++) {
					array.data[x][y] = (float)get_rand_range_int(bottom_line, upper_bound);
				}
			}
			return array;
		}
		if (mychar == 'F') {
			
			if (fl == 0) {
				printf("There is no such file\n");
				exit(1);
			}
			for (int x = 0; x < 3; x++) {
				for (int y = 0; y < 3; y++) {
					fscanf(fl, "%f", &array.data[x][y]);
				}
			}
			fclose(fl);
			return array;
		}
		if (mychar == 'M') {
			for (int x = 0; x < 3; x++) {
				for (int y = 0; y < 3; y++) {
					printf("%d row %d column:  ", x + 1, y + 1);
					scanf("%f", &array.data[x][y]);
				}
			}
			return array;
		}
	}
}

void ArrayPrint(matrix array) {
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			printf("%f	", array.data[x][y]);
		}
		printf("\n");
	}
}

//invers
matrix ArrayInvers(matrix array1) {
	matrix array2;
	array2.data[0][0] = array1.data[1][1] * array1.data[2][2] - array1.data[1][2] * array1.data[2][1];
	array2.data[0][1] = array1.data[0][1] * array1.data[2][2] - array1.data[0][2] * array1.data[2][1];
	array2.data[0][2] = array1.data[0][1] * array1.data[1][2] - array1.data[0][2] * array1.data[1][1];
	array2.data[1][0] = array1.data[1][0] * array1.data[2][2] - array1.data[2][0] * array1.data[1][2];
	array2.data[1][1] = array1.data[0][0] * array1.data[2][2] - array1.data[0][2] * array1.data[2][0];
	array2.data[1][2] = array1.data[0][0] * array1.data[1][2] - array1.data[0][2] * array1.data[1][0];
	array2.data[2][0] = array1.data[1][0] * array1.data[2][1] - array1.data[1][1] * array1.data[2][0];
	array2.data[2][1] = array1.data[0][0] * array1.data[2][1] - array1.data[0][1] * array1.data[2][0];
	array2.data[2][2] = array1.data[0][0] * array1.data[1][1] - array1.data[0][1] * array1.data[1][0];
	return array2;
}

//Determinant
float ArrayDeterminant(matrix array) {
	float determinant = 0.0;
	determinant = array.data[0][0] * array.data[1][1] * array.data[2][2] + array.data[1][0] * array.data[2][1] * array.data[0][2] +
		array.data[2][0] * array.data[0][1] * array.data[1][2] - array.data[2][0] * array.data[1][1] * array.data[0][2] -
		array.data[0][0] * array.data[2][1] * array.data[1][2] - array.data[1][0] * array.data[0][1] * array.data[2][2];
	return determinant;
}

//summ
matrix ArraySumm(matrix array1, matrix array2) {
	matrix array3;
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			array3.data[x][y] = array1.data[x][y] + array2.data[x][y];
		}
	}
	return array3;
}

//Multiplication
matrix ArrayMultiplication(matrix array1, matrix array2) {
	matrix array3;
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			for (int z = 0; z < 3; z++) {
				array3.data[x][y] =array1.data[x][z] * array2.data[z][y];
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
			MyChar = getch();
			if (MyChar > 96) MyChar = MyChar - 32;
			if (MyChar == 'O') {
				system("cls");
				FILE *fl;
				printf("You want to find the inverse matrix.\n");
				fl = fopen("invers_matrix_fill.txt", "r");
				matrix array1 = InitArray(fl);
				fclose(fl);
				matrix invers = ArrayInvers(array1);
				float determenant = ArrayDeterminant(array1);
				if (determenant == 0) {
					printf("not invers matrix");
				}
				else {
					system("cls");
					ArrayPrint(array1);
					printf("\ndetermemamt array = %f\n", determenant);
					printf("invers:\n");
					ArrayPrint(invers);
				}
				fl = fopen("invers_matrix.txt", "w+");
				if (fl != NULL)
				{
					fputs("determinant=", fl);
					fprintf(fl, "%f\n", determenant);
					fprintf(fl, "\n");
					for (int x = 0; x < 3; x++) {
						for (int y = 0; y < 3; y++) {
							fprintf(fl, "%f  ", invers.data[x][y]);
						}
						fprintf(fl, "\n");
					}
				}
				fclose(fl);
				break;
			}
			if (MyChar == 'D') {
				system("cls");
				FILE *fl;
				printf("You want to find the determinant of the matrix.\n");
				fl = fopen("determinant_matrix_fill.txt", "r");
				matrix array = InitArray(fl);
				fclose(fl);
				float determenant = ArrayDeterminant(array);
				system("cls");
				ArrayPrint(array);
				printf("\ndetermemamt array = %f", determenant);
				fl = fopen("determinant_matrix.txt", "w+");
				if (fl != NULL)
				{
					fputs("determinant=", fl);
					fprintf(fl, "%f", determenant);
				}
				fclose(fl);
				break;
			}
			if (MyChar == 'M') {
				system("cls");
				FILE *fl;
				printf("You want to find the matrix multiplication.\n");
				fl = fopen("multiplication_matrix_1_fill.txt", "r");
				matrix array1 = InitArray(fl);
				fclose(fl);
				fl = fopen("\multiplication_matrix_2_fill.txt", "r");
				matrix array2 = InitArray(fl);
				fclose(fl);
				matrix array3 = ArrayMultiplication(array1, array2);
				system("cls");
				ArrayPrint(array1);
				printf("*\n");
				ArrayPrint(array2);
				printf("=\n");
				ArrayPrint(array3);
				fl = fopen("multiplication_matrix.txt", "w+");
				if (fl != NULL)
				{
					for (int x = 0; x < 3; x++) {
						for (int y = 0; y < 3; y++) {
							fprintf(fl, "%f ", array3.data[x][y]);
						}
						fprintf(fl, "\n");
					}
				}
				fclose(fl);
				break;
			}
			if (MyChar == 'S') {
				system("cls");
				FILE *fl;
				fl = fopen("sum_matrix_1_fill.txt", "r");
				matrix array1 = InitArray(fl);
				fclose(fl);
				fl = fopen("sum_matrix_2_fill.txt", "r");
				matrix array2 = InitArray( fl);
				fclose(fl);
				matrix array3 = ArraySumm(array1, array2);
				system("cls");
				ArrayPrint(array1);
				printf("+\n");
				ArrayPrint(array2);
				printf("=\n");
				ArrayPrint(array3);
				fl = fopen("sum_matrix.txt", "w+");
				if (fl != NULL)
				{
					for (int x = 0; x < 3 ; x++) {
						for (int y = 0; y < 3 ; y++) {
							fprintf(fl, "%f  ", array3.data[x][y]);
						}
						fprintf(fl, "\n");
					}
				}
				fclose(fl);
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