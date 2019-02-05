#!/bin/bash
clear
echo compiling executable
g++ -Wall -Werror -std=c++17 -g *.cpp *.h -o lab2
echo running test21
./lab2 in21.txt out_test21.txt
echo running test22
./lab2 in22.txt out_test22.txt
echo running test23
./lab2 in23.txt out_test23.txt
echo running test24
./lab2 in24.txt out_test24.txt
echo running test25
./lab2 in25.txt out_test25.txt
echo running test26
./lab2 in26.txt out_test26.txt
echo running test27
./lab2 in27.txt out_test27.txt
echo running test28
./lab2 in28.txt out_test28.txt
echo running test29
./lab2 in29.txt out_test29.txt
echo running test61
./lab2 in61.txt out_test61.txt
echo running test62
./lab2 in62.txt out_test62.txt
echo checking diff for test21
colordiff out21.txt out_test21.txt
echo checking diff for test22
colordiff out22.txt out_test22.txt
echo checking diff for test23
colordiff out23.txt out_test23.txt
echo checking diff for test24
colordiff out24.txt out_test24.txt
echo checking diff for test25
colordiff out25.txt out_test25.txt
echo checking diff for test26
colordiff out26.txt out_test26.txt
echo checking diff for test27
colordiff out27.txt out_test27.txt
echo checking diff for test28
colordiff out28.txt out_test28.txt
echo checking diff for test29
colordiff out29.txt out_test29.txt
echo checking diff for test61
colordiff out61.txt out_test61.txt
echo checking diff for test62
colordiff out62.txt out_test62.txt
