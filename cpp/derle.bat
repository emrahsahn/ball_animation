@echo off
echo Ball Animation Derleme Betigi
echo -------------------------------

rem MinGW bin dizinini PATH'e ekle
set PATH=C:\MinGW\bin;%PATH%

rem SFML yolunu belirle
set SFML_PATH=C:\SFML

rem SFML yolunu kontrol et
if not exist "%SFML_PATH%" (
    echo SFML bulunamadi! Lutfen SFML'i indirip kurun.
    echo SFML'i https://www.sfml-dev.org/download.php adresinden indirip %SFML_PATH% dizinine cikartin.
    goto :EOF
)

echo SFML dizini: %SFML_PATH%

rem Dizinleri olustur
if not exist bin mkdir bin

rem Font dosyasini kontrol et
if not exist arial.ttf (
    echo Font dosyasi kopyalaniyor...
    copy "C:\Windows\Fonts\arial.ttf" . >nul 2>&1
    if not exist arial.ttf (
        echo Uyari: Font dosyasi kopyalanamadi!
    )
)

rem Derle
echo Derleniyor...
g++ ball_animation.cpp -o bin/ball_animation.exe -I"%SFML_PATH%/include" -L"%SFML_PATH%/lib" -lsfml-graphics -lsfml-window -lsfml-system

rem Derleme basarili mi kontrol et
if %ERRORLEVEL% == 0 (
  echo Derleme basarili!
  
  rem DLL dosyalarini kopyala
  echo DLL dosyalari kopyalaniyor...
  copy "%SFML_PATH%\bin\*.dll" bin\
  
  rem Font dosyasini kopyala
  if exist arial.ttf (
    copy arial.ttf bin\
  ) else (
    echo Uyari: arial.ttf dosyasi bulunamadi!
  )
  
  echo Program hazir! bin\ball_animation.exe dosyasini calistirabilirsiniz.
) else (
  echo Derleme sirasinda hata olustu!
  echo SFML yolu dogru ayarlandigindan emin olun: %SFML_PATH%
)

pause
