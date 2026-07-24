#ifndef GRAPH_H
#define GRAPH_H

#include "task.h"

#define MAKS_DUGUM 256

/* ── Komşuluk listesi ile yönlü graf ───────────────────── */
typedef struct GrafKenar {
    int              hedef_id;
    struct GrafKenar *sonraki;
} GrafKenar;

typedef struct {
    int       dugum_idler[MAKS_DUGUM];  /* kayıtlı görev ID'leri */
    GrafKenar *komsular[MAKS_DUGUM];    /* adjacency list         */
    int       dugum_sayi;
} Graf;

void graf_baslat(Graf *g);
void graf_dugum_ekle(Graf *g, int id);
void graf_dugum_sil(Graf *g, int id);
int  graf_kenar_ekle(Graf *g, int kaynak, int hedef);  /* bağımlılık */
int  graf_kenar_sil(Graf *g, int kaynak, int hedef);
void graf_topologik_sirala(Graf *g);                   /* Kahn + BFS */
int  graf_dongu_var_mi(Graf *g);                       /* DFS        */
void graf_ascii_ciz(const Graf *g);                    /* ASCII görsel */
void graf_komsulari_yazdir(const Graf *g, int id);

#endif
