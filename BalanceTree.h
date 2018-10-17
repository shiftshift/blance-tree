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
	int Height(BstNode* tree);//��������
	void RotateFromLtoR1(BstNode** tree);//��˳��
	void RotateFromRtoL1(BstNode** tree);//������
	void RotateFromLtoR2(BstNode** tree);//����������˳��
	void RotateFromRtoL2(BstNode** tree);//��˳����������
	int Insert(BstNode** tree, int num);//�ݹ����
	void CreateTree(BstNode** tree);//����ƽ�������
	void PrintTree(BstNode* tree, int layer);//��ֱ����״��ӡ������
	void Print(BstNode* tree);//���������ӡ
	BstNode* SearchTree(BstNode* tree, int key);//����
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
	(*tree)->height = max(Height((*tree)->lchild), Height((*tree)->rchild))+1;//�ڵ�����Ҳ��һ��߶ȣ����Լ�1
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
	RotateFromLtoR1(tree);//ע��*tree�ı��ˣ�pָ���*treeָ�븳����ֵ
}

void BTree::RotateFromRtoL2(BstNode** tree)
{
	RotateFromLtoR1(&((*tree)->rchild));
	RotateFromRtoL1(tree);
}

int BTree::Insert(BstNode** tree, int num)
{
	if (!(*tree))//û�н�������
	{
		*tree = (BstNode*)malloc(sizeof(BstNode));
		if (!*tree)
		{
			cout << "�ռ����ʧ��" << endl;
			return -1;//ʧ���˳�
		}
		(*tree)->data = num;
		(*tree)->height = 1;
		(*tree)->lchild = nullptr;
		(*tree)->rchild = nullptr;
		return 0;//�ɹ��˳�
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
				RotateFromRtoL1(tree);//�½ڵ�ҽӵ����������������ϣ�ƽ������ͬ�ţ�������õ�������
			else
				RotateFromRtoL2(tree);//˵���½ڵ�ҽӵ����������������ϣ�����ƽ��������ŵ������������Ҫ����˫������
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
		cout << "��������:";
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


