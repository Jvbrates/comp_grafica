CC = g++
CFLAGS = -Wall -Werror -g
LDLIBS = -lglut -lGL -lGLU

OBJS = gl_canvas2d.o Renderizable.o collisions.o Conteiner.o ImageSelector.o ImageManagement.o Histogram.o button.o TextBox.o EventListener.o  \
			 main.o

TARGETS = main

all: ${TARGETS}



# para gerar o programa principal, precisa de todos os .o)
main: ${OBJS}

# apaga os arquivos gerados
clean:
	rm -f ${OBJS} ${OBJS_MONT} ${TARGETS} ${MAQS} ${OBJS:.o=.d}

# para calcular as dependências de cada arquivo .c (e colocar no .d)
%.d: %.cpp
	@set -e; rm -f $@; \
	 $(CC) -MM $(CPPFLAGS) $< > /tmp/$@.$$$$; \
	 sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < /tmp/$@.$$$$ > $@; \
	 rm -f /tmp/$@.$$$$

# inclui as dependências
include $(OBJS:.o=.d)
