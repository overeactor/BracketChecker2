@echo off
setlocal enabledelayedexpansion

set "INPUT_DIR=tests"
set "OUTPUT_FILE=results\all_results.txt"

if not exist results (
    mkdir results
)

echo BracketChecker2 Batch Test Results > "%OUTPUT_FILE%"
echo =================================== >> "%OUTPUT_FILE%"
echo. >> "%OUTPUT_FILE%"

rem Fixed order of test files
for %%f in (
    test1_simple.cpp
    test2_strings.cpp
    test3_char.cpp
    test4_complex.cpp
    test5_unmatched.cpp
    test6_wrong_closing.cpp
    test7_1001_lines.cpp
    test8_1001_chars.cpp
    test9_define.cpp
    test10_empty.cpp
    test11_not_cpp.txt
    test13_not_opened.cpp
    test14_string_literal.cpp
    test15_string_literal.cpp
) do (
    set "filename=%%f"
    set "ext=%%~xf"
    set "filepath=%INPUT_DIR%\%%f"

    rem Set description
    set "description="
    if "%%f"=="test1_simple.cpp" set "description=Testing simple bracket matching."
    if "%%f"=="test2_strings.cpp" set "description=Testing brackets inside strings."
    if "%%f"=="test3_char.cpp" set "description=Testing brackets inside character literals."
    if "%%f"=="test4_complex.cpp" set "description=Testing complex nesting and mixed types."
    if "%%f"=="test5_unmatched.cpp" set "description=Testing unmatched opening brackets."
    if "%%f"=="test6_wrong_closing.cpp" set "description=Testing wrong closing brackets."
    if "%%f"=="test7_1001_lines.cpp" set "description=Testing code with 1001 lines (TOO_LONG_PROGRAM)."
    if "%%f"=="test8_1001_chars.cpp" set "description=Testing line with 1001 characters (TOO_LONG_LINE)."
    if "%%f"=="test9_define.cpp" set "description=Testing macro usage (#define detection)."
    if "%%f"=="test10_empty.cpp" set "description=Testing completely empty file."
    if "%%f"=="test11_not_cpp.txt" set "description=Testing a non-C++ file (should be ignored or flagged)."
    if "%%f"=="test13_not_opened.cpp" set "description=Not opened bracket"
    if "%%f"=="test14_string_literal.cpp" set "description=No matched bracket after \""
    if "%%f"=="test15_string_literal.cpp" set "description=No matched bracket in string literal"

    if /I "%%~xf"==".cpp" (
        echo Running %%f >> "%OUTPUT_FILE%"
        echo Description: !description! >> "%OUTPUT_FILE%"
        echo ---------- >> "%OUTPUT_FILE%"

        BracketChecker2.exe "!filepath!" "results\temp_result.txt"

        if exist results\temp_result.txt (
            echo === Result === >> "%OUTPUT_FILE%"
            type results\temp_result.txt >> "%OUTPUT_FILE%"
            echo. >> "%OUTPUT_FILE%"
            del results\temp_result.txt
        ) else (
            echo [ERROR] BracketChecker2.exe failed or produced no output for %%f >> "%OUTPUT_FILE%"
            echo. >> "%OUTPUT_FILE%"
        )
    ) else (
        echo Skipping %%f – not a .cpp file. >> "%OUTPUT_FILE%"
        echo Description: !description! >> "%OUTPUT_FILE%"
        echo. >> "%OUTPUT_FILE%"
    )
)

echo Done! All results are in %OUTPUT_FILE%
pause
