#include <iostream>
#include <string>
#include <queue>
#include <Windows.h>
#include <fstream>
using namespace std;
const int MAX = 1000;

struct Node {
	string name = "None", Email="None";
	long long age = 0, TEL = 0;
	Node* next = NULL;
};

Node read[100];
int n = 0;

class Book {
public:
	Book();
	void CreateBook();
	void TravalBook();
	void GetLength();
	bool IsEmpty();
	Node* FindName();
	Node* FindTEL();
	void InsertAtEnd();
	void DeleteAll();
	void Delete();
	void SaveNow();
	void Read();
private:
	Node* head;
};

Book::Book()
{
	head = new Node();
	head->age = head->TEL = 0;
	head->Email = head->name = "None";
	head->next = NULL;
}

void Book::CreateBook()
{
	int n;
	cout << "Input the number:" << endl;
	cin >> n;
	Node* pnew, * ptemp;
	ptemp = head;
	if (n <= 0) {
		cout << "输入的节点有误" << endl;
		return;
	}
	for (int i = 0; i < n; i++) {
		cout << endl;
		pnew = new Node;
		cout << "请输入姓名：";
		cin >> pnew->name;
		cout << "请输入年龄：";
		cin >> pnew->age;
		cout << "请输入手机号码：";
		cin >> pnew->TEL;
		cout << "请输入电子邮箱：";
		cin >> pnew->Email;	
		ptemp->next = pnew;
		pnew->next = NULL;
		ptemp = pnew;
	}
}

void Display(Node* p)
{
	cout << "name: " << p->name << endl
		<< "age: " << p->age << endl
		<< "Tel: " << p->TEL << endl
		<< "Email: " << p->Email << endl << endl;
}

void Book::TravalBook()
{
	if (IsEmpty()) {
		cout << "当前无联系人!" << endl;
		return;
	}
	else {
		Node* p = head->next;
		while (p != NULL) {
			Display(p);
			p = p->next;
		}
	}
	cout << endl;
}

void Book::GetLength()
{
	int count = 0;
	Node* p = head->next;
	while (p != NULL) {
		count++;
		p = p->next;
	}
	cout << "联系人数为:" << count << endl;
}

bool Book::IsEmpty()
{
	if (head->next == NULL) {
		return true;
	}
	return false;
}

Node* Book::FindName()
{
	cout << "请输入姓名:" << endl;
	string name;
	cin >> name;
	Node* p = head->next;
	while (p != NULL) {
		if (p->name == name)
			break;
		p = p->next;
	}
	if (p != NULL) {
		cout << "Find it!" << endl;
	}
	else
		cout << "Can not find it!" << endl;
	return p;
}

Node* Book::FindTEL()
{
	cout << "请输入号码";
	long long tel;
	cin >> tel;
	Node* p = head->next;
	while (p != NULL) {
		if (p->TEL == tel)
			break;
		p = p->next;
	}
	if (p != NULL) {
		cout << "Find it!" << endl;
	}
	else
		cout << "Can not Find it!" << endl;
	return p;
}

void Book::InsertAtEnd()
{
	Node* pnew = new Node;
	cout << "请输入姓名：";
	cin >> pnew->name;
	cout << "请输入手机号码：";
	cin >> pnew->TEL;
	cout << "请输入电子邮箱：";
	cin >> pnew->Email;
	cout << "请输入年龄：";
	cin >> pnew->age;
	pnew->next = head;
	Node* p = head;
	while (p->next != NULL)
		p = p->next;
	p->next = pnew;
}

void Book::DeleteAll()
{
	Node* p = head->next;
	Node* ptemp = new Node;
	while (p != NULL) {
		ptemp = p;
		p->next = p;
		ptemp->next = NULL;
		delete ptemp;
	}
	head->next = NULL;
}

void Book::Delete()
{
	cout << "请选择查找待删联系人:" << endl
		<< "1.name\t2.Telephone\t3.返回上一级" << endl;
	int choice;
	cin >> choice;
	Node* p = new Node;
	if (choice == 1)
		p = FindName();
	if (choice == 2)
		p = FindTEL();
	if (choice == 3)
		return;
	if (p == NULL) {
		cout << "Delete error!" << endl;
		return;
	}
	else {
		if (p == head->next) {
			head->next = head->next->next;
			delete p;
		}
		else {
			Node* temp = head;
			while (temp->next != p) {
				temp = temp->next;
			}
			temp->next = p->next;
			delete p;
		}
	}
}

void Book::SaveNow()
{
	ofstream fileo;
	fileo.open("data.txt",ios::app);
	if (!IsEmpty()) {
		Node* p = head->next;
		while (p != NULL) {
			fileo << "name: " << p->name << endl
				<< "age: " << p->age << endl
				<< "Tel: " << p->TEL << endl
				<< "Email: " << p->Email << endl << endl;
			p = p->next;
		}
		cout << "保存成功！" << endl;
		fileo.close();
	}
}

void Book::Read()
{
	fstream ifile;
	ifile.open("data.txt", ios::in||ios::_Nocreate);
	if (!ifile) {
		cout << "打开失败,未曾保存过文本文件!" << endl;
		return;
	}
	cout << "成功读取文本文件!" << endl;
	cout << "文本内容如下:" << endl;
	string s;
	long long t;
	while (!ifile.eof()) {	
		ifile >> s;
		ifile >> s;
		read[n].name = s;
		ifile >> s;
		ifile >> t;
		read[n].age = t;
		ifile >> s;
		ifile >> t;
		read[n].TEL = t;
		ifile >> s;
		ifile >> s;
		read[n].Email = s;
		Display(&read[n]);
		n++;
	}
	cout << endl;
	return;
}

void Display()
{
	cout << "https://github.com/lvzhineng/Project-assignments/tree/master/LinkList" << endl
		<< "=======PHONE BOOK=======" << endl;
	cout << "1---创建" << endl << "2---添加" << endl << "3---获取当前联系人数" << endl
		<< "4---遍历" << endl << "5---查找(电话)" << endl << "6---查找(姓名)" << endl
		<< "7---删除联系人" << endl << "8---删除整个通讯录" << endl
		<< "9---保存为文件" << endl << "10---读取保存过的文件" << endl << "11---清屏" << endl
		<< "12---退出" << endl;
}

void Clear()
{
	system("cls");
	Display();
}
int main()
{
	Book B;
	Node* p;
	Display();
	while (1) {
		int order;
		cout << endl << "please input the order:" << endl;
		cin >> order;
		switch (order)
		{
		case 1:
			B.CreateBook();
			break;
		case 2:
			B.InsertAtEnd();
			break;
		case 3:
			B.GetLength();
			break;
		case 4:
			B.TravalBook();
			break;
		case 5:
			p = B.FindTEL();
			Display(p);
			break;
		case 6:
			p = B.FindName();
			Display(p);
			break;
		case 7:
			B.Delete();
			break;
		case 8:
			B.DeleteAll();
			break;
		case 9:
			B.SaveNow();
			break;
		case 10:
			B.Read();
			break;
		case 11:
			Clear();
			break;
		default:
			for (int i = 0; i <= 100; i++) {
				cout << i << "%";
				Sleep(25);
				cout << "\r";
			}
			cout << "成功退出!" << endl;
			exit(0);
		}
	}
	return 0;
}
/*
4
Elon
18
137135135
2114134@gg.com

Tesla
20
1351341341
teslaisbest@gg.com

Jack
30
1342352451
jack1314@gg.com

lvzhineng
19
13675551520
13675551520@163.com
*/
