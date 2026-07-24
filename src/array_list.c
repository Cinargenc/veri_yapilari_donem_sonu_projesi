#include "array_list.h"
#include "colors.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void dizi_baslat(DiziListe *dl) { dl->sayi = 0; }

/* Ekle ─────────────────────────────────────────────────── */
int dizi_ekle(DiziListe *dl, const Gorev *g) {
    if (dl->sayi >= MAKS_GOREV) {
        printf(STL_HATA "[DIZI] Kapasite dolu!\n" SIFIRLA); return -1;
    }
    dl->veri[dl->sayi++] = *g;
    return 0;
}

/* Sil ──────────────────────────────────────────────────── */
int dizi_sil(DiziListe *dl, int id) {
    for (int i = 0; i < dl->sayi; i++) {
        if (dl->veri[i].id == id) {
            /* Son elemanı boşluğa taşı */
            dl->veri[i] = dl->veri[--dl->sayi];
            return 0;
        }
    }
    return -1;
}

/* Güncelle ─────────────────────────────────────────────── */
int dizi_guncelle(DiziListe *dl, const Gorev *g) {
    for (int i = 0; i < dl->sayi; i++) {
        if (dl->veri[i].id == g->id) { dl->veri[i] = *g; return 0; }
    }
    return -1;
}

/* Lineer arama ─────────────────────────────────────────── */
Gorev* dizi_bul_id(DiziListe *dl, int id) {
    for (int i = 0; i < dl->sayi; i++)
        if (dl->veri[i].id == id) return &dl->veri[i];
    return NULL;
}

/* qsort karşılaştırıcılar */
static int cmp_id(const void *a, const void *b) {
    return ((Gorev*)a)->id - ((Gorev*)b)->id;
}
static int cmp_oncelik(const void *a, const void *b) {
    return ((Gorev*)b)->oncelik - ((Gorev*)a)->oncelik; /* azalan */
}
static int cmp_tarih(const void *a, const void *b) {
    double d = difftime(((Gorev*)a)->son_tarih, ((Gorev*)b)->son_tarih);
    return (d > 0) - (d < 0);
}

/* İkili arama — önce ID'ye göre sıralı olmalı */
Gorev* dizi_binary_ara(DiziListe *dl, int id) {
    qsort(dl->veri, dl->sayi, sizeof(Gorev), cmp_id);
    int lo = 0, hi = dl->sayi - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (dl->veri[mid].id == id) return &dl->veri[mid];
        if (dl->veri[mid].id < id) lo = mid + 1;
        else                       hi = mid - 1;
    }
    return NULL;
}

void dizi_sirala_oncelik(DiziListe *dl) {
    qsort(dl->veri, dl->sayi, sizeof(Gorev), cmp_oncelik);
}
void dizi_sirala_tarih(DiziListe *dl) {
    qsort(dl->veri, dl->sayi, sizeof(Gorev), cmp_tarih);
}

/* Listele ──────────────────────────────────────────────── */
void dizi_listele(const DiziListe *dl) {
    if (dl->sayi == 0) {
        printf(STL_UYARI "  [DIZI] Liste bos.\n" SIFIRLA); return;
    }
    printf(STL_BASLIK "\n=== DIZI LISTE (%d gorev) ===\n" SIFIRLA, dl->sayi);
    for (int i = 0; i < dl->sayi; i++) gorev_yazdir(&dl->veri[i]);
}
