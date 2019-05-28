#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#define randomInt(x,y) (rand()%(y-x+1)+x)
int access[32];//��������
int size = 3;//�����̷�����ڴ�Ĵ�С
int lost = 0;//ȱҳ��

void generate()
{
	int maxLength, e, m, p;
	double t;
	printf("������Ҫ������ɷ������еĳ���\n");
	scanf("%d", &maxLength);
	printf("������ҳ����\n");
	scanf("%d", &e);
	printf("�����빤������ʼλ��\n");
	scanf("%d", &p);
	printf("�����빤�����ƶ�Ч��\n");
	scanf("%d", &m);
	printf("������0-1֮���t\n");
	scanf("%lf", &t);
	srand((unsigned)time(NULL));
	int iterNum = 0; 
	int index=0;
	for (int i = 0; i < maxLength;)
	{
		if (i + m >= maxLength)
			iterNum = maxLength - i;
		else
			iterNum = m;
		for (int j =0;j<iterNum;j++)
		{
			int temp=randomInt(p%32,(p+e)%32);
			access[index]=temp;
			printf("%d ",access[index]);
			index++;
		}
		
		double r=randomInt(0,100)/100.0;
		if(r<t)
			p=randomInt(0,32);
		else
			p++;
		i=i+iterNum;

	}
	printf("\n");
}
typedef struct node
{
    int num;
    struct node* next;
} Node, *pNode;

typedef struct queue
{
    int n;
    pNode front;
    pNode rear;
    
} Queue, *pQueue;

void initQueue (pQueue q)
{
    q->rear = (pNode) malloc (sizeof (Node));
    
    if (q->rear == NULL)
    {
        printf ("failed\n");
    }
    
    else
    {
        q->front = q->rear;
        q->rear->next = NULL;
        q->front->next = NULL;
        q->n = 0;
    }
}

void push (pQueue q, int num)
{
    pNode p = (pNode) malloc (sizeof (Node));
    
    if (p == NULL)
    {
        printf ("failed");
    }
    
    else
    {
        p->next = NULL;
        p->num = num;
        
        if (q->front == q->rear)
        {
            q->front->next = p;
            q->rear = p;
        }
        
        else
        {
            q->rear->next = p;
            q->rear = p;
        }
        
        q->n++;
    }
}

void pop (pQueue q)
{
    pNode p;
    
    if (q->front != q->rear)
    {
        p = q->front->next;
        q->front->next = p->next;
        
        if (p == q->rear)
        {
            q->front = q->rear;
        }
        
        q->n--;
        free (p);
    }
}

void destroy (pQueue q)
{
    while (q->front != q->rear)
    {
        pop (q);
    }
}


int findInQueue (pQueue q, int num)
{
    pNode p;
    
    if (q->front != q->rear)
    {
        p = q->front->next;
        
        while (p)
        {
            if (p->num == num)
            {
                return 1;
            }
            
            else
            {
                p = p->next;
            }
        }
    }
    
    return 0;
}

void fifo (pQueue q, int num)
{
    if (findInQueue (q, num))
    {
        printf ("----------------------����ҳ���ѱ�����,���û�----------------------\n");
    }
    
    else
    {
        if (q->n == size)
        {
            pop (q);
            push (q, num);
            lost++;
        }
        
        else
        {
            push (q, num);
        }
    }
}


void fifoTest()
{
    Queue q;
    pNode p;
    initQueue (&q);
    int i = 0;
    printf ("�Ƚ��ȳ��û��㷨\n");
    
    for (; i < 32; i++)
    {
        fifo (&q, access[i]);
        p = q.front->next;
        
        while (p)
        {
            printf ("%d ", p->num);
            p = p->next;
        }
        
        printf ("\n");
    }
    
    printf ("�Ƚ��ȳ��㷨ȱҳ�ʣ�%2f \nȱҳ��Ϊ�� %d\n", lost / 32.0, lost);
    destroy (&q);
}
int main()
{
	generate();
    fifoTest();
	return 0;
 } 
