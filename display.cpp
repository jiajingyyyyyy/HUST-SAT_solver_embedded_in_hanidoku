#include"define.cpp"
#include"cnfparser.cpp"
#include"solver.cpp"
#include"hanidoku.cpp"

int main()
{
    int op = 1, op1 = 1, op2 = 1, flag_cnf, difficulty;
    clock_t start, finish;
    double time1, time2, rate;
    bool res;
    while (op)
    {
        system("cls");
        printf("\n----------------------------->> MENUE <<----------------------------------\n");
        printf("\n                     1.DPLL     2.Hanidoku    0.退出                       \n\n");
        printf("--------------------------------------------------------------------------\n>>");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            flag_cnf = 1, op1 = 1; 
            while (op1)
            {
                system("cls");
                printf("\n--------------------------------*** SAT Solver ***--------------------------------\n\n");
                printf("\n------------------------------>> OPTIONS <<---------------------------------------\n");
                printf("\t1.读取文件 			 2.打印文件\n");
                printf("\t3.DPLL 				 4.打印并保存结果\n");
                printf("\t0.返回 \n");
                printf("-------------------------------------------------------------------------\n>>");
                scanf("%d", &op1);
                switch (op1)
                {
                case 1: 
                	printf("----是否读取默认路径文件？\n");
                	printf("	1 -> [y] / 2 -> [n] \n");
                	int  DefaultOrNot;
					scanf("%d", &DefaultOrNot);
					if(DefaultOrNot == 2 )
					{
	                    printf("请输入测试文件地址:\n");  
	                    scanf("%s", fileName);						
					}
					else strcpy(fileName, "C:\\Users\\86153\\Desktop\\SAT\\test\\基准算例\\功能测试\\sat-20.cnf");
                    if (ReadCNF(CNF, SAT) == OK)
                        flag_cnf = 0, printf("cnf文件读取完毕！\n");
                    else
                        printf("cnf文件读取失败!\n");
					getchar(); 
                 	printf("\n------------------PLEASE 按回车键继续-----------------\n"); 
                    getchar();
                    break;
                case 2:
                    if (flag_cnf)
                        printf("尚未未读取cnf文件!\n ");
                    else
                    {
                        printf("文件中有如下子句：\n");
                        printf("___________________________\n");
                        for (clause* lp = CNF; lp; lp = lp->next)
                        {
                            for (node* tp = lp->head; tp; tp = tp->next)
                                printf("%d ", tp->value);
                            printf("\n");
                        }
                    }
                    printf("\n------------------PLEASE 按回车键继续-----------------\n"); 
                    getchar(), getchar();
                    break;
                case 3:
                    if (flag_cnf)
                        printf("尚未未读取cnf文件!\n ");
                    else
                    {
                    	printf("----请选择变元选取策略：\n");
                    	printf("----0:退出\n");
                    	printf("----1:选取第一个变元\n");
                    	printf("----2:选取总体变元中出现次数最多的变元\n");
                    	printf("----3:选取短子句中出现次数最多的变元（绝对值）\n");
                    	printf("----4:选取短子句中出现次数最多的变元\n");
                    	scanf("%d", &branchRule);
                    	ans = (int*)malloc(sizeof(int) * (boolCnt + 1));
	                    for (int i = 0; i <= boolCnt; i++)
	                        ans[i] = 1;
	                    start = clock();
	                    res = DPLL(CNF, ans, SAT);
	                        
	                    finish = clock();
	                    if (!res) printf("不可满足！\n");
	                    else printf("可满足！\n");
	                    
	                    time1 = (double)(finish - start);
	                    printf("OVERDPLL      t = %lfms\n", time1);
	                    destroyClause(CNF);
	                    ReadCNF(CNF, SAT);
	                    time2 = time1; 
	                    while(branchRule)
	                        {
	                        	time1 = time2;
	                        	printf("\n----请再次选择变元选取策略：\n");
		                    	scanf("%d", &branchRule);
		                    	if(branchRule == 0) break;
		                        for (int i = 0; i <= boolCnt; i++)
		                            ans[i] = 1;
		                        start = clock();
		                        res = DPLL(CNF, ans, SAT);
		                        if (!res) printf("不可满足！\n");
	            		        else printf("可满足！\n");
		                        finish = clock();
		                        time2 = (double)(finish - start);
		                        printf("OVERDPLL      t = %lfms\n", time2);
		                    
		                        if(time1 == 0 || time1 == time2 || time2 == 0) printf("时间优化率为 0 %%\n"); 
		                        else if(time1 < time2) printf("时间优化率为-%lf %%", (100 * 1.0 *(time2 - time1)) / time1);
			                    else printf("时间优化率为%lf %%", (100 * 1.0 *(time1 - time2)) / time1);
			                    
							}
	                
                    }
		                    
                    printf("\n------------------PLEASE 按回车键继续-----------------\n"); 
                    getchar(), getchar();
                    break;
                case 4:
                    for (int i = 1; i <= boolCnt; i++)
                    {
                        if (ans[i])
                            printf("%d \n", i);
                        else
                            printf("%d \n", -i);
                    }
                    if (flag_cnf)
                        printf("尚未未读取cnf文件!\n ");
                    else
                    {
                    	printf("----是否保存到默认路径？\n");
	                	printf("	1 -> [y] / 2 -> [n] \n");
	                	int  DefaultOrNot;
						scanf("%d", &DefaultOrNot);
						if(DefaultOrNot == 2 )
						{
		                    printf("请输入保存文件地址:\n");
		                    scanf("%s", fileName);						
						}
						else strcpy(fileName, "C:\\Users\\86153\\Desktop\\SAT\\save");
                        if (printCNF(res, ans, time1, time2))
                            printf("结果已保存\n");
                        else
                            printf("结果保存失败!\n");
                    }
                    printf("\n------------------PLEASE 按回车键继续-----------------\n"); 
                    getchar(), getchar();
                    break;
                case 0:
                    break;
                }
            }
            break;
        case 2:
             op2 = 1;
            while (op2)
            {
                system("cls");
                printf("\n---------------------------*** Hanidoku Base On DPLL ***------------------------\n\n");
                printf("\n--------------------------------OPTIONS---------------------------------\n\n");
                printf("     	              1.Hanidoku   0.Return                            \n\n");
                printf("------------------------------------------------------------------------\n");
                scanf("%d", &op2);
                switch (op2)
                {
                case 1:     
                    hanidoku();
                    printf("\n------------------PLEASE 按回车键继续-----------------\n"); 
                    getchar(), getchar();
                    break;
                default:
                    break;
                }
            }
            break;
        case 0:
            break;
        }
    }
    return 0;
}
