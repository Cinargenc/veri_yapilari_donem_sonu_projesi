#include "file_io.h"
#include "colors.h"
#include <stdio.h>

/* ── Görevleri .bin dosyasına yaz ──────────────────────── */
int dosyaya_kaydet(const Gorev *gorevler, int sayi) {
    FILE *fp = fopen(DOSYA_ADI, "wb");
    if (!fp) {
        printf(STL_HATA "[HATA] Dosya acilamadi: %s\n" SIFIRLA, DOSYA_ADI);
        return -1;
    }
    /* Önce kayıt sayısını yaz */
    fwrite(&sayi, sizeof(int), 1, fp);
    /* Ardından tüm görev yapılarını yaz */
    fwrite(gorevler, sizeof(Gorev), sayi, fp);
    fclose(fp);
    printf(STL_BASARI "[KAYIT] %d gorev '%s' dosyasina kaydedildi.\n" SIFIRLA,
           sayi, DOSYA_ADI);
    return sayi;
}

/* ── Görevleri .bin dosyasından oku ────────────────────── */
int dosyadan_yukle(Gorev *gorevler, int maks) {
    FILE *fp = fopen(DOSYA_ADI, "rb");
    if (!fp) return 0;   /* Dosya yoksa sessizce çık */

    int sayi = 0;
    fread(&sayi, sizeof(int), 1, fp);
    if (sayi > maks) sayi = maks;
    int okunan = (int)fread(gorevler, sizeof(Gorev), sayi, fp);
    fclose(fp);
    printf(STL_BASARI "[YUKLE] %d gorev '%s' dosyasindan yuklendi.\n" SIFIRLA,
           okunan, DOSYA_ADI);
    return okunan;
}
