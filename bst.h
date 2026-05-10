#ifndef BST_H
#define BST_H

#include "task.h"

/* ── İkili Arama Ağacı (deadline'a göre sıralı) ─────── */
typedef struct BSTDugum {
    Gorev           veri;
    struct BSTDugum *sol;
    struct BSTDugum *sag;
} BSTDugum;

typedef struct { BSTDugum *kok; } BST;

void     bst_baslat(BST *bst);
void     bst_ekle(BST *bst, const Gorev *g);
BSTDugum* bst_ara(BST *bst, int id);
void     bst_sil(BST *bst, int id);
void     bst_inorder_yazdir(const BST *bst);                     /* tarih sırası */
void     bst_aralik_sorgula(BST *bst, time_t baslangic, time_t bitis);
void     bst_temizle(BST *bst);
int      bst_guncelle(BST *bst, const Gorev *g);

#endif
