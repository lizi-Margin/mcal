//2025 shc
//2023.10.11 shc 

//胡海洋debug 孙浩程code 朱锐doc
#include <cstdlib>
#define VER "5.2"
//2023数据结构第一次上机作业 -- 计算器
//支持运算：
//+ - * / 加减乘除
//^ 乘方
//sin(v) cos(v) tan(v) 三角函数
//ln(v) log(v1,v2) lg(v) 对数运算
//以及上述运算的自由组合

//最大允许输入的算式长度为 SLENGTH  


#include <iostream>
#include <stack>
#include <cmath>

#include <csignal> 

using namespace std;

#define SLENGTH 100000  //算式最大长度
#define ERRORRES 114514

void handle_signal(int sig) {
  if (sig == SIGINT) {
    cout.put('\n');
    cout.flush();
    exit(0);
  }
}

// 符号&数字判断
bool isNum(char word){
  return (48<= word && word <=57) || word == '.';
}

bool isAsign(char word){
  return word==43||word==45||word==42||word==47 || word ==94  ; // ^
}

bool isLeftKuohao(char word){
  return word==40;
}

bool isRightKuohao(char word){
  return word==41;
}

bool isComma(char word){
   return word==44;
 }  

bool isEq( char word ){
  return word==61 || word== 0; 
}

bool isLetter( char word ){
  return (word >= 'a' && word <= 'z') || (word >= 'A' && word <= 'Z');
}


// 求运算符等级
short getRank(char word){
  if(isLeftKuohao(word) || isLetter(word)) { return 0 ;}
  if(word == 43||word==45) { return 1;}
  if(word==42||word==47) { return 2 ;}
  if(word==94) {return 3;}
  return 1;
}


// 计算
double calc ( char sign , double num1, double num2){
  
  if(!isAsign(sign)) {return ERRORRES;}
  if( sign == 43) { return num1+num2;}
  if(sign == 45) { return num1-num2;}
  if ( sign == 42) { return num1*num2;}
  if ( sign == 47 ) { return num1/num2;}
  if (sign == 94 ) { return pow(num1,num2);}
  return ERRORRES;
}

void computeLast(stack<double> * mStack, stack<char> * sStack){
        if (isLeftKuohao( sStack-> top())||sStack->empty()){return;}
        double tempNum1 = mStack -> top();mStack->pop();
        double tempNum2 = mStack -> top();mStack-> pop();
        mStack->push(calc(sStack->top(),tempNum2 , tempNum1));//1
        sStack->pop();
        
}

void doFunction(stack <double> * mStack , stack<char> * sStack){
  if (isLeftKuohao( sStack-> top())||sStack->empty()){return;}
  char funType = sStack -> top() ; 
  sStack -> pop();

 
  double var = mStack -> top();
  mStack -> pop(); 

  double var2 = 0; 
  if(funType=='l'){
    if (mStack->empty()) { cout << "ERROR: log(v1,v2)函数应该输入两个参数！"<<endl;}
    var2=mStack -> top();
    mStack -> pop ();
    if (var2==')') { cout << "ERROR: log(v1,v2)函数应该输入两个参数！"<<endl;}
  }


  if (funType == 's') { mStack -> push(sin(var));}
  else if (funType == 'c'){ mStack -> push(cos(var));}
  else if ( funType == 't') { mStack  -> push(tan(var));}
  else if (funType == 'l') {
    mStack -> push (log(var)/log(var2));
  }
  else if ( funType == 'n') { mStack -> push(log(var));}
  else if (funType == 'g') {mStack -> push(log10(var));}
  return;
}


double  getAnswer ( ) {


  //字符串
  char s[SLENGTH];for ( int ii = 0 ; ii<SLENGTH; ii ++ ){s[ii]= 0;}

  cin.getline(s,SLENGTH); 
  if (cin.eof()) {  //处理Ctrl+D (EOF)
    exit(0);
    //return ERRORRES;
  }
  if (cin.fail()) {  //处理输入错误
    cin.clear();
    return ERRORRES;
  }
  
  //主栈和符号栈
  stack<double>  *  mStack = new stack<double>;
  stack<char> * sStack = new stack<char>;
  
  
  //Flags
  bool circuitEndFlag = false;
  bool figureFlag = false;
  bool figureIsFloat = false;
  double numIter =0;
  bool specialFunctionFlag = false;
  //bool isExistMinus = false;
  bool lastSignLeftKuoHao=true;
  bool minusSignFlag=false;

  //临时栈
  stack <char> * figureTempStack ;
  int letterSum =0;
  //thisWord 
  char thisWord;
  for (int ii =0 ; circuitEndFlag != true && ii < SLENGTH  ; ii +=1){ 
    thisWord = s[ii];
    if ( thisWord == ' '){continue;}
    //cout<< ii+1<<" Loop  " << thisWord<<endl; 
 
    //特殊函数判断
    //因为特殊函数前面永远不会有数字，所以放在这个位置
    if(isLetter(thisWord) && specialFunctionFlag == false){specialFunctionFlag = true ;
      letterSum += thisWord;  
    }   
    else if ( isLetter(thisWord) && specialFunctionFlag == true){
      letterSum += thisWord;
    }
    else if (isLeftKuohao(thisWord)&&specialFunctionFlag == true){
      sStack->push(thisWord);
      if (letterSum == 330) {sStack->push('s');}//sin
      if (letterSum == 325) {sStack->push('c');}//cos
      if (letterSum == 323) {sStack->push('t');}//tan
      if (letterSum == 322) {sStack->push('l');}//log() &
      if (letterSum == 211) {sStack -> push('g');} //lg()
      if (letterSum == 218) {sStack->push('n');}//ln() 
      specialFunctionFlag = false;
      letterSum = 0;

      continue; // continue -----> 规避之后的左括号判断
    }

   
    //isNum 判断
    if ( isNum(thisWord)&& figureFlag == false) { figureFlag =true;
      figureTempStack = new  stack<char>;
      figureIsFloat = false;
      numIter = 1;
      figureTempStack-> push(thisWord);
    } 
    else if (isNum(thisWord)&&figureFlag == true){
      if(thisWord != '.'){
        figureTempStack->push(thisWord);
        if(figureIsFloat == true) { numIter = numIter*0.1;}
      }
      else {
        figureIsFloat = true;
      }     
    }
    else if(!isNum(thisWord)&&figureFlag == true){
      figureFlag = false;
      double sum=0;
       //iter可能导致浮点结果不完全准确
      for( ; !figureTempStack->empty();){
        sum+=(figureTempStack->top()-48)*numIter;//死循环
        figureTempStack->pop();
        numIter=numIter * 10; 
      }
      delete figureTempStack;
      

      
      if ( minusSignFlag == false) { mStack -> push ( sum );}
      else {
        mStack -> push( - sum );
        minusSignFlag = false;
      }
      
      ii--;
      continue;
    }


    //lastSignLeftKuoHao判断
    if(lastSignLeftKuoHao == true && thisWord == '-') { 
      minusSignFlag = true;
      lastSignLeftKuoHao = false;
      continue; //continue ------>
    }else{
      lastSignLeftKuoHao = false;
    }
    if(isLeftKuohao(thisWord)) { lastSignLeftKuoHao = true;}



    //等号判断
    if(isEq(thisWord)){
      circuitEndFlag = true;
      for (;!sStack->empty();)   //死循环！！！！！！
      {computeLast(mStack,sStack);}
    }


    //左括号   
    if(isLeftKuohao(thisWord)){
      if(minusSignFlag == true){
        sStack -> pop();
        sStack -> push('-');
        minusSignFlag = false;
      }
      sStack ->push(thisWord);}

    //运算符
    if( isAsign(thisWord)){
       
        
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
      
      //thisWord==45?sStack->push('+'):sStack->push(thisWord);
      if(thisWord ==45) { minusSignFlag = true; sStack-> push ('+');}
      else {sStack-> push(thisWord);}
    }
    
    //右括号
    if ( isRightKuohao(thisWord) ) {
      for(;!isLeftKuohao(sStack->top());){
        if(isLetter(sStack->top())){
          doFunction(mStack,sStack);
          break; //break --->
        }
        computeLast( mStack, sStack);
      } //死循环警告
      sStack->pop();//希望sStack->top();是左括号
    }
    
    //函数逗号 specialFunction
    if( isComma(thisWord)){
      for(;!isLetter(sStack->top()) && !isComma(sStack->top());){
        if(isLeftKuohao(sStack->top())){cout<<"topKuohaoERROR"<<endl;}
        computeLast(mStack,sStack);
      }
      if(isComma(sStack->top())){sStack->pop();}
    }


    //一直输出操作数栈顶
  //    if (!mStack->empty()){
  //       cout << "mTop: "<< mStack->top()<<endl; 
  //    }
  //    else{
  //       cout << "mTop: empty"<<endl; 
  //   }
  //    if (!sStack->empty()){
  //       cout << "sTop: "<< sStack->top()<<endl; 
  //    }
  //    else{
  //       cout << "sTop: empty"<<endl; 
  //   }
  }


  //得出结论
  double ans = mStack -> top();
  mStack->pop();

  if(mStack -> size() > 0||!sStack->empty()){
    delete sStack;delete mStack;
    return ERRORRES;
  }
  else {
    delete sStack ; delete mStack; 
    return ans ; 
  }
}


int main () {
  signal(SIGINT, handle_signal);
  
  cout<<"MCAL VER"<<VER<<" by shc 2023.10-2025"<<endl;
  while (1) {
    cout << ""<<endl;
    cout << getAnswer() << endl;
    cout<<""<<endl;
    cout <<"-                     -;"<<endl;
  }
  return 0;
}
