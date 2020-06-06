#!/bin/bash

#  output_test.sh
#  p3
#
#  Created by Connor Turco on 6/5/20.
#  Copyright © 2020 Connor Turco. All rights reserved.

make logman
echo ============================ Test 1 =====================================
echo -------------------------------------------------------------------------
./logman test-1-log.txt < test-1-cmds.txt > testy.txt
sdiff testy.txt test1correct.txt
echo -------------------------------------------------------------------------
echo |
echo |
echo ============================ Test 5 =====================================
echo -------------------------------------------------------------------------
./logman test-5-log.txt < test-5-cmds.txt > testy.txt
sdiff testy.txt test5correct.txt
echo -------------------------------------------------------------------------
echo |
echo |
echo ============================ Test 6 =====================================
echo -------------------------------------------------------------------------
./logman test-6-log.txt < test-6-cmds.txt > testy.txt
sdiff testy.txt test6correct.txt
echo -------------------------------------------------------------------------
echo |
echo |
echo ============================ Spec Test ===================================
echo -------------------------------------------------------------------------
./logman spec-test-log.txt < spec-test-cmds.txt > testy.txt
sdiff testy.txt spec-test-out.txt
echo -------------------------------------------------------------------------


