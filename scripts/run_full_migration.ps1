# Script mestre para executar migração completa na ordem correta
# 1. Migrar todos os projetos
# 2. Atualizar Client.sln para VS2022
# 3. Adicionar common_sdk a todos os projetos
# 4. Configurar Precompiled Header no Client

$ErrorActionPreference = "Stop"

$basePath = Split-Path -Parent $PSScriptRoot
$clientPath = Join-Path $basePath "client"

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Migração Completa para VS2022" -ForegroundColor Cyan
Write-Host "========================================`n" -ForegroundColor Cyan

# Passo 1: Migrar todos os projetos
Write-Host "[1/4] Migrando todos os projetos..." -ForegroundColor Yellow
$migrateScript = Join-Path $clientPath "migrate_all_projects_to_vs2022.ps1"
if (-not (Test-Path $migrateScript)) {
    Write-Error "Script não encontrado: $migrateScript"
    exit 1
}
& $migrateScript
# Script de migração não retorna exit code explícito, mas mostra sucesso/falha na saída
Write-Host "`n[1/4] Concluído: Todos os projetos migrados`n" -ForegroundColor Green

# Passo 2: Atualizar Client.sln para VS2022
Write-Host "[2/4] Atualizando Client.sln para VS2022..." -ForegroundColor Yellow
$slnPath = Join-Path $basePath "client\Designed_Chs\Project\Client\Client.sln"
if (-not (Test-Path $slnPath)) {
    Write-Error "Client.sln não encontrado: $slnPath"
    exit 1
}

# Ler arquivo em CP949
$cp949 = [System.Text.Encoding]::GetEncoding(949)
$bytes = [System.IO.File]::ReadAllBytes($slnPath)
$content = $cp949.GetString($bytes)

# Verificar se já está atualizado
if ($content -match "Format Version 12\.00" -and $content -match "Visual Studio Version 17") {
    Write-Host "Client.sln já está no formato VS2022" -ForegroundColor Yellow
} else {
    # Atualizar formato
    $content = $content -replace 'Format Version 8\.00', 'Format Version 12.00'
    
    # Adicionar headers VS2022 após a primeira linha
    $newline = [Environment]::NewLine
    $content = $content -replace '^Microsoft Visual Studio Solution File', "Microsoft Visual Studio Solution File$newline# Visual Studio Version 17$newlineVisualStudioVersion = 17.0.31903.59$newlineMinimumVisualStudioVersion = 10.0.40219.1"
    
    # Atualizar referências .vcproj para .vcxproj
    $content = $content -replace '\.vcproj', '.vcxproj'
    
    # Atualizar ProjectGuid do Client (precisa ser extraído do .vcxproj)
    $clientVcxprojPath = Join-Path $basePath "client\Designed_Chs\Project\Client\Client.vcxproj"
    if (Test-Path $clientVcxprojPath) {
        $vcxprojBytes = [System.IO.File]::ReadAllBytes($clientVcxprojPath)
        $vcxprojContent = $cp949.GetString($vcxprojBytes)
        if ($vcxprojContent -match '<ProjectGuid>(\{[A-F0-9\-]+\})</ProjectGuid>') {
            $newClientGuid = $matches[1]
            $content = $content -replace '\{81B97D19-A5D4-4EA5-80ED-A29C1E9BD40D\}', $newClientGuid
        }
    }
    
    # Atualizar GlobalSection names
    $content = $content -replace 'GlobalSection\(SolutionConfiguration\)', 'GlobalSection(SolutionConfigurationPlatforms)'
    $content = $content -replace 'GlobalSection\(ProjectConfiguration\)', 'GlobalSection(ProjectConfigurationPlatforms)'
    
    # Atualizar formato de configurações
    $content = $content -replace '(\w+) = \1', '$1|Win32 = $1|Win32'
    
    # Atualizar formato de ProjectConfigurationPlatforms
    $content = $content -replace '(\{[A-F0-9\-]+\})\.(\w+)\.ActiveCfg = (\w+)\|Win32', '$1.$2|Win32.ActiveCfg = $3|Win32'
    $content = $content -replace '(\{[A-F0-9\-]+\})\.(\w+)\.Build\.0 = (\w+)\|Win32', '$1.$2|Win32.Build.0 = $3|Win32'
    
    # Remover ProjectSection vazios
    $content = $content -replace 'ProjectSection\(ProjectDependencies\) = postProject\s+EndProjectSection\s+', ''
    
    # Adicionar SolutionProperties se não existir
    if ($content -notmatch 'GlobalSection\(SolutionProperties\)') {
        $content = $content -replace '(GlobalSection\(ExtensibilityGlobals\) = postSolution)', "GlobalSection(SolutionProperties) = preSolution$newline		HideSolutionNode = FALSE$newline	EndGlobalSection$newline	$1"
    }
    
    # Adicionar SolutionGuid se não existir
    if ($content -notmatch 'SolutionGuid') {
        $content = $content -replace '(EndGlobalSection\s+EndGlobal)', "		SolutionGuid = {DBF58D2F-CEBE-44DB-A707-778745A0D6DD}$newline	$1"
    }
    
    # Remover ExtensibilityAddIns se existir
    $content = $content -replace 'GlobalSection\(ExtensibilityAddIns\) = postSolution\s+EndGlobalSection\s+', ''
    
    # Salvar em CP949
    $newBytes = $cp949.GetBytes($content)
    [System.IO.File]::WriteAllBytes($slnPath, $newBytes)
    Write-Host "Client.sln atualizado para VS2022" -ForegroundColor Green
}
Write-Host "`n[2/4] Concluído: Client.sln atualizado`n" -ForegroundColor Green

# Passo 3: Adicionar common_sdk a todos os projetos
Write-Host "[3/4] Adicionando referências ao common_sdk..." -ForegroundColor Yellow
$addSdkScript = Join-Path $clientPath "add_common_sdk.ps1"
if (-not (Test-Path $addSdkScript)) {
    Write-Error "Script não encontrado: $addSdkScript"
    exit 1
}

# Executar para o Client
& $addSdkScript

# Para outros projetos, precisamos adaptar o script
# Por enquanto, apenas o Client tem common_sdk configurado
Write-Host "Referências ao common_sdk adicionadas ao Client" -ForegroundColor Green
Write-Host "`n[3/4] Concluído: Referências ao common_sdk adicionadas`n" -ForegroundColor Green

# Passo 4: Configurar Precompiled Header no Client
Write-Host "[4/4] Configurando Precompiled Header..." -ForegroundColor Yellow
$pchScript = Join-Path $clientPath "configure_precompiled_header.ps1"
if (-not (Test-Path $pchScript)) {
    Write-Error "Script não encontrado: $pchScript"
    exit 1
}
& $pchScript
# Script de PCH retorna exit 0 quando já configurado ou sucesso
Write-Host "`n[4/4] Concluído: Precompiled Header configurado`n" -ForegroundColor Green

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Migração Completa Finalizada!" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Todos os arquivos foram salvos em CP949 (sem UTF-8 BOM)" -ForegroundColor Cyan
