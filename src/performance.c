#include "performance.h"
#include "array_list.h"
#include "hash_table.h"
#include "bst.h"
#include "priority_queue.h"
#include "linked_list.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
/* ── Windows yüksek çözünürlüklü zamanlayıcı ────────────── */
static LARGE_INTEGER perf_freq;
static int perf_hazir = 0;

static void zamanlayici_baslat(void) {
    if (!perf_hazir) {
        QueryPerformanceFrequency(&perf_freq);
        perf_hazir = 1;
    }
}

static LARGE_INTEGER zaman_al(void) {
    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);
    return t;
}

static double sure_ms_win(LARGE_INTEGER baslangic) {
    LARGE_INTEGER bitis;
    QueryPerformanceCounter(&bitis);
    return 1000.0 * (double)(bitis.QuadPart - baslangic.QuadPart) / (double)perf_freq.QuadPart;
}

#define ZAMAN_TUR         LARGE_INTEGER
#define ZAMAN_BASLAT()    zamanlayici_baslat()
#define ZAMAN_AL()        zaman_al()
#define SURE_MS(bas)      sure_ms_win(bas)

#else
/* ── POSIX/diğer — clock() fallback ─────────────────────── */
#define ZAMAN_TUR         clock_t
#define ZAMAN_BASLAT()    ((void)0)
#define ZAMAN_AL()        clock()
#define SURE_MS(bas)      (1000.0 * (clock() - (bas)) / CLOCKS_PER_SEC)

#endif

/* ── Rastgele görev üret ────────────────────────────────── */
static Gorev rastgele_gorev(int id) {
    Gorev g = {0};
    g.id       = id;
    g.oncelik  = (rand() % 5) + 1;
    g.durum    = (GorevDurum)(rand() % 3);
    g.son_tarih = time(NULL) + (rand() % 30) * 86400L;
    snprintf(g.baslik,   MAX_BASLIK,   "Gorev_%d", id);
    snprintf(g.aciklama, MAX_ACIKLAMA, "Aciklama_%d", id);
    snprintf(g.kategori, MAX_KATEGORI, "Kat_%d", id % 5);
    return g;
}

/* ── Tablo başlığı ──────────────────────────────────────── */
static void tablo_baslik(const int *boyutlar, int bsayi) {
    printf(KALIN P_CAMGOBEGI "\n  %-25s", "ISLEM");
    for (int i = 0; i < bsayi; i++) printf("   N=%-5d", boyutlar[i]);
    printf("\n  %-25s", "-------------------------");
    for (int i = 0; i < bsayi; i++) printf(" %9s", "---------");
    printf(SIFIRLA "\n");
}

static void tablo_satir(const char *baslik, double *v, int n) {
    printf("  %-25s", baslik);
    for (int i = 0; i < n; i++) {
        if (v[i] < 0.01)
            printf(" %7.4fms", v[i]);  /* mikrosaniye hassasiyeti */
        else
            printf(" %7.2fms", v[i]);
    }
    printf("\n");
}

/* ── Güvenli boyut sınırlaması ─────────────────────────── */
static int guvenli_boyut(int n, int maks) {
    return n > maks ? maks : n;
}

/* ══════════════════════════════════════════════════════════
   ARAMA TESTLERİ
   ══════════════════════════════════════════════════════════ */

static double test_dizi_arama(int n) {
    n = guvenli_boyut(n, MAKS_GOREV);
    DiziListe dl; dizi_baslat(&dl);
    for (int i = 1; i <= n; i++) { Gorev g = rastgele_gorev(i); dizi_ekle(&dl, &g); }
    int tekrar = 1000;
    ZAMAN_TUR t = ZAMAN_AL();
    for (int r = 0; r < tekrar; r++) {
        volatile Gorev *sonuc = dizi_bul_id(&dl, rand() % n + 1);
        (void)sonuc;
    }
    return SURE_MS(t) / tekrar;
}

static double test_ht_arama(int n) {
    n = guvenli_boyut(n, (int)(HT_KAPASITE * 0.7));
    HashTablo ht; ht_baslat(&ht);
    for (int i = 1; i <= n; i++) { Gorev g = rastgele_gorev(i); ht_ekle(&ht, &g); }
    int tekrar = 1000;
    ZAMAN_TUR t = ZAMAN_AL();
    for (int r = 0; r < tekrar; r++) {
        volatile Gorev *sonuc = ht_al(&ht, rand() % n + 1);
        (void)sonuc;
    }
    return SURE_MS(t) / tekrar;
}

static double test_bst_arama(int n) {
    BST bst; bst_baslat(&bst);
    for (int i = 1; i <= n; i++) { Gorev g = rastgele_gorev(i); bst_ekle(&bst, &g); }
    int tekrar = 1000;
    ZAMAN_TUR t = ZAMAN_AL();
    for (int r = 0; r < tekrar; r++) {
        volatile BSTDugum *sonuc = bst_ara(&bst, rand() % n + 1);
        (void)sonuc;
    }
    double s = SURE_MS(t) / tekrar;
    bst_temizle(&bst);
    return s;
}

static double test_bl_arama(int n) {
    BagliListe bl; bl_baslat(&bl);
    for (int i = 1; i <= n; i++) { Gorev g = rastgele_gorev(i); bl_ekle_son(&bl, &g); }
    int tekrar = 1000;
    ZAMAN_TUR t = ZAMAN_AL();
    for (int r = 0; r < tekrar; r++) {
        volatile BLDugum *sonuc = bl_bul(&bl, rand() % n + 1);
        (void)sonuc;
    }
    double s = SURE_MS(t) / tekrar;
    bl_temizle(&bl);
    return s;
}

/* ══════════════════════════════════════════════════════════
   EKLEME TESTLERİ
   ══════════════════════════════════════════════════════════ */

static double test_dizi_ekle(int n) {
    n = guvenli_boyut(n, MAKS_GOREV);
    DiziListe dl; dizi_baslat(&dl);
    ZAMAN_TUR t = ZAMAN_AL();
    for (int i = 1; i <= n; i++) { Gorev g = rastgele_gorev(i); dizi_ekle(&dl, &g); }
    return SURE_MS(t);
}

static double test_bl_ekle(int n) {
    BagliListe bl; bl_baslat(&bl);
    ZAMAN_TUR t = ZAMAN_AL();
    for (int i = 1; i <= n; i++) { Gorev g = rastgele_gorev(i); bl_ekle_bas(&bl, &g); }
    double s = SURE_MS(t);
    bl_temizle(&bl);
    return s;
}

static double test_heap_ekle(int n) {
    n = guvenli_boyut(n, MAKS_GOREV);
    OncelikKuyrugu ok; ok_baslat(&ok);
    ZAMAN_TUR t = ZAMAN_AL();
    for (int i = 1; i <= n; i++) { Gorev g = rastgele_gorev(i); ok_ekle(&ok, &g); }
    return SURE_MS(t);
}

/* ══════════════════════════════════════════════════════════
   SIRALAMA TESTLERİ
   ══════════════════════════════════════════════════════════ */

static double test_dizi_sirala(int n) {
    n = guvenli_boyut(n, MAKS_GOREV);
    DiziListe dl; dizi_baslat(&dl);
    for (int i = 1; i <= n; i++) { Gorev g = rastgele_gorev(i); dizi_ekle(&dl, &g); }
    ZAMAN_TUR t = ZAMAN_AL();
    dizi_sirala_oncelik(&dl);
    return SURE_MS(t);
}

/* Sessiz in-order traversal — sadece eleman sayar, ekrana yazmaz */
static int _sessiz_inorder_say(const BSTDugum *k) {
    if (!k) return 0;
    return _sessiz_inorder_say(k->sol) + 1 + _sessiz_inorder_say(k->sag);
}

static double test_bst_inorder(int n) {
    BST bst; bst_baslat(&bst);
    for (int i = 1; i <= n; i++) { Gorev g = rastgele_gorev(i); bst_ekle(&bst, &g); }
    ZAMAN_TUR t = ZAMAN_AL();
    volatile int toplam = _sessiz_inorder_say(bst.kok);
    (void)toplam;
    double s = SURE_MS(t);
    bst_temizle(&bst);
    return s;
}

static double test_heap_extract(int n) {
    n = guvenli_boyut(n, MAKS_GOREV);
    OncelikKuyrugu ok; ok_baslat(&ok);
    for (int i = 1; i <= n; i++) { Gorev g = rastgele_gorev(i); ok_ekle(&ok, &g); }
    ZAMAN_TUR t = ZAMAN_AL();
    while (!ok_bos_mu(&ok)) ok_en_acil_cikar(&ok);
    return SURE_MS(t);
}

/* ══════════════════════════════════════════════════════════
   SİLME TESTLERİ
   ══════════════════════════════════════════════════════════ */

static double test_dizi_sil(int n) {
    n = guvenli_boyut(n, MAKS_GOREV);
    DiziListe dl; dizi_baslat(&dl);
    for (int i = 1; i <= n; i++) { Gorev g = rastgele_gorev(i); dizi_ekle(&dl, &g); }
    ZAMAN_TUR t = ZAMAN_AL();
    for (int i = n; i >= 1; i--) dizi_sil(&dl, i);
    return SURE_MS(t);
}

static double test_ht_sil(int n) {
    n = guvenli_boyut(n, (int)(HT_KAPASITE * 0.7));
    HashTablo ht; ht_baslat(&ht);
    for (int i = 1; i <= n; i++) { Gorev g = rastgele_gorev(i); ht_ekle(&ht, &g); }
    ZAMAN_TUR t = ZAMAN_AL();
    for (int i = n; i >= 1; i--) ht_sil(&ht, i);
    return SURE_MS(t);
}

static double test_bl_sil(int n) {
    BagliListe bl; bl_baslat(&bl);
    for (int i = 1; i <= n; i++) { Gorev g = rastgele_gorev(i); bl_ekle_son(&bl, &g); }
    ZAMAN_TUR t = ZAMAN_AL();
    for (int i = n; i >= 1; i--) bl_sil(&bl, i);
    double s = SURE_MS(t);
    bl_temizle(&bl);
    return s;
}

/* ══════════════════════════════════════════════════════════
   ANA TEST
   ══════════════════════════════════════════════════════════ */
void perf_test_calistir(void) {
    srand(42);
    ZAMAN_BASLAT();

    int boyutlar[] = {100, 500, 1000};
    int bsayi = 3;

    printf(STL_BASLIK "\n╔══════════════════════════════════════════════════════╗\n" SIFIRLA);
    printf(STL_BASLIK "║        PERFORMANS KARSILASTIRMA TESTLERI             ║\n" SIFIRLA);
    printf(STL_BASLIK "╚══════════════════════════════════════════════════════╝\n" SIFIRLA);

    printf(P_SARI "\n  Test yapiliyor, lutfen bekleyin...\n" SIFIRLA);

    /* [1] ARAMA */
    printf(P_SARI "\n[1] ARAMA KARSILASTIRMASI (ortalama 1000 sorgu)\n" SIFIRLA);
    tablo_baslik(boyutlar, bsayi);
    {
        double v[3];
        for (int i = 0; i < bsayi; i++) v[i] = test_dizi_arama(boyutlar[i]);
        tablo_satir("Dizi Lineer Arama O(n)", v, bsayi);
        for (int i = 0; i < bsayi; i++) v[i] = test_ht_arama(boyutlar[i]);
        tablo_satir("Hash Table O(1)", v, bsayi);
        for (int i = 0; i < bsayi; i++) v[i] = test_bst_arama(boyutlar[i]);
        tablo_satir("BST Arama O(log n)", v, bsayi);
        for (int i = 0; i < bsayi; i++) v[i] = test_bl_arama(boyutlar[i]);
        tablo_satir("Bagli Liste O(n)", v, bsayi);
    }

    /* [2] EKLEME */
    printf(P_SARI "\n[2] EKLEME KARSILASTIRMASI (toplam N ekleme)\n" SIFIRLA);
    tablo_baslik(boyutlar, bsayi);
    {
        double v[3];
        for (int i = 0; i < bsayi; i++) v[i] = test_dizi_ekle(boyutlar[i]);
        tablo_satir("Dizi Ekle O(1)", v, bsayi);
        for (int i = 0; i < bsayi; i++) v[i] = test_bl_ekle(boyutlar[i]);
        tablo_satir("Bagli Liste O(1)", v, bsayi);
        for (int i = 0; i < bsayi; i++) v[i] = test_heap_ekle(boyutlar[i]);
        tablo_satir("Min-Heap O(log n)", v, bsayi);
    }

    /* [3] SIRALAMA */
    printf(P_SARI "\n[3] SIRALAMA KARSILASTIRMASI\n" SIFIRLA);
    tablo_baslik(boyutlar, bsayi);
    {
        double v[3];
        for (int i = 0; i < bsayi; i++) v[i] = test_dizi_sirala(boyutlar[i]);
        tablo_satir("qsort O(n log n)", v, bsayi);
        for (int i = 0; i < bsayi; i++) v[i] = test_bst_inorder(boyutlar[i]);
        tablo_satir("BST In-Order O(n)", v, bsayi);
        for (int i = 0; i < bsayi; i++) v[i] = test_heap_extract(boyutlar[i]);
        tablo_satir("Heap Extract O(n log n)", v, bsayi);
    }

    /* [4] SİLME */
    printf(P_SARI "\n[4] SILME KARSILASTIRMASI (N eleman sil)\n" SIFIRLA);
    tablo_baslik(boyutlar, bsayi);
    {
        double v[3];
        for (int i = 0; i < bsayi; i++) v[i] = test_dizi_sil(boyutlar[i]);
        tablo_satir("Dizi Sil O(n)", v, bsayi);
        for (int i = 0; i < bsayi; i++) v[i] = test_ht_sil(boyutlar[i]);
        tablo_satir("Hash Sil O(1)", v, bsayi);
        for (int i = 0; i < bsayi; i++) v[i] = test_bl_sil(boyutlar[i]);
        tablo_satir("Bagli Liste Sil O(n)", v, bsayi);
    }

    /* [5] BELLEK */
    printf(P_SARI "\n[5] YAKLASIK BELLEK KULLANIMI\n" SIFIRLA);
    printf(KALIN P_CAMGOBEGI "  %-25s %12s %12s\n" SIFIRLA,
           "YAPI", "N=100", "N=1000");
    printf("  %-25s %12s %12s\n",
           "-------------------------", "------------", "------------");
    printf("  %-25s %9.1f KB %9.1f KB\n", "DiziListe (statik)",
           100 * sizeof(Gorev) / 1024.0, 1000 * sizeof(Gorev) / 1024.0);
    printf("  %-25s %9.1f KB %9.1f KB\n", "BagliListe (dinamik)",
           100 * (sizeof(BLDugum)) / 1024.0, 1000 * (sizeof(BLDugum)) / 1024.0);
    printf("  %-25s %9.1f KB %9.1f KB\n", "BST (dinamik)",
           100 * sizeof(BSTDugum) / 1024.0, 1000 * sizeof(BSTDugum) / 1024.0);
    printf("  %-25s %9.1f KB %9.1f KB\n", "HashTablo (statik)",
           sizeof(HashTablo) / 1024.0, sizeof(HashTablo) / 1024.0);
    printf("  %-25s %9.1f KB %9.1f KB\n", "Heap (statik)",
           100 * sizeof(Gorev) / 1024.0, 1000 * sizeof(Gorev) / 1024.0);

    printf(P_YESIL "\n  Testler tamamlandi.\n" SIFIRLA);
}
