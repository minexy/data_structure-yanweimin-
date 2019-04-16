#include <stdio.h>
#include <malloc.h>
typedef int Type;

//链表节点
typedef struct linknode
{
    Type data;
    struct linknode *next;
}LinkNode, *QueueNode;

//定义队列，其中元素按链表形式存储
typedef struct queue{
    QueueNode front;  //队头
    QueueNode rear;  //队尾
}Queue;

QueueNode NewNode(){
    //建立新的链表存储节点
    QueueNode newnode = (QueueNode)malloc(sizeof(LinkNode));
    if(!newnode){
        printf("out of memory!\n");
        exit(1);
    }
    newnode->next = NULL;  //新节点next指针初始化
    return newnode;
}

//队列初始化
void InitQueue(Queue *queue){
    QueueNode node = NewNode();
    queue->front = node;
    queue->rear = queue->front;
}

//插入(队尾)
void EnQueue(Queue *queue, Type newdata){
    //从队尾插入
    QueueNode newnode = NewNode();
    newnode->data = newdata;
    queue->rear->next = newnode; 
    queue->rear = newnode;
}

//删除(队头)
Type DeleteQueue(Queue *queue, Type del_item){
    //从头开始删除，遵循先进先出的顺序
    if(queue->rear == queue->front){
        printf("empty queue!\n");
        exit(2);
    }
    QueueNode  del_node;  //要删除的节点
    del_node = queue->front->next;
    del_item = del_node->data;
    queue->front->next = del_node->next; 
    if(queue->rear == del_node) queue->rear = queue->front;  //队列中只有一个元素，删除后变空
    free(del_node);  //释放删除节点的空间
    return del_item;
}

//销毁队列(包括队头，即整个队列的地址空间都要释放)
void DestroyQueue(Queue *queue){
    //从队头开始销毁
    while (queue->front)
    {
        queue->rear = queue->front->next;
        free(queue->front);
        queue->front = queue->rear;
    }    
}

//清空队列
void ClearQueue(Queue *queue){
    QueueNode node;
    while (queue->front->next)
    {
        node = queue->front->next;
        queue->front->next = node->next;
        free(node);  //销毁每个有内容的节点
    }
    queue->rear = queue->front;  //最后头尾重合
}

//打印队列
void ShowQueue(Queue queue){
    QueueNode  next_node = queue.front->next;
    if(queue.front == queue.rear) printf("empty queue!\n");
    else{
        while(next_node){
            printf("%d\t", next_node->data);
            next_node = next_node->next;
        }
    }
}

// int main(){
//     Queue new_queue;
//     Type delete_item;
//     InitQueue(&new_queue);
//     for(int i=1; i<5; i++){
//         EnQueue(&new_queue, 2*i+3);
//     }
//     printf("the original queue is: ");
//     ShowQueue(new_queue);
//     EnQueue(&new_queue, 100);
//     printf("\nnow we insert 100 into the queue: ");
//     ShowQueue(new_queue);
//     delete_item = DeleteQueue(&new_queue, delete_item);
//     printf("\nnow we delete %d from the head of the queue!\n", delete_item);
//     delete_item = DeleteQueue(&new_queue, delete_item);
//     printf("now we delete %d from the head of the queue!\n", delete_item);
//     ClearQueue(&new_queue);
//     printf("after function ClearQueue,the queue is an ");
//     ShowQueue(new_queue);
//     return 0;
// } 