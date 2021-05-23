#include <stdio.h>
void calculator(a,b,choice)
{
 switch(choice)
 {
   case 1:printf("Addition\n Sum=%d", a+b); break;
   case 2:printf("Subtraction\n Difference=%d", a-b); break;
   case 3:printf("Multiplication\n Product=%d", a*b); break;
   case 4:printf("Division\n Quotient=%d",a/b); break;
   default:printf("error\n"); break;
 }

}
void main()
{
   int a, b, c, choice;
   printf("Enter your choice\n");
   printf(" 1. Addition\n 2. Subtraction\n 3. Multiplication\n 4.Division\n");
   scanf("%d",&choice);

   printf("Enter a and b values");
   scanf("%d %d",&a, &b);
   calculator(a,b,choice);
}

