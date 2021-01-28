#include "progettoAlgoritmi.cpp"
#include <iostream>
using namespace std;

/***********************************************************************************************/
/************************MAIN*******************************************************************/
/***********************************************************************************************/
int main()
{
	
	/********TEST MIN HEAP*******************/
	cout<<"---------------------------MIN HEAP-------------------------"<<endl;
	FibMinHeap<int>* h1=new FibMinHeap<int>;
	h1->insert(4);
	h1->insert(2);
	h1->insert(10);
	h1->insert(100);
	h1->insert(17);
	
	h1->print();

	//TEST UNION
	FibMinHeap<int>* h2=new FibMinHeap<int>;
	h2->insert(18);
	h2->insert(65);
	h2->insert(12);
	h2->insert(19);
	h2->insert(198);
	h2->insert(171);
	h2->insert(171);
	h2->insert(171);
	h2->insert(171);
	
	cout<<"-------------------------------UNIONE--------------------------------------"<<endl;
	FibMinHeap<int>* h3=Union(h1,h2);
	h3->printlistaradici();
	h3->print();
	cout<<"-------------------------------UNIONE--------------------------------------"<<endl<<endl<<endl;

    
	cout<<"-------------------------------EXTRACT MIN--------------------------------------"<<endl;
	Nodo<int>* m=h3->extractMin();
	cout<<"minimo estratto :"<<m->getkey()<<endl<<endl;
	
	h3->printlistaradici();
	h3->print();
	
	m=h3->ritornaTesta();
   
	m=h3->extractMin();
	cout<<"minimo estratto :"<<m->getkey()<<endl<<endl;
	h3->printlistaradici();
	h3->print();
	
	h3->insert(1);
	h3->printlistaradici();
	h3->print();
	m=h3->extractMin();
	cout<<"minimo estratto :"<<m->getkey()<<endl<<endl;
	h3->printlistaradici();
	h3->print();
	cout<<"-------------------------------EXTRACT MIN--------------------------------------"<<endl<<endl<<endl;
	
	
	
	//decreasekey after extract min
	cout<<"-------------------------------DECREASEKEY--------------------------------------"<<endl;
	h3->decreasekey(17,5); //nodo che c'è
	h3->printlistaradici();
	h3->print();
	
	h3->decreasekey(171,2); //nodo che c'è
	h3->printlistaradici();
	h3->print();
	
	h3->decreasekey(2,-1); //è il minimo
	h3->printlistaradici();
	h3->print();
	
	cout<<"-------------------------------DECREASEKEY--------------------------------------"<<endl<<endl<<endl;
	
	
	//extract min after dk
	m=h3->extractMin();
	cout<<"minimo estratto :"<<m->getkey()<<endl<<endl;
	h3->printlistaradici();
	h3->print();
	
    //delete after decreasekey and extract min
	
	cout<<"-------------------------------DELETE--------------------------------------"<<endl;
	h3->pisanodelete(198);
	h3->printlistaradici();
	h3->print();
	
		
	h3->pisanodelete(5);
	h3->printlistaradici();
	h3->print();
	
	h3->pisanodelete(37);
	h3->printlistaradici();
	h3->print();
	
	cout<<"eliminazione min"<<endl;
	h3->pisanodelete(10); //eliminazione min
	h3->printlistaradici();
	h3->print();
	
	cout<<"------------------------------DELETE--------------------------------------"<<endl<<endl;
	
	//extract min after delete 
	m=h3->extractMin();
	cout<<"minimo estratto :"<<m->getkey()<<endl<<endl;
	h3->printlistaradici();
	h3->print();
	
	//decreasekey after delete
	h3->decreasekey(19,5);
	h3->printlistaradici();
	
	h3->print();
	
	
	
	FibMinHeap<int>* h4=new FibMinHeap<int>;
	h4->insert(20);
	h4->insert(2);
	h4->insert(10);
	h4->insert(98);
	h4->insert(13);
	
	//union after operations
    FibMinHeap<int>* h5=Union(h4,h3);
	h5->printlistaradici();
	h5->print();
//	cout<<h5->ritornaMin()->key<<endl;
	
	
	cout<<"delete of all"<<endl;
	
/*	h5->pisanodelete(13);
	h5->pisanodelete(98);
	h5->pisanodelete(10);
	h5->pisanodelete(2);
	h5->pisanodelete(20);
	h5->pisanodelete(100);
	h5->pisanodelete(18);
	h5->pisanodelete(12);
	h5->pisanodelete(65);
	h5->pisanodelete(5);
	h5->pisanodelete(171);
	h5->pisanodelete(171);
	h5->pisanodelete(171);
	*/
	
	h5->empty();
	
	//test di stampa con struttura vuota
	h5->printlistaradici();
	h5->print();
	
	//test di delete con struttura vuota
	h5->pisanodelete(5);
	h5->printlistaradici();
	h5->print();
	
	h5->insert(16);
	h5->printlistaradici();
	h5->print();
	
	cout<<h5->findMin()->getkey()<<" "<<h5->ritornaTesta()->getkey()<<endl;
	h5->pisanodelete(16);
	
//	cout<<"main"<<endl;
	h5->printlistaradici();
	h5->print();
	
	/********TEST MIN HEAP*******************/
	
	
	
	cout<<"---------------------------MAX HEAP-------------------------"<<endl;
	
	//*******TEST MAX HEAP*******************
	
	FibMaxHeap<int>* h1m=new FibMaxHeap<int>;
	h1m->insert(4);
	h1m->insert(2);
	h1m->insert(10);
	h1m->insert(100);
	h1m->insert(17);
	
	h1m->print();

	//TEST UNION
	FibMaxHeap<int>* h2m=new FibMaxHeap<int>;
	h2m->insert(18);
	h2m->insert(65);
	h2m->insert(12);
	h2m->insert(19);
	h2m->insert(198);
	h2m->insert(171);
	h2m->insert(171);
	h2m->insert(171);
	h2m->insert(171);
	
	cout<<"-------------------------------UNIONE--------------------------------------"<<endl;
	FibMaxHeap<int>* h3m=Union(h1m,h2m);
	h3m->printlistaradici();
	h3m->print();
	cout<<"-------------------------------UNIONE--------------------------------------"<<endl<<endl<<endl;

    
	cout<<"-------------------------------EXTRACT MAX--------------------------------------"<<endl;
	Nodo<int>* mm=h3m->extractMax();
	cout<<"max estratto :"<<mm->getkey()<<endl<<endl;
	
	h3m->printlistaradici();
	h3m->print();
	
	mm=h3m->ritornaTesta();
   
	mm=h3m->extractMax();
	cout<<"max estratto :"<<mm->getkey()<<endl<<endl;
	h3m->printlistaradici();
	h3m->print();
	cout<<"-------------------------------EXTRACT MAX--------------------------------------"<<endl<<endl<<endl;
	
	
	
	//increasekey after extract min
	cout<<"-------------------------------INCREASEKEY--------------------------------------"<<endl;
	h3m->increasekey(17,21);
	h3m->printlistaradici();
	h3m->print();
	
	h3m->increasekey(171,200);
	h3m->printlistaradici();
	
	h3m->print();
	
	cout<<"-------------------------------INCREASEKEY--------------------------------------"<<endl<<endl<<endl;
	
	
	//extract max after dk
	mm=h3m->extractMax();
	cout<<"max estratto :"<<mm->getkey()<<endl<<endl;
	h3m->printlistaradici();
	h3m->print();
	
    //delete after decreasekey and extract min
	
	cout<<"-------------------------------DELETE--------------------------------------"<<endl;
	h3m->pisanodelete(171); //171 c'è
	h3m->printlistaradici();
	h3m->print();
	
		
	h3m->pisanodelete(5); //5 non c'è
	h3m->printlistaradici();
	h3m->print();
	
	h3m->pisanodelete(37); //37 non c'è
	h3m->printlistaradici();
	h3m->print();
	
	cout<<"------------------------------DELETE--------------------------------------"<<endl<<endl;
	
	//extract max after delete 
	mm=h3m->extractMax();
	cout<<"max estratto :"<<mm->getkey()<<endl<<endl;
	h3m->printlistaradici();
	h3m->print();
	
	//increase after delete
	h3m->increasekey(19,5);
	h3m->printlistaradici();
	
	h3m->print();
	
	
	
	FibMaxHeap<int>* h4m=new FibMaxHeap<int>;
	h4m->insert(20);
	h4m->insert(10);
	h4m->insert(98);
	h4m->insert(13);
	
	//union after operations
    FibMaxHeap<int>* h5m=Union(h4m,h3m);
	h5m->printlistaradici();
	h5m->print();
//	cout<<h5->ritornaMin()->key<<endl;
	
	
	cout<<"delete of all"<<endl;
	
/*	h5m->pisanodelete(13);
	h5m->pisanodelete(98);
	h5m->pisanodelete(10);
	h5m->pisanodelete(10);
	h5m->pisanodelete(2);
	h5m->pisanodelete(20);
	h5m->pisanodelete(18);
	h5m->pisanodelete(12);
	h5m->pisanodelete(21);
	h5m->pisanodelete(19);
	h5m->pisanodelete(4);
	h5m->pisanodelete(65);
	h5m->pisanodelete(100);
*/	
	h5m->empty();

	//test di stampa con struttura vuota
	h5m->printlistaradici();
	h5m->print();
	
	//test di delete con struttura vuota
	h5m->pisanodelete(5);
	h5m->printlistaradici();
	h5m->print();
	
	h5m->insert(16);
	h5m->printlistaradici();
	h5m->print();
	
	cout<<h5m->findMax()->getkey()<<" "<<h5m->ritornaTesta()->getkey()<<endl;
	h5m->pisanodelete(16);
	h5m->printlistaradici();
	h5m->print();
	
	
	return 0;
}
