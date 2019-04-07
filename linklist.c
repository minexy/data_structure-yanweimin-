#include <stdio.h>
#include <ctype.h>
#include <malloc.h>

typedef int T; //方便维护修改

typedef struct node
{
    T Element;
    struct node *Link;
} Node;typedef Node *List;

T *InputElement()
{
    static T a;
    scanf("%d", &a);
    return &a;
}

//通过读取键盘输入建立新节点
Node *NewNode()
{
    Node *p;
    p = (Node *)malloc(sizeof(Node)); //为新节点分配空间
    if (!p)
    { //分配失败
        fprintf(stderr, "the memory is full!\n");
        exit(1);
    }
    p->Element = *InputElement();
    p->Link = NULL;
    return p;
}

//指定参数建立新节点
Node *PraNode(T element)
{
    Node *p;
    p = (Node *)malloc(sizeof(Node));
    if (!p)
    {
        fprintf(stderr, "the memory is full!l\n");
        exit(1);
    }
    p->Element = element;
    p->Link = NULL;
    return p;
}

//头插
List BuildList()
{
    Node *p;                                 // new Node
    List first = (List)malloc(sizeof(Node)); //first不存储数据，只指向第一个节点
    first->Link = NULL;  //使用前须初始化
    Node *tail = NULL; //tail为尾节点
    char input;
    printf("Insert new elements to build a list?y/n\n");
    input = getchar();
    while (tolower(input) != 'n')
    {
        p = NewNode();
        if (!first->Link)
            first->Link = p; //first指针指向list首地
        //将p接入List（地址），再移动tail节点至尾部（即p节点）
        //基本动作：接入新节点，指针后移
        else
            tail->Link = p;
        tail = p;
        printf("another element?y/n\n");
        while (getchar() != '\n');
        input = getchar();
    }
    input = getchar();
    printf("inputting is over!\n");
    return first; //返回list首地址
}

//尾插
List BuildReverse(){
    Node *p;
    List first = (List)malloc(sizeof(Node));
    first->Link = NULL;
    char input;
    printf("Insert new elements to build a list?y/n\n");
    input = getchar();
    while (tolower(input) != 'n'){
        p = NewNode();
        //新节点接入链表，头指针前移
        p->Link = first->Link;
        first->Link = p;
        printf("another element?y/n\n");
        while (getchar() != '\n');
        input = getchar();
    }
    return first;
}

int GetLength(List list)
{
    int length = 0;
    for (; list; list = list->Link)
    {
        length++;
    }
    return length;
}

//在指定位置插入元素T,当前位置原元素后移
List Insert(List list, int position, T item)
{
    int step = 0;
    Node *tail = list; //指定位置前一个节点
    Node *newnode = PraNode(item);
    //找到指定位置前一个节点，然后修改指针指向
    //循环跳出条件：①遍历list，未找到指定位置②找到指定位置
    while (tail && step != (position - 1))
    {
        tail = tail->Link;
        step++;
    }
    if (step == (position - 1))  //找到正确插入位置
    {
        newnode->Link = tail->Link;
        tail->Link = newnode;
        printf("inserting is succeeded!\n");
    }
    else
        printf("inserting is forbidden! invalid position!\n");
    return list;
}

//删除指定位置的节点
List Delete(List list, int position)
{
    int step = 0;
    if (!list->Link)
    {
        printf("list is empty!\n");
        exit(1);
    }
    Node *tail = list;
    //找到指定位置的前一个节点，修改指针指向
    while (tail->Link && step < (position - 1))
    {
        tail = tail->Link;
        step++;
    }
    if (step == (position - 1) && tail->Link)
        //找到指定位置的前驱节点，并且此节点不是尾节点才能正确删除
        tail->Link = tail->Link->Link;
    else
        printf("invalid position!\n");

    return list;
}

//合并有序链表
List MergeList(List la, List lb){
    List pa,pb,pc,lc;
    pa = la->Link;
    pb = lb->Link;
    lc = la;  //lc使用la地址，函数结束时，la链表与合并后的lc相同
    pc = la;
    while(pa&&pb){
        if(pa->Element <= pb->Element){
            pc->Link = pa;
            pc = pa;
            pa = pa->Link;
        }
        else{
            pc->Link = pb;
            pc = pb;
            pb = pb->Link;
        }
    }
    pc->Link = pa?pa:pb;
    free(lb);  //释放lb头指针后，链表lb销毁
    return lc;    
}

void ShowList(List list)
{
    if(!list->Link) printf("empty!\n");
    Node *tail = list->Link;
    for (; tail; tail = tail->Link)
    {
        printf("%d\t", tail->Element);
    }
}

// int main()
// {
    
//     return 0;
// }