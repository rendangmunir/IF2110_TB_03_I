/* File : tree.h */
/* ADT pohon N-Ary */
/* Representasi Address dengan pointer */

#include "treebalasan.h"

AddressBalasan NewTreeNodeBalasan(InfotypeBalasan root)
/* Mengalokasikan sebuah Address t, bernilai Nil jika tidak berhasil */
/* Mengirimkan Address hasil alokasi sebuah elemen bernilai root
   Jika alokasi berhasil, maka Address tidak Nil dan menghasilkan t
   ROOT(t) = val, SUBADDRESS(t) terdefinisi dengan ukuran INITIAL,
   TREECOUNT(t) = 0, dan TREECAPACITY(t) = INITIAL 
   Jika alokasi gagal, maka mengirimkan Nil */
{
	AddressBalasan t = (AddressBalasan) malloc(sizeof(NodeBalasan));

	if (t != Nil_BALASAN) 
	{
		ROOT_BALASAN(t) = root;
		SUBADDRESS_BALASAN(t) = (AddressBalasan*) malloc(INITIAL_BALASAN * sizeof(AddressBalasan*));
		TREECOUNT_BALASAN(t) = 0;
		TREECAPACITY_BALASAN(t) = INITIAL_BALASAN;
	}

	return t;
}

TreeBalasan NewTreeBalasan(InfotypeBalasan root, TreeBalasan child)
/* Jika alokasi berhasil, menghasilkan sebuah pohon dari root dan child;
   dan TREECOUNT bertambah satu jika child bukan Nil */
/* Jika alokasi gagal, menghasilkan pohon kosong (Nil) */
{
	AddressBalasan t = NewTreeNodeBalasan(root);
	if (t != Nil_BALASAN)
	{
		SUBTREE_BALASAN(t, TREECOUNT_BALASAN(t)) = child;

		if (child != Nil_BALASAN)
			TREECOUNT_BALASAN(t)++;
	}
	return t;
}

void CreateTreeBalasan(InfotypeBalasan root, TreeBalasan child, TreeBalasan *t)
/* I.S. : Sembarang
   F.S. : Menghasilkan sebuah pohon t
   		  Jika alokasi berhasil, menghasilkan sebuah pohon dari root dan child;
   		  dan TREECOUNT bertambah satu jika child bukan Nil
   		  Jika alokasi gagal, menghasilkan pohon kosong (Nil) */
{
	*t = NewTreeNodeBalasan(root);
	if (*t != Nil_BALASAN)
	{
		SUBTREE_BALASAN(*t, TREECOUNT_BALASAN(*t)) = child;

		if (child != Nil_BALASAN)
			TREECOUNT_BALASAN(*t)++;
	}
}

void ConnectChildBalasan(TreeBalasan child, TreeBalasan *t)
/* I.S. : t dan child terdefinisi
   F.S. : t terhubung dengan child dan TREECOUNT bertambah satu jika child bukan Nil */
{
	if (TREECOUNT_BALASAN(*t) == TREECAPACITY_BALASAN(*t))
		ExpandCapacityBalasan(t);

	SUBTREE_BALASAN(*t, TREECOUNT_BALASAN(*t)) = child;

	if (child != Nil_BALASAN)
		TREECOUNT_BALASAN(*t)++;
}

void ConnectParentBalasan(TreeBalasan parent, TreeBalasan *t)
/* I.S. : t dan parent terdefinisi
	F.S. : t menjadi child dari parent, ROOT(t) menjadi ROOT(parent) */
{
	ConnectChildBalasan(*t, &parent);

	*t = parent;
}

void DeallocateTreeBalasan(AddressBalasan t)
/* I.S. : t terdefinisi
   F.S. : t dikembalikan ke sistem
   Melakukan dealokasi/pengembalian Address t */
{
	free(t);
}

boolean HasNoChildBalasan(TreeBalasan t)
/* Mengirimkan true jika t tidak memiliki child */
{
	if (TREECOUNT_BALASAN(t) == 0)
		return true;
	return false;
}

boolean HasOneChildBalasan(TreeBalasan t)
/* Mengirimkan true jika t hanya memiliki 1 child */
{
	if (TREECOUNT_BALASAN(t) == 1)
		return true;
	return false;
}

/***** Display Tree *****/
void PrintTreeBalasan(TreeBalasan t)
/* I.S. : t terdefinisi
   F.S. : Semua simpul t sudah dicetak secara preorder: root dan child(ren)
   		  Setiap pohon ditandai dengan tanda kurung buka dan tanda kurung tutup ()
   		  Pohon kosong ditandai dengan () */
{
	if (t == Nil_BALASAN) {
		// printf("()");
	} else {
		printf("(");
		printf("%d", ROOT_BALASAN(t));
		int i;
		for (i = 0; i < TREECOUNT_BALASAN(t); i++)
			PrintTreeBalasan(SUBTREE_BALASAN(t,i));
		printf(")");
	}
}

void ExpandCapacityBalasan(TreeBalasan *t)
/* Proses: Memperbesar dua kali lipat capacity t */
/* I.S. : t terdefinisi */
/* F.S. : Ukuran SubTree menjadi dua kali lipat ukuran semula */
{
	TREECAPACITY_BALASAN(*t) *= 2;

	AddressBalasan *temp = SUBADDRESS_BALASAN(*t);

	SUBADDRESS_BALASAN(*t) = (AddressBalasan*) malloc(TREECAPACITY_BALASAN(*t) * sizeof(AddressBalasan*));
	TREECOUNT_BALASAN(*t) = 0;
	
	int i;
	for (i = 0; i < TREECAPACITY_BALASAN(*temp); i++)
		SUBTREE_BALASAN(*t,i) = SUBTREE_BALASAN(*temp,i);
}

void insertTreeBalasan(TreeBalasan t, int parentID, InfotypeBalasan child) {
	boolean found = false;
	TreeBalasan c = NewTreeBalasan(child, Nil_BALASAN);

	insertTreeRecursionBalasan(t, parentID, c, &found);
}

void insertTreeRecursionBalasan(TreeBalasan t, int parentID, TreeBalasan child, boolean* f) {
	if (t != Nil_BALASAN) {
		int i = 0;

		if (ROOT_BALASAN(t).id == parentID) {
			*f = true;
			ConnectChildBalasan(child, &t);
		}
			// if (operation == 'd') printf("(%d: %d)", ROOT(t), *f);

		while (i < TREECOUNT_BALASAN(t) && !(*f)) {
			insertTreeRecursionBalasan(SUBTREE_BALASAN(t, i), parentID, child, f);
			i += 1;
		}
	}
}

void deleteTreeBalasan(TreeBalasan* t, int parentID) {
	boolean found = false;

	deleteTreeRecursionBalasan(t, parentID, &found);
}

void deleteTreeRecursionBalasan(TreeBalasan* t, int parentID, boolean* f) {
	if (*t != Nil_BALASAN) {
		int i = 0;

		if (ROOT_BALASAN(*t).id == parentID) {
			*f = true;
			*t = Nil_BALASAN;
		}

		while (!(*f) && i < TREECOUNT_BALASAN(*t)) {
			deleteTreeRecursionBalasan(&SUBTREE_BALASAN(*t, i), parentID, f);
			i += 1;
		}
	}
}

// Tree* searchTree(Tree t, Infotype val) {
// 	boolean found = false;
// 	Tree* res = Nil;

// 	searchTreeRecursion(t, val, &found, &res, '#', Nil);
// 	return res;
// }

// void searchTreeRecursion(Tree t, Infotype val, boolean* f, Tree** treeResult, char operation, Tree node) {
// 	if (t != Nil) {
// 		int i = 0;

// 		if (operation == 'd') printf("%d\n", ROOT(t));
// 		if (ROOT(t).id == val) {
// 			*f = true;
// 			*treeResult = &t;

// 			if (operation == 'i') {
// 				ConnectChild(node, &t);
// 			} else if (operation == 'd') {
// 				t = Nil;
// 			}
// 		}
// 		if (t != Nil) {
// 			// if (operation == 'd') printf("(%d: %d)", ROOT(t), *f);

// 			while (i < TREECOUNT(t) && !(*f)) {
// 				searchTreeRecursion(SUBTREE(t, i), val, f, treeResult, operation, node);
// 				i += 1;
// 			}
// 		}
// 	}
// }