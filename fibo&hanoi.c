#include <stdio.h>
#include <malloc.h>
#define INIT_SIZE 100
#define INCREAMENT_SIZE 10
#define NEW_SIZE INIT_SIZE+INCREAMENT_SIZE
typedef enum {ERROR, OK} status;  //BOOL

//每个Hanoi节点存储起点，终点，编号
typedef struct hanoi
{
    char prior;
    char next;
    int number;
}HanoiStep;
typedef HanoiStep Type;
//做Fibonacci函数用下面的定义Type
//typedef int Type

typedef struct stack
{
    Type *base;  //栈底
    Type *top;      //栈顶，栈非空时指向顶部相邻的可用地址
    int stacksize;
}Stack;

status InitStack(Stack *stack){
    //初始化
    stack->base = (Type*)malloc(INIT_SIZE*sizeof(Type));
    if(!stack->base){
        printf("out of memory!\n");
        exit(1);
    }
    stack->top = stack->base;  //头尾初始点相同
    stack->stacksize = INIT_SIZE;
    return OK;
}

status Push(Stack *stack, Type element){
    if(stack->top-stack->base >= stack->stacksize){
        //栈满时需要开新的空间
        stack->base = (Type*)realloc(stack->base,NEW_SIZE*sizeof(Type));
        if(!stack->base){
            printf("out of memory!\n");
            exit(3);
        }
        stack->top = stack->base + stack->stacksize;
        stack->stacksize += INCREAMENT_SIZE;
    }
    *stack->top = element;  //栈顶写入新元素
    stack->top++;  //栈顶后（上）移
    return OK;
}

Type Pop(Stack *stack, Type element){
    if (stack->top == stack->base){
        printf("stack is empty!\n");
        exit(4);
    }
    element = *(--stack->top);  //栈顶元素出，栈顶后（下）移
    return element;
}

//fibo函数
// int Fibo(int n){ 
//     //fibonacci
//     int cur_number;
//     if (n==0){
//         cur_number = 0;
//     }
//     else if(n==1){
//         cur_number = 1;
//     }
//     else if(n>1){
//         cur_number = Fibo(n-2) + Fibo(n-1);
//     }
//     else{
//         printf("invalid fibo!\n");
//         exit(1);
//     }
//     return cur_number;
// }

// void GetFibo(Stack *stack, int n){
//     //将斐波那契数列存入栈中
//     for(int i=n ; i>=0; i--){
//         Push(stack, Fibo(i));
//     }
// }

//每个棋子的移动轨迹
void HanoiMove(Stack *stack, char pre, int num, char next){
    HanoiStep step;
    step.prior = pre;
    step.number = num;
    step.next = next;
    Push(stack, step);
}

void Hanoi(Stack *stack, int n, char x, char y, char z){
    if (n==1) HanoiMove(stack, x, n, z);
    else{
        //每一步都将空闲杆做为中间杆
        //先将N-1个棋子移动到中间杆上
        //然后将第N个棋子移动到目标杆上
        //以此递推
        Hanoi(stack, n-1, x, z, y); 
        HanoiMove(stack, x, n, z);
        Hanoi(stack, n-1, y, x, z);
    }
}

void Show(Stack stack){
    if(stack.top == stack.base) printf("stack is empty!\n");
    else{
        Type *current = stack.base;  //从栈底开始读
        while (current != stack.top)
        {
            printf("move %d from %c to %c\n", current->number,current->prior,current->next);
            current++;
        }
    }
}

// int main(){
//     Stack stack;
//     InitStack(&stack);
//     Hanoi(&stack, 5, 'x', 'y', 'z');
//     Show(stack);
//     return 0;
// }