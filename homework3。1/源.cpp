#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>

using namespace std;

typedef struct HTNode {
	char character;
	int weight;		//权重
	int parent, lchild, rchild;	//双亲，左、右孩子 
}HTNode, * HuffmanTree;		//哈夫曼树（动态分配数组）

typedef char** HuffmanCode;	//哈夫曼编码表 
class Huffman
{
public:
	void Interface();			//界面 
	void Select(int a, int* p1, int* p2);		//选出权值最小，且 parent 为 0 的主、次节点 
	int HuffmanCoding();		//初始化 动态存储（构建哈夫曼树，并求编码 HC ）
	void HuffmanDisplay(int n);		//显示哈夫曼编码 
	void Weight_File(int n);		//将权值数据存放在数据文件
	void EnCoding(int n);			//编码 
	void DeCoding(int n);			//译码 
	void Display_HuffmanTree(int m);		//显示哈夫曼树 
	void coprint(HuffmanTree start);
	void Exit();		//退出 
private:
	HuffmanTree HT;
	HuffmanCode HC;
	HTNode HFT[52];
	int number;
};


void Huffman::Interface()		//界面
{
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "***** 哈夫曼编码/译码器 *****" << endl;
	cout << "*****  1  创建哈夫曼树  *****" << endl;
	cout << "*****  2    输出编码    *****" << endl;
	cout << "*****  3      编码      *****" << endl;
	cout << "*****  4      译码      *****" << endl;
	cout << "*****  5  显示哈夫曼树  *****" << endl;
	cout << "*****  0      退出      *****" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}
void Huffman::Select(int a, int* p1, int* p2)
{
	int i, j, x, y; // 临时变量
	// 找到第一个 parent 为 0 的结点
	for (i = 1; i <= a; ++i)
	{
		if (HT[i].parent == 0)
		{
			x = i;
			break;
		}
	}

	// 找到权值最小的结点
	for (j = i + 1; j <= a; j++)
	{
		if (HT[j].weight < HT[x].weight && HT[j].parent == 0)
		{
			x = j; // 选出最小节点
		}
	}

	// 找到第二个 parent 为 0 的结点，且与第一个结点不相同
	for (i = 1; i <= a; i++)
	{
		if (HT[i].parent == 0 && x != i)
		{
			y = i;
			break;
		}
	}

	// 找到权值次小的结点
	for (j = i + 1; j <= a; j++)
	{
		if (HT[j].weight < HT[y].weight && HT[j].parent == 0 && x != j)
		{
			y = j; // 选出权值次小结点
		}
	}

	// 按照 x 和 y 的大小重新设置 p1 和 p2 的值
	if (x > y)
	{
		*p1 = y; // 插入元素
		*p2 = x;
	}
	else
	{
		*p1 = x;
		*p2 = y;
	}
}

// 初始化（构建哈夫曼树，并求编码）
int Huffman::HuffmanCoding()
{
	int n; // 字符集大小
	cout << "输入字符集大小：";
	cin >> n;
	getchar(); // 去除缓存区回车键
	cout << endl;
	int i, m, w, c, start, f; // 临时变量
	int p1, p2; // 哈夫曼树节点指针
	char ch, * cd; // 字符编码
	m = 2 * n - 1;
	HT = new HTNode[m + 1]; // 创建哈夫曼树
	// 初始化 n 个叶子节点
	for (i = 1; i <= n; i++)
	{
		cout << "输入第" << i << "个叶子节点信息和权值";
		cin >> ch >> w;
		while (getchar() != '\n')
		{
			continue; // 去除缓冲区其他字符
		}
		HT[i].character = ch;
		HT[i].weight = w;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
		// 静态存储 HFT[]
		HFT[i].character = ch;
		HFT[i].weight = w;
		HFT[i].parent = 0;
		HFT[i].lchild = 0;
		HFT[i].rchild = 0;
	}
	// 初始化其余结点
	for (; i <= m; i++)
	{
		HT[i].character = '0';
		HT[i].weight = 0;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;

		// 静态存储 HFT[]
		HFT[i].character = '0';
		HFT[i].weight = 0;
		HFT[i].parent = 0;
		HFT[i].lchild = 0;
		HFT[i].rchild = 0;
	}

	// 建立哈夫曼树
	for (i = n + 1; i <= m; i++)
	{
		Select(i - 1, &p1, &p2);
		HT[p1].parent = i;
		HT[p2].parent = i;
		HT[i].lchild = p1;
		HT[i].rchild = p2;
		HT[i].weight = HT[p1].weight + HT[p2].weight; // 下一个结点的权值等于此时最小两个结点之和
		// 静态存储 HFT[]
		HFT[p1].parent = i;
		HFT[p2].parent = i;
		HFT[i].lchild = p1;
		HFT[i].rchild = p2;
		HFT[i].weight = HFT[p1].weight + HFT[p2].weight;
	}

	cout << endl << "动态和静态存储均已建立完成！" << endl << endl;

	HC = new char* [n + 1]; // 字符编码
	cd = new char[n];
	cd[n - 1] = '\0';
	for (i = 1; i <= n; i++)
	{
		start = n - 1; // 初始化编码起始位置
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
		HC[i] = new char[n - start]; // 为每个叶子节点编码分配内存
		strcpy(HC[i], &cd[start]); // 将编码存储到HC[i]中
	}
	delete[] cd;

	return n; // 返回字符集大小
}
//显示哈夫曼编码
void Huffman::HuffmanDisplay(int n)
{
	int i;
	cout << endl << "哈夫曼树生成哈夫曼编码：" << endl;
	for (i = 1; i <= n; i++)
	{
		cout << HT[i].character << " : " << HC[i] << endl;
	}
}

void Huffman::Weight_File(int n)	//将权值数据存放在数据文件
{
	ofstream outfile;	//文件输出流
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
	cout << "权值数据已存放在数据文件data.txt中！" << endl;
}

//进行编码
void Huffman::EnCoding(int n)
{
	int i, j;
	string str;
	cout << "输入字符集：" << endl;
	getchar();	//去除缓冲区 “\n” 
	getline(cin, str);
	cout << "编码码值：" << endl;
	for (i = 0; i < str.length(); i++)
	{
		for (j = 0; j <= n; j++)
		{
			if (HT[j].character == str[i])
			{
				cout << HC[j];		//输出编码码值 
				break;
			}
		}
	}
	cout << endl;
}

//译码
void Huffman::DeCoding(int n)
{
	int i, j, k, l;
	string cod;//输入编码
	char hl[10001] = { 0 };
	cout << endl << "输入译码：" << endl;
	getchar();
	getline(cin, cod);
	k = 0;
	cout << "译码值为：" << endl;
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

//显示哈夫曼树
void Huffman::Display_HuffmanTree(int m)
{
	number = 0;
	cout << "哈夫曼树：" << endl;
	HuffmanTree p;
	p = HT + m;
	coprint(p);
	cout << "哈夫曼树完毕！！！" << endl;
}
//先序遍历
void Huffman::coprint(HuffmanTree start)	//start = HT + p （递归）
{
	if (start != HT)
	{
		number++;		//已被声明为全局变量
		coprint(HT + start->rchild);		//递归先序遍历
		if (start->character == ' ')
		{
			cout << setw(5 * number) << "空" << endl;
		}
		else
		{
			cout << setw(5 * number) << start->character << endl;
		}
		coprint(HT + start->lchild);
		number--;
	}
}

void Huffman::Exit()		//退出
{
	cout << "已退出！！！" << endl;
	exit(0);
}

int main()
{
	//freopen("in1.txt", "r", stdin);
	//freopen("out1.txt", "w", stdout);
	Huffman huff;
	char x;
	int n;
	huff.Interface();//显示系统界面
	while (1)
	{
		cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~";
		cout << endl << "输入您要操作的步骤：";
		//x = cin.get();
		cin >> x;
		switch (x)
		{
		case '1':n = huff.HuffmanCoding();//创建一个哈夫曼树
			huff.Weight_File(n);  //存储到文件data中
			break;
		case '2':huff.HuffmanDisplay(n);//显示编码
			break;
		case '3':huff.EnCoding(n);//编码
			break;
		case '4':huff.DeCoding(n);//译码
			break;
		case '5':huff.Display_HuffmanTree(2 * n - 1);//显示哈夫曼树
			break;
		case '0':huff.Exit();//退出
			break;
		default: cout << "此步骤无效！！！" << endl;
		}
	}
	return 0;
}