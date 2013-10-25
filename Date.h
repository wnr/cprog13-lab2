#ifndef DATE_H
#define DATE_H

namespace lab2 {
  
  /* Abstract interface class for representing dates. */
  class Date {
    //The number of days in a week.
    int numDaysPerWeek;
    
    //The number of months in a year.
    int numMonthsPerYear;
    
    //The current year.
    int year;
    
    //The current month. 1 = first month of the year.
    int month;
    
    //The current day of the month.
    int day;
    
  public:   
    /* Default constructor. */
    Date();
    
    /* Initializer constructor. */
    Date(int daysPerWeek, int monthsPerYear, int year, int month, int day);
    
    /* Copy constructor. */
    Date(const & Date date);
    
    /* ======= Getters ======= */
    
    /* Gets the current year. */
    int year() const;
    
    /* Gets the current month. */
    int month() const;
    
    /* Gets the current day. */
    int day() const;
    
    /* Gets the current week day. */
    int week_day() const;
    
    /* Gets the number of days in a week. */
    int days_per_week() const;
    
    /* Gets the number of months in a year. */
    int months_per_year() const;
    
    /* Gets the number of days of the current month. Pure virtual since this is unknown to the Date abstract class. */
    virtual int days_this_month() const = NULL;
    
    /* ======= Operators ======= */
    
    /* Prefixed ++ operator. */
    const Date & operator++ ();
    
    /* Prefixed -- operator. */
    const Date & operator-- ();
    
    /* += operator. */
    const Date & operator+= (const Date & date);
    
    /* -= operator. */
    const Date & operator-= (const Date & date);
    
    /* == operator. */
    bool operator== (const Date & date) const;
    
    /* != operator. */
    bool operator!= (const Date & date) const;
    
    /* < operator. */
    bool operator< (const Date & date) const;
    
    /* > operator. */
    bool operator> (const Date & date) const;
    
    /* <= operator. */
    bool operator<= (const Date & date) const;
    
    /* >= operator. */
    bool operator>= (const date & date) const;
    
    /* - operator. Returns the number of days diffing the two dates. */
    int operator- (const Date & date) const;
    
    /* ======= Adder / Setters ======= */
    
    /* Adds a year. */
    Date & add_year(int n = 1);
    
    /* Adds a month. Will increment year if needed. */
    Date & add_month(int n = 1);
    
    /* ======= Misc ======= */
    
    /* Gets the number of days since modified julian day. */
    int mod_julian_day() const;
  };
  
  /* << operator. Function used to print object by ostream. */
  ostream & operator<< (ostream & os, const Date & date);
}

#endif
