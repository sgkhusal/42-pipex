#!/bin/bash

cd ..
git clone https://github.com/mariadaan/PIPEXaminator.git
cd PIPEXaminator
bash all_tests.sh

cd ..
#memory leak tester
git clone https://github.com/denisgodoy/pipex-tester
cd pipex-tester
make

cd ..
git clone git@github.com:Yoo0lh/pipex_tester_42.git 
cd pipex_tester_42/
./pipex_tester.sh m #mandatory
./pipex_tester.sh b #bonus multiple pipes - mudar nome do executável para pipex_bonus
./pipex_tester.sh h #bonus heredoc - mudar nome do executável para pipex_bonus
#./pipex_tester.sh a # all

cd ..
# esse tester tem algumas coisas para arrumar
##git clone https://github.com/HEADLIGHTER/pipexfasttest.git
##cd pipexfasttest && vim pipextest.sh
# edit PIPEXPATH --> ../, TESTPATH and OUTPATH
# remove "cd $PIPEXPATH && " line 10-14, 59, 64, 70, 75
#./pipextest.sh

#Test 3 - ok!!
#corrigir: ./pipexfasttest/infile ls -slslksdfow| wc -cmlw
#< pipexfasttest/infile ls -slslksdfow | wc -cmlw
#./pipex ./pipexfasttest/infile "ls -slslksdfow" "wc -cmlw" ./pipexfasttest/outs/out3

#Error 2 - ok!!
#./pipex ./pipexfasttest/infile "" "ls -abdsnj" ./pipexfasttest/outs/out6
#< pipexfasttest/infile "" | ls -abdsnj > pipexfasttest/outs/out6
