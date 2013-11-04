#ifndef GREGORIAN_H
#define GREGORIAN_H

#include "jesus.h"

namespace lab2 {
  class Gregorian : public Jesus {
  public:
    /* Default constructor. Inits to current date. */
    Gregorian();
    
    /* Initializing constructor. */
    Gregorian(int year, int month, int day);
    
    /* ======= Operators ======= */
    
    /* Postfixed ++ operator. Adds one day. */
    const Gregorian operator++ (int);

    /* Postfixed -- operator. Removes one day. */
    const Gregorian operator-- (int);
   
    /* ======= Misc ======= */
    
    /* Gets the number of days since modified julian day.
     * Pure virtual because the MJD depends on specific date calculations. */
    int mod_julian_day() const;
    
  protected:
    /* Returns true if the current year is a leap year. */
    virtual bool is_leap() const;
  };
}

#endif
