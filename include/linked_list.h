#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "task.h"

/* ── Çift yönlü bağlı liste düğümü ─────────────────────── */
typedef struct BLDugum {
    Gorev           veri;
    struct BLDugum *onceki;
    struct BLDugum *sonraki;
} BLDugum;

typedef struct {
    BLDugum *bas;
    BLDugum *son;
    int       sayi;
} BagliListe;

void    bl_baslat(BagliListe *bl);
void    bl_ekle_bas(BagliListe *bl, const Gorev *g);
void    bl_ekle_son(BagliListe *bl, const Gorev *g);
int     bl_sil(BagliListe *bl, int id);
BLDugum* bl_bul(BagliListe *bl, int id);
int     bl_guncelle(BagliListe *bl, const Gorev *g);
void    bl_listele(const BagliListe *bl);
void    bl_temizle(BagliListe *bl);

#endif
