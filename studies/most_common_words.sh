#!/bin/bash
# Program from https://cs61.seas.harvard.edu/site/2021/ProcessControl/
# Call this script as, e.g., “./mostcommonwords.sh 1000 < file”

tr -cs A-Za-z '\n' |
tr A-Z a-z |
sort |
uniq -c |
sort -rn |
#wc -l
head -n $1