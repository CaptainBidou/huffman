#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h> 
//ceil, floor : #include <math.h>


#include "include/traces.h" 
#include "include/check.h" 
#include "include/huffman.c"
#include "include/elt.c"










int main(int argc,char* argv[]) {

if(argc==2)
{
   T_huffmanTab* p = malloc(sizeof(T_huffmanTab));
    FILE* fic = fopen(argv[1],"r");
    if(fic==NULL)
    {
        printf("erreur d'ouverture du fichier");
        exit(1);
    }
    fread(p,sizeof(T_huffmanTab),1,fic);
    //afficherHuffman(p);
    int valMax=maxHuffman(p);
    //printf("valMax : %d",valMax);


   int bit=fgetc(fic);
    int caractere=valMax;
    while(bit!=EOF)
    {   
        
        
        if(bit==48)
        {
            caractere=searchVal(p,caractere*-1);
            //printf("caractere : %d\n",caractere);
        
        //getchar();
        }
        if(bit==49)
        {caractere=searchVal(p,caractere);
        }

        if(caractere<MAXCARS)
        {
            printf("%c",caractere);
            //printf("%d\n",j);
            caractere=valMax;
        }

        //printf("%c",bit);
        bit=fgetc(fic);
    }


    
}








if(argc==3)
{
    T_indirectHeap * p = NULL;
    T_elt minLeft;
    T_elt minRight;
    //on déclare une nouvelle heap indirecte
    p=newIndirectHeap();

    //on déclare notre tableau huffman 
    T_huffmanTab* huffTab = huffmanTab();

    //char* data = "bonjour";

    //on ajoute les occurences des caractères dans data
    getDataChar(p,argv[1]);
    //on affiche le tableau
    afficherData(p);
    //on set notre tree 
    setTree(p);
    //on affiche le tree
    afficherTree(p);
    showHeap(p);



    while(p->nbElt>2){
        //on exporte les minimums
        createDotPOT(p->tree,p->nbElt,"tas");
        minLeft=exportHeapMin(p);
        minRight=exportHeapMin(p);
        //on les ajoute à notre huffmanTree
        huffmanTabAddNode(huffTab,p,minLeft,minRight);

        showHeap(p);
    }
    minLeft=p->tree[0];
    minRight=p->tree[1];
    p->tree[0]=0;
    p->tree[1]=0;
    p->nbElt=0;
    huffmanTabAddNode(huffTab,p,minLeft,minRight);
    showHeap(p);
    afficherHuffman(huffTab);
    //huffmanTreeCreate(huffTab,p);
    T_caracteres* caracteresTab = encoderCaract(huffTab,p);
   creerFic(caracteresTab,huffTab,argv[2],argv[1]);


    T_avlNode* arbre=avlConstruire(huffTab,maxHuffman(huffTab));
    createDotBST(arbre, "root");

    calcul(huffTab,caracteresTab,p);





}




/*
T_huffmanTree* huff = NULL;
huff = huffman(p);*/



}


















