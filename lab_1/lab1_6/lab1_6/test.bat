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

rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������(�������� � �������������� ����� ���������)
rem echo test3
rem %PROGRAM% test-data\testFile.txt > nul
rem fc.exe "%TEMP%\result.txt" test-data\testResultFile.txt > nul
rem if ERRORLEVEL 1 goto err

rem ��� ������� � ����������� ����������� ��������� ��������� ��� ��������(�������� � �������������� ����� �� ���������)
rem echo test4
rem %PROGRAM% test-data\testFile.txt > "%TEMP%\result.txt" 
rem fc.exe "%TEMP%\result.txt" test-data\testResultFile1.txt > nul
rem if NOT ERRORLEVEL 1 goto err


echo OK
exit 0

:err
echo Program testing failed
exit 1