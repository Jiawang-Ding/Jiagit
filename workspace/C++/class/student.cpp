#include <iostream>
#include <stdio.h>
using namespace std;

/******************************** Student 类 *******************************/
class Student{

private:
    char *m_name;
    int m_age;
    float m_score;

public:
    Student();
    Student(char *name, int age, float score);
//    ~Student();
    void show();
    void setName(char *name);
    void setAge(int age);
    void setScore(float score);
    char* getName() const;
    int getAge() const;
    int getScore() const;

};

/***************************** 类构造函数 ********************************/
/*
Student::Student(char *name, int age, float score){
    m_name = name;
    m_age = age;
    m_score = score;
}
*/
Student::Student(){
    m_name = NULL;
    m_age = 0;
    m_score = 0;
}
/* 初始化列表方式 */
Student::Student(char *name,int age,float score):m_name(name),m_age(age),m_score(score){
}

/***************************** 类成员函数 ********************************/
void Student::show(){
    cout << "name:" << m_name << "  age:" << m_age << " score:" << m_score <<endl;
}

void Student::setName(char *name){
    m_name = name;
}

void Student::setAge(int age){
    m_age = age;
}

void Student::setScore(float score){
    m_score = score;
}

char* Student::getName() const{
    return m_name;
}

int Student::getAge() const{
    return m_age;
}

int Student::getScore() const{
    return m_score;
}
/***************************** 类析构函数 ********************************/
//Student::~Student(){}



class VarLenArr{
public :
    typedef char* NAME; //类里重定义数据类型

    VarLenArr(int len);
    ~VarLenArr();
    void show(void);
    void write(int n,int value);
    int read(int n);
    NAME getname();

private :
    int *m_arr;
    const int m_len;
    NAME m_arr_name;
};

VarLenArr::VarLenArr(int len):m_len(len){
    if(len>0){
        m_arr = new int[len];
    }else{
        m_arr = NULL;
    }

    m_arr_name = "This is arr example";
}

VarLenArr::~VarLenArr(){
    cout << "~VarLenArr" << endl;
    if(m_arr != NULL){
       // delete []&m_arr;
    }else{
        cout << "m_arr is NULL" << endl;
    }
}

void VarLenArr::show(void){
    for(int i=0;i < m_len;i++)
    {
        cout << m_arr++ << ":" << *m_arr << " " ;
        if((i+1)%10 == 0)
            cout << endl;
    }
}

void VarLenArr::write(int n,int value){
    m_arr[n] = value;
}

int VarLenArr::read(int n){
    return m_arr[n];
}

//使用类里typdef定义的类型，需要使用类调用
VarLenArr::NAME VarLenArr::getname(){
    return m_arr_name;
}

int main()
{
    /*//静态方式
    Student stu((char *)"Xiaoming", 10, 99.9);
    stu.show();
    Student li((char *)"Liyongcheng", 18, 38.0);
    li.show();
    

    //动态方式
    Student *pstu = new Student();
    pstu->setName((char *)"Liuzuoshen");
    pstu->setAge(21);
    pstu->setScore(77.0);
    pstu->show();*/

    VarLenArr *arr = new VarLenArr(60);

    for(int i=0;i < 60;i++)
     arr->write(i,i);

    arr->show();

    cout << arr->getname() << endl;
    
    delete arr;

    return 0;
}
