//
// Created by wsl on 19-4-20.
//

#ifndef SQLDB_VM_H
#define SQLDB_VM_H

#include <vector>
#include "../src/object.h"
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

    void delFunc(vector<string> tokens);

    void ldelFunc(vector<string> tokens);

    void hdelFunc(vector<string> tokens);

    void catFunc(vector<string> tokens);

    void typeFunc(vector<string> tokens);

    void linsertFunc(vector<string> tokens);

    void lsortFunc(vector<string> tokens);

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

                //del string_key
            case DEL:
                delFunc(tokens);
                break;
                //ldel list_index
            case LDEL:
                ldelFunc(tokens);
                break;
                //linsert list_key index string
            case LINSERT:
                linsertFunc(tokens);
                break;
                //lsort list_key
            case LSORT:
                lsortFunc(tokens);
                break;
                //hdel map_name key
            case HDEL:
                hdelFunc(tokens);
                break;
            case EXIST:
                existFunc(tokens);
                break;

                //type 检查key的类型
            case TYPES:
                typeFunc(tokens);
                break;
                //cat 查看内部情况
            case CAT:
                catFunc(tokens);
                break;
            case EXIT:
                exit(1);
            default:
                cout << "I don't know what are you f**k saying!!!" << endl;
                break;

        }

    }
}

VirtualMachine::VirtualMachine() {
    //cmd 初始化
    init();
    //数据库底层 哈系表初始化
    mp = new DBMap(10);
}

VirtualMachine::~VirtualMachine() {
    delete mp;
}

void VirtualMachine::init() {
    _init(dict);
}

// get key
void VirtualMachine::getFunc(vector<string> tokens) {
    auto *p = (DBString *) mp->get(tokens[1]);
    if (p == nullptr) {
        cout << "I got Nothing!" << endl;
    } else if (p->type == DBSTRING_OBJECT) {
        cout << p->buff << endl;
    } else {
        cout << "It is not a string!" << endl;
    }
}

//set key value_string
void VirtualMachine::setFunc(vector<string> tokens) {
    string key = tokens[1];
    auto *value = (DBString *) mp->get(key);
    if (value != nullptr && value->type != DBSTRING_OBJECT) {
        cout << "This key has exist!" << endl;
        return;
    } else if (value == nullptr) {
        value = new DBString(tokens[2]);
        mp->insert(key, value);
    } else {
        value->buff = key;
    }

}

void VirtualMachine::existFunc(vector<string> tokens) {
    if (mp->has_key(tokens[1])) {
        cout << "I find it!" << endl;
    } else {
        cout << "I don't find it" << endl;
    }
}

// lpush list 1 2 3
void VirtualMachine::lpushFunc(vector<string> tokens) {
    string key = tokens[1];
    auto *value = (DBList *) mp->get(key);
    bool is_here = true;
    if (value != nullptr && value->type != DBLIST_OBJECT) {
        cout << "This key has exist!" << endl;
        return;
    } else if (value == nullptr) {
        value = new DBList();
        is_here = false;
    }

    for (int i = 2; i < tokens.size(); i++) {
        value->append(tokens[i]);
    }
    if (!is_here) {
        mp->insert(key, value);
    }
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
    if (tokens.size() == 1) {
        mp->keys();
        return;
    }
    auto *p = (DBMap *) mp->get(tokens[1]);
    p->keys();
}

// hset map_name k1 v1 k2 v2
// 首先查看数据库中是否有 map_name
void VirtualMachine::hsetFunc(vector<string> tokens) {
    auto *value = (DBMap *) mp->get(tokens[1]);
    bool is_here = true;
    if (value != nullptr && value->type != DBMAP_OBJECT) {
        cout << "This key has exist!" << endl;
        return;
    } else if (value == nullptr) {
        value = new DBMap();
        is_here = false;
    }

    for (int i = 2; i <= tokens.size() - 2; i = i + 2) {
        value->insert(tokens[i], tokens[i + 1]);
    }
    if (!is_here) {
        mp->insert(tokens[1], value);
    }
}

// hget map_name key
void VirtualMachine::hgetFunc(vector<string> tokens) {
    auto *p = (DBMap *) mp->get(tokens[1]);
    if (p != nullptr && p->type == DBMAP_OBJECT) {
        auto *value = p->get(tokens[2]);
        if (value != nullptr) {
            cout << value->values() << endl;
        } else {
            cout << "There is not this key in the db!" << endl;
        }
    } else {
        cout << "There is not this db!" << endl;
    }
}

//del key
void VirtualMachine::delFunc(vector<string> tokens) {
    mp->del(tokens[1]);
}

//ldel list_type_key index
void VirtualMachine::ldelFunc(vector<string> tokens) {
    auto *p = (DBList *) mp->get(tokens[1]);
    if (p != nullptr && p->type == DBLIST_OBJECT) {
        p->del(stoi(tokens[2]));
    } else {
        cout << "I can't del it!" << endl;
    }

}

//linsert list_key index string
void VirtualMachine::linsertFunc(vector<string> tokens) {
    auto *p = (DBList *) mp->get(tokens[1]);
    if (p != nullptr && p->type == DBLIST_OBJECT) {
        p->insert(tokens[3], stoi(tokens[2]));
    } else {
        cout << "I can't insert it!" << endl;
    }
}

//lsort list_key
//lsort list_key desc
void VirtualMachine::lsortFunc(vector<string> tokens) {
    auto *p = (DBList *) mp->get(tokens[1]);
    if(p!=nullptr){
        bool reverse = (tokens.size()!=2 && tokens[2]=="desc");
        p->sort(reverse);
    }else{
        cout<<"I can't sort it!"<<endl;
    }
}

//hdel map_type_key key
void VirtualMachine::hdelFunc(vector<string> tokens) {
    auto *p = (DBMap *) mp->get(tokens[1]);
    if (p != nullptr && p->type == DBMAP_OBJECT) {
        p->del(tokens[2]);
    } else {
        cout << "I can't del it!" << endl;
    }
}


//cat
//cat string_key
//cat list_key
//cat map_key
void VirtualMachine::catFunc(vector<string> tokens) {
    if (tokens.size() == 1) {
        mp->values();
    } else {
        auto *p = mp->get(tokens[1]);
        if (p == nullptr) {
            cout << "There is not this key!" << endl;
            return;
        }
        switch (p->type) {
            case DBSTRING_OBJECT:
                cout << p->values() << endl;
                break;
            case DBLIST_OBJECT:
                cout << p->values() << endl;
                break;
            case DBMAP_OBJECT:
                cout << p->values() << endl;
                break;
            default:
                cout << "I can't cat it!" << endl;
        }
    }
}


void VirtualMachine::typeFunc(vector<string> tokens) {
    mp->types(tokens[1]);
}

#endif //SQLDB_VM_H
