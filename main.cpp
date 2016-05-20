#include <stdlib.h>
#include <stdio.h>
#include "cirMgr.h"

using namespace std;

int main(int argc, char** argv)
{
	CirMgr *CirMgr = 0;
	CirMgr->readCircuit(argv[1]);
	//CirMgr->connect();
	//CirMgr->dfsTraversal();
	return 0;
}
