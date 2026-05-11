#include "linear_ds.h"
#include "colors.h"
#include <stdio.h>

/* ══════════════════════════════════════════════════════════
   YIGIN (Stack) implementasyonu
   ══════════════════════════════════════════════════════════ */

void yigin_baslat(Yigin *y)          { y->tepe = -1; }
int  yigin_bos_mu(const Yigin *y)    { return y->tepe == -1; }
int  yigin_dolu_mu(const Yigin *y)   { return y->tepe == YIGIN_KAPASITESI - 1; }

void yigin_it(Yigin *y, IslemKaydi kayit) {
    if (yigin_dolu_mu(y)) {
        printf(STL_HATA "[YIGIN] Dolu! En eski islem siliniyor.\n" SIFIRLA);
        /* Shift left — en eski kaydı at */
        for (int i = 0; i < YIGIN_KAPASITESI - 1; i++)
            y->veri[i] = y->veri[i + 1];
        y->veri[y->tepe] = kayit;
        return;
    }
    y->veri[++y->tepe] = kayit;
}

IslemKaydi yigin_cek(Yigin *y) {
    if (yigin_bos_mu(y)) {
        printf(STL_UYARI "[YIGIN] Bos — geri alinacak islem yok.\n" SIFIRLA);
        IslemKaydi bos = {0}; return bos;
    }
    return y->veri[y->tepe--];
}

IslemKaydi* yigin_bak(Yigin *y) {
    if (yigin_bos_mu(y)) return NULL;
    return &y->veri[y->tepe];
}

/* ══════════════════════════════════════════════════════════
   KUYRUK (Queue) implementasyonu
   ══════════════════════════════════════════════════════════ */

void kuyruk_baslat(Kuyruk *k) { k->on = k->arka = k->sayi = 0; }
int  kuyruk_bos_mu(const Kuyruk *k)  { return k->sayi == 0; }
int  kuyruk_dolu_mu(const Kuyruk *k) { return k->sayi == KUYRUK_KAPASITESI; }

/* Enqueue ──────────────────────────────────────────────── */
int kuyruk_ekle(Kuyruk *k, const Gorev *g) {
    if (kuyruk_dolu_mu(k)) {
        printf(STL_HATA "[KUYRUK] Dolu!\n" SIFIRLA); return -1;
    }
    k->veri[k->arka] = *g;
    k->arka = (k->arka + 1) % KUYRUK_KAPASITESI;
    k->sayi++;
    return 0;
}

/* Dequeue ──────────────────────────────────────────────── */
int kuyruk_cikar(Kuyruk *k, Gorev *g) {
    if (kuyruk_bos_mu(k)) {
        printf(STL_UYARI "[KUYRUK] Bos!\n" SIFIRLA); return -1;
    }
    *g = k->veri[k->on];
    k->on = (k->on + 1) % KUYRUK_KAPASITESI;
    k->sayi--;
    return 0;
}

/* Peek ─────────────────────────────────────────────────── */
Gorev* kuyruk_bak(Kuyruk *k) {
    if (kuyruk_bos_mu(k)) return NULL;
    return &k->veri[k->on];
}

/* Listele ──────────────────────────────────────────────── */
void kuyruk_listele(const Kuyruk *k) {
    if (k->sayi == 0) { printf(STL_UYARI "  [KUYRUK] Bos.\n" SIFIRLA); return; }
    printf(STL_BASLIK "\n=== GOREV KUYRUGU (%d gorev) ===\n" SIFIRLA, k->sayi);
    for (int i = 0; i < k->sayi; i++) {
        int idx = (k->on + i) % KUYRUK_KAPASITESI;
        printf(P_SARI "  [%d] " SIFIRLA, i + 1);
        gorev_yazdir(&k->veri[idx]);
    }
}
