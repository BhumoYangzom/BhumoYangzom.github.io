//It is easy to add in LinkedList.
//It is easy to insert.
//Access is hard, random access.

#include<iostream>
using namespace std;

template <class DT>
class LinkedList{
protected:
    DT* _info;
    LinkedList<DT>* _next;
public:
    LinkedList();
    LinkedList(DT& i, LinkedList<DT>* n) ; // Project3 increment linked list
    LinkedList(const LinkedList<DT>& other); // copy constructor
    //LinkedList (const LinkedList<DT>* next);
    LinkedList<DT>& operator = ( LinkedList<DT>& other);// assignment operator
    DT& operator [] (int pos);
    //void operator = (const LinkedList<DT>& other); // assignment operator for null;
    
    ~LinkedList(); // work on the empty constructor
    
    void add (DT& newone); //void add (DT& other)
    void remove ();
    int size();
    DT& infoAT (int i);
    void insertAt (int i, DT& one);
    void removeAt (int i); // Check if removeAT
    // additional method created
    void copy (const LinkedList<DT>& other);
    DT* getInfo();
    LinkedList<DT>* getNext();
    void setInfo(DT* info);
    void setNext(LinkedList<DT>* next);
    void display();
};
//Implementing the default constructor
template <class DT>
LinkedList<DT>:: LinkedList()

{
    _info = NULL;
    _next = NULL;
}
 
// Implementing the constructor with two parameters.
template <class DT>
LinkedList<DT>::LinkedList(DT& i, LinkedList<DT>* n) {
    _info = new DT(i);
    _next = n;
}

// Implementing getters and setters

template<class DT>
DT* LinkedList<DT>:: getInfo(){
    return _info;
}
template <class DT>
LinkedList<DT>* LinkedList<DT>:: getNext(){
    return _next;
}
template <class DT>
void LinkedList<DT>:: setInfo(DT* info){
    _info = info;
}
template <class DT>
void LinkedList<DT>:: setNext(LinkedList<DT> *next){
    _next = next;
}
// MINE: Writing the copy method
template <class DT>
void LinkedList<DT>:: copy(const LinkedList<DT> &other){
    if (other._info == NULL)
        _info = NULL;
    else {
        _info = new DT (*other._info); //copying
        // if (_info==NULL) throw LinkedListMemory();
    }
    if(other._next == NULL)
        _next == NULL;
    else {
        _next = other._next; // copying
        //if (_next == NULL) throw LinkedListMemory();
    }
}
//implementing the assignment operator
template<class DT>
LinkedList<DT>& LinkedList <DT>:: operator=( LinkedList<DT> &other) {
    //TODO: Write this implementation
    //working
    if (_info != NULL)
        delete _info;
    if (_next != NULL)
        delete _next;
    copy(other); // calling the copy method.
    return other;
}

//MINE from reading the textbook: Implementing the copy constructor

template<class DT>
LinkedList<DT>::LinkedList(const LinkedList<DT>& other) {
    copy(other);
}
// Implementing the size() method. Gives the size of the linkedlist
template <class DT>
int LinkedList<DT>:: size(){
    if (_info==NULL)
        return 0;
    return (1+ (*_next).size()); // one plus the size of the next linkedlist.
}
// Implementing the add method. Add to linkedlist
template <class DT>
void LinkedList<DT>:: add (DT& one) {
    if (_info == NULL)
        _info = new DT (one);
    else {
    LinkedList<DT>* temp = new LinkedList(*_info, _next); // Info pointing to the next
    _info = new DT (one);
    _next = temp;
    }
    
}
//Implementing insertAt method. Inserts the element at the specified integer index.
template <class DT> // inserting at a particular position in linkedlist.
void LinkedList<DT>:: insertAt (int pos, DT& x) {
    if (pos ==0) {
        add(x);
    }
    else {
        (*_next).insertAt (pos -1, x); // no need for change, created a new linked list that points to the new list
    }
}

// writing the destructor
template <class DT>
LinkedList<DT>:: ~ LinkedList(){
    if (_info == NULL) {
        return;
    }
    else {
        delete _info;
        _info = NULL; // creating garbage
        delete _next; // the rest of the box is deleted
        _next = NULL; // creating garbage
    }
}

// house cleaning
template <class DT>
void LinkedList<DT>:: remove() {
    if (_info != NULL) {
        delete _info;
        delete _info;
        LinkedList<DT>* temp = _next; // keeping a copy of the next
        _info = (*temp)._info;
        _next = (*temp)._next;
        delete temp;
    }
}

// implementing removeAt; use remove method and specify the position. Exceptions use????
template <class DT>
void LinkedList<DT>:: removeAt(int i){
    // TODO: write this method.
    if (i ==0) {
        return remove();
    }
    _next->removeAt(i-1);
}

// implementing the infoAT method.
// no out of bound position in linkedlist
template <class DT>
DT& LinkedList <DT>:: infoAT(int pos){
    if (pos ==0)
        return *_info;
    return (*_next).infoAT(pos-1);
        
    
}
//Implementing the [] operator for arrays.
template <class DT>
DT& LinkedList <DT>:: operator[](int pos) {
    return infoAT (pos);// returning the value at the position.
}


class Term {
protected:
    int coefficient;
    int exponent;
public:
    // MINE: The default constructors and other constructors.
    Term ();
    
    Term (int coefficient, int exponents); //to make the terms of the polynomials
    ~Term(); // destructor for term class
   // all the necessary methods
    int getExponent();
    int getCoefficient();
    void setExponent(int e);
    void setCoefficient(int co);
    void display();
    
};
Term:: Term() {
    
}

// Implementaion for the term constructor with parameters.
Term:: Term (int co_efficient, int exponents) {
    coefficient = co_efficient;
    exponent = exponents;
}
// Implementing the getters and setters for exponent and coefficient.
int Term:: getExponent() {
    return exponent;
}
int Term:: getCoefficient() {
    return coefficient;
}
void Term::setExponent(int e) {
    exponent = e;
}
void Term::setCoefficient(int co){
    coefficient = co;
}
void Term:: display(){
    while (getExponent() != 0)
    {
    cout<<"("<<getCoefficient()<<", "<<getExponent()<<") + ";
    }
    cout <<endl;
}
class Polynomial {
    //int degree;
    
protected:
    LinkedList<Term>* myPoly;
    //Term& myTerm;
public:
     //all the necessay class methods and the methods you are asked to implement
    
    Polynomial();// constructor
    Polynomial (LinkedList<Term>* otherPoly); // constructor with two parameters
    ~Polynomial(); // destructor
    
    /* Given a value for x evaluate the polynomial and print the result.*/
    int evaluatePoly(int x); // Question: Does the method only takes integer data type?
    
    /* Add a term to the polynomial and make sure that the polynomial is kept in sorted order of the exponent.*/
    void addTerm (int coefficient, int exponent); // Just integer datatype. //bool suggestion
    
    /*Delete the term, that is set the coefficient to be zero for the term containing the exponent specified as the parameter.*/
    void deleteTerm (int exponent); //bool, suggestion
    
    /*Perform polynomial addition with the polynomial specified in the parameter and create a new polynomial.*/
    LinkedList<Term>* addPolynomial (LinkedList<Term>* otherPoly); // Return type Polynomial?
    
    //Overload the + operator.
     LinkedList<Term>* operator + ( LinkedList<Term>* other); // Check if right
    
    /*Perform polynomial multiplication with the polynomial specified in the parameter and create a new polynomial*/
    LinkedList<Term>* multiplyPolynomial (LinkedList<Term>* other); // Return type right?
    
    /* overloading the * operator*/
    LinkedList<Term>* operator * (LinkedList<Term>* other);
    
    /* Print the polynomial in a suitable form such that polynomial can be read.*/
    void printPolynomial();
    
     /* Overload the << operator*/
    ostream& operator << (Polynomial& p);
    //Returns the degree or the highest exponent value of the polynomial
    int getDegree();
    void setDegree(int d);
};
Polynomial:: Polynomial(LinkedList<Term>* otherPoly) {
    myPoly = otherPoly;

}
LinkedList<Term>* Polynomial:: operator*(LinkedList<Term>* other) {
    other = new LinkedList<Term> ();
    Term* otherTerm = other->getInfo();
    LinkedList<Term>* otherNext = other->getNext();
    other = (otherTerm, otherNext);
    
    LinkedList<Term>* product = new LinkedList<Term>(); // the linkedlist where the product of the polynomials is stored.
    Term* productInfo= product->getInfo();
    LinkedList<Term>* productNext = product->getNext();
    product = (*productInfo, productNext);
    
    
    myPoly = new LinkedList<Term> ();
    Term* myTerm = myPoly->getInfo();
    LinkedList<Term> myNext = *myPoly->getNext();
    myPoly = &(myTerm, myNext);
    
    
    return product;
}

// Implementing the + operator for adding two polynomials.

 LinkedList<Term>* Polynomial:: operator+ ( LinkedList<Term>* other )
{
    LinkedList<Term>* temp = new LinkedList<Term> ();
    Term* tempTerm =temp->getInfo();
    LinkedList<Term>* tempNext = temp->getNext();
    temp = (((*tempTerm)), tempNext);
    
    Term* otherTerm = other->getInfo();
    LinkedList<Term>* nextOther = other->getNext();
    other = (((otherTerm)), nextOther);
    
    Term* myTerm = myPoly->getInfo();
    LinkedList<Term>* myNext = myPoly->getNext();
    myPoly = new LinkedList<Term> ();
    myPoly = (((*myTerm)), myNext);
    
    int co =0; // coefficient of the temp terms
    co = tempTerm->getCoefficient();
    int e = 0; // exponent of the temp terms.
    e= tempTerm->getExponent();
    
    while (myNext && nextOther != NULL) // When both the linkedlist are not null.
    {
        if (otherTerm->getExponent()== myTerm->getExponent()) {
            
            co = otherTerm->getCoefficient() + myTerm->getCoefficient();
            e=myTerm->getExponent(); // exponent remains the same.
            
            nextOther = nextOther->getNext();
            otherTerm = nextOther->getInfo();
            otherTerm = new Term (otherTerm->getCoefficient(), otherTerm->getExponent());
            
            
            myNext = myNext->getNext();
            myTerm = myNext->getInfo();
            myTerm = new Term (myTerm->getCoefficient(), myTerm->getExponent());
            
            tempNext = tempNext->getNext();
            tempTerm = tempNext->getInfo();
            tempTerm = new Term(co, e);
        }
        if (otherTerm->getExponent()!= myTerm->getExponent()){
            if (otherTerm->getExponent() > myTerm->getExponent()) {
                // assigning the higher degree term to the temp linked list.
                co = otherTerm->getExponent();
                e = otherTerm ->getCoefficient();
                nextOther = nextOther->getNext();
                otherTerm = nextOther->getInfo();
                otherTerm = new Term (otherTerm->getCoefficient(), otherTerm->getExponent());
                
                
                myNext = myNext->getNext();
                myTerm = myNext->getInfo();
                myTerm = new Term (myTerm->getCoefficient(), myTerm->getExponent());
                
                tempNext = tempNext->getNext();
                tempTerm = tempNext->getInfo();
                tempTerm = new Term(co, e);
            }
            else if (otherTerm->getExponent() < myTerm->getExponent()) {
                co = myTerm->getExponent();
                e = myTerm->getCoefficient();
                nextOther = nextOther->getNext();
                otherTerm = nextOther->getInfo();
                otherTerm = new Term (otherTerm->getCoefficient(), otherTerm->getExponent());
                
                
                myNext = myNext->getNext();
                myTerm = myNext->getInfo();
                myTerm = new Term (myTerm->getCoefficient(), myTerm->getExponent());
                
                tempNext = tempNext->getNext();
                tempTerm = tempNext->getInfo();
                tempTerm = new Term(co, e);
            }
        }
        if (otherTerm->getExponent()==0) {
            nextOther = nextOther->getNext();
            nextOther = NULL;
        }
        if (myTerm->getExponent()==0) {
            myNext = myNext->getNext();
            myNext = NULL;
        }
        
}
    
    return temp;
}


//Complete this method after overloading the + operator
LinkedList<Term>* Polynomial::addPolynomial(LinkedList<Term>* other) {
    LinkedList<Term>* temp = new LinkedList<Term> ();
    
    return temp;
}
LinkedList<Term>* Polynomial:: multiplyPolynomial(LinkedList<Term> *other){
    LinkedList<Term>* temp = new LinkedList<Term> ();
    // write this method
    return temp;
}
void Polynomial::addTerm(int coefficient, int exponent) {
    //LinkedList<DT>* temp = new LinkedList(_info, _next); // Info pointing to the next
    //_info = new DT (one);
   // _next = temp;
    
    Term* newTerm= new Term (coefficient, exponent);
    LinkedList<Term>* next;
    //myPoly = new LinkedList<Term>();
    newTerm = myPoly->getInfo();
    next = myPoly->getNext();
   // myPoly = (newTerm, next);
    int count = 0;
    while (myPoly != NULL)
    {
    if (newTerm->getExponent() > exponent) {
        this->myPoly->add(*newTerm);
        count++;
    }
    else if (newTerm->getExponent() == exponent){
        coefficient = coefficient + newTerm->getCoefficient();
        newTerm = new Term (coefficient, exponent);
        myPoly->add(*newTerm);
        myPoly->removeAt(count);
        count++;
    }
    
   else
       this->myPoly->insertAt(count, *newTerm);
    }
    
}
// Implementing the deleteTerm method. Lookfor the term with the given exponent and sets the coefficient to zero. Try to use the myPoly variable.
void Polynomial::deleteTerm(int e) {
    int co;
    Term* t = myPoly->getInfo();
    if (t->getExponent() == e){
        co =t->getCoefficient();
        co = 0;
    }
}
int Polynomial::evaluatePoly(int x) {
    //Finish
    int sum=0;
    Term* p= myPoly->getInfo();
    while (myPoly->getNext() != NULL) {
        sum = p->getCoefficient()* x^(p->getExponent());
    }
    
    return sum;
}

//ostream& Polynomial::operator * (Polynomial& p) {
    //ostream& s;
   // return s;
//}

int main () {
    
    
    return 0;
    //LinkedList<Polynomial>* Polynomials = new LinkedList<Polynomial> (10);
    
    // create an array of polynomials the maximum being 10;
  
    //LinkedList<Polynomial>* Polynomials[10];
    //Polynomial Polynomials[10];
    
  //  LinkedList<int>* one = new LinkedList<int>();
    //LinkedList<Term>* p ;
    //LinkedList<Term>* other;
    
 /*
  char command;
    
    int polynum, coefficient, exponent, value;
    int i, j; // polynomial number
    
    cin >> command;
    
    while (!cin.eof()) {
        switch (command) {
            case 'I':
                cin>>polynum>>coefficient>>exponent;
                //Polynomials[polynum-1].addTerm (coefficient, exponent);
                break;
            case 'D':
                //.......;
                break;
            case 'A':
                cin>> i >>j ;
                //Polynomials[i]+Polynomials[j];
                break;
            case 'M':
                cin>>i>>j;
                //Polynomials[i].addPolynomial(Polynomials[j]);
                break;
            case 'E':
                cin>>polynum>>value;
               // Polynomials[polynum].evaluatePoly(value);
                break;
            case 'P':
                //cout<< Polynomials[polynum];
                break;
                
            default:
                cout<<"I missed something, Oopps! "<<endl;
                break;
        }
        cin>>command;
        
    }
    

    
}

/*
 Summary:
 
 We are going to study:
 1. Pointer implementation
 2. Array Implementation
 We learned about LinkedList and if the index is -2, then you know that it is empty. But then, it is time consuming a task.
 
 _next is pointing to the location of the next to the next empty spot.
 You have to increment this linked list in the project.
 
 for polynomials:
 
 f(x) = 2 x^5 -3x^2 + 10x -500
 terms: 5, 2, 1, 0
 
 create a class called term:
 
 class Term {
 protected:
 int c;
 int exponent;
 
 }
 
 create a class called polynomial:
 
 class polynomial {
 public:
 LinkedList <Term>* mp; // you can add a term to the polynomial.
 }
 */
    
    
    
}
