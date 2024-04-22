CC = g++
CFLAGS = -Wall -Werror -g -Wno-sign-compare
LDLIBS = -lglut -lGL -lGLU

# Subdiretório para os binários
BINDIR = bin

# Lista dos objetos
OBJS = gl_canvas2d.o Renderizable.o collisions.o Conteiner.o image/ImageSelector.o image/ImageManagement.o \
       image/Histogram.o button.o TextBox.o EventListener.o geometry/Polygon.o \
       main.o

# Adiciona o subdiretório aos objetos, exceto para o main
OBJDIR_OBJS = $(patsubst %.o,$(BINDIR)/%.o, $(OBJS))



TARGETS = main

all: ${TARGETS}

# para gerar o programa principal, precisa de todos os .o)
main: $(OBJDIR_OBJS)
	echo $^
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

# Regra para compilar os objetos no subdiretório
$(BINDIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

# apaga os arquivos gerados
clean:
	rm -f $(BINDIR)/*.o $(TARGETS) $(OBJS:.o=.d)

# para calcular as dependências de cada arquivo .c (e colocar no .d)
dependences/%.d: %.cpp
	 set -e; rm -f $@; \
	 $(CC) -MM $(CPPFLAGS) $< > /tmp/$(subst /,_,$@).$$$$; \
	 sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < /tmp/$(subst /,_,$@).$$$$ > $@; \
	 rm -f /tmp/$@.$$$$

# inclui as dependências
include $(OBJS:%.o=dependences/%.d)
