/*
 * File:	generator.cpp
 *
 * Description:	This file contains the public and member function
 *		definitions for the code generator for Simple C.
 *
 *		Extra functionality:
 *		- putting all the global declarations at the end
 */

# include <sstream>
# include <iostream>
# include "generator.h"
# include "machine.h"
// # include "Tree.h"
# include "Register.h"
# include "label.h"

using namespace std;

//FP
//Comparison, different assembly instructions

/* This needs to be set to zero if temporaries are placed on the stack. */

# define SIMPLE_PROLOGUE 0


/* This should be set if we want to use the callee-saved registers. */

# define CALLEE_SAVED 0

/*
 * Function:	operator << (private)
 *
 * Description:	Write an expression to the specified stream.  This function
 *		first checks to see if the expression is in a register, and
 *		if not then uses its operand.
 */

/*
static ostream &operator <<(ostream &ostr, Expression *expr)
{
    if (expr->_register != nullptr)
	return ostr << expr->_register;

    return ostr << expr->_operand;
}
*/

ostream& operator<<(ostream &ostr, Expression *expr)
{
    if (expr->_register == nullptr)
        return ostr << expr->_operand;

    unsigned size = expr->type().size();
    return ostr << expr->_register->name(size);
}

/* The registers and their related functions */
int offset;
Label *retLabel;

//.data section
typedef std::vector<string> Strings;
Strings stringLabels;
typedef std::vector<string> Reals;
Reals realLabels;

static std::string suffix(Expression *expr) { return FP(expr) ? "sd\t" : (BYTE(expr) ? "b\t" : "l\t"); }

typedef vector<Register *>Registers;

static Register *ebx = new Register("%ebx", "%bl");
static Register *esi = new Register("%esi");
static Register *edi = new Register("%edi");
# if CALLEE_SAVED
static Registers callee_saved = {ebx, esi, edi};
# else
static Registers callee_saved = {};
# endif

static Register *eax = new Register("%eax", "%al");
static Register *edx = new Register("%edx", "%dl");
static Register *ecx = new Register("%ecx", "%cl");
static Registers registers = {eax, edx, ecx};

static Register *xmm0 = new Register("%xmm0");
static Register *xmm1 = new Register("%xmm1");
static Register *xmm2 = new Register("%xmm2");
static Register *xmm3 = new Register("%xmm3");
static Register *xmm4 = new Register("%xmm4");
static Register *xmm5 = new Register("%xmm5");
static Register *xmm6 = new Register("%xmm6");
static Register *xmm7 = new Register("%xmm7");
static Registers fp_registers = {xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7};

//======================== Control Functions ======================
//Function for testing booleans, used in other control functions
void Expression::test(const Label &label, bool ifTrue)
{
    generate();

    if (_register == nullptr)
        load(this, getreg());

    cout << "\tcmpl\t$0, " << this << endl;
    cout << (ifTrue ? "\tjne\t" : "\tje\t") << label << endl;

    assign(this, nullptr);
}


void While::generate()
{
    cout << "# While call" << endl;

    Label loop, exit;
    cout << loop << ":" << endl;
    _expr->test(exit, false); //TODO: Test this
    _stmt->generate();
    release();

    cout << "\tjmp\t" << loop << endl;
    cout << exit << ":" << endl;
}

//First sets up expression check to either jump to else, or exit when if fails
//Then checks else isn't null to output contents and label
//Finally places exit label
void If::generate()
{
    cout << "# If call" << endl;

    Label ifLabel, elseLabel, exitLabel;

    //Code to test if label
    if(_elseStmt != NULL)
        _expr->test(elseLabel, false);
    else
        _expr->test(exitLabel, false);

    //Then label, then jump to exit
    _thenStmt->generate();
    cout << "\tjmp\t" << exitLabel << endl;

    if(_elseStmt != NULL)
    {
        //Else label
        cout << elseLabel << ":" << endl;
        //Else statement
        _elseStmt->generate();
    }
    cout << exitLabel << ":" << endl;
}

//TODO: Check that this works
void Return::generate()
{
	//TODO: Should we be able to return literals?
    cout << "# Return call" << endl;
    //Call generate on Expression
    _expr->generate();

    //Save expression result in some register
    //Maybe check if part of assignment
    load(_expr, eax); //Shuld be getreg()?

    //TODO: Jump to function epilogue so it skips rest of function
    //TODO: Need to make it so we have function global set
    	//How do we have any number of function labels?
    cout << "\tjmp\t" << *retLabel << endl; //TODO: Maybe don't need this?
}

//Assignment implemented below


//======================== Unary Functions =========================
//TODO: For unary, do I need to be releasing getreg()?
void Not::generate()
{
    cout << "# Not call" << endl;

    _expr->generate();

    load(_expr, getreg());
    cout << "\tcmp"<< suffix(_expr) << "$0, " << _expr << endl;
    cout << "\tsete\t" << _expr->_register->byte() << endl;
    cout << "\tmovzbl\t" << _expr->_register->byte() << ", " << _expr << endl;

    assign(this, _expr->_register); //Check
}

void Negate::generate()
{
    cout << "# Unary function call" << endl;

    _expr->generate();

    load(_expr, getreg());
    cout << "\tneg" << suffix(_expr) << _expr << endl;

    assign(this, _expr->_register);
}

//TODO: Need to find a way to test dereference

void Dereference::generate()
{
    cout << "# Dereference call" << endl;

    _expr->generate();

	if(_expr->_register == nullptr)
	    load(_expr, getreg());

    cout << "\tmov" << suffix(_expr) << "(" << _expr << "), ";
    assign(_expr, nullptr); //Lets go of register to use

    assign(this, FP(this) ? fp_getreg(): getreg());
    cout << this << endl;
}

void Address::generate()
{
    cout << "# Address call" << endl;

	//Not a dereference
    if(_expr->isDereference() == nullptr)
    {
		_expr->generate();
		assign(this, getreg()); //Needs to be 32 since it will be address
		cout << "\tlea" << suffix(_expr) << _expr << ", " << this << endl;
    }
    else //If expression is a dereference
    {
    	Expression *child = _expr->isDereference();
        child->generate();

        //Load variable being dereferenced into this
        load(child, getreg());

        assign(this, child->_register);
        _operand = _expr->_operand;
    }
}

void Cast::generate()
{
    cout << "# Cast call" << endl;

    _expr->generate();

    if(_expr->_register == nullptr)
    	load(_expr, FP(_expr) ? fp_getreg(): getreg());

    const Type &src = _expr->type(), &dest = _type;

    if(src.size() == 1) //Src is char
    {
    	if(dest.size() == 1) {
    		assign(this, _expr->_register);
    	} else if(dest.size() == 4) {
            //assign(this, getreg());
            cout << "\tmovsbl\t" << _expr << ", " << _expr->_register->name() << endl;
    		assign(this, _expr->_register);
    	} else {
            //sign extend into 32 bit

            //cvt 32 bit to 64 bit
    		assign(this, fp_getreg());
    		cout << "\tcvtsi2sd\t" << _expr << ", " << this << endl;
    		assign(_expr, nullptr);
    	}
    }
    else if(src.size() == 4) //Src is int
    {
    	if(dest.size() == 1) {
    		assign(this, _expr->_register);
    	} else if(dest.size() == 4) {
    		assign(this, _expr->_register);
    	} else {
    		assign(this, fp_getreg());
    		cout << "\tcvtsi2sd\t" << _expr << ", " << this << endl;
    		assign(_expr, nullptr);
    	}
    }
    else if(src.size() == 8) //Src is fp
    {
    	if(dest.size() == 1) {
    	} else if(dest.size() == 4) {
    		assign(this, getreg());
    		cout << "\tcvttsd2si\t" << _expr << ", " << this << endl;
    		assign(_expr, nullptr);
    	}
    	else {
            //Do nothing?
    	}

    }
}

//========================= Binary Functions =======================
//--- Arithmetic functions -----
void genArithmetic(Expression* result, Expression *left, Expression *right, const string& op)
{
    left->generate();
    right->generate();

    if(left->_register == nullptr)
        load(left, FP(left) ? fp_getreg() : getreg());

    cout << "\t" << op << suffix(left);
    cout << right << ", " << left << endl;

    assign(right, nullptr);
    assign(result, left->_register);
}

void int_divide(Expression* result, Expression *left, Expression *right, Register *reg)
{
    left->generate();
    right->generate();

    //Performs move for us
    load(left, eax);
    cout << "\tcltd" << endl;
    load(right, ecx);
    cout << "\tidivl\t" << right << endl; //edx:eax = edx:eax / ecx

    assign(nullptr, eax);
    assign(nullptr, edx);
    assign(nullptr, ecx);
    assign(result, reg);
}

void Add::generate()
{
    cout << "# Add call" << endl;
    genArithmetic(this, _left, _right, "add");
}

void Subtract::generate()
{
    cout << "# Subtract call" << endl;
    genArithmetic(this, _left, _right, "sub");
}

void Multiply::generate()
{
    cout << "# Multiply call" << endl;
    genArithmetic(this, _left, _right, FP(_left) ? "mul" : "imul");
}

void Divide::generate()
{
    cout << "# Divide call" << endl;
    if(FP(_left)) genArithmetic(this, _left, _right, "div");
    else int_divide(this, _left, _right, eax);
}

void Remainder::generate()
{
    cout << "# Remainder call" << endl;
    int_divide(this, _left, _right, edx);
}


//----- logical control functions --------
//TODO: More or less complete, still unsure about release() call
void logicFunction(Expression *result, Expression *left, Expression *right, const string& op)
{
    left->generate();
    right->generate();

    release(); //TODO: Should we be doing this here?
    load(left, getreg()); //movl x,%eax
    cout << "\tcmpl\t" << right << ", " << left << endl; //cmpl y, %eax
    cout << "\t" << op << "\t" << left->_register->byte() << endl; //setl %al. Should be char part of whatever reg?
    cout << "\tmovzbl\t" << left->_register->byte() << ", " << left << endl;

    assign(right, nullptr);
    assign(result, left->_register);
}

void LessThan::generate()
{
    cout << "# LessThan call" << endl;
    logicFunction(this, _left, _right, "setl");
}

void GreaterThan::generate()
{
    cout << "# GreaterThan call" << endl;
    logicFunction(this, _left, _right, "setg");
}

void LessOrEqual::generate()
{
    cout << "# LessOrEqual call" << endl;
    logicFunction(this, _left, _right, "setle");
}

void GreaterOrEqual::generate()
{
    cout << "# GreaterOrEqual call" << endl;
    logicFunction(this, _left, _right, "setge");
}

void Equal::generate()
{
    cout << "# Equal call" << endl;
    logicFunction(this, _left, _right, "sete");
}

void NotEqual::generate()
{
    cout << "# Not equal call" << endl;
    logicFunction(this, _left, _right, "setne");
}

//----- Actual logic functions ------
void LogicalAnd::generate()
{
    cout << "# AND call" << endl;

    //release(); //TODO: Should I call this?
    Label eitherFalse, exit;

    _left->generate();
    _right->generate();

    //Is left != 0 jump to True
    load(_left, eax);
    cout << "\tcmp" << suffix(_left) << "$1, " << _left << endl;
    cout << "\tjne\t" << eitherFalse << endl;

    //Is right != jump to true
    load(_right, eax);
    cout << "\tcmp" << suffix(_right) << "$1, " << _right << endl;
    cout << "\tjne\t" << eitherFalse << endl;

    //If code still gets here, set to false
    cout << "\tmovl\t$1, " << eax << endl;
    cout << "\tjmp\t" << exit << endl;

    cout << eitherFalse << ":" << endl;
    cout << "\tmovl\t$0, " << eax << endl;

    cout << exit << ":" << endl;

    assign(nullptr, _right->_register);
    assign(this, eax);
}

//TODO: Test since this uses multiple in a row
void LogicalOr::generate()
{
    cout << "# OR call" << endl;

    //release(); //TODO: Should I call this?
    Label eitherTrue, exit;

    _left->generate();
    _right->generate();

    //Is left != 0 jump to True
    load(_left, eax);
    cout << "\tcmp" << suffix(_left) << "$0, " << _left << endl;
    cout << "\tjne\t" << eitherTrue << endl;

    //Is right != jump to true
    load(_right, eax);
    cout << "\tcmp" << suffix(_right) << "$0, " << _right << endl;
    cout << "\tjne\t" << eitherTrue << endl;

    //If code still gets here, set to false
    cout << "\tmovl\t$0, " << eax << endl;
    cout << "\tjmp\t" << exit << endl;

    cout << eitherTrue << ":" << endl;
    cout << "\tmovl\t$1, " << eax << endl;

    cout << exit << ":" << endl;

    assign(nullptr, _right->_register);
    assign(this, eax);
}

//========================= Register Functions ======================

Register *getreg()
{
    for (unsigned i = 0; i < registers.size(); i ++)
        if (registers[i]->_node == nullptr)
            return registers[i];

    load(nullptr, registers[0]);
    return registers[0];
}

Register *fp_getreg()
{
    for (unsigned i = 0; i < fp_registers.size(); i ++)
        if (fp_registers[i]->_node == nullptr)
            return fp_registers[i];

    load(nullptr, fp_registers[0]);
    return fp_registers[0];
}

//Sets expression register to register and registers node to expression
void assign(Expression *expr, Register *reg)
{
    if (expr != nullptr) {
        if (expr->_register != nullptr)
            expr->_register->_node = nullptr;

        expr->_register = reg;
    }
    if (reg != nullptr) {
        if (reg->_node != nullptr)
            reg->_node->_register = nullptr;

        reg->_node = expr;
    }
}

void assigntemp(Expression *expr)
{
    stringstream ss;

    offset = offset - expr->type().size();
    ss << offset << "(%ebp)";
    expr->_operand = ss.str();
}

//Generates assembly to either assign put expr into reg or reg into expr
void load(Expression *expr, Register *reg)
{
    if (reg->_node != expr) {
    	//If register does belong to node gen assembly to reg into expr
        if (reg->_node != nullptr) {
            unsigned size = reg->_node->type().size();

            assigntemp(reg->_node);
            cout << "\tmov" << suffix(reg->_node);
            cout << reg->name(size) << ", ";
            cout << reg->_node->_operand << endl;
        }

		//If expression exists, gen assembly to put expr into reg
        if (expr != nullptr) {
            unsigned size = expr->type().size();
            cout << "\tmov" << suffix(expr) << expr;
            cout << ", " << reg->name(size) << endl;
        }

        assign(expr, reg);
    }
}

void release()
{
    for (unsigned i = 0; i < registers.size(); i ++)
    {
        assign(nullptr, registers[i]);
    }
    //TODO: Floating point version
}

void spill()
{
	for (unsigned i = 0; i < registers.size(); i ++)
    {
        load(nullptr, registers[i]);
    }
    //TODO: Floating point version
}

//========================= PHASE 5 FUNCTIONS =======================
/*
 * Function:	align (private)
 *
 * Description:	Return the number of bytes necessary to align the given
 *		offset on the stack.
 */

static int align(int offset)
{
    if (offset % STACK_ALIGNMENT == 0)
	return 0;

    return STACK_ALIGNMENT - (abs(offset) % STACK_ALIGNMENT);
}

//=================TODO: Implement
void Real::generate()
{
    cout << "# Real here" << endl;
    stringstream ss;
    Label *realLabel = new Label();

    //Set operand to just label name
    ss << *realLabel;
    _operand = ss.str();

    //Finish full label for data section and push to list
    ss << ":\t.double\t" << _value;
    realLabels.push_back(ss.str());
}

void String::generate()
{
    cout << "# String here" << endl;
}

/*
 * Function:	Identifier::generate
 *
 * Description:	Generate code for an identifier.  Since there is really no
 *		code to generate, we simply update our operand.
 */

void Identifier::generate()
{
    stringstream ss;

    if (_symbol->_offset != 0)
	ss << _symbol->_offset << "(%ebp)";
    else
	ss << global_prefix << _symbol->name();

    _operand = ss.str();
}


/*
 * Function:	Integer::generate
 *
 * Description:	Generate code for an integer.  Since there is really no
 *		code to generate, we simply update our operand.
 */

void Integer::generate()
{
    stringstream ss;


    ss << "$" << _value;
    _operand = ss.str();
}


/*
 * Function:	Call::generate
 *
 * Description:	Generate code for a function call expression.
 *
 *		NOT FINISHED: Only guaranteed to work if the argument is
 *		either an integer literal or an integer scalar variable.
 */

void Call::generate()
{
	cout << "# Call generate called!" << endl;
//	*retLabel = "." + _id->name() + ".exit:";

    unsigned bytesPushed = 0;


    /* Compute how many bytes will be pushed on the stack. */

    for (int i = _args.size() - 1; i >= 0; i --) {
	bytesPushed += _args[i]->type().size();

	if (STACK_ALIGNMENT != 4 && _args[i]->_hasCall)
	    _args[i]->generate();
    }


    /* Adjust the stack keep it aligned.  We do this by simply subtracting
       the necessary number of bytes from the stack pointer.  Effectively,
       we are pushing nonexistent arguments on the stack so that the total
       number of bytes pushed is a multiple of the alignment. */

    if (align(bytesPushed) > 0) {
	cout << "\tsubl\t$" << align(bytesPushed) << ", %esp" << endl;
	bytesPushed += align(bytesPushed);
    }


    /* Push each argument on the stack. */

    for (int i = _args.size() - 1; i >= 0; i --) {
	if (STACK_ALIGNMENT == 4 || !_args[i]->_hasCall)
	    _args[i]->generate();

	cout << "\tpushl\t" << _args[i] << endl;
    }


    /* Call the function and then adjust the stack pointer back. */
	release();
    cout << "\tcall\t" << global_prefix << _id->name() << endl;

    //TODO: Trying to store eax which was just set to expression register
//    load(this, eax);
    assign(this, eax);

    if (bytesPushed > 0)
	cout << "\taddl\t$" << bytesPushed << ", %esp" << endl;
}


/*
 * Function:	Assignment::generate
 *
 * Description:	Generate code for an assignment statement.
 *
 *		NOT FINISHED: Only guaranteed to work if the right-hand
 *		side is an integer literal and the left-hand side is an
 *		integer scalar.
 */

void Assignment::generate()
{
    _right->generate();


	if(_left->isDereference() != nullptr)
	{
		cout << "#Left is dereference" << endl;

		Expression * addr = _left->isDereference();
		addr->generate();

		if(addr->_register == nullptr)
        	load(addr, FP(_left) ? fp_getreg() : getreg());

        cout << "\tmov"<< suffix(_left) << _right << ", (" << addr << ")" << endl;
	}
	else
	{
		_left->generate();
		cout << "\tmov"<< suffix(_left) << _right << ", " << _left << endl;
	}
}


/*
 * Function:	Block::generate
 *
 * Description:	Generate code for this block, which simply means we
 *		generate code for each statement within the block.
 */

void Block::generate()
{
    for (unsigned i = 0; i < _stmts.size(); i ++)
    {
	       _stmts[i]->generate();
   }
}


/*
 * Function:	Function::generate
 *
 * Description:	Generate code for this function, which entails allocating
 *		space for local variables, then emitting our prologue, the
 *		body of the function, and the epilogue.
 *
 *		The stack must be aligned at the point at which a function
 *		begins execution.  Since the call instruction pushes the
 *		return address on the stack and each function is expected
 *		to push its base pointer, we adjust our offset by that
 *		amount and then perform the alignment.
 *
 *		On a 32-bit Intel platform, 8 bytes are pushed (4 for the
 *		return address and 4 for the base pointer).  Since Linux
 *		requires a 4-byte alignment, all we need to do is ensure
 *		the stack size is a multiple of 4, which will usually
 *		already be the case.  However, since OS X requires a
 *		16-byte alignment (thanks, Apple, for inventing your own
 *		standards), we will often see an extra amount of stack
 *		space allocated.
 *
 *		On a 64-bit Intel platform, 16 bytes are pushed (8 for the
 *		return address and 8 for the base pointer).  Both Linux and
 *		OS X require 16-byte alignment.
 */

void Function::generate()
{
	cout << "# Function generate called!" << endl;
    int param_offset, offset;

    retLabel = new Label();
    // cout << retLabel << endl;


    /* Generate our prologue. */

    param_offset = PARAM_OFFSET + SIZEOF_REG * callee_saved.size();
    offset = param_offset;
    allocate(offset);

    cout << global_prefix << _id->name() << ":" << endl;
    cout << "\tpushl\t%ebp" << endl;

    for (unsigned i = 0; i < callee_saved.size(); i ++)
	cout << "\tpushl\t" << callee_saved[i] << endl;

    cout << "\tmovl\t%esp, %ebp" << endl;

    if (SIMPLE_PROLOGUE) {
	offset -= align(offset - param_offset);
	cout << "\tsubl\t$" << -offset << ", %esp" << endl;
    } else
	cout << "\tsubl\t$" << _id->name() << ".size, %esp" << endl;


    /* Generate the body of this function. */

    _body->generate();


    //TODO: Output first epilogue label
    cout << *retLabel << ":" << endl;

    /* Generate our epilogue. */

    cout << "\tmovl\t%ebp, %esp" << endl;

    for (int i = callee_saved.size() - 1; i >= 0; i --)
	cout << "\tpopl\t" << callee_saved[i] << endl;

    cout << "\tpopl\t%ebp" << endl;
    cout << "\tret" << endl << endl;

    if (!SIMPLE_PROLOGUE) {
	offset -= align(offset - param_offset);
	cout << "\t.set\t" << _id->name() << ".size, " << -offset << endl;
    }

    cout << "\t.globl\t" << global_prefix << _id->name() << endl << endl;
}


/*
 * Function:	generateGlobals
 *
 * Description:	Generate code for any global variable declarations.
 */

void generateGlobals(Scope *scope)
{
    const Symbols &symbols = scope->symbols();

    for (unsigned i = 0; i < symbols.size(); i ++)
	if (!symbols[i]->type().isFunction()) {
	    cout << "\t.comm\t" << global_prefix << symbols[i]->name() << ", ";
	    cout << symbols[i]->type().size() << endl;
	}

    //TODO: Possibly take this out, adding data section
    cout << "\t.data" << endl;
    for(unsigned i = 0; i < realLabels.size(); i++)
    {
        cout << realLabels[i] << endl;
    }
}
