//
// Created by wsl on 19-4-11.
//

#ifndef SQLDB_OBJECT_H
#define SQLDB_OBJECT_H

// 字符串, 列表, 字典 Objects
#define DBSTRING_OBJECT 1
#define DBLIST_OBJECT 2
#define DBMAP_OBJECT 3

class Object {
public:
    int type; // sqldb中object的类别
    explicit Object(int t) {
        type = t;
    }

    virtual std::string values()=0;
    virtual ~Object(){
        std::cout<<"delete "<<"Object"<<std::endl;
    };
};

#endif //SQLDB_OBJECT_H
