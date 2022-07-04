#include "../include/date.hpp"
#include <iostream>

int main()
{
    auto date { project::Date::random_date() };

    std::cout << date << '\n';

    std::cout << "Please enter a date (dd/mm/yyy) => ";
    std::cin >> date;
    
    std::cout << "10 days later: " << (date+10) << '\n';
    std::cout << "20 days later: " << (20+date) << '\n';

    std::cout << "10 days before: " << (date-10) << '\n';
    std::cout << "20 days before: " << (date-20) << '\n';

    std::cout << "Setting initial date: " << date.set(1,1,1900) << '\n';

    std::cout << "Setting next day: " << ++date << '\n';
    std::cout << "Setting previous day: " << --date << '\n';

    std::cout << "Setting: " << date.set(4, 7, 2022) << '\n';
    int diff = date - project::Date{20,1,1997};
    std::cout << "Diff with (20/1/1997) : " << diff << " days, " << (diff/365.) << " years\n";
    return 0;
}