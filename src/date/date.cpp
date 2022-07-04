#include "../../include/date.hpp"
#include <iostream>
#include <cstring>
#include <random>
#include <string>

#define STATIC

namespace project{
    
    // FREE UTIL FUNCTIONS
    static void tokenize(const char * p, int(&date)[3]){
        if(std::strlen(p) > 10)
            exit(EXIT_FAILURE);

        char sdate[10];
        std::strncpy(sdate, p, std::strlen(p));

        int i{};

        // gg/aa/yil
        char * token = strtok(sdate, "/");
        while(token){
            date[i++] = std::stoi(token);
            token = strtok(NULL, "/");
        }

    }

    // CTORS
    Date::Date()
    {

    }

    Date::Date(int d, int m, int y)
        : m_day{d}, m_mon{m}, m_year{y}
    {

    }

    Date::Date(const char *p)
    {
        int date[3]{};
        tokenize(p, date);

        m_day = date[0];
        m_mon = date[1];
        m_year = date[2];
    }

    Date::Date(std::time_t timer)
    {
        struct std::tm* tm;
        tm = std::localtime(&timer);
        
        m_day = tm->tm_mday;
        m_mon = tm->tm_mon+1;
        m_year = tm->tm_year + 1900;
    }

    // GET FUNCTIONS
    int Date::get_month_day()const
    {
        return m_day;
    }
    
    int Date::get_month()const{
        return m_mon;
    }

    int Date::get_year()const{
        return m_year;
    }

    int Date::get_year_day()const{
        int year = static_cast<int>(isleap(m_year));

        for(int i=0; i<get_month()-1; ++i){
            year += mon_duration[i];
        }
        year += m_day;
        return year;
    }

    Date::Weekday Date::get_week_day()const
    {
        return static_cast<Date::Weekday>(day_of_week(m_day, m_mon, m_year));
    }

    // UTIL FUNCTIONS
    STATIC constexpr bool Date::isleap(int y)
    {
        if(y % 4 == 0  && (y % 400 == 0 || y%100 != 0)){
            return true;
        }
        return false;
    }

    STATIC int Date::day_of_week(int d, int m, int y)
    {
        static constexpr int t[] = { 0, 3, 2, 5, 0, 3,
                       5, 1, 4, 6, 2, 4 };
        y -= m < 3;
        return ( y + y / 4 - y / 100 +
             y / 400 + t[m - 1] + d) % 7;
    }

    // SET FUNCTIONS
    Date& Date::set_month_day(int day)
    {
        m_day = day;
        return *this;
    }

    Date& Date::set_month(int month)
    {
        m_mon = month;
        return *this;
    }

    Date& Date::set_year(int year)
    {
        m_year = year;
        return *this;
    }

    Date& Date::set(int day, int mon, int year)
    {
        return set_month_day(day).set_month(mon).set_year(year);
    }

    // RANDOM
    STATIC Date Date::random_date()
    {
        std::random_device dev;
        static std::mt19937 eng( dev() );
        static std::uniform_int_distribution dist_year{ random_min_year, random_max_year };
        static std::uniform_int_distribution dist_mon{ 1, 12 };

        int year{ dist_year(eng) };
        int mon{ dist_mon(eng) };

        std::uniform_int_distribution dist_day{ 25, mon_duration[mon-1] + static_cast<int>(isleap(year)) };
        int day{ dist_day(eng) };

        return { day, mon, year };
    }

    // OPERATOR FUNCTIONS
    Date& Date::operator++()
    {
        int month_duration = (get_month() != 2 && get_month_day() != 28) ? mon_duration[get_month()-1] : mon_duration[get_month()-1] + static_cast<int>(isleap(get_year()));
        
        if( !(m_mon == 12 && m_day == 31)) // If not last day of year
        {
            if(get_month_day() + 1 <= month_duration)
            {
                ++m_day;

            } else { // If last day of month
                ++m_mon;
                m_day = 1;
            }
        } 
        else { // If last day of year
            ++m_year;
            m_day = 1;
            m_mon = 1;
        }   
        return *this;     
    }
    Date Date::operator++(int)
    {
        Date temp{ *this };
        ++(*this);
        return temp;
    }

    Date& Date::operator--()
    {
        if( !(m_mon == 1 && m_day == 1)) // If not first day of year
        {
            if(get_month_day() - 1 >= 1)
            {
                --m_day;

            } else { // If first day of month
                --m_mon;
                m_day = (get_month() != 2) ? mon_duration[get_month()-1] : mon_duration[get_month()-1] + static_cast<int>(isleap(get_year()));
            }
        } else { // If first day of year
            --m_year;
            m_day = 31;
            m_mon = 12;
        }   
        return *this;     
    }

    Date Date::operator--(int)
    {
        Date temp{ *this };
        --(*this);
        return temp;
    }

    Date Date::operator-(int day)const
    {
        Date temp{ *this };
        while( day-- )
        {
            --temp;
        }
        return temp;
    }

    Date& Date::operator+=(int day)
    {
        while( day -- )
        {
            ++(*this);
        }
        return *this;
    }

    Date& Date::operator-=(int day)
    {
        while( day -- )
        {
            --(*this);
        }
        return *this;
    }
    
    std::ostream& operator<<(std::ostream& os, const Date& o)
    {
        return os << o.get_month_day() << '/' << o.get_month() << '/' << o.get_year();
    }

    std::istream& operator>>(std::istream& is, Date& o)
    {
        std::string strdate;
        std::getline(is, strdate);
        int date[3];
        tokenize(strdate.c_str(), date);
        o.m_day  = date[0];
        o.m_mon  = date[1];
        o.m_year = date[2];
        return is;
    }

    bool operator<(const Date& x, const Date& y)
    {
        if(x.m_year > y.m_year)
        {
            return false;
        }

        if(x.m_year < y.m_year){
            return true;
        }
        else if(x.m_mon < y.m_mon){
            return true;
        }
        else if(x.m_day < y.m_day){
            return true;
        }
        else {
            return false;
        }
    }

    bool operator==(const Date& x, const Date& y)
    {
        // x == y
        return !(x < y) && !(y < x);
    }

    bool operator>(const Date& x, const Date& y)
    {
        // x > y
        return y < x;
    }

    bool operator>=(const Date& x, const Date& y)
    {
        // x >= y
        return !(x < y);
    }

    bool operator<=(const Date& x, const Date& y)
    {
        // x <= y
        return !(y < x);
    }

    bool operator!=(const Date& x, const Date& y)
    {
        // x != y
        return !(x == y);
    }

    int operator-(const Date &d1, const Date& d2)
    {
        if( d1 == d2)
            return 0;
        
        int diff{};

        if(d1 < d2)
        {
            Date iter{ d2 }; 
            while( d1 != iter )
            {
                --diff;
                --iter;
            }
        } else {
            Date iter{ d1 }; 
            while( iter != d2)
            {
                ++diff;
                --iter;
            }
        }
        return diff;
    }

    Date operator+(const Date &date, int n)
    {
        Date iter{ date };
        while(n--)
        {
            ++iter;
        }
        return iter;
    }

    Date operator+(int n, const Date& date)
    {
        return date + n;
    }

    Date::Weekday& operator++(Date::Weekday &r)
    {
        return r = r == Date::Weekday::Saturday ? Date::Weekday::Sunday : static_cast<Date::Weekday>(static_cast<int>(r)+1);
    }

    Date::Weekday operator++(Date::Weekday &r, int)
    {
        auto temp{ r }; 
        ++r;
        return temp;
    }

    Date::Weekday& operator--(Date::Weekday &r)
    {
        return r = r == Date::Weekday::Sunday ? Date::Weekday::Saturday : static_cast<Date::Weekday>(static_cast<int>(r)-1);
    }

    Date::Weekday operator--(Date::Weekday &r, int)
    {
        auto temp{ r }; 
        --r;
        return temp;
    }
}