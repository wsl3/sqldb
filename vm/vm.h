//
// Created by wsl on 19-4-20.
//

#ifndef SQLDB_VM_H
#define SQLDB_VM_H

#include <vector>
#include "compile.h"
#include "cmdobjects.h"
#include "../src/dmap.h"

using namespace std;

class VirtualMachine {
private:
    map<string, int> dict;
    DBMap *mp;

    void init();

    void getFunc(vector<string> tokens);

    void existFunc(vector<string> tokens);

    void setFunc(vector<string> tokens);

    void lpushFunc(vector<string> tokens);

    void rangeFunc(vector<string> tokens);

    void keysFunc(vector<string> tokens);
    void hsetFunc(vector<string> tokens);
    void hgetFunc(vector<string> tokens);

public:
    VirtualMachine();

    ~VirtualMachine();

    void run();

};


void VirtualMachine::run() {
    init();
    while (true) {
        // 读取输入命令
        vector<string> tokens = readCommand();
        if (tokens.empty()) {
            continue;
        }

        switch (dict[tokens[0]]) {
            //String
            case GET:
                getFunc(tokens);
                break;
            case SET:
                setFunc(tokens);
                break;
            // List
            case LPUSH:
                lpushFunc(tokens);
                break;
            case RANGE:
                rangeFunc(tokens);
                break;
            // Map
            case KEYS:
                keysFunc(tokens);
                break;
            case HSET:
                hsetFunc(tokens);
                break;
            case HGET:
                hgetFunc(tokens);
                break;


            case EXIST:
                existFunc(tokens);
                break;
            case EXIT:
                exit(1);
            default:
                cout<<"I don't know what are you f**k saying!!!"<<endl;
                break;

        }

    }
}

VirtualMachine::VirtualMachine() {
    //cmd 初始化
    init();
    //数据库底层 哈系表初始化
    mp = new DBMap(1000);
}

VirtualMachine::~VirtualMachine() {
    delete mp;
}

void VirtualMachine::init() {
    _init(dict);
}

// get key
void VirtualMachine::getFunc(vector<string> tokens) {
    //cout << "get 操作\n";
    auto *p = mp->get(tokens[1]);
    if (p == nullptr) {
        std::cout << "I got Nothing!" << std::endl;
        return;
    }
    switch (p->type) {
        case 1:
            cout << ((DBString *) p)->buff << endl;
            break;
        case 2:
            cout << ((DBList *) p)->values() << endl;
            break;

        case 3:
            cout << ((DBMap *) p)->values() << endl;
            break;
    }
}

void VirtualMachine::setFunc(vector<string> tokens) {
    cout << "set 操作\n";
    string key = tokens[1];
    DBString *value = new DBString(tokens[2]);
    mp->insert(key, value);

}

void VirtualMachine::existFunc(vector<string> tokens) {
    if (mp->has_key(tokens[1])) {
        cout << "I find it!" << endl;
    } else {
        cout << "I don't find it" << endl;
    }
}

void VirtualMachine::lpushFunc(vector<string> tokens) {
    string key = tokens[1];
    auto *value = new DBList();
    for (int i = 2; i < tokens.size(); i++) {
        value->append(tokens[i]);
    }
    mp->insert(key, value);
}

// range key begin end
void VirtualMachine::rangeFunc(vector<string> tokens) {
    string key = tokens[1];
    auto *p = (DBList *) (mp->get(key));
    if (p != nullptr) {
        p->range(stoi(tokens[2]), stoi(tokens[3]));
    } else {
        cout << "I don't find the key: " + key << endl;
    }
}

//keys or keys map_name
void VirtualMachine::keysFunc(vector<string> tokens) {
    if(tokens.size()==1){
        mp->keys();
        return;
    }
    auto *p = (DBMap*)mp->get(tokens[1]);
    p->keys();
}

// hset map_name k1 v1 k2 v2
// 首先查看数据库中是否有 map_name
void VirtualMachine::hsetFunc(vector<string> tokens) {
    DBMap* value;
    bool is_here = mp->has_key(tokens[1]);
    if(is_here){
        value = (DBMap*)mp->get(tokens[1]);
    }else{
        value = new DBMap();
    }

    for(int i=2;i<=tokens.size()-2;i=i+2){
        value->insert(tokens[i], tokens[i+1]);
    }
    if(!is_here){
        mp->insert(tokens[1], value);
    }
}

// hget map_name key
void VirtualMachine::hgetFunc(vector<string> tokens) {
    auto *p = (DBMap*)mp->get(tokens[1]);
    if(p!= nullptr){
        auto* value = p->get(tokens[2]);
        if(value != nullptr){
            cout<<value->values()<<endl;
        }else{
            cout<<"There is not this key in the db!"<<endl;
        }
    }else{
        cout<<"There is not this db!"<<endl;
    }
}
#endif //SQLDB_VM_H
