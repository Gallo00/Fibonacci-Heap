
/* IMPLEMENTAZIONE HEAP DI FIBONACCI TEMPLATE
   SAMUELE MARIA GALLINA
   
 //  RUNNABILE SIA SU WIN CHE UBUNTU

*/

#include <iostream>
#include <cmath> //ci saranno dei calcoli logaritmici

using namespace std;
template <class T>
struct Nodo  
{
	Nodo<T>* padre;
	Nodo<T>* figlio;
	Nodo<T>* right;
	Nodo<T>* left;
	
	T key;
	int degree; //suo numero di figli
	bool mark;

	char C;  //variabile utile per poter cercare il nodo
};

template <class T>
class FH
{
	private:
	    int numero_nodi; //numero nodi totali della struttura
		Nodo<T>* extreme;
		Nodo<T>* infinite;  //punta a NULL normalmente, punterà(temporaneamente) a un nodo se esso è (idealmente) con key=-∞
		
	public:
	    FH()
		{
			numero_nodi=0;
		    extreme=NULL;
			infinite=NULL;
		}
	void setnumero_nodi(int n) {numero_nodi=n;}
	int numNodi() { return this->numero_nodi; }

	void setExtreme(Nodo<T>* ex) {extreme=ex;}
	Nodo<T>* ritornaExtreme() {return this->extreme;}
	
	void setinfinite(Nodo<T>* x) {infinite=x;}
	Nodo<T>* returnInfinite() {return infinite;}
	
	virtual bool compare(T a,T b) = 0;
	
};

template <class T>
class FibonacciHeap : public FH<T> 
{
	private: 
	    Nodo<T>* testa;
		void LINK(Nodo<T>* y,Nodo<T>* x); //impostare y come figlio di x
		void CONSOLIDATE();   //consolidamento alberi

		void changekey(Nodo<T>* x,T nuovakey);
		void changekey(Nodo<T>* node,T vecchiakey,T nuovakey); //agisce come una find, richiamerà l'altra dk
		
			
		void find(Nodo<T>* n,T k);
		
		
		void Taglio(Nodo<T>* x,Nodo<T>* y); //si rimuove x dai figli di y e viene inserito nella lista delle radici
		void Taglio_cascata(Nodo<T>* y); //da applicare ricorsivamente in quanto in seguito alla decreasekey potrebbero essere violate
		                                 //le proprietà del min-heap
										 
		void preorder(Nodo<T>* x); //visita preorder di un albero con numero di figli qualunque
		Nodo<T>* insert(Nodo<T>* nuovo); //variante della insert
	public: 
	    bool trovato;
	    FibonacciHeap() : FH<T>() {testa=NULL;trovato=false;} //costruttore, per l'ereditarietà costruirà anche FH<T>
		
		
		
		Nodo<T>* insert(T key);  //inserimento per l'utente
		
		Nodo<T>* findExtreme() { return this->ritornaExtreme(); }      //findExtreme
		void printExtreme() { cout<<(this->findExtreme())->key<<endl;} //printExtreme
		
		void printNumNodi(){ cout<<this->numNodi()<<endl;}
		Nodo<T>* ritornaTesta(){return testa;}
		
		Nodo<T>* extractExtreme();
		//extractExtreme
		
		void print(); //usa la preorder, stampa ogni nodo
		void printlistaradici(); //stampa solo le radici

		void changekey(T vecchiakey,T nuovakey);
		
		
	    //più semplice da gestire
		void pisanodelete(T k)
		{
			if(this->ritornaExtreme()==NULL) return;
			
			if(k==this->ritornaExtreme()->key) extractExtreme();
			else
			{
				find(this->ritornaTesta(),k);
				Nodo<T>*x=this->returnInfinite();
				if(x==NULL) return; //elemento non presente
				
				Nodo<T>* y=x->padre;
				if(y!=NULL) 
				{
					Taglio(x,y);
					Taglio_cascata(y);
				}
				this->setinfinite(NULL);
				//aggiungere figli di x alla lista delle radici
				if(x->figlio!=NULL)
	            {
		            Nodo<T>* iter=x->figlio;
					Nodo<T>* iter2=iter->right;
					iter->padre=NULL;
					insert(iter);

					while(iter2!=x->figlio)
					{
						iter=iter2;
						iter2=iter->right;
						iter->padre=NULL;
						insert(iter);
					}
				}
				//togliere x dalla lista delle radici
				x->left->right=x->right;
	            x->right->left=x->left;
	            if(x==testa) testa=x->right;
				this->setnumero_nodi(this->numNodi()-1);
	
			}
		}			

};

/***********************************************************************************************/
/************************CLASSE SPECIALIZZATA MIN HEAP*********************************************/
/***********************************************************************************************/
template <class T>
class FibMinHeap : public FibonacciHeap<T>
{
	public:
	    FibMinHeap() : FibonacciHeap<T>() {}
		template <class U> friend FibMinHeap<T>* Union(FibMinHeap<T>* H1,FibMinHeap<T>* H2);
	    
		bool compare(T y,T x)
		{
			if( y < x ) return true;
			else return false;
		}
		
		Nodo<T>* extractMin() {return this->extractExtreme();}
		void decreasekey(T vecchiakey,T nuovakey) { this->changekey(vecchiakey,nuovakey);}
		Nodo<T>* findMin() {return this->findExtreme();}
		void printMin() {this->printExtreme();}
};
/***********************************************************************************************/
/************************CLASSE SPECIALIZZATA MIN HEAP*********************************************/
/***********************************************************************************************/



/***********************************************************************************************/
/************************CLASSE SPECIALIZZATA MAX HEAP*********************************************/
/***********************************************************************************************/
template <class T>
class FibMaxHeap : public FibonacciHeap<T>
{
	public:
	    FibMaxHeap() : FibonacciHeap<T>() {}
		template <class U> friend FibMaxHeap<T>* Union(FibMaxHeap<T>* H1,FibMaxHeap<T>* H2);
	    
		bool compare(T x,T y)
		{
			if( x > y ) return true;
			else return false;
		}
		
		Nodo<T>* extractMax() {return this->extractExtreme();}
		void increasekey(T vecchiakey,T nuovakey) { this->changekey(vecchiakey,nuovakey);}
		Nodo<T>* findMax() {return this->findExtreme();}
		void printMax() {this->printExtreme();}
};
/***********************************************************************************************/
/************************CLASSE SPECIALIZZATA MAX HEAP*********************************************/
/***********************************************************************************************/




/***********************************************************************************************/
/************************METODI DI STAMPA A SCHERMO*********************************************/
/***********************************************************************************************/
template <class T>
void FibonacciHeap<T>::print()
{
	if(this->ritornaExtreme()==NULL){cout<<"STRUTTURA VUOTA"<<endl; return;}
	Nodo<T>* iter=testa;
	cout<<"  |radice : ";
	preorder(testa);
	
	for(iter=testa->right;iter!=testa;iter=iter->right)
	{
		cout<<"  |radice : ";
		preorder(iter);
	}
	cout<<"numNodi="<<this->numNodi();
	cout<<endl<<endl<<endl;
}

template <class T>
void FibonacciHeap<T>::preorder(Nodo<T>* x)
{
	if(x!=NULL)
	{
		cout<<x->key<<" "<<"grado="<<x->degree<<" ";
		if(x->figlio!=NULL)
		{
			Nodo<T>* iter=x->figlio;
			cout<<"->[figli di "<<x->key<<" : "; 
			preorder(iter);
			for(iter=x->figlio->right;iter!=x->figlio;iter=iter->right)
				preorder(iter);
			cout<<"] ";
		}
	}
}



template <class T>
void FibonacciHeap<T>::printlistaradici()
{
	if(this->ritornaExtreme()==NULL) {cout<<"STRUTTURA VUOTA"<<endl; return;}
	Nodo<T>* iter=testa;
	cout<<"LISTA RADICI: "<<iter->key<<" ";
	while(iter->right!=testa)
	{
		iter=iter->right;
		cout<<iter->key<<" ";
	}
	cout<<endl;
}

/***********************************************************************************************/
/************************METODI DI STAMPA A SCHERMO*********************************************/
/***********************************************************************************************/



/*--------------------------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************/
/************************METODI DI INSERIMENTO*********************************************/
/***********************************************************************************************/
template <class T>
Nodo<T>* FibonacciHeap<T>::insert(T key)
{
	Nodo<T>* nuovo=new Nodo<T>;
	nuovo->key=key;
	nuovo->padre=nuovo->figlio=NULL;
	nuovo->right=nuovo->left=NULL;

	nuovo->degree=0;
	nuovo->mark=false;
	nuovo->C='N';
	if(this->ritornaExtreme()==NULL)  //lista con il solo nodo "nuovo"
	{
		nuovo->right=nuovo;
		nuovo->left=nuovo;
		this->setExtreme(nuovo);
		testa=nuovo;
	}
	else  //inserire "nuovo" nella lista, optiamo per l'inserimento in testa
	{
		Nodo<T>* ultimo_nodo=testa->left;
		nuovo->right=testa;
		nuovo->left=ultimo_nodo;
		testa->left=nuovo;
		
		testa=nuovo;
		ultimo_nodo->right=testa;

		if(this->compare(testa->key , this->ritornaExtreme()->key)) //compare
		{
		    this->setExtreme(testa);
		}
	}
			
	this->setnumero_nodi(this->numNodi()+1);
	return nuovo;
} 

template <class T>
Nodo<T>* FibonacciHeap<T>::insert(Nodo<T>* nuovo)
{
	nuovo->C='N';
	if(this->ritornaExtreme()==NULL)  //lista con il solo nodo "nuovo"
	{
		nuovo->right=nuovo;
		nuovo->left=nuovo;
		this->setExtreme(nuovo);
		testa=nuovo;
	}
	else  //inserire "nuovo" nella lista, optiamo per l'inserimento in testa
	{
		Nodo<T>* ultimo_nodo=testa->left;
		nuovo->right=testa;
		nuovo->left=ultimo_nodo;
		testa->left=nuovo;
		
		testa=nuovo;
		ultimo_nodo->right=testa;

		if(this->compare(testa->key,this->ritornaExtreme()->key)) //compare
		{
		    this->setExtreme(testa);
		}
	}
			
//	setnumero_nodi(numNodi()+1);  //è usata solo in metodi che prevedono una "ricollocazione", non un vero e proprio inserimento
	return nuovo;
} 
/***********************************************************************************************/
/************************METODI DI INSERIMENTO*********************************************/
/***********************************************************************************************/



/*--------------------------------------------------------------------------------------------------------------------------------------*/




/***********************************************************************************************/
/************************UNIONE TRA DUE HF*********************************************/
/***********************************************************************************************/
template <class T>
FibMinHeap<T>* Union(FibMinHeap<T>* H1,FibMinHeap<T>* H2)
{
	//CASI BASE
	if(H1->ritornaExtreme()==NULL && H2->ritornaExtreme()==NULL) return NULL;
	if(H1->ritornaExtreme()==NULL) return H2;
	if(H2->ritornaExtreme()==NULL) return H1;
	//CASI BASE
	
	
	int x=H1->numNodi();
	int y=H2->numNodi();
	
	FibMinHeap<T>* Hresult=new FibMinHeap<T>;
	
	
	//concatenare liste radici
	Hresult=H1;
	((Hresult->ritornaTesta())->left)->right=H2->ritornaTesta();
	Nodo<T>* tmp=(H2->ritornaTesta())->left;
	(H2->ritornaTesta())->left=(Hresult->ritornaTesta())->left;
	
	(Hresult->ritornaTesta())->left=tmp;
	tmp->right=Hresult->ritornaTesta();

	if((H1->ritornaExtreme())->key < (H2->ritornaExtreme())->key) //compare(potrebbe dare problemi)
	{
		Nodo<T>* m; 
		m=H1->ritornaExtreme();
		Hresult->setExtreme(m);
	}
	else 
	{ 
        Nodo<T>* n; 
		n=H2->ritornaExtreme();
		Hresult->setExtreme(n);
	}
	H1=NULL;
	H2=NULL;
	Hresult->setnumero_nodi(x+y);
	return Hresult;
}


template <class T>
FibMaxHeap<T>* Union(FibMaxHeap<T>* H1,FibMaxHeap<T>* H2)
{
	//CASI BASE
	if(H1->ritornaExtreme()==NULL && H2->ritornaExtreme()==NULL) return NULL;
	if(H1->ritornaExtreme()==NULL) return H2;
	if(H2->ritornaExtreme()==NULL) return H1;
	//CASI BASE
	
	
	int x=H1->numNodi();
	int y=H2->numNodi();
	
	FibMaxHeap<T>* Hresult=new FibMaxHeap<T>;
	
	
	//concatenare liste radici
	Hresult=H1;
	((Hresult->ritornaTesta())->left)->right=H2->ritornaTesta();
	Nodo<T>* tmp=(H2->ritornaTesta())->left;
	(H2->ritornaTesta())->left=(Hresult->ritornaTesta())->left;
	
	(Hresult->ritornaTesta())->left=tmp;
	tmp->right=Hresult->ritornaTesta();

	if((H1->ritornaExtreme())->key > (H2->ritornaExtreme())->key) //compare(potrebbe dare problemi)
	{
		Nodo<T>* m; 
		m=H1->ritornaExtreme();
		Hresult->setExtreme(m);
	}
	else 
	{ 
        Nodo<T>* n; 
		n=H2->ritornaExtreme();
		Hresult->setExtreme(n);
	}
	H1=NULL;
	H2=NULL;
	Hresult->setnumero_nodi(x+y);
	return Hresult;
}
/***********************************************************************************************/
/************************UNIONE TRA DUE HF*********************************************/
/***********************************************************************************************/



/*--------------------------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************/
/************************LINKING TRA Y E X( Y DIVENTA FIGLIO DI X)*********************************************/
/***********************************************************************************************/
template <class T>
void FibonacciHeap<T>::LINK(Nodo<T>* y,Nodo<T>* x) 
{
	//rimuovere y dalla lista delle radici
	(y->left)->right=y->right;
	(y->right)->left=y->left;
	
	if(y==testa) {testa=y->right;}
	
	//far diventare y figlio di x
	if(x->figlio==NULL)  //caso x non ha figli
	{
		x->figlio=y;
		y->padre=x;
		y->right=y->left=y;
	}
	else //x ha almeno un figlio
	{
		y->right=x->figlio;
		
		Nodo<T>* z=(x->figlio)->left;
		z->right=y;
		
		(x->figlio)->left=y;
		y->left=z;
		
		y->padre=x;
		x->figlio=y;
	}
	x->degree++;
	y->mark=false;
	
}
/***********************************************************************************************/
/************************LINKING TRA Y E X( Y DIVENTA FIGLIO DI X)*********************************************/
/***********************************************************************************************/



/*--------------------------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************/
/************************CONSOLIDAMENTO ALBERI*********************************************/
/***********************************************************************************************/
template <class T>
void FibonacciHeap<T>::CONSOLIDATE()
{
	int D=int(log(this->numNodi())/log(2));
	Nodo<T>* A[D];
	for(int i=0; i<=D;i++) A[i]=NULL;
	//A array_ausiliario 
	//per ogni nodo nella lista delle radici...
	Nodo<T>* iter=testa;
	do
	{
		int d=iter->degree;  
		while(A[d]!=NULL &&iter!=A[d])
		{
			Nodo<T>* y=A[d];
		
			if(this->compare(y->key,iter->key))  
			{
				Nodo<T>* tmp=iter;
				iter=y;
				y=tmp;
			}
			LINK(y,iter);
			A[d]=NULL;
			d++;
		}
		A[d]=iter;
		iter=iter->right;
	}while(iter!=testa);

    this->setExtreme(NULL);
	
	for(int i=0;i<=D;i++)
	{
		if(A[i]!=NULL)
		{
			if(this->ritornaExtreme()==NULL)
			{
				testa=A[i];
				testa->left=testa;
				testa->right=testa;
			//	this->setmin(A[i]);
			    this->setExtreme(A[i]);
			}
			else
			{
				Nodo<T>* ultimo_nodo=testa->left;
				
				(A[i])->right=testa;
				(A[i])->left=ultimo_nodo;
				testa->left=A[i];
				testa=A[i];
				ultimo_nodo->right=testa;
				

				if(this->compare((A[i])->key,this->ritornaExtreme()->key)) this->setExtreme(A[i]);
				
			}
		}
	}
}
/***********************************************************************************************/
/************************CONSOLIDAMENTO ALBERI*********************************************/
/***********************************************************************************************/



/*--------------------------------------------------------------------------------------------------------------------------------------*/




/***********************************************************************************************/
/************************ESTRAZIONE ELEMENTO MINIMO*********************************************/
/***********************************************************************************************/
template <class T>
Nodo<T>* FibonacciHeap<T>::extractExtreme() 
{

	if(this->ritornaExtreme()==NULL) return NULL;
	
	//aggiungere tutti i figli di Extreme nella lista delle radici
	Nodo<T>* x=this->ritornaExtreme();
//	printlistaradici();
	if(x->figlio!=NULL)
	{
		Nodo<T>* iter=x->figlio;
		Nodo<T>* iter2=iter->right;
		iter->padre=NULL;
		insert(iter);

		while(iter2!=x->figlio)
		{
			iter=iter2;
			iter2=iter->right;
			iter->padre=NULL;
			insert(iter);
		}
		
	}
	//TOGLIERE MIN
	
	x->left->right=x->right;
	x->right->left=x->left;
	if(x==testa) testa=x->right;
	
	if(x==x->right){this->setExtreme(NULL);testa=NULL;}  
	else
	{
		this->setExtreme(x->right);
		CONSOLIDATE();
	}
	this->setnumero_nodi(this->numNodi()-1);
	return x;
}
/***********************************************************************************************/
/************************ESTRAZIONE ELEMENTO MINIMO*********************************************/
/***********************************************************************************************/



/*--------------------------------------------------------------------------------------------------------------------------------------*/



/***********************************************************************************************/
/************************METODI DECREASEKEY***********************************************************/
/***********************************************************************************************/
template <class T>
void FibonacciHeap<T>::changekey(T vecchiakey,T nuovakey)  //DK #1
{
	if(this->ritornaExtreme()==NULL) 
	{ 
        cout<<"errore ,struttura vuota"<<endl;
		return;
	}
	changekey(testa,vecchiakey,nuovakey);
	trovato=false;
}

template <class T>
void FibonacciHeap<T>::changekey(Nodo<T>* node,T vecchiakey,T nuovakey) //DK #2
{
	if(node==NULL) return;
    if(trovato==true) return;
	Nodo<T>*x=node;
	x->C='Y';
	Nodo<T>* p1=NULL;
	Nodo<T>* p2=NULL;
	
	if(x->key==vecchiakey)
	{ 
        trovato=true;
        p2=x;
		x->C='N';
		p1=p2;
		changekey(p1,nuovakey);
	}

    if(p2==NULL)
	{
	    if(x->figlio!=NULL) changekey(x->figlio,vecchiakey,nuovakey);
	    if(x->right->C !='Y' ) changekey(x->right,vecchiakey,nuovakey);
	}
	
    x->C='N';
}

template <class T>
void FibonacciHeap<T>::changekey(Nodo<T>* x,T nuovakey) //DK #3
{
	if(this->compare(x->key,nuovakey))
	{
		cout<<"errore , nuova key non accettabile"<<endl;
		return;
	}

	x->key=nuovakey;
	Nodo<T>* y=x->padre;

	if(y!=NULL && this->compare(x->key,y->key))  //compare
	{
		Taglio(x,y);
		Taglio_cascata(y);
	} 

	if(this->compare(x->key,this->ritornaExtreme()->key)) //compare
		this->setExtreme(x);
}
/***********************************************************************************************/
/************************METODI DECREASEKEY***********************************************************/
/***********************************************************************************************/





/*--------------------------------------------------------------------------------------------------------------------------------------*/






/***********************************************************************************************/
/************************METODI DI TAGLIO***********************************************************/
//(METODI DI SUPPORTO PER DECREASEKEY)************************************************************
/***********************************************************************************************/
template <class T>
void FibonacciHeap<T>::Taglio(Nodo<T>* x,Nodo<T>* y)
{
	//rimozione x dai figli di y
	
	if(x==x->right) //caso x figlio unico
	{
		y->figlio=NULL;
	}
	
	x->left->right=x->right;
	x->right->left=x->left;
	
	if(x==y->figlio) y->figlio=x->right;
	

	y->degree--;
	
	//inserimento di x nella lista delle radici
	
    x->right=testa;
	x->left=testa->left;
	Nodo<T>* tmp=testa->left;
	testa->left=x;
	testa=x;
	tmp->right=testa;
	
    
	x->padre=NULL;
	x->mark=false;
	//testa
}

template <class T>
void FibonacciHeap<T>:: Taglio_cascata(Nodo<T>* y)
{
	Nodo<T>* z=y->padre;
	if(z!=NULL)
	{
		if(y->mark==false) y->mark=true;
		else 
		{
			Taglio(y,z);
			Taglio_cascata(z);
		}
	}
	
}
/***********************************************************************************************/
/************************METODI DI TAGLIO***********************************************************/
//(METODI DI SUPPORTO PER DECREASEKEY)************************************************************
/***********************************************************************************************/



/***********************************************************************************************/
/************************FIND***********************************************************/
//****************************************************************************************
/***********************************************************************************************/
template <class T>
void FibonacciHeap<T>::find(Nodo<T>* node,T vecchiakey) //setta infinito al nodo trovato(se lo trova...)
{
	if(node==NULL) return;
	Nodo<T>*x=node;
	x->C='Y';
	Nodo<T>* p1=NULL;
	Nodo<T>* p2=NULL;
	
	if(x->key==vecchiakey)
	{ 
        p2=x;
		x->C='N';
		p1=p2;
	
		this->setinfinite(p1);

	}
    if(p2==NULL)
	{
	    if(x->figlio!=NULL) find(x->figlio,vecchiakey);
	    if(x->right->C !='Y' ) find(x->right,vecchiakey);
	}
	
    x->C='N';
}
/***********************************************************************************************/
/************************FIND***********************************************************/
//****************************************************************************************
/***********************************************************************************************/


