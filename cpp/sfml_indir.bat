@echo off
echo SFML Indirme ve Kurulum Betigi
echo ------------------------------

rem Indirme dizini
set DOWNLOAD_DIR=%TEMP%\sfml_download
set SFML_DIR=C:\SFML

rem Dizin kontrolu
if exist "%SFML_DIR%" (
    echo SFML zaten %SFML_DIR% dizininde kurulu gorunuyor.
    choice /C YN /M "Mevcut kurulumu silip yeniden indirmek istiyor musunuz?"
    if errorlevel 2 goto :EOF
    rd /s /q "%SFML_DIR%"
)

rem Gecici dizin olustur
if not exist "%DOWNLOAD_DIR%" mkdir "%DOWNLOAD_DIR%"

echo SFML indiriliyor...
echo NOT: Bu betik PowerShell kullanarak SFML'i indirir.

rem PowerShell ile SFML indirme
powershell -Command "& {Add-Type -AssemblyName System.IO.Compression.FileSystem; [Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12; Invoke-WebRequest -Uri 'https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip' -OutFile '%DOWNLOAD_DIR%\sfml.zip'; [System.IO.Compression.ZipFile]::ExtractToDirectory('%DOWNLOAD_DIR%\sfml.zip', '%DOWNLOAD_DIR%')}"

if %ERRORLEVEL% NEQ 0 (
    echo Indirme veya cikarma isleminde hata olustu!
    goto :cleanup
)

echo SFML C:\SFML dizinine tasiniyor...
xcopy /E /I /Y "%DOWNLOAD_DIR%\SFML-2.5.1" "%SFML_DIR%"

echo Arial fontunu kopyalaniyor...
copy "C:\Windows\Fonts\arial.ttf" .

echo Temizlik yapiliyor...
:cleanup
rd /s /q "%DOWNLOAD_DIR%"

echo SFML kurulumu tamamlandi!
echo Simdi derle.bat dosyasini calistirabilirsiniz.

pause
