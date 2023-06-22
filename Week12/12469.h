class BigInt{
	public:
        long long operator [](int i) const { return m[i]; }
        long long &operator [](int i) { return m[i]; }
        BigInt(){ l=1, m[0]=0; sign=1; }
        friend istream& operator>>(istream&, BigInt&);   
        friend ostream& operator<<(ostream&, BigInt);   
        BigInt operator +( const BigInt &y );  
        BigInt operator -( const BigInt &y );
    private:
        long long m[MAX_N];
        int l; //長度
        int sign;
};
#include<iostream>
#include<algorithm>
#include<string> 
#define MAX_N 1000
#define MAX_Bit 5
#define MAX 100000

class BigInt{
	public:
        long long operator [](int i) const { return m[i]; }
        long long &operator [](int i) { return m[i]; }
        BigInt(){ l=1, m[0]=0; sign=1; }
        friend istream& operator>>(istream&, BigInt&);   
        friend ostream& operator<<(ostream&, BigInt);   
        BigInt operator +( const BigInt &y );  
        BigInt operator -( const BigInt &y );
    private:
        long long m[MAX_N];
        int l; //長度
        int sign;
};

istream& operator>>(istream &in,  BigInt &b)  
{
    string str; in >> str;
    if(str[0] == '-'){
        b.sign = -1;
        str = str.substr(1, str.length() - 1);
    }
  	else{
      b.sign = 1;
    }
    reverse(str.begin(), str.end());

    int id = 0;
    for(int i = 0; i < str.size(); i += MAX_Bit){
        string substring;
        substring = str.substr(i, MAX_Bit);
        reverse(substring.begin(), substring.end());
        b.m[id++] = stoi(substring);
    }
    b.l = id;
    return in;
}
ostream& operator<<(ostream &out,  BigInt b)  
{
    if(b.sign == -1) out << "-";
    out << b[b.l - 1];
    for(int i = b.l - 2; i >= 0; i--){
        out.width(5);
        out.fill('0');
        out << b[i];
    }
    return out;
}
BigInt BigInt::operator +(const BigInt &y)
{
    BigInt x(*this);
    int i;
    long long carry;
    for(carry = 0, i = 0; i < x.l || i < y.l || carry; i++){
        carry += (i < x.l) * x[i] * x.sign + (i < y.l) * y[i] * y.sign;
        x[i] = carry % MAX;
        carry = carry / MAX;
    }
    x.l = i;

    x.sign = (x[x.l - 1] >= 0) ? 1 : -1;
    if(x[x.l - 1] >= 0){
        for(i = 0; i < x.l; i++){
            if(x[i] < 0){
                x[i + 1]--;
                x[i] += MAX;
            }
        }
    } 
    else{
        for(i = 0; i < x.l; i++){
            if(x[i] > 0){
                x[i + 1]++;
                x[i] -= MAX;
            }
        }
    }

    for(int i = 0; i < x.l; i++){
        x[i] *= x.sign;
    }
    for(; x.l > 1 && x[x.l - 1] == 0; x.l--);
    if(x.sign == -1 && x.l == 1 && x[0] == 0) x.sign = 1;
    return x;
}
BigInt BigInt::operator -( const BigInt &y ){
    BigInt x(*this);
	int i;
	long long carry;
	for(carry = 0, i = 0; i < x.l || i < y.l || carry; i++)
    {
		carry += (i < x.l) * x[i] * x.sign - (i < y.l) * y[i] * y.sign;
		x[i] = carry % MAX;
		carry /= MAX;
	}
	x.l = i;

	x.sign = (x[x.l - 1] >= 0) ? 1 : -1;
    if(x[x.l - 1] >= 0){
        for(i = 0; i < x.l; i++){
            if(x[i] < 0){
                x[i + 1]--;
                x[i] += MAX;
            }
        }
    } 
    else{
        for(i = 0; i < x.l; i++){
            if(x[i] > 0){
                x[i + 1]++;
                x[i] -= MAX;
            }
        }
    }

    for(int i = 0; i < x.l; i++){
        x[i] *= x.sign;
    }
    for(; x.l > 1 && x[x.l - 1] == 0; x.l--);
    if(x.sign == -1 && x.l == 1 && x[0] == 0) x.sign = 1;
    return x;
}








