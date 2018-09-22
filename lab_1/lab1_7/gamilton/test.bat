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

rem ѕри запуске с правильными параметрами ожидаетс€ ненулевой код возврата(пустой файл)
echo test3
%PROGRAM% test-data\emptyFile.txt >nul
if NOT ERRORLEVEL 1 goto err

rem ѕри запуске с правильными параметрами ожидаетс€ ненулевой код возврата(некорректные данные в файле)
echo test4
%PROGRAM% test-data\fileErr1.txt >nul
if NOT ERRORLEVEL 1 goto err

rem ѕри запуске с правильными параметрами ожидаетс€ ненулевой код возврата(некорректные данные в файле)
echo test5
%PROGRAM% test-data\fileErr2.txt >nul
if NOT ERRORLEVEL 1 goto err

rem ѕри запуске с правильными параметрами ожидаетс€ нулевой код возврата(исходный и результирующий файлы совпадают)
echo test6
%PROGRAM% test-data\matrix1.txt> "%TEMP%\Result1.txt" 
fc.exe "%TEMP%\Result1.txt" test-data\result1.txt > nul
if ERRORLEVEL 1 goto err

rem ѕри запуске с правильными параметрами ожидаетс€ нулевой код возврата(исходный и результирующий файлы совпадают)
echo test7
%PROGRAM% test-data\matrix2.txt> "%TEMP%\Result2.txt" 
fc.exe "%TEMP%\Result2.txt" test-data\result2.txt > nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1