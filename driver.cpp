/*
driver.cpp: test the vectorio header
Created: Thu May 26 11:18:34 CDT 2016
*/
#include <iostream>
#include <vector>
#include "vectorio.h"
using namespace std;
class Printable{
    public:
        Printable(int s1,double s2){
            stuffOne=s1;
            stuffTwo=s2;
        }
        friend ostream& operator<<(ostream& o,Printable& p){
            o<<p.stuffOne<<", "<<p.stuffTwo;
            return o;
        }
    private:
        int stuffOne;
        double stuffTwo;
};
int main(){
    vector<vector<int> > testLevelOne;
    int initOne[6]={1,2,3,4,5,6}; int* arr=initOne;
    testLevelOne.push_back(vector<int>(arr,arr+6));

    int initTwo[9]={1,2,3,4,5,6,7,8,9}; arr=initTwo;
    testLevelOne.push_back(vector<int>(arr,arr+9));

    int initThree[6]={1,20,3,400,5,6}; arr=initThree;
    testLevelOne.push_back(vector<int>(arr,arr+6));

    for(unsigned int i=0;i<testLevelOne.size();i++){
        cout<<testLevelOne[i]<<endl;
    }
    cout<<endl;
    cout<<endl;
    cout<<testLevelOne<<endl;



    
    vector<int> testInput;
    testInput>>1>>2>>3>>4>>5;
    cout<<testInput<<endl;
    
    vector<double> testInputDouble;
    testInputDouble>>1.002>>2.10>>3.0>>4.8>>5.0;
    cout<<testInputDouble<<endl;

    vector<Printable> printables;
    printables>>Printable(1,2.4)>>Printable(3,2.001)>>Printable(1,7.232);
    cout<<printables<<endl;


    return 0;
}
