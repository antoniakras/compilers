#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define HASH 100
#define EXPAND_SIZE 1024
#define CURR_SIZE (total*sizeof(quad)) 
#define NEW_SIZE (EXPAND_SIZE*sizeof(quad) + CURR_SIZE)


int curr_scope;
int scope_flag = 0;
int flag = 0;
char *func_name;
unsigned int programVarOffset =0;
unsigned int functionLocalOffset=0;
unsigned int formalArgOffset=0;
unsigned int scopeSpaceCounter =1;
int currQuad=0;
int total=0;
int globalVariables=0;
unsigned int tmp_func=0;
unsigned int tempcounter=0;
char tmp_buf[50];
struct Stack* locals;
struct Stack* formals;
struct Stack* breakst;
struct Stack* contst;
struct Stack* returnst;
int orQuad;
int functionJump;


enum SymbolType{
    LIB,USERF,GLOBAL,LOCAL_VAR,FORMAL_ARG
};

enum symbol_t{var_s,programfunc_s,libraryfunc_s};

typedef enum iopcode{ 
    assign,         add,            sub,
    mul,            _div,           mod,
    uminus,         and,            or,
    not,            if_eq,          if_noteq,
    if_lesseq,      if_greatereq,   if_less,
    if_greater,     call,           param,
    ret,            getretval,      funcstart,
    funcend,        tablecreate,    jump,
    tablegetelem,   tablesetelem

}iopcode;


typedef enum scopespace_t{
    programvar,
    functionlocal,
    formalarg,
} scopespace_t;

typedef enum expr_t{

    var_e,
    tableitem_e,

    programfunc_e,
    libraryfunc_e,

    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,

    constnum_e,
    constbool_e,
    conststring_e,

    nil_e

}expr_t;

typedef struct SymTable {
    char *name;
    enum SymbolType type; // global , local , argument
    char *category; //func or variable
    int scope;
    int line;
    scopespace_t space;
    unsigned int offset;
    unsigned int address;
    unsigned int totallocals;
    int label;
    int isActive; // 0 off , 1 on 
    struct SymTable *next;
    struct SymTable *scope_next;
    struct SymTable *prev;
}sym_t;

typedef struct HashTable{
    int size;
    sym_t **hash_array;
}hash_table;


/*hash table*/
hash_table* hash_tbl;


int hash(int key){
    return (key % HASH);
}

typedef struct list{
    int label;
    struct list *next;
}list;

typedef struct expr{
    expr_t type;
    sym_t* sym; //to front leei symbol
    struct expr* index; 
    /*expr index : manage dynamic tables*/
    int numConst;
    char* strConst;
    unsigned char boolConst;
    struct expr* next;
    struct list* trueList;
    struct list* falseList;
}expr;


struct Stack{
    int size;    
    int top;
    int* elems;
};


typedef struct for_p{
    unsigned test,enter;
}for_p;

typedef struct stmt_t{
    int breakList,contList,returnList;
}stmt_t;

struct call{
    char* name;
    unsigned char method;
    /*1=norm , 2=method , 3=suffix*/
    expr* elist;
};


typedef struct quad{
    iopcode op;
    expr* arg1;
    expr* arg2;
    expr* result;
    unsigned int label;
    unsigned int line;
    unsigned taddress;
}quad;

quad* quads =(quad*)0;

sym_t *head_of_scope; //to head tou scope

expr *tmpFuncName;


sym_t *put(char* name,enum SymbolType type,char *category ,int line, int scope){

    if(type==2) globalVariables++;

    sym_t *new_Sym_table = malloc(sizeof(struct SymTable));
    int pos=hash(atoi(name));
    int flag=0; //check if scope next is null or not found.
    new_Sym_table->name=malloc(sizeof(char*));
    strcpy(new_Sym_table->name, name);
    new_Sym_table->type=type;
    new_Sym_table->category=malloc(sizeof(char*));
    strcpy(new_Sym_table->category, category);
    new_Sym_table->line=line;
    new_Sym_table->scope=scope;
    new_Sym_table->isActive=1;
    new_Sym_table->next=NULL;
    new_Sym_table->scope_next=NULL;
    sym_t *curr=hash_tbl->hash_array[pos];
    sym_t *curr_head_scope = head_of_scope;


    if(curr==NULL){
          curr=new_Sym_table;
    }else{

        while(curr->next){
            curr=curr->next;      
        }
        curr->next=new_Sym_table;
    }

    while((curr_head_scope->next) &&(curr_head_scope->scope != scope) ){
         curr_head_scope=curr_head_scope->next;   
     }

        if(curr_head_scope->scope==scope){
            
            // new_Sym_table->scope_next = curr_head_scope->scope_next;
            // curr_head_scope->scope_next =new_Sym_table;
              while(curr_head_scope->scope_next){
                  curr_head_scope=curr_head_scope->scope_next;
           }

          curr_head_scope->scope_next=new_Sym_table;
          


         }else{
              sym_t *new_scopelist= malloc(sizeof(struct SymTable));
              curr_head_scope->next=new_scopelist;
              new_scopelist->next=NULL;
              new_scopelist->prev=curr_head_scope;
              new_scopelist->scope_next=new_Sym_table;
              new_scopelist->scope=scope;
        }
        return new_Sym_table;
}

void init(){
    //create & initialize symtable with LIB FUNCTIONS.
    int i=0;
    func_name=malloc(sizeof(char*));
    hash_tbl = malloc(sizeof(hash_table));
    hash_tbl->size=0;
    hash_tbl->hash_array=malloc(HASH * sizeof(sym_t));
    head_of_scope= malloc(sizeof(sym_t));
    head_of_scope->scope =0;
    head_of_scope->next =NULL;
    head_of_scope->scope_next =NULL;
    head_of_scope->prev = NULL;
    for(i ; i < HASH ; i++){
        hash_tbl->hash_array[i] = NULL;
    }

    //initialize LIB FUNCTIONS.
    put("print",LIB,"FUNC",0,0);
    put("input",LIB,"FUNC",0,0);
    put("oblctmemberkeys",LIB,"FUNC",0,0);
    put("objecttotalmembers",LIB,"FUNC",0,0);
    put("objectcopy",LIB,"FUNC",0,0);
    put("totalarguments",LIB,"FUNC",0,0);
    put("argument",LIB,"FUNC",0,0);
    put("typeof",LIB,"FUNC",0,0);
    put("strtonum",LIB,"FUNC",0,0);
    put("sqrt",LIB,"FUNC",0,0);
    put("cos",LIB,"FUNC",0,0);
    put("sin",LIB,"FUNC",0,0);

}

scopespace_t currScopeSpace(void){
    if(scopeSpaceCounter==1){
        return programvar;
    }else{
        if(scopeSpaceCounter%2==0){
            return formalarg;
        }else{
            return functionlocal;
        }
    }
}

unsigned int currScopeOffset(void){
    switch (currScopeSpace()){
        case programvar: return programVarOffset;
        case functionlocal: return functionLocalOffset;
        case formalarg: return formalArgOffset;
        default: assert(0);
    }
}

void inCurrScopeOffset(void){
    switch(currScopeSpace()){
        case programvar: ++programVarOffset;
        case functionlocal: ++functionLocalOffset;
        case formalarg: ++formalArgOffset;
        default: assert(0);
    }
}

void exitScopeSpace(void){
    assert(scopeSpaceCounter>1);
    --scopeSpaceCounter;
}

void enterScopeSpace(void){
    ++scopeSpaceCounter;
}

void resetFormalArgsOffset(){
    formalArgOffset = 0;
}

void resetFuncLocalsOffset(){
    functionLocalOffset = 0;
}

void restoreCurrScopeOffset(unsigned int i){
    switch(currScopeSpace()){
        case programvar:
            programVarOffset = i;
            break;
        case functionlocal:
            functionLocalOffset = i;
            break;
        case formalarg:
            formalArgOffset = i;
            break;
        default:
            assert(0);
    }
}


void expand(){
    assert(total==currQuad);
    quad* p = (quad*)malloc(NEW_SIZE);
    if(quads){
        memcpy(p,quads,CURR_SIZE);
        free(quads);
    }
    quads=p;
    total +=EXPAND_SIZE;
}

void emit(iopcode op, expr *arg1, expr *arg2, expr *result,unsigned int label , unsigned int line){
    /*allocate memory for new quad*/
    if(currQuad==total) expand();
    quad *p = quads + currQuad++;
    p->op=op;
    p->arg1=arg1;
    p->arg2=arg2;
    p->result=result;
    p->label=label;
    p->line=line; 
}


char* newtempname(){
    char* tempName =(char*)malloc(sizeof(char*));
    sprintf(tempName, "_t%d", tempcounter);
    tempName = strdup(tempName);
    tempcounter++;
    return tempName;
}

sym_t* newtemp(){
    char* newTemp = newtempname();
    sym_t *tmp1= put(newTemp,LOCAL_VAR,"VAR",0,curr_scope);
    return tmp1;
}

void resettemp(){
    /*called at the end of a stmt*/
    tempcounter=0;
}

int currscope(){
   
    return curr_scope;
}


sym_t* lookup(char* name, int scope){
     /*Look up symbol (name) at a given scope*/
}


struct Stack* newStack(int size){
    struct Stack *p;
    p = (struct Stack*)malloc(sizeof(struct Stack));
    p->top = -1;
    p->size = size;
    p->elems = (int*)malloc(sizeof(int) * size);
 
    return p;
}

int isEmpty(struct Stack* st){
    if(st->top == -1){
        return 1;
    }
    return 0;  
}

int isFull(struct Stack* st){
    if(st->top == st->size - 1) return 1;
    return 0; 
}

int stackSize(struct Stack* st){
    return st->top + 1;
}

int pop(struct Stack* st){
     if (!isEmpty(st)){
        return st->elems[st->top--];
     }else{
         return -1;
     }
}

void push(struct Stack* st,int elem){
    if (!isFull(st)){
         st->elems[++st->top] = elem;
    }
}

expr* newExpr(expr_t t){
    expr* e = (expr*)malloc(sizeof(expr));
    memset(e,0,sizeof(expr));
    e->type=t;
    return e;
}

expr* newExpr_constString(char* s){

    expr* e = newExpr(conststring_e);
    e->strConst=strdup(s);

    return e;
}

expr* newExpr_constBool( int b){
    expr* e = newExpr(constbool_e);
    if(b==1){
        e->boolConst='1';
    }else{
        e->boolConst='0';
    }
    return e;
}

expr* num_expr(double i){
  expr* e = newExpr(constnum_e);
  e->numConst=i;
  return e;
}

expr* lvalue_expr(sym_t* s){
    /*Make lvalue expr out of a symbol
    access type from symbol*/
    assert(s);
    expr* e = (expr*)malloc(sizeof(expr));
    memset(e,0,sizeof(expr));
    e->next=(expr*)0;
    e->sym=s;
    switch (s->type)
    {
        case LOCAL_VAR: e->type=var_e; break;
        case FORMAL_ARG: e->type=var_e; break;
        case GLOBAL: e->type=var_e; break;
        case USERF: e->type = programfunc_e; break;
        case LIB: e->type = libraryfunc_e; break;
        /*default: assert(0);*/
    }

    return e;
    
}


void convert2Bool(expr* e){
    //expr* newEx = newExpr(constbool_e);
    if(e->type == constnum_e){
        if(e->numConst == 0){
            e->boolConst = '0';
        }else{
            e->boolConst = '1';
        }
    }else if(e->type == programfunc_e || e->type == libraryfunc_e || e->type == newtable_e || e->type == tableitem_e){
        e->boolConst = '1';
    }else if(e->type == nil_e){
        e->boolConst = '0';
    }else if(e->type == conststring_e){
        if(!(strcmp(e->strConst, ""))){
            e->boolConst = '1';
        }else{
            e->boolConst = '0';
        }
    }
    
}


expr* emit_ifTableItem(expr* e){
    if(e->type != tableitem_e){
        return e;
    }else{
        expr* result = newExpr(var_e);
        result->sym=newtemp();
      emit(
          tablegetelem,
          e,
          e->index,
          result,
          NULL,
          NULL
          /*tmp null den kserw ti tha mpei*/
      );
      return result;
    }
    
}

expr* member_item (expr* lv, char* name) {
    lv = emit_ifTableItem(lv); // Emit code if r-value use of table item expr* ti = newexpr(tableitem_e); // Make a new expression
    expr* ti = newExpr(tableitem_e);
    ti->sym = lv->sym;
    ti->index = newExpr_constString(name); // Const string index return ti;
    return ti;
}

 /* new temp function name ,hidden vars*/
char* newTempFuncName(){
    char* name;
    name = (char*)malloc(sizeof(char*));
    sprintf(name, "_f%d", tmp_func);
    name = strdup(name);
    tmp_func++;
    return name;
}

void patchLabel(unsigned int quadNo,unsigned int label){
    assert(quadNo <currQuad); 
    assert(!quads[quadNo].label);
    quads[quadNo].label=label;
}

unsigned int nextQuad (void){return currQuad;}


expr* reverse_elist(expr* elist){
    expr* tmp=NULL;
    expr* oldlist=elist;
    expr* newlist=NULL;
    while(oldlist){
        tmp=newlist;
        newlist=oldlist;
        oldlist=oldlist->next;
        newlist->next=tmp;
    }
    return newlist;
}

expr* make_call(expr* lv, expr* reversed_elist, unsigned int line){
    expr* func = emit_ifTableItem(lv);
    while(reversed_elist){
        emit(param,NULL,NULL,reversed_elist,nextQuad(),line);
        reversed_elist=reversed_elist->next;
    }
    emit (call,NULL,NULL,func,nextQuad(),line);
    expr* result = newExpr(var_e);
    result->sym= newtemp();
    printf("Make call type result %u\n",result->type);
    emit(getretval,NULL,NULL,result,nextQuad(),line);
    return result;
}

void check_arith(expr* e, int line){
    if(e->type == constbool_e||
    e->type == conststring_e||
    e->type == nil_e||
    e->type == newtable_e||
    e->type == programfunc_e||
    e->type == libraryfunc_e||
    e->type == boolexpr_e) printf("Illegsl expr used in %d!\n",line); //itan fprintf gia na pigainei sto file alla eixe warning
}


stmt_t* make_stmt(stmt_t* s){
    s=(stmt_t*)malloc(sizeof(stmt_t));
    s->breakList=0;
    s->contList=0;
    return s;
}

int newList(int i){
    quads[i].label=0;
    return i;
}

int mergeList(int l1, int l2){
    if(!l1){
        return l2;
    }else{
        if(!l2){
            return l1;
        }else{
            int i=l1;
            while(quads[i].label){
                i=quads[i].label;
            }
            quads[i].label=l2;
            return l1;
        }
    }
}

list* mergeBackPatch(list* list1, list *list2){
    assert(list1);
while(list1->next)
{
    list1 = list1->next;
}
list1->next = list2;

return list1;
}

list * makeList(unsigned int quad)
{
    list *newList=(list*)malloc(sizeof(list));
    newList->label = quad;
    newList->next = NULL;
    return newList;

}

void patchList (int list,int label){
    while(list!=-1){
        int next = quads[list].label;
        quads[list].label=label;
        list=next;
    }
}

void backPatch(list* list, int label){

    while(list)
    {
      
        quads[list->label].label = label;
            
        list = list->next;
    }

}



/*list of scopese*/
sym_t *list_head=NULL;


/**/
void newDummyScope(int scope)
{
    sym_t *newScope, * tmpScope = head_of_scope;
    int found = 0;
    while(tmpScope->next!= NULL)
    {
        if(tmpScope->scope == scope)
       { found = 1;break;}
  
        tmpScope = tmpScope->next;
       
       
    }
    if(found==0 && tmpScope->scope != scope){
        newScope= malloc(sizeof(sym_t));
        newScope->scope = scope;
        newScope->next = NULL;
        newScope->scope_next = NULL;
        newScope->prev = tmpScope;    
        tmpScope->next = newScope;
    }
}

void print_output(){
    enum SymbolType type;
    sym_t *curr= head_of_scope;
    sym_t *curr2;

    while(curr){
         printf("\x1B[32m" "---------------SCOPE #%d ",curr->scope);
         printf("-----------------\n" "\x1B[0m");
        curr2=curr->scope_next;
         while(curr2){

             if(curr2->type==LIB){
               printf("\"%s\" [%s] (line: %d) (scope: %d)\n",curr2->name,"LIB FUNCTION",curr2->line,curr2->scope);
             }else if(curr2->type==USERF){
               printf("\"%s\" [%s] (line: %d) (scope: %d)\n",curr2->name,"USER FUNCTION",curr2->line,curr2->scope);

             }else if(curr2->type==GLOBAL){
                  if(curr2->category=="FUNC"){
                        printf("\"%s\" [%s] (line: %d) (scope: %d)\n",curr2->name,"GLOBAL FUNCTION",curr2->line,curr2->scope);
                    }else{
                    printf("\"%s\" [%s] (line: %d) (scope: %d)\n",curr2->name,"GLOBAL VARIABLE",curr2->line,curr2->scope);
                        }

             }else if(curr2->type==LOCAL_VAR){
                 printf("\"%s\" [%s] (line: %d) (scope: %d)\n",curr2->name,"LOCAL VARIABLE",curr2->line,curr2->scope);
             }else if(curr2->type==FORMAL_ARG){
                 printf("\"%s\" [%s] (line: %d) (scope: %d)\n",curr2->name,"FORMAL ARGUMENT",curr2->line,curr2->scope);
             }
             curr2=curr2->scope_next;
         }

         curr=curr->next;

    }

}

void deactivate(int scope){
    //only variable deactivation: LOCAL_VAR,FORMAL_ARG
    //search scope list and modify isActive flag
    //iterate from scope 1 ++ , globals can't be deactivated/
    sym_t *lookScope;
    sym_t *lookInScope;
    lookScope = head_of_scope;

    if(scope == 0) return;

    while(lookScope->scope!=scope && lookScope->next){
         lookScope=lookScope->next;
    }
    
    if(lookScope->scope==scope){
        lookInScope=lookScope->scope_next;
            while(lookInScope){
                lookInScope->isActive=0;
                lookInScope=lookInScope->scope_next;
        }
    }

}

int is_Function(char *name,int scope){
    //printf("pira name %s\n",name);
    int i = 0;
    sym_t *dummyNode;
    sym_t *lookInScope;
    dummyNode = head_of_scope;

    while(dummyNode->next && dummyNode->scope!=scope){
        dummyNode=dummyNode->next;
    }

    //an den uparxei to scope (apokleietai alla gia asfaleia to tsekarw)    
    if(dummyNode->scope!=scope){
        printf("den uparxei to scope auto");
        return 5;
    } 

    while(dummyNode){
        lookInScope=dummyNode->scope_next;
        while(lookInScope){
                if(strcmp(lookInScope->name,name)==0 && lookInScope->type==LIB) return 0;
                if(strcmp(lookInScope->name,name)==0 &&  (strcmp(lookInScope->category,"FUNC")==0) && lookInScope->isActive==1) return 0;
                if(strcmp(lookInScope->name,name)==0 && lookInScope->isActive==1) return 1; //to brika alla den einai function giati an itan func tha eixe kanei return
                lookInScope=lookInScope->scope_next;
        }
        dummyNode=dummyNode->prev;
    }
    return 1;
}

sym_t * lookup_LocalVar(int scope , char *name, int typeEnum,int line){
    sym_t *dummyNode;
    sym_t *lookInScope;
    sym_t* found=NULL;
    dummyNode = head_of_scope;

    while(dummyNode->next && dummyNode->scope!=scope){
        dummyNode=dummyNode->next;
    }

    lookInScope=dummyNode->scope_next;
    while(lookInScope){
        if(strcmp(lookInScope->name,name)==0 && lookInScope->type==LIB){ 
            return NULL; //error
        }else if(strcmp(lookInScope->name,name)==0 && strcmp(lookInScope->category,"FUNC")==0 && lookInScope->isActive==1){
                found=lookInScope;
        }else if(strcmp(lookInScope->name,name)==0 && strcmp(lookInScope->category,"VAR")==0 && lookInScope->isActive==1){
                found=lookInScope;
        }        
        lookInScope=lookInScope->scope_next;
    }
    
    if(found==NULL){
        if(scope==0){
            return put(name,GLOBAL,"VAR",line,scope);
        }else{
            return put(name,LOCAL_VAR,"VAR",line,scope);
        }
    }
    return found;
}



int lookup_Formal(int scope, char *name, int typeEnum,int line){
    sym_t *lookScope;
    sym_t *lookInScope;
    //psaxnw gia libs
    lookScope = head_of_scope;
    lookInScope=lookScope->scope_next;

    while(lookInScope){
        if(strcmp(lookInScope->name,name)==0 && lookInScope->type==LIB) return 1 ;
            lookInScope=lookInScope->scope_next;
    }

    //psaxnw an exoun idi dilothei
    lookScope = head_of_scope;
    while(lookScope->scope!=scope && lookScope->next){
         lookScope=lookScope->next;
    }
    
    if(lookScope->scope==scope){
        lookInScope=lookScope->scope_next;
            while(lookInScope){
                if(strcmp(lookInScope->name,name)==0 && lookInScope->isActive==1) return 2;
                lookInScope=lookInScope->scope_next;
            }
    }
    put(name,FORMAL_ARG,"VAR",line,scope);
    return 0;
}


sym_t * lookup_GlblVar(char *name){
    //can't have access to outer function formals , locals.
    //function var has same name as func previously declared.
    //if scope == 0 , check if global ::x exists 
    sym_t *lookScope;
    sym_t *lookInScope;
    lookScope = head_of_scope;
    lookInScope=lookScope->scope_next;

    while(lookInScope){
                if(strcmp(lookInScope->name,name)==0 && lookInScope->type==GLOBAL) return lookInScope ;
                if(strcmp(lookInScope->name,name)==0 && lookInScope->type==LIB) return lookInScope ;
                if(strcmp(lookInScope->name,name)==0 && lookInScope->type==USERF) return lookInScope ;

                lookInScope=lookInScope->scope_next;
            }
    return NULL;
}

//funcdef
int lookup_FuncDef(int scope, char* name, int type ,int line){
    //type 0 gia id 1 gia func decl 2 gia func call
    //returns: 0-ola kala 1-libFunction 2-Var and Func same name 3-Out of Bounds 4-Function Redeclaration
    int i=0;
    sym_t *dummyNode;
    sym_t *lookInScope;
    dummyNode = head_of_scope;

    while( dummyNode->scope!=scope  && dummyNode->next){
        dummyNode=dummyNode->next;
    }

    lookInScope=dummyNode->scope_next;
    while(lookInScope){
        if(strcmp(lookInScope->name,name)==0 && lookInScope->type==LIB){
                return 1; //error
        }else if(strcmp(lookInScope->name,name)==0 && strcmp(lookInScope->category,"FUNC")==0 && lookInScope->isActive==1){
                 return 4; //error
        }else if(strcmp(lookInScope->name,name)==0 && strcmp(lookInScope->category,"VAR")==0 && lookInScope->isActive==1){
                 return 2; //error
        }
         lookInScope=lookInScope->scope_next;
     }


    return 0;
}

unsigned int istempname (char* s) {
return *s == '_';
}

unsigned int istempexpr (expr* e) {
return e->sym && istempname(e->sym->name);
}


sym_t* lookup_X(int scope, char* name, int type ,int line)
{
    int funcBetween=0, foundVar=0, foundFunc=0, found=0;
    sym_t *dummyNode = head_of_scope, *lookInScope;

      while( (dummyNode->scope != scope)&&(dummyNode->next) ){
         dummyNode=dummyNode->next;
     }
    //Seg ?
     while(dummyNode!=NULL)
     {
        lookInScope = dummyNode->scope_next;
        while(lookInScope)
        {
            
            //to vrika sto scope mou h sto 0 ara oti kai na vrw einai ok
            if(dummyNode->scope == scope || dummyNode->scope == 0)
            {
                if(strcmp(lookInScope->name,name)==0 && strcmp(lookInScope->category,"FUNC")==0 && lookInScope->isActive==1){
                return lookInScope;
                } 
                if(strcmp(lookInScope->name,name)==0 && strcmp(lookInScope->category,"VAR")==0 && lookInScope->isActive==1){
                return lookInScope;
                } 
              
                if(strcmp(lookInScope->name,name)==0 && lookInScope->type==LIB){
                return lookInScope; 
                } 

            //se apo eksw scope
            }else{

                if(strcmp(lookInScope->category,"FUNC")==0) funcBetween=1;
                if(strcmp(lookInScope->name,name)==0 && strcmp(lookInScope->category,"FUNC")==0 && lookInScope->isActive==1){
                    foundFunc=1;
                    return lookInScope;
                    } 
                if(strcmp(lookInScope->name,name)==0 && strcmp(lookInScope->category,"VAR")==0 && lookInScope->isActive==1){
                   foundVar=1;
                   return lookInScope;
                } 
            }
            lookInScope=lookInScope->scope_next;
        }
       
        dummyNode = dummyNode->prev;
    }

    //ama vrethike tote elegxw ama uparxei func in between
    if(foundFunc==1 || foundVar ==1){
        if(funcBetween==1)
        {
            if(foundFunc==1) return NULL;  // auta ta null einai lathos, den kseroume pws na epistrefoume me fun in between
            else{
                return NULL;//error var with func in between
            }
        }
    return NULL;//den eixa func in between ara eite vrhka var eite func ola komple 
    }
    //ama de vrethike tote kanw put
    else{
        if(scope==0){
            return put(name,GLOBAL,"VAR",line,scope);
        }else{
            return put(name,LOCAL_VAR,"VAR",line,scope);
        }
        return NULL;
    }
}

void print_quads(FILE* f){	
    int i;
    fprintf(f,"\n----INTERMEDIATE CODE  ----\n");
        for(i=0;i < nextQuad() ; i++){
            if((quads+i)->op == add){
                if( ((quads+i)->arg1->type) == constnum_e && ((quads+i)->arg2->type) == constnum_e){
                    fprintf(f, "%d: ADD %s %d %d LINE: %d\n",i, (quads+i)->result->sym->name, (int)((quads+i)->arg1->numConst), (int)((quads+i)->arg2->numConst), (quads+i)->line);
                }else if( ((quads+i)->arg1->type) == constnum_e){
                    fprintf(f, "%d: ADD %s %d %s LINE: %d\n",i, (quads+i)->result->sym->name, (int)((quads+i)->arg1->numConst), (quads+i)->arg2->sym->name, (quads+i)->line);
                }else if( ((quads+i)->arg2->type) == constnum_e){
                    fprintf(f, "%d: ADD %s %s %d LINE: %d\n",i, (quads+i)->result->sym->name, (quads+i)->arg1->sym->name, (int)((quads+i)->arg2->numConst), (quads+i)->line);
                }else{
                    fprintf(f, "%d: ADD %s %s %s LINE: %d\n",i, (quads+i)->result->sym->name, (quads+i)->arg1->sym->name, (quads+i)->arg2->sym->name, (quads+i)->line);

                }
            }else if((quads+i)->op == sub){
                if( ((quads+i)->arg1->type) == constnum_e && ((quads+i)->arg2->type) == constnum_e){
                    fprintf(f, "%d: SUB %s %d %d LINE: %d\n",i, (quads+i)->result->sym->name, (int)((quads+i)->arg1->numConst), (int)((quads+i)->arg2->numConst), (quads+i)->line);
                }else if( ((quads+i)->arg1->type) == constnum_e){
                    fprintf(f, "%d: SUB %s %d %s LINE: %d\n",i, (quads+i)->result->sym->name, (int)((quads+i)->arg1->numConst), (quads+i)->arg2->sym->name, (quads+i)->line);
                }else if( ((quads+i)->arg2->type) == constnum_e){
                    fprintf(f, "%d: SUB %s %s %d LINE: %d\n",i, (quads+i)->result->sym->name, (quads+i)->arg1->sym->name, (int)((quads+i)->arg2->numConst), (quads+i)->line);
                }else{
                    fprintf(f, "%d: SUB %s %s %s LINE: %d\n",i, (quads+i)->result->sym->name, (quads+i)->arg1->sym->name, (quads+i)->arg2->sym->name, (quads+i)->line);

                }
            }else if((quads+i)->op == mul){
                if( ((quads+i)->arg1->type) == constnum_e && ((quads+i)->arg2->type) == constnum_e){
                    fprintf(f, "%d: MUL %s %d %d LINE: %d\n",i, (quads+i)->result->sym->name, (int)((quads+i)->arg1->numConst), (int)((quads+i)->arg2->numConst), (quads+i)->line);
                }else if( ((quads+i)->arg1->type) == constnum_e){
                    fprintf(f, "%d: MUL %s %d %s LINE: %d\n",i, (quads+i)->result->sym->name, (int)((quads+i)->arg1->numConst), (quads+i)->arg2->sym->name, (quads+i)->line);
                }else if( ((quads+i)->arg2->type) == constnum_e){
                    fprintf(f, "%d: MUL %s %s %d LINE: %d\n",i, (quads+i)->result->sym->name, (quads+i)->arg1->sym->name, (int)((quads+i)->arg2->numConst), (quads+i)->line);
                }else{
                    fprintf(f, "%d: MUL %s %s %s LINE: %d\n",i, (quads+i)->result->sym->name, (quads+i)->arg1->sym->name, (quads+i)->arg2->sym->name, (quads+i)->line);

                }
            }else if((quads+i)->op == _div){
                if( ((quads+i)->arg1->type) == constnum_e && ((quads+i)->arg2->type) == constnum_e){
                    fprintf(f, "%d: DIV %s %d %d LINE: %d\n",i, (quads+i)->result->sym->name, (int)((quads+i)->arg1->numConst), (int)((quads+i)->arg2->numConst), (quads+i)->line);
                }else if( ((quads+i)->arg1->type) == constnum_e){
                    fprintf(f, "%d: DIV %s %d %s LINE: %d\n",i, (quads+i)->result->sym->name, (int)((quads+i)->arg1->numConst), (quads+i)->arg2->sym->name, (quads+i)->line);
                }else if( ((quads+i)->arg2->type) == constnum_e){
                    fprintf(f, "%d: DIV %s %s %d LINE: %d\n",i, (quads+i)->result->sym->name, (quads+i)->arg1->sym->name, (int)((quads+i)->arg2->numConst), (quads+i)->line);
                }else{
                    fprintf(f, "%d: DIV %s %s %s LINE: %d\n",i, (quads+i)->result->sym->name, (quads+i)->arg1->sym->name, (quads+i)->arg2->sym->name, (quads+i)->line);

                }
            }else if((quads+i)->op == mod){
                if( ((quads+i)->arg1->type) == constnum_e && ((quads+i)->arg2->type) == constnum_e){
                    fprintf(f, "%d: MOD %s %d %d LINE: %d\n",i, (quads+i)->result->sym->name, (int)((quads+i)->arg1->numConst), (int)((quads+i)->arg2->numConst), (quads+i)->line);
                }else if( ((quads+i)->arg1->type) == constnum_e){
                    fprintf(f, "%d: MOD %s %d %s LINE: %d\n",i, (quads+i)->result->sym->name, (int)((quads+i)->arg1->numConst), (quads+i)->arg2->sym->name, (quads+i)->line);
                }else if( ((quads+i)->arg2->type) == constnum_e){
                    fprintf(f, "%d: MOD %s %s %d LINE: %d\n",i, (quads+i)->result->sym->name, (quads+i)->arg1->sym->name, (int)((quads+i)->arg2->numConst), (quads+i)->line);
                }else{
                    fprintf(f, "%d: MOD %s %s %s LINE: %d\n",i, (quads+i)->result->sym->name, (quads+i)->arg1->sym->name, (quads+i)->arg2->sym->name, (quads+i)->line);

                }
            }else if((quads+i)->op == if_less){
                if( ((quads+i)->arg1->type) == constnum_e && ((quads+i)->arg2->type) == constnum_e ){
                    fprintf(f, "%d: IF LESS %d %d LABEL: %d LINE: %d\n",i, (int)((quads+i)->arg1->numConst), (int)((quads+i)->arg2->numConst),(quads+i)->label ,(quads+i)->line);

                }else if ((quads+i)->arg1->type == constnum_e ) {
                    fprintf(f, "%d: IF LESS %d %s LABEL: %d LINE: %d\n",i, (int)((quads+i)->arg1->numConst), ((quads+i)->arg2->sym->name),(quads+i)->label ,(quads+i)->line);
                 
                }else if( (quads+i)->arg2->type == constnum_e ){
                    fprintf(f, "%d: IF LESS %s %d LABEL: %d LINE: %d\n",i, ((quads+i)->arg1->sym->name), (int)((quads+i)->arg2->numConst),(quads+i)->label ,(quads+i)->line);
                }else{
                    fprintf(f, "%d: IF LESS %s %s LABEL: %d LINE: %d\n",i, ((quads+i)->arg1->sym->name), ((quads+i)->arg2->sym->name),(quads+i)->label ,(quads+i)->line);
                }
            }else if((quads+i)->op == if_greatereq){
               if( ((quads+i)->arg1->type) == constnum_e && ((quads+i)->arg2->type) == constnum_e ){
                    fprintf(f, "%d: IF GREATEQ %d %d LABEL: %d LINE: %d\n",i, (int)((quads+i)->arg1->numConst), (int)((quads+i)->arg2->numConst),(quads+i)->label ,(quads+i)->line);

                }else if ((quads+i)->arg1->type == constnum_e ) {
                    fprintf(f, "%d: IF GREATEQ %d %s LABEL: %d LINE: %d\n",i, (int)((quads+i)->arg1->numConst), ((quads+i)->arg2->sym->name),(quads+i)->label ,(quads+i)->line);
                 
                }else if( (quads+i)->arg2->type == constnum_e ){
                    fprintf(f, "%d: IF GREATEQ %s %d LABEL: %d LINE: %d\n",i, ((quads+i)->arg1->sym->name), (int)((quads+i)->arg2->numConst),(quads+i)->label ,(quads+i)->line);
                }else{
                    fprintf(f, "%d: IF GREATEQ %s %s LABEL: %d LINE: %d\n",i, ((quads+i)->arg1->sym->name), ((quads+i)->arg2->sym->name),(quads+i)->label ,(quads+i)->line);
                }
            }else if((quads+i)->op == if_eq){
                if(((quads+i)->arg1->type) == constnum_e){
                    if(((quads+i)->arg2->type) == constnum_e){
                        fprintf(f, "%d: IF EQ %d %d LABEL: %d LINE: %d\n",i, (int)((quads+i)->arg1->numConst), (int)((quads+i)->arg2->numConst),(quads+i)->label ,(quads+i)->line);
                    }else if((quads+i)->arg2->type == constbool_e){
                        fprintf(f, "%d: IF EQ %d %c LABEL: %d LINE: %d\n",i, (int)((quads+i)->arg1->numConst), ((quads+i)->arg2->boolConst), (quads+i)->label ,(quads+i)->line);
                    }else if((quads+i)->arg2->type == conststring_e ){
                        fprintf(f, "%d: IF EQ %d %s LABEL: %d LINE: %d\n",i, (int)((quads+i)->arg1->numConst), ((quads+i)->arg2->strConst), (quads+i)->label ,(quads+i)->line);
                    }else{
                        fprintf(f, "%d: IF EQ %d %s LABEL: %d LINE: %d\n",i, (int)((quads+i)->arg1->numConst), ((quads+i)->arg2->sym->name), (quads+i)->label ,(quads+i)->line);
                    }
                }else if(((quads+i)->arg1->type) == constbool_e ){
                    if(((quads+i)->arg2->type) == constnum_e){
                        fprintf(f, "%d: IF EQ %c %d LABEL: %d LINE: %d\n",i, (int)((quads+i)->arg1->boolConst), (int)((quads+i)->arg2->numConst),(quads+i)->label ,(quads+i)->line);
                    }else if((quads+i)->arg2->type == constbool_e ){
                        fprintf(f, "%d: IF EQ %c %c LABEL: %d LINE: %d\n",i, (int)((quads+i)->arg1->boolConst), ((quads+i)->arg2->boolConst), (quads+i)->label ,(quads+i)->line);
                    }else if((quads+i)->arg2->type == conststring_e){
                        fprintf(f, "%d: IF EQ %c %s LABEL: %d LINE: %d\n",i, (int)((quads+i)->arg1->boolConst), ((quads+i)->arg2->strConst), (quads+i)->label ,(quads+i)->line);
                    }else{
                        fprintf(f, "%d: IF EQ %c %s LABEL: %d LINE: %d\n",i, (int)((quads+i)->arg1->boolConst), ((quads+i)->arg2->sym->name), (quads+i)->label ,(quads+i)->line);
                    }
                }else if(((quads+i)->arg1->type) == conststring_e){
                    if(((quads+i)->arg2->type) == constnum_e){
                        fprintf(f, "%d: IF EQ %s %d LABEL: %d LINE: %d\n",i, ((quads+i)->arg1->strConst), (int)((quads+i)->arg2->numConst),(quads+i)->label ,(quads+i)->line);
                    }else if((quads+i)->arg2->type == constbool_e  ){
                        fprintf(f, "%d: IF EQ %s %c LABEL: %d LINE: %d\n",i, ((quads+i)->arg1->strConst), ((quads+i)->arg2->boolConst), (quads+i)->label ,(quads+i)->line);
                    }else if((quads+i)->arg2->type == conststring_e){
                        fprintf(f, "%d: IF EQ %s %s LABEL: %d LINE: %d\n",i, ((quads+i)->arg1->strConst), ((quads+i)->arg2->strConst), (quads+i)->label ,(quads+i)->line);
                    }else{
                        fprintf(f, "%d: IF EQ %s %s LABEL: %d LINE: %d\n",i, ((quads+i)->arg1->strConst), ((quads+i)->arg2->sym->name), (quads+i)->label ,(quads+i)->line);
                    }
                }else if(((quads+i)->arg1->type) == var_e){
                    if(((quads+i)->arg2->type) == constnum_e){
                        fprintf(f, "%d: IF EQ %s %d LABEL: %d LINE: %d\n",i, ((quads+i)->arg1->sym->name), (int)((quads+i)->arg2->numConst),(quads+i)->label ,(quads+i)->line);
                    }else if((quads+i)->arg2->type == constbool_e  ){
                        fprintf(f, "%d: IF EQ %s %c LABEL: %d LINE: %d\n",i, ((quads+i)->arg1->sym->name), ((quads+i)->arg2->boolConst), (quads+i)->label ,(quads+i)->line);
                    }else if((quads+i)->arg2->type == conststring_e){
                        fprintf(f, "%d: IF EQ %s %s LABEL: %d LINE: %d\n",i, ((quads+i)->arg1->sym->name), ((quads+i)->arg2->strConst), (quads+i)->label ,(quads+i)->line);
                    }else{
                        fprintf(f, "%d: IF EQ %s %s LABEL: %d LINE: %d\n",i, ((quads+i)->arg1->sym->name), ((quads+i)->arg2->sym->name), (quads+i)->label ,(quads+i)->line);
                    }
                }else{
                    if(((quads+i)->arg2->sym)!=NULL)
                    {
                    fprintf(f, "%d: IF EQ %s %s LABEL: %d LINE: %d\n",i, ((quads+i)->arg1->sym->name), ((quads+i)->arg2->sym->name),(quads+i)->label ,(quads+i)->line);

                    }else
                  {  fprintf(f, "%d: IF EQ %s %c LABEL: %d LINE: %d\n",i, ((quads+i)->arg1->sym->name), ((quads+i)->arg2->boolConst),(quads+i)->label ,(quads+i)->line);}
                }
            }else if((quads+i)->op == if_greater){
                if( ((quads+i)->arg1->type) == constnum_e && ((quads+i)->arg2->type) == constnum_e ){
                    fprintf(f, "%d: IF GREATER %d %d LABEL: %d LINE: %d\n",i, (int)((quads+i)->arg1->numConst), (int)((quads+i)->arg2->numConst),(quads+i)->label ,(quads+i)->line);

                }else if ((quads+i)->arg1->type == constnum_e ) {
                    fprintf(f, "%d: IF GREATER %d %s LABEL: %d LINE: %d\n",i, (int)((quads+i)->arg1->numConst), ((quads+i)->arg2->sym->name),(quads+i)->label ,(quads+i)->line);
                 
                }else if( (quads+i)->arg2->type == constnum_e ){
                    fprintf(f, "%d: IF GREATER %s %d LABEL: %d LINE: %d\n",i, ((quads+i)->arg1->sym->name), (int)((quads+i)->arg2->numConst),(quads+i)->label ,(quads+i)->line);
                }else{
                    fprintf(f, "%d: IF GREATER %s %s LABEL: %d LINE: %d\n",i, ((quads+i)->arg1->sym->name), ((quads+i)->arg2->sym->name),(quads+i)->label ,(quads+i)->line);
                }
            }else if((quads+i)->op == if_lesseq){
                if( ((quads+i)->arg1->type) == constnum_e && ((quads+i)->arg2->type) == constnum_e ){
                    fprintf(f, "%d: IF LESSEQ %d %d LABEL: %d LINE: %d\n",i, (int)((quads+i)->arg1->numConst), (int)((quads+i)->arg2->numConst),(quads+i)->label ,(quads+i)->line);

                }else if ((quads+i)->arg1->type == constnum_e ) {
                    fprintf(f, "%d: IF LESSEQ %d %s LABEL: %d LINE: %d\n",i, (int)((quads+i)->arg1->numConst), ((quads+i)->arg2->sym->name),(quads+i)->label ,(quads+i)->line);
                 
                }else if( (quads+i)->arg2->type == constnum_e ){
                    fprintf(f, "%d: IF LESSEQ %s %d LABEL: %d LINE: %d\n",i, ((quads+i)->arg1->sym->name), (int)((quads+i)->arg2->numConst),(quads+i)->label ,(quads+i)->line);
                }else{
                    fprintf(f, "%d: IF LESSEQ %s %s LABEL: %d LINE: %d\n",i, ((quads+i)->arg1->sym->name), ((quads+i)->arg2->sym->name),(quads+i)->label ,(quads+i)->line);
                }         
                
            }else if((quads+i)->op == if_noteq){
               if( ((quads+i)->arg1->type) == constnum_e && ((quads+i)->arg2->type) == constnum_e ){
                    fprintf(f, "%d: IF NOTEQ %d %d LABEL: %d LINE: %d\n",i, (int)((quads+i)->arg1->numConst), (int)((quads+i)->arg2->numConst),(quads+i)->label ,(quads+i)->line);

                }else if ((quads+i)->arg1->type == constnum_e ) {
                    fprintf(f, "%d: IF NOTEQ %d %s LABEL: %d LINE: %d\n",i, (int)((quads+i)->arg1->numConst), ((quads+i)->arg2->sym->name),(quads+i)->label ,(quads+i)->line);
                 
                }else if( (quads+i)->arg2->type == constnum_e ){
                    fprintf(f, "%d: IF NOTEQ %s %d LABEL: %d LINE: %d\n",i, ((quads+i)->arg1->sym->name), (int)((quads+i)->arg2->numConst),(quads+i)->label ,(quads+i)->line);
                }else{
                    fprintf(f, "%d: IF NOTEQ %s %s LABEL: %d LINE: %d\n",i, ((quads+i)->arg1->sym->name), ((quads+i)->arg2->sym->name),(quads+i)->label ,(quads+i)->line);
                }
            }else if((quads+i)->op == and){
                if( ((quads+i)->arg1->type) == arithexpr_e){
                    fprintf(f, "%d: AND %s %d LINE: %d\n",i, (quads+i)->result->sym->name, (int)((quads+i)->arg1->numConst), (quads+i)->line);
                }
            }else if((quads+i)->op == or){
                if( ((quads+i)->arg1->type) == constnum_e){
                    fprintf(f, "%d: OR %s %d LINE: %d\n",i, (quads+i)->result->sym->name, (int)((quads+i)->arg1->numConst), (quads+i)->line);
                }
            }else if((quads+i)->op == jump){
                
                    fprintf(f, "%d: JUMP  %d \n",i,(int)((quads+i)->label));
                
            }
            else if((quads+i)->op == funcstart ){
                     
                fprintf(f, "%d: FUNCSTART %s LINE: %d\n",i, (quads+i)->arg1->sym->name, (quads+i)->line);
            }else if((quads+i)->op == funcend){
                       
                    fprintf(f, "%d: FUNCEND %s LINE: %d\n",i, (quads+i)->arg1->sym->name, (quads+i)->line);
            }else if( (quads+i)->op == call){
                fprintf(f , "%d: CALL %s  LINE: %d\n", i, (quads+i)->arg1->sym->name , (quads+i)->line);
            }else if( (quads+i)->op == param){
                if(((quads+i)->arg1->type)==constnum_e){
                    fprintf(f, "%d: PARAM %d  LINE: %d\n",i,  (int)((quads+i)->arg1->numConst), (quads+i)->line);
                }else if(((quads+i)->arg1->type)==conststring_e){
                    fprintf(f, "%d: PARAM %s  LINE: %d\n",i,  (quads+i)->arg1->strConst, (quads+i)->line);
                }else if(((quads+i)->arg1->type)==constbool_e){
                    fprintf(f, "%d: PARAM %c  LINE: %d\n",i,  (quads+i)->arg1->boolConst, (quads+i)->line);
                }else if(((quads+i)->arg1->type)==nil_e){
                    fprintf(f, "%d: PARAM NULL LINE: %d\n",i,  (quads+i)->line);
                }else {
                    fprintf(f, "%d: PARAM  %s  LINE: %d\n",i,  (quads+i)->arg1->sym->name, (quads+i)->line);
                }
            }else if( (quads+i)->op == getretval){
            //    fprintf(f , "%d: GETRETVAL %s  LINE: %d\n", i, (quads+i)->arg1->sym->name , (quads+i)->line);
            }else if((quads+i)->op == uminus){
                fprintf(f, "%d: UMINUS %s %s  LINE: %d\n",i, (quads+i)->arg1->sym->name, (quads+i)->result->sym->name, (quads+i)->line);
            }else if( (quads+i)->op == assign){
                if(((quads+i)->arg1->type)==constnum_e){
                    fprintf(f, "%d: ASSIGN %s %d  LINE: %d\n",i, (quads+i)->result->sym->name, (int)((quads+i)->arg1->numConst), (quads+i)->line);
                }else if(((quads+i)->arg1->type)==conststring_e){
                    fprintf(f, "%d: ASSIGN %s %s  LINE: %d\n",i, (quads+i)->result->sym->name, (quads+i)->arg1->strConst, (quads+i)->line);
                }else if(((quads+i)->arg1->type)==constbool_e){
                    fprintf(f, "%d: ASSIGN %s %c  LINE: %d\n",i, (quads+i)->result->sym->name, (quads+i)->arg1->boolConst, (quads+i)->line);
                }else if(((quads+i)->arg1->type)==nil_e){
                    fprintf(f, "%d: ASSIGN %s NULL LINE: %d\n",i, (quads+i)->result->sym->name, (quads+i)->line);
                }else {
                    fprintf(f, "%d: ASSIGN %s %s  LINE: %d\n",i, (quads+i)->result->sym->name, (quads+i)->arg1->sym->name, (quads+i)->line);
                }
            }else if( (quads+i)->op == ret){
                if(((quads+i)->arg1)){
                    if(((quads+i)->arg1->type)==constnum_e){
                        fprintf(f, "%d: RET  %d  LINE: %d\n",i, (int)((quads+i)->arg1->numConst), (quads+i)->line);
                    }else if(((quads+i)->arg1->type)==conststring_e){
                        fprintf(f, "%d: RET  %s  LINE: %d\n",i, (quads+i)->arg1->strConst, (quads+i)->line);
                    }else if(((quads+i)->arg1->type)==constbool_e){
                        fprintf(f, "%d: RET %c  LINE: %d\n",i, (quads+i)->arg1->boolConst, (quads+i)->line);
                    }else if(((quads+i)->arg1->type)==nil_e){
                        fprintf(f, "%d: RET NULL LINE: %d\n",i, (quads+i)->line);
                    }else {
                        fprintf(f, "%d: RET %s LINE: %d\n",i, (quads+i)->arg1->sym->name, (quads+i)->line);
                    }
                }else{
                    fprintf(f, "%d: RET NULL LINE: %d\n",i, (quads+i)->line);
                }

            }else if((quads+i)->op == tablecreate){
                printf("table create\n");
		    fprintf(f, "%d: TABLE_CREATE %s LINE: %d\n",i, (quads+i)->arg1->sym->name, (quads+i)->line);
	    }else if((quads+i)->op == tablegetelem){
            
                    printf("eimai tablegetelem\n");
            if((quads+i)->arg2->type == var_e) {
                    printf("eimai tablegetelem var_e\n");

                fprintf(f, "%d: TABLE_GET_ELEMENT %s %s %s LINE: %d\n", i, (quads+i)->result->sym->name, (quads+i)->arg1->sym->name, (quads+i)->arg2->sym->name, (quads+i)->line);
            }else if((quads+i)->arg2->type == constnum_e){
                    printf("eimai tablegetelem constnum_e\n");

                fprintf(f, "%d: TABLE_GET_ELEMENT %s %s %d LINE: %d\n", i, (quads+i)->result->sym->name, (quads+i)->arg1->sym->name, (quads+i)->arg2->numConst, (quads+i)->line);
            }else if((quads+i)->arg2->type == constbool_e){
                    printf("eimai tablegetelem constbool_e\n");

                fprintf(f, "%d: TABLE_GET_ELEMENT %s %s %c LINE: %d\n", i, (quads+i)->result->sym->name, (quads+i)->arg1->sym->name, (quads+i)->arg2->boolConst, (quads+i)->line);
            }else if((quads+i)->arg2->type == conststring_e){
                    printf("eimai tablegetelem conststring_e\n");

                fprintf(f, "%d: TABLE_GET_ELEMENT arg1 %s  %s  %s LINE: %d\n", i, (quads+i)->result->sym->name, (quads+i)->arg1->sym->name, (quads+i)->arg2->strConst, (quads+i)->line);
            }else{
                    printf("eimai tablegetelem else\n");
                     fprintf(f, "%d: TABLE_GET_ELEMENT %s %s %s LINE: %d\n", i, (quads+i)->result->sym->name, (quads+i)->arg1->sym->name, (quads+i)->arg2->sym->name, (quads+i)->line);

            }
        
        }
        
        else if((quads+i)->op == tablesetelem){
            if((quads+i)->result->type == var_e ){
                 printf("eimai var\n");
                      printf("eimai var");
                if((quads+i)->arg2->type == var_e) {
                    fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %s %s LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->sym->name, (quads+i)->result->sym->name, (quads+i)->line);
                }  else if((quads+i)->arg2->type == conststring_e) {
                    fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %s %s LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->strConst, (quads+i)->result->sym->name, (quads+i)->line);
                }  else if((quads+i)->arg2->type == constnum_e) {
                    fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %d %s LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->numConst, (quads+i)->result->sym->name, (quads+i)->line);
                }else if((quads+i)->arg2->type == constbool_e) {
                    fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %c %s LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->boolConst, (quads+i)->result->sym->name, (quads+i)->line);
                }else{
                     fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %s %s LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->sym->name, (quads+i)->result->sym->name, (quads+i)->line);
                }
      }

            else if((quads+i)->result->type == conststring_e ){
                 printf("eimai conststring");

                if((quads+i)->arg2->type == var_e) {
                    fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %s %s LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->sym->name, (quads+i)->result->strConst, (quads+i)->line);
                }  else if((quads+i)->arg2->type == conststring_e) {
                    fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %s %s LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->strConst, (quads+i)->result->strConst, (quads+i)->line);
                }  else if((quads+i)->arg2->type == constnum_e) {
                    fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %d %s LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->numConst, (quads+i)->result->strConst, (quads+i)->line);
                }else if((quads+i)->arg2->type == constbool_e) {
                    fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %c %s LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->boolConst, (quads+i)->result->strConst, (quads+i)->line);
                }else{
                     fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %s %s LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->sym->name, (quads+i)->result->strConst, (quads+i)->line);
                }

            }else if((quads+i)->result->type == constbool_e ){
                    printf("eimai boolconst\n");

                if((quads+i)->arg2->type == var_e) {
                    fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %s %c LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->sym->name, (quads+i)->result->boolConst, (quads+i)->line);
                }  else if((quads+i)->arg2->type == conststring_e) {
                    fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %s %c LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->strConst, (quads+i)->result->boolConst, (quads+i)->line);
                }  else if((quads+i)->arg2->type == constnum_e) {
                    fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %d %c LINE: %d\n", i, (quads+i)->arg1->sym->name, (int)(quads+i)->arg2->numConst, (quads+i)->result->boolConst, (quads+i)->line);
                }else if((quads+i)->arg2->type == constbool_e) {
                    fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %c %c LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->boolConst, (quads+i)->result->boolConst, (quads+i)->line);
                }else{
                     fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %s %c LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->sym->name, (quads+i)->result->boolConst, (quads+i)->line);
                }
            }else if((quads+i)->result->type == constnum_e ){

                if((quads+i)->arg2->type == var_e) {
                     printf("eimai constnum_e var_e\n");
                    fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %s %d LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->sym->name, (int)(quads+i)->result->numConst, (quads+i)->line);
                }  else if((quads+i)->arg2->type == conststring_e) {
                     printf("eimai constnum_e conststring_e\n");
                    fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %s %d LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->strConst, (int)(quads+i)->result->numConst, (quads+i)->line);
                }  else if((quads+i)->arg2->type == constnum_e) {
                     printf("eimai constnum_e constnum_e\n");
                    fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %d %d LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->numConst, (int)(quads+i)->result->numConst, (quads+i)->line);
                }else if((quads+i)->arg2->type == constbool_e) {
                     printf("eimai constnum_e constbool_e\n");
                    fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %c %d LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->boolConst, (int)(quads+i)->result->numConst, (quads+i)->line);
                }else{
                     fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %s %d LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->sym->name, (int)(quads+i)->result->numConst, (quads+i)->line);
                }
            }
            
            else {

                if((quads+i)->arg2->type == var_e) {
                        printf("eimai else var_e\n");

                    fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %s %s LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->sym->name, (quads+i)->result->sym->name, (quads+i)->line);
                }  else if((quads+i)->arg2->type == conststring_e) {
                        printf("eimai else conststring_e\n");

                    fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %s %s LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->strConst, (quads+i)->result->sym->name, (quads+i)->line);
                }  else if((quads+i)->arg2->type == constnum_e) {
                        printf("eimai else constnum_e\n");

                    fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %d %s LINE: %d\n", i, (quads+i)->arg1->sym->name, (int)(quads+i)->arg2->numConst, (quads+i)->result->sym->name, (quads+i)->line);
                }else if((quads+i)->arg2->type == constbool_e) {
                        printf("eimai else constbool_e\n");

                    fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %c %s LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->boolConst, (quads+i)->result->sym->name, (quads+i)->line);
                }else{
                     fprintf(f, "%d: TABLE_SET_ELEMEMENT %s %s %s LINE: %d\n", i, (quads+i)->arg1->sym->name, (quads+i)->arg2->sym->name,(quads+i)->result->sym->name, (quads+i)->line);
                }
            }
            
        }        
    }
}

