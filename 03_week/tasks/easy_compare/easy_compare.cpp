#include <stdexcept>
#include <tuple>

struct Date {
    unsigned year = 0u;
    unsigned month = 0u;
    unsigned day = 0u;
};

struct StudentInfo {
    size_t id;
    char mark;
    int score;
    unsigned course;
    Date birth_date;
};

bool operator>(const Date& date1, const Date& date2) {
    if (date1.year > date2.year) return true;
    else if (date1.year == date2.year){
        if (date1.month > date2.month) return true;
        else if (date1.month == date2.month) {
            if (date1.day > date2.day) return true;
        }        
    }
    return false;
}

bool operator<(const Date& date1, const Date& date2) {
    if (date1.year < date2.year) return true;
    else if (date1.year == date2.year){
        if (date1.month < date2.month) return true;
        else if (date1.month == date2.month) {
            if (date1.day < date2.day) return true;
        }        
    }
    return false;
}

bool operator>=(const Date& date1, const Date& date2) {
if (date1.year > date2.year) return true;
    else if (date1.year == date2.year){
        if (date1.month > date2.month) return true;
        else if (date1.month == date2.month) {
            if (date1.day >= date2.day) return true;
        }        
    }
    return false;
}

bool operator<=(const Date& date1, const Date& date2) {
    if (date1.year < date2.year) return true;
    else if (date1.year == date2.year){
        if (date1.month < date2.month) return true;
        else if (date1.month == date2.month) {
            if (date1.day <= date2.day) return true;
        }        
    }
    return false;
}

bool operator==(const Date& date1, const Date& date2) {
    return date1.year == date2.year   &&
           date1.month == date2.month &&
           date1.day == date2.day;
}

bool operator!=(const Date& date1, const Date& date2) {
    return date1.year != date2.year   ||
           date1.month != date2.month ||
           date1.day != date2.day;
}

bool operator<(const StudentInfo& s1, const StudentInfo& s2) {
    if (std::tie(s1.mark) > std::tie(s2.mark)) return true;
    else if (std::tie(s1.mark) == std::tie(s2.mark)) {
        if (s1.score < s2.score) return true;
        else if (s1.score == s2.score) {
            if (s1.course > s2.course) return true;
            else if (s1.course == s2.course) {
                if (s1.birth_date < s2.birth_date) return true;
            }
        } 
    }
    return false;
}

bool operator==(const StudentInfo& s1, const StudentInfo& s2) {
    return std::tie(s1.mark, s1.score) == std::tie(s2.mark, s2.score);                   
}

bool operator!=(const StudentInfo& s1, const StudentInfo& s2) {
    if (std::tie(s1.mark) != std::tie(s2.mark) || 
        s1.score != s2.score                   ||
        s1.course != s2.course                 ||
        s1.birth_date != s2.birth_date) 
        return true; 
    return false;
}

