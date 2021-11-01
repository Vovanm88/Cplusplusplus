#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <utility>

#define plusplusplus -=-2
#define minusminusminus +=-2
#define List vector
#define of <

#define doubles double>
#define floats float> 
#define bools unsigned bool>

#define int64s long long>
#define int32s int>
#define int16s short>
#define int8s char>
#define ints int>

#define uint64s unsigned long long>
#define uint32s unsigned int>
#define uint16s unsigned short>
#define uint8s unsigned char>
#define uints unsigned int>

#define int(a) _CpppFeatures::integerify(a)
#define int64(a) _CpppFeatures::integerify64(a)
#define BigInteger _CpppFeatures::BInt

#define map(fn, arr) std::transform(arr.begin(), arr.end(), arr.begin(), fn)

namespace _CpppFeatures{
	template <typename G>
	int integerify(G num){
		return (int)num;
	}
	int integerify(std::string num){
		return std::atoi(num.c_str());
	}
	int integerify(const char *Str){
		return std::atoi(Str);
	}
	template <typename G>
	long long integerify64(G num){
		return (long long)num;
	}
	long long integerify64(std::string num){
		return std::atoll(num.c_str());
	}	
	long long integerify64(const char *Str){
		return std::atoll(Str);
	}	

	// Copypasted from https://github.com/panks/BigInteger
	// Todo: write own implemention
	class BInt{
	private:
	    std::string number;
	    bool sign;
	public:
	    BInt(); // empty constructor initializes zero
	    BInt(std::string s); // "std::string" constructor
	    BInt(std::string s, bool sin); // "std::string" constructor
	    BInt(int n); // "int" constructor
	    void setNumber(std::string s);
	    const std::string& getNumber(); // retrieves the number
	    void setSign(bool s);
	    const bool& getSign();
	    BInt absolute(); // returns the absolute value
	    void operator = (BInt b);
	    bool operator == (BInt b);
	    bool operator != (BInt b);
	    bool operator > (BInt b);
	    bool operator < (BInt b);
	    bool operator >= (BInt b);
	    bool operator <= (BInt b);
	    BInt& operator ++(); // prefix
	    BInt  operator ++(int); // postfix
	    BInt& operator --(); // prefix
	    BInt  operator --(int); // postfix
	    BInt operator + (BInt b);
	    BInt operator - (BInt b);
	    BInt operator * (BInt b);
	    BInt operator / (BInt b);
	    BInt operator % (BInt b);
	    BInt& operator += (BInt b);
	    BInt& operator -= (BInt b);
	    BInt& operator *= (BInt b);
	    BInt& operator /= (BInt b);
	    BInt& operator %= (BInt b);
	    BInt& operator [] (int n);
	    BInt operator -(); // unary minus sign
	    operator std::string(); // for conversion from BInt to std::string
	private:
	    bool equals(BInt n1, BInt n2);
	    bool less(BInt n1, BInt n2);
	    bool greater(BInt n1, BInt n2);
	    std::string add(std::string number1, std::string number2);
	    std::string subtract(std::string number1, std::string number2);
	    std::string multiply(std::string n1, std::string n2);
	    std::pair<std::string, long long> divide(std::string n, long long den);
	    std::string toString(long long n);
	    long long toInt(std::string s);
	};
	BInt::BInt() { // empty constructor initializes zero
	    number = "0";
	    sign = false;
	}
	BInt::BInt(std::string s) { // "std::string" constructor
	    if( isdigit(s[0]) ) { // if not signed
	        setNumber(s);
	        sign = false; // +ve
	    } else {
	        setNumber( s.substr(1) );
	        sign = (s[0] == '-');
	    }
	}
	BInt::BInt(std::string s, bool sin) { // "std::string" constructor
	    setNumber( s );
	    setSign( sin );
	}
	BInt::BInt(int n) { // "int" constructor
	    std::stringstream ss;
	    std::string s;
	    ss << n;
	    ss >> s;
	    if( isdigit(s[0]) ) { // if not signed
	        setNumber( s );
	        setSign( false ); // +ve
	    } else {
	        setNumber( s.substr(1) );
	        setSign( s[0] == '-' );
	    }
	}
	void BInt::setNumber(std::string s) {
	    number = s;
	}
	const std::string& BInt::getNumber() { // retrieves the number
	    return number;
	}
	void BInt::setSign(bool s) {
	    sign = s;
	}
	const bool& BInt::getSign() {
	    return sign;
	}
	BInt BInt::absolute() {
	    return BInt( getNumber() ); // +ve by default
	}
	void BInt::operator = (BInt b) {
	    setNumber( b.getNumber() );
	    setSign( b.getSign() );
	}
	bool BInt::operator == (BInt b) {
	    return equals((*this) , b);
	}
	
	bool BInt::operator != (BInt b) {
	    return ! equals((*this) , b);
	}
	
	bool BInt::operator > (BInt b) {
	    return greater((*this) , b);
	}
	bool BInt::operator < (BInt b) {
	    return less((*this) , b);
	}
	bool BInt::operator >= (BInt b) {
	    return equals((*this) , b)
	           || greater((*this), b);
	}
	bool BInt::operator <= (BInt b) {
	    return equals((*this) , b)
	           || less((*this) , b);
	}
	BInt& BInt::operator ++() { // prefix
	    (*this) = (*this) + 1;
	    return (*this);
	}
	BInt BInt::operator ++(int) { // postfix
	    BInt before = (*this);
	    (*this) = (*this) + 1;
	    return before;
	}
	
	BInt& BInt::operator --() { // prefix
	    (*this) = (*this) - 1;
	    return (*this);
	}
	
	BInt BInt::operator --(int) { // postfix
	    BInt before = (*this);
	    (*this) = (*this) - 1;
	    return before;
	}
	
	BInt BInt::operator + (BInt b) {
	    BInt addition;
	    if( getSign() == b.getSign() ) { // both +ve or -ve
	        addition.setNumber( add(getNumber(), b.getNumber() ) );
	        addition.setSign( getSign() );
	    } else { // sign different
	        if( absolute() > b.absolute() ) {
	            addition.setNumber( subtract(getNumber(), b.getNumber() ) );
	            addition.setSign( getSign() );
	        } else {
	            addition.setNumber( subtract(b.getNumber(), getNumber() ) );
	            addition.setSign( b.getSign() );
	        }
	    }
	    if(addition.getNumber() == "0") // avoid (-0) problem
	        addition.setSign(false);
	    return addition;
	}
	
	BInt BInt::operator - (BInt b) {
	    b.setSign( ! b.getSign() ); // x - y = x + (-y)
	    return (*this) + b;
	}
	BInt BInt::operator * (BInt b) {
	    BInt mul;
	    mul.setNumber( multiply(getNumber(), b.getNumber() ) );
	    mul.setSign( getSign() != b.getSign() );
	    if(mul.getNumber() == "0") // avoid (-0) problem
	        mul.setSign(false);
	    return mul;
	}
	// Warning: Denomerator must be within "long long" size not "BInt"
	BInt BInt::operator / (BInt b) {
	    long long den = toInt( b.getNumber() );
	    BInt div;
	    div.setNumber( divide(getNumber(), den).first );
	    div.setSign( getSign() != b.getSign() );
	    if(div.getNumber() == "0") // avoid (-0) problem
	        div.setSign(false);
	    return div;
	}
	// Warning: Denomerator must be within "long long" size not "BInt"
	BInt BInt::operator % (BInt b) {
	    long long den = toInt( b.getNumber() );
	    BInt rem;
	    long long rem_int = divide(number, den).second;
	    rem.setNumber( toString(rem_int) );
	    rem.setSign( getSign() != b.getSign() );
	    if(rem.getNumber() == "0") // avoid (-0) problem
	        rem.setSign(false);
	    return rem;
	}
	BInt& BInt::operator += (BInt b) {
	    (*this) = (*this) + b;
	    return (*this);
	}
	BInt& BInt::operator -= (BInt b) {
	    (*this) = (*this) - b;
	    return (*this);
	}
	BInt& BInt::operator *= (BInt b) {
	    (*this) = (*this) * b;
	    return (*this);
	}
	BInt& BInt::operator /= (BInt b) {
	    (*this) = (*this) / b;
	    return (*this);
	}
	BInt& BInt::operator %= (BInt b) {
	    (*this) = (*this) % b;
	    return (*this);
	}
	BInt& BInt::operator [] (int n) {
	    return *(this + (n*sizeof(BInt)));
	}
	BInt BInt::operator -() { // unary minus sign
	    return (*this) * -1;
	}
	BInt::operator std::string() { // for conversion from BInt to std::string
	    std::string signedString = ( getSign() ) ? "-" : ""; // if +ve, don't print + sign
	    signedString += number;
	    return signedString;
	}
	bool BInt::equals(BInt n1, BInt n2) {
	    return n1.getNumber() == n2.getNumber()
	           && n1.getSign() == n2.getSign();
	}
	bool BInt::less(BInt n1, BInt n2) {
	    bool sign1 = n1.getSign();
	    bool sign2 = n2.getSign();
	    if(sign1 && ! sign2) // if n1 is -ve and n2 is +ve
	        return true;
	    else if(! sign1 && sign2)
	        return false;
	    else if(! sign1) { // both +ve
	        if(n1.getNumber().length() < n2.getNumber().length() )
	            return true;
	        if(n1.getNumber().length() > n2.getNumber().length() )
	            return false;
	        return n1.getNumber() < n2.getNumber();
	    } else { // both -ve
	        if(n1.getNumber().length() > n2.getNumber().length())
	            return true;
	        if(n1.getNumber().length() < n2.getNumber().length())
	            return false;
	        return n1.getNumber().compare( n2.getNumber() ) > 0; // greater with -ve sign is LESS
	    }
	}
	bool BInt::greater(BInt n1, BInt n2) {
	    return ! equals(n1, n2) && ! less(n1, n2);
	}
	std::string BInt::add(std::string number1, std::string number2) {
	    std::string add = (number1.length() > number2.length()) ?  number1 : number2;
	    char carry = '0';
	    int differenceInLength = abs( (int) (number1.size() - number2.size()) );
	    if(number1.size() > number2.size())
	        number2.insert(0, differenceInLength, '0'); // put zeros from left
	    else// if(number1.size() < number2.size())
	        number1.insert(0, differenceInLength, '0');
	    for(int i=number1.size()-1; i>=0; --i) {
	        add[i] = ((carry-'0')+(number1[i]-'0')+(number2[i]-'0')) + '0';
	        if(i != 0) {
	            if(add[i] > '9') {
	                add[i] -= 10;
	                carry = '1';
	            } else
	                carry = '0';
	        }
	    }
	    if(add[0] > '9') {
	        add[0]-= 10;
	        add.insert(0,1,'1');
	    }
	    return add;
	}
	
	std::string BInt::subtract(std::string number1, std::string number2) {
	    std::string sub = (number1.length()>number2.length())? number1 : number2;
	    int differenceInLength = abs( (int)(number1.size() - number2.size()) );
	    if(number1.size() > number2.size())
	        number2.insert(0, differenceInLength, '0');
	    else
	        number1.insert(0, differenceInLength, '0');
	    for(int i=number1.length()-1; i>=0; --i) {
	        if(number1[i] < number2[i]) {
	            number1[i] += 10;
	            number1[i-1]--;
	        }
	        sub[i] = ((number1[i]-'0')-(number2[i]-'0')) + '0';
	    }
	    while(sub[0]=='0' && sub.length()!=1) // erase leading zeros
	        sub.erase(0,1);
	    return sub;
	}
	std::string BInt::multiply(std::string n1, std::string n2) {
	    if(n1.length() > n2.length())
	        n1.swap(n2);
	    std::string res = "0";
	    for(int i=n1.length()-1; i>=0; --i) {
	        std::string temp = n2;
	        int currentDigit = n1[i]-'0';
	        int carry = 0;
	        for(int j=temp.length()-1; j>=0; --j) {
	            temp[j] = ((temp[j]-'0') * currentDigit) + carry;
	            if(temp[j] > 9) {
	                carry = (temp[j]/10);
	                temp[j] -= (carry*10);
	            } else
	                carry = 0;
	            temp[j] += '0'; // back to std::string mood
	        }
	        if(carry > 0)
	            temp.insert(0, 1, (carry+'0'));
	        temp.append((n1.length()-i-1), '0'); // as like mult by 10, 100, 1000, 10000 and so on
	        res = add(res, temp); // O(n)
	    }
	    while(res[0] == '0' && res.length()!=1) // erase leading zeros
	        res.erase(0,1);
	    return res;
	}	
	std::pair<std::string, long long> BInt::divide(std::string n, long long den) {
	    long long rem = 0;
	    std::string result;
	    result.resize(30000);
	    for(int indx=0, len = n.length(); indx<len; ++indx) {
	        rem = (rem * 10) + (n[indx] - '0');
	        result[indx] = rem / den + '0';
	        rem %= den;
	    }
	    result.resize( n.length() );
	    while( result[0] == '0' && result.length() != 1)
	        result.erase(0,1);
	    if(result.length() == 0)
	        result = "0";
	    return make_pair(result, rem);
	}
	std::string BInt::toString(long long n) {
	    std::stringstream ss;
	    std::string temp;
	    ss << n;
	    ss >> temp;
	    return temp;
	}
	long long BInt::toInt(std::string s) {
	    long long sum = 0;
	    for(int i=0; i<s.length(); i++)
	        sum = (sum*10) + (s[i] - '0');
	    return sum;
	}
}
