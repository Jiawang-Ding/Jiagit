#include <iostream>
#include <string>

using namespace std;

int main()
{
    int index;
    string s1(30,'*');
    string s2 = "* sc++ plus";
    string s3 = "* dingding";
    string s4(36,'*');
    
    s1.insert(15," test ");
    s1.erase(15,6);
    s4.erase(30);
    
    index = s2.find("s",0);
    cout << "Found at index :" << index << endl;
    
    index = s3.rfind("i",5);
    cout << "Found at index :" << index << endl;

    cout << s1 << "\n" << s2 << "\n" << s3 << "\n" << s4 << endl;

    return 0;
}
