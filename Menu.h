#pragma once

/*
菜单类
构成简单的用户界面
*/
#include "string.h"
#include "stdio.h"
#include "conio.h"
#include<iostream>
#define MAX_MENUITEMS	10
using namespace std;
class Menu
{
public:
	Menu();
	Menu(const char* sPrompt); 
	virtual ~Menu();
private:
	char prompt[256]; 
	char *items[MAX_MENUITEMS];
	int count;
public:
	void AddItem(const char* item);
	int Choice();

};

Menu::Menu()
{
	count = 0;
	prompt[0] = 0;
}
Menu::Menu(const char* prompt)
{
	count = 0;
	strcpy_s(this->prompt,256, prompt); //保存提示
}

Menu::~Menu()
{
	for (int i = 0; i<count; i++)
		delete[] items[i];
}

void Menu::AddItem(const char* item)
{
	if (count >= MAX_MENUITEMS)
		return;
	items[count] = new char[strlen(item) + 1];
	strcpy_s(items[count], strlen(item) + 1, item);
	count++;
}

int Menu::Choice()
{
	if (prompt[0])
		puts(prompt);
	else
		puts("Please select:");
	for (int i = 0; i<count; i++)
		printf("%d %s\n", i + 1, items[i]);
	do
	{
		printf("Please choose: ");
		int c;
		cin >> c;
		if (c >= 1 && c <= count)
		{
			putchar('\n');
			return c;
		}
		else
			printf("\nInvalid number.\n");
	} while (true);
}