#include <iostream>
#include <factorial.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter a number: " << endl;
    cin >>n;
    factorial f;
    f.set(n);
    cout <<"";
    cout << "The factorial of"<< n << "is" <<f.get();
    return 0;

}
