#include <iostream>
#include <iomanip>
#include <cstdio>
#include <ctype.h>
#include <cassert>
#include <cstring>
#include <string>
#include <sstream>
#include <map>
#include "cirMgr.h"
#include "cirGate.h"

using namespace std;

string int2str(int i){
   stringstream istr;
   string str;
   istr<<i;
   istr>>str;
   return str;
}

vector<string> input;
vector<string> in;
vector<string> out;
map<string,CirGate*> AllGate;
map<string,CirGate*> AllWire;

bool CirMgr::readCircuit(const string& fileName)
{
   ifstream fin(fileName.c_str(),ios::in);
   string str;
   while(getline(fin,str)){     
      input.push_back(str);
   }
   fin.close();
   handleInput();
   return true;
}

void construct(CirGate* newGate, string str, int i){
	if (AllWire.find(str) == AllWire.end()){
		CirGate* newWire = new CirGate;
		newWire->GateID = str;
		AllWire[str] = newWire;
	}
	if (i == 0){
		AllWire[str]->fanout.push_back(newGate);
		newGate->faninL = AllWire[str];
	}
	else if (i == 1){
		AllWire[str]->fanout.push_back(newGate);
		newGate->faninR = AllWire[str];
	}
	else AllWire[str]->faninL = newGate;	
}

bool CirMgr::handleInput(){
	bool in_f, out_f;
	in_f = false;
	out_f = false;
   for(unsigned i = 0; i<input.size();i++){
      string word;
      stringstream istring(input[i]);
      istring >> word;
		if (word == "wire"){
			out_f = false;
		}
		else if (word == "output" || out_f == true){
			in_f = false;
			if (out_f == true) {
				int l = word.length();
				out.push_back(word.substr(0,l-1));
			}
			out_f = true;
			while (istring >> word){
				int l = word.length();
				out.push_back(word.substr(0,l-1));
			}
		}
		else if (word == "input" || in_f == true){
			if (in_f == true) {
				int l = word.length();
				in.push_back(word.substr(0,l-1));
			}
			in_f = true;
			while (istring >> word){
				int l = word.length();
				in.push_back(word.substr(0,l-1));
			}
		}
      else if (word[0] == 'N'){
         cout << word << endl;
         CirGate* newGate = new CirGate;
			newGate->Type = word;
			if (word == "NOT1"){
				istring >> word;
         	//cout << word << ' ';
				AllGate[word] = newGate;
				newGate->GateID = word;
				istring >> word;
				string str0, str1;
				istring >> str0;
				istring >> str1;
				int l0, l1;
				l0 = str0.length();
				l1 = str1.length();
				//cout << str0.substr(3,l0-5) << ' ';
				//cout << str1.substr(3,l1-4) << endl;
				if (str0[1] == 'A'){
					construct(newGate, str0.substr(3,l0-5), 0);
					construct(newGate, str1.substr(3,l1-4), 2);
				}
				else{
					construct(newGate, str0.substr(3,l0-4), 2);
					construct(newGate, str1.substr(3,l1-4), 0);
				}
			}
			else if (word == "NAND2"){
				istring >> word;
         	//cout << word << ' ';
				AllGate[word] = newGate;
				newGate->GateID = word;
				istring >> word;
				string str0, str1, str2;
				istring >> str0;
				istring >> str1;
				istring >> str2;
				int l0, l1, l2;
				l0 = str0.length();
				l1 = str1.length();
				l2 = str2.length();
				//cout << str0.substr(3,l0-5) << ' ';
				//cout << str1.substr(3,l1-5) << ' ';
				//cout << str2.substr(3,l2-4) << endl;
				if (str0[1] == 'A'){
					if (str1[1] == 'B'){
						construct(newGate, str0.substr(3,l0-5), 0);
						construct(newGate, str1.substr(3,l1-5), 1);
						construct(newGate, str2.substr(3,l2-4), 2);
					}
					else{
						construct(newGate, str0.substr(3,l0-5), 0);
						construct(newGate, str1.substr(3,l1-5), 2);
						construct(newGate, str2.substr(3,l2-4), 1);
					}
				}
				else if (str0[1] == 'B'){
					if (str1[1] == 'A'){
						construct(newGate, str0.substr(3,l0-5), 1);
						construct(newGate, str1.substr(3,l1-5), 0);
						construct(newGate, str2.substr(3,l2-4), 2);
					}
					else{
						construct(newGate, str0.substr(3,l0-5), 1);
						construct(newGate, str1.substr(3,l1-5), 2);
						construct(newGate, str2.substr(3,l2-4), 0);
					}

				}
				else{
					if (str1[1] == 'A'){
						construct(newGate, str0.substr(3,l0-5), 2);
						construct(newGate, str1.substr(3,l1-5), 0);
						construct(newGate, str2.substr(3,l2-4), 1);
					}
					else{
						construct(newGate, str0.substr(3,l0-5), 2);
						construct(newGate, str1.substr(3,l1-5), 1);
						construct(newGate, str2.substr(3,l2-4), 0);
					}
				}
			}
			else if (word == "NOR2"){
				istring >> word;
         	//cout << word << ' ';
				AllGate[word] = newGate;
				newGate->GateID = word;
				istring >> word;
				string str0, str1, str2;
				istring >> str0;
				istring >> str1;
				istring >> str2;
				int l0, l1, l2;
				l0 = str0.length();
				l1 = str1.length();
				l2 = str2.length();
				//cout << str0.substr(3,l0-5) << ' ';
				//cout << str1.substr(3,l1-5) << ' ';
				//cout << str2.substr(3,l2-4) << endl;
				if (str0[1] == 'A'){
					if (str1[1] == 'B'){
						construct(newGate, str0.substr(3,l0-5), 0);
						construct(newGate, str1.substr(3,l1-5), 1);
						construct(newGate, str2.substr(3,l2-4), 2);
					}
					else{
						construct(newGate, str0.substr(3,l0-5), 0);
						construct(newGate, str1.substr(3,l1-5), 2);
						construct(newGate, str2.substr(3,l2-4), 1);
					}
				}
				else if (str0[1] == 'B'){
					if (str1[1] == 'A'){
						construct(newGate, str0.substr(3,l0-5), 1);
						construct(newGate, str1.substr(3,l1-5), 0);
						construct(newGate, str2.substr(3,l2-4), 2);
					}
					else{
						construct(newGate, str0.substr(3,l0-5), 1);
						construct(newGate, str1.substr(3,l1-5), 2);
						construct(newGate, str2.substr(3,l2-4), 0);
					}

				}
				else{
					if (str1[1] == 'A'){
						construct(newGate, str0.substr(3,l0-5), 2);
						construct(newGate, str1.substr(3,l1-5), 0);
						construct(newGate, str2.substr(3,l2-4), 1);
					}
					else{
						construct(newGate, str0.substr(3,l0-5), 2);
						construct(newGate, str1.substr(3,l1-5), 1);
						construct(newGate, str2.substr(3,l2-4), 0);
					}
				}
			}
      }
   }
	printIn();
	printOut();
	printSummary();
	connect();
	//string s;
	//char c;
	for (unsigned i=0; i<in.size(); i++){
		dfsTraversal(AllWire[in[i]], "", 0, true);
	}
   return true;
}

void CirMgr::connect(){
	for(map<string,CirGate*>::iterator i=AllWire.begin(); i!=AllWire.end(); i++){  
		if ((((*i).second)->faninL) != NULL){
			if (((*i).second)->fanout.size() != 0) (((*i).second)->faninL)->fanout = ((*i).second)->fanout;
			else{
				((((*i).second)->faninL)->fanout).push_back((*i).second);
				(*i).second->Type = "out";
			}
		}
		else {
			(*i).second->Type = "in";
			//cout << (*i).second->GateID << endl;
		}
		vector<CirGate*> tmpOut = ((*i).second)->fanout;
		for(unsigned j=0; j<tmpOut.size(); j++){
			if ((*i).second->faninL != NULL){
				if (tmpOut[j]->faninL == (*i).second)	tmpOut[j]->faninL = (*i).second->faninL;
				else tmpOut[j]->faninR = (*i).second->faninL;
			}
		}
   }
	/*for(map<string,CirGate*>::iterator i=AllGate.begin(); i!=AllGate.end(); i++){
		if (((*i).second)->faninL != NULL && ((*i).second)->faninR != NULL)
			cout << ((*i).second)->GateID  << ' ' << ((*i).second)->faninL->GateID << ' ' << ((*i).second)->faninR->GateID << endl;
		if (((*i).second)->Type == "NOT1")
			cout << ((*i).second)->GateID  << ' ' << ((*i).second)->faninL->GateID << endl;
		if (((*i).second)->fanout.size() == 0)
			cout << "Out:" << ((*i).second)->GateID << endl;
	}*/
}
/**********************************************************/
/*   class CirMgr member functions for circuit printing   */
/**********************************************************/
/*********************
Circuit Statistics
==================
  PI          20
  PO          12
  AIG        130
------------------
  Total      162
*********************/
void
CirMgr::printSummary() const
{
   cout<<"Circuit Statistics"<<endl
       <<"=================="<<endl
       <<"  Gate Num"<<setw(6)<<right<<AllGate.size()<<endl
       <<"  In"<<setw(12)<<right<<in.size()<<endl
       <<"  Out"<<setw(11)<<right<<out.size()<<endl<<endl;
}

void CirMgr::printIn() const
{
	cout << "Inputs: ";
	for(unsigned i=0; i<in.size(); i++) cout << in[i] << ' ';
	cout << endl;
}

void
CirMgr::printOut() const
{
	cout << "Outputs: ";
	for(unsigned i=0; i<out.size(); i++) cout << out[i] << ' ';
	cout << endl;
}

bool trueGate(CirGate* from, CirGate* to){
	if (to->Type == "NOT1")
		return true;
	else if (to->Type == "NOR2"){
		if (to->faninL->time == to->faninR->time){
			if (to->faninL->value == 1 && to->faninR->value == 1)
				return true;
			else if (to->faninL->value == 0 && to->faninR->value == 0)
				return true;
			else if (to->faninL->value == 1 && to->faninR->value == 0 && to->faninL == from)
				return true;
			else if (to->faninL->value == 0 && to->faninR->value == 1 && to->faninR == from)
				return true;			
		}		
		else if (to->faninL->time > to->faninR->time){
			if (to->faninR->value == 1 && to->faninR == from)
				return true;
			else if (to->faninR->value == 0 && to->faninL == from)
				return true;
		}
		else if (to->faninL->time < to->faninR->time){
			if (to->faninL->value == 1 && to->faninL == from)
				return true;
			else if (to->faninL->value == 0 && to->faninR == from)
				return true;
		}
	}
	else if (to->Type == "NAND2"){
		if (to->faninL->time == to->faninR->time){
			if (to->faninL->value == 1 && to->faninR->value == 1)
				return true;
			else if (to->faninL->value == 0 && to->faninR->value == 0)
				return true;
			else if (to->faninL->value == 1 && to->faninR->value == 0 && to->faninR == from)
				return true;
			else if (to->faninL->value == 0 && to->faninR->value == 1 && to->faninL == from)
				return true;			
		}		
		else if (to->faninL->time > to->faninR->time){
			if (to->faninR->value == 1 && to->faninL == from)
				return true;
			else if (to->faninR->value == 0 && to->faninR == from)
				return true;
		}
		else if (to->faninL->time < to->faninR->time){
			if (to->faninL->value == 1 && to->faninR == from)
				return true;
			else if (to->faninL->value == 0 && to->faninL == from)
				return true;
		}
	}
	return false;
}

void CirMgr::dfsTraversal(CirGate* c, string s, int delay, bool left){	
	//cout << c->GateID;
	string str;
	if (c->Type != "in" && c->Type != "out" && left == true)
		str = s + c->GateID + "/A";
	else if (c->Type != "in" && c->Type != "out" && left == false)
		str = s + c->GateID + "/B";
	else
		str = s + c->GateID;
	if (c->fanout.size() != 0){
		str = str + " -> ";
		delay = delay + 1;
		for (unsigned i=0; i<c->fanout.size(); i++){
			if (c->fanout[i]->faninL == c) dfsTraversal(c->fanout[i], str, delay, true);
			else dfsTraversal(c->fanout[i], str, delay, false);
		}
	}
	else {
		cout << str << " delay = " << delay-1;
		cout << endl;
	}
}





