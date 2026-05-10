#ifndef QUEUE_H
#define QUEUE_H

#include "task.h"

#define KUYRUK_KAPASITESI 512

/* ── Dairesel dizi tabanlı kuyruk ─────────────────────── */
typedef struct {
    Gorev veri[KUYRUK_KAPASITESI];
    int   on;
    int   arka;
    int   sayi;
} Kuyruk;

void   kuyruk_baslat(Kuyruk *k);
int    kuyruk_bos_mu(const Kuyruk *k);
int    kuyruk_dolu_mu(const Kuyruk *k);
int    kuyruk_ekle(Kuyruk *k, const Gorev *g);       /* enqueue */
int    kuyruk_cikar(Kuyruk *k, Gorev *g);            /* dequeue */
Gorev* kuyruk_bak(Kuyruk *k);                        /* peek    */
void   kuyruk_listele(const Kuyruk *k);

#endif
