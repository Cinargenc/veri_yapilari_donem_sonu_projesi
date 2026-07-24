#include "linked_list.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>

void bl_baslat(BagliListe *bl) { bl->bas = bl->son = NULL; bl->sayi = 0; }

static BLDugum* dugum_olustur(const Gorev *g) {
    BLDugum *d = (BLDugum*)malloc(sizeof(BLDugum));
    if (!d) { printf(STL_HATA "[LL] Bellek hatasi!\n" SIFIRLA); return NULL; }
    d->veri = *g; d->onceki = d->sonraki = NULL;
    return d;
}

/* Başa ekle ─────────────────────────────────────────────── */
void bl_ekle_bas(BagliListe *bl, const Gorev *g) {
    BLDugum *d = dugum_olustur(g);
    if (!d) return;
    d->sonraki = bl->bas;
    if (bl->bas) bl->bas->onceki = d;
    else         bl->son = d;
    bl->bas = d;
    bl->sayi++;
}

/* Sona ekle ─────────────────────────────────────────────── */
void bl_ekle_son(BagliListe *bl, const Gorev *g) {
    BLDugum *d = dugum_olustur(g);
    if (!d) return;
    d->onceki = bl->son;
    if (bl->son) bl->son->sonraki = d;
    else         bl->bas = d;
    bl->son = d;
    bl->sayi++;
}

/* Bul ───────────────────────────────────────────────────── */
BLDugum* bl_bul(BagliListe *bl, int id) {
    BLDugum *cur = bl->bas;
    while (cur) { if (cur->veri.id == id) return cur; cur = cur->sonraki; }
    return NULL;
}

/* Sil ───────────────────────────────────────────────────── */
int bl_sil(BagliListe *bl, int id) {
    BLDugum *d = bl_bul(bl, id);
    if (!d) return -1;
    if (d->onceki)  d->onceki->sonraki = d->sonraki;
    else            bl->bas = d->sonraki;
    if (d->sonraki) d->sonraki->onceki = d->onceki;
    else            bl->son = d->onceki;
    free(d);
    bl->sayi--;
    return 0;
}

/* Güncelle ─────────────────────────────────────────────── */
int bl_guncelle(BagliListe *bl, const Gorev *g) {
    BLDugum *d = bl_bul(bl, g->id);
    if (!d) return -1;
    d->veri = *g;
    return 0;
}

/* Listele ──────────────────────────────────────────────── */
void bl_listele(const BagliListe *bl) {
    if (!bl->bas) { printf(STL_UYARI "  [LL] Liste bos.\n" SIFIRLA); return; }
    printf(STL_BASLIK "\n=== BAGLI LISTE (%d gorev) ===\n" SIFIRLA, bl->sayi);
    BLDugum *cur = bl->bas;
    while (cur) { gorev_yazdir(&cur->veri); cur = cur->sonraki; }
}

/* Temizle ──────────────────────────────────────────────── */
void bl_temizle(BagliListe *bl) {
    BLDugum *cur = bl->bas;
    while (cur) { BLDugum *tmp = cur->sonraki; free(cur); cur = tmp; }
    bl->bas = bl->son = NULL; bl->sayi = 0;
}
