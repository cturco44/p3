// Project Identifier: 01BD41C3BF016AD7E8B6F837DF18926EC3E83350
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

using VectorPtr = const LogEntry*;

auto Logger::binary_search_lower(long long int ts) const {
    return lower_bound(master.begin(), master.end(), ts, IDLess());
    
}
auto Logger::binary_search_upper(long long int ts) const {
    return upper_bound(master.begin(), master.end(), ts, IDLess());
    
}

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
    else if(cmd == 'k') {
        k_cmd();
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
    sort(excerpt_list.begin(), excerpt_list.end());
    print_condensed_el();

}
void Logger::a_cmd() {
    int entryID;
    cin >> entryID;
    if(entryID >= (int)master.size() || entryID < 0) {
        return;
    }
    
    excerpt_list.push_back(id_holder[(size_t)entryID]);
    cout << "log entry " << entryID << " appended\n";
}
void Logger::p_cmd() const {
    
    for(unsigned int i = 0; i < (unsigned int)excerpt_list.size(); ++i) {
        unsigned int x = excerpt_list[i];
        cout << i << "|" << master[x].entryID << "|"
        << ts_convert_back(master[x].timestamp) << "|" << master[x].category << "|"
        << master[x].message << "\n";
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
    if(index >= (int)excerpt_list.size() || index < 0) {
        return;
    }
    unsigned int ptr = excerpt_list[(unsigned long)index];
    excerpt_list.erase(excerpt_list.begin() + index);
    excerpt_list.push_back(ptr);
    cout << "Moved excerpt list entry " << index << "\n";
}
void Logger::r_cmd() {
    if(!searched_yet) {
        return;
    }
    int size = 0;
    if(last_search == other) {
        for(auto it = search_results_2[0]; it != search_results_2[1]; ++it) {
            unsigned int index = (unsigned int)(it - search_results_2[0]);
            excerpt_list.push_back(index);
            ++size;
        }
    }
    else if(last_search == c) {
        for(auto it = search_results_c[0]; it != search_results_c[1]; ++it) {
            unsigned int index = (unsigned int)(it - search_results_c[0]);
            excerpt_list.push_back(index);
            ++size;
        }
    }
    else {
        for(auto it = search_results.begin(); it != search_results.end(); ++it) {
            unsigned int index = (unsigned int)(&(*(*it)) - &master[0]);
            excerpt_list.push_back(index);
            ++size;
        }
    }

    cout << size << " log entries appended\n";
}
void Logger::d_cmd() {
    int delete_pos;
    cin >> delete_pos;
    
    if(delete_pos >= (int)excerpt_list.size() || delete_pos < 0) {
        return;
    }
    excerpt_list.erase(excerpt_list.begin() + delete_pos);
    cout << "Deleted excerpt list entry " << delete_pos << "\n";
}
void Logger::b_cmd() {
    int index;
    cin >> index;
    if(index >= (int)excerpt_list.size() || index < 0) {
        return;
    }
    unsigned int ptr = excerpt_list[(unsigned long)index];
    excerpt_list.erase(excerpt_list.begin() + index);
    excerpt_list.push_front(ptr);
    cout << "Moved excerpt list entry " << index << "\n";

}
void Logger::t_cmd() {
    string ts1, ts2;
    getline(cin, ts1, '|');
    cin >> ts2;
    ts1.erase(0,1);
    if(ts1.length() != 14 || ts2.length() != 14) {
        return;
    }
    searched_yet = true;
    last_search = other;
    clear_search_results();
    
    long long int ts1_converted = ts_convert(ts1);
    long long int ts2_converted = ts_convert(ts2);
    
    auto it = binary_search_lower(ts1_converted);
    auto end = binary_search_upper(ts2_converted);
    
    cout << "Timestamps search: " << end - it << " entries found\n";
    search_results_2.push_back(it);
    search_results_2.push_back(end);
    
}
void Logger::m_cmd() {
    string ts;
    cin >> ts;
    if(ts.size() != 14) {
        return;
    }
    searched_yet = true;
    last_search = other;
    clear_search_results();
    long long int ts_converted = ts_convert(ts);
    auto it = binary_search_lower(ts_converted);
    auto end = binary_search_upper(ts_converted);
    
    cout << "Timestamp search: " << end - it << " entries found\n";
    search_results_2.push_back(it);
    search_results_2.push_back(end);
    
}
void Logger::k_cmd() {
    string search;
    getline(cin, search);
    lowercase(search);
    search.erase(0, 1);
    clear_search_results();
    
    searched_yet = true;
    last_search = k;
    vector<string> set;
    vector<VectorPtr> saved;
    vector<VectorPtr> holder;
    
    vector_helper(search.begin(), search.end(), set);
    bool first = true;
    for(auto set_it = set.begin(); set_it != set.end(); ++set_it) {
        auto it = k_hash.find(*set_it);
        if(it != k_hash.end()) {
            if(first) {
                copy(it->second.begin(), it->second.end(), back_inserter(saved));
            }
            else {
                set_intersection(it->second.begin(), it->second.end(), saved.begin(), saved.end(), back_inserter(holder), LogEntryPtrLess());
            }

        }
        if(!first) {
            holder.swap(saved);
            holder.clear();
        }
        first = false;

    }
    if(saved.empty()) {
        cout << "Keyword search: 0 entries found\n";
        return;
    }
    
    copy(saved.begin(), saved.end(), back_inserter(search_results));
    cout << "Keyword search: " << search_results.size() << " entries found\n";
}
void Logger::c_cmd() {
    string search;
    getline(cin, search);
    //Convert to lowercase and delete space (first char because of getline)
    lowercase(search);
    search.erase(0, 1);
    
    searched_yet = true;
    last_search = c;
    clear_search_results();
    auto it = c_hash.find(search);
    if(it != c_hash.end()) {
        search_results_c.push_back(it->second.begin());
        search_results_c.push_back(it->second.end());
        cout << "Category search: "
        << search_results_c[1] - search_results_c[0] << " entries found\n";
    }
    else {
        cout << "Category search: 0 entries found\n";
    }
    
}
void Logger::g_cmd() const {
    if(last_search == other) {
        if(search_results_2.empty()) {
            return;
        }
        for(auto it = search_results_2[0]; it != search_results_2[1]; ++it) {
            cout << it->entryID << "|" << ts_convert_back(it->timestamp)
            << "|" << it->category << "|" << it->message << "\n" ;
        }
    }
    else if(last_search == c) {
        if(search_results_c.empty()) {
            return;
        }
        for(auto it = search_results_c[0]; it != search_results_c[1]; ++it) {
            cout << (*it)->entryID << "|" << ts_convert_back((*it)->timestamp)
            << "|" << (*it)->category << "|" << (*it)->message << "\n" ;
        }
    }
    else {
        for(auto it = search_results.cbegin(); it != search_results.cend(); ++it) {
            cout << (*it)->entryID << "|" << ts_convert_back((*it)->timestamp)
            << "|" << (*it)->category << "|" << (*it)->message << "\n" ;
        }
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
    const LogEntry* begin = &master[excerpt_list[0]];
    cout << "0|" << begin->entryID << "|" << ts_convert_back(begin->timestamp)
    << "|" << begin->category << "|" << begin->message << "\n";

    cout << "...\n";

    const LogEntry* end = &master[excerpt_list.back()];
    cout << excerpt_list.size() - 1 << "|"
    << end->entryID << "|" << ts_convert_back(end->timestamp)
    << "|" << end->category << "|" << end->message << "\n";
}

long long int Logger::ts_convert(string ts) const {
    ts.erase(remove(ts.begin(), ts.end(), ':'), ts.end());
    long long int ts_final = stoll(ts, nullptr, 10);
    return ts_final;
}
void Logger::clear_search_results() {
    search_results.clear();
    search_results_c.clear();
    search_results_2.clear();
}
void Logger::initializer() {
    std::sort(master.begin(), master.end(), LogEntryLess());
    for(auto it = master.cbegin(); it != master.cend(); ++it) {
        string cat = it->lc_category;
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
        //For a command
        unsigned int index = (unsigned int)(&(*it) - &master[0]);
        id_holder.resize(master.size());
        id_holder[(size_t)it->entryID] = index;
        
    }
    
}
void Logger::unordered_set_helper(string::iterator start, string::iterator end,
                                  unordered_set<string> &set) const {
    if(start == end) {
        return;
    }
    start = find_if(start, end, (int(*)(int))isalnum);
    string::iterator it = find_if_not(start, end, (int(*)(int))isalnum);
    if(start != it) {
        set.emplace(string(start, it));
    }
    unordered_set_helper(it, end, set);
    
}
void Logger::vector_helper(string::iterator start, string::iterator end,
                                  vector<string> &set) const {
    if(start == end) {
        return;
    }
    start = find_if(start, end, (int(*)(int))isalnum);
    string::iterator it = find_if_not(start, end, (int(*)(int))isalnum);
    if(start != it) {
        set.emplace_back(string(start, it));
    }
     vector_helper(it, end, set);
    
}

void uppercase(string &s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
}
void lowercase(string &s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}
