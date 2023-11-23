#include <stdio.h>
#include "../../modules/listdinkicauan/listdinkicauan.c"
#include "../../modules/listutas/listutas.c"

void printUtas(List l){
    Address p = l;
    while (p != NULL){
        int index = INDEX(p);
        Word author = AUTHOR(p);
        DATETIME datetime = DATETIME(p);
        Word text = TEXT(p);
        
        printf("\n");
        printf("ID = %d", index);
        
        printf("\n");
        printf("%s", author.TabWord);
        
        printf("\n");
        printf("%s", text.TabWord);
        printf("\n");

        p = NEXT(p);
    }
}

int main(){
    ListDinKicauan l;
    CreateListDinKicauan(&l,5);
    Kicauan k1 = {1, {"Hello, world!", 13}, 10, {"John", 4}, {23, 11, 2023, {12, 30, 45}}, 0, 0};
    Kicauan k2 = {2, {"Programming is fun!", 21}, 15, {"Alice", 5}, {24, 11, 2023, {14, 20, 30}}, 0, 0};
    insertLastKicauan(&l,k1);
    insertLastKicauan(&l,k2);
    printf("panjang list kicau = %d", listLengthKicauan(l));
    // Sample data
    Word author = {"John", 4};
    DATETIME datetime = {23, 11, 2023, {12, 30, 45}};
    Word text = {"Hello, world!", 13};
    EltypeUtas dummy;
    dummy.author = author;
    dummy.datetime = datetime;
    dummy.text = text;
    Address address1 = newNodeUtas(dummy);
    List utas = NULL;
    insertLastUtas(&utas,dummy);
    insertLastUtas(&utas,dummy);
    insertLastUtas(&utas,dummy);
    insertLastUtas(&utas,dummy);
    insertLastUtas(&utas,dummy);
    insertLastUtas(&utas,dummy);
    insertLastUtas(&utas,dummy);

    deleteAtUtas(&utas, 3);



    List p = NULL;
    printUtas(utas);

    

}