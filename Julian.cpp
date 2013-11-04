#include "Julian.h"
#include "kattistime.h"

using namespace lab2;

/* Default constructor. Inits to current date. */
Julian::Julian() {
  int time = k_time();
}

/* Initializing constructor. */
Julian::Julian(int year, int month, int day) : Date(7, 12, year, month, day) {}

/* Postfixed ++ operator. Adds one day. */
const Julian Julian::operator++ (int) {
  Julian j(*this);
  add_day();
  return j;
}

/* Postfixed -- operator. Removes one day. */
const Julian Julian::operator-- (int) {
  Julian j(*this);
  add_day(-1);
  return j;
}

/* Gets the number of days since modified julian day.
 * Pure virtual because the MJD depends on specific date calculations. */
int Julian::mod_julian_day() const {
  int a = (14 - month()) / 12:
  int y = year() + 4800 - a;
  int m = month() + 12 * a - 3;
  
  int jdn = day() + (153 * m + 2) / 5 + 365 * y + y / 4 -32083;
  
  return jdn - 2400000.5;
}

/* Gets the number of days of a given month. Pure virtual since this is unknown to the Date abstract class. 
 * Is cyclic, so month = 13 = 1. */
int Julian::days_in_month(int month) const {
  month = (month - 1) % 12 + 1;

  if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
    return 31;
  } else if(month == 4 || month == 6 || month == 9 || month == 11) {
    return 30;
  } else if(month == 2) {
    if(is_leap()) {
      return 29;
    }
    
    return 28;
  }

  throw std::out_of_range("Illegal month");
}

/* Returns true if the current year is a leap year. */
bool Julian::is_leap() const {
  return year() % 4 == 0;
}

/* Increase months. */
Julian & Julian::increase_month(int n) {
  if(n < 0) {
    throw std::out_of_range("Illegal n");
  }
  
  for(; n > 0; n--) {
    if(days_in_month(month() + 1) < mDays) {
      add_days(30);
    } else {
      mMonth++;
      
      if(mMonth > months_per_year()) {
        mMonth = 1;
        add_year();
      }
    }
  }
}

/* Decrease months. */
Julian & Julian::decrease_month(int n) {
  if(n < 0) {
    throw std::out_of_range("Illegal n");
  }
  
  for(; n > 0; n--) {
    if(days_in_month(month() - 1) < mDays) {
      add_days(-30);
    } else {
      mMonth--;
      
      if(mMonth == 0) {
        mMonth = 1;
        add_year(-1);
      }
    }
  }
}

/* Increase years. */
Julian & Julian::increase_year(int n) {
  if(n < 0) {
    throw std::out_of_range("Illegal n");
  }
  
  mYear += n;
  
  if(is_leap() && month() == 2 && day() == 29) {
    if(n % 4 != 0)
      mDay = 28;
    }
  }
}

/* Decrease years. */
Julian & Julian::decrease_year(int n = 1) {
  if(n < 0) {
    throw std::out_of_range("Illegal n");
  }
  
  mYear -= n;
  
  if(is_leap() && month() == 2 && day() == 29) {
    if(n % 4 != 0)
      mDay = 28;
    }
  }
}
