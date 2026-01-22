# Próximos Passos: Criar Instalador com Visual Studio 2022

## Visão Geral

O Visual Studio 2022 não inclui suporte nativo para criar instaladores, mas a Microsoft fornece uma extensão oficial que adiciona essa funcionalidade.

---

## Passo 1: Instalar Extensão "Microsoft Visual Studio Installer Projects 2022"

### **Método 1: Via Visual Studio (Recomendado)**

1. **Abrir Visual Studio 2022**
2. **Menu:** `Extensions` → `Manage Extensions`
3. **Aba:** `Online`
4. **Pesquisar:** `Microsoft Visual Studio Installer Projects 2022`
5. **Clicar em:** `Download`
6. **Fechar Visual Studio** (necessário para instalar)
7. **Instalar:** O VSIX Installer abrirá automaticamente
8. **Reabrir Visual Studio**

### **Método 2: Download Direto**

1. **Acessar:** https://marketplace.visualstudio.com/items?itemName=VisualStudioClient.MicrosoftVisualStudio2022InstallerProjects
2. **Clicar em:** `Download`
3. **Executar:** O arquivo `.vsix` baixado
4. **Reabrir Visual Studio**

### **Verificar Instalação**

Após reinstalar o Visual Studio:
- **File** → **New** → **Project**
- Procurar por "Setup" ou "Installer"
- Deve aparecer: **"Setup Project"** ou **"Visual Studio Installer Projects"**

---

## Passo 2: Adicionar Setup Project ao Solution

### **2.1. Criar Setup Project**

1. **Abrir Solution:** `Designed_Chs\Project\Client\Client.sln`
2. **Botão direito na Solution** → **Add** → **New Project**
3. **Pesquisar:** `Setup Project` ou `Installer`
4. **Selecionar:** **"Setup Project"** (ou "Visual Studio Installer Projects")
5. **Nome:** `NostaugiaSetup`
6. **Localização:** `Designed_Chs\Project\Client\` (mesmo diretório do Client.sln)
7. **Clicar:** `Create`

### **2.2. Estrutura Criada**

Após criar, você terá:
```
Designed_Chs\Project\Client\
├── Client.sln
├── Client.vcxproj
└── NostaugiaSetup\
    └── NostaugiaSetup.vdproj
```

---

## Passo 3: Configurar Setup Project

### **3.1. Adicionar Primary Output (Executável + DLLs)**

1. **Botão direito em `NostaugiaSetup`** → **View** → **File System**
2. **Botão direito em "Application Folder"** → **Add** → **Project Output**
3. **Project:** Selecionar `Client`
4. **Configuration:** `Release`
5. **Selecionar:** `Primary Output`
6. **Clicar:** `OK`

**O que isso faz:**
- Adiciona automaticamente `fk.exe` (executável principal)
- Adiciona automaticamente todas as DLLs linkadas (DEUtil.dll, etc.)
- Mantém sincronizado com o build do projeto

### **3.2. Adicionar Arquivos de Dados do Jogo**

#### **Opção A: Adicionar Pasta `data\` Completa**

1. **Botão direito em "Application Folder"** → **Add** → **Folder**
2. **Nome:** `data`
3. **Botão direito em `data`** → **Add** → **File**
4. **Navegar para:** `client\nostaugia\data\`
5. **Selecionar todos os arquivos** (ou adicionar um por um):
   - `dklegend.dpk`
   - `dklegend.dpi`
   - `darkedeneng.ini`
   - Pasta `info\` (com todos os `.inf`)
   - Pasta `font\` (com `.ttf`)
   - Pasta `music\` (com todos os `.ogg`)

#### **Opção B: Adicionar Arquivos Individuais**

1. **Botão direito em "Application Folder"** → **Add** → **File**
2. **Adicionar arquivos de configuração na raiz:**
   - `FileListVersion.inf`
   - `interface.ini`
   - `item.inf`
   - `guildmapper_new.inf`
   - `Jin2.txt`
   - `DKLEGEND.HIS`
   - Outros `.inf`, `.ini`, `.txt`, `.his`

### **3.3. Configurar Propriedades do Setup Project**

1. **Botão direito em `NostaugiaSetup`** → **Properties**

#### **Propriedades Importantes:**

- **ProductName:** `Dark Eden Nostaugia`
- **Title:** `Dark Eden Nostaugia Setup`
- **Manufacturer:** `Nostaugia` (ou seu nome)
- **ProductCode:** (gerado automaticamente, não alterar)
- **RemovePreviousVersions:** `True` (se quiser atualizar versões antigas)
- **Version:** `1.0.0` (incrementar para novas versões)

#### **Output File Name:**

- **Output file name:** `Nostaugia_Setup.msi`
- **Package files as:** `In setup file` (tudo em um arquivo) ou `As loose uncompressed files` (separado)

### **3.4. Criar Atalhos (Opcional)**

1. **Botão direito em "Primary Output from Client (Release)"** → **Create Shortcut**
2. **Renomear:** `Nostaugia` (ou `Dark Eden Nostaugia`)
3. **Arrastar para:** `User's Desktop` (para atalho na área de trabalho)
4. **Arrastar para:** `User's Programs Menu` (para atalho no menu Iniciar)

**Configurar Ícone do Atalho:**
1. **Selecionar o atalho criado**
2. **Properties** → **Icon**
3. **Selecionar ícone** (`.ico` file) ou usar ícone do executável

### **3.5. Configurar Pré-requisitos (Opcional)**

Se o jogo precisar de DLLs específicas ou runtimes:

1. **Botão direito em `NostaugiaSetup`** → **Properties**
2. **Clicar em:** `Prerequisites...`
3. **Marcar opções necessárias:**
   - Visual C++ Redistributable (se necessário)
   - DirectX Runtime (se necessário)
   - Outros pré-requisitos

**Opções de Download:**
- `Download prerequisites from the same location as my application` (incluir no instalador)
- `Download prerequisites from the component vendor's website` (baixar durante instalação)

---

## Passo 4: Build do Setup Project

### **4.1. Configurar Build Configuration**

1. **Build** → **Configuration Manager**
2. **Verificar:** `NostaugiaSetup` está marcado para build
3. **Configuration:** `Release` (recomendado para distribuição)

### **4.2. Build**

**Método 1: Build Individual**
1. **Botão direito em `NostaugiaSetup`** → **Build**
2. Aguardar compilação

**Método 2: Build Solution**
1. **Build** → **Rebuild Solution**
2. Isso compila o Client primeiro, depois o Setup

### **4.3. Localização do Instalador Gerado**

Após build bem-sucedido, o instalador estará em:

```
Designed_Chs\Project\Client\NostaugiaSetup\Release\
├── Nostaugia_Setup.msi        ← Instalador principal
├── setup.exe                  ← Launcher (se configurado)
└── [arquivos de pré-requisitos, se houver]
```

---

## Passo 5: Testar Instalador

### **5.1. Teste Básico**

1. **Executar:** `Nostaugia_Setup.msi`
2. **Seguir wizard de instalação**
3. **Verificar instalação:**
   - Executável está no local correto
   - DLLs estão presentes
   - Dados do jogo (`data\`) estão instalados
   - Arquivos de configuração estão na raiz
   - Atalhos foram criados (se configurados)

### **5.2. Teste de Desinstalação**

1. **Painel de Controle** → **Programas e Recursos**
2. **Encontrar:** `Dark Eden Nostaugia`
3. **Desinstalar**
4. **Verificar:** Todos os arquivos foram removidos

### **5.3. Teste em Máquina Limpa (Recomendado)**

1. **VM ou máquina de teste** sem o jogo instalado
2. **Copiar:** `Nostaugia_Setup.msi`
3. **Instalar** na máquina limpa
4. **Verificar:** Jogo funciona corretamente
5. **Verificar:** Todas as DLLs estão presentes

---

## Passo 6: Distribuição

### **6.1. Arquivos para Distribuir**

**Opção A: Apenas MSI**
- Distribuir apenas: `Nostaugia_Setup.msi`
- Usuário executa e instala normalmente

**Opção B: MSI + Setup.exe**
- Se configurou `setup.exe` como launcher
- Distribuir ambos: `setup.exe` e `Nostaugia_Setup.msi`
- Usuário executa `setup.exe`

**Opção C: Compactado**
- Compactar `Nostaugia_Setup.msi` em ZIP
- Distribuir ZIP
- Usuário extrai e executa MSI

### **6.2. Versionamento**

Para criar nova versão:

1. **Atualizar versão no Setup Project:**
   - Botão direito em `NostaugiaSetup` → **Properties**
   - **Version:** `1.0.1` (incrementar)
   - **ProductCode:** Será gerado automaticamente (não alterar manualmente)

2. **Rebuild:**
   - Build → Rebuild Solution

3. **Novo instalador:** `Nostaugia_Setup.msi` (versão atualizada)

---

## Troubleshooting

### **Problema: "Setup Project" não aparece ao criar novo projeto**

**Causa:** Extensão não instalada ou Visual Studio não reiniciado.

**Solução:**
1. Verificar se extensão está instalada: `Extensions` → `Manage Extensions` → `Installed`
2. Fechar e reabrir Visual Studio
3. Se ainda não aparecer, reinstalar extensão

### **Problema: "Primary Output" não inclui DLLs**

**Causa:** DLLs não estão sendo copiadas para `Release\` durante build.

**Solução:**
1. Verificar Post-Build Event do projeto Client
2. Garantir que DLLs estão sendo copiadas para `$(OutDir)`
3. Rebuild do projeto Client
4. Verificar se DLLs estão em `Release\`

### **Problema: Instalador não copia arquivos de dados**

**Causa:** Arquivos não foram adicionados ao Setup Project.

**Solução:**
1. Verificar File System Editor
2. Adicionar arquivos manualmente se necessário
3. Verificar caminhos dos arquivos

### **Problema: Instalador muito grande**

**Causa:** Incluindo muitos arquivos ou pré-requisitos.

**Solução:**
1. **Properties** → **Package files as:** `As loose uncompressed files`
2. Ou remover pré-requisitos e fazer download durante instalação
3. Ou usar compressão diferente

---

## Estrutura Final do Setup Project

Após configurar corretamente, o File System Editor deve mostrar:

```
Application Folder
├── Primary Output from Client (Release)
│   └── (fk.exe + DLLs automaticamente)
├── data\
│   ├── dklegend.dpk
│   ├── dklegend.dpi
│   ├── info\
│   ├── font\
│   └── music\
├── FileListVersion.inf
├── interface.ini
├── item.inf
└── [outros arquivos de configuracao]

User's Desktop
└── Nostaugia (shortcut)

User's Programs Menu
└── Nostaugia (shortcut)
```

---

## Referências

- **Extensão:** https://marketplace.visualstudio.com/items?itemName=VisualStudioClient.MicrosoftVisualStudio2022InstallerProjects
- **Documentação Microsoft:** https://learn.microsoft.com/en-us/visualstudio/deployment/installer-projects-net-core
- **WiX Toolset (Alternativa):** https://wixtoolset.org/

---

## Resumo Rápido

```cmd
# 1. Instalar extensão
Extensions → Manage Extensions → "Microsoft Visual Studio Installer Projects 2022"

# 2. Adicionar Setup Project
Solution → Add → New Project → Setup Project

# 3. Configurar
- Adicionar Primary Output (Client)
- Adicionar arquivos de dados (data\, *.inf, etc.)
- Configurar propriedades (nome, versão, etc.)
- Criar atalhos (opcional)

# 4. Build
Build → Rebuild Solution

# 5. Testar
Executar Nostaugia_Setup.msi

# 6. Distribuir
Copiar Nostaugia_Setup.msi para distribuição
```

---

**Status:** ✅ Documentação completa. Pronto para seguir os passos!
