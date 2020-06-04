//
//  logger.hpp
//  p3
//
//  Created by Connor Turco on 6/4/20.
//  Copyright © 2020 Connor Turco. All rights reserved.
//

#ifndef logger_hpp
#define logger_hpp

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <deque>

struct LogEntry {
    long long int timestamp;
    std::string category;
    std::string message;
    int entryID;
    
    LogEntry(long long int timestamp_in, std::string category_in, std::string message_in, int entryID_in) :
    timestamp(timestamp_in), category(category_in), message(message_in), entryID(entryID_in) {}
    
};
class Logger {
public:
    void push_master(long long int timestamp_in, std::string category_in, std::string message, int entryID) {
        master.emplace_back(timestamp_in, category_in, message, entryID);
    }
private:
    std::unordered_map<std::string, std::vector<LogEntry*>> c_hash;
    std::unordered_map<std::string, std::vector<LogEntry*>> k_hash;
    std::deque<LogEntry*> excerpt_results;
    std::vector<LogEntry> master;
    std::vector<LogEntry*> search_results;
    
    
};

#endif /* logger_hpp */
