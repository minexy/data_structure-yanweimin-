#include <stdio.h>
#define MAXSIZE 100

typedef int T;

typedef struct {
    T data;
    int cur;  //“指针”
}StaticNode, SLinkList[MAXSIZE];

void InitSpace_SL(SLinkList space){
    //初始化备用链表,以后所有操作的数据都会存储在这里
    //可以将其理解为物理存储空间，每个节点space[i]中存储数据和其“地址”：i
    //初始化的链表在未操作前都是顺序指向的
    for(int i=0;i<MAXSIZE-1;i++) space[i].cur = i+1; //cur"指针”初始化
    space[MAXSIZE-1].cur = 0;  //最后一个“指针”指向头，也可以理解为指向空
}

int Malloc_SL(SLinkList space){
    //可以理解为库中的malloc函数
    int i= space[0].cur;
    //检查待分配的节点（空间）是否存在可用
    if(space[0].cur) space[0].cur = space[i].cur;
    return i;  //分配成功，返回节点位置i（地址）
}

//释放节点[k]，并让头节点指向[k]，以便释放的空间处于可用状态
void Free_SL(SLinkList space, int k){
    space[k].cur = space[0].cur;
    space[0].cur = k;  
}

void  Union_SL(SLinkList space,int head_a){
    int tail_a,length_a,length_b,pretail,search;
    T input_b;
    InitSpace_SL(space);  //初始化空间
    head_a = Malloc_SL(space);  //头节点，不存储内容，只起指针作用
    tail_a = head_a;
    printf("input the length of a and b:\t");
    scanf("%d%d",&length_a,&length_b);
    //录入A表
    for(int i=0;i!=length_a;i++){
        int j = Malloc_SL(space);
        printf("input for a:\t");
        scanf("%d",&space[j].data);
        space[tail_a].cur = j;
        tail_a = j;
    }
    space[tail_a].cur = 0;  //封住A表的尾节点
    for (int j=0;j!=length_b;j++){
        pretail = head_a;  //搜索位置节点的前驱指针
        search = space[head_a].cur;  //从A表的第一个节点开始搜索
        printf("input for b:\t");
        scanf("%d",&input_b);
        while(search!=space[tail_a].cur && space[search].data!=input_b){
            //搜索到A表尾或匹配到输入
            pretail = search;
            search = space[search].cur;
        }
        if(search==space[tail_a].cur){
            //未匹配到输入，新建节点存入输入，并且插入到A表尾
            int new_b = Malloc_SL(space);
            space[new_b].data = input_b;
            space[new_b].cur = space[tail_a].cur;
            space[tail_a].cur = new_b;
        }
        else{
            //匹配到输入，删除匹配到的节点，并释放其所占空间
            space[pretail].cur = space[search].cur;
            Free_SL(space, search);
            //如果匹配到的是A表尾，需纠正表A尾节点地址
            if(tail_a=search) tail_a = pretail;
        }
    }
    // printf("A & B is :\t");  //test
    // int ergodic_pointer = space[head_a].cur;
    // while(ergodic_pointer){
    //     printf("%d\t", space[ergodic_pointer].data);
    //     ergodic_pointer = space[ergodic_pointer].cur;
    // } 
}

// int main(){
//     SLinkList newspace;
//     int ssl_a;
//     Union_SL(newspace,ssl_a);
//     return 0;
// }