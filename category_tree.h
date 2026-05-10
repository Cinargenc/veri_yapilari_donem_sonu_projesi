#ifndef CATEGORY_TREE_H
#define CATEGORY_TREE_H

#include "task.h"

#define MAKS_COCUK    32
#define MAKS_KAT_GOREV 256

/* ── N-ary Kategori Ağacı ───────────────────────────────── */
typedef struct KatDugum {
    char            ad[MAX_KATEGORI];
    int             gorev_idler[MAKS_KAT_GOREV];
    int             gorev_sayi;
    struct KatDugum *cocuklar[MAKS_COCUK];
    int             cocuk_sayi;
} KatDugum;

typedef struct { KatDugum *kok; } KategoriAgaci;

void      kat_baslat(KategoriAgaci *ka);
KatDugum* kat_dugum_bul(KatDugum *k, const char *ad);
KatDugum* kat_ekle(KategoriAgaci *ka, const char *ebeveyn_ad, const char *yeni_ad);
void      kat_gorev_ekle(KategoriAgaci *ka, const char *kat_ad, int gorev_id);
void      kat_gorev_sil(KategoriAgaci *ka, const char *kat_ad, int gorev_id);
void      kat_yazdir(const KatDugum *k, int seviye);
void      kat_temizle(KatDugum *k);

#endif
