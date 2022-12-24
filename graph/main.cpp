#include <cstdio>
#include "graph.h"
#include <string>

void writeOutput();
void insertNodeI();
void insertNodeII();
void removeNodeI();
void removeNodeII();
void breadthFirst();
void depthFirst();
void breadthFirstI();
void depthFirstI();
void copyConstructor();
void assignOperator();
void IsConnected();
void IsPathAvailable();
void route();
void test();


graph<string> g;
const int MAX_SIZE = 25;
 
int main()
{

	int choice = 0;

	while (true)
		{
			
			writeOutput();
			cin.sync();
			
			cin >> choice;
			if (cin.fail()) {cin.clear(); cin.sync(); choice = 0;} 

			switch(choice)
				{
					case 1:
						cout << " " << endl;
						insertNodeI();
						cout << " " << endl;
					break;
						
					case 2:
						cout << " " << endl;
						insertNodeII();
						cout << " " << endl;
					break;
					
					case 3:
						cout << " " << endl;
						removeNodeI();
						cout << " " << endl;
					break;
					
					case 4:
						cout << " " << endl;
						removeNodeII();
						cout << " " << endl;
					break;

					case 5:
						cout << " " << endl;
						breadthFirst();
						cout << " " << endl;
					break;

					case 6:
						cout << " " << endl;
						depthFirst();
						cout << " " << endl;
					break;
					
					case 7:
						cout << " " << endl;
						breadthFirstI();
						cout << " " << endl;
					break;

					case 8:
						cout << " " << endl;
						depthFirstI();
						cout << " " << endl;
					break;
					
					case 9:
						cout << " " << endl;
						g.generalBF();
						cout << " " << endl;
					break;

					case 10:
						cout << " " << endl;
						g.generalDF();
						cout << " " << endl;
					break;

					case 11:
						cout << " " << endl;
						copyConstructor();
						cout << " " << endl;
					break;

					case 12:
						cout << " " << endl;
						assignOperator();
						cout << " " << endl;
					break;
					
					case 13:
						cout << " " << endl;
						IsConnected();
						cout << " " << endl;
					break;

					case 14:
						cout << " " << endl;
						IsPathAvailable();
						cout << " " << endl;
					break;
					
					case 15:
						cout << " " << endl;
						route();
						cout << " " << endl;
					break;
					
					case 16:
						cout << " " << endl;
						test();
						cout << " " << endl;
					break;
					
				}
			
		}
		
	 
	return 0;

}



void writeOutput()
{

	cout << "1) insert node (I)" << endl;
	cout << "2) insert node (II)" << endl;
	cout << "3) remove node (I)" << endl;
	cout << "4) remove node (II)" << endl;
	cout << "5) breadth first search" << endl;
	cout << "6) depth first search" << endl;
	cout << "7) breadth first search (i)" << endl;
	cout << "8) depth first search (i)" << endl;
	cout << "9) general breadth first" << endl;
	cout << "10) general depth first" << endl;
	cout << "11) copy constructor" << endl;
	cout << "12) assign operator" << endl;
	cout << "13) is connected" << endl;
	cout << "14) is path available" << endl;
	cout << "15) route" << endl;
    cout << "15) test" << endl;

	cout << "Do your choice" << endl;

}

void test()
{
	graph<string> _G;
	
	typedef vertex<string> V;
	typedef m_iterator<V> I;
	typedef link<string>  L;

	V *v1 = _G.insertVertex("10");
	V *v2 = _G.insertVertex("20");
	
	_G.addLink(*v1,*v2);

	_G.show();
}

void insertNodeI()
{
	
	string str; 

	cout << "Insert the value of the node you want to create" << endl;
	
    cin.sync();
    cin>>str;

    
	if (cin.fail()) {cin.clear(); cin.sync(); return;}

	g.insertVertex(str);
	g.show();

	
}


void insertNodeII()
{
	string src; 
	string dst; 

	cout << "Insert source and destination of the link you want to create" << endl;
	cin.sync();
    cin>>src;
    cin>>dst;
     
    
	if (cin.fail()) {cin.clear(); cin.sync(); return;}

	g.insertVertex(src,dst);
	g.show();

	
}

void removeNodeI()
{
	
	string str;

	cout << "Insert the value of the node you want to delete" << endl;
	
    cin.sync();
    cin>>str;
     
    
	if (cin.fail()) {cin.clear(); cin.sync(); return;}

	g.removeVertex(str);
	g.show();

}


void removeNodeII()
{
	string src; 
	string dst; 

	cout << "Insert source and destination of the link you want to delete" << endl;
	cin.sync();
    cin>>src;
    cin>>dst;
     

	if (cin.fail()) {cin.clear(); cin.sync(); return;}

	g.removeLink(src,dst);
	g.show();
	
}

void breadthFirst()
{
	
	g.breadthFirst(g.begin());
}

void depthFirst()
{
	
	g.depthFirst(g.begin());
}


void breadthFirstI()
{
	
	string str; 
	
	cout << "Insert a value in the graph" << endl;
	
    cin.sync();
    cin>>str;
	
	if (cin.fail()) {cin.clear(); cin.sync(); return;}

	m_iterator< vertex <string> > P = g.locate(str);

	if (P != g.end())
		g.breadthFirst(&(*P));
	
}

void depthFirstI()
{
	
	string str; 
	
	cout << "Insert a value in the graph" << endl;
	
    cin.sync();
    cin>>str;

	
	if (cin.fail()) {cin.clear(); cin.sync(); return;}

	m_iterator< vertex <string> > P = g.locate(str);

	if (P != g.end())
		g.depthFirst(&(*P));

}

void IsConnected()
{
	
	string src; 
	string dst; 

	cout << "Insert source and destination of the link you want to check" << endl;
	cin.sync();
    cin >> src;
    cin >> dst;
     
	
	if (cin.fail()) {cin.clear(); cin.sync(); return;}

	const char *str = g.isConnected(src,dst)? "nodi connessi":"nessuna connessione tra i nodi";

	cout << str << endl;

}

void IsPathAvailable()
{
	
	string src; 
	string dst; 

	cout << "Insert source and destination of the link you want to check" << endl;
	cin.sync();
    cin>>src;
    cin>>dst;
     
    	
	if (cin.fail()) {cin.clear(); cin.sync(); return;}

	const char *str = g.isPathAvailable(src,dst)? "nodi connessi":"nessuna connessione tra i nodi";

	m_iterator< vertex <string> > P = g.locate(src);
	
	cout << str << endl;
	
}

void route()
{
	
	string src; 
	string dst; 

	cout << "Insert source and destination of the link you want to check" << endl;
	cin.sync();
    cin>>src;
    cin>>dst;
     
    	
	if (cin.fail()) {cin.clear(); cin.sync(); return;}

	const char *str = g.isPathAvailable(src,dst)? "nodi connessi":"nessuna connessione tra i nodi";

	g.routeTo(src,dst);
	
	 
	
}

void copyConstructor()
{
	
	graph<string> copy(g);
	copy.show();

}

void assignOperator()
{
	
	graph<string> copy;

	copy = g;
	copy.show();

}
