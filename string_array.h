#include <iostream>
#include<cstring>
using namespace std;

class myStr
{
private:
    char* data;
    int length;
    int* next;
    int* nextVal;
public:
    myStr(const char*);
    ~myStr();
    myStr(const int&);
    myStr(const myStr&);
    void print();
    void kmp_next();
    void kmp_nextVal();
    void printNext();
    void printNextVal();   
    friend bool replaceStr(myStr&, const int&, const myStr&, const myStr&);
    friend int kmpMatch(const myStr&, const myStr&);
    friend int simpleMatch(const myStr&, const myStr&);

};

struct matrixNode
{
    int row;
    int col;
    int value;
};


class myMatrix
{
private:
    matrixNode* nodeList;
    int rowNum;
    int colNum;
    int nodeNum;

public:
    myMatrix(const int&, const int&, const int&, const int*);
    ~myMatrix();
    myMatrix();
    myMatrix(const myMatrix&);
    void printMatrix();
    void FastTransposeSMatrix(myMatrix&);
};






