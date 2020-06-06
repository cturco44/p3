// Project Identifier: 01BD41C3BF016AD7E8B6F837DF18926EC3E83350
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
#include <unordered_set>
void uppercase(std::string &s);
void lowercase(std::string &s);

enum LastSearch{k,c,other};
struct LogEntry {
    long long int timestamp;
    std::string category;
    std::string lc_category;
    std::string message;
    int entryID;
    
    LogEntry(long long int timestamp_in, std::string category_in, std::string message_in, int entryID_in) :
    timestamp(timestamp_in), category(category_in), message(message_in), entryID(entryID_in) {
        lc_category = category;
        lowercase(lc_category);
    }
    
};
struct IDLess {
    bool operator()(long long int lhs, const LogEntry &rhs) const {
        return lhs < rhs.timestamp;
    }
    bool operator()(const LogEntry &rhs, long long int lhs) const {
        return rhs.timestamp < lhs;
    }
    bool operator()(const LogEntry &lhs, const LogEntry &rhs) const {
        return rhs.timestamp < lhs.timestamp;
    }
    
};
struct LogEntryLess {
    bool operator()(const LogEntry &lhs, const LogEntry &rhs) const {
        if(lhs.timestamp == rhs.timestamp) {
            if(lhs.lc_category == rhs.lc_category) {
                return lhs.entryID < rhs.entryID;
            }
            return lhs.lc_category < rhs.lc_category;
        }
        return lhs.timestamp < rhs.timestamp;
    }
};
struct LogEntryPtrLess {
    bool operator()(const LogEntry* lhs, const LogEntry* rhs) const {
        if(lhs->timestamp == rhs->timestamp) {
            std::string lhs_cat = lhs->lc_category;
            std::string rhs_cat = rhs->lc_category;
            if(lhs_cat == rhs_cat) {
                return lhs->entryID < rhs->entryID;
            }
            return lhs_cat < rhs_cat;
        }
        return lhs->timestamp < rhs->timestamp;
    }
};
class Logger {
public:
    Logger() {
        searched_yet = false;
        last_search = other;
    }
    void push_master(long long int timestamp_in, std::string category_in, std::string message, int entryID) {
        master.emplace_back(timestamp_in, category_in, message, entryID);
    }
    void process_cmd(char cmd);
    void a_cmd();
    void p_cmd() const;
    void t_cmd();
    void m_cmd();
    void g_cmd() const;
    void c_cmd();
    void r_cmd();
    void d_cmd();
    void b_cmd();
    void e_cmd();
    void l_cmd();
    void s_cmd();
    void k_cmd();
    void initializer();
private:
    
    std::unordered_map<std::string, std::vector<const LogEntry*>> c_hash;
    std::unordered_map<std::string, std::vector<const LogEntry*>> k_hash;
    std::deque<unsigned int> excerpt_list;
    std::vector<LogEntry> master;
    std::vector<const LogEntry*> search_results;
    std::vector<unsigned int> id_holder;
    std::vector<std::vector<LogEntry>::const_iterator> search_results_2;
    std::vector<std::vector<const LogEntry*>::const_iterator> search_results_c;
    LastSearch last_search;
    bool searched_yet;
    
    std::string ts_convert_back(long long int ts) const;
    auto binary_search_lower(long long int ts) const;
    long long int ts_convert(std::string ts) const;
    auto binary_search_upper(long long int ts) const;
    void clear_search_results();
    void print_condensed_el() const;
    void unordered_set_helper(std::string::iterator start, std::string::iterator end, std::unordered_set<std::string> &set) const;
        void vector_helper(std::string::iterator start, std::string::iterator end, std::vector<std::string> &set) const;

};

#endif /* logger_hpp */
