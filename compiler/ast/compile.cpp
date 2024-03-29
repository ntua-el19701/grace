#include "ast.hpp"
#include <stack>

llvm::BasicBlock *activeBB;
std::stack <llvm::BasicBlock*> pattern;

stack < bool > has_return;
stack < bool > after_created;

bool main_called=false;
bool skip_assign=false;

std::string word;
int word_size;
bool zero_found=false;

Value * son;
int update_param;
bool need_update=false;

Value * from_expr;
bool from_expression=false;

string active_fun="emptyfun";

llvm::Function *activefunction;

Typos keepheadertype;     



Value* arrayAllocationInt = nullptr;
Value* arrayAllocationChar = nullptr;
Value* arrayAllocationArray = nullptr;
Value* arrayAllocationArraySizes = nullptr;

std::map < std::string , Value * > arrayAllocationArraymap;
std::map < std::string , Value * > arrayAllocationArraySizesmap;
std::map < std::string , Value * > arrayAllocationCharmap;
std::map < std::string , Value * > arrayAllocationIntmap;

std::map < std::string , Value * > array_ending;

int int_references_counter=0;
int char_references_counter=0;
int array_references_counter=0;

std::vector < llvm :: Type * > args; /// parameters to insert (reference + kanoniko)
std::vector < std::string > args_name; ///name of parameters in the function
std::vector < bool > args_array; ///name of parameters in the function
std::vector < llvm:: Value * > params; /// parameters to call a function

std::vector < int > array_sizes;

std::stack < vector < int > > keep_array_sizes;

std::map < std::string , int > array_is_ref;
std::stack < vector < std::string > > active_arguments_names;


std::map < std::string , std::vector < bool > > func_ref;
std::map < std::string , std::vector < bool > > array_ref;

std::map < std::string , llvm::Function *> declared_function; 

std::map < std::string , stack < llvm:: Value * > > keep_variables_values;

std::map < std::string , int > reference_position;

std::map < std::string , stack < llvm:: Value * > > keep_references_pointers;

std::vector <bool> args_ref; // true: argument is reference , false: argument not reference

std::map < std::string , int > this_is_ref;

std::map <std::string , int > word_length;

std::string find_parents(std::string child){

    return parent[child];

}

pair < int,int > find_array(std::string name,bool is_int){

    int counter=0;
    

    if(is_int){
    for(const auto& pair: maparrayint){
    //std::cout<<"Array Int Name: " << pair.first << " - Begin Pos "<< counter<<" - Size: " << pair.second<<std::endl;
 
    if(pair.first==name){
      return make_pair(counter+int_counter+1,pair.second+int_counter+1);
    }

       counter+=pair.second;
    }

    counter=0;
    }
    else
    for(const auto& pair: maparraychar){
    //std::cout<<"Array Int Name: " << pair.first << " - Begin Pos "<< counter<<" - Size: " << pair.second<<std::endl;
 
    if(pair.first==name){
      return make_pair(counter+char_counter+1,pair.second+char_counter+1);
    }

       counter+=pair.second;
    }


    return make_pair(-1,-1);


}

std::string header_name;

bool is_assign=false;
bool is_integer=true;
bool array_variable=false;
bool from_func_call=false;
bool from_func_decl=false;



int size_array=-1;

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
    arrayAllocationArray=arrayAllocationArraymap[active_fun];
    arrayAllocationChar=arrayAllocationCharmap[active_fun];
    arrayAllocationArraySizes=arrayAllocationArraySizesmap[active_fun];
    arrayAllocationInt=arrayAllocationIntmap[active_fun];
    activeBB = pattern.top();
    Builder.SetInsertPoint(activeBB);
    pattern.pop();
    return nullptr;
}

Value * Header::compile() { 

   
    args.clear(); /// empty the vector
    args_name.clear();
    args_ref.clear();
    args_array.clear();
    args_counter=0;

    if(from_func_decl==false){

    pattern.push(activeBB);
    std::string name = nam.getName();
    active_fun=name;

    int_references_counter=0;
    char_references_counter=0;
    array_references_counter=0;


    if(active_fun=="main"){
        active_fun="main.1";
    }

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
  
     llvm::BasicBlock *BB;
      llvm::Function *function;
    if(declared_function[active_fun]!=0){
        
        function= declared_function[active_fun];
        BB = llvm::BasicBlock::Create(TheContext, entry, function);  //define the first BB

    }
    else{
   function =
    llvm::Function::Create(function_type, llvm::Function::ExternalLinkage,
                    active_fun, TheModule.get());
    BB = llvm::BasicBlock::Create(TheContext, entry, function);  //define the first BB
    }

    ///CALL THE FIRST FUNCTION
    vector< Value*> empty_vec;
    empty_vec.clear();
    if(main_called==false){
        Builder.CreateCall(TheModule->getFunction(active_fun),empty_vec);
        main_called=true;
        if(active_fun=="main.1")
        active_fun="main";
    }
    
    Builder.SetInsertPoint(BB);
    activeBB=BB;

    activefunction=function;

    func_ref[name]=args_ref;
    array_ref[name]=args_array;

  
   
    Type * intPointerType = Type::getInt32PtrTy(TheContext);
    Type * charPointerType = Type::getInt8PtrTy(TheContext);    
    Type * intType = Type::getInt32Ty(TheContext);
    std::map < std::string , llvm::Value * > ref_params; 
    ref_params.clear();
    if(int_references_counter != 0){
        
        arrayAllocationInt = Builder.CreateAlloca(ArrayType::get(intPointerType, int_references_counter), nullptr,"ArrayIntPointers");
        arrayAllocationIntmap[active_fun]=arrayAllocationInt;
    }
    if(char_references_counter!=0){
       
        arrayAllocationChar = Builder.CreateAlloca(ArrayType::get(charPointerType, char_references_counter), nullptr,"ArrayCharPointers");
        arrayAllocationCharmap[active_fun]=arrayAllocationChar;
    }
    if(array_references_counter!=0){
       
        arrayAllocationArray = Builder.CreateAlloca(ArrayType::get(intType, array_references_counter), nullptr,"ArrayPointers");
        arrayAllocationArraymap[active_fun]=arrayAllocationArray;

        arrayAllocationArraySizes = Builder.CreateAlloca(ArrayType::get(intType, array_references_counter), nullptr,"ArrayPointers");
        arrayAllocationArraySizesmap[active_fun]=arrayAllocationArraySizes;


    }

    int int_pos=0;
    int char_pos=0;
    int array_pos=0;

    //active_arguments_names.push(args_name);
     //for(auto i=0;i<args_name.size();i++){
     //   std::cout<<args_name[i]<<" ";
    // }

    for(auto i=0;i<args_name.size();i++){
        

        Value * rhs = activefunction->getArg(i);
        std::string var_name= args_name[i];
       
        int var_type = vartype[var_name]; ///ID is INTEGER OR CHAR
        int var_pos = vars[var_name];   ///POSITION IN VARS TABLE , USELESS IF ID IS ARRAY
        bool is_ref = varref[var_name];


        if(array_is_ref[var_name]){

             if(var_type==0){   ///ARRAY INT

                Value * pointer = Builder.CreateGEP(intType,arrayAllocationArray,c32(array_pos),"Int32");
                Builder.CreateStore(rhs,pointer);
                reference_position[var_name]=array_pos;

                Value * pointerSize = Builder.CreateGEP(intType,arrayAllocationArraySizes,c32(array_pos),"Int32");
                Value * emptyint = c32(0);
                Builder.CreateStore(emptyint,pointerSize);

                array_pos++;

               
               
             }
            if(var_type==1){ ///ARRAY CHAR

       
                Value * pointer = Builder.CreateGEP(intType,arrayAllocationArray,c32(array_pos),"Int32");
                Builder.CreateStore(rhs,pointer);
                reference_position[var_name]=array_pos;

                Value * pointerSize = Builder.CreateGEP(intType,arrayAllocationArraySizes,c32(array_pos),"Int32");
                Value * new_rhs =  activefunction->getArg(i+1);
                i=i+1;
                Builder.CreateStore(new_rhs,pointerSize);

                array_pos++;
            }

        }
        else

        if(is_ref){ ///This is for reference parameters

            if(var_type==0){ ///INTEGER
                Value * pointer = Builder.CreateGEP(intPointerType,arrayAllocationInt,c32(int_pos),"pointerInt");
                Builder.CreateStore(rhs,pointer);
                reference_position[var_name]=int_pos;
                int_pos++;

            }

            if(var_type==1){ ///Char
             Value * pointer = Builder.CreateGEP(charPointerType,arrayAllocationChar,c32(char_pos),"pointerChar");
            Builder.CreateStore(rhs,pointer);
            reference_position[var_name]=char_pos;
            char_pos++;
            }

            
          
            

        }   ///END OF REFERENCE
         else {  ///NOT REFERENCE
        if(var_type==0){ ///INTEGER

            ///NOT ARRAY
            llvm::PointerType* pointerType = TheVarsInt->getType();
            Value * lhs = Builder.CreateGEP(pointerType, TheVarsInt, c32(var_pos), name);
            Builder.CreateStore(rhs, lhs); 
         


        }
        if(var_type==1){ ///Char

            ///NOT ARRAY
            llvm::PointerType* pointerType = TheVarsChar->getType();
            Value * lhs = Builder.CreateGEP(pointerType, TheVarsChar, c32(var_pos), name);
            Builder.CreateStore(rhs, lhs); 
         


        }
        
    }///END OF NOT REFERENCE
       



    }

   

    }
    else{               ///FUNCTION DECLARATION
    std::string name = nam.getName();
    active_fun=name;        //Name of active function




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
   
    declared_function[active_fun]=function;

    func_ref[name]=args_ref;
    array_ref[name]=args_array;
    

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

    if((is_integer)&&(array_variable==false)){   ///VARIABLE INTEGER

        if(varref[par_name]==true){ ///REFERENCE INTEGER
        args.push_back(Builder.getInt32Ty()->getPointerTo());  //if reference
        args_ref.push_back(true);
        int_references_counter++;
        }

        else{       ///VARIABLE INTEGER
        args.push_back(i32);
        args_ref.push_back(false);

        }
    args_counter++;
    args_name.push_back(par_name);
    args_array.push_back(false);
    }
    else
     if((is_integer)&&(array_variable)){                ///ARRAY INTEGER

        array_variable=true;
        args_ref.push_back(true);
        args.push_back(i32);
        args_counter+=1;
        args_name.push_back(par_name);
        args_array.push_back(true);
        array_is_ref[par_name]=1;
        array_references_counter++;

    }
    
    else
     if((is_integer==false)&&(array_variable==false)){  ///VARIABLE CHAR

        if(varref[par_name]==true){
            args.push_back(Builder.getInt8Ty()->getPointerTo());  //if reference
            args_ref.push_back(true);
            char_references_counter++;
        }
        else{
            args.push_back(i8);
            args_ref.push_back(false);
        }
        args_counter++;

        args_name.push_back(par_name);
         args_array.push_back(false);

    }

    else
    if((is_integer==false)&&(array_variable)){                ///ARRAY CHAR

         array_variable=true;
        args_ref.push_back(true);
        args.push_back(i32); // Number ?
        args.push_back(i32); ///THIS IS THE SIZE
        args_counter+=1;
          args_counter+=1;  ///THIS IS FOR THE SIZE
        args_name.push_back(par_name);
        args_array.push_back(true);

        args_name.push_back(par_name+"_size"); ///THIS IS THE SIZE NAME
        args_array.push_back(false); ///THIS IS FOR THE SIZE NAME
        args_ref.push_back(false);

        array_is_ref[par_name]=1;
        array_references_counter++;
    }
     
    


    if(comma_id_gen != nullptr) comma_id_gen -> compile();
    return nullptr;
}

Value * Type_gen::compile(){
   // std::cout<<"c32("<<size<<")"<<std::endl;
    if(type_gen != nullptr) type_gen->compile();
    return nullptr;
}

Value * Fpar_def::compile(){

   // llvm::Type* new_integer = Type::getInt32Ty(TheContext);



    std::string par_name = active_fun + "-" + name.getName();

   if(fpar_type->getType()==0){ ///Integer
    is_integer = true;

    if(fpar_type->getArray()==1){   ///ARRAY OF INTEGERS , ALWAYS REFERENCE
        array_variable=true;
        args_ref.push_back(true);
        args.push_back(i32);
        args_counter+=1;
        args_name.push_back(par_name);
        args_array.push_back(true);
        array_is_ref[par_name]=1;
        array_references_counter++;
        
    }
    else{                           ///VARIABLE INTEGER
    array_variable=false;
    if(varref[par_name]==true){
        args.push_back(Builder.getInt32Ty()->getPointerTo());  //if reference
        args_ref.push_back(true);
        int_references_counter++;
    }
    else{
   //args.push_back(Builder.getInt32Ty()->getPointerTo()); if reference
    args.push_back(i32);
    args_ref.push_back(false);
    }
        args_counter++;
        args_name.push_back(par_name);
        args_array.push_back(false);
  
    }
    
   }

    if(fpar_type->getType()==1){ ///char
    is_integer = false;


     if(fpar_type->getArray()==1){   ///ARRAY OF CHARS , ALWAYS REFERENCE
        array_variable=true;
        args_ref.push_back(true);
        args.push_back(i32); // Number ?
        args.push_back(i32); ///THIS IS THE SIZE
        args_counter+=1;
        args_counter+=1;  ///THIS IS FOR THE SIZE
        args_name.push_back(par_name);
        args_array.push_back(true);

        args_name.push_back(par_name+"_size"); ///THIS IS THE SIZE NAME
        args_array.push_back(false); ///THIS IS FOR THE SIZE NAME
         args_ref.push_back(false);

        array_is_ref[par_name]=1;
        array_references_counter++;
  
    }
    else{                           ///VARIABLE CHAR
        array_variable=false;
    if(varref[par_name]==true){
        args.push_back(Builder.getInt8Ty()->getPointerTo());  //if reference
        args_ref.push_back(true);
        char_references_counter++;
    }
    else{
    args.push_back(i8);
    args_ref.push_back(false);
    }
    args_counter++;
    args_name.push_back(par_name);
     args_array.push_back(false);
    }

     }




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
    
    if((is_assign)&&(skip_assign==false)){

        std::string name=id.getName();
        std::string var_name = active_fun + "-" + name;
        std::string new_active_fun=active_fun;
        while((vars[var_name]==0)&&(maparraychar[var_name]==0)&&(maparrayint[var_name]==0)){
            
            new_active_fun = find_parents(new_active_fun);
            var_name=new_active_fun+"-"+name;
             
        }

         int var_type = vartype[var_name];
         int var_pos = vars[var_name];
         bool is_ref = varref[var_name];

    if(word_size!=0){       /// r<-"ABC"
        
        pair < int , int > possible_array;
        possible_array = find_array(var_name,false) ;


        if(possible_array.first>-1) {
        //word_length[var_name]=word_size;
        Value * v = c32(possible_array.first);
        return v;
        }
        else{
             ///THELW NOUMERO STIN THESI 0
            int pos = reference_position[var_name];
            Type * intType = Type::getInt32Ty(TheContext);
            Value * pointer =  Builder.CreateGEP(intType,arrayAllocationArray,c32(pos),"pointerArray");
            Value * v = Builder.CreateLoad(Type::getInt32Ty(TheContext), pointer, name);
            return v;
        }


    }
    else

    if(from_expression==true){ //ARRAYS

        /*
        if( word_length[var_name]==0){
            word_length[var_name]=20;   ///NEED CHANGE
        }
        */

         if(var_type==0){ ///INTEGER

            if(array_is_ref[var_name]==1){    ///THIS IS REFERENCE ARRAY

              int pos = reference_position[var_name];
              
              Type * intType = Type::getInt32Ty(TheContext);
              Value * pointer =  Builder.CreateGEP(intType,arrayAllocationArray,c32(pos),"pointerArray");
              Value * v = Builder.CreateLoad(Type::getInt32Ty(TheContext), pointer, name);
              llvm::PointerType* pointerType = TheVarsInt->getType();
              Value * new_pos = Builder.CreateAdd(v, from_expr, "addtmp");
              return Builder.CreateGEP(pointerType, TheVarsInt, new_pos, name);


            }
            else{ ///THIS IS NOT REFERENCE ARRAY

                  pair < int , int > possible_array;
                  possible_array=find_array(var_name,true);

                  Value * v = c32(possible_array.first);
                  Value * new_pos = Builder.CreateAdd(v, from_expr, "addtmp");
                  llvm::PointerType* pointerType = TheVarsInt->getType();
                  return Builder.CreateGEP(pointerType, TheVarsInt, new_pos, name);



            }

         }

         if(var_type==1){ ///CHAR
             if(array_is_ref[var_name]==1){    ///THIS IS REFERENCE ARRAY

              int pos = reference_position[var_name];
              
              Type * intType = Type::getInt32Ty(TheContext);
              Value * pointer =  Builder.CreateGEP(intType,arrayAllocationArray,c32(pos),"pointerArray");
              Value * v = Builder.CreateLoad(Type::getInt32Ty(TheContext), pointer, name);
              llvm::PointerType* pointerType = TheVarsChar->getType();
              Value * new_pos = Builder.CreateAdd(v, from_expr, "addtmp");
              return Builder.CreateGEP(pointerType, TheVarsChar, new_pos, name);
        

            }
            else{ ///THIS IS NOT REFERENCE ARRAY

                  pair < int , int > possible_array;
                  possible_array=find_array(var_name,false);

                  Value * v = c32(possible_array.first);
                  Value * new_pos = Builder.CreateAdd(v, from_expr, "addtmp");
                  llvm::PointerType* pointerType = TheVarsChar->getType();
                  return Builder.CreateGEP(pointerType, TheVarsChar, new_pos, name);

            }


         }

    

    } ///END OF ARRAYS
    else
    if(is_ref){ //REFERENCE

        int pos = reference_position[var_name];

        if(var_type==0){ ///INTEGER
            Type * intPointerType = Type::getInt32PtrTy(TheContext);
            Value * pointer =  Builder.CreateGEP(intPointerType,arrayAllocationInt,c32(pos),"pointerInt");
            Value * v = Builder.CreateLoad(Type::getInt32PtrTy(TheContext), pointer, name);
            return  v;
        }
        if(var_type==1){ ///CHAR
            Type * charPointerType = Type::getInt8PtrTy(TheContext);
            Value * pointer =  Builder.CreateGEP(charPointerType,arrayAllocationChar,c32(pos),"pointerChar");
            Value * v = Builder.CreateLoad(Type::getInt8PtrTy(TheContext), pointer, name);
            return  v;
        }


    } //END REFERENCE

        else{///NOT REFERENCE
         if(var_type==0){ ///INTEGER

            llvm::PointerType* pointerType = TheVarsInt->getType();
            return Builder.CreateGEP(pointerType, TheVarsInt, c32(var_pos), name);

         }

         else{

        if(var_type==1){ ///CHAR

            llvm::PointerType* pointerType = TheVarsChar->getType();
            return Builder.CreateGEP(pointerType, TheVarsChar, c32(var_pos), name);

         }

         }
        }///END NOT REFERENCE

    }

    else{
   
    return id.compile();
    }


    
        
    } // kati me id
        
    else if(flag == 2) {//kati me const_String
       // const_string.compile();
       std::string get_word = const_string.getStr();

        word_size=0;
        word="";
        for(auto i=1;i<get_word.size()-1;i++){
            word+=get_word[i];
            word_size++;
        }
        

       return nullptr;

    }
    else if (flag == 3){
       
        skip_assign=true;
        from_expr = expr->compile();    // Value of [array]
        skip_assign=false;
      //  std::cout<<"===================";
        //from_expr->print(llvm::outs());
        from_expression=true;
        Value * result = l_value->compile();
        from_expression=false;
        return result;
    

        

    } 
    return nullptr;
    
}

Value * Assign::compile(){

   word_size=0;
   word="";

   Value *rhs = expr->compile();
   is_assign=true;
   Value *lhs =  l_value->compile();
   is_assign = false;
   

    if(word_size==0)
        Builder.CreateStore(rhs, lhs); 

    else{
        
        Value * pos = lhs;
        Type * charpointerType = Type::getInt8PtrTy(TheContext);
        for(auto i=0;i<word_size;i++){
            Value * word_value = c32(i);
            Value * character = c8(word[i]);
            
            Value * new_pos = Builder.CreateAdd(pos, word_value, "addtmpString");
            Value * last_pointer = Builder.CreateGEP(charpointerType, TheVarsChar, new_pos, "Stringpointer");
            Builder.CreateStore(character, last_pointer);
            
            if(word[i]=='`'){
                std::string name = l_value->getName();
                 std::string var_name = active_fun + "-" + name;

                std::string new_active_fun=active_fun;

                while((vars[var_name]==0)&&(maparraychar[var_name]==0)&&(maparrayint[var_name]==0)){
            
                 new_active_fun = find_parents(new_active_fun);
                 var_name=new_active_fun+"-"+name;

                 }
                array_ending[var_name]=last_pointer;
            }
                 
        }


         
    }

    if(zero_found==true){
        
           std::string name = l_value->getName();
                 std::string var_name = active_fun + "-" + name;

                std::string new_active_fun=active_fun;

                while((vars[var_name]==0)&&(maparraychar[var_name]==0)&&(maparrayint[var_name]==0)){
            
                 new_active_fun = find_parents(new_active_fun);
                 var_name=new_active_fun+"-"+name;

                 }
                array_ending[var_name]=lhs;
                zero_found=false;
    }
    word_size=0;

    return nullptr;
}

Value * Func_call_stmt::compile(){
   
    Value *v;

    array_sizes.clear();

    int size_of_array_char=0;
    
    
    
    this_is_ref.clear();

    params.clear();

    header_name = id.getName();
    position=0;

    from_expression=false;

    if(expr!=nullptr) {
        
        if(func_ref[header_name][position]==false){ ///PARAMETER NOT REFERENCE

         v = expr->compile();
         params.push_back(v);
         array_sizes.push_back(0);
        }
        
        else{                               ///PARAMETER REFERENCE OR ARRAY
            


            int flag=0; 
           
            std::string var_name=active_fun + "-" + expr->getName();
           
            bool reff=false;
            for(const auto& pair: reference_position){
            if(pair.first==var_name){
                reff=true;
            }
             }



            if(array_ref[header_name][position]==true){
          
                 if(reff){ //////////////ARRAY IS REFERENCE WRONGGGGGGGGGGGGGGGGGGG
                    int pos=reference_position[var_name];
                            Type * intType = Type::getInt32Ty(TheContext);
                            Value * pointer =  Builder.CreateGEP(intType,arrayAllocationArray,c32(pos),"pointerArraytesting");
                            Value * v = Builder.CreateLoad(Type::getInt32Ty(TheContext), pointer, "name");
                            params.push_back(v);
                            flag=1;

                    int var_type = vartype[var_name];
                    if(var_type==1){ ///CHAR

                     Type * intType = Type::getInt32Ty(TheContext);
                            Value * pointer =  Builder.CreateGEP(intType,arrayAllocationArraySizes,c32(pos),"pointerArraytesting");
                            Value * v = Builder.CreateLoad(Type::getInt32Ty(TheContext), pointer, "name");
                            params.push_back(v);
                            position++;

                    }
                 }
                else{
                    
                    
            int var_type = vartype[var_name]; ///ID is INTEGER OR CHAR
            pair < int , int > possible_array;
            if(var_type==0){ ///INT
                possible_array=find_array(var_name,true);
        

                if(possible_array.first==-1){
                    flag=0;
                }
                else{
             
                    flag=1;
                    

                    /*
                    for(const auto& pair: maparrayint){
                    //std::cout<<"Array Int Name: " << pair.first << " - Begin Pos "<< counter<<" - Size: " << pair.second<<std::endl;
 
                    if(pair.first==var_name){
                          array_sizes.push_back(pair.second);
                    }
                    }
                    */


                    v = c32(possible_array.first);//////////IF REF
                     params.push_back(v);

                }

            }
            else
            if(var_type==1){ ///CHAR
                possible_array=find_array(var_name,false);
                if(possible_array.first==-1){
                    flag=0;
                }
                else{
                   
                    flag=1;
                    
                    for(const auto& pair: maparraychar){
                    //std::cout<<"Array Int Name: " << pair.first << " - Begin Pos "<< counter<<" - Size: " << pair.second<<std::endl;
                   
                    if(pair.first==var_name){
                          size_of_array_char=pair.second;
                    }
                    }
                    
                    v = c32(possible_array.first);
                    params.push_back(v);
                    params.push_back(c32(size_of_array_char));
                    position++;
                 

                }
            }
            }
            }

                    /// Variable Reference
            if(flag==0){
             array_sizes.push_back(0);
            is_assign=true;
                std::string var_name=active_fun + "-" + expr->getName();
              v = expr->compile();
              this_is_ref[var_name]=1;
              params.push_back(v);
            
            is_assign=false;
            }
            //}
        
        
        }
        position++;
        
        if(comma_expr_gen != nullptr) comma_expr_gen->compile();   
    }


 


    /// NEED TO STORE THE VARIABLES OF THE FUNCTION I CALL
    std::string function_name = id.getName();

    for(const auto& pair: variable_function){
    
        if((pair.second==function_name)&&(this_is_ref[pair.first]!=1)){
            std::string var_name=pair.first;

            int var_type = vartype[var_name]; ///ID is INTEGER OR CHAR
            int var_pos = vars[var_name];   ///POSITION IN VARS TABLE , USELESS IF ID IS ARRAY

        Value * v;
        Value * val;

            if(var_type==0){ ///INTEGER

                 llvm::PointerType* pointerType = TheVarsInt->getType();
                  v = Builder.CreateGEP(pointerType, TheVarsInt, c32(var_pos), var_name);
                 val =  Builder.CreateLoad(Type::getInt32Ty(TheContext), v, var_name);
              }
      if(var_type==1){ ///CHAR

          llvm::PointerType* pointerType = TheVarsChar->getType();
          v = Builder.CreateGEP(pointerType, TheVarsChar, c32(var_pos), var_name);
          val =  Builder.CreateLoad(Type::getInt32Ty(TheContext), v, var_name);
    }

            keep_variables_values[var_name].push(val);
     

            

        }
   }
/*
    for (auto i=0;i<array_sizes.size();i++){
        std::cout<<array_sizes[i]<<" ";
    }
*/
   // keep_array_sizes.push(array_sizes);

    Value * result = Builder.CreateCall(TheModule->getFunction(id.getName()),params);
   
    //keep_array_sizes.pop();
   // active_arguments_names.pop();

    ///NEED TO POP AND REPLACE IN TheVarsInt - TheVarsChar
      for(const auto& pair: variable_function){
    
        if((pair.second==function_name)&&(this_is_ref[pair.first]!=1)){
            std::string var_name=pair.first;

            int var_type = vartype[var_name]; ///ID is INTEGER OR CHAR
            int var_pos = vars[var_name];   ///POSITION IN VARS TABLE , USELESS IF ID IS ARRAY

            Value * old_val = keep_variables_values[var_name].top();
            keep_variables_values[var_name].pop();

          
            if(var_type==0){ ///INTEGER

                 llvm::PointerType* pointerType = TheVarsInt->getType();
                  v = Builder.CreateGEP(pointerType, TheVarsInt, c32(var_pos), var_name);
                  Builder.CreateStore(old_val, v); 
              }
            if(var_type==1){ ///CHAR

                llvm::PointerType* pointerType = TheVarsChar->getType();
                v = Builder.CreateGEP(pointerType, TheVarsChar, c32(var_pos), var_name);
                 Builder.CreateStore(old_val, v); 
                
            }

            

        }
   }


    return result;
}

Value * Comma_expr_gen::compile(){
   
   Value * v;
   int size_of_array_char=0;
    
   
        if(func_ref[header_name][position]==false){ ///PARAMETER NOT REFERENCE

         v = expr->compile();
         params.push_back(v);
         array_sizes.push_back(0);
        }
        
        else{                               ///PARAMETER REFERENCE OR ARRAY
            


            int flag=0; 
           
            std::string var_name=active_fun + "-" + expr->getName();


            bool reff=false;
            for(const auto& pair: reference_position){
            if(pair.first==var_name){
                reff=true;
            }
             }
           


            if(array_ref[header_name][position]==true){
                    
                 if(reff){ //////////////ARRAY IS REFERENCE WRONGGGGGGGGGGGGGGGGGGG
                    int pos=reference_position[var_name];
                            Type * intType = Type::getInt32Ty(TheContext);
                            Value * pointer =  Builder.CreateGEP(intType,arrayAllocationArray,c32(pos),"pointerArraytesting");
                            Value * v = Builder.CreateLoad(Type::getInt32Ty(TheContext), pointer, "name");
                            params.push_back(v);
                            flag=1;
                           
                            int var_type = vartype[var_name];
                            if(var_type==1){ ///CHAR

                            Type * intType = Type::getInt32Ty(TheContext);
                            Value * pointer =  Builder.CreateGEP(intType,arrayAllocationArraySizes,c32(pos),"pointerArraytesting");
                            Value * v = Builder.CreateLoad(Type::getInt32Ty(TheContext), pointer, "name");
                            params.push_back(v);
                            position++;

                    }
                 }
                else{
                    
                    
            int var_type = vartype[var_name]; ///ID is INTEGER OR CHAR
            pair < int , int > possible_array;
            if(var_type==0){ ///INT
                possible_array=find_array(var_name,true);
        

                if(possible_array.first==-1){
                    flag=0;
                }
                else{
             
                    flag=1;
                    
                    /*
                    for(const auto& pair: maparrayint){
                    //std::cout<<"Array Int Name: " << pair.first << " - Begin Pos "<< counter<<" - Size: " << pair.second<<std::endl;
 
                    if(pair.first==var_name){
                          array_sizes.push_back(pair.second);
                    }
                    }
                    */

                    v = c32(possible_array.first);//////////IF REF
                     params.push_back(v);

                }

            }
            else
            if(var_type==1){ ///CHAR

                
                possible_array=find_array(var_name,false);
                if(possible_array.first==-1){
                    flag=0;
                }
                else{
                   
                    flag=1;
                    for(const auto& pair: maparraychar){
                    //std::cout<<"Array Int Name: " << pair.first << " - Begin Pos "<< counter<<" - Size: " << pair.second<<std::endl;
                   
                    if(pair.first==var_name){
                          size_of_array_char=pair.second;
                    }
                    }
                    v = c32(possible_array.first);
                    params.push_back(v);
                    params.push_back(c32(size_of_array_char));
                    position++;


                }
            }
            }
            }

                    /// Variable Reference
            if(flag==0){
             array_sizes.push_back(0);
            is_assign=true;
                std::string var_name=active_fun + "-" + expr->getName();
              v = expr->compile();
              this_is_ref[var_name]=1;
              params.push_back(v);
            
            is_assign=false;
            }
            //}
        
        
        }
        position++;
      
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

    array_sizes.clear();

    int size_of_array_char=0;
    
    
    
    this_is_ref.clear();

    params.clear();

    header_name = id.getName();
    position=0;

    from_expression=false;

    if(expr!=nullptr) {
        
        if(func_ref[header_name][position]==false){ ///PARAMETER NOT REFERENCE

         v = expr->compile();
         params.push_back(v);
         array_sizes.push_back(0);
        }
        
        else{                               ///PARAMETER REFERENCE OR ARRAY
            


            int flag=0; 
           
            std::string var_name=active_fun + "-" + expr->getName();
           
            bool reff=false;
            for(const auto& pair: reference_position){
            if(pair.first==var_name){
                reff=true;
            }
             }



            if(array_ref[header_name][position]==true){
          
                 if(reff){ //////////////ARRAY IS REFERENCE WRONGGGGGGGGGGGGGGGGGGG
                    int pos=reference_position[var_name];
                            Type * intType = Type::getInt32Ty(TheContext);
                            Value * pointer =  Builder.CreateGEP(intType,arrayAllocationArray,c32(pos),"pointerArraytesting");
                            Value * v = Builder.CreateLoad(Type::getInt32Ty(TheContext), pointer, "name");
                            params.push_back(v);
                            flag=1;

                    int var_type = vartype[var_name];
                    if(var_type==1){ ///CHAR

                     Type * intType = Type::getInt32Ty(TheContext);
                            Value * pointer =  Builder.CreateGEP(intType,arrayAllocationArraySizes,c32(pos),"pointerArraytesting");
                            Value * v = Builder.CreateLoad(Type::getInt32Ty(TheContext), pointer, "name");
                            params.push_back(v);
                            position++;

                    }
                 }
                else{
                    
                    
            int var_type = vartype[var_name]; ///ID is INTEGER OR CHAR
            pair < int , int > possible_array;
            if(var_type==0){ ///INT
                possible_array=find_array(var_name,true);
        

                if(possible_array.first==-1){
                    flag=0;
                }
                else{
             
                    flag=1;
                    

                    /*
                    for(const auto& pair: maparrayint){
                    //std::cout<<"Array Int Name: " << pair.first << " - Begin Pos "<< counter<<" - Size: " << pair.second<<std::endl;
 
                    if(pair.first==var_name){
                          array_sizes.push_back(pair.second);
                    }
                    }
                    */


                    v = c32(possible_array.first);//////////IF REF
                     params.push_back(v);

                }

            }
            else
            if(var_type==1){ ///CHAR
                possible_array=find_array(var_name,false);
                if(possible_array.first==-1){
                    flag=0;
                }
                else{
                   
                    flag=1;
                    
                    for(const auto& pair: maparraychar){
                    //std::cout<<"Array Int Name: " << pair.first << " - Begin Pos "<< counter<<" - Size: " << pair.second<<std::endl;
                   
                    if(pair.first==var_name){
                          size_of_array_char=pair.second;
                    }
                    }
                    
                    v = c32(possible_array.first);
                    params.push_back(v);
                    params.push_back(c32(size_of_array_char));
                    position++;

                }
            }
            }
            }

                    /// Variable Reference
            if(flag==0){
             array_sizes.push_back(0);
            is_assign=true;
                std::string var_name=active_fun + "-" + expr->getName();
              v = expr->compile();
              this_is_ref[var_name]=1;
              params.push_back(v);
            
            is_assign=false;
            }
            //}
        
        
        }
        position++;
        
        if(comma_expr_gen != nullptr) comma_expr_gen->compile();   
    }


 


    /// NEED TO STORE THE VARIABLES OF THE FUNCTION I CALL
    std::string function_name = id.getName();

    for(const auto& pair: variable_function){
    
        if((pair.second==function_name)&&(this_is_ref[pair.first]!=1)){
            std::string var_name=pair.first;

            int var_type = vartype[var_name]; ///ID is INTEGER OR CHAR
            int var_pos = vars[var_name];   ///POSITION IN VARS TABLE , USELESS IF ID IS ARRAY

        Value * v;
        Value * val;

            if(var_type==0){ ///INTEGER

                 llvm::PointerType* pointerType = TheVarsInt->getType();
                  v = Builder.CreateGEP(pointerType, TheVarsInt, c32(var_pos), var_name);
                 val =  Builder.CreateLoad(Type::getInt32Ty(TheContext), v, var_name);
              }
      if(var_type==1){ ///CHAR

          llvm::PointerType* pointerType = TheVarsChar->getType();
          v = Builder.CreateGEP(pointerType, TheVarsChar, c32(var_pos), var_name);
          val =  Builder.CreateLoad(Type::getInt32Ty(TheContext), v, var_name);
    }

            keep_variables_values[var_name].push(val);
     

            

        }
   }
/*
    for (auto i=0;i<array_sizes.size();i++){
        std::cout<<array_sizes[i]<<" ";
    }
*/
   // keep_array_sizes.push(array_sizes);

    Value * result = Builder.CreateCall(TheModule->getFunction(id.getName()),params);
   
    //keep_array_sizes.pop();
   // active_arguments_names.pop();

    ///NEED TO POP AND REPLACE IN TheVarsInt - TheVarsChar
      for(const auto& pair: variable_function){
    
        if((pair.second==function_name)&&(this_is_ref[pair.first]!=1)){
            std::string var_name=pair.first;

            int var_type = vartype[var_name]; ///ID is INTEGER OR CHAR
            int var_pos = vars[var_name];   ///POSITION IN VARS TABLE , USELESS IF ID IS ARRAY

            Value * old_val = keep_variables_values[var_name].top();
            keep_variables_values[var_name].pop();

          
            if(var_type==0){ ///INTEGER

                 llvm::PointerType* pointerType = TheVarsInt->getType();
                  v = Builder.CreateGEP(pointerType, TheVarsInt, c32(var_pos), var_name);
                  Builder.CreateStore(old_val, v); 
              }
            if(var_type==1){ ///CHAR

                llvm::PointerType* pointerType = TheVarsChar->getType();
                v = Builder.CreateGEP(pointerType, TheVarsChar, c32(var_pos), var_name);
                 Builder.CreateStore(old_val, v); 
                
            }

            

        }
   }


    return result;
   
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

    std::string new_active_fun=active_fun;

    while((vars[var_name]==0)&&(maparraychar[var_name]==0)&&(maparrayint[var_name]==0)){
            
        new_active_fun = find_parents(new_active_fun);
        var_name=new_active_fun+"-"+name;

    }

    


    // Return Value of  Variable for assign

    int var_type = vartype[var_name]; ///ID is INTEGER OR CHAR
    int var_pos = vars[var_name];   ///POSITION IN VARS TABLE , USELESS IF ID IS ARRAY
    bool is_ref = varref[var_name];

    if(from_expression==true){ ///ARRAY
    

         if(var_type==0){ ///INTEGER

            if(array_is_ref[var_name]==1){    ///THIS IS REFERENCE ARRAY

             int pos = reference_position[var_name];
              
              Type * intType = Type::getInt32Ty(TheContext);
              Value * pointer =  Builder.CreateGEP(intType,arrayAllocationArray,c32(pos),"pointerArray");
              Value * v = Builder.CreateLoad(Type::getInt32Ty(TheContext), pointer, name);
              llvm::PointerType* pointerType = TheVarsInt->getType();
              Value * new_pos = Builder.CreateAdd(v, from_expr, "addtmp");
              Value * last_pointer = Builder.CreateGEP(pointerType, TheVarsInt, new_pos, name);
              return Builder.CreateLoad(Type::getInt32Ty(TheContext), last_pointer, name);
            }
            else{  ///NOT REFERENCE ARRAY
                pair < int , int > possible_array;
                  possible_array=find_array(var_name,true);

                  Value * v = c32(possible_array.first);
                  Value * new_pos = Builder.CreateAdd(v, from_expr, "addtmp");

                  llvm::PointerType* pointerType = TheVarsInt->getType();
                  Value * last_pointer = Builder.CreateGEP(pointerType, TheVarsInt, new_pos, name);
                  return Builder.CreateLoad(Type::getInt32Ty(TheContext), last_pointer, name);
            }
            
        }
         if(var_type==1){ ///CHAR

            if(array_is_ref[var_name]==1){    ///THIS IS REFERENCE ARRAY

            int pos = reference_position[var_name];
              
              Type * intType = Type::getInt32Ty(TheContext);
              Value * pointer =  Builder.CreateGEP(intType,arrayAllocationArray,c32(pos),"pointerArray");
              Value * v = Builder.CreateLoad(Type::getInt32Ty(TheContext), pointer, name);
              llvm::PointerType* pointerType = TheVarsChar->getType();
              Value * new_pos = Builder.CreateAdd(v, from_expr, "addtmp");
              Value * last_pointer = Builder.CreateGEP(pointerType, TheVarsChar, new_pos, name);
              return Builder.CreateLoad(Type::getInt8Ty(TheContext), last_pointer, name);
            }
            else{  ///NOT REFERENCE ARRAY
                  pair < int , int > possible_array;
                  possible_array=find_array(var_name,false);

                  Value * v = c32(possible_array.first);
                  Value * new_pos = Builder.CreateAdd(v, from_expr, "addtmp");
                  llvm::PointerType* pointerType = TheVarsChar->getType();
                  Value * last_pointer = Builder.CreateGEP(pointerType, TheVarsChar, new_pos, name);
                  return Builder.CreateLoad(Type::getInt8Ty(TheContext), last_pointer, name);

            }
            
        }

    } /// END ARRAY
    else
    if(is_ref){ //REFERENCE

        int pos = reference_position[var_name];

        if(var_type==0){ ///INTEGER
            Type * intPointerType = Type::getInt32PtrTy(TheContext);
            Value * pointer =  Builder.CreateGEP(intPointerType,arrayAllocationInt,c32(pos),"pointerInt");
            Value * v = Builder.CreateLoad(Type::getInt32PtrTy(TheContext), pointer, name);
            return  Builder.CreateLoad(Type::getInt32Ty(TheContext), v, name);
        }
        if(var_type==1){ ///CHAR
            Type * charPointerType = Type::getInt8PtrTy(TheContext);
            Value * pointer =  Builder.CreateGEP(charPointerType,arrayAllocationChar,c32(pos),"pointerChar");
            Value * v = Builder.CreateLoad(Type::getInt8PtrTy(TheContext), pointer, name);
            return  Builder.CreateLoad(Type::getInt8Ty(TheContext), v, name);
        }


    } //END REFERENCE

    else{ ///NOT REFERENCE
    if(var_type==0){ ///INTEGER

         llvm::PointerType* pointerType = TheVarsInt->getType();
         Value * v = Builder.CreateGEP(pointerType, TheVarsInt, c32(var_pos), name);
         return  Builder.CreateLoad(Type::getInt32Ty(TheContext), v, name);
    }
    if(var_type==1){ ///CHAR

        llvm::PointerType* pointerType = TheVarsChar->getType();
         Value * v = Builder.CreateGEP(pointerType, TheVarsChar, c32(var_pos), name);
         return  Builder.CreateLoad(Type::getInt8Ty(TheContext), v, name);


    }
    } ///END NOT REFERENCE




    return nullptr;
}

Value * StringConst::compile(){
    return nullptr;
}


Value * Const_char::compile() {
    if((str[1]=='\\')&&(str[2]=='0')){
        zero_found=true;
        str[1]='`';
        //return c8('\0');
    }
    if((str[1]=='\\')&&(str[2]=='n')){
        zero_found=true;
        str[1]=' ';
        //return c8('\0');
    }
    return c8(str[1]);
}

//PRINTSSSS

Value * Write_Integer::compile(){

    Value *val = e->compile();
    Value *n64 = Builder.CreateSExt(val, i64, "ext");
    Builder.CreateCall(TheWriteInteger, {n64});
  
  /*
    llvm::PointerType* pointerType = activefunction->getType();
    Value *nl = Builder.CreateGEP(pointerType, TheNL, {c32(0), c32(0)}, "nl");
    Builder.CreateCall(TheWriteString, {nl});

    */
     return nullptr;
}

Value * Write_String::compile(){

    ///Print a text
    std::string new_str="";

    if(flag==0){

          std::string var_name = active_fun + "-" + id.getName();

           std::string new_active_fun=active_fun;
            while((vars[var_name]==0)&&(maparraychar[var_name]==0)&&(maparrayint[var_name]==0)){
            
                new_active_fun = find_parents(new_active_fun);
                var_name=new_active_fun+"-"+id.getName();

            }

          pair < int , int > possible_array;
          possible_array = find_array(var_name,false) ;
          int pos=possible_array.first;

          if(pos!=-1){ ///THIS IS NOT REFERENCE ARRAY
          int sizes=word_length[var_name];
          
      
      

        for(auto i=0 ; i<sizes;i++){
            
            int new_pos=pos+i;
            llvm::PointerType* pointerType = TheVarsChar->getType();
            Value * v = Builder.CreateGEP(pointerType, TheVarsChar, c32(new_pos), "load");
            Value * result =  Builder.CreateLoad(Type::getInt8Ty(TheContext), v, "load");

            Builder.CreateCall(TheWriteChar, {result});

            if(v==array_ending[var_name]){
               // std::cout<<i; ARRAY ENDINGGGGGGGGGGGG
                break;
            }
        }
        }


        else{ ///THIS IS REFERENCE ARRAY

   
    /*
         int pos = reference_position[var_name];
         Type * intType = Type::getInt32Ty(TheContext);
         Value * pointer =  Builder.CreateGEP(intType,arrayAllocationArray,c32(pos),"pointerArray");
         Value * v = Builder.CreateLoad(Type::getInt32Ty(TheContext), pointer, "name");
         
         Type * charpointerType = Type::getInt8PtrTy(TheContext);

          int sizes=word_length[var_name];

          if(sizes==0) sizes=200;

          */
        

            int pos = reference_position[var_name];
              
              Type * intType = Type::getInt32Ty(TheContext);
              Value * pointerS =  Builder.CreateGEP(intType,arrayAllocationArraySizes,c32(pos),"pointerArray");
              Value * length  = Builder.CreateLoad(Type::getInt32Ty(TheContext), pointerS, var_name);
     
                Value * pointer =  Builder.CreateGEP(intType,arrayAllocationArray,c32(pos),"pointerArray");
                Value * v = Builder.CreateLoad(Type::getInt32Ty(TheContext), pointer, "name");
   

             
             //   Value *n64 = Builder.CreateSExt(v, i64, "ext");
              //  Builder.CreateCall(TheWriteInteger, {n64});


           
        
            Value * count=c32(0);



            // Save the original insertion point
           // llvm::BasicBlock OriginalBB = Builder.GetInsertBlock();
           // llvm::IRBuilderBase::InsertPoint originalInsertPoint = Builder.saveIP();

            for(int i=0;i<200;i++){

            llvm::Value *condValue = length;
            llvm::Value *cond = Builder.CreateICmpSGT(condValue, c32(0), "if_cond");
            
          


            llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
            llvm::BasicBlock *ThenBB = llvm::BasicBlock::Create(TheContext, "then", TheFunction);
            llvm::BasicBlock *ElseBB = llvm::BasicBlock::Create(TheContext, "else", TheFunction);
            llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(TheContext, "endif", TheFunction);

            /* conditional branch, set insert point and save thenValue */
            Builder.CreateCondBr(cond, ThenBB, ElseBB);
    
    
            Builder.SetInsertPoint(ThenBB);

           //Value *n64 = Builder.CreateSExt(length, i64, "ext");
           // Builder.CreateCall(TheWriteInteger, {n64});
         

            Value * word_value = count;
            Value * new_pos = Builder.CreateAdd(v, word_value, "addtmpString");
            llvm::PointerType* pointerType = TheVarsChar->getType();
            Value * ptr = Builder.CreateGEP(pointerType, TheVarsChar, new_pos, "load");
            Value * result =  Builder.CreateLoad(Type::getInt8Ty(TheContext), ptr, "load");

            Builder.CreateCall(TheWriteChar, {result});

           // Builder.CreateBr(AfterBB);
  
          //  Builder.SetInsertPoint(ElseBB);
          //  return nullptr;
            

          //Builder.SetInsertPoint(AfterBB);
          // Builder.SetInsertPoint(activeBB);

            ThenBB = Builder.GetInsertBlock();
            Builder.CreateBr(AfterBB);
            Builder.SetInsertPoint(ElseBB);
            Builder.CreateBr(AfterBB);

           // Builder.CreateRetVoid();

            Builder.SetInsertPoint(AfterBB);
       
            length = Builder.CreateSub(length, c32(1), "subtmp1");
            count = Builder.CreateAdd(count, c32(1), "addtmp1");

           


            }
          // Builder.SetInsertPoint(activeBB);

    /*
           llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();

            llvm::BasicBlock *LoopBB = llvm::BasicBlock::Create(TheContext, "loop", TheFunction);
            llvm::BasicBlock *BodyBB = llvm::BasicBlock::Create(TheContext, "body", TheFunction);
            llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(TheContext, "endwhile", TheFunction);
            Builder.CreateBr(LoopBB);
            Builder.SetInsertPoint(LoopBB);
            llvm::Value *condValue = length;
            llvm::Value *cond = Builder.CreateICmpNE(condValue, c32(0), "while_cond");
            Builder.CreateCondBr(cond, BodyBB, AfterBB);
    
            Builder.SetInsertPoint(BodyBB);

               n64 = Builder.CreateSExt(length, i64, "ext");
             Builder.CreateCall(TheWriteInteger, {n64});
            Value * word_value = count;
            Value * new_pos = Builder.CreateAdd(v, word_value, "addtmpString");
            llvm::PointerType* pointerType = TheVarsChar->getType();
            Value * ptr = Builder.CreateGEP(pointerType, TheVarsChar, new_pos, "load");
            Value * result =  Builder.CreateLoad(Type::getInt8Ty(TheContext), ptr, "load");

             Builder.CreateCall(TheWriteChar, {result});

             length = Builder.CreateSub(length, c32(1), "subtmp1");

             n64 = Builder.CreateSExt(length, i64, "ext");
             Builder.CreateCall(TheWriteInteger, {n64});


             count = Builder.CreateAdd(length, c32(1), "addtmp1");

    
            Builder.CreateBr(LoopBB);
 
            Builder.SetInsertPoint(AfterBB);
    */
            return nullptr;



        /*
        for(auto i=0 ; i<sizes;i++){
            
            
            Value * word_value = c32(i);
            Value * new_pos = Builder.CreateAdd(v, word_value, "addtmpString");
            llvm::PointerType* pointerType = TheVarsChar->getType();
            Value * v = Builder.CreateGEP(pointerType, TheVarsChar, new_pos, "load");
            Value * result =  Builder.CreateLoad(Type::getInt8Ty(TheContext), v, "load");
            /////  NEED TO CHECK IF RESULT == ` and break BROKEN
            //result->print(llvm::outs());
            llvm::Value* charConstant = llvm::ConstantInt::get(llvm::Type::getInt8Ty(TheContext), '`');

            // Compare the Value* with the char value
            llvm::Value* isEqual = Builder.CreateICmpEQ(result, charConstant, "compare");

            // Convert the result to an integer (0 or 1)
            llvm::Value* check = Builder.CreateZExt(isEqual, llvm::Type::getInt32Ty(TheContext), "result");
            
          


             Builder.CreateCall(TheWriteChar, {result});
        }
        */
        
        
       /*
            Value * new_pos = v;
            llvm::PointerType* pointerType = TheVarsChar->getType();
            Value * result_ptr = Builder.CreateGEP(pointerType, TheVarsChar, new_pos, "load");
            
            Builder.CreateCall(TheWriteString, {result_ptr});
        */

        }


        llvm::PointerType* pointerType = activefunction->getType();
       Value *nl = Builder.CreateGEP(pointerType, TheNL, {c32(0), c32(0)}, "nl");
      Builder.CreateCall(TheWriteString, {nl});

    }


    if(flag==1){
    std::string str="";
    str+=x;

    for(int i=1;i<str.size()-1;i++){
        new_str+=str[i];
    }

    }


    // Value * v = Builder.CreateGlobalString(StringRef(new_str),"varName");

    //Builder.CreateCall(TheWriteString, {v});
    std::string print_str="";
    for(int i=0;i<new_str.size();i++){
        
        if(i<new_str.size()-1){
            
            if((new_str[i]=='\\') &&(new_str[i+1]=='n')){
                if(print_str!=""){
                    Value * v = Builder.CreateGlobalString(StringRef(print_str),"varName");

                    Builder.CreateCall(TheWriteString, {v});
                    print_str="";
                }
                llvm::PointerType* pointerType = activefunction->getType();
                Value *nl = Builder.CreateGEP(pointerType, TheNL, {c32(0), c32(0)}, "nl");
                Builder.CreateCall(TheWriteString, {nl});
            
            i++;
            }
            else
            print_str+=new_str[i];

        }
        else

        print_str+=new_str[i];
    }

    if(print_str!=""){
    Value * v = Builder.CreateGlobalString(StringRef(new_str),"varName");

    Builder.CreateCall(TheWriteString, {v});
    }

    ///Print ARRAY CHAR
    // ----------------------------TO DO
    /*
    llvm::PointerType* pointerType = activefunction->getType();
    Value *nl = Builder.CreateGEP(pointerType, TheNL, {c32(0), c32(0)}, "nl");
    Builder.CreateCall(TheWriteString, {nl});
    */
    return nullptr;
}

Value * Write_Char::compile(){

    ///---------------------------TO DO

    Value *val = e->compile();
    Builder.CreateCall(TheWriteChar, {val});
     llvm::PointerType* pointerType = activefunction->getType();
    Value *nl = Builder.CreateGEP(pointerType, TheNL, {c32(0), c32(0)}, "nl");
    Builder.CreateCall(TheWriteString, {nl});
     return nullptr;


   /* if(flag==0){
        
        
        Value *val = id.compile();
       Builder.CreateCall(TheWriteChar, {val});
    

       
    }
    else{

   
   std::string new_str = "";
    new_str+=str[1];
   
     Value * v = Builder.CreateGlobalString(StringRef(new_str),"varName");
     Builder.CreateCall(TheWriteString, {v});

    }

    llvm::PointerType* pointerType = activefunction->getType();
    Value *nl = Builder.CreateGEP(pointerType, TheNL, {c32(0), c32(0)}, "nl");
    Builder.CreateCall(TheWriteString, {nl});
     return nullptr;*/
}

Value * ReadInteger::compile(){
    return Builder.CreateCall(TheReadInteger,{});
}

Value * ReadChar::compile(){
    return Builder.CreateCall(TheReadChar,{});
}

Value * Ascii::compile() {
    if(flag == 0){
        char c = character[1];
        Value *charValue = Builder.getInt8(c);
    // return charValue;
        return Builder.CreateCall(TheAscii, {charValue});
    }
    else{
        
        Value * v = id.compile();
        
        return Builder.CreateCall(TheAscii, {v});
    }

}

Value* Chr::compile() {
    if(flag == 0){
        Value *val = llvm::ConstantInt::get(llvm::Type::getInt32Ty(TheContext), num);
        Value *n64 = Builder.CreateSExt(val, i64, "ext");
        return Builder.CreateCall(TheChr, {n64});
    }
    else{
        Value * v = id.compile();
        
        return Builder.CreateCall(TheChr, {v});
    }
}

Value * ReadString::compile(){
    Value * v = e->compile();
    Value *n64 = Builder.CreateSExt(v, i64, "ext");
    Value * idv = id.compile(); ////READSTRING NEED POINTER
    return Builder.CreateCall(TheReadString,{n64,idv});
}

Value * Strlen::compile(){

   
    ///REFERENCE NOT WORKING ///////

    


    ////NEED TO CREATE A POINTER TO id

     std::string name=lv->getName();


        std::string var_name = active_fun + "-" + name;
        std::string new_active_fun=active_fun;
        while((vars[var_name]==0)&&(maparraychar[var_name]==0)&&(maparrayint[var_name]==0)){
            
            new_active_fun = find_parents(new_active_fun);
            var_name=new_active_fun+"-"+name;
             
        }

    Value * v = c32(0);

  
    //std::vector < std::string > name_list=active_arguments_names.top();
    //std::vector < int > array_size_list=keep_array_sizes.top();
    /*
    int flag=0;
    for(auto i=0;i<name_list.size();i++){
        if(var_name==name_list[i]){
            v = c32(array_size_list[i]);
            return v;
        }
    }
    */
   bool is_ref = varref[var_name];
  
   if(is_ref){

     int pos = reference_position[var_name];
              
              Type * intType = Type::getInt32Ty(TheContext);
              Value * pointer =  Builder.CreateGEP(intType,arrayAllocationArraySizes,c32(pos),"pointerArray");
               v = Builder.CreateLoad(Type::getInt32Ty(TheContext), pointer, name);
     
     return v;
   }
   else{
    

    for(const auto& pair: maparraychar){
    //std::cout<<"Array Int Name: " << pair.first << " - Begin Pos "<< counter<<" - Size: " << pair.second<<std::endl;
    
    if(pair.first==var_name){
      v = c32(pair.second);
      return v;
    }

    }

    return v;
   }

    
}

Value * StrCmp::compile(){
    //Value *v1 = lv1->compile();
    //Value *v2 = lv2->compile();
    return nullptr;
    
}
Value * StrCpy::compile(){
    //Value *v1 = lv1->compile();
    //Value *v2 = lv2->compile();
        return nullptr;

   
}
Value * StrCat::compile(){
    //Value *v1 = lv1->compile();
    //Value *v2 = lv2->compile();
        return nullptr;

}
