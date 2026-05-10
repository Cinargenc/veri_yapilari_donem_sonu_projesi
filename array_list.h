#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "task.h"

/* ── Dizi tabanlı görev listesi ─────────────────────────── */
typedef struct {
    Gorev  veri[MAKS_GOREV];
    int    sayi;
} DiziListe;

void  dizi_baslat(DiziListe *dl);
int   dizi_ekle(DiziListe *dl, const Gorev *g);
int   dizi_sil(DiziListe *dl, int id);
Gorev* dizi_bul_id(DiziListe *dl, int id);           /* lineer arama */
Gorev* dizi_binary_ara(DiziListe *dl, int id);       /* ikili arama (sıralı gerekir) */
void  dizi_sirala_oncelik(DiziListe *dl);
void  dizi_sirala_tarih(DiziListe *dl);
void  dizi_listele(const DiziListe *dl);
int   dizi_guncelle(DiziListe *dl, const Gorev *g);

#endif
