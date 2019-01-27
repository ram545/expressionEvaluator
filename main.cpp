#include "./stack.cpp"
#include <cstring>

node<char> Parser(string exp){
	int i,len=exp.length(),temp,temp1;
	node<int> op1,op2;
	Stack<node> s;
	Stack<char> s1;
	for(i=0;i<len;i++){
		if(exp[i]>='0' && exp[i]<='9'){
			while(i<len && (exp[i]>='0' && exp[i]<='9')){
				temp = exp[i]-'0';
				temp1 = temp1*10+temp;
				i++;
			}
			i--;
			node<int> oper(temp1);
			s.push(oper);
		}
		else if(exp[i]=='(')
			s1.push(exp[i]);
		else if(exp[i]==')'){
			while(s1.peek()!='('){
				node<char> exp(s1.pop());
				op1=s.pop();
				op2=s.pop();
				exp.setRight(op2);
				exp.setLeft(op1);
				s1.push(exp);
			}
		}

	}
}

int main(){
	string expression;
	cin >> expression;
	node<char> value=Parser(expression);
	int Evaluate(value);
	return 0;
}