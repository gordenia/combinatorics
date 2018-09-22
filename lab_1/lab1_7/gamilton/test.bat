rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ��� ������� ��� ���������� ��������� ��������� ��� ��������
echo test1
%PROGRAM% >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ��������� �������� ����� ��������� ��������� ��� ��������
echo test2
%PROGRAM% fileNotFound.txt >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ��������� ��� ��������(������ ����)
echo test3
%PROGRAM% test-data\emptyFile.txt >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ��������� ��� ��������(������������ ������ � �����)
echo test4
%PROGRAM% test-data\fileErr1.txt >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ��������� ��� ��������(������������ ������ � �����)
echo test5
%PROGRAM% test-data\fileErr2.txt >nul
if NOT ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������(�������� � �������������� ����� ���������)
echo test6
%PROGRAM% test-data\matrix1.txt> "%TEMP%\Result1.txt" 
fc.exe "%TEMP%\Result1.txt" test-data\result1.txt > nul
if ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������(�������� � �������������� ����� ���������)
echo test7
%PROGRAM% test-data\matrix2.txt> "%TEMP%\Result2.txt" 
fc.exe "%TEMP%\Result2.txt" test-data\result2.txt > nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1