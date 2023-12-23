@ECHO OFF
cd %1
%2.exe < %3.in > %3.out
fc.exe %3.out %3.ans
exit 0