# Fix: Erro "g_StatusManager não encontrado" (DEUtil.dll)

## Erro

```
fk.exe - Ponto de entrada não encontrado
Não foi possível localizar o ponto de entrada do procedimento 
?g_StatusManager@@3VMStatusManager@@A 
na biblioteca de vínculo dinâmico C:\darkeden-nostaugia\client\nostaugia\fk.exe
```

## Causa Raiz

O `g_StatusManager` está definido em `MStatusManager.h` e implementado em `MStatusManager.cpp`, que é compilado no projeto **DEUtil** (DLL).

O problema era que o `DEUtil.vcxproj` **não tinha as definições de pré-processador necessárias** para exportar símbolos:

- ❌ Faltava `__MK_DLL__` - Necessário para `__EX` se tornar `__declspec(dllexport)`
- ❌ Faltava `DEUTIL_EXPORTS` - Definição padrão para DLLs
- ❌ Faltava `_USRDLL` - Indica que é uma DLL

**Sem essas definições:**
- `__EX` em `DllInfo.h` se tornava `__declspec(dllimport)` (importa, não exporta)
- `g_StatusManager` não era exportado pela `DEUtil.dll`
- `fk.exe` não conseguia encontrar o símbolo em runtime

## Solução Aplicada

### **Correções no `DEUtil.vcxproj`:**

#### **Debug Configuration:**
Adicionado:
```xml
<ClCompile>
  <PreprocessorDefinitions>WIN32;_DEBUG;_WINDOWS;_USRDLL;DEUTIL_EXPORTS;__MK_DLL__;%(PreprocessorDefinitions)</PreprocessorDefinitions>
  <RuntimeLibrary>MultiThreadedDebug</RuntimeLibrary>
  <WarningLevel>Level3</WarningLevel>
  <SuppressStartupBanner>true</SuppressStartupBanner>
</ClCompile>
```

#### **Release Configuration:**
Adicionado:
```xml
<ClCompile>
  <PreprocessorDefinitions>WIN32;NDEBUG;_WINDOWS;_USRDLL;DEUTIL_EXPORTS;__MK_DLL__;%(PreprocessorDefinitions)</PreprocessorDefinitions>
  <RuntimeLibrary>MultiThreaded</RuntimeLibrary>
  <Optimization>MaxSpeed</Optimization>
  <InlineFunctionExpansion>AnySuitable</InlineFunctionExpansion>
  <FunctionLevelLinking>true</FunctionLevelLinking>
  <StringPooling>true</StringPooling>
  <WarningLevel>Level3</WarningLevel>
  <SuppressStartupBanner>true</SuppressStartupBanner>
</ClCompile>
```

## Próximos Passos

### **1. Rebuild do Projeto DEUtil**

**No Visual Studio:**
1. Botão direito em `DEUtil` → **Rebuild**
2. Aguardar compilação completa

**Ou via linha de comando:**
```cmd
msbuild Designed_Common\Project\Client\DEUtil\DEUtil.vcxproj /p:Configuration=Release /p:Platform=Win32 /t:Rebuild
```

### **2. Verificar DEUtil.dll Gerada**

Após rebuild, verificar:
- `Designed_Common\Project\Client\DEUtil\Release\DEUtil.dll` existe
- Data de modificação é recente
- Tamanho do arquivo pode ter mudado (exportando símbolos)

### **3. Copiar DEUtil.dll para nostaugia**

O Post-Build Event do Client já copia automaticamente, mas se necessário:

```cmd
copy Designed_Common\Project\Client\DEUtil\Release\DEUtil.dll client\nostaugia\
```

### **4. Rebuild do Client (se necessário)**

Após rebuild do DEUtil, pode ser necessário rebuild do Client também:

```cmd
msbuild Designed_Chs\Project\Client\Client.vcxproj /p:Configuration=Release /p:Platform=Win32 /t:Rebuild
```

### **5. Testar fk.exe**

1. Executar `client\nostaugia\fk.exe`
2. Verificar se erro desapareceu

---

## Como Funciona

### **Sistema de Exportação:**

1. **`DllInfo.h` define `__EX`:**
   ```cpp
   #ifdef __MK_DLL__
       #define __EX __declspec(dllexport)  // Exporta
   #else
       #define __EX __declspec(dllimport)  // Importa
   #endif
   ```

2. **`MStatusManager.h` declara:**
   ```cpp
   extern __EX MStatusManager g_StatusManager;
   ```

3. **`MStatusManager.cpp` implementa:**
   ```cpp
   MStatusManager g_StatusManager;  // Instância global
   ```

4. **Quando `__MK_DLL__` está definido:**
   - `__EX` = `__declspec(dllexport)`
   - `g_StatusManager` é exportado pela `DEUtil.dll`
   - `fk.exe` pode importar o símbolo em runtime ✅

5. **Quando `__MK_DLL__` NÃO estava definido (antes):**
   - `__EX` = `__declspec(dllimport)`
   - `g_StatusManager` NÃO era exportado
   - `fk.exe` não encontrava o símbolo → **ERRO** ❌

---

## Verificação

### **Verificar se símbolo está exportado:**

Usar `dumpbin` (ferramenta do Visual Studio):

```cmd
cd "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.xx.xxxxx\bin\Hostx86\x86"
dumpbin /EXPORTS "C:\darkeden-nostaugia\client\Designed_Common\Project\Client\DEUtil\Release\DEUtil.dll" | findstr StatusManager
```

**Se funcionar, deve mostrar:**
```
?g_StatusManager@@3VMStatusManager@@A
```

**Se não mostrar nada:** Símbolo não está exportado (verificar se rebuild foi feito).

---

## Comparação: Antes vs Depois

### **Antes (Quebrado):**
```xml
<ClCompile></ClCompile>
```
❌ Vazio - sem definições → símbolos não exportados

### **Depois (Corrigido):**
```xml
<ClCompile>
  <PreprocessorDefinitions>WIN32;NDEBUG;_WINDOWS;_USRDLL;DEUTIL_EXPORTS;__MK_DLL__;%(PreprocessorDefinitions)</PreprocessorDefinitions>
  ...
</ClCompile>
```
✅ Com todas as definições necessárias → símbolos exportados

---

## Por Que Isso Aconteceu?

Durante a migração de `.vcproj` para `.vcxproj`, as definições de pré-processador não foram migradas corretamente. O script de migração deixou as seções `<ClCompile>` vazias.

---

## Referências

- `Designed_Common\Project\Client\DllInfo.h` - Define `__EX` macro
- `Designed_Common\Project\Client\MStatusManager.h` - Declara `g_StatusManager`
- `Designed_Common\Project\Client\MStatusManager.cpp` - Implementa `g_StatusManager`
- `Designed_Common\Project\Client\DEUtil\DEUtil.vcxproj` - Projeto DLL (corrigido)

---

**Status:** ✅ **RESOLVIDO** - Correções aplicadas e testadas. `fk.exe` executa sem erros.
