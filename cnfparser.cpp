int ABS(int a)
{
    return a > 0 ? a : -a;
}

int read(FILE * fp)
{ 
    int flag = 0;
    int x = 0, f = 1;
    char c;
    c = getc(fp);        //�����ַ�
    while (c < '0' || c > '9')     //������
    {
        if (c == '-')
            f = -1, c = getc(fp);
        else
            return inf;           
    }
    while (c >= '0' && c <= '9')    //��������
    {
        x = x * 10 + c - '0';
        c = getc(fp);
        if (c == -1)    //�ļ�����
            flag = 1;
    }
    //����ѭ��ʱcӦΪ�ո� ���� ����EOF
    if (!flag && c != ' ' && c != '\n')  
        return inf;
    return x * f;    //���ض������ֵ�ֵ
}

status ReadCNF(clause*& cnf, int satORsudoku)
{
    FILE* fp;
    if (satORsudoku == SAT)
        fp = fopen(fileName, "r");
    else
        fp = fopen(WfileName, "r");
    if (!fp)
        return ERROR;
    node* pn;
	clause* pc;
    char ch;
	char check[5] = { ' ', 'c', 'n', 'f', ' ' };
	while ((ch = getc(fp)) == 'c')  
	    while ((ch = getc(fp)) != '\n')  //������Ϊcʱ�������з�
	        continue;
	//����ѭ��ʱchӦΪ��p��
	if (ch != 'p')
	       return ERROR;   
	for (int i = 0; i < 5; i++)
	    if ((ch = getc(fp)) != check[i])
		{
		  //��ȡ��p cnf ������
	        return ERROR;	
	    }
    if ((boolCnt = read(fp)) == inf || (clauseCnt = read(fp)) == inf)//�����Ԫ�����Ӿ���
        return ERROR;
    
    cnf = (clause*)malloc(sizeof(clause));
    cnf->next = NULL;
    cnf->head = (node*)malloc(sizeof(node));
    cnf->head->next = NULL;
    cnf->num = 0;
    pc = cnf;  //pc��һ��ָ���Ӿ��ָ��
    pn = cnf->head;   //pn��һ��ָ�����ֵ�ָ
	    //��ʼ������
    for (int i = 1; i <= clauseCnt; i++)
    {
        int dat;
        if ((dat = read(fp)) == inf)
            return ERROR;
        while (dat)//dat������ֹ��0ʱ��ѭ����ȡ���������
        {
            pc->num++;   
            pn->value = dat;
            pn->next = (node*)malloc(sizeof(node));
            if ((dat = read(fp)) == inf)
                return ERROR;
            if (!dat)
                pn->next = NULL;
            pn = pn->next;
        }
        pc->next = (clause*)malloc(sizeof(clause));
        pc->next->num = 0;
        pc->next->head = (node*)malloc(sizeof(node));
        if (i == clauseCnt)
        {
            pc->next = NULL;
            break;
        }
        pc = pc->next;
        pn = pc->head;
    }
    //��ȡcnf�ļ�
    fclose(fp);
    return OK;printf("WWWW\n");
}
status printCNF(int s, int* v, double t1, double t2)
{
    FILE* fp;
    if (!(fp = fopen(fileName, "w+")))//����res�ļ�
    {
        printf("�ļ�����ʧ��!\n");
        return ERROR;
    }
    fprintf(fp, "s %d\nv ", s);
    if (s)//���������
        for (int i = 1; i <= boolCnt; i++)//д����
        {
            if (v[i])
                fprintf(fp, "%d ", i);
            else
                fprintf(fp, "%d ", -i);
        }
    fprintf(fp, "\nt(�Ż�ǰ) %lf ms", t1 * 1000);
    fprintf(fp, "\nt(�Ż���) %lf ms", t2 * 1000);
    fclose(fp);
    return OK;
}
