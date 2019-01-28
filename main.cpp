/**********************************************************************
* FILENAME:        main.cpp
*
* DESCRIPTION/PURPOSE:
* Design and implement an expression evaluator to evaluate arithmetic expression.
* Expression can have unary and binary operators.
* To start with, you can assume following as possible operators.
* Unary +, Unary -, Binary +, Binary -, multiplication * and division /
*
* AUTHOR: 20020298 | Rama Krishna | sabbella.krishna@wipro.com
* START DATE: 01/25/2019
* SUBMISSION DATE: 01/25/2019
*
* Design: (Explain below algorithm in steps)
* 1) Two stacks one for operators and one for operands
* 2) traverse the length of the string
* 3) if operand, push into operand stack
* 4) if operator is ( , push into operator stack
* 5) if operator is )
*           until top of operator stack is (
*           pop one operator and two operands
*           push the result into operand stack
* 6) if operator is - or +
*           if start of string or immediate left to other operator(expect next to ')' eg:")-" or ")+")
*           push 0 into operand stack(for handling unary -)
* 7) for any new operator check precedence with operator on top of stack
*           while precedence less than or equal to top of stack
*              pop one operator,two operators and push result into operand stack
*           push operator in operator stack
* 8) until operator stack is empty
*               pop one operator,two operators and push result into operand stack
* 9) Finally, operand stack has one value and operator stack is emptys
* ...
**********************************************************************/
#include ".\stack.cpp"
#include <cstdlib>

int precedence(char a){
    if(a=='*' || a=='/')
        return 2;
    else if(a=='+' || a=='-')
        return 1;
    return 0;
}

int result(int a,int b,char c){
    if(c=='*')
        return a*b;
    else if(c=='/'){
        if(b==0){
            cout << "Division by zero not permitted" << endl;
            _Exit(1);
        }
        else
        return a/b;
    }
    else if(c=='+')
        return a+b;
    else if(c=='-')
        return a-b;
}

int evaluator(string exp){
    Stack<int> s1(200);
    Stack<char> s(100);
    int op1,op2,len=exp.length(),i,temp,temp1;
    char op;
    for(i=0;i<len;i++){
        temp=0;
        if(exp[i]>='0' && exp[i]<='9'){
            while(i<len && (exp[i]>='0' && exp[i]<='9')){
                temp1=exp[i]-'0';
                i++;
                temp = temp*10+temp1;
            }
            s1.push(temp);
            i--;
        }
        else{
            if(exp[i]=='(')
                s.push(exp[i]);
            else if(exp[i]==')'){
                while(s.peek()!='('){
                    op1 = s1.pop();
                    op2 = s1.pop();
                    op = s.pop();
                    temp = result(op2,op1,op);
                    s1.push(temp);
                }
                s.pop();
            }
            else{
                if(exp[i]=='-' || exp[i]=='+'){
                    if(i==0 || (exp[i-1]<'0' || exp[i-1]>'9')){
                        if(exp[i-1]!=')')
                            s1.push(0);
                    }
                }
                while(!(s.isEmpty()) && (precedence(exp[i])<=precedence(s.peek()))){
                    op1 = s1.pop();
                    op2 = s1.pop();
                    op = s.pop();
                    temp = result(op2,op1,op);
                    s1.push(temp);
                }
                s.push(exp[i]);
            }
        }
    }
    while(!s.isEmpty()){
        op1 = s1.pop();
        op2 = s1.pop();
        op = s.pop();
        temp = result(op2,op1,op);
        s1.push(temp);
    }
    return s1.peek();
}

int Parser(string exp){
    Stack<node> s1(200);
    Stack<char> s(100);
    int len=exp.length(),i,temp;
    node oper,op1,op2,opr;
    char op;
    for(i=0;i<len;i++){
        if(exp[i]>='0' && exp[i]<='9'){
            temp=i;
            while(temp<len && (exp[temp]>='0' && exp[temp]<='9'))
                temp++;
            opr = new node[];
            opr.setValue(exp.substr(i,temp-i));
            s1.push(opr);
            i=temp-1;
        }
        else{
            if(exp[i]=='(')
                s.push(exp[i]);
            else if(exp[i]==')'){
                while(s.peek()!='('){
                    op1 = s1.pop();
                    op2 = s1.pop();
                    op = s.pop();
                    oper = new node();
                    oper.setValue(op);
                    oper.right=op1;
                    oper.left=op2;
                    s1.push(oper);
                }
                s.pop();
            }
            else{
                if(exp[i]=='-' || exp[i]=='+'){
                    if(i==0 || (exp[i-1]<'0' || exp[i-1]>'9')){
                        if(exp[i-1]!=')'){
                            opr=new node();
                            opr.setValue("0");
                        }
                    }
                }
                while(!(s.isEmpty()) && (precedence(exp[i])<=precedence(s.peek()))){
                    op1 = s1.pop();
                    op2 = s1.pop();
                    op = s.pop();
                    oper = new node();
                    oper.setValue(op);
                    oper.right=op1;
                    oper.left=op2;
                    s1.push(oper);
                }
                s.push(exp[i]);
            }
        }
    }
    while(!s.isEmpty()){
        op1 = s1.pop();
        op2 = s1.pop();
        op = s.pop();
        oper = new node();
        oper.setValue(op);
        oper.right=op1;
        oper.left=op2;
        s1.push(oper);
    }
    return s1.peek();
}
int main(){
    int value;
    string expression;
    cin >> expression;
    value = evaluator(expression);
    cout << value << endl;
    return 0;
}


/**********************************************************************
* TestCases:
* 1. -10+20*8-90/2 ans: 105
* 2. (-10+20)*8-90/2 ans: 35
* 3. 10+20*30-((5+2)*5+25) ans: 550
* 4. 10+20-30*2*5 ans: -270
*
**********************************************************************/
