#include "ast.hpp"
#include <stack>

llvm::BasicBlock *activeBB;
std::stack <llvm::BasicBlock*> pattern;

stack < bool > has_return;
stack < bool > after_created;


string active_fun="emptyfun";

llvm::Function *activefunction;

Typos keepheadertype;


std::vector < llvm :: Type * > args; /// parameters to insert (reference + kanoniko)
std::vector < std::string > args_name; ///name of parameters in the function
std::vector < llvm:: Value * > params; /// parameters to call a function

std::map < std::string , std::vector < bool > > func_ref;


std::vector <bool> args_ref; // true: argument is reference , false: argument not reference


std::string find_parents(std::string child){

    return parent[child];

}

std::string header_name;

bool is_assign=false;
bool is_integer=true;
bool from_func_call=false;
bool from_func_decl=false;

bool return_found = false; ///for if then else


int position=0;
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

    keepheadertype=header->getRetType()->getTypos();

    block -> compile();

    if(header->getRetType()->getTypos() == 2){ Builder.CreateRetVoid(); }
    /*
    else
    if(activeBB->empty()==true){
        
        if(header->getRetType()->getTypos() == 0){ Builder.CreateRet(c32(0)); }
        if(header->getRetType()->getTypos() == 1){ Builder.CreateRet(c8('A')); }
        if(header->getRetType()->getTypos() == 2){ Builder.CreateRetVoid(); }
        
        
    }
    */

    active_fun = find_parents(active_fun);
    activeBB = pattern.top();
    Builder.SetInsertPoint(activeBB);
    pattern.pop();
    return nullptr;
}

Value * Header::compile() {

   
    args.clear(); /// empty the vector
    args_name.clear();
    args_ref.clear();
    args_counter=0;

    if(from_func_decl==false){

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
    
    activefunction=function;

    func_ref[name]=args_ref;

    for(auto i=0;i<args_counter;i++){

        int var_pos = vars[args_name[i]];

    }

    }
    else{
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

     func_ref[name]=args_ref;

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
    else if(func_decl != nullptr)
        func_decl->compile();
    else if(var_def != nullptr)
        var_def->compile();
    else{
        return nullptr;
    }
    return nullptr;
}

Value * Func_decl::compile(){
    
    from_func_decl=true;
    header->compile();
    from_func_decl=false;

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

    std::string par_name = active_fun + "-" + name.getName();

    if(is_integer){

        if(varref[par_name]==true){
        args.push_back(Builder.getInt32Ty()->getPointerTo());  //if reference
        args_ref.push_back(true);
    }
    else{
    args.push_back(i32);
    args_ref.push_back(false);

    }
    }
    

    else{

        if(varref[par_name]==true){
        args.push_back(Builder.getInt8Ty()->getPointerTo());  //if reference
        args_ref.push_back(true);
    }
    else{
    args.push_back(i8);
    args_ref.push_back(false);
    }


    }
    

    args_counter++;

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

    if(varref[par_name]==true){
        args.push_back(Builder.getInt32Ty()->getPointerTo());  //if reference
        args_ref.push_back(true);
    }
    else{
   //args.push_back(Builder.getInt32Ty()->getPointerTo()); if reference
    args.push_back(i32);
    args_ref.push_back(false);
    }
    
   }

    if(fpar_type->getType()==1){ ///char
    is_integer = false;

    if(varref[par_name]==true){
        args.push_back(Builder.getInt8Ty()->getPointerTo());  //if reference
        args_ref.push_back(true);
    }
    else{
    args.push_back(i8);
    args_ref.push_back(false);
    }
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
           
        }
    }


    int var_type = vartype[var_name];
    int var_pos = vars[var_name];

    std::cout<<name<<" Var type: "<<var_type<<" Var pos: "<<var_pos<<std::endl;

    if(c!=-1){   ///variable is argument


       bool ref = args_ref[c];
            
        llvm::Value* v;

    
    if(var_type==0){ ///INTEGER
        llvm::PointerType* pointerType = activefunction->getType();
        return Builder.CreateGEP(pointerType, activefunction, c32(c), name);
    }
    else{
        if(var_type==1){ ///CHAR
        llvm::PointerType* pointerType = activefunction->getType();
        return Builder.CreateGEP(pointerType, activefunction, c32(c), name);
    }

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
    else{
       
    return id.compile();
    }
        
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

   Builder.CreateStore(rhs, lhs); 

    return nullptr;
}

Value * Func_call_stmt::compile(){
   
    Value *v;
    params.clear();

    header_name = id.getName();
    position=0;

    if(expr!=nullptr) {
        
        if(func_ref[header_name][position]==false)
        v = expr->compile();
        
        else{
            std::cout<<"REFERENCE";
            from_func_call=true;
              v = expr->compile();
              from_func_call=false;
        }
        position++;
        params.push_back(v);
    }
    if(comma_expr_gen != nullptr) comma_expr_gen->compile();
    return Builder.CreateCall(TheModule->getFunction(id.getName()),params);
   
}

Value * Comma_expr_gen::compile(){
   
   Value * v;
    
        
        if(func_ref[header_name][position]==false)
        v = expr->compile();
        
        else{
            std::cout<<"REFERENCE";
            from_func_call=true;
              v = expr->compile();
              from_func_call=false;
        }

    position++;
      
    
        
    params.push_back(v);
    if(comma_expr_gen != nullptr) comma_expr_gen->compile();
    return nullptr;
}

Value * If::compile(){
    
    llvm::Value *condValue = condition->compile();
    llvm::Value *cond = Builder.CreateICmpNE(condValue, c1(false), "if_cond");
   
    
    llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *ThenBB = llvm::BasicBlock::Create(TheContext, "then", TheFunction);
    llvm::BasicBlock *ElseBB = llvm::BasicBlock::Create(TheContext, "else", TheFunction);
    llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(TheContext, "endif", TheFunction);

    /* conditional branch, set insert point and save thenValue */
    Builder.CreateCondBr(cond, ThenBB, ElseBB);
    
    Builder.SetInsertPoint(ThenBB);
    
    has_return.push(false);
    after_created.push(false);

    if(stmt1 != nullptr)
    stmt1->compile();
    ThenBB = Builder.GetInsertBlock();

    if(has_return.top()==false){
    Builder.CreateBr(AfterBB);
    after_created.pop();
    after_created.push(true);
    has_return.pop();
    }

    has_return.push(false);
    Builder.SetInsertPoint(ElseBB);
    if(stmt2 != nullptr) stmt2->compile();

    if(has_return.top()==false){
   
    Builder.CreateBr(AfterBB);
    after_created.pop();
    after_created.push(true);
    has_return.pop();
    }

    Builder.SetInsertPoint(AfterBB);

    if(after_created.top()==false){
       
        if(keepheadertype == 0){ Builder.CreateRet(c32(0)); }
        if(keepheadertype == 1){ Builder.CreateRet(c8('A')); }
        if(keepheadertype == 2){ Builder.CreateRetVoid(); }
        
        

    }   

    after_created.pop();
 

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
    
    if(has_return.empty()==false){
        has_return.pop();
        has_return.push(true);
    }
    return nullptr;
    
}

Value * Func_call_expr::compile(){
    
    Value *v;
    params.clear();
 
    header_name = id.getName();
    position=0;

    std::cout<<"header name is"<<header_name<<std::endl;
    for(int i=0;i<func_ref[header_name].size();i++){
        std::cout<<func_ref[header_name][i]<<" ";
    }
    std::cout<<endl;


    if(expr!=nullptr) {
        
        if(func_ref[header_name][position]==false)
        v = expr->compile();
        
        else{
            std::cout<<"REFERENCE";
            from_func_call=true;
              v = expr->compile();
              from_func_call=false;
        }
        position++;
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

    if(from_func_call){
        
        int c=-1;

        for(auto i=0;i<args_counter;i++){

            if(var_name==args_name[i]){
                c=i;
                std::cout<<"FOUND";
           
            }
        }

        int var_type = vartype[var_name];

        int var_pos = vars[var_name];

        if(c!=-1){    ///variable is argument
            
        bool ref = args_ref[c];  ///karterw deikti  // exw ref = true ara deikti alliws value
        llvm::Value* v ; 
    if(var_type==0){ ///INTEGER
       
        if(ref){
              return activefunction->getArg(c);
        }
        else{

            llvm::PointerType* pointerType = activefunction->getType();
            return Builder.CreateGEP(pointerType, activefunction, c32(c), name);

        }

          
       
    }
    else
    if(var_type==1){ ///CHAR

       if(ref){
           return activefunction->getArg(c);
        }
        else
        {
            llvm::PointerType* pointerType = activefunction->getType();
            return Builder.CreateGEP(pointerType, activefunction, c8(c), name);
        }
      
   
    }
    else
    return nullptr;

   }
   else{                ///variable is not argument
    llvm::Value* v;
    std::cout<<name<<" Var type: "<<var_type<<" Var pos: "<<var_pos<<std::endl;
    if(var_type==0){ ///INTEGER
        llvm::PointerType* pointerType = TheVarsInt->getType();
        return Builder.CreateGEP(pointerType, TheVarsInt, c32(var_pos), name);
        //return Builder.CreateLoad(Type::getInt32Ty(TheContext), v, name);
    }
    else
    if(var_type==1){ ///CHAR
      
        llvm::PointerType* pointerType = TheVarsChar->getType();
        return Builder.CreateGEP(pointerType, TheVarsChar, c32(var_pos), name);
       // return Builder.CreateLoad(Type::getInt8Ty(TheContext), v, name);

    }
    return nullptr;
    }



    }

    else{   /// EPISTREFW TIMI

    int c=-1;

    for(auto i=0;i<args_counter;i++){

        if(var_name==args_name[i]){
            c=i;
           
        }
    }

  
    int var_type = vartype[var_name];

    int var_pos = vars[var_name];

   // printThat();
   
   if(c!=-1){   ///variable is argument
      
        bool ref = args_ref[c];
     
            
        llvm::Value* v ; 
    if(var_type==0){ ///INTEGER
       
        if(ref){
            v=activefunction->getArg(c);
            return  Builder.CreateLoad(Type::getInt32Ty(TheContext), v, name);
        }
        else

        return activefunction->getArg(c);
       
    }
    else
    if(var_type==1){ ///CHAR

        if(ref){
            v=activefunction->getArg(c);
            return  Builder.CreateLoad(Type::getInt8Ty(TheContext), v, name);
        }
        else
       
       return activefunction->getArg(c);
   
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
 
    return nullptr;
   
    }
}

Value * StringConst::compile(){
    return nullptr;
}

Value * Const_char::compile() {
    
    return c8(str[1]);
}

