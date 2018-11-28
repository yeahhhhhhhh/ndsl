#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

class Name{
	public:
	  int age;
	  char* c;
	  int *b;
	public:
	  Name(){
//	  	  b = new int;
	  	  cout << "this is 无参构造器" << endl;
	  }
//	  Name(int age, const char* c){
//	  	  this -> age = age;
//	  	  this -> c = new char(strlen(c) + 1);
//	  	  strcpy(this->c, c);
//	  	  b = new int;
//	  	  cout << "this is 带参构造函数 age = " << age << endl;
//	  }
	  Name(const Name& n){
//	  	  age = n.age;
//	  	  this -> c = (char*)malloc(strlen(n.c) + 1);
//	  	  strcpy(c, n.c);
	  	  cout << "this is 自定义拷贝构造函数" << endl;
	  }
	  
	  const Name &operator=(Name &n){
	  	  std::cout<<"operator="<<std::endl;
	  	  return *this;
	  }
	  
//	  ~Name(){
//	  	  delete b;
//	  	  cout << "this is ~Name()" << endl;
//	  }
};

void aaa(Name n){
//	return *this;
}

int main (int argc, char const* argv[]){
//	Name a(10, "a");
//	Name b(20, "b");
//	a = b; // 并不调用自定义拷贝构造函数,而是调用operator=运算符重载，赋值和初始化不相同
	Name a;
	aaa(a);
	
	
	
	
	
//	a.b = new int;
//	Name c = a; // 调用自定义拷贝构造函数
//	cout << "this is 验证是否拷贝成功 c.age = " << c.age << c.c <<endl;
//	cout << "this is 验证是否拷贝成功 a.age = " << a.age << a.c <<endl;
	return 0;
}





















