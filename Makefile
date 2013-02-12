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

VERSION_TAG_SHORT=$(shell git describe --tags --abbrev=0)
#$(info $(VERSION_TAG_SHORT))

VERSION_BUILD_TIME=$(shell date)
#$(info $(VERSION_BUILD_TIME))

CFLAGS= -g -Wall -D_REENTRANT

LDFLAGS=

LIB= -lpthread -lm

CC= g++ $(CFLAGS)
LD= g++

# List of Sources
SRC=main.c         \
    display.c      \
    parameter.c

# List of Objects
OBJ= $(SRC:.c=.o)

# List of dependances
DEP= $(SRC:.c=.d)

PROG_NAME=hexViewer

.PHONY: all
all: $(PROG_NAME)

%.o: %.c
	@echo $(F_VERT)"     (.o)  $<"$(F_NORMALE)
	@$(CC) -o $@ -c $<

%.d: %.c
	@echo $(F_BLUE)"     (.d)  $<"$(F_NORMALE)
	@$(CC) -MM -MD -o $@ $< 

.PHONY: clean
clean:
	rm -f $(PROG_NAME) $(OBJ) $(DEP) *.i *.s *.bck

$(PROG_NAME):$(OBJ)
	@echo $(F_ROUGE)"     (bin) $@"$(F_NORMALE)
	@$(LD) -o $@ $^ $(LIB)

# inclusion des dependances
-include $(DEP)

.PHONY: package
# http://alp.developpez.com/tutoriels/debian/creer-paquet/
package: all
	@echo 'Create packages ...'
	@mkdir -p package/$(PROG_NAME)/DEBIAN/
	@mkdir -p package/$(PROG_NAME)/usr/bin/
	@mkdir -p package/$(PROG_NAME)/usr/share/doc/
	@mkdir -p package/$(PROG_NAME)/usr/share/edn/
	# Create the control file
	@echo "Package: "$(PROG_NAME) > package/$(PROG_NAME)/DEBIAN/control
	@echo "Version: "$(VERSION_TAG_SHORT) >> package/$(PROG_NAME)/DEBIAN/control
	@echo "Section: Development,Editors" >> package/$(PROG_NAME)/DEBIAN/control
	@echo "Priority: optional" >>package/$(PROG_NAME)/DEBIAN/control
	@echo "Architecture: all" >> package/$(PROG_NAME)/DEBIAN/control
	@echo "Depends: bash" >> package/$(PROG_NAME)/DEBIAN/control
	@echo "Maintainer: Mr DUPIN Edouard <yui.heero@gmail.com>" >> package/$(PROG_NAME)/DEBIAN/control
	@echo "Description: Binary comparator for shell console" >> package/$(PROG_NAME)/DEBIAN/control
	@echo "" >> package/$(PROG_NAME)/DEBIAN/control
	# Create the PostRm
	@#echo "#!/bin/bash" > package/$(PROG_NAME)/DEBIAN/postrm
	@#echo "rm ~/."$(PROG_NAME) >> package/$(PROG_NAME)/DEBIAN/postrm
	@#echo "" >> package/$(PROG_NAME)/DEBIAN/postrm
	# Enable Execution in script
	@#chmod 755 package/$(PROG_NAME)/DEBIAN/post*
	@#chmod 755 package/$(PROG_NAME)/DEBIAN/pre*
	# copy licence and information : 
	@cp README package/$(PROG_NAME)/usr/share/doc/README
	@cp licence.txt package/$(PROG_NAME)/usr/share/doc/copyright
	@echo "First generation in progress" > package/$(PROG_NAME)/usr/share/doc/changelog
	@cp -vf $(PROG_NAME) package/$(PROG_NAME)/usr/bin/
	@#cp -vf data/*.xml package/$(PROG_NAME)/usr/share/edn/
	@cd package; dpkg-deb --build $(PROG_NAME)

install:
	sudo cp -fv hexViewer /usr/bin/hexViewer


