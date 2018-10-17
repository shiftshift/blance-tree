#pragma once
#include<algorithm>
#include<iostream>
using namespace std;
struct BstNode {
	int height=0;
	int data=0;
	BstNode *lchild,*rchild;
};

class BTree
{
private:
public:
	int Height(BstNode* tree);//返回树高
	void RotateFromLtoR1(BstNode** tree);//单顺旋
	void RotateFromRtoL1(BstNode** tree);//单逆旋
	void RotateFromLtoR2(BstNode** tree);//先逆旋，再顺旋
	void RotateFromRtoL2(BstNode** tree);//先顺旋，再逆旋
	int Insert(BstNode** tree, int num);//递归插入
	void CreateTree(BstNode** tree);//创建平衡二叉树
	void PrintTree(BstNode* tree, int layer);//垂直的树状打印二叉树
	void Print(BstNode* tree);//中序排序打印
	BstNode* SearchTree(BstNode* tree, int key);//查找
};

int BTree::Height(BstNode* tree)
{
	if (!tree)
		return 0;
	return tree->height;
}

void BTree::RotateFromLtoR1(BstNode** tree)
{
	BstNode*p= (*tree)->lchild;
	(*tree)->lchild = p->rchild;
	p->rchild = (*tree);
	(*tree)->height = max(Height((*tree)->lchild), Height((*tree)->rchild))+1;//节点自身也算一层高度，所以加1
	p->height = max(Height(p->lchild), Height(p->rchild)) + 1;
	(*tree) = p;
}

void BTree::RotateFromRtoL1(BstNode** tree)
{
	BstNode*p = (*tree)->rchild;
	(*tree)->rchild = p->lchild;
	p->lchild = (*tree);
	(*tree)->height = max(Height((*tree)->lchild), Height((*tree)->rchild)) + 1;
	p->height = max(Height(p->lchild), Height(p->rchild)) + 1;
	(*tree) = p;
}

void BTree::RotateFromLtoR2(BstNode** tree)
{
	RotateFromRtoL1(&((*tree)->lchild));
	RotateFromLtoR1(tree);//注意*tree改变了，p指针给*tree指针赋了新值
}

void BTree::RotateFromRtoL2(BstNode** tree)
{
	RotateFromLtoR1(&((*tree)->rchild));
	RotateFromRtoL1(tree);
}

int BTree::Insert(BstNode** tree, int num)
{
	if (!(*tree))//没有结点则进入
	{
		*tree = (BstNode*)malloc(sizeof(BstNode));
		if (!*tree)
		{
			cout << "空间分配失败" << endl;
			return -1;//失败退出
		}
		(*tree)->data = num;
		(*tree)->height = 1;
		(*tree)->lchild = nullptr;
		(*tree)->rchild = nullptr;
		return 0;//成功退出
	}
	else if (num < (*tree)->data)
	{
		if (Insert(&((*tree)->lchild), num) == -1)
		{
			return -1;
		}
		if ((Height((*tree)->lchild) - Height((*tree)->rchild)) == 2)
		{
			if (num < (*tree)->lchild->data)
				RotateFromLtoR1(tree);
			else
				RotateFromLtoR2(tree);
		}
	}
	else if (num > (*tree)->data)
	{
		if (Insert(&((*tree)->rchild), num) == -1)
		{
			return -1;
		}
		if ((Height((*tree)->lchild) - Height((*tree)->rchild)) == -2)
		{
			if (num > (*tree)->rchild->data)
				RotateFromRtoL1(tree);//新节点挂接到右子树的右子树上，平衡因子同号，仅需调用单旋函数
			else
				RotateFromRtoL2(tree);//说明新节点挂接到右子树的左子树上，产生平衡因子异号的情况，所以需要调用双旋函数
		}
	}
	(*tree)->height = max(Height((*tree)->lchild), Height((*tree)->rchild)) + 1;
	return 0;
}

void BTree::CreateTree(BstNode** tree)
{
	int num=-1;
	while (num<0)
	{
		cout << "输入数据:";
		cin >> num;
	}
	while (num != -1)
	{
		Insert(tree, num);
		cin >> num;
	}
}

void BTree::PrintTree(BstNode* tree,int layer)
{
	if (tree->rchild)
	{
		PrintTree(tree->rchild, layer + 1);
	}
	for (int i = 1; i <= layer; i++)
	cout << " ";
	cout << tree->data << endl;
	if (tree->lchild)
	{
	PrintTree(tree->lchild, layer + 1);
	}
}

void BTree::Print(BstNode* tree)
{
	if (!tree)
		return;
	Print(tree->lchild);
	cout << tree->data << " ";
	Print(tree->rchild);
	return;
}

BstNode* BTree::SearchTree(BstNode* tree, int key)
{
	BstNode*p = tree;
	if (!p)
		return nullptr;
	while (p)
	{
		if (p->data == key)
			return p;
		else if (key < p->data)
			p = p->lchild;
		else if (key >p->data)
			p = p->rchild;
	}
	return nullptr;
}


