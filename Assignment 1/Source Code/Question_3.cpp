#include<iostream>
#include<conio.h>
#include<string>

using namespace std;

class dataBlock
{
private:
	int data[1024];
	dataBlock *next;
public:
	dataBlock();
	dataBlock(int);
	void set(int);
	int* get();
	void setNext(dataBlock *);
	dataBlock* getNext();
	void showData();
	~dataBlock() {
	
	}
};
dataBlock::dataBlock() 
{
	set(0);
	next = NULL;
}
dataBlock::dataBlock(int d)
{
	set(d);
	next = NULL;
}
void dataBlock::set(int x)
{
	for (int i = 0; i<1024; i++)
		data[i] = x;
}
int* dataBlock::get()
{
	return data;
}
void dataBlock::setNext(dataBlock *ptr)
{
	next = ptr;
}
dataBlock* dataBlock::getNext()
{
	return next;
}
void dataBlock::showData()
{
	cout << get() << "\t"<< get()[1];
}
class directBlock {
private:
	dataBlock* headdataBlock;
	dataBlock* currentdataBlock;
	int size;
	directBlock* dNext=NULL;
public:
	directBlock();
	void dSet(int);
	void dSetNext(directBlock *ptr);
	directBlock* dGetNext();
	void dShowData();
	void start();
	void next();
	dataBlock* get();
	int length();
	void add(int d);
	void showList();
	~directBlock() {

	}
};
directBlock::directBlock() {
	headdataBlock = NULL;
	currentdataBlock = NULL;
	size = 0;
	dNext = NULL;
}
void directBlock::dSet(int x)
{
	dataBlock data[10];
	for (int i = 0; i < 10; i++)
	{
		data[i].set(x);
	}
}
void directBlock::dSetNext(directBlock *ptr)
{
	dNext = ptr;
}
directBlock* directBlock::dGetNext()
{
	return dNext;
}
void directBlock::dShowData()
{
	cout << get() << "\t" << get()[1].get()<<"\t";
}
void directBlock::start() {
	currentdataBlock = headdataBlock;
}
void directBlock::next() {
	if (currentdataBlock->getNext() != NULL) {
		currentdataBlock = currentdataBlock->getNext();
	}
}
dataBlock* directBlock::get() {
	if (currentdataBlock != NULL) {

		return currentdataBlock;
	}
}
int directBlock::length()
{
	return size;
}
void directBlock::add(int d)
{
	dataBlock* newdataBlock = new dataBlock(d);
	if (size == 0) {
		currentdataBlock = newdataBlock;
		headdataBlock = newdataBlock;
		currentdataBlock->setNext(headdataBlock);
	}
	else {
		newdataBlock->setNext(currentdataBlock->getNext());
		currentdataBlock->setNext(newdataBlock);
		currentdataBlock = newdataBlock;
	}
	size++;
}
void directBlock::showList() {
	dataBlock* ptr;
	ptr = headdataBlock;
	do {
		ptr->showData();
		ptr = ptr->getNext();
	} while (ptr != headdataBlock);
	cout << endl;
}

class indirectBlock {
private:
	directBlock* headDirectBlock;
	directBlock* currentDirectBlock;
	int size;
public:
	indirectBlock();
	void indSet(int x);
	void start();
	void next();
	directBlock* get();
	int length();
	void add(int d);
	void showList();
	~indirectBlock() {

	}
};
indirectBlock::indirectBlock() {
	headDirectBlock = NULL;
	currentDirectBlock = NULL;
	size = 0;
}
void indirectBlock::indSet(int x)
{
	directBlock direct[5];
	for (int i = 0; i < 5; i++)
	{
		direct[i].add(x);
	}
	currentDirectBlock = direct;
}

void indirectBlock::start() {
	currentDirectBlock = headDirectBlock;
}
void indirectBlock::next() {
	if (currentDirectBlock->dGetNext() != NULL) {
		currentDirectBlock = currentDirectBlock->dGetNext();
	}
}
directBlock* indirectBlock::get() {
	if (currentDirectBlock != NULL) {
		return currentDirectBlock;
	}
}
int indirectBlock::length()
{
	return size;
}
void indirectBlock::add(int d)
{
	directBlock* newdirectBlock = new directBlock();
	if (size == 0) {
		currentDirectBlock = newdirectBlock;
		headDirectBlock = newdirectBlock;
		currentDirectBlock->dSetNext(headDirectBlock);
	}
	else {
		newdirectBlock->dSetNext(currentDirectBlock->dGetNext());
		currentDirectBlock->dSetNext(newdirectBlock);
		currentDirectBlock = newdirectBlock;
	}
	size++;
}
void indirectBlock::showList() {
	directBlock* ptr;
	ptr = headDirectBlock;
	do {
		ptr->dShowData();
		ptr = ptr->dGetNext();
	} while (ptr != headDirectBlock);
	cout << endl;
}

void listMake(int size) 
{
	int ind_temp, d_temp;

	if (size <= 40)
	{

		directBlock d1;
		int temp1 = size % 4;
		int temp2 = size / 4;
		if (temp1 == 0)
		{
		for (int i = 0; i < temp2; i++)
			{
				d1.add(i);
			}
			cout << temp2 << " data blocks are filled\n";
			cout << "length of direct list is: " << d1.length() << endl;
		}
		else
		{
			for (int i = 0; i < temp2 + 1; i++)
			{
				d1.add(4);
			}
			cout << temp2 + 1 << " data blocks are filled\n";
			cout << "length of direct list is: " << d1.length() << endl;
		}
	}
	else if (size <= 200)
	{	
		indirectBlock ind1;
		int temp1,temp2,temp3;
		temp1 = size / 40;
		temp2 = size % 40;
		if (temp2 == 0)
		{
			for(int i=0; i<temp1; i++)
			{
				ind1.add(4);
			}
		}
		else
		{
			directBlock d1;
			for (int i = 0; i<temp1+1; i++)
			{
				ind1.add(4);
			}
			temp3 = (size - (temp1 * 40)) / 4;
			if ((size - (temp1 * 40)) % 4 == 0) 
			{
				for (int i = 0; i < temp3; i++)
				{
					d1.add(i);
					ind1.showList();
				}
				ind1.get()[temp3-1]=d1;
			}
			else
			{
				for (int i = 0; i < temp3+1; i++)
				{
					d1.add(i);
				}
				ind1.get()[temp3]=d1;
			}
		}
		ind1.showList();
		cout << size / 40 << " direct blocks are completely filled\n";
		cout << "length of indirect list is: " << ind1.length() << endl;
		d_temp = size % 40;
		cout << d_temp / 4 << " data blocks are filled\n";
	}
	else 
	{
		indirectBlock ind1;
		directBlock d1;
		int temp1, temp2, temp3;
		temp1 = size / 200;
		temp2 = size % 200;
		if (temp2 == 0)
		{
			for (int i = 0; i < temp1; i++)
			{
				ind1.add(4);
			}
		}
		else 
		{
			for (int i = 0; i < temp1; i++)
			{
				ind1.add(4);
			}
			ind1.add(4);
			if (temp2 % 40 == 0)
			{
				for (int i = 0; i<temp2/40; i++)
				{
					d1.add(4);
				}
			}
			else
			{
				for (int i = 0; i<temp2/40 + 1; i++)
				{
					d1.add(4);
				}
				temp3 = (size - (temp1 * 200) - (temp2 * 40)) / 4;
				if ((size - (temp1 * 200) - (temp2 * 40)) % 4 == 0)
				{
					for (int i = 0; i < temp3; i++)
					{
						d1.add(4);
					}
					d1.add(4);
					ind1.get()[ind1.length()-1]=d1;
				}
				else
				{
					for (int i = 0; i < temp3+1; i++)
					{
						d1.add(i);
					}
					ind1.get()[ind1.length()-1]=d1;
				}

			}
		}
		cout << size / 200 << " indirect blocks are completely filled\n";
		cout << "length of indirect list is: " << ind1.length() << endl;
		ind_temp = size % 200;
		cout << ind_temp / 40 << " direct blocks are completely filled\n";
		cout << "length of list is: " << d1.length() << endl;
		d_temp = ind_temp % 40;
		if (d_temp % 4 != 0) {
			cout << d_temp/4+1<< " data blocks are filled\n";
		}
		else
			cout << d_temp/4 << " data blocks are filled\n";
	}
}
void main() {
	

	int size;

	cout << "enter the size in kilo bytes: ";
	cin >> size;
	listMake(size);

	_getch();
	//return 0;
}