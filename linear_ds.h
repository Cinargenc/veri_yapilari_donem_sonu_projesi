#ifndef LINEAR_DS_H
#define LINEAR_DS_H

#include "task.h"

/* ══════════════════════════════════════════════════════════
   YIGIN (Stack) — Geri alma (Undo) işlemleri için
   ══════════════════════════════════════════════════════════ */

typedef enum { OP_EKLE, OP_SIL, OP_GUNCELLE } IslemTipi;

typedef struct {
    IslemTipi tip;
    Gorev     eski;   /* SIL/GUNCELLE için önceki veri */
    Gorev     yeni;   /* EKLE/GUNCELLE için yeni veri  */
} IslemKaydi;

#define YIGIN_KAPASITESI 256

typedef struct {
    IslemKaydi veri[YIGIN_KAPASITESI];
    int        tepe;  /* -1 = boş */
} Yigin;

void        yigin_baslat(Yigin *y);
int         yigin_bos_mu(const Yigin *y);
int         yigin_dolu_mu(const Yigin *y);
void        yigin_it(Yigin *y, IslemKaydi kayit);
IslemKaydi  yigin_cek(Yigin *y);
IslemKaydi* yigin_bak(Yigin *y);

/* ══════════════════════════════════════════════════════════
   KUYRUK (Queue) — Dairesel dizi tabanlı görev kuyruğu
   ══════════════════════════════════════════════════════════ */

#define KUYRUK_KAPASITESI 512

typedef struct {
    Gorev veri[KUYRUK_KAPASITESI];
    int   on;
    int   arka;
    int   sayi;
} Kuyruk;

void   kuyruk_baslat(Kuyruk *k);
int    kuyruk_bos_mu(const Kuyruk *k);
int    kuyruk_dolu_mu(const Kuyruk *k);
int    kuyruk_ekle(Kuyruk *k, const Gorev *g);    /* enqueue */
int    kuyruk_cikar(Kuyruk *k, Gorev *g);          /* dequeue */
Gorev* kuyruk_bak(Kuyruk *k);                      /* peek    */
void   kuyruk_listele(const Kuyruk *k);

#endif /* LINEAR_DS_H */
