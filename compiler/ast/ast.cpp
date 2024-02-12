#include "ast.hpp"

LLVMContext AST::TheContext;
IRBuilder<> AST::Builder(TheContext);
std::unique_ptr<Module> AST::TheModule;
std::unique_ptr<legacy::FunctionPassManager> AST::TheFPM;


GlobalVariable *AST::TheNL;
GlobalVariable *AST::TheVarsInt;
GlobalVariable *AST::TheVarsChar;
GlobalVariable *AST::TheVarsIntArray; //for Varaibles Int Arrays
GlobalVariable *AST::TheVarsCharArray; //for Variables Char Arrays
Function *AST::TheWriteInteger;
Function *AST::TheWriteString;
Function *AST::TheWriteChar;
Function *AST::TheReadInteger;
Function *AST::TheReadString;
Function *AST::TheReadChar;
Function *AST::TheAscii;
Function *AST::TheChr;
Function *AST::TheStrlen;
Function *AST::TheStrCompare;
Function *AST::TheStrCopy;
Function *AST::TheStrCat;


Type *AST::i8;
Type *AST::i32;
Type *AST::i64;