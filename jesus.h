#ifndef JESUS_H
#define JESUS_H

#include "date.h"

namespace lab2 {
  long mod(long a, long b);

  class Jesus : public Date {
  public:
    /* Initializer constructor. */
    Jesus(int year, int month, int day);

    /* ======= Misc ======= */

    /* Gets the number of days since modified julian day.
     * Pure virtual because the MJD depends on specific date calculations. */
    int mod_julian_day() const = 0;

    /* Gets the week day name. */
    std::string week_day_name() const;

    /* Gets the month name. */
    std::string month_name() const;

  protected:
    /* Returns true if the current year is a leap year. */
    virtual bool is_leap() const = 0;

    /* Gets the number of days of a given month. Pure virtual since this is unknown to the Date abstract class.
     * Is cyclic, so month = 13 = 1. */
    int days_in_month(int month) const;

    /* Increase months. */
    Jesus & increase_month(int n = 1);

    /* Decrease months. */
    Jesus & decrease_month(int n = 1);

    /* Increase years. */
    Jesus & increase_year(int n = 1);

    /* Decrease years. */
    Jesus & decrease_year(int n = 1);
  };
}

#endif
