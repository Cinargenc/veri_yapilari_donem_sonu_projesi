#ifndef TASK_H
#define TASK_H

#include <time.h>

/* ── Sabitler ───────────────────────────────────────────── */
#define MAX_BASLIK       128
#define MAX_ACIKLAMA     256
#define MAX_KATEGORI     64
#define MAX_BAGIMLILIK   20
#define MAKS_GOREV       1000

/* ── Durum sabit listesi ────────────────────────────────── */
typedef enum {
    BEKLIYOR      = 0,
    DEVAM_EDIYOR  = 1,
    TAMAMLANDI    = 2
} GorevDurum;

/* ── Ana veri modeli ────────────────────────────────────── */
typedef struct {
    int        id;
    char       baslik[MAX_BASLIK];
    char       aciklama[MAX_ACIKLAMA];
    int        oncelik;                    /* 1=Düşük … 5=Kritik */
    time_t     son_tarih;                  /* Unix timestamp      */
    char       kategori[MAX_KATEGORI];
    GorevDurum durum;
    int        bagimliliklar[MAX_BAGIMLILIK];
    int        bagim_sayi;
} Gorev;

/* ── Yardımcı fonksiyonlar ──────────────────────────────── */
const char* durum_yazi(GorevDurum d);
const char* oncelik_yazi(int o);
const char* oncelik_renk(int o);
const char* durum_renk(GorevDurum d);
char*       tarih_yazi(time_t t, char *buf, int len);
void        gorev_yazdir(const Gorev *g);
void        gorev_gir(Gorev *g, int id);
int         id_uret(void);
void        id_baslangic_ayarla(int id);
void        utf8_satir_oku(char *buf, int buf_boyut);
int         sayi_oku(void);

#endif /* TASK_H */
