#ifndef STACK_H
#define STACK_H

#include "task.h"

/* ── Geri alma (Undo) işlem türleri ────────────────────── */
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

#endif
