#include "calendar.h"
#include <exception>

using namespace lab2;

Calendar::Calendar() {}

Calendar::Calendar(const Calendar & c) {
  events = c.events;
  currentDate = c.currentDate;
}

bool Calendar::set_date(int year, int month, int day) {
  try {
    currentDate = T(year, month, day);
  } catch(std::out_of_range oor) {
    return false;
  }

  return true;
}

bool Calendar::add_event(const std::string & event, int day, int month, int year) {
  try {
    if(exist(event, day, month, year)) {
      return false;
    }

    events.append(Event(event, T(year, month, day)));
  } catch(std::out_of_range oor) {
    return false;
  }

  return true;
}

bool Calendar::add_event(const std::string & event) {
  T d;

  return add_event(event, d.day(), d.month(), d.year());
}

bool Calendar::remove_event(const std::string & event, int day, int month, int year) {

  try {
    std::iterator<Event> pos = find(event, day, month, year);

    if(pos != events.end()) {
      events.erase(pos);
    } else {
      return false;
    }
  } catch(std::out_of_range oor) {
    return false;
  }

  return true;
}

std::iterator<Event> Calendar::find(const std::string & event, int day, int month, int year) const {
  Event e(event, T(year, month, day));

  return std::find(events.begin(), events.end(), e);
}

bool Calendar::exist(const std::string & event, int day, int month, int year) const {
  return find(event, day, month, year) != events.end();
}