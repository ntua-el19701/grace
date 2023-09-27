#ifndef __SYMBOL_HPP__
#define __SYMBOL_HPP__

#include <map>
#include <string>
#include <vector>

void yyerror(const char *msg);

void yyerror(const char *msg, const std::string& name);

enum Typos { TYPE_int, TYPE_char, TYPE_nothing,  TYPE_bool, TYPE_const_char, TYPE_const_string};
enum EntryType { ENTRY_CONSTANT, ENTRY_PARAMETER, ENTRY_VARIABLE, ENTRY_FUNCTION};
extern int lineno;

struct SymbolEntry {
Typos type;
EntryType entryType;
int arraySize = 0;
SymbolEntry() {}
SymbolEntry(Typos t, EntryType et, int arr) : type(t), entryType(et), arraySize(arr) {}
};

struct ParameterEntry { //struct that has the fields of a parameter : type, name and arraySize
Typos type;
std::string name;
int arraySize = 0;
ParameterEntry() {}
ParameterEntry(Typos t, std::string n, int arr) : type(t), name(n), arraySize(arr) {}
};


struct FunctionEntry {  //struct that has the fields of a function : return type and a vector that contains its parameters
Typos return_type;
std::vector<ParameterEntry> parameters; // vector for parameters (EntryType will always be ENTRY_Parameter)

std::vector<ParameterEntry> getParams(){
    return parameters;
}
FunctionEntry() {}
FunctionEntry(Typos t, std::vector<ParameterEntry> st)  {
    return_type = t;
  
    if(!st.empty()){
        parameters = st;
    }
}
};

class Func_scope{  //has a map with the function name and a function Entry field. Here we insert a new funtion 
public:
    Func_scope(){}
    void insert(std::string s, std::vector<ParameterEntry> st, Typos t){
        //to do look if there is a function with the same name
        if (funcs.find(s) != funcs.end()){ yyerror("Duplicate Function Name : ", s); }

        
        funcs[s] = FunctionEntry(t, st);
        
    }
    void printScope(){
       for(const auto &elem : funcs){
           std::cout<<elem.first << " " << elem.second.return_type << " " ;
           if(!elem.second.parameters.empty()) {
                std::cout<<" with these parameters : ";
               for (auto i = elem.second.parameters.rbegin(); i != elem.second.parameters.rend(); ++i){
                std::cout << std::endl << i->name << " " << i->type << " " << i->arraySize ;
               }
               std::cout<< std::endl;
            }
       }
    }
    FunctionEntry *lookup(std::string s){
        if (funcs.find(s) == funcs.end()) return nullptr;
        return &funcs[s];
    }    
private:
    std::map<std::string, FunctionEntry> funcs;
};

class FunctionTable{  // contains all the functions of the program
public:
   void insert(std::string s, std::vector<ParameterEntry> st, Typos t){
         // each scope is one function
        Func_scopes.insert(s ,st, t);
    }
   void printST (){
     std::cout<<"Printing FT: " << std::endl;
        Func_scopes.printScope();
        std::cout<<std::endl;
    }
    FunctionEntry *lookup(std::string s){
        FunctionEntry *f =  Func_scopes.lookup(s);
        if (f != nullptr) return f;
        yyerror("Function not found: ", s);
        return nullptr;
    }
    
private:
    Func_scope Func_scopes;
};

class Scope {
public:
    Scope() {}
    void insert(std::string s, Typos t, EntryType et, int isArr){
        if (locals.find(s) != locals.end()){ yyerror("Duplicate variable: ", s); } 
        //std::cout<<"insert in scope "<<std::endl;
        locals[s] = SymbolEntry(t, et, isArr);
    }
    SymbolEntry *lookup(std::string s){
        if (locals.find(s) == locals.end()) return nullptr;
        return &locals[s];
    }
    void reduceSize() { 
        size=size-1;
    }

    void incrSize() {
        size=size+1;
    }

    int getSize(){
        return size;
    }

    void printScope(){
       for(const auto &elem : locals){
           std::cout<<elem.first << " " << elem.second.type << " " << elem.second.entryType << " " << elem.second.arraySize << std::endl;
       }
    }

private:
    std::map<std::string, SymbolEntry> locals;
    int size;
};

class SymbolTable{
public:
    SymbolEntry *lookup(std::string s) {
        for (auto i = scopes.rbegin(); i != scopes.rend(); ++i) {
            SymbolEntry *e = i->lookup(s);
             if (e != nullptr) return e;
        }
         yyerror("Variable not found: ", s);
         return nullptr;
    }

    void insert(std::string s, Typos t, EntryType et, int arr) {
        scopes.back().insert(s , t, et, arr);
        //std::cout<<s<<" insert"<<std::endl;
    }

    void openScope () {
        std::cout<<"scope opened \n"<<std::endl;
        size++;
        scopes.push_back(Scope());
        //std::cout<<"size of scope: "  << size;

    }

    void closeScope () {
        std::cout<<"scope closed \n"<<std::endl;
        size--;
        scopes.pop_back();
      //  std::cout<<"size of scope: " << size;
    }

    void printST (){
        std::cout<<"Printing ST with size " << size << std::endl;
        for (auto i = scopes.rbegin(); i != scopes.rend(); i++) {
            i->printScope();
            std::cout<<std::endl;
         }
    
    }
private:
    std::vector<Scope> scopes;
    int size=0;

};


extern SymbolTable st;
extern FunctionTable ft;


#endif