//enter your name here Yaqian Yang
//enter your email here yang.yaqi@northeastern.edu

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* function to encrypt the data*/
void encrypt(char text[], int key)
{
    //insert your code here
    int i;
    char ch;
    for (i = 0; text[i] != '\0'; ++i)
    {
        ch = text[i];
        if (ch >= 'a' && ch <= 'z')
        {
            ch = (ch - 'a' + key) % 26 + 'a';
            text[i] = ch;
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            ch = (ch - 'A' + key) % 26 + 'A';
            text[i] = ch;
        }
    }
}

/*function to decrypt the data*/
void decrypt(char text[], int key)
{
    int i;
    char ch;
    //insert your code here
    for (i = 0; text[i] != '\0'; ++i)
    {
        ch = text[i];
        if (ch >= 'a' && ch <= 'z')
        {
            ch = (ch - 'a' - key) % 26 + 'a';
            text[i] = ch;
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            ch = (ch - 'A' - key) % 26 + 'A';
            text[i] = ch;
        }
    }
}

/*----------- Main program---------------*/
int main()
{
    char text[20];
    /*Input string */
    printf("Enter the message:  ");
    scanf("%s", text);
    printf("text input   = %s\n", text);
    /*call function to encrypt the data*/
    encrypt(text, 3);
    printf("Encrypted value = %s\n", text);
    /*call function to decrypt the data*/
    decrypt(text, 3);
    printf("Decrypted value = %s\n", text);

    return 0;
}
