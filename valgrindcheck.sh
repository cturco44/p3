#!/bin/bash

#  valgrindcheck.sh
#  p3
#
#  Created by Connor Turco on 6/5/20.
#  Copyright © 2020 Connor Turco. All rights reserved.

make debug
echo ============================ Test 1 =====================================
echo -------------------------------------------------------------------------
valgrind ./logman_debug test-1-log.txt < test-1-cmds.txt
echo -------------------------------------------------------------------------
echo |
echo |
echo ============================ Spec Test ===================================
echo -------------------------------------------------------------------------
valgrind ./logman_debug spec-test-log.txt < spec-test-cmds.txt
echo -------------------------------------------------------------------------
echo |
echo |
echo ============================ Sample All ===================================
echo -------------------------------------------------------------------------
valgrind ./logman_debug sample-log.txt < sample-all-cmds.txt
echo -------------------------------------------------------------------------
make clean
