
/* IMPLEMENTAZIONE HEAP DI FIBONACCI TEMPLATE
   SAMUELE MARIA GALLINA
   
 //  RUNNABILE SIA SU WIN CHE UBUNTU
	 
*/

#include <iostream>
#include <cmath> //ci saranno dei calcoli logaritmici

using namespace std;

template <class T>
class Nodo  
{
	private:
		Nodo<T>* padre;
		Nodo<T>* figlio;
		Nodo<T>* right;
		Nodo<T>* left;
	
		T key;
		int degree; //suo numero di figli
		bool mark;

		char C;  //variabile utile per poter cercare il nodo
		
	public:
	
	    Nodo<T>* getpadre(){return padre;}
		Nodo<T>* getfiglio(){return figlio;}
		Nodo<T>* getright(){return right;}
		Nodo<T>* getleft(){return left;}
		
		T getkey(){return key;}
		int getdegree(){return degree;}
		bool getmark(){return mark;}
		
		char getC(){return C;}
	
		void setpadre(Nodo<T>* x){padre=x;}
		void setfiglio(Nodo<T>* x){figlio=x;}
		void setright(Nodo<T>* x){right=x;}
		void setleft(Nodo<T>* x){left=x;}
		
		void setkey(T x){key=x;}
		void setdegree(int x){degree=x;}
		void setmark(bool x){mark=x;}
		
		void setC(char x){C=x;}
		
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
			
			if(k==this->ritornaExtreme()->getkey()){Nodo<T>* x=extractExtreme(); delete x; /*evitare memory leak*/ }
			else
			{
				find(this->ritornaTesta(),k);
				Nodo<T>*x=this->returnInfinite();
				if(x==NULL) return; //elemento non presente
				
				Nodo<T>* y=x->getpadre();
				if(y!=NULL) 
				{
					Taglio(x,y);
					Taglio_cascata(y);
				}
				this->setinfinite(NULL);
				//aggiungere figli di x alla lista delle radici
				if(x->getfiglio()!=NULL)
	            {
		            Nodo<T>* iter=x->getfiglio();
					Nodo<T>* iter2=iter->getright();
				    iter->setpadre(NULL);
					insert(iter);

					while(iter2!=x->getfiglio())
					{
						iter=iter2;
						iter2=iter->getright();
						iter->setpadre(NULL);
						insert(iter);
					}
				}
				//togliere x dalla lista delle radici
				x->getleft()->setright(x->getright());
				
				x->getright()->setleft(x->getleft());
				
	            if(x==testa) testa=x->getright();
				
				
				delete x; //evitare memory leak
				
				
				this->setnumero_nodi(this->numNodi()-1);
	
			}
		}
		
		void empty()
		{
			if(this->ritornaExtreme()==NULL) return; //struttura vuota
			
			while(this->ritornaExtreme()!=NULL)
			{
				Nodo<T>* x=extractExtreme();
				delete x;
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
	
	for(iter=testa->getright();iter!=testa;iter=iter->getright())
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
		cout<<x->getkey()<<" "<<"grado="<<x->getdegree()<<" ";
		if(x->getfiglio()!=NULL)
		{
			Nodo<T>* iter=x->getfiglio();
			cout<<"->[figli di "<<x->getkey()<<" : "; 
			preorder(iter);
			for(iter=x->getfiglio()->getright();iter!=x->getfiglio();iter=iter->getright())
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
	cout<<"LISTA RADICI: "<<iter->getkey()<<" ";
	while(iter->getright()!=testa)
	{
		iter=iter->getright();
		cout<<iter->getkey()<<" ";
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
	nuovo->setkey(key);
	nuovo->setpadre(NULL); nuovo->setfiglio(NULL);
	nuovo->setright(NULL); nuovo->setleft(NULL);
	nuovo->setdegree(0);
	nuovo->setmark(false);
	nuovo->setC('N');
	
	if(this->ritornaExtreme()==NULL)  //lista con il solo nodo "nuovo"
	{
		nuovo->setright(nuovo);
		
		nuovo->setleft(nuovo);
		
		this->setExtreme(nuovo);
		testa=nuovo;
	}
	else  //inserire "nuovo" nella lista, optiamo per l'inserimento in testa
	{
		Nodo<T>* ultimo_nodo=testa->getleft();
		
		nuovo->setright(testa);
		nuovo->setleft(ultimo_nodo);
		testa->setleft(nuovo);
		
		testa=nuovo;
	    ultimo_nodo->setright(testa);

		if(this->compare(testa->getkey() , this->ritornaExtreme()->getkey())) //compare
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
	nuovo->setC('N');
	if(this->ritornaExtreme()==NULL)  //lista con il solo nodo "nuovo"
	{
		nuovo->setright(nuovo);
		nuovo->setleft(nuovo);
		
		this->setExtreme(nuovo);
		testa=nuovo;
	}
	else  //inserire "nuovo" nella lista, optiamo per l'inserimento in testa
	{
		Nodo<T>* ultimo_nodo=testa->getleft();
		
		nuovo->setright(testa);
		nuovo->setleft(ultimo_nodo);
		
		testa->setleft(nuovo);
		
		testa=nuovo;

	    ultimo_nodo->setright(testa);

		if(this->compare(testa->getkey(),this->ritornaExtreme()->getkey())) //compare
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
	((Hresult->ritornaTesta())->getleft())->setright(H2->ritornaTesta());
	
	Nodo<T>* tmp=(H2->ritornaTesta())->getleft();
	(H2->ritornaTesta())->setleft((Hresult->ritornaTesta())->getleft());

	(Hresult->ritornaTesta())->setleft(tmp);

	tmp->setright(Hresult->ritornaTesta());

	if((H1->ritornaExtreme())->getkey() < (H2->ritornaExtreme())->getkey()) 
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
	((Hresult->ritornaTesta())->getleft())->setright(H2->ritornaTesta());
	
	Nodo<T>* tmp=(H2->ritornaTesta())->getleft();

	(H2->ritornaTesta())->setleft((Hresult->ritornaTesta())->getleft());

	(Hresult->ritornaTesta())->setleft(tmp);

	tmp->setright(Hresult->ritornaTesta());


	if((H1->ritornaExtreme())->getkey() > (H2->ritornaExtreme())->getkey()) 
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
	(y->getleft())->setright(y->getright());

	(y->getright())->setleft(y->getleft());
	
	if(y==testa) {testa=y->getright();}
	
	//far diventare y figlio di x
	if(x->getfiglio()==NULL)  //caso x non ha figli
	{
		x->setfiglio(y);
		
		y->setpadre(x);

		y->setright(y);
		y->setleft(y);
	}
	else //x ha almeno un figlio
	{
		y->setright(x->getfiglio());
		
		Nodo<T>* z=(x->getfiglio())->getleft();
		z->setright(y);

		x->getfiglio()->setleft(y);

		y->setleft(z);

		y->setpadre(x);

		x->setfiglio(y);
	}
	x->setdegree(x->getdegree()+1);

	y->setmark(false);
	
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
		int d=iter->getdegree();  
		while(A[d]!=NULL &&iter!=A[d])
		{
			Nodo<T>* y=A[d];
		
			if(this->compare(y->getkey(),iter->getkey()))  
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
		iter=iter->getright();
	}while(iter!=testa);

    this->setExtreme(NULL);
	
	for(int i=0;i<=D;i++)
	{
		if(A[i]!=NULL)
		{
			if(this->ritornaExtreme()==NULL)
			{
				testa=A[i];
				testa->setleft(testa);
				
				testa->setright(testa);
				
			    this->setExtreme(A[i]);
			}
			else
			{
				Nodo<T>* ultimo_nodo=testa->getleft();

				(A[i])->setright(testa);

				(A[i])->setleft(ultimo_nodo);

				testa->setleft(A[i]);
				
				testa=A[i];
				ultimo_nodo->setright(testa);

				if(this->compare((A[i])->getkey(),this->ritornaExtreme()->getkey())) this->setExtreme(A[i]);
				
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
	if(x->getfiglio()!=NULL)
	{
		Nodo<T>* iter=x->getfiglio();
		Nodo<T>* iter2=iter->getright();
		
		iter->setpadre(NULL);
		insert(iter);

		while(iter2!=x->getfiglio())
		{
			iter=iter2;
			iter2=iter->getright();
			
			iter->setpadre(NULL);
			insert(iter);
		}
		
	}
	//TOGLIERE MIN

	x->getleft()->setright(x->getright());
	
	x->getright()->setleft(x->getleft());
	if(x==testa) testa=x->getright();
	
	if(x==x->getright()){this->setExtreme(NULL);testa=NULL;}  
	else
	{
		this->setExtreme(x->getright());
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
    if(trovato==true) return;  //evita chiamate ricorsive eccessive
	Nodo<T>*x=node;
	x->setC('Y');
	Nodo<T>* p1=NULL;
	Nodo<T>* p2=NULL;
	
	if(x->getkey()==vecchiakey)
	{ 
        trovato=true;
        p2=x;
	//	x->C='N';
		x->setC('N');
		
		p1=p2;
		changekey(p1,nuovakey);
	}

    if(p2==NULL)
	{
	    if(x->getfiglio()!=NULL) changekey(x->getfiglio(),vecchiakey,nuovakey);
	    if(x->getright()->getC() !='Y' ) changekey(x->getright(),vecchiakey,nuovakey);
	}
	
	x->setC('N');
}

template <class T>
void FibonacciHeap<T>::changekey(Nodo<T>* x,T nuovakey) //DK #3
{
	if(this->compare(x->getkey(),nuovakey))
	{
		cout<<"errore , nuova key non accettabile"<<endl;
		return;
	}

	x->setkey(nuovakey);
	
	Nodo<T>* y=x->getpadre();

	if(y!=NULL && this->compare(x->getkey(),y->getkey()))  //compare
	{
		Taglio(x,y);
		Taglio_cascata(y);
	} 

	if(this->compare(x->getkey(),this->ritornaExtreme()->getkey())) //compare
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
	
	if(x==x->getright()) //caso x figlio unico
	{
		y->setfiglio(NULL);
	}
	
	x->getleft()->setright(x->getright());
	
	x->getright()->setleft(x->getleft());
	
	if(x==y->getfiglio()) y->setfiglio(x->getright());
	
	

	y->setdegree(y->getdegree()-1);
	
	//inserimento di x nella lista delle radici
	
	x->setright(testa);
	x->setleft(testa->getleft());
	
	Nodo<T>* tmp=testa->getleft();
	testa->setleft(x);
	testa=x;
	
	tmp->setright(testa);
	
    
	x->setpadre(NULL);
	
	x->setmark(false);
	//testa
}

template <class T>
void FibonacciHeap<T>:: Taglio_cascata(Nodo<T>* y)
{
	Nodo<T>* z=y->getpadre();
	if(z!=NULL)
	{
		if(y->getmark()==false){ y->setmark(true); }
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




/*--------------------------------------------------------------------------------------------------------------------------------------*/




/***********************************************************************************************/
/************************FIND***********************************************************/
//****************************************************************************************
/***********************************************************************************************/
template <class T>
void FibonacciHeap<T>::find(Nodo<T>* node,T vecchiakey) //setta infinito al nodo trovato(se lo trova...)
{
	if(node==NULL) return;
	Nodo<T>*x=node;
	x->setC('Y');
	Nodo<T>* p1=NULL;
	Nodo<T>* p2=NULL;
	
	if(x->getkey()==vecchiakey)
	{ 
        p2=x;
		x->setC('N');
		p1=p2;
	
		this->setinfinite(p1);

	}
    if(p2==NULL)
	{
	    if(x->getfiglio()!=NULL) find(x->getfiglio(),vecchiakey);
	    if(x->getright()->getC() !='Y' ) find(x->getright(),vecchiakey);
	}
	
	x->setC('N');
}
/***********************************************************************************************/
/************************FIND***********************************************************/
//****************************************************************************************
/***********************************************************************************************/
