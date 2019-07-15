#include <iostream>
#include <vector>
using namespace std;

template<class DT>
class ExceptionAdd{
};

template<class DT>
class ExceptionMultiply{};

template<class DT>
class ExceptionCV{};

template<class DT>
class SparseRow {
protected:
    int row; // row number.
    int col; // column number.
    DT value; // We will assume that all our values will be integers.
public:
    SparseRow(); // Default contructor;
    SparseRow (int r, int c, DT& v);
    virtual ~SparseRow();  //Desctructor
    void display(); // print row number, column number, value.
    //other methods as you deem fit.
    void setCol(int j); // sets the column no as j.
    void setRow(int i); // set the row no as i.
    void setValue(int a); // set the value as a.
    int getCol(); // gives the column index.
    int getRow(); //give the row index.
    int getValue(); //gives the value at a specific row and column.
};
// Definition of SparseRow default constructor.
template <class DT>
SparseRow<DT>::SparseRow(){
    row = -1;
    col = -1;
    value= -1;
}
// Implementing SparseRow constructor.
template <class DT>
SparseRow<DT>:: SparseRow(int r, int c, DT& v) {
    row = r;
    col = c;
    value = v;
    
}
// SparseRow destructor
template <class DT>
SparseRow<DT>:: ~ SparseRow() {
    
}
//Implementing the display()
template <class DT>
void SparseRow<DT>:: display(){
    cout<<row<<", "<<col <<", "<<value<<", "<<endl;
}
//Implementing the setCol().
template <class DT>
void SparseRow<DT>::setCol(int j) {
    col = j;
}
//Implementing the setRow.
template <class DT>
void SparseRow<DT>:: setRow (int j) {
    row = j;
}
//Implementing the setValue().
template <class DT>
void SparseRow<DT>::setValue(int a) {
    value = a;
}
//Implementing the getCol().
template <class DT>
int SparseRow<DT>::getCol(){
    return col;
}
//Implementing the getRow().
template <class DT>
int SparseRow<DT>::getRow(){
    return row;
}
//Implementing the getValue().
template <class DT>
int SparseRow<DT>::getValue(){
    return value;
}
template <class DT> // providing a signature of the sparsematrix class template.
class SparseMatrix;

template <class DT>
ostream& operator << (ostream& o, const SparseMatrix<DT>& sm);// for later use

template <class DT>
class SparseMatrix {
    friend ostream& operator << <DT>(ostream& o, const SparseMatrix<DT>& sm);
    
protected:
    int noRows; // Number of rows of the original matrix.
    int noCols; // Number of columns of the original matrix.
    int commonValue; //read from input.
    int noNonSparseValues;
    vector<SparseRow<DT>>* myMatrix; //Array: Dynamic array
public:
    SparseMatrix();
    SparseMatrix(int n, int m, int cv);
    virtual ~SparseMatrix(); //Destructor
    void setSparseRow (int pos, int r, int c, DT& v);
    
    SparseMatrix<DT>* operator * (SparseMatrix<DT>& M); // Operator overloading For multiplication
    SparseMatrix<DT>* operator + (SparseMatrix<DT>& A); // Operator overloading for addition
    SparseMatrix<DT>* operator ! (); // Operator overloading for transpose
    void display(); //Display the sparse matrix
    void displayMatrix(); //Display the matrix in its original format.
    ostream& display (ostream& s);
    int getValueAt(int r, int c); // Gives the value at row r and column c.
    void setCol(int j); // Sets the column index to j.
    void setRow(int i); // Sets the row index to i.
    void setValue(int a); // Sets the value to a.
    vector<SparseRow<DT>>* getMyMatrix(); // Gives my sparse Matrix.
    void setMyMatrix(int r, int c, DT& value, int location); //Sets my matrix.
    void setNSV (int i);
    int getNSV ();
    void setMatrix (vector<SparseRow<DT>>* M);
};
//Default constructor
template <class DT>
SparseMatrix<DT>:: SparseMatrix() {
    // to be finished
}
// SparseMatrix constructor.
template <class DT>
SparseMatrix<DT>::SparseMatrix (int n, int m, int cv)
{
    noRows = n;
    noCols = m;
    commonValue = cv;
    //noNonSparseValues = noNSV;
    myMatrix = new vector<SparseRow<DT>>();
}

template <class DT>
SparseMatrix<DT>:: ~SparseMatrix() {
    if (myMatrix != NULL) {
        delete [] myMatrix;
    }
}

template <class DT>
void SparseMatrix<DT>:: setMatrix(vector<SparseRow<DT>>* M) {
    myMatrix = M;
}

template <class DT>
ostream& operator << (ostream& o, SparseMatrix<DT>& sm) {
    return  sm.display(o);
}
template <class DT>
void SparseMatrix<DT>:: setNSV(int i){
    noNonSparseValues = i;
}

template <class DT>
int SparseMatrix<DT>:: getNSV()
{
    return noNonSparseValues;
}
template <class DT>
ostream& SparseMatrix <DT>:: display(ostream& s) {
    for (int i =0; i < myMatrix->size(); ++i) {
        s << myMatrix->at(i).getRow()<< ", "<<myMatrix->at(i).getRow()<<", "<<myMatrix->at(i).getValue()<< endl;
    }
    return s;
}
//Implementing setMyMatrix, set my matrix to the specified row number, column number and the value.
template <class DT>
void SparseMatrix<DT>::setMyMatrix(int r, int c, DT& value, int location){
    SparseRow<DT> s = SparseRow<DT>(r, c, value);
    myMatrix->push_back(s);
}
//Implementing display(). Prints out the matrix.
template <class DT>
void SparseMatrix<DT>:: display() {
    for (int i=0; i< this->noNonSparseValues; i++) {
        myMatrix->at(i).display();
    }
}
//Implementing displayMatrix(). Prints out the value at the specified row number and column number.
template <class DT>
void SparseMatrix<DT>:: displayMatrix()
{
    for (int i = 0; i < noRows; i++)
    {
        for (int j=0; j < noCols; j++)
        {
            cout << getValueAt(i,j)<< " ";
        }
        cout <<endl;
    }
}
//Implementing getValueAt(). Gives the values at the specified indices.
template <class DT>
int SparseMatrix<DT>::getValueAt(int r, int c)
{
    for (int i=0; i<noNonSparseValues; i++)
    {
        if (myMatrix->at(i).getRow()==r && myMatrix->at(i).getCol() == c) {
            return myMatrix->at(i).getValue();
        }
    }
    return commonValue;
}
// Implementing getMyMatrix(), returns a sparse matrix.
template <class DT>
vector<SparseRow<DT>>* SparseMatrix<DT>:: getMyMatrix(){
    return myMatrix;
}
// Matrix transpose
template <class DT>
SparseMatrix<DT>* SparseMatrix <DT>:: operator! () {
    SparseMatrix<DT>* SM = new SparseMatrix<DT>(noRows, noCols, commonValue); // A pointer of SparseMatrix
    SM->setNSV(noNonSparseValues);
    int loc = 0;
    //looping through the SparseMatrix pointer SM
    for (int i =0; i < noNonSparseValues; i++) {
        int r = myMatrix->at(i).getCol();
        int c = myMatrix->at(i).getRow();
        int val = myMatrix->at(i).getValue();
        SM->setMyMatrix(r, c, val, loc);
        loc++;
        /**
         SM->myMatrix->at(i).setRow(myMatrix->at(i).getCol());
         SM->myMatrix->at(i).setCol(myMatrix->at(i).getRow());
         SM->myMatrix->at(i).setValue(myMatrix->at(i).getValue());
         */
    }
    return SM;
}
//Matrix addition
template <class DT>
SparseMatrix<DT>* SparseMatrix <DT>:: operator+(SparseMatrix<DT>& A) {
    SparseMatrix<DT>* temp = new SparseMatrix (noRows, noCols, commonValue);
    temp->setNSV(noNonSparseValues+ A.getNSV());
    
    SparseMatrix<DT>* sm;
    
    if (noCols != A.noRows  && noRows != A.noCols)
    {
        throw ExceptionAdd<DT>();
    }
    
    if (commonValue != A.commonValue) {
        throw ExceptionAdd<DT>();
    }
    
    int count =0; // a counter
    int i = 0; //row index
    int j; // column index
    int valueToAdd;// the value to be added.
    bool found; // a boolean
    int location = 0; // the position of the value in the array.
    int r =0; // row
    int c =0; // column
    bool* myArray = new bool [A.noNonSparseValues];
    for (int k=0; k < A.noNonSparseValues; k++) {
        myArray[k]=false;
    }
    while(i < noNonSparseValues) {
        j=0;
        found = false;
        //(*temp).myMatrix[(*temp).noNonSparseValues].row = myMatrix[i].row;
        //(*temp).myMatrix[(*temp).noNonSparseValues].col = myMatrix[i].col;
        valueToAdd = commonValue;
        while((j < A.noNonSparseValues) && (!found)) {
            if ((myMatrix->at(i).getRow() == A.myMatrix->at(j).getRow()) && (myMatrix->at(i).getCol() == A.myMatrix->at(j).getCol())) {
                found = true;
                valueToAdd = A.myMatrix->at(j).getValue();
                myArray[j] = true;
                count++;
                r = A.myMatrix->at(j).getRow();
                c= A.myMatrix->at(j).getCol();
            }
            else {
                j++;
                
            }
        }
        if (!found) {
            r = myMatrix->at(j).getRow();
            c= myMatrix->at(j).getCol();
        }
        int addition = myMatrix->at(i).getValue()+valueToAdd;
        
        if (addition != commonValue) {
            (*temp).setMyMatrix(r,c, addition, location);
            location ++;
        }
        
        else {
            count++;
        }
        
        i++;
    }
    for (int k=0; k<A.noNonSparseValues; k++) {
        if (!myArray[k]) {
            (*temp).myMatrix->at(location).setRow(myMatrix->at(k).getRow());
            (*temp).myMatrix->at(location).setCol(myMatrix->at(k).getCol());
            (*temp).myMatrix->at(location).setValue(myMatrix->at(k).getValue());
            location ++;
        }
    }
    int size;
    size = noNonSparseValues + A.noNonSparseValues - count;
    int index=0; //
    sm = new SparseMatrix(noRows, noCols, commonValue);
    sm->setNSV(size);
    for (int i=0; i < size; i++) {
        DT v = temp->myMatrix->at(i).getValue();
        sm->setMyMatrix(temp->myMatrix->at(i).getRow(), temp->myMatrix->at(i).getCol(),
                        v, index);
        index ++;
        
    }
    delete [] myArray;
    return sm;
    
}

//Matrix multiplication
template <class DT>
SparseMatrix<DT>* SparseMatrix <DT>:: operator*(SparseMatrix<DT>& M) {
    
    SparseMatrix<DT>* transpose = !M;
    
    
    SparseMatrix<DT>* MulMatrix; // This is the matrix to be returned.
    SparseMatrix<DT>* trialMatrix = new SparseMatrix(noRows, noCols, commonValue);// A trial SparseMatrix
    trialMatrix->setNSV(noNonSparseValues+ M.getNSV());
    SparseMatrix* trialMatrix_2 = new SparseMatrix(noRows, noCols, commonValue);
    trialMatrix_2->setNSV(noNonSparseValues+ M.getNSV());
    
    if (noCols != M.noRows )
    {
        throw ExceptionMultiply<DT>();
    }
    
    if (commonValue != M.commonValue) {
        throw ExceptionMultiply<DT>();
    }
    
    int before= 0; // Position of the rows.
    int ValueToAdd; // value to be added
    int after; // Position of the rows
    int counter = 0; // a counter
    int location2 = 0; // location of the matrix
    int index_1 = 0; // index of the first matrix
    int index_2; // index fo the second matrix
    int location = 0;
    int count = 0;
    
    while (index_1 < noNonSparseValues) {
        index_2 = 0;
        while ((index_2< transpose->noNonSparseValues)) {
            
            if ((this->myMatrix->at(index_1).getCol() == transpose->myMatrix->at(index_2).getCol()))
            {
                int row = myMatrix->at(index_1).getRow();
                int col = transpose->myMatrix->at(index_2).getRow();
                DT v = myMatrix->at(index_1).getValue() * transpose->myMatrix->at(index_2).getValue();
                
                trialMatrix->setMyMatrix(row, col, v, location);
                location++;
                count++;
            }
            index_2++;
        }
        index_1++;
    }
    //A while loop that  assigns the rows, cols, and the values.
    while (before < trialMatrix->noNonSparseValues)
    {
        after = before + 1;
        
        int r = trialMatrix->myMatrix->at(before).getRow();
        int c = trialMatrix->myMatrix->at(before).getCol();
        int v = trialMatrix->myMatrix->at(before).getValue();
        ValueToAdd = v;
        while (after < count)
        {
            if (trialMatrix->myMatrix->at(after).getRow() == r && trialMatrix->myMatrix->at(after).getCol() == c)
            {
                
                ValueToAdd += trialMatrix->myMatrix->at(after).getValue();
                trialMatrix->myMatrix->at(after).setValue(commonValue);
            }
            after++;
        }
        // In case if the value to add is not equal to the common value, the matrix details are set as specified.
        if (ValueToAdd != commonValue  )
        {
            (*trialMatrix_2 ).setMyMatrix(r, c, ValueToAdd, location2);
            location2++;
            counter++;
        }
        before++;
    }
    
    int SizeFinal = counter; // The final size of the matrix.
    
    int location3= 0;
    MulMatrix = new SparseMatrix(noRows,noCols,commonValue); // Instantiating the MulMatrix.
    MulMatrix->setNSV(SizeFinal);
    
    //looping to derive the row numbers, column numbers and the values of the multiplied matrix..
    for (int i = 0; i < SizeFinal; i++)
    {
        int r = trialMatrix_2 ->myMatrix->at(i).getRow();
        int c = trialMatrix_2 ->myMatrix->at(i).getCol();
        int v = trialMatrix_2 ->myMatrix->at(i).getValue();
        //cout << "it is "<< r << " " << c << " " << v<< endl;
        MulMatrix->setMyMatrix(r, c, v, location3);
        location3++;
    }
    
    //delete trialMatrix;
    //delete trialMatrix_2;
    
    return MulMatrix;
    
}

int main(int argc, const char * argv[]) {
    try {
        int n, m, cv;
        SparseMatrix<int>* temp = new SparseMatrix<int>();
        int v;
        //int k;
        cout<<endl<<"First Matrix"<<endl;
        cin>>n>>m>>cv;
        cout <<n << " "<<m << " "<<cv<<endl; //read the first matrix
        
        SparseMatrix<int>* firstOne = new SparseMatrix<int >(n, m, cv);
        int count=0;
        for (int i=0; i < n; i++)
        {
            for (int j=0; j < m; j++) {
                
                cin>>v;
                
                if (v != cv){
                    SparseRow<int> obj = SparseRow <int>(i, j, v);
                    firstOne->setMyMatrix(i, j, v, count);
                }
                
                
                //firstOne->getMyMatrix()->push_back(obj);
                count ++;
            }
            
        }
        firstOne->setNSV(count);
        
        firstOne->getMyMatrix()->at(0).display();
        
        cout <<"First one in sparse matrix format"<<endl;
        cout<< *firstOne;
        
        cout <<"First one in normal matrix format"<<endl;
        (*firstOne).displayMatrix();
        
        
        cout<<endl<<"second Matrix"<<endl;
        cin>>n>>m>>cv;
        SparseMatrix<int>* secondOne = new SparseMatrix<int>(n, m, cv);
        cout <<n <<" "<<m <<" "<<cv<<endl; //read the second matrix
        
        
        int count2=0;
        for (int i=0; i < n; i++)
        {
            for (int j=0; j < m; j++) {
                
                cin>>v;
                
                if (v != cv){
                    SparseRow<int> obj = SparseRow <int>(i, j, v);
                    secondOne->setMyMatrix(i, j, v, count2);
                }
                
                
                //firstOne->getMyMatrix()->push_back(obj);
                count2 ++;
            }
            
        }
        secondOne->setNSV(count2);
        
        
        cout<<"Second one in sparse matrix format"<<endl;
        cout<<*secondOne;
        
        cout<<"Second one in normal matrix format"<<endl;
        (*secondOne).displayMatrix();
        
        temp =!(*firstOne);
        cout <<"After Transpose first on in normal format"<<endl;
        (*temp).displayMatrix();
        
        temp =!(*secondOne);
        cout<<"After Transpose second one in normal format"<<endl;
        (*temp).displayMatrix();
        
        cout <<"Multiplication of matrices in sparse matrix form: "<<endl;
        temp = (*secondOne) * (*firstOne);
        cout<<*temp;
        
        cout << "Addition of matrices in sparse matrix form: "<<endl;
        temp = (*secondOne) + (*firstOne);
        cout<<*temp;
        
    } catch (ExceptionMultiply<int> myException) {
        cout <<"Multiplication error"<<endl;
        
    }
    catch (ExceptionAdd<int> myException) {
        cout <<"Addition error"<<endl;
        
    }
    catch (ExceptionCV<int> myException) {
        cout <<"Common Value error"<<endl;
        
    }
    
    return 0;
}
