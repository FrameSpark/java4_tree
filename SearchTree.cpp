/*
	Lab 1, задача #5, Васильев Александр
	Среди минимальных путей между листьями выбрать тот,
	у которого сумма ключей всех его вершин минимальна,
	и удалить (правым удалением) центральную вершину этого пути.
	Выполнить прямой (левый) обход полученного дерева.
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

//нахождение узла минимального пути
int findShortcutNode(treeNode *curr, int &sum)
{
	if (curr == NULL) //если узел пустой
		return 0;
	if (curr->left == NULL && curr->right == NULL) //если дошли до листа, то возвращаем 1
	{
		sum = curr->key;
		return 1;
	}

	int leftSum = 0, rightSum = 0;
	int left  = findShortcutNode(curr->left, leftSum); //идем налево
	int right = findShortcutNode(curr->right, rightSum); //идём направо

	if (curr->left != NULL && curr->right != NULL) //узел с двумя потомками (центральный узел)
	{
		if (!shortcutNode) //первая запись центральной вершины
		{
			shortcut = left + right; //длина кротчайшего пути
			shortcutSum = leftSum + rightSum + curr->key; //сумма всех ключей пути
			shortcutNode = curr;
		}
		else
			//либо длина пути меньше, либо длины совпадают, и тогда смотрим по сумме ключей
			if (left + right < shortcut || (left + right == shortcut && (leftSum + rightSum + curr->key < shortcutSum)))
			{
				shortcut = left + right;
				shortcutSum = leftSum + rightSum + curr->key; //сумма всех ключей пути
				shortcutNode = curr;
			}

		//передаем в переменную (на уровень выше) значение наименьше суммы
		sum = ((leftSum < rightSum) ? leftSum : right) + curr->key;
		return ((left < right) ? left : right) + 1; //возвращаем наименьшее значение
	}
	else //узел с одним потомком, либо left либо right будет = 0
	{
		if (left == 0)
		{
			sum = rightSum + curr->key; //возвращаем правую сумму + текущий узел
			return right + 1;
		}
		else
			if (right == 0)
			{ 
				sum = leftSum + curr->key; //возвращаем левую сумму + текущий узел
				return left + 1;
			}
	}
}

//возвращает указатель на предка данного узла
treeNode *findPrevNode(treeNode *curr, treeNode *shortcutNode)
{
	if (curr == NULL)
		return NULL;

	if (curr->left == shortcutNode || curr->right == shortcutNode)
		return curr;

	treeNode *prev;
	prev = findPrevNode(curr->left, shortcutNode);
	if (!prev) //если prev == NULL, то выполняем обход вправо
		prev = findPrevNode(curr->right, shortcutNode);

	return prev;
}

//удаление узла минимального пути
void delShortcutNode(treeNode *&root)
{
	if (root == NULL)
		return;

	int sum;
	findShortcutNode(root, sum); //находим узел для удаления
	treeNode *prev = findPrevNode(root, shortcutNode);
	
	if (!shortcutNode) //если есть только один лист, удаляем корень
	{
		treeNode *p = (root->left != NULL) ? root->left : root->right;
		root->left = root->right = NULL;
		delete root;
		root = p;
		return;
	}
	treeNode *p = shortcutNode->right; //крайний левый из правого поддерева
	treeNode *prevRight = p; //предыдущий в правом поддереве
	while (p->left != NULL)
	{
		prevRight = p;
		p = p->left;
	}
	prevRight->left = NULL; //обнуляем у предпоследнего узла указатель
		
	if (prev) //если shortcutNode - не корень
	{
		if (prev->left == shortcutNode)
			prev->left = p;
		else
			prev->right = p;

		p->left = shortcutNode->left;
		if (prevRight != p) //если в правом поддереве первый элемент с левыми поддеревьями
			p->right = shortcutNode->right;
	}
	else //если shortcutNode - корень (с двумя потомками)
	{
		p->left = shortcutNode->left;
		if (prevRight != p) //если в правом поддереве первый элемент с левыми поддеревьями
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