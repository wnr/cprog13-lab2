#ifndef JULIAN_H
#define JULIAN_H

#include "jesus.h"

namespace lab2 {
  class Julian : public Jesus {
  public:
    /* Default constructor. Inits to current date. */
    Julian();

    /* Initializing constructor. */
    Julian(int year, int month, int day);

    /* Copy constructor. */
    Julian(const Date & date);

    /* Copy constructor. */
    Julian(const Date * date);

    /* Postfixed ++ operator. Adds one day. */
    const Julian operator++ (int);

    /* Postfixed -- operator. Removes one day. */
    const Julian operator-- (int);

    /* Assignment operator. */
    Julian & operator= (const Date & date);

    /* ======= Misc ======= */

    /* Gets the number of days since modified julian day.
     * Pure virtual because the MJD depends on specific date calculations. */
    int mod_julian_day() const;

  protected:
    /* Returns true if the current year is a leap year. */
    bool is_leap() const;

    void set_to_mjd(int mjd);
  };
}

#endif
