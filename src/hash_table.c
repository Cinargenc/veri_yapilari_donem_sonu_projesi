#include "hash_table.h"
#include "colors.h"
#include <stdio.h>
#include <string.h>

/* ── Hash fonksiyonu (linear probing) ───────────────────── */
static int hash(int id) { return (id * 2654435761u) % HT_KAPASITE; }

void ht_baslat(HashTablo *ht) {
    memset(ht->tablo, 0, sizeof(ht->tablo));
    ht->sayi = ht->catisma_sayisi = 0;
}

/* Ekle ─────────────────────────────────────────────────── */
int ht_ekle(HashTablo *ht, const Gorev *g) {
    if (ht->sayi >= HT_KAPASITE * 0.75) {
        printf(STL_HATA "[HT] Yukleme faktoru asimi!\n" SIFIRLA); return -1;
    }
    int idx = hash(g->id);
    int ilk_cikma = -1;
    for (int i = 0; i < HT_KAPASITE; i++) {
        int probe = (idx + i) % HT_KAPASITE;
        if (ht->tablo[probe].durum == DOLU && ht->tablo[probe].veri.id == g->id) {
            ht->tablo[probe].veri = *g; return 0; /* güncelle */
        }
        if (ht->tablo[probe].durum == SILINDI && ilk_cikma == -1)
            ilk_cikma = probe;
        if (ht->tablo[probe].durum == BOS) {
            int hedef = (ilk_cikma != -1) ? ilk_cikma : probe;
            ht->tablo[hedef].veri   = *g;
            ht->tablo[hedef].durum  = DOLU;
            if (i > 0) ht->catisma_sayisi++;
            ht->sayi++;
            return 0;
        }
        if (i > 0) ht->catisma_sayisi++;
    }
    return -1;
}

/* Al ────────────────────────────────────────────────────── */
Gorev* ht_al(HashTablo *ht, int id) {
    int idx = hash(id);
    for (int i = 0; i < HT_KAPASITE; i++) {
        int probe = (idx + i) % HT_KAPASITE;
        if (ht->tablo[probe].durum == BOS) return NULL;
        if (ht->tablo[probe].durum == DOLU && ht->tablo[probe].veri.id == id)
            return &ht->tablo[probe].veri;
    }
    return NULL;
}

/* Sil ───────────────────────────────────────────────────── */
int ht_sil(HashTablo *ht, int id) {
    int idx = hash(id);
    for (int i = 0; i < HT_KAPASITE; i++) {
        int probe = (idx + i) % HT_KAPASITE;
        if (ht->tablo[probe].durum == BOS) return -1;
        if (ht->tablo[probe].durum == DOLU && ht->tablo[probe].veri.id == id) {
            ht->tablo[probe].durum = SILINDI;
            ht->sayi--;
            return 0;
        }
    }
    return -1;
}

/* Güncelle ─────────────────────────────────────────────── */
int ht_guncelle(HashTablo *ht, const Gorev *g) { return ht_ekle(ht, g); }

/* İstatistik ────────────────────────────────────────────── */
void ht_istatistik(const HashTablo *ht) {
    printf(STL_BASLIK "\n=== HASH TABLO ISTATISTIK ===\n" SIFIRLA);
    printf("  Kapasite      : %d\n", HT_KAPASITE);
    printf("  Kayitli gorev : " P_YESIL "%d\n" SIFIRLA, ht->sayi);
    printf("  Catisma sayisi: " P_SARI "%d\n" SIFIRLA, ht->catisma_sayisi);
    printf("  Yukleme faktoru: " P_MAVI "%.2f%%\n" SIFIRLA,
           100.0 * ht->sayi / HT_KAPASITE);
}
