#include<stdio.h>
#include <math.h>
#include <string.h>

#define AVM_STACKSIZE 4096
#define AVM_STACKENV_SIZE 4
#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))
#define AVM_TABLE_HASHSIZE 211
#define AVM_ENDING_PC codeSize
#define AVM_MAX_INSTRUCTIONS 24
#define AVM_NUMACTUALS_OFFSET +4
#define AVM_SAVEDPC_OFFSET +3
#define AVM_SAVEDTOP_OFFSET +2
#define AVM_SAVEDTOPSP_OFFSET +1
#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic
#define execute_jle execute_relational
#define execute_jlt execute_relational
#define execute_jgt execute_relational
#define execute_jge execute_relational

unsigned char executionFinished = 0;
unsigned pc =0;
unsigned currLine =0;
unsigned codeSize = 0;
unsigned totalActuals = 0;
char** stringArray;
double* numArray;
userfunc* userFArray;
char** libFuncsArray;
instruction* instructionsArray= (instruction*)0;
int totalGlobals = 0;
unsigned totalFuncs=0;
typedef void (*execute_func_t)(instruction*);

avm_memcell stack[AVM_STACKSIZE];

typedef struct avm_table_bucket {
    avm_memcell key;
    avm_memcell value;
    struct avm_table_bucket* next;
} avm_table_bucket;

typedef struct avm_table {
    unsigned refCounter;
    avm_table_bucket* strIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* numIndexed[AVM_TABLE_HASHSIZE];
    unsigned total;
} avm_table;


typedef void (*library_func_t)(void);

library_func_t lib_table[11];


int libHash_func(char* id) {
      if(!strcmp(id,"print")) return 0; 
	  if(!strcmp(id,"typeof")) return 1; 
	  if(!strcmp(id,"sqrt")) return 2; 
	  if(!strcmp(id,"objectmemberkeys")) return 3; 
	  if(!strcmp(id,"objecttotalmembers")) return 4; 
	  if(!strcmp(id,"objectcopy")) return 5;
	  if(!strcmp(id,"totalarguments")) return 6; 
	  if(!strcmp(id,"argument")) return 7; 
	  if(!strcmp(id,"strtonum")) return 8; 
	  if(!strcmp(id,"cos")) return 9; 
	  if(!strcmp(id,"sin")) return 10; 
}

avm_memcell ax, bx, cx;
avm_memcell retval;
unsigned top, topsp;


void avm_warning(char* format,char* arg1,char* arg2) {
     printf("Warning: %s\n",format);
}

void avm_error(char* format){
    printf("Error: %s\n",format);
}
extern void avm_calllibfunc(char* funcName);



void avm_tabledestroy(avm_table* t){
    avm_tablebucketdestroy(t->strIndexed);
    avm_tablebucketdestroy(t->numIndexed);
    free(t);
}

void avm_memcellclear(avm_memcell* key);

avm_memcell* avm_tablegetelem(avm_table* table, avm_memcell* index){}
void avm_tablesetelem(avm_table* table, avm_memcell* index, avm_memcell* content){}

void avm_tableincrefcounter(avm_table* t) {
    (t->refCounter)++;
}

void avm_tabledecrefcounter(avm_table* t) {
    assert(t->refCounter > 0);
    if (!--t->refCounter) {
        avm_tabledestroy(t);
    }
}

void avm_tablebucketsinit(avm_table_bucket** p) {
    unsigned i;
    for (i = 0; i < AVM_TABLE_HASHSIZE; i++) {
        p[i] = (avm_table_bucket*)0;
    }
}

avm_table* avm_tablenew(void) {
    avm_table* t = (avm_table*)malloc(sizeof(avm_table));
    AVM_WIPEOUT(*t);

    t->refCounter = t->total = 0;
    avm_tablebucketsinit(t->numIndexed);
    avm_tablebucketsinit(t->strIndexed);

    return t;
}


void avm_tablebucketdestroy(avm_table_bucket** p) {
    unsigned i = 0;
    for (i = 0; i < AVM_TABLE_HASHSIZE; ++i, ++p) {
        avm_table_bucket* b;
        for (b = *p; b;) {
            avm_table_bucket* del = b;
            b = b->next;
            avm_memcellclear(&(del->key));
            avm_memcellclear(&(del->value));
            free(del);
        }
        p[i] = (avm_table_bucket*)0;
    }
}




static void avm_initstack(void) {
//     *lib_table  =(library_func_t*) malloc(sizeof(library_func_t));
    unsigned i;
    for (i = 0; i < AVM_STACKSIZE; i++) {
        AVM_WIPEOUT(stack[i]);
        stack[i].type = undef_m;
    }

    topsp = AVM_STACKSIZE - 1;
	top = AVM_STACKSIZE - 1 - totalGlobals ;
    printf("topavm = %u\n",top);
    /*na baloume ta globals*/
}

/* APO DIALEKSH 15 !!! */

double consts_getnumber(unsigned index) {
    return numArray[index];
}

char* consts_getstring(unsigned index) {
//    printf("gyrnaw to string %s \n",stringArray[index]);
    return stringArray[index];

}
/*na ftiaxoyme kapou to array of libfuncs (apo ekei pou diavazoume ths 4hs?)*/
/*return libfuncs[index]*/
char* libfuncs_getused(unsigned index) {
    return libFuncsArray[index];
}

/*apo fronti*/
avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg){
        printf("avm translate: arg->type %u\n",arg->type);

    switch(arg->type){
        /*variables*/
        case global_a:
            

            return &stack[AVM_STACKSIZE-1-(arg->val)];
        case local_a:
            
            return &stack[topsp-(arg->val)];
        case formal_a:
            

            return &stack[topsp+AVM_STACKENV_SIZE+1+(arg->val)];
        case retval_a:
            printf("eimai retval\n");
           return &retval;

        /*constants*/
        case number_a: {
            reg->type=number_m;
            reg->data.numVal =consts_getnumber(arg->val);
            return reg;
        }
           case string_a: {
            
            reg->type = string_m;
            reg->data.strVal =strdup((char*)consts_getstring(arg->val));
           
            return reg;
        }
        case bool_a: {

            reg->type = bool_m;
            reg->data.boolVal = arg->val;
            return reg;
        }
        case nil_a: {
            reg->type = nil_m;
            return reg;
        }

        /*functions*/
        case userfunc_a: {
            reg->type = userfunc_m;
            reg->data.funcVal = arg->val; /* Adress already stored */
            return reg;
        }
        case libfunc_a: {
            reg->type = libfunc_m;
            reg->data.libfuncVal = libfuncs_getused(arg->val);
            return reg;
        }
        default:
        printf("break1 arg->type %u\n",arg->type);
        assert(0);
            break;
        
        }
}



char* typeStrings[] = {
    "number",
    "string",
    "bool",
    "table",
    "userfunc",
    "libfunc",
    "nil",
    "undef"
};


void avm_push_envvalue(unsigned val) {
    stack[top].type = number_m;
    stack[top].data.numVal = val;
    avm_dec_top();
}


unsigned avm_get_envvalue(unsigned i) {
    assert(stack[i].type == number_m);
    unsigned val = (unsigned)stack[i].data.numVal;
    assert(stack[i].data.numVal == ((double)val));
    return val;
}

void execute_funcexit(instruction* unused) {
    printf("FUNCEXITTTTTTTTT!\n");
    unsigned oldTop = top;
    top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    printf("FUNCEXITTTTTTTTT2222222222!\n");
// EDW EXOYME THEMATAKII
/// to allaksa apo oldtop++ sto anapodo !!
    while (++oldTop<= top) {/*Intntionally ignoring first*/
        avm_memcellclear(&stack[oldTop]);
    }
    printf("FUNCEXITTTTTTTTT33333333!\n");

}




unsigned avm_totalactuals() {
    printf("mpika total actuals\n");
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}
avm_memcell* avm_getactual(unsigned i) {
    assert(i < avm_totalactuals());
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

typedef char* (*tostring_func_t)(avm_memcell* m);
char* number_tostring(avm_memcell* m){
    char* text = (char*)malloc(sizeof(char));
    sprintf(text, "%f", m->data.numVal);
  return(text);
}
char* string_tostring(avm_memcell* m) {
    return m->data.strVal;
}
char* bool_tostring(avm_memcell* m){
    if(m->data.boolVal == '1') return "true";
    return "false";
}
char* table_tostring(avm_memcell* m){

}
char* userfunc_tostring(avm_memcell* m){
    char* text = (char*)malloc(sizeof(char));
    sprintf(text, "%u", userFArray[m->data.funcVal].address);
    return(text);
}
char* libfunc_tostring(avm_memcell* m) {
    return m->data.libfuncVal;
}
char* nil_tostring(avm_memcell* m){
    return "nill";
}
char* undef_tostring(avm_memcell* m){
    return "undef";
}

tostring_func_t tostringFuncs[] = {
    number_tostring,
    string_tostring,
    bool_tostring,
    table_tostring,
    userfunc_tostring,
    libfunc_tostring,
    nil_tostring,
    0
};
char* avm_tostring(avm_memcell* m) {
    printf("avm to string\n");
    
    printf("type = %d\n",m->type);
    assert((m->type >= 0) &&( m->type <= 7));
    return (*tostringFuncs[m->type])(m);
}

double avm_get_envalue(unsigned i){
return stack[i].data.numVal;
}

void libfunc_print() {
    printf("mpika lib\n");
    unsigned n = avm_totalactuals();
    printf("ta total einai %u\n",n);
    unsigned i;
    for (i = 0; i < n; i++) {
        char* s = strdup(avm_tostring(avm_getactual(i)));
        printf("MOY EDOSE I STRTRIJGRJG %s",s);
        puts(s);
        //free(s);
    }
}

void libfunc_typeof() {
    unsigned n = avm_totalactuals();

    if (n != 1) {
        retval.type = nil_m;
        avm_error("one arg expected in typeof!");
    } else {
        /*thats how a libfunc returns a result */
        avm_memcellclear(&retval);
        retval.type = string_m;
        retval.data.strVal = strdup(typeStrings[avm_getactual(0)->type]);
    }
}

void libfunc_sqrt(){
	int actuals=avm_totalactuals(); 

	if(actuals>1){
		avm_error("Error, sqrt: wrong number of arguments");
		retval.type=nil_m;
		return;
	}

	if(avm_getactual(0)->type !=0){
		avm_error("Error, sqrt: wrong input type.");
		retval.type=nil_m;
		return;
	} 

	avm_memcellclear(&retval);
    retval.type =number_m;
	retval.data.numVal= sqrt(avm_getactual(0)->data.numVal);
	
}


void libfunc_cos(){
printf("eimai cos\n");
	int actuals=avm_totalactuals(); 

	if(actuals>1){
		avm_error("Error, cos: wrong number of arguments");
		retval.type=nil_m;
		return;
	}

	if(avm_getactual(0)->type !=0){
		avm_error("Error, cos: wrong input type.");
		retval.type=nil_m;
		return;
	} 

	avm_memcellclear(&retval);
    retval.type =number_m;
    //convert to num?
	retval.data.numVal= cos(avm_getactual(0)->data.numVal);
	
}

void libfunc_sin(){
	int actuals=avm_totalactuals(); 

	if(actuals>1){
		avm_error("Error, sin: wrong number of arguments");
		retval.type=nil_m;
		return;
	}

	if(avm_getactual(0)->type !=0){
		avm_error("Error, sin: wrong input type.");
		retval.type=nil_m;
		return;
	} 

	avm_memcellclear(&retval);
    retval.type =number_m;
	retval.data.numVal= sin(avm_getactual(0)->data.numVal);
	
}

void libfunc_strtonum(){

	int actuals=avm_totalactuals();
	double result;
	int digit,i,j=0;
	char *input,*tmp_res;

	if(actuals>1){
		avm_error("Error, strtonum: wrong number of arguments");
		retval.type=nil_m;
		return;
	}

	if(avm_getactual(0)->type !=1){
		avm_error("Error, strtonum: wrong input type.");
		retval.type=nil_m;
		return;
	} 

    input=strdup(avm_getactual(0)->data.strVal);

	for (i = 0; i < strlen(input); i++) {
		if(isdigit(input[i])){
			tmp_res[j]=input[i];
			j++;
		}
	}

	if(digit==0){
		avm_error("Error, strtonum: no numbers found in string.");
		retval.type=nil_m;
		return;
	}

	    retval.type=number_m;
	    retval.data.numVal=  atoi(tmp_res);
		return;	
}

void libfunc_totalarguments(void) {
    /*get topsp of prev activation record*/
    unsigned p_topsp = avm_get_envvalue(topsp +AVM_SAVEDTOPSP_OFFSET);
    avm_memcellclear(&retval);
    if(!p_topsp)
    {
        avm_error("'totalarguments' called outside of a function");
        retval.type = nil_m;
    }else{
        /*extract the num of actual args for the prev activation record*/
        retval.type = number_m;
        retval.data.numVal = avm_get_envalue(p_topsp +AVM_NUMACTUALS_OFFSET);
    }
}

void libfunc_objectmemberkeys(){}

void libfunc_objecttotalmembers(){}

void libfunc_objectcopy(){}

void libfunc_argument(){}

void libfunc_input(){}


/*every lib func is manually added in the vm library function resolution map*/

void avm_registerlibfunc(char* id, library_func_t addr) {
	lib_table[libHash_func(id)] = addr;
}



/*typical hashing*/
library_func_t avm_getlibraryfunc(char* id){
    printf("GET LIB FUNC \n");
	  if(!strcmp(id,"print")) return libfunc_print; 
	  if(!strcmp(id,"typeof")) return libfunc_typeof; 
	  if(!strcmp(id,"sqrt")) return libfunc_sqrt; 
	  if(!strcmp(id,"objectmemberkeys")) return libfunc_objectmemberkeys; 
	  if(!strcmp(id,"objecttotalmembers")) return libfunc_objecttotalmembers; 
	  if(!strcmp(id,"objectcopy")) return libfunc_objectcopy;
	  if(!strcmp(id,"totalarguments")) return libfunc_totalarguments; 
	  if(!strcmp(id,"argument")) return libfunc_argument; 
	  if(!strcmp(id,"strtonum")) return libfunc_strtonum; 
	  if(!strcmp(id,"cos")) return libfunc_cos; 
	  if(!strcmp(id,"sin")) return libfunc_sin;  
}

void avm_calllibfunc(char* id) {
    library_func_t f = avm_getlibraryfunc(id);
    if (!f) {
        avm_error("unsupported lib func called!");
        executionFinished=1;
    } else {
        /*notice that enter function and exit function are called manually*/
        topsp = top;
        totalActuals = 0;
        (*f)();                                /*call lib func*/
        if (!executionFinished) {              /*an error may naturally occur inside*/
            execute_funcexit((instruction*)0); /*return sequence*/
        }
    }
}





typedef double (*arithmetic_func_t)(double x, double y);

double add_impl(double x, double y) { return x + y; }
double sub_impl(double x, double y) { return x - y; }
double mul_impl(double x, double y) { return x * y; }
double div_impl(double x, double y) {
 /*ADD ERROR CHECK*/
        return x / y;
   
}
double mod_impl(double x, double y) {
 /*ADD ERROR CHECK*/

        return ((unsigned)x) % ((unsigned)y);

}

/*dispatcher for arithm funcs*/
arithmetic_func_t arithmeticFuncs[] = {
    add_impl,
    sub_impl,
    mul_impl,
    div_impl,
    mod_impl
};

typedef int (*relational_func_t)(double x, double y);

int jle_impl(double x, double y) { return x <= y; }
int jge_impl(double x, double y) { return x >= y; }
int jlt_impl(double x, double y) { return x < y; }
int jgt_impl(double x, double y) { return x > y; }

/*dispatcher for arithm funcs*/
relational_func_t relationalFuncs[] = {
    jle_impl,
    jge_impl,
    jlt_impl,
    jgt_impl
};

void execute_arithmetic(instruction* instr) {
    printf("execute arithmetic");
    avm_memcell* lv = avm_translate_operand(&(instr->result), (avm_memcell*)0);
    avm_memcell* rv1 = avm_translate_operand(&(instr->arg1), &ax);
    avm_memcell* rv2 = avm_translate_operand(&(instr->arg2), &bx);

    assert(lv && (&stack[AVM_STACKSIZE-1] >= lv &&  &stack[top] < lv || lv== &retval));
    assert(rv1 && rv2);

    if (rv1->type != number_m || rv2->type != number_m) {
        avm_error("not a number in arithmetic!"); 
    } else {
        arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
        avm_memcellclear(lv);
        lv->type = number_m;
        lv->data.numVal = (*op)(rv1->data.numVal, rv2->data.numVal);
    }
}


void execute_relational(instruction* instr) {
    printf("execute relational");
    //avm_memcell* lv = avm_translate_operand(&(instr->result), (avm_memcell*)0);
    printf("gamo\n");
    avm_memcell* rv1 = avm_translate_operand(&(instr->arg1), &ax);
    printf("ta\n");
    avm_memcell* rv2 = avm_translate_operand(&(instr->arg2), &bx);
    printf("relational\n");

    int result=0;
    //assert(lv && (&stack[AVM_STACKSIZE-1] >= lv &&  &stack[top] < lv || lv== &retval));
    
    assert(rv1 && rv2);

    if (rv1->type != number_m || rv2->type != number_m) {
        avm_error("not a number in relational!"); 
    } else
    {
        relational_func_t op = relationalFuncs[instr->opcode - jle_v];
        result =  (*op)(rv1->data.numVal, rv2->data.numVal);
    }
    if(!executionFinished && result )
    {
        pc = instr->result.val;
    }
    
}

typedef unsigned char (*tobool_func_t)(avm_memcell*);

unsigned char number_tobool(avm_memcell* m) { return m->data.numVal != 0; }
unsigned char string_tobool(avm_memcell* m) { return m->data.strVal[0] != 0; }
unsigned char bool_tobool(avm_memcell* m) { return m->data.boolVal; }
unsigned char table_tobool(avm_memcell* m) { return 1; }
unsigned char userfunc_tobool(avm_memcell* m) { return 1; }
unsigned char libfunc_tobool(avm_memcell* m) { return 1; }
unsigned char nil_tobool(avm_memcell* m) { return 0; }
unsigned char undef_tobool(avm_memcell* m) {
    assert(0);
    return 0;
}

tobool_func_t toboolFuncs[] = {
    number_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undef_tobool
};

unsigned char avm_tobool(avm_memcell* m) {
    assert(m->type >= 0 && m->type < undef_m);
    return (*toboolFuncs[m->type])(m);
}


void execute_newtable(instruction* instr) {
    printf("execute new tbl");

    avm_memcell* lv = avm_translate_operand(&instr->result, (avm_memcell*)0);
    assert(lv && (&stack[AVM_STACKSIZE - 1] >= lv && lv > &(stack[top]) || lv == &retval));

    avm_memcellclear(lv);

    lv->type = table_m;
    lv->data.tableVal = avm_tablenew();
    avm_tableincrefcounter(lv->data.tableVal);
}


userfunc* avm_getfuncinfo(unsigned address){
    int i=0;
    while(userFArray[i].address!= address && i!= totalFuncs)
    {
        i++;
    }
    if(userFArray[i].address == address) return &userFArray[i];
    return NULL;
}

void execute_assign(instruction* instr) {
    
   printf("Mpika assign\n"); 
   //akuro
    avm_memcell* lv = avm_translate_operand(&(instr->result), (avm_memcell*)0);
    //retval

    avm_memcell* rv = avm_translate_operand(&(instr->arg1), &ax);

    /*na to tsekaroyme auto  dialeksh 15 slide 17*/
//  assert(lv && (&stack[AVM_STACKSIZE-1] >= lv &&  lv > &stack[top] || lv == &retval));
    assert(rv);
    avm_assign(lv, rv);
    printf("assign TELOS\n");
}
void execute_add(instruction* instr);
void execute_sub(instruction* instr);
void execute_mul(instruction* instr);
void execute_div(instruction* instr);
void execute_mod(instruction* instr);
void execute_uminus(instruction* instr){}
void execute_and(instruction* instr){}
void execute_or(instruction* instr){}
void execute_not(instruction* instr){}

typedef int (*equal_func_t)(avm_memcell* x, avm_memcell* y);

int number_eq(avm_memcell*  x, avm_memcell*  y) { return x->data.numVal == y->data.numVal; }
int string_eq(avm_memcell* x, avm_memcell* y) { if(!strcmp(x->data.strVal,y->data.strVal)==0) return 1;return 0; }
int bool_eq(avm_memcell*  x, avm_memcell*  y) { return x->data.boolVal == y->data.boolVal; }
int table_eq(avm_memcell*  x, avm_memcell*  y) { return ((&x)==(&y)); }
int userfunc_eq(avm_memcell*  x, avm_memcell*  y) { return((&x)==(&y)); }
int libfunc_eq(avm_memcell*  x, avm_memcell*  y) { return ((&x)==(&y)); }

/*dispatcher for equal funcs*/
equal_func_t equalFuncs[] = {
    number_eq,
    string_eq,
    bool_eq,
    table_eq,
    userfunc_eq,
    libfunc_eq

};

void execute_jeq(instruction* instr){
    printf("execute jeq");

    assert(instr->result.type == label_a);

    avm_memcell* rv1 = avm_translate_operand(&(instr->arg1), &ax);
    avm_memcell* rv2 = avm_translate_operand(&(instr->arg2), &bx);

    int result = 0;

    if (rv1->type == undef_m || rv2->type == undef_m) {
        avm_error("'undef' involved in equality");
    } else if (rv1->type == nil_m || rv2->type == nil_m) {
        result = rv1->type == nil_m && rv2->type == nil_m;
    } else if (rv1->type == bool_m || rv2->type == bool_m) {
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    } else if (rv1->type != rv2->type) {
        avm_error("illegal operation");
    } else {
        
        equal_func_t op = equalFuncs[rv1->type];
        result =  (*op)(rv1, rv2);

    }

    if (!executionFinished && result) {
        pc = instr->result.val;
    }
}
void execute_jne(instruction* instr){
    printf("execute jne");

    assert(instr->result.type == label_a);

    avm_memcell* rv1 = avm_translate_operand(&(instr->arg1), &ax);
    avm_memcell* rv2 = avm_translate_operand(&(instr->arg2), &bx);

    int result = 0;

    if (rv1->type == undef_m || rv2->type == undef_m) {
        avm_error("'undef' involved in equality");
    } else if (rv1->type == nil_m || rv2->type == nil_m) {
        result = rv1->type == nil_m && rv2->type == nil_m;
    } else if (rv1->type == bool_m || rv2->type == bool_m) {
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    } else if (rv1->type != rv2->type) {
        avm_error("illegal operation");
    } else {
        
        equal_func_t op = equalFuncs[rv1->type];
        result =  (*op)(rv1, rv2);

    }

    if (!executionFinished && !result) {
        pc = instr->result.val;
    }

}
void execute_jle(instruction* instr);
void execute_jlt(instruction* instr);
void execute_jgt(instruction* instr);
void execute_jge(instruction* instr);
void execute_jump(instruction* instr){ 
    printf("MPIKA JUMPPPPPPPPP !!!!SOSSS!!!!! TOP AVM ==== %u\n", top); 
    pc = instr->result.val;
   
   // pc = *(instr->result.jumpaddr);
}

void execute_call(instruction* instr){
printf("kanw call\n");
/// SOOOOSSS apo arg1 allaksa se result sto tcode.h !! !
    avm_memcell* func = avm_translate_operand(&instr->result, &ax);

    assert(func);
    avm_callsaveenvironment();
printf("after callsaverek;l\n");
    switch (func->type) {
        case userfunc_m: {
printf("call userf\n");

            pc = userFArray[func->data.funcVal].address;
            assert(pc < AVM_ENDING_PC);
            assert(instructionsArray[pc].opcode == funcenter_v);
            break;
        }
        case string_m:
{printf("call string\n");

            avm_calllibfunc(func->data.strVal);}
            break;
        case libfunc_m:
            {printf("call lib\n");

            avm_calllibfunc(func->data.libfuncVal);}
            break;
        default: {
            printf("default\n");
            char* s = avm_tostring(func);
            avm_error("call: cannot bind to function!");
            free(s);
            executionFinished = 1;
        }
    }

}
void execute_pusharg(instruction* instr){
    printf("kanw pusharg\n");
    /// allagh apo arg1 se result ston tcode!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    avm_memcell* arg = avm_translate_operand(&instr->result, &ax);
    assert(arg);
    avm_assign(&stack[top], arg);
    ++totalActuals;
    printf("total eavfjvf %u \n", totalActuals);
    avm_dec_top();
}

void execute_funcenter(instruction* instr) {
    printf("mpika edw funcENTERRRRRRRRRRRRR\n");
    avm_memcell* func = avm_translate_operand(&instr->result, &ax);
    assert(func);
    assert(pc == userFArray[func->data.funcVal].address); /*func address should match pc */
    
    /*callee actions here*/
    totalActuals = 0;
    userfunc* funcInfo = avm_getfuncinfo(pc);
    topsp = top;
    top = top - funcInfo->localSize;
}

void execute_newtable(instruction* instr);

void execute_tablegetelem(instruction* instr) {
    printf("execute tbl get elem");

    avm_memcell* lv = avm_translate_operand(&instr->result, (avm_memcell*)0);
    avm_memcell* t = avm_translate_operand(&instr->arg1, (avm_memcell*)0);
    avm_memcell* i = avm_translate_operand(&instr->arg2, &ax);

    assert(lv && (&stack[AVM_STACKSIZE-1] >= lv &&  &stack[top] <lv || lv == &retval));
    assert(t && (&stack[AVM_STACKSIZE-1]) >= t &&  &stack[top] <t);
    assert(i);

    avm_memcellclear(lv);

    lv->type = nil_m;

    if (t->type != table_m) {
        avm_error("Illegal use of type as table");
    } else {
        avm_memcell* content = avm_tablegetelem(t->data.tableVal, i);
        if (content) {
            avm_assign(lv, content);
        } else {
            char* ts = avm_tostring(t);
            char* is = avm_tostring(i);
            avm_warning(" %s [%s] not found!", ts, is);
            free(ts);
            free(is);
        }
    }
}

void execute_tablesetelem(instruction* instr) {
    printf("execute tbl set elem");

    avm_memcell* t = avm_translate_operand(&instr->arg1, (avm_memcell*)0);

    avm_memcell* i = avm_translate_operand(&instr->arg2, &ax);
    avm_memcell* c = avm_translate_operand(&instr->result, &bx);

    assert(t && &stack[AVM_STACKSIZE-1] >= t && &stack[top] < t);
    assert(i && c);

    if (t->type != table_m) {
        avm_error(" illegal use of type as table!");
        executionFinished = 1;
    } else {
        avm_tablesetelem(t->data.tableVal, i, c);
    }
}

void execute_nop(instruction* instr){}


execute_func_t executeFuncs[] = {
    execute_assign,
    execute_add,
    execute_sub,
    execute_mul,
    execute_div,
    execute_mod,
    execute_uminus,
    execute_and,
    execute_or,
    execute_not,
    execute_jeq,
    execute_jne,
    execute_jle,
    execute_jge,
    execute_jlt,
    execute_jgt,
    execute_call,
    execute_pusharg,
    execute_funcenter,
    execute_funcexit,
    execute_newtable,
    execute_tablegetelem,
    execute_tablesetelem,
    execute_nop,
    execute_jump
};



void execute_cycle(void) {
    if (executionFinished) {
        return;
    } else if (pc == AVM_ENDING_PC) {
        executionFinished = 1;
        return;
    } else {
        assert(pc < AVM_ENDING_PC);
        instruction* instr = instructionsArray + pc;
        assert(instr->opcode >= 0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);
        unsigned oldPC = pc;
        executeFuncs[instr->opcode](instr);
        if (pc == oldPC) {
            pc++;
        }
    }
}

typedef void (*memclear_func_t)(avm_memcell*);

void memclear_string(avm_memcell* m) {
    printf("mem clear string\n");
    assert(m->data.strVal);
    free(m->data.strVal);
}

void memclear_table(avm_memcell* m) {
    printf("mem clear tbl\n");

    assert(m->data.tableVal);
    avm_tabledecrefcounter(m->data.tableVal);
}

memclear_func_t memclearFuncs[] = {
    0,               /* number */
    memclear_string, /* string */
    0,               /* bool */
    memclear_table,  /* table */
    0,               /* userfunc */
    0,               /* libfunc */
    0,               /* nil */
    0,               /* undef */
};

void avm_memcellclear(avm_memcell* m) {
    printf("mem clear \n");
    printf("mem clear type %u \n",m->type);
   
    if (m->type != undef_m) {
        memclear_func_t f = memclearFuncs[m->type];
        if (f) {
            (*f)(m);
        }
        m->type = undef_m;
    }
}

void avm_assign(avm_memcell* lv, avm_memcell* rv) {
       if (lv == rv) {
           return; /*Same cells? Destructive to assign!*/
    }
   
    // if (lv->type == table_m && rv->type == table_m && lv->data.tableVal == rv->data.tableVal) {
      
    //     return; /*Same tables? No need to assign.*/
    // }
       if (rv->type == undef_m||rv -> type ==  nil_m) {
        avm_warning("assigning from 'undef' content!","","");
    }

    avm_memcellclear(lv);                /*clear old cell contents*/
   
    memcpy(lv, rv, sizeof(avm_memcell)); 

    if (lv->type == string_m) {
        lv->data.strVal = strdup(rv->data.strVal);
    } else if (lv->type == table_m) {
        avm_tableincrefcounter(lv->data.tableVal);
    }
}


void avm_callsaveenvironment() {
    avm_push_envvalue(totalActuals);
    avm_push_envvalue(pc + 1);
    avm_push_envvalue(top + totalActuals + 2);
    avm_push_envvalue(topsp);
}


void avm_dec_top(void) {
    printf("avm dec top\n");
    if (!top) {
        avm_error("Stack Overflow"); /* Stack Overflow */
        executionFinished=1;
    } else {
        --top;
    }
}





void avm_initialize(void){
    avm_initstack();
    /*init hash table*/
    avm_registerlibfunc("print",libfunc_print);
    avm_registerlibfunc("typeof",libfunc_typeof);
    avm_registerlibfunc("sqrt",libfunc_sqrt);
    avm_registerlibfunc("input",libfunc_input);
    avm_registerlibfunc("objectmemberkeys",libfunc_objectmemberkeys);
    avm_registerlibfunc("objecttotalmembers",libfunc_objecttotalmembers);
    avm_registerlibfunc("objectcopy",libfunc_objectcopy);
    avm_registerlibfunc("totalarguments",libfunc_totalarguments);
    avm_registerlibfunc("argument",libfunc_argument);
    avm_registerlibfunc("strtonum",libfunc_strtonum);
    avm_registerlibfunc("cos",libfunc_cos);
    avm_registerlibfunc("sin",libfunc_sin);
}


void readMagicNumber(FILE *binary){

    unsigned int magicNum;
      fread(&magicNum,sizeof(unsigned),1,binary);
      if(magicNum != 340200501)
      {
        avm_error("Wrong Magic Number\n");
        assert(0);
      }
}

void readString(FILE *binary){
    unsigned int totalStr;
    unsigned int sizeStr;

    fread(&totalStr,sizeof(unsigned),1,binary);
    stringArray= (char**) malloc(totalStr * sizeof(char*));

    int i =0;
    while(i<totalStr)
    {
        fread(&sizeStr,sizeof(unsigned),1,binary);
     //   char* newString = (char*) malloc(sizeof(char)*sizeStr);
        

        char **stringArrItem = stringArray + i;
        fread(&(*stringArrItem),sizeof(char*),1,binary);

    //    *stringArrItem = strdup(newString);
        i++;
    }

}


void readNumConst(FILE *binary){
    unsigned int totalNums;

    fread(&totalNums,sizeof(unsigned),1,binary);
    numArray= (double*) malloc(sizeof(double) * totalNums);

    int i =0;
    while(i<totalNums)
    {
        double newNum;
        fread(&newNum,sizeof(double),1,binary);
        double *numArrItem = numArray + i;
        *numArrItem = newNum;
        i++;
    }

}

void readUserF(FILE *binary){
    unsigned int  address, localSize;
    char* id;

    fread(&totalFuncs,sizeof(unsigned),1,binary);
    userFArray= (userfunc*) malloc(sizeof(userfunc) * totalFuncs);

    int i =0;
    while(i<totalFuncs)
    {
        userfunc* newFunc=userFArray + i;

        fread(&(newFunc->address),sizeof(int),1,binary);
        fread(& (newFunc->localSize),sizeof(int),1,binary);
        fread(&(newFunc->id),sizeof(char*),1,binary);


        // newFunc->address=address;
        // newFunc->localSize=localSize;
        // newFunc->id=strdup(id);

        i++;
    }

}

void readLibFuncs(FILE *binary){
    unsigned int totalLibs;
    unsigned int sizeStr;

    fread(&totalLibs,sizeof(unsigned),1,binary);

    libFuncsArray= (char**) malloc(totalLibs * sizeof(char*));

    int i =0;
    while(i<totalLibs)
    {
        fread(&sizeStr,sizeof(unsigned),1,binary);
    //    char* newLib = (char*) malloc(sizeof(char)*sizeStr);


        char **libArrItem = libFuncsArray + i;
        fread(&(*libArrItem),sizeof(char*),1,binary);

   //     *libArrItem = strdup(newLib);
        i++;
    }

}


void readCode(FILE *binary){

    fread(&codeSize,sizeof(unsigned),1,binary);

    instructionsArray= (instruction*) malloc(sizeof(instruction) * codeSize);

    int i =0;
    while(i<codeSize)
    {
        instruction *newInstr = instructionsArray + i;
        fread(&(newInstr->opcode),sizeof(unsigned),1,binary);
        fread(&(newInstr->result.type),sizeof(int),1,binary);
        fread(&(newInstr->result.val),sizeof(unsigned),1,binary);
        fread(&(newInstr->arg1.type),sizeof(int),1,binary);
        fread(&(newInstr->arg1.val),sizeof(unsigned),1,binary);
        fread(&(newInstr->arg2.type),sizeof(int),1,binary);
        fread(&(newInstr->arg2.val),sizeof(unsigned),1,binary);
        fread(&(newInstr->srcLine),sizeof(unsigned),1,binary);
        i++;
    }

}

void readTotalGlobals(FILE *binary){

    unsigned int totalGlobals;
    fread(&totalGlobals,sizeof(unsigned),1,binary);

}


void readAll(FILE *binary){
    readMagicNumber(binary);
    readString(binary);
    readNumConst(binary);
    readUserF(binary);
    readLibFuncs(binary);
    readCode(binary);
    readTotalGlobals(binary);
}