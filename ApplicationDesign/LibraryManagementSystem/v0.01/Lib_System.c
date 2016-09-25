# include <stdio.h>
# include <stdlib.h>
# include <io.h>
# include <string.h>
# include "Lib_System.h"

int main()
{
	L_department head1, p1;
	L_book head2, p;
	L_card p2, tp2;
	L_record p3, tp3;
	char ch;

	if (access(PATH_FOLDER, 0) != 0)//检测文件夹是否存在，不存在则创建
		system(CREATE_FOLDER);
	if ((access(PATH_DEPARTMENT, 0) != 0) || (access(PATH_CARD, 0) != 0) || (access(PATH_RECORD, 0) != 0) || (access(PATH_BOOK, 0) != 0))
	{//若是第一次使用，则会先要求用户输入数据构建链表
		head1 = NULL;
		head2 = NULL;
		

		printf("由于之前的数据为空或数据文件已损坏，请先输入数据.\n");
		printf("Step 1:院系信息\n");
		do
		{
			p1 = (L_department)malloc(sizeof(department));
			printf("院系：\n");
			printf("请输入院系编号：");
			scanf("%u", &p1->department_num);
			getchar();
			printf("请输入院系名称：");
			gets_s(p1->name, 39);
			printf("请输入院系地址：");
			gets_s(p1->address, 99);
			printf("请输入院系联系方式：");
			scanf("%lu", &p1->tel);
			getchar();
			p1->head_card = NULL;

			p1->next = head1;
			head1 = p1;

			do
			{
				printf("是否继续输入院系信息？(Y/N)\n");
				ch = getchar();
				getchar();
			} while ((ch != 'Y') && (ch != 'y') && (ch != 'n') && (ch != 'N'));

		} while ((ch == 'Y') || (ch == 'y'));

		printf("Step 2:借书证信息\n");
		do
		{
			ch = 'Y';
			p2 = (L_card)malloc(sizeof(card));
			printf("借书证：\n");

			printf("请输入所属院系编号：");
			scanf("%u", &p2->department_num);
			getchar();
			printf("请输入借书证编号：");
			scanf("%u", &p2->Lib_card_num);
			getchar();
			printf("请输入姓名：");
			gets_s(p2->name, 19);
			printf("请输入E-mail：");
			gets_s(p2->E_mail, 39);
			printf("请输入联系方式：");
			scanf("%lu", &p2->tel);
			getchar();

			p2->head_record = NULL;
			p2->next = NULL;
			p1 = head1;
			while (p1 != NULL)
			{
				if (p1->department_num == p2->department_num)
				{
					break;
				}
				else
					p1 = p1->next;
			}
			if (p1 == NULL)
			{
				printf("该院系编号不存在，请核对后再输入！\n");
				continue;
			}
			else
			{
				if (p1->head_card == NULL)
					p1->head_card = p2;
				else
				{
					tp2 = p1->head_card;
					while (tp2->next != NULL)
						tp2 = tp2->next;
					tp2->next = p2;
				}
			}

			do
			{
				printf("是否继续输入借书证信息？(Y/N)\n");
				ch = getchar();
				getchar();
			} while ((ch != 'Y') && (ch != 'y') && (ch != 'n') && (ch != 'N'));
			
		} while ((ch == 'Y') || (ch == 'y'));

		printf("Step 3:借阅记录：\n");
		do
		{
			ch = 'Y';
			p3 = (L_record)malloc(sizeof(record));

			printf("请输入借阅记录信息\n");
			printf("请输入借书证号：");
			scanf("%u", &p3->Lib_card_num);
			getchar();
			printf("请输入图书编号：");
			scanf("%u", &p3->book_num);
			getchar();
			printf("请输入借书日期（形式例如20160101)：");
			scanf("%u", &p3->borrow_time);
			getchar();
			printf("请输入还书期限天数：");
			scanf("%u", &p3->return_period);
			getchar();
			printf("请输入归还日期（形式为20160101，尚未归还则输入-1）：");
			scanf("%d", &p3->return_time);
			getchar();

			p3->next = NULL;
			p1 = head1;
			while (p1 != NULL)
			{
				p2 = p1->head_card;
				while (p2 != NULL)
				{
					if (p2->Lib_card_num == p3->Lib_card_num)
					{
						tp3 = p2->head_record;
						if (tp3 == NULL)
							p2->head_record = p3;
						else
						{
							while (tp3->next != NULL)
								tp3 = tp3->next;
							tp3->next = p3;
						}
						break;
					}
					else
					{
						p2 = p2->next;
					}
				}
				if (p2 != NULL)
					break;
				else
				{
					p1 = p1->next;
				}
			}
			if (p1 == NULL)
			{
				printf("该借书证号不存在，请核对后再输入！\n");
				continue;
			}

			do
			{
				printf("是否继续输入借阅记录？(Y/N)\n");
				ch = getchar();
				getchar();
			} while ((ch != 'Y') && (ch != 'y') && (ch != 'n') && (ch != 'N'));

		} while ((ch == 'Y') || (ch == 'y'));

		p = head2;
		printf("Step 4:图书信息：\n");
		do
		{
			p = (L_book)malloc(sizeof(book));
			
			printf("请输入图书编号：");
			scanf("%u", &p->book_num);
			getchar();
			printf("请输入书籍名称：");
			gets_s(p->name, 39);
			printf("请输入书籍种类：");
			gets_s(p->class, 39);

			p->next = head2;
			head2 = p;

			do
			{
				printf("是否继续输入图书信息？(Y/N)\n");
				ch = getchar();
				getchar();
			} while ((ch != 'Y') && (ch != 'y') && (ch != 'n') && (ch != 'N'));

		} while ((ch == 'Y') || (ch == 'y'));

		if (head1 != NULL)
			SysDataSaveI(head1);
		if (head2 != NULL)
			SysDataSaveII(head2);
		printf("数据输入完毕，欢迎您的使用。");


	}
	else//若之前存在数据文件则读取信息构建三重链表
	{
		head1 = SysDataReadI();
		head2 = SysDataReadII();
	}

	StartMenu(head1, head2);

	return 0;
}

L_department SysDataReadI()//用来读取L_department的三重链表
{
	L_department head, p;
	L_card p2, tp2;
	L_record p3, tp3;
	FILE * fp_d, *fp_c, *fp_r;

	head = NULL;

	if (((fp_d = fopen(PATH_DEPARTMENT, "rb")) == NULL) || ((fp_c = fopen(PATH_CARD, "rb")) == NULL)
		|| ((fp_r = fopen(PATH_RECORD, "rb")) == NULL))
	{
		printf(FAIL_FOPEN);
		exit(EXIT_FAILURE);
	}

	while (!feof(fp_d))
	{
		p = (L_department)malloc(sizeof(department));
		fread(p, sizeof(department), 1, fp_d);
		if (!feof(fp_d))
		{
			p->head_card = NULL;
			p->next = head;
			head = p;
		}
	}
	
	while (!feof(fp_c))
	{
		p = head;
		p2 = (L_card)malloc(sizeof(card));
		fread(p2, sizeof(card), 1, fp_c);
		p2->next = NULL;
		p2->head_record = NULL;
		if (!feof(fp_c))
		{
			while (p->department_num != p2->department_num)
				p = p->next;
			if (p->department_num == p2->department_num)
			{
				if (p->head_card == NULL)
					p->head_card = p2;
				else
				{
					tp2 = p->head_card;
					while (tp2->next != NULL)
						tp2 = tp2->next;
					tp2->next = p2;
				}
			}
			else
			{
				printf(FAIL_READDATA);
				exit(EXIT_FAILURE);
			}
		}
	}

	

	while (!feof(fp_r))
	{
		p = head;
		p3 = (L_record)malloc(sizeof(record));
		fread(p3, sizeof(record), 1, fp_r);
		p3->next = NULL;
		if (!feof(fp_r))
		{
			tp2 = p->head_card;
			while (tp2 == NULL)
			{
				p = p->next;
				tp2 = p->head_card;
			}
			while (p3->Lib_card_num != tp2->Lib_card_num)
			{
				if (tp2->next != NULL)
					tp2 = tp2->next;
				else
				{
					p = p->next;
					tp2 = p->head_card;
					while (tp2 == NULL)
					{
						p = p->next;
						tp2 = p->head_card;
					}
				}
			}
			if (p3->Lib_card_num == tp2->Lib_card_num)
			{
				if (tp2->head_record == NULL)
					tp2->head_record = p3;
				else
				{
					tp3 = tp2->head_record;
					while (tp3->next != NULL)
						tp3 = tp3->next;
					tp3->next = p3;
				}
			}
			else
			{
				printf(FAIL_READDATA);
				exit(EXIT_FAILURE);
			}
		}
	}

	if ((fclose(fp_c) == EOF) || (fclose(fp_d) == EOF) || (fclose(fp_r) == EOF))
	{
		printf(FAIL_FCLOSE);
		exit(EXIT_FAILURE);
	}
	return head;
}

L_book SysDataReadII()//用来读取L_book的单重链表
{
	L_book p, head;
	FILE * fp;

	head = NULL;

	if ((fp = fopen(PATH_BOOK, "rb")) == NULL)
	{
		printf(FAIL_FOPEN);
		exit(EXIT_FAILURE);
	}

	while (!feof(fp))
	{
		p = (L_book)malloc(sizeof(book));
		fread(p, sizeof(book), 1, fp);
		if (!feof(fp))
		{
			p->next = head;
			head = p;
		}
	}

	if (fclose(fp) == EOF)
	{
		printf(FAIL_FCLOSE);
		exit(EXIT_FAILURE);
	}

	return head;
}

void SysDataSaveI(const L_department head)//保存院系借书证记录的三重链表
{
	FILE * fp_d, *fp_c, *fp_r;
	L_department p_d;
	L_card p_c;
	L_record p_r;
	p_d = head;

	if (((fp_d = fopen(PATH_DEPARTMENT, "wb")) == NULL) || ((fp_c = fopen(PATH_CARD, "wb")) == NULL)
		|| ((fp_r = fopen(PATH_RECORD, "wb")) == NULL))
	{
		printf(FAIL_SAVE);
		exit(EXIT_FAILURE);
	}

	while (p_d != NULL)
	{
		fwrite(p_d, sizeof(department), 1, fp_d);
		p_c = p_d->head_card;
		while (p_c != NULL)
		{
			fwrite(p_c, sizeof(card), 1, fp_c);
			p_r = p_c->head_record;
			while (p_r != NULL)
			{
				fwrite(p_r, sizeof(record), 1, fp_r);
				p_r = p_r->next;
			}
			p_c = p_c->next;
		}
		p_d = p_d->next;
	}

	if ((fclose(fp_c) == EOF) || (fclose(fp_d) == EOF) || (fclose(fp_r) == EOF))
	{
		printf(FAIL_FCLOSE);
		exit(EXIT_FAILURE);
	}

	return;
}

void SysDataSaveII(const L_book head)//保存图书链表
{
	L_book p = head;
	FILE * fp;
	if ((fp = fopen(PATH_BOOK, "wb")) == NULL)
	{
		printf(FAIL_FOPEN);
		exit(EXIT_FAILURE);
	}
	while(p!=NULL)
	{
		fwrite(p, sizeof(book), 1, fp);
		p = p->next;
	}

	if (fclose(fp) == EOF)
	{
		printf(FAIL_FCLOSE);
		exit(EXIT_FAILURE);
	}

	return;
}

void RecordManagement(L_department head)//子菜单之一
{
	int choose;       

	while (1)
	{
		printf("\t\t\t\t****************借阅记录管理******************\n");
		printf("\t\t\t\t\tOption 1:记录查询\n\t\t\t\t\tOption 2:添加记录\n\t\t\t\t\tOption 3:删除记录\n\t\t\t\t\tOption 4:修改记录\n\t\t\t\t\tOption 5:返回上一级\n");
		printf("\t\t\t\t**********************************************\n");
		do
		{
			printf("请输入选择执行的功能序号：");
			scanf("%d", &choose);
			getchar();
		} while (choose > 5 || choose <= 0);

		switch (choose)
		{
		case 1:RecordCheck(head); break;
		case 2:RecordAdd(head); break;
		case 3:RecordDel(head); break;
		case 4:RecordChange(head); break;
		case 5: return;
		}
		if (head != NULL)
			SysDataSaveI(head);
	}
}

L_card CardFound(L_department head,unsigned int num)
{
	L_department p1;
	L_card p2;
	L_record p3;
	p1 = head;
	int i = 1;

	while (p1 != NULL)
	{
		p2 = p1->head_card;
		while (p2 != NULL)
		{
			if (p2->Lib_card_num == num)
				return p2;
			else
				p2 = p2->next;
		}
		p1 = p1->next;
	}

	printf("借书证号未找到！\n");
	return NULL;
}

L_card RecordCheck(L_department head)
{
	unsigned int num;
	L_card p2;
	L_record p3;
	int i = 1;

	printf("请输入对应借书证号：");
	scanf("%u", &num);
	p2 = CardFound(head, num);
	if (p2 == NULL)
		return NULL;
	p3 = p2->head_record;
	if (p3 == NULL)
	{
		printf("该借书证下不存在借书记录.\n");
		return NULL;
	}
	printf(RECORD);
	while (p3 != NULL)
	{
		printf("NO.%d\n", i++);
		printf(PRINT_RECORD, p3->Lib_card_num, p3->book_num, p3->borrow_time, p3->return_period, p3->return_time);
		p3 = p3->next;
	}
	return p2;
}

void RecordAdd(L_department head)
{
	L_department p1;
	L_card p2;
	L_record p,p3;
	p1 = head;
	p = (L_record)malloc(sizeof(record));
	unsigned int num;

	printf("请输入借阅记录信息\n");
	printf("请输入借书证号：");
	scanf("%u", &p->Lib_card_num);
	printf("请输入图书编号：");
	scanf("%u", &p->book_num);
	printf("请输入借书日期（形式例如20160101)：");
	scanf("%u", &p->borrow_time);
	printf("请输入还书期限天数：");
	scanf("%u", &p->return_period);
	printf("请输入归还日期（形式为20160101，尚未归还则输入-1）：");
	scanf("%d", &p->return_time);
	p->next = NULL;

	p2 = CardFound(head, p->Lib_card_num);
	if (p2 == NULL)
		return;
	p3 = p2->head_record;
	if (p3 == NULL)
		p2->head_record = p;
	else
	{
		while (p3->next != NULL)
			p3 = p3->next;
		p3->next = p;
	}
	return;
}

void RecordDel(L_department head)
{
	unsigned int num;
	L_card p2;
	L_record p3, p;
	int i = 1;

	p2 = RecordCheck(head);
	if (p2 == NULL)
		return;
	p3 = p2->head_record;
	printf("请输入要删除记录的序号：");
	scanf("%d", &i);
	if (i == 1)
	{
		p2->head_record = p3->next;
	}
	else
	{
		while (i--)
		{
			if (i == 1)
				p = p3;
			p3 = p3->next;
		}
		p->next = p3;
	}
}

void RecordChange(L_department head)
{
	L_card p2;
	L_record p3;
	int i = 1;

	p2 = RecordCheck(head);
	if (p2 == NULL)
		return;
	p3 = p2->head_record;
	printf("请输入要修改记录的序号：");
	scanf("%d", &i);
	while (--i)
		p3 = p3->next;
	printf("请输入修改后的借阅记录信息\n");
	printf("请输入图书编号：");
	scanf("%u", &p3->book_num);
	printf("请输入借书日期（形式例如20160101)：");
	scanf("%u", &p3->borrow_time);
	printf("请输入还书期限天数：");
	scanf("%u", &p3->return_period);
	printf("请输入归还日期（形式为20160101，尚未归还则输入-1）：");
	scanf("%d", &p3->return_time);

	return;
}

void DepartmentManagement(L_department head)
{
	int choose;

	while (1)
	{
		printf("\t\t\t\t****************院系信息管理******************\n");
		printf("\t\t\t\t\tOption 1:院系一览\n\t\t\t\t\tOption 2:添加院系\n\t\t\t\t\tOption 3:删除院系\n\t\t\t\t\tOption 4:修改院系信息\n\t\t\t\t\tOption 5:返回上一级\n");
		printf("\t\t\t\t**********************************************\n");
		do
		{
			printf("请输入选择执行的功能序号：");
			scanf("%d", &choose);
			getchar();
		} while (choose > 5 || choose <= 0);

		switch (choose)
		{
		case 1:DepartmentLook(head); break;
		case 2:DepartmentAdd(head); break;
		case 3:DepartmentDel(head); break;
		case 4:DepartmentChange(head); break;
		case 5:return;
		}
		if (head != NULL)
			SysDataSaveI(head);
	}
}

L_department DepartmentLook(L_department head)
{
	L_department p;
	p = head;
	int i = 1;
	if (head == NULL)
	{
		printf("院系信息不存在!\n");
		return NULL;
	}
	printf(DEPARTMENT);
	while (p != NULL)
	{
		printf("NO.%d\n", i++);
		printf(PRINT_DEPARTMENT, p->department_num, p->name, p->address, p->tel);
		p = p->next;
	}

	return head;
}

void DepartmentAdd(L_department head)
{
	L_department p, tp;
	p = head;
	tp = (L_department)malloc(sizeof(department));

	if (head == NULL)
	{
		printf("你遇到了程序正常运行永远也不会遇到的问题！链表头竟然为NULL!\n");
		return;
	}
	printf("请输入院系编号：");
	scanf("%u", &tp->department_num);
	getchar();
	printf("请输入院系名称：");
	gets_s(tp->name, 39);
	printf("请输入院系地址：");
	gets_s(tp->address, 99);
	printf("请输入院系联系方式：");
	scanf("%lu", &tp->tel);
	tp->next = NULL;
	tp->head_card = NULL;

	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = tp;

	return;
}

void DepartmentDel(L_department head)
{
	L_department p, tp;
	p = head;
	int i;

	if(DepartmentLook(head)==NULL)
		return;
	printf("请输入要删除院系对应的序号：");
	scanf("%d", &i);
	if (i == 1)
	{
		p->department_num = p->next->department_num;
		p->tel = p->next->tel;
		strcpy(p->address, p->next->address);
		strcpy(p->name, p->next->name);
		p->head_card = p->next->head_card;

		head->next = head->next->next;
	}
	else
	{
		while (i--)
		{
			if (i == 1)
				tp = p;
			p = p->next;
		}
		tp->next = p;
	}
	return;
}

void DepartmentChange(L_department head)
{
	L_department p;
	p = head;
	int i = 1;
	
	if (DepartmentLook(head) == NULL)
		return;
	printf("请输入要修改院系对应的序号：");
	scanf("%d", &i);
	getchar();;
	while (--i)
		p = p->next;
	printf("请输入院系名称：");
	gets_s(p->name, 39);
	printf("请输入院系地址：");
	gets_s(p->address, 99);
	printf("请输入院系联系方式：");
	scanf("%lu", &p->tel);

	return;
}

void CardManagement(L_department head)
{
	int choose;

	while (1)
	{
		printf("\t\t\t\t****************借书证件管理******************\n");
		printf("\t\t\t\t\tOption 1:添加借书证\n\t\t\t\t\tOption 2:删除借书证\n\t\t\t\t\tOption 3:修改借书证信息\n\t\t\t\t\tOption 4:查询院系下的借书证\n\t\t\t\t\tOption 5:返回上一级\n");
		printf("\t\t\t\t**********************************************\n");
		do
		{
			printf("请输入选择执行的功能序号：");
			scanf("%d", &choose);
			getchar();
		} while (choose > 5 || choose <= 0);
		
		switch (choose)
		{
		case 1:CardAdd(head); break;
		case 2:CardDel(head); break;
		case 3:CardChange(head); break;
		case 4:CardCheck(head); break;
		case 5:return;
		}
		if (head != NULL)
			SysDataSaveI(head);
	}
}

L_department CardCheck(L_department head)
{
	L_department p;
	L_card p2;
	int i;
	p = head;

	if (DepartmentLook(head) == NULL)
		return NULL;
	printf("请输入对应院系序号：");
	scanf("%d", &i);
	while (--i)
		p = p->next;
	if ((p2 = p->head_card) == NULL)
	{
		printf("该院系下无借书证信息！\n");
		return NULL;
	}
	printf(CARD);
	i = 1;
	while (p2 != NULL)
	{
		printf("NO.%d\n", i++);
		printf(PRINT_CARD,p2->department_num,p2->Lib_card_num,p2->name,p2->E_mail,p2->tel);
		p2 = p2->next;
	}
	return NULL;
}

void CardAdd(L_department head)
{
	L_department p1;
	L_card p2, p;
	p1 = head;
	p = (L_card)malloc(sizeof(card));

	printf("请输入所属院系编号：");
	scanf("%u", &p->department_num);
	getchar();
	printf("请输入借书证编号：");
	scanf("%u", &p->Lib_card_num);
	getchar();
	printf("请输入姓名：");
	gets_s(p->name, 19);
	printf("请输入E-mail：");
	gets_s(p->E_mail, 39);
	printf("请输入联系方式：");
	scanf("%lu", &p->tel);
	p->next = NULL;
	p->head_record = NULL;

	while (p1 != NULL)
	{
		if (p1->department_num == p->department_num)
		{
			p2 = p1->head_card;
			if (p2 == NULL)
				p1->head_card = p;
			else
			{
				while (p2->next != NULL)
					p2 = p2->next;
				p2->next = p;
			}
			return;
		}
		p1 = p1->next;
	}
	printf("没有找到对应院系！\n");
	return;
}

void CardDel(L_department head)
{
	unsigned int num;
	L_department p1;
	L_card p2, p;
	p1 = head;

	if (head == NULL)
	{
		printf("你遇到了程序正常运行永远也不会遇到的问题！链表头竟然为NULL!\n");
		return;
	}
	printf("请输入要删除的借书证号：");
	scanf("%u", &num);
	while (p1 != NULL)
	{
		p = NULL;
		p2 = p1->head_card;
		while (p2 != NULL)
		{
			if (p2->Lib_card_num == num)
			{
				if (p == NULL)
					p1->head_card = p2->next;
				else
					p->next = p2->next;
				return;
			}
			else
			{
				p = p2;
				p2 = p2->next;
			}
		}
		p1 = p1->next;
	}
	printf("借书证号不存在！\n");
	return;
}

void CardChange(L_department head)
{
	unsigned int num;
	L_department p1;
	L_card p2;
	p1 = head;

	if (head == NULL)
	{
		printf("你遇到了程序正常运行永远也不会遇到的问题！链表头竟然为NULL!\n");
		return;
	}
	printf("请输入要修改的借书证号：");
	scanf("%u", &num);
	getchar();
	while (p1 != NULL)
	{
		p2 = p1->head_card;
		while (p2 != NULL)
		{
			if (p2->Lib_card_num == num)
			{
				printf("请输入姓名：");
				gets_s(p2->name, 19);
				printf("请输入E-mail：");
				gets_s(p2->E_mail, 39);
				printf("请输入联系方式：");
				scanf("%lu", &p2->tel);
				return;
			}
			else
				p2 = p2->next;
		}
		p1 = p1->next;
	}
	printf("借书证号未找到！\N");
	return;
}

void BookManagement(L_book head)
{
	int choose;

	while (1)
	{
		printf("\t\t\t\t****************图书信息管理******************\n");
		printf("\t\t\t\t\tOption 1:添加图书\n\t\t\t\t\tOption 2:删除图书\n\t\t\t\t\tOption 3:修改图书信息\n\t\t\t\t\tOption 4:图书总览\n\t\t\t\t\tOption 5:返回上一级\n");
		printf("\t\t\t\t**********************************************\n");
		do
		{
			printf("请输入选择执行的功能序号：");
			scanf("%d", &choose);
			getchar();
		} while (choose > 5 || choose <= 0);

		switch (choose)
		{
		case 1:BookAdd(head); break;
		case 2:BookDel(head); break;
		case 3:BookChange(head); break;
		case 4:BookLook(head); break;
		case 5:return;
		}
		if (head != NULL)
			SysDataSaveII(head);
	}
}

void BookLook(L_book head)
{
	L_book p;
	p = head;
	int i = 1;

	if (head == NULL)
	{
		printf("找不到图书信息！\n");
		return;
	}
	printf(BOOK);
	while (p != NULL)
	{
		printf("NO.%d\n", i++);
		printf(PRINT_BOOK, p->book_num, p->name, p->class);
		p = p->next;
	}
	return;
}

void BookAdd(L_book head)
{
	L_book p, tp;
	tp = (L_book)malloc(sizeof(book));

	if (head == NULL)
	{
		printf("你遇到了程序正常运行永远也不会遇到的问题！链表头竟然为NULL!\n");
		return;
	}
	printf("请输入图书编号：");
	scanf("%u", &tp->book_num);
	getchar();
	printf("请输入书籍名称：");
	gets_s(tp->name, 39);
	printf("请输入书籍类型：");
	gets_s(tp->class, 39);
	tp->next = NULL;
	p = head;

	while (p->next != NULL)
		p = p->next;
	p->next = tp;

	return;
}

void BookDel(L_book head)
{
	unsigned int num;
	L_book p, tp;
	p = head;
	tp = NULL;

	if (head == NULL)
	{
		printf("你遇到了程序正常运行永远也不会遇到的问题！链表头竟然为NULL!\n");
		return;
	}
	printf("请输入要删除图书的编号：");
	scanf("%u", &num);
	
	while (p != NULL)
	{
		if (p->book_num == num)
		{
			if (tp == NULL)
			{
				head->book_num = p->next->book_num;
				strcpy(head->name, p->next->name);
				head->next = p->next->next;
			}
			else tp->next = p->next;
			return;
		}
		else
		{
			tp = p;
			p = p->next;
		}
	}
		printf("该图书编号不存在！");
		return;
}

void BookChange(L_book head)
{
	unsigned int num;
	L_book p;
	p = head;

	printf("请输入要修改的图书的编号：");
	scanf("%u", &num);
	getchar();
	while (p != NULL)
	{
		if (p->book_num == num)
		{
			printf("请输入书籍名称：");
			gets_s(p->name, 39);
			printf("请输入书籍类型：");
			gets_s(p->class, 39);
			return;
		}
		else
			p = p->next;
	}
		printf("该图书编号不存在！");
		return;
}

void OtherOptions(L_department head1, L_book head2)
{
	int choose;

	while (1)
	{
		printf("\t\t\t\t****************其它相关功能******************\n");
		printf("\t\t\t\t\tOption 1:某书籍被借阅次数\n\t\t\t\t\tOption 2:某院系借阅总次数\n\t\t\t\t\tOption 3:院系下书籍未归还统计\n\t\t\t\t\tOption 4:返回上一级\n");
		printf("\t\t\t\t**********************************************\n");
		do
		{
			printf("请输入选择执行的功能序号：");
			scanf("%d", &choose);
		} while (choose > 4 || choose <= 0);

		switch (choose)
		{
		case 1:BorrowCheck(head1,head2); break;
		case 2:DepartmentBorrowCheck(head1); break;
		case 3:ReturnCheck(head1); break;
		case 4:return;
		}
	}
}

void BorrowCheck(L_department head,L_book head2)
{
	L_department p1;
	L_card p2;
	L_record p3;
	L_book p4;
	unsigned int num;
	int i = 0;

	printf("请输入要查询图书的编号：");
	scanf("%u", &num);

	p4 = head2;
	while (p4 != NULL)
	{
		if (p4->book_num == num)
			i++;
		p4 = p4->next;
	}
	if (i == 0)
	{
		printf("这本书不存在！\n");
		return;
	}
	p1 = head;
	i = 0;
	while (p1 != NULL)
	{
		p2 = p1->head_card;
		while (p2 != NULL)
		{
			p3 = p2->head_record;
			while (p3 != NULL)
			{
				if (p3->book_num == num)
					i++;
				p3 = p3->next;
			}
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	printf("该图书一共被借阅%d次！\n", i);
	return;
}

void DepartmentBorrowCheck(L_department head)
{
	L_department p1;
	L_card p2;
	L_record p3;
	unsigned int num;
	int i = 0;
	p1 = head;

	printf("请输入想查询的院系编号：");
	scanf("%u", &num);
	while (p1 != NULL)
	{
		if (p1->department_num == num)
		{
			p2 = p1->head_card;
			while (p2 != NULL)
			{
				p3 = p2->head_record;
				while (p3 != NULL)
				{
					i++;
					p3 = p3->next;
				}
				p2 = p2->next;
			}
			printf("该院系借阅次数共计%d次！\n", i);
			return;
		}
		else
			p1 = p1->next;
	}
	printf("找不到该院系！\n");
	return;
}

void ReturnCheck(L_department head)
{
	L_department p1;
	L_card p2;
	L_record p3;
	unsigned num;
	int i, j;
	j = 0;
	int sign = 0;
	p1 = head;

	printf("请输入要查询的院系编号：");
	scanf("%u", &num);

	while (p1 != NULL)
	{
		if(num==p1->department_num)
		{
			sign = 1;
			p2 = p1->head_card;
			while (p2 != NULL)
			{
				p3 = p2->head_record;
				i = 0;
				while (p3 != NULL)
				{
					if (p3->return_time == -1)
						i++;
					p3 = p3->next;
				}
				if (i > 0)
				{
					printf("借书证%u共计%d本书未归还！\n", p2->Lib_card_num, i);
					j++;
				}
				p2 = p2->next;
			}
		}
		p1 = p1->next;
	}
	if (j == 0)
		printf("该院系学生无未归还记录!\n");
	if (sign == 0)
		printf("该院系不存在！\n");
	return 0;
}

void StartMenu(L_department head1,L_book head2)//主菜单
{
	int choose;

	while (1)
	{
		printf("\n\n\t\t\t\t****************高校图书管理系统**************\n");
		printf("\t\t\t\t\tOption 1:院系管理\n\t\t\t\t\tOption 2:借书证管理\n\t\t\t\t\tOption 3:借阅记录管理\n\t\t\t\t\tOption 4:图书信息管理\n"
			"\t\t\t\t\tOption 5:其他\n\t\t\t\t\tOption 6:退出\n");
		printf("\t\t\t\t**********************************************\n");
		do
		{
			printf("请输入选择执行的功能序号：");
			scanf("%d", &choose);
		} while (choose > 6 || choose <= 0);

		switch (choose)
		{
		case 1:DepartmentManagement(head1); break;
		case 2:CardManagement(head1); break;
		case 3:RecordManagement(head1); break;
		case 4:BookManagement(head2); break;
		case 5:OtherOptions(head1, head2); break;
		case 6: 
			{
				if(head1!=NULL)
					SysDataSaveI(head1);
				if(head2!=NULL)
					SysDataSaveII(head2);
				exit(EXIT_SUCCESS);
			}
		}
	}
	return;
}
