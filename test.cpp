#include <assert.h>
#include <iostream>
#include <time.h>

#include "date.h"

#include "calendar.h"
#include "kattistime.h"

using namespace lab2;

class TestDate : public Date {
public:
  TestDate() : Date() {}
  TestDate(int numDaysPerWeek, int numMonthsPerYear, int year, int month, int day) : Date(numDaysPerWeek, numMonthsPerYear, year, month, day) {}
  TestDate(const Date & date) : Date(date) {}

  int mod_julian_day() const { return 0; }
  std::string month_name() const { return std::string(); }
  std::string week_day_name() const { return std::string(); }

protected:
  int days_in_month(int month) const {
    if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
      return 31;
    } else if(month == 4 || month == 6 || month == 9 || month == 11) {
      return 30;
    } else if(month == 2) {
      return 28;
    }

    throw std::out_of_range("Illegal month");
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
  // days_this_month
  {
    TestDate date(7, 12, 1991, 11, 4);
    assert(date.days_this_month() == 30);

    date = TestDate(7, 12, 1991, 4, 4);
    assert(date.days_this_month() == 30);
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

  set_k_time(time(NULL));

  {
    std::cout << "----------------------------------------" << std::endl;
    Calendar<Gregorian> cal;
    cal.set_date(2000, 12, 2);
    cal.add_event("Basketträning", 4, 12, 2000);
    cal.add_event("Basketträning", 11, 12, 2000);
    cal.add_event("Nyårsfrukost", 1, 1, 2001);
    cal.add_event("Första advent", 1); // år = 2000, månad = 12
    cal.add_event("Vårdagjämning", 20, 3); // år = 2000
    cal.add_event("Julafton", 24, 12);
    cal.add_event("Kalle Anka hälsar god jul", 24); // också på julafton
    cal.add_event("Julafton", 24); // En likadan händelse samma datum ska
    // ignoreras och inte sättas in i kalendern
    cal.add_event("Min första cykel", 20, 12, 2000);
    cal.remove_event("Basketträning", 4);
    std::cout << cal; // OBS! Vårdagjämning och första advent är
    // före nuvarande datum och skrivs inte ut
    std::cout << "----------------------------------------" << std::endl;
    cal.remove_event("Vårdagjämning", 20, 3, 2000);
    cal.remove_event("Kalle Anka hälsar god jul", 24, 12, 2000);
    cal.set_date(2000, 11, 2);
    if (! cal.remove_event("Julafton", 24)) {
    std::cout << " cal.remove_event(\"Julafton\", 24) tar inte"<< std::endl
    << " bort något eftersom aktuell månad är november" << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
    std::cout << cal;
  }
  {
    Calendar<Gregorian> cal;
    assert(cal.set_date(2100, 2, 29) == false);

    cal.add_event("VeyplGA", 1, 1, 2014);
    cal.add_event("cjJMbGs", 1, 1, 2014);

    std::cout << std::endl << cal << std::endl;
  }

  std::cout << std::endl << std::endl << "\033[32mAll tests passed.\033[0m" << std::endl;

  return 0;
}
