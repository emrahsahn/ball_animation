# Ball Animation (C++ Versiyonu)

Bu proje, bir Python Tkinter uygulamasının C++ ve SFML kütüphanesi kullanılarak yapılmış versiyonudur.

## İçindekiler

1. [Gereksinimler](#gereksinimler)
2. [MinGW Kurulumu](#mingw-kurulumu)
3. [SFML Kurulumu](#sfml-kurulumu)
4. [Projeyi Derleme](#projeyi-derleme)
5. [Kullanım](#kullanım)
6. [Sorun Giderme](#sorun-giderme)

## Gereksinimler

Uygulamayı derlemek ve çalıştırmak için aşağıdaki bileşenlere ihtiyacınız vardır:

- **MinGW C++ Derleyicisi** (GCC)
- **SFML Kütüphanesi** (2.5 veya üzeri sürüm)
- **Arial Font Dosyası** (Windows Fonts klasöründen)
- **CMake** (isteğe bağlı, 3.10 veya üzeri)

## MinGW Kurulumu

### 1. MinGW İndirme ve Kurulum

1. [MinGW-w64 indirme sayfasına](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/) gidin.
2. En son sürümü indirin (örneğin: x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z).
3. İndirdiğiniz arşivi `C:\MinGW` dizinine çıkartın.
   - Eğer farklı bir dizine çıkartırsanız, `derle.bat` dosyasındaki yolu güncellemeniz gerekecektir.

### 2. PATH Ayarları

MinGW'nin `bin` klasörünü sistem PATH değişkeninize ekleyin:

1. Windows arama çubuğuna "Ortam Değişkenleri" yazın ve "Sistem ortam değişkenlerini düzenle"yi seçin.
2. "Ortam Değişkenleri" butonuna tıklayın.
3. "Sistem değişkenleri" altında "Path" değişkenini bulun ve "Düzenle"ye tıklayın.
4. "Yeni" butonuna tıklayın ve `C:\MinGW\bin` dizinini ekleyin.
5. "Tamam" butonlarına tıklayarak tüm pencereleri kapatın.

### 3. Kurulumu Doğrulama

Yeni bir PowerShell veya Komut İstemi açın ve aşağıdaki komutu çalıştırın:

```
g++ --version
```

Bu komut, GCC derleyicisinin sürüm bilgisini göstermelidir. Eğer bir hata alırsanız, PATH ayarlarını kontrol edin.

## SFML Kurulumu

### 1. SFML İndirme

1. [SFML indirme sayfasına](https://www.sfml-dev.org/download.php) gidin.
2. MinGW derleyicinizle uyumlu SFML sürümünü indirin:
   - MinGW 32-bit için, GCC MinGW 32-bit seçeneğini indirin.
   - MinGW 64-bit için, GCC MinGW 64-bit seçeneğini indirin.

### 2. SFML Kurulum

1. İndirdiğiniz zip dosyasını `C:\SFML` klasörüne çıkartın.
   - Eğer farklı bir dizine çıkartırsanız, `derle.bat` dosyasındaki `SFML_PATH` değişkenini güncellemeniz gerekecektir.

2. SFML dizininizin şu klasörleri içerdiğinden emin olun:
   - `bin` (DLL dosyaları)
   - `include` (header dosyaları)
   - `lib` (library dosyaları)

### 3. Font Dosyasını Kopyalama

1. `font_kopyala.bat` dosyasını çalıştırarak Windows Fonts klasöründen arial.ttf dosyasını otomatik olarak kopyalayabilirsiniz.
2. Veya manuel olarak `C:\Windows\Fonts` klasöründen `arial.ttf` dosyasını proje klasörüne kopyalayabilirsiniz.

## Projeyi Derleme

Projeyi derlemek için üç farklı yöntem sunulmuştur:

### 1. Doğrudan G++ ile Derleme (Önerilen)

1. `cpp` klasörüne gidin.
2. `derle.bat` dosyasını çalıştırın.
3. Derleme başarılı olursa, `bin` klasöründe `ball_animation.exe` dosyası oluşturulacaktır.

Bu yöntem, `derle.bat` dosyasındaki aşağıdaki komutları kullanır:

```bat
g++ ball_animation.cpp -o bin/ball_animation.exe ^
  -I%SFML_PATH%/include ^
  -L%SFML_PATH%/lib ^
  -lsfml-graphics -lsfml-window -lsfml-system
```

### 2. CMake ile Derleme

1. `cpp` klasörüne gidin.
2. `build.bat` dosyasını çalıştırın.
3. Derleme başarılı olursa, `build\bin` klasöründe `ball_animation.exe` dosyası oluşturulacaktır.

Windows için CMake adımları:
```
mkdir build
cd build
cmake .. -G "MinGW Makefiles"  # MinGW kullanıyorsanız
cmake --build . --config Release
```

Linux için CMake adımları:
```
mkdir build
cd build
cmake ..
make
```

### 3. Tek Adımda Kurulum ve Çalıştırma

Tüm adımları otomatik olarak gerçekleştirmek için:

1. `cpp` klasörüne gidin.
2. `kurulum_ve_calistir.bat` dosyasını çalıştırın.
3. Bu betik, font dosyasını kontrol eder, SFML'i kontrol eder, projeyi derler ve başarılı olursa çalıştırır.

## Kullanım

Uygulama çalıştırıldığında, aşağıdaki kontrolleri kullanabilirsiniz:

- **Start**: Animasyonu başlatır
- **Stop**: Animasyonu durdurur
- **Reset**: Tüm topları temizler
- **Speedup**: Topların hızını artırır
- **Renk Butonları**: Kırmızı, mavi ve sarı renk seçimleri
- **Boyut Butonları**: Farklı boyutlarda top ekleme

## Sorun Giderme

### SFML Header Dosyaları Bulunamadı

Eğer `SFML/Graphics.hpp: No such file or directory` hatası alırsanız:

1. SFML'in doğru şekilde kurulu olduğundan emin olun.
2. `derle.bat` dosyasını açın ve `SFML_PATH` değişkeninin SFML'in kurulu olduğu dizini gösterdiğinden emin olun.

### Linker Hataları

Eğer `undefined reference to 'sf::***'` gibi hatalar alırsanız:

1. MinGW ve SFML sürümlerinin uyumlu olduğundan emin olun.
2. 32-bit MinGW için 32-bit SFML, 64-bit MinGW için 64-bit SFML kullanın.
3. Derleme komutunda kütüphane linklerinin doğru olduğundan emin olun.

### Çalışma Zamanı Hataları

Program çalıştırıldığında DLL hatası alırsanız:

1. SFML DLL dosyalarının uygulama ile aynı klasörde olduğundan emin olun.
2. `bin` klasöründe aşağıdaki DLL dosyalarının bulunduğunu kontrol edin:
   - sfml-graphics-2.dll
   - sfml-window-2.dll
   - sfml-system-2.dll

### Font Hatası

Eğer program "Font yüklenemedi" hatası verirse:

1. `arial.ttf` dosyasının program ile aynı dizinde olduğundan emin olun.
2. `font_kopyala.bat` dosyasını çalıştırarak font dosyasını tekrar kopyalamayı deneyin.
