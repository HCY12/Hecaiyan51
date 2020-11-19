nclude<stdio.h>
#include<windows.h>
#include<time.h>
#pragma warning(disable:4996)
typedef int Elemtype;
typedef struct node
{
	Elemtype data;
	struct node *next;
} Node, *LinkList;
LinkList Createlist()//1．随机产生或键盘输入一组元素，建立一个带头结点的单向链表（无序）。
{
	LinkList L, p;
	L = (LinkList)malloc(sizeof(Node));     //建立空表   1.建立头结点
	L->next = NULL;                         //           2.建立空的单链表L
	//printf("please input the numbers :\n");
	Elemtype x;
	//scanf("%d", &x);          //手动输入
	x = rand()%20;             //随机产生0-19之间的数
	int n = 10;                //产生10个
	while (n)                 //头插法
	{
		p = (LinkList)malloc(sizeof(Node));
		p->data = x;
		p->next = L->next;
		L->next = p;           //将结点p头插入链表L 
		x = rand() % 20;    
		n--;
		//scanf("%d", &x);              //手动输入
	}
	return L;
}
//2．遍历单向链表。
void put(LinkList H)
{
	LinkList L = H;
	LinkList q;
	while (L->next != NULL)
	{
		L = L->next;
		q = L;
		printf("%d ", q->data);
	}
	printf("\n");
}
//3．把单向链表中元素逆置（不允许申请新的结点空间）。
void nizhi(LinkList h)//将链表逆置
{
	LinkList l = h;
	LinkList p, q;
	p = l->next;
	l->next = NULL;
	while (p)
	{
		q = p;
		p = p->next;
		q->next = l->next;
		l->next = q;
	}
}
//4.实现在非递减有序链表中删除值为x的结点
void deleted(LinkList H,int x)
{
	LinkList L = H, q, p;
	while (L->next != NULL)
	{
		p = L->next;
		if (p->data  == x)
		{
			q = p->next;
			free(p);
			L->next = q;
			break;
		}
		L = L->next;
	}
	if (L->next == NULL){
		printf("没有该元素!!\n");
	}
}
//5．编写在非递减有序链表中插入一个元素使链表元素仍有序的函数，并利用该函数建立一个非递减有序单向链表。
void insert(LinkList H, int x)
{
	LinkList L = H;
	LinkList p;
	LinkList q = (LinkList)malloc(sizeof(Node));
	while (L->next != NULL)
	{
		L = L->next;
		p = L;
		if (p->data >= x&&p->next->data >= x){       //考虑加入的元素比H中所有元素都小
			q->data = x;
			q->next = p->next;
			p->next = q;
			q = NULL;
			break;
		}
		if (p->data <= x&&p->next->data <= x){       //考虑加入的元素比H中所有元素都大
			q->data = x;
			q->next = p->next;
			p->next = q;
			q = NULL;
			break;
		}
		if (p->data <= x&&p->next->data >= x)
		{
			q->data = x;
			q->next = p->next;
			p->next = q;
			q = NULL;
			break;
		}
	}
	if (q != NULL)
	{
		q = (LinkList)malloc(sizeof(Node));
		q->data = x;
		q->next = NULL;
		L->next = q;
	}
}
//6.构建非递减有序单向链表->递增；
LinkList sort(LinkList h)
{
	int i = 0;
	if (h == NULL){
		return NULL;
	}
	LinkList _head = h->next;
	while (_head != NULL){
		_head = _head->next;
		i++;
	}
	LinkList p = h->next;
	LinkList p_pre = p;
	while (i - 1){
		LinkList p_pre = h->next;;
		Elemtype temp = p_pre->data;
		p = h->next->next;
		while (p != NULL){
			if (temp <= (p->data))
			{
				p = p->next;
			}
			else
			{
				Elemtype temp_change;
				temp_change = p->data;
				p->data = p_pre->data;
				p_pre->data = temp_change;
				p = p->next;
			}
			p_pre = p_pre->next;
			temp = p_pre->data;
		}
		p_pre->next = NULL;
		i--;
	}
	return h;
}
//7．利用算法1建立两个非递减有序单向链表，然后合并成一个非递减链表。
void hebing(LinkList H, LinkList L)
{
	LinkList p = H;
	while (p->next != NULL)
	{
		p = p->next;
		insert(L, p->data);
	}
	sort(L);
}
//菜单
void menu()
{
	printf("##############################################\n");
	printf("##################单链表管理##################\n");
	printf("#################1.建立单链表#################\n");
	printf("#################2.遍历单链表#################\n");
	printf("#################3.逆置单链表#################\n");
	printf("#############4.排序为非递减单链表#############\n");
	printf("######5.将两个链表合并成一个非递减链表########\n");
	printf("#########6.插入一个元素使链表仍然有序#########\n");
	printf("#################7.删除元素###################\n");
	printf("###################8.退出#####################\n");
	printf("please enter your choice#");
}
//主函数
int main()
{
	srand((unsigned long)time(NULL));
	int i = 1;
	int t = 0;
	LinkList S = Createlist();
	LinkList W;
	LinkList L;
	LinkList Q;
	while (i){
		menu();
		int choice = 0;
		scanf("%d", &choice);
		switch (choice){
			case 1:
				S;
				printf("已建立有10个随机数的单链表!\n");
				break;
			case 2:  
				printf("链表S:");
				put(S);
				break;
			case 3:
				printf("逆置链表S:");
				nizhi(S);
				put(S);
				break;
			case 4:
				printf("排序后的非递减有序链表S:");
				L = sort(S);
				put(L);
				break;
			case 5:
				Q = Createlist();
				sort(Q);
				printf("新的链表非递减有序S:");
				put(Q);
				printf("\n");
				W = Createlist();
				sort(W);
				printf("新的链表非递减有序W:");
				put(W);
				printf("\n");
				hebing(Q, W);
				printf("合并后的非递减有序链表S+W:");
				put(W);
				printf("\n");
				break;
			case 6:
				printf("please enter he element you want to insert:");
				scanf("%d", &t);
				sort(S);
				insert(S, t);
				printf("基于原链表S，加入%d后的非递减有序链表S:", t);
				put(S);
				deleted(S, t);
				break;
			case 7:
				printf("please enter your want Deleted elements:");
				scanf("%d", &t);
				deleted(S, t);
				sort(S);
				printf("基于原链表S，删除%d后的非递减有序链表S:", t);
				put(S);
				break;
			case 8:
				i = 0;
				break;
			default:
				printf("输入错误，请重新输入!");
				break;
		}
	}
	system("pause");
	return 0;
}
