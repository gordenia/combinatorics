rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамл€ющих кавычек (если они были)

rem ѕеременна€ PROGRAM будет хранить первый аргумент командной строки заключЄнный в кавычки
set PROGRAM="%~1"

rem ѕри запуске без параметров ожидаетс€ ненулевой код возврата
echo test1
%PROGRAM% >nul
if NOT ERRORLEVEL 1 goto err

rem ѕри неудачном открытии файла ожидаетс€ ненулевой код возврата
echo test2
%PROGRAM% fileNotFound.txt >nul
if NOT ERRORLEVEL 1 goto err

rem ѕри запуске с правильными параметрами ожидаетс€ нулевой код возврата(исходный и результирующий файлы совпадают)
rem echo test3
rem %PROGRAM% test-data\testFile.txt > nul
rem fc.exe "%TEMP%\result.txt" test-data\testResultFile.txt > nul
rem if ERRORLEVEL 1 goto err

rem ѕри запуске с правильными параметрами ожидаетс€ ненулевой код возврата(исходный и результирующий файлы не совпадают)
rem echo test4
rem %PROGRAM% test-data\testFile.txt > "%TEMP%\result.txt" 
rem fc.exe "%TEMP%\result.txt" test-data\testResultFile1.txt > nul
rem if NOT ERRORLEVEL 1 goto err


echo OK
exit 0

:err
echo Program testing failed
exit 1