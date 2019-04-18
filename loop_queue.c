//循环队列
#include <stdio.h>
#include <malloc.h>
#define MAXSIZE 5
typedef int Type;

//顺序存储队列
typedef struct{
    Type *base;
    int front;
    int rear;
}LoopQueue;

//初始化，为队列分配空间
void InitQueue(LoopQueue *queue){
    queue->base = (Type*)malloc(MAXSIZE*sizeof(Type));
    if(!queue->base){
        printf("out of memory!\n");
        exit(1);
    }
    queue->front = queue->rear = 0;  //初始化时，头尾相同
}

//进队
void EnQueue(LoopQueue *queue, Type new_data){
    if((queue->rear+1) % MAXSIZE == queue->front){
        printf("the queue is full!\n");
        exit(2);
    } 
    queue->base[queue->rear] = new_data;  //头非空时，始终在第一个节点的位置
    queue->rear = (queue->rear + 1) % MAXSIZE;  //非空时，尾节点与头节点至少差一个节点，以便判断存储空间是否满
}

//出队，并返回出队值
Type DeleteQueue(LoopQueue *queue, Type delete_data){
    if(queue->front == queue->rear){
        printf("the queue is empty or somethings else is wrong!\n");
        exit(3);
    }
    delete_data = queue->base[queue->front];  //头出
    queue->front = (queue->front + 1) % MAXSIZE;  //头后移
    return delete_data;
}

//打印
void ShowQueue(LoopQueue queue){
    int position = queue.front;
    while((position+1) % MAXSIZE != queue.rear){  //到达尾节点时停止
        printf("%d\t", queue.base[position]);
        position = (position+1) % MAXSIZE;
    }
    printf("%d\t", queue.base[position]);  //打印尾节点
}

// void main(){
//     LoopQueue queue;
//     Type delete_data;
//     InitQueue(&queue);
//     for(int i=1; i<5; i++){
//         EnQueue(&queue, 2*i+3);
//     }
//     printf("the original queue is:");
//     ShowQueue(queue);
//     delete_data = DeleteQueue(&queue, delete_data);
//     printf("\nnow we delete %d from the head of the queue!\n");
//     EnQueue(&queue, 100);
//     printf("after the function EnQueue the new queue is:");
//     ShowQueue(queue);
// }