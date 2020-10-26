#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <regex>
#include "stdlib.h"

using namespace std;

regex regOnlyReal("[-]?[0-9]*");
regex regOnlyImaginary("[-]?[0-9]*[i]");
regex regBoth("[-]?[0-9]*[+-][0-9]*[i]");

class ComplexNumber{
public:
    ComplexNumber(){
        this->real = 0;
        this->imaginary = 0;
    }
    int getReal(){
        return this->real;
    }
    int getImaginary(){
        return this->imaginary;
    }
    void setReal(int r){
        this->real = r;
    }
    void setImaginary(int i){
        this->imaginary = i;
    }
private:
    int real;
    int imaginary;
};
string cal(string a, string op, string b){
    string aR="";
    string aI="";
    string bR="";
    string bI="";
    string result = "";
    if( regex_match(a, regOnlyReal) && regex_match(b, regOnlyReal) ){   // a only real part & b only real part
        if(op == "*")
            return to_string( atoi( a.c_str() ) * atoi( b.c_str() ) );
        else if(op == "+")
            return to_string( atoi( a.c_str() ) + atoi( b.c_str() ) );
        else if(op == "-")
            return to_string( atoi( a.c_str() ) - atoi( b.c_str() ) );
    }
    else if( regex_match(a, regOnlyImaginary) && regex_match(b, regOnlyImaginary) ){    // a only imaginary part & b only imaginary part
        for(int i=0;i<a.size()-1;i++)   // get imaginary of a
            aI += a[i];
        for(int i=0;i<b.size()-1;i++)   // get imaginary of b
            bI += b[i];
        if(op == "*"){
            if(atoi( aI.c_str() ) * atoi( bI.c_str()) < 0)
                result = to_string( atoi( aI.c_str() ) * atoi( bI.c_str() ) * -1)+"i";
            else
                result = to_string( atoi( aI.c_str() ) * atoi( bI.c_str() ))+"i";
        }
        else if(op == "+")
            result = to_string( atoi( aI.c_str() ) + atoi( bI.c_str() ))+"i";
        else if(op == "-")
            result = to_string( atoi( aI.c_str() ) - atoi( bI.c_str() ))+"i";
        return result;
    }
    else if( regex_match(a, regOnlyReal) && regex_match(b, regOnlyImaginary) ){   // a only real part & b only imaginary part
        for(int i=0;i<b.size()-1;i++)   // get imaginary of b
            bI += b[i];
        if(op == "*")
            return to_string( atoi( a.c_str() ) * atoi( bI.c_str() ) )+"i";
        else if(op == "+"){
            return to_string( atoi( a.c_str() ) + atoi( b.c_str() ) )+"i";
        }
        else if(op == "-"){
            if(atoi(bI.c_str())<0)
                return to_string( atoi( a.c_str() )) + "+" +to_string( atoi( bI.c_str() ) ) +"i";
            return to_string( atoi( a.c_str() )) + "-" +to_string( atoi( bI.c_str() ) ) +"i";
        }
    }
    else if( regex_match(a, regOnlyImaginary) && regex_match(b, regOnlyReal) ){     // a only imaginary part & b only real part
        for(int i=0;i<a.size()-1;i++)
            aI += a[i];
        if(op == "*")
            return to_string( atoi( b.c_str() ) * atoi( aI.c_str() ) )+"i";
        else if(op == "+")
            return to_string( atoi( b.c_str() ) + atoi( a.c_str() ) )+"i";
        else if(op == "-")
            return to_string( atoi( b.c_str() ) + atoi( a.c_str() ) )+"i";
    }
    else if(regex_match(a, regBoth) && regex_match(b, regOnlyReal)){
        for(int i=1;;i++){                          
            if(a[i] == '+' || a[i] == '-'){
                for(int j=0;j<i;j++)                // get real part of a
                    aR += a[j];
                if(a[i] == '-')
                    aI += '-';
                for(int j=i+1;a[j]!='i';j++)        // get imaginary part of a
                    aI += a[j];
                break;
            }
        }
        if(op == "*")
            return to_string( atoi(aR.c_str()) * atoi(b.c_str() )) + to_string(atoi( aI.c_str() ) * atoi( b.c_str() ) )+"i";
        else if(op == "+")
            return to_string( atoi(aR.c_str()) + atoi(b.c_str() )) + to_string(atoi( aI.c_str() ) )+"i";
        else if(op == "-")
            return to_string( atoi(aR.c_str()) - atoi(b.c_str() )) + to_string(atoi( aI.c_str() ) )+"i";
    }
    else if(regex_match(a, regBoth) && regex_match(b, regOnlyImaginary)){
        for(int i=1;;i++){                          
            if(a[i] == '+' || a[i] == '-'){
                for(int j=0;j<i;j++)                // get real part of a
                    aR += a[j];
                if(a[i] == '-')
                    aI += '-';
                for(int j=i+1;a[j]!='i';j++)        // get imaginary part of a
                    aI += a[j];
                break;
            }
        }
        for(int i=0;i<b.size()-1;i++)               // get imaginary part of b
            bI += b[i];
        if(op == "*")
            return to_string( atoi(aI.c_str()) * atoi(bI.c_str())*-1 ) + to_string( atoi(aR.c_str()) * atoi(bI.c_str()) )+"i";
        else if(op == "+"){
            if( atoi(aI.c_str()) + atoi(bI.c_str()) > 0)
                return to_string( atoi(aR.c_str()) ) + "+" + to_string( atoi(aI.c_str()) + atoi(bI.c_str()) )+"i";
            return to_string( atoi(aR.c_str()) ) + "-" + to_string( atoi(aI.c_str()) + atoi(bI.c_str()) )+"i";
        }
        else if(op == "-")
            return to_string( atoi(aR.c_str()) ) + to_string( atoi(aI.c_str()) - atoi(bI.c_str()) )+"i";
    }
    else if(regex_match(a, regOnlyReal) && regex_match(b, regBoth)){
        for(int i=1;;i++){                          
            if(b[i] == '+' || b[i] == '-'){
                for(int j=0;j<i;j++)                // get real part of a
                    bR += b[j];
                if(b[i] == '-')
                    bI += '-';
                for(int j=i+1;b[j]!='i';j++)        // get imaginary part of a
                    bI += b[j];
                break;
            }
        }
        if(op == "*")
            return to_string( atoi(bR.c_str()) * atoi(a.c_str() )) + to_string(atoi( bI.c_str() ) * atoi( a.c_str() ) )+"i";
        else if(op == "+")
            return to_string( atoi(aR.c_str()) + atoi(bR.c_str()) ) + to_string( atoi(bI.c_str()) )+"i";
        else if(op == "-")
            return to_string( atoi(aR.c_str()) - atoi(bR.c_str()) ) + to_string( atoi(bI.c_str())*-1 )+"i";
    }
    else if(regex_match(a, regOnlyImaginary) && regex_match(b, regBoth)){
        for(int i=0;i<a.size()-1;i++)               // get imaginary part of a
            aI += a[i];
        for(int i=1;;i++){                          
            if(b[i] == '+' || b[i] == '-'){
                for(int j=0;j<i;j++)                // get real part of a
                    bR += b[j];
                if(b[i] == '-')
                    bI += '-';
                for(int j=i+1;b[j]!='i';j++)        // get imaginary part of a
                    bI += b[j];
                break;
            }
        }
        if(op == "*"){
            if( atoi(bR.c_str()) * atoi(aI.c_str()) > 0)
                return to_string( atoi(bI.c_str()) * atoi(aI.c_str())*-1 ) + "+" + to_string( atoi(bR.c_str()) * atoi(aI.c_str()) )+"i";
            else if( atoi(bR.c_str()) * atoi(aI.c_str()) == 0 )
                return to_string( atoi(bI.c_str()) * atoi(aI.c_str())*-1 );
            return to_string( atoi(bI.c_str()) * atoi(aI.c_str())*-1 ) + to_string( atoi(bR.c_str()) * atoi(aI.c_str()) )+"i";
        }
        else if(op == "+")
            return to_string( atoi(bR.c_str()) ) + to_string( atoi(bI.c_str()) + atoi(aI.c_str()) )+"i";
        else if(op == "-")
            return to_string( atoi(bR.c_str())*-1 ) + to_string( atoi(aI.c_str()) - atoi(bI.c_str()) )+"i";
    }
    else if(regex_match(a, regBoth) && regex_match(b, regBoth) ){
        for(int i=1;;i++){                          
            if(a[i] == '+' || a[i] == '-'){
                for(int j=0;j<i;j++)                // get real part of a
                    aR += a[j];
                if(a[i] == '-')
                    aI += '-';
                for(int j=i+1;a[j]!='i';j++)        // get imaginary part of a
                    aI += a[j];
                break;
            }
        }
        for(int i=1;;i++){                          
            if(b[i] == '+' || b[i] == '-'){
                for(int j=0;j<i;j++)                // get real part of a
                    bR += b[j];
                if(b[i] == '-')
                    bI += '-';
                for(int j=i+1;b[j]!='i';j++)        // get imaginary part of b
                    bI += b[j];
                break;
            }
        }
        int resultR = 0;
        int resultI = 0;
        if(op == "*"){
            resultR = atoi(aR.c_str()) * atoi(bR.c_str()) + atoi(aI.c_str()) * atoi(bI.c_str())*-1;
            resultI = atoi(aR.c_str()) * atoi(bI.c_str()) + atoi(bR.c_str()) * atoi(aI.c_str());
            if(resultI < 0)
                result = to_string(resultR) + to_string(resultI)+"i";
            else if(resultI>0)
                result = to_string(resultR) + "+" + to_string(resultI)+"i";
            else if(resultI == 0)
                result = to_string(resultR);
        }
        else if(op == "+"){
            resultR = atoi(aR.c_str()) + atoi(bR.c_str());
            resultI = atoi(aI.c_str()) + atoi(bI.c_str());
            if(resultI < 0)
                result = to_string(resultR) + to_string(resultI)+"i";
            else if(resultI>0)
                result = to_string(resultR) + "+" + to_string(resultI)+"i";
            else if(resultI == 0)
                result = to_string(resultR);
        }
        else if(op == "-"){
            resultR = atoi(aR.c_str()) - atoi(bR.c_str());
            resultI = atoi(aI.c_str()) - atoi(bI.c_str());
            if(resultI < 0)
                result = to_string(resultR) + to_string(resultI)+"i";
            else if(resultI>0)
                result = to_string(resultR) + "+" + to_string(resultI)+"i";
            else if(resultI == 0)
                result = to_string(resultR);
        }
        return result;
    }
}
int main(){
    int num = 1;
    // cin>>num;
    for(int count=0;count<num;count++){
        char temps[] = "(5+3i)*(2-3i)*(5-9i)+216i+(7-3i)*5-(5-2i)*7-13+i-2i*(5-3i)-7i+5";
        // cin>>temps;
        string s;
        for(int i=0;;i++){
            if(temps[i] == '\0')
                break;
            else if(temps[i] == 'i'){
                if(temps[i-1] == '+')
                    s += '1';
                else if(temps[i-1] == '-')
                    s += '1';
            }
            s += temps[i];
        }
        cout<<endl<<"s[]: "<<s<<endl;
        int lengthOfS = sizeof(temps)/sizeof(temps[0]);
        bool flag=false;
        string temp="";
        vector<string> tempArray;
        regex reg("[0-9]*");
        for(int i=0;i<lengthOfS+1;i++){
            string regString = "";
            regString += s[i];
            if(s[i] == '(')
                flag = true;
            else if(s[i] == ')'){
                if(temp != "")
                    tempArray.push_back(temp);
                temp = "";
                flag = false;
            }
            else if( (s[i] == '+' || s[i] == '-' || s[i] == '*') && !flag){
                if(temp != "")
                    tempArray.push_back(temp);
                temp = s[i];
                if(temp != "")
                    tempArray.push_back(temp);
                temp = "";
            }
            else if( (regex_match(regString, reg) && !flag) || s[i] == 'i')     // s[i] is number
                temp += s[i];
            if(flag)
                if(s[i] != '(' && s[i] != 'i')
                    temp += s[i];
            if(i==lengthOfS){
                if(temp != "")
                    tempArray.push_back(temp);
            }
        }
        cout<<"---- tempArray: "<<endl;
        for(int i=0;i<tempArray.size();i++){
            cout<<i<<": "<<tempArray[i]<<endl;
        }
        for(int i=0;i<tempArray.size();i++){                // scan mul first
            if(tempArray[i] == "*"){
                tempArray[i-1] = cal(tempArray[i-1], "*", tempArray[i+1]);
                for(int j=i;j<tempArray.size()-2;j++)       // move [j+2] to [j]
                    tempArray[j] = tempArray[j+2];
                tempArray.resize(tempArray.size()-2);
                i -= 1;
                cout<<"--"<<endl;
                for(int i=0;i<tempArray.size();i++)
                    cout<<i<<": "<<tempArray[i]<<endl;
                continue;
            }
        }
        for(int i=0;i<tempArray.size();i++){                // scan +, -
            if(tempArray[i] == "+" ||  tempArray[i] == "-"){
                tempArray[i-1] = cal(tempArray[i-1], tempArray[i], tempArray[i+1]);
                for(int j=i;j<tempArray.size()-2;j++)       // move [j+2] to [j]
                    tempArray[j] = tempArray[j+2];
                tempArray.resize(tempArray.size()-2);
                i -= 1;
                cout<<"--"<<endl;
                for(int i=0;i<tempArray.size();i++)
                    cout<<i<<": "<<tempArray[i]<<endl;
            }
        }

        // -- print Complex Number --
        ComplexNumber r;
        if( regex_match(tempArray[0], regOnlyReal)){
            string aR = tempArray[0];
            r.setReal(atoi(aR.c_str()));
        }
        else if( regex_match(tempArray[0], regOnlyImaginary) ){
            string aI = "";
            for(int i=0;i<tempArray[0].size()-1;i++)
                aI += tempArray[0][i];
            r.setImaginary(atoi(aI.c_str()));
        }
        else if( regex_match(tempArray[0], regBoth) ){
            string aR = "";
            string aI = "";
            for(int i=1;;i++){                          
                if(tempArray[0][i] == '+' || tempArray[0][i] == '-'){
                    for(int j=0;j<i;j++)                // get real part of a
                        aR += tempArray[0][j];
                    if(tempArray[0][i] == '-')
                        aI += '-';
                    for(int j=i+1;tempArray[0][j]!='i';j++)        // get imaginary part of a
                        aI += tempArray[0][j];
                    
                    break;
                }
            }
            r.setReal(atoi(aR.c_str()));
            r.setImaginary(atoi(aI.c_str()));
        }
        if( r.getReal() == 0 && r.getImaginary() == 0){
            cout<<"0";
        }
        else if(r.getReal() == 0){
            if(r.getImaginary() == 1)
                cout<<"i";
            else if(r.getImaginary() == -1)
                cout<<"-i";
            else
                cout<<r.getImaginary()<<"i";
        }
        else if(r.getImaginary() == 0){
            cout<<r.getReal();
        }
        else{
            if(r.getImaginary() == 1)
                cout<<"("<<r.getReal()<<"+"<<"i"<<")";
            else if(r.getImaginary() == -1)
                cout<<"("<<r.getReal()<<"-"<<"i"<<")";
            else{
                if(r.getImaginary() > 1){
                    cout<<"("<<r.getReal()<<"+"<<r.getImaginary()<<"i"<<")";
                }
                else if(r.getImaginary() < 1){
                    cout<<"("<<r.getReal()<<r.getImaginary()<<"i"<<")";
                }
            }
        }
        cout<<endl;
    }
    return 0;
}
