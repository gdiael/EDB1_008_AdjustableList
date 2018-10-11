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
	return false;
}

bool LinkedList::insertEnd(string s)
{
    return false;
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
			novo->Insert(n, n->getNext());
			this->quantity++;
            return true;
        }
        counter++;
    }
    
    return false;
}

bool LinkedList::insertOrdered(string s)
{
		
    int counter = 1;
    Node<string>* n = this->head->getNext();
    while(n != this->tail){
        if(n->getValue() > s){
            break;
        };
        n = n->getNext();
        counter++;
    };

    Node<string>* novo = new Node<string>(s);
    novo->Insert(n->getPrevious(), n);
    this->quantity++;
    return true;
}

Node<string>* LinkedList::searchCF(string s)
{
	std::cout << "\tERRO: LinkedList::searchCF - not yet implemented.\n";
    return nullptr;
}

Node<string>* LinkedList::searchMF(string s)
{
	std::cout << "\tERRO: LinkedList::searchMF - not yet implemented.\n";
    return nullptr;
}

string LinkedList::removeEnd(void)
{
    return "";
}

string LinkedList::removeBegin(void)
{
    return "";
}

string LinkedList::remove(int indice)
{
    return "";
}
