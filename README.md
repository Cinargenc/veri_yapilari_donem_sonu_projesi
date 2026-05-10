# Veri Yapıları Dönem Sonu Projesi

Bu proje, C programlama dili kullanılarak geliştirilmiş modüler bir veri yapıları uygulamasıdır. Projede farklı veri yapıları ve sistem bileşenleri ayrı modüller halinde tasarlanmış olup, derleme işlemlerinin kolaylaştırılması amacıyla `Makefile` kullanılmıştır.

Proje; Windows, Linux ve macOS işletim sistemlerinde çalışabilecek şekilde geliştirilmiştir.

---

# Gereksinimler

Projeyi derleyip çalıştırabilmek için sisteminizde aşağıdaki araçların kurulu olması gerekmektedir:

- GCC veya benzeri bir C derleyicisi
- `make` aracı

`make` aracı sisteminizde kurulu değilse:

- Windows için: `MinGW` veya `MSYS2`
- Linux için: Paket yöneticileri (`apt`, `pacman` vb.)
- macOS için: `Xcode Command Line Tools`

---

# Projeyi İndirme

Projeyi bilgisayarınıza klonlamak için terminal üzerinden aşağıdaki komutları çalıştırın:

```bash
git clone https://github.com/Cinargenc/veri_yapilari_donem_sonu_projesi.git
cd veri_yapilari_donem_sonu_projesi
```

---

# Projeyi Derleme

Projede birden fazla `.c` ve `.h` dosyası bulunduğundan dolayı derleme işlemleri `Makefile` üzerinden gerçekleştirilmektedir.

Projeyi derlemek için terminalde aşağıdaki komutu çalıştırmanız yeterlidir:

```bash
make
```

Bu işlem sonucunda tüm kaynak dosyaları derlenecek ve çalıştırılabilir program dosyası oluşturulacaktır.

Derleme işlemi başarılı olduğunda terminal ekranında hata mesajı görünmeyecektir.

---

# Programı Çalıştırma

Derleme işlemi tamamlandıktan sonra program aşağıdaki komutlarla çalıştırılabilir.

## Windows

```bash
gorev_sistemi.exe
```

## Linux / macOS

```bash
./gorev_sistemi
```

---

# Proje Yapısı

Proje modüler programlama yaklaşımı kullanılarak geliştirilmiştir. Kaynak kodlar farklı `.c` ve `.h` dosyalarına ayrılarak daha düzenli, okunabilir ve sürdürülebilir bir yapı oluşturulmuştur.

Bu yapı sayesinde:

- Kod okunabilirliği artırılmıştır.
- Bakım ve geliştirme işlemleri kolaylaştırılmıştır.
- Derleme süreci `Makefile` ile otomatik hale getirilmiştir.
- Platform bağımsız kullanım hedeflenmiştir.

---

# Kullanılan Teknolojiler

- C Programlama Dili
- GCC Derleyicisi
- Makefile
- Modüler Programlama Yaklaşımı

---

# Not

Çalıştırılabilir dosyanın adı işletim sistemine veya `Makefile` yapılandırmasına göre değişiklik gösterebilir. Eğer farklı bir çıktı oluşursa `Makefile` dosyasını kontrol edebilirsiniz.
