#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>

using namespace std;

typedef struct HTNode {
	char character;
	int weight;		//Ȩ��
	int parent, lchild, rchild;	//˫�ף����Һ��� 
}HTNode, * HuffmanTree;		//������������̬�������飩

typedef char** HuffmanCode;	//����������� 
class Huffman
{
public:
	void Interface();			//���� 
	void Select(int a, int* p1, int* p2);		//ѡ��Ȩֵ��С���� parent Ϊ 0 �������νڵ� 
	int HuffmanCoding();		//��ʼ�� ��̬�洢����������������������� HC ��
	void HuffmanDisplay(int n);		//��ʾ���������� 
	void Weight_File(int n);		//��Ȩֵ���ݴ���������ļ�
	void EnCoding(int n);			//���� 
	void DeCoding(int n);			//���� 
	void Display_HuffmanTree(int m);		//��ʾ�������� 
	void coprint(HuffmanTree start);
	void Exit();		//�˳� 
private:
	HuffmanTree HT;
	HuffmanCode HC;
	HTNode HFT[52];
	int number;
};


void Huffman::Interface()		//����
{
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "***** ����������/������ *****" << endl;
	cout << "*****  1  ������������  *****" << endl;
	cout << "*****  2    �������    *****" << endl;
	cout << "*****  3      ����      *****" << endl;
	cout << "*****  4      ����      *****" << endl;
	cout << "*****  5  ��ʾ��������  *****" << endl;
	cout << "*****  0      �˳�      *****" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}
void Huffman::Select(int a, int* p1, int* p2)
{
	int i, j, x, y; // ��ʱ����
	// �ҵ���һ�� parent Ϊ 0 �Ľ��
	for (i = 1; i <= a; ++i)
	{
		if (HT[i].parent == 0)
		{
			x = i;
			break;
		}
	}

	// �ҵ�Ȩֵ��С�Ľ��
	for (j = i + 1; j <= a; j++)
	{
		if (HT[j].weight < HT[x].weight && HT[j].parent == 0)
		{
			x = j; // ѡ����С�ڵ�
		}
	}

	// �ҵ��ڶ��� parent Ϊ 0 �Ľ�㣬�����һ����㲻��ͬ
	for (i = 1; i <= a; i++)
	{
		if (HT[i].parent == 0 && x != i)
		{
			y = i;
			break;
		}
	}

	// �ҵ�Ȩֵ��С�Ľ��
	for (j = i + 1; j <= a; j++)
	{
		if (HT[j].weight < HT[y].weight && HT[j].parent == 0 && x != j)
		{
			y = j; // ѡ��Ȩֵ��С���
		}
	}

	// ���� x �� y �Ĵ�С�������� p1 �� p2 ��ֵ
	if (x > y)
	{
		*p1 = y; // ����Ԫ��
		*p2 = x;
	}
	else
	{
		*p1 = x;
		*p2 = y;
	}
}

// ��ʼ������������������������룩
int Huffman::HuffmanCoding()
{
	int n; // �ַ�����С
	cout << "�����ַ�����С��";
	cin >> n;
	getchar(); // ȥ���������س���
	cout << endl;
	int i, m, w, c, start, f; // ��ʱ����
	int p1, p2; // ���������ڵ�ָ��
	char ch, * cd; // �ַ�����
	m = 2 * n - 1;
	HT = new HTNode[m + 1]; // ������������
	// ��ʼ�� n ��Ҷ�ӽڵ�
	for (i = 1; i <= n; i++)
	{
		cout << "�����" << i << "��Ҷ�ӽڵ���Ϣ��Ȩֵ";
		cin >> ch >> w;
		while (getchar() != '\n')
		{
			continue; // ȥ�������������ַ�
		}
		HT[i].character = ch;
		HT[i].weight = w;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
		// ��̬�洢 HFT[]
		HFT[i].character = ch;
		HFT[i].weight = w;
		HFT[i].parent = 0;
		HFT[i].lchild = 0;
		HFT[i].rchild = 0;
	}
	// ��ʼ��������
	for (; i <= m; i++)
	{
		HT[i].character = '0';
		HT[i].weight = 0;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;

		// ��̬�洢 HFT[]
		HFT[i].character = '0';
		HFT[i].weight = 0;
		HFT[i].parent = 0;
		HFT[i].lchild = 0;
		HFT[i].rchild = 0;
	}

	// ������������
	for (i = n + 1; i <= m; i++)
	{
		Select(i - 1, &p1, &p2);
		HT[p1].parent = i;
		HT[p2].parent = i;
		HT[i].lchild = p1;
		HT[i].rchild = p2;
		HT[i].weight = HT[p1].weight + HT[p2].weight; // ��һ������Ȩֵ���ڴ�ʱ��С�������֮��
		// ��̬�洢 HFT[]
		HFT[p1].parent = i;
		HFT[p2].parent = i;
		HFT[i].lchild = p1;
		HFT[i].rchild = p2;
		HFT[i].weight = HFT[p1].weight + HFT[p2].weight;
	}

	cout << endl << "��̬�;�̬�洢���ѽ�����ɣ�" << endl << endl;

	HC = new char* [n + 1]; // �ַ�����
	cd = new char[n];
	cd[n - 1] = '\0';
	for (i = 1; i <= n; i++)
	{
		start = n - 1; // ��ʼ��������ʼλ��
		c = i;
		f = HT[i].parent;
		while (f != 0)
		{
			--start;
			if (HT[f].lchild == c)
			{
				cd[start] = '0';
			}
			else
			{
				cd[start] = '1';
			}
			c = f;
			f = HT[f].parent;
		}
		HC[i] = new char[n - start]; // Ϊÿ��Ҷ�ӽڵ��������ڴ�
		strcpy(HC[i], &cd[start]); // ������洢��HC[i]��
	}
	delete[] cd;

	return n; // �����ַ�����С
}
//��ʾ����������
void Huffman::HuffmanDisplay(int n)
{
	int i;
	cout << endl << "�����������ɹ��������룺" << endl;
	for (i = 1; i <= n; i++)
	{
		cout << HT[i].character << " : " << HC[i] << endl;
	}
}

void Huffman::Weight_File(int n)	//��Ȩֵ���ݴ���������ļ�
{
	ofstream outfile;	//�ļ������
	int i;
	outfile.open("data.txt");
	if (!outfile)
	{
		cout << "can't open file!" << endl;
	}
	else
	{
		for (i = 1; i <= n; i++)
		{
			outfile << HT[i].weight << "	";
		}
	}
	outfile.close();
	cout << "Ȩֵ�����Ѵ���������ļ�data.txt�У�" << endl;
}

//���б���
void Huffman::EnCoding(int n)
{
	int i, j;
	string str;
	cout << "�����ַ�����" << endl;
	getchar();	//ȥ�������� ��\n�� 
	getline(cin, str);
	cout << "������ֵ��" << endl;
	for (i = 0; i < str.length(); i++)
	{
		for (j = 0; j <= n; j++)
		{
			if (HT[j].character == str[i])
			{
				cout << HC[j];		//���������ֵ 
				break;
			}
		}
	}
	cout << endl;
}

//����
void Huffman::DeCoding(int n)
{
	int i, j, k, l;
	string cod;//�������
	char hl[10001] = { 0 };
	cout << endl << "�������룺" << endl;
	getchar();
	getline(cin, cod);
	k = 0;
	cout << "����ֵΪ��" << endl;
	while (cod[k] != '\0' && k < cod.size())
	{
		for (i = 1; i <= n; i++)
		{
			l = k;
			for (j = 0; j < strlen(HC[i]) && l < cod.size(); j++, l++)
			{
				hl[j] = cod[l];
			}
			hl[j] = '\0';
			if (strcmp(HC[i], hl) == 0)
			{
				cout << HT[i].character;
				k = k + strlen(HC[i]);
				break;
			}
		}
	}
	cout << endl;
}

//��ʾ��������
void Huffman::Display_HuffmanTree(int m)
{
	number = 0;
	cout << "����������" << endl;
	HuffmanTree p;
	p = HT + m;
	coprint(p);
	cout << "����������ϣ�����" << endl;
}
//�������
void Huffman::coprint(HuffmanTree start)	//start = HT + p ���ݹ飩
{
	if (start != HT)
	{
		number++;		//�ѱ�����Ϊȫ�ֱ���
		coprint(HT + start->rchild);		//�ݹ��������
		if (start->character == ' ')
		{
			cout << setw(5 * number) << "��" << endl;
		}
		else
		{
			cout << setw(5 * number) << start->character << endl;
		}
		coprint(HT + start->lchild);
		number--;
	}
}

void Huffman::Exit()		//�˳�
{
	cout << "���˳�������" << endl;
	exit(0);
}

int main()
{
	//freopen("in1.txt", "r", stdin);
	//freopen("out1.txt", "w", stdout);
	Huffman huff;
	char x;
	int n;
	huff.Interface();//��ʾϵͳ����
	while (1)
	{
		cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~";
		cout << endl << "������Ҫ�����Ĳ��裺";
		//x = cin.get();
		cin >> x;
		switch (x)
		{
		case '1':n = huff.HuffmanCoding();//����һ����������
			huff.Weight_File(n);  //�洢���ļ�data��
			break;
		case '2':huff.HuffmanDisplay(n);//��ʾ����
			break;
		case '3':huff.EnCoding(n);//����
			break;
		case '4':huff.DeCoding(n);//����
			break;
		case '5':huff.Display_HuffmanTree(2 * n - 1);//��ʾ��������
			break;
		case '0':huff.Exit();//�˳�
			break;
		default: cout << "�˲�����Ч������" << endl;
		}
	}
	return 0;
}