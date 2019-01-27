#include<iostream>
using namespace std;

template<typename T>
class Stack{
	private:
		T *arr;
		int top;
		int capacity;
	public:
		Stack(int Size=15){
			arr = new T[Size];
			top = -1;
			capacity = Size;
		}
		~Stack(){
			delete[] arr;
			top=0;
			capacity=0;
		}
		void push(T var){
			if(isFull())
				cout << "Stack is full" << endl;
			else
				arr[++top]=var;
		}
		T pop(){
			if(isEmpty()){
				cout << "Stack is empty" << endl;
				return NULL;
			}
			else
				return arr[top--];
		}
		T peek(){
			if(isEmpty()){
				cout << "Stack is empty" << endl;
				return NULL;
			}
			else
				return arr[top];
		}
		bool isEmpty(){
			return top==-1;
		}
		bool isFull(){
			return top==capacity-1;
		}
};

template <typename U>
class node{
	private:
		U root;
		node *right;
		node *left;
	public:
		node(U var){
			root=var;
			right=NULL;
			left=NULL;
		}
		node(){
			root=0;
			right=NULL;
			left=NULL:
		}
		void setRight(node a){
			right=a;
		}
		void setLeft(node b){
			left=b;
		}
}