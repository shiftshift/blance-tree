// ConsoleApplication3.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<memory.h>
#include"Menu.h"
#include"BalanceTree.h"
using namespace std;
int main()
{
	BstNode*tree = nullptr;
	int select,num,choice;
	BTree bt;
	Menu menu;
	cout << "这是一个平衡二叉树程序，接下来需要创建树，请输入数据（以-1结束输入）！" << endl;
	bt.CreateTree(&tree);
	cout << "树形输出：" << endl;
	bt.PrintTree(tree, 0);
	menu.AddItem(".查找");
	menu.AddItem(".插入");
	menu.AddItem(".排序输出");
	menu.AddItem(".退出");
	while (1)
	{
		switch (menu.Choice())
		{
		case 1:
			cout << "请输入要查找的数据" << endl;
			cin >> num;
			if (bt.SearchTree(tree, num) != nullptr)
			{
				cout << "数据在二叉树中" << endl;
			}
			else
				cout << "数据不在二叉树中" << endl;
			break;
		case 2:
			cout << "请输入要插入的数据：" << endl;
			cin >> num;
			bt.Insert(&tree, num);
			cout << "树形输出：" << endl;
			bt.PrintTree(tree, 0);
			break;
		case 3:
			bt.Print(tree);
			cout << endl;
			break;
		case 4:
			return 0;
		default:
			cout << "重新选择\n" << endl;
		}
	}
    return 0;
}

