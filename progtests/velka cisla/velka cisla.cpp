#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cstdint>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

class CBigInt
{
public:








	CBigInt()
	{
		this->number.push_back(0);
		this->neg = false;
	}

	CBigInt(const int number_r)
	{
		if (number_r < 0) neg = true;
		int temp;
		int number = number_r;
		if (number == 0) this->number.push_back(0);
		while (number != 0)
		{
			temp = abs(number % 10);
			this->number.push_back(temp);
			number /= 10;
		}
	}

	CBigInt(const CBigInt& num)
	{
		this->number = num.number;
		this->neg = num.neg;
	}















	CBigInt& operator= (const CBigInt& num)
	{
		this->number.clear();
		this->number = num.number;
		this->neg = num.neg;
		return *this;
	}

	CBigInt& operator= (const int numb)
	{
		int temp;
		this->number.clear();
		int num = numb;
		while (num != 0)
		{
			temp = num % 10;
			this->number.push_back(temp);
			num /= 10;
		}
		if (numb < 0) this->neg = true;
		return *this;
	}

	CBigInt& operator= (const string& num)
	{
		vector <int> temp;
		bool old_neg = this->neg;
		int push = 0;
		int shift = 0;
		if (num.length() > 0)
		{
			if ((int)num[0] == '-')
			{
				this->neg = true;
			}
			else this->neg = false;
		}
		//delete first zeros

		bool first = true;
		for (int i = num.length() - 1; i >= 0; --i)
		{
			if (shift == 1)
			{
				temp.push_back(push);
				shift = 0;
				push = 0;
			}
			if (num[i] == '-' && first)
			{
				first = false;
				continue;
			}
			if (num[i] < '0' || num[i] > '9')
			{
				this->neg = old_neg;
				throw  invalid_argument("invalid param");
			}
			push += abs((int)num[i] - (int)'0');
			shift++;
		}
		if (shift != 0) temp.push_back(push);
		int del = 0;
		for (auto i = temp.end() - 1; i >= temp.begin(); i--)
		{
			if (i == temp.begin()) break;
			if ((*i) == 0) del++;
			else break;
		}
		for (int i = 0; i < del; i++)
		{
			temp.pop_back();
		}
		this->number.clear();
		this->number = temp;
		return *this;
	}

	CBigInt(const string& num)
	{
		*this = num;
	}















	bool greater(const CBigInt& num) const
	{
		if (!this->neg && num.neg) return true;
		else if (this->neg && !num.neg) return false;
		if (!this->neg && !num.neg && this->number.size() > num.number.size()) return true;
		if (!this->neg && !num.neg && this->number.size() < num.number.size()) return false;
		if (this->neg && num.neg && this->number.size() < num.number.size()) return true;
		if (this->neg && num.neg && this->number.size() > num.number.size()) return false;

		if (!this->neg && !num.neg)
		{
			auto c = num.number.end() - 1;
			for (auto i = this->number.end() - 1; i >= this->number.begin(); i--)
			{
				if ((*i) < (*c)) return false;
				else if ((*i) > (*c)) return true;
				if (c == num.number.begin()) break;
				c--;
			}

		}
		if (this->neg && num.neg)
		{
			auto c = num.number.end() - 1;
			for (auto i = this->number.end() - 1; i >= this->number.begin(); i--)
			{
				if ((*i) > (*c)) return false;
				else if ((*i) < (*c)) return true;
				if (c == num.number.begin()) break;
				c--;
			}
		}
		return false;
	}

	bool greater_n(const CBigInt& num) const
	{
		if (this->number.size() > num.number.size()) return true;
		if (this->number.size() < num.number.size()) return false;

		auto c = num.number.end() - 1;
		for (auto i = this->number.end() - 1; i >= this->number.begin(); i--)
		{
			if ((*i) < (*c)) return false;
			if ((*i) > (*c)) return true;
			if (c == num.number.begin()) break;
			c--;
		}
		return true;
	}














	CBigInt& operator+= (const CBigInt& num)
	{
		CBigInt c;
        bool carry = false;

        if(this.neg && !num.neg) return b - a;
        else if(this.neg && !num.neg) return b - a;
        else if (!a.positive && !b.positive) c.positive = false;
        long long int size = a.number.size() < b.number.size() ? b.number.size() : a.number.size();
        
        for (long long int i = 0; i < size; i++  )
        {
          if (i == a.number.size() && i == b.number.size()) break;

          if (i == a.number.size() || i == b.number.size())
          {
            c.number.push_back((i == a.number.size() ? b.number[i] : a.number[i]) + (carry ? 1 : 0));
            carry = false;
          }
          c.number.push_back ((a.number[i] + b.number[i] + (carry ? 1 : 0)) % 10);
          if ((a.number[i] + b.number[i] + (carry ? 1 : 0) > 9) )
          {
            carry = true;
          }
          else carry = false;
        }
        if (carry) c.number.push_back(1);
        return c;
		return *this;
	}

	CBigInt& operator+= (const int num)
	{
		CBigInt a(num);
		*this += a;
		return *this;
	}

	CBigInt& operator+= (const string& num)
	{
		CBigInt a(num);
		*this += a;
		return *this;
	}















	CBigInt& mult(vector <int>& vec, int num)
	{
		CBigInt* ret = new CBigInt;
		ret->number.clear();
		int carry = 0;
		for (auto i = vec.begin(); i < vec.end(); i++)
		{
			ret->number.push_back((((*i) * num) + carry) % 10);
			carry = (((*i) * num) + carry) / 10;
		}
		if (carry != 0) ret->number.push_back(carry);
		return *ret;
	}



















	CBigInt& operator*= (CBigInt& num)
	{
		if ((num.number.size() == 1 && (*num.number.begin()) == 0) || (this->number.size() == 1 && (*this->number.begin()) == 0))
		{
			this->number.clear();
			this->number.push_back(0);
			this->neg = false;
			return *this;
		}
		CBigInt ret, temp;
		int shift = 0;
		for (auto i = num.number.begin(); i < num.number.end(); i++)
		{
			temp = mult(this->number, ((*i) % 10));
			for (int c = 0; c < shift; c++)
			{
				temp.number.insert(temp.number.begin(), 0);
			}
			ret += temp;
			shift++;
		}
		if (this->neg && num.neg) this->neg = false;
		else if (!this->neg && num.neg) this->neg = true;
		else if (this->neg && !num.neg) this->neg = true;
		else if (!this->neg && !num.neg) this->neg = false;
		this->number = ret.number;
		return *this;
	}

	CBigInt& operator*= (const int num)
	{
		CBigInt a(num);
		*this *= a;
		return *this;
	}

	CBigInt& operator*= (const string& num)
	{
		CBigInt a;
		a = num;
		*this *= a;
		return *this;
	}

















	friend CBigInt operator+(CBigInt n1, const CBigInt& num)
	{
		n1 += num;
		return n1;
	}

	friend CBigInt operator+(CBigInt n1, const int num)
	{
		n1 += num;
		return n1;
	}

	friend CBigInt operator+(CBigInt n1, const string& num)
	{
		n1 += num;
		return n1;
	}

	friend CBigInt operator + (const int num1, CBigInt num2)
	{
		CBigInt* a = new CBigInt;
		*a = num2;
		*a += num1;
		return *a;
	}

	friend CBigInt operator + (const string& num1, CBigInt num2)
	{
		CBigInt* a = new CBigInt;
		*a = num2;
		*a += num1;
		return *a;
	}









	friend CBigInt operator*(CBigInt n1, CBigInt& num)
	{
		n1 *= num;
		return n1;
	}

	friend CBigInt operator*(CBigInt n1, const int num)
	{
		n1 *= num;
		return n1;
	}

	friend CBigInt operator*(CBigInt n1, const string& num)
	{
		n1 *= num;
		return n1;
	}

	friend CBigInt operator * (const int num1, CBigInt num2)
	{
		num2 *= num1;
		return num2;
	}

	friend CBigInt operator * (const string& num1, CBigInt num2)
	{
		CBigInt* a = new CBigInt;
		*a = num2;
		*a *= num1;
		return *a;
	}

	// comparison operators, any combination {CBigInt/int/string} {<,<=,>,>=,==,!=} {CBigInt/int/string}










	bool eq(const CBigInt& num) const
	{
		if (!this->neg && num.neg) return false;
		else if (this->neg && !num.neg) return false;
		if (!this->neg && !num.neg && this->number.size() < num.number.size()) return false;
		if (!this->neg && !num.neg && this->number.size() > num.number.size()) return false;
		if (this->neg && num.neg && this->number.size() > num.number.size()) return false;
		if (this->neg && num.neg && this->number.size() < num.number.size()) return false;

		auto c = num.number.begin();
		for (auto i = this->number.begin(); i < this->number.end(); i++)
		{
			if ((*i) != (*c)) return false;
			//if (c == num.number.begin()) break;
			c++;
		}
		return true;
	}











	friend bool operator== (const CBigInt n1, const CBigInt& num)
	{
		return n1.eq(num);
	}

	friend bool operator== (const CBigInt n1, const string& num)
	{
		CBigInt ret(num);
		return n1.eq(ret);
	}

	friend bool operator== (const CBigInt n1, const int num)
	{
		CBigInt ret(num);
		return n1.eq(ret);
	}

	friend bool operator== (const string& num1, const CBigInt& num2)
	{
		CBigInt ret(num1);
		return num2.eq(ret);
	}

	friend bool operator== (const int num1, const CBigInt& num2)
	{
		CBigInt ret(num1);
		return num2.eq(ret);
	}












	friend bool operator!= (const CBigInt n1, const CBigInt& num)
	{
		return !n1.eq(num);
	}

	friend bool operator!= (const CBigInt n1, const string& num)
	{
		CBigInt ret(num);
		return !n1.eq(ret);
	}

	friend bool operator!= (const CBigInt n1, const int num)
	{
		CBigInt ret(num);
		return !n1.eq(ret);
	}

	friend bool operator!= (const string& num1, const CBigInt& num2)
	{
		CBigInt ret(num1);
		return !num2.eq(ret);
	}

	friend bool operator!= (const int num1, const CBigInt& num2)
	{
		CBigInt ret(num1);
		return !num2.eq(ret);
	}










	friend bool operator< (const CBigInt n1, const CBigInt& num)
	{
		return !n1.greater(num) && !n1.eq(num);
	}

	friend bool operator< (const CBigInt n1, const string& num)
	{
		CBigInt ret(num);
		return !n1.greater(ret) && !n1.eq(ret);
	}

	friend bool operator< (const CBigInt n1, const int num)
	{
		CBigInt ret(num);
		return !n1.greater(ret) && !n1.eq(ret);
	}

	friend bool operator< (const string& num1, const CBigInt& num2)
	{
		CBigInt ret(num1);
		return !ret.greater(num2) && !num2.eq(ret);
	}

	friend bool operator< (const int num1, const CBigInt& num2)
	{
		CBigInt ret(num1);
		return !ret.greater(num2) && !num2.eq(ret);
	}










	friend bool operator> (const CBigInt n1, const CBigInt& num)
	{
		return n1.greater(num) && !n1.eq(num);
	}

	friend bool operator> (const CBigInt n1, const string& num)
	{
		CBigInt ret(num);
		return n1.greater(ret) && !n1.eq(ret);
	}

	friend bool operator> (const CBigInt n1, const int num)
	{
		CBigInt ret(num);
		return n1.greater(ret) && !n1.eq(ret);
	}

	friend bool operator> (const string& num1, const CBigInt& num2)
	{
		CBigInt ret(num1);
		return ret.greater(num2) && !num2.eq(ret);
	}

	friend bool operator> (const int num1, const CBigInt& num2)
	{
		CBigInt ret(num1);
		return ret.greater(num2) && !num2.eq(ret);
	}













	friend bool operator>= (const CBigInt n1, const CBigInt& num)
	{
		return n1.greater(num) || n1.eq(num);
	}

	friend bool operator>= (const CBigInt n1, const string& num)
	{
		CBigInt ret(num);
		return n1.greater(ret) || n1.eq(ret);
	}

	friend bool operator>= (const CBigInt n1, const int num)
	{
		CBigInt ret(num);
		return n1.greater(ret) || n1.eq(ret);
	}

	friend bool operator>= (const string& num1, const CBigInt& num2)
	{
		CBigInt ret(num1);
		return ret.greater(num2) || num2.eq(ret);
	}

	friend bool operator>= (const int num1, const CBigInt& num2)
	{
		CBigInt ret(num1);
		return ret.greater(num2) || num2.eq(ret);
	}













	friend bool operator<= (const CBigInt n1, const CBigInt& num)
	{
		return !n1.greater(num) || n1.eq(num);
	}

	friend bool operator<= (const CBigInt n1, const string& num)
	{
		CBigInt ret(num);
		return !n1.greater(ret) || n1.eq(ret);
	}

	friend bool operator<= (const CBigInt n1, const int num)
	{
		CBigInt ret(num);
		return !n1.greater(ret) || n1.eq(ret);
	}

	friend bool operator<= (const string& num1, const CBigInt& num2)
	{
		CBigInt ret(num1);
		return !ret.greater(num2) || ret.eq(num2);
	}

	friend bool operator<= (const int num1, const CBigInt& num2)
	{
		CBigInt ret(num1);
		return !ret.greater(num2) || ret.eq(num2);
	}










	friend ostringstream& operator<< (ostringstream& oss, const CBigInt& num)
	{
		int p = num.number.size() - 1;
		for (; p >= 0; p--) if (num.number[p] != 0) break;
		if (p == -1)
		{
			oss << '0';
			return oss;
		}
		if (num.neg) oss << "-";

		for (int i = p; i >= 0; i--)
		{
			oss << num.number[i];
		}
		return oss;
	}

	friend bool operator>> (istringstream& iss, CBigInt& num)
	{
		string str = iss.str();
		string numb = "";
		int i = 0;
		for (i = 0; i < (int)str.length(); i++)
		{
			if ((str[i] < '0' || str[i] > '9') && str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '-') return false;
			else if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n') break;
		}
		for (; i < (int)str.length(); i++)
		{
			if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-') numb += str[i];
			else break;
		}
		if (numb == "-") return false;
		num = numb;
		return true;
	}

private:
	bool neg = false;
	vector<int> number;
};

#ifndef __PROGTEST__
static bool equal(const CBigInt& x, const char* val)
{
	ostringstream oss;
	oss << x;
	return oss.str() == val;
}

int main(void)
{
  CBigInt a, b;
    istringstream is;

    is.clear();
    is.str("-123");
    assert(is >> a);
    assert(equal(a, "-123"));
    is.clear();
    is.str(" \t -123");
    assert(is >> a);
    assert(equal(a, "-123"));
    a = 69;
    is.clear();
    is.str("- 123");
    assert(!(is >> a));
    assert(equal(a, "69"));
    is.clear();
    is.str("-000123");
    assert(is >> a);
    assert(equal(a, "-123"));
    a = CBigInt("-00123");
    assert(equal(a, "-123"));
    a = CBigInt("0000000123");
    assert(equal(a, "123"));
    a = CBigInt("-0000000123");
    assert(equal(a, "-123"));
    is.clear();
    is.str("-0000000000123");
    assert(is >> a);
    assert(equal(a, "-123"));

    a = "-316761194058188125330";
    b = "-63352238811637625066";
    assert(a * b == b * a);
}
#endif /* __PROGTEST__ */
