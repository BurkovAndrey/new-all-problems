#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

#define SIZE 5

typedef struct string_info {
	char *word;
	int len;
}string;
string replace_symb(string str, int i, char a);
string delete_symb(string str, int i);
string insert_symb(string str, int i, char a);
string correct_str(string str);
string reallocate_buffer(string str);
string trim_buffer(string str);

string replace_symb(string str, int i, char a) {
	str.word[i] = a;
	return str;
}

string delete_symb(string str, int i) {
	for (int j = i; j < str.len - 1; j++) {
		str.word[j] = str.word[j + 1];
	}
	str.len--;
	return str;
}

string insert_symb(string str, int i, char a) {
	for (int j = str.len; j > i - 1; j--) {
		str.word[j] = str.word[j - 1];
	}
	str.word[i] = a;
	str.len++;
	return str;
}

string correct_str(string str) {
	int memory = str.len;
	for (int i = 0; i < str.len; i++) {
		if (str.word[0] == ' ') {	
			str = delete_symb(str, 0);
			i--;
		}
		else if (str.word[0] >= 'a' && str.word[0] <= 'z') {	
			str.word[0] -= 32;
		}
		else if (str.word[i] == ' ' && str.word[i + 1] == ' ') {	
			str = delete_symb(str, i);
			i--;
		}
		else if (str.word[i] == ' ' && (str.word[i + 1] == '.' || str.word[i + 1] == ',' || str.word[i + 1] == '!' || str.word[i + 1] == '?' || str.word[i + 1] == ';' || str.word[i + 1] == ':')) {
			str = delete_symb(str, i);
			i--;
		}
		else if (str.word[i] == ' ' && (str.word[i - 1] == '.' || str.word[i - 1] == '?' || str.word[i - 1] == '!') && (str.word[i + 1] >= 'a' && str.word[i + 1] <= 'z')) {	
			str.word[i + 1] -= 32;
		}
		else if ((str.word[i] == ',' || str.word[i] == ':' || str.word[i] == ';' || str.word[i] == '.' || str.word[i] == '!' || str.word[i] == '?') && str.word[i + 1] != ' ') {

			
			if (str.len == memory) {
				str = reallocate_buffer(str);
				memory = str.len + SIZE;
			}
			str = insert_symb(str, i + 1, ' ');
		}

	}
	str = trim_buffer(str);

	return str;
}

console_input(char *parr) {

}
file_input() {

}
string reallocate_buffer(string str) {
	string newstr;
	newstr.len = str.len;
	newstr.word = malloc(sizeof(char) * (str.len + SIZE));

	for (int i = 0; i < str.len; i++) {
		newstr.word[i] = str.word[i];
	}

	free(str.word);
	return newstr;
}
string trim_buffer(string str) {
	string newstr;
	newstr.len = str.len;
	newstr.word = malloc(sizeof(char) * newstr.len);

	for (int i = 0; i < str.len; i++) {
		newstr.word[i] = str.word[i];
	}

	free(str.word);
	return newstr;
}
string GetText(FILE *fp, char terminator) {
	char temp;
	string str;

	str.len = 0;
	str.word = malloc(sizeof(char) * (SIZE));

	int i = 0;
	printf("Your simbols: \n");
	while (((temp = getc(fp)) != terminator) && (temp != EOF)) {
		if (fp != stdin) {
			printf("%c", temp);
		}
		//Посимвольный ввод
		str.word[i] = temp;
		i++;
		str.len++;

		if (i % SIZE == 0) {
			str = reallocate_buffer(str);
		}
	}
	str = trim_buffer(str);
	return str;
}

void put_string(string str) {
	for (int i = 0; i < str.len; i++) {
		putchar(str.word[i]);
	}
}

int main() {
	while (1) {
		string str;
		char termin;
		char MyChar = 0;
		printf("Input terminator: ");
		tryAgain:
		termin = getch();
		if (termin == '\r') goto tryAgain;
		printf("%c\n", termin);
		FILE *fp;
		printf("Input type of insertion\n input from the console - C. \n input from file - F.\n");
		MyChar = getch();
		if (MyChar > 96) MyChar = MyChar - 32;
				if (MyChar == 'C') {
					fp = stdin;
					if (fp == NULL) {
						printf("File opening error!\n");
					}
					else {
						str = GetText(fp, termin);
						str = correct_str(str);

						printf("\nFinal string: \n");
						put_string(str);
					}
				}
				if (MyChar == 'F') {
					fp = fopen("Text.txt", "r");
					if (fp == NULL) {
						printf("File opening error!\n");
					}
					else {
						str = GetText(fp, termin);
						str = correct_str(str);

						printf("\nFinal string: \n");
						put_string(str);
					}
					fclose(fp);
				}
			printf("\nWould you like to repeat the calculation? \nEnter Y or N \n");
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