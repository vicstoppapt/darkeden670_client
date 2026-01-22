# Sistema de Atualização: Componentes e Ferramentas

## Visão Geral

O Dark Eden usa um sistema de atualização distribuído com três componentes principais:

1. **DpkUnpacker** - Ferramenta para descompactar arquivos `.dpk` (pacotes de dados do jogo)
2. **GameUpdater** - Aplicativo que verifica e baixa atualizações do jogo
3. **AutoPatchManager** - Ferramenta para desenvolvedores criar patches (arquivos `.dp2`)

---

## 1. DpkUnpacker

### **Localização:** `Designed_Common\Project\DpkUnpacker\`

### **Propósito:**
Ferramenta de linha de comando para descompactar arquivos `.dpk` (Dark Eden Package).

### **O que faz:**
- **Descompacta** arquivos do formato `.dpk` (pacote de dados do jogo)
- Usa `VirtualFileSystem` (VFS) para acessar arquivos dentro do `.dpk`
- Permite extrair arquivos individuais ou todos os arquivos de uma vez

### **Formato de Arquivos:**
- **`.dpk`** - Pacote principal (contém dados comprimidos)
- **`.dpi`** - Índice do pacote (lista de arquivos dentro do `.dpk`)
- **`.dpl`** - Lista de pacotes (opcional)

### **Uso:**
```cmd
DpkUnpaker.exe
# Solicita caminho do arquivo ou "all" para descompactar tudo
# Exemplo: "data/ui/txt/title.rpk" ou "all"
```

### **Funcionalidades:**
1. **Descompactar arquivo específico:**
   - Usuário informa caminho do arquivo
   - Extrai apenas esse arquivo do `.dpk`

2. **Descompactar tudo:**
   - Usuário informa "all"
   - Extrai todos os arquivos do `.dpk` para o sistema de arquivos real

3. **Criar pacote (modo `__DPK_PAKER__`):**
   - Permite criar novos arquivos `.dpk` a partir de um diretório
   - Usa `CStatDir` para contar arquivos e diretórios

### **Dependências:**
- `VirtualFileSystem` (VFS) - Sistema de arquivos virtual do jogo
- `CNFS` - Sistema de arquivos NFS usado internamente

### **Código Principal:**
```cpp
// Abre sistema de arquivos virtual
vfs.Start("dklegend", O_RDWR);

// Descompacta arquivo específico ou todos
if(strcmp(buf, "all") == 0) {
    // Descompacta todos os arquivos
    for(int i = 0; i < tt.gl_pathc; i++) {
        vfs.CreateRealFile(fileName, fileName);
    }
} else {
    // Descompacta arquivo específico
    vfs.CreateRealFile(buf, buf);
}
```

### **Quando usar:**
- **Desenvolvimento:** Extrair arquivos do `.dpk` para edição
- **Debug:** Verificar conteúdo dos pacotes
- **Modding:** Extrair recursos do jogo para modificação

---

## 2. GameUpdater

### **Localização:** `Designed_Common\Project\GameUpdater\`

### **Propósito:**
Aplicativo MFC (Windows) que verifica e baixa atualizações do jogo antes de iniciar o cliente.

### **O que faz:**
1. **Verifica versão** do jogo (local vs servidor)
2. **Baixa arquivos de patch** (`.dp2`) do servidor HTTP
3. **Aplica patches** aos arquivos do jogo
4. **Inicia o jogo** (`nostaugia.exe` ou `fk.exe`) após atualização

### **Fluxo de Atualização:**

```
1. Usuário executa GameUpdater.exe
   ↓
2. Carrega configuração (updateclient.inf)
   ↓
3. Verifica status do servidor de atualização
   ↓
4. Compara versão local vs servidor (version.inf)
   ↓
5. Se precisa atualizar:
   ├── Baixa FileList.inf ou RecentFileList.inf
   ├── Gera lista de arquivos para atualizar
   ├── Verifica espaço em disco
   ├── Baixa arquivos .dp2 (patches)
   ├── Aplica patches:
   │   ├── Remove arquivos deletados
   │   ├── Aplica arquivos atualizados
   │   ├── Aplica mudanças de tipo de packing
   │   └── Atualiza FileList.inf
   └── Limpa arquivos temporários
   ↓
6. Inicia jogo (nostaugia.exe)
```

### **Componentes Principais:**

#### **UpdateManager** (`UpdateManager.h`, `UpdateManager.cpp`)
- Gerencia todo o processo de atualização
- Baixa arquivos via HTTP
- Aplica patches aos arquivos do jogo
- Verifica integridade (MD5 checksum)

#### **UpdateManagerThread** (`UpdateManagerThread.cpp`)
- Thread separada para processar atualização
- Evita travar a interface do usuário
- Mostra progresso na tela

#### **GameUpdaterDlg** (`GameUpdaterDlg.cpp`)
- Interface gráfica (MFC Dialog)
- Mostra progresso da atualização
- Exibe mensagens de status

### **Arquivos de Configuração:**

#### **`data/info/updateclient.inf`**
- Configuração do cliente de atualização
- URL do servidor de atualização
- Diretórios de dados

#### **`version.inf`** (servidor)
- Versão atual do jogo no servidor
- Comparado com versão local

#### **`FileList.inf`** ou `RecentFileList.inf`** (servidor)
- Lista de todos os arquivos do jogo
- Inclui MD5 checksum, tamanho, tipo de packing
- Usado para determinar quais arquivos precisam atualização

### **Formato de Patch:**
- **`.dp2`** - Arquivo de patch comprimido
- Contém diferenças entre versão antiga e nova
- Aplicado via `RealData` (descomprime e aplica)

### **Servidor de Atualização:**
- **Protocolo:** HTTP (não TCP socket)
- **URL padrão:** `fk.t1dk.com` (hardcoded em `UpdateManager.cpp`)
- **Estrutura esperada:**
  ```
  http://{HttpUrl}/darkeden/recentpatchdata/{DataDir}/
  ├── version.inf
  ├── RecentFileList.inf
  └── [arquivos .dp2]
  ```

### **Funcionalidades Especiais:**

#### **Atualização do Próprio Updater:**
- `CheckUpdaterPatch()` - Verifica se o updater precisa atualizar
- Se sim, baixa nova versão e aplica antes de continuar

#### **Guild Mark Updates:**
- `CheckGuildVersion()` - Verifica atualizações de emblemas de guild
- `DownloadRecentGuildMark()` - Baixa novos emblemas

#### **Verificação de Integridade:**
- MD5 checksum de cada arquivo
- Verifica se patch não está corrompido antes de aplicar

### **Quando usar:**
- **Distribuição:** Incluir `GameUpdater.exe` com instalação
- **Atualizações:** Usuário executa updater antes de jogar
- **Manutenção:** Sistema automático de patches

---

## 3. AutoPatchManager

### **Localização:** `Designed_Common\Project\AutoPatchManager20\`

### **Propósito:**
Ferramenta MFC (Windows) para desenvolvedores criarem patches (arquivos `.dp2`) para distribuição.

### **O que faz:**
1. **Compara** versão antiga vs versão nova do jogo
2. **Identifica** arquivos modificados, novos e deletados
3. **Gera** arquivos de patch (`.dp2`)
4. **Cria** `FileList.inf` atualizado

### **Interface:**
- **Dialog MFC** com lista de arquivos
- **Colunas:** Nome do arquivo, tipo de packing, status
- **Modos:**
  - **Recent File Mode:** Arquivos da versão mais recente
  - **New File Mode:** Arquivos novos ou modificados

### **Funcionalidades:**

#### **1. BuildPatchFileListTable()**
- Analisa diretório de arquivos
- Compara com versão anterior
- Identifica mudanças

#### **2. MakePatch()**
- Gera arquivos `.dp2` para arquivos modificados
- Cria `FileList.inf` atualizado
- Aplica compressão/configurações

#### **3. AutoSplitSpk()**
- Divide arquivos grandes em múltiplos patches
- Útil para arquivos muito grandes

#### **4. BackupUpdateToZip()**
- Cria backup das atualizações em ZIP
- Útil para versionamento

### **Tipos de Packing:**
O sistema suporta diferentes tipos de empacotamento:
- Tipos definidos em `s_szPackingString[][]`
- Permite mudança de tipo de packing entre versões

### **Fluxo de Criação de Patch:**

```
1. Desenvolvedor modifica arquivos do jogo
   ↓
2. Abre AutoPatchManager
   ↓
3. Seleciona diretório com versão nova
   ↓
4. AutoPatchManager compara com versão antiga:
   ├── Identifica arquivos modificados
   ├── Identifica arquivos novos
   ├── Identifica arquivos deletados
   └── Identifica mudanças de tipo de packing
   ↓
5. Desenvolvedor revisa lista de mudanças
   ↓
6. Clica em "Make Patch"
   ↓
7. AutoPatchManager gera:
   ├── Arquivos .dp2 (patches comprimidos)
   ├── FileList.inf atualizado
   └── (Opcional) Backup em ZIP
   ↓
8. Desenvolvedor faz upload para servidor de atualização
```

### **Arquivos Gerados:**

#### **`.dp2` Files:**
- Um arquivo `.dp2` por arquivo modificado/novo
- Comprimido e pronto para distribuição
- Nome: `{caminho_arquivo}.dp2`

#### **`FileList.inf`:**
- Lista completa de arquivos do jogo
- Inclui MD5 checksum, tamanho, tipo de packing
- Usado pelo `GameUpdater` para verificar atualizações

### **Quando usar:**
- **Desenvolvimento:** Após modificar arquivos do jogo
- **Release:** Antes de publicar nova versão
- **Hotfix:** Para correções urgentes

---

## Relação Entre os Componentes

### **Fluxo Completo:**

```
┌─────────────────────────────────────────────────────────┐
│ DESENVOLVIMENTO                                         │
└─────────────────────────────────────────────────────────┘
         │
         │ 1. Desenvolvedor modifica arquivos
         ↓
┌─────────────────────────────────────────────────────────┐
│ AutoPatchManager                                        │
│ - Compara versões                                       │
│ - Gera patches (.dp2)                                   │
│ - Cria FileList.inf                                     │
└─────────────────────────────────────────────────────────┘
         │
         │ 2. Upload para servidor HTTP
         ↓
┌─────────────────────────────────────────────────────────┐
│ SERVIDOR DE ATUALIZAÇÃO (HTTP)                          │
│ http://fk.t1dk.com/darkeden/recentpatchdata/            │
│ ├── version.inf                                         │
│ ├── RecentFileList.inf                                  │
│ └── [arquivos .dp2]                                     │
└─────────────────────────────────────────────────────────┘
         │
         │ 3. Usuário executa GameUpdater.exe
         ↓
┌─────────────────────────────────────────────────────────┐
│ GameUpdater                                             │
│ - Verifica versão                                      │
│ - Baixa patches (.dp2)                                 │
│ - Aplica patches                                        │
│ - Inicia jogo                                           │
└─────────────────────────────────────────────────────────┘
         │
         │ 4. Jogo usa arquivos atualizados
         ↓
┌─────────────────────────────────────────────────────────┐
│ Cliente do Jogo (fk.exe)                                │
│ - Lê arquivos de data/                                  │
│ - Usa VirtualFileSystem para acessar .dpk               │
└─────────────────────────────────────────────────────────┘
```

### **DpkUnpacker (Ferramenta Auxiliar):**
- **Uso:** Desenvolvimento/debug
- **Quando:** Precisa extrair arquivos do `.dpk` para edição
- **Não faz parte do fluxo de atualização automático**

---

## Formato de Arquivos

### **`.dpk` (Dark Eden Package)**
- **Formato:** Pacote comprimido contendo dados do jogo
- **Estrutura:** Usa VirtualFileSystem (VFS) internamente
- **Uso:** Armazena recursos do jogo (sprites, UI, dados)
- **Exemplo:** `dklegend.dpk`, `darkeden.dpk`

### **`.dpi` (Dark Eden Package Index)**
- **Formato:** Índice dos arquivos dentro do `.dpk`
- **Uso:** Lista de arquivos e suas localizações no pacote
- **Exemplo:** `dklegend.dpi`

### **`.dp2` (Dark Eden Patch)**
- **Formato:** Arquivo de patch comprimido
- **Uso:** Contém diferenças entre versões
- **Aplicação:** Descomprimido e aplicado pelo GameUpdater
- **Geração:** Criado pelo AutoPatchManager

### **`.inf` (Information Files)**
- **Formato:** Arquivos de texto com informações
- **Tipos:**
  - `version.inf` - Versão do jogo
  - `FileList.inf` - Lista completa de arquivos
  - `RecentFileList.inf` - Lista de arquivos recentes
  - `updateclient.inf` - Configuração do updater

---

## Integração com Setup/Instalador

### **Considerações para Instalador:**

1. **GameUpdater.exe deve ser incluído:**
   - Usuário precisa do updater para receber atualizações
   - Pode ser o executável principal (substitui `fk.exe` como ponto de entrada)

2. **Estrutura de Diretórios:**
   ```
   [Pasta de Instalação]\
   ├── GameUpdater.exe      ← Ponto de entrada
   ├── fk.exe               ← Cliente do jogo
   ├── data\
   │   ├── dklegend.dpk
   │   ├── dklegend.dpi
   │   └── info\
   │       └── updateclient.inf  ← Configuração do updater
   └── [outros arquivos]
   ```

3. **Atalho:**
   - Criar atalho para `GameUpdater.exe` (não `fk.exe`)
   - Updater verifica atualizações e inicia o jogo

4. **DpkUnpacker:**
   - **NÃO incluir** no instalador (ferramenta de desenvolvimento)
   - Manter apenas para desenvolvedores

5. **AutoPatchManager:**
   - **NÃO incluir** no instalador (ferramenta de desenvolvimento)
   - Usar apenas para criar patches

---

## Resumo

| Componente | Propósito | Usuário | Incluir no Instalador? |
|------------|-----------|---------|------------------------|
| **DpkUnpacker** | Descompactar `.dpk` | Desenvolvedor | ❌ Não |
| **GameUpdater** | Verificar e baixar atualizações | Usuário final | ✅ Sim (principal) |
| **AutoPatchManager** | Criar patches (`.dp2`) | Desenvolvedor | ❌ Não |

---

## Referências

- `Designed_Common\Project\DpkUnpacker\` - Código do DpkUnpacker
- `Designed_Common\Project\GameUpdater\` - Código do GameUpdater
- `Designed_Common\Project\AutoPatchManager20\` - Código do AutoPatchManager
- `VirtualFileSystem` - Sistema de arquivos virtual usado pelos componentes

---

**Status:** ✅ Análise completa dos três componentes do sistema de atualização.
