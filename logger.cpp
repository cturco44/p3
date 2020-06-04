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
    string ts;
    cin >> ts;
    
}
void Logger::m_cmd() {
    string ts;
    cin >> ts;
    long long int ts_converted = ts_convert(ts);
    auto it = binary_search_lower(ts_converted);
    auto end = it;
    //Get [begin, end) range
    while(end->timestamp == ts_converted) {
        ++end;
    }
    
    while(it != end) {
        search_results.push_back(&(*it));
        ++it;
    }
    
    
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
long long int Logger::ts_convert(string ts) const {
    ts.erase(remove(ts.begin(), ts.end(), ':'), ts.end());
    long long int ts_final = stoll(ts, nullptr, 10);
    return ts_final;
}
