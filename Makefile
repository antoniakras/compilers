all:
	flex --outfile=alflex.c alflex.l
	bison -v --yacc --defines --output=parser.c parser.y
	gcc -g -o calc alflex.c parser.c  syntax_header.h -lm
