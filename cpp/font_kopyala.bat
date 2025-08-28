@echo off
echo Arial font dosyası kopyalanıyor...

rem Windows Font klasöründen arial.ttf dosyasını kopyala
copy "C:\Windows\Fonts\arial.ttf" .

if exist arial.ttf (
  echo Font dosyası başarıyla kopyalandı!
) else (
  echo Font dosyası kopyalanamadı! Lütfen manuel olarak C:\Windows\Fonts klasöründen arial.ttf dosyasını bu klasöre kopyalayın.
)

pause
