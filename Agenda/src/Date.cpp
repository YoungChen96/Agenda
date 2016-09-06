#include "Date.hpp"
  #include <sstream>
  const int long_month[7] = {
    1, 3, 5, 7, 8, 10, 12
  };
  const int short_month[5] = {
    2, 4, 6, 9, 11
  };
  /**
  * @brief default constructor
  */
  Date::Date() {
    m_year =m_month =m_day =m_hour =m_minute =0;
  }

  /**
  * @brief constructor with arguments
  */
  Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute) {
    m_year =t_year;
    m_month =t_month;
    m_day =t_day;
    m_hour =t_hour;
    m_minute =t_minute;
  }

  /**
  * @brief constructor with a string
  */
  int str_to_int(std::string & str) {
    std::stringstream ss(str);
    int value;
    ss >> value;
    return value;
  }
  Date::Date(std::string dateString) {
    std::string str ="";
    int len =dateString.length();
    if (dateString.length() !=16) {
      m_year =0;m_month =0;m_day =0;m_hour =0;m_minute =0;
      return ;
    }
    if (dateString[4] !='-' || dateString[7] !='-' || dateString[10] !='/' ||
      dateString[13] !=':') {
      m_year =0;m_month =0;m_day =0;m_hour =0;m_minute =0;
      return ;
    }
    for (int i =0; i < len; ++i) {
      if ((dateString[i] >'9' || dateString[i] <'0') && (4 != i && 7 != i &&
        10 != i && 13 !=i) ) {
        m_year =0;m_month =0;m_day =0;m_hour =0;m_minute =0;
        return ;
      }
    }
    int count =0;
    for (int i =0; i <dateString.length(); ++i) {
      if (dateString[i] >= '0' && dateString[i] <='9') {
        str +=dateString[i];
      } else {
        switch(count) {
          case 0:
          m_year =str_to_int(str);
          break;
          case 1:
          m_month =str_to_int(str);
          break;
          case 2:
          m_day =str_to_int(str);
          break;
          case 3:
          m_hour =str_to_int(str);
          break;
          case 4:
          m_minute =str_to_int(str);
        }
        ++count;
        str ="";
      }
    }
    m_minute =str_to_int(str);
    /*std::string sub1 =dateString.substr(0, 4);
    m_year =str_to_int(sub1);
    std::string sub2 =dateString.substr(5, 2);
    m_month =str_to_int(sub2);
    std::string sub3 =dateString.substr(8, 2);
    m_day =str_to_int(sub3);
    std::string sub4 =dateString.substr(11, 2);
    m_hour =str_to_int(sub4);
    std::string sub5 =dateString.substr(14);
    m_minute =str_to_int(sub5);
    /*if (!isValid(*this)) {
      m_year =m_month =m_day =m_hour =m_minute =0;
    }*/
  }
  int Date::getYear(void) const {
    return m_year;
  }

  /**
  * @brief set the year of a date
  * @param a integer indicate the new year of a date
  */
  void Date::setYear(const int t_year) {
    if (t_year >0)
    m_year =t_year;
  }

  /**
  * @brief return the month of a Date
  * @return   a integer indicate the month of a date
  */
  int Date::getMonth(void) const {
    return m_month;
  }

  /**
  * @brief set the month of a date
  * @param a integer indicate the new month of a date
  */
  void Date::setMonth(const int t_month) {
    if (t_month >0 && t_month <=12)
    m_month =t_month;
  }

  /**
  * @brief return the day of a Date
  * @return   a integer indicate the day of a date
  */
  int Date::getDay(void) const {
    return m_day;
  }

  /**
  * @brief set the day of a date
  * @param a integer indicate the new day of a date
  */
  void Date::setDay(const int t_day) {
    int temp =m_day;
    m_day =t_day;
    if (!isValid(*this)) m_day =temp;
  }

  /**
  * @brief return the hour of a Date
  * @return   a integer indicate the hour of a date
  */
  int Date::getHour(void) const {
    return m_hour;
  }

  /**
  * @brief set the hour of a date
  * @param a integer indicate the new hour of a date
  */
  void Date::setHour(const int t_hour) {
    if (t_hour >=0 && t_hour <24)
    m_hour =t_hour;
  }

  /**
  * @brief return the minute of a Date
  * @return   a integer indicate the minute of a date
  */
  int Date::getMinute(void) const {
    return m_minute;
  }

  /**
  * @brief set the minute of a date
  * @param a integer indicate the new minute of a date
  */
  void Date::setMinute(const int t_minute) {
    if (t_minute >=0 && t_minute <60)
    m_minute =t_minute;
  }

  /**
  *   @brief check whether the date is valid or not
  *   @return the bool indicate valid or not
  */
  bool isRun(const int _year) {
    if (_year % 400 ==0) return true;
    if (_year %4 ==0 && 0 !=_year %100) return true;
    return false;
  }

  bool Date::isValid(const Date t_date) {
    if (t_date.getYear() <1000 || t_date.getYear() >9999) return false;
    if (t_date.getMonth() <=0 || t_date.getMonth()>12) return false;
    if (t_date.getDay() <=0 || t_date.getDay() >31) return false;
    if (t_date.getHour() <0 || t_date.getHour() >=24) return false;
    if (t_date.getMinute() < 0 || t_date.getMinute() >=60) return false;
    if (31 == t_date.getDay()) {
      for (int i =0; i <5; i++) {
        if (t_date.getMonth() ==short_month[i]) return false;
      }
    }
    if (2 ==t_date.getMonth()) {
      if (t_date.getDay() ==29) {
        if (!isRun(t_date.getYear())) return false;
      } else if (t_date.getDay() > 29) return false;
    }
    
    return true;
  }

  /**
  * @brief convert a string to date, if the format is not correct return
  * 0000-00-00/00:00
  * @return a date
  */
  Date Date::stringToDate(const std::string t_dateString) {
    Date temp =Date(t_dateString);
    return temp;
  }

  /**
  * @brief convert a date to string, if the format is not correct return
  * 0000-00-00/00:00
  */
  std::string int_to_str(const int& value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
  }
  std::string Date::dateToString(Date t_date) {
    std::string result ="";
    if (!isValid(t_date)) {
      result ="0000-00-00/00:00";
      return result;
    }
    result +=int_to_str(t_date.getYear()) + "-";
    if (t_date.getMonth() <10) {
        result += "0";
    }
    result += int_to_str(t_date.getMonth()) + "-";
    if (t_date.getDay() <10) result +="0";
    result +=int_to_str(t_date.getDay()) + "/";
    if (t_date.getHour() <10) result +="0";
    result +=int_to_str(t_date.getHour()) + ":";
    if (t_date.getMinute() <10) result +="0";
    result +=int_to_str(t_date.getMinute());
    return result;
  }                                                           // wait to see

  /**
  *  @brief overload the assign operator
  */
  Date &Date::operator=(const Date &t_date) {
    m_year =0;m_month =0;m_day =0;m_hour =0;m_minute =0;
    if (isValid(t_date)) {
        m_year =t_date.m_year;
        m_month =t_date.m_month;
        m_day =t_date.m_day;
        m_hour =t_date.m_hour;
        m_minute =t_date.m_minute;
    }
    return *this;
  }

  /**
  * @brief check whether the CurrentDate is equal to the t_date
  */
  bool Date::operator==(const Date &t_date) const {
    if (t_date.m_year !=m_year) return false;
    if (t_date.m_month !=m_month) return false;
    if (t_date.m_day !=m_day) return false;
    if (t_date.m_hour !=m_hour) return false;
    if (t_date.m_minute !=m_minute) return false;
    return true;
  }

  /**
  * @brief check whether the CurrentDate is  greater than the t_date
  */
  bool Date::operator>(const Date &t_date) const {
    if (m_year > t_date.m_year) return true;
    if (m_year ==t_date.m_year) {
        if (m_month >t_date.m_month) return true;
        if (m_month ==t_date.m_month) {
            if (m_day >t_date.m_day) return true;
            if (m_day ==t_date.m_day) {
                if (m_hour >t_date.m_hour) return true;
                if (m_hour == t_date.m_hour) {
                    if (m_minute >t_date.m_minute) return true;
                }
            }
        }
    }
    return false;
  }

  /**
  * @brief check whether the CurrentDate is  less than the t_date
  */
  bool Date::operator<(const Date &t_date) const {
    return !(*this > t_date || *this ==t_date);
  }

  /**
  * @brief check whether the CurrentDate is  greater or equal than the t_date
  */
  bool Date::operator>=(const Date &t_date) const {
    return (*this > t_date || *this ==t_date);
  }

  /**
  * @brief check whether the CurrentDate is  less than or equal to the t_date
  */
  bool Date::operator<=(const Date &t_date) const {
    return !(*this >t_date);
  }