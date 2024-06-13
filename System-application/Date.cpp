#include<iostream>
#include<ctime>
#include<iomanip>
#include"Date.h"
using namespace std;
date::date(const int d,const int m,const int y){
    setDate(d,m,y);
}

void date::setDate(const int d,const int m, const int y){
    if (day<1||month<1||year<1){std::cerr<<"invalid day/month or/and year";}
    else{day=d;
        month=m;
        year=y;
        if (day==31&&(month==4||month==6||month==9||month==11)||day>31){
            day=1;
            month++;
            if (month>12){
                month=1;
                year++;
            }
        }}
}
