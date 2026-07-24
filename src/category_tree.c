#include "category_tree.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static KatDugum* dugum_olustur(const char *ad) {
    KatDugum *d = (KatDugum*)calloc(1, sizeof(KatDugum));
    if (!d) return NULL;
    strncpy(d->ad, ad, MAX_KATEGORI - 1);
    return d;
}

void kat_baslat(KategoriAgaci *ka) {
    ka->kok = dugum_olustur("Kok");
}

/* BFS ile düğüm bul ────────────────────────────────────── */
KatDugum* kat_dugum_bul(KatDugum *k, const char *ad) {
    if (!k) return NULL;
    if (strcmp(k->ad, ad) == 0) return k;
    for (int i = 0; i < k->cocuk_sayi; i++) {
        KatDugum *b = kat_dugum_bul(k->cocuklar[i], ad);
        if (b) return b;
    }
    return NULL;
}

/* Kategori ekle ─────────────────────────────────────────── */
KatDugum* kat_ekle(KategoriAgaci *ka, const char *ebeveyn_ad, const char *yeni_ad) {
    KatDugum *eb = kat_dugum_bul(ka->kok, ebeveyn_ad);
    if (!eb) { printf(STL_HATA "  [KAT] Ebeveyn bulunamadi: %s\n" SIFIRLA, ebeveyn_ad); return NULL; }
    if (eb->cocuk_sayi >= MAKS_COCUK) { printf(STL_HATA "  [KAT] Cocuk limiti doldu.\n" SIFIRLA); return NULL; }
    /* Zaten varsa döndür */
    KatDugum *var = kat_dugum_bul(ka->kok, yeni_ad);
    if (var) return var;
    KatDugum *yeni = dugum_olustur(yeni_ad);
    eb->cocuklar[eb->cocuk_sayi++] = yeni;
    return yeni;
}

/* Görevi kategoriye ekle ────────────────────────────────── */
void kat_gorev_ekle(KategoriAgaci *ka, const char *kat_ad, int gorev_id) {
    KatDugum *d = kat_dugum_bul(ka->kok, kat_ad);
    if (!d) d = kat_ekle(ka, "Kok", kat_ad);  /* otomatik oluştur */
    if (!d || d->gorev_sayi >= MAKS_KAT_GOREV) return;
    /* Zaten eklenmiş mi? */
    for (int i = 0; i < d->gorev_sayi; i++)
        if (d->gorev_idler[i] == gorev_id) return;
    d->gorev_idler[d->gorev_sayi++] = gorev_id;
}

/* Görevi kategoriden sil ─────────────────────────────────── */
void kat_gorev_sil(KategoriAgaci *ka, const char *kat_ad, int gorev_id) {
    KatDugum *d = kat_dugum_bul(ka->kok, kat_ad);
    if (!d) return;
    for (int i = 0; i < d->gorev_sayi; i++) {
        if (d->gorev_idler[i] == gorev_id) {
            d->gorev_idler[i] = d->gorev_idler[--d->gorev_sayi];
            return;
        }
    }
}

/* Ağacı yazdır (girinti ile) ────────────────────────────── */
void kat_yazdir(const KatDugum *k, int seviye) {
    if (!k) return;
    /* Girinti çiz */
    for (int i = 0; i < seviye; i++) printf("  ");
    if (seviye == 0)
        printf(STL_BASLIK "[%s]\n" SIFIRLA, k->ad);
    else
        printf(P_CAMGOBEGI "|__ " P_BEYAZ "%s" SIFIRLA " (%d gorev)\n", k->ad, k->gorev_sayi);

    /* Görev ID listesi */
    if (k->gorev_sayi > 0) {
        for (int i = 0; i < seviye + 1; i++) printf("  ");
        printf(P_SARI "Gorevler: ");
        for (int i = 0; i < k->gorev_sayi; i++)
            printf("#%d ", k->gorev_idler[i]);
        printf(SIFIRLA "\n");
    }
    for (int i = 0; i < k->cocuk_sayi; i++)
        kat_yazdir(k->cocuklar[i], seviye + 1);
}

/* Belleği temizle ───────────────────────────────────────── */
void kat_temizle(KatDugum *k) {
    if (!k) return;
    for (int i = 0; i < k->cocuk_sayi; i++) kat_temizle(k->cocuklar[i]);
    free(k);
}
