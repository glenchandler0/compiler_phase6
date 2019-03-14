/*
 * File:	generator.h
 *
 * Description:	This file contains the function declarations for the code
 *		generator for Simple C.  Most of the function declarations
 *		are actually member functions provided as part of Tree.h.
 */

# ifndef GENERATOR_H
# define GENERATOR_H
// # include "Scope.h"
// # include "machine.h"
# include "Tree.h"
// # include "generator2.h"

void generateGlobals(Scope *scope);

//For Registers
# define FP(expr) ((expr)->type().isReal())
# define BYTE(expr) ((expr)->type().size() == 1)

static std::string suffix(Expression *expr) { return FP(expr) ? "sd\t" : (BYTE(expr) ? "b\t" : "l\t"); }

Register *getreg();

Register *fp_getreg();

void assign(Expression *expr, Register *reg);

void assigntemp(Expression *expr);

void load(Expression *expr, Register *reg);


# endif /* GENERATOR_H */
