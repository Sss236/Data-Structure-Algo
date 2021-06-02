//enter your name here Yaqian Yang
// enter your email here yang.yaqi@northeastern.edu

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 8

int queue[N];
int front = -1;
int rear = -1;
int elementcount = 0;

int peek() {
   return queue[front]; // To see the data at the front of the queue//
}
bool isempty()
{
    return elementcount==0; //checking if the queue is empty
}

bool isfull()
{
    
    return elementcount==N;// checking if the queue is full
}


int enqueue(int data)
{
//insert your code here
 if(!isfull()){
   rear = (rear+1)%N;
   queue[rear]=data;
   printf("Enqueued data is:%d\n",queue[rear]);
   elementcount++;
   if(elementcount == 1){
      front = rear;
   }
   return 0;
  }else{
    printf("Queue is full");
  }
}


void dequeue()
{
    
    //insert your code here
     if(!isempty()){
       printf("Dequeued data is:%d\n",queue[front]);
       front = (front + 1)%N;
       elementcount--;
    }
}
void display()
{
    
    
    //insert your code here
    if(!isempty()){
      printf("the queue is:");
      int i = front;
      while(i != rear ){
        printf("%d ",queue[i]);
        i = (i + 1)%N;
      }
    }
    printf("\n");
}

int main()
    {
   /* insert 8 items */
enqueue(11);
enqueue(22);
enqueue(33);
enqueue(44);
enqueue(66);
enqueue(77);
enqueue(88);
enqueue(99);
display();
printf("\n");
dequeue();
dequeue();
dequeue();
dequeue();
display();
    
printf("\n Element at front: %d\n",peek());
printf(" \nTotal number of elements in the queue are %d\n", elementcount);

        
return 0;
    }

