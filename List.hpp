
using namespace cop4530;

template <class T>
void List<T>::init()
{
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    head->prev = nullptr;
    tail->next = nullptr;
    tail->prev = head;
}

template <class T>
List<T>::List()             //default constructor
{
    init();
}

template <class T>
List<T>::~List()            //destructor
{
    clear();
    delete head;        //reclaims head/tail memory
    delete tail;
}

template <class T>
List<T>::List(const List & rhs) //copy constructor
{
    init();     //initializes list
    for( auto & x : rhs)
        push_back(x);       //uses rangle loop to push back elements into the list
}

template <class T>
const List<T> & List<T>::operator=(const List & rhs)    //copy assignment operator
{
    std::cout<<"copy assign being called."<<std::endl;
    List copy = rhs;
    std::swap(*this, copy);     //creates copy of list parameter and swaps the calling object with the copy
    return *this;
}

template <class T>
List<T>::List(List && rhs) //move constructor *not txt
{
    init();
    std::swap(theSize, rhs.theSize);
    std::swap(head, rhs.head);          //initializes new list and swaps members w parameter list members
    std::swap(tail, rhs.tail);


    for(auto & x : rhs)     //iterate through the parameter list
    {
        for(auto itr = begin();itr!=end();itr++)        //iterate through the newly constructed list
        {
            std::swap(*itr, x);         //std::swap the values of the lists
        }
    }
    rhs.clear();        //clear the rhs list
    rhs.head = nullptr;     //set head and tail to nullptr
    rhs.tail = nullptr;
}

template <class T>
List<T> & List<T>::operator=(List && rhs)
{
    if(&rhs == this)
    {
        return *this;           //self assignment check
    }
    else{
        std::swap(theSize, rhs.theSize);
        std::swap(head, rhs.head);          //swap value of size, head, tail, clear parameter list
        std::swap(tail, rhs.tail);
        rhs.clear();
        return *this;
    }

}


template <class T>
List<T>::List(std::initializer_list<T> iList)    //constructor w init list
{
    init();
    for(auto it : iList)
    {
        push_back(it);          //iterate through init list and push back element into List
    }
}

template <class T>
List<T>::List(int num, const T& val)      //constructor for num copies of val
{
    init();
    for (int i=0;i<num;i++)
    {
        push_back(val);         //push back the chosen value num # of times via a for loop
    }
}

template <class T>
List<T>::List(const_iterator start, const_iterator end)   //constructs list w elements from another list betwen start and end
{
    init();
    for(List<T>::const_iterator itr = start; itr != end; itr++)     //iterate through the list from specific iterators
    {
        push_back(*itr);            //push back the value the iterator is pointing to in a new List.
    }
}

template <class T>
List<T> & List<T>::operator=(std::initializer_list<T> iList)    //sets list = init list
{
    clear();        //clears current list
    for(auto it : iList)
    {
        push_back(it);      //pushes back the value found at that position in iList
    }
    return *this;
}

template <class T>          //size fxn
int List<T>::size() const
{
    return theSize;
}

template <class T>
bool List<T>::empty() const         //empty fxn, returns true if empty
{
    return size() == 0;
}

template <class T>
void List<T>::clear()         //clear fxn, deletes all elements in list w/ fxn pop_front
{
    while (!empty())
        pop_front();
}

template <class T>
void List<T>::reverse()
{
    List temp;          //construct temporary list

    for(const_iterator itr = begin();itr!=end();itr++)          //iterate through the current List
    {
        temp.push_front(*itr);      //set temp = reverse of current list via push_front()
    }

    *this = std::move(temp);       //set current List = temp list
}

template <class T>
typename List<T>::iterator List<T>::begin()
{
    return iterator(head->next);        //return iterator @ first element
}

template <class T>
typename List<T>::const_iterator List<T>::begin() const
{
    return const_iterator(head->next);  //return const_iterator @ first element
}

template <class T>
typename List<T>::iterator List<T>::end()
{
    return iterator(tail);  //return iterator @ tail
}

template <class T>
typename List<T>::const_iterator List<T>::end() const
{
    return const_iterator(tail);         //return const_iterator @ tail
}

template <class T>
T & List<T>::front()
{
    return *begin();        //dereference begin() iterator
}

template <class T>
const T & List<T>::front() const
{
    return *begin();        //dereference begin() iterator
}

template <class T>
T & List<T>::back()
{
    return *--end();        //decrement and dereference end() iterator
}

template <class T>
const T & List<T>::back() const
{
    return *--end();        //decrement and dereference end() iterator
}

template <class T>
void List<T>::push_front(const T & val)
{
    std::cout<<"copy push being called"<<std::endl;
    insert( begin(), val);      //inserts element val at the begin() iterator, aka first element position.
}


template <class T>
void List<T>::push_front(T && val)
{
    insert( begin(), std::move(val));   //inserts element val at the begin() iterator, aka first element position.
}


template <class T>
void List<T>::push_back(const T & val)
{
    insert( end(), val);        //inserts element val at the end() iterator, aka last element position.
}

template <class T>
void List<T>::push_back(T && val)
{
    insert( end(), std::move(val)); //inserts element val at the end() iterator, aka last element position.
}

template <class T>
void List<T>::pop_front()
{
    erase(begin());     //calls erase() with one parameter, passes in begin() fxn which is an iterator pointing to first position
}

template <class T>
void List<T>::pop_back()
{
    erase(--end());     //calls erase() with one parameter, passes in --end() fxn which is an iterator decremented from tail position
}

// ------------- const_iterator class ---------
template <class T>
List<T>::const_iterator::const_iterator()
{
    current = nullptr;  //const_iterator constructor, sets current to a nullptr
}

template <class T>
const T & List<T>::const_iterator::operator*() const
{
    return retrieve();      //dereference operator calls retrieve fxn
}

template <class T>
typename List<T>::const_iterator & List<T>::const_iterator::operator++()        //increment prefix operator
{
        current = current->next;        //sets current = pointing to next node
        return *this;
}

template <class T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)       //increment postfix operator
{
    const_iterator old = *this;     //creates iterator old, sets = position of current iterator
    ++(*this);      //increments the current iterator
    return old;     //returns newly created iterator
}


template <class T>
typename List<T>::const_iterator & List<T>::const_iterator::operator--()        //decrement prefix operator
{
    current = current->prev;        //sets current = pointing to previous node
    return *this;
}

template <class T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int)       //decrement postfix operator
{
    const_iterator old = *this;     //creates iterator old, sets = position of current iterator
    --(*this);      //decrements the current iterator
    return old;     //returns newly created iterator
}

template <class T>
bool List<T>::const_iterator::operator==(const const_iterator & rhs) const
{
    return current == rhs.current;  //returns true if the current iterator is pointing to the same thing as rhs.current
}

template <class T>
bool List<T>::const_iterator::operator!=(const const_iterator & rhs) const
{
    return current != rhs.current;  //returns true if the current iterator is NOT pointing to the same thing as rhs.current
}

template <class T>
T & List<T>::const_iterator::retrieve() const
{
    if(current != nullptr)      //if iterator == valid position
    {
        return current->data;    //"retrieves" data
    }
    else
    {
    throw "Invalid iterator position.";     //else throw an error
    }
}

template <class T>
List<T>::const_iterator::const_iterator(Node * p)
{
    current = p;        //sets current pointer = passed in pointer
}

//-------------iterator class-------------

template <class T>
List<T>::iterator::iterator()       //default iterator constructor
{}

template <class T>
T & List<T>::iterator::operator*()
{
    return const_iterator::retrieve();      //calls inherited(?) function from const_iterator
}

template <class T>
const T & List<T>::iterator::operator*() const
{
    return const_iterator::retrieve();      //calls inherited(?) function from const_iterator
}

template <class T>
typename List<T>::iterator & List<T>::iterator::operator++() //increment prefix operator
{
    this->current = this->current->next;        //sets current = pointing to next node
    return *this;
}

template <class T>
typename List<T>::iterator List<T>::iterator::operator++(int)   //increment postfix operator
{
    iterator old = *this;   //creates iterator old, sets = position of current iterator
    ++(*this);  //increments the current iterator
    return old; //returns newly created iterator
}

template <class T>
typename List<T>::iterator & List<T>::iterator::operator--()    //decrement prefix operator
{
    this->current = this->current->prev;    //sets current = pointing to previous node
    return *this;
}

template <class T>
typename List<T>::iterator List<T>::iterator::operator--(int)   //decrement postfix operator
{
    iterator old = *this;   //creates iterator old, sets = position of current iterator
    --(*this);      //decrements the current iterator
    return old; //returns newly created iterator
}

template <class T>
List<T>::iterator::iterator(Node * p)
{
    this->current = p;      //sets current pointer = passed in pointer
}

//--------------List class---------------

template <class T>
void List<T>::remove(const T &val)
{
    iterator itr = begin();     //create new itr at beginning of List
    while (itr != end())
    {
        if (itr.current->data == val)       //iterate thru List, if data == val...
        {
            erase(itr);     //call erase() function at that position
        }
        itr++;      //increment itr
    }
}

template <class T>
template <class PREDICATE>
void List<T>::remove_if(PREDICATE pred)
{
    iterator itr = begin();     //create new itr at beginning of List
    while (itr != end())        //iterate thru list..
    {
        if(bool(pred(*itr)))        //if the predicate is true for the element @ itr, bool value = true
        {
            erase(itr);     //and element is erased
        }
        itr++;      //increment iterator
    }
}

template <class T>
void List<T>::print(std::ostream& os, char ofc) const
{
    for(const_iterator itr = begin(); itr != end(); ++itr)      //create iterator and iterate thru List
    {
        os<<*itr<<ofc;      //output element iterator pointing towards, followed by delimiter
    }
}

template <class T>
typename List<T>::iterator List<T>::erase(iterator itr)
{
    Node * p = itr.current;     //creation of new node, set equal to current
    iterator retVal;    //construct new iterator retVal
    retVal.current = p->next;       //set retval.current point to next node in list
    p->prev->next = p->next;            //the previous node before p will point to the one after p
    p->next->prev = p->prev;        //and vice versa, the node after p will point backwards to the node before p
    delete p;           //p deleted to reclaim memory
    theSize--;          //theSize decremented as node is effectively removed
    return retVal;          //return iterator retVal pointing to next node
}

template <class T>
typename List<T>::iterator List<T>::erase(iterator from, iterator to)
{
    for(iterator itr = from; itr != to; itr = erase(itr))
    {}      //uses for loop with iterator to call erase(1 param) for the iterator positions between the positions passed through
    return to;      //return the iterator that was removed up to but not removed itself
}


template <class T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val)
{
    Node * p = itr.current;     //creation of pointer p to Node = pointer to current node
    theSize++;                              //theSize incremented
    Node * newNode = new Node{val, p->prev, p};             //creation of new node, initalize data as value and prev and next values
    p->prev->next = newNode;        //the previous node in List's next points to the NewNode
    p->prev = newNode;          //p's previous now points to the new Node

    return itr;         //returns iterator to the position after NewNode was inserted
}


template <class T>
typename List<T>::iterator List<T>::insert(iterator itr, T&& val)
{
    Node * p = itr.current;         //creation of pointer p to Node = pointer to current Node
    theSize++;                      //theSize incremented
    Node * newNode = new Node{std::move(val), p->prev, p};              //creation of new Node, use of std::move to move value and initialize newNode
    p->prev->next = newNode;        //rearrangement of pointers to insert newNode in front of current itr position
    p->prev = newNode;

    return p;
}



template <class T>
std::ostream & operator<<(std::ostream &os, const List<T> &l)       //<< ostream overload
{
    l.print(os);            //call to print fxn
    return os;
}

template <class T>
bool operator==(const List<T> & lhs, const List<T> &rhs)
{
    if (lhs.size() != rhs.size())
    {
        return false;           //immediately, if the lists have differnt sizes, they are different and fxn returns false
    }
    else
    {
       typename List<T>::const_iterator itr1 = lhs.begin();     //creation of iterator for lhs list
       typename List<T>::const_iterator itr2 = rhs.begin();         //creation of iterator for rhs list

        for(int i = 0;i<lhs.size();i++)         //for loop for the size of the lists
        {
            if (*itr1 != *itr2)     //if they ever are not equal, return false
            {
                return false;
            }
            else
            {
                itr1++;     //increment both iterators and repeat
                itr2++;
            }
        }
        return true;        //if nothing found different, return true
    }
}

template <class T>
bool operator!=(const List<T> & lhs, const List<T> &rhs)
{
    int counter = 0;
    typename List<T>::const_iterator itr1 = lhs.begin();     //creation of iterators itr1 and itr2 for each list
    typename List<T>::const_iterator itr2 = rhs.begin();

       if (lhs.size() == rhs.size())            //if they have the same size, they could still be different lists.
       {
            for(int i = 0;i<lhs.size();i++)
            {
                if (*itr1 == *itr2)         //if the element at both iterators is equal, increase a counter
                {
                    counter ++;
                    itr1++;                     //both iterators also incremented
                    itr2++;
                    if(counter == lhs.size())
                    {
                        return false;               //if counter == the size of the lists, they are equivalent lists and will return false
                    }
                }
            }
        return true;                //if they have the same size, but counter doesn't increase to size number, they are different
       }
       else
       {
           return true;         //if they have different sizes, automatically different lists
       }
}
