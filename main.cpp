// Project Identifier: 01BD41C3BF016AD7E8B6F837DF18926EC3E83350
//  main.cpp
//  p3
//
//  Created by Connor Turco on 6/3/20.
//  Copyright © 2020 Connor Turco. All rights reserved.
//

#include <iostream>
#include "xcode_redirect.hpp"
#include <string>
#include <fstream>
#include <algorithm>
#include "logger.h"

using namespace std;

long long int ts_convert(string ts) {
    ts.erase(remove(ts.begin(), ts.end(), ':'), ts.end());
    long long int ts_final = stoll(ts, nullptr, 10);
    return ts_final;
}

void read_in(int argc, char* argv[], Logger &main_log) {
    string filename;
    for(int i = 0; i < argc; ++i) {
        string holder = string(argv[i]);
        if(holder == "-h" || holder == "--help") {
            cout << "Log filename is only command line argument\n";
            exit(0);
        }
        else {
            filename = holder;
        }
    }
    
    ifstream fin;
    fin.open(filename);
    if(!fin.is_open()) {
        cerr << "Open Failed\n";
        exit(1);
    }
    
    int count = 0;
    string ts, cat, msg;
    while(getline(fin, ts, '|')) {
        getline(fin, cat, '|');
        getline(fin, msg);
        main_log.push_master(ts_convert(ts), cat, msg, count);
        ++count;
    }
    cout << count << " entries read\n";

    
}
int main(int argc, char * argv[]) {
    std::ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    
    Logger main_log;
    read_in(argc, argv, main_log);
    main_log.initializer();
    
    char cmd;
    do {
        cout << "% ";
        cin >> cmd;
        main_log.process_cmd(cmd);
    } while (cmd != 'q');

    return 0;
}
