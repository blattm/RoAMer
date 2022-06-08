##############################################################################
##  Based on:
##
##  Makefile for Detours Test Programs.
##
##  Microsoft Research Detours Package
##
##  Copyright (c) Microsoft Corporation.  All rights reserved.
##


!include ..\common.mak

LIBS=$(LIBS) kernel32.lib

##############################################################################

all: dirs \
    $(BIND)\exitprocess_sleep$(DETOURS_BITS).dll \
    \
!IF $(DETOURS_SOURCE_BROWSING)==1
    $(OBJD)\exitprocess_sleep$(DETOURS_BITS).bsc \
!ENDIF
    option

##############################################################################

dirs:
    @if not exist $(BIND) mkdir $(BIND) && echo.   Created $(BIND)
    @if not exist $(OBJD) mkdir $(OBJD) && echo.   Created $(OBJD)

$(OBJD)\exitprocess_sleep.obj : exitprocess_sleep.cpp

$(OBJD)\exitprocess_sleep.res : exitprocess_sleep.rc

$(BIND)\exitprocess_sleep$(DETOURS_BITS).dll $(BIND)\exitprocess_sleep$(DETOURS_BITS).lib: \
        $(OBJD)\exitprocess_sleep.obj $(OBJD)\exitprocess_sleep.res $(DEPS)
    cl /LD $(CFLAGS) /Fe$(@R).dll /Fd$(@R).pdb \
        $(OBJD)\exitprocess_sleep.obj $(OBJD)\exitprocess_sleep.res \
        /link $(LINKFLAGS) /subsystem:console \
        /export:DetourFinishHelperProcess,@1,NONAME \
        $(LIBS)

$(OBJD)\exitprocess_sleep$(DETOURS_BITS).bsc : $(OBJD)\exitprocess_sleep.obj
    bscmake /v /n /o $@ $(OBJD)\exitprocess_sleep.sbr

##############################################################################

clean:
    -del *~ 2>nul
    -del $(BIND)\exitprocess_sleep*.* 2>nul
    -rmdir /q /s $(OBJD) 2>nul

realclean: clean
    -rmdir /q /s $(OBJDS) 2>nul

############################################### Install non-bit-size binaries.

!IF "$(DETOURS_OPTION_PROCESSOR)" != ""

$(OPTD)\exitprocess_sleep$(DETOURS_OPTION_BITS).dll:
$(OPTD)\exitprocess_sleep$(DETOURS_OPTION_BITS).pdb:

$(BIND)\exitprocess_sleep$(DETOURS_OPTION_BITS).dll : $(OPTD)\exitprocess_sleep$(DETOURS_OPTION_BITS).dll
    @if exist $? copy /y $? $(BIND) >nul && echo $@ copied from $(DETOURS_OPTION_PROCESSOR).
$(BIND)\exitprocess_sleep$(DETOURS_OPTION_BITS).pdb : $(OPTD)\exitprocess_sleep$(DETOURS_OPTION_BITS).pdb
    @if exist $? copy /y $? $(BIND) >nul && echo $@ copied from $(DETOURS_OPTION_PROCESSOR).

option: \
    $(BIND)\exitprocess_sleep$(DETOURS_OPTION_BITS).dll \
    $(BIND)\exitprocess_sleep$(DETOURS_OPTION_BITS).pdb \

!ELSE

option:

!ENDIF