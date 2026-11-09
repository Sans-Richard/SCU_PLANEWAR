@echo off
setlocal enabledelayedexpansion

echo ========================================
echo   PlaneWar 发布打包脚本
echo ========================================
echo.

set "QT_DIR=D:\Qt\5.14.2\mingw73_32"
set "SRC_EXE=build-PlanWar-Desktop_Qt_5_14_2_MinGW_32_bit-Release\release\PlaneWar.exe"
set "OUT_DIR=PlaneWar_Release"

echo [1/4] 创建发布目录并复制 exe...
if not exist "%OUT_DIR%" mkdir "%OUT_DIR%"
copy /y "%SRC_EXE%" "%OUT_DIR%\" >nul
echo       完成.

echo [2/4] 复制 Qt DLL 和 MinGW 运行时...
copy /y "%QT_DIR%\bin\Qt5Core.dll" "%OUT_DIR%\" >nul
copy /y "%QT_DIR%\bin\Qt5Gui.dll" "%OUT_DIR%\" >nul
copy /y "%QT_DIR%\bin\Qt5Widgets.dll" "%OUT_DIR%\" >nul
copy /y "%QT_DIR%\bin\libgcc_s_dw2-1.dll" "%OUT_DIR%\" >nul
copy /y "%QT_DIR%\bin\libstdc++-6.dll" "%OUT_DIR%\" >nul
copy /y "%QT_DIR%\bin\libwinpthread-1.dll" "%OUT_DIR%\" >nul
echo       完成.

echo [3/4] 复制平台插件 (platforms)...
if not exist "%OUT_DIR%\platforms" mkdir "%OUT_DIR%\platforms"
copy /y "%QT_DIR%\plugins\platforms\qwindows.dll" "%OUT_DIR%\platforms\" >nul
echo       完成.

echo [4/4] 复制资源文件夹...
if exist "PlaneWar\resource" (
    if not exist "%OUT_DIR%\resource" mkdir "%OUT_DIR%\resource"
    xcopy /E /Y "PlaneWar\resource\*" "%OUT_DIR%\resource\" >nul
    echo       资源文件夹已复制.
) else (
    echo       [警告] PlaneWar\resource 文件夹不存在, 跳过.
)

echo.
echo ========================================
echo   打包完成!
echo   输出目录: %OUT_DIR%
echo ========================================
echo.
echo 目录内容:
dir "%OUT_DIR%"
echo.
echo 要分发给别人, 请把整个 "%OUT_DIR%" 文件夹
echo 压缩成 zip 文件发给他们即可.
echo 对方解压后双击 PlaneWar.exe 就能玩了!
echo.
pause