#include <stdio.h>
#include <string.h>
#define SIZE 100


void replace_symb(char *str, int i, char a) {
	str[i] = a;
}

void delete_symb(char *str, int i) {

	for (int j = i; j < SIZE - 1; j++) {
		str[j] = str[j + 1];
	}
}

void insert_symb(char *str, int i, char a) {

	for (int j = SIZE; j > i - 1; j--) {
		str[j + 1] = str[j];
	}
	str[i] = a;
}

void correct_str(char *str) {
	for (int i = 0; i < SIZE; i++) {
		if (str[0] == ' ') {
			delete_symb(str, 0);
			i--;
		}
		else if (str[0] >= 'a' && str[0] <= 'z') {
			str[0] -= 32;
		}
		else if (str[i] == ' ' && str[i + 1] == ' ') {
			delete_symb(str, i);
			i--;
		}
		else if (str[i] == ' ' && (str[i + 1] == '.' || str[i + 1] == ',' || str[i + 1] == '!' || str[i + 1] == '?' || str[i + 1] == ';' || str[i + 1] == ':')) {
			delete_symb(str, i);
			i--;
		}
		else if (str[i] == ' ' && (str[i - 1] == '.' || str[i - 1] == '?' || str[i - 1] == '!') && (str[i + 1] >= 'a' && str[i + 1] <= 'z')) {
			str[i + 1] -= 32;
		}
		else if ((str[i] == ',' || str[i] == ':' || str[i] == ';' || str[i] == '.' || str[i] == '!' || str[i] == '?') && str[i + 1] != ' ') {
			insert_symb(str, i + 1, ' ');
		}

	}
}

int main() {
	while (1) {
		char str[SIZE];
		printf("Input text: \n");
		fgets(str, SIZE, stdin);
		correct_str(str);
		printf("\nCorrected text: \n");
		puts(str);
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
}