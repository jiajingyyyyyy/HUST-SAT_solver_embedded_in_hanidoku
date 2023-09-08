void destroyClause(clause*& cnf)
{
    clause* ppc, * pc2; //指向子句的指针
    node* pn1, * pn2;   //指向文字的指针
    ppc = cnf;
    while (ppc) 
    {
        pn1 = ppc->head;   //依次删除子句
        while (pn1)
            pn2 = pn1->next, free(pn1), pn1 = pn2;  //依次删除文字
        pc2 = ppc->next, free(ppc), ppc = pc2;   
    }
    cnf = NULL;
}

void removeClause(clause*& cnf, clause*& cl)
{
    if (cl == cnf) //如果是头子句 
        cnf = cnf->next;  //头子句的next变为头子句
    else
    {
        clause* ppc = cnf;
        while (ppc && ppc->next != cl)
            ppc = ppc->next;     //定位要删除的子句
        ppc->next = ppc->next->next;
    }
    node* pn1, * pn2;
    for (pn1 = cl->head; pn1;)
        pn2 = pn1->next, free(pn1), pn1 = pn2;  //删除文字
    free(cl);
    cl = NULL;
}

void removeNode(node*& head, node*& nd)
{
    node* ppn = head;
    if (ppn == nd)  //如果要删除头节点
        head = head->next;  //头节点的next成为头节点
    else
    {
        while (ppn && ppn->next != nd)
            ppn = ppn->next;  //定位节点
        ppn->next = ppn->next->next;  
    }
    free(nd);
    nd = NULL;
}

status addClause(clause* cl, clause*& cnf)
{
    if (cl)//首插法插入单子句
    {
        cl->next = cnf;
        cnf = cl;
        return OK;
    }
    return ERROR; 
}

bool isUnitClause(clause* cl)
{
    if (cl->head != NULL) {
        if (cl->head->next == NULL)
            return true;
    }
    return false;
}

void delelteSingleClause(clause* s, clause*& cnf)
{
    clause* tmp;
    int n = s->head->value;//要删除的变元的值
    for (clause* ppc = cnf; ppc; ppc = tmp) //遍历所有子句
    {
        tmp = ppc->next;//用temp存储当前子句的next 当前子句被删除后可以找到下一子句
        for (node* ppn = ppc->head; ppn; ppn = ppn->next)
        {
            if (ppn->value == n)
            {
                removeClause(cnf, ppc);//如果包含该变元 删除该子句
                break;
            }
            if (ppn->value == -n)
            {
                removeNode(ppc->head, ppn);//如果包含该变元的反 删除该节点
                ppc->num--;
                break;
            }
        }
    }
}

bool emptyClause(clause* cnf)
{
    for (clause* p = cnf; p; p = p->next)
        if (!p->head)
            return true;
    return false;
}

void getForgery(clause*& forgery, clause* cnf)
{
    clause* ppc, * pc;  //指向子句的指针
    node* ppn, * pn;    //指向文字的指针
    forgery = (clause*)malloc(sizeof(clause));
    forgery->head = (node*)malloc(sizeof(node));
    forgery->next = NULL;
    forgery->head->next = NULL;
    forgery->num = 0;
    //初始化问题
    for (pc = cnf, ppc = forgery; pc != NULL; pc = pc->next, ppc = ppc->next)//复制当前cnf 为回溯做准备
    {
        for (pn = pc->head, ppn = ppc->head; pn != NULL; pn = pn->next, ppn = ppn->next)
        {
            ppc->num++;
            ppn->value = pn->value;
            ppn->next = (node*)malloc(sizeof(node));
            ppn->next->next = NULL;
            if (pn->next == NULL)
                free(ppn->next), ppn->next = NULL;
        }
        ppc->next = (clause*)malloc(sizeof(clause));
        ppc->next->head = (node*)malloc(sizeof(node));
        ppc->next->next = NULL;
        ppc->next->head->next = NULL;
        ppc->next->num = 0;
        if (pc->next == NULL)
            free(ppc->next->head), free(ppc->next), ppc->next = NULL;
    }
}

int getMaxBool(clause* cnf)   //选择出现次数最多的变元
{
    int* cnt = (int*)malloc(sizeof(int) * (boolCnt * 2 + 1));
    for (int i = 0; i <= boolCnt * 2; i++)  //初始化cnt数组
        cnt[i] = 0;
    for (clause* pc = cnf; pc; pc = pc->next)
        for (node* pn = pc->head; pn; pn = pn->next)
        {
            if (pn->value > 0)
                cnt[pn->value]++;   
            else
                cnt[boolCnt - pn->value]++;

        }
    int maxBool, maxTimes = 0;
    for (int i = 1; i <= boolCnt; i++)   //选择变元的正面
        if (cnt[i] > maxTimes)
            maxTimes = cnt[i], maxBool = i;
    if (maxTimes == 0)  //只剩下变元的反
    {
        for (int i = boolCnt + 1; i <= boolCnt * 2; i++)
            if (cnt[i] > maxTimes)
                maxTimes = cnt[i], maxBool = boolCnt - i;  
    }
    free(cnt);
    return maxBool;
}

int getFirstBool(clause* cnf)
{
	clause * pc = cnf;
	return ABS(pc -> head -> value);
} 

int getMaxBool_2(clause* cnf)  //选取总出现次数最多的变元
{
    int* cnt = (int*)malloc(sizeof(int) * (boolCnt * 2 + 1));
    for (int i = 0; i <= boolCnt * 2; i++)  //初始化cnt数组
        cnt[i] = 0;
    for (clause* pc = cnf; pc; pc = pc->next)
        for (node* pn = pc->head; pn; pn = pn->next)
        {
            if (pn->value > 0)
                cnt[pn->value]++;   
            else
                cnt[boolCnt - pn->value]++;
        }
    int maxBool, maxTimes = 0;
    for (int i = 1; i <= boolCnt; i++)   //选择变元的正面
        if (cnt[i] > maxTimes)
            maxTimes = cnt[i], maxBool = i;
    if (maxTimes == 1)  //只剩下变元的反
    {
        for (int i = boolCnt + 1; i <= boolCnt * 2; i++)
            if (cnt[i] > maxTimes)
                maxTimes = cnt[i], maxBool = boolCnt - i;  
    }
    free(cnt);
    return maxBool;
}

int getNextBool_3(clause* cnf)              //选取在短子句总出现次数最多的变元
{
    double* weight = (double*)malloc(sizeof(double) * (boolCnt + 1));
    
    for (int i = 0; i <= boolCnt; i++)
        weight[i] = 0.0;
    
	for (clause* pc = cnf; pc; pc = pc->next)
        for (node* pn = pc->head; pn; pn = pn->next)
        if(pn -> value)
            weight[ABS(pn->value)] += pow(2.0, (double)(-(pc->num)));
//				weight[ABS(pn->value)] += -(pc->num);	
    double maxWeight = 0 ;
    int maxBool=0 ;
    for (int i = 1; i <= boolCnt; i++)
        if (weight[i] > maxWeight)
            maxWeight = weight[i], maxBool = i;
    free(weight);
    return maxBool;
}

int getNextBool_4(clause* cnf)            //选取在短子句出现次数最多的变元
{
    double* weight = (double*)malloc(sizeof(double) * (boolCnt * 2 + 1));
    for (int i = 0; i <= boolCnt * 2; i++)
        weight[i] = 0.0;
    for (clause* pc = cnf; pc; pc = pc->next)
        for (node* pn = pc->head; pn; pn = pn->next)
        {
            if (pn->value > 0)
                weight[pn->value] += pow(2.0, (double)(-(pc->num)));
            else
                weight[boolCnt - pn->value] += pow(2.0, (double)(-(pc->num)));
        }
    double maxWeight = 0.0;
    int maxBool=0;
    for (int i = 1; i <= boolCnt; i++)
        if (weight[i] + weight[i + boolCnt] > maxWeight)
        {
            maxWeight = weight[i] + weight[i + boolCnt], maxBool = i;
        }
    if (weight[maxBool] < weight[maxBool + boolCnt])
        maxBool = -maxBool;
    free(weight);
    return maxBool;
}

bool DPLL(clause*& cnf, int* v, int satORsudoku)
{
    int flag = 1;
    clause* pc;
    while (flag)//能找到单子句
    {
        flag = 0;
        pc = cnf;
        
        while (pc && !isUnitClause(pc))
		{
			//遍历寻找单子句
            pc = pc->next;
		}  
        if (pc != NULL)//找到单子句pc
        {
            if (pc->head->value > 0)   //在结果数组中保存pc的值
                v[pc->head->value] = 1;  
            else
                v[-pc->head->value] = 0;
            delelteSingleClause(pc, cnf);  //根据单子句规则化简
            if (cnf == NULL)        //子句已完全化简
                return true;
            else if (emptyClause(cnf)) //存在空子句
                return false;
            flag = 1;   //找到了单子句
        }
        
    }
    int maxBool;

    if (branchRule == 1) maxBool = getFirstBool(cnf);
    if(branchRule == 2) maxBool = getMaxBool(cnf);
    else if(branchRule == 3) maxBool = getNextBool_3(cnf);
    else if(branchRule == 4) maxBool = getNextBool_4(cnf);

    clause* newSingleClause = (clause*)malloc(sizeof(clause)), *forgery;
    newSingleClause->head = (node*)malloc(sizeof(node));
    newSingleClause->next = NULL;
    newSingleClause->head->value = maxBool;
    newSingleClause->head->next = NULL;
    newSingleClause->num = 1;
    getForgery(forgery, cnf);     //复制当前cnf 为回溯做准备
    addClause(newSingleClause, forgery);      //加入单子句
	
    if (DPLL(forgery, v, satORsudoku) == true)
    {
    	return true; 
	}
    //如果结果为false
    destroyClause(forgery);  //删除副本
    newSingleClause = (clause*)malloc(sizeof(clause));
    newSingleClause->head = (node*)malloc(sizeof(node));
    newSingleClause->next = NULL;
    newSingleClause->head->value = -maxBool;
    newSingleClause->head->next = NULL;
    newSingleClause->num = 1;
    addClause(newSingleClause, cnf);    //加入相反的单子句
    getForgery(forgery, cnf);
    bool ans = DPLL(forgery, v, satORsudoku); //DPLL
    destroyClause(forgery);   //删除副本
    return ans;  //返回ans
}
