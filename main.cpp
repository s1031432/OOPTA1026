#include <iostream>
using namespace std;

class ComplexNumber{
    public:
        ComplexNumber(){
            this->real = 0;
            this->imaginary = 0;
        }
        ComplexNumber(int r, int i){
            this->real = r;
            this->imaginary = i;
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
        ComplexNumber operator+ (ComplexNumber n);
        ComplexNumber operator- (ComplexNumber n);
        ComplexNumber operator* (ComplexNumber n);
        ComplexNumber operator/ (ComplexNumber n);
        ComplexNumber operator= (string n);
        friend ostream &operator<<( ostream& out, const ComplexNumber &n);
        friend istream &operator>>( istream& in, ComplexNumber &n);
    private:
        int real;
        int imaginary;
};
ComplexNumber ComplexNumber::operator+ (ComplexNumber n){
    ComplexNumber temp;
    temp.real = this->real + n.real;
    temp.imaginary = this->imaginary + n.imaginary;
    return temp;
}
ComplexNumber ComplexNumber::operator- (ComplexNumber n){
    ComplexNumber temp;
    temp.real = this->real - n.real;
    temp.imaginary = this->imaginary - n.imaginary;
    return temp;
}
ComplexNumber ComplexNumber::operator* (ComplexNumber n){
    ComplexNumber temp;
    temp.real = this->real * n.real - this->imaginary * n.imaginary;
    temp.imaginary = this->real * n.imaginary + this->imaginary * n.real;
    return temp;
}
ComplexNumber ComplexNumber::operator/ (ComplexNumber n){
    ComplexNumber temp;
    temp.real = (this->real*n.real+this->imaginary*n.imaginary) / (n.real*n.real + n.imaginary*n.imaginary);
    temp.imaginary = (this->imaginary*n.real - this->real*n.imaginary) / (n.real*n.real + n.imaginary*n.imaginary);
    return temp;
}
ComplexNumber ComplexNumber::operator= (string n){  // example for n: (5, 3), (7, 9), (-3, 2)
    string tempString;
    bool flag = 0;
    for(int i=0;i<n.size();i++){
        if(n[i] == '(' || n[i] == ' '){
            tempString = "";
            flag = 1;
        }
        else if(n[i] == ','){
            this->real = atoi(tempString.c_str());
            flag = 0;
        }
        else if(n[i] == ')'){
            this->imaginary = atoi(tempString.c_str());
            flag = 0;
        }
        else if(flag){
            tempString += n[i];
        }
    }
    return *this;
}
ostream &operator<<( ostream& out, const ComplexNumber &n){
    out<<"("<<n.real<<", "<<n.imaginary<<")";
    return out;
}
istream &operator>>( istream& in, ComplexNumber &n){
    in >> n.real >> n.imaginary;
    return in;
}
int main(){
    ComplexNumber n1(4, 4);
    ComplexNumber n2(2, -2);
    ComplexNumber n3;
    n3 = "(-3, 2)";
    cout<<"n3: "<<n3<<endl;
    n3 = n1+n2;
    cout<<"n3: "<<n3<<endl;
    n3 = n1-n2;
    cout<<"n3: "<<n3<<endl;
    n3 = n1*n2;
    cout<<"n3: "<<n3<<endl;
    n3 = n1/n2;
    cout<<"n3: "<<n3<<endl;
    return 0;
}
