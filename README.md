# Görev Yönetim ve Planlayıcı Sistemi

Bu proje, BMT210 Veri Yapıları dersi dönem sonu projesi olarak geliştirilmiştir. C programlama dili kullanılarak çeşitli veri yapıları (dizi, bağlı liste, yığın, kuyruk, öncelik kuyruğu, BST, hash tablo, graf, kategori ağacı) ile modüler bir görev yönetim sistemi oluşturulmuştur.

Sistem, görev ekleme, silme, güncelleme, arama, bağımlılık yönetimi ve performans karşılaştırmaları gibi işlemleri destekler. Tüm veri yapıları aynı anda kullanılır ve işlemlerin tutarlılığı sağlanır.

## Özellikler

- **Görev Yönetimi**: Görev ekleme, silme, güncelleme
- **Undo İşlemi**: Yığın (Stack) kullanarak son işlemi geri alma
- **Farklı Veri Yapılarında Görüntüleme**:
  - Dizi listesi
  - Bağlı liste
  - Tarihe göre sıralı (BST In-Order)
  - Öncelik kuyruğu (En acil görevler)
  - Bekleyen kuyruk (Queue)
  - ID ile hızlı arama (Hash Table)
- **Tarih Aralığı Sorgulama**: BST kullanarak tarih filtreleme
- **Bağımlılık Yönetimi**: Graf yapısı ile görev bağımlılıkları
- **Topolojik Sıralama**: Görevlerin bağımlılık sırasına göre işlenmesi
- **Kategori Hiyerarşisi**: Ağaç yapısı ile kategori yönetimi
- **Performans Testleri**: Farklı veri yapılarının karşılaştırması
- **Veri Kalıcılığı**: Görevlerin dosyaya kaydedilmesi ve yüklenmesi

## Gereksinimler

- GCC derleyicisi (C11 standardı desteği ile)
- Windows için: MinGW veya MSYS2
- Linux/macOS için: GCC ve make

## Kurulum ve Çalıştırma

### 1. Projeyi İndirme

```bash
git clone https://github.com/Cinargenc/veri_yapilari_donem_sonu_projesi.git
cd veri_yapilari_donem_sonu_projesi
```

### 2. Derleme

```bash
make
```

Eğer `make` kurulu değilse, manuel derleme:

```bash
gcc -Wall -Wextra -std=c11 -O2 -o gorev_sistemi main.c task.c file_io.c array_list.c linked_list.c stack.c queue.c priority_queue.c bst.c hash_table.c graph.c category_tree.c performance.c
```

### 3. Çalıştırma

Windows:
```bash
gorev_sistemi.exe
```

Linux/macOS:
```bash
./gorev_sistemi
```

## Kullanım

Program çalıştırıldığında ana menü görüntülenir. Rakamlarla seçim yapabilirsiniz:

1. **Görev Ekle**: Yeni görev oluşturma
2. **Görev Sil**: ID ile görev silme
3. **Görev Güncelle**: Mevcut görevi düzenleme
4. **Son İşlemi Geri Al**: Undo işlemi (Stack)
5-11. **Görev Listeleme**: Farklı veri yapılarında görüntüleme
12. **Bağımlılık Ekle / Graf Göster**: Görev bağımlılıkları
13. **Topolojik Görev Sırası**: Bağımlılık sırasına göre sıralama
14. **Proje Hiyerarşisi**: Kategori ağacı
15. **Alt Kategori Ekle**: Yeni kategori ekleme
16. **Performans Karşılaştırma Testleri**: Veri yapılarının hız testi
17. **Hash Tablo İstatistiği**: Çakışma sayısı vb.
18. **Kuyruktaki Görevi İşle**: Queue'dan görev alma
0. **Kaydet ve Çık**: Değişiklikleri kaydet ve çıkış

## Proje Yapısı

- `main.c`: Ana program ve menü
- `task.c/h`: Görev veri modeli ve yardımcı fonksiyonlar
- `file_io.c/h`: Dosya okuma/yazma işlemleri
- `array_list.c/h`: Dinamik dizi
- `linked_list.c/h`: Bağlı liste
- `stack.c/h`: Yığın
- `queue.c/h`: Kuyruk
- `priority_queue.c/h`: Öncelik kuyruğu
- `bst.c/h`: İkili arama ağacı
- `hash_table.c/h`: Hash tablo
- `graph.c/h`: Graf
- `category_tree.c/h`: Kategori ağacı
- `performance.c/h`: Performans testleri
- `colors.h`: Terminal renk kodları
- `Makefile`: Derleme scripti

## Katkıda Bulunma

Bu proje eğitim amaçlıdır. Geliştirmeler için fork edip pull request gönderebilirsiniz.

## Lisans

Bu proje açık kaynak kodludur.
