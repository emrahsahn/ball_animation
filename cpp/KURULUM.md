# MinGW ve SFML Kurulum Talimatları

## 1. MinGW (GCC Derleyicisi) Kurulumu

1. [MinGW-w64 indirme sayfasına](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/) gidin
2. En son x86_64 sürümünü indirin (örneğin: `x86_64-posix-seh`)
3. İndirilen arşivi `C:\` dizinine çıkartın ve klasörün adını `mingw64` olarak değiştirin
4. Sistem ortam değişkenlerinize (PATH) `C:\mingw64\bin` dizinini ekleyin:
   - Windows arama çubuğuna "Ortam Değişkenleri" yazın
   - "Sistem ortam değişkenlerini düzenle"yi seçin
   - "Ortam Değişkenleri" butonuna tıklayın
   - "Sistem değişkenleri" altında "Path" değişkenini bulun ve "Düzenle"ye tıklayın
   - "Yeni" butonuna tıklayın ve `C:\mingw64\bin` dizinini ekleyin
   - "Tamam" butonlarına tıklayarak tüm pencereleri kapatın
5. Yeni bir PowerShell veya Komut İstemi açın ve `g++ --version` komutunu çalıştırarak kurulumu doğrulayın

## 2. SFML Kütüphanesi Kurulumu

1. [SFML indirme sayfasına](https://www.sfml-dev.org/download.php) gidin
2. MinGW ile uyumlu SFML sürümünü indirin (GCC MinGW seçeneği)
3. İndirilen arşivi `C:\` dizinine çıkartın ve klasörün adını `SFML` olarak değiştirin
4. Dll dosyalarını projenize kopyalayın ya da sistem PATH'ine ekleyin

## 3. CMake ile Derleme

Derleyici ve SFML kurulumlarını tamamladıktan sonra, build.bat dosyasını düzenleyin:

```batch
@echo off
echo Ball Animation C++ Projesi Derleme Scripti
echo ---------------------------------------------

rem Build klasörü oluştur
if not exist build mkdir build
cd build

rem CMake ile projeyi yapılandır (SFML yolunu belirt)
echo CMake ile projeyi yapılandırılıyor...
cmake .. -G "MinGW Makefiles" -DSFML_DIR=C:/SFML/lib/cmake/SFML

rem Projeyi derle
echo Proje derleniyor...
cmake --build . --config Release

rem Başarılı ise bilgi ver
if %ERRORLEVEL% == 0 (
    echo Derleme başarılı!
    echo Programı çalıştırmak için: build\bin\ball_animation.exe
    
    rem DLL dosyalarını kopyala
    echo SFML DLL dosyaları kopyalanıyor...
    copy C:\SFML\bin\*.dll bin\
) else (
    echo Derleme sırasında bir hata oluştu!
)

cd ..
pause
```

## 4. Font Dosyası

Programın font hatası vermemesi için:
1. Windows'un Fonts klasöründen (`C:\Windows\Fonts`) Arial fontunu (`arial.ttf`) kopyalayın
2. Bu dosyayı projenizin `cpp` klasörüne yapıştırın
