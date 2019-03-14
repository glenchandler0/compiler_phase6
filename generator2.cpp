# include <iostream>
# include <sstream>
# include "generator2.h"
// # include "generator.h"

using namespace std;

int offset = 0;

typedef vector<Register *>Registers;

//Normal Registers
static Register *eax = new Register("%eax", "%al");
static Register *edx = new Register("%edx");
static Register *ecx = new Register("%ecx");
static Registers registers = {eax, edx, ecx};

//FP Registers TODO: Check this
static Register *xmm0 = new Register("%xmm0");
static Register *xmm1 = new Register("%xmm1");
static Register *xmm2 = new Register("%xmm2");
static Register *xmm3 = new Register("%xmm3");
static Register *xmm4 = new Register("%xmm4");
static Register *xmm5 = new Register("%xmm5");
static Register *xmm6 = new Register("%xmm6");
static Register *xmm7 = new Register("%xmm7");
static Registers fp_registers = {xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7};


//****************** More Tree.h implementations ****************
/*
void Expression::test(const Label &label, bool ifTrue)
{
	generate();

	if (_register == nullptr)
		load(this, getreg());

	cout << "\tcmpl\t$0, " << this << endl;
	cout << (ifTrue ? "\tjne\t" : "\tje\t") << label << endl;

	assign(this, nullptr);
}
*/
