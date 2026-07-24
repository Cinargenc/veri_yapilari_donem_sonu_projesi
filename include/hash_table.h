#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "task.h"

#define HT_KAPASITE 2048

typedef enum { BOS = 0, DOLU, SILINDI } HtDurum;

typedef struct {
    Gorev   veri;
    HtDurum durum;
} HtYuva;

typedef struct {
    HtYuva  tablo[HT_KAPASITE];
    int     sayi;
    int     catisma_sayisi;   /* performans istatistiği */
} HashTablo;

void   ht_baslat(HashTablo *ht);
int    ht_ekle(HashTablo *ht, const Gorev *g);
Gorev* ht_al(HashTablo *ht, int id);
int    ht_sil(HashTablo *ht, int id);
int    ht_guncelle(HashTablo *ht, const Gorev *g);
void   ht_istatistik(const HashTablo *ht);

#endif
