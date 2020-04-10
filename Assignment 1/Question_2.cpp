#include<iostream>
#include<string>
using namespace std;

class Item {
private:
	string name_of_item;
	int quantity;
	string category;
	int price;
	int total_price;
public:
	//Default Constructor
	Item() {};
	Item(string name_of_item, string category, int quantity, int price)
	{
		this->name_of_item = name_of_item;
		this->category = category;
		this->quantity = quantity;
		this->price = price;
	};
	void setName(string name)
	{
		this->name_of_item = name;
	}
	string getName()
	{
		return this->name_of_item;
	}
	void setCategory(string category)
	{
		this->category = category;
	}
	string getCategory()
	{
		return this->category;
	}

	void setPrice(int price)
	{
		this->price = price;
	}
	int getPrice()
	{
		return this->price;
	}

	void setQuantity(int quantity)
	{
		this->quantity = quantity;
	}
	int getQuantity()
	{
		return this->quantity;
	}

	int calculatePrice()
	{
		return this->total_price = quantity*price;
	}

};
class Node
{
public:
	void set(Item new_item)
	{
		this->new_item = new_item;
	}
	Item get() 
	{ 
		return this->new_item; 
	}
	Node *getNext() 
	{ 
		return nextNode; 
	}
	void setNext(Node *nextNode)
	{
		this->nextNode = nextNode;
	}
private:
	Item new_item;
	Node *nextNode;
};
class LinkedList 
{
public:
	LinkedList() {
		headNode = new Node;
		headNode->setNext(NULL);
		currentNode = NULL;
		size = 0;
	};
	
	int length()
	{
		return size;
	}
	
	void add(Item new_item)
	{
		Node* newNode = new Node(); //object created	
		newNode->set(new_item); //set value
		if (currentNode != NULL) {//not first node
			newNode->setNext(currentNode->getNext());
			currentNode->setNext(newNode);
			lastCurrentNode = currentNode;
			currentNode = newNode;
		}
		else {
			newNode->setNext(NULL); //1st element,clear memory
			headNode->setNext(newNode);
			lastCurrentNode = headNode;
			currentNode = newNode;
		}
		size++;
	}
	
	void next()
	{
		lastCurrentNode = currentNode;
		currentNode = currentNode->getNext();
	}
	
	Item get()
	{
		return currentNode->get();
	}
    void display()
    {
    	Node *tempNode = currentNode;
    	currentNode = headNode;
    	for (int i = 1;i <= size;i++)
    	{
	    	this->next();
	    	if (currentNode != NULL)
	    	{
		    	cout << "Item : "<< i << endl;	
		    	cout << "\t" << "Product\t\t" << (this->get()).getName()<< endl;
				cout << "\t" << "Category\t" << (this->get()).getCategory()<< endl;
				cout << "\t" << "Price\t\t" << (this->get()).getPrice()<< endl;
				cout << "\t" << "Quantity\t" << (this->get()).getQuantity()<< endl;	
			}
       }
       currentNode = tempNode;
	}

	 bool search(string item_name)
	 {
	 	currentNode = headNode;
	 	bool flag = 0;
	 	for (int i = 1;i <= size; i++)
    	{
    		lastCurrentNode = currentNode;
	    	this->next();
	    	if((this->get()).getName()== item_name)
	    	{
	    		cout<<"Item Found"<<endl;
	    		flag = 1;
	    	    return 1;
	    		break;
			}
		}
			if(flag == 0)
			{
				cout<<"Item not found"<<endl;
				return 0;
			}		
	  }
	  
	  void del(string item_name)
	  {
	  	bool isItemFound = this->search(item_name);
	  	if (isItemFound == 1)
	  	{
	  			lastCurrentNode->setNext(currentNode->getNext());
	  			delete currentNode;	
	  			cout<<"Item Deleted"<<endl;
	  			size--;
		}

	  }
	  
	  void end()
	  {
	  	currentNode = headNode;
	  	for (int i = 1; i <= size; i++)
	  	{
		  	if(currentNode != NULL)
		  	{
		  		this->next();	
			}
		}	
	  }
	  
	  
	 void insert(int position, Item new_item)
	  {
	  	currentNode = headNode;
	  	for (int i = 1 ; i < position; i++)
	  	{
	  	    if(currentNode != NULL)
		  	{
		  		this->next();	
			}		
		}
        this->add(new_item);
	  }
	  
	void squish()
	{
	  	currentNode = headNode;
	  	this->next();
		int tempsize = size;
	  	for (int i = 1 ; i <= tempsize ; i++)
	  	{
	  		if((lastCurrentNode->get()).getName() == (currentNode->get()).getName())
	  		{
	  				lastCurrentNode->setNext(currentNode->getNext());
	  				delete currentNode;	
	  				currentNode=lastCurrentNode->getNext();
					size--;
		    }
		    else this->next();
		}		
	}
	
	void twin()
	{
		currentNode = headNode;
		this->next();
		while (currentNode != NULL)
		{
			this->add(this->get());
			this->next();
		}
	}
  	  
private: 
	int size;
	Node *headNode;
	Node *currentNode, *lastCurrentNode;
	
};
//Driver Function
int main()
 {
	Item item1("Mouse Pad", "Laptop Accessories", 2, 600);
	Item item2("Apple", "Food", 50, 12);
	Item item3("Headphones", "Accessories", 4, 1000);
	
	LinkedList linkedlist;
	linkedlist.add(item1);
	linkedlist.add(item2);
	linkedlist.add(item3);
	cout << "List without twin or squish \n";
	linkedlist.display();
	linkedlist.twin();
	cout << "List after twin\n";	
	linkedlist.display();
	linkedlist.squish();
	cout << "List after squish\n";	
	linkedlist.display();
	return 0;
	
}
