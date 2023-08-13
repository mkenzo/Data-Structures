PROJ_NAME=ted

ALUNO= matheusk
LIBS= -lm
OBJETOS= circle.o figure.o flags.o geo.o line.o lista.o main.o path.o qry.o rectangle.o svg.o system.o text.o cpt.o quicksort.o

# compilador
CC=gcc

# Flags
CFLAGS= -ggdb -O0 -std=c99 -fstack-protector-all -Werror=implicit-function-declaration
LDFLAGS=-O0

$(PROJ_NAME): $(OBJETOS)
	$(CC) -o $(PROJ_NAME) $(LDFLAGS) $(OBJETOS) $(LIBS)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

main.o: libs.h path.h flags.h system.h cpt.h geo.h svg.h qry.h main.c

system.o:  system.h path.h flags.h system.c

flags.o: flags.h flags.c

path.o: path.h libs.h path.c

lista.o: lista.h libs.h figure.h circle.h rectangle.h text.h line.h lista.c

geo.o: geo.h system.h cpt.h circle.h rectangle.h line.h text.h figure.h geo.c

svg.o: svg.h geo.h system.h cpt.h lista.h circle.h rectangle.h line.h text.h figure.h svg.c

qry.o: qry.h lista.h system.h svg.h figure.h circle.h rectangle.h text.h line.h cpt.h qry.c

figure.o: figure.h figure.c

circle.o: circle.h circle.c

rectangle.o: rectangle.h rectangle.c

line.o: line.h line.c

text.o: text.h text.c

cpt.o: cpt.h libs.h lista.h cpt.c

quicksort.o: quicksort.h lista.h figure.h circle.h rectangle.h text.h line.h quicksort.c

pack: $(PROJ_NAME)
	rm -f ../$(ALUNO).zip
	echo $(ALUNO)
	date >> .entrega
	cd ..; zip $(ALUNO).zip -r src/.c src/.h src/Makefile LEIA-ME.txt .entrega

