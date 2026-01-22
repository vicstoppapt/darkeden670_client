# Script para configurar Precompiled Header no Client.vcxproj
# Arquivo salvo em CP949 (sem UTF-8 BOM)

$ErrorActionPreference = "Stop"

$basePath = Split-Path -Parent $PSScriptRoot
$vcxprojPath = Join-Path $basePath "client\Designed_Chs\Project\Client\Client.vcxproj"

Write-Host "Configurando Precompiled Header..." -ForegroundColor Cyan
Write-Host "Arquivo: $vcxprojPath" -ForegroundColor Gray

if (-not (Test-Path $vcxprojPath)) {
    Write-Host "ERRO: Arquivo não encontrado: $vcxprojPath" -ForegroundColor Red
    exit 1
}

# Ler arquivo em CP949
$cp949 = [System.Text.Encoding]::GetEncoding(949)
$bytes = [System.IO.File]::ReadAllBytes($vcxprojPath)
$content = $cp949.GetString($bytes)

# Verificar se já está configurado
if ($content -match 'PrecompiledHeader="Use"') {
    Write-Host "Precompiled Header já está configurado." -ForegroundColor Yellow
    exit 0
}

# 1. Adicionar PrecompiledHeader="Use" nas seções ClCompile globais (Debug, Release, ReleaseLog)
# Usar quebras de linha reais, não literais
$newline = [Environment]::NewLine
$content = $content -replace '(<ClCompile>\s*<AdditionalIncludeDirectories>)', "<ClCompile>$newline      <PrecompiledHeader>Use</PrecompiledHeader>$newline      <PrecompiledHeaderFile>Client_PCH.h</PrecompiledHeaderFile>$newline      <AdditionalIncludeDirectories>"

# 2. Adicionar ItemDefinitionGroup específico para Client_PCH.cpp (Create)
$itemGroupEnd = '</ItemGroup>'
$pchConfigSection = @"

  <ItemDefinitionGroup Condition="'`$(Configuration)|`$(Platform)'=='Debug|Win32'">
    <ClCompile>
      <PrecompiledHeader>Create</PrecompiledHeader>
      <PrecompiledHeaderFile>Client_PCH.h</PrecompiledHeaderFile>
    </ClCompile>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'`$(Configuration)|`$(Platform)'=='Release|Win32'">
    <ClCompile>
      <PrecompiledHeader>Create</PrecompiledHeader>
      <PrecompiledHeaderFile>Client_PCH.h</PrecompiledHeaderFile>
    </ClCompile>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'`$(Configuration)|`$(Platform)'=='ReleaseLog|Win32'">
    <ClCompile>
      <PrecompiledHeader>Create</PrecompiledHeader>
      <PrecompiledHeaderFile>Client_PCH.h</PrecompiledHeaderFile>
    </ClCompile>
  </ItemDefinitionGroup>
  <ItemGroup>
    <ClCompile Condition="'`$(Configuration)|`$(Platform)'=='Debug|Win32'" Include="..\..\..\Designed_Common\Project\Client\Client_PCH.cpp">
      <PrecompiledHeader Condition="'`$(Configuration)|`$(Platform)'=='Debug|Win32'">Create</PrecompiledHeader>
    </ClCompile>
    <ClCompile Condition="'`$(Configuration)|`$(Platform)'=='Release|Win32'" Include="..\..\..\Designed_Common\Project\Client\Client_PCH.cpp">
      <PrecompiledHeader Condition="'`$(Configuration)|`$(Platform)'=='Release|Win32'">Create</PrecompiledHeader>
    </ClCompile>
    <ClCompile Condition="'`$(Configuration)|`$(Platform)'=='ReleaseLog|Win32'" Include="..\..\..\Designed_Common\Project\Client\Client_PCH.cpp">
      <PrecompiledHeader Condition="'`$(Configuration)|`$(Platform)'=='ReleaseLog|Win32'">Create</PrecompiledHeader>
    </ClCompile>
  </ItemGroup>
$itemGroupEnd
"@

# Encontrar a última tag </ItemGroup> antes de <Import Project="$(VCTargetsPath)\Microsoft.Cpp.targets" />
$importPattern = '<Import Project="`$\(VCTargetsPath\)\\Microsoft\.Cpp\.targets" />'
if ($content -match $importPattern) {
    # Inserir configuração específica para Client_PCH.cpp antes do ItemGroup que contém o Import
    # Na verdade, melhor adicionar ItemMetadata diretamente no ClCompile do Client_PCH.cpp
    # Usar uma abordagem diferente - modificar a linha ClCompile do Client_PCH.cpp para incluir PrecompiledHeader
}

# Abordagem mais simples: modificar a linha Client_PCH.cpp diretamente
$clientPchLine = '    <ClCompile Include="..\..\..\Designed_Common\Project\Client\Client_PCH.cpp" />'
$clientPchWithPch = @"
    <ClCompile Include="..\..\..\Designed_Common\Project\Client\Client_PCH.cpp">
      <PrecompiledHeader Condition="'`$(Configuration)|`$(Platform)'=='Debug|Win32'">Create</PrecompiledHeader>
      <PrecompiledHeader Condition="'`$(Configuration)|`$(Platform)'=='Release|Win32'">Create</PrecompiledHeader>
      <PrecompiledHeader Condition="'`$(Configuration)|`$(Platform)'=='ReleaseLog|Win32'">Create</PrecompiledHeader>
      <PrecompiledHeaderFile Condition="'`$(Configuration)|`$(Platform)'=='Debug|Win32'">Client_PCH.h</PrecompiledHeaderFile>
      <PrecompiledHeaderFile Condition="'`$(Configuration)|`$(Platform)'=='Release|Win32'">Client_PCH.h</PrecompiledHeaderFile>
      <PrecompiledHeaderFile Condition="'`$(Configuration)|`$(Platform)'=='ReleaseLog|Win32'">Client_PCH.h</PrecompiledHeaderFile>
    </ClCompile>
"@

$content = $content -replace [regex]::Escape($clientPchLine), $clientPchWithPch

# Salvar em CP949
$newBytes = $cp949.GetBytes($content)
[System.IO.File]::WriteAllBytes($vcxprojPath, $newBytes)

Write-Host "`nPrecompiled Header configurado com sucesso!" -ForegroundColor Green
Write-Host "  - ClCompile global: PrecompiledHeader=Use para todos os arquivos" -ForegroundColor Cyan
Write-Host "  - Client_PCH.cpp: PrecompiledHeader=Create para gerar o .pch" -ForegroundColor Cyan
Write-Host "Arquivo salvo em CP949 (sem UTF-8 BOM)" -ForegroundColor Cyan
