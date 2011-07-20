##################################################################################################################
#                                                                                                                #
#   Fichier     :   Makefile                                                                                     #
#                                                                                                                #
#   Type        :   Makefile d'un programme complet                                                              #
#                                                                                                                #
#   Auteur      :   Heero Yui                                                                                    #
#                                                                                                                #
#   Evolutions  :   Date          Auteur        Raison                                                           #
#                2010-01-29      Heero Yui      Mise en place d'un makefile ultra simple                         #
#                                                                                                                #
# Concu Pour le projet hexViwer                                                                                  #
#                                                                                                                #
##################################################################################################################
export F_GRAS=[1m
export F_INVERSER=[7m
export F_SOUSLIGNER=[4m
export F_NORMALE=[m
export F_NOIR=[31m
export F_ROUGE=[31m
export F_VERT=[32m
export F_MARRON=[33m
export F_BLUE=[34m
export F_VIOLET=[35m
export F_CYAN=[36m
export F_GRIS=[37m
export CADRE_HAUT_BAS='	$(F_INVERSER)                                                                    $(F_NORMALE)'
export CADRE_COTERS='	$(F_INVERSER)  $(F_NORMALE)								  $(F_INVERSER)  $(F_NORMALE)'


CFLAGS= -g -Wall -D_REENTRANT

LDFLAGS=

LIB= -lpthread -lm

CC= g++ $(CFLAGS)
LD= g++

# Liste des fichiers
SRC=main.c         \
    display.c      \
    parameter.c

# Liste des objets
OBJ= $(SRC:.c=.o)

# Liste des dépendances
DEP= $(SRC:.c=.d)


#
BIN=hexViewer 
    
.PHONY: all
all: encadrer $(BIN)


encadrer:
ifneq ($(COLOR),normal)
	@echo $(CADRE_HAUT_BAS)
	@echo $(CADRE_COTERS)
	@echo '           DEBUT DE COMPILATION DU PROGRAMME :'$(CADRE_COTERS)
	@echo '                    $(F_VIOLET)$(BIN)$(F_NORMALE) '$(CADRE_COTERS)
	@echo $(CADRE_COTERS)
	@echo '          $(F_GRIS) Heero Yui Makefile                                 29-01-2010$(F_NORMALE)'$(CADRE_COTERS)
	@echo $(CADRE_HAUT_BAS)
endif

   
#
%.o: %.c
	@echo $(F_VERT)"     (.o)  $<"$(F_NORMALE)
	@$(CC) -o $@ -c $<

%.d: %.c
	@echo $(F_BLUE)"     (.d)  $<"$(F_NORMALE)
	@$(CC) -MM -MD -o $@ $< 
    
    
.PHONY: clean
clean:
	rm -f $(BIN) $(OBJ) $(DEP) *.i *.s *.bck

$(BIN):$(OBJ)
	@echo $(F_ROUGE)"     (bin) $@"$(F_NORMALE)
	@$(LD) -o $@ $^ $(LIB)
	
	
	
# inclusion des dependances
-include $(DEP)

