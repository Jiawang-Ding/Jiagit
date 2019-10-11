#include <iostream>

using namespace std;

class Base{

public :
    Base();
    virtual ~Base(); //必须声明为虚函数否则test2无法析构派生类
    virtual void func();
    virtual void func(char *str);

protected:
    char *m_str;
    
};

Base::Base(){
    m_str = new char[100];
    cout << "Base constructor" << endl;
}

Base::~Base(){
    delete[] m_str;
    cout << "Base destructor" << endl;
}

void Base::func(){
    cout << "This is base func" << endl;
}

void Base::func(char *str){
    //m_str = str;
    cout << "This is base func(char*) :" << str << endl;
}

class Derived: public Base{
public:
    Derived();
    ~Derived();
    void func();
    void func(int data);
private:
    
    char *m_name;

};

Derived::Derived(){

    m_name = new char[100];
    cout << "Derived constructor" << endl;
}

Derived::~Derived(){
    delete[] m_name;
    cout << "Derived destructor" << endl;
}

void Derived::func(){
    cout << "This is derived func" << endl;
}

void Derived::func(int data){
    cout << "This is derived func(int):" << data << endl;
}

/***************************************************************************
 * 构成多态的条件
 * 1.必须存在继承关系
 * 2.继承关系中必须有同名的虚函数，并且他们是覆盖关系（函数原型相同）
 * 3.存在基类的指针，通过该指针调用虚函数
 ***************************************************************************/
int main()
{
    
    cout << "Base class size:" << sizeof(Base) << endl;
    cout << "Derived class size:" << sizeof(Derived) << endl;


    cout << "____________ test1 ____________" << endl;
    /* 基类指针指向基类对象 */
    Base *p = new Base();
    p->func(); //调用void Base::func();基类指针正常访问基类成员函数   
    p->func("Hello world"); //调用void Base::func(char*str);基类指针正常访问基类成员函数
    //p->func(123); //编译错误，因为基类指针只能访问从基类继承过去的成员，不能访问派生类新成
    delete p ;

    cout << "____________ test2 ____________" << endl;
    /* 基类指针指向派生类对象 */
    Base *pb = new Derived();
    pb->func(); //调用void Derived::func();基类指针访问派生类成员函数（多态表现）
    pb->func("Hai baby"); //调用void Base::func();基类指针访问基类成员函数
    //pb->func(123); //编译错误，因为基类指针只能访问从基类继承过去的成员，不能访问派生类新成员
    delete pb ;

    cout << "____________ test3 ____________" << endl;
    /* 派生类指针指向派生类对象 */
    Derived *pd = new Derived();
    pd->func(); //正常访问成员函数
    pd->func(1024); //正常访问成员函数
    pd->Base::func("HA HA HA"); //正常访问从父类继承过来的成员函数
    pd->Base::func(); //正常访问从父类继承过来的成员函数
    delete pd;

    return 0;
}
