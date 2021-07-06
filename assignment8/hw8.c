// name: <your name here> Yaqian Yang
// email: <your email here> yang.yaqi@northeastern.edu

// please start with a copy of your hw7.c, rename it to hw.8
// and then complete the assignment

// name: <your name here>
// email: <your email here>

// format of document is a bunch of data lines beginning with an integer (rank
// which we ignore) then a ',' followed by a double-quoted string (city name)
// then a ',' followed by a double-quoted string (population) - ignore commas
// and covert to int; or (X) - convert to 0 then a lot of entries that are
// ignored

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXSTRING 200

// finite state machine states
#define STARTSTATE 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define ACCEPTSTATE 10
#define ERRORSTATE 11

// check if a character c is a digit
bool isDigit(char c)
{
  if ('0' <= c && c <= '9')
  {
    return true;
  }
  else
  {
    return false;
  }
}

// append character c to string s
void appendChar(char *s, char c)
{
  char charToStr[2]; // convert char to string
  charToStr[0] = c;
  charToStr[1] = '\0'; // put NUL to terminate string of one character
  strcat(s, charToStr);
}

// Implementation HW8
#define TABLECOUNT 400

struct dataNode
{
  char cityName[MAXSTRING];
  int value;
  int popInt;
  struct dataNode *next;
};

void addElementToTable(struct dataNode **table, struct dataNode *element)
{
  int key = element->value % TABLECOUNT;
  struct dataNode *temp = table[key];
  table[key] = element;
  element->next = temp;
}

void printTable(struct dataNode **table)
{
  for (int i = 0; i < 400; i++)
  {
    printf("TABLE[%d]:\n", i);
    struct dataNode *cur = table[i];
    while (cur != NULL)
    {
      printf("key/value: [%s] / [%d]\n", cur->cityName, cur->popInt);
      struct dataNode *tmp = cur;
      cur = cur->next;
      free(tmp); // free allocated space
    }
    printf("\n");
  }
}
// End of HW8 Implementation

int main()
{
  char inputLine[MAXSTRING]; // temporary string to hold input line
  char cityStr[MAXSTRING];   // city name
  int lineNum;               // line number (city rank)
  int popInt;                // population
  int state;                 // FSM state
  int nextChar;              // index of next character in input string
  char temp[MAXSTRING];      // temp string to build up extracted strings from input
                             // characters

  // HW8
  struct dataNode *table1[TABLECOUNT];
  struct dataNode *table2[TABLECOUNT];
  struct dataNode *table3[TABLECOUNT];
  memset(table1, 0, TABLECOUNT * sizeof(struct dataNode *));
  memset(table2, 0, TABLECOUNT * sizeof(struct dataNode *));
  memset(table3, 0, TABLECOUNT * sizeof(struct dataNode *));
  // End of HW8

  FILE *fp;
  fp = fopen("pop.csv", "r");

  if (fp != NULL)
  {
    fgets(inputLine, MAXSTRING, fp); // prime the pump for the first line

    // ***** BEGIN FINTITE STATE MACHINE *****

    // STARTSTATE: digit -> S1
    // S1: digit -> S1; , -> S2
    // S2: " -> S3
    // S3: !" -> S3; " -> S4
    // S4: , -> S5
    // S5: " -> S6; ( -> ACCEPTSTATE
    // S6: digit -> S6; , -> S6; " -> ACCEPTSTATE;
    // ACCEPTSTATE: done!
    // else go to ERRORSTATE
    //
    while (feof(fp) == 0)
    {
      nextChar = 0;
      state = STARTSTATE;
      strcpy(temp, ""); // temp = ""

      if (nextChar >= strlen(inputLine))
      {
        // if no input string then go to ERRORSTATE
        state = ERRORSTATE;
      }

      while ((state != ERRORSTATE) && (state != ACCEPTSTATE))
      {
        switch (state)
        {
        case STARTSTATE:
          // look a digit to confirm a valid line
          if (isDigit(inputLine[nextChar]))
          {
            state = S1;
            appendChar(temp, inputLine[nextChar]);
          }
          else
          {
            state = ERRORSTATE;
          }
          break;

          // ADD YOUR CODE HERE
        case S1:
          if (isDigit(inputLine[nextChar]))
          {
            appendChar(temp, inputLine[nextChar]);
          }
          else if (inputLine[nextChar] == ',')
          {
            state = S2;
            lineNum = atoi(temp);
          }
          else
          {
            state = ERRORSTATE;
          }
          break;

        case S2:
          if (inputLine[nextChar] == '\"')
          {
            state = S3;
            strcpy(cityStr, ""); // clear cityName before add new name
          }
          else
          {
            state = ERRORSTATE;
          }
          break;

        case S3:
          if (inputLine[nextChar] == '\"')
          {
            state = S4;
          }
          else
          {
            appendChar(cityStr, inputLine[nextChar]);
          }
          break;

        case S4:
          if (inputLine[nextChar] == ',')
          {
            state = S5;
          }
          else
          {
            state = ERRORSTATE;
          }
          break;

        case S5:
          if (inputLine[nextChar] == '(')
          {
            state = ACCEPTSTATE;
            popInt = 0;
          }
          else if (inputLine[nextChar] == '\"')
          {
            state = S6;
            strcpy(temp, "");
          }
          else
          {
            state = ERRORSTATE;
          }
          break;

        case S6:
          if (inputLine[nextChar] == ',')
          {
            // Do nothing
          }
          else if (isDigit(inputLine[nextChar]))
          {
            appendChar(temp, inputLine[nextChar]);
          }
          else if (inputLine[nextChar] == '\"')
          {
            state = ACCEPTSTATE;
            popInt = atoi(temp);
          }
          else
          {
            state = ERRORSTATE;
          }
          break;

        case ACCEPTSTATE:
          // nothing to do - we are done!
          break;

        default:
          state = ERRORSTATE;
          break;
        } // end switch

        // advance input
        nextChar++;

      } // end while state machine loop

      // ***** END FINITE STATE MACHINE *****

      // process the line - print out raw line and the parsed fields
      //   printf("> %.60s\n", inputLine);
      //   printf("[%.30s]: %d\n", cityStr, popInt);

      // HW8
      struct dataNode *node1 = (struct dataNode *)malloc(sizeof(struct dataNode));
      node1->value = strlen(cityStr);
      printf("%s , %d\n", cityStr, (int)strlen(cityStr));
      strcpy(node1->cityName, cityStr);
      node1->popInt = popInt;
      addElementToTable(table1, node1);
      struct dataNode *node2 = (struct dataNode *)malloc(sizeof(struct dataNode));
      int sumOfCharaterCode = 0;
      for (int i = 0; i < strlen(cityStr); i++)
      {
        sumOfCharaterCode = sumOfCharaterCode + ((int)cityStr[i]);
      }
      node2->value = sumOfCharaterCode;
      strcpy(node2->cityName, cityStr);
      node2->popInt = popInt;
      addElementToTable(table2, node2);
      struct dataNode *node3 = (struct dataNode *)malloc(sizeof(struct dataNode));
      node3->value = (int)(cityStr[0]) * (int)(cityStr[1]);
      node3->popInt = popInt;
      strcpy(node3->cityName, cityStr);
      addElementToTable(table3, node3);

      // End of HW8

      // get next line
      fgets(inputLine, MAXSTRING, fp);

    } // end while file input loop

    fclose(fp);

    // HW8
    printf("***** HASH TABLE 1 ***** \n \n =================== \n");
    printTable(table1);
    printf("\n\n\n");
    printf("***** HASH TABLE 2 ***** \n \n =================== \n");
    printTable(table2);
    printf("\n\n\n");
    printf("***** HASH TABLE 3 ***** \n \n =================== \n");
    printTable(table3);
    // End of HW8
  }
  else
  {
    printf("File not found!\n");
  }

  return 0;
}
