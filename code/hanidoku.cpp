void ReadSatissudo(char a[][COL], FILE *fp)
{
    for (int i = 0; i < ROW; i++)
    {
        fgets(a[i], COL, fp);
    }
    fclose(fp);
    return ;
}

void CreatMod(char a[][COL], char b[][COL], int numDigits)
{
	int i,j,k;
	srand((unsigned)time(NULL));
	for( i = 0; i < ROW ; i ++)
        for( j = 0; j < COL ; j++)
            b[i][j] = a[i][j];
            
    int c[numDigits][2];
    int m,flag = 0;

    for(i = 0; i < numDigits; i ++)
    {   
    	flag = 0;
    	j = rand()%9 + 1;
        k = rand()%9 + 1;
        
        if(j % 2 == 1)
        {
        	j = j * 2 - 1;
       	    k = k * 4 - 2;
		}
        else
        {
        	j = j * 2 - 1;
       	    k = k * 4;
		}
        
        for(m = 0; m < i ; m++)
            if( j == c[m][0] && k == c[m][1])
			{
				flag = 1;
				break;
			} 
            
        
    	if(flag == 0 && b[j][k] >= '1' && b[j][k] <= '9')
    	{
    		b[j][k] = '0';
    		c[i][0] = j;
    		c[i][1] = k;
		}
		else i --;	
	}
}
void show(char a[][COL])	
{
	system("cls");
	printf("\n\n>>>-----------------------------------<<<\n");
	for(int i = 0; i < ROW - 1; i ++)
	{
		printf("%s", a[i]);
	}
	printf(">>>-----------------------------------<<<\n");
	printf("----请依次输入所要填充的位置的行数，列数，和数字\n");
	return ;
}
	
void TurnToInt(char a[][COL], numNode b[][10])
{
	memset(b, 0, sizeof(b));
	int cnt;
	for(int i = 0; i < ROW - 1; i ++)
	{
		cnt = 1;
		if(i % 2 == 0) continue;
		for(int j = 0; j < COL; j ++)
		{
			if(a[i][j] >= '0' && a[i][j] <= '9')
			{
				b[i / 2 + 1][cnt ++].v = a[i][j] - '0';
				b[i / 2 + 1][cnt - 1].x = i/2 + 1;
				b[i / 2 + 1][cnt - 1].y = cnt - 1;
			}
		}
		while(cnt <= 9){
			b[i / 2 + 1][cnt ++].v = 0;
			b[i / 2 + 1][cnt - 1].x = i/2 + 1;
			b[i / 2 + 1][cnt - 1].y = cnt - 1;
		}
	}
	return;
}

void Non_Repeat(FILE *fp, numNode a[][10])
{
	for(int i = 1; i <= 9; i ++)
		for(int j = 1; j <= 9; j ++)
		{
			if(j <= 5)
			{
				for(int k = 1; k <= 4 + j; k ++)
				{
					for(int q = 1; q + k <= j + 4; q ++)
					{
						fprintf(fp, "%d %d %d\n",-(i + a[j][k].x* 100 + a[j][k].y*10), -(i + a[j][q + k].x*100 + a[j][q + k].y * 10), 0);
//						fprintf(fp, "%d %d %d\n", -(i + a[j][q].x * 100 + a[j][q].y * 10), -(i + a[j][q].x) * 100 + a[j][q].y * 10, 0);
					}
					
				}	
			
			}	
			else 
			{
				for(int k = 1; k <= 14 - j; k ++)
				{
					for(int q = 1; q + k <= 14 - j; q ++)
					{
						fprintf(fp, "%d %d %d\n",-(i + a[j][k].x * 100 + a[j][k].y*10), -(i + a[j][q + k].x*100 + a[j][q + k].y * 10), 0);
//						fprintf(fp, "%d %d %d\n", -(i + a[j][q].x * 100 + a[j][q].y * 10), -(i + a[j][q].x) * 100 + a[j][q].y * 10, 0);
					}
					
				}	
			}
		}	
	
} 


void LinProcecc(numNode a[][10], FILE *fp, int line)
{
	int st, end, l;//必出现的连续数字起始与结束数值，所容纳变元的数量 
	//对于确定位置的数字cnf 
	if(line <= 5)
	{
		st = 5 - line + 1;
		end = 2 * 5 - st;
		l = 4 + line;
		for(int j = st; j <= end; j ++)
		{
			for(int i = 1; i <= l; i ++)
			{
				fprintf(fp, "%d ", a[line][i].x * 100 + a[line][i].y * 10 + j); 
			}
			fprintf(fp, "%d\n", 0);		
		}
		for(int i = 1; i <= 5 - line; i ++)
		{
			for(int j = 5 + line; j < 5 + line + i; j ++)
			{
				for(int k = 1; k <= l; k ++)
				{
					fprintf(fp, "%d %d ", 100 + 10 * k + i, 100 + 10 * k + j);
				}
				fprintf(fp, "%d\n", 0);
			}
		}
	}
	else
	{	
		st = line - 4;
		end = 2 * 5 - st;
		l = 14 - line;
		int fc = 10 - line;
		for(int j = st; j <= end; j ++)
		{
			for(int i = 1; i <= l; i ++)
			{
				fprintf(fp, "%d ", a[line][i].x * 100 + a[line][i].y * 10 + j);   	
			}
			fprintf(fp, "%d\n", 0);	
		}
		
		//对于连续性约束条件下的数字进行cnf
		for(int i = 1; i <= 5 - fc; i ++)
		{
			for(int j = 5 + fc; j < 5 + fc + i; j ++)
			{
				for(int k = 1; k <= l; k ++)
				{
					fprintf(fp, "%d %d ", 100 + 10 * k + i, 100 + 10 * k + j);
				}
				fprintf(fp, "%d\n", 0);
			}
		} 
	}	
	return;
}

void Turn(numNode a[][10], numNode b[][10])
{
	memset(b, 0, sizeof(b));
	b[1][1] = a[1][5], b[1][2] = a[2][6], b[1][3] = a[3][7], b[1][4] = a[4][8], b[1][5] = a[5][9];
	b[2][1] = a[1][4], b[2][2] = a[2][5], b[2][3] = a[3][6], b[2][4] = a[4][7], b[2][5] = a[5][8], b[2][6] = a[6][8];//2
	b[3][1] = a[1][3], b[3][2] = a[2][4], b[3][3] = a[3][5], b[3][4] = a[4][6], b[3][5] = a[5][7], b[3][6] = a[6][7], b[3][7] = a[7][7];//3
	b[4][1] = a[1][2], b[4][2] = a[2][3], b[4][3] = a[3][4], b[4][4] = a[4][5], b[4][5] = a[5][6], b[4][6] = a[6][6], b[4][7] = a[7][6], b[4][8] = a[8][6];
	b[5][1] = a[1][1], b[5][2] = a[2][2], b[5][3] = a[3][3], b[5][4] = a[4][4], b[5][5] = a[5][5], b[5][6] = a[6][5], b[5][7] = a[7][5], b[5][8] = a[8][5], b[5][9] = a[9][5];
	b[6][1] = a[2][1], b[6][2] = a[3][2], b[6][3] = a[4][3], b[6][4] = a[5][4], b[6][5] = a[6][4], b[6][6] = a[7][4], b[6][7] = a[8][4], b[6][8] = a[9][4];
	b[7][1] = a[3][1], b[7][2] = a[4][2], b[7][3] = a[5][3], b[7][4] = a[6][3], b[7][5] = a[7][3], b[7][6] = a[8][3], b[7][7] = a[9][3];
	b[8][1] = a[4][1], b[8][2] = a[5][2], b[8][3] = a[6][2], b[8][4] = a[7][2], b[8][5] = a[8][2], b[8][6] = a[9][2];
	b[9][1] = a[5][1], b[9][2] = a[6][1], b[9][3] = a[7][1], b[9][4] = a[8][1], b[9][5] = a[9][1];
}



void ToCnf(numNode a[][10], const char fileName[], int holes)
{
	FILE *fp;
	fp = fopen(fileName, "w");
	if (fp == NULL) 
	{
        printf("无法打开文件：%s\n", fileName);
        return;
    }
	fprintf(fp, "%c %s %d %d\n", 'p', "cnf", 549,  5272 - holes);//5272
	for (int x = 1; x <= 9; ++x) //将已知条件转化为cnf 
	{
        for (int y = 1; y <= 9; ++y)
            if(a[x][y].v != 0)
            {
            	fprintf(fp, "%d %d\n", (a[x][y].x)*100 + (a[x][y].y)*10 + a[x][y].v, 0);
			}
	}
	
	numNode b[10][10];	
	for(int i = 1; i <= 9; i ++)	LinProcecc(a, fp, i);
	Non_Repeat(fp, a);
	Turn(a, b);//生成新的蜂窝数独，将反对角线转化成行
	for(int i = 1; i <= 9; i ++)	LinProcecc(b, fp, i);
	Non_Repeat(fp, b);	
	Turn(a, b); Turn(b, a);
	for(int i = 1; i <= 9; i ++)	LinProcecc(a, fp, i);
	Non_Repeat(fp, a);
	
	fclose(fp);	
	return ;
}


void AddNode(char a[][COL], int x, int y, int z)
{
	x = x*2 - 1;
	int cnt = 0;
	for(int i = 0; i < y; )
	{
		if(a[x][cnt] <= '9' && a[x][cnt] >= '0')
		{
			cnt++;  i ++;
		} 
		else cnt++;
		if(i == y) 
		{
			cnt--; 
			a[x][cnt] = z + '0';
			break;
		}
	}
	
	show(a);
	return ;
}
void hanidoku()
{
	printf("----请选择游戏难度：\n");
	printf("---- >> 1 Easy\t  >> 2 Moderate\t  >> 3 Hard\n");
	int ch, holes;
	scanf("%d", &ch);
	if(ch == 1)		holes = 10;
	else if(ch == 2) holes = 25;
	else holes = 30;
	srand((unsigned)time(NULL));
	int r = rand() % 3;
	char FileName[50] = "C:\\Users\\86153\\Desktop\\SAT\\ans\\ans1.txt";
	if(r == 1) strcpy(FileName, "C:\\Users\\86153\\Desktop\\SAT\\ans\\ans2.txt");
	else if(r == 2) strcpy(FileName, "C:\\Users\\86153\\Desktop\\SAT\\ans\\ans3.txt");//三种填充合法布局 
	//对棋盘进行初始化 
	char a[ROW][COL], b[ROW][COL];
	numNode c[10][10], d;
	FILE * fp;
	fp = fopen(FileName, "r");
	ReadSatissudo(a, fp);
	CreatMod(a, b, holes);
	show(b);
	ans = (int*)malloc(sizeof(int) * (boolCnt + 1));
	int resofhani;
	int Hcnt = 0;
	char CnfFileName[100];
	strcpy(CnfFileName, "C:\\Users\\86153\\Desktop\\SAT\\ans\\pretreat.txt");
	strcpy(fileName, "C:\\Users\\86153\\Desktop\\SAT\\ans\\pretreat.txt"); 
	while(1)
	{
		show(b);
		TurnToInt(b, c);
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		c[x][y].x = x;	c[x][y].y = y;	c[x][y].v = z;
		AddNode(b, x, y, z);
		Hcnt ++;
		printf("----是否进行可行性验证?\n 1 -> y      0 -> n\n");
		printf("注意：可行性验证每局游戏只能进行一次！！！\n");
		int ifcheck;
		scanf("%d", &ifcheck); 
		if(ifcheck)
		{
			int flag_cnf = 0;
//			char CnfFileName[100];
//				strcpy(CnfFileName, "C:\\Users\\86153\\Desktop\\SAT\\ans\\pretreat.txt");
				ToCnf(c, CnfFileName, holes - Hcnt);
//			strcpy(fileName, "C:\\Users\\86153\\Desktop\\SAT\\ans\\pretreat.txt"); 
			if (ReadCNF(CNF, SAT) == OK)
                flag_cnf = 0;
			if (flag_cnf)
                printf("尚未未读取cnf文件!\n ");
            else
            {
                int res;
				branchRule = 1;
                ans = (int*)malloc(sizeof(int) * (boolCnt + 1));
                for (int i = 0; i <= boolCnt; i++)
                    ans[i] = 1;
                res = DPLL(CNF, ans, SAT);
                printf("OVERDPLL\n");
                if (!res)
                {
                    resofhani = ERROR;
                    printf("不可满足！\n");
				}
                            
                else
                {
                    resofhani = OK;
                    printf("可满足！\n");
                }
            }
		if(resofhani == ERROR)
		{
			printf("---请注意，当前hanidoku无解！，请重新填充");
		}
		}
		if(Hcnt == holes)
		{
			printf("----恭喜！填充完成！\n");
			break;
		}
		printf("\n------------------PLEASE 按回车键继续-----------------\n"); 
                    getchar(), getchar();
	} 
	return ;
}
