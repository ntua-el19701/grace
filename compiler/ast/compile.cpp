#include "ast.hpp"
#include <stack>

llvm::BasicBlock *activeBB;
std::stack <llvm::BasicBlock*> pattern;

string active_fun="emptyfun";

llvm::Function *function;


std::vector < llvm :: Type * > args; /// parameters to insert
std::vector < std::string > args_name; ///name of parameters in the function
std::vector < llvm:: Value * > params; /// parameters to call a function


std::vector <llvm:: Value*> vec_args;


std::string find_parents(std::string child){

    return parent[child];

}

bool is_assign=false;
bool is_integer=true;
int args_counter=0; ///number of parameters in the function

void printThat(){

std::cout<<endl;
std::cout<<"Int Size: "<<int_counter<<std::endl;
std::cout<<"Char Size: "<<char_counter<<std::endl;
std::cout<<endl;


   for(const auto& pair: vars){
    std::cout<<"Name: " << pair.first << " - Value: " << pair.second<<std::endl;
   }
   std::cout<<endl;

   for(const auto& pair: vartype){
    std::cout<<"Name: " << pair.first << " - Type: " << pair.second<<std::endl;
   }

    std::cout<<endl;

   for(const auto& pair: varref){
    std::cout<<"Name: " << pair.first << " - Ref: " << std::boolalpha << pair.second<<std::endl;
   }
    
    std::cout<<endl;

    for(const auto& pair: parent){
    std::cout<<"Name: " << pair.first << " - Parent: " << pair.second<<std::endl;
   }
}


Value * Func_def::compile (){
    header -> compile();
    if(local_def_gen != nullptr) local_def_gen->compile();


    block -> compile();

    if(header->getRetType()->getTypos() == 2){ Builder.CreateRetVoid(); }
    active_fun = find_parents(active_fun);
    activeBB = pattern.top();
    Builder.SetInsertPoint(activeBB);
    pattern.pop();
    return nullptr;
}

Value * Header::compile() {

   
    args.clear(); /// empty the vector
    args_name.clear();
    args_counter=0;

    pattern.push(activeBB);
    std::string name = nam.getName();
    active_fun=name;

    if(fpar_def != nullptr) fpar_def->compile();
    if(fpar_def_gen != nullptr) fpar_def_gen->compile();


    llvm::FunctionType *function_type ; 


    int fun_type = ret_type->getTypos();
    
    
    if(fun_type==0){ ///RETURN INT
          function_type= llvm::FunctionType::get(i32, args, false);
    }
    else
    if(fun_type==1){ ///RETURN CHAR
          function_type= llvm::FunctionType::get(i8, args, false);
    }
    else
    if(fun_type==2){ ///RETURN NOTHING
          function_type= llvm::FunctionType::get(Type::getVoidTy(TheContext), args, false);
    }
    else
          function_type= llvm::FunctionType::get(i32, args, false);

    std::string entry = active_fun+"-entry";
  
    llvm::Function *function =
    llvm::Function::Create(function_type, llvm::Function::ExternalLinkage,
                    active_fun, TheModule.get());
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, entry, function);  //define the first BB
    Builder.SetInsertPoint(BB);
    activeBB=BB;
    vec_args.clear();

    for(auto i=0;i<args_counter;i++){

        int var_pos = vars[args_name[i]];

        llvm::Value *Arg = function->getArg(i);

        vec_args.push_back(function->getArg(i));

    /*
        llvm::Value *lhs;
        llvm::Value *rhs;
       
    if(args[i]==i32){ ///INTEGER
      
        llvm::PointerType* pointerType = TheVarsInt->getType();
        lhs = Builder.CreateGEP(pointerType, TheVarsInt, c32(var_pos));
        rhs = Arg;//Builder.CreateLoad(Type::getInt32Ty(TheContext), function->getArg(i));
        Builder.CreateStore(rhs, lhs); 
    }
    else
    if(args[i]==i8){ ///CHAR
       
        llvm::PointerType* pointerType = TheVarsChar->getType();
        lhs = Builder.CreateGEP(pointerType, TheVarsChar, c32(var_pos));
        rhs = Arg;//Builder.CreateLoad(Type::getInt8Ty(TheContext), Arg);
        Builder.CreateStore(rhs, lhs); 
    }
        */
    }


    return nullptr;
}

Value * Local_def_gen::compile(){
    local_def->compile();
    if(local_def_gen!=nullptr) local_def_gen->compile();
    return nullptr;
}

Value * Block::compile(){
    for (Stmt *s : stmt_list) s->compile();

    return nullptr;
}

Value * Local_def::compile(){    
    if (func_def != nullptr)
        func_def->compile();
    else if(func_decl != nullptr){}
      //  func_decl->compile();
    else if(var_def != nullptr)
        var_def->compile();
    else{
        return nullptr;
    }
    return nullptr;
}

Value * Func_decl::compile(){
    header->compile();
    return nullptr;
}

Value * Var_def::compile(){
    /*id.compile();
    type->compile();
    if(comma_id_gen != nullptr) comma_id_gen ->compile();
    return nullptr; */
    return nullptr;
}

Value * MyType::compile(){
    if(type_gen != nullptr) type_gen -> compile();
    return nullptr;
}

Value * Comma_id_gen::compile(){

    if(is_integer)
    args.push_back(i32);

    else
    args.push_back(i8);

    args_counter++;
    std::string par_name = active_fun + "-" + name.getName();
    args_name.push_back(par_name);


    if(comma_id_gen != nullptr) comma_id_gen -> compile();
    return nullptr;
}

Value * Type_gen::compile(){
    std::cout<<"c32("<<size<<")"<<std::endl;
    if(type_gen != nullptr) type_gen->compile();
    return nullptr;
}

Value * Fpar_def::compile(){

   // llvm::Type* new_integer = Type::getInt32Ty(TheContext);


    std::string par_name = active_fun + "-" + name.getName();

   if(fpar_type->getType()==0){ ///Integer
    is_integer = true;
    args.push_back(i32);
    
   }

    if(fpar_type->getType()==1){ ///char
    is_integer = false;
    args.push_back(i8);
     }

    args_counter++;
    args_name.push_back(par_name);


    if(comma_id_gen != nullptr) comma_id_gen->compile();
    fpar_type->compile();
    return nullptr;
}

Value * Fpar_def_gen::compile(){
    fpar_def->compile();
    if(fpar_def_gen != nullptr) fpar_def_gen->compile();
    return nullptr;
}

Value * Fpar_type::compile(){
    if(type_gen != nullptr) type_gen->compile();
    return nullptr;
}

Value * L_value::compile(){
    if(flag == 1){ /// id
        
        //id.compile();
    if(is_assign){

    std::string name=id.getName();
    std::string var_name = active_fun + "-" + name;
    std::cout<<var_name<<std::endl; 
    

    int c=-1;

    for(auto i=0;i<args_counter;i++){

        if(var_name==args_name[i]){
            c=i;
            cout<<"Found:"<<c<<std::endl;
        }
    }


    int var_type = vartype[var_name];
    int var_pos = vars[var_name];

    std::cout<<name<<" Var type: "<<var_type<<" Var pos: "<<var_pos<<std::endl;

    if(c!=-1){   ///variable is argument


        llvm::Value *Arg = vec_args[c];
            
        llvm::Value* v;

        
        Value * array[] = {Arg};

    if(var_type==0){ ///INTEGER

       // llvm::PointerType* pointerType = Arg->getType();
        return Builder.CreateGEP(Arg->getType(),Arg,c32(0),  name);
       // return Arg;
    }

    }
    else{
    if(var_type==0){ ///INTEGER
        llvm::PointerType* pointerType = TheVarsInt->getType();
        return Builder.CreateGEP(pointerType, TheVarsInt, c32(var_pos), name);
       
    }
    else
    if(var_type==1){ ///CHAR
      
        llvm::PointerType* pointerType = TheVarsChar->getType();
        return  Builder.CreateGEP(pointerType, TheVarsChar, c32(var_pos), name);

    }
    return nullptr;
    }


    }
    else
    return id.compile();

        
    } // kati me id
        
    else if(flag == 2) //kati me const_String
        const_string.compile();
    else if (flag == 3){
        l_value->compile();
        expr->compile();
    } 
    return nullptr;
    
}

Value * Assign::compile(){
   is_assign=true;
   Value *lhs =  l_value->compile();
   is_assign = false;
   Value *rhs = expr->compile();
    std::cout<<"out";

   Builder.CreateStore(rhs, lhs); 

    return nullptr;
}

Value * Func_call_stmt::compile(){
    /*id.compile();
    if(expr!=nullptr) expr->compile();
    if(comma_expr_gen != nullptr) comma_expr_gen->compile();
    return nullptr;*/
    
    Value *v;
    params.clear();

    if(expr!=nullptr) {
        
        v = expr->compile();
        
        params.push_back(v);
    }
    if(comma_expr_gen != nullptr) comma_expr_gen->compile();
    return Builder.CreateCall(TheModule->getFunction(id.getName()),params);
   
}

Value * Comma_expr_gen::compile(){
    Value* v = expr->compile();
        
    params.push_back(v);
    if(comma_expr_gen != nullptr) comma_expr_gen->compile();
    return nullptr;
}

Value * If::compile(){
    /*condition->compile();
    if(stmt1!=nullptr)
        stmt1->compile();
    if (stmt2 != nullptr) { stmt2->compile(); }
    return nullptr;*/
    llvm::Value *condValue = condition->compile();
    llvm::Value *cond = Builder.CreateICmpNE(condValue, c1(false), "if_cond");
    //llvm::Value *thenValue = nullptr;
  //  llvm::Value *elseValue = nullptr;
    
    llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *ThenBB = llvm::BasicBlock::Create(TheContext, "then", TheFunction);
    llvm::BasicBlock *ElseBB = llvm::BasicBlock::Create(TheContext, "else", TheFunction);
    llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(TheContext, "endif", TheFunction);

    /* conditional branch, set insert point and save thenValue */
    Builder.CreateCondBr(cond, ThenBB, ElseBB);
    
    Builder.SetInsertPoint(ThenBB);
    if(stmt1 != nullptr)
    stmt1->compile();
    ThenBB = Builder.GetInsertBlock();
    Builder.CreateBr(AfterBB);
    Builder.SetInsertPoint(ElseBB);
    if(stmt2 != nullptr) stmt2->compile();
    Builder.CreateBr(AfterBB);
    Builder.SetInsertPoint(AfterBB);


    return nullptr;
  
}


Value * Cond::compile(){
   Value * lv = cond1->compile();
   Value * rv = nullptr;
   if(cond2 != nullptr) rv= cond2->compile();
   
   if(*op == '|') return Builder.CreateOr(lv, rv);
   else if(*op == '&') return Builder.CreateAnd(lv, rv);
   else if(*op == '!') return Builder.CreateNot(lv);
   return nullptr;
}

Value * While::compile(){
    

    llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();

    llvm::BasicBlock *LoopBB = llvm::BasicBlock::Create(TheContext, "loop", TheFunction);
    llvm::BasicBlock *BodyBB = llvm::BasicBlock::Create(TheContext, "body", TheFunction);
    llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(TheContext, "endwhile", TheFunction);
    Builder.CreateBr(LoopBB);
    Builder.SetInsertPoint(LoopBB);
    llvm::Value *condValue = condition->compile();
    llvm::Value *cond = Builder.CreateICmpNE(condValue, c1(false), "while_cond");
    Builder.CreateCondBr(cond, BodyBB, AfterBB);
    
    Builder.SetInsertPoint(BodyBB);
    stmt->compile();
    
    Builder.CreateBr(LoopBB);
 
    Builder.SetInsertPoint(AfterBB);
    
    return nullptr;
}

Value * Return::compile(){
    Value *r = nullptr; 
    if(expr!=nullptr) r=expr->compile();
    Builder.CreateRet(r); 
    return nullptr;
    
}

Value * Func_call_expr::compile(){
    
    Value *v;
    params.clear();

    if(expr!=nullptr) {
        
        v = expr->compile();
        
        params.push_back(v);
    }
    if(comma_expr_gen != nullptr) comma_expr_gen->compile();
    return Builder.CreateCall(TheModule->getFunction(id.getName()),params);

}

Value * BinOp::compile(){
    
    Value *l = expr1->compile();
    Value *r = expr2->compile();


    if(*op == '+')       return Builder.CreateAdd(l, r, "addtmp");
    else if(*op == '-')  return Builder.CreateSub(l, r, "subtmp");
    else if(*op == '*')  return Builder.CreateMul(l, r, "multmp");
    else if(*op == '/')  return Builder.CreateSDiv(l, r, "divtmp");
    else if(*op == '%')  return Builder.CreateSRem(l, r, "modtmp");
    
    return nullptr;
}

Value * UnOp::compile(){
    
    Value *v = expr->compile();
    if (op == '+') return v;
    else if(op == '-') return Builder.CreateMul(v, c32(-1));
    return nullptr;
}

Value * Compare::compile(){
    Value *lv = expr1->compile();
    Value *rv = expr2->compile();

    if(*op == '=') return Builder.CreateICmp(llvm::CmpInst::ICMP_EQ, lv, rv);
    
    else if (*op == '#')  return Builder.CreateICmp(CmpInst::ICMP_NE, lv, rv);

    else if (*op == '>')  return Builder.CreateICmp(CmpInst::ICMP_SGT, lv, rv);

    else if (*op == '<')  return Builder.CreateICmp(CmpInst::ICMP_SLT, lv, rv);

    else if (*op == 'g')  return Builder.CreateICmp(CmpInst::ICMP_SGE, lv, rv);

    else if (*op == 'l')  return Builder.CreateICmp(CmpInst::ICMP_SLE, lv, rv);

    return nullptr; // will never be reached
}

Value * IntConst::compile(){
    return c32(num);
}

Value * Id::compile(){
    
    std::string var_name = active_fun + "-" + name;
    std::cout<<var_name<<std::endl; 

    int c=-1;

    for(auto i=0;i<args_counter;i++){

        if(var_name==args_name[i]){
            c=i;
            cout<<"Found:"<<c<<std::endl;
        }
    }

   // char onoma[] = { name, '_', 'p', 't', 'r', '\0' };
    
   // std::cout<<"heree";
    int var_type = vartype[var_name];

    int var_pos = vars[var_name];

   // printThat();
   
   if(c!=-1){   ///variable is argument


        llvm::Value *Arg = vec_args[c];
            
        llvm::Value* v;
    if(var_type==0){ ///INTEGER
      
       // llvm::PointerType* pointerType = TheVarsInt->getType();
      //  v = Builder.CreateGEP(pointerType, Arg, c32(0), name);
        
        return Arg; 
       //return  Builder.CreateLoad(Type::getInt32Ty(TheContext), v, name);
       // llvm::PointerType* pointerType = TheVarsInt->getType();
       // lhs = Builder.CreateGEP(pointerType, TheVarsInt, c32(var_pos));
       // rhs = Arg;//Builder.CreateLoad(Type::getInt32Ty(TheContext), function->getArg(i));
       // Builder.CreateStore(rhs, lhs); 
    }
    else
    if(var_type==1){ ///CHAR
       return Arg;
       //return Builder.CreateLoad(Type::getInt8Ty(TheContext), Arg, var_name);
       // llvm::PointerType* pointerType = TheVarsChar->getType();
       // lhs = Builder.CreateGEP(pointerType, TheVarsChar, c32(var_pos));
       // rhs = Arg;//Builder.CreateLoad(Type::getInt8Ty(TheContext), Arg);
       // Builder.CreateStore(rhs, lhs); 
    }
    else
    return nullptr;



   }
    else{  ///variable is not argument
    llvm::Value* v;
    std::cout<<name<<" Var type: "<<var_type<<" Var pos: "<<var_pos<<std::endl;
    if(var_type==0){ ///INTEGER
        llvm::PointerType* pointerType = TheVarsInt->getType();
        v = Builder.CreateGEP(pointerType, TheVarsInt, c32(var_pos), name);
        return Builder.CreateLoad(Type::getInt32Ty(TheContext), v, name);
    }
    else
    if(var_type==1){ ///CHAR
      
        llvm::PointerType* pointerType = TheVarsChar->getType();
        v = Builder.CreateGEP(pointerType, TheVarsChar, c32(var_pos), name);
        return Builder.CreateLoad(Type::getInt8Ty(TheContext), v, name);

    }
    return nullptr;
    }
   // onoma[1] = '\0';
    return nullptr;
   // return Builder.CreateLoad(v, name);
    
}

Value * StringConst::compile(){
    return nullptr;
}

Value * Const_char::compile() {
    
    return c8(*str);
}

