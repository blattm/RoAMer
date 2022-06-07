@ECHO OFF
setlocal enabledelayedexpansion


for /F "usebackq delims=" %%F in (`dir "hooks/hooks" /b /ad-h`) do (
    echo %%F
    cd /d "hooks/hooks/%%F"
    nmake
    cd "..\..\..\"
)

SET DETOURS_TARGET_PROCESSOR=X64

for /F "usebackq delims=" %%F in (`dir "hooks/hooks" /b /ad-h`) do (
    echo %%F
    cd /d "hooks/hooks/%%F"
    nmake
    cd "..\..\..\"
)