#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

class A{
	public:
	  int *p;
	public:
	  A(){
	    p = new int;
	  	cout << "this is 无参构造函数" << endl;
	  } 
	  ~A(){
	  	delete p;
	  	cout << "this is 析构函数" << endl;
	  }
	  A(A&& a){
	  	p = a.p;
	  	a.p = nullptr;
	  	cout << "this is 移动构造函数" << endl;
	  }
};

int main (int argc, char const* argv[]){
	A a;
	A b = move(a);
	return 0;
}







