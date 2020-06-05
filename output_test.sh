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
make clean

