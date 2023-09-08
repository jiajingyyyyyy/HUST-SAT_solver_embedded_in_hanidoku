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
        printf("\n                     1.DPLL     2.Hanidoku    0.�˳�                       \n\n");
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
                printf("\t1.��ȡ�ļ� 			 2.��ӡ�ļ�\n");
                printf("\t3.DPLL 				 4.��ӡ��������\n");
                printf("\t0.���� \n");
                printf("-------------------------------------------------------------------------\n>>");
                scanf("%d", &op1);
                switch (op1)
                {
                case 1: 
                	printf("----�Ƿ��ȡĬ��·���ļ���\n");
                	printf("	1 -> [y] / 2 -> [n] \n");
                	int  DefaultOrNot;
					scanf("%d", &DefaultOrNot);
					if(DefaultOrNot == 2 )
					{
	                    printf("����������ļ���ַ:\n");  
	                    scanf("%s", fileName);						
					}
					else strcpy(fileName, "C:\\Users\\86153\\Desktop\\SAT\\test\\��׼����\\���ܲ���\\sat-20.cnf");
                    if (ReadCNF(CNF, SAT) == OK)
                        flag_cnf = 0, printf("cnf�ļ���ȡ��ϣ�\n");
                    else
                        printf("cnf�ļ���ȡʧ��!\n");
					getchar(); 
                 	printf("\n------------------PLEASE ���س�������-----------------\n"); 
                    getchar();
                    break;
                case 2:
                    if (flag_cnf)
                        printf("��δδ��ȡcnf�ļ�!\n ");
                    else
                    {
                        printf("�ļ����������Ӿ䣺\n");
                        printf("___________________________\n");
                        for (clause* lp = CNF; lp; lp = lp->next)
                        {
                            for (node* tp = lp->head; tp; tp = tp->next)
                                printf("%d ", tp->value);
                            printf("\n");
                        }
                    }
                    printf("\n------------------PLEASE ���س�������-----------------\n"); 
                    getchar(), getchar();
                    break;
                case 3:
                    if (flag_cnf)
                        printf("��δδ��ȡcnf�ļ�!\n ");
                    else
                    {
                    	printf("----��ѡ���Ԫѡȡ���ԣ�\n");
                    	printf("----0:�˳�\n");
                    	printf("----1:ѡȡ��һ����Ԫ\n");
                    	printf("----2:ѡȡ�����Ԫ�г��ִ������ı�Ԫ\n");
                    	printf("----3:ѡȡ���Ӿ��г��ִ������ı�Ԫ������ֵ��\n");
                    	printf("----4:ѡȡ���Ӿ��г��ִ������ı�Ԫ\n");
                    	scanf("%d", &branchRule);
                    	ans = (int*)malloc(sizeof(int) * (boolCnt + 1));
	                    for (int i = 0; i <= boolCnt; i++)
	                        ans[i] = 1;
	                    start = clock();
	                    res = DPLL(CNF, ans, SAT);
	                        
	                    finish = clock();
	                    if (!res) printf("�������㣡\n");
	                    else printf("�����㣡\n");
	                    
	                    time1 = (double)(finish - start);
	                    printf("OVERDPLL      t = %lfms\n", time1);
	                    destroyClause(CNF);
	                    ReadCNF(CNF, SAT);
	                    time2 = time1; 
	                    while(branchRule)
	                        {
	                        	time1 = time2;
	                        	printf("\n----���ٴ�ѡ���Ԫѡȡ���ԣ�\n");
		                    	scanf("%d", &branchRule);
		                    	if(branchRule == 0) break;
		                        for (int i = 0; i <= boolCnt; i++)
		                            ans[i] = 1;
		                        start = clock();
		                        res = DPLL(CNF, ans, SAT);
		                        if (!res) printf("�������㣡\n");
	            		        else printf("�����㣡\n");
		                        finish = clock();
		                        time2 = (double)(finish - start);
		                        printf("OVERDPLL      t = %lfms\n", time2);
		                    
		                        if(time1 == 0 || time1 == time2 || time2 == 0) printf("ʱ���Ż���Ϊ 0 %%\n"); 
		                        else if(time1 < time2) printf("ʱ���Ż���Ϊ-%lf %%", (100 * 1.0 *(time2 - time1)) / time1);
			                    else printf("ʱ���Ż���Ϊ%lf %%", (100 * 1.0 *(time1 - time2)) / time1);
			                    
							}
	                
                    }
		                    
                    printf("\n------------------PLEASE ���س�������-----------------\n"); 
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
                        printf("��δδ��ȡcnf�ļ�!\n ");
                    else
                    {
                    	printf("----�Ƿ񱣴浽Ĭ��·����\n");
	                	printf("	1 -> [y] / 2 -> [n] \n");
	                	int  DefaultOrNot;
						scanf("%d", &DefaultOrNot);
						if(DefaultOrNot == 2 )
						{
		                    printf("�����뱣���ļ���ַ:\n");
		                    scanf("%s", fileName);						
						}
						else strcpy(fileName, "C:\\Users\\86153\\Desktop\\SAT\\save");
                        if (printCNF(res, ans, time1, time2))
                            printf("����ѱ���\n");
                        else
                            printf("�������ʧ��!\n");
                    }
                    printf("\n------------------PLEASE ���س�������-----------------\n"); 
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
                    printf("\n------------------PLEASE ���س�������-----------------\n"); 
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
