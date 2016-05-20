#include <iostream>
#include <iomanip>
#include <sstream>
#include <cassert>
#include "cirGate.h"
#include "cirMgr.h"
#include "util.h"

using namespace std;

void
CirGate::reportGate() const
{
   cout<<"=================================================="<<endl
       <<setw(50)<<'='<<'\r'<<"= "<<Type<<'('<<GateID<<')';
   if(Symbol.size()!=0)
      cout<<"\""<<Symbol<<"\"";
   cout<<", line "<<LineNo<<endl
       <<"=================================================="<<endl;
}

void
CirGate::reportFanin(int level) 
{
   assert (level >= 0);
   CirGate::setGlobalRef();
   this->dfsTraversalD(this,level,0,false,false);
}

void
CirGate::reportFanout(int level) 
{
   assert (level >= 0);
   CirGate::setGlobalRef();
   this->dfsTraversalU(this,level,0,false,false);
}
void 
CirGate::dfsTraversalU(CirGate* c,int l,int n,bool invert,bool reprint)
{
   for(int i=0;i<2*n;i++)
      cout<<' ';
   if(invert==true)
      cout<<'!';
   if(reprint==true)
      cout<<c->Type<<' '<<c->GateID<<" (*)"<<endl;
   else
      cout<<c->Type<<' '<<c->GateID<<endl;
   c->setToGlobalRef();
   if(l>n&&!reprint){
      for(int i=0;i<c->fanout.size();i++){
         if(!c->fanout[i]->isGlobalRef()){
            if(c->fanout[i]->faninL==c)
               invert=c->fanout[i]->invertL;
            else if(c->fanout[i]->faninR==c)
               invert=c->fanout[i]->invertR;
            dfsTraversalU(c->fanout[i],l,n+1,invert,reprint);
         }
         else if(c->fanout[i]->isGlobalRef()){
            if(n<l-1)
               reprint=true;
            if(c->fanout[i]->faninL==c->fanout[i]->faninR)
               invert=c->fanout[i]->invertR;
            else{
               if(c->fanout[i]->faninL==c)
                  invert=c->fanout[i]->invertL;
               else if(c->fanout[i]->faninR==c)
                  invert=c->fanout[i]->invertR;
            }
            dfsTraversalU(c->fanout[i],l,n+1,invert,reprint);
         }
      }
   }
}
void 
CirGate::dfsTraversalD(CirGate* c,int l,int n,bool invert,bool reprint)
{
   for(int i=0;i<2*n;i++)
      cout<<' ';
   if(invert==true)
      cout<<'!';
   if(reprint==true)
      cout<<c->Type<<' '<<c->GateID<<" (*)"<<endl;
   else
      cout<<c->Type<<' '<<c->GateID<<endl;
   c->setToGlobalRef();
   if(l>n&&!reprint){
      if(c->faninL!=NULL&&!c->faninL->isGlobalRef()){
         invert=c->invertL;
         dfsTraversalD(c->faninL,l,n+1,invert,reprint);
      }
      else if(c->faninL!=NULL&&c->faninL->isGlobalRef()){
         if(n<l-1&&(c->faninL->Type!="PI"&&c->faninL->Type!="CONST"))
            reprint=true;
         invert=c->invertL;
         dfsTraversalD(c->faninL,l,n+1,invert,reprint);
         reprint=false;
      }
      if(c->faninR!=NULL&&!c->faninR->isGlobalRef()){
         invert=c->invertR;
         dfsTraversalD(c->faninR,l,n+1,invert,reprint);
      }
      else if(c->faninR!=NULL&&c->faninR->isGlobalRef()){
         if(n<l-1&&(c->faninR->Type!="PI"&&c->faninR->Type!="CONST"))
            reprint=true;
         invert=c->invertR;
         dfsTraversalD(c->faninR,l,n+1,invert,reprint);
         reprint=false;
      }
   }
}








