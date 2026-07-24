#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "task.h"

/* ── Min-Heap (öncelik = oncelik*-1 + deadline) ────────── */
/* Küçük skor = daha acil görev                             */
typedef struct {
    Gorev veri[MAKS_GOREV];
    int   sayi;
    time_t referans_zaman;  /* heap tutarlılığı için sabit referans */
} OncelikKuyrugu;

void   ok_baslat(OncelikKuyrugu *ok);
int    ok_bos_mu(const OncelikKuyrugu *ok);
void   ok_ekle(OncelikKuyrugu *ok, const Gorev *g);
Gorev  ok_en_acil_cikar(OncelikKuyrugu *ok);  /* extract-min */
Gorev* ok_en_acil_bak(OncelikKuyrugu *ok);    /* peek-min    */
void   ok_listele(const OncelikKuyrugu *ok, int n); /* ilk n acil */
int    ok_sil(OncelikKuyrugu *ok, int id);
void   ok_yenile(OncelikKuyrugu *ok);         /* referans güncelle + rebuild */

/* Öncelik skoru: küçük = acil (deadline yakın + öncelik yüksek) */
double ok_skor(const Gorev *g);
double ok_skor_ref(const Gorev *g, time_t ref);

#endif
