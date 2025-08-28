cmake_minimum_required(VERSION 3.10)

# MinGW derleyicisini kullanmak için ayarlar
set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")

project(ball_animation)

# C++11 standardını kullan
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Derleme türünü ayarla (Debug veya Release)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# SFML kütüphanesini bul
# Not: SFML yüklü değilse, bu satırları yorum yapabilir ve 
# manuel olarak SFML'yi bağlayabilirsiniz
find_package(SFML 2.5 COMPONENTS graphics window system)

# Kaynak dosyaları ekle
add_executable(ball_animation ball_animation.cpp)

# SFML kütüphanelerini bağla
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

# Derlenen uygulama için çalışma dizinini ayarla
set_target_properties(ball_animation PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
