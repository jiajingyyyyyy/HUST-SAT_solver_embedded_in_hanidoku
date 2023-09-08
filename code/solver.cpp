void destroyClause(clause*& cnf)
{
    clause* ppc, * pc2; //ָ���Ӿ��ָ��
    node* pn1, * pn2;   //ָ�����ֵ�ָ��
    ppc = cnf;
    while (ppc) 
    {
        pn1 = ppc->head;   //����ɾ���Ӿ�
        while (pn1)
            pn2 = pn1->next, free(pn1), pn1 = pn2;  //����ɾ������
        pc2 = ppc->next, free(ppc), ppc = pc2;   
    }
    cnf = NULL;
}

void removeClause(clause*& cnf, clause*& cl)
{
    if (cl == cnf) //�����ͷ�Ӿ� 
        cnf = cnf->next;  //ͷ�Ӿ��next��Ϊͷ�Ӿ�
    else
    {
        clause* ppc = cnf;
        while (ppc && ppc->next != cl)
            ppc = ppc->next;     //��λҪɾ�����Ӿ�
        ppc->next = ppc->next->next;
    }
    node* pn1, * pn2;
    for (pn1 = cl->head; pn1;)
        pn2 = pn1->next, free(pn1), pn1 = pn2;  //ɾ������
    free(cl);
    cl = NULL;
}

void removeNode(node*& head, node*& nd)
{
    node* ppn = head;
    if (ppn == nd)  //���Ҫɾ��ͷ�ڵ�
        head = head->next;  //ͷ�ڵ��next��Ϊͷ�ڵ�
    else
    {
        while (ppn && ppn->next != nd)
            ppn = ppn->next;  //��λ�ڵ�
        ppn->next = ppn->next->next;  
    }
    free(nd);
    nd = NULL;
}

status addClause(clause* cl, clause*& cnf)
{
    if (cl)//�ײ巨���뵥�Ӿ�
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
    int n = s->head->value;//Ҫɾ���ı�Ԫ��ֵ
    for (clause* ppc = cnf; ppc; ppc = tmp) //���������Ӿ�
    {
        tmp = ppc->next;//��temp�洢��ǰ�Ӿ��next ��ǰ�Ӿ䱻ɾ��������ҵ���һ�Ӿ�
        for (node* ppn = ppc->head; ppn; ppn = ppn->next)
        {
            if (ppn->value == n)
            {
                removeClause(cnf, ppc);//��������ñ�Ԫ ɾ�����Ӿ�
                break;
            }
            if (ppn->value == -n)
            {
                removeNode(ppc->head, ppn);//��������ñ�Ԫ�ķ� ɾ���ýڵ�
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
    clause* ppc, * pc;  //ָ���Ӿ��ָ��
    node* ppn, * pn;    //ָ�����ֵ�ָ��
    forgery = (clause*)malloc(sizeof(clause));
    forgery->head = (node*)malloc(sizeof(node));
    forgery->next = NULL;
    forgery->head->next = NULL;
    forgery->num = 0;
    //��ʼ������
    for (pc = cnf, ppc = forgery; pc != NULL; pc = pc->next, ppc = ppc->next)//���Ƶ�ǰcnf Ϊ������׼��
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

int getMaxBool(clause* cnf)   //ѡ����ִ������ı�Ԫ
{
    int* cnt = (int*)malloc(sizeof(int) * (boolCnt * 2 + 1));
    for (int i = 0; i <= boolCnt * 2; i++)  //��ʼ��cnt����
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
    for (int i = 1; i <= boolCnt; i++)   //ѡ���Ԫ������
        if (cnt[i] > maxTimes)
            maxTimes = cnt[i], maxBool = i;
    if (maxTimes == 0)  //ֻʣ�±�Ԫ�ķ�
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

int getMaxBool_2(clause* cnf)  //ѡȡ�ܳ��ִ������ı�Ԫ
{
    int* cnt = (int*)malloc(sizeof(int) * (boolCnt * 2 + 1));
    for (int i = 0; i <= boolCnt * 2; i++)  //��ʼ��cnt����
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
    for (int i = 1; i <= boolCnt; i++)   //ѡ���Ԫ������
        if (cnt[i] > maxTimes)
            maxTimes = cnt[i], maxBool = i;
    if (maxTimes == 1)  //ֻʣ�±�Ԫ�ķ�
    {
        for (int i = boolCnt + 1; i <= boolCnt * 2; i++)
            if (cnt[i] > maxTimes)
                maxTimes = cnt[i], maxBool = boolCnt - i;  
    }
    free(cnt);
    return maxBool;
}

int getNextBool_3(clause* cnf)              //ѡȡ�ڶ��Ӿ��ܳ��ִ������ı�Ԫ
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

int getNextBool_4(clause* cnf)            //ѡȡ�ڶ��Ӿ���ִ������ı�Ԫ
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
    while (flag)//���ҵ����Ӿ�
    {
        flag = 0;
        pc = cnf;
        
        while (pc && !isUnitClause(pc))
		{
			//����Ѱ�ҵ��Ӿ�
            pc = pc->next;
		}  
        if (pc != NULL)//�ҵ����Ӿ�pc
        {
            if (pc->head->value > 0)   //�ڽ�������б���pc��ֵ
                v[pc->head->value] = 1;  
            else
                v[-pc->head->value] = 0;
            delelteSingleClause(pc, cnf);  //���ݵ��Ӿ���򻯼�
            if (cnf == NULL)        //�Ӿ�����ȫ����
                return true;
            else if (emptyClause(cnf)) //���ڿ��Ӿ�
                return false;
            flag = 1;   //�ҵ��˵��Ӿ�
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
    getForgery(forgery, cnf);     //���Ƶ�ǰcnf Ϊ������׼��
    addClause(newSingleClause, forgery);      //���뵥�Ӿ�
	
    if (DPLL(forgery, v, satORsudoku) == true)
    {
    	return true; 
	}
    //������Ϊfalse
    destroyClause(forgery);  //ɾ������
    newSingleClause = (clause*)malloc(sizeof(clause));
    newSingleClause->head = (node*)malloc(sizeof(node));
    newSingleClause->next = NULL;
    newSingleClause->head->value = -maxBool;
    newSingleClause->head->next = NULL;
    newSingleClause->num = 1;
    addClause(newSingleClause, cnf);    //�����෴�ĵ��Ӿ�
    getForgery(forgery, cnf);
    bool ans = DPLL(forgery, v, satORsudoku); //DPLL
    destroyClause(forgery);   //ɾ������
    return ans;  //����ans
}
