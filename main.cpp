#include <iostream>
#include <queue>
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
        mStack->push(calc(sStack->top(),tempNum2 , tempNum1));//1
        sStack->pop();
        
}

int  getAnswer ( ) {
  char s[SLENGTH];for ( int ii = 0 ; ii<SLENGTH; ii ++ ){s[ii]= 0;}

  cin >> s;

  stack<int>  *  mStack = new stack<int>;
  stack<char> * sStack = new stack<char>;
  
  
  bool isExistMinus = false;
  
  
  
  char thisWord;
  bool flag = true;
  bool figureFlag = false;
  stack <char> * figureTempStack ;
  for (int ii =0 ; flag != false &&( thisWord=s[ii])!=13 ; ii +=1){
    // cout<< ii+1<<" Loop  " << thisWord<<endl; 
    //isNum 判断
    if ( isNum(thisWord)&& figureFlag == false) { figureFlag =true;
      figureTempStack = new  stack<char>;
      figureTempStack-> push(thisWord);
    } 
    else if (isNum(thisWord)&&figureFlag == true){
      figureTempStack->push(thisWord);}
    else if(!isNum(thisWord)&&figureFlag == true){
      figureFlag = false;
      int sum=0;
      int iter = 1;
      for( ; !figureTempStack->empty();){
        sum+=(figureTempStack->top()-48)*iter;//死循环
        figureTempStack->pop();
        iter=iter * 10; 
      }
      delete figureTempStack;
      
      if(!isExistMinus)mStack->push(sum);
      else {
          mStack->push(-sum);
          isExistMinus=false;
      }
      
      ii--;
      continue;
    }
    //等号判断
    if(isEq(thisWord)){flag = false;
      for (;!sStack->empty();)   //死循环！！！！！！
      {computeLast(mStack,sStack);}
    }




    //其他判断
    if(isLeftKuohao(thisWord)){sStack ->push(thisWord);}
    if( isAsign(thisWord)){
        
        if(thisWord == 45) {
            isExistMinus=true;
        }
        
        
        
      if ( sStack->empty() || getRank(thisWord)>getRank(sStack-> top()) ){
        // cout<<"isAsign >"<<endl;
        // sStack->push(thisWord);
      }
      else if (getRank(thisWord)==getRank(sStack->top())){
        // cout << "isAsign =" << endl;
        computeLast(mStack,sStack);
        // sStack->push(thisWord);
      }
      else if (getRank(thisWord)<getRank(sStack->top())){
        // cout << "isAsign <" << endl;
        computeLast(mStack,sStack);
        // sStack->push(thisWord);
      }
      
      thisWord==45?sStack->push('+'):sStack->push(thisWord);
      
    }
 
    if ( isRightKuohao(thisWord) ) {
      for(;!isLeftKuohao(sStack->top());){
      computeLast( mStack, sStack);} //死循环警告
      sStack->pop();//希望sStack->top();是左括号
      
      
    }
    //一直输出操作数栈顶
    // if (!mStack->empty()){
        // cout << "mTop: "<< mStack->top()<<endl; 
    // }
    // else{
        // cout << "mTop: empty"<<endl; 
    // }
  }

  int ans = mStack -> top();
  mStack->pop();

  if(mStack -> size() > 0||!sStack->empty()){

    // cout<<mStack->top()<<endl;
    // cout<<sStack->top()<<endl;
    delete sStack;delete mStack;//delete  figureTempQueue;
    return 114514;
  }
  else {
    delete sStack ; delete mStack;//delete figureTempQueue;
    // cout << "answer is :"<< endl;
    return ans ; 
  }
}

int main () {
  cout << getAnswer() << endl;
}
