# pragma once

# define PATH_FOLDER "d:\\LibSystem" 
# define CREATE_FOLDER "md d:\\LibSystem"
# define PATH_DEPARTMENT "d:\\LibSystem\\DepartmentInfo.dat"
# define PATH_CARD "d:\\LibSystem\\CardInfo.dat"
# define PATH_RECORD "d:\\LibSystem\\RecordInfo.dat"
# define PATH_BOOK "d:\\LibSystem\\BookInfo.dat"

# define FAIL_FOPEN "File open failed.Exit."
# define FAIL_FCLOSE "File close failed.Exit."
# define FAIL_READDATA "Failed to read data.Exit."
# define FAIL_SAVE "Failed to save data.Exit."

# define DEPARTMENT "\t\t\t**********院系信息**********\n"
# define CARD "\t\t\t**********借书证信息**********\n"
# define RECORD "\t\t\t**********借阅记录**********\n"
# define BOOK "\t\t\t**********图书信息**********\n"

# define PRINT_DEPARTMENT "编号：%u\n院系名称：%s\n地址：%s\n联系方式：%lu\n"
# define PRINT_CARD "所属院系编号：%u\n借书证号：%u\n姓名：%s\nE-mail:%s\n手机号:%lu\n"
# define PRINT_RECORD "借书证号：%u\n图书号：%u\n借书时间:%u\n归还限时:%u天\n还书时间:%d\n"
# define PRINT_BOOK "书籍编号：%u\n书名：%s\n种类：%s\n"

typedef struct book {
	unsigned int book_num;//考虑到院系编号及借书号一般少于11位，故采用unsigned int
	char name[40];
	char class[40];
	struct book * next;
}book,*L_book;

typedef struct record {
	unsigned int Lib_card_num;
	unsigned int book_num;
	unsigned int borrow_time;//设定该值及之下的还书日期形式示例为：20160816
	unsigned int return_period;//设定该值为天数
	int return_time;//尚未归还则显示-1

	struct record * next;
}record,*L_record;

typedef struct Lib_card {
	unsigned int department_num;
	unsigned int Lib_card_num;
	char name[20];
	char E_mail[40];
	unsigned long tel;//电话号码一般大于11位，故采用unsigned long

	struct Lib_card * next;
	L_record head_record;
}card, *L_card;

typedef struct department {
	unsigned int department_num;
	char name[40];
	char address[100];
	unsigned long tel;

	struct department * next;
	L_card head_card;
}department, *L_department;

L_department SysDataReadI();
L_book SysDataReadII();
void SysDataSaveI(const L_department head);
void SysDataSaveII(const L_book head);

L_card CardFound(L_department head, unsigned int num);
L_card RecordCheck(L_department head);
void RecordAdd(L_department head);
void RecordDel(L_department head);
void RecordChange(L_department head);
void RecordManagement(L_department head);

L_department DepartmentLook(L_department head);
void DepartmentAdd(L_department head);
void DepartmentDel(L_department head);
void DepartmentChange(L_department head);
void DepartmentManagement(L_department head);

L_department CardCheck(L_department head);
void CardAdd(L_department head);
void CardDel(L_department head);
void CardChange(L_department head);
void CardManagement(L_department head);

void BookLook(L_book head);
void BookAdd(L_book head);
void BookDel(L_book head);
void BookChange(L_book head);
void BookManagement(L_book head);

void ReturnCheck(L_department head);
void DepartmentBorrowCheck(L_department head);
void BorrowCheck(L_department head, L_book head2);
void OtherOptions(L_department head1, L_book head2);

void StartMenu(L_department head1, L_book head2);
