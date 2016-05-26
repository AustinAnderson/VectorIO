/******************************************************************************
File:    vectorio.h
Authour: Austin Anderson

Description:

  adds stream insertion compatibility 
  to stl vectors by templated recursion

  example: 
    vector<double> ex(4,32);
    cout<<ex<<endl;

  output:
     ___________________
    |_32_|_32_|_32_|_32_|

******************************************************************************/

#ifndef VECTOR_IO
#define VECTOR_IO

#include <vector>
#include <sstream>
namespace globalsRbadButItsTheOnlyWay{
    static bool printingForMat=false;
}
namespace std{
    //printVec uses recursion between itself and the overloaded insertion
    //operator to determine which level of vector its at and how to format it
    //this allows operator<< to work on vector<vector<someType> > as well as on
    //vector<someType>
    template <typename T>
    string printVec(vector<T>& v){
        stringstream formatter;
        vector<string> values;
        //the static int determines the max size across multiple levels of
        //recursion, which is usually a bad practice, but is in this case the
        //only available option in order to use the operator << to print vectors
        //or anything else, since arguments cant be passed to it.
        static int _MAXSIZE_FOR_ENTRY_=0;
        bool mat=false;
                //determine if the object is a vector of vectors by searching
                //for "|_..." in a single value
                for(int i=0;i<v.size();i++){
                    formatter<<v[i];
                    if(formatter.str().find("|_")!=string::npos){
                        mat=true;//printing a matrix
                        globalsRbadButItsTheOnlyWay::printingForMat=true;//subsequent
                        //calls to lower depth in the recursion will need to
                        //know they are printing for a matrix so they can avoid
                        //resetting the _MAXSIZE_FOR_ENTRY_ variable
                    }
                }
                formatter.str("");
                if(!mat&&!globalsRbadButItsTheOnlyWay::printingForMat){
                    //if it is a vector of directly printable objects,
                    //_MAXSIZE_FOR_ENTRY_ can be reset now
                    _MAXSIZE_FOR_ENTRY_=0;
                }
                //find the maximum length of the string of the value
                for(int i=0;i<v.size();i++){
                    formatter<<v[i];//causes a recursive call to this function
                    //if v[i] is a vector
                    values.push_back(formatter.str());
                    //guarded by mat because _MAXSIZE_FOR_ENTRY_ needs to be the
                    //max length of entries insted of rows
                    if(!mat&&_MAXSIZE_FOR_ENTRY_<formatter.str().size()){
                        _MAXSIZE_FOR_ENTRY_=formatter.str().size();
                    }
                    formatter.str("");
                }
                for(int i=0;i<v.size();i++){
                    //if it is a mat, values will be the formatted vector row
                    //from the recursive call, so simply print it and an endline
                    if(mat&&i<v.size()-1){
                        formatter<<values[i]<<endl;
                    }
                    //last needs to not have an endline
                    else if(mat&&i==v.size()-1){
                        formatter<<values[i];
                    }
                    else{
                        //put out the leading braket
                        formatter<<"|_";
                        int currentSize=values[i].size();
                        int avgSize=(_MAXSIZE_FOR_ENTRY_-currentSize)/2;
                        //tack on avgSize _'s to center the entry
                        for(int j=0;j<avgSize;j++){
                            formatter<<"_";
                        }
                        formatter<<values[i];
                        //from avgSize, the spaces have already been taken up by
                        //the entry, so go from avgSize+currentSize to _MAXSIZE_FOR_ENTRY_
                        //to add _MAXSIZE_FOR_ENTRY_-(avgSize+currentSize) more
                        //_'s to finish centering the text
                        for(int j=avgSize+currentSize;j<=_MAXSIZE_FOR_ENTRY_;j++){
                            formatter<<"_";
                        }
                    }
                }
                if(!mat){
                    formatter<<"|";
                    //add a line of _'s to the front of the stringstream to give
                    //the top of the display
                    if(!globalsRbadButItsTheOnlyWay::printingForMat){
                        formatter.str(" "+string(formatter.str().size()-2,'_')+"\n"+formatter.str());
                    }
                }
                if(mat&&globalsRbadButItsTheOnlyWay::printingForMat){
                    //clean up static variables for later calls
                    _MAXSIZE_FOR_ENTRY_=0;
                    globalsRbadButItsTheOnlyWay::printingForMat=false;
                    //formatter's size contains the sum of all the row's sizes,
                    //so it needs to be devided by the number of rows:
                    //values.size()
                    formatter.str(" "+string(formatter.str().size()/values.size()-2,'_')+"\n"+formatter.str());
                }
        return formatter.str();
    }
    //recurses on type T with the above helper function to work for printing
    //vectors of anything, even other vectors.
    template <typename T>
    ostream& operator<<(ostream& os,vector<T>& v){
        os<<printVec(v);
        return os;
    }
    //allows << to work with pairs.
    template <typename T1,typename T2>
    ostream& operator<<(ostream& os,pair<T1,T2>& p){
        os<<"("<<p.first<<","<<p.second<<")";
        return os;
    }
    //allows vector filling to work like
    //vector>>element1>>element2>>element3>>element4...;
    template <typename T>
    vector<T>& operator>>(vector<T>& v,const T& i){
        v.push_back(i);
        return v;
    }
}
#endif
