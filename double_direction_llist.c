#include <stdio.h>
#include <malloc.h>
typedef int T;

typedef struct doublelinknode
{   //双向链表，定义节点前后指针
    T data;
    struct doublelinknode *next;
    struct doublelinknode *prior;  
}DLNode, *DLList;

//新建链表，其中头节点只有地址，不包含数据
//每个新建节点都需要修改4个指针2*（prior+next）
DLList Build(){
    DLList new_list, tail = NULL, new_node = NULL;
    new_list = (DLList)malloc(sizeof(DLNode));
    new_list->next = new_list;
    new_list->prior = new_list;
    for(int i=1; i<6; i++){  //通过自定义循环建表
        new_node = (DLList)malloc(sizeof(DLNode));
        if(!new_node){
            printf("memory_allocation fault!\n");
            exit(3);
        }
        new_node->data = 2*i+5;
        if(new_list->next == new_list){
            new_list->next = new_node;
            new_list->prior = new_node;
            new_node->prior = new_list;
            new_node->next = new_list;
            tail = new_node;
        }
        else{
            //当链表非空时，每当在表尾插入一个新节点时，都要修改头节点的前驱
            tail->next = new_node;
            new_node->next = new_list;
            new_node->prior = tail;
            new_list->prior = new_node; //头节点前驱
            tail = new_node;
        }
    }
    return new_list;
}

void Insert(DLList list, int position, T data){
    DLList search_pointer = list, new_node;  //搜索指针
    int now_position = 0; //搜索起点：头节点
    if(position<1) { //非法位置
        printf("******invalid position!*********\n");
        exit(2);
    }
    while(now_position < position-1 && search_pointer->next != list){
        //找到插入位置前驱或搜索到表尾
        search_pointer = search_pointer->next;
        now_position++;
    }
    if(now_position < position-1 && search_pointer->next == list) {
        //搜索位置合法（即搜索位置仍然未到指定位置前驱）但已搜索到表尾
        //插入位置非法
        printf("*******invalid positon!all are over!88*********\n");
        exit(1);    
    }
    else{
        new_node = (DLList)malloc(sizeof(DLNode));
        if(!new_node){
            printf("memory_allocation fault!\n");
            exit(4);
        }
        new_node->data = data;
        new_node->next = search_pointer->next;
        search_pointer->next->prior = new_node;
        search_pointer->next = new_node;
        new_node->prior = search_pointer;
    }
}

void Show(DLList list){
    DLList tail = list;
    if(list->next == list) printf("list is empty!\n");
    else{
        while(tail->next != list){
         printf("%d\t",tail->next->data);
         tail = tail->next;  
        }
    }
}

// void main(){
//     DLList test_list;
//     printf("\n********list_building begins***********\n");
//     test_list = Build();
//     printf("*********building is done!******\n");
//     printf("the list is:\n");
//     Show(test_list);
//     printf("\n\n**********inserting begins************\n");
//     Insert(test_list, 6, 100);
//     printf("inserting is done!\nthe new list is:\n");
//     Show(test_list);
// }