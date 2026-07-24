# 🗂️ Görev Yönetim ve Planlayıcı Sistemi

> **BMT210 Veri Yapıları** — Dönem Sonu Projesi  
> C dili ile çoklu veri yapısı kullanılarak geliştirilmiş terminal tabanlı görev yöneticisi.

---

## 📌 Proje Hakkında

Bu proje; **dizi, bağlı liste, yığın, kuyruk, öncelik kuyruğu, BST, hash tablo, graf** ve **kategori ağacı** veri yapılarının gerçek bir uygulamada birlikte nasıl kullanıldığını göstermek amacıyla geliştirilmiştir.

Her görev işlemi (ekleme, silme, güncelleme) tüm veri yapılarında eş zamanlı olarak gerçekleşir. Bu sayede her yapının farklı avantajları canlı olarak karşılaştırılabilir.

---

## ✨ Özellikler

| Özellik | Kullanılan Veri Yapısı |
|---|---|
| Görev ekleme / silme / güncelleme | Tüm yapılara yayılır |
| Son işlemi geri alma (Undo) | **Yığın (Stack)** |
| Sırasız listeleme | **Dizi (Array List)** |
| Bağlı listeleme | **Bağlı Liste (Linked List)** |
| Tarihe göre sıralı listeleme | **BST (In-Order Traversal)** |
| En acil görevler | **Öncelik Kuyruğu (Max-Heap)** |
| FIFO görev işleme | **Dairesel Kuyruk (Queue)** |
| O(1) ID araması | **Hash Tablo (Zincirleme)** |
| Tarih aralığı sorgusu | **BST (Budamalı Arama)** |
| Görev bağımlılıkları | **Yönlü Graf (DFS / Topo Sort)** |
| Proje kategori hiyerarşisi | **Kategori Ağacı (N-li Ağaç)** |
| Veri yapıları performans testi | `performance.c` |
| Kalıcı depolama | Binary dosya (`gorevler.bin`) |

---

## 📁 Proje Yapısı

```
.
├── src/                    ← Kaynak dosyaları (.c)
│   ├── main.c              # Giriş noktası ve ana menü
│   ├── task.c              # Görev veri modeli + giriş/çıkış fonksiyonları
│   ├── file_io.c           # Binary dosyaya kaydet / yükle
│   ├── array_list.c        # Dizi tabanlı liste
│   ├── linked_list.c       # Tek yönlü bağlı liste
│   ├── stack.c             # Yığın (Undo işlemleri)
│   ├── queue.c             # Dairesel kuyruk
│   ├── priority_queue.c    # Max-heap öncelik kuyruğu
│   ├── bst.c               # İkili arama ağacı (tarih anahtarı)
│   ├── hash_table.c        # Hash tablo (ID → Görev, zincirleme)
│   ├── graph.c             # Yönlü graf + topolojik sıralama
│   ├── category_tree.c     # N-li kategori ağacı
│   └── performance.c       # Karşılaştırmalı benchmark testleri
│
├── include/                ← Başlık dosyaları (.h)
│   ├── task.h
│   ├── file_io.h
│   ├── array_list.h
│   ├── linked_list.h
│   ├── stack.h
│   ├── queue.h
│   ├── priority_queue.h
│   ├── bst.h
│   ├── hash_table.h
│   ├── graph.h
│   ├── category_tree.h
│   ├── performance.h
│   └── colors.h            # ANSI terminal renk makroları
│
├── Makefile                ← Derleme betiği
└── README.md
```

---

## 🚀 Kurulum ve Çalıştırma

### Gereksinimler

- **GCC** — C11 desteği ile (`gcc --version` ile kontrol edin)
- **Windows**: [MinGW-w64](https://www.mingw-w64.org/) veya [MSYS2](https://www.msys2.org/)
- **Linux / macOS**: `gcc` + `make` (genellikle kurulu gelir)

---

### 1. Repoyu klonla

```bash
git clone https://github.com/Cinargenc/veri_yapilari_donem_sonu_projesi.git
cd veri_yapilari_donem_sonu_projesi
```

### 2. Derle

```bash
make
```

`make` yoksa manuel:

```bash
# Windows
gcc -Wall -Wextra -std=c11 -O2 -I include -o gorev_sistemi src/*.c

# Linux / macOS
gcc -Wall -Wextra -std=c11 -O2 -I include -o gorev_sistemi src/*.c
```

### 3. Çalıştır

**Windows:**
```cmd
gorev_sistemi.exe
```

**Linux / macOS:**
```bash
./gorev_sistemi
```

---

## 🖥️ Menü Referansı

```
┌─────────────────────────────────────────┐
│               ANA MENU                 │
├─────────────────────────────────────────┤
│  1. Gorev Ekle                          │
│  2. Gorev Sil                           │
│  3. Gorev Guncelle                      │
│  4. Son Islemi Geri Al  (Undo/Stack)    │
├─────────────────────────────────────────┤
│  5. Tum Gorevler  (Dizi)                │
│  6. Tum Gorevler  (Bagli Liste)         │
│  7. Tarihe Gore Sirali (BST In-Order)   │
│  8. En Acil Gorevler  (Priority Queue)  │
│  9. Bekleyen Kuyruk   (Queue)           │
│ 10. ID ile Hizli Ara  (Hash Table)      │
│ 11. Tarih Araligi Sorgula (BST)         │
├─────────────────────────────────────────┤
│ 12. Bagimlilik Ekle / Graf Goster       │
│ 13. Topologik Gorev Sirasi              │
│ 14. Proje Hiyerarsisi (Kategori Agaci)  │
│ 15. Alt Kategori Ekle                   │
├─────────────────────────────────────────┤
│ 16. Performans Karsilastirma Testleri   │
│ 17. Hash Tablo Istatistigi              │
│ 18. Kuyruktaki Gorevi Isle (Dequeue)    │
├─────────────────────────────────────────┤
│  0. Kaydet ve Cik                       │
└─────────────────────────────────────────┘
```

---

## 👥 Geliştiriciler

| İsim | Numara |
|---|---|
| Çınar Genç | 24181616059 |
| Yusuf Kuru | 24181616006 |

**Ders:** BMT210 Veri Yapıları  
**Dönem:** 2024–2025 Bahar
