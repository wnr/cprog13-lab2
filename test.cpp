#include <assert.h>
#include <iostream>

#include "Date.h"

using namespace lab2;

class TestDate : public Date {
public:
  TestDate() : Date() {}
  TestDate(int numDaysPerWeek, int numMonthsPerYear, int year, int month, int day) : Date(numDaysPerWeek, numMonthsPerYear, year, month, day) {}
  TestDate(const Date & date) : Date(date) {}
  
  int mod_julian_day() const { return 0; }
  
protected:
  int days_in_month(int month) const {
    if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
      return 31;
    } else if(month == 4 || month == 6 || month == 9 || month == 11) {
      return 30;
    } else if(month == 2) {
      return 28;
    }

    throw EXCEPTION_ILLEGAL_ARGUMENT;
  }
};

int main() {
  // Default Constructor & simple getters
  {
    TestDate date;
    assert(date.year() == 0);
    assert(date.month() == 0);
    assert(date.day() == 0);
    assert(date.days_per_week() == 0 && date.days_per_year() == 0);
  }
  // Initializer and Copy Constructor
  {
    TestDate date(7, 12, 2, 1, 4);
    assert(date.year() == 2);
    assert(date.month() == 1);
    assert(date.day() == 4);
    assert(date.days_per_week() == 7 && date.months_per_year() == 12);

    TestDate otherDate(date);
    assert(date.year() == 2);
    assert(date.month() == 1);
    assert(date.day() == 4);
    assert(otherDate.days_per_week() == 7 && otherDate.months_per_year() == 12);
  }
  // week_day
  {
    TestDate date(7, 12, 1991, 11, 4);
    assert(date.week_day() == 4);

    date = TestDate(7, 12, 1991, 11, 7);
    assert(date.week_day() == 7);

    date = TestDate(7, 12, 1991, 11, 7);
    assert(date.week_day() == 7);

    date = TestDate(7, 12, 1991, 11, 8);
    assert(date.week_day() == 1);

    date = TestDate(7, 12, 1991, 11, 23);
    assert(date.week_day() == 2);
  }
  // days_this_month
  {
    TestDate date(7, 12, 1991, 11, 4);
    assert(date.days_this_month() == 30);

    date = TestDate(7, 12, 1991, 4, 4);
    assert(date.days_this_month() == 30git );
  }
  // days_per_year
  {
    TestDate date(7, 12, 1991, 11, 23);
    assert(date.days_per_year() == 365);
  }
  // add_year
  {
    TestDate date(7, 12, 1991, 11, 23);
    date.add_year();
    assert(date.year() == 1992);
    assert(date.month() == 11);
    assert(date.day() == 23);

    date.add_year(3);
    assert(date.year() == 1995);
    assert(date.month() == 11);
    assert(date.day() == 23);

    date.add_year(-1);
    assert(date.year() == 1994);
    assert(date.month() == 11);
    assert(date.day() == 23);
  }
  // add_month
  {
    TestDate date(7, 12, 1991, 11, 23);
    date.add_month();
    assert(date.year() == 1991);
    assert(date.month() == 12);
    assert(date.day() == 23);

    date.add_month(2);
    assert(date.year() == 1992);
    assert(date.month() == 2);
    assert(date.day() == 23);

    date.add_month(-1);
    assert(date.year() == 1992);
    assert(date.month() == 1);
    assert(date.day() == 23);

    date.add_month(-3);
    assert(date.year() == 1991);
    assert(date.month() == 10);
    assert(date.day() == 23);

    date = TestDate(7, 12, 1991, 1, 31);
    date.add_month();
    assert(date.year() == 1991);
    assert(date.month() == 2);
    assert(date.day() == 28);

    date = TestDate(7, 12, 1991, 3, 30);
    date.add_month(-1);
    assert(date.year() == 1991);
    assert(date.month() == 2);
    assert(date.day() == 28);
  }
  // add_day
  {
    TestDate date(7, 12, 1991, 11, 23);
    date.add_day();
    assert(date.year() == 1991);
    assert(date.month() == 11);
    assert(date.day() == 24);

    date.add_day(10);
    assert(date.year() == 1991);
    assert(date.month() == 12);
    assert(date.day() == 4);

    date.add_day(-4);
    assert(date.year() == 1991);
    assert(date.month() == 11);
    assert(date.day() == 30);

    date.add_day(100);
    assert(date.year() == 1992);
    assert(date.month() == 3);
    assert(date.day() == 10);
  }
  // ++ -- += -= operators
  {
    TestDate date(7, 12, 1991, 11, 23);

    ++date;
    assert(date.year() == 1991);
    assert(date.month() == 11);
    assert(date.day() == 24);

    --date;
    assert(date.year() == 1991);
    assert(date.month() == 11);
    assert(date.day() == 23);

    date += 2;
    assert(date.year() == 1991);
    assert(date.month() == 11);
    assert(date.day() == 25);

    date += -1;
    assert(date.year() == 1991);
    assert(date.month() == 11);
    assert(date.day() == 24);

    date -= -1;
    assert(date.year() == 1991);
    assert(date.month() == 11);
    assert(date.day() == 25);

    date -= 1;
    assert(date.year() == 1991);
    assert(date.month() == 11);
    assert(date.day() == 24);
  }
  // copmaring operators
  {
    TestDate date(7, 12, 1991, 11, 23);
    TestDate date2(7, 12, 1991, 11, 23);

    assert(!(date < date2));
    assert(date == date2);
    assert(!(date > date2));
    assert(!(date != date2));
    assert(date <= date2);
    assert(date >= date2);

    date2.add_day();

    assert(date < date2);
    assert(!(date == date2));
    assert(!(date > date2));
    assert(!(date >= date2));
    assert(date <= date2);
    assert(date != date2);

    date2.add_day(-2);
    date2.add_month();

    assert(date < date2);
    assert(!(date == date2));
    assert(date <= date2);
    assert(date != date2);
    assert(!(date > date2));
    assert(!(date >= date2));

    date2.add_month(-2);
    date2.add_year();

    assert(date < date2);
    assert(!(date == date2));
    assert(date <= date2);
    assert(date != date2);
    assert(!(date > date2));
    assert(!(date >= date2));
  }
  // diff operator
  {
    TestDate date(7, 12, 1991, 11, 23);
    TestDate date2(7, 12, 1991, 11, 23);

    assert(date-date2 == 0);

    ++date2;
    assert(date-date2 == -1);

    date += 2;
    assert(date-date2 == 1);

    date = date2;

    date.add_year();
    assert(date-date2 == 365);

    date.add_year(-2);
    assert(date-date2 == -365);

    date = date2;

    date.add_month(1);
    assert(date-date2 == 31);
  }

  std::cout << "\033[32mAll tests passed.\033[0m" << std::endl;

  return 0;
}
