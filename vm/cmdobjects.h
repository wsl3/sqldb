//
// Created by wsl on 19-4-20.
//

#ifndef SQLDB_CMDOBJECTS_H
#define SQLDB_CMDOBJECTS_H

#include <map>
#include "../src/dmap.h"

//string
#define GET 1
#define SET 2

//list
#define LPUSH 21
#define RANGE 22


//map
#define KEYS 41
#define HSET 42
#define HGET 43


#define EXIST 3
#define EXIT 4



void _init(std::map<std::string, int> &dict) {
    dict["get"] = 1;
    dict["set"] = 2;

    dict["lpush"] = 21;
    dict["range"] = 22;

    dict["keys"] = 41;
    dict["hset"] = 42;
    dict["hget"] = 43;


    dict["exist"] = 3;
    dict["exit"] = 4;
}


#endif //SQLDB_CMDOBJECTS_H
