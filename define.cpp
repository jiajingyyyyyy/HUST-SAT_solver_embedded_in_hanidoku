#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define Hanidoku 1
#define SAT 0
#define ROW 20
#define COL 40
typedef struct node           //��������
{
    int value;                //��������С��0��ʾ���ھ����еĴ��з�
    node* next;               //��һ����
} node;
typedef struct clause           //�����Ӿ�
{
    int num;                    //����Ӿ������ֵĸ���
    node* head;                 //ָ����һ������
    clause* next;              //ָ����һ������
} clause;
typedef struct numNode
{
	int x;               //������Ԫ�غ����� 
	int y;               //������Ԫ�������� 
	int v;               //������Ԫ�ص�ֵ 
}numNode;
typedef int status;

int ABS(int a);                                                   //�������㺯��
int read(FILE *fp);                                               //���
status ReadCNF(clause*& cnf, int satORsudoku);                    //��ȡcnf�ļ�
void destroyClause(clause*& cnf);                                 //ɾ��SAT����
void removeClause(clause*& cnf, clause*& cl);                     //ɾ���Ӿ�
void removeNode(clause* cl, node*& nd);                           //ɾ������
status addClause(clause* cl, clause*& cnf);                       //���뵥�Ӿ�
bool isUnitClause(clause* cl);                                    //�Ӿ��ж��Ƿ�Ϊ���Ӿ�
void delelteSingleClause(clause* s, clause*& cnf);                //���Ӿ����
bool emptyClause(clause* cnf);                                    //�Ӿ��п�
void getForgery(clause*& forgery, clause* cnf);                   //��ȡ����
int getMaxBool(clause* cnf);                                      //��ȡ���ִ������ı�Ԫ 
int getFirstBool(clause* cnf);									  //��ȡ��һ����Ԫ 
int getNextBool_3(clause* cnf);                                   //��ȡ���Ӿ��о���ֵ�������ı�Ԫ 
int getNextBool_4(clause* cnf);                                   //��ȡ���Ӿ��г������ı�Ԫ 
bool DPLL(clause*& cnf, int* v, int satORsudoku);                 //DPLL�㷨
status printCNF(int s, int* v, double t1, double t2);             //����res�ļ�
void ReadSatissudo(char a[][COL], FILE *fp);					  //�ӱ�׼�����ж�ȡ�������� 
void CreatMod(char a[][COL], char b[][COL], int numDigits);       //�ڶ�������������� 
void show(char a[][COL]);                                         //��ӡ������������ 
void TurnToInt(char a[][COL], numNode b[][10]);                   //�õ�����ÿһ��Ԫ�ص�λ������  
void ToCnf(int a[][COL], const char fileName, int holes);         //�õ���ǰ���̵�cnf�ļ� 
void hanidoku();                                                  //�������������Ϸ 
void Turn(numNode a[][10], numNode b[][10]);                      //������������Ԫ�����ŶԽ��߽��з�ת 
void LinProcecc(numNode a[][10], FILE *fp, int line);             //��ÿ�н���Լ���������ƣ��õ�cnf�ļ� 
void Non_Repeat(FILE *fp, numNode a[][10]);                       //ÿ�������ֲ��ظ� 
void AddNode(char a[][COL], int x, int y, int z);                 //��������������н��мӵ� 
int getNextBool_3(clause* cnf) ;
const int N = 50;
int inf = 0x3f3f3f3f; 
int boolCnt, clauseCnt, sumOfAns, branchRule;//��Ԫ���� �Ӿ�����  ѡ����� ��֧��Ԫ 
char fileName[200], WfileName[100];  //cnf�ļ��ļ���
int *ans=NULL; //�������
clause* CNF=NULL; //SAT����
char map[N][N];
int jjy;
