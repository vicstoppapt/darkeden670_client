# Base de Conhecimento Técnico - Dark Eden Client VS2022

**Última Atualização:** Janeiro 2025  
**Status do Projeto:** ✅ Migração completa, compilando e executando

---

## 📋 Índice

1. [Visão Geral do Projeto](#visão-geral-do-projeto)
2. [Estrutura de Diretórios](#estrutura-de-diretórios)
3. [Encoding e Codificação](#encoding-e-codificação)
4. [Configurações de Projeto](#configurações-de-projeto)
5. [Problemas Resolvidos](#problemas-resolvidos)
6. [Dependências e Bibliotecas](#dependências-e-bibliotecas)
7. [Processo de Compilação](#processo-de-compilação)
8. [Runtime e Distribuição](#runtime-e-distribuição)
9. [Troubleshooting](#troubleshooting)
10. [Referências Rápidas](#referências-rápidas)

---

## Visão Geral do Projeto

### O Que É

Migração de 15 projetos C++ de Visual Studio 2003/2005 (`.vcproj`) para Visual Studio 2022 (`.vcxproj`), preservando encoding CP949/EUC-KR dos arquivos fonte.

### Status Atual

- ✅ **15 projetos migrados** com sucesso
- ✅ **Compilação funcionando** (Release, Debug, ReleaseLog)
- ✅ **Runtime funcionando** (`fk.exe` executa sem erros)
- ✅ **Todas as correções aplicadas** e documentadas
- ✅ **Post-Build Event** configurado (cópia automática de DLLs)
- ✅ **Documentação completa** em `client\docs\`

### Projetos Migrados

1. **Client** - `Designed_Chs\Project\Client\` (executável principal)
2. **CWinMain Library** - `Designed_Common\Project\Client\CWinMain Library\`
3. **D3DLib** - `Designed_Common\Project\Client\D3DLib\`
4. **DEUtil** - `Designed_Common\Project\Client\DEUtil\` (DLL)
5. **DirectXLib** - `Designed_Common\Project\Client\DXLib\`
6. **FileCheckLib** - `Designed_Common\Project\Client\FileCheckLib\`
7. **Frame Library** - `Designed_Common\Project\Client\FrameLib\`
8. **MZLib** - `Designed_Common\Project\Client\MZLib\`
9. **MiniLZO** - `Designed_Common\Project\Client\MiniLZO\`
10. **OggLib** - `Designed_Common\Project\Client\OggLib\`
11. **RarLib** - `Designed_Common\Project\Client\RarLib\`
12. **SpriteLib** - `Designed_Common\Project\Client\SpriteLib\`
13. **VirtualFileSystem** - `Designed_Common\Project\Client\VirtualFileSystem\`
14. **VolumeLib** - `Designed_Common\Project\Client\VolumeLib\`
15. **lib** - `Designed_Chs\Project\NEW - VS_UI\lib\`

---

## Estrutura de Diretórios

### Estrutura Principal

```
c:\darkeden-nostaugia\
└── client/
    ├── docs/                          # ✅ Toda documentação
    │   ├── README.md                  # Índice principal
    │   ├── TECHNICAL_KNOWLEDGE_BASE.md  # Este arquivo
    │   ├── MIGRATION_TO_VS2022.md     # Documento principal de migração
    │   ├── COMPLETE_FIXES_SUMMARY.md  # Resumo de correções
    │   ├── ARCHITECTURE.md           # Arquitetura do projeto
    │   ├── FIX_DEUTIL_EXPORT_ERROR.md # Fix: g_StatusManager
    │   └── ... (outros documentos)
    │
    ├── scripts/                       # ✅ Scripts utilitários
    │   ├── README.md                  # Documentação dos scripts
    │   ├── migrate_all_projects_to_vs2022.ps1
    │   ├── run_full_migration.ps1
    │   ├── add_common_sdk.ps1
    │   ├── configure_precompiled_header.ps1
    │   ├── organize_for_distribution.bat
    │   ├── prepare_setup.bat
    │   └── setup_template.iss
    │
    ├── Designed_Chs/                  # Variante CHS (China)
    │   └── Project\Client\
    │       ├── Client.vcxproj         # ⭐ COMPILE AQUI
    │       ├── Client.vcxproj.filters
    │       ├── src\
    │       │   └── a_ida_BasicException.cpp  # Stub _set_new_handler
    │       └── Release\               # Output: fk.exe
    │
    ├── Designed_Common/               # Código compartilhado
    │   ├── Project\Client\
    │   │   ├── DEUtil\               # DLL (exporta g_StatusManager)
    │   │   │   └── DEUtil.vcxproj
    │   │   ├── D3DLib\
    │   │   ├── DirectXLib\
    │   │   └── ... (outros projetos)
    │   └── Lib\                      # Bibliotecas pré-compiladas
    │       ├── BasicS.lib            # ⚠️ Pré-compilado VS6/2003
    │       ├── NPGAMELIB.LIB         # ⚠️ Pré-compilado
    │       └── *.dll                 # DLLs externas
    │
    ├── common_libs\                   # SDK comum
    │   └── vs2003lib\                # DirectX SDK antigo
    │
    ├── nostaugia\                     # Pasta de execução do jogo
    │   ├── fk.exe                    # Executável principal
    │   ├── *.dll                     # DLLs necessárias
    │   └── data\                     # Dados do jogo
    │
    └── dist\                          # Distribuição (criado por scripts)
        ├── bin\                      # Executáveis e DLLs
        └── data\                     # Dados do jogo
```

### Arquitetura: Designed_Chs vs Designed_Common

**Designed_Common:**
- Código compartilhado entre variantes
- Bibliotecas estáticas (.lib)
- DLLs utilitárias (DEUtil.dll)
- Headers comuns

**Designed_Chs:**
- Variante específica (China)
- Projeto executável principal
- Código específico da variante
- **COMPILE AQUI:** `Designed_Chs\Project\Client\Client.vcxproj`

**Por que compilar em Designed_Chs?**
- Contém o executável principal (`fk.exe`)
- Variante ativa do projeto
- Post-Build Event configurado aqui

---

## Encoding e Codificação

### ⚠️ REGRA CRÍTICA: Encoding

**Arquivos Fonte (.cpp, .h, .c, .hpp):**
- **MUST:** CP949/EUC-KR (sem BOM)
- **FORBIDDEN:** UTF-8 BOM
- **Razão:** Contém caracteres coreanos, encoding original do projeto

**Arquivos de Projeto (.vcxproj, .vcxproj.filters):**
- **MUST:** UTF-8 (sem BOM)
- **Razão:** Visual Studio 2022 requer UTF-8 para arquivos XML

**Arquivos de Solução (.sln):**
- **MUST:** UTF-8 com BOM
- **Razão:** Padrão Visual Studio

**Scripts (.ps1, .bat):**
- **MUST:** Compatível com Windows (ANSI/CP1252 para .bat)
- **Razão:** Execução no Windows

### Validação de Encoding

**Script de Validação:**
```powershell
# Executar após qualquer modificação
.\validate_encoding_integrity.ps1
```

**Regra de Ouro:**
- **NUNCA** converter arquivos fonte para UTF-8
- **SEMPRE** preservar CP949 em arquivos fonte
- **SEMPRE** usar UTF-8 sem BOM em `.vcxproj`

---

## Configurações de Projeto

### Client.vcxproj (Projeto Principal)

**Configurações Importantes:**

1. **PlatformToolset:** `v143` (VS2022)
2. **RuntimeLibrary:**
   - Debug: `MultiThreadedDebug`
   - Release: `MultiThreaded`
3. **CharacterSet:** `MultiByte`
4. **PrecompiledHeader:** `Use` (`Client_PCH.h`)

**Dependências de Linker (Release):**
```
legacy_stdio_definitions.lib  # ⚠️ CRÍTICO: Funções C runtime antigas
BasicS.lib                    # ⚠️ Pré-compilado VS6/2003
NPGAMELIB.LIB                 # ⚠️ Pré-compilado
... (outras bibliotecas)
```

**Post-Build Event:**
- Copia DLLs de `Designed_Common\Lib\` para `$(OutDir)`
- Copia DLLs geradas (DEUtil.dll) para `$(OutDir)`
- Copia tudo para `client\nostaugia\`

**Arquivo Crítico:**
- `src\a_ida_BasicException.cpp` - Stub para `g_SetNewHandler()`

### DEUtil.vcxproj (DLL)

**Configurações Críticas:**

**PreprocessorDefinitions (Debug):**
```
WIN32;_DEBUG;_WINDOWS;_USRDLL;DEUTIL_EXPORTS;__MK_DLL__
```

**PreprocessorDefinitions (Release):**
```
WIN32;NDEBUG;_WINDOWS;_USRDLL;DEUTIL_EXPORTS;__MK_DLL__
```

**⚠️ CRÍTICO:** `__MK_DLL__` deve estar definido para exportar símbolos!

**Sistema de Exportação:**
- `DllInfo.h` define `__EX` macro
- Se `__MK_DLL__` definido: `__EX` = `__declspec(dllexport)`
- Se não definido: `__EX` = `__declspec(dllimport)`
- `g_StatusManager` precisa ser exportado pela DLL

---

## Problemas Resolvidos

### 1. ✅ `_set_new_handler` - Conflito de Assinatura

**Erro:**
```
LNK2019: unresolved external symbol "int (__cdecl*__cdecl _set_new_handler(int (__cdecl*)(unsigned int)))(unsigned int)"
from BasicS.lib(BasicException.obj)
```

**Causa:**
- `BasicS.lib` pré-compilado com VS6/2003
- Assinatura de `_set_new_handler()` mudou no VS2022
- Incompatibilidade de assinatura

**Solução:**
Arquivo `a_ida_BasicException.cpp` com stub:
```cpp
void __cdecl g_SetNewHandler(void)
{
    // Stub - não chama _set_new_handler()
}
```

**Localização:** `Designed_Chs\Project\Client\src\a_ida_BasicException.cpp`

---

### 2. ✅ `_vsprintf` e `__snprintf` - Funções C Runtime Antigas

**Erro:**
```
LNK2019: unresolved external symbol _vsprintf referenced in NPGAMELIB.LIB(NPGameLib.obj)
LNK2019: unresolved external symbol __snprintf referenced in NPGAMELIB.LIB(NPGameLib.obj)
```

**Causa:**
- `NPGAMELIB.LIB` usa nomes antigos de funções C runtime
- VS2022 não expõe essas funções diretamente

**Solução:**
Adicionado `legacy_stdio_definitions.lib` em `Client.vcxproj`:
```xml
<AdditionalDependencies>
  ...
  legacy_stdio_definitions.lib
  ...
</AdditionalDependencies>
```

**Configurações:** Release, ReleaseLog

---

### 3. ✅ `g_StatusManager` - Exportação DLL

**Erro Runtime:**
```
fk.exe - Ponto de entrada não encontrado
Não foi possível localizar o ponto de entrada do procedimento 
?g_StatusManager@@3VMStatusManager@@A
```

**Causa:**
- `DEUtil.vcxproj` não tinha `__MK_DLL__` definido
- `g_StatusManager` não era exportado pela DLL
- `fk.exe` não encontrava o símbolo em runtime

**Solução:**
Adicionadas definições em `DEUtil.vcxproj`:
- `__MK_DLL__` - Ativa exportação
- `DEUTIL_EXPORTS` - Definição padrão DLL
- `_USRDLL` - Indica DLL

**Arquivo:** `Designed_Common\Project\Client\DEUtil\DEUtil.vcxproj`

**Documentação Completa:** `docs\FIX_DEUTIL_EXPORT_ERROR.md`

---

## Dependências e Bibliotecas

### Bibliotecas Pré-Compiladas (⚠️ Não Recompiláveis)

**Localização:** `Designed_Common\Lib\`

1. **BasicS.lib**
   - Compilado com VS6/2003
   - Tratamento de exceções, memória, estruturas básicas
   - **Problema:** Conflito `_set_new_handler` → Resolvido com stub

2. **NPGAMELIB.LIB**
   - Compilado com VS antigo
   - Funções de jogo (GameGuard, logging)
   - **Problema:** Funções C runtime antigas → Resolvido com `legacy_stdio_definitions.lib`

### DLLs Externas

**Localização:** `Designed_Common\Lib\` e `nostaugia\`

**DLLs Necessárias:**
- `IFC22.dll` / `ifc22.dll` - Interface
- `GL.dll` / `gl.dll` - OpenGL
- `Timer.dll` / `timer.dll` - Timer
- `BasicS.dll` / `basics.dll` - Biblioteca básica
- `vorbisfile.dll`, `vorbis.dll`, `vorbisenc.dll`, `ogg.dll` - Audio
- `DEUtil.dll` - Utilitários (gerada pelo projeto)
- `gmp.dll`, `pcre.dll` - Bibliotecas auxiliares
- `msvcrt.dll`, `msvcr71.dll`, `msvcirt.dll` - Runtime C

**⚠️ IMPORTANTE:** Post-Build Event copia automaticamente para `nostaugia\`

### Diretórios de Include

**SDK Comum:** `common_libs\vs2003lib\Include\`

**Diretórios Adicionados Automaticamente:**
- `Designed_Common\Project\Client\...` (vários projetos)
- `Designed_Chs\Project\NEW - VS_UI\src\header\`
- `common_libs\vs2003lib\Include\` (DirectX SDK)

**Script:** `scripts\add_common_sdk.ps1` adiciona automaticamente

---

## Processo de Compilação

### Compilação Normal

**No Visual Studio:**
1. Abrir `Client.sln`
2. Selecionar configuração: **Release** (ou Debug)
3. Build → Build Solution (ou F7)

**Via Linha de Comando:**
```cmd
cd c:\darkeden-nostaugia\client
msbuild Designed_Chs\Project\Client\Client.sln /p:Configuration=Release /p:Platform=Win32
```

### Ordem de Compilação

1. **Bibliotecas estáticas** (D3DLib, DirectXLib, etc.)
2. **DEUtil.dll** (deve compilar antes do Client)
3. **Client.exe** (fk.exe)

**Dependências:**
- Client depende de todas as bibliotecas
- Client depende de DEUtil.dll

### Output

**Executável:**
- `Designed_Chs\Project\Client\Release\fk.exe`

**DLLs:**
- `Designed_Common\Project\Client\DEUtil\Release\DEUtil.dll`
- Outras DLLs de projetos (se houver)

**Post-Build Event:**
- Copia tudo para `client\nostaugia\` automaticamente

### Clean Build

**Quando fazer Clean + Build:**
- Mudanças em `.vcxproj` (configurações)
- Mudanças em headers de pré-compilação (PCH)
- Mudanças em headers globais
- Erros estranhos de linker

**Como fazer:**
- Build → Clean Solution
- Build → Rebuild Solution

---

## Runtime e Distribuição

### Execução

**Executável:** `client\nostaugia\fk.exe`

**Requisitos:**
- Todas as DLLs em `nostaugia\` (copiadas pelo Post-Build Event)
- Dados do jogo em `nostaugia\data\`
- Arquivos de configuração em `nostaugia\`

### Distribuição

**Scripts Disponíveis:**

1. **`scripts\organize_for_distribution.bat`**
   - Organiza binários em `dist\bin\`

2. **`scripts\prepare_setup.bat`**
   - Prepara estrutura completa em `dist\`
   - Binários → `dist\bin\`
   - Dados → `dist\data\`
   - Config → `dist\` (raiz)

3. **`scripts\setup_template.iss`**
   - Template Inno Setup para criar instalador

**Documentação:** `docs\SETUP_AND_DISTRIBUTION.md`

---

## Troubleshooting

### Erro: "Cannot open include file"

**Causa:** Diretórios de include faltando

**Solução:**
```powershell
.\scripts\add_common_sdk.ps1 -ProjectPath "Designed_Chs\Project\Client\Client.vcxproj"
```

### Erro: "Unresolved external symbol"

**Causas Comuns:**
1. Biblioteca não linkada → Verificar `AdditionalDependencies`
2. Biblioteca pré-compilada incompatível → Verificar se precisa de stub/compatibilidade
3. Símbolo não exportado (DLL) → Verificar `__MK_DLL__` e `__EX`

**Soluções:**
- Adicionar biblioteca em `AdditionalDependencies`
- Adicionar `legacy_stdio_definitions.lib` (funções C antigas)
- Verificar exportação DLL (dumpbin /EXPORTS)

### Erro: "g_StatusManager não encontrado"

**Causa:** `DEUtil.dll` não exporta o símbolo

**Solução:**
1. Verificar `DEUtil.vcxproj` tem `__MK_DLL__` definido
2. Rebuild do projeto DEUtil
3. Verificar com `dumpbin /EXPORTS DEUtil.dll | findstr StatusManager`

**Documentação:** `docs\FIX_DEUTIL_EXPORT_ERROR.md`

### Erro: Encoding (caracteres coreanos quebrados)

**Causa:** Arquivo fonte convertido para UTF-8

**Solução:**
- **NUNCA** converter arquivos fonte
- Preservar CP949/EUC-KR
- Validar com `validate_encoding_integrity.ps1`

### Erro: DLL não encontrada em runtime

**Causa:** DLL não copiada para `nostaugia\`

**Solução:**
1. Verificar Post-Build Event está configurado
2. Executar build novamente
3. Copiar manualmente se necessário

---

## Referências Rápidas

### Documentação Principal

- **`docs\README.md`** - Índice de toda documentação
- **`docs\MIGRATION_TO_VS2022.md`** - Documento principal (muito completo)
- **`docs\COMPLETE_FIXES_SUMMARY.md`** - Resumo de todas as correções
- **`docs\ARCHITECTURE.md`** - Arquitetura do projeto

### Correções Específicas

- **`docs\FIX_DEUTIL_EXPORT_ERROR.md`** - Erro g_StatusManager
- **`docs\WHY_STUB_SOLUTION_FOUND_FASTER.md`** - Explicação técnica do stub

### Scripts

- **`scripts\README.md`** - Documentação dos scripts
- **`scripts\migrate_all_projects_to_vs2022.ps1`** - Migração de projetos
- **`scripts\run_full_migration.ps1`** - Migração completa

### Distribuição

- **`docs\SETUP_AND_DISTRIBUTION.md`** - Setup e distribuição
- **`docs\NEXT_STEPS_INSTALLER.md`** - Guia de instalador

### Arquivos Críticos

**Código:**
- `Designed_Chs\Project\Client\src\a_ida_BasicException.cpp` - Stub _set_new_handler

**Projetos:**
- `Designed_Chs\Project\Client\Client.vcxproj` - Projeto principal
- `Designed_Common\Project\Client\DEUtil\DEUtil.vcxproj` - DLL crítica

**Headers:**
- `Designed_Common\Project\Client\DllInfo.h` - Define `__EX` macro
- `Designed_Common\Project\Client\MStatusManager.h` - Declara `g_StatusManager`

---

## Comandos Úteis

### Verificar Exportações DLL

```cmd
cd "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.xx.xxxxx\bin\Hostx86\x86"
dumpbin /EXPORTS "C:\darkeden-nostaugia\client\Designed_Common\Project\Client\DEUtil\Release\DEUtil.dll" | findstr StatusManager
```

### Rebuild Completo

```cmd
cd c:\darkeden-nostaugia\client
msbuild Designed_Chs\Project\Client\Client.sln /p:Configuration=Release /p:Platform=Win32 /t:Clean,Build
```

### Organizar Distribuição

```cmd
cd c:\darkeden-nostaugia\client
scripts\prepare_setup.bat
```

---

## Notas Importantes para Próxima IA

### ⚠️ REGRAS CRÍTICAS

1. **Encoding:**
   - **NUNCA** converter arquivos fonte para UTF-8
   - **SEMPRE** preservar CP949/EUC-KR em arquivos fonte
   - **SEMPRE** usar UTF-8 sem BOM em `.vcxproj`

2. **Bibliotecas Pré-Compiladas:**
   - `BasicS.lib` e `NPGAMELIB.LIB` são pré-compiladas
   - Não tentar recompilar
   - Usar stubs/compatibilidade quando necessário

3. **Exportação DLL:**
   - Projetos DLL precisam de `__MK_DLL__` definido
   - Verificar `DllInfo.h` para sistema de exportação
   - Usar `dumpbin` para verificar exportações

4. **Post-Build Event:**
   - Já configurado em `Client.vcxproj`
   - Copia DLLs automaticamente para `nostaugia\`
   - Não remover sem substituir

5. **Estrutura:**
   - Documentação em `client\docs\`
   - Scripts em `client\scripts\`
   - Não mover arquivos sem atualizar paths

### ✅ Status Atual

- **Compilação:** ✅ Funcionando
- **Runtime:** ✅ Funcionando
- **Documentação:** ✅ Completa
- **Scripts:** ✅ Organizados
- **Paths:** ✅ Atualizados

### 🎯 Próximos Passos Sugeridos

1. Criar instalador (ver `docs\NEXT_STEPS_INSTALLER.md`)
2. Testar em máquina limpa
3. Validar encoding periodicamente
4. Documentar novos problemas (se houver)

---

**Boa sorte, próxima IA! 🚀**

Este documento contém todo o conhecimento técnico necessário para continuar o trabalho. Consulte os documentos específicos para detalhes.

---

**Última Sessão:** Janeiro 2025  
**Status:** ✅ Projeto funcional e documentado  
**Próxima IA:** Você tem tudo que precisa! 💪
