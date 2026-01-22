# Scripts - Dark Eden Client

Scripts utilitários para migração, build e distribuição do cliente.

---

## Scripts de Migração

### `migrate_all_projects_to_vs2022.ps1`

Migra todos os projetos de `.vcproj` para `.vcxproj` (VS2022).

**Uso:**
```powershell
cd client
.\scripts\migrate_all_projects_to_vs2022.ps1
```

**O que faz:**
- Converte 15 projetos de `.vcproj` para `.vcxproj`
- Preserva encoding CP949
- Cria `.vcxproj.filters`
- Configura PlatformToolset v143

---

### `run_full_migration.ps1`

Executa migração completa incluindo configurações adicionais.

**Uso:**
```powershell
cd client
.\scripts\run_full_migration.ps1
```

**O que faz:**
1. Executa `migrate_all_projects_to_vs2022.ps1`
2. Adiciona SDK comum aos projetos
3. Configura precompiled headers
4. Aplica correções pós-migração

---

## Scripts de Configuração

### `add_common_sdk.ps1`

Adiciona diretórios de include do SDK comum aos projetos.

**Uso:**
```powershell
cd client
.\scripts\add_common_sdk.ps1 -ProjectPath "Designed_Chs\Project\Client\Client.vcxproj"
```

**Parâmetros:**
- `-ProjectPath` - Caminho para o `.vcxproj`
- `-IsLibProject` - Se é projeto de biblioteca
- `-NeedsVirtualFileSystem` - Adiciona includes do VirtualFileSystem
- `-NeedsDirectXSDK` - Adiciona includes do DirectX SDK

---

### `configure_precompiled_header.ps1`

Configura precompiled headers (PCH) nos projetos.

**Uso:**
```powershell
cd client
.\scripts\configure_precompiled_header.ps1 -ProjectPath "Designed_Chs\Project\Client\Client.vcxproj"
```

**O que faz:**
- Configura `PrecompiledHeader` = "Use"
- Define `PrecompiledHeaderFile`
- Configura `PrecompiledHeaderOutputFile`

---

## Scripts de Distribuição

### `organize_for_distribution.bat`

Organiza executáveis e DLLs em `dist\bin\`.

**Uso:**
```cmd
cd client
scripts\organize_for_distribution.bat
```

**O que faz:**
- Cria `dist\bin\`
- Copia `fk.exe` e todas as DLLs necessárias
- Organiza estrutura limpa para distribuição

---

### `prepare_setup.bat`

Prepara estrutura completa de distribuição para criar instalador.

**Uso:**
```cmd
cd client
scripts\prepare_setup.bat
```

**O que faz:**
1. Chama `organize_for_distribution.bat`
2. Copia dados do jogo para `dist\data\`
3. Copia arquivos de configuração para `dist\`

**Resultado:** Estrutura completa em `dist\` pronta para instalador.

---

### `setup_template.iss`

Template Inno Setup para criar instalador.

**Uso:**
1. Abrir com Inno Setup Compiler
2. Ajustar configurações (AppName, AppVersion, etc.)
3. Compilar

**Requisitos:**
- Inno Setup instalado
- Estrutura `dist\` criada por `prepare_setup.bat`

---

## Estrutura de Pastas

```
client/
├── scripts/
│   ├── README.md                           # Este arquivo
│   ├── migrate_all_projects_to_vs2022.ps1  # Migração de projetos
│   ├── run_full_migration.ps1              # Migração completa
│   ├── add_common_sdk.ps1                  # Adicionar SDK
│   ├── configure_precompiled_header.ps1    # Configurar PCH
│   ├── organize_for_distribution.bat       # Organizar distribuição
│   ├── prepare_setup.bat                   # Preparar setup
│   └── setup_template.iss                  # Template Inno Setup
└── dist/                                    # Criado pelos scripts
    ├── bin/                                 # Executáveis e DLLs
    └── data/                                # Dados do jogo
```

---

## Requisitos

### PowerShell Scripts (.ps1)
- PowerShell 5.1 ou superior
- ExecutionPolicy: `Bypass` ou `RemoteSigned`
- Visual Studio 2022 instalado (para ferramentas MSBuild)

### Batch Scripts (.bat)
- Windows 10/11
- CMD ou PowerShell

### Inno Setup (.iss)
- Inno Setup Compiler instalado
- Estrutura `dist\` criada

---

## Execução

### Primeira Vez (Migração Completa)

```powershell
cd client
.\scripts\run_full_migration.ps1
```

### Apenas Organizar Distribuição

```cmd
cd client
scripts\prepare_setup.bat
```

### Criar Instalador

1. Executar `prepare_setup.bat`
2. Abrir `setup_template.iss` no Inno Setup
3. Ajustar configurações
4. Compilar

---

## Troubleshooting

### Erro: "ExecutionPolicy"

```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

### Erro: "Script não encontrado"

Certifique-se de executar de `client\`:
```cmd
cd c:\darkeden-nostaugia\client
```

### Erro: "dist não existe"

Os scripts criam automaticamente. Se falhar, criar manualmente:
```cmd
mkdir client\dist\bin
mkdir client\dist\data
```

---

## Referências

- `../docs/README.md` - Índice de documentação
- `../docs/MIGRATION_TO_VS2022.md` - Documentação principal
- `../docs/SETUP_AND_DISTRIBUTION.md` - Guia de distribuição
- `../docs/NEXT_STEPS_INSTALLER.md` - Guia de instalador
