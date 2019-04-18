//
// Created by wsl on 19-4-18.
//

#ifndef SQLDB_EXCPTIONS_H
#define SQLDB_EXCPTIONS_H

#include <exception>

class LexerException : public std::exception {
public:

    const char *what() const throw() {
        return "LexError: can't find another \"";
    }
};

#endif //SQLDB_EXCPTIONS_H
