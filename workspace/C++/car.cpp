#include <iostream>
using namespace std;

class CType
{
private:
    int radius;
    int width;
public:
    CType(int r,int w):radius(r),width(w){

    }
    void typeshow()
    {
        cout << " radius:" << radius << " width:" << width << endl; 
    }
};

class CEngine
{

};

class CCar
{
private:
    int price;
    CType type;
    CEngine engine;
public:
    CCar(int p,int tr,int tw);
    void carshow();
};

CCar::CCar(int p,int tr, int tw):price(p),type(tr,tw){

}

void CCar::carshow(){
    cout << "price:" << price;
    type.typeshow();
}



int& setvalue(int& data)
{
   data += 10;

   return data;
}

int main()
{
//    CCar car(20000,17,225);
//    car.carshow();

    int n=100,m=200;
    int value;
    float f = 3.14f;

    const int &p = (n+m);
    const int &f1 = f;
    int&n1 = n;

    value = setvalue(n1);
    cout << "p:" << p << " value:" << value << " f1:" << f1 <<" f:"<< f << endl;

    return 0;
}

