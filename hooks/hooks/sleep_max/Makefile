##############################################################################
##  Based on:
##
##  Makefile for Detours Test Programs.
##
##  Microsoft Research Detours Package
##
##  Copyright (c) Microsoft Corporation.  All rights reserved.
##

# !include ..\common.mak

# LIBS=$(LIBS) kernel32.lib

# all: dirs \
#     $(BIND)\sleep_max_3.exe \
# !IF $(DETOURS_SOURCE_BROWSING)==1
#     $(OBJD)\sleep_max_3.bsc \
# !ENDIF
#     option

# ##############################################################################

# clean:
#     -del *~ 2>nul
#     -del $(BIND)\sleep_max_3.* 2>nul
#     -rmdir /q /s $(OBJD) 2>nul

# realclean: clean
#     -rmdir /q /s $(OBJDS) 2>nul

# ##############################################################################

# dirs:
#     @if not exist $(BIND) mkdir $(BIND) && echo.   Created $(BIND)
#     @if not exist $(OBJD) mkdir $(OBJD) && echo.   Created $(OBJD)

# $(OBJD)\sleep_max_3.obj : sleep_max_3.cpp

# $(BIND)\sleep_max_3.exe : $(OBJD)\sleep_max_3.obj $(DEPS)
#     cl $(CFLAGS) /Fe$@ /Fd$(@R).pdb $(OBJD)\sleep_max_3.obj \
#         /link $(LINKFLAGS) $(LIBS) /subsystem:console \
#         /export:DetourFinishHelperProcess,@1,NONAME \
#         /export:SleepExMax3 \

# $(OBJD)\sleep_max_3.bsc : $(OBJD)\sleep_max_3.obj
#     bscmake /v /n /o $@ $(OBJD)\sleep_max_3.sbr







!include ..\common.mak

LIBS=$(LIBS) kernel32.lib

##############################################################################

all: dirs \
    $(BIND)\sleep_max_3$(DETOURS_BITS).dll \
    $(BIND)\sleep5.exe \
    \
!IF $(DETOURS_SOURCE_BROWSING)==1
    $(OBJD)\sleep_max_3$(DETOURS_BITS).bsc \
    $(OBJD)\sleep5.bsc \
!ENDIF
    option

##############################################################################

dirs:
    @if not exist $(BIND) mkdir $(BIND) && echo.   Created $(BIND)
    @if not exist $(OBJD) mkdir $(OBJD) && echo.   Created $(OBJD)

$(OBJD)\sleep_max_3.obj : sleep_max_3.cpp

$(OBJD)\sleep_max_3.res : sleep_max_3.rc

$(BIND)\sleep_max_3$(DETOURS_BITS).dll $(BIND)\sleep_max_3$(DETOURS_BITS).lib: \
        $(OBJD)\sleep_max_3.obj $(OBJD)\sleep_max_3.res $(DEPS)
    cl /LD $(CFLAGS) /Fe$(@R).dll /Fd$(@R).pdb \
        $(OBJD)\sleep_max_3.obj $(OBJD)\sleep_max_3.res \
        /link $(LINKFLAGS) /subsystem:console \
        /export:DetourFinishHelperProcess,@1,NONAME \
        /export:SleepExMax3 \
        /export:SleepMax3 \
        $(LIBS)

$(OBJD)\sleep_max_3$(DETOURS_BITS).bsc : $(OBJD)\sleep_max_3.obj
    bscmake /v /n /o $@ $(OBJD)\sleep_max_3.sbr

$(OBJD)\sleep5.obj : sleep5.cpp

$(BIND)\sleep5.exe : $(OBJD)\sleep5.obj $(DEPS)
    cl $(CFLAGS) /Fe$@ /Fd$(@R).pdb $(OBJD)\sleep5.obj \
        /link $(LINKFLAGS) $(LIBS) \
        /subsystem:console

$(OBJD)\sleep5.bsc : $(OBJD)\sleep5.obj
    bscmake /v /n /o $@ $(OBJD)\sleep5.sbr

##############################################################################

clean:
    -del *~ 2>nul
    -del $(BIND)\sleep_max_3*.* 2>nul
    -del $(BIND)\sleep5.* 2>nul
    -rmdir /q /s $(OBJD) 2>nul

realclean: clean
    -rmdir /q /s $(OBJDS) 2>nul

############################################### Install non-bit-size binaries.

!IF "$(DETOURS_OPTION_PROCESSOR)" != ""

$(OPTD)\sleep_max_3$(DETOURS_OPTION_BITS).dll:
$(OPTD)\sleep_max_3$(DETOURS_OPTION_BITS).pdb:

$(BIND)\sleep_max_3$(DETOURS_OPTION_BITS).dll : $(OPTD)\sleep_max_3$(DETOURS_OPTION_BITS).dll
    @if exist $? copy /y $? $(BIND) >nul && echo $@ copied from $(DETOURS_OPTION_PROCESSOR).
$(BIND)\sleep_max_3$(DETOURS_OPTION_BITS).pdb : $(OPTD)\sleep_max_3$(DETOURS_OPTION_BITS).pdb
    @if exist $? copy /y $? $(BIND) >nul && echo $@ copied from $(DETOURS_OPTION_PROCESSOR).

option: \
    $(BIND)\sleep_max_3$(DETOURS_OPTION_BITS).dll \
    $(BIND)\sleep_max_3$(DETOURS_OPTION_BITS).pdb \

!ELSE

option:

!ENDIF