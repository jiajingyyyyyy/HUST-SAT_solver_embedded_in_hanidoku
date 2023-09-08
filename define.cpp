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
typedef struct node           //保存文字
{
    int value;                //文字名，小于0表示其在句子中的带有非
    node* next;               //下一变量
} node;
typedef struct clause           //保存子句
{
    int num;                    //标记子句中文字的个数
    node* head;                 //指向下一个文字
    clause* next;              //指向下一个句子
} clause;
typedef struct numNode
{
	int x;               //棋盘上元素横坐标 
	int y;               //棋盘上元素纵坐标 
	int v;               //棋盘上元素的值 
}numNode;
typedef int status;

int ABS(int a);                                                   //辅助计算函数
int read(FILE *fp);                                               //快读
status ReadCNF(clause*& cnf, int satORsudoku);                    //读取cnf文件
void destroyClause(clause*& cnf);                                 //删除SAT问题
void removeClause(clause*& cnf, clause*& cl);                     //删除子句
void removeNode(clause* cl, node*& nd);                           //删除文字
status addClause(clause* cl, clause*& cnf);                       //加入单子句
bool isUnitClause(clause* cl);                                    //子句判断是否为单子句
void delelteSingleClause(clause* s, clause*& cnf);                //单子句规则
bool emptyClause(clause* cnf);                                    //子句判空
void getForgery(clause*& forgery, clause* cnf);                   //获取副本
int getMaxBool(clause* cnf);                                      //获取出现次数最多的变元 
int getFirstBool(clause* cnf);									  //获取第一个变元 
int getNextBool_3(clause* cnf);                                   //获取短子句中绝对值出现最多的变元 
int getNextBool_4(clause* cnf);                                   //获取短子句中出现最多的变元 
bool DPLL(clause*& cnf, int* v, int satORsudoku);                 //DPLL算法
status printCNF(int s, int* v, double t1, double t2);             //创建res文件
void ReadSatissudo(char a[][COL], FILE *fp);					  //从标准棋盘中读取蜂窝数独 
void CreatMod(char a[][COL], char b[][COL], int numDigits);       //挖洞法生成随机棋盘 
void show(char a[][COL]);                                         //打印蜂窝数独棋盘 
void TurnToInt(char a[][COL], numNode b[][10]);                   //得到数独每一个元素的位置坐标  
void ToCnf(int a[][COL], const char fileName, int holes);         //得到当前棋盘的cnf文件 
void hanidoku();                                                  //进入蜂窝数独游戏 
void Turn(numNode a[][10], numNode b[][10]);                      //将蜂窝数独的元素沿着对角线进行翻转 
void LinProcecc(numNode a[][10], FILE *fp, int line);             //对每行进行约束条件限制，得到cnf文件 
void Non_Repeat(FILE *fp, numNode a[][10]);                       //每两格数字不重复 
void AddNode(char a[][COL], int x, int y, int z);                 //向蜂窝数独棋盘中进行加点 
int getNextBool_3(clause* cnf) ;
const int N = 50;
int inf = 0x3f3f3f3f; 
int boolCnt, clauseCnt, sumOfAns, branchRule;//变元数量 子句数量  选择策略 分支变元 
char fileName[200], WfileName[100];  //cnf文件文件名
int *ans=NULL; //结果数组
clause* CNF=NULL; //SAT问题
char map[N][N];
int jjy;
