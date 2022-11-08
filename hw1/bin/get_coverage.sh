#!/usr/bin/env bash

./runUnitTests

lcov -t "report" -o report.info -c -d ../build/CMakeFiles/project1_lib.dir

lcov --remove report.info -o report_filtered.info \
    '/usr/include/*' \
    'include/gtest' \

genhtml -o report report_filtered.info

open report/index.html

rm report_filtered.info report.info
rm DFA_test.doa