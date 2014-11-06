##
## Makefile for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
## 
## Made by otoshigami
## Login   <otoshigami@epitech.net>
## 
## Started on  Sun Jun 15 08:48:53 2014 otoshigami
## Last update Thu Nov  6 21:44:49 2014 guerot
##

## FILES

NAME		=	babel_server

SRC		=	main			\
			PAAudioService		\
			APAAudioStream		\
			PAAudioInputStream	\
			PAAudioOutputStream	\
			PAAudioDevice		\
			CircularBuffer		\
			AudioRecorder		\
			AudioPlayer		\
			AudioBuffer		\
			SampleFormat

SRC_EXT		=	.cpp

## DIRECTORIES

DOBJ		=	obj
DSRC		=	src
DBIN		=	.

## COMPILATION

DINC		=	include		\
			template

CFLAGS		=	-Wall		\
			-Wextra

MAKED		=	make --no-print-directory -C

## LINKAGE

LIB		=	rt		\
			asound		\
			jack		\
			pthread

DLIB		=

LDFLAGS		=

## RUNS

CC		=	g++ -fmax-errors=10
# CC		=	clang++ -ferror-limit=5
RM		=	rm -rf
MD		=	mkdir -p

####################
## INTERNAL RULES ##
####################

## CONSTANTS

DBGBOOL		=	yes

PROFILE		=	no

DBG		=	-g3		\
			-ggdb

WERROR		=	-Werror

## FILES

OBJ		=	$(addsuffix .o, $(SRC))
_SRC		=	$(addsuffix $(SRC_EXT), $(SRC))

## DIRECTORIES

DINC		:=	$(addsuffix /, $(DINC))
DOBJ		:=	$(addsuffix /, $(DOBJ))
DSRC		:=	$(addsuffix /, $(DSRC))
DBIN		:=	$(addsuffix /, $(DBIN))

## COMPILATION ARGS

CINC		=	$(addprefix -I, $(DINC))

COBJ		=	$(addprefix $(DOBJ), $(OBJ))
CSRC		=	$(addprefix $(DSRC), $(_SRC))
CNAME		=	$(addprefix $(DBIN), $(NAME))

## LINKAGE ARGS

LIB		:=	$(addprefix -l, $(LIB))
DLIB		:=	$(addsuffix /, $(DLIB))
DLIB		:=	$(addprefix -L, $(DLIB))

## FLAGS

ifeq ($(DBGBOOL), yes)
	CFLAGS  += $(DBG)
endif

ifeq ($(DBGBOOL), no)
	CFLAGS	+= $(WERROR)
endif

ifeq ($(PROFILE), yes)
	CFLAGS	+= -pg
	LDFLAGS += -pg
endif

CFLAGS		+=	$(CINC)
LDFLAGS		+=	$(DLIB)				\
			libportaudio.a			\
			$(LIB)


## MISC RULES

MAKEOBJ		= $(addprefix $(DOBJ), %.o) : $(addprefix $(addprefix $(DSRC), %), $(SRC_EXT))

all:	$(CNAME)

dbg:	$(CNAME)

$(CNAME):	$(COBJ)
		@$(MD) $(DBIN)
		@echo "Linkage : $(CNAME)"
		@$(CC) $(COBJ) -o $(CNAME) $(LDFLAGS)

$(COBJ):	$(MAKEOBJ)
		@$(MD) $(DOBJ)
		@for dir in `cd $(DSRC); ls -d */ 2> /dev/null`; \
		do \
		if [ ! -d "$(DOBJ)$$dir" ];then \
			$(MD) $(DOBJ)$$dir; \
		fi \
		done
		@echo "Compilation : $<"
		@$(CC) -c $< -o $@ $(CFLAGS)

clean:
		@$(RM) $(COBJ)

fclean:		clean
		@$(RM) $(CNAME)

re:		fclean all
redbg:		fclean dbg

.PHONY:		fclean clean all dbg re
