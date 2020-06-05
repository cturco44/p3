#!/bin/bash

#  Script.sh
#  p3
#
#  Created by Connor Turco on 6/5/20.
#  Copyright © 2020 Connor Turco. All rights reserved.

make debug
perf record -F 1000 --call-graph dwarf -e cycles:u ./logman_debug < spec-test-log.txt
perf report

