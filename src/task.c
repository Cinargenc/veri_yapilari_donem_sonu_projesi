#include "task.h"
#include "colors.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ── ID üreteci ─────────────────────────────────────────── */
static int sonraki_id = 1;

int id_uret(void)               { return sonraki_id++; }
void id_baslangic_ayarla(int n) { if (n >= sonraki_id) sonraki_id = n + 1; }

/* ── Metin dönüştürücüler ───────────────────────────────── */
const char* durum_yazi(GorevDurum d) {
    switch (d) {
        case BEKLIYOR:     return "Bekliyor";
        case DEVAM_EDIYOR: return "Devam Ediyor";
        case TAMAMLANDI:   return "Tamamlandi";
        default:           return "?";
    }
}
const char* oncelik_yazi(int o) {
    switch (o) {
        case 1: return "Dusuk";
        case 2: return "Normal";
        case 3: return "Orta";
        case 4: return "Yuksek";
        case 5: return "Kritik";
        default: return "?";
    }
}
const char* oncelik_renk(int o) {
    switch (o) {
        case 5: return P_KIRMIZI;
        case 4: return KIRMIZI;
        case 3: return P_SARI;
        case 2: return P_YESIL;
        default: return CAMGOBEGI;
    }
}
const char* durum_renk(GorevDurum d) {
    switch (d) {
        case BEKLIYOR:     return P_SARI;
        case DEVAM_EDIYOR: return P_MAVI;
        case TAMAMLANDI:   return P_YESIL;
        default:           return BEYAZ;
    }
}

/* ── Tarih yazdırma (NULL-safe) ─────────────────────────── */
char* tarih_yazi(time_t t, char *buf, int len) {
    if (t <= 0) {
        snprintf(buf, len, "(tarih yok)");
        return buf;
    }
    struct tm *tm_info = localtime(&t);
    if (!tm_info) {
        snprintf(buf, len, "(gecersiz tarih)");
        return buf;
    }
    strftime(buf, len, "%d/%m/%Y %H:%M", tm_info);
    return buf;
}

/* ── Görev yazdır ───────────────────────────────────────── */
void gorev_yazdir(const Gorev *g) {
    char tbuf[32];
    tarih_yazi(g->son_tarih, tbuf, sizeof(tbuf));

    printf(KALIN "+-----------------------------------------------------------+\n" SIFIRLA);
    printf(KALIN "| " P_CAMGOBEGI "ID:%-4d" SIFIRLA " " KALIN "Baslik: " P_BEYAZ "%s" SIFIRLA "\n" SIFIRLA,
           g->id, g->baslik);
    printf("| Aciklama : %s\n", g->aciklama);
    printf("| Kategori : %s    Oncelik: %s%s" SIFIRLA "\n",
           g->kategori, oncelik_renk(g->oncelik), oncelik_yazi(g->oncelik));
    printf("| Son Tar. : %s    Durum  : %s%s" SIFIRLA "\n",
           tbuf, durum_renk(g->durum), durum_yazi(g->durum));
    if (g->bagim_sayi > 0) {
        printf("| Bagiml.  : ");
        for (int i = 0; i < g->bagim_sayi; i++) printf(P_SARI "#%d " SIFIRLA, g->bagimliliklar[i]);
        printf("\n");
    }
    printf(KALIN "+-----------------------------------------------------------+\n" SIFIRLA);
}


/* ── UTF-8 güvenli satır okuma ─────────────────────────── */
/* Windows CMD'de fgets() UTF-8 multi-byte karakterleri
   yanlış sayar ve erken keser. ReadConsoleW ile okuyup
   UTF-8'e dönüştürüyoruz. */
void utf8_satir_oku(char *buf, int buf_boyut) {
#ifdef _WIN32
    wchar_t wbuf[512];
    DWORD okunan = 0;
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

    if (ReadConsoleW(hIn, wbuf, 511, &okunan, NULL) && okunan > 0) {
        /* Sondaki \r\n'yi kaldır */
        while (okunan > 0 && (wbuf[okunan-1] == L'\n' || wbuf[okunan-1] == L'\r'))
            okunan--;
        wbuf[okunan] = L'\0';

        WideCharToMultiByte(CP_UTF8, 0, wbuf, -1, buf, buf_boyut, NULL, NULL);
    } else {
        buf[0] = '\0';
    }
#else
    if (fgets(buf, buf_boyut, stdin))
        buf[strcspn(buf, "\n")] = 0;
    else
        buf[0] = '\0';
#endif
}

/* ── Sayısal giriş (scanf yerine — UTF-8 uyumlu) ──────── */
int sayi_oku(void) {
    char satir[64];
    utf8_satir_oku(satir, sizeof(satir));
    return atoi(satir);
}

/* ── Görev girişi ───────────────────────────────────────── */
void gorev_gir(Gorev *g, int id) {
    int gun, ay, yil, saat = 0, dakika = 0, tmp;
    struct tm tm_info = {0};
    memset(g, 0, sizeof(Gorev));
    g->id = id;

    printf(STL_BILGI "  Baslik     : " SIFIRLA);
    utf8_satir_oku(g->baslik, MAX_BASLIK);

    printf(STL_BILGI "  Aciklama   : " SIFIRLA);
    utf8_satir_oku(g->aciklama, MAX_ACIKLAMA);

    printf(STL_BILGI "  Kategori   : " SIFIRLA);
    utf8_satir_oku(g->kategori, MAX_KATEGORI);

    do {
        printf(STL_BILGI "  Oncelik (1-5): " SIFIRLA);
        g->oncelik = sayi_oku();
    } while (g->oncelik < 1 || g->oncelik > 5);

    /* Tarih girişi — saat:dakika opsiyonel */
    int tarih_ok = 0;
    while (!tarih_ok) {
        printf(STL_BILGI "  Son Tarih (GG/AA/YYYY veya GG/AA/YYYY SS:DD): " SIFIRLA);
        char satir[128];
        utf8_satir_oku(satir, sizeof(satir));

        saat = 23; dakika = 59;  /* varsayılan: günün sonu */
        int okunan = sscanf(satir, "%d/%d/%d %d:%d", &gun, &ay, &yil, &saat, &dakika);
        if (okunan >= 3) {
            /* Tarih doğrulama */
            if (gun < 1 || gun > 31 || ay < 1 || ay > 12 || yil < 2000 || yil > 2100) {
                printf(STL_HATA "  Gecersiz tarih! (GG:1-31, AA:1-12, YYYY:2000-2100)\n" SIFIRLA);
                continue;
            }
            if (saat < 0 || saat > 23 || dakika < 0 || dakika > 59) {
                printf(STL_HATA "  Gecersiz saat! (SS:0-23, DD:0-59)\n" SIFIRLA);
                continue;
            }
            tm_info.tm_mday = gun; tm_info.tm_mon = ay - 1;
            tm_info.tm_year = yil - 1900; tm_info.tm_hour = saat;
            tm_info.tm_min  = dakika; tm_info.tm_isdst = -1;
            g->son_tarih = mktime(&tm_info);
            if (g->son_tarih == (time_t)-1) {
                printf(STL_HATA "  Tarih donusturme hatasi! Tekrar deneyin.\n" SIFIRLA);
                continue;
            }
            tarih_ok = 1;
        } else {
            printf(STL_HATA "  Hatali format! Ornek: 15/06/2026 veya 15/06/2026 14:30\n" SIFIRLA);
        }
    }

    do {
        printf(STL_BILGI "  Durum (0=Bekliyor 1=Devam 2=Tamam): " SIFIRLA);
        tmp = sayi_oku();
    } while (tmp < 0 || tmp > 2);
    g->durum = (GorevDurum)tmp;
}
