#include <iostream>
#include <string>
#include <queue>
#include <Windows.h>
#include <fstream>
using namespace std;
const int MAX = 100;

struct Node {
	string name = "None", Email="None";
	int age = 0, TEL = 0;
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
		return;
	}
	else {
		Node* p = head->next;
		while (p != NULL) {
			Display(p);
			p = p->next;
		}
	}
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
	cout << "请输入姓名";
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
	int tel;
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
	cout << "文本内容如下:" << endl;
	string s;
	int t;
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
	cout << "成功读取文本文件" << endl;
	return;
}

int main()
{
	Book B;
	Node* p;
	while (1) {
		cout << "please input the order:" << endl
			<< "1.创建\t2.增加\t3.获取联系人数\t4.按电话查找\t5.按姓名查找\t"
			<< "6.删除联系人\t7.删除整个通讯录\t8.保存\t9.读取保存的文件\t10.退出" << endl;
		int order;
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
			p = B.FindTEL();
			Display(p);
			break;
		case 5:
			p = B.FindName();
			Display(p);
			break;
		case 6:
			B.Delete();
			break;
		case 7:
			B.DeleteAll();
			break;
		case 8:
			B.SaveNow();
			break;
		case 9:
			B.Read();
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
2
Elon
23
12123
234
Alice
14
23525
23423
*/
