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
#include <set>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <memory>
#include <functional>
#include <stdexcept>
#endif /* __PROGTEST */
using namespace std;

#ifndef __PROGTEST__
class CTimeStamp
{
public:

    CTimeStamp(int year, int  month, int day, int hour, int minute, int sec)
    {
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = hour;
        this->minute = minute;
        this->sec = sec;
    }


    int Compare(const CTimeStamp& x) const
    {
        if (year < x.getYear()) return -1;
        else if (year > x.getYear()) return 1;
        else if (month < x.getMonth()) return -2;
        else if (month > x.getMonth()) return 2;
        else if (day < x.getDay()) return -3;
        else if (day > x.getDay()) return 3;
        else if (hour < x.getHour()) return -4;
        else if (hour > x.getHour()) return 4;
        else if (minute < x.getMinute()) return -5;
        else if (minute > x.getMinute()) return 5;
        else if (sec < x.getSec()) return -6;
        else if (sec > x.getSec()) return 6;
        else return 0;
    }
    friend ostream& operator << (ostream& os, const CTimeStamp& x)
    {
        return os << x.year << '-' << setw(2) << setfill('0') << x.month << '-' << setw(2) << setfill('0') << x.day << ' ' << setw(2) << setfill('0') <<  x.hour << ':' << setw(2) << setfill('0') << x.minute << ':' << setw(2) << setfill('0') << x.sec;
    }

    int getYear()   const { return year; }
    int getMonth()  const { return month; }
    int getDay()    const { return day; }
    int getHour()   const { return hour; }
    int getMinute() const { return minute; }
    int getSec()    const { return sec; }
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int sec;
};


//=================================================================================================
class CMailBody
{
public:
    CMailBody(int size, const char* data)
    {
        this->m_Size = size;
        this->m_Data = new char[strlen(data) + 1];
        strcpy(this->m_Data, data);
    }

    CMailBody(const CMailBody& body)
    {
        this->m_Size = body.m_Size;
        this->m_Data = new char[strlen(body.m_Data) + 1];
        strcpy(this->m_Data, body.m_Data);
    }

    CMailBody& operator= (const CMailBody& copy)
    {
        if (this->m_Data) delete[] this->m_Data;
        this->m_Size = copy.m_Size;
        this->m_Data = new char[strlen(copy.m_Data) + 1];
        strcpy(this->m_Data, copy.m_Data);
        return *this;
    }

    ~CMailBody()
    {
        //		if(this->m_Data) delete[] this->m_Data;
    }

    friend ostream& operator <<                           (ostream& os,
                                                           const CMailBody& x)
    {
        return os << "mail body: " << x.m_Size << " B";
    }

    //int getSize() const { return m_Size; }
private:
    int            m_Size;
    char* m_Data;
};
//=================================================================================================
class CAttach
{
public:
    CAttach(int               x)
    {
        this->m_X = x;
        this->m_RefCnt = 1;
    }
    void           AddRef(void) const
    {
        m_RefCnt++;
    }
    void           Release(void) const
    {
        if (!--m_RefCnt)
            delete this;
    }
    //int getm_X() const { return m_X; }
private:
    int            m_X;
    mutable int    m_RefCnt;
    CAttach(const CAttach& x)
    {
        this->m_X = x.m_X;
        this->m_RefCnt = x.m_RefCnt;
    }
    CAttach& operator =                              (const CAttach& x)
    {
        this->m_X = x.m_X;
        this->m_RefCnt = x.m_RefCnt;
        return *this;
    }
    ~CAttach(void) = default;
    friend ostream& operator <<                           (ostream& os,
                                                           const CAttach& x)
    {
        return os << "attachment: " << x.m_X << " B";
    }
};
//=================================================================================================
#endif /* __PROGTEST__, DO NOT remove */


class CMail
{
public:

    CMail(const CTimeStamp& timeStamp, const string& from, const CMailBody& body, const CAttach* attach) :time(timeStamp), from(from), body(body), attach(attach)
    {
        if(attach)attach->AddRef();
    }

    ~CMail()
    {}

    CMail& operator= (const CMail& mail)
    {
        this->time = mail.TimeStamp();
        this->from = mail.From();
        this->body = mail.Body();
        this->attach = mail.Attachment();
        return *this;
    }
    const string& From(void) const			{ return from; }
    const CMailBody& Body(void) const		{ return body; }
    const CTimeStamp& TimeStamp(void) const { return time; }
    const CAttach* Attachment(void) const	{ return attach; }

    friend ostream& operator << (ostream& os, const CMail& x)
    {
        os << x.time << ' ' << x.from << ' ' << x.body;
        if (x.attach) os << " + " << *(x.attach);
        //os << endl;
        return os;
    }
private:
    CTimeStamp time;
    string from;
    CMailBody body;
    const CAttach* attach;
};
//=================================================================================================
struct CFolder
{
    string name;
    list <const CMail*> mails;
};
//=================================================================================================
class CMailBox
{
public:
    CMailBox(void)
    {
        CFolder folder;
        folder.name = "inbox";
        folders.push_back(folder);
    }

    bool           Delivery(const CMail& mail)
    {
        CFolder folder;
        folder.name = "inbox";
        auto inbox = lower_bound(folders.begin(), folders.end(), folder, [](const CFolder a, const CFolder b)
        {
            return a.name < b.name;
        });
        CMail* n_mail = new CMail ( CTimeStamp ( 0, 0, 0, 0, 0, 0 ), "temp", CMailBody ( 0, "temp" ), nullptr ) ;
        *n_mail = mail;
        auto i = lower_bound((*inbox).mails.begin(), (*inbox).mails.end(), n_mail, [](const CMail* a, const CMail* b)
        {
            if (a->TimeStamp().Compare(b->TimeStamp()) < 0) return 1;
            else return 0;
        });
        (*inbox).mails.insert(i, n_mail);
        auto it = lower_bound(allmails.begin(), allmails.end(), n_mail, [](const CMail* a, const CMail* b)
        {
            if (a->TimeStamp().Compare(b->TimeStamp()) < 0) return 1;
            else return 0;
        });
        allmails.insert(it, n_mail);
        return true;
    }

    bool           NewFolder(const string& folderName)
    {
        CFolder folder;
        folder.name = folderName;
        if (binary_search(folders.begin(), folders.end(), folder, [](const CFolder a, const CFolder b)
        {
            return a.name < b.name;
        })) return false;
        auto i = lower_bound(folders.begin(), folders.end(), folder, [](const CFolder a, const CFolder b)
        {
            return a.name < b.name;
        });
        folders.insert(i, folder);
        return true;
    }

    bool MoveMail(const string& fromFolder, const string& toFolder)
    {
        CFolder folder;

        folder.name = fromFolder;
        if (!binary_search(folders.begin(), folders.end(), folder, [](const CFolder a, const CFolder b)
        {
            return a.name < b.name;
        })) return false;
        auto from = lower_bound(folders.begin(), folders.end(), folder, [](const CFolder a, const CFolder b)
        {
            return a.name < b.name;
        });

        folder.name = toFolder;
        if (!binary_search(folders.begin(), folders.end(), folder, [](const CFolder a, const CFolder b)
        {
            return a.name < b.name;
        })) return false;
        auto to = lower_bound(folders.begin(), folders.end(), folder, [](const CFolder a, const CFolder b)
        {
            return a.name < b.name;
        });

        for (auto i = (*from).mails.begin(); i != (*from).mails.end(); i++)
        {
            auto mail = lower_bound((*to).mails.begin(), (*to).mails.end(), (*i), [](const CMail* a, const CMail* b)
            {
                if (a->TimeStamp().Compare(b->TimeStamp()) < 0) return 1;
                else return 0;
            });
            (*to).mails.insert(mail, (*i));
        }
        (*from).mails.clear();
        return true;
    }

    list<CMail>    ListMail(const string& folderName,
                            const CTimeStamp& from,
                            const CTimeStamp& to) const
    {
        list<CMail> mails;
        CFolder folder;
        folder.name = folderName;

        auto _folder = lower_bound(folders.begin(), folders.end(), folder, [](const CFolder a, const CFolder b)
        {
            return a.name < b.name;
        });

        CMail mailFrom(from, "temp", CMailBody(1, "temp"), nullptr);
        auto fromTime = lower_bound((*_folder).mails.begin(), (*_folder).mails.end(), &mailFrom, [](const CMail* a, const CMail* b)
        {
            if (a->TimeStamp().Compare(b->TimeStamp()) < 0) return 1;
            else return 0;
        });

        for (auto i = fromTime; i != (*_folder).mails.end(); i++)
        {
            if ((*i)->TimeStamp().Compare(to) <= 0) mails.push_back(*(*i));
            else break;
        }
        return mails;
    }
    set<string>    ListAddr(const CTimeStamp& from,
                            const CTimeStamp& to) const
    {
        set<string> addresses;
        CMail mailFrom(from, "temp", CMailBody(1, "temp"), nullptr);
        auto fromTime = lower_bound(allmails.begin(), allmails.end(), &mailFrom, [](const CMail* a, const CMail* b)
        {
            if (a->TimeStamp().Compare(b->TimeStamp()) < 0) return 1;
            else return 0;
        });

        for (auto i = fromTime; i != allmails.end(); i++)
        {
            if ((*i)->TimeStamp().Compare(to) <= 0) addresses.insert((*i)->From());
            else break;
        }
        return addresses;
    }
private:
    list <const CMail*>  allmails;
    list <CFolder> folders;
};
//=================================================================================================
#ifndef __PROGTEST__
static string showMail(const list<CMail>& l)
{
    ostringstream oss;
    for (const auto& x : l)
        oss << x << endl;
    return oss.str();
}
static string showUsers(const set<string>& s)
{
    ostringstream oss;
    for (const auto& x : s)
        oss << x << endl;
    return oss.str();
}
int main(void)
{
    list<CMail> mailList;
    set<string> users;
    CAttach   * att;

    CMailBox m0;
    assert ( m0 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 15, 24, 13 ), "user1@fit.cvut.cz", CMailBody ( 14, "mail content 1" ), nullptr ) ) );
    assert ( m0 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 15, 26, 23 ), "user2@fit.cvut.cz", CMailBody ( 22, "some different content" ), nullptr ) ) );
    att = new CAttach ( 200 );
    assert ( m0 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 11, 23, 43 ), "boss1@fit.cvut.cz", CMailBody ( 14, "urgent message" ), att ) ) );
    assert ( m0 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 18, 52, 27 ), "user1@fit.cvut.cz", CMailBody ( 14, "mail content 2" ), att ) ) );
    att -> Release ();
    att = new CAttach ( 97 );
    assert ( m0 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 16, 12, 48 ), "boss1@fit.cvut.cz", CMailBody ( 24, "even more urgent message" ), att ) ) );
    att -> Release ();
    assert ( showMail ( m0 . ListMail ( "inbox",
                                        CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                                        CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) ) == "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B + attachment: 200 B\n"
                                                                                       "2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
                                                                                       "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B\n"
                                                                                       "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B + attachment: 97 B\n"
                                                                                       "2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 200 B\n" );
    assert ( showMail ( m0 . ListMail ( "inbox",
                                        CTimeStamp ( 2014, 3, 31, 15, 26, 23 ),
                                        CTimeStamp ( 2014, 3, 31, 16, 12, 48 ) ) ) == "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B\n"
                                                                                      "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B + attachment: 97 B\n" );
    assert ( showUsers ( m0 . ListAddr ( CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                                         CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) ) == "boss1@fit.cvut.cz\n"
                                                                                        "user1@fit.cvut.cz\n"
                                                                                        "user2@fit.cvut.cz\n" );
    assert ( showUsers ( m0 . ListAddr ( CTimeStamp ( 2014, 3, 31, 15, 26, 23 ),
                                         CTimeStamp ( 2014, 3, 31, 16, 12, 48 ) ) ) == "boss1@fit.cvut.cz\n"
                                                                                       "user2@fit.cvut.cz\n" );

    CMailBox m1;
    assert ( m1 . NewFolder ( "work" ) );
    assert ( m1 . NewFolder ( "spam" ) );
    assert ( !m1 . NewFolder ( "spam" ) );
    assert ( m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 15, 24, 13 ), "user1@fit.cvut.cz", CMailBody ( 14, "mail content 1" ), nullptr ) ) );
    att = new CAttach ( 500 );
    assert ( m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 15, 26, 23 ), "user2@fit.cvut.cz", CMailBody ( 22, "some different content" ), att ) ) );
    att -> Release ();
    assert ( m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 11, 23, 43 ), "boss1@fit.cvut.cz", CMailBody ( 14, "urgent message" ), nullptr ) ) );
    att = new CAttach ( 468 );
    assert ( m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 18, 52, 27 ), "user1@fit.cvut.cz", CMailBody ( 14, "mail content 2" ), att ) ) );
    att -> Release ();
    assert ( m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 16, 12, 48 ), "boss1@fit.cvut.cz", CMailBody ( 24, "even more urgent message" ), nullptr ) ) );
    assert ( showMail ( m1 . ListMail ( "inbox",
                                        CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                                        CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) ) == "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B\n"
                                                                                       "2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
                                                                                       "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B\n"
                                                                                       "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B\n"
                                                                                       "2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B\n" );
    assert ( showMail ( m1 . ListMail ( "work",
                                        CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                                        CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) ) == "" );
    assert ( m1 . MoveMail ( "inbox", "work" ) );
    assert ( showMail ( m1 . ListMail ( "inbox",
                                        CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                                        CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) ) == "" );
    assert ( showMail ( m1 . ListMail ( "work",
                                        CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                                        CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) ) == "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B\n"
                                                                                       "2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
                                                                                       "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B\n"
                                                                                       "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B\n"
                                                                                       "2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B\n" );
    assert ( m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 19, 24, 13 ), "user2@fit.cvut.cz", CMailBody ( 14, "mail content 4" ), nullptr ) ) );
    att = new CAttach ( 234 );
    assert ( m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 13, 26, 23 ), "user3@fit.cvut.cz", CMailBody ( 9, "complains" ), att ) ) );
    att -> Release ();
    assert ( showMail ( m1 . ListMail ( "inbox",
                                        CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                                        CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) ) == "2014-03-31 13:26:23 user3@fit.cvut.cz mail body: 9 B + attachment: 234 B\n"
                                                                                       "2014-03-31 19:24:13 user2@fit.cvut.cz mail body: 14 B\n" );
    assert ( showMail ( m1 . ListMail ( "work",
                                        CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                                        CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) ) == "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B\n"
                                                                                       "2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
                                                                                       "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B\n"
                                                                                       "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B\n"
                                                                                       "2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B\n" );
    assert ( m1 . MoveMail ( "inbox", "work" ) );
    assert ( showMail ( m1 . ListMail ( "inbox",
                                        CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                                        CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) ) == "" );
    assert ( showMail ( m1 . ListMail ( "work",
                                        CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                                        CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) ) == "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B\n"
                                                                                       "2014-03-31 13:26:23 user3@fit.cvut.cz mail body: 9 B + attachment: 234 B\n"
                                                                                       "2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
                                                                                       "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B\n"
                                                                                       "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B\n"
                                                                                       "2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B\n"
                                                                                       "2014-03-31 19:24:13 user2@fit.cvut.cz mail body: 14 B\n" );

    return 0;
}
#endif /* __PROGTEST__ */
