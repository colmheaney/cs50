#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[]) {

    string name = GetString();
    int n = strlen(name);

    printf("%c", toupper(name[0]));

    for(int i = 0; i < n; i++) {
        if(name[i] == 32)
            printf("%c", toupper(name[i + 1]));
    }

    printf("\n");
}
