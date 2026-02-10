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

bool operator<(const Date& date1, const Date& date2) {
    return std::tie(date1.year, date1.month, date1.day) < std::tie(date2.year, date2.month, date2.day);
}

bool operator==(const Date& date1, const Date& date2) {
    return std::tie(date1.year, date1.month, date1.day) == std::tie(date2.year, date2.month, date2.day);
}

bool operator>(const Date& date1, const Date& date2) {
    return !(date1 < date2) && !(date1 == date2); 
}

bool operator>=(const Date& date1, const Date& date2) {
    return !(date1 < date2) || (date1 == date2);
}

bool operator<=(const Date& date1, const Date& date2) {
    return (date1 < date2) || (date1 == date2);
}

bool operator!=(const Date& date1, const Date& date2) {
    return !(date1 == date2); 
}

bool operator<(const StudentInfo& s1, const StudentInfo& s2) {
    return std::tie(s1.mark, s2.score, s1.course, s2.birth_date) > std::tie(s2.mark, s1.score, s2.course, s1.birth_date);
}

bool operator==(const StudentInfo& s1, const StudentInfo& s2) {
    return std::tie(s1.mark, s1.score) == std::tie(s2.mark, s2.score);                   
}

bool operator!=(const StudentInfo& s1, const StudentInfo& s2) {
    return !(s1 == s2);
}

