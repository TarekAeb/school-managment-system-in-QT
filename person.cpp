#include "person.h"
#include <stdexcept>
#include <cctype> // for isdigit
#include <regex>
#include<QString>
#include<string>
Person::Person(const std::string &name, const std::string &id, const std::string &phone,
               const std::string &email, const std::string &dateOfBirth, const std::string &password)
{
    setName(name);
    setID(id);
    setPhone(phone);
    setEmail(email);
    setDateOfBirth(dateOfBirth);
    setPassword(password);
}

Person::~Person()
{
    // Destructor implementation
}

void Person::setName(const std::string &name)
{
    validateName(name);
    this->name = name;
}

std::string Person::getName() const
{
    return name;
}

void Person::setID(const std::string &id)
{
    validateID(id);
    this->id = id;
}

std::string Person::getID() const
{
    return id;
}

void Person::setEmail(const std::string &email)
{
    validateEmail(email);
    this->email = email;
}

std::string Person::getEmail() const
{
    return email;
}

void Person::setPhone(const std::string &phone)
{
    validatePhone(phone);
    this->phone = phone;
}

std::string Person::getPhone() const
{
    return phone;
}

void Person::setDateOfBirth(const std::string &dateOfBirth)
{
    validateDateOfBirth(dateOfBirth);
    this->dateOfBirth = dateOfBirth;
}

std::string Person::getDateOfBirth() const
{
    return dateOfBirth;
}

void Person::setPassword(const std::string &password)
{
    // Hash the password before storing it
    this->password = hashPassword(password);
}

std::string Person::getPassword() const
{
    return password;
}

std::string Person::hashPassword(const std::string &password)
{
    QByteArray hashedPassword = QCryptographicHash::hash(password.c_str(), QCryptographicHash::Sha256).toHex();
    return hashedPassword.toStdString();
}

void Person::validateName(const std::string &name) const
{
    if (name.size() < 3)
    {
        throw std::invalid_argument("Name must have at least three characters and include whitespace.");
    }

    int spaceCount = 0;
    for (char c : name)
    {
        if (c == ' ')
        {
            spaceCount++;
        }
    }

    if (spaceCount == 0)
    {
        throw std::invalid_argument("Name must contain at least one space.");
    }
}

void Person::validateID(const std::string &id) const
{
    if (id.size() != 10)
    {
        throw std::invalid_argument("ID must contain exactly 10 digits.");
    }

    for (char c : id)
    {
        if (!std::isdigit(c))
        {
            throw std::invalid_argument("ID must contain only digits.");
        }
    }
}


void Person::validateEmail(const std::string &email) const
{
    // Regular expression pattern for email ending with "@ensia.edu.dz"
    std::regex emailPattern(R"([a-zA-Z0-9._%+-]+@ensia.edu.dz)");

    if (!std::regex_match(email, emailPattern))
    {
        throw std::invalid_argument("Invalid email format. Email must end with '@ensia.edu.dz'.");
    }
}


void Person::validatePhone(const std::string &phone) const
{
    if (phone.size() != 10 || phone[0] != '0')
    {
        throw std::invalid_argument("Phone number must be 10 digits and start with '0'.");
    }
}



void Person::validateDateOfBirth(const std::string &dateOfBirth) const
{
    // Regular expression pattern for date format "YYYY-MM-DD"
    std::regex datePattern("\\d{4}-\\d{2}-\\d{2}");

    if (!std::regex_match(dateOfBirth, datePattern))
    {
        throw std::invalid_argument("Invalid date format. Date must be in the format YYYY-MM-DD.");
    }

    // Extracting year, month, and day from the date string
    int year = std::stoi(dateOfBirth.substr(0, 4));
    int month = std::stoi(dateOfBirth.substr(5, 2));
    int day = std::stoi(dateOfBirth.substr(8, 2));

    // Checking the validity of the date components
    if ((year < 1900 )|| (year > 2100))
    {
        throw std::invalid_argument("Invalid year. Year must be between 1900 and 2100.");
    }

    if ((month < 1 )|| (month > 12))
    {
        throw std::invalid_argument("Invalid month. Month must be between 1 and 12.");
    }

    // Checking for the number of days based on the month
    if ((day < 1 )|| (day > 31))
    {
        throw std::invalid_argument("Invalid day. Day must be between 1 and 31.");
    }

    // Additional logic for checking days in specific months (e.g., February)
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    {
        throw std::invalid_argument("Invalid day. April, June, September, and November have 30 days.");
    }

    if (month == 2)
    {
        // Checking for leap year
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > 29 || (day > 28 && !isLeapYear))
        {
            throw std::invalid_argument("Invalid day. February has 28 or 29 days in a leap year.");
        }
    }
}


