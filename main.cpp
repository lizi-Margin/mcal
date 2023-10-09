#include <iostream>
#include <stack>

using namespace std ;

#define SLENGTH 100000

bool isNum(char word){
  return 48<= word && word <=57;
}

bool isAsign(char word){
  return word==43||word==45||word==42||word==47 ; // ||word==61;
}

bool isLeftKuohao(char word){
  return word==40;
}

bool isRightKuohao(char word){
  return word==41;
}

bool isEq( char word ){
  return word==61;
}

short getRank(char word){
  if(isLeftKuohao(word)) { return 0 ;}
  if(word == 43||word==45) { return 1;}
  if(word==42||word==47) { return 2 ;}
  return 1;
}

int calc ( char sign , int num1, int num2){
  
  if(!isAsign(sign)) {return 114514;}
  if( sign == 43) { return num1+num2;}
  if(sign == 45) { return num1-num2;}
  if ( sign == 42) { return num1*num2;}
  if ( sign == 47 ) { return num1/num2;}
  return 114514;
}

void computeLast(stack<int> * mStack, stack<char> * sStack){
        if (isLeftKuohao( sStack-> top())||sStack->empty()){return;}
        int tempNum1 = mStack -> top();mStack->pop();
        int tempNum2 = mStack -> top();mStack-> pop();
        mStack->push(calc(sStack->top(),tempNum1 , tempNum2));
        sStack->pop();
        
}

int  getAnswer ( ) {
  char s[SLENGTH];for ( int ii = 0 ; ii<SLENGTH; ii ++ ){s[ii]= 0;}

  cin >> s;

  stack<int>  *  mStack = new stack<int>;
  stack<char> * sStack = new stack<char>;
  
  char thisWord;
  bool flag = true;
  for (int ii =0 ; flag != false &&( thisWord=s[ii])!=13 ; ii +=1){//和回车
    cout<< ii+1<<" Loop  " << thisWord<<endl; 
    if(isEq(thisWord)){flag = false;
      for (;!sStack->empty();)   //死循环！！！！！！
      {computeLast(mStack,sStack);}
    }
   
    if (isNum(thisWord)){mStack->push(thisWord-48);}
    if(isLeftKuohao(thisWord)){sStack ->push(thisWord);}
    if( isAsign(thisWord)){
      if ( sStack->empty() || getRank(thisWord)>getRank(sStack-> top()) ){
        cout<<"isAsign >"<<endl;
        sStack->push(thisWord);
      }
      else if (getRank(thisWord)==getRank(sStack->top())){
        cout << "isAsign =" << endl;
        computeLast(mStack,sStack);
        sStack->push(thisWord);
      }
      else if (getRank(thisWord)<getRank(sStack->top())){
        cout << "isAsign <" << endl;
        computeLast(mStack,sStack);
        sStack->push(thisWord);
        
      }
    }
 
    if ( isRightKuohao(thisWord) ) {
      for(;!isLeftKuohao(sStack->top());){
      computeLast( mStack, sStack);}
      sStack->pop();//希望sStack->top();是左括号
      
      
    }


    cout << "mTop: "<< mStack->top()<<endl; 
    
  }

  int ans = mStack -> top();
  mStack->pop();

  if(mStack -> size() > 0||!sStack->empty()){
    cout<<mStack->top()<<endl;
    cout<<sStack->top()<<endl;
    delete sStack;delete mStack;
    return 114514;
  }
  else {
    delete sStack ; delete mStack;
    cout << "anser is :"<< endl;
    return ans ; 
  }
}

int main () {
  cout << getAnswer() << endl;
}
