#ifndef COLORS_H
#define COLORS_H

#ifdef _WIN32
#include <windows.h>
#endif
#include <locale.h>

/* ── ANSI Kaçış Kodları ─────────────────────────────────── */
#define SIFIRLA          "\033[0m"
#define KALIN            "\033[1m"
#define ALTI_CIZILI      "\033[4m"

/* Ön plan renkleri */
#define SIYAH            "\033[30m"
#define KIRMIZI          "\033[31m"
#define YESIL            "\033[32m"
#define SARI             "\033[33m"
#define MAVI             "\033[34m"
#define MAGENTA          "\033[35m"
#define CAMGOBEGI        "\033[36m"
#define BEYAZ            "\033[37m"

/* Parlak renkler */
#define P_KIRMIZI        "\033[91m"
#define P_YESIL          "\033[92m"
#define P_SARI           "\033[93m"
#define P_MAVI           "\033[94m"
#define P_MAGENTA        "\033[95m"
#define P_CAMGOBEGI      "\033[96m"
#define P_BEYAZ          "\033[97m"

/* Arka plan */
#define ARK_KIRMIZI      "\033[41m"
#define ARK_YESIL        "\033[42m"
#define ARK_MAVI         "\033[44m"
#define ARK_MAGENTA      "\033[45m"

/* Hazır stiller */
#define STL_BASLIK       KALIN P_CAMGOBEGI
#define STL_HATA         KALIN P_KIRMIZI
#define STL_BASARI       KALIN P_YESIL
#define STL_UYARI        KALIN P_SARI
#define STL_BILGI        P_MAVI
#define STL_VURGU        KALIN P_BEYAZ

/* Windows'ta ANSI ve UTF-8'i etkinleştir */
static inline void konsol_hazirla(void) {
    setlocale(LC_ALL, ".UTF-8");
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    /* Çıkış: ANSI renk desteği */
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD  mOut = 0;
    GetConsoleMode(hOut, &mOut);
    SetConsoleMode(hOut, mOut | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif
}

#endif /* COLORS_H */
