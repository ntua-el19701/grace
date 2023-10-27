#include "ast.hpp"

#include<vector>
#include<map>

std::pair < int , bool > parameter;  /// TYPE - BOOL REF

std::map < std::string , std::string > parent;   ///Find the previus function
std::map < std::string , int > vars; /// Find the position of variable in VARS
std::map < std::string , int > vartype;  /// Find the Type - REF for variable/parameter
std::map < std::string , bool > varref;
std::map < std::string , int > maparrayint;
std::map < std::string , int > maparraychar;

int int_counter=0;
int char_counter=0;
int fun_counter=0;
int array_int_counter=0;
int array_char_counter=0;
int array_size=-1;
int array_int_size=0;
int array_char_size=0;


string prev_fun="emptyfun"; ///keep the previus function

std::string find_parent(std::string child){

    return parent[child];

}

void printThis(){

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

    for(const auto& pair: maparrayint){
    std::cout<<"Array Int Name: " << pair.first << " - Size: " << pair.second<<std::endl;
   }

    for(const auto& pair: maparraychar){
    std::cout<<"Array Char Name: " << pair.first << " - Size: " << pair.second<<std::endl;
   }

    
    std::cout<<endl;

    for(const auto& pair: parent){
    std::cout<<"Name: " << pair.first << " - Parent: " << pair.second<<std::endl;
   }
}

void Local_def::preCompile(){    
    
    
    if (func_def != nullptr)
        func_def->preCompile();
    else if(func_decl != nullptr)
        func_decl->preCompile();
    else if(var_def != nullptr)
        var_def->preCompile();
    
    
}


void Local_def_gen::preCompile(){
    local_def->preCompile();
    if(local_def_gen!=nullptr) local_def_gen->preCompile();
    
}

void Header::preCompile() {
    /// ? add fun_name , return type in maps ?
    std::string name = nam.getName();
    parent[name]=prev_fun;
    prev_fun=name;
    if(fpar_def != nullptr) fpar_def->preCompile();
    if(fpar_def_gen != nullptr) fpar_def_gen->preCompile();

}

void Var_def::preCompile(){
 

    parameter.first = type->getTypos();
    parameter.second = false;

    array_size=-1;

    std::string new_var = prev_fun + "-" + id.getName();

    vartype[new_var] = parameter.first;
    varref[new_var]=parameter.second;

    if(parameter.first == TYPE_int){
        
        if(type->getTypeGen()!=nullptr){ ///Integer Array
            maparrayint[new_var] = type->getTypeGen()->getSize();
            array_int_counter++;
            array_size=type->getTypeGen()->getSize();
            array_int_size+=array_size;
        }
        
        else{  //Integer Variable
        int_counter++;
        vars[new_var]=int_counter;
        }
    }
    else{
    if(parameter.first == TYPE_char){

        if(type->getTypeGen()!=nullptr){ ///Char Array
            maparraychar[new_var] = type->getTypeGen()->getSize();
            array_char_counter++;
            array_size=type->getTypeGen()->getSize();
            array_char_size+=array_size;
        }
        else{ //Char Variable

        char_counter++;
        vars[new_var]=char_counter;

        }

    }
    }



    if(comma_id_gen != nullptr) comma_id_gen->preCompile();
   // fpar_type->compile();

    //  printThis();

}

void Block::preCompile(){
    
   
}

void Func_decl::preCompile(){
    
    /* empty */
    //header->preCompile();
}

void Func_def::preCompile (){
    header -> preCompile();
    if(local_def_gen != nullptr) local_def_gen->preCompile();
    block -> preCompile();

    prev_fun = find_parent(prev_fun);

    if(prev_fun=="emptyfun"){
        printThis();

    }
    
}

void Comma_id_gen::preCompile(){

    std::string new_var;
    new_var = prev_fun + "-" + name.getName();

    vartype[new_var] = parameter.first;
    varref[new_var]=parameter.second;

    if(parameter.first == TYPE_int){

        if(array_size!=-1){ //Integer Array
            maparrayint[new_var] = array_size;
            array_int_counter++;
             array_int_size+=array_size;
         
        }
        else{   //Integer Variable
        int_counter++;
        vars[new_var]=int_counter;
        }
    }
    else{
         if(array_size!=-1){ //char Array
            maparraychar[new_var] = array_size;
            array_char_counter++;
            array_char_size+=array_size;
           
        }
        else{   //Char Variable
        char_counter++;
        vars[new_var]=char_counter;
        }

    }

    if(comma_id_gen != nullptr) comma_id_gen -> preCompile();
  
}

void Fpar_def_gen::preCompile(){
    fpar_def->preCompile();
    if(fpar_def_gen != nullptr) fpar_def_gen->preCompile();
    
}

void Fpar_def::preCompile(){

    parameter.first = fpar_type->getType();
    parameter.second = ref;
    array_size=-1;


    std::string new_var;
    new_var = prev_fun + "-" + name.getName();

    vartype[new_var] = parameter.first;
    varref[new_var]=parameter.second;

    if(parameter.first == TYPE_int){
        int_counter++;
        vars[new_var]=int_counter;
    }
    else{
        char_counter++;
        vars[new_var]=char_counter;

    }



    if(comma_id_gen != nullptr) comma_id_gen->preCompile();
   // fpar_type->compile();

  //printThis();
    
}


