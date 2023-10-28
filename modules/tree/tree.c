/* File : tree.h */
/* ADT pohon N-Ary */
/* Representasi Address dengan pointer */
/* ElType adalah Makanan */

#include "tree.h"

Address NewTreeNode(Infotype root)
/* Mengalokasikan sebuah Address t, bernilai Nil jika tidak berhasil */
/* Mengirimkan Address hasil alokasi sebuah elemen bernilai root
   Jika alokasi berhasil, maka Address tidak Nil dan menghasilkan t
   ROOT(t) = val, SUBADDRESS(t) terdefinisi dengan ukuran INITIAL,
   TREECOUNT(t) = 0, dan TREECAPACITY(t) = INITIAL 
   Jika alokasi gagal, maka mengirimkan Nil */
{
	Address t = (Address) malloc(sizeof(Node));

	if (t != Nil) 
	{
		ROOT(t) = root;
		SUBADDRESS(t) = (Address*) malloc(INITIAL * sizeof(Address*));
		TREECOUNT(t) = 0;
		TREECAPACITY(t) = INITIAL;
	}

	return t;
}

Tree NewTree(Infotype root, Tree child)
/* Jika alokasi berhasil, menghasilkan sebuah pohon dari root dan child;
   dan TREECOUNT bertambah satu jika child bukan Nil */
/* Jika alokasi gagal, menghasilkan pohon kosong (Nil) */
{
	Address t = NewTreeNode(root);
	if (t != Nil)
	{
		SUBTREE(t, TREECOUNT(t)) = child;

		if (child != Nil)
			TREECOUNT(t)++;
	}
	return t;
}

void CreateTree(Infotype root, Tree child, Tree *t)
/* I.S. : Sembarang
   F.S. : Menghasilkan sebuah pohon t
   		  Jika alokasi berhasil, menghasilkan sebuah pohon dari root dan child;
   		  dan TREECOUNT bertambah satu jika child bukan Nil
   		  Jika alokasi gagal, menghasilkan pohon kosong (Nil) */
{
	*t = NewTreeNode(root);
	if (*t != Nil)
	{
		SUBTREE(*t, TREECOUNT(*t)) = child;

		if (child != Nil)
			TREECOUNT(*t)++;
	}
}

void ConnectChild(Tree child, Tree *t)
/* I.S. : t dan child terdefinisi
   F.S. : t terhubung dengan child dan TREECOUNT bertambah satu jika child bukan Nil */
{
	if (TREECOUNT(*t) == TREECAPACITY(*t))
		ExpandCapacity(t);

	SUBTREE(*t, TREECOUNT(*t)) = child;

	if (child != Nil)
		TREECOUNT(*t)++;
}

void ConnectParent(Tree parent, Tree *t)
/* I.S. : t dan parent terdefinisi
	F.S. : t menjadi child dari parent, ROOT(t) menjadi ROOT(parent) */
{
	ConnectChild(*t, &parent);

	*t = parent;
}

void DeallocateTree(Address t)
/* I.S. : t terdefinisi
   F.S. : t dikembalikan ke sistem
   Melakukan dealokasi/pengembalian Address t */
{
	free(t);
}

boolean HasNoChild(Tree t)
/* Mengirimkan true jika t tidak memiliki child */
{
	if (TREECOUNT(t) == 0)
		return true;
	return false;
}

boolean HasOneChild(Tree t)
/* Mengirimkan true jika t hanya memiliki 1 child */
{
	if (TREECOUNT(t) == 1)
		return true;
	return false;
}

/***** Display Tree *****/
void PrintTree(Tree t)
/* I.S. : t terdefinisi
   F.S. : Semua simpul t sudah dicetak secara preorder: root dan child(ren)
   		  Setiap pohon ditandai dengan tanda kurung buka dan tanda kurung tutup ()
   		  Pohon kosong ditandai dengan () */
{
	if (t == Nil) {
		// printf("()");
	} else {
		printf("(");
		printf("%d", ROOT(t));
		int i;
		for (i = 0; i < TREECOUNT(t); i++)
			PrintTree(SUBTREE(t,i));
		printf(")");
	}
}

void ExpandCapacity(Tree *t)
/* Proses: Memperbesar dua kali lipat capacity t */
/* I.S. : t terdefinisi */
/* F.S. : Ukuran SubTree menjadi dua kali lipat ukuran semula */
{
	TREECAPACITY(*t) *= 2;

	Address *temp = SUBADDRESS(*t);

	SUBADDRESS(*t) = (Address*) malloc(TREECAPACITY(*t) * sizeof(Address*));
	TREECOUNT(*t) = 0;
	
	int i;
	for (i = 0; i < TREECAPACITY(*temp); i++)
		SUBTREE(*t,i) = SUBTREE(*temp,i);
}

void insertTree(Tree t, Infotype parent, Infotype child) {
	boolean found = false;
	Tree c = NewTree(child, Nil);

	insertTreeRecursion(t, parent, c, &found);
}

void insertTreeRecursion(Tree t, Infotype parent, Tree child, boolean* f) {
	if (t != Nil) {
		int i = 0;

		if (ROOT(t) == parent) {
			*f = true;
			ConnectChild(child, &t);
		}
			// if (operation == 'd') printf("(%d: %d)", ROOT(t), *f);

		while (i < TREECOUNT(t) && !(*f)) {
			insertTreeRecursion(SUBTREE(t, i), parent, child, f);
			i += 1;
		}
	}
}

void deleteTree(Tree* t, Infotype parent) {
	boolean found = false;
	Tree* res = Nil;

	deleteTreeRecursion(t, parent, &found);
}

void deleteTreeRecursion(Tree* t, Infotype parent, boolean* f) {
	if (*t != Nil) {
		int i = 0;

		if (ROOT(*t) == parent) {
			*f = true;
			*t = Nil;
		}

		while (!(*f) && i < TREECOUNT(*t)) {
			deleteTreeRecursion(&SUBTREE(*t, i), parent, f);
			i += 1;
		}
	}
}

Tree* searchTree(Tree t, Infotype val) {
	boolean found = false;
	Tree* res = Nil;

	searchTreeRecursion(t, val, &found, &res, '#', Nil);
	return res;
}

void searchTreeRecursion(Tree t, Infotype val, boolean* f, Tree** treeResult, char operation, Tree node) {
	if (t != Nil) {
		int i = 0;

		if (operation == 'd') printf("%d\n", ROOT(t));
		if (ROOT(t) == val) {
			*f = true;
			*treeResult = &t;

			if (operation == 'i') {
				ConnectChild(node, &t);
			} else if (operation == 'd') {
				t = Nil;
			}
		}
		if (t != Nil) {
			// if (operation == 'd') printf("(%d: %d)", ROOT(t), *f);

			while (i < TREECOUNT(t) && !(*f)) {
				searchTreeRecursion(SUBTREE(t, i), val, f, treeResult, operation, node);
				i += 1;
			}
		}
	}
}