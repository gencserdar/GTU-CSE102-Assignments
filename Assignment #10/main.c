#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define STACK_BLOCK_SIZE 10

typedef struct
{
    int *array;
    int currentsize;
    int maxsize;
} Stack;

int init(Stack *s);
Stack *init_return();
int push(Stack *s, int d);
int pop(Stack *s);
void moveDisk(int from, int to, int disk);
void move(Stack *first, Stack *third, int s, int d);

void main()
{
    int a = 1, b = 3, c = 2, total; // a = source pole, b = destination pole, c = middle pole
    Stack *first, *third, *second;  // poles 1, 3 and 2

    int size;
    printf("Enter Tower size: ");
    scanf("%d", &size);

    // initialize a stack for each pole
    first = init_return();
    second = init_return();
    third = init_return();

    if (size % 2 == 0) // if size is even change third pole and middle pole
    {
        int temp = b;
        b = c;
        c = temp;
    }
    total = pow(2, size) - 1; // total number of moves

    for (int i = size; i >= 1; i--)
        push(first, i);
    for (int i = 1; i <= total; i++)
    {
        if (i % 3 == 1)
            move(first, third, a, b);
        else if (i % 3 == 2)
            move(first, second, a, c);
        else if (i % 3 == 0)
            move(second, third, c, b);
    }
}
// print the disk movement
void moveDisk(int from, int to, int disk)
{
    printf("Move the disk %d from \'%d\' to \'%d\'\n", disk, from, to);
}

// to execute the movement between two poles
void move(Stack *first, Stack *third, int s, int d)
{
    // pop the disks
    int p1 = pop(first);
    int p2 = pop(third);

    // pole1 empty
    if (p1 == -999)
    {
        push(first, p2);
        moveDisk(d, s, p2); // print the movement
    }
    // pole2 empty
    else if (p2 == -999)
    {
        push(third, p1);
        moveDisk(s, d, p1); // print the movement
    }
    // top disk of pole1 > top disk of pole2
    else if (p1 > p2)
    {
        push(first, p1);
        push(first, p2);
        moveDisk(d, s, p2); // print the movement
    }
    // top disk of pole1 < top disk of pole2
    else
    {
        push(third, p2);
        push(third, p1);
        moveDisk(s, d, p1); // print the movement
    }
}
Stack *init_return()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));                // initialize stack
    stack->maxsize = STACK_BLOCK_SIZE;                            // set max size of stack
    stack->currentsize = -1;                                      // top
    stack->array = (int *)malloc(STACK_BLOCK_SIZE * sizeof(int)); // set the stack capacity

    if (init(stack) == 1) // if initializing is successful, is there any chance of failing tho?
        return stack;     // return the created stack
    else
    {
        printf("\nSTACK INITIALIZATION FAILED\n");
        exit(0);
    }
}

int init(Stack *s)
{
    if (s != NULL) // if stack pointer does not point null this means it is initialized successfully
        return 1;
    else
        return 0;
}

// push disk into a pole
int push(Stack *s, int d)
{
    if (s->currentsize == s->maxsize - 1) // if stack is full
    {
        s->maxsize = s->maxsize + STACK_BLOCK_SIZE;
        s->array = (int *)realloc(s->array, s->maxsize * sizeof(s->array));
        return 1;
    }
    else
        s->array[++(s->currentsize)] = d;
    return 0;
}

// pop disk from a pole
int pop(Stack *s)
{
    if (s->currentsize == -1) // if stack is empty
        return -999;
    else
        return s->array[(s->currentsize)--];
}