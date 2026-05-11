#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "colors.h"
#include "task.h"
#include "array_list.h"
#include "linked_list.h"
#include "linear_ds.h"
#include "priority_queue.h"
#include "bst.h"
#include "hash_table.h"
#include "graph.h"
#include "category_tree.h"
#include "performance.h"

/* ═══════════════════════════════════════════════════════════
   Global veri yapıları
   ═══════════════════════════════════════════════════════════ */
static DiziListe      dizi;
static BagliListe     bl;
static Yigin          yigin;
static Kuyruk         kuyruk;
static OncelikKuyrugu ok;
static BST            bst;
static HashTablo      ht;
static Graf           graf;
static KategoriAgaci  kat_agaci;

/* ── Tüm yapılara görev ekle ────────────────────────────── */
static void yapilara_ekle(const Gorev *g) {
    dizi_ekle(&dizi, g);
    bl_ekle_son(&bl, g);
    ok_ekle(&ok, g);
    bst_ekle(&bst, g);
    ht_ekle(&ht, g);
    kuyruk_ekle(&kuyruk, g);
    graf_dugum_ekle(&graf, g->id);
    kat_gorev_ekle(&kat_agaci, g->kategori, g->id);
}

/* ── Tüm yapılardan görev sil ───────────────────────────── */
static void yapilardan_sil(int id) {
    dizi_sil(&dizi, id);
    bl_sil(&bl, id);
    ok_sil(&ok, id);
    bst_sil(&bst, id);
    ht_sil(&ht, id);
    graf_dugum_sil(&graf, id);
}

/* ── Tüm yapılarda görev güncelle ─────────────────────────── */
static void yapilarda_guncelle(const Gorev *g) {
    dizi_guncelle(&dizi, g);
    bl_guncelle(&bl, g);
    ht_guncelle(&ht, g);
    bst_guncelle(&bst, g);
    ok_sil(&ok, g->id);
    ok_ekle(&ok, g);
}

/* ── Sistemi kaydet ─────────────────────────────────────── */
static void kaydet(void) {
    dosyaya_kaydet(dizi.veri, dizi.sayi);
}

/* ── Başlık ekranı ──────────────────────────────────────── */
static void baslik_yazdir(void) {
    printf(STL_BASLIK
        "\n╔══════════════════════════════════════════════════╗\n"
        "║       GOREV YONETIM VE PLANLAYICI SISTEMI       ║\n"
        "║          BMT210 Veri Yapilari Projesi            ║\n"
        "╚══════════════════════════════════════════════════╝\n"
        SIFIRLA);
}

/* ── Ana menü ────────────────────────────────────────────── */
static void menu_yazdir(void) {
    printf(KALIN P_CAMGOBEGI
        "\n┌─────────────────────────────────────────┐\n"
        "│               ANA MENU                 │\n"
        "├─────────────────────────────────────────┤\n" SIFIRLA);
    printf(P_BEYAZ
        "│  1. Gorev Ekle                          │\n"
        "│  2. Gorev Sil                           │\n"
        "│  3. Gorev Guncelle                      │\n"
        "│  4. Son Islemi Geri Al  (Undo/Stack)    │\n"
        "├─────────────────────────────────────────┤\n"
        "│  5. Tum Gorevler  (Dizi)                │\n"
        "│  6. Tum Gorevler  (Bagli Liste)         │\n"
        "│  7. Tarihe Gore Sirali (BST In-Order)   │\n"
        "│  8. En Acil Gorevler  (Priority Queue)  │\n"
        "│  9. Bekleyen Kuyruk   (Queue)           │\n"
        "│ 10. ID ile Hizli Ara  (Hash Table)      │\n"
        "│ 11. Tarih Araligi Sorgula (BST)         │\n"
        "├─────────────────────────────────────────┤\n"
        "│ 12. Bagimlilik Ekle / Graf Goster       │\n"
        "│ 13. Topologik Gorev Sirasi              │\n"
        "│ 14. Proje Hiyerarsisi (Kategori Agaci)  │\n"
        "│ 15. Alt Kategori Ekle                   │\n"
        "├─────────────────────────────────────────┤\n"
        "│ 16. Performans Karsilastirma Testleri   │\n"
        "│ 17. Hash Tablo Istatistigi              │\n"
        "│ 18. Kuyruktaki Gorevi Isle (Dequeue)    │\n"
        "├─────────────────────────────────────────┤\n"
        "│  0. Kaydet ve Cik                       │\n"
        "└─────────────────────────────────────────┘\n" SIFIRLA);
    printf(STL_BILGI "  Secim: " SIFIRLA);
}

/* ══════════════════════════════════════════════════════════
   İşlem fonksiyonları
   ══════════════════════════════════════════════════════════ */

/* 1. Görev ekle */
static void gorev_ekle_isle(void) {
    printf(STL_BASLIK "\n--- GOREV EKLE ---\n" SIFIRLA);
    Gorev g;
    gorev_gir(&g, id_uret());
    /* Undo kaydı */
    IslemKaydi kayit = {.tip = OP_EKLE, .yeni = g};
    yigin_it(&yigin, kayit);
    yapilara_ekle(&g);
    kaydet();
    printf(STL_BASARI "  Gorev #%d eklendi.\n" SIFIRLA, g.id);
}

/* 2. Görev sil */
static void gorev_sil_isle(void) {
    printf(STL_BASLIK "\n--- GOREV SIL ---\n" SIFIRLA);
    printf(STL_BILGI "  Silinecek gorev ID: " SIFIRLA);
    printf("  "); int id = sayi_oku();
    Gorev *g = ht_al(&ht, id);
    if (!g) { printf(STL_HATA "  ID bulunamadi.\n" SIFIRLA); return; }
    IslemKaydi kayit = {.tip = OP_SIL, .eski = *g};
    yigin_it(&yigin, kayit);
    yapilardan_sil(id);
    kaydet();
    printf(STL_BASARI "  Gorev #%d silindi.\n" SIFIRLA, id);
}

/* 3. Görev güncelle */
static void gorev_guncelle_isle(void) {
    printf(STL_BASLIK "\n--- GOREV GUNCELLE ---\n" SIFIRLA);
    printf(STL_BILGI "  Guncellenecek gorev ID: " SIFIRLA);
    printf("  "); int id = sayi_oku();
    Gorev *eski = ht_al(&ht, id);
    if (!eski) { printf(STL_HATA "  ID bulunamadi.\n" SIFIRLA); return; }
    printf(P_SARI "  Mevcut gorev:\n" SIFIRLA);
    gorev_yazdir(eski);
    printf(P_YESIL "\n  Yeni bilgileri girin:\n" SIFIRLA);
    Gorev yeni;
    gorev_gir(&yeni, id);
    IslemKaydi kayit = {.tip = OP_GUNCELLE, .eski = *eski, .yeni = yeni};
    yigin_it(&yigin, kayit);
    yapilarda_guncelle(&yeni);
    kaydet();
    printf(STL_BASARI "  Gorev #%d guncellendi.\n" SIFIRLA, id);
}

/* 4. Undo */
static void undo_isle(void) {
    if (yigin_bos_mu(&yigin)) {
        printf(STL_UYARI "  Geri alinacak islem yok.\n" SIFIRLA); return;
    }
    IslemKaydi kayit = yigin_cek(&yigin);
    switch (kayit.tip) {
        case OP_EKLE:
            yapilardan_sil(kayit.yeni.id);
            printf(STL_BASARI "  UNDO: Gorev #%d ekleme geri alindi.\n" SIFIRLA, kayit.yeni.id);
            break;
        case OP_SIL:
            yapilara_ekle(&kayit.eski);
            printf(STL_BASARI "  UNDO: Gorev #%d silme geri alindi.\n" SIFIRLA, kayit.eski.id);
            break;
        case OP_GUNCELLE:
            yapilarda_guncelle(&kayit.eski);
            printf(STL_BASARI "  UNDO: Gorev #%d guncelleme geri alindi.\n" SIFIRLA, kayit.eski.id);
            break;
    }
    kaydet();
}

/* 10. Hash Table ile arama */
static void ht_arama_isle(void) {
    printf(STL_BILGI "\n  Aranacak gorev ID: " SIFIRLA);
    printf("  "); int id = sayi_oku();
    Gorev *g = ht_al(&ht, id);
    if (g) gorev_yazdir(g);
    else   printf(STL_HATA "  Gorev bulunamadi.\n" SIFIRLA);
}

/* 11. BST aralık sorgulama */
static void bst_aralik_isle(void) {
    int g1, a1, y1, g2, a2, y2;
    struct tm tm1 = {0}, tm2 = {0};
    char satir[64];
    printf(STL_BILGI "\n  Baslangic tarihi (GG/AA/YYYY): " SIFIRLA);
    utf8_satir_oku(satir, sizeof(satir));
    sscanf(satir, "%d/%d/%d", &g1, &a1, &y1);
    printf(STL_BILGI "  Bitis tarihi    (GG/AA/YYYY): " SIFIRLA);
    utf8_satir_oku(satir, sizeof(satir));
    sscanf(satir, "%d/%d/%d", &g2, &a2, &y2);
    tm1.tm_mday=g1; tm1.tm_mon=a1-1; tm1.tm_year=y1-1900; tm1.tm_isdst=-1;
    tm2.tm_mday=g2; tm2.tm_mon=a2-1; tm2.tm_year=y2-1900; tm2.tm_hour=23; tm2.tm_min=59; tm2.tm_isdst=-1;
    bst_aralik_sorgula(&bst, mktime(&tm1), mktime(&tm2));
}

/* 12. Bağımlılık */
static void bagimlilik_isle(void) {
    printf(STL_BASLIK "\n--- BAGIMLILIK YONETIMI ---\n" SIFIRLA);
    printf("  1. Bagimlilik ekle\n  2. Grafi goster\n  Secim: ");
    int s = sayi_oku();
    if (s == 1) {
        printf(STL_BILGI "  Kaynak gorev ID: " SIFIRLA);
        int k = sayi_oku();
        printf(STL_BILGI "  Hedef gorev ID : " SIFIRLA);
        int h = sayi_oku();
        /* Bağımlılığı görev yapısına da kaydet */
        Gorev *gk = ht_al(&ht, k);
        if (gk && gk->bagim_sayi < MAX_BAGIMLILIK)
            gk->bagimliliklar[gk->bagim_sayi++] = h;
        graf_kenar_ekle(&graf, k, h);
        printf(STL_BASARI "  #%d --> #%d bagimliligi eklendi.\n" SIFIRLA, k, h);
        if (graf_dongu_var_mi(&graf))
            printf(STL_HATA "  [UYARI] Dongude bagimlilik tespit edildi!\n" SIFIRLA);
        kaydet();
    } else {
        graf_ascii_ciz(&graf);
    }
}

/* 15. Alt kategori */
static void kat_ekle_isle(void) {
    char eb[MAX_KATEGORI], yeni[MAX_KATEGORI];
    printf(STL_BILGI "  Ebeveyn kategori adi ('Kok' ise Kok): " SIFIRLA);
    utf8_satir_oku(eb, MAX_KATEGORI);
    printf(STL_BILGI "  Yeni kategori adi: " SIFIRLA);
    utf8_satir_oku(yeni, MAX_KATEGORI);
    KatDugum *d = kat_ekle(&kat_agaci, eb, yeni);
    if (d) printf(STL_BASARI "  '%s' kategorisi eklendi.\n" SIFIRLA, yeni);
}

/* 18. Kuyruktan görev işle */
static void kuyruk_isle(void) {
    Gorev g;
    if (kuyruk_cikar(&kuyruk, &g) == 0) {
        printf(STL_BASARI "\n  Kuyruktan alindi:\n" SIFIRLA);
        gorev_yazdir(&g);
    }
}

/* ══════════════════════════════════════════════════════════
   main
   ══════════════════════════════════════════════════════════ */
int main(void) {
    konsol_hazirla();

    /* Yapıları başlat */
    dizi_baslat(&dizi);
    bl_baslat(&bl);
    yigin_baslat(&yigin);
    kuyruk_baslat(&kuyruk);
    ok_baslat(&ok);
    bst_baslat(&bst);
    ht_baslat(&ht);
    graf_baslat(&graf);
    kat_baslat(&kat_agaci);

    /* Dosyadan yükle */
    Gorev tmp[MAKS_GOREV];
    int yuklenen = dosyadan_yukle(tmp, MAKS_GOREV);
    for (int i = 0; i < yuklenen; i++) {
        id_baslangic_ayarla(tmp[i].id);
        yapilara_ekle(&tmp[i]);
    }

    baslik_yazdir();
    printf(STL_BILGI "  %d gorev yuklendi.\n" SIFIRLA, yuklenen);

    int secim;
    do {
        menu_yazdir();
        secim = sayi_oku();
        switch (secim) {
            case 1:  gorev_ekle_isle();                        break;
            case 2:  gorev_sil_isle();                         break;
            case 3:  gorev_guncelle_isle();                    break;
            case 4:  undo_isle();                              break;
            case 5:  dizi_listele(&dizi);                      break;
            case 6:  bl_listele(&bl);                          break;
            case 7:  bst_inorder_yazdir(&bst);                 break;
            case 8:  ok_listele(&ok, 5);                       break;
            case 9:  kuyruk_listele(&kuyruk);                  break;
            case 10: ht_arama_isle();                          break;
            case 11: bst_aralik_isle();                        break;
            case 12: bagimlilik_isle();                        break;
            case 13: graf_topologik_sirala(&graf);             break;
            case 14:
                printf(STL_BASLIK "\n=== PROJE HIYERARSISI ===\n" SIFIRLA);
                kat_yazdir(kat_agaci.kok, 0);                  break;
            case 15: kat_ekle_isle();                          break;
            case 16: perf_test_calistir();                     break;
            case 17: ht_istatistik(&ht);                       break;
            case 18: kuyruk_isle();                            break;
            case 0:
                kaydet();
                printf(STL_BASARI "\n  Sistem kapatiliyor. Gorusuruz!\n" SIFIRLA);
                break;
            default:
                printf(STL_HATA "  Gecersiz secim!\n" SIFIRLA);
        }
    } while (secim != 0);

    /* Bellek temizliği */
    bl_temizle(&bl);
    bst_temizle(&bst);
    kat_temizle(kat_agaci.kok);

    return 0;
}
