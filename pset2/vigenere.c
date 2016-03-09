#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void vigenere_encrypt(string p, string k);

int main(int argc, string argv[]) {

	if (argc == 2) {

		//get keyword
		string key = argv[1];

		//check if keyword contains any non-alphanumeric chars
		for (int i = 0; i < argv[1][i]; i++) {
			if (!(isalpha(argv[1][i]))) {
				printf("Usage: vigenere [key]\n");
				return 1;
			}
		}

		//get phrase to encrypt
		string phrase = GetString();

		//encrypt phrase 
	vigenere_encrypt(phrase, key);

	} else {
		printf("Usage: vigenere [key]\n");
		return 1;
	}
	return 0;
}

//responsible for encrypting phrase and printing cipher
void vigenere_encrypt(string p, string k) {

	int pLen = strlen(p);
	int kLen = strlen(k);
	int ki = 0;
	int offset = 0;
	char ch;

	for (int i = 0; i < pLen; i++) {

		//determine whether keyword char is upper or lower
		if (isupper(k[ki])) {
			offset = 65;
		} else if (islower(k[ki])) {
			offset = 97;
		}

		//print the cipher
		if (isupper(p[i]))	{	
			ch = (p[i] + (k[ki] - offset) - 65) % 26 + 65;	
			ki = (ki + 1) % kLen;
			printf("%c", ch);
		}
		else if (islower(p[i])) {
			ch = (p[i] + (k[ki] - offset) - 97) % 26 + 97;
			ki = (ki + 1) % kLen;
			printf("%c", ch);
		}
		else {
			ch = p[i];
			printf("%c", ch);
		}
	}
	printf("\n");
}
