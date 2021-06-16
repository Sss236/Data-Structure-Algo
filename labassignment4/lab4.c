//enter your name here : Yaqian Yang
//enter your email here : yang.yaqi@northeastern.edu
#include<stdio.h>

int a;
int factorial;


int fact(int n)
{
    if(n == 0){
        return 1;
    }else{
        return (n*fact(n-1));
    }
    
}

int main()
{
    scanf("%d", &a);
    factorial = fact(a);
    printf("%d",factorial);
    return 0;
}


