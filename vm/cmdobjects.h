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

//del
#define DEL 77
#define LDEL 78
#define HDEL 79

#define TYPES 98
#define CAT 99
#define EXIST 100
#define EXIT 101




void _init(std::map<std::string, int> &dict) {
    dict["get"] = 1;
    dict["set"] = 2;

    dict["lpush"] = 21;
    dict["range"] = 22;

    dict["keys"] = 41;
    dict["hset"] = 42;
    dict["hget"] = 43;

    dict["del"] = 77;
    dict["ldel"] = 78;
    dict["hdel"] = 79;

    dict["types"] = 98;
    dict["cat"] = 99;
    dict["exist"] = 100;
    dict["exit"] = 101;
}


#endif //SQLDB_CMDOBJECTS_H
