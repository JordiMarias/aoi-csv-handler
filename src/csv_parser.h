//
// Created by jordimarias on 5/11/22.
//

#ifndef CSV_HANDLER_CSV_PARSER_H
#define CSV_HANDLER_CSV_PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "MessageSent.h"
#include "MessageReceived.h"
#include "Vehicle.h"
#include "Database.h"

class CSVParser {
public:
    CSVParser();
    void parse_sent_positioned(const std::string& file_sent,const std::string& file_positioned, Database& database);
    void parse_received(const std::string& file_location, Database& database);
private:
    static const std::regex positioned_match_;
    static const std::regex positioned_file_;
    static const std::regex sent_match_;
    static const std::regex sent_file_;
    static const std::regex received_file_;
    static const std::regex received_match_;
};


#endif //CSV_HANDLER_CSV_PARSER_H
