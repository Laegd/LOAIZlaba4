#include <iostream>
#include <cstdlib>
#include <locale>

using namespace std;

struct Node
{
	int data;
	struct Node* left;
	struct Node* right;
};

struct Node* root;

struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
	if (r == NULL)
	{
		r = (struct Node*)malloc(sizeof(struct Node));
		if (r == NULL)
		{
			cout << "Ошибка выделения памяти" << endl;
			exit(0);
		}
		r->left = NULL;
		r->right = NULL;
		r->data = data;
		if (root == NULL) return r;
		if (data > root->data) root->left = r;
		else if (data < root->data) root->right = r;
		else return r;
		return r;
	}
	if (data > r->data)
		CreateTree(r, r->left, data);
	else if (data < r->data)
		CreateTree(r, r->right, data);
	else return root;
	return root;
}
struct Node* find(struct Node* r, int data)
{
	if (r->data == data) return r;
	else if (r->data < data && r->left != NULL)
	{
		find(r->left, data);
	}
	else if (r->data > data && r->right != NULL)
	{
		find(r->right, data);
	}
	else
	{
		cout << "Не найдено";
		return NULL;
	}
}
void print_tree(struct Node* r, int l)
{
	if (r == NULL)
	{
		return;
	}
	print_tree(r->right, l + 1);
	for (int i = 0; i < l; i++)
	{
		printf(" ");
	}
	cout << r->data << endl;
	print_tree(r->left, l + 1);
}
int fcount(struct Node* r, int data, int count)
{
	if (r == NULL) return count;
	if (r->data == data) count++;
	count = fcount(r->right, data, count);
	count = fcount(r->left, data, count);
	return count;
}
int main()
{
	setlocale(LC_ALL, "");
	int D, start = 1, co;
	struct Node* r = NULL;
	printf("Введите -1 - окончание построения дерева. Одинаковые символы не вводить! Не введутся\n");
	while (start)
	{
		printf("Введите число : ");
		cin >> D;
		if (D == -1)
		{
			printf("Построение дерева окончено\n\n");
			start = 0;
		}
		else
			root = CreateTree(root, root, D);

	}
	print_tree(root, 0);
	cout << "Введите какое число искать: ";
	cin >> D;
	r = find(root, D);
	cout << "" << r->data << " найдено";
	co = fcount(root, D, 0);
	cout << endl << "Количество = " << co;
	return 0;
}