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
    $(BIND)\zwterminateprocess_sleep$(DETOURS_BITS).dll \
    \
!IF $(DETOURS_SOURCE_BROWSING)==1
    $(OBJD)\zwterminateprocess_sleep$(DETOURS_BITS).bsc \
!ENDIF
    option

##############################################################################

dirs:
    @if not exist $(BIND) mkdir $(BIND) && echo.   Created $(BIND)
    @if not exist $(OBJD) mkdir $(OBJD) && echo.   Created $(OBJD)

$(OBJD)\zwterminateprocess_sleep.obj : zwterminateprocess_sleep.cpp

$(OBJD)\zwterminateprocess_sleep.res : zwterminateprocess_sleep.rc

$(BIND)\zwterminateprocess_sleep$(DETOURS_BITS).dll $(BIND)\zwterminateprocess_sleep$(DETOURS_BITS).lib: \
        $(OBJD)\zwterminateprocess_sleep.obj $(OBJD)\zwterminateprocess_sleep.res $(DEPS)
    cl /LD $(CFLAGS) /Fe$(@R).dll /Fd$(@R).pdb \
        $(OBJD)\zwterminateprocess_sleep.obj $(OBJD)\zwterminateprocess_sleep.res \
        /link $(LINKFLAGS) /subsystem:console \
        /export:DetourFinishHelperProcess,@1,NONAME \
        $(LIBS)

$(OBJD)\zwterminateprocess_sleep$(DETOURS_BITS).bsc : $(OBJD)\zwterminateprocess_sleep.obj
    bscmake /v /n /o $@ $(OBJD)\zwterminateprocess_sleep.sbr

##############################################################################

clean:
    -del *~ 2>nul
    -del $(BIND)\zwterminateprocess_sleep*.* 2>nul
    -rmdir /q /s $(OBJD) 2>nul

realclean: clean
    -rmdir /q /s $(OBJDS) 2>nul

############################################### Install non-bit-size binaries.

!IF "$(DETOURS_OPTION_PROCESSOR)" != ""

$(OPTD)\zwterminateprocess_sleep$(DETOURS_OPTION_BITS).dll:
$(OPTD)\zwterminateprocess_sleep$(DETOURS_OPTION_BITS).pdb:

$(BIND)\zwterminateprocess_sleep$(DETOURS_OPTION_BITS).dll : $(OPTD)\zwterminateprocess_sleep$(DETOURS_OPTION_BITS).dll
    @if exist $? copy /y $? $(BIND) >nul && echo $@ copied from $(DETOURS_OPTION_PROCESSOR).
$(BIND)\zwterminateprocess_sleep$(DETOURS_OPTION_BITS).pdb : $(OPTD)\zwterminateprocess_sleep$(DETOURS_OPTION_BITS).pdb
    @if exist $? copy /y $? $(BIND) >nul && echo $@ copied from $(DETOURS_OPTION_PROCESSOR).

option: \
    $(BIND)\zwterminateprocess_sleep$(DETOURS_OPTION_BITS).dll \
    $(BIND)\zwterminateprocess_sleep$(DETOURS_OPTION_BITS).pdb \

!ELSE

option:

!ENDIF