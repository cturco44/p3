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
#include <unordered_set>

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
    else if(cmd == 'r') {
        r_cmd();
    }
    else if(cmd == 'd') {
        d_cmd();
    }
    else if(cmd == 'b') {
        b_cmd();
    }
    else if(cmd == 'e') {
        e_cmd();
    }
    else if(cmd == 'l') {
        l_cmd();
    }
    else if(cmd == 's') {
        s_cmd();
    }
}
void Logger::s_cmd() {
    cout << "excerpt list sorted\n";
    if(excerpt_list.empty()) {
        cout << "(previously empty)\n";
        return;
    }
    cout << "previous ordering:\n";
    print_condensed_el();
    cout << "new ordering:\n";
    sort(excerpt_list.begin(), excerpt_list.end(), LogEntryPtrLess());
    print_condensed_el();

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
void Logger::l_cmd() {
    cout << "excerpt list cleared\n";
    if(excerpt_list.empty()) {
        cout << "(previously empty)\n";
        return;
    }
    cout << "previous contents:\n";
    print_condensed_el();
    
    excerpt_list.erase(excerpt_list.begin(), excerpt_list.end());
    
    
    
}
void Logger::e_cmd() {
    int index;
    cin >> index;
    if(index >= (int)excerpt_list.size()) {
        return;
    }
    auto ptr = excerpt_list[index];
    excerpt_list.erase(excerpt_list.begin() + index);
    excerpt_list.push_back(ptr);
    cout << "Moved excerpt list entry " << index << "\n";
}
void Logger::r_cmd() {
    copy(search_results.begin(), search_results.end(), back_inserter(excerpt_list));
    cout << search_results.end() - search_results.begin()
    << " entries appended\n";
}
void Logger::d_cmd() {
    int delete_pos;
    cin >> delete_pos;
    
    if(delete_pos >= (int)excerpt_list.size()) {
        return;
    }
    excerpt_list.erase(excerpt_list.begin() + delete_pos);
    cout << "Deleted excerpt list entry " << delete_pos << "\n";
}
void Logger::b_cmd() {
    int index;
    cin >> index;
    if(index >= (int)excerpt_list.size()) {
        return;
    }
    auto ptr = excerpt_list[index];
    excerpt_list.erase(excerpt_list.begin() + index);
    excerpt_list.push_front(ptr);
    cout << "Moved excerpt list entry " << index << "\n";
    
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
void Logger::print_condensed_el() const {
    
    cout << "0|" << (*excerpt_list.begin())->entryID << "|"
    << ts_convert_back((*excerpt_list.begin())->timestamp)
    << "|" << (*excerpt_list.begin())->category << "|"
    << (*excerpt_list.begin())->message << "\n";
    
    cout << "...\n";
    
    cout << excerpt_list.size() - 1 << "|"
    << (excerpt_list.back())->entryID << "|"
    << ts_convert_back((excerpt_list.back())->timestamp)
    << "|" << (excerpt_list.back())->category << "|"
    << (excerpt_list.back())->message << "\n";
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
        
        unordered_set<string> set;
        unordered_set_helper(cat.begin(), cat.end(), set);
        string msg = it->message;
        lowercase(msg);
        unordered_set_helper(msg.begin(), msg.end(), set);
        
        for(auto j = set.begin(); j != set.end(); ++j) {
            auto check = k_hash.emplace(*j, vector<const LogEntry*> {&(*it)});
            if(!check.second) {
                (check.first)->second.push_back(&(*it));
            }
        }
        
    }
    
}
void Logger::unordered_set_helper(string::iterator start, string::iterator end,
                                  unordered_set<string> &set) const {
    if(start == end) {
        return;
    }
    start = find_if(start, end, (int(*)(int))isalnum);
    string::iterator it = find_if_not(start, end, (int(*)(int))isalnum);
    set.emplace(string(start, it));
    unordered_set_helper(it, end, set);
    
}
void uppercase(string &s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
}
void lowercase(string &s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}
