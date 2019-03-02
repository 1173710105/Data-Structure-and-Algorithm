#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NULL ((void *)0)

struct PolyNode
{
    float coef;//��¼ϵ��
    int exp;//��¼ָ��
    struct PolyNode *next ;//��¼��һ�ڵ��
};

typedef struct PolyNode* PolyPointer;
typedef struct PolyNode* Position;
PolyPointer PolyMult(PolyPointer a, PolyPointer b, PolyPointer available);// �˷�
PolyPointer New_PolyNode_avail(PolyPointer available);
PolyPointer Avail_Insert(float coef, int exp, Position c, PolyPointer available);
PolyPointer New_PolyNode();
PolyPointer Create_Polynomial(char *filename,PolyPointer available);
float calculate(float x, PolyPointer List);
PolyPointer PolyAdd (PolyPointer a, PolyPointer b, PolyPointer available);
PolyPointer PolySub (PolyPointer a, PolyPointer b, PolyPointer available);
void Delete_Poly(PolyPointer L);
void PolyDiv(PolyPointer quotient, PolyPointer remainder,PolyPointer a, PolyPointer b, PolyPointer available);
void Destroy_List(PolyPointer p);
void Print_Poly(PolyPointer p);
void recycle_avail(PolyPointer p, PolyPointer available);
void Write_Polynomial_To_File(char *filename,PolyPointer head);


int main()
{
    char *filename1 = "coef_exp1.txt";
    char *filename2 = "coef_exp2.txt";
    PolyPointer available = New_PolyNode();//���ڴ洢���ÿռ�
    PolyPointer head1 = Create_Polynomial(filename1,available);//���ض���ʽ1
    PolyPointer head2 = Create_Polynomial(filename2,available);//���ض���ʽ2
    float x0 = 0.0f;
    float result1 = calculate(x0,head1);
    float result2 = calculate(x0,head2);
    PolyPointer head3 = PolyAdd(head1,head2,available);
    PolyPointer head4 = PolySub(head1,head2,available);
    PolyPointer head5 = PolyMult(head1,head2,available);
    Write_Polynomial_To_File("coef_exp3.txt",head5);
    PolyPointer quotient = New_PolyNode_avail(available);
    PolyPointer remainder = New_PolyNode_avail(available);
    PolyDiv(quotient,remainder,head1,head2,available);
    printf("����ʽ1��");
    Print_Poly(head1);
    printf("����ʽ2��");
    Print_Poly(head2);
    printf("����ʽ1�ڵ�X=%.1f��ֵΪ��%.1f\n",x0,result1);
    printf("����ʽ2�ڵ�X=%.1f��ֵΪ��%.1f\n",x0,result2);
    printf("����ʽ1 + ����ʽ2 ��ֵΪ��");
    Print_Poly(head3);
    printf("����ʽ1 - ����ʽ2 ��ֵΪ��");
    Print_Poly(head4);
    printf("����ʽ1 * ����ʽ2 ��ֵΪ��");
    Print_Poly(head5);
    printf("����ʽ1 / ����ʽ2 ��ֵΪ��\n");
    printf("��  Ϊ��");
    Print_Poly(quotient);
    printf("����Ϊ��");
    Print_Poly(remainder);

    //Write_Polynomial_To_File("coef_exp3.txt",head3);
    Destroy_List(head1);
    Destroy_List(head2);
    Destroy_List(head3);
    Destroy_List(head4);
    Destroy_List(head5);
    Destroy_List(quotient);
    Destroy_List(remainder);
    Destroy_List(available);//ɾ������Ŀ��ÿռ�

    return 0;
}

/*������˳�򴴽�����ʽ������ʽ�������ļ��ж�ȡ*/
PolyPointer Create_Polynomial(char *filename,PolyPointer available)
{
    FILE *fp;
    fp = fopen(filename,"r");
    if(fp==NULL)
    {
        printf("���ļ�ʧ��\n");
        return NULL;
    }
    PolyPointer head, p;
    head = New_PolyNode();//����ʽͷָ��
    float coef;
    int exp;
    while(!feof(fp))
    {
        p = head;
        fscanf(fp,"%f\t%d\n",&coef,&exp);
        //printf("%f\t%d\n",coef,exp);
        while((p->next!=NULL)&&((p->next->exp)>=exp))//�ҵ���ȷ�Ĳ���λ��
            p = p->next;
        Avail_Insert(coef,exp,p,available);//��ָ��λ�ò���һ���ڵ�
    }
    fclose(fp);
    return head;
}

/*����һ���½ڵ㣬���ҽ�����ڵ��ʼ��*/
PolyPointer New_PolyNode()
{
    PolyPointer node = (PolyPointer)malloc(sizeof(struct PolyNode));
    node->coef = 0.0;
    node->exp = 0;
    node->next = NULL;
    return node;
}

/*������ʽд�뵽�ļ�֮��ȥ*/
void Write_Polynomial_To_File(char *filename,PolyPointer head)
{
    FILE *fp;
    fp = fopen(filename,"w");
    if(fp==NULL)
    {
        printf("���ļ�ʧ��\n");
        return;
    }
    PolyPointer p = head;
    while(p->next)
    {
        fprintf(fp,"%.2f\t%d\n",p->next->coef,p->next->exp);
        p = p->next;
    }
    fclose(fp);
}
/*�������ʽ�ڵ�x=x0��ֵ*/
float calculate(float x, PolyPointer List)
{
    float result = 0;
    PolyPointer p;
    p = List;
    while(p->next)
    {
        result += (p->next->coef)*pow(x,p->next->exp);
        p = p->next;
    }
    return result;
}
/*�Ƚ������ڵ��ֵ*/
char  Compare (int x, int y)
{
    char c;
    if( x == y )
        c = '=';
    else if( x > y )
        c = '>';
    else
        c = '<';
    return c;
}

/*���б�β������һ���ڵ�*/
/*PolyPointer Attch(float coef, int exp, PolyPointer d)
{
    PolyPointer x;
    x = New_PolyNode();
    x->coef = coef;
    x->exp = exp;
    d->next= x;
    return  x;
}*/
/*��������ʽ���*/
PolyPointer PolyAdd (PolyPointer a, PolyPointer b, PolyPointer available)
{
    PolyPointer p, q, d, c;
    float y ;
    p = a->next;
    q = b->next;
    c = New_PolyNode_avail(available);
    d = c;
    while ((p!=NULL)&&(q!=NULL))
    {
        switch (Compare(p->exp,q->exp))
        {
            case '=' :
                y = p->coef + q->coef ;
                if(fabs(y)>0.01)//�������ʽ�ݴ��������ϵ����Ӳ�����0��������ӵ���β
                    d = Avail_Insert(y,p->exp,d,available);
                p = p->next;
                q = q->next;
                break;
            case '>':
                d = Avail_Insert(p->coef, p->exp, d, available);
                p = p->next;
                break;
            case '<':
                d = Avail_Insert(q->coef, q->exp, d, available);
                q = q->next;
                break;
        }
    }
    //�������ʽ1������δ������ɣ���������и��Ӳ���
    while (p!=NULL)
    {
        d = Avail_Insert( p->coef, p->exp, d, available);
        p = p->next ;
    }
    //�������ʽ2������δ������ɣ���������и��Ӳ���
    while (q !=NULL)
    {
        d = Avail_Insert(q->coef, q->exp, d, available);
        q = q->next ;
    }
    d->next = NULL;
    //����ӵ���0ʱ��ֻ�б�ͷ�����ܲ���������㣬��ʱ����һ��0X^0
    if(c->next==NULL)
    {
        c->next = New_PolyNode_avail(available);
    }
    return c;
}
/*��������ʽ���*/
PolyPointer PolySub (PolyPointer a, PolyPointer b,PolyPointer available)
{
    PolyPointer p, q, d, c;
    float y ;
    p = a->next;
    q = b->next;
    c = New_PolyNode_avail(available);
    d = c;
    while ((p!=NULL)&&(q!=NULL))
    {
        switch (Compare(p->exp,q->exp))
        {
            case '=' :
                y = p->coef - q->coef ;
                if(fabs(y)>0.01)//�������ʽ�ݴ��������ϵ�����������0��������ӵ���β
                    d = Avail_Insert(y, p->exp, d, available);
                p = p->next;
                q = q->next;
                break;
            case '>':
                d = Avail_Insert(p->coef, p->exp, d, available);
                p = p->next;
                break;
            case '<':
                d = Avail_Insert(-q->coef, q->exp, d,available);
                q = q->next;
                break;
        }
    }
    //�������ʽ1������δ������ɣ���������и��Ӳ���
    while (p!=NULL)
    {
        d = Avail_Insert(p->coef, p->exp, d, available);
        p = p->next ;
    }
    //�������ʽ2������δ������ɣ���������и��Ӳ���
    while (q !=NULL)
    {
        d = Avail_Insert(-q->coef,q->exp,d, available);
        q = q->next ;
    }
    d->next = NULL;
    //���������0ʱ��ֻ�б�ͷ�����ܲ���������㣬��ʱ����һ��0X^0
    if(c->next==NULL)
    {
        c->next = New_PolyNode_avail(available);
    }
    return c;
}

/*������ʽ��ˣ�˼·�����ν�����ʽ1�е�ÿһ�����γ��Զ���ʽ2��
Ȼ�󽫽�������ݴ�����ӵ��µĶ���ʽ*/
PolyPointer PolyMult(PolyPointer a, PolyPointer b, PolyPointer available)// �˷�
{
    /*
    �ഴ��һ���б����ڴ洢������֮��ϵ��Ϊ0����̭��Ա��������
    */
    PolyPointer p, q, c2, avail;
    PolyPointer c = New_PolyNode_avail(available); //���ڴ洢���֮�����ʽ�Ľ��
    int acoef, aexp, bcoef, bexp;
    int AB_Coef, AB_Exp;
    p = a;//����ʽ1�Ľڵ�ָ��
    q = b;//����ʽ2�Ľڵ�ָ��
    c2 = c;//���֮�����ʽ�ڵ�ָ��
    avail = available;//���ÿռ�ڵ�ָ��
    while(p->next!=NULL)//��������ʽһ
    {
        acoef = p->next->coef;
        aexp  = p->next->exp;
        q = b;
        p = p->next;
        while(q->next!=NULL)//��������ʽ2
        {
            bcoef = q->next->coef;
            bexp  = q->next->exp;
            AB_Coef = acoef*bcoef;
            q = q->next;
            if(AB_Coef==0)
                continue;
            AB_Exp = aexp+bexp;
            c2 = c;
            //��ʼ���µĶ���ʽ
            if(c2->next==NULL)
            {
                Avail_Insert(AB_Coef,AB_Exp,c2,available);
                continue;
            }

            while(c2->next!=NULL)
            {
                //������˳�򽫽�����ӵ��µĶ���ʽ
                if((c2->next->exp)>AB_Exp)
                {
                    c2 = c2->next;
                    if(c2->next==NULL)
                    {
                        Avail_Insert(AB_Coef,AB_Exp,c2,available);//��˽�������¶���ʽ���ݴ���С�ģ��ʸ��ӵ�ĩβ
                        break;
                    }
                    continue;
                }
                //����˽������ݴ��ڶ���ʽ�Ѿ����ڣ���ֻ�����µĶ���ʽ�н�����ϲ�
                if(c2->next->exp==AB_Exp)
                {
                    int Temp_Coef = c2->next->coef+AB_Coef;
                    //�����ϲ�������ϵ��Ϊ0�������µĶ���ʽ��ȥ���ýڵ㣬���ýڵ���յ����ÿռ�
                    if(Temp_Coef==0)
                    {
                        avail->next = c2->next;
                        avail = avail->next;
                        c2->next = avail->next;
                        avail->next = NULL;
                    }
                    else
                    {
                        //�����ϲ�������ϵ����Ϊ0����ֻ���޸ĸ���ϵ��
                        c2->next->coef = Temp_Coef;
                    }
                    break;
                }
                else
                {
                    //�����˽������ݴβ�Ϊ��ֵ����δ�����֣����ڰ����ݴ�������Ӧλ�ò���ý����
                    Avail_Insert(AB_Coef,AB_Exp,c2,available);
                    break;
                }
            }

        }
    }
    return c;
}
/*�����б�*/
void Destroy_List(PolyPointer p)
{
    Position q;
    while(p)
    {
        q = p->next;
        free(p);
        p = q;
    }
}

/*���ö���Ľڵ�ռ䴴���½ڵ㣬��ɲ���Ԫ�ز���*/
PolyPointer Avail_Insert(float coef, int exp, Position c, PolyPointer available)
{

    PolyPointer new_node = New_PolyNode_avail(available);
    new_node->coef = coef;
    new_node->exp  = exp;
    new_node->next = c->next;
    c->next = new_node;
    return new_node;
}
/*����ʽ����
1�������ӵĵ�һ����Է�ĸ����ߴ���õ�����
2������ĸ��������
3���ӷ��ӵ���Ӧ���м�ȥ�յõ��ĳ˻�
4���ѵ�һ��ʽ�����µı���ʽ���ظ�ǰ�������õ�������ڶ���ʽ
5���ظ����Ĳ����õ������������ʽ����ʽС�ڳ�ʽ���������������
*/
void PolyDiv(PolyPointer quotient, PolyPointer remainder,PolyPointer a, PolyPointer b, PolyPointer available)
{
    PolyPointer nodeheader = New_PolyNode_avail(available);//���ڴ������̵Ľڵ�ͷ
    PolyPointer node = New_PolyNode_avail(available);//���ڴ�������
    PolyPointer a1, b1, quo;
    PolyPointer temp1, temp2;
    temp1 = NULL;//���ڼ�¼����*����
    temp2 = NULL;//���ڼ�¼�µı����� = ������ - ����*����
    nodeheader->next = node;
    a1 = a;//���ڼ�¼������
    b1 = b;//���ڼ�¼����
    quo = quotient;
    while((a1->next->exp)>=(b1->next->exp))
    {
        quo->next = New_PolyNode_avail(available);//���ڼ�¼�������
        quo = quo->next;
        node->coef = a1->next->coef/b1->next->coef;
        node->exp  = a1->next->exp - b1->next->exp;
        quo->coef = node->coef;
        quo->exp  = node->exp;
        temp1 = PolyMult(nodeheader,b,available);//��ȡ����*����
        if(temp2)
            recycle_avail(temp2,available);//�����ڴ�ռ䵽���ÿռ�
        temp2 = PolySub(a1,temp1,available);//���ڻ�ȡ�µı����� = ������ - ����*����
        if(temp1)
            recycle_avail(temp1,available);//�����ڴ�ռ䵽���ÿռ�
        a1 = temp2;//���±�����
    }
    remainder->next = a1->next;//�������
    recycle_avail(nodeheader,available);//�������̽ڵ�
}
/*��ӡ����ʽ*/
void Print_Poly(PolyPointer q)
{
    PolyPointer p = q;
    while(p->next)
    {
        printf("%.1fX^%d",p->next->coef,p->next->exp);
        p = p->next;
        if(p->next)
        {
            if(p->next->coef>0)
                printf("+");
        }
    }
    printf("\n");
}
/*���ÿ��ÿռ䴴���½ڵ�*/
PolyPointer New_PolyNode_avail(PolyPointer available)
{
    PolyPointer new_node;
    if(available->next!=NULL)//�жϿ��ÿռ��Ƿ��п��ÿռ�
    {
        new_node = available->next;
        available->next = new_node->next;
        new_node->coef = 0.0;
        new_node->exp = 0;
        new_node->next = NULL;
    }
    else
    {
        new_node = New_PolyNode();
    }
    return new_node;
}
/*��������Ľڵ㵽���ÿռ�*/
void recycle_avail(PolyPointer p, PolyPointer available)
{
    PolyPointer avail = available;
    while(avail->next)
    {
        avail = avail->next;
    }
    while(p)
    {
        avail->next = p;
        avail = avail->next;
        p = p->next;
        avail->next = NULL;
    }
}
