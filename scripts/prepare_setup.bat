@echo off
REM Prepara estrutura completa de distribuicao para criacao de instalador
REM Uso: prepare_setup.bat

setlocal

set SCRIPT_DIR=%~dp0
set CLIENT_DIR=%SCRIPT_DIR%..
set DIST_DIR=%CLIENT_DIR%\dist
set DIST_BIN=%DIST_DIR%\bin
set DIST_DATA=%DIST_DIR%\data

echo Preparando estrutura de distribuicao...
echo.

REM Criar estrutura de diretorios
if not exist "%DIST_DIR%" mkdir "%DIST_DIR%"
if not exist "%DIST_BIN%" mkdir "%DIST_BIN%"
if not exist "%DIST_DATA%" mkdir "%DIST_DATA%"

REM Limpar diretorios anteriores
if exist "%DIST_BIN%\*" del /Q "%DIST_BIN%\*"
if exist "%DIST_DATA%\*" del /S /Q "%DIST_DATA%\*"

echo [1/3] Organizando binarios...
call "%SCRIPT_DIR%organize_for_distribution.bat"

echo.
echo [2/3] Copiando dados do jogo...

REM Copiar estrutura de dados de nostaugia
set NOSTAUGIA_DIR=%CLIENT_DIR%\nostaugia
if exist "%NOSTAUGIA_DIR%\data" (
    xcopy /E /I /Y "%NOSTAUGIA_DIR%\data\*" "%DIST_DATA%\" >nul
    echo [OK] Dados do jogo copiados
) else (
    echo [AVISO] Pasta data nao encontrada em nostaugia
)

REM Copiar arquivos de configuracao para raiz (serao copiados para raiz na instalacao)
if exist "%NOSTAUGIA_DIR%\*.inf" (
    copy /Y "%NOSTAUGIA_DIR%\*.inf" "%DIST_DIR%\" 2>nul
    echo [OK] Arquivos .inf copiados
)
if exist "%NOSTAUGIA_DIR%\*.ini" (
    copy /Y "%NOSTAUGIA_DIR%\*.ini" "%DIST_DIR%\" 2>nul
    echo [OK] Arquivos .ini copiados
)
if exist "%NOSTAUGIA_DIR%\*.txt" (
    copy /Y "%NOSTAUGIA_DIR%\*.txt" "%DIST_DIR%\" 2>nul
    echo [OK] Arquivos .txt copiados
)

echo.
echo [3/3] Estrutura de distribuicao preparada!
echo.
echo Estrutura criada:
echo   %DIST_BIN%     - Executaveis e DLLs
echo   %DIST_DATA%    - Dados do jogo
echo   %DIST_DIR%     - Arquivos de configuracao
echo.
echo Proximo passo: Criar instalador usando Inno Setup ou VS Installer Projects
echo.

endlocal
