//
//  logger.cpp
//  p3
//
//  Created by Connor Turco on 6/4/20.
//  Copyright © 2020 Connor Turco. All rights reserved.
//

#include "logger.h"
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <cctype>

using namespace std;
using MasterIt = vector<const LogEntry>::iterator;

void Logger::process_cmd(char cmd) {
    if(cmd == '#') {
        string comment;
        getline(cin, comment);
    }
    else if(cmd == 'a') {
        a_cmd();
    }
    else if(cmd == 'p') {
        p_cmd();
    }
    else if(cmd == 'm') {
        m_cmd();
    }
    else if(cmd == 'g') {
        g_cmd();
    }
    else if(cmd == 't') {
        t_cmd();
    }
    else if(cmd == 'c') {
        c_cmd();
    }
}
void Logger::a_cmd() {
    int entryID;
    cin >> entryID;
    
    for(auto it = master.begin(); it != master.end(); ++it) {
        if(it->entryID == entryID) {
            excerpt_list.push_back(&(*it));
            return;
        }
    }
}
void Logger::p_cmd() const {
    size_t index = 0;
    for(auto it = excerpt_list.cbegin(); it != excerpt_list.cend(); ++it) {
        cout << index << "|" << (*it)->entryID << "|"
        << ts_convert_back((*it)->timestamp) << "|" << (*it)->category << "|"
        << (*it)->message << "\n";
        ++index;
    }
}
void Logger::t_cmd() {
    string ts1, ts2;
    getline(cin, ts1, '|');
    cin >> ts2;
    
    clear_search_results();
    long long int ts1_converted = ts_convert(ts1);
    long long int ts2_converted = ts_convert(ts2);
    
    auto it = binary_search_lower(ts1_converted);
    auto end = binary_search_upper(ts2_converted);
    
    cout << "Timestamp search: " << end - it << " entries found\n";
    while(it != end) {
        search_results.push_back(&(*it));
        ++it;
    }
    
}
void Logger::m_cmd() {
    string ts;
    cin >> ts;
    
    clear_search_results();
    long long int ts_converted = ts_convert(ts);
    auto it = binary_search_lower(ts_converted);
    auto end = binary_search_upper(ts_converted);
    
    cout << "Timestamp search: " << end - it << " entries found\n";
    while(it != end) {
        search_results.push_back(&(*it));
        ++it;
    }
    
    
}
void Logger::c_cmd() {
    clear_search_results();
    string search;
    getline(cin, search);
    //Convert to lowercase and delete space (first char because of getline)
    lowercase(search);
    search.erase(0, 1);
    
    auto it = c_hash.find(search);
    if(it != c_hash.end()) {
        copy(it->second.begin(), it->second.end(), back_inserter(search_results));
    }
    cout << "Category search: " << search_results.size() << " entries found\n";
}
void Logger::g_cmd() const {
    for(auto it = search_results.cbegin(); it != search_results.cend(); ++it) {
        cout << (*it)->entryID << "|" << ts_convert_back((*it)->timestamp)
        << "|" << (*it)->category << "|" << (*it)->message << "\n" ;
    }
}
string Logger::ts_convert_back(long long int ts) const {
    string ts_converted = to_string(ts);
    size_t num_zeros = 10 - ts_converted.length();;
    string front (num_zeros, '0');
    ts_converted = front + ts_converted;
    ts_converted.insert(8, ":");
    ts_converted.insert(6, ":");
    ts_converted.insert(4, ":");
    ts_converted.insert(2, ":");
    
    return ts_converted;
}
MasterIt Logger::binary_search_lower(long long int ts) const {
    return lower_bound(master.begin(), master.end(), ts, IDLess());
    
}
MasterIt Logger::binary_search_upper(long long int ts) const {
    return upper_bound(master.begin(), master.end(), ts, IDLess());
    
}
long long int Logger::ts_convert(string ts) const {
    ts.erase(remove(ts.begin(), ts.end(), ':'), ts.end());
    long long int ts_final = stoll(ts, nullptr, 10);
    return ts_final;
}
void Logger::clear_search_results() {
    search_results.clear();
}
void Logger::initializer() {
    std::sort(master.begin(), master.end(), LogEntryLess());
    for(auto it = master.cbegin(); it != master.cend(); ++it) {
        string cat = it->category;
        lowercase(cat);
        auto check = c_hash.emplace(cat, vector<const LogEntry*> {&(*it)});
        if(!check.second) {
            (check.first)->second.push_back(&(*it));
        }
    }
}
void uppercase(string &s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
}
void lowercase(string &s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}
