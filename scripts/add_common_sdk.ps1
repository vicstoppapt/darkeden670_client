# Script para adicionar referências ao common_sdk e diretórios de include necessários
# Suporta Client.vcxproj e lib.vcxproj
$vcxprojPath = "c:\darkeden-nostaugia\client\Designed_Chs\Project\Client\Client.vcxproj"
$libVcxprojPath = "c:\darkeden-nostaugia\client\Designed_Chs\Project\NEW - VS_UI\lib\lib.vcxproj"

$cp949 = [System.Text.Encoding]::GetEncoding(949)

# Função para processar um projeto específico
function Add-CommonSdkToProject {
    param(
        [string]$vcxprojPath,
        [string[]]$includeDirs,
        [string]$commonSdkInclude,
        [string]$commonSdkLib,
        [string]$commonSdkBin,
        [switch]$IsLibProject,
        [switch]$NeedsVirtualFileSystem,
        [switch]$NeedsDirectXSDK
    )
    
    if (-not (Test-Path $vcxprojPath)) {
        Write-Host "Arquivo não encontrado: $vcxprojPath" -ForegroundColor Yellow
        return
    }
    
    $content = $cp949.GetString([System.IO.File]::ReadAllBytes($vcxprojPath))
    $originalContent = $content

    # Detectar D3DLib automaticamente pelo caminho
    $isD3DLib = $vcxprojPath -match 'D3DLib[\\/]D3DLib\.vcxproj$'
    if ($isD3DLib) {
        $NeedsVirtualFileSystem = $true
    }

    # Para projeto lib, precisa de múltiplos diretórios para headers VS_UI, widgets, etc.
    if ($IsLibProject) {
        $libPchDir = "..\..\..\..\Designed_Common\Project\NEW - VS_UI\lib"
        $clientDir = "..\..\..\..\Designed_Common\Project\Client"
        $vsUiHeaderDir = "..\..\..\..\Designed_Common\Project\NEW - VS_UI\src\header"
        $vsUiHangulDir = "..\..\..\..\Designed_Common\Project\NEW - VS_UI\src\hangul"
        $vsUiWidgetDir = "..\..\..\..\Designed_Common\Project\NEW - VS_UI\src\widget"
        $vsUiImmDir = "..\..\..\..\Designed_Common\Project\NEW - VS_UI\src\Imm"
        $libUiDir = "..\..\..\..\Designed_Common\Lib\ui"
        $virtualFileSystemDir = "..\..\..\..\Designed_Common\Project\Client\VirtualFileSystem"
        $d3dLibDir = "..\..\..\..\Designed_Common\Project\Client\D3DLib"
        $spriteLibDir = "..\..\..\..\Designed_Common\Project\Client\SpriteLib"
        $frameLibDir = "..\..\..\..\Designed_Common\Project\Client\FrameLib"
        $sXmlDir = "..\..\..\..\Designed_Common\Project\Client\SXml"
        $commonSdkIncludeDir = "..\..\..\..\common_sdk\Include"
        
        $libIncludeDirs = "$libPchDir;$vsUiHeaderDir;$vsUiHangulDir;$vsUiWidgetDir;$vsUiImmDir;$libUiDir;$clientDir;$virtualFileSystemDir;$d3dLibDir;$spriteLibDir;$frameLibDir;$sXmlDir;$commonSdkIncludeDir"
        
        # Verificar se todos já existem
        $allDirsPresent = ($content -match [regex]::Escape($libPchDir)) -and
                         ($content -match [regex]::Escape($clientDir)) -and
                         ($content -match [regex]::Escape($vsUiHeaderDir)) -and
                         ($content -match [regex]::Escape($vsUiHangulDir)) -and
                         ($content -match [regex]::Escape($vsUiWidgetDir)) -and
                         ($content -match [regex]::Escape($vsUiImmDir)) -and
                         ($content -match [regex]::Escape($libUiDir)) -and
                         ($content -match [regex]::Escape($virtualFileSystemDir)) -and
                         ($content -match [regex]::Escape($d3dLibDir)) -and
                         ($content -match [regex]::Escape($spriteLibDir)) -and
                         ($content -match [regex]::Escape($frameLibDir)) -and
                         ($content -match [regex]::Escape($sXmlDir)) -and
                         ($content -match [regex]::Escape($commonSdkIncludeDir))
        
        if ($allDirsPresent) {
            Write-Host "Diretórios do lib já configurados." -ForegroundColor Yellow
            return
        }
        
        $newline = [Environment]::NewLine
        # Se já tem AdditionalIncludeDirectories, adicionar os que faltam
        if ($content -match '<AdditionalIncludeDirectories>([^<]+)</AdditionalIncludeDirectories>') {
            $existingDirs = $matches[1]
            $dirsToAdd = @()
            
            if ($existingDirs -notmatch [regex]::Escape($vsUiHeaderDir)) { $dirsToAdd += $vsUiHeaderDir }
            if ($existingDirs -notmatch [regex]::Escape($vsUiHangulDir)) { $dirsToAdd += $vsUiHangulDir }
            if ($existingDirs -notmatch [regex]::Escape($vsUiWidgetDir)) { $dirsToAdd += $vsUiWidgetDir }
            if ($existingDirs -notmatch [regex]::Escape($vsUiImmDir)) { $dirsToAdd += $vsUiImmDir }
            if ($existingDirs -notmatch [regex]::Escape($libUiDir)) { $dirsToAdd += $libUiDir }
            if ($existingDirs -notmatch [regex]::Escape($virtualFileSystemDir)) { $dirsToAdd += $virtualFileSystemDir }
            if ($existingDirs -notmatch [regex]::Escape($d3dLibDir)) { $dirsToAdd += $d3dLibDir }
            if ($existingDirs -notmatch [regex]::Escape($spriteLibDir)) { $dirsToAdd += $spriteLibDir }
            if ($existingDirs -notmatch [regex]::Escape($frameLibDir)) { $dirsToAdd += $frameLibDir }
            if ($existingDirs -notmatch [regex]::Escape($sXmlDir)) { $dirsToAdd += $sXmlDir }
            if ($existingDirs -notmatch [regex]::Escape($commonSdkIncludeDir)) { $dirsToAdd += $commonSdkIncludeDir }
            
            if ($dirsToAdd.Count -gt 0) {
                $additionalDirs = ($dirsToAdd -join ";")
                $content = $content -replace '(<AdditionalIncludeDirectories>)([^<]+)(</AdditionalIncludeDirectories>)', "`$1`$2;$additionalDirs`$3"
            }
        } else {
            # Adicionar ao ClCompile vazio
            $content = $content -replace '(<ClCompile>\s*</ClCompile>)', "<ClCompile>$newline      <AdditionalIncludeDirectories>$libIncludeDirs;%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>$newline    </ClCompile>"
        }
        
        # Adicionar WIN32 nas definições de pré-processador se não existir
        if ($content -notmatch '<PreprocessorDefinitions>WIN32') {
            # Adicionar PreprocessorDefinitions em cada ClCompile que não tem
            if ($content -match '(<ClCompile>\s*<AdditionalIncludeDirectories>[^<]+</AdditionalIncludeDirectories>\s*)</ClCompile>') {
                $content = $content -replace '(<ClCompile>\s*<AdditionalIncludeDirectories>[^<]+</AdditionalIncludeDirectories>\s*)</ClCompile>', "`$1$newline      <PreprocessorDefinitions>WIN32;%(PreprocessorDefinitions)</PreprocessorDefinitions>$newline    </ClCompile>"
            } elseif ($content -match '(<ClCompile>\s*<AdditionalIncludeDirectories>[^<]+</AdditionalIncludeDirectories>)') {
                $content = $content -replace '(<ClCompile>\s*<AdditionalIncludeDirectories>[^<]+</AdditionalIncludeDirectories>)', "`$1$newline      <PreprocessorDefinitions>WIN32;%(PreprocessorDefinitions)</PreprocessorDefinitions>"
            }
        }
        
        if ($content -ne $originalContent) {
            $bytes = $cp949.GetBytes($content)
            [System.IO.File]::WriteAllBytes($vcxprojPath, $bytes)
            Write-Host "Diretórios do lib configurados:" -ForegroundColor Green
            Write-Host "  - $libPchDir" -ForegroundColor Cyan
            Write-Host "  - $vsUiHeaderDir" -ForegroundColor Cyan
            Write-Host "  - $vsUiHangulDir" -ForegroundColor Cyan
            Write-Host "  - $vsUiWidgetDir" -ForegroundColor Cyan
            Write-Host "  - $vsUiImmDir" -ForegroundColor Cyan
            Write-Host "  - $libUiDir" -ForegroundColor Cyan
            Write-Host "  - $clientDir" -ForegroundColor Cyan
            Write-Host "  - $virtualFileSystemDir" -ForegroundColor Cyan
            Write-Host "  - $d3dLibDir" -ForegroundColor Cyan
            Write-Host "  - $spriteLibDir" -ForegroundColor Cyan
            Write-Host "  - $frameLibDir" -ForegroundColor Cyan
            Write-Host "  - $sXmlDir" -ForegroundColor Cyan
            Write-Host "  - $commonSdkIncludeDir" -ForegroundColor Cyan
        }
        return
    }
    
    # Adicionar VirtualFileSystem se necessário
    if ($NeedsVirtualFileSystem -and $content -notmatch [regex]::Escape("..\VirtualFileSystem")) {
        $virtualFileSystemDir = "..\VirtualFileSystem"
        if ($IsLibProject) {
            $virtualFileSystemDir = "..\..\..\..\Designed_Common\Project\Client\VirtualFileSystem"
        }
        if ($includeDirs.Count -eq 0) {
            $includeDirs = @($virtualFileSystemDir)
        } else {
            $includeDirs = @($virtualFileSystemDir) + $includeDirs
        }
    }
    
    # Adicionar common_sdk\Include se necessário para DirectX
    if ($NeedsDirectXSDK -and $commonSdkInclude -and $content -notmatch [regex]::Escape($commonSdkInclude)) {
        if ($includeDirs.Count -eq 0) {
            $includeDirs = @($commonSdkInclude)
        } else {
            $includeDirs = @($commonSdkInclude) + $includeDirs
        }
    }
    
    # Lógica para Client.vcxproj
    $allIncludes = $commonSdkInclude
    foreach ($dir in $includeDirs) {
        $allIncludes += ";$dir"
    }

    # Verificar se common_sdk já existe (mas pode faltar os outros diretórios)
    if ($content -match [regex]::Escape($commonSdkInclude)) {
        # Verificar se VirtualFileSystem já está nos includes
        if ($content -match [regex]::Escape($includeDirs[0])) {
            Write-Host "Todos os diretórios de include já estão configurados." -ForegroundColor Yellow
            return
        }
        # Se common_sdk existe mas faltam outros, adicionar apenas os que faltam
        $missingIncludes = ""
        foreach ($dir in $includeDirs) {
            if ($content -notmatch [regex]::Escape($dir)) {
                $missingIncludes += ";$dir"
            }
        }
        if ($missingIncludes) {
            # Adicionar diretórios faltantes aos AdditionalIncludeDirectories existentes
            $content = $content -replace '(<AdditionalIncludeDirectories>)([^<]+)(;%(AdditionalIncludeDirectories))', "`$1`$2$missingIncludes`$3"
        } else {
            Write-Host "Todos os diretórios de include já estão configurados." -ForegroundColor Yellow
            return
        }
    } else {
        # Se common_sdk não existe, adicionar tudo (caso ClCompile vazio ou sem AdditionalIncludeDirectories)
        $newline = [Environment]::NewLine
        
        # Substituir ClCompile vazio ou adicionar AdditionalIncludeDirectories
        if ($content -match '<ClCompile>\s*</ClCompile>') {
            $content = $content -replace '(<ClCompile>\s*</ClCompile>)', "<ClCompile>$newline      <AdditionalIncludeDirectories>$allIncludes;%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>$newline    </ClCompile>"
        } elseif ($content -match '<AdditionalIncludeDirectories>([^<]+)</AdditionalIncludeDirectories>') {
            # Adicionar aos existentes
            $content = $content -replace '(<AdditionalIncludeDirectories>)([^<]+)(</AdditionalIncludeDirectories>)', "`$1`$2;$allIncludes`$3"
        }
        
        # Substituir Link vazio por Link com AdditionalLibraryDirectories
        if ($content -match '<Link>\s*</Link>') {
            $content = $content -replace '(<Link>\s*</Link>)', "<Link>$newline      <AdditionalLibraryDirectories>$commonSdkLib;$commonSdkBin;%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>$newline    </Link>"
        }
    }
    
    # Adicionar WIN32 nas definições de pré-processador em TODAS as configurações
    # Usar regex para encontrar cada ItemDefinitionGroup e garantir WIN32 em cada um
    $newline = [Environment]::NewLine
    # Padrão para encontrar ItemDefinitionGroup com ClCompile que não tem WIN32
    $pattern = '(?s)(<ItemDefinitionGroup[^>]*>.*?<ClCompile>.*?)(?:(?=<PreprocessorDefinitions>WIN32)|(?=<PreprocessorDefinitions>)|(?=</ClCompile>))'
    if ($content -match $pattern) {
        # Adicionar WIN32 em cada ClCompile que não tem, dentro de cada ItemDefinitionGroup
        # Se ClCompile tem AdditionalIncludeDirectories mas não tem PreprocessorDefinitions
        $content = $content -replace '(?s)(<ItemDefinitionGroup[^>]*>.*?<ClCompile>.*?<AdditionalIncludeDirectories>[^<]+</AdditionalIncludeDirectories>)(\s*)(</ClCompile>)', "`$1$newline      <PreprocessorDefinitions>WIN32;%(PreprocessorDefinitions)</PreprocessorDefinitions>`$3"
        # Se ClCompile está vazio
        $content = $content -replace '(?s)(<ItemDefinitionGroup[^>]*>.*?<ClCompile>)(\s*)(</ClCompile>)', "`$1$newline      <PreprocessorDefinitions>WIN32;%(PreprocessorDefinitions)</PreprocessorDefinitions>$newline    `$3"
        # Se ClCompile tem PreprocessorDefinitions mas não tem WIN32
        $content = $content -replace '(?s)(<ItemDefinitionGroup[^>]*>.*?<ClCompile>.*?<PreprocessorDefinitions>)(?!.*WIN32)([^<]+)(</PreprocessorDefinitions>)', "`$1WIN32;`$2`$3"
    }
    # Fallback: se não encontrou ItemDefinitionGroup, usar método anterior
    if ($content -notmatch '<PreprocessorDefinitions>WIN32') {
        if ($content -match '(<ClCompile>\s*<AdditionalIncludeDirectories>[^<]+</AdditionalIncludeDirectories>\s*)</ClCompile>') {
            $content = $content -replace '(<ClCompile>\s*<AdditionalIncludeDirectories>[^<]+</AdditionalIncludeDirectories>\s*)</ClCompile>', "`$1$newline      <PreprocessorDefinitions>WIN32;%(PreprocessorDefinitions)</PreprocessorDefinitions>$newline    </ClCompile>"
        } elseif ($content -match '(<ClCompile>\s*<AdditionalIncludeDirectories>[^<]+</AdditionalIncludeDirectories>)') {
            $content = $content -replace '(<ClCompile>\s*<AdditionalIncludeDirectories>[^<]+</AdditionalIncludeDirectories>)', "`$1$newline      <PreprocessorDefinitions>WIN32;%(PreprocessorDefinitions)</PreprocessorDefinitions>"
        } elseif ($content -match '(<ClCompile>\s*)</ClCompile>') {
            $content = $content -replace '(<ClCompile>\s*)</ClCompile>', "`$1$newline      <PreprocessorDefinitions>WIN32;%(PreprocessorDefinitions)</PreprocessorDefinitions>$newline    </ClCompile>"
        }
    }
    
    if ($content -ne $originalContent) {
        # Salvar em CP949
        $bytes = $cp949.GetBytes($content)
        [System.IO.File]::WriteAllBytes($vcxprojPath, $bytes)
        
        Write-Host "Diretórios de include configurados com sucesso!" -ForegroundColor Green
        Write-Host "  - common_sdk\Include" -ForegroundColor Cyan
        foreach ($dir in $includeDirs) {
            Write-Host "  - $dir" -ForegroundColor Cyan
        }
    }
}

# Processar Client.vcxproj
$commonSdkInclude = "..\..\..\..\common_sdk\Include"
$commonSdkLib = "..\..\..\..\common_sdk\Lib"
$commonSdkBin = "..\..\..\..\common_sdk\bin"

$includeDirs = @(
    "..\..\..\Designed_Common\Project\Client\VirtualFileSystem",
    "..\..\..\Designed_Common\Project\Client",
    "..\..\..\Designed_Common\Project\Client\Packet",
    "..\..\..\Designed_Common\Project\Client\WinLib",
    "..\..\..\Designed_Common\Project\Client\FrameLib",
    "..\..\..\Designed_Common\Project\Client\RarLib",
    "..\..\..\Designed_Common\Project\NEW - VS_UI\src\header"
)

Add-CommonSdkToProject -vcxprojPath $vcxprojPath -includeDirs $includeDirs -commonSdkInclude $commonSdkInclude -commonSdkLib $commonSdkLib -commonSdkBin $commonSdkBin

# Processar lib.vcxproj
Add-CommonSdkToProject -vcxprojPath $libVcxprojPath -includeDirs @() -commonSdkInclude "" -commonSdkLib "" -commonSdkBin "" -IsLibProject
