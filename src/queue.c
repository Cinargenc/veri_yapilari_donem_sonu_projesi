#include "queue.h"
#include "colors.h"
#include <stdio.h>

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
