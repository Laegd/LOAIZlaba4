#include <iostream>
#include <cstdlib>
#include <locale>

using namespace std;

struct Node
{
	char str;
	int data;
	struct Node* left;
	struct Node* right;
};

struct Node* root;

struct Node* CreateTree(struct Node* root, struct Node* r, int data, char strt)
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
		r->str = strt;
		if (root == NULL) return r;
		if (data > root->data) root->left = r;
		else if (data < root->data) root->right = r;
		else return r;
		return r;
	}
	if (data > r->data)
		CreateTree(r, r->left, data, strt);
	else if (data < r->data)
		CreateTree(r, r->right, data, strt);
	else return root;
	return root;
}
struct Node* find(struct Node* r, char strt)
{
	if (towlower(r->str) == towlower(strt)) return r;
	else if (towlower(r->str) < towlower(strt) && r->left != NULL)
	{
		find(r->left, strt);
	}
	else if (towlower(r->str) > towlower(strt) && r->right != NULL)
	{
		find(r->right, strt);
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
	cout << r->data << "(" << r->str << ")" << endl;
	print_tree(r->left, l + 1);
}
int fcount(struct Node* r, char strt, int count)
{
	if (r == NULL) return count;
	if (towlower(r->str) == towlower(strt)) count++;
	count = fcount(r->right, strt, count);
	count = fcount(r->left, strt, count);
	return count;
}
int main()
{
	setlocale(LC_ALL, "");
	int D, start = 1, co;
	char str;
	struct Node* r = NULL;
	printf("Введите -1 - окончание построения дерева. Одинаковые символы не вводить! Не введутся\n");
	while (start)
	{
		cout << "Введите число: ";
		cin >> D;
		if (D != -1)
		{
			cout << "Введите слово: ";
			cin >> str;
		}
		if (D == -1)
		{
			printf("Построение дерева окончено\n\n");
			start = 0;
		}
		else
			root = CreateTree(root, root, D, str);
	}
	print_tree(root, 0);
	cout << "Введите какое число искать: ";
	cin >> str;
	r = find(root, str);
	cout << "" << r->str << " найдено";
	co = fcount(root, str, 0);
	cout << endl << "Количество = " << co;
	return 0;
}