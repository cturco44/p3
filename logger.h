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
struct IDLess {
    bool operator()(long long int lhs, const LogEntry &rhs) const {
        return lhs < rhs.timestamp;
    }
    bool operator()(const LogEntry &rhs, long long int lhs) const {
        return rhs.timestamp < lhs;
    }
};
struct LogEntryLess {
    bool operator()(const LogEntry &lhs, const LogEntry &rhs) const {
        if(lhs.timestamp == rhs.timestamp) {
            if(lhs.category == rhs.category) {
                return lhs.entryID < rhs.entryID;
            }
            return lhs.category < rhs.category;
        }
        return lhs.timestamp < rhs.timestamp;
    }
};
class Logger {
public:
    void push_master(long long int timestamp_in, std::string category_in, std::string message, int entryID) {
        master.emplace_back(timestamp_in, category_in, message, entryID);
    }
    void sort_master() {
        std::sort(master.begin(), master.end(), LogEntryLess());
    }
    void process_cmd(char cmd);
    void a_cmd();
    void p_cmd() const;
    void t_cmd();
    void m_cmd();
    void g_cmd() const;
private:
    std::unordered_map<std::string, std::vector<LogEntry*>> c_hash;
    std::unordered_map<std::string, std::vector<LogEntry*>> k_hash;
    std::deque<LogEntry*> excerpt_list;
    std::vector<LogEntry> master;
    std::vector<const LogEntry*> search_results;
    
    std::string ts_convert_back(long long int ts) const;
    std::vector<const LogEntry>::iterator binary_search_lower(long long int ts) const;
    long long int ts_convert(std::string ts) const;
};

#endif /* logger_hpp */
