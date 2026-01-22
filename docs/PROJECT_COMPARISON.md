# Comparação de Projetos: client vs client-project-compiling

## Objetivo

Este documento compara os dois projetos disponíveis para identificar qual é mais consistente, polido e adequado para uso como base.

---

## Projetos Comparados

1. **`client`** (atual) - `c:\darkeden-nostaugia\client\`
2. **`client-project-compiling`** (referência) - `c:\darkeden-nostaugia\client-project-compiling\client-project\`

---

## 1. Encoding dos Arquivos .vcxproj

### **client (atual):**
- `Client.vcxproj`: `encoding="utf-8"` (declarado no XML)
- Arquivo salvo em **UTF-8 sem BOM** ✅
- **Status:** Correto

### **client-project-compiling:**
- `Client.vcxproj`: `encoding="utf-8"` (declarado no XML)
- Arquivo salvo em **UTF-8 sem BOM** ✅
- **Status:** Correto

**Conclusão:** ✅ Ambos estão corretos. Arquivos `.vcxproj` devem estar em UTF-8 (sem BOM), independente do encoding dos arquivos fonte.

---

## 2. Configurações de Compilação

| Configuração | client (atual) | client-project-compiling | Status |
|-------------|----------------|-------------------------|--------|
| **PlatformToolset** | `v143` (VS2022) | `v143` (VS2022) | ✅ Igual |
| **RuntimeLibrary (Debug)** | `MultiThreadedDebug` | `MultiThreadedDebug` | ✅ Igual |
| **RuntimeLibrary (Release)** | `MultiThreaded` | `MultiThreaded` | ✅ Igual |
| **Optimization (Release)** | `MinSpace` | `MinSpace` | ✅ Igual |
| **Optimization (Debug)** | `Disabled` | `Disabled` | ✅ Igual |
| **DebugInformationFormat (Release)** | `ProgramDatabase` | `ProgramDatabase` | ✅ Igual |

**Conclusão:** ✅ Configurações de compilação idênticas.

---

## 3. Bibliotecas Linkadas (Release)

### **client (atual):**
```xml
<AdditionalDependencies>
  ...Oldnames.lib;
  legacy_stdio_definitions.lib;  ← ✅ PRESENTE
  DSetup.lib;...
</AdditionalDependencies>
```
- ✅ `legacy_stdio_definitions.lib` - **PRESENTE** (resolve `_vsprintf`, `__snprintf`)
- ✅ `OggStream.lib`, `VFS.lib`, `ZLib.lib` - Release (sem `_Debug`)
- ✅ `VS_UI_release.lib` - Release
- ✅ `DX.lib`, `SP.lib`, `FR.lib` - Release (sem `_Debug`)
- ✅ `Libcmt.lib`, `Libcimt.lib`, `Libcpmt.lib` - Runtime estático Release

### **client-project-compiling:**
```xml
<AdditionalDependencies>
  ...Oldnames.lib;
  DSetup.lib;...  ← ❌ FALTA legacy_stdio_definitions.lib
</AdditionalDependencies>
```
- ❌ `legacy_stdio_definitions.lib` - **AUSENTE** (pode causar erros de linker)
- ✅ `OggStream.lib`, `VFS.lib`, `ZLib.lib` - Release (sem `_Debug`)
- ✅ `VS_UI_release.lib` - Release
- ✅ `DX.lib`, `SP.lib`, `FR.lib` - Release (sem `_Debug`)
- ✅ `Libcmt.lib`, `Libcimt.lib`, `Libcpmt.lib` - Runtime estático Release

**⚠️ Diferença Crítica:** O projeto `client-project-compiling` **não tem** `legacy_stdio_definitions.lib`, o que pode causar erros de linker:
```
Error LNK2019: unresolved external symbol _vsprintf
Error LNK2019: unresolved external symbol __snprintf
```

---

## 4. Bibliotecas Linkadas (Debug)

### **client (atual):**
- ✅ `OggStream_Debug.lib`, `VFS_Debug.lib`, `ZLib_Debug.lib` - Debug
- ✅ `VS_UI_Debug.lib` - Debug
- ✅ `DX_Debug.lib`, `SP_Debug.lib`, `FR_Debug.lib` - Debug
- ✅ `WinLib_Debug.lib`, `Volume_Debug.lib`, `DX3D_Debug.lib` - Debug
- ✅ Nomenclatura consistente: `_Debug` (maiúscula)

### **client-project-compiling:**
- ⚠️ `OggStream_Debug.lib`, `VFS_debug.lib`, `ZLib_debug.lib` - **Inconsistência** (`_Debug` vs `_debug`)
- ✅ `VS_UI_Debug.lib` - Debug
- ⚠️ `DX_debug.lib`, `SP_debug.lib`, `FR_debug.lib` - **Inconsistência**
- ✅ `WinLib_Debug.lib`, `Volume_Debug.lib`, `DX3D_Debug.lib` - Debug

**⚠️ Inconsistência:** O projeto `client-project-compiling` usa `_debug` (minúsculo) enquanto o padrão é `_Debug` (maiúscula). Isso pode causar problemas se as bibliotecas forem nomeadas com maiúscula.

---

## 5. Diretórios de Bibliotecas (AdditionalLibraryDirectories)

### **client (atual):**
```xml
<AdditionalLibraryDirectories>
  ..\..\..\Designed_Common\Lib;
  ..\..\..\Designed_Common\Lib\ui;
  ..\..\..\Designed_Common\Project\xerces\lib;
  ..\..\..\common_libs\vs2003lib\Lib;      ← ✅ PRESENTE
  ..\..\..\common_libs\dx90bsdk\Lib;      ← ✅ PRESENTE
</AdditionalLibraryDirectories>
```
- ✅ `common_libs\vs2003lib\Lib` - **PRESENTE** (importante para `dxguid.lib` correto)
- ✅ `common_libs\dx90bsdk\Lib` - **PRESENTE**
- ✅ Ordem: `vs2003lib` antes de `dx90bsdk` (correto para resolver símbolos DirectMusic)

### **client-project-compiling:**
```xml
<AdditionalLibraryDirectories>
  ..\..\..\Designed_Common\Lib;
  ..\..\..\Designed_Common\Lib\ui;
  ..\..\..\Designed_Common\Project\xerces\lib;
  ..\..\..\vs2003lib\Lib;                 ← ⚠️ Caminho diferente
</AdditionalLibraryDirectories>
```
- ⚠️ `vs2003lib\Lib` - **Caminho diferente** (sem `common_libs\`)
- ❌ `common_libs\dx90bsdk\Lib` - **AUSENTE**
- ⚠️ Pode não encontrar o `dxguid.lib` correto com símbolos DirectMusic

**⚠️ Problema:** Caminhos diferentes podem causar problemas se a estrutura de diretórios não corresponder.

---

## 6. Arquivos Específicos da Variante

### **client (atual):**
- ✅ `src\a_ida_BasicException.cpp` - **PRESENTE** (resolve `_set_new_handler`)

### **client-project-compiling:**
- ✅ `src\a_ida_BasicException.cpp` - **PRESENTE**
- ✅ `src\a_ida_BasicData.cpp` - **PRESENTE** (extra)
- ✅ `src\MyClient.cpp` - **PRESENTE** (customizações CHS)

**Nota:** O projeto `client-project-compiling` tem arquivos extras que podem ser úteis.

---

## 7. Tamanho e Organização

### **client (atual):**
- `Client.vcxproj`: **~2,321 linhas**
- Organização mais compacta
- Configurações bem definidas
- Estrutura limpa

### **client-project-compiling:**
- `Client.vcxproj`: **~11,447 linhas**
- Organização mais verbosa
- Pode ter configurações duplicadas ou desnecessárias
- Estrutura mais complexa

**Análise:** O projeto atual é mais compacto e fácil de manter.

---

## 8. Correções Aplicadas

### **client (atual):**
- ✅ `legacy_stdio_definitions.lib` adicionado (resolve `_vsprintf`, `__snprintf`)
- ✅ `a_ida_BasicException.cpp` adicionado (resolve `_set_new_handler`)
- ✅ Caminhos de bibliotecas corretos (`common_libs\vs2003lib\Lib`)
- ✅ Ordem correta de diretórios (vs2003lib antes de dx90bsdk)

### **client-project-compiling:**
- ❌ `legacy_stdio_definitions.lib` **NÃO está presente**
- ✅ `a_ida_BasicException.cpp` presente
- ⚠️ Caminhos de bibliotecas diferentes
- ⚠️ Pode ter problemas de linker

---

## Conclusão da Comparação

### **Projeto Mais Consistente e Polido: `client` (atual)** ✅

#### **Vantagens do projeto atual:**

1. ✅ **`legacy_stdio_definitions.lib` presente**
   - Resolve erros de linker com `NPGAMELIB.LIB`
   - Evita `LNK2019: unresolved external symbol _vsprintf`

2. ✅ **Caminhos de bibliotecas corretos**
   - `common_libs\vs2003lib\Lib` presente
   - `common_libs\dx90bsdk\Lib` presente
   - Estrutura de diretórios consistente

3. ✅ **Nomenclatura consistente**
   - `_Debug` com maiúscula (padrão)
   - Evita problemas de case-sensitivity

4. ✅ **Ordem correta de diretórios**
   - `vs2003lib` antes de `dx90bsdk`
   - Garante que `dxguid.lib` correto seja encontrado primeiro

5. ✅ **Projeto mais compacto**
   - ~2,321 linhas vs ~11,447 linhas
   - Mais fácil de manter e entender

#### **Problemas do `client-project-compiling`:**

1. ❌ **Falta `legacy_stdio_definitions.lib`**
   - Pode causar erros de linker com `NPGAMELIB.LIB`
   - Precisa ser adicionado manualmente

2. ⚠️ **Caminhos de bibliotecas diferentes/incompletos**
   - `vs2003lib\Lib` sem `common_libs\`
   - Falta `common_libs\dx90bsdk\Lib`
   - Pode não funcionar se estrutura for diferente

3. ⚠️ **Inconsistência de nomenclatura**
   - `_debug` (minúsculo) vs `_Debug` (maiúscula)
   - Pode causar problemas de case-sensitivity

4. ⚠️ **Projeto muito grande**
   - ~11,447 linhas pode ter redundâncias
   - Mais difícil de manter

---

## Encoding dos Arquivos Fonte

### Regra de Encoding

- **Arquivos `.vcxproj`**: UTF-8 sem BOM (sempre) ✅
- **Arquivos fonte (`.cpp`, `.h`)**: CP949/EUC-KR (preservar encoding original)
- **Arquivos novos criados**: UTF-8 sem BOM (se apenas ASCII/inglês)

### Verificação do `client-project-compiling`

**Arquivos `.vcxproj`:**
- ✅ Estão corretos (UTF-8 sem BOM)

**Arquivos fonte:**
- ⚠️ Para verificar encoding dos arquivos fonte, seria necessário inspecionar arquivos específicos que contenham caracteres coreanos/chineses
- ⚠️ Arquivos como `MyClient.cpp` podem ter encoding diferente se contiverem caracteres especiais

**Recomendação:**
- ✅ Verificar encoding de arquivos específicos se necessário
- ✅ Usar ferramenta de validação de encoding após modificações

---

## Recomendações

### ✅ **Usar `client` (atual) como base:**

1. **Mais completo:** Tem todas as correções necessárias
2. **Mais consistente:** Nomenclatura e caminhos corretos
3. **Mais polido:** Estrutura limpa e organizada
4. **Pronto para compilar:** Não precisa de correções adicionais

### ⚠️ **Aplicar do `client-project-compiling` apenas se necessário:**

1. **Arquivos extras:**
   - `src\a_ida_BasicData.cpp` - Se necessário
   - `src\MyClient.cpp` - Se necessário para customizações CHS

2. **Verificar encoding:**
   - Se arquivos fonte tiverem encoding incorreto, corrigir

3. **Não copiar:**
   - ❌ Não copiar `.vcxproj` (tem problemas)
   - ❌ Não copiar configurações (menos polidas)

---

## Referências

- `ARCHITECTURE.md` - Estrutura de projetos Designed_Chs vs Designed_Common
- `MIGRATION_TO_VS2022.md` - Detalhes sobre migração e correções aplicadas
- `README.md` - Índice de toda a documentação
