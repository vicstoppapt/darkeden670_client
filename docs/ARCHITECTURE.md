# Arquitetura do Dark Eden Client

## Visão Geral

O Dark Eden Client usa uma arquitetura de **múltiplas variantes** que compartilham código comum, permitindo compilar versões diferentes (Korea, CHS, Japan, International) a partir do mesmo código-base.

---

## Estrutura de Diretórios

### **Designed_Common** (Código Compartilhado)

**Localização:** `Designed_Common\Project\Client\`

**Propósito:** Contém 99% do código-fonte compartilhado entre todas as variantes regionais.

**Conteúdo:**
- ✅ **Código-fonte do jogo** (`.cpp`, `.h`)
  - `Client.cpp`, `GameMain.cpp` - Lógica principal do jogo
  - `Packet\` - Sistema de pacotes de rede
  - `SpriteLib\`, `DXLib\`, `FrameLib\` - Bibliotecas de renderização
  - `D3DLib\`, `VolumeLib\` - Bibliotecas de áudio/gráficos
  - `MZLib\`, `OggLib\`, `RarLib\` - Bibliotecas de compressão/formato
- ✅ **Subprojetos de bibliotecas** (geram `.lib`)
  - Cada subprojeto compila para uma biblioteca estática
  - Exemplos: `SpriteLib.vcxproj` → `SP.lib`, `DXLib.vcxproj` → `DX.lib`
- ✅ **Headers compartilhados**
  - `Designed_Common\Lib\ui\` - Headers de UI e utilitários
- ❌ **NÃO contém** projeto principal `Client.vcxproj` que gera executável
- ❌ **NÃO gera** `.exe` diretamente

**Estrutura:**
```
Designed_Common\Project\Client\
├── Client.cpp              ← Código principal (mas não é projeto executável)
├── GameMain.cpp            ← Loop principal do jogo
├── Client_PCH.h            ← Precompiled header
├── SpriteLib\              ← Subprojeto: SpriteLib.vcxproj → SP.lib
│   ├── CSprite.cpp
│   └── CSpritePack.cpp
├── DXLib\                  ← Subprojeto: DXLib.vcxproj → DX.lib
│   ├── CDirectDraw.cpp
│   └── CDirectInput.cpp
├── FrameLib\               ← Subprojeto: FrameLib.vcxproj → FR.lib
├── D3DLib\                 ← Subprojeto: D3DLib.vcxproj → DX3D.lib
├── Packet\                 ← Sistema de pacotes (código-fonte, não subprojeto)
│   ├── Cpackets\
│   └── Gpackets\
└── ... (outros subprojetos e código-fonte)
```

### **Designed_Chs** (Variante Chinesa - Projeto Executável)

**Localização:** `Designed_Chs\Project\Client\`

**Propósito:** Variante específica para o mercado chinês que compila o executável final.

**Conteúdo:**
- ✅ **Projeto principal** `Client.vcxproj` e `Client.sln`
  - Define `__DESIGNED_CHS` (macro de variante chinesa)
  - Gera executável final (`fk.exe`, `dklegend_d.exe`)
- ✅ **Arquivos específicos da variante**
  - `src\a_ida_BasicException.cpp` - Workaround para `_set_new_handler`
  - `src\MyClient.cpp` - Customizações específicas CHS (se existir)
- ✅ **Referencia código de `Designed_Common`**
  - Via caminhos relativos: `..\..\..\Designed_Common\Project\Client\`
  - Todos os arquivos `.cpp` e `.h` são referenciados, não copiados

**Estrutura:**
```
Designed_Chs\Project\Client\
├── Client.vcxproj          ← PROJETO PRINCIPAL (gera .exe)
├── Client.sln              ← Solution file
├── Client.vcxproj.filters  ← Organização no Solution Explorer
├── src\
│   ├── a_ida_BasicException.cpp  ← Workaround para BasicS.lib
│   └── MyClient.cpp              ← Customizações CHS (opcional)
└── (referencia Designed_Common via caminhos relativos no .vcxproj)
```

---

## Fluxo de Compilação

### Processo Completo

```
1. Compilar Bibliotecas (em Designed_Common\Project\Client\)
   ├── SpriteLib.vcxproj    → SP.lib
   ├── DXLib.vcxproj        → DX.lib
   ├── FrameLib.vcxproj     → FR.lib
   ├── D3DLib.vcxproj       → DX3D.lib
   ├── VolumeLib.vcxproj    → Volume.lib
   ├── WinLib.vcxproj       → WinLib.lib
   └── ... (outras bibliotecas)

2. Compilar Client (em Designed_Chs\Project\Client\)
   ├── Client.vcxproj
   │   ├── Compila arquivos de Designed_Common\Project\Client\*.cpp
   │   ├── Compila arquivos de Designed_Chs\Project\Client\src\*.cpp
   │   └── Linka todas as bibliotecas (.lib)
   └── → fk.exe (executável final)
```

### Por Que Esta Ordem?

1. **Bibliotecas primeiro:** O projeto Client depende das bibliotecas compiladas
2. **Dependências automáticas:** `ProjectReference` no `.vcxproj` garante ordem correta
3. **Build paralelo:** MSBuild pode compilar bibliotecas em paralelo, mas aguarda conclusão antes do Client

---

## Arquitetura de Múltiplas Variantes

### Variantes Suportadas

| Variante | Diretório | Macro Definida | Características |
|----------|-----------|----------------|-----------------|
| **CHS** (Chinês) | `Designed_Chs\` | `__DESIGNED_CHS` | Versão chinesa simplificada |
| **Korea** (Coreano) | `Designed_Korea\` | `__DESIGNED_KOREA` | Versão coreana (padrão/completa) |
| **Japan** (Japonês) | `Designed_Japan\` | `__DESIGNED_JAPAN` | Versão japonesa |
| **International** | `Designed_Internation\` | `__DESIGNED_INTERNATION` | Versão internacional/inglês |

### O Que É Compartilhado

**Todas as variantes usam:**
- ✅ Código de `Designed_Common\Project\Client\`
- ✅ Bibliotecas de `Designed_Common\Lib\`
- ✅ Headers de `Designed_Common\Lib\ui\`
- ✅ Subprojetos de bibliotecas (SpriteLib, DXLib, etc.)

### O Que É Específico de Cada Variante

**Cada variante tem:**
- ✅ Seu próprio `Client.vcxproj` em `Designed_*\Project\Client\`
- ✅ Arquivos específicos (ex: `MyClient.cpp`, `a_ida_BasicException.cpp`)
- ✅ Configurações via `#ifdef __DESIGNED_*` em `ContentsFilter.h`
- ✅ Macro de pré-processador definida no `.vcxproj`

### Exemplo de Customização por Variante

**Arquivo:** `Designed_Common\Project\Client\ContentsFilter.h`

```cpp
#ifdef __DESIGNED_CHS
    #define __HERO_SYSTEM __ON
    #define __CHAR_DELETE __OFF
    #define __SERVER_SELECT_REVEWAL __ON
#elif defined(__DESIGNED_KOREA)
    #define __HERO_SYSTEM __ON
    #define __CHAR_DELETE __OFF
    #define __SERVER_SELECT_REVEWAL __ON
#elif defined(__DESIGNED_INTERNATION)
    #define __HERO_SYSTEM __OFF
    #define __CHAR_DELETE __ON
    #define __SERVER_SELECT_REVEWAL __OFF
#endif
```

---

## Por Que Esta Arquitetura?

### Vantagens

1. **Reutilização de Código (99%)**
   - Uma única base de código mantida
   - Mudanças em `Designed_Common` afetam todas as variantes
   - Reduz duplicação e erros

2. **Customização Regional**
   - Cada variante pode ter ajustes específicos
   - Flags de compilação (`__DESIGNED_*`) controlam features
   - Arquivos específicos (`MyClient.cpp`) para customizações maiores

3. **Compilação Independente**
   - Cada variante compila seu próprio `.exe`
   - Não há conflito entre variantes
   - Pode compilar múltiplas variantes em paralelo

4. **Manutenção Simplificada**
   - Bug fix em `Designed_Common` → corrige todas as variantes
   - Feature nova → adiciona em `Designed_Common`, ativa via flag
   - Testes podem ser feitos em uma variante e aplicar a todas

### Desvantagens

1. **Complexidade de Build**
   - Precisa compilar bibliotecas antes do Client
   - Múltiplos projetos para gerenciar

2. **Dependências de Caminhos**
   - Caminhos relativos podem quebrar se estrutura mudar
   - Requer estrutura de diretórios específica

---

## Resumo: Onde Compilar?

### ❌ **NÃO compilar em `Designed_Common`:**
- Não há projeto executável (`Client.vcxproj`) lá
- Apenas código-fonte e subprojetos de bibliotecas
- Não gera `.exe` diretamente

### ✅ **COMPILAR em `Designed_Chs`:**
- Contém o projeto principal `Client.vcxproj`
- Gera o executável final (`fk.exe`)
- Referencia automaticamente o código de `Designed_Common`
- Define a variante correta (`__DESIGNED_CHS`)

### 📁 **Estrutura de Compilação:**

```
client\
├── Designed_Common\          ← Código compartilhado (99%)
│   ├── Project\Client\       ← Código-fonte + subprojetos
│   └── Lib\                  ← Bibliotecas compiladas (.lib)
│
└── Designed_Chs\             ← Variante CHS (projeto executável)
    └── Project\Client\
        ├── Client.vcxproj    ← COMPILE AQUI
        └── src\              ← Arquivos específicos CHS
```

---

## Referências

- `MIGRATION_TO_VS2022.md` - Detalhes sobre migração e configurações
- `README.md` - Índice de toda a documentação
- `Designed_Common\Project\Client\ContentsFilter.h` - Feature flags por variante
- `Designed_Chs\Project\Client\Client.vcxproj` - Projeto principal CHS
