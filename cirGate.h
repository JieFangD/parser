#ifndef CIR_GATE_H
#define CIR_GATE_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class CirGate;

class CirGate
{
public:
   CirGate() : faninL(NULL),faninR(NULL),_ref(0){}
   ~CirGate() {}

   // Basic access methods
   string getTypeStr() const { return Type; }

   // Printing functions
   void printGate() const;
   void reportGate() const;
   void reportFanin(int level) ;
   void reportFanout(int level) ;
   void dfsTraversalD(CirGate*,int,int,bool,bool);
   void dfsTraversalU(CirGate*,int,int,bool,bool);
   bool isGlobalRef() { return (_ref==_gRef); }
   void setToGlobalRef() { _ref=_gRef; }
   static void setGlobalRef() { _gRef++; } 

   string           GateID;
   string           Type;    
   string           Symbol;
   vector<CirGate*> fanout;
   CirGate*         faninL;
   CirGate*         faninR;

private:
   static unsigned  _gRef;
   unsigned         _ref;
};

#endif // CIR_GATE_H
