# Ball Animation SFML Kurulum Rehberi

Bu belge, Ball Animation C++ projesini derlemek ve çalıştırmak için SFML kütüphanesinin nasıl kurulacağını anlatır.

## 1. SFML Kütüphanesini İndirme

1. [SFML indirme sayfasına](https://www.sfml-dev.org/download.php) gidin.
2. MinGW için SFML sürümünü indirin (GCC MinGW seçeneği).
   - MinGW 32-bit kullanıyorsanız, 32-bit sürümünü indirin.
   - MinGW 64-bit kullanıyorsanız, 64-bit sürümünü indirin.

## 2. SFML Kütüphanesini Kurma

1. İndirdiğiniz zip dosyasını `C:\SFML` klasörüne çıkartın.
   - Farklı bir dizine çıkartırsanız, `derle.bat` dosyasındaki `SFML_PATH` değişkenini güncellemeniz gerekecektir.

## 3. Arial Font Dosyasını Bulma

1. Windows Fonts klasöründen (`C:\Windows\Fonts`) arial.ttf dosyasını kopyalayın.
2. Bu dosyayı cpp klasörüne yapıştırın.

## 4. Derleme ve Çalıştırma

1. `derle.bat` dosyasını çalıştırın.
2. Derleme başarılı olursa, `bin` klasöründe `ball_animation.exe` dosyası oluşacaktır.
3. Bu exe dosyasını çalıştırabilirsiniz.

## Sorun Giderme

### SFML header dosyaları bulunamadı hatası

`SFML/Graphics.hpp: No such file or directory` gibi bir hata alırsanız:
- SFML'in doğru dizine çıkartıldığından emin olun.
- `derle.bat` dosyasındaki `SFML_PATH` değişkenini SFML'in kurulu olduğu dizine ayarlayın.

### Linker hataları

`undefined reference to 'sf::***'` gibi hatalar alırsanız:
- MinGW ve SFML sürümlerinin uyumlu olduğundan emin olun.
- 32-bit MinGW için 32-bit SFML, 64-bit MinGW için 64-bit SFML kullanın.

### Çalışma zamanı hataları

Programı çalıştırdığınızda DLL hatası alırsanız:
- SFML DLL dosyalarının uygulama ile aynı klasörde olduğundan emin olun.
- `bin` klasöründe aşağıdaki DLL dosyalarının bulunduğunu kontrol edin:
  - sfml-graphics-2.dll
  - sfml-window-2.dll
  - sfml-system-2.dll
