# Script para migrar todos os projetos de .vcproj para .vcxproj (VS2022)
# Todos os arquivos são salvos em CP949 (sem UTF-8 BOM)

$ErrorActionPreference = "Stop"

# Caminho base
$basePath = Split-Path -Parent $PSScriptRoot
$modulesPath = Join-Path $basePath "modernization\scripts\Modules"

# Verificar se os módulos existem
if (-not (Test-Path $modulesPath)) {
    Write-Host "ERRO: Módulos não encontrados em: $modulesPath" -ForegroundColor Red
    exit 1
}

# Importar módulos
Write-Host "Importando módulos..." -ForegroundColor Cyan
Import-Module (Join-Path $modulesPath "ProjectModernization.psm1") -Force
Import-Module (Join-Path $modulesPath "PathAndStructure.psm1") -Force

# Lista de projetos para migrar
$projects = @(
    @{
        Name = "Client"
        Path = Join-Path $basePath "client\Designed_Chs\Project\Client"
        VcprojName = "Client.vcproj"
    },
    @{
        Name = "CWinMain Library"
        Path = Join-Path $basePath "client\Designed_Common\Project\Client\CWinMain Library"
        VcprojName = "CWinMain Library.vcproj"
    },
    @{
        Name = "D3DLib"
        Path = Join-Path $basePath "client\Designed_Common\Project\Client\D3DLib"
        VcprojName = "D3DLib.vcproj"
    },
    @{
        Name = "DEUtil"
        Path = Join-Path $basePath "client\Designed_Common\Project\Client\DEUtil"
        VcprojName = "DEUtil.vcproj"
    },
    @{
        Name = "DirectXLib"
        Path = Join-Path $basePath "client\Designed_Common\Project\Client\DXLib"
        VcprojName = "DirectXLib.vcproj"
    },
    @{
        Name = "FileCheckLib"
        Path = Join-Path $basePath "client\Designed_Common\Project\Client\FileCheckLib"
        VcprojName = "FileCheckLib.vcproj"
    },
    @{
        Name = "Frame Library"
        Path = Join-Path $basePath "client\Designed_Common\Project\Client\FrameLib"
        VcprojName = "Frame Library.vcproj"
    },
    @{
        Name = "MZLib"
        Path = Join-Path $basePath "client\Designed_Common\Project\Client\MZLib"
        VcprojName = "MZLib.vcproj"
    },
    @{
        Name = "MiniLZO"
        Path = Join-Path $basePath "client\Designed_Common\Project\Client\MiniLZO"
        VcprojName = "MiniLZO.vcproj"
    },
    @{
        Name = "OggLib"
        Path = Join-Path $basePath "client\Designed_Common\Project\Client\OggLib"
        VcprojName = "OggLib.vcproj"
    },
    @{
        Name = "RarLib"
        Path = Join-Path $basePath "client\Designed_Common\Project\Client\RarLib"
        VcprojName = "RarLib.vcproj"
    },
    @{
        Name = "SpriteLib"
        Path = Join-Path $basePath "client\Designed_Common\Project\Client\SpriteLib"
        VcprojName = "SpriteLib.vcproj"
    },
    @{
        Name = "VirtualFileSystem"
        Path = Join-Path $basePath "client\Designed_Common\Project\Client\VirtualFileSystem"
        VcprojName = "VirtualFileSystem.vcproj"
    },
    @{
        Name = "VolumeLib"
        Path = Join-Path $basePath "client\Designed_Common\Project\Client\VolumeLib"
        VcprojName = "VolumeLib.vcproj"
    },
    @{
        Name = "lib"
        Path = Join-Path $basePath "client\Designed_Chs\Project\NEW - VS_UI\lib"
        VcprojName = "lib.vcproj"
    }
)

$successCount = 0
$failCount = 0
$failedProjects = @()

Write-Host "`n========================================" -ForegroundColor Cyan
Write-Host "Migração de Projetos para VS2022" -ForegroundColor Cyan
Write-Host "Total de projetos: $($projects.Count)" -ForegroundColor Cyan
Write-Host "========================================`n" -ForegroundColor Cyan

foreach ($project in $projects) {
    $projectPath = $project.Path
    $projectName = $project.Name
    $vcprojPath = Join-Path $projectPath $project.VcprojName
    
    Write-Host "----------------------------------------" -ForegroundColor Yellow
    Write-Host "Processando: $projectName" -ForegroundColor Yellow
    Write-Host "Caminho: $projectPath" -ForegroundColor Gray
    
    # Verificar se o diretório existe
    if (-not (Test-Path $projectPath)) {
        Write-Host "ERRO: Diretório não encontrado: $projectPath" -ForegroundColor Red
        $failCount++
        $failedProjects += $projectName
        continue
    }
    
    # Verificar se o .vcproj existe
    if (-not (Test-Path $vcprojPath)) {
        Write-Host "ERRO: Arquivo .vcproj não encontrado: $vcprojPath" -ForegroundColor Red
        $failCount++
        $failedProjects += $projectName
        continue
    }
    
    try {
        # Passo 1: Converter .vcproj para .vcxproj
        Write-Host "  [1/3] Convertendo .vcproj para .vcxproj..." -ForegroundColor Cyan
        Convert-AllProjects -ProjectRoot $projectPath
        
        # Verificar se o .vcxproj foi criado
        $vcxprojName = $project.VcprojName -replace '\.vcproj$', '.vcxproj'
        $vcxprojPath = Join-Path $projectPath $vcxprojName
        
        if (-not (Test-Path $vcxprojPath)) {
            throw "Arquivo .vcxproj não foi criado: $vcxprojPath"
        }
        
        # Passo 2: Adicionar arquivos fonte
        Write-Host "  [2/3] Adicionando arquivos fonte..." -ForegroundColor Cyan
        Add-SourceFilesToProjects -ProjectRoot $projectPath
        
        # Passo 3: Criar .vcxproj.filters
        Write-Host "  [3/4] Criando .vcxproj.filters..." -ForegroundColor Cyan
        Create-ProjectFilters -ProjectRoot $projectPath
        
        # Verificar se o .filters foi criado
        $filtersPath = Join-Path $projectPath "$vcxprojName.filters"
        if (-not (Test-Path $filtersPath)) {
            Write-Host "  AVISO: Arquivo .filters não foi criado: $filtersPath" -ForegroundColor Yellow
        }
        
        # Passo 4: Corrigir ConfigurationType para projetos de biblioteca
        Write-Host "  [4/4] Verificando ConfigurationType..." -ForegroundColor Cyan
        $fixedCount = Fix-LibraryConfigurationType -ProjectRoot $projectPath
        if ($fixedCount -gt 0) {
            Write-Host "  Corrigido ConfigurationType em $fixedCount configuração(ões)" -ForegroundColor Yellow
        }
        
        Write-Host "  SUCESSO: $projectName migrado com sucesso" -ForegroundColor Green
        $successCount++
        
    } catch {
        Write-Host "  ERRO ao migrar $projectName : $_" -ForegroundColor Red
        $failCount++
        $failedProjects += $projectName
    }
}

Write-Host "`n========================================" -ForegroundColor Cyan
Write-Host "Resumo da Migração" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Sucesso: $successCount" -ForegroundColor Green
Write-Host "Falhas: $failCount" -ForegroundColor $(if ($failCount -gt 0) { "Red" } else { "Green" })

if ($failedProjects.Count -gt 0) {
    Write-Host "`nProjetos com falha:" -ForegroundColor Red
    foreach ($failed in $failedProjects) {
        Write-Host "  - $failed" -ForegroundColor Red
    }
}

Write-Host "`nTodos os arquivos foram salvos em CP949 (sem UTF-8 BOM)" -ForegroundColor Cyan
Write-Host "Migração concluída.`n" -ForegroundColor Cyan
