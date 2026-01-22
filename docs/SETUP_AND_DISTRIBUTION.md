# Setup e Distribuição

Guia para organizar arquivos compilados e preparar distribuição do cliente.

---

## Estrutura de Distribuição

### Estrutura Recomendada

```
client/
├── dist/
│   ├── bin/          # Executáveis e DLLs
│   │   ├── fk.exe
│   │   ├── *.dll
│   │   └── ...
│   ├── data/         # Dados do jogo
│   │   ├── font/
│   │   ├── info/
│   │   ├── music/
│   │   └── ...
│   ├── *.inf         # Arquivos de configuração (raiz)
│   ├── *.ini
│   └── *.txt
└── scripts/
    ├── organize_for_distribution.bat
    ├── prepare_setup.bat
    └── setup_template.iss
```

---

## Scripts de Distribuição

### 1. `organize_for_distribution.bat`

**Localização:** `scripts\organize_for_distribution.bat`

**Função:** Organiza executáveis e DLLs compilados em `client\dist\bin\`

**Uso:**
```cmd
cd client
scripts\organize_for_distribution.bat
```

**O que faz:**
- Cria `dist\bin\` se não existir
- Limpa diretório anterior
- Copia `fk.exe` de `Designed_Chs\Project\Client\Release\`
- Copia todas as DLLs do Release
- Copia DLLs de `Designed_Common\Lib\`
- Copia `DEUtil.dll` do projeto DEUtil

---

### 2. `prepare_setup.bat`

**Localização:** `scripts\prepare_setup.bat`

**Função:** Prepara estrutura completa de distribuição para criação de instalador

**Uso:**
```cmd
cd client
scripts\prepare_setup.bat
```

**O que faz:**
1. Chama `organize_for_distribution.bat` para organizar binários
2. Copia estrutura de dados de `nostaugia\data\` para `dist\data\`
3. Copia arquivos de configuração (`.inf`, `.ini`, `.txt`) para `dist\`

**Resultado:**
- Estrutura completa em `dist\` pronta para criar instalador

---

### 3. `setup_template.iss`

**Localização:** `scripts\setup_template.iss`

**Função:** Template Inno Setup para criar instalador

**Uso:**
1. Abrir com Inno Setup Compiler
2. Ajustar configurações (AppName, AppVersion, etc.)
3. Compilar

**Estrutura de Instalação:**
- Executável e DLLs → `{app}\` (raiz de instalação)
- Dados do jogo → `{app}\data\`
- Arquivos de configuração → `{app}\` (raiz)

---

## Workflow de Distribuição

### Opção 1: Distribuição Manual

1. **Compilar projeto** (Release)
2. **Organizar arquivos:**
   ```cmd
   cd client
   scripts\organize_for_distribution.bat
   ```
3. **Copiar manualmente:**
   - `dist\bin\*` → pasta de distribuição
   - `nostaugia\data\*` → pasta de distribuição\data\
   - Arquivos de configuração → raiz da distribuição

---

### Opção 2: Preparar para Instalador

1. **Compilar projeto** (Release)
2. **Preparar estrutura completa:**
   ```cmd
   cd client
   scripts\prepare_setup.bat
   ```
3. **Criar instalador:**
   - Usar `scripts\setup_template.iss` com Inno Setup
   - Ou seguir guia em `NEXT_STEPS_INSTALLER.md` para VS Installer Projects

---

## Arquivos Necessários para Distribuição

### Binários (dist\bin\)

- `fk.exe` - Executável principal
- `DEUtil.dll` - Utilitários do cliente
- `IFC22.dll` / `ifc22.dll` - Interface
- `GL.dll` / `gl.dll` - OpenGL
- `Timer.dll` / `timer.dll` - Timer
- `BasicS.dll` / `basics.dll` - Biblioteca básica
- `vorbisfile.dll`, `vorbis.dll`, `vorbisenc.dll`, `ogg.dll` - Audio
- `gmp.dll`, `pcre.dll` - Bibliotecas auxiliares
- `msvcrt.dll`, `msvcr71.dll`, `msvcirt.dll` - Runtime C

### Dados (dist\data\)

- `font\` - Fontes
- `info\` - Arquivos de informação
- `music\` - Músicas do jogo
- Outros arquivos de dados do jogo

### Configuração (raiz)

- `*.inf` - Arquivos de informação
- `*.ini` - Arquivos de configuração
- `*.txt` - Arquivos de texto

---

## Notas Importantes

1. **Post-Build Event:** O `Client.vcxproj` já tem Post-Build Event que copia DLLs automaticamente para `nostaugia\` após compilação.

2. **Estrutura `nostaugia\`:** Esta pasta contém os arquivos do jogo em execução. Use `dist\` para distribuição limpa.

3. **Encoding:** Scripts `.bat` devem ser salvos em encoding compatível (ANSI/CP1252) para funcionar corretamente no Windows.

4. **Paths Relativos:** Todos os scripts usam paths relativos baseados em `client\` como raiz.

---

## Próximos Passos

Após preparar a distribuição:

1. **Criar Instalador:**
   - Ver `NEXT_STEPS_INSTALLER.md` para guia completo
   - Usar Microsoft Visual Studio Installer Projects 2022
   - Ou usar Inno Setup com `setup_template.iss`

2. **Testar Instalação:**
   - Instalar em máquina limpa
   - Verificar se todos os arquivos estão presentes
   - Testar execução do jogo

---

## Referências

- `NEXT_STEPS_INSTALLER.md` - Guia completo para criar instalador
- `COMPLETE_FIXES_SUMMARY.md` - Resumo de todas as correções
- `MIGRATION_TO_VS2022.md` - Documentação principal de migração
