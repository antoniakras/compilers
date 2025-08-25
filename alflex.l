%{
    #include "parser.h" /* yparser */
    #include <stdio.h>
    #include <stdlib.h>
    #include "parser.h"
    /*#define  YY_DECL int alpha_yylex (void* ylval)*/
    unsigned int numToken = 0;
        
    struct alpha_token_t {
        unsigned int     numline;
        unsigned int     numToken;
        char          *content;
        char          *category;
        struct alpha_token_t *pnext;
    };

    struct alpha_token_t *head = NULL; 
    
    void insertLine(char *content,char *category, char *type, char *description){
        struct alpha_token_t *newToken = (struct alpha_token_t*) malloc(sizeof (struct alpha_token_t));
        struct alpha_token_t *tmp;
        
        newToken->numline=yylineno;
        if(type == "LINE_COMMENT")
        {
            newToken->numline= (newToken->numline)-1;
        }
        if(type == "BLOCK_COMMENT"){
            newToken->numline= (newToken->numline)-1;
        }
        newToken->numToken=++numToken;
        newToken->content=content;
        newToken->category=category;
        newToken->pnext = NULL;

        if(head==NULL){
            head=newToken;
        }else{
            tmp=head;
            while(tmp->pnext!=NULL){
                tmp=tmp->pnext;
            }
            tmp->pnext=newToken;
        }
       // printf("%u: #%u   '%s'  %s  %s  <- %s\n" , newToken->numline, newToken->numToken, newToken->content, newToken->category, type, description);
        }
%}


%option yylineno
%option noyywrap

IF              "if"
ELSE            "else"
WHILE           "while"
FOR             "for"
FUNCTION        "function"
RETURN          "return"
BREAK           "break"
CONTINUE        "continue"
AND             "and"
NOT             "not"
OR              "or"
LOCAL           "local"
TRUE            "true"
FALSE           "false"
NIL             "nil"
EQUAL		"="
PLUS		"+"
MINUS		"-"
MULTIPLY	"*"
SLASH_F	"/"
SLASH_B "\\"
PERCENT		"%"
EQUAL_TWO	"=="
NOT_EQUAL	"!="
PLUS_TWO	"++"
MINUS_TWO	"--"
GREATER		">"
LESS		"<"
B_EQUAL	">="
L_EQUAL	"<="
NUM		[0-9]+ 
FLOAT		([0-9]+([.][0-9]*)?|[.][0-9]+)
STRING	    \"
LEFT_BRACKET	"{"
RIGHT_BRACKET     "}"
LEFT_SQ_BRACKET	"["
RIGHT_SQ_BRACKET	"]"
LEFT_PARENTH	"("
RIGHT_PARENTH	")"
SEMICOLON		";"
COMMA			","
COLON			":"
NAMESPACE_ "::"
DOT			"."
DOT_TWO		".."
ID		[a-zA-Z][a-zA-Z_0-9]*
COMMENT 	"//".*
COMMENT_STAR 	"/*"
NEWLINE			"\n"
TAB			"\t"
SPACE		" "
OTHER	\"|!|$|@|#|^|_|&

%%

{IF}    {insertLine(yytext,"KEYWORD", "IF", "enumerated"); return IF;}
{ELSE}    {insertLine(yytext,"KEYWORD", "ELSE", "enumerated"); return ELSE;}
{WHILE}    {insertLine(yytext,"KEYWORD", "WHILE", "enumerated"); return WHILE;}
{FOR}    {insertLine(yytext,"KEYWORD", "FOR", "enumerated"); return FOR;}
{FUNCTION}    {insertLine(yytext,"KEYWORD", "FUNCTION", "enumerated"); return FUNCTION;}
{RETURN}    {insertLine(yytext,"KEYWORD", "RETURN", "enumerated"); return RETURN;}
{BREAK}    {insertLine(yytext,"KEYWORD", "BREAK", "enumerated"); return BREAK;}
{CONTINUE}    {insertLine(yytext,"KEYWORD", "CONTINUE", "enumerated"); return CONTINUE;}
{AND}    {insertLine(yytext,"KEYWORD", "AND", "enumerated"); return AND;}
{NOT}    {insertLine(yytext,"KEYWORD", "NOT", "enumerated"); return NOT;}
{OR}    {insertLine(yytext,"KEYWORD", "OR", "enumerated"); return OR;}
{LOCAL}    {insertLine(yytext,"KEYWORD", "LOCAL", "enumerated"); return LOCAL;}
{TRUE}    {insertLine(yytext,"KEYWORD", "TRUE", "enumerated"); return TRUE;}
{FALSE}    {insertLine(yytext,"KEYWORD", "FALSE", "enumerated"); return FALSE;}
{NIL}    {insertLine(yytext,"KEYWORD", "NIL", "enumerated"); return NIL;}
{EQUAL}    {insertLine(yytext,"OPERATOR", "EQUAL", "enumerated"); return EQUAL;}
{PLUS}    {insertLine(yytext,"OPERATOR", "PLUS", "enumerated"); return PLUS;}
{MINUS}    {insertLine(yytext,"OPERATOR", "MINUS", "enumerated"); return MINUS;}
{MULTIPLY}    {insertLine(yytext,"OPERATOR", "MULTIPLY", "enumerated"); return MULTIPLY;}
{SLASH_F}    {insertLine(yytext,"OPERATOR", "SLASH_F", "enumerated"); return SLASH_F;}
{SLASH_B}    {insertLine(yytext,"OPERATOR", "SLASH_B", "enumerated"); }
{PERCENT}    {insertLine(yytext,"OPERATOR", "PERCENT", "enumerated"); return PERCENT;}
{EQUAL_TWO}    {insertLine(yytext,"OPERATOR", "EQUAL_TWO", "enumerated"); return EQUAL_TWO;}
{NOT_EQUAL}    {insertLine(yytext,"OPERATOR", "NOT_EQUAL", "enumerated"); return NOT_EQUAL;}
{PLUS_TWO}    {insertLine(yytext,"OPERATOR", "PLUS_TWO", "enumerated"); return PLUS_TWO;}
{MINUS_TWO}    {insertLine(yytext,"OPERATOR", "MINUS_TWO", "enumerated"); return MINUS_TWO;}
{GREATER}    {insertLine(yytext,"OPERATOR", "GREATER", "enumerated"); return GREATER;}
{LESS}    {insertLine(yytext,"OPERATOR", "LESS", "enumerated"); return LESS;}
{B_EQUAL}    {insertLine(yytext,"OPERATOR", "B_EQUAL", "enumerated"); return B_EQUAL;}
{L_EQUAL}    {insertLine(yytext,"OPERATOR", "L_EQUAL", "enumerated"); return L_EQUAL;}
{NUM}    {insertLine(yytext,"CONST_INT", "NUM", "enumerated"); yylval.int_val =  atoi(yytext); return NUM;}
{FLOAT}    {insertLine(yytext,"CONST_REAL", "B_EQUAL", "enumerated"); yylval.real_val = atof(yytext); return FLOAT;}
{LEFT_BRACKET}    {insertLine(yytext,"PUNCTUATION", "LEFT_BRACKET", "enumerated"); return LEFT_BRACKET; }
{RIGHT_BRACKET}    {insertLine(yytext,"PUNCTUATION", "RIGHT_BRACKET", "enumerated"); return RIGHT_BRACKET; }
{LEFT_SQ_BRACKET}    {insertLine(yytext,"PUNCTUATION", "LEFT_SQ_BRACKET", "enumerated"); return LEFT_SQ_BRACKET;}
{RIGHT_SQ_BRACKET}    {insertLine(yytext,"PUNCTUATION", "RIGHT_SQ_BRACKET", "enumerated"); return RIGHT_SQ_BRACKET;}
{LEFT_PARENTH}    {insertLine(yytext,"PUNCTUATION", "LEFT_PARENTH", "enumerated"); return LEFT_PARENTH;}
{RIGHT_PARENTH}    {insertLine(yytext,"PUNCTUATION", "RIGHT_PARENTH", "enumerated"); return RIGHT_PARENTH;}
{SEMICOLON}    {insertLine(yytext,"PUNCTUATION", "SEMICOLON", "enumerated"); return SEMICOLON;}
{COMMA}    {insertLine(yytext,"PUNCTUATION", "COMMA", "enumerated"); return COMMA;}
{COLON}    {insertLine(yytext,"PUNCTUATION", "COLON", "enumerated"); return COLON;}
{NAMESPACE_}    {insertLine(yytext,"PUNCTUATION", "NAMESPACE_", "enumerated"); return NAMESPACE_;}
{DOT}    {insertLine(yytext,"PUNCTUATION", "DOT", "enumerated"); return DOT;}
{DOT_TWO}    {insertLine(yytext,"PUNCTUATION", "DOT_TWO", "enumerated"); return DOT_TWO;}
{ID}    {insertLine(yytext,"ID", yytext, "enumerated"); yylval.string_Val = strdup(yytext); return ID;}
{COMMENT}    { 
         int c;
            while((c = input())!= '\n'&& c!=EOF){
                ;
            }
            insertLine("","COMMENT","LINE_COMMENT","enumerated");
                  
}
   
{COMMENT_STAR} {
     int c;
     int Blockline=yylineno;
     int count_open=1;
     int count_close=0;
     int count_nested=0;
            while( count_close!=count_open && (c = input()) ){
                if(c=='/'){
                    if((c=input())=='*'){
                        count_open++;
                    }else{
                        unput(c);
                    }
                    
                }else if(c=='*'){
                    if((c=input())=='/') {
                        count_close++;
                    }else{
                        unput(c); 
                    }
                   
                    if(count_open!=count_close){
                    count_nested++;
                    }
                         
                    if(count_close<count_open){
                      insertLine("","NESTED_COMMENT","","enumerated");
                    }
                }
            }
            if (count_close==count_open){ 
                        insertLine("","BLOCK_COMMENT","","enumerated");
                        if(count_nested!=0) printf("Block comment has: %d  nested comment[s]\n",count_nested );
                        break;
            }else{
                printf("ERROR : Block comment has not been closed\n");
            }
}

{NEWLINE} 
{TAB}
{SPACE}
{STRING}  {

int flag = 0;
int flag1 =0;
int i=0;
register int in;
char *array = (char*) malloc(sizeof(char));
 
enum States{
     norm,
     backslash
};
enum States state;
state = norm;
     
while(flag==0 && (in = input()) ){
 
    switch (state){

    case norm:
        if(in =='\\') {
            state=backslash;
    
        }else if(in == '"'){
            flag = 1;
            break;
        }
        else{
            array[i]= in;
            i++;
            state = norm;
          }
        break;
   case backslash:
        if(in =='n'){
            array [i++]='\n';
        }else if(in == 't'){
            array [i++]='\t';
        }else if(in == '\"'){
            array [i++]='\"';
        }else if(in == ','){
            array [i]=',';
        }else if(in == '\\'){
            array [i++]='\\';
            break;
        }else{
            flag1 = 1;   
        }
        i++;
        state = norm;
        break;

        default:
         break;
    }
     array = realloc(array, i+1);
}

if(flag==0){
    printf("ERROR : Found unclosed string\n");
 }else{
    if(flag1==0){
        insertLine(array,"STRING",array,"char*");
    }else{
        printf("ERROR : Escape Character Detected\n");
    }
 }
    yylval.string_Val = strdup(array);
    return STRING;
}

{OTHER}	  {printf("UNDEFINED CHAR IN LINE: %d\n",yylineno);}
%%

/*
int main(int argc,char** argv){
    yyin = fopen( argv[1], "r" );
    alpha_yylex(head);
}*/

