
## FILES

NAME		=	babel_server

SRC		=	main			\
			Babel			\
			BoostAsyncService	\
			TcpAsyncServer		\
			BoostTcpAsyncServer	\
			TcpAsyncClient		\
			BoostTcpAsyncClient	\
			BoostAsyncTimer		\
			AsyncTimer		\
			BabelServer		\
			BabelClient

SRC_EXT		=	.cpp

## DIRECTORIES

DOBJ		=	obj
DSRC		=	src
DBIN		=	.

## COMPILATION

DINC		=	include		\
			template

CFLAGS		=	-Wextra

MAKED		=	make --no-print-directory -C

## LINKAGE

LIB		=	boost_system

DLIB		=

LDFLAGS		=

## RUNS

CC		=	g++ -fmax-errors=5
# CC		=	clang++ -ferror-limit=5
RM		=	rm -rf
MD		=	mkdir -p

####################
## INTERNAL RULES ##
####################

## CONSTANTS

DBGBOOL		=	no

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
