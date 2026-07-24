#include "graph.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ── İndeks yardımcıları ────────────────────────────────── */
static int idx_bul(const Graf *g, int id) {
    for (int i = 0; i < g->dugum_sayi; i++)
        if (g->dugum_idler[i] == id) return i;
    return -1;
}

void graf_baslat(Graf *g) {
    memset(g, 0, sizeof(Graf));
}

/* Düğüm ekle ────────────────────────────────────────────── */
void graf_dugum_ekle(Graf *g, int id) {
    if (idx_bul(g, id) >= 0) return;  /* zaten var */
    if (g->dugum_sayi >= MAKS_DUGUM) return;
    g->dugum_idler[g->dugum_sayi] = id;
    g->komsular[g->dugum_sayi]    = NULL;
    g->dugum_sayi++;
}

/* Düğüm sil ─────────────────────────────────────────────── */
void graf_dugum_sil(Graf *g, int id) {
    int idx = idx_bul(g, id);
    if (idx < 0) return;
    /* Komşu listesini temizle */
    GrafKenar *k = g->komsular[idx];
    while (k) { GrafKenar *t = k->sonraki; free(k); k = t; }
    /* Diğer düğümlerin bu ID'ye olan kenarlarını sil */
    for (int i = 0; i < g->dugum_sayi; i++) {
        GrafKenar **prev = &g->komsular[i];
        while (*prev) {
            if ((*prev)->hedef_id == id) {
                GrafKenar *t = *prev; *prev = t->sonraki; free(t);
            } else prev = &(*prev)->sonraki;
        }
    }
    /* Diziyi sıkıştır */
    g->dugum_idler[idx] = g->dugum_idler[g->dugum_sayi - 1];
    g->komsular[idx]    = g->komsular[g->dugum_sayi - 1];
    g->dugum_sayi--;
}

/* Kenar ekle (kaynak → hedef bağımlılığı) ──────────────── */
int graf_kenar_ekle(Graf *g, int kaynak, int hedef) {
    int k = idx_bul(g, kaynak);
    if (k < 0) { printf(STL_HATA "[GRAF] Kaynak ID bulunamadi.\n" SIFIRLA); return -1; }
    GrafKenar *e = (GrafKenar*)malloc(sizeof(GrafKenar));
    if (!e) return -1;
    e->hedef_id = hedef;
    e->sonraki  = g->komsular[k];
    g->komsular[k] = e;
    return 0;
}

/* Kenar sil ─────────────────────────────────────────────── */
int graf_kenar_sil(Graf *g, int kaynak, int hedef) {
    int k = idx_bul(g, kaynak);
    if (k < 0) return -1;
    GrafKenar **prev = &g->komsular[k];
    while (*prev) {
        if ((*prev)->hedef_id == hedef) {
            GrafKenar *t = *prev; *prev = t->sonraki; free(t); return 0;
        }
        prev = &(*prev)->sonraki;
    }
    return -1;
}

/* ── Kahn BFS Topolojik Sıralama ─────────────────────────── */
void graf_topologik_sirala(Graf *g) {
    int n = g->dugum_sayi;
    if (n == 0) { printf(STL_UYARI "  [GRAF] Bos.\n" SIFIRLA); return; }

    int in_derece[MAKS_DUGUM] = {0};
    /* In-derece hesapla */
    for (int i = 0; i < n; i++) {
        GrafKenar *k = g->komsular[i];
        while (k) {
            int hi = idx_bul(g, k->hedef_id);
            if (hi >= 0) in_derece[hi]++;
            k = k->sonraki;
        }
    }
    /* Sıfır in-dereceli düğümleri kuyruğa al */
    int kuyruk[MAKS_DUGUM], on = 0, arka = 0;
    for (int i = 0; i < n; i++)
        if (in_derece[i] == 0) kuyruk[arka++] = i;

    printf(STL_BASLIK "\n=== TOPOLOGIK GOREV SIRASI ===\n" SIFIRLA);
    int islem = 0;
    while (on < arka) {
        int idx = kuyruk[on++];
        printf(P_CAMGOBEGI "  Adim %d" SIFIRLA " --> Gorev ID: " P_BEYAZ "%d\n" SIFIRLA,
               ++islem, g->dugum_idler[idx]);
        GrafKenar *k = g->komsular[idx];
        while (k) {
            int hi = idx_bul(g, k->hedef_id);
            if (hi >= 0 && --in_derece[hi] == 0) kuyruk[arka++] = hi;
            k = k->sonraki;
        }
    }
    if (islem != n)
        printf(STL_HATA "  [UYARI] Dongude %d gorev var!\n" SIFIRLA, n - islem);
}

/* ── DFS döngü tespiti ───────────────────────────────────── */
static int dfs_dongu(const Graf *g, int idx, int *ziyaret, int *yigin) {
    ziyaret[idx] = yigin[idx] = 1;
    GrafKenar *k = g->komsular[idx];
    while (k) {
        int hi = idx_bul(g, k->hedef_id);
        if (hi >= 0) {
            if (!ziyaret[hi] && dfs_dongu(g, hi, ziyaret, yigin)) return 1;
            if (yigin[hi]) return 1;
        }
        k = k->sonraki;
    }
    yigin[idx] = 0;
    return 0;
}

int graf_dongu_var_mi(Graf *g) {
    int ziyaret[MAKS_DUGUM] = {0}, yigin[MAKS_DUGUM] = {0};
    for (int i = 0; i < g->dugum_sayi; i++)
        if (!ziyaret[i] && dfs_dongu(g, i, ziyaret, yigin)) return 1;
    return 0;
}

/* ── ASCII Görselleştirme ────────────────────────────────── */
void graf_ascii_ciz(const Graf *g) {
    printf(STL_BASLIK "\n=== BAGIMLILIK GRAFI (ASCII) ===\n" SIFIRLA);
    if (g->dugum_sayi == 0) { printf(STL_UYARI "  Bos.\n" SIFIRLA); return; }
    for (int i = 0; i < g->dugum_sayi; i++) {
        printf(P_CAMGOBEGI "  [G#%d]" SIFIRLA, g->dugum_idler[i]);
        GrafKenar *k = g->komsular[i];
        if (!k) { printf(" (bagimsiz)\n"); continue; }
        while (k) {
            printf(P_SARI " ---> " SIFIRLA P_BEYAZ "[G#%d]" SIFIRLA, k->hedef_id);
            k = k->sonraki;
        }
        printf("\n");
    }
}

/* Komşuları yazdır */
void graf_komsulari_yazdir(const Graf *g, int id) {
    int idx = idx_bul(g, id);
    if (idx < 0) { printf(STL_HATA "  ID bulunamadi.\n" SIFIRLA); return; }
    printf(P_MAVI "  Gorev #%d bagimli olduklari:\n" SIFIRLA, id);
    GrafKenar *k = g->komsular[idx];
    if (!k) { printf("  (Bagimlilik yok)\n"); return; }
    while (k) { printf("    --> Gorev #%d\n", k->hedef_id); k = k->sonraki; }
}
