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

};

DBString::DBString(std::string s):Object(DBSTRING_OBJECT) {
    buff = s;
    length = s.length();
}


#endif //SQLDB_DSTRING_H
