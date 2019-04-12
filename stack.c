#include <stdio.h>
#include <malloc.h>
#define INIT_SIZE 100
#define INCREAMENT_SIZE 10
#define NEW_SIZE INIT_SIZE+INCREAMENT_SIZE
#define FORMATS 8  //8进制

typedef int Type;
typedef enum {ERROR, OK} status;  //BOOL

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

Type GetTop(Stack *stack){
    Type top_element;
    if(stack->base == stack->top){
        printf("stack is empty!\n");
        exit(2);
    }
    top_element = *(stack->top-1);
    return top_element;
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

status Clear(Stack *stack){
    stack->top = stack->base;
    return OK;
}

void Show(Stack stack){
    if(stack.top == stack.base) printf("stack is empty!\n");
    else{
        Type *current = stack.top-1;
        while (current != stack.base-1)
        {
            printf("%d\t", *current);
            current--;
        }
    }
}

void formats_conver(Type number){
    //进制转换
    Stack stack_convert;
    InitStack(&stack_convert);
    while(number){
        Push(&stack_convert, number%FORMATS);
        number = number/FORMATS;
    }
    Show(stack_convert);
}

// int main(){
//     int conver_num = 1334;
//     formats_conver(conver_num);
//     return 0;
// }