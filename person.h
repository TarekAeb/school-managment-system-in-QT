#ifndef PERSON_H
#define PERSON_H

#include <QCryptographicHash>
#include <string>
#include<QString>
QT_BEGIN_NAMESPACE
class Person {
private:
    std::string name;
    std::string id;
    std::string email;
    std::string phone;
    std::string dateOfBirth;
    std::string password;

    std::string hashPassword(const std::string &password);
    void validateName(const std::string &name) const;
    void validateID(const std::string &id) const;
    void validateDateOfBirth(const std::string &dateOfBirth) const;
    void validateEmail(const std::string &email) const;
    void validatePhone(const std::string &phone) const;
public:
    ~Person();

    Person(const std::string &name, const std::string &id, const std::string &phone,
           const std::string &email, const std::string &dateOfBirth, const std::string &password);

    void setName(const std::string &name);
    std::string getName() const;

    void setID(const std::string &id);
    std::string getID() const;

    void setDateOfBirth(const std::string &dateOfBirth);
    std::string getDateOfBirth() const;

    void setEmail(const std::string &email);
    std::string getEmail() const;

    void setPhone(const std::string &phone);
    std::string getPhone() const;

    void setPassword(const std::string &password);
    std::string getPassword() const;



};

#endif // PERSON_H
