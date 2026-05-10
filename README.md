Veri Yapıları Dönem Sonu Projesi

Bu proje, modüler C programlama mimarisi kullanılarak geliştirilmiştir ve derleme işlemlerinin kolaylaştırılması amacıyla bir Makefile içermektedir. Aşağıdaki adımları takip ederek projeyi kendi bilgisayarınızda derleyebilir ve çalıştırabilirsiniz.

#Gereksinimler

Projeyi çalıştırabilmek için sisteminizde aşağıdaki araçların kurulu olması gerekmektedir:

C Derleyicisi (GCC önerilir)
make aracı

make aracı sisteminizde kurulu değilse:

Windows için: MinGW veya MSYS2 üzerinden kurulabilir.
Linux/macOS için: Paket yöneticileri (apt, brew, pacman vb.) kullanılarak yüklenebilir.
Kurulum ve Çalıştırma
1. Projeyi Klonlayın

Terminal veya komut satırını açarak aşağıdaki komutları çalıştırın:

git clone https://github.com/Cinargenc/veri_yapilari_donem_sonu_projesi
cd veri_yapilari_donem_sonu_projesi
2. Projeyi Derleyin

Projede birden fazla .c ve .h dosyası bulunduğundan dolayı derleme işlemleri Makefile üzerinden gerçekleştirilmektedir.

Aşağıdaki komutu çalıştırmanız yeterlidir:

make

Bu işlem sonucunda tüm modüller derlenecek ve çalıştırılabilir ana program oluşturulacaktır.

Proje; Windows, Linux ve macOS (ARM/M serisi işlemciler dahil) sistemlerinde çalışabilecek şekilde tasarlanmıştır.

3. Programı Çalıştırın

Derleme işlemi başarıyla tamamlandıktan sonra programı aşağıdaki komutlarla çalıştırabilirsiniz.

Windows
gorev_sistemi.exe
Linux / macOS
./gorev_sistemi
Proje Yapısı

Proje, modüler programlama yaklaşımıyla geliştirilmiştir. Her veri yapısı ve sistem bileşeni ayrı kaynak dosyalarında tanımlanmıştır. Bu yapı sayesinde:

Kod okunabilirliği artırılmış,
Bakım ve geliştirme süreçleri kolaylaştırılmış,
Platform bağımsız derleme desteği sağlanmıştır.
Not

Çalıştırılabilir dosyanın adı kullanılan işletim sistemine göre farklılık gösterebilir. Eğer farklı bir isim oluşursa Makefile içeriğini kontrol edebilirsiniz. adı Makefile konfigürasyonunuza göre farklılık gösterebilir.)

4. Temizlik İşlemleri (Opsiyonel):
Kodlar üzerinde değişiklik yapmak isterseniz veya sistemi baştan derlemeniz gerekirse, daha önce oluşturulmuş derleme kalıntılarını (object dosyalarını) temizlemek için şu komutu kullanabilirsiniz:

Bash
make clean
