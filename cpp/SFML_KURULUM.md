# SFML Kurulumu

Bu belge, SFML kütüphanesinin kurulumu ve projeye entegrasyonu hakkında bilgi verir.

## SFML İndirme ve Kurulum

1. [SFML'in resmi web sitesine](https://www.sfml-dev.org/download.php) gidin.
2. MinGW derleyicinize uygun SFML sürümünü indirin:
   - MinGW için, "GCC MinGW" başlığı altındaki sürümü seçin.
   - İndirdiğiniz SFML sürümü ve MinGW sürümünüzün uyumlu olduğundan emin olun.

3. İndirdiğiniz zip dosyasını çıkartın (örneğin: `C:\SFML` dizinine).

## CMakeLists.txt Dosyasında SFML Yolunu Ayarlama

CMakeLists.txt dosyasında SFML için yolu ayarlamanız gerekir. Bu dosya halihazırda şu yapılandırmayı içerir:

```cmake
if(SFML_FOUND)
    target_link_libraries(ball_animation sfml-graphics sfml-window sfml-system)
else()
    # Manuel olarak SFML'yi bağla (SFML yolunu düzenleyin)
    # SFML klasörünüzün yolunu buraya yazın (örn. C:/SFML)
    set(SFML_DIR "C:/SFML")
    set(SFML_INCLUDE_DIR "${SFML_DIR}/include")
    set(SFML_LIB_DIR "${SFML_DIR}/lib")
    
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(ball_animation 
        ${SFML_LIB_DIR}/libsfml-graphics.a
        ${SFML_LIB_DIR}/libsfml-window.a
        ${SFML_LIB_DIR}/libsfml-system.a
    )
    
    # SFML DLL'lerini kopyala
    file(GLOB SFML_DLLS "${SFML_DIR}/bin/*.dll")
    file(COPY ${SFML_DLLS} DESTINATION "${CMAKE_BINARY_DIR}/bin")
endif()
```

Eğer SFML'i farklı bir dizine kurduysanız, `set(SFML_DIR "C:/SFML")` satırını kendi SFML dizininizle değiştirin.

## SFML DLL Dosyaları

Uygulamayı çalıştırmak için SFML DLL dosyalarının uygulama ile aynı dizinde olması gerekir. CMakeLists.txt dosyası, derlenmiş uygulamanın bulunduğu bin klasörüne DLL dosyalarını otomatik olarak kopyalamayı dener.

Eğer bu otomatik kopyalama çalışmazsa, şu DLL dosyalarını manuel olarak uygulamanızın bin klasörüne kopyalamanız gerekir:

- sfml-graphics-2.dll
- sfml-window-2.dll
- sfml-system-2.dll

Bu DLL dosyaları SFML kurulum dizininizdeki bin klasöründe bulunur (örn. C:\SFML\bin).

## Sorun Giderme

1. **CMake SFML'i bulamıyor**: CMakeLists.txt dosyasındaki SFML_DIR değişkenini doğru yola ayarladığınızdan emin olun.

2. **Derleme hataları**: MinGW sürümünüz ve SFML sürümünüzün uyumlu olduğundan emin olun.

3. **Çalışma zamanı hataları**: Uygulamanızın bin klasöründe gerekli DLL dosyalarının bulunduğundan emin olun.

4. **Font hatası**: Programın font hatası vermemesi için arial.ttf dosyasını bin klasörüne kopyalayın.
