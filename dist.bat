echo off

REM batch file for distribution of UPLOADFILE
REM $Header: /comm/uploadFile/dist.bat 3     09/05/20 2:44 tsupo $

chmod -R +w dist

rm -Rf dist\src

mkdir dist\src
mkdir dist\src\cocoUpple
mkdir dist\src\cocoUpple\res
mkdir dist\src\inc
mkdir dist\src\lib

copy *.c dist\src
copy cocoUpple\cocoUpple.rc dist\src\cocoUpple
copy cocoUpple\*.cpp        dist\src\cocoUpple
copy cocoUpple\*.h          dist\src\cocoUpple
copy cocoUpple\res\*.ico dist\src\cocoUpple\res
copy cocoUpple\res\*.rc2 dist\src\cocoUpple\res
copy cocoUpple\res\*.cur dist\src\cocoUpple\res
copy cocoUpple\cocoUpple.exe.manifest dist
copy cocoUpple\Release\cocoUpple.exe  dist
copy readme.txt                       dist
copy Release\uploadFile.exe           dist
copy Release\xmlRPC.dll               dist

copy *.dsw dist\src\
copy *.dsp dist\src
REM copy cocoUpple\*.aps dist\src\cocoUpple
REM copy cocoUpple\*.clw dist\src\cocoUpple
copy cocoUpple\*.dsp dist\src\cocoUpple

copy ..\xmlRPC\xmlRPC.h dist\src\inc
copy ..\xmlRPC\Release\xmlRPC.lib dist\src\lib
