//
// Created by wsl on 19-4-10.
//

#ifndef SQLDB_DSTRING_H
#define SQLDB_DSTRING_H

#include "object.h"
#include <string>

class DBString: public Object {
public:
    unsigned long length; //buff.length() 返回值为 unsigned long
    std::string buff;

    explicit DBString(std::string s);
    std::string values() override;
    ~DBString() override;
};

DBString::DBString(std::string s):Object(DBSTRING_OBJECT) {
    buff = s;
    length = s.length();
}
std::string DBString::values() {
    return buff;
}
DBString::~DBString() {
    std::cout<< "delete "<<buff<<std::endl;
}


#endif //SQLDB_DSTRING_H
