/*
Завдання 3.
Скласти  програму, яка використовує  патерн  Компонувальник  для створення файлу html-файлу. Передбачити у програмі наступні класи
Абстрактний Компонент(містить метод додавання компоненти , метод друку у файл)
Компонент-листок, що виводить у файл елемент заголовок 1 рівня(<h1> text</h1>)
Компонент-листок, що виводить у файл елемент заголовок 2 рівня(<h2> text</h2>)
Компонент-композит, що заносить у файл елемент <div  style = "background-color: колір" > ….   </div>.
Композит може містити у собі інші композити(div) та листки(h1, h2)
Наприклад,
int main()
{
Element * root = new Composite("LightSteelBlue");
root->Add(new H1("first"));
root->Add(new H2("second"));


Element * inner = new Composite("Violet");
inner->Add(new H2("third"));

Element * inner2 = new Composite("LightGreen");
inner2->Add(new H1("fourth"));

root->Add(inner);
root->Add((Element *)inner2);

root->Print();
}

// fileComposite.html
<div style = "background-color:Tomato">
<h1> first</h1>
<h2> second</h2>
<div style = "background-color:Violet">
<h2> third</h2>
</div>
<div style = "background-color:LightGreen">
<h1> fourth</h1>
</div>
</div>

*/

#include "stdafx.h"
#include <iostream> 
#include <string>
#include <fstream>
#include <vector>


using namespace std;

class IElement
{
protected:
	string str;
	ofstream file;
public:

	IElement(string str)
	{
		this->str = str;
	}

	IElement()
	{}

	virtual void Add(IElement* element) = 0;

	virtual void Print()
	{
		file.open("fileComposite.html", ios::app);
		file << str;
		file.close();
	}
};

class Element : public IElement
{
protected:
	string color;
	vector<IElement*> elements;

public:

	Element(string line)
	{
		color = line;
	}

	Element()
	{}



	void Add(IElement* element)
	{
		elements.push_back(element);
	}

	void Print()

	{
		file.open("fileComposite.html", ios::app);// was ::app

		if (!file.is_open())
		{
			cerr << "Error - write to file\n";
			return;
		}

		file << "<div  style = \"background-color:" + color + "\">\n";
		file.close();
		for (int i = 0; i < elements.size(); ++i)
		{
			elements[i]->Print();
		}
		file.open("fileComposite.html", ios::app);
		file << "</  div>\n";
		file.close();

	}
};


class H1 : public IElement
{
public:

	H1(string line)
	{
		str = "<h1> " + line + "</h1>\n";
	}

	virtual void Add(IElement* element)
	{}


};

class H2 : public IElement
{

public:

	H2(string line)
	{
		str = "<h2> " + line + "</h2>\n";
	}

	virtual void Add(IElement* element)
	{}

};

int main()
{
	IElement * root = new Element("LightSteelBlue");
	root->Add(new H1("first"));
	root->Add(new H2("second"));


	IElement * inner = new Element("Violet");
	inner->Add(new H2("third"));

	IElement * inner2 = new Element("LightGreen");
	inner2->Add(new H1("fourth"));

	root->Add(inner);
	root->Add((IElement *)inner2);

	root->Print();


	return 0;
}