//
//  LinkedList.cpp
//
//  Created by Eiji Adachi Medeiros Barbosa
//

#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList()
{
    this->head = new Node<string>();
    this->tail = new Node<string>();
    
    this->head->setNext(this->tail);
    this->head->setPrevious(NULL);

    this->tail->setNext(NULL);
    this->tail->setPrevious(this->head);

    this->quantity = 0;
}

LinkedList::~LinkedList()
{
    Node<string>* n = this->head;
    
    while(n != this->tail)
    {
        Node<string>* toDestroy = n;
        
        n = n->getNext();
        
        delete toDestroy;
    }
    
    delete this->tail;
}

Node<string>* LinkedList::getHead(void)
{
    return this->head;
}

Node<string>* LinkedList::getTail(void)
{
    return this->tail;
}

int LinkedList::getQuantity(void)
{
    return this->quantity;
}

bool LinkedList::isEmpty(void)
{
    return this->quantity == 0;
}

string LinkedList::get(int i)
{
    if( i < 1 || i > this->getQuantity())
    {
        throw invalid_argument("Valor do índice de busca deve estar entre [1, quantity].");
    }
    
    int counter = 1;
    
    string result;
    for(Node<string>* n = this->head->getNext(); n != this->tail; n = n->getNext())
    {
        if( i == counter )
        {
            result = n->getValue();
            break;
        }
        counter++;
    }
    
    return result;
}

int LinkedList::search(string s)
{
    // implementação de busca sequencial
	int counter = 1;
    
    for(Node<string>* n = this->head->getNext(); n != this->tail; n = n->getNext())
    {
        if( s == n->getValue() )
        {
            return counter;
        }
        counter++;
    }

	// std::cerr << "A string [" << s << "] não foi encontrada na lista encadeada!" << std::endl;
    return -1;
}

void LinkedList::print(void)
{
    for(Node<string>* n = this->head->getNext(); n != this->tail; n = n->getNext())
    {
        std::cout << n->getValue() << " ";
    }
    std::cout << std::endl;
}

ListStatus LinkedList::checkConsistency()
{
    if( this->head == NULL )
    {
        return HeadNull;
    }
    else if( this->head->getNext() == NULL )
    {
        return HeadNextNull;
    }
    else if( this->head->getNext()->getPrevious() != this->head )
    {
        return IncorrectLink;
    }
    else if( this->head->getPrevious() != NULL )
    {
        return HeadPrevious;
    }
    
    if( this->tail == NULL )
    {
        return TailNull;
    }
    else if( this->tail->getPrevious() == NULL )
    {
        return TailPreviousNull;
    }
    else if( this->tail->getPrevious()->getNext() != this->tail )
    {
        return IncorrectLink;
    }
    else if( this->tail->getNext() != NULL )
    {
        return TailNext;
    }
    
    if(this->isEmpty())
    {
        if( this->head->getNext() != this->tail )
        {
            return HeadTail;
        }
        
        if( this->head != this->tail->getPrevious() )
        {
            return HeadTail;
        }
    }
    else
    {
        // Verifica encadeamento dos elementos
        for(Node<string>* i = this->head->getNext(); i != this->tail; i=i->getNext())
        {
            if( i->getNext()->getPrevious() != i )
            {
                return IncorrectLink;
            }
            if( i->getPrevious()->getNext() != i )
            {
                return IncorrectLink;
            }
        }
    }
    
    return OK;
}

bool LinkedList::insertBegin(string s)
{
	Node<string>* novo = new Node<string>(s);
	novo->InsertAfter(this->head);
   	this->quantity++;
    return true;
}

bool LinkedList::insertEnd(string s)
{
	Node<string>* novo = new Node<string>(s);
	novo->InsertBefore(this->tail);
	this->quantity++;
    return true;
}

bool LinkedList::insert(int i, string s)
{
    if( i < 1 || i > this->quantity+1)
    {
        std::cerr << "Valor do índice de inserção deve estar entre [1, " << this->quantity+1 << "]." << std::endl;
        return false;
    }
		
    int counter = 1;
    
    for(Node<string>* n = this->head; n != this->tail; n = n->getNext())
    {
        if( i == counter )
        {
            Node<string>* novo = new Node<string>(s);
			novo->InsertAfter(n);
			this->quantity++;
            return true;
        }
        counter++;
    }
    
    return false;
}

bool LinkedList::insertOrdered(string s)
{	
    Node<string>* n = this->head->getNext();
    while(n != this->tail){
        if(n->getValue() > s){
            break;
        };
        n = n->getNext();
    };

    Node<string>* novo = new Node<string>(s);
    novo->InsertBefore(n);
    this->quantity++;
    return true;
}

Node<string>* LinkedList::searchCF(string s)
{
	Node<string>* n = this->head->getNext();
    while(n != this->tail){
        if(n->getValue() == s){
            break;
        };
        n = n->getNext();
    };
    if(n == this->tail){
        // cerr << "O elemento [" << s << "] não foi encontrado na lista encadeada!" << endl;
        return nullptr;
    };
    n->setCount(n->getCount()+1);
    Node<string>* p = n->getPrevious();
    while(n->getCount() > p->getCount() && p != this->head){
        p = p->getPrevious();
    };
    if(p != n->getPrevious()){
        n->Remove();
        n->InsertAfter(p);
    }
    return n;
}

Node<string>* LinkedList::searchMF(string s)
{
    Node<string>* n = this->head->getNext();
    while(n != this->tail){
        if(n->getValue() == s){
            break;
        };
        n = n->getNext();
    };
    if(n == this->tail){
        // cerr << "O elemento [" << s << "] não foi encontrado na lista encadeada!" << endl;
        return nullptr;
    };
	n->Remove();
    n->InsertAfter(this->head);
    return n;
}

string LinkedList::removeEnd(void)
{
	if( this->isEmpty())
	{
		std::cerr << "A lista está vazia, não há elementos a remover!" << std::endl;
        return "";
	};
    Node<string>* toRemove = this->tail->getPrevious();
	string str = toRemove->getValue();
	toRemove->Remove();
	delete toRemove;
	this->quantity--;
    return str;
}

string LinkedList::removeBegin(void)
{
	if( this->isEmpty())
	{
		std::cerr << "A lista está vazia, não há elementos a remover!" << std::endl;
        return "";
	};
    Node<string>* toRemove = this->head->getNext();
	string str = toRemove->getValue();
	toRemove->Remove();
	delete toRemove;
	this->quantity--;
    return str;
}

string LinkedList::remove(int indice)
{
    if( indice < 1 || indice > this->quantity)
    {
        std::cerr << "Valor do índice para remoção deve estar entre [1, " << this->quantity << "]." << std::endl;
        return "";
    };
	if( this->isEmpty() )
	{
		std::cerr << "A lista está vazia, não há elementos a remover!" << std::endl;
        return "";
	};
		
    int counter = 1;
    
    for(Node<string>* n = this->head->getNext(); n != this->tail; n = n->getNext())
    {
        if( indice == counter )
        {
            string str = n->getValue();
			n->Remove();
			delete n;
			this->quantity--;
            return str;
        }
        counter++;
    };
    
    return "";
}
