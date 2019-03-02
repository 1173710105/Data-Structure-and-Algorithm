#include <stdio.h>
#include <stdlib.h>
#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define MAX 1025
//���
struct node
{
    int data; //�ؼ���
    struct node *lchild;  //������
    struct node *rchild;  //������
};
//���ڵ�
typedef struct
{
    struct node * child; //���ڵ�
}ROOT;
typedef struct node NODE;
typedef struct node AVLT;
typedef int boolean;
typedef NODE *BST;



NODE *new_Node(int R);
void AVLInsert(AVLT **PT ,int R);
void set_up_BST_TREE(ROOT *root,char *filename);
ROOT new_Root();
void PreOrder(AVLT *BT);
NODE *search(int k, AVLT *F,int *depth);
void Delete(int k ,AVLT **F);
void delete_Node(NODE *node);
int DeleteMin(AVLT **F);
int Depth(AVLT *T);  //������������
boolean IsAVL(AVLT *T);   //�ж�ƽ�������
void Adjust_BF(AVLT **T);
void Adjust_Tree(AVLT **T);
void AVL_Delete(int R, ROOT *root);
void InOrder(AVLT *BT);
void destory_tree(AVLT *BT);

int set_up_Binary(char *filename,int **array);
void SelectSort_increase(int max,int **array);
int Binary_Search(int k, int max, int *depth, int *array);

void analyse_btree_search(AVLT *BT, char *filename);
void analyse_binary_search(int *array,int max, char *filename);
int menu();

int analyse_btree_search_failure(AVLT *BT,int depth);




int main()
{
    int choice;
    ROOT root = new_Root();
    int *array;
    int max;
    int tree_flag = 0;
    int array_flag = 0;
    int data;
    int depth=0;
    NODE *node;

    while(1)
    {
        choice = menu();
        switch(choice)
        {
        case 1:
            set_up_BST_TREE(&root,"increase.txt");
            tree_flag = 1;
            printf("�������Ҷ������ɹ�\n");
            system("pause");
            system("cls");
            break;
        case 2:
            array = (int *)malloc(sizeof(int)*MAX);
            max = set_up_Binary("increase.txt",&array);
            array_flag = 1;
            printf("�����۰�����б�ɹ�\n");
            system("pause");
            system("cls");
            break;
        case 3:
            if(tree_flag)
            {
                printf("��������Ҫ����Ľڵ���Ϣ��");
                scanf("%d",&data);
                AVLInsert(&(root.child),data);
                printf("����ڵ�ɹ�\n");
            }
            else
                printf("���󣺲��Ҷ�����δ����\n");
            system("pause");
            system("cls");
            break;
        case 4:
            if(tree_flag)
            {
                printf("��������Ҫɾ���Ľڵ���Ϣ��");
                scanf("%d",&data);
                Delete(data,&(root.child));
                printf("ɾ���ڵ�ɹ�\n");
            }
            else
                printf("���󣺲��Ҷ�����δ����\n");
            system("pause");
            system("cls");
            break;
        case 5:
            if(tree_flag)
            {
                printf("��������Ҫ���ҵĽڵ���Ϣ��");
                scanf("%d",&data);
                depth = 0;
                node = search(data,root.child,&depth);
                if(node)
                {
                    printf("���ҵ����ýڵ���ϢΪ��%d\n",node->data);
                    printf("���Ϊ%d\n",depth);
                }
                else
                {
                    printf("�޸ýڵ���Ϣ\n");
                    printf("���Ϊ%d\n",depth);
                }
            }
            else
                printf("���󣺲��Ҷ�����δ����\n");
            system("pause");
            system("cls");
            break;
        case 6:
            if(tree_flag)
            {
                printf("\n��������\n");
                InOrder(root.child);
            }
            else
                printf("���󣺲��Ҷ�����δ����\n");
            system("pause");
            system("cls");
            break;
        case 7:
            if(tree_flag)
            {
                printf("\n���Ҷ�����ʱ�����ܷ��������");
                printf("\n�������������Ľ����\n");
                destory_tree(root.child);
                root.child = NULL;
                set_up_BST_TREE(&root,"random.txt");
                analyse_btree_search(root.child,"increase.txt");
                set_up_BST_TREE(&root,"random.txt");
                int failure = analyse_btree_search_failure(root.child,1);
                printf("����ʧ��ƽ�����ҳ���=%.3f\n",((float)failure)/(MAX-1));
                destory_tree(root.child);
                root.child = NULL;
                set_up_BST_TREE(&root,"increase.txt");
                printf("\n˳������������Ľ����\n");
                analyse_btree_search(root.child,"increase.txt");
                failure = analyse_btree_search_failure(root.child,1);
                printf("����ʧ��ƽ�����ҳ���=%.3f\n",((float)failure)/(MAX-1));
            }
            else
                printf("���󣺲��Ҷ�����δ����\n");
            system("pause");
            system("cls");
            break;
        case 8:
            if(array_flag)
            {
                printf("\n�۰����ʱ�����ܷ��������\n");
                analyse_binary_search(array,max,"random.txt");
            }
            else
                printf("�����۰�����б�δ����\n");
            system("pause");
            system("cls");
            break;
        case 9:
            free(array);
            destory_tree(root.child);
            exit(0);
            break;
        default:
            break;
        }
    }
    return 0;
}
int menu()
{
    int choice;
    printf("������ʵ�ֵĹ���:\n");
    printf("1.�������������\n");
    printf("2.�����۰�����б�\n");
    printf("3.�ڲ��Ҷ������в���ڵ�\n");
    printf("4.�ڲ��Ҷ�������ɾ���ڵ�\n");
    printf("5.�ò��Ҷ���������һ���ڵ�\n");
    printf("6.�ò��Ҷ���������\n");
    printf("7.���������������еĲ��Ҷ������Ĳ���ʱ������\n");
    printf("8.�����۰���ҵĲ���ʱ������\n");
    printf("9.�˳�\n");
    printf("���������ѡ��:");
    scanf(" %d",&choice);
    return choice;
}
void PreOrder(AVLT *BT)
{
    if(BT)
    {
        printf("%d\t",BT->data);
        if(BT->lchild)
            printf("%d->%d\t",BT->data,BT->lchild->data);
        else
            printf("\t");
        if(BT->rchild)
            printf("%d->%d\t",BT->data,BT->rchild->data);
        else
            printf("\t");
        printf("\n");
        PreOrder(BT->lchild);
        PreOrder(BT->rchild);
    }
}
void InOrder(AVLT *BT)
{
    if(BT)
    {
        InOrder(BT->lchild);
        printf("%d ",BT->data);
        InOrder(BT->rchild);
    }
}
void set_up_BST_TREE(ROOT *root,char *filename)
{
    FILE *fp;
    fp = fopen(filename,"r");
    if(fp==NULL)
    {
        printf("���ļ�ʧ��\n");
        exit(1);
    }
    int num;
    while(!feof(fp))
    {
        fscanf(fp,"%d\n",&num);
        AVLInsert(&(root->child),num);
    }
    fclose(fp);
}
void AVLInsert(AVLT **T ,int R)
{
    //���ڵ���Ϣ��ͬ����������
    if(!(*T)) //��ն������в���Ԫ��
    {
        (*T) = new_Node(R);
    }
    else if(R<(*T)->data) //���������ϲ���
    {
        AVLInsert(&((*T)->lchild), R);
    }
    else if(R>(*T)->data)     //���������ϲ���
    {
        AVLInsert(&((*T)->rchild), R) ;
    }
}
ROOT new_Root()
{
    ROOT root;
    root.child = NULL;
    return root;
}
NODE *new_Node(int R)
{
    NODE *node = (NODE*)malloc(sizeof(NODE));
    node->data = R;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}
void analyse_btree_search(AVLT *BT, char *filename)
{
    FILE *fp;
    fp = fopen(filename,"r");
    if(fp==NULL)
    {
        printf("���ļ�ʧ��\n");
        exit(1);
    }
    int num;
    int succee_depth;
    int succee_mean = 0;
    while(!feof(fp))
    {
        fscanf(fp,"%d\n",&num);
        succee_depth = 0;
        search(num,BT,&succee_depth);
        succee_mean += succee_depth;
    }
    fclose(fp);
    printf("���ҳɹ�ƽ�����ҳ���=%.3f\n",((float)succee_mean)/((float)(MAX-1)));
}
void analyse_binary_search(int *array,int max, char *filename)
{
    FILE *fp;
    fp = fopen(filename,"r");
    if(fp==NULL)
    {
        printf("���ļ�ʧ��\n");
        exit(1);
    }
    int num;
    int succee_depth;
    int failure_depth;
    int succee_mean = 0;
    int failure_mean = 0;
    while(!feof(fp))
    {
        fscanf(fp,"%d\n",&num);
        succee_depth = 0;
        failure_depth = 0;
        Binary_Search(num,max,&succee_depth,array);
        succee_mean += succee_depth;
        //Binary_Search(num-1,max,&failure_depth,array);
        failure_mean+=succee_depth+1;
    }
    fclose(fp);
    printf("���ҳɹ�ƽ�����ҳ���=%.3f\n",((float)succee_mean)/((float)(MAX-1)));
    printf("����ʧ��ƽ�����ҳ���=%.3f\n",((float)failure_mean)/((float)(MAX-1)));

}
int analyse_btree_search_failure(AVLT *BT,int depth)
{
    if(BT->lchild==NULL&&BT->rchild==NULL)
    {
        return depth*2;
    }
    else if(BT->lchild==NULL&&BT->rchild!=NULL)
    {
        return depth + analyse_btree_search_failure(BT->rchild,depth+1);
    }
    else if(BT->lchild!=NULL&&BT->rchild==NULL)
    {
        return depth + analyse_btree_search_failure(BT->lchild,depth+1);
    }
    else
    {
        return analyse_btree_search_failure(BT->lchild,depth+1) + analyse_btree_search_failure(BT->rchild,depth+1);
    }
}
NODE *search(int k, AVLT *F,int *depth)
{
    NODE *p = F;
    if ( p == NULL )
    {
        (*depth)++;
        return NULL;
    }
    else if( k == p->data)
    {
        (*depth)++;
        return p;
    }
    else if( k < p->data )
    {
        (*depth)++;
        return search(k, p->lchild,depth);
    }
    else if( k > p->data)
    {
        (*depth)++;
        return search(k, p->rchild,depth);
    }
}
void Delete(int k ,AVLT **F)
{
    if((*F) != NULL)
    {
        if (k < (*F)->data)
            Delete(k, &((*F)->lchild)) ;
        else if(k > (*F)->data)
            Delete(k, &((*F)->rchild));
        else
        {
            NODE *node;
            if ((*F)->rchild == NULL)
            {
                node = *F;
                (*F) = (*F)->lchild;
                delete_Node(node);
            }
            else if((*F)->lchild == NULL)
            {
                node = *F;
                (*F) = (*F)->rchild;
                delete_Node(node);

            }
            else
            {
                (*F)->data = DeleteMin(&((*F)->rchild));
            }
        }
    }
}
int DeleteMin(AVLT **F)
{
    int temp;
    AVLT *p;
    if((*F)->lchild == NULL )
    {
        p = *F;
        temp = (*F)->data;
        (*F) = (*F)->rchild;
        delete_Node(p);
        return temp;
    }
    else
    {
        temp = DeleteMin(&((*F)->lchild));
        return temp;
    }
}
void delete_Node(NODE *node)
{
    free(node);
}
int Depth(AVLT *T)  //������������
{
    int ldepth,rdepth;
    if(T==NULL)
        return(0);
    else
    {
        ldepth=Depth(T->lchild);
        rdepth=Depth(T->rchild);
        if(ldepth>rdepth)
            return(ldepth+1);
        else
            return(rdepth+1);
   }
}
int set_up_Binary(char *filename,int **array)
{
    FILE *fp;
    fp = fopen(filename,"r");
    if(fp==NULL)
    {
        printf("���ļ�ʧ��\n");
        exit(1);
    }
    int num;
    int max = 0;
    while(!feof(fp))
    {
        fscanf(fp,"%d\n",&num);
        (*array)[max] = num;
        max++;
    }
    fclose(fp);
    SelectSort_increase(max,array);
    return max;
}
void SelectSort_increase(int max,int **array)
{
    int i, j, minindex, min, tempmin,temp;
    for(i=0;i<max-1;i++)
    {
        minindex = i;
        min = (*array)[minindex];
        for(j=i+1;j<max;j++)
        {
            tempmin = (*array)[j];
            if(tempmin<min)
            {
                minindex = j;
                min = tempmin;
            }
        }
        if(minindex!=i)
        {
            temp = (*array)[i];
            (*array)[i] = (*array)[minindex];
            (*array)[minindex] = temp;
        }
    }
}
int Binary_Search(int k, int max, int *depth, int *array)
{
    int  low , up , mid ;
    low = 0;
    up = max;
    while(low<=up)
    {
        mid = (up-low)/2 + low;
        if ( array[mid] == k)
        {
            (*depth)++;
            return mid ;
        }
        else if ( array[mid] > k )
        {
            (*depth)++;
            up = mid - 1 ;
        }
        else
        {
            (*depth)++;
            low = mid + 1 ;
        }
    }
    return -1;
}
void destory_tree(AVLT *BT)
{
    if(BT==NULL)
        return;
    else if(BT->lchild==NULL&&BT->rchild==NULL)
    {
        delete_Node(BT);
    }
    else
    {
        destory_tree(BT->lchild);
        destory_tree(BT->rchild);
        delete_Node(BT);
    }
}
