@echo off
set INPUT_DIR=tests
set OUTPUT_FILE=results\all_results.txt

if not exist results (
    mkdir results
)

echo BracketChecker2 Batch Test Results > %OUTPUT_FILE%
echo =================================== >> %OUTPUT_FILE%
echo. >> %OUTPUT_FILE%

for %%f in (%INPUT_DIR%\*.cpp) do (
    setlocal enabledelayedexpansion
    set "filename=%%~nxf"

    echo Testing !filename!... >> %OUTPUT_FILE%
    echo ---------- >> %OUTPUT_FILE%

    BracketChecker2.exe "%%f" "results\temp_result.txt"

    type results\temp_result.txt >> %OUTPUT_FILE%
    echo. >> %OUTPUT_FILE%
    echo. >> %OUTPUT_FILE%

    del results\temp_result.txt
    endlocal
)

echo Done! All results are in %OUTPUT_FILE%
pause
