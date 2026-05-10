#ifndef FILE_IO_H
#define FILE_IO_H

#include "task.h"

#define DOSYA_ADI "gorevler.bin"

/* Tüm görevleri ikili dosyaya kaydeder, adet döner */
int dosyaya_kaydet(const Gorev *gorevler, int sayi);

/* Dosyadan görevleri yükler, okunan adet döner */
int dosyadan_yukle(Gorev *gorevler, int maks);

#endif
