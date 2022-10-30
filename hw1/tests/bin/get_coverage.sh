#!/usr/bin/env bash

./test_auto

lcov -t "report" -o report.info -c -d ../build/CMakeFiles/test_auto.dir/

lcov --remove report.info -o report_filtered.info \
    '/usr/include/*' \
    '11' \
    '11/*' \

genhtml -o report report_filtered.info

open report/index.html
