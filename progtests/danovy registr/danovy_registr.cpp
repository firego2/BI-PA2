#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <stdexcept>
#include <algorithm>
using namespace std;
#endif /* __PROGTEST__ */


class CCitizen
{
public:
	string name = "";
	string account = "";
	string address = "";
	int sumInc;
	int sumExp;
};

class cmp_names
{
public:
	bool operator()(CCitizen* const& c1, CCitizen* const& c2) 
	{
		if (c1->name == c2->name)
			return (c1->address < c2->address);
		else return (c1->name < c2->name);
	}
};

class cmp_accounts
{
public:
	bool operator()(CCitizen* const& c1, CCitizen* const& c2) 
	{
		return (c1->account < c2->account);
	}
};


class CIterator
{

public:
	CIterator(const vector <CCitizen*>& p)
	{
		temp = p;
		it = temp.begin();
	}

	bool                     AtEnd(void) const { return (it == temp.end()); }
	void                     Next(void) { it++; }
	string                   Name(void) const { return (*it)->name; }
	string                   Addr(void) const { return (*it)->address; }
	string                   Account(void) const { return (*it)->account; }
private:
	vector <CCitizen*> temp;
	vector <CCitizen*>::iterator it;
};

class CTaxRegister
{
public:
	bool                     Birth(const string& name, const string& addr, const string& account);
	bool                     Death(const string& name, const string& addr);
	bool                     Income(const string& account, int amount);
	bool                     Income(const string& name, const string& addr, int amount);
	bool                     Expense(const string& account, int amount);
	bool                     Expense(const string& name, const string& addr, int amount);
	bool                     Audit(const string& name, const string& addr, string& account, int& sumIncome, int& sumExpense) const;
	CIterator                ListByName(void) const;
private:
	vector <CCitizen> registry;
	vector <CCitizen*> citizensABC;
	vector <CCitizen*> accountsABC;
	int capacity = 0;
};


bool CTaxRegister::Birth(const string& name,
	const string& addr,
	const string& account)
{
	CCitizen temp;
	temp.name = name;
	temp.address = addr;
	temp.account = account;
	temp.sumInc = 0;
	temp.sumExp = 0;


	if (binary_search(citizensABC.begin(), citizensABC.end(), &temp, cmp_names())) return false;
	if (binary_search(accountsABC.begin(), accountsABC.end(), &temp, cmp_accounts())) return false;

	auto position1 = lower_bound(citizensABC.begin(), citizensABC.end(), &temp, cmp_names());
	auto position2 = lower_bound(accountsABC.begin(), accountsABC.end(), &temp, cmp_accounts());

	if (capacity == 0)
	{
		registry.reserve(registry.capacity() + 300000);
		capacity = 300000;
	}
	capacity--;

	registry.push_back(temp);
	citizensABC.insert(position1, &registry.back());
	accountsABC.insert(position2, &registry.back());
	return true;
}

bool CTaxRegister::Death(const string& name, const string& addr)
{
	CCitizen temp;
	temp.name = name;
	temp.address = addr;

	if (!binary_search(citizensABC.begin(), citizensABC.end(), &temp, cmp_names())) return false;

	auto position1 = lower_bound(citizensABC.begin(), citizensABC.end(), &temp, cmp_names());
	temp.account = (*position1)->account;
	auto position2 = lower_bound(accountsABC.begin(), accountsABC.end(), &temp, cmp_accounts());
	
	citizensABC.erase(position1);
	accountsABC.erase(position2);
	return true;
}

bool CTaxRegister::Income(const string& account, int amount)
{
	CCitizen temp;
	temp.account = account;

	if (!binary_search(accountsABC.begin(), accountsABC.end(), &temp, cmp_accounts())) return false;
	auto position = lower_bound(accountsABC.begin(), accountsABC.end(), &temp, cmp_accounts());

	(*position)->sumInc += amount;
	return true;
}

bool CTaxRegister::Income(const string& name, const string& addr, int amount)
{
	CCitizen temp;
	temp.name = name;
	temp.address = addr;

	if (!binary_search(citizensABC.begin(), citizensABC.end(), &temp, cmp_names())) return false;
	auto position = lower_bound(citizensABC.begin(), citizensABC.end(), &temp, cmp_names());
	
	(*position)->sumInc += amount;
	return true;
}

bool CTaxRegister::Expense(const string& account, int amount)
{
	CCitizen temp;
	temp.account = account;

	if (!binary_search(accountsABC.begin(), accountsABC.end(), &temp, cmp_accounts())) return false;
	auto position = lower_bound(accountsABC.begin(), accountsABC.end(), &temp, cmp_accounts());

	(*position)->sumExp += amount;
	return true;
}

bool CTaxRegister::Expense(const string& name, const string& addr, int amount)
{
	CCitizen temp;
	temp.name = name;
	temp.address = addr;

	if (!binary_search(citizensABC.begin(), citizensABC.end(), &temp, cmp_names())) return false;
	auto position = lower_bound(citizensABC.begin(), citizensABC.end(), &temp, cmp_names());

	(*position)->sumExp += amount;
	return true;
}

bool CTaxRegister::Audit(const string& name, const string& addr, string& account, int& sumIncome, int& sumExpense) const
{
	CCitizen temp;
	temp.name = name;
	temp.address = addr;

	if (!binary_search(citizensABC.begin(), citizensABC.end(), &temp, cmp_names())) return false;
	auto position = lower_bound(citizensABC.begin(), citizensABC.end(), &temp, cmp_names());

	account = (*position)->account;
	sumIncome = (*position)->sumInc;
	sumExpense = (*position)->sumExp;
	return true;
}

CIterator CTaxRegister::ListByName(void) const
{
	CIterator ret(citizensABC);
	return ret;
}


#ifndef __PROGTEST__
int main(void)
{
	
	return 0;
}
#endif /* __PROGTEST__ */
