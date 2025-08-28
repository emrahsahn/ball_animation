@echo off
echo Ball Animation Kurulum ve Derleme
echo ---------------------------------

rem Font dosyasını kopyala
echo Font dosyası kontrol ediliyor...
if not exist arial.ttf (
  echo Font dosyası kopyalanıyor...
  copy "C:\Windows\Fonts\arial.ttf" . >nul 2>&1
  if not exist arial.ttf (
    echo Uyarı: Font dosyası kopyalanamadı!
  ) else (
    echo Font dosyası kopyalandı.
  )
) else (
  echo Font dosyası zaten mevcut.
)

rem SFML kontrolü
set SFML_PATH=C:\SFML
if not exist %SFML_PATH% (
  echo SFML dizini bulunamadı: %SFML_PATH%
  echo Lütfen SFML'i indirip C:\SFML dizinine çıkartın veya
  echo derle.bat dosyasını düzenleyerek SFML_PATH değişkenini güncelleyin.
  goto :EOF
)

rem Derle
call derle.bat

rem Derleme başarılı ise çalıştır
if exist bin\ball_animation.exe (
  echo Program çalıştırılıyor...
  start bin\ball_animation.exe
)

exit
