#ifndef __AST_CLASS_HPP__
#define __AST_CLASS_HPP__

#include <iostream>
#include <fstream>
#include <stack>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Utils.h>


using namespace llvm;
extern int int_counter;
extern int char_counter; 
extern int array_int_counter;
extern int array_char_counter;
extern int array_int_size;
extern int array_char_size;

extern std::map < std::string , int > maparrayint;
extern std::map < std::string , int > maparraychar;

extern std::stack <llvm::BasicBlock*> pattern;
extern llvm::BasicBlock *activeBB;

class AST {
public:
  virtual void printAST(std::ostream &out) const = 0;
  virtual void sem() {}
  virtual Value* compile() {return nullptr;}
  virtual void preCompile() {}
  
//virtual std::set<std::string> preCompile() { return {}; }

   void llvm_compile_and_dump(bool optimize=true) {
    // Initialize
    TheModule = std::make_unique<Module>("Grace program", TheContext);
    TheFPM = std::make_unique<legacy::FunctionPassManager>(TheModule.get());

    if (optimize) {
      TheFPM->add(createPromoteMemoryToRegisterPass());
      TheFPM->add(createInstructionCombiningPass());
      TheFPM->add(createReassociatePass());
      TheFPM->add(createGVNPass());
      TheFPM->add(createCFGSimplificationPass());
    }
    TheFPM->doInitialization(); 
    // Initialize types
    i8 = IntegerType::get(TheContext, 8);
    i32 = IntegerType::get(TheContext, 32);
    i64 = IntegerType::get(TheContext, 64);


  // Initialize global variables Array Int
  llvm::ArrayType *vars_type_int = ArrayType::get(i32, int_counter+5);
    TheVarsInt = new GlobalVariable(
      *TheModule, vars_type_int, false, GlobalValue::PrivateLinkage,
      ConstantAggregateZero::get(vars_type_int), "vars_int");
    TheVarsInt->setAlignment(llvm::MaybeAlign(16));


   // Initialize global variables Array Char
    llvm::ArrayType *vars_type_char = ArrayType::get(i8, char_counter+5);
    TheVarsChar = new GlobalVariable(
      *TheModule, vars_type_char, false, GlobalValue::PrivateLinkage,
      ConstantAggregateZero::get(vars_type_char), "vars_char");
    TheVarsChar->setAlignment(llvm::MaybeAlign(16));


    //Create Array-Integers
    std::cout<<array_int_size<<std::endl;

    
      llvm::ArrayType *vars_type_array_int = ArrayType::get(i32, array_int_size+5 );
    TheVarsIntArray = new GlobalVariable(
      *TheModule, vars_type_array_int, false, GlobalValue::PrivateLinkage,
      ConstantAggregateZero::get(vars_type_array_int), "Array_Int_vars");
    TheVarsIntArray->setAlignment(llvm::MaybeAlign(16));
    
    
    int counter=0;
    std::string name="main-array";
    for(const auto& pair: maparrayint){
    std::cout<<"Array Int Name: " << pair.first << " - Begin Pos "<< counter<<" - Size: " << pair.second<<std::endl;
 
    //if(pair.first==name){
    //  std::cout<<counter<<" "<<pair.second<<std::endl;
    //}

       counter+=pair.second;
    }
    
    //Create Array-Chars
      llvm::ArrayType *vars_type_array_char = ArrayType::get(i8, array_char_size+5);
    TheVarsCharArray = new GlobalVariable(
      *TheModule, vars_type_array_char, false, GlobalValue::PrivateLinkage,
      ConstantAggregateZero::get(vars_type_array_char), "Array_Char_vars");
    TheVarsCharArray->setAlignment(llvm::MaybeAlign(16));


    // Initialize global variables (new line)
    llvm::ArrayType *nl_type = llvm::ArrayType::get(i8, 2);
    TheNL = new llvm::GlobalVariable(
    *TheModule, nl_type, true, llvm::GlobalValue::PrivateLinkage,
    llvm::ConstantArray::get(nl_type, {c8('\n'), c8('\0')}), "nl");
    TheNL->setAlignment(llvm::MaybeAlign(1));

    // Initialize library functions
    /* writeInteger - lib.a */
    llvm::FunctionType *writeInteger_type =
    llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), { i32 }, false); //32 or 64?
    TheWriteInteger =
    llvm::Function::Create(writeInteger_type, llvm::Function::ExternalLinkage,
                    "writeInteger", TheModule.get());

    /* writeString - lib.a */
    llvm::FunctionType *writeString_type =
    llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext),
                        { llvm::PointerType::get(i8, 0) }, false);
    TheWriteString =
    llvm::Function::Create(writeString_type, llvm::Function::ExternalLinkage,
                    "writeString", TheModule.get());

    // Define and start the main function.      
    llvm::FunctionType *main_type = llvm::FunctionType::get(i32, {}, false);
    //llvm::FunctionType *main_type = llvm::FunctionType::get(Type::getVoidTy(TheContext), {}, false);
    llvm::Function *main =
    llvm::Function::Create(main_type, llvm::Function::ExternalLinkage,
                    "main", TheModule.get());
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", main);  //define the first BB
    Builder.SetInsertPoint(BB);
    activeBB=BB;

    
    
     // Emit the program code.
    compile();
    
    Builder.CreateRet(c32(0));

     // Verify the IR. 
    bool bad = verifyModule(*TheModule, &llvm::errs());  
    if (bad) {
        std::cerr << "The IR is bad!" << std::endl;
        TheModule->print(llvm::errs(), nullptr);
        std::exit(1);
    }

    // Optimize!
   // TheFPM->run(*main);

    // Print out the IR.
    TheModule->print(llvm::outs(), nullptr);

}
public:
  Typos type;

protected:
  static LLVMContext TheContext;
  static IRBuilder<> Builder;
  static std::unique_ptr<Module> TheModule;
  static std::unique_ptr<legacy::FunctionPassManager> TheFPM;


  static GlobalVariable *TheNL; //for new line
  static GlobalVariable *TheVarsInt; //for Variables Integers
  static GlobalVariable *TheVarsIntArray; //for Varaibles Int Arrays
  static GlobalVariable *TheVarsChar; //for Variables Char
  static GlobalVariable *TheVarsCharArray; //for Variables Char Arrays

  static Function *TheWriteInteger;
  static Function *TheWriteString;

  static Type *i8;
  static Type *i32;
  static Type *i64;




  static ConstantInt* c1(int c) {
        return llvm::ConstantInt::get(TheContext, llvm::APInt(1, c, true));
    }
  static ConstantInt* c8(char c) {
    return ConstantInt::get(TheContext, APInt(8, c, true));
  }
  static ConstantInt* c32(int n) {
    return ConstantInt::get(TheContext, APInt(32, n, true));
  }
};



#endif