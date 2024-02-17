#include "string_array.h"

using namespace std;

void myStr::print(){
    for(int i = 0; i < this->length; i++)
        cout << this->data[i];

    cout << endl;
}

void myStr::printNext(){
    for(int i = 0; i < length; i++)
        cout << next[i];
    cout << endl;
}

void myStr::printNextVal(){
    for(int i = 0; i < length; i++)
        cout << nextVal[i];
    cout << endl;
}

void myMatrix::printMatrix(){
    cout << rowNum << "," << colNum << "," << nodeNum << endl;

    for(int i = 0; i < nodeNum; i++)
        cout << nodeList[i].row << "," << nodeList[i].col << "," << nodeList[i].value << endl;
}
myStr::myStr(const char*string) {
    length = strlen(string);
    data = new char[length+1];
    strcpy(data, string);
    data[length] = '\0';
    next = new int[length];
    nextVal = new int[length];
    kmp_next();
    kmp_nextVal();
}
myStr::myStr(const int& Length) {
    length = Length;
    data = new char[length + 1];
    data[length] = '\0';
    next = new int[length];
    nextVal = new int[length];
}
myStr::myStr(const myStr& mystr) {
    length = mystr.length;
    data = new char[length + 1];
    strcpy(data, mystr.data);
    next = new int[length];
    nextVal = new int[length];
    for (int i = 0; i < length; ++i) {
        next[i] = mystr.next[i];
        nextVal[i] = mystr.nextVal[i];
    }
}
myStr::~myStr() {
    length = 0;
    delete[] data;
    delete[] next;
    delete[] nextVal;
}
void myStr::kmp_next() {
    next = new int[length];
    int j = 0, k = -1;
    next[0] = -1;

    while (j < length - 1) {
        if (k == -1 || data[j] == data[k]) {
            ++j;
            ++k;
            next[j] = k;
        }
        else {
            k = next[k];
        }
    }
    
    for (int i = 0; i < length; ++i) {
        next[i] = next[i] + 1;
    }
    
}

void myStr::kmp_nextVal() {
    nextVal = new int[length];
    int j = 1, k = 0;
    nextVal[0] = 0;

    while (j < length) {
        if (k == 0 || data[j - 1] == data[k - 1]) {
            ++j;
            ++k;
            if (data[j - 1] != data[k - 1]) {
                nextVal[j - 1] = k - 1;
            }
            else {
                nextVal[j - 1] = nextVal[k - 1];
            }
        }
        else {
            k = nextVal[k];
        }
    }
    
    for (int i = 0; i < length; ++i) {
       if(nextVal[i]) nextVal[i] = nextVal[i] + 1;
    }
}
bool replaceStr(myStr& S, const int& start, const myStr& T,const myStr&V) {
    int pos =simpleMatch(S,T);
    if (pos != -1) {
        int V_length = strlen(V.data);
        int new_length = S.length - T.length + V_length;
        char* new_data = new char[new_length + 1];

        strncpy(new_data, S.data, pos);
        strncpy(new_data + pos, V.data, V_length);
        strncpy(new_data + pos + V_length, S.data + pos + T.length, S.length - pos - T.length);

        delete[] S.data;
        S.data = new_data;
        S.length = new_length;

        return true;
    }
    return false;
}
int kmpMatch(const myStr& S, const myStr& T) {
    int lenS = S.length;
    int lenT = T.length;
    int i = 0, j = 0;

    while (i < lenS && j < lenT) {
        if (j == -1 || S.data[i] == T.data[j]) {
            ++i;
            ++j;
        }
        else {
            j = T.next[j]-1; // ʹ�� T �� next ������л���
        }
    }

    if (j == lenT) {
        return i - lenT+1; // ����ƥ����ʼλ��
    }
    else {
        return -1; // û��ƥ��
    }
}
int simpleMatch(const myStr& S, const myStr& T) {
    bool find = false;
    for (int i = 0; i <= S.length - T.length; ++i) {
        find = true;
        for (int j = 0; j < T.length; ++j) {
            if (S.data[i + j] != T.data[j]) {
                find = false;
                break;
            }
        }
        if (find) return i+1; // Convert index to start from 0
    }
    return -1;
}
myMatrix::myMatrix(const int& rNum, const int& cNum, const int& nNum, const int* matrix) {
    rowNum = rNum;
    colNum = cNum;
    nodeNum = nNum;
    nodeList = new matrixNode[nodeNum]; // �����ڴ�
    for (int i = 0; i < nNum; ++i) {
        nodeList[i].row = matrix[i*3];
        nodeList[i].col = matrix[i*3 + 1];
        nodeList[i].value = matrix[i*3 + 2];
    }
}
myMatrix::~myMatrix() {
    delete[] nodeList;
}
myMatrix::myMatrix() : nodeList(nullptr), rowNum(0), colNum(0), nodeNum(0) {
}
myMatrix::myMatrix(const myMatrix& matrix) {
    rowNum = matrix.rowNum;
    colNum = matrix.colNum;
    nodeNum = matrix.nodeNum;
    nodeList = new matrixNode[nodeNum];
    for (int i = 0; i < nodeNum; ++i) {
        nodeList[i] = matrix.nodeList[i];
    }
}
void myMatrix::FastTransposeSMatrix(myMatrix& matrix) {
    // ����ת�ú��ϡ�����������������ͷ���Ԫ�ظ���
    matrix.rowNum = colNum;
    matrix.colNum = rowNum;
    matrix.nodeNum = nodeNum;

    // ������ʱ�������ڴ洢ת�ú��ϡ�����ڵ���Ϣ
    matrixNode* tempNodeList = new matrixNode[nodeNum];

    // ��̬�����ڴ涨�� count �� startPos ����
    int* count = new int[matrix.colNum + 1];
    int* startPos = new int[matrix.colNum + 1];

    // ��ʼ�� count �� startPos ����
    for (int i = 0; i <= matrix.colNum; ++i) {
        count[i] = 0;
        startPos[i] = 0;
    }

    // ������ǰ����Ľڵ����飬���ڵ���Ϣ����ת��
    for (int i = 0; i < nodeNum; ++i) {
        count[nodeList[i].col]++;
    }

    for (int i = 1; i <= matrix.colNum; ++i) {
        startPos[i] = startPos[i - 1] + count[i - 1];
    }

    for (int i = 0; i < nodeNum; ++i) {
        int pos = startPos[nodeList[i].col];
        tempNodeList[pos].row = nodeList[i].col;
        tempNodeList[pos].col = nodeList[i].row;
        tempNodeList[pos].value = nodeList[i].value;
        startPos[nodeList[i].col]++;
    }

    // ��ת�ú�Ľڵ����鸳ֵ���µľ������
    matrix.nodeList = tempNodeList;

    // �ͷŶ�̬������ڴ�
    delete[] count;
    delete[] startPos;
}
