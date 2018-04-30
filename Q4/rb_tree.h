#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

class rb_tree
{
private:
	class node
	{
	public:
		int data;
		node *p;
		node *l, *r;
		std::string color;
		node(int datax, std::string colorx)
		{
			data = datax;
			p = NULL;
			l = NULL;
			r = NULL;
			color = colorx;
		}
	};

	// root of the tree;
	node* root;
	// special NIL element
	node* NIL;
public:
	rb_tree()
	{
		NIL = new node(NULL, "BLACK");
		root = NIL;
	}

	void rb_insert(int ele);
	void rb_insert_fixup(node *ele);
	node* create_node(int ele);
	void left_rotate(node *ele);
	void right_rotate(node *ele);
	void print();
	void inorder(node *ele, HANDLE hc);
	void search(int key);
};


void rb_tree::rb_insert(int el)
{
	node *ele = create_node(el);
	node *y = NIL;
	node *x = root;

	while (x != NIL)
	{
		y = x;
		if (ele->data < x->data)
			x = x->l;
		else
			x = x->r;
	}

	ele->p = y;
	if (y == NIL)
		root = ele;
	else if (ele->data < y->data)
		y->l = ele;
	else
		y->r = ele;

	rb_insert_fixup(ele);
}

void rb_tree::rb_insert_fixup(node *ele)
{
	node *y = NULL;
	while (ele->p->color.compare("RED") == 0)
	{
		if (ele->p == ele->p->p->l)
		{
			y = ele->p->p->r;
			if (y->color.compare("RED") == 0)
			{
				y->color = "BLACK";
				ele->p->color = "BLACK";
				ele->p->p->color = "RED";
			}
			else
			{
				if (ele == ele->p->r)
				{
					ele = ele->p;
					left_rotate(ele);
				}

				ele->p->color = "BLACK";
				ele->p->p->color = "RED";
				right_rotate(ele->p->p);
			}
		}
		else
		{
			y = ele->p->p->l;
			if (y->color.compare("RED") == 0)
			{
				y->color = "BLACK";
				ele->p->color = "BLACK";
				ele->p->p->color = "RED";
			}
			else
			{
				if (ele == ele->p->l)
				{
					ele = ele->p;
					left_rotate(ele);
				}

				ele->p->color = "BLACK";
				ele->p->p->color = "RED";
				right_rotate(ele->p->p);
			}
		}
	}

	root->color = "BLACK";
}

rb_tree::node* rb_tree::create_node(int ele)
{
	rb_tree::node* temp = new node(ele, "RED");
	temp->l = NIL;
	temp->r = NIL;
	temp->p = NIL;

	return temp ? temp : NULL;
}

void rb_tree::left_rotate(node *ele)
{
	node *y = ele->r;
	ele->r = y->l;

	if (y->l != NIL)
		y->l->p = ele;

	y->p = ele->p;
	if (ele->p == NIL)
		root = y;
	else if (ele == ele->p->l)
		ele->p->l = y;
	else
		ele->p->r = y;

	y->l = ele;
	ele->p = y;
}

void rb_tree::right_rotate(node *ele)
{
	node *y = ele->l;
	ele->l = y->r;

	if (y->r != NIL)
		y->r->p = ele;

	y->p = ele->p;
	if (ele->p == NIL)
		root = y;
	else if (ele == ele->p->r)
		ele->p->r = y;
	else
		ele->p->l = y;

	y->r = ele;
	ele->p = y;
}

void rb_tree::print()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int k;
	inorder(root, hConsole);
	SetConsoleTextAttribute(hConsole, 7);
}

void rb_tree::inorder(node *ele, HANDLE hc)
{
	if (ele == NIL)
		return;
	inorder(ele->l, hc);
	if (ele->color.compare("RED") == 0)
		SetConsoleTextAttribute(hc, 4);
	else
		SetConsoleTextAttribute(hc, 7);
	std::cout << ele->data << " ";
	inorder(ele->r, hc);
}

void rb_tree::search(int key)
{
	node *temp = root;
	bool flag = false;
	while (temp != NIL)
	{
		if (key < temp->data)
			temp = temp->l;
		else if (key > temp->data)
			temp = temp->r;
		else
		{
			flag = true;
			break;
		}
	}

	std::cout << std::endl;
	if (flag)
		std::cout << "Key is present in tree.";
	else
		std::cout << "Key is not present in tree.";
}	