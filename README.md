# veri_yapilari_donem_sonu_projesi

Proje tamamen modüler bir C mimarisiyle yazılmış olup, derleme işlemleri için bir Makefile  içermektedir. Projeyi kendi bilgisayarınızda derleyip çalıştırmak için aşağıdaki adımları izleyebilirsiniz.  

Gereksinimler:

C Derleyicisi (GCC vb.)

make aracı (Sisteminize kurulu değilse Windows için MinGW üzerinden, Linux/macOS için paket yöneticisinden kurabilirsiniz).

Adım Adım Kurulum:

1. Projeyi Klonlayın:
Öncelikle terminal veya komut satırını açıp projeyi bilgisayarınıza indirin ve proje dizinine girin:

Bash
git clone https://github.com/Cinargenc/veri_yapilari_donem_sonu_projesi
cd veri_yapıları

2. Projeyi Derleyin:
Sistemde birden fazla .c ve .h dosyası bulunduğu için tek tek derlemek yerine Makefile  kullanıyoruz. Terminale sadece aşağıdaki komutu yazmanız yeterlidir:  

Bash
make
Bu komut, tüm modülleri derleyip birbirine bağlayacak ve çalıştırılabilir (executable) ana dosyayı oluşturacaktır. (Not: Proje, Linux, Windows ve macOS (M serisi ARM mimarileri dahil) ortamlarında derlenebilecek şekilde tasarlanmıştır.)

3. Sistemi Başlatın:
Derleme işlemi hatasız tamamlandıktan sonra oluşan programı çalıştırarak sistemi başlatabilirsiniz:

Windows sistemler için:

Bash
gorev_sistemi.exe
Linux / macOS sistemler için:

Bash
./gorev_sistemi
(Not: Çalıştırılabilir dosyanın adı Makefile konfigürasyonunuza göre farklılık gösterebilir.)

4. Temizlik İşlemleri (Opsiyonel):
Kodlar üzerinde değişiklik yapmak isterseniz veya sistemi baştan derlemeniz gerekirse, daha önce oluşturulmuş derleme kalıntılarını (object dosyalarını) temizlemek için şu komutu kullanabilirsiniz:

Bash
make clean
