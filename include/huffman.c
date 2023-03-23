#include <stdio.h> // sprintf
#include <string.h> // strdup, strcmp
#include <stdlib.h> // malloc, free
#include "huffman.h"




/*----tp5--------------------------------------------------------------------------*/

//Initialisation de la structure T_indirectHeap
T_indirectHeap * newIndirectHeap(){
    T_indirectHeap *p = (T_indirectHeap *) malloc(sizeof(T_indirectHeap));
    p->nbElt = 0;

    printf("New Indirect Heap declared");
    getchar();
    return p;
}

//Enregistrer les données dans un tableau de caractères
void getDataChar(T_indirectHeap *p,char *fichier){
    FILE* fic = fopen(fichier,"r");
    char temp=fgetc(fic);

     while(temp!=EOF){
        p->data[temp]++;
        temp=fgetc(fic);

    }
    fclose(fic);
}


//On set le tableau de caractères avec les caractères qui ont une occurence > 0
void setTree(T_indirectHeap *p)
{
    int i=0;
    while(i<129)
    {
        if(p->data[i]>0)
        {
            insertHeapMin(p,i);
            
        }
        i++;
    }


}

//Affichage du tableau de caractères avec les caractères qui ont une occurence > 0
void afficherTree(T_indirectHeap *p){
    for(int i=0;i<129;i++)
    {
        printf("p->tree[%d] : %d\n",i,p->tree[i]);
    }
}

//Affichage du tableau de données
void afficherData(T_indirectHeap *p){
    for(int i=0;i<129;i++)
    {
        printf("p->data[%d] : %d\n",i,p->data[i]);
    }
}

//On trouve les minimums de ce tableau
void insertHeapMin(T_indirectHeap *p, T_elt e){
    assert(p->nbElt < MAXCARS);
	p->tree[p->nbElt] = e;
	p->nbElt++;
	siftUp(p, p->nbElt - 1);
}

void siftUp(T_indirectHeap *p, int k) {
	while (iPARENT(k) >= 0 && VALP(p, k) < VALP(p, iPARENT(k))) {
		swap(p, k, iPARENT(k));
		k = iPARENT(k);
	}
}

void swap(T_indirectHeap *p, int i, int j) {
	
	T_elt aux;
	aux = p->tree[i];
	p->tree[i] = p->tree[j];
	p->tree[j] = aux;
 
}

void showHeap_rec(T_indirectHeap *p, int root, int indent)
{
	if(isINTREE(root,p->nbElt)){
		showHeap_rec(p,iRCHILD(root),indent+1);
		for(int i=0;i<indent;i++) printf("\t");
		printf("%d\n",p->tree[root]);
		showHeap_rec(p,iLCHILD(root),indent+1);
	}
}
void showHeap(T_indirectHeap *p) {
	assert(p!=NULL);
	printf("Affichage du tas (nbElt : %d)\n",p->nbElt);
	showHeap_rec(p,0,0); 
}


void siftDown(T_indirectHeap *p, int k) {
	int fin = isLEAF(k, p->nbElt);
	while (!fin) 
	{
		int i = iLCHILD(k);
		if (iRCHILD(k) < p->nbElt && VALP(p, iRCHILD(k)) < VALP(p,iLCHILD(k))) 
			{
				i = iRCHILD(k);
			}
		if (VALP(p, k) <= VALP(p, i)) 
		{
		fin = 1;
		}
		else 
		{
			swap(p, k, i);
			k = i;
			fin = isLEAF(k, p->nbElt);
		}
	}
}



T_elt exportHeapMin(T_indirectHeap *p){
	T_elt aux;
	aux = p->tree[0];
	p->tree[0] = p->tree[p->nbElt - 1];
	p->tree[p->nbElt - 1] = aux;
	p->nbElt--;
	siftDown(p, 0);
	return aux;
}







//On créé un huffman tableau 
T_huffmanTab * huffmanTab(){
    T_huffmanTab *p = (T_huffmanTab *) malloc(sizeof(T_huffmanTab));
    for(int i=0;i<2*MAXCARS-1;i++)
    {
        p->huffman[i]=0;
    }
    return p;
}


void huffmanTabAddNode(T_huffmanTab* pHuffman,T_indirectHeap *pHeap,T_elt left,T_elt right){
    int caseData=MAXCARS;
    for(int i=MAXCARS;i<2*MAXCARS-1;i++)
    {
        if(pHeap->data[i]==0)
        {
            caseData=i;
            break;
        }
    }
    
    pHeap->data[caseData]=pHeap->data[left]+pHeap->data[right];
    pHuffman->huffman[left]=caseData*-1;
    pHuffman->huffman[right]=caseData;
    
    insertHeapMin(pHeap,caseData);




}

void afficherHuffman(T_huffmanTab *p){
    for(int i=0;i<2*MAXCARS-1;i++)
    {
        printf("p->huffman[%d] : %d\n",i,p->huffman[i]);
    }
}



T_caracteres* newCaract(){
    T_caracteres *p = (T_caracteres *) malloc(sizeof(T_caracteres));
    return p;
}



T_caracteres* encoderCaract(T_huffmanTab *huffTab,T_indirectHeap* p){

    T_caracteres* caract=newCaract();

    printf("car : occ : long : bits\n");
    printf("----+-----+------+-----\n");
    int noeudFinal=p->tree[0];
    for(int i=0;i<128;i++)
    {
        if(p->data[i]!=0)
        {

            int noeudCourant=i;
            int codeCara=i;
            while(noeudCourant!=noeudFinal)
            {
                if(caract->caracteres[codeCara]==NULL)
                {
                    
                        if(huffTab->huffman[noeudCourant]<0)
                        {
                            strcpy(&caract->caracteres[codeCara],"0");
                        }
                        else
                        {
                            strcpy(&caract->caracteres[codeCara],"1");
                        }
                    
                    
                    }

                else{
                        

                        if(huffTab->huffman[noeudCourant]<0)
                        {
                            
                            strcat(&caract->caracteres[codeCara],"0");
                        }
                        else
                        {
                            strcat(&caract->caracteres[codeCara],"1");
                           /*printf("%s",caract->caracteres[codeCara]);
                            getchar();
                            
                            
                            printf("concat done");
                            getchar();*/
                        }
                }
               
                noeudCourant=abs(huffTab->huffman[noeudCourant]);

            }
            reverse(&caract->caracteres[codeCara]);

            printf("'%c' |   %d |   %d | %s\n",i,p->data[i],strlen(&caract->caracteres[codeCara]),&caract->caracteres[codeCara]);

        }
    }


return caract;


}


void reverse(char* str)
{
    // récupère la longueur de la string
    int n = strlen(str);
 
    // commence à échanger les caractères des deux extrémités de la string
    for (int i = 0, j = n - 1; i < j; i++, j--)
    {
        char ch = str[i];
        str[i] = str[j];
        str[j] = ch;
    }
}


//On créé l'arbre de huffman à partir de ces minimums
//uniquement pour l'affichage
T_huffmanTree * huffmanTreeCreate(T_huffmanTab* HuffmanTab,T_indirectHeap *p){
   

    T_huffmanTree *pTree = newHuffmanTree(p->tree[0]);
    return pTree;
}


int maxHuffman(T_huffmanTab* p){
    int max=0;
    for(int i=0;i<2*MAXCARS-1;i++)
    {
        if(abs(p->huffman[i])>max)
        {
            max=abs(p->huffman[i]);
        }
    }
    return max;
}

int searchVal(T_huffmanTab* p,int val){

    for(int i=0;i<2*MAXCARS-1;i++)
    {
        if(p->huffman[i]==val)
        {
            return i;
        }
    }
    return 0;
}


T_huffmanTree * newHuffmanTree(int code)
{
    T_huffmanTree *p=malloc(sizeof(T_huffmanTree));
    p->left=NULL;
    p->right=NULL;
    p->code=code;
    return p;
}

void creerFic(T_caracteres* caract,T_huffmanTab* huffTab,char *fichier,char *fichierLectureNom){
    int c=0;
    FILE* fichierLecture = fopen(fichierLectureNom,"r");
    FILE* fic = fopen(fichier,"w");
    fwrite(huffTab,sizeof(T_huffmanTab),1,fic);
    char temp=fgetc(fichierLecture);

//on créé nos octet
   T_format* format=malloc(sizeof(T_format));
    format->nbOctet=0;
    int bit=0;
//on initialise nos octets
    for(int i=0;i<128;i++){
        format->octet[i]=0b00000000 ;
    }


int longueur;
char vide = 0b00000000;
    while(temp!=EOF){
        longueur=strlen(&caract->caracteres[temp]);
        //printf("longueur : %c\n",&caract->caracteres[temp][0]);
        /*if(bit==8){
            bit=0;
            format->nbOctet++;
        }
        else{
                if(bit+longueur<=7)
                    {
                    format->octet[format->nbOctet]=format->octet[format->nbOctet]<<longueur;
                    vide=0b00000000;
                    for(int i=0;i<longueur;i++){
                        if(&caract->caracteres[temp][i]=='1'){
                            vide=vide|0b00000001;
                        }
                        vide=vide<<1;

                    }
                    format->octet[format->nbOctet]=format->octet[format->nbOctet]|vide;
                    }

                else{
                    format->octet[format->nbOctet]=format->octet[format->nbOctet]<<bit-7;
                    vide=0b00000000;
                    for(int i=0;i<bit-7;i++){
                        if(&caract->caracteres[temp][i]=='1'){
                            vide=vide|0b00000001;
                        }
                        vide=vide<<1;

                    }
                    format->octet[format->nbOctet]=format->octet[format->nbOctet]|vide;

                    format->nbOctet++;

                    format->octet[format->nbOctet]=format->octet[format->nbOctet]<<longueur+bit-7;
                        vide=0b00000000;
                    for(int i=0;i<longueur+bit-7;i++){
                        if(&caract->caracteres[temp][i]=='1'){
                            vide=vide|0b00000001;
                        }
                        vide=vide<<1;

                    }
                    format->octet[format->nbOctet]=format->octet[format->nbOctet]|vide;



                    }
        }*/


        printf("%s",&caract->caracteres[temp]);
        fwrite(&caract->caracteres[temp],sizeof(char*),1,fic);
        temp=fgetc(fichierLecture);
        c++;
        bit++;
    }
    fclose(fic);
    fclose(fichierLecture);
    
    /*fwrite(huffTab,sizeof(T_huffmanTab),1,fic);
    for(int i=0;i<format->nbOctet+1;i++){
        fwrite(&format->octet[i],sizeof(char),1,fic);
    }*/






    
}

void calcul(T_huffmanTab *huffTab,T_caracteres *caract,T_indirectHeap* p){
    int longueurOrigin=0;
    int longueurHuffman=0;


    for(int i=0 ; i<128;i++)
    {
        if(p->data[i]!=0)
        {
            longueurOrigin=longueurOrigin+8*p->data[i];
           // printf("%d\n",strlen(&caract->caracteres[i]));
            longueurHuffman=longueurHuffman+strlen(&caract->caracteres[i])*p->data[i];
        }


    }
printf("Longueur du code binaire original : %d bits\n",longueurOrigin);
printf("Longueur du code binaire de Huffman : %d bits\n",longueurHuffman);
printf("Taux de compression : %f %\n",(float)longueurHuffman*100/longueurOrigin);


}





T_huffmanTree* construireArbre(T_huffmanTab *huffTab,int valeurNoeud){
    if(valeurNoeud==0)
    {
        return NULL;
    }


    T_huffmanTree *pTree = newHuffmanTree(valeurNoeud);
    pTree->left=construireArbre(huffTab,searchVal(huffTab,valeurNoeud*-1));
    pTree->right=construireArbre(huffTab,searchVal(huffTab,valeurNoeud));
    return pTree;
}




T_avlNode * newAvlNode(int val){
    T_avlNode *p=malloc(sizeof(T_avlNode));
    p->val=val;
    p->l=NULL;
    p->r=NULL;
    return p;
}

T_avlNode* avlConstruire(T_huffmanTab *huffTab,int valeurNoeud){
    if(valeurNoeud==0)
    {
        return NULL;
    }

    T_avlNode *pTree = newAvlNode(valeurNoeud);


    pTree->l=avlConstruire(huffTab,searchVal(huffTab,valeurNoeud*-1));
    pTree->r=avlConstruire(huffTab,searchVal(huffTab,valeurNoeud));
    return pTree;
}













/******fonction bst prof ***************************************************/
#include <sys/stat.h>

char * outputPath = "."; 

static void  genDotBST(T_avlNode* root, FILE *fp) {
	// Attention : les fonction toString utilisent un buffer alloué comme une variable statique 
	// => elles renvoient toujours la même adresse 
	// => on ne peut pas faire deux appels à toString dans le même printf()

    fprintf(fp, "\t%s",toString(root->val)); 
    fprintf(fp, " [label = \"{<c> %s | { <g> | <d>}}\"];\n",toString(root->val));
    if (root->r == NULL && root->l == NULL) {
        fprintf(fp, "\t%s", toString(root->val)); 
		fprintf(fp, " [label = \"{<c> %s | { <g> NULL | <d> NULL}}\"];\n", toString(root->val));
	}
    else if (root->r == NULL) {
        fprintf(fp, "\t%s", toString(root->val));
		fprintf(fp, " [label = \"{<c> %s | { <g> | <d> NULL}}\"];\n", toString(root->val));
	}
	else if ( root->l == NULL) {
        fprintf(fp, "\t%s",toString(root->val));
		fprintf(fp, " [label = \"{<c> %s | { <g> NULL | <d> }}\"];\n", toString(root->val));
	}
	
    if (root->l) {
        fprintf(fp, "\t%s",toString(root->val));
		fprintf(fp, ":g -> %s;\n", toString(root->l->val));
        genDotBST(root->l, fp);
    }

    if (root->r) {
        fprintf(fp, "\t%s",toString(root->val));
		fprintf(fp,":d -> %s;\n", toString(root->r->val));
        genDotBST(root->r, fp);
    }
}


void createDotBST(const T_avlNode* root, const char *basename) {
	static char oldBasename[FILENAME_MAX + 1] = "";
	static unsigned int noVersion = 0;

	char DOSSIER_DOT[FILENAME_MAX + 1]; 
	char DOSSIER_PNG[FILENAME_MAX + 1]; 

	char fnameDot [FILENAME_MAX + 1];
	char fnamePng [FILENAME_MAX + 1];
	char	cmdLine [2 * FILENAME_MAX + 20];
	FILE *fp;
	struct stat sb;
	

	// Au premier appel, création (si nécessaire) des répertoires
	// où seront rangés les fichiers .dot et .png générés par cette fonction	

	// il faut créer le répertoire outputPath s'il n'existe pas 
	if (stat(outputPath, &sb) == 0 && S_ISDIR(sb.st_mode)) {
    } else {
        printf("Création du répertoire %s\n", outputPath);
		mkdir(outputPath, 0777);
    }

	// il faut créer les répertoires outputPath/png et /dot 
	sprintf(DOSSIER_DOT, "%s/dot/",outputPath);
	sprintf(DOSSIER_PNG, "%s/png/",outputPath);

	if (oldBasename[0] == '\0') {
		mkdir(DOSSIER_DOT,	S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
		mkdir(DOSSIER_PNG,	S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	}

	 // S'il y a changement de nom de base alors recommencer à zéro
	 // la numérotation des fichiers 

	if (strcmp(oldBasename, basename) != 0) {
		noVersion = 0;
		strcpy(oldBasename, basename); 
	}

	sprintf(fnameDot, "%s%s_v%02u.dot", DOSSIER_DOT, basename, noVersion);
	sprintf(fnamePng, "%s%s_v%02u.png", DOSSIER_PNG, basename, noVersion);

	CHECK_IF(fp = fopen(fnameDot, "w"), NULL, "erreur fopen dans saveDotBST"); 
	
	noVersion ++;
    fprintf(fp, "digraph %s {\n", basename);
 	fprintf(fp, 
		"\tnode [\n"
			"\t\tfontname  = \"Arial bold\" \n"
			"\t\tfontsize  = \"14\"\n"
			"\t\tfontcolor = \"red\"\n"
			"\t\tstyle     = \"rounded, filled\"\n"
			"\t\tshape     = \"record\"\n"
			"\t\tfillcolor = \"grey90\"\n"
			"\t\tcolor     = \"blue\"\n"
			"\t\twidth     = \"2\"\n"
			"\t]\n"
		"\n"
		"\tedge [\n"
			"\t\tcolor     = \"blue\"\n"
		"\t]\n\n"
	);

    if (root == NULL)
        fprintf(fp, "\n");
    else
        genDotBST(root, fp);

    fprintf(fp, "}\n");	
    fclose(fp);

    sprintf(cmdLine, "dot -Tpng  %s -o %s", fnameDot, fnamePng);
    system(cmdLine);

    printf("Creation de '%s' et '%s' ... effectuee\n", fnameDot, fnamePng);
}



/*****fonctions prof pour heap*********************************/


static void genDotPOT_rec(unsigned char t[],unsigned int n, int root, FILE *fp){
// t : tas
// n : taille du tas
// root : indice de la racine du sous-arbre à produire
// fp : flux correspondant à un fichier ouvert en écriture où écrire le
if(!isINTREE(root,n)) return;
fprintf(fp, "\t%d",root);
fprintf(fp, " [label = \"%d\"];\n",t[root]);
if ( isINTREE(iRCHILD(root),n) && isINTREE(iLCHILD(root),n) ) {
fprintf(fp, "\t%d", root);
fprintf(fp, " [label = \"%d\"];\n", t[root]);
}
else
if ( isINTREE(iRCHILD(root),n) ) {
fprintf(fp, "\t%d", root);
fprintf(fp, " [label = \"%d\"];\n", t[root]);
}
else
if ( isINTREE(iLCHILD(root),n) ) {
fprintf(fp, "\t%d",root);
fprintf(fp, " [label = \"%d\"];\n", t[root]);
}
if ( isINTREE(iLCHILD(root),n) ) {
fprintf(fp, "\t%d",root);
fprintf(fp, ":sw -> %d;\n", iLCHILD(root));
genDotPOT_rec(t, n, iLCHILD(root), fp);
}
if ( isINTREE(iRCHILD(root),n) ) {
fprintf(fp, "\t%d",root);
fprintf(fp,":se -> %d;\n", iRCHILD(root));
genDotPOT_rec(t, n, iRCHILD(root), fp);
}
}


void createDotPOT(unsigned char t [], unsigned int n,const char *basename) {
	static char oldBasename[FILENAME_MAX + 1] = "";
	static unsigned int noVersion = 0;

	char DOSSIER_DOT[FILENAME_MAX + 1]; 
	char DOSSIER_PNG[FILENAME_MAX + 1]; 

	char fnameDot [FILENAME_MAX + 1];
	char fnamePng [FILENAME_MAX + 1];
	char	cmdLine [2 * FILENAME_MAX + 20];
	FILE *fp;
	struct stat sb;
	

	// Au premier appel, création (si nécessaire) des répertoires
	// où seront rangés les fichiers .dot et .png générés par cette fonction	

	// il faut créer le répertoire outputPath s'il n'existe pas 
	if (stat(outputPath, &sb) == 0 && S_ISDIR(sb.st_mode)) {
    } else {
        printf("Création du répertoire %s\n", outputPath);
		mkdir(outputPath, 0777);
    }

	// il faut créer les répertoires outputPath/png et /dot 
	sprintf(DOSSIER_DOT, "%s/dot/",outputPath);
	sprintf(DOSSIER_PNG, "%s/png/",outputPath);

	if (oldBasename[0] == '\0') {
		mkdir(DOSSIER_DOT,	S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
		mkdir(DOSSIER_PNG,	S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	}

	 // S'il y a changement de nom de base alors recommencer à zéro
	 // la numérotation des fichiers 

	if (strcmp(oldBasename, basename) != 0) {
		noVersion = 0;
		strcpy(oldBasename, basename); 
	}

	sprintf(fnameDot, "%s%s_v%02u.dot", DOSSIER_DOT, basename, noVersion);
	sprintf(fnamePng, "%s%s_v%02u.png", DOSSIER_PNG, basename, noVersion);

	CHECK_IF(fp = fopen(fnameDot, "w"), NULL, "erreur fopen dans saveDotBST"); 
	
	noVersion ++;
	fprintf(fp, "digraph %s {\n", basename);
	fprintf(fp, 
	"\tnode [\n"
		"\t\tfontname  = \"Arial bold\" \n"
		"\t\tfontsize  = \"14\"\n"
		"\t\tfontcolor = \"red\"\n"
		"\t\tstyle     = \"rounded, filled\"\n"
		"\t\tshape     = \"circle\"\n"
		"\t\tfillcolor = \"grey90\"\n"
		"\t\tcolor     = \"blue\"\n"
		"\t\twidth     = \"0.5\"\n"
		"\t]\n"
	"\n"
	"\tedge [\n"
		"\t\tcolor     = \"blue\"\n"
	"\t]\n\n"
	);


	genDotPOT_rec(t,n,0,fp);

	fprintf(fp, "}\n");	
	fclose(fp);

	sprintf(cmdLine, "dot -Tpng  %s -o %s", fnameDot, fnamePng);
	system(cmdLine);

	printf("Creation de '%s' et '%s' ... effectuee\n", fnameDot, fnamePng);
}