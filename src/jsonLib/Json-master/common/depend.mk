## ----------------------------------------------------------------------------
## "THE BEER-WARE LICENSE" (Revision 42):
## <benjamin.viguier@epitech.eu> wrote this file. As long as you retain this 
## notice you can do whatever you want with this stuff. If we meet some day,
## and you think this stuff is worth it, you can buy me a beer in
## return Benjamin Viguier
## ----------------------------------------------------------------------------

CC		=	gcc
CPP		=	g++
ifdef COMPILO
 CPP		=	$(COMPILO)
 CC			=	$(COMPILO)
endif

AR		=	ar rc
ifdef STATIC_LK
  AR  = $(STATIC_LK)
endif

ifndef	DEBUG
 DEBUG	=	true
endif

ifndef	WALL
 WALL		=	false
endif

ifndef	RELEASE
 RELEASE	=	true
endif

ifndef	OPTI_FLAG
 OPTI_FLAG	=	-O3
endif

ifndef  OUTPATH
 OUTPATH = .
endif

ifndef	CPPFLAGS
  CPPFLAGS	+=	-W -Wall -Wextra
endif

ifeq	($(WALL),true)
  CPPFLAGS	+=	-W -Wall -Wextra
endif

ifndef TARGET
  TARGET=linux
endif

ifeq	($(RELEASE),true)
  CPPFLAGS	+=	$(OPTI_FLAG)
  CPPFLAGS	+= -Wno-unused-result
  ifneq ($(TARGET),windows)
    CPPFLAGS	+= -Werror
  endif
  DEBUG		=	false
else
  CPPFLAGS	+=	-O0
endif

ifeq  ($(FORCE_DEBUG), true)
  DEBUG = true
endif

ifeq	($(DEBUG),true)
  CPPFLAGS	+=	-D DEBUG_ON -g
endif

ifeq	($(shell uname -s),Darwin)
  CPPFLAGS	+=	-fno-common
endif

CFLAGS		=	$(CPPFLAGS)

CFLAGS		+=	-std=c11
CPPFLAGS	+=	-std=c++14

ODIR		=	objs

SDIR		=	srcs

# COLORS
DEFAULT		=	'\033[0m'
WHITE		=	'\033[0;97m'
BLACK		=	'\033[1;30m'
RED		=	'\033[1;31m'
GREEN		=	'\033[1;92m'
YELLOW		=	'\033[1;33m'
BLUE		=	'\033[1;34m'
MAGENTA		=	'\033[1;35m'
CYAN		=	'\033[1;36m'
