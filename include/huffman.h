#include "elt.h"

#define MAXCARS 128

/*Structures*****************************************/
typedef struct {
unsigned int nbElt;
unsigned char tree[MAXCARS];
int data[2*MAXCARS-1];
} T_indirectHeap;

typedef struct T_Node{
struct T_Node* left;
struct T_Node* right;
T_elt code;
}T_huffmanTree;


typedef struct aNode{
	T_elt val; // élément contenu dans le noeud 
	struct aNode *l; // pointeur vers sous-arbre gauche
	struct aNode *r; // pointeur vers sous-arbre droit 
} T_avlNode, *T_avl;




typedef struct{
int huffman[2*MAXCARS-1];
}T_huffmanTab;

typedef struct{
char *caracteres[MAXCARS];
}T_caracteres;



typedef struct{

	unsigned char octet[2*MAXCARS];
	int nbOctet;
}T_format;


/**************************************************/


/*Processus****************************************
1) On traite la chaine en entrée en comptant le nombre d'occurences de chaque caractère
2) On crée un tableau de caractères avec les caractères qui ont une occurence > 0
3) On trouve les minimums de ce tableau
4) On créé l'arbre de huffman à partir de ces minimums
5) on determine les codes de chaque caractère
6) on encode la chaine en entrée
***************************************************/


/*Declaration de macro-fonctions***********************************************/


#define iPARENT(i) 			(i-1)/2
#define iLCHILD(i) 			(2*i)+1
#define iRCHILD(i) 			(2*i)+2
#define iLASTINTERNAL(n)	n/2 -1
#define isINTERNAL(i,n) 	(2*i<(n-1))
#define isLEAF(i,n) 			(2*i>=(n-1))
#define isINTREE(i,n)		(i<n)
#define isROOT(i)				(i==0)
#define nbINTERNALS(n) 		n/2
#define nbLEAVES(n) 			ceil((double)n/2)
#define VALP(T_indirectHeap, i)		T_indirectHeap->data[T_indirectHeap->tree[i]]		
#define VAL(T_indirectHeap, i)			T_indirectHeap.data[T_indirectHeap.tree[i]]

/********************************************************************************/



/*Declaration de Fonctions************************************************ */


//Enregistrer les données dans un tableau de caractères

T_indirectHeap * newIndirectHeap();

void getDataChar(T_indirectHeap *p,char *fichier);

void afficherData(T_indirectHeap *p);

void setTree(T_indirectHeap *p);

void afficherTree(T_indirectHeap *p);

void insertHeapMin(T_indirectHeap *p,T_elt e);

T_elt exportHeapMin(T_indirectHeap *p);

T_huffmanTree* huffmanTreeCreate(T_huffmanTab* HuffmanTab,T_indirectHeap *p);

T_huffmanTree * newHuffmanTree(int code);

void siftUp(T_indirectHeap *p, int k);

void swap(T_indirectHeap *p, int i, int j);

void huffmanTabAddNode(T_huffmanTab* pHuffman,T_indirectHeap *pHeap,T_elt left,T_elt right);

T_caracteres* encoderCaract(T_huffmanTab *huffTab,T_indirectHeap* p);
/*******************************************************************************/