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
    $(BIND)\terminateprocess_sleep$(DETOURS_BITS).dll \
    \
!IF $(DETOURS_SOURCE_BROWSING)==1
    $(OBJD)\terminateprocess_sleep$(DETOURS_BITS).bsc \
!ENDIF
    option

##############################################################################

dirs:
    @if not exist $(BIND) mkdir $(BIND) && echo.   Created $(BIND)
    @if not exist $(OBJD) mkdir $(OBJD) && echo.   Created $(OBJD)

$(OBJD)\terminateprocess_sleep.obj : terminateprocess_sleep.cpp

$(OBJD)\terminateprocess_sleep.res : terminateprocess_sleep.rc

$(BIND)\terminateprocess_sleep$(DETOURS_BITS).dll $(BIND)\terminateprocess_sleep$(DETOURS_BITS).lib: \
        $(OBJD)\terminateprocess_sleep.obj $(OBJD)\terminateprocess_sleep.res $(DEPS)
    cl /LD $(CFLAGS) /Fe$(@R).dll /Fd$(@R).pdb \
        $(OBJD)\terminateprocess_sleep.obj $(OBJD)\terminateprocess_sleep.res \
        /link $(LINKFLAGS) /subsystem:console \
        /export:DetourFinishHelperProcess,@1,NONAME \
        $(LIBS)

$(OBJD)\terminateprocess_sleep$(DETOURS_BITS).bsc : $(OBJD)\terminateprocess_sleep.obj
    bscmake /v /n /o $@ $(OBJD)\terminateprocess_sleep.sbr

##############################################################################

clean:
    -del *~ 2>nul
    -del $(BIND)\terminateprocess_sleep*.* 2>nul
    -rmdir /q /s $(OBJD) 2>nul

realclean: clean
    -rmdir /q /s $(OBJDS) 2>nul

############################################### Install non-bit-size binaries.

!IF "$(DETOURS_OPTION_PROCESSOR)" != ""

$(OPTD)\terminateprocess_sleep$(DETOURS_OPTION_BITS).dll:
$(OPTD)\terminateprocess_sleep$(DETOURS_OPTION_BITS).pdb:

$(BIND)\terminateprocess_sleep$(DETOURS_OPTION_BITS).dll : $(OPTD)\terminateprocess_sleep$(DETOURS_OPTION_BITS).dll
    @if exist $? copy /y $? $(BIND) >nul && echo $@ copied from $(DETOURS_OPTION_PROCESSOR).
$(BIND)\terminateprocess_sleep$(DETOURS_OPTION_BITS).pdb : $(OPTD)\terminateprocess_sleep$(DETOURS_OPTION_BITS).pdb
    @if exist $? copy /y $? $(BIND) >nul && echo $@ copied from $(DETOURS_OPTION_PROCESSOR).

option: \
    $(BIND)\terminateprocess_sleep$(DETOURS_OPTION_BITS).dll \
    $(BIND)\terminateprocess_sleep$(DETOURS_OPTION_BITS).pdb \

!ELSE

option:

!ENDIF