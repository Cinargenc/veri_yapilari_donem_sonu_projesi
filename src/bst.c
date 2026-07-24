#include "bst.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>

void bst_baslat(BST *bst) { bst->kok = NULL; }

static BSTDugum* dugum_olustur(const Gorev *g) {
    BSTDugum *d = (BSTDugum*)malloc(sizeof(BSTDugum));
    if (!d) return NULL;
    d->veri = *g; d->sol = d->sag = NULL;
    return d;
}

/* BST anahtarı: son_tarih (eşitlik durumunda id) */
static int bst_cmp(const Gorev *a, const Gorev *b) {
    double d = difftime(a->son_tarih, b->son_tarih);
    if (d != 0) return (d > 0) - (d < 0);
    return a->id - b->id;
}

/* Ekle ─────────────────────────────────────────────────── */
static BSTDugum* _ekle(BSTDugum *kok, const Gorev *g) {
    if (!kok) return dugum_olustur(g);
    if (bst_cmp(g, &kok->veri) < 0) kok->sol = _ekle(kok->sol, g);
    else                             kok->sag = _ekle(kok->sag, g);
    return kok;
}
void bst_ekle(BST *bst, const Gorev *g) { bst->kok = _ekle(bst->kok, g); }

/* Ara (ID'ye göre — tüm ağacı tara) ───────────────────── */
static BSTDugum* _ara_id(BSTDugum *k, int id) {
    if (!k) return NULL;
    if (k->veri.id == id) return k;
    BSTDugum *sol = _ara_id(k->sol, id);
    return sol ? sol : _ara_id(k->sag, id);
}
BSTDugum* bst_ara(BST *bst, int id) { return _ara_id(bst->kok, id); }

/* En küçük düğüm (sil için) */
static BSTDugum* _en_kucuk(BSTDugum *k) {
    while (k->sol) { k = k->sol; } return k;
}

/* Sil ──────────────────────────────────────────────────── */
static BSTDugum* _sil(BSTDugum *k, int id) {
    if (!k) return NULL;
    if (k->veri.id == id) {
        if (!k->sol) { BSTDugum *sag = k->sag; free(k); return sag; }
        if (!k->sag) { BSTDugum *sol = k->sol; free(k); return sol; }
        BSTDugum *hef = _en_kucuk(k->sag);
        k->veri = hef->veri;
        k->sag  = _sil(k->sag, hef->veri.id);
    } else {
        k->sol = _sil(k->sol, id);
        k->sag = _sil(k->sag, id);
    }
    return k;
}
void bst_sil(BST *bst, int id) { bst->kok = _sil(bst->kok, id); }

/* Güncelle ─────────────────────────────────────────────── */
int bst_guncelle(BST *bst, const Gorev *g) {
    bst_sil(bst, g->id);
    bst_ekle(bst, g);
    return 0;
}

/* In-order (tarih sırası) yazdır ───────────────────────── */
static void _inorder(const BSTDugum *k) {
    if (!k) return;
    _inorder(k->sol);
    gorev_yazdir(&k->veri);
    _inorder(k->sag);
}
void bst_inorder_yazdir(const BST *bst) {
    if (!bst->kok) { printf(STL_UYARI "  [BST] Bos.\n" SIFIRLA); return; }
    printf(STL_BASLIK "\n=== BST - TARIH SIRALI GOREVLER ===\n" SIFIRLA);
    _inorder(bst->kok);
}

/* Aralık sorgusu (pruning ile — BST sıralı yapısından yararlan) */
static void _aralik(const BSTDugum *k, time_t bas, time_t bit, int *sayac) {
    if (!k) return;
    /* Sol alt ağaca sadece mevcut düğüm başlangıçtan büyükse git */
    if (difftime(k->veri.son_tarih, bas) > 0)
        _aralik(k->sol, bas, bit, sayac);
    /* Mevcut düğüm aralıkta mı? */
    if (difftime(k->veri.son_tarih, bas) >= 0 &&
        difftime(bit, k->veri.son_tarih) >= 0) {
        gorev_yazdir(&k->veri);
        (*sayac)++;
    }
    /* Sağ alt ağaca sadece mevcut düğüm bitişten küçükse git */
    if (difftime(bit, k->veri.son_tarih) > 0)
        _aralik(k->sag, bas, bit, sayac);
}
void bst_aralik_sorgula(BST *bst, time_t baslangic, time_t bitis) {
    int sayac = 0;
    printf(STL_BASLIK "\n=== BST ARALIK SORGULAMA ===\n" SIFIRLA);
    _aralik(bst->kok, baslangic, bitis, &sayac);
    printf(P_YESIL "  Toplam %d gorev bulundu.\n" SIFIRLA, sayac);
}

/* Temizle ──────────────────────────────────────────────── */
static void _temizle(BSTDugum *k) {
    if (!k) return;
    _temizle(k->sol); _temizle(k->sag); free(k);
}
void bst_temizle(BST *bst) { _temizle(bst->kok); bst->kok = NULL; }
