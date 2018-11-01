/*
	Lab 1, ������ #5, �������� ���������
	����� ����������� ����� ����� �������� ������� ���,
	� �������� ����� ������ ���� ��� ������ ����������,
	� ������� (������ ���������) ����������� ������� ����� ����.
	��������� ������ (�����) ����� ����������� ������.
*/

#include <iostream>
#include <fstream>

using namespace std;

struct treeNode
{
	int key;
	int count;
	treeNode *left, *right;
};

void pushTree(treeNode *&p, int x)
{
	if (p == NULL)
	{
		p = new treeNode;
		p->key = x;
		p->count = 1;
		p->left = NULL;
		p->right = NULL;
	}
	else
	{
		if (x < p->key)
			pushTree(p->left, x);
		else
			if (x > p->key)
				pushTree(p->right, x);
			else
				p->count++;
	}
}

void printTree(treeNode *p)
{
	if (p == NULL)
		return;

	cout << p->key << " ";
	printTree(p->left);
	printTree(p->right);
}

int shortcutSum, shortcut;
treeNode *shortcutNode = NULL;

//���������� ���� ������������ ����
int findShortcutNode(treeNode *curr, int &sum)
{
	if (curr == NULL) //���� ���� ������
		return 0;
	if (curr->left == NULL && curr->right == NULL) //���� ����� �� �����, �� ���������� 1
	{
		sum = curr->key;
		return 1;
	}

	int leftSum = 0, rightSum = 0;
	int left  = findShortcutNode(curr->left, leftSum); //���� ������
	int right = findShortcutNode(curr->right, rightSum); //��� �������

	if (curr->left != NULL && curr->right != NULL) //���� � ����� ��������� (����������� ����)
	{
		if (!shortcutNode) //������ ������ ����������� �������
		{
			shortcut = left + right; //����� ����������� ����
			shortcutSum = leftSum + rightSum + curr->key; //����� ���� ������ ����
			shortcutNode = curr;
		}
		else
			//���� ����� ���� ������, ���� ����� ���������, � ����� ������� �� ����� ������
			if (left + right < shortcut || (left + right == shortcut && (leftSum + rightSum + curr->key < shortcutSum)))
			{
				shortcut = left + right;
				shortcutSum = leftSum + rightSum + curr->key; //����� ���� ������ ����
				shortcutNode = curr;
			}

		//�������� � ���������� (�� ������� ����) �������� ��������� �����
		sum = ((leftSum < rightSum) ? leftSum : right) + curr->key;
		return ((left < right) ? left : right) + 1; //���������� ���������� ��������
	}
	else //���� � ����� ��������, ���� left ���� right ����� = 0
	{
		if (left == 0)
		{
			sum = rightSum + curr->key; //���������� ������ ����� + ������� ����
			return right + 1;
		}
		else
			if (right == 0)
			{ 
				sum = leftSum + curr->key; //���������� ����� ����� + ������� ����
				return left + 1;
			}
	}
}

//���������� ��������� �� ������ ������� ����
treeNode *findPrevNode(treeNode *curr, treeNode *shortcutNode)
{
	if (curr == NULL)
		return NULL;

	if (curr->left == shortcutNode || curr->right == shortcutNode)
		return curr;

	treeNode *prev;
	prev = findPrevNode(curr->left, shortcutNode);
	if (!prev) //���� prev == NULL, �� ��������� ����� ������
		prev = findPrevNode(curr->right, shortcutNode);

	return prev;
}

//�������� ���� ������������ ����
void delShortcutNode(treeNode *&root)
{
	if (root == NULL)
		return;

	int sum;
	findShortcutNode(root, sum); //������� ���� ��� ��������
	treeNode *prev = findPrevNode(root, shortcutNode);
	
	if (!shortcutNode) //���� ���� ������ ���� ����, ������� ������
	{
		treeNode *p = (root->left != NULL) ? root->left : root->right;
		root->left = root->right = NULL;
		delete root;
		root = p;
		return;
	}
	treeNode *p = shortcutNode->right; //������� ����� �� ������� ���������
	treeNode *prevRight = p; //���������� � ������ ���������
	while (p->left != NULL)
	{
		prevRight = p;
		p = p->left;
	}
	prevRight->left = NULL; //�������� � �������������� ���� ���������
		
	if (prev) //���� shortcutNode - �� ������
	{
		if (prev->left == shortcutNode)
			prev->left = p;
		else
			prev->right = p;

		p->left = shortcutNode->left;
		if (prevRight != p) //���� � ������ ��������� ������ ������� � ������ ������������
			p->right = shortcutNode->right;
	}
	else //���� shortcutNode - ������ (� ����� ���������)
	{
		p->left = shortcutNode->left;
		if (prevRight != p) //���� � ������ ��������� ������ ������� � ������ ������������
			p->right = shortcutNode->right;

		root = p;
	}

	shortcutNode->left = shortcutNode->right = NULL;
	delete shortcutNode;
	shortcutNode = NULL;
}

int main()
{
	treeNode *root = NULL;

	ifstream fin("input.txt");
	int x;
	while (!fin.eof())
	{
		fin >> x;
		pushTree(root, x);
	}

	cout << "original tree: " << endl;
	printTree(root);
	cout << endl;

	while (root)
	{
		delShortcutNode(root);
		printTree(root);
		cout << endl;
	}

	system("PAUSE");
	return 0;
}