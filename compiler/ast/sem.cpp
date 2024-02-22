//sem.cpp

#include "ast.hpp"
#include <vector>
#include <stack>
/// ERRORS TO DO :  READINTEGER, REF
Typos prevType; // used for comma id gen
bool prevRef;
int prevAns;
vector<int> functions; //vector that contains each return value of every function
bool returned = false; //flag to check if function returns correctly
bool idGenFlag = false; // if this is false then comma id gen inserts variable. else it inserts parameter
int arraySize = 0;
bool idflag = 0; //used to check if we have an id
int idAfterArr = 0; //this is to find if we have x[i] (id after array)
bool constFlag = 0;
int arrayFlag = 0; //used to see if a parameter is an array in L value
int arrayIndex = -1; //used to check arrayIndex
bool main_found = false;
bool func_has_body = false; ///used to separate Func_decl -> false with Func_def -> true 
bool check_if_array=false;
bool expr_is_id=false;
int array_dimension_counter=0; ///Used in Var_def , Fpar_def , Comma_id_gen , Mytype in order to find Array Dimensions When Declaring the variable
bool check_completed=false;
bool from_assign = false;
bool visited = false;
Typos keep_type;
string keepidname;

int dimensions_keep = -1;
int func_counter = 0;
int fun_counter=0;

std::map < std::string,int > functions_exist;

std::map <std::string, vector < int > > func_decl_params;
std::map <std::string, vector < int > > function_params;

std::vector < int > function_parameters; ///1 int , 2 char , 3 ref int , 4 ref char

std::vector<ParameterEntry> vec;    /// used in HEADER, Fpar_def , Fpar_def_gen
std::vector<ParameterEntry> fcallparams; // used for func_Call
extern int lineno;
/*
    COMPARE
*/

// Compare 2 Expressions , Return Type = Bool if correct
void Compare::sem() {
    expr1->findType();
    expr2->findType();

   // std::cout<<expr1->type<<" "<<expr2->type<<std::endl;
    if(expr1->type != expr2->type) yyerror("Type Mismatch");
    type = TYPE_bool;
    
} 

/*
    COND
*/

// Check if Type cond1 = Bool & Type cond2 = Bool , Return Type = Bool if Correct
void Cond::sem() {
    cond1->check_type(TYPE_bool);
    if(cond2 != nullptr){
        cond2->check_type(TYPE_bool);
    }
    type=TYPE_bool;
}

/*
    HEADER
*/

// fun ID (Fpar_def ; Fpar_def_gen) : Ret_type ;
// ID : nam , Fpar_def = fp , Fpar_def_gen = fpg , Ret_type = r
void Header::sem(){
    
    function_parameters.clear();
    // vec contains PARAMETERS ( Type , name , arraysize)
    // Clear this Header parameters to add them again later
    while (!vec.empty()) // empty the vector that will contain possible parameters of the funtion
    {
        vec.pop_back();
    }
     if((fpar_def != nullptr)&&(func_counter==0)) yyerror("First Function Can't Have Arguments");
    
    func_counter=1;

   /* if(func_has_body){
         functions_exist[nam.getName()]=2;
    }
    else{
        functions_exist[nam.getName()]=1; ///1 = func_decl
    }
    */
   
    // Function declaration without or with body , -100 = No body , 0 = Has Body
    if(func_has_body==false){
     st.insert(nam.getName(),ret_type->getTypos(),ENTRY_FUNCTION, -100);
    
    }
    else
    st.insert(nam.getName(),ret_type->getTypos(),ENTRY_FUNCTION, 0);
    
    //if Header has body , get the Expected Return Type
    //functions = Vector with expected return Types
    if(func_has_body==true){
    functions.push_back(ret_type->getTypos());
    }

    //call frpar_def , fpardef_gen in order to create vector vec
    if(fpar_def != nullptr)
        fpar_def->sem();
    if(fpar_def_gen!= nullptr)
        fpar_def_gen->sem();
    

    if(func_has_body==false){
        func_decl_params[nam.getName()]=function_parameters;
         functions_exist[nam.getName()]=1; 
    }
    else{
    if(functions_exist[nam.getName()]==1){
        std::vector < int > previus_params =  func_decl_params[nam.getName()];

    if(previus_params.size()!=function_parameters.size()){
        yyerror("Funcion Declaration and Defitition are not the same: ",nam.getName());
    }
        for(auto i=0;i<previus_params.size();i++){

          
            if(previus_params[i]!=function_parameters[i])
                yyerror("Funcion Declaration and Defitition are not the same:",nam.getName());
        }
        }
    functions_exist[nam.getName()]=2;

    }

    // Function declaration with parameters at vec without or with body , 0 = No body , 1 = Has Body
    if(func_has_body==true){
        ft.insert(nam.getName(), vec,ret_type->getTypos(),1);
    }
    else
        ft.insert(nam.getName(), vec,ret_type->getTypos(),0);

    func_has_body = true;

  //  ft.printST();
   // st.printST();
   
}

/*
    FUNC DEF
*/

// New Function with body
// Func_def = header + local_def_gen + block
void Func_def::sem(){

    fun_counter++;
    // --------header-------
    func_has_body = true;

    //Open new Symbol Table Scope
    if(main_found==false){
    st.openScope();
    header->sem();
    main_found=true;
    }
    else{
    header->sem();
    st.openScope();
    }

    // --------local_def_gen---------
    if(local_def_gen != nullptr){
        local_def_gen->sem();
    }

    // ---------block--------

    block -> fetch_func(header->getName());  // insert parameters in Symbol Table
 
    block->sem();
    block->checkReturn();
    functions.pop_back();  // pop the return value of the function we just checked.
    returned = false;      // set this to false (initialize it)
    st.closeScope();
    
    fun_counter--;
    if(fun_counter==0){
         for(const auto& pair: functions_exist){
        if(pair.second==1){
            yyerror("Function Declared But Not Defined!",pair.first);
        }
         }
    }

}
/*
    BLOCK
*/
void Block::sem(){
    
    for (Stmt *s : stmt_list) s->sem();
    
} 
void Block::checkReturn(){  //checks if funtion returned correctly
    //std::cout<<returned; 
    if(functions.back() == 2 && returned == false){
        returned = true;
    }
    else if(returned==false && functions.back() != 2){
        yyerror("Function doesn't return anything!" );
    }

}

//insert fpar_def parameters in Symbol Table 
void Block::fetch_func(std::string name){
    FunctionEntry *f = ft.lookup(name);
    std::vector<ParameterEntry> params = f->parameters;
    //st.printST();
    for (auto i = params.rbegin(); i != params.rend(); ++i){
       // std::cout<< i->name << std::endl;
        st.insert(i->name, i->type, ENTRY_PARAMETER, i->arraySize);
       // st.printST();
    }
    
}

/*
    LOCAL DEF
*/
void Local_def::sem(){

    //3 Cases: Local def is func_def OR func_decl OR var_def

    if (func_def != nullptr)
        func_def->sem();
    else if(func_decl != nullptr)
        func_decl->sem();
    else if(var_def != nullptr)
        var_def->sem();
    else{
        return;
    }
}

/*
    LOCAL DEF GEN    
*/
// Calls local_def->sem()
void Local_def_gen::sem(){
    
    local_def->sem();
    if (local_def_gen != nullptr){
        local_def_gen->sem();
    }
}

/*
    FUNC DECL
*/
void Func_decl::sem() { 
   
    func_has_body = false;
    header->sem();
   
}

/*
    VAR DEF
*/
// Var_def has id , comma_id_gen->sem() , type

void Var_def::sem() {
    
    //get arraysize in Var_def declaration , add to the scope
    arraySize = 0;

    array_dimension_counter = 0;
    type->sem();

    //std::cout<<"NAME: "<<id.getName()<<" TYPE: "<<type->getTypos()<<" Dimensions: "<<array_dimension_counter<<std::endl;
    st.insert(id.getName(), type->getTypos(), ENTRY_VARIABLE, array_dimension_counter);

    prevType = type->getTypos(); // for comma id gen
    if(comma_id_gen!=nullptr){
        idGenFlag = false;
        comma_id_gen->sem();
    }
    
}

/*
    COMMA ID GEN
*/
// Comes from Fpar_def , does the same work for each (,)
void Comma_id_gen::sem() {
    if(idGenFlag == 0) {    /// Comes From Val_Def
     //   std::cout<<"NAME: "<<name.getName()<<" TYPE: "<<prevType<<" Dimensions: "<<array_dimension_counter<<std::endl;
        st.insert(name.getName(),prevType ,ENTRY_VARIABLE, array_dimension_counter); 
    }
    else{           ///comes from Fpar_def      

        function_parameters.push_back(prevAns);

     // std::cout<<"NAME: "<<name.getName()<<" TYPE: "<<prevType<<" Dimensions: "<<array_dimension_counter<<std::endl;
        vec.push_back(ParameterEntry(prevType, name.getName(), array_dimension_counter));
    }
    if(comma_id_gen!=nullptr)     
       comma_id_gen->sem();
}


int arr_dimension_size_counter=0;
int array_expected_dimension_size;
int dimensions_found = 0;
/*
    ASSIGN
*/
void Assign::sem() {
    
    dimensions_found = 0;
    visited = false;
    check_if_array = true;

    expr ->sem();
     if(visited) dimensions_found ++ ;   /// if expr is String then +1 dimension
    
    l_value->sem();
    type = l_value->type;
   
    //std::cout<<"Expected Dimensions:"<<array_expected_dimension_size<<std::endl;
    //std::cout<<"Real Dimensions:"<<arr_dimension_size_counter<<std::endl;

     if(functions_exist[l_value->getName()]!=0){
         yyerror("This is a function!!!!!",l_value->getName() );
     }

    expr->check_type(l_value->type); // check that the assigned type is the same as the type of the id

}

/*
    L_VALUE
*/


void L_value::sem(){
 
    if(flag == 1){
        expr_is_id = true; 
        SymbolEntry *e = st.lookup(id.getName()); /// find Symbol

     //   std::cout<<"ID: "<<id.getName()<<std::endl;

        array_expected_dimension_size = e->arraySize;
        type = e->type;
        keep_type = e->type;
        keepidname=id.getName();
        
        if(check_if_array==true){
            if(array_expected_dimension_size!=dimensions_found){
              //  std::cout<<"Expected Dimensions:"<<array_expected_dimension_size<<std::endl;
              //  std::cout<<"Real Dimensions:"<<dimensions_found<<std::endl;
                yyerror("Dimensions are wrong !", id.getName());
            }
            dimensions_found=0;
        }
        else{

           // std::cout<<"eimai dame:size= "<<dimensions_found<<" "<<array_expected_dimension_size<<std::endl;

            if(dimensions_found > 0){
                if(array_expected_dimension_size!=dimensions_found){
                 //   std::cout<<"Expected Dimensions:"<<array_expected_dimension_size<<std::endl;
                 //   std::cout<<"Real Dimensions:"<<dimensions_found<<std::endl;
                    yyerror("Dimensions are wrong !", id.getName());
                }

                dimensions_found = 0;
                if(dimensions_keep==-1) dimensions_keep = 0;
            }
            else
                if(dimensions_keep==-1) dimensions_keep = array_expected_dimension_size;


        }
     
        
        
    }
    else if(flag == 2){ ///comes only from px. x <- "hi";

        type = TYPE_char;
        
        visited = true;

    }
    else if(flag == 3) {//array

       dimensions_found ++;
        l_value->sem();

       dimensions_found = 0;  ///reset

        expr->sem();
        expr->arrayCheck();
        type = l_value->type;
        dimensions_found = 0; // reset
        
        
    }
}

void L_value::arrayCheck(){
    if(l_value != nullptr) l_value->arrayCheck();
    else if(expr != nullptr) expr->arrayCheck();
    else if(id.isValid()) id.arrayCheck();
    else if(const_string.isValid()) const_string.arrayCheck();
}

char* L_value::getName() {
        if(flag == 1){
            if(id.isValid()){
               // std::cout<<id.getName();
                
                return id.getName();
            }
        }
        else if(flag == 3){
            
            
            return l_value->getName();
              
        }
        return nullptr;
      

}


/*
    BIN OP
*/
void BinOp::sem(){
    expr1->check_type(TYPE_int);  // only integers
    expr2->check_type(TYPE_int);
    type = TYPE_int;
   
    constFlag = 1;
}

/*
    UN OP
*/
void UnOp::sem(){
    expr->check_type(TYPE_int);  // only integers
    type = TYPE_int;
    constFlag = 1;
}

/*
    IF
*/
void If::sem(){
    
    condition->check_type(TYPE_bool);
    
    bool if_returned=false;
    bool else_returned=false;
    
    if(stmt1!=nullptr)
        stmt1->sem();

    if_returned=returned;
   
    returned=false;
    if (stmt2 != nullptr) { 
        
        stmt2->sem();
        else_returned=returned;
    }
    if(if_returned && else_returned){ returned=true;}
    else returned=false;
    

}

/*
    WHILE   
*/
void While::sem(){
    condition->check_type(TYPE_bool);
    stmt->sem();
}

/*
    RETURN
*/
void Return::sem(){
    
    int ret = functions.back(); // find the ret type of that should be returned

    if(expr != nullptr){
        expr->findType();  //find the type that is actually returned
      
        if(expr->type != ret){ //check if they match
            yyerror("Return value not correct");
        }
    }
    else {
        if(ret != TYPE_nothing) yyerror("Return value not correct!");
    }
    returned = true;
    
}

/*
    FPAR DEF
*/
// This is called from header->sem(), Creates vector vec with all the function parameters

void Fpar_def::sem(){


    //Find arraySize

   array_dimension_counter=0;
   if(fpar_type->getArray() == 1){

        if(ref==false){
            yyerror("Array Must Be Reference",name.getName());
        }
      array_dimension_counter = 1; // char[] or int[]
    }


    
    fpar_type->sem();
    
   // std::cout<<"NAME: "<<name.getName()<<" TYPE: "<<fpar_type->getType()<<" Dimensions: "<<array_dimension_counter<<std::endl;
    
    int ans=0;
    if(fpar_type->getType()==0){
        if(ref){
            ans=3;
        }
        else
        ans=1;
    }
    if(fpar_type->getType()==1){
        if(ref){
            ans=4;
        }
        else
        ans=2;
    }
    function_parameters.push_back(ans);
    vec.push_back(ParameterEntry(fpar_type->getType(),name.getName(), array_dimension_counter));
 //   st.insert(name.getName(),fpar_type->getType(), ENTRY_PARAMETER, arraySize);
    
 // keep the type in order to insert the new parameter for each ,   
    prevType = fpar_type->getType();
    prevAns=ans;
    if(comma_id_gen!=nullptr){
       idGenFlag = true;
       comma_id_gen->sem();
    }
    //st.printST();
}

/*
    FPAR DEF GEN
*/
// Calls Fpar_def 
void Fpar_def_gen::sem(){
    
    fpar_def->sem();
    if(fpar_def_gen != nullptr)
        fpar_def_gen->sem();
}

/*
    TYPE GEN
*/

void Type_gen::sem(){

    if(size<=0)yyerror("Array Size Must be > 0");
    if(type_gen!=nullptr){
        array_dimension_counter++;
        type_gen->sem();
    }
}

/*
    TYPE
*/
void MyType::sem(){
     if(type_gen!=nullptr){
        array_dimension_counter++;
        type_gen->sem();
    }
}
/*
    FPAR TYPE
*/
void Fpar_type::sem(){
    type=typos;
    if(type_gen!=nullptr){       
        array_dimension_counter++;
        type_gen->sem(); 
    }
}

/*
    FUNC CALL EXPR
*/
void Func_call_expr::sem(){   
   
   while (!fcallparams.empty()) // empty the vector that will contain the parameters fot a fun call
    {
        fcallparams.pop_back();
    }

     if( functions_exist[id.getName()]==0)yyerror("Undefined Function !",id.getName());
   SymbolEntry *s = st.lookup(id.getName());
   if (s != nullptr){ 
   FunctionEntry *f = ft.lookup(id.getName());   // find if there is a function with this name
   if (f != nullptr){ 
    type = f->return_type; // set the type as the return type of the function
    
   }
   std::vector<ParameterEntry> correctParams = f->getParams();

   if(expr == nullptr && correctParams.size() != 0){
    yyerror("Function called without parameters! ", id.getName());
   }

   check_if_array = false;
   expr_is_id = false;
   visited = false;
  
   dimensions_found = 0;
   dimensions_keep = -1;
   constFlag = false;

   if(expr != nullptr){
   // expr->findType();
    expr->sem();

    if(visited) dimensions_found++;  ///string
   
       if(expr_is_id){  
        fcallparams.push_back(ParameterEntry(expr->type, "const", dimensions_keep ));
        }
    
    
    else{
        dimensions_found=0;
         if(visited) dimensions_found++;  ///string
        //  std::cout<<"CONSTANT ID: Dimensions = "<<dimensions_found<<std::endl;
        fcallparams.push_back(ParameterEntry(expr->type, "const", dimensions_found));  //const is a random name. It will never be used. Here the entry is a constant. Also we assume there are no constant arrays
        
        }       
    if(comma_expr_gen != nullptr){
       comma_expr_gen->sem();
    }
    
    if(correctParams.size() != fcallparams.size()){
       yyerror("Function called with wrong amount of parameters: ", id.getName());
    } 
    else{
        for (int i = 0; i < static_cast<int>(correctParams.size()); i++){
            if(correctParams.at(i).type != fcallparams.at(i).type)
                yyerror("Function called with wrong parameters: ", id.getName());
            else if(correctParams.at(i).arraySize != 0  && fcallparams.at(i).arraySize == 0)
                yyerror("Parameter is an array! Function called with wrong parameters:: ", id.getName());
            else if(correctParams.at(i).arraySize > 0 && fcallparams.at(i).arraySize != correctParams.at(i).arraySize)
                yyerror("Parameter array size wrong! Function called with wrong parameters: ", id.getName());
            else if(correctParams.at(i).arraySize == 0 && fcallparams.at(i).arraySize != correctParams.at(i).arraySize)
                yyerror("Function called with an array, but it does not wait one. Function called with wrong parameters: ", id.getName());
        }   
    } 
   }
   }
   
    
   
}   

void Func_call_expr::arrayCheck(){

    FunctionEntry *f = ft.lookup(id.getName());
    if(f->return_type != TYPE_int){
        yyerror("Wrong index array");
    }
}

/*
    COMMA EXPR GEN
*/
void Comma_expr_gen::sem(){
    check_if_array = false;
   expr_is_id = false;
   visited = false;
  
   dimensions_found = 0;
   dimensions_keep = -1;
   constFlag = false;

   if(expr != nullptr){
    //expr->findType();
    expr->sem();

    if(visited) dimensions_found++;  ///string
   
      if(expr_is_id){  
        fcallparams.push_back(ParameterEntry(expr->type, "const", dimensions_keep ));
        }
    
    
    else{
        dimensions_found=0;
         if(visited) dimensions_found++;  ///string
       //   std::cout<<"CONSTANT ID: Dimensions = "<<dimensions_found<<std::endl;
        fcallparams.push_back(ParameterEntry(expr->type, "const", dimensions_found));  //const is a random name. It will never be used. Here the entry is a constant. Also we assume there are no constant arrays
        
        }


    if(comma_expr_gen != nullptr){
       comma_expr_gen->sem();
    }
    
    
   }
}

/*
    FUNC CALL STMT //SAME AS FUNC CALL EXPR 
*/ 
void Func_call_stmt::sem(){  //DO I HAVE TO FETCH FUNC SCOPE?? HERE WE AREwhat happens in the symbol table? create new scope for the variables of the function only
    
    while (!fcallparams.empty()) // empty the vector that will contain the parameters fot a fun call
    {
        fcallparams.pop_back();
    }

    if( functions_exist[id.getName()]==0)yyerror("Undefined Function !",id.getName());
   SymbolEntry *s = st.lookup(id.getName());
   if (s != nullptr){ 
   FunctionEntry *f = ft.lookup(id.getName());   // find if there is a function with this name
   if (f != nullptr){ 
    type = f->return_type; // set the type as the return type of the function
    
   }
   std::vector<ParameterEntry> correctParams = f->getParams();

   if(expr == nullptr && correctParams.size() != 0){
    yyerror("Function called without parameters! ", id.getName());
   }

   check_if_array = false;
   expr_is_id = false;
   visited = false;
  
   dimensions_found = 0;
   dimensions_keep = -1;
   constFlag = false;

   if(expr != nullptr){
    //expr->findType();
    
    expr->sem();

    if(visited) dimensions_found++;  ///string
   
     if(expr_is_id){  
        fcallparams.push_back(ParameterEntry(expr->type, "const", dimensions_keep ));
        }
    
    
    else{
        dimensions_found=0;
         if(visited) dimensions_found++;  ///string
       //   std::cout<<"CONSTANT ID: Dimensions = "<<dimensions_found<<std::endl;
        fcallparams.push_back(ParameterEntry(expr->type, "const", dimensions_found));  //const is a random name. It will never be used. Here the entry is a constant. Also we assume there are no constant arrays
        
        }       
    if(comma_expr_gen != nullptr){
       comma_expr_gen->sem();
    }
    
    if(correctParams.size() != fcallparams.size()){
       yyerror("Function called with wrong amount of parameters: ", id.getName());
    } 
    else{
        for (int i = 0; i < static_cast<int>(correctParams.size()); i++){
            if(correctParams.at(i).type != fcallparams.at(i).type)
                yyerror("Function called with wrong parameters: ", id.getName());
            else if(correctParams.at(i).arraySize != 0  && fcallparams.at(i).arraySize == 0)
                yyerror("Parameter is an array! Function called with wrong parameters:: ", id.getName());
            else if(correctParams.at(i).arraySize > 0 && fcallparams.at(i).arraySize != correctParams.at(i).arraySize)
                yyerror("Parameter array size wrong! Function called with wrong parameters: ", id.getName());
            else if(correctParams.at(i).arraySize == 0 && fcallparams.at(i).arraySize != correctParams.at(i).arraySize)
                yyerror("Function called with an array, but it does not wait one. Function called with wrong parameters: ", id.getName());
        }   
    } 
   }
   }
   
    
   
}   

/*
    WRITE INTEGER
*/
void Write_Integer::sem(){
    /*if(n == -1){
    SymbolEntry *e = st.lookup(id.getName());
    type = e->type;
    if(type != TYPE_int)
        yyerror("Write_Integer only prints Integers!");
    }*/
}

/*
    WRITE String
*/
void Write_String::sem(){
   /* if(flag == 0){
    SymbolEntry *e = st.lookup(id.getName());
    type = e->type;
    if(type != TYPE_char)
        yyerror("Write_String only prints Strings!");
    }*/
}

/*
    WRITE char
*/
void Write_Char::sem(){
    /*SymbolEntry *e = st.lookup(id.getName());
    type = e->type;
    if(type != TYPE_char)
        yyerror("Write_Char only prints Chars!");*/
}
/*
    ID
*/
void Id::sem(){
    
    idflag = 1;
   // type = TYPE_id;
   
}



char* Id::getName(){
        
        return name;
}
void Id::arrayCheck(){
    //std::cout<<"array check";
    SymbolEntry *e = st.lookup(name);

    if(e->type != TYPE_int) 
        yyerror("Wrong array index") ;
} 

void Ret_type::sem(){
    type = typos;
   
}
/*
    INT CONST
*/
void IntConst::sem() {
    type = TYPE_int;
    idflag = 0;
   
}
void IntConst::arrayCheck(){
   arrayIndex = num;
}

/*
    CONST CHAR
*/
void Const_char::sem() {
    type = TYPE_char;
    idflag = 0;
}
void Const_char::arrayCheck(){
    yyerror("Wrong array index");
}

/*
    STRING CONST
*/
void StringConst::sem() {
 
    //type = TYPE_const_string;
    type = TYPE_char;
    array_dimension_counter++;
    idflag = 0;
}
void StringConst::arrayCheck(){
    yyerror("Wrong array index");
}

void Ascii::sem(){
    type = TYPE_int;
}

void Chr::sem(){
    type = TYPE_char;

}
void Strlen::sem(){
    type = TYPE_int;
}

void StrCmp::sem(){
    type = TYPE_int;
}

void StrCat::sem(){
   
}
void StrCpy::sem(){

}
