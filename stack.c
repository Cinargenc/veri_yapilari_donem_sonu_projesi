#include "stack.h"
#include "colors.h"
#include <stdio.h>

void yigin_baslat(Yigin *y)          { y->tepe = -1; }
int  yigin_bos_mu(const Yigin *y)    { return y->tepe == -1; }
int  yigin_dolu_mu(const Yigin *y)   { return y->tepe == YIGIN_KAPASITESI - 1; }

void yigin_it(Yigin *y, IslemKaydi kayit) {
    if (yigin_dolu_mu(y)) {
        printf(STL_HATA "[YIGIN] Dolu! En eski islem siliniyor.\n" SIFIRLA);
        /* Shift left — en eski kaydı at */
        for (int i = 0; i < YIGIN_KAPASITESI - 1; i++)
            y->veri[i] = y->veri[i + 1];
        y->veri[y->tepe] = kayit;
        return;
    }
    y->veri[++y->tepe] = kayit;
}

IslemKaydi yigin_cek(Yigin *y) {
    if (yigin_bos_mu(y)) {
        printf(STL_UYARI "[YIGIN] Bos — geri alinacak islem yok.\n" SIFIRLA);
        IslemKaydi bos = {0}; return bos;
    }
    return y->veri[y->tepe--];
}

IslemKaydi* yigin_bak(Yigin *y) {
    if (yigin_bos_mu(y)) return NULL;
    return &y->veri[y->tepe];
}
