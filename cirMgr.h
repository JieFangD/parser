#ifndef CIR_MGR_H
#define CIR_MGR_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include "cirGate.h"

using namespace std;

class CirMgr
{
public:
   CirMgr() {}
   ~CirMgr() {}

   // Member functions about circuit construction
   bool readCircuit(const string&);

   // Member functions about circuit reporting
   void printSummary() const;
   void printIn() const;
   void printOut() const;
   bool handleInput();
	void connect();
   void dfsTraversal(CirGate*, string, int, bool);
	bool trueGate(CirGate*, CirGate*);

private:
   vector<string>    	sortGate;
   vector<string>    	Netlist;
   vector<string>    	Symb;
   bool              	foundInput;
   //map<string,CirGate*> AllGate;
	//map<string,CirGate*> AllWire;

   int               a[5];      //M,I,L,O,A
   int               ANum;
};

#endif // CIR_MGR_H
