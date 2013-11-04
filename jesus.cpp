#include "jesus.h"

using namespace lab2;

/* << operator. Function used to print object by ostream. */
//TODO fix as spec.
std::ostream & operator<< (std::ostream & os, const lab2::Jesus & date) {
  os << date.year() << "-" << date.month() << "-" << date.day();
  return os;
}

/* Initializer constructor. */
Jesus::Jesus(int year, int month, int day) : Date(7, 12, year, month, day) {}

/* Gets the week day name. */
std::string Jesus::week_day_name() const {
  if(week_day() == 1) {
    return std::string("monday");
  } else if(week_day() == 2) {
    return std::string("tuesday");
  } else if(week_day() == 3) {
    return std::string("wednesday");
  } else if(week_day() == 4) {
    return std::string("thursday");
  } else if(week_day() == 5) {
    return std::string("friday");
  } else if(week_day() == 6) {
    return std::string("saturday");
  } else if(week_day() == 7) {
    return std::string("sunday");
  }
  
  throw std::exception();
}

/* Gets the month name. */
std::string Jesus::month_name() const {
  if(month() == 1) {
    return std::string("january");
  } else if(month() == 2) {
    return std::string("february");
  } else if(month() == 3) {
    return std::string("march");
  } else if(month() == 4) {
    return std::string("april");
  } else if(month() == 5) {
    return std::string("may");
  } else if(month() == 6) {
    return std::string("june");
  } else if(month() == 7) {
    return std::string("july");
  } else if(month() == 8) {
    return std::string("august");
  } else if(month() == 9) {
    return std::string("september");
  } else if(month() == 10) {
    return std::string("october");
  } else if(month() == 11) {
    return std::string("november");
  } else if(month() == 12) {
    return std::string("december");
  }
  
  throw std::exception();
}

/* Gets the number of days of a given month. Pure virtual since this is unknown to the Date abstract class. 
 * Is cyclic, so month = 13 = 1. */
int Jesus::days_in_month(int month) const {
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

/* Increase months. */
Jesus & Jesus::increase_month(int n) {
  if(n < 0) {
    throw std::out_of_range("Illegal n");
  }
  
  for(; n > 0; n--) {
    if(days_in_month(month() + 1) < mDay) {
      add_day(30);
    } else {
      mMonth++;
      
      if(mMonth > months_per_year()) {
        mMonth = 1;
        add_year();
      }
    }
  }
  
  return *this;
}

/* Decrease months. */
Jesus & Jesus::decrease_month(int n) {
  if(n < 0) {
    throw std::out_of_range("Illegal n");
  }
  
  for(; n > 0; n--) {
    if(days_in_month(month() - 1) < mDay) {
      add_day(-30);
    } else {
      mMonth--;
      
      if(mMonth == 0) {
        mMonth = 1;
        add_year(-1);
      }
    }
  }
  
  return *this;
}

/* Increase years. */
Jesus & Jesus::increase_year(int n) {
  if(n < 0) {
    throw std::out_of_range("Illegal n");
  }
  
  mYear += n;
  
  if(month() == 2 && day() == 29) {
  
    if(is_leap()) {
      mDay = 28;
    }
  }
  
  return *this;
}

/* Decrease years. */
Jesus & Jesus::decrease_year(int n) {
  if(n < 0) {
    throw std::out_of_range("Illegal n");
  }
  
  mYear -= n;
  
  if(month() == 2 && day() == 29) {
    if(!is_leap()) {
      mDay = 28;
    }
  }
  
  return *this;
}
