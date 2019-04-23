//
// Created by wsl on 19-4-20.
//

#ifndef SQLDB_CMDOBJECTS_H
#define SQLDB_CMDOBJECTS_H

#include <map>
#include "../src/dmap.h"


#define GET 1
#define SET 2
#define EXIST 3
#define EXIT 4



void _init(std::map<std::string, int> &dict) {
    dict["get"] = 1;
    dict["set"] = 2;
    dict["exist"] = 3;
    dict["exit"] = 4;
}


#endif //SQLDB_CMDOBJECTS_H
