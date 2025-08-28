@echo off
echo Ball Animation C++ Projesi Derleme Scripti
echo ---------------------------------------------

rem MinGW'nin PATH'e eklenmesi
set PATH=C:\MinGW\bin;%PATH%

rem Build klasörü oluştur
if not exist build mkdir build
cd build

rem CMake ile projeyi yapılandır
echo CMake ile projeyi yapılandırılıyor...
cmake .. -G "MinGW Makefiles"

rem Projeyi derle
echo Proje derleniyor...
mingw32-make

rem Başarılı ise bilgi ver
if %ERRORLEVEL% == 0 (
    echo Derleme başarılı!
    echo Programı çalıştırmak için: bin\ball_animation.exe
    
    rem arial.ttf dosyasını bin klasörüne kopyala
    echo Font dosyası kopyalanıyor...
    if exist ..\arial.ttf (
        copy ..\arial.ttf bin\
    ) else (
        echo Uyarı: arial.ttf dosyası bulunamadı.
        echo Windows Fonts klasöründen (C:\Windows\Fonts) arial.ttf dosyasını cpp klasörüne kopyalayın.
    )
    
    rem SFML DLL dosyalarını kontrol et
    if exist bin\sfml-graphics-2.dll (
        echo SFML DLL dosyaları hazır.
    ) else (
        echo Uyarı: SFML DLL dosyaları bulunamadı.
        echo SFML_DIR değişkenini CMakeLists.txt dosyasında düzenlemeniz gerekebilir.
    )
) else (
    echo Derleme sırasında bir hata oluştu!
)

cd ..
pause
