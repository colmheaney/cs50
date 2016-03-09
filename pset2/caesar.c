#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void caesar_encrypt(string p, int k);

int main(int argc, string argv[]) {

	if (argc == 2) {

		//get key
		int key = atoi(argv[1]);

		//get phrase to encrypt
		string phrase = GetString();

		//encrypt phrase 
		caesar_encrypt(phrase, key);

	} else {
		printf("Usage: ceasar [key]\n");
		return 1;
	}
	return 0;
}

//responsible for encrypting phrase and printing cipher
void caesar_encrypt(string p, int k) {

	int pLen = strlen(p);
	char ch;

	for (int i = 0; i < pLen; i++) {

		if (isupper(p[i]))	{	
			ch = (p[i] + k - 65) % 26 + 65;	
			printf("%c", ch);
		}
		else if (islower(p[i])) {
			ch = (p[i] + k - 97) % 26 + 97;
			printf("%c", ch);
		}
		else {
			ch = p[i];
			printf("%c", ch);
		}
	}
	printf("\n");
}
