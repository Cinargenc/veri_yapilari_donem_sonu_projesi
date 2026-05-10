#include "priority_queue.h"
#include "colors.h"
#include <stdio.h>
#include <time.h>

void ok_baslat(OncelikKuyrugu *ok) { ok->sayi = 0; ok->referans_zaman = time(NULL); }
int  ok_bos_mu(const OncelikKuyrugu *ok) { return ok->sayi == 0; }

/* ── Öncelik skoru ──────────────────────────────────────── *
 * Küçük skor = daha acil görev (min-heap)                   *
 *                                                           *
 * Süresi geçmiş:  skor = -100 + (kalan_gun) - oncelik      *
 *                 → ne kadar geçmişse o kadar acil          *
 * Tarih var:      skor = kalan_gun / oncelik                *
 *                 → yakın deadline + yüksek öncelik = acil  *
 * Tarih yok:      skor = 14 / oncelik                       *
 *                 → 14 gün kalmış gibi değerlendirilir      *
 * ──────────────────────────────────────────────────────── */
double ok_skor_ref(const Gorev *g, time_t ref) {
    int onc = g->oncelik;
    if (onc < 1) onc = 1;  /* 0'a bölme koruması */

    /* Tarih girilmemişse → 14 gün kalmış gibi değerlendir, önceliğe göre sırala */
    if (g->son_tarih <= 0) {
        return 14.0 / onc;
        /* Kritik(5)=2.8, Yuksek(4)=3.5, Orta(3)=4.7, Normal(2)=7.0, Dusuk(1)=14.0 */
    }

    double kalan_gun = difftime(g->son_tarih, ref) / 86400.0;
    if (kalan_gun < 0) {
        /* Süresi geçmiş — en acil: ne kadar geçmişse ve yüksek öncelikse o kadar acil */
        return -100.0 + kalan_gun - onc;
    }
    return kalan_gun / onc;
}

double ok_skor(const Gorev *g) {
    return ok_skor_ref(g, time(NULL));
}

/* Heap yardımcıları — referans zamanı kullanarak tutarlı karşılaştırma */
static double skor_hesapla(const OncelikKuyrugu *ok, int i) {
    return ok_skor_ref(&ok->veri[i], ok->referans_zaman);
}

static void yukari_tasima(OncelikKuyrugu *ok, int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (skor_hesapla(ok, parent) > skor_hesapla(ok, i)) {
            Gorev tmp = ok->veri[parent];
            ok->veri[parent] = ok->veri[i];
            ok->veri[i] = tmp;
            i = parent;
        } else break;
    }
}

static void asagi_tasima(OncelikKuyrugu *ok, int i) {
    int n = ok->sayi;
    while (1) {
        int en_kucuk = i, sol = 2*i+1, sag = 2*i+2;
        if (sol < n && skor_hesapla(ok, sol) < skor_hesapla(ok, en_kucuk))
            en_kucuk = sol;
        if (sag < n && skor_hesapla(ok, sag) < skor_hesapla(ok, en_kucuk))
            en_kucuk = sag;
        if (en_kucuk == i) break;
        Gorev tmp = ok->veri[i]; ok->veri[i] = ok->veri[en_kucuk];
        ok->veri[en_kucuk] = tmp;
        i = en_kucuk;
    }
}

/* Referans zamanını güncelle ve heap'i yeniden düzenle */
void ok_yenile(OncelikKuyrugu *ok) {
    ok->referans_zaman = time(NULL);
    /* Tüm heap'i yeniden oluştur — O(n) */
    for (int i = ok->sayi / 2 - 1; i >= 0; i--)
        asagi_tasima(ok, i);
}

/* Ekle ─────────────────────────────────────────────────── */
void ok_ekle(OncelikKuyrugu *ok, const Gorev *g) {
    if (ok->sayi >= MAKS_GOREV) {
        printf(STL_HATA "[OK] Dolu!\n" SIFIRLA); return;
    }
    ok->veri[ok->sayi++] = *g;
    yukari_tasima(ok, ok->sayi - 1);
}

/* Extract-min ──────────────────────────────────────────── */
Gorev ok_en_acil_cikar(OncelikKuyrugu *ok) {
    Gorev bos = {0};
    if (ok_bos_mu(ok)) { printf(STL_UYARI "[OK] Bos!\n" SIFIRLA); return bos; }
    Gorev en_acil = ok->veri[0];
    ok->veri[0] = ok->veri[--ok->sayi];
    if (ok->sayi > 0) asagi_tasima(ok, 0);
    return en_acil;
}

/* Peek ─────────────────────────────────────────────────── */
Gorev* ok_en_acil_bak(OncelikKuyrugu *ok) {
    return ok_bos_mu(ok) ? NULL : &ok->veri[0];
}

/* Sil (ID'ye göre) ─────────────────────────────────────── */
int ok_sil(OncelikKuyrugu *ok, int id) {
    for (int i = 0; i < ok->sayi; i++) {
        if (ok->veri[i].id == id) {
            ok->veri[i] = ok->veri[--ok->sayi];
            if (i < ok->sayi) {
                yukari_tasima(ok, i);
                asagi_tasima(ok, i);
            }
            return 0;
        }
    }
    return -1;
}

/* ── Öncelik etiket rengi ──────────────────────────────── */
static const char* acillik_etiketi(double skor) {
    if (skor < -100.0) return P_KIRMIZI "!! SURESI GECMIS !!" SIFIRLA;
    if (skor < 1.0)    return P_KIRMIZI "COK ACIL" SIFIRLA;
    if (skor < 3.0)    return P_SARI    "ACIL" SIFIRLA;
    if (skor < 7.0)    return SARI      "ORTA" SIFIRLA;
    if (skor < 14.0)   return P_YESIL   "NORMAL" SIFIRLA;
    return CAMGOBEGI "DUSUK" SIFIRLA;
}

/* İlk n acil görevi listele ────────────────────────────── */
void ok_listele(const OncelikKuyrugu *ok, int n) {
    if (ok_bos_mu(ok)) { printf(STL_UYARI "  [OK] Bos.\n" SIFIRLA); return; }

    /* Listelemeden önce referans zamanını güncelle */
    OncelikKuyrugu tmp = *ok;
    tmp.referans_zaman = time(NULL);
    /* Heap'i yeni referans zamanıyla yeniden oluştur */
    for (int i = tmp.sayi / 2 - 1; i >= 0; i--)
        asagi_tasima(&tmp, i);

    if (n > tmp.sayi) n = tmp.sayi;
    printf(STL_BASLIK "\n=== EN ACIL %d GOREV (Min-Heap) ===\n" SIFIRLA, n);

    /* Geçici kopya üzerinde extract yaparak sıralı yazdır */
    for (int i = 0; i < n; i++) {
        Gorev g = ok_en_acil_cikar(&tmp);
        double skor = ok_skor(&g);
        printf(P_KIRMIZI "  [%d. Acil]" SIFIRLA " skor: %.4f  %s\n",
               i + 1, skor, acillik_etiketi(skor));
        gorev_yazdir(&g);
    }
}
