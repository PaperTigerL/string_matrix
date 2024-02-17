#include "string_array.h"
using namespace std;
int main() {	
    /*
	myStr S("hello TJU!");
    myStr T("TJU");
    myStr T1("NKU");
    myStr T2("future");
    int isFind;
    isFind=replaceStr(S,8,T1,T2);
    cout<<isFind<<endl;//0
    isFind=replaceStr(S,1,T, T2);
    cout<<isFind<<endl;//1
    S.print();//hello future!
    isFind=replaceStr(S,1,T1, T2);
    cout<<isFind<<endl;//0
  */
    int isFind;
    myStr matchS("aabaabaabaac");
    myStr matchT("aabaac");
/**
    isFind=simpleMatch(matchS,matchT);
    cout<<isFind<<endl;//7
  */
    /*
   matchS.kmp_next();
   matchS.kmp_nextVal();
   matchS.printNext();//012123456789
   matchS.printNextVal();//002002002009
   */
    /*
   matchT.kmp_next();
   matchT.kmp_nextVal();
   matchT.printNext();//012123
   matchT.printNextVal();//002003

   isFind=kmpMatch(matchS,matchT);
   cout<<isFind<<endl;//7
 */

	
   int i[]={2,3,10,2,4,30,4,4,25};
   myMatrix M(5,6,3,i);
   M.printMatrix();//5,6,3
                //2,3,10
                //2,4,30
                //4,4,25
   myMatrix T;
   
   M.FastTransposeSMatrix(T);
   T.printMatrix();//6,5,3
                //3,2,10
                //4,2,30
                //4,4,25
	
    return 0;
}