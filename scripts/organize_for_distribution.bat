@echo off
REM Organiza executáveis e DLLs compilados em estrutura limpa para distribuição
REM Uso: organize_for_distribution.bat

setlocal

set SCRIPT_DIR=%~dp0
set CLIENT_DIR=%SCRIPT_DIR%..
set DIST_DIR=%CLIENT_DIR%\dist\bin

echo Organizando arquivos para distribuicao...
echo.

REM Criar diretorio de distribuicao
if not exist "%DIST_DIR%" mkdir "%DIST_DIR%"

REM Limpar diretorio anterior
if exist "%DIST_DIR%\*" del /Q "%DIST_DIR%\*"

REM Copiar executavel
if exist "%CLIENT_DIR%\Designed_Chs\Project\Client\Release\fk.exe" (
    copy /Y "%CLIENT_DIR%\Designed_Chs\Project\Client\Release\fk.exe" "%DIST_DIR%\"
    echo [OK] fk.exe copiado
) else (
    echo [AVISO] fk.exe nao encontrado em Release
)

REM Copiar DLLs do Release
set RELEASE_DIR=%CLIENT_DIR%\Designed_Chs\Project\Client\Release
if exist "%RELEASE_DIR%" (
    copy /Y "%RELEASE_DIR%\*.dll" "%DIST_DIR%\" 2>nul
    echo [OK] DLLs do Release copiadas
)

REM Copiar DLLs de Designed_Common\Lib
set COMMON_LIB_DIR=%CLIENT_DIR%\Designed_Common\Lib
if exist "%COMMON_LIB_DIR%\*.dll" (
    copy /Y "%COMMON_LIB_DIR%\*.dll" "%DIST_DIR%\" 2>nul
    echo [OK] DLLs de Designed_Common\Lib copiadas
)

REM Copiar DEUtil.dll
if exist "%CLIENT_DIR%\Designed_Common\Project\Client\DEUtil\Release\DEUtil.dll" (
    copy /Y "%CLIENT_DIR%\Designed_Common\Project\Client\DEUtil\Release\DEUtil.dll" "%DIST_DIR%\"
    echo [OK] DEUtil.dll copiado
)

echo.
echo Organizacao concluida!
echo Arquivos em: %DIST_DIR%
echo.

endlocal
