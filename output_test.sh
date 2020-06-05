#!/bin/bash

#  output_test.sh
#  p3
#
#  Created by Connor Turco on 6/5/20.
#  Copyright © 2020 Connor Turco. All rights reserved.

make logman
echo ============================ Test 1 =====================================
echo -------------------------------------------------------------------------
./logman_debug test-1-log.txt < test-1-cmds.txt > testy.txt
sdiff testy.txt test1correct.txt
echo -------------------------------------------------------------------------
echo |
echo |
echo ============================ Spec Test ===================================
echo -------------------------------------------------------------------------
./logman_debug spec-test-log.txt < spec-test-cmds.txt > testy.txt
sdiff testy.txt spec-test-out.txt
echo -------------------------------------------------------------------------
echo |
echo |
echo ============================ Sample All ===================================
echo -------------------------------------------------------------------------
./logman_debug sample-log.txt < sample-all-cmds.txt > testy.txt
diff testy.txt sample-all-out.txt
echo -------------------------------------------------------------------------
make clean


