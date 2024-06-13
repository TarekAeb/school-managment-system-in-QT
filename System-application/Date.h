#ifndef date_H
#define date_H
class date{
public:
    date();
    date(const int,const int,const int);
    void setDate(const int,const int,const int);

private:
    int day,month,year;
    void isLeaper(int);
};
#endif
