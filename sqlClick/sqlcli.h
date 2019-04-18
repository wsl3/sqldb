//
// Created by wsl on 19-4-18.
//

#ifndef SQLDB_SQLCLI_H
#define SQLDB_SQLCLI_H

#include <vector>
#include <string>
#include "../error/excptions.h"

// string ---> tokens
void lexer(std::string str, std::vector<std::string> &tokens) {

    try {
        unsigned long length = str.length();
        std::string temp;
        for (unsigned long first = 0, last = 0; last < length;) {
            //保证 first,last
            if (str[first] == ' ' && str[last] == ' ') {
                first++;
                last++;
                continue;
            }

            if(str[first]=='\"'){
                while (last < length && str[++last] != '\"') {}
                if(last==length){
                    throw LexerException();
                }
                first++;
            }else{
                while (last < length && str[++last] != '\"' && str[last] != ' ') {}
                if(last<length && str[last]=='\"'){
                    throw LexerException();
                }
            }
            temp = str.substr(first, last-first);
            tokens.push_back(temp);
            last++;
            first = last;
        }
    } catch (LexerException &e) {
        std::cout << e.what() << std::endl;
    }


}


//从命令行读取 string, 返回 tokens
std::vector<std::string> readCommand() {

    std::string str;
    std::vector<std::string> tokens;
    std::cout<<"sqldb>> ";
    std::getline(std::cin, str);

    lexer(str, tokens);
    return tokens;
}


#endif //SQLDB_SQLCLI_H
