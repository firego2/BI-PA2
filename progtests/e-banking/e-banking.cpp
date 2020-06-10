#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
#endif /* __PROGTEST__ */

class CTransaction;
//class CList;
class CPerson;


class CTransaction
{
public:
    CPerson* from = NULL;
    CPerson* to = NULL;

    int amount;
    char *signature;
    CTransaction* next;
    CTransaction* prev;
};


class CPerson
{
public:
    ~CPerson()
    {
        if(!freed) delete [] accountID;
    }

    int Balance()
    {
        return balance;
    }

    char *accountID;
    int balance = 0;

    int first_value;

    CPerson* next = NULL;
    CPerson* prev = NULL;
    CTransaction* transactions = NULL;
    bool freed = false;
    friend ostringstream& operator<< (ostringstream& oss, const CPerson& account)
    {
        oss << account.accountID << ':' << endl << "   " << account.first_value << endl; // \n?????
        CTransaction* act = account.transactions;
        while (true)
        {
            if (!act || !act->next) break;
            act = act->next;
        }
        while (true)
        {
            if (!act) break;
            if (!strcmp(act->from->accountID, account.accountID))
            {
                oss << " - " << act->amount << ", to: " << act->to->accountID << ", sign: " << act->signature << endl;
            }
            else oss << " + " << act->amount << ", from: " << act->from->accountID << ", sign: " << act->signature << endl;
            act = act->prev;
        }
        oss << " = " << account.balance << endl;
        return oss;
    }
};

class CBank
{
public:
    CPerson* find_acc(const char* acc)
    {
        CPerson* act = start;
        while (true)
        {
            if (!act) break;
            if (!strcmp(act->accountID, acc)) return act;
            else act = act->next;
        }
        return NULL;
    };
    // default constructor
    CBank()
    {
        start = NULL;
        //transactions = NULL;
    }

    // copy constructor
    CBank(const CBank& copy)
    {
        CPerson* act = copy.start;
        CPerson* cpy = NULL;
        //CPerson* temp = NULL;

        while (true)
        {
            if (!act || !act->next) break;
            act = act->next;

        }
        while (true) // coping all accounts
        {
            if (!act) break;
            cpy = new CPerson;


            cpy->accountID = new char [strlen(act->accountID) + 1];
            strcpy(cpy->accountID, act->accountID);

            cpy->balance = act->balance;
            cpy->first_value = act->first_value;
            cpy->transactions = NULL;
            if (start) start->prev = cpy;
            cpy->next = start;
            start = cpy;
            act = act->prev;
        }
        CTransaction* actt;
        CTransaction* cpyt;
        cpy = start;
        act = copy.start;
        while (true) // coping transactions to all accounts
        {
            if (!cpy || !act) break;

            actt = act->transactions;

            while(true)
            {
                if (!actt ||!actt->next) break;
                actt = actt->next;

            }
            while (true) // going by all transactions
            {
                if (!actt) break;
                if (!strcmp(actt->from->accountID, cpy->accountID) || !strcmp(actt->to->accountID, cpy->accountID))
                {
                    cpyt = new CTransaction;
                    cpyt->from = find_acc(actt->from->accountID);
                    cpyt->to = find_acc(actt->to->accountID);
                    cpyt->amount = actt->amount;


                    cpyt->signature = new char [strlen(actt->signature) + 1];
                    strcpy(cpyt->signature, actt->signature);


                    cpyt->next = cpy->transactions;
                    if(cpy->transactions) cpy->transactions->prev = cpyt;
                    cpy->transactions = cpyt;
                    cpyt = NULL;
                }
                actt = actt->prev;
            }
            act = act->next;
            cpy = cpy->next;
        }

    }
    // destructor
    ~CBank()
    {
        CPerson *tempp = NULL;
        CTransaction* tempt = NULL;
        while (true)
        {
            if (!start) break;
            while (true)
            {
                if (!start->transactions) break;
                tempt = start->transactions->next;
                delete [] start->transactions->signature;
                delete start->transactions;
                start->transactions = tempt;
            }
            tempp = start->next;
            delete [] start->accountID;
            start->freed = true;
            delete start;
            start = tempp;
        }
    }
    // operator =
    CBank& operator= (const CBank& copy)
    {
		CPerson *tempp = NULL;
        CTransaction* tempt = NULL;
        while (true)
        {
            if (!start) break;
            while (true)
            {
                if (!start->transactions) break;
                tempt = start->transactions->next;
                delete [] start->transactions->signature;
                delete start->transactions;
                start->transactions = tempt;
            }
            tempp = start->next;
            delete [] start->accountID;
            start->freed = true;
            delete start;
            start = tempp;
        }

		start = NULL;

        CPerson* act = copy.start;
        CPerson* cpy = NULL;

        while (true)
        {
            if (!act || !act->next) break;
            act = act->next;

        }
        while (true) // coping all accounts
        {
            if (!act) break;
            cpy = new CPerson;


            cpy->accountID = new char [strlen(act->accountID) + 1];
            strcpy(cpy->accountID, act->accountID);


            cpy->balance = act->balance;
            cpy->first_value = act->first_value;
            cpy->transactions = NULL;
            if (start) start->prev = cpy;
            cpy->next = start;
            start = cpy;
            act = act->prev;
        }
        CTransaction* actt;
        CTransaction* cpyt;
        cpy = start;
        act = copy.start;
        while (true) // coping transactions to all accounts
        {
            if (!cpy || !act) break;

            actt = act->transactions;

            while (true)
            {
                if (!actt || !actt->next) break;
                actt = actt->next;

            }
            while (true) // going by all transactions
            {
                if (!actt) break;
                if (!strcmp(actt->from->accountID, cpy->accountID) || !strcmp(actt->to->accountID, cpy->accountID))
                {
                    cpyt = new CTransaction;
                    cpyt->from = find_acc(actt->from->accountID);
                    cpyt->to = find_acc(actt->to->accountID);
                    cpyt->amount = actt->amount;


                    cpyt->signature = new char [strlen(actt->signature) + 1];
                    strcpy(cpyt->signature, actt->signature);


                    cpyt->next = cpy->transactions;
                    if (cpy->transactions) cpy->transactions->prev = cpyt;
                    cpy->transactions = cpyt;
                    cpyt = NULL;
                }
                actt = actt->prev;
            }
            act = act->next;
            cpy = cpy->next;
        }
        return *this;
    }


    bool   NewAccount(const char* accID,
                      int          initialBalance)
    {
        if (find_acc(accID)) return false;
        CPerson* account = new CPerson;


        account->accountID = new char [strlen(accID) + 1];
        strcpy(account->accountID, accID);


        account->balance = initialBalance;
        account->first_value = initialBalance;
        account->next = NULL;
        account->prev = NULL;
        account->next = start;
        if(start) start->prev = account;
        start = account;
        return true;
    }
    bool   Transaction(const char* debAccID,
                       const char* credAccID,
                       unsigned int amount,
                       const char* signature)
    {
        CPerson* from = find_acc(debAccID);
        CPerson* to = find_acc(credAccID);
        if (!from || !to || from == to) return false;

        CTransaction* transactionf = new CTransaction;
        transactionf->amount = amount;


        transactionf->signature = new char [strlen(signature) + 1];
        strcpy(transactionf->signature, signature);


        transactionf->from = from;
        transactionf->to = to;
        transactionf->next = from->transactions;
        transactionf->prev = NULL;
        if(from->transactions) from->transactions->prev = transactionf;
        from->transactions = transactionf;
        CTransaction* transactiont = new CTransaction;
        transactiont->amount = amount;


        transactiont->signature = new char [strlen(signature) + 1];
        strcpy(transactiont->signature, signature);


        transactiont->from = from;
        transactiont->to = to;
        transactiont->next = to->transactions;
        transactiont->prev = NULL;
        if (to->transactions) to->transactions->prev = transactiont;
        to->transactions = transactiont;

        from->balance -= amount;
        to->balance += amount;
        return true;
    }
    bool   TrimAccount(const char* accID)
    {
        CPerson* acc = find_acc(accID);
        if (!acc) return false;
        acc->first_value = acc->balance;
        CTransaction* act = acc->transactions;
        CTransaction* temp = NULL;
        while (true)
        {
            if (!act) break;
            temp = act->next;
            delete [] act->signature;
            delete act;
            act = temp;
        }
        acc->transactions = NULL;
        return true;
    }

    CPerson Account(const char *accID)
    {
        CPerson* ref = find_acc(accID);
        if (!ref) throw invalid_argument("Account doesnt exist.");
        CPerson ret;
        ret.accountID = new char [strlen(ref->accountID) + 1];
        strcpy(ret.accountID, ref->accountID);
        ret.balance = ref->balance;
        ret.first_value = ref->first_value;
        ret.transactions = ref->transactions;
        return ret;
    }

private:
    CPerson* start = NULL;
    //CTransaction* transactions = NULL;
};

#ifndef __PROGTEST__
int main(void)
{
    ostringstream os;
    char accCpy[100], debCpy[100], credCpy[100], signCpy[100];
    CBank x0;
    assert(x0.NewAccount("123456", 1000));
    assert(x0.NewAccount("987654", -500));
    assert(x0.Transaction("123456", "987654", 300, "XAbG5uKz6E="));
    assert(x0.Transaction("123456", "987654", 2890, "AbG5uKz6E="));
    assert(x0.NewAccount("111111", 5000));
    assert(x0.Transaction("111111", "987654", 290, "Okh6e+8rAiuT5="));
    assert(x0.Account("123456").Balance() == -2190);
    assert(x0.Account("987654").Balance() == 2980);
    assert(x0.Account("111111").Balance() == 4710);
    os.str("");
    os << x0.Account("123456");
    assert(!strcmp(os.str().c_str(), "123456:\n   1000\n - 300, to: 987654, sign: XAbG5uKz6E=\n - 2890, to: 987654, sign: AbG5uKz6E=\n = -2190\n"));
    os.str("");
    os << x0.Account("987654");
    assert(!strcmp(os.str().c_str(), "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 290, from: 111111, sign: Okh6e+8rAiuT5=\n = 2980\n"));
    os.str("");
    os << x0.Account("111111");
    assert(!strcmp(os.str().c_str(), "111111:\n   5000\n - 290, to: 987654, sign: Okh6e+8rAiuT5=\n = 4710\n"));
    assert(x0.TrimAccount("987654"));
    assert(x0.Transaction("111111", "987654", 123, "asdf78wrnASDT3W"));
    os.str("");
    os << x0.Account("987654");
    assert(!strcmp(os.str().c_str(), "987654:\n   2980\n + 123, from: 111111, sign: asdf78wrnASDT3W\n = 3103\n"));

    CBank x2;
    strncpy(accCpy, "123456", sizeof(accCpy));
    assert(x2.NewAccount(accCpy, 1000));
    strncpy(accCpy, "987654", sizeof(accCpy));
    assert(x2.NewAccount(accCpy, -500));
    strncpy(debCpy, "123456", sizeof(debCpy));
    strncpy(credCpy, "987654", sizeof(credCpy));
    strncpy(signCpy, "XAbG5uKz6E=", sizeof(signCpy));
    assert(x2.Transaction(debCpy, credCpy, 300, signCpy));
    strncpy(debCpy, "123456", sizeof(debCpy));
    strncpy(credCpy, "987654", sizeof(credCpy));
    strncpy(signCpy, "AbG5uKz6E=", sizeof(signCpy));
    assert(x2.Transaction(debCpy, credCpy, 2890, signCpy));
    strncpy(accCpy, "111111", sizeof(accCpy));
    assert(x2.NewAccount(accCpy, 5000));
    strncpy(debCpy, "111111", sizeof(debCpy));
    strncpy(credCpy, "987654", sizeof(credCpy));
    strncpy(signCpy, "Okh6e+8rAiuT5=", sizeof(signCpy));
    assert(x2.Transaction(debCpy, credCpy, 2890, signCpy));
    assert(x2.Account("123456").Balance() == -2190);
    assert(x2.Account("987654").Balance() == 5580);
    assert(x2.Account("111111").Balance() == 2110);
    os.str("");
    os << x2.Account("123456");
    assert(!strcmp(os.str().c_str(), "123456:\n   1000\n - 300, to: 987654, sign: XAbG5uKz6E=\n - 2890, to: 987654, sign: AbG5uKz6E=\n = -2190\n"));
    os.str("");
    os << x2.Account("987654");
    assert(!strcmp(os.str().c_str(), "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 2890, from: 111111, sign: Okh6e+8rAiuT5=\n = 5580\n"));
    os.str("");
    os << x2.Account("111111");
    assert(!strcmp(os.str().c_str(), "111111:\n   5000\n - 2890, to: 987654, sign: Okh6e+8rAiuT5=\n = 2110\n"));
    assert(x2.TrimAccount("987654"));
    strncpy(debCpy, "111111", sizeof(debCpy));
    strncpy(credCpy, "987654", sizeof(credCpy));
    strncpy(signCpy, "asdf78wrnASDT3W", sizeof(signCpy));
    assert(x2.Transaction(debCpy, credCpy, 123, signCpy));
    os.str("");
    os << x2.Account("987654");
    assert(!strcmp(os.str().c_str(), "987654:\n   5580\n + 123, from: 111111, sign: asdf78wrnASDT3W\n = 5703\n"));

    CBank x4;
    assert(x4.NewAccount("123456", 1000));
    assert(x4.NewAccount("987654", -500));
    assert(!x4.NewAccount("123456", 3000));
    assert(!x4.Transaction("123456", "666", 100, "123nr6dfqkwbv5"));
    assert(!x4.Transaction("666", "123456", 100, "34dGD74JsdfKGH"));
    assert(!x4.Transaction("123456", "123456", 100, "Juaw7Jasdkjb5"));
    try
    {
        x4.Account("666").Balance();
        assert("Missing exception !!" == NULL);
    }
    catch (...)
    {
    }
    try
    {
        os << x4.Account("666").Balance();
        assert("Missing exception !!" == NULL);
    }
    catch (...)
    {
    }
    assert(!x4.TrimAccount("666"));

    CBank x6;
    assert(x6.NewAccount("123456", 1000));
    assert(x6.NewAccount("987654", -500));
    assert(x6.Transaction("123456", "987654", 300, "XAbG5uKz6E="));
    assert(x6.Transaction("123456", "987654", 2890, "AbG5uKz6E="));
    assert(x6.NewAccount("111111", 5000));
    assert(x6.Transaction("111111", "987654", 2890, "Okh6e+8rAiuT5="));
    CBank x7(x6);
    assert(x6.Transaction("111111", "987654", 123, "asdf78wrnASDT3W"));
    assert(x7.Transaction("111111", "987654", 789, "SGDFTYE3sdfsd3W"));
    assert(x6.NewAccount("99999999", 7000));
    assert(x6.Transaction("111111", "99999999", 3789, "aher5asdVsAD"));
    assert(x6.TrimAccount("111111"));
    assert(x6.Transaction("123456", "111111", 221, "Q23wr234ER=="));
    os.str("");
    cout << x6.find_acc("111111").balance;
    os << x6.Account("111111");
    assert(!strcmp(os.str().c_str(), "111111:\n   -1802\n + 221, from: 123456, sign: Q23wr234ER==\n = -1581\n"));
    os.str("");
    os << x6.Account("99999999");
    assert(!strcmp(os.str().c_str(), "99999999:\n   7000\n + 3789, from: 111111, sign: aher5asdVsAD\n = 10789\n"));
    os.str("");
    os << x6.Account("987654");
    assert(!strcmp(os.str().c_str(), "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 2890, from: 111111, sign: Okh6e+8rAiuT5=\n + 123, from: 111111, sign: asdf78wrnASDT3W\n = 5703\n"));
    os.str("");
    os << x7.Account("111111");
    assert(!strcmp(os.str().c_str(), "111111:\n   5000\n - 2890, to: 987654, sign: Okh6e+8rAiuT5=\n - 789, to: 987654, sign: SGDFTYE3sdfsd3W\n = 1321\n"));
    try
    {
        os << x7.Account("99999999").Balance();
        assert("Missing exception !!" == NULL);
    }
    catch (...)
    {
    }
    os.str("");
    os << x7.Account("987654");
    assert(!strcmp(os.str().c_str(), "987654:\n   -500\n + 300, from: 123456, sign: XAbG5uKz6E=\n + 2890, from: 123456, sign: AbG5uKz6E=\n + 2890, from: 111111, sign: Okh6e+8rAiuT5=\n + 789, from: 111111, sign: SGDFTYE3sdfsd3W\n = 6369\n"));

    CBank x8;
    CBank x9;
    assert(x8.NewAccount("123456", 1000));
    assert(x8.NewAccount("987654", -500));
    assert(x8.Transaction("123456", "987654", 300, "XAbG5uKz6E="));
    assert(x8.Transaction("123456", "987654", 2890, "AbG5uKz6E="));
    assert(x8.NewAccount("111111", 5000));
    assert(x8.Transaction("111111", "987654", 2890, "Okh6e+8rAiuT5="));
    x9 = x8;
    assert(x8.Transaction("111111", "987654", 123, "asdf78wrnASDT3W"));
    assert(x9.Transaction("111111", "987654", 789, "SGDFTYE3sdfsd3W"));
    assert(x8.NewAccount("99999999", 7000));
    assert(x8.Transaction("111111", "99999999", 3789, "aher5asdVsAD"));
    assert(x8.TrimAccount("111111"));
    os.str("");
    os << x8.Account("111111");
    assert(!strcmp(os.str().c_str(), "111111:\n   -1802\n = -1802\n"));
    os.str("");
    os << x9.Account("111111");
    assert(!strcmp(os.str().c_str(), "111111:\n   5000\n - 2890, to: 987654, sign: Okh6e+8rAiuT5=\n - 789, to: 987654, sign: SGDFTYE3sdfsd3W\n = 1321\n"));
    CBank x;
    assert(x.NewAccount("9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999", 7000));
    assert(!x.Transaction("111111", "987654", 123, "asdf78wrnASDT3W"));
    assert(!x.TrimAccount("111111"));


    return 0;
}
#endif /* __PROGTEST__ */
