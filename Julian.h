#ifndef JULIAN_H
#define JULIAN_H

#include "Date.h"

namespace lab2 {
  class Julian : Date {
  public:
    /* Default constructor. Inits to current date. */
    Julian();
    
    /* Initializing constructor. */
    Julian(int year, int month, int day);
    
    /* ======= Operators ======= */
    
    /* Postfixed ++ operator. Adds one day. */
    const Julian operator++ (int);

    /* Postfixed -- operator. Removes one day. */
    const Julian operator-- (int);
    
  protected:
    /* Returns true if the current year is a leap year. */
    virtual bool is_leap() const;
    
    /* Increase months. */
    Julian & increase_month(int n = 1);

    /* Decrease months. */
    Julian & decrease_month(int n = 1);
    
    /* Increase years. */
    Julian & increase_year(int n = 1);

    /* Decrease years. */
    Julian & decrease_year(int n = 1);
  };
}

/* << operator. Function used to print object by ostream. Prints on the format YYYY-MM-DD */
std::ostream & operator<< (std::ostream & os, const lab2::Julian & date);

#endif
