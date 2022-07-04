#include <gtest/gtest.h>
#include "../include/date.hpp"

#include <ctime>
#include <cstdlib>

class DateTest : public ::testing::Test
{

};

TEST_F(DateTest, Default_CTOR){
    project::Date date;

    EXPECT_EQ( date.get_month_day(), 1);
    EXPECT_EQ( date.get_month(), 1);
    EXPECT_EQ( date.get_year(), 1900);
}

TEST_F(DateTest, Args_CTOR)
{
    project::Date date{ 20, 1, 1997 };
    EXPECT_EQ( date.get_month_day(), 20);
    EXPECT_EQ( date.get_month(), 1);
    EXPECT_EQ( date.get_year(), 1997);
}

TEST_F(DateTest, CStr_CTOR)
{
    project::Date date{ "20/01/1997" };
    EXPECT_EQ( date.get_month_day(), 20);
    EXPECT_EQ( date.get_month(), 1);
    EXPECT_EQ( date.get_year(), 1997);
}

TEST_F(DateTest, Timer_CTOR)
{
    struct tm tm;
    char buf[16];
    memset(&tm, 0, sizeof(struct tm));
    strptime("20/01/1997", "%d/%m/%Y", &tm);
    time_t t = mktime(&tm);  // t is now your desired time_t

    project::Date date{ t };

    EXPECT_EQ( date.get_month_day(), 20);
    EXPECT_EQ( date.get_month(), 1);
    EXPECT_EQ( date.get_year(), 1997);
}

TEST_F(DateTest, Get_Week_Day)
{
    project::Date date{ 20, 01, 1997 };
    EXPECT_EQ(date.get_week_day(), project::Date::Weekday::Monday);
}

TEST_F(DateTest, Set_Functions)
{
    project::Date date{ 20, 01, 1997 };
    
    int month_day = 1;
    int month = 2;
    int year = 2021;

    date.set_month_day(month_day);
    date.set_month(month);
    date.set_year(year);
    
    EXPECT_EQ(date.get_month_day(), month_day);
    EXPECT_EQ(date.get_month(), month);
    EXPECT_EQ(date.get_year(), year);
}

TEST_F(DateTest, Set_Function)
{
    project::Date date;
    
    int month_day = 1;
    int month = 2;
    int year = 2021;

    date.set(month_day, month, year);
    
    EXPECT_EQ(date.get_month_day(), month_day);
    EXPECT_EQ(date.get_month(), month);
    EXPECT_EQ(date.get_year(), year);
}

TEST_F(DateTest, OperatorFunctions_Increment_1)
{
    project::Date date;
    
    int month_day = 1;
    int month = 1;
    int year = 2020;

    date.set(month_day, month, year);
    
    ++date;

    EXPECT_EQ(date.get_month_day(), ++month_day);
    EXPECT_EQ(date.get_month(), month);
    EXPECT_EQ(date.get_year(), year);
}

TEST_F(DateTest, OperatorFunctions_Increment_2)
{
    project::Date date;
    
    int month_day = 31;
    int month = 12;
    int year = 2019;

    date.set(month_day, month, year);
    
    ++date;

    EXPECT_EQ(date.get_month_day(), 1);
    EXPECT_EQ(date.get_month(), 1);
    EXPECT_EQ(date.get_year(), ++year);
}

TEST_F(DateTest, OperatorFunctions_Increment_LeapYear_1)
{
    project::Date date{"28/2/1904"};
    ++date;
    EXPECT_EQ(date.get_month_day(), 29);
    EXPECT_EQ(date.get_month(), 2);
    EXPECT_EQ(date.get_year(), 1904);
}

TEST_F(DateTest, OperatorFunctions_Increment_LeapYear_2)
{
    project::Date date{"29/2/1904"};
    ++date;
    EXPECT_EQ(date.get_month_day(), 1);
    EXPECT_EQ(date.get_month(), 3);
    EXPECT_EQ(date.get_year(), 1904);
}

TEST_F(DateTest, OperatorFunctions_Increment_NotLeapYear_1)
{
    project::Date date{"28/2/1905"};
    ++date;
    EXPECT_EQ(date.get_month_day(), 1);
    EXPECT_EQ(date.get_month(), 3);
    EXPECT_EQ(date.get_year(), 1905);
}

TEST_F(DateTest, OperatorFunctions_Increment_NotLeapYear_2)
{
    project::Date date{"1/3/1905"};
    ++date;
    EXPECT_EQ(date.get_month_day(), 2);
    EXPECT_EQ(date.get_month(), 3);
    EXPECT_EQ(date.get_year(), 1905);
}

TEST_F(DateTest, OperatorFunctions_Decrement_LeapYear_1)
{
    project::Date date{"1/3/1904"};
    --date;
    EXPECT_EQ(date.get_month_day(), 29);
    EXPECT_EQ(date.get_month(), 2);
    EXPECT_EQ(date.get_year(), 1904);
}

TEST_F(DateTest, OperatorFunctions_Decrement_LeapYear_2)
{
    project::Date date{"29/2/1904"};
    --date;
    EXPECT_EQ(date.get_month_day(), 28);
    EXPECT_EQ(date.get_month(), 2);
    EXPECT_EQ(date.get_year(), 1904);
}

TEST_F(DateTest, OperatorFunctions_Decrement_NotLeapYear_1)
{
    project::Date date{"1/3/1905"};
    --date;
    EXPECT_EQ(date.get_month_day(), 28);
    EXPECT_EQ(date.get_month(), 2);
    EXPECT_EQ(date.get_year(), 1905);
}

TEST_F(DateTest, OperatorFunctions_Decrement_NotLeapYear_2)
{
    project::Date date{"28/2/1905"};
    --date;
    EXPECT_EQ(date.get_month_day(), 27);
    EXPECT_EQ(date.get_month(), 2);
    EXPECT_EQ(date.get_year(), 1905);
}

TEST_F(DateTest, OperatorFunctions_Decrement_1)
{
    project::Date date;
    
    int month_day = 1;
    int month = 1;
    int year = 2020;

    date.set(month_day, month, year);
    
    --date;

    EXPECT_EQ(date.get_month_day(), 31);
    EXPECT_EQ(date.get_month(), 12);
    EXPECT_EQ(date.get_year(), --year);
}

TEST_F(DateTest, OperatorFunctions_Decrement_2)
{
    project::Date date;
    
    int month_day = 31;
    int month = 12;
    int year = 2019;

    date.set(month_day, month, year);
    
    --date;

    EXPECT_EQ(date.get_month_day(), --month_day);
    EXPECT_EQ(date.get_month(), month);
    EXPECT_EQ(date.get_year(), year);
}

TEST_F(DateTest, Equal_1)
{
    project::Date datex;
    project::Date datey;
    
    int month_day = 1;
    int month = 1;
    int year = 2020;

    datex.set(month_day, month, year);
    datey.set(month_day, month, year);
    
    EXPECT_TRUE( datex == datey );
}

TEST_F(DateTest, Equal_2)
{
    project::Date datex;
    project::Date datey;
    
    int month_day = 1;
    int month = 1;
    int year = 2020;

    datex.set(month_day, month, year);
    datey.set(month_day, month, year);
    
    --datex;
    ++datex;
    
    EXPECT_TRUE( datex == datey );
}

TEST_F(DateTest, Less_Than_1)
{
    project::Date datex;
    project::Date datey;
    
    int month_day = 1;
    int month = 1;
    int year = 2020;

    datex.set(month_day, month, year);
    datey.set(month_day, month, year);
    
    --datex;
    
    EXPECT_TRUE ( datex < datey );
    EXPECT_FALSE( datey < datex );
}

TEST_F(DateTest, Less_Than_2)
{
    project::Date datex;
    project::Date datey;
    
    datex.set(1, 1, 2020);
    datey.set(1, 1, 2021);
    
    EXPECT_TRUE ( datex < datey );
    EXPECT_FALSE( datey < datex );
}

TEST_F(DateTest, Less_Than_3)
{
    project::Date datex;
    project::Date datey;
    
    datex.set(1, 1, 2020);
    datey.set(1, 2, 2020);
    
    EXPECT_TRUE ( datex < datey );
    EXPECT_FALSE( datey < datex );
}

TEST_F(DateTest, Less_Than_4)
{
    project::Date datex;
    project::Date datey;
    
    datex.set(1, 1, 2020);
    datey.set(2, 1, 2020);
    
    EXPECT_TRUE ( datex < datey );
    EXPECT_FALSE( datey < datex );
}

TEST_F(DateTest, Greater_Than)
{
    project::Date datex;
    project::Date datey;
    
    int month_day = 1;
    int month = 1;
    int year = 2020;

    datex.set(month_day, month, year);
    datey.set(month_day, month, year);
    
    ++datex;
    
    EXPECT_TRUE ( datex > datey );
    EXPECT_FALSE( datey > datex );
}

TEST_F(DateTest, Less_Or_Equal)
{
    project::Date datex;
    project::Date datey;
    
    int month_day = 1;
    int month = 1;
    int year = 2020;

    datex.set(month_day, month, year);
    datey.set(month_day, month, year);

    EXPECT_TRUE( datex <= datey && "First" );
    EXPECT_TRUE( datey <= datex && "First" );
    
    --datex;

    EXPECT_TRUE ( datex <= datey && "Second" );
    EXPECT_FALSE( datey <= datex && "Second" );
}

TEST_F(DateTest, Greater_Or_Equal_1)
{
    project::Date datex;
    project::Date datey;
    
    int month_day = 1;
    int month = 1;
    int year = 2020;

    datex.set(month_day, month, year);
    datey.set(month_day, month, year);

    EXPECT_TRUE( datex >= datey );
    EXPECT_TRUE( datey >= datex );
    
    ++datex;

    EXPECT_TRUE ( datex >= datey);
    EXPECT_FALSE( datey >= datex);
}

TEST_F(DateTest, Greater_Or_Equal_Day)
{
    project::Date datex;
    project::Date datey;
    
    datex.set(2, 1, 2020);
    datey.set(1, 1, 2020);

    EXPECT_TRUE ( datex >= datey );
    EXPECT_FALSE( datey >= datex );
}
TEST_F(DateTest, Greater_Or_Equal_Mon)
{
    project::Date datex;
    project::Date datey;
    
    datex.set(1, 2, 2020);
    datey.set(1, 1, 2020);

    EXPECT_TRUE ( datex >= datey );
    EXPECT_FALSE( datey >= datex );
}
TEST_F(DateTest, Greater_Or_Equal_Year)
{
    project::Date datex;
    project::Date datey;
    
    datex.set(1, 1, 2021);
    datey.set(1, 1, 2020);

    EXPECT_TRUE ( datex >= datey );
    EXPECT_FALSE( datey >= datex );
}
TEST_F(DateTest, Greater_Or_Equal_DayMonYear)
{
    project::Date datex;
    project::Date datey;
    
    datex.set(2, 2, 2021);
    datey.set(1, 1, 2020);

    EXPECT_TRUE ( datex >= datey );
    EXPECT_FALSE( datey >= datex );
}

TEST_F(DateTest, Diff_1)
{
    project::Date datex;
    project::Date datey;
    
    datex.set(1, 1, 2020);
    datey.set(1, 1, 2020);

    EXPECT_EQ(datey - datex,  0);
    EXPECT_EQ(datex - datey,  0);
}

TEST_F(DateTest, Diff_2)
{
    project::Date datex;
    project::Date datey;
    
    datex.set( 1, 1, 2020);
    datey.set(11, 1, 2020);

    EXPECT_EQ(datey - datex,  10);
    EXPECT_EQ(datex - datey, -10);
}

TEST_F(DateTest, Diff_NotLeapYear)
{
    project::Date datex;
    project::Date datey;
    
    datex.set( 1, 1, 1905);
    datey.set( 1, 1, 1906);

    EXPECT_EQ(datey - datex,  365);
    EXPECT_EQ(datex - datey, -365);
}

TEST_F(DateTest, Diff_LeapYear)
{
    project::Date datex;
    project::Date datey;
    
    datex.set( 1, 1, 1904);
    datey.set( 1, 1, 1905);

    EXPECT_EQ(datey - datex,  366);
    EXPECT_EQ(datex - datey, -366);
}

TEST_F(DateTest, OperatorPlus_1)
{
    project::Date date(4,7,2022);
    project::Date target(9,7,2022);
    EXPECT_EQ( date + 5, target);
    EXPECT_EQ( 5 + date, target);
}

TEST_F(DateTest, OperatorPlus_LeapYear)
{
    project::Date date(27,2,1904);
    project::Date target(3,3,1904);

    EXPECT_EQ( date + 5, target);
    EXPECT_EQ( 5 + date, target);
}

TEST_F(DateTest, OperatorPlus_NotLeapYear)
{
    project::Date date(27,2,1905);
    project::Date target(4,3,1905);
    
    EXPECT_EQ( date + 5, target);
    EXPECT_EQ( 5 + date, target);
}

TEST_F(DateTest, WeekDayIncrement_1)
{
    using Weekday = project::Date::Weekday;
    auto day = Weekday::Sunday;
    
    ++ day;

    EXPECT_EQ(day, Weekday::Monday);
}

TEST_F(DateTest, WeekDayIncrement_2)
{
    using Weekday = project::Date::Weekday;
    auto day = Weekday::Saturday;
    
    ++ day;

    EXPECT_EQ(day, Weekday::Sunday);
}

TEST_F(DateTest, WeekDayDecrement_1)
{
    using Weekday = project::Date::Weekday;
    auto day = Weekday::Sunday;
    
    -- day;

    EXPECT_EQ(day, Weekday::Saturday);
}

TEST_F(DateTest, WeekDayDecrement_2)
{
    using Weekday = project::Date::Weekday;
    auto day = Weekday::Saturday;
    
    -- day;

    EXPECT_EQ(day, Weekday::Friday);
}