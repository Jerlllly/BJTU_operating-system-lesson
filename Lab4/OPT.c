#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#define randomInt(x,y) (rand()%(y-x+1)+x)
int block = 3;
int access[32]; //��������
int* memo;
int lost = 0;//û�ҵ���ҳ����
int index = 0;//ָʾ��ǰ�±�
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

void initMemo()
{
	memo = (int*) malloc (block * sizeof (int));
    int i = 0;
    
    for (; i < block; i++)
    {
        memo[i] = -1;
    }
    
    return;
}

int  isInMemo (int n)
{
    int i = 0;
    
    for (; i < block; i++)
    {
        if (access[n] == memo[i])
        {
            return 1;
        }
    }
    
    return 0;
}

void optimal (int n)
{
    int i = 0, j = 0;
    
    if (isInMemo (n))
    {
        printf ("----------------------����ҳ���ѱ�����,���û�----------------------\n");
    }
    
    else
        if (index == block)
        {
            lost++;
            int max = 0, pos, tag;
            
            for (i = 0; i < block; i++)
            {
                tag = -1;
                
                for (j = n + 1; j < 32; j++)
                {
                    if (access[j] == memo[i])
                    {
                        tag = j;
                        break;
                    }
                }
                
                if (tag == -1)
                {
                    max = 32;
                    pos = i;
                    break;
                }
                
                else
                {
                    if (max < tag)
                    {
                        max = tag;
                        pos = i;
                    }
                }
            }
            
            memo[pos] = access[n];
        }
        
        else
        {
            memo[index] = access[n];
            index++;
        }
}

void testOptimal()
{
    initMemo();
    int i = 0;
    printf ("����û��㷨��\n");
    
    for (; i < 32; i++)
    {
        optimal (i);
        printf ("%d %d %d\n", memo[0], memo[1], memo[2]);
    }
    
    printf ("����û��㷨ȱҳ�ʣ� %2f \nȱҳ��Ϊ�� %d\n", lost / 32.0, lost);
    lost = 0;
    free (memo);
    index = 0;
}
int main()
{
	initMemo();
	generate();
	testOptimal();
	printf("\n");
	system("pause");
	return 0; 
}
