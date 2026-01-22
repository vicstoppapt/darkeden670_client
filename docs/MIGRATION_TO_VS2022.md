# Migração de Projetos para Visual Studio 2022

## Objetivo
Migrar todos os projetos de formato `.vcproj` (Visual Studio 2003/2005) para `.vcxproj` (Visual Studio 2022), preservando a codificação EUC-KR (CP949) dos arquivos fonte.

## Projetos Migrados

A migração foi aplicada aos seguintes projetos:

1. **Client** - `client\Designed_Chs\Project\Client\`
2. **CWinMain Library** - `client\Designed_Common\Project\Client\CWinMain Library\`
3. **D3DLib** - `client\Designed_Common\Project\Client\D3DLib\`
4. **DEUtil** - `client\Designed_Common\Project\Client\DEUtil\`
5. **DirectXLib** - `client\Designed_Common\Project\Client\DXLib\`
6. **FileCheckLib** - `client\Designed_Common\Project\Client\FileCheckLib\`
7. **Frame Library** - `client\Designed_Common\Project\Client\FrameLib\`
8. **MZLib** - `client\Designed_Common\Project\Client\MZLib\`
9. **MiniLZO** - `client\Designed_Common\Project\Client\MiniLZO\`
10. **OggLib** - `client\Designed_Common\Project\Client\OggLib\`
11. **RarLib** - `client\Designed_Common\Project\Client\RarLib\`
12. **SpriteLib** - `client\Designed_Common\Project\Client\SpriteLib\`
13. **VirtualFileSystem** - `client\Designed_Common\Project\Client\VirtualFileSystem\`
14. **VolumeLib** - `client\Designed_Common\Project\Client\VolumeLib\`
15. **lib** - `client\Designed_Chs\Project\NEW - VS_UI\lib\`

**Total:** 15 projetos migrados com sucesso.

## Arquivos Necessários

### Arquivos a Criar
1. **Client.vcxproj** - Projeto no formato VS2022
2. **Client.vcxproj.filters** - Organização de arquivos no Solution Explorer
3. **Client.vcxproj.user** (opcional) - Configurações de usuário (debug, working directory)

### Arquivos a Atualizar
1. **Client.sln** - Atualizar para formato VS2022 (Format Version 12.00)

### Arquivos a Manter
- **Client.vcproj** - Manter como referência (não deletar)
- Arquivos fonte (.cpp, .h) - **NÃO MODIFICAR** (preservar encoding CP949)

## Processo de Migração

### Passo 1: Converter .vcproj para .vcxproj

**Script disponível:** `modernization\scripts\Modules\ProjectModernization.psm1`

Função: `Convert-AllProjects`

**O que faz:**
- Lê `Client.vcproj` (encoding gb2312/CP949)
- Extrai configurações (Debug, Release, ReleaseLog)
- Converte para formato `.vcxproj` em **CP949** (corrigido)
- Define PlatformToolset como `v143` (VS2022)
- Preserva configurações de compilador e linker

**✅ CORRIGIDO:** Scripts agora salvam diretamente em CP949.

**Resultado:** `Client.vcxproj` criado, mas sem lista de arquivos fonte.

### Passo 2: Adicionar Arquivos Fonte ao .vcxproj

**Script disponível:** `modernization\scripts\Modules\ProjectModernization.psm1`

Função: `Add-SourceFilesToProjects`

**O que faz:**
- Extrai lista de arquivos de `Client.vcproj`
- Adiciona `<ClCompile Include="...">` para .cpp, .c, .cxx
- Adiciona `<ClInclude Include="...">` para .h, .hpp
- Adiciona `<ResourceCompile Include="...">` para .rc

**Resultado:** `Client.vcxproj` com todos os arquivos fonte listados.

### Passo 3: Criar .vcxproj.filters

**Script disponível:** `modernization\scripts\Modules\PathAndStructure.psm1`

Função: `Create-ProjectFilters`

**O que faz:**
- Extrai estrutura de filtros de `Client.vcproj`
- Cria hierarquia de filtros (Source Files, Header Files, subpastas)
- Associa cada arquivo ao seu filtro correspondente
- Gera GUIDs únicos para cada filtro

**Resultado:** `Client.vcxproj.filters` criado com organização de arquivos.

### Migração em Lote de Todos os Projetos

Foi criado o script `migrate_all_projects_to_vs2022.ps1` que migra automaticamente todos os 15 projetos de uma vez.

**Script:** `client\scripts\migrate_all_projects_to_vs2022.ps1`

**Projetos migrados automaticamente:**
1. Client
2. CWinMain Library
3. D3DLib
4. DEUtil
5. DirectXLib
6. FileCheckLib
7. Frame Library
8. MZLib
9. MiniLZO
10. OggLib
11. RarLib
12. SpriteLib
13. VirtualFileSystem
14. VolumeLib
15. lib

**Processo executado para cada projeto:**
1. Conversão de `.vcproj` para `.vcxproj` (CP949)
2. Adição de arquivos fonte ao `.vcxproj`
3. Criação de `.vcxproj.filters` (CP949)

**Garantias:**
- Todos os arquivos salvos em CP949 (sem UTF-8 BOM)
- Encoding de arquivos fonte preservado
- Estrutura de projetos mantida
- Configurações de compilação preservadas

**Resultado:** Todos os 15 projetos foram migrados com sucesso. Todos os arquivos `.vcxproj` e `.filters` foram criados e salvos em CP949.

### Passo 4: Atualizar Client.sln

#### Problema

O arquivo `Client.sln` estava no formato antigo (Format Version 8.00) usado pelo Visual Studio 2003/2005. O Visual Studio 2022 não abre soluções nesse formato antigo, resultando em erro ao tentar abrir o projeto.

#### Causa Técnica

O Visual Studio 2022 requer o formato de solução 12.00 (introduzido no Visual Studio 2013) com estruturas atualizadas:

1. **Format Version**: O formato 8.00 é incompatível com VS2022
2. **GlobalSection Names**: Os nomes das seções mudaram:
   - `SolutionConfiguration` -> `SolutionConfigurationPlatforms`
   - `ProjectConfiguration` -> `ProjectConfigurationPlatforms`
3. **Estrutura de Configurações**: As configurações de plataforma mudaram de formato:
   - Antigo: `Debug = Debug`
   - Novo: `Debug|Win32 = Debug|Win32`
4. **Headers VS2022**: Faltavam os headers específicos do Visual Studio 2022
5. **ProjectGuid**: O GUID do projeto Client estava desatualizado e não correspondia ao GUID no `.vcxproj`
6. **Referências de Projeto**: Referências ainda apontavam para `.vcproj` em vez de `.vcxproj`

#### Alterações Realizadas

1. **Atualização do Format Version**
   - De: `Format Version 8.00`
   - Para: `Format Version 12.00`

2. **Adição de Headers VS2022**
   ```
# Visual Studio Version 17
   VisualStudioVersion = 17.0.31903.59
MinimumVisualStudioVersion = 10.0.40219.1
```

3. **Atualização de Referências de Projeto**
   - Todas as referências `.vcproj` foram alteradas para `.vcxproj`

4. **Correção do ProjectGuid do Projeto Client**
   - De: `{81B97D19-A5D4-4EA5-80ED-A29C1E9BD40D}`
   - Para: `{458C083E-3636-463E-B10F-10EE3899FDAF}` (corresponde ao GUID no Client.vcxproj)

5. **Atualização de GlobalSection Names**
   - `GlobalSection(SolutionConfiguration)` -> `GlobalSection(SolutionConfigurationPlatforms)`
   - `GlobalSection(ProjectConfiguration)` -> `GlobalSection(ProjectConfigurationPlatforms)`

6. **Atualização do Formato de Configurações**
   - SolutionConfigurationPlatforms:
     - `Debug = Debug` -> `Debug|Win32 = Debug|Win32`
     - `Release = Release` -> `Release|Win32 = Release|Win32`
     - `ReleaseLog = ReleaseLog` -> `ReleaseLog|Win32 = ReleaseLog|Win32`
   - ProjectConfigurationPlatforms:
     - `{GUID}.Debug.ActiveCfg = Debug|Win32` -> `{GUID}.Debug|Win32.ActiveCfg = Debug|Win32`
     - `{GUID}.Debug.Build.0 = Debug|Win32` -> `{GUID}.Debug|Win32.Build.0 = Debug|Win32`
     - (Mesma lógica aplicada para Release e ReleaseLog)

7. **Remoção de ProjectSection Vazios**
   - Removidos `ProjectSection(ProjectDependencies)` vazios de projetos que não possuem dependências

8. **Adição de SolutionProperties**
   ```
   GlobalSection(SolutionProperties) = preSolution
       HideSolutionNode = FALSE
   EndGlobalSection
   ```

9. **Atualização de ExtensibilityGlobals**
   - Adicionado `SolutionGuid` na seção `ExtensibilityGlobals`

#### Por Que a Versão Antiga Não Abria

O Visual Studio 2022 utiliza um parser de solução que:
- Rejeita formatos anteriores à versão 12.00
- Requer a estrutura `SolutionConfigurationPlatforms` e `ProjectConfigurationPlatforms`
- Valida que os ProjectGuids correspondam aos arquivos `.vcxproj` referenciados
- Exige o formato de configuração com plataforma explícita (`Config|Platform`)

Quando o VS2022 tenta abrir um `.sln` no formato 8.00, o parser falha na validação inicial e retorna erro, impedindo a abertura da solução.

#### Por Que a Nova Versão Abre

A versão atualizada:
- Utiliza o Format Version 12.00, suportado pelo VS2022
- Contém os headers corretos que identificam a versão do Visual Studio
- Possui a estrutura de GlobalSections no formato esperado pelo parser
- Mantém consistência entre ProjectGuids no `.sln` e nos `.vcxproj`
- Usa o formato de configuração de plataforma que o VS2022 espera
- Referencia corretamente os arquivos `.vcxproj` em vez de `.vcproj`

O parser do VS2022 valida todas essas condições e, ao passar, permite a abertura da solução.

#### Encoding

O arquivo foi salvo em CP949 (EUC-KR) sem BOM, conforme política de encoding do projeto. Isso garante compatibilidade com o restante do código-fonte que utiliza CP949.

## Requisitos de Codificação

### Arquivos de Projeto (.vcxproj, .sln, .filters)
- **Encoding:** CP949 (EUC-KR) - **OBRIGATÓRIO** para .vcxproj e .filters
- **Encoding:** UTF-8 com BOM - Permitido para .sln (padrão Visual Studio)
- **Proibido:** UTF-8 sem BOM para arquivos de projeto
- **✅ CORRIGIDO:** Scripts agora salvam .vcxproj e .filters em CP949

### Arquivos Fonte (.cpp, .h, .c, .hpp)
- **Encoding:** CP949 (EUC-KR) - **OBRIGATÓRIO**
- **Proibido:** UTF-8 (com ou sem BOM)
- **Ação:** NÃO modificar arquivos fonte diretamente

### Regras de Operação
1. Scripts de modernização preservam encoding de arquivos fonte
2. **Arquivos de projeto (.vcxproj, .filters) são salvos como CP949** (corrigido)
3. Nunca adicionar flag `/utf-8` ao compilador (permite CP949)
4. Scripts usam CP949 explicitamente para salvar arquivos de projeto

## Estrutura de Referência

Projeto de referência migrado (com problemas de encoding):
```
c:\darkeden-nostaugia - Copia\client-project-compiling\client-project\Designed_Chs\Project\Client\
```

**Arquivos presentes:**
- Client.vcxproj
- Client.vcxproj.filters
- Client.vcxproj.user
- Client.sln (atualizado)

**Problema identificado:** Migração anterior não preservou encoding corretamente.

## Execução da Migração

### ✅ Scripts Corrigidos

Os scripts em `modernization\scripts\Modules\` foram corrigidos para salvar arquivos de projeto (.vcxproj, .filters) diretamente em **CP949**.

### Opção 1: Migrar Todos os Projetos (Recomendado)

Execute o script `migrate_all_projects_to_vs2022.ps1` localizado em `client\scripts\` para migrar todos os projetos de uma vez.

**Como Executar:**

```powershell
cd "c:\darkeden-nostaugia\client"
powershell -ExecutionPolicy Bypass -File .\scripts\migrate_all_projects_to_vs2022.ps1
```

**O que o script faz:**
1. Identifica automaticamente todos os projetos que precisam ser migrados
2. Para cada projeto:
   - Converte `.vcproj` → `.vcxproj` (em CP949)
   - Adiciona arquivos fonte ao `.vcxproj`
   - Cria `.vcxproj.filters` (em CP949)
3. Exibe resumo com sucessos e falhas

**Vantagens:**
- Migra todos os projetos de uma vez
- Processo automatizado e consistente
- Todos os arquivos salvos em CP949 (sem UTF-8 BOM)
- Relatório de progresso detalhado

### Opção 2: Migrar Projeto Individual

Execute o script `migrate_client_to_vs2022.ps1` para migrar apenas o projeto Client.

#### Como Executar o Script Isoladamente

**Método 1: Via PowerShell (Recomendado)**

1. Abra o PowerShell (não ISE)
2. Navegue até o diretório:
   ```powershell
   cd "c:\darkeden-nostaugia\client\Designed_Chs\Project\Client"
   ```

3. Execute o script com bypass da política de execução:
   ```powershell
   powershell -ExecutionPolicy Bypass -File .\migrate_client_to_vs2022.ps1
   ```

   **OU** configure a política de execução uma vez (recomendado):
   ```powershell
   Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
   .\migrate_client_to_vs2022.ps1
   ```

**Método 2: Via Explorer (Duplo Clique)**

1. Abra o Explorer e navegue até:
   ```
   c:\darkeden-nostaugia\client\Designed_Chs\Project\Client
   ```

2. Clique com botão direito em `migrate_client_to_vs2022.ps1`
3. Selecione "Executar com PowerShell"

   **Nota:** Se der erro de política, use o Método 1 ou 3.

**Método 3: Via Linha de Comando (CMD)**

1. Abra o CMD
2. Execute:
   ```cmd
   cd /d "c:\darkeden-nostaugia\client\Designed_Chs\Project\Client"
   powershell -ExecutionPolicy Bypass -File migrate_client_to_vs2022.ps1
   ```

**Troubleshooting:**

- **Erro "não está assinado digitalmente" ou "não pode ser carregado":**
  
  **Solução Rápida (temporária):**
  ```powershell
  powershell -ExecutionPolicy Bypass -File .\migrate_client_to_vs2022.ps1
  ```
  
  **Solução Permanente (recomendado):**
  ```powershell
  Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
  ```
  Isso permite executar scripts locais sem assinatura. Depois disso, você pode executar:
  ```powershell
  .\migrate_client_to_vs2022.ps1
  ```
  
  **Verificar política atual:**
  ```powershell
  Get-ExecutionPolicy -List
  ```

- **Erro "módulos não encontrados":**
  - Verifique se o caminho `modernization\scripts\Modules` existe
  - O script resolve caminhos relativos automaticamente

- **Erro de encoding:**
  - Scripts foram corrigidos para salvar em CP949
  - Se ainda houver problemas, verifique se o arquivo `Client.vcproj` existe

**O que o script faz:**
1. Importa os módulos necessários automaticamente
2. Converte `Client.vcproj` → `Client.vcxproj` (em CP949)
3. Adiciona arquivos fonte ao `.vcxproj`
4. Cria `Client.vcxproj.filters` (em CP949)
5. Mostra resumo do que foi criado

**Vantagens:**
- Execução isolada - não precisa importar módulos manualmente
- Caminhos relativos resolvidos automaticamente
- Mensagens de progresso claras

### Opção 3: Usar Scripts Diretamente (Avançado)

Se preferir executar os scripts diretamente sem o wrapper:

```powershell
# 1. Navegar até o diretório do projeto
cd "c:\darkeden-nostaugia\client\Designed_Chs\Project\Client"

# 2. Importar módulos
$scriptRoot = "c:\darkeden-nostaugia\modernization\scripts\Modules"
Import-Module (Join-Path $scriptRoot "ProjectModernization.psm1")
Import-Module (Join-Path $scriptRoot "PathAndStructure.psm1")

# 3. Converter projeto
Convert-AllProjects -ProjectRoot "c:\darkeden-nostaugia\client\Designed_Chs\Project\Client"

# 4. Adicionar arquivos fonte
Add-SourceFilesToProjects -ProjectRoot "c:\darkeden-nostaugia\client\Designed_Chs\Project\Client"

# 5. Criar filters
Create-ProjectFilters -ProjectRoot "c:\darkeden-nostaugia\client\Designed_Chs\Project\Client"
```

**Nota:** Scripts agora salvam diretamente em CP949 (corrigido).

### Opção 4: Migração Manual

1. Abrir `Client.vcproj` no Visual Studio 2022
2. VS2022 oferece conversão automática
3. **ATENÇÃO:** Verificar encoding dos arquivos fonte após conversão
4. Validar com `validate_encoding_integrity.ps1`

## Validação Pós-Migração

### Script de Validação
```
modernization\scripts\Validation\validate_encoding_integrity.ps1
```

**O que verifica:**
- Arquivos fonte mantêm encoding CP949
- Arquivos de projeto DEVEM ser CP949 (não UTF-8)
- Nenhum arquivo fonte foi convertido para UTF-8

### Verificação Manual

**Verificar encoding de arquivo fonte:**
```powershell
$bytes = [System.IO.File]::ReadAllBytes("arquivo.cpp")
$cp949 = [System.Text.Encoding]::GetEncoding(949)
$content = $cp949.GetString($bytes)
# Verificar se caracteres coreanos aparecem corretamente
```

**Verificar encoding de arquivo de projeto (.vcxproj, .filters):**
```powershell
# Verificar se Client.vcxproj está em CP949 (não UTF-8)
$bytes = [System.IO.File]::ReadAllBytes("Client.vcxproj")
$cp949 = [System.Text.Encoding]::GetEncoding(949)
$content = $cp949.GetString($bytes)
# Se houver caracteres coreanos no XML, devem aparecer corretamente

# Verificar se não está em UTF-8 (sem BOM)
$utf8 = [System.Text.Encoding]::UTF8
$utf8Content = $utf8.GetString($bytes)
# Comparar com $content - se diferentes, arquivo está em CP949 (correto)
```

## Diferenças do Projeto de Referência

### Problemas Identificados na Migração Anterior

1. **Encoding:** Possível conversão de arquivos fonte para UTF-8
2. **Caminhos:** Verificar se caminhos relativos estão corretos
3. **Configurações:** Verificar se todas as flags de compilador foram preservadas

### ✅ Correções Aplicadas nos Scripts

**Scripts corrigidos para salvar em CP949:**

1. **ProjectModernization.psm1:** Todas as ocorrências de `UTF8Encoding` foram substituídas por CP949
   - Linha 257-258: `Convert-AllProjects` - corrigido
   - Linha 406-407: `Fix-VcxprojXmlStructure` - corrigido
   - Linha 437-438: `Fix-VcxprojFormatting` - corrigido
   - Linha 501-502: `Fix-VcxprojItemGroups` - corrigido

2. **PathAndStructure.psm1:** Todas as ocorrências de `UTF8Encoding` foram substituídas por CP949
   - Linha 188-193: `Create-ProjectFilters` - corrigido (usa MemoryStream + conversão)
   - Linha 215-217: `Add-IncludeDirectory` - corrigido
   - Linha 227-228: `Add-IncludeDirectory` (fallback) - corrigido
   - Linha 270-271: `Fix-ProjectPaths` - corrigido
   - Linha 314-315: `Add-CommonSDKInclude` - corrigido
   - Linha 420-422: `Fix-VcxprojFilters` - corrigido

**Nota:** Arquivos .sln mantêm UTF-8 com BOM (padrão Visual Studio).

## Checklist de Migração

### Para Cada Projeto Migrado

- [ ] [NomeProjeto].vcxproj criado
- [ ] [NomeProjeto].vcxproj contém todas as configurações (Debug, Release, ReleaseLog)
- [ ] [NomeProjeto].vcxproj lista todos os arquivos fonte (.cpp, .h)
- [ ] [NomeProjeto].vcxproj.filters criado com hierarquia correta
- [ ] **Encoding de [NomeProjeto].vcxproj validado (CP949, não UTF-8)**
- [ ] **Encoding de [NomeProjeto].vcxproj.filters validado (CP949, não UTF-8)**
- [ ] Encoding de arquivos fonte validado (CP949)
- [ ] Projeto abre corretamente no VS2022
- [ ] Projeto compila sem erros de encoding
- [ ] Caracteres coreanos aparecem corretamente no código

### Para a Solução

- [ ] Client.sln atualizado para formato VS2022
- [ ] Todas as referências de projetos atualizadas para `.vcxproj`
- [ ] Todos os ProjectGuids consistentes entre `.sln` e `.vcxproj`
- [ ] Solução abre corretamente no VS2022
- [ ] Todos os projetos são carregados sem erros

## Notas Importantes

1. **NÃO deletar** arquivos `.vcproj` - manter como referência
2. **NÃO modificar** arquivos fonte diretamente - usar scripts
3. **SEMPRE validar** encoding após qualquer modificação
4. Todos os arquivos de projeto (`.vcxproj`, `.filters`) são salvos em **CP949 sem BOM**
5. **PROIBIDO** usar UTF-8 BOM em arquivos de projeto
6. O script `scripts\migrate_all_projects_to_vs2022.ps1` migra todos os projetos automaticamente

## Histórico de Migração

### Migração em Lote (Todos os Projetos)

**Data:** Execução realizada com sucesso

**Projetos Migrados:** 15 projetos

**Lista Completa:**
1. Client - `client\Designed_Chs\Project\Client\`
2. CWinMain Library - `client\Designed_Common\Project\Client\CWinMain Library\`
3. D3DLib - `client\Designed_Common\Project\Client\D3DLib\`
4. DEUtil - `client\Designed_Common\Project\Client\DEUtil\`
5. DirectXLib - `client\Designed_Common\Project\Client\DXLib\`
6. FileCheckLib - `client\Designed_Common\Project\Client\FileCheckLib\`
7. Frame Library - `client\Designed_Common\Project\Client\FrameLib\`
8. MZLib - `client\Designed_Common\Project\Client\MZLib\`
9. MiniLZO - `client\Designed_Common\Project\Client\MiniLZO\`
10. OggLib - `client\Designed_Common\Project\Client\OggLib\`
11. RarLib - `client\Designed_Common\Project\Client\RarLib\`
12. SpriteLib - `client\Designed_Common\Project\Client\SpriteLib\`
13. VirtualFileSystem - `client\Designed_Common\Project\Client\VirtualFileSystem\`
14. VolumeLib - `client\Designed_Common\Project\Client\VolumeLib\`
15. lib - `client\Designed_Chs\Project\NEW - VS_UI\lib\`

**Arquivos Criados para Cada Projeto:**
- `[NomeProjeto].vcxproj` - Projeto no formato VS2022 (CP949)
- `[NomeProjeto].vcxproj.filters` - Organização de arquivos (CP949)

**Resultado:** 
- Todos os 15 projetos foram migrados com sucesso
- Todos os arquivos foram salvos em CP949 (sem UTF-8 BOM)
- Todos os arquivos fonte mantiveram encoding CP949
- Nenhum arquivo foi convertido para UTF-8

**Script Utilizado:** `client\scripts\migrate_all_projects_to_vs2022.ps1`

**Validação:**
- Todos os arquivos `.vcxproj` foram criados e verificados
- Todos os arquivos `.vcxproj.filters` foram criados e verificados
- Encoding CP949 confirmado para todos os arquivos de projeto
- Solução `Client.sln` atualizada para referenciar todos os projetos migrados

### Processo de Restauração e Migração Completa

**Quando Usar:** Quando `Designed_Chs` e `Designed_Common` foram removidos ou corrompidos, ou para começar do zero com um backup limpo.

**Localização do Backup:** `backup-client\`

**Estrutura do Backup:**
- `backup-client\Designed_Chs\` - Projetos específicos do cliente
- `backup-client\Designed_Common\` - Bibliotecas comuns

**Processo Completo:**

1. **Remover Diretórios Existentes (se necessário):**
   ```powershell
   Remove-Item -Path "c:\darkeden-nostaugia\client\Designed_Chs" -Recurse -Force -ErrorAction SilentlyContinue
   Remove-Item -Path "c:\darkeden-nostaugia\client\Designed_Common" -Recurse -Force -ErrorAction SilentlyContinue
   ```

2. **Copiar do Backup:**
   ```powershell
   Copy-Item -Path "c:\darkeden-nostaugia\backup-client\Designed_Chs" -Destination "c:\darkeden-nostaugia\client\Designed_Chs" -Recurse -Force
   Copy-Item -Path "c:\darkeden-nostaugia\backup-client\Designed_Common" -Destination "c:\darkeden-nostaugia\client\Designed_Common" -Recurse -Force
   ```

3. **Executar Script de Migração Completa:**
   ```powershell
   cd c:\darkeden-nostaugia\client
   powershell -ExecutionPolicy Bypass -File "run_full_migration.ps1"
   ```

**Nota Importante sobre GUIDs:**
- Quando os projetos são migrados, novos GUIDs podem ser gerados para cada `.vcxproj`
- O `Client.sln` precisa ter os GUIDs correspondentes aos `.vcxproj` gerados
- Se o Visual Studio abrir a solução após a migração, ele pode atualizar os GUIDs automaticamente no `.sln`
- Para garantir consistência, verifique se os ProjectGuids no `.sln` correspondem aos `<ProjectGuid>` nos `.vcxproj`

**Validação Após Migração:**
- Verificar se `Client.sln` abre sem erros no Visual Studio 2022
- Verificar se todos os 15 projetos são carregados corretamente
- Verificar se não há erros XML (`<#text> unrecognized`)
- Verificar se os GUIDs dos projetos no `.sln` correspondem aos nos `.vcxproj`

**Se a Migração Falhar:**
- Apagar `Designed_Chs` e `Designed_Common` novamente
- Copiar do backup novamente
- Executar o script novamente até funcionar corretamente

### Script de Migração Completa (run_full_migration.ps1)

**Localização:** `client\scripts\run_full_migration.ps1`

**Objetivo:** Executar todo o processo de migração na ordem correta, incluindo migração de projetos, atualização da solução, adição de referências ao common_sdk e configuração de Precompiled Header.

**Processo Executado (4 Passos):**

#### Passo 1: Migração de Todos os Projetos
- **Script:** `scripts\migrate_all_projects_to_vs2022.ps1`
- **Ação:** Converte todos os 15 projetos de `.vcproj` para `.vcxproj`
- **Resultado:** 
  - 15 arquivos `.vcxproj` criados (CP949)
  - 15 arquivos `.vcxproj.filters` criados (CP949)
  - Todos os arquivos fonte adicionados aos projetos

#### Passo 2: Atualização do Client.sln
- **Ação:** Atualiza `Client.sln` para formato VS2022
- **Alterações Realizadas:**
  - Format Version: `8.00` → `12.00`
  - Adiciona headers VS2022 (Visual Studio Version 17)
  - Atualiza referências: `.vcproj` → `.vcxproj`
  - Corrige ProjectGuid do Client para corresponder ao `.vcxproj` (extraído do `Client.vcxproj`)
  - Atualiza GlobalSection names:
    - `SolutionConfiguration` → `SolutionConfigurationPlatforms`
    - `ProjectConfiguration` → `ProjectConfigurationPlatforms`
- **Nota sobre GUIDs dos Projetos:**
  - O script atualiza automaticamente o GUID do projeto Client
  - GUIDs dos projetos de biblioteca são atualizados quando o Visual Studio abre a solução
  - Se necessário, o Visual Studio pode atualizar todos os GUIDs automaticamente ao carregar a solução
  - Para verificar: comparar ProjectGuids no `.sln` com `<ProjectGuid>` nos `.vcxproj` correspondentes
  - Atualiza formato de configurações: `Debug = Debug` → `Debug|Win32 = Debug|Win32`
  - Adiciona `SolutionProperties` e `SolutionGuid`
- **Encoding:** CP949 (sem UTF-8 BOM)

#### Passo 3: Adição de Referências ao common_sdk e Diretórios de Include
- **Script:** `scripts\add_common_sdk.ps1`
- **Projeto:** Client.vcxproj
- **Configurações Adicionadas:**
  - `AdditionalIncludeDirectories`: 
    - `..\..\..\..\common_sdk\Include` - Headers do common_sdk
    - `..\..\..\Designed_Common\Project\Client\VirtualFileSystem` - Headers do VirtualFileSystem (ex: vfstream.h)
    - `..\..\..\Designed_Common\Project\Client` - Diretório base dos projetos comuns
    - `..\..\..\Designed_Common\Project\Client\Packet` - Headers de pacotes de rede
    - `..\..\..\Designed_Common\Project\Client\WinLib` - Bibliotecas Windows
  - `AdditionalLibraryDirectories`: `..\..\..\..\common_sdk\Lib` e `..\..\..\..\common_sdk\bin`
- **Aplicado em:** Todas as configurações (Debug, Release, ReleaseLog)
- **Motivo:** Esses diretórios estavam no `.vcproj` antigo mas não foram migrados automaticamente. O script restaura todas as referências necessárias
- **Encoding:** CP949 (sem UTF-8 BOM)

#### Passo 4: Configuração de Precompiled Header
- **Script:** `scripts\configure_precompiled_header.ps1`
- **Projeto:** Client.vcxproj
- **Configurações Adicionadas:**
  - **ClCompile Global (Debug, Release, ReleaseLog):**
    - `PrecompiledHeader="Use"`
    - `PrecompiledHeaderFile="Client_PCH.h"`
  - **Client_PCH.cpp (específico):**
    - `PrecompiledHeader="Create"` (para gerar o `.pch`)
    - `PrecompiledHeaderFile="Client_PCH.h"`
- **Encoding:** CP949 (sem UTF-8 BOM)

**Execução:**
```powershell
cd c:\darkeden-nostaugia\client
powershell -ExecutionPolicy Bypass -File "run_full_migration.ps1"
```

**Garantias:**
- Todos os passos executados na ordem correta
- Todos os arquivos salvos em CP949 (sem UTF-8 BOM)
- Encoding de arquivos fonte preservado
- Solução pronta para abrir no Visual Studio 2022

**Validação Final:**
- 15 projetos migrados com sucesso
- Client.sln atualizado e válido para VS2022
- Referências ao common_sdk configuradas
- Precompiled Header configurado corretamente
- Nenhum erro de encoding ou formato

### Configurações Adicionais do Projeto Client

#### Referências ao common_sdk e Diretórios de Include

**Arquivo:** `Client.vcxproj`

**Localização:** Seções `ItemDefinitionGroup` para Debug, Release e ReleaseLog

**Configurações Adicionadas:**

1. **ClCompile - AdditionalIncludeDirectories:**
   ```xml
   <AdditionalIncludeDirectories>..\..\..\..\common_sdk\Include;..\..\..\Designed_Common\Project\Client\VirtualFileSystem;..\..\..\Designed_Common\Project\Client;..\..\..\Designed_Common\Project\Client\Packet;..\..\..\Designed_Common\Project\Client\WinLib;%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
   ```
   
   **Diretórios incluídos:**
   - `..\..\..\..\common_sdk\Include` - Headers do common_sdk
   - `..\..\..\Designed_Common\Project\Client\VirtualFileSystem` - Headers do VirtualFileSystem (ex: vfstream.h)
   - `..\..\..\Designed_Common\Project\Client` - Diretório base dos projetos comuns
   - `..\..\..\Designed_Common\Project\Client\Packet` - Headers de pacotes de rede
   - `..\..\..\Designed_Common\Project\Client\WinLib` - Bibliotecas Windows

2. **Link - AdditionalLibraryDirectories:**
   ```xml
   <AdditionalLibraryDirectories>..\..\..\..\common_sdk\Lib;..\..\..\..\common_sdk\bin;%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>
   ```

**Por Que É Necessário:**
- O projeto Client depende de bibliotecas e headers localizados em `client/common_sdk`
- O código usa includes como `#include "vfstream.h"` que está em `VirtualFileSystem/`
- Sem essas referências, o compilador não encontra os headers necessários (ex: erro `Cannot open include file: 'vfstream.h'`)
- As bibliotecas não são linkadas corretamente durante o build

**Nota sobre Estrutura de Diretórios:**
- No `.vcproj` antigo, esses diretórios estavam explicitamente listados nos `AdditionalIncludeDirectories`
- O caminho original referia `..\..\..\..\Darkeden\Designed_Common\project\client\...` (estrutura do computador antigo do desenvolvedor)
- Na migração para `.vcxproj`, esses diretórios foram convertidos para a estrutura atual: `..\..\..\Designed_Common\Project\Client\...`
- Os caminhos relativos são calculados a partir do `.vcxproj` localizado em `client\Designed_Chs\Project\Client\`

**Script Automático:**
- O script `scripts\add_common_sdk.ps1` foi atualizado para adicionar automaticamente todos esses diretórios
- Execute `scripts\add_common_sdk.ps1` ou `scripts\run_full_migration.ps1` para configurar automaticamente

**Encoding:** CP949 (sem UTF-8 BOM)

#### Precompiled Header (PCH)

**Arquivo:** `Client.vcxproj`

**Configuração Global (ItemDefinitionGroup):**

Para todas as configurações (Debug, Release, ReleaseLog):
```xml
<ClCompile>
  <PrecompiledHeader>Use</PrecompiledHeader>
  <PrecompiledHeaderFile>Client_PCH.h</PrecompiledHeaderFile>
  ...
</ClCompile>
```

**Configuração Específica para Client_PCH.cpp:**

```xml
<ClCompile Include="..\..\..\Designed_Common\Project\Client\Client_PCH.cpp">
  <PrecompiledHeader Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">Create</PrecompiledHeader>
  <PrecompiledHeader Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">Create</PrecompiledHeader>
  <PrecompiledHeader Condition="'$(Configuration)|$(Platform)'=='ReleaseLog|Win32'">Create</PrecompiledHeader>
  <PrecompiledHeaderFile Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">Client_PCH.h</PrecompiledHeaderFile>
  <PrecompiledHeaderFile Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">Client_PCH.h</PrecompiledHeaderFile>
  <PrecompiledHeaderFile Condition="'$(Configuration)|$(Platform)'=='ReleaseLog|Win32'">Client_PCH.h</PrecompiledHeaderFile>
</ClCompile>
```

**Por Que É Necessário:**
- Precompiled Headers aceleram significativamente a compilação
- `Client_PCH.cpp` gera o arquivo `.pch` (Precompiled Header)
- Todos os outros arquivos `.cpp` usam o `.pch` gerado
- Sem essa configuração, ocorre erro: "Cannot open include file: 'client_PCH.h': No such file or directory"

**Erro XML Corrigido:**
- **Problema:** Literais `\`r\`n` no XML causavam erro `<#text> unrecognized`
- **Solução:** Removidos literais e substituídos por quebras de linha reais
- **Resultado:** XML válido e bem formatado

**Encoding:** CP949 (sem UTF-8 BOM)

### Correção de Problemas de Build após Migração

#### Problema 1: ConfigurationType Incorreto em Projetos de Biblioteca

**Erro:**
```
Error LNK1561: entry point must be defined
```

**Projetos Afetados:**
- VolumeLib
- MiniLZO
- DEUtil

**Causa:**
O script de migração (`ProjectModernization.psm1`) não estava capturando corretamente o `ConfigurationType` dos atributos da tag `<Configuration>` no `.vcproj` antigo. A regex capturava apenas o conteúdo interno, não os atributos da tag.

**Valores Corretos nos `.vcproj` Antigos:**
- **VolumeLib:** `ConfigurationType="4"` → StaticLibrary
- **MiniLZO:** `ConfigurationType="4"` → StaticLibrary
- **DEUtil:** `ConfigurationType="2"` → DynamicLibrary

**Correção Aplicada:**
1. **VolumeLib.vcxproj** e **MiniLZO.vcxproj:**
   - Alterado `<ConfigurationType>Application</ConfigurationType>` para `<ConfigurationType>StaticLibrary</ConfigurationType>` nas 2 configurações (Debug e Release)

2. **DEUtil.vcxproj:**
   - Alterado `<ConfigurationType>Application</ConfigurationType>` para `<ConfigurationType>DynamicLibrary</ConfigurationType>` nas 2 configurações (Debug e Release)

3. **Correção no Script (`ProjectModernization.psm1`):**
   - Linha 25 e 31: Regex modificada para capturar atributos separadamente:
     ```powershell
     # Antes:
     '<Configuration\s+Name="([^"]+)"[^>]*>(.*?)</Configuration>'
     
     # Depois:
     '<Configuration\s+Name="([^"]+)"([^>]*)>(.*?)</Configuration>'
     ```
   - Linha 27 e 33: Adicionado campo `Attributes` no hash:
     ```powershell
     $configurations += @{ Name = $configMatch.Groups[1].Value; Attributes = $configMatch.Groups[2].Value; Content = $configMatch.Groups[3].Value }
     ```
   - Linha 68-70: Alterado para buscar `ConfigurationType`, `UseOfMFC` e `CharacterSet` nos atributos ao invés do conteúdo:
     ```powershell
     # Antes: $config.Content -match 'ConfigurationType="(\d+)"'
     # Depois: $attributes = $config.Attributes
     #         $attributes -match 'ConfigurationType="(\d+)"'
     ```

**Por Que Funcionava Antes:**
No `.vcproj` antigo, o `ConfigurationType` estava no atributo da tag `<Configuration>`, mas o script procurava apenas no conteúdo interno. Bibliotecas estáticas/dinâmicas não têm entry point (`main()`/`WinMain()`), então quando configuradas como `Application`, geravam erro "entry point must be defined".

#### Problema 2: AdditionalIncludeDirectories Faltando em Projetos de Biblioteca

**Erro:**
```
Error C1083: Cannot open include file: '[arquivo].h': No such file or directory
```

**Projetos Afetados e Correções Aplicadas:**

| Projeto | Includes Faltando | Caminho Relativo Adicionado | Configurações Corrigidas |
|---------|------------------|---------------------------|-------------------------|
| **D3DLib** | `CDirectDraw.h`, `CSpriteSurface.h` | `..;..\SpriteLib` | Debug, Release |
| **DirectXLib** | `Profiler.h`, `DXLib\CDirectSound.h` | `..;.` | Debug, Release |
| **FileCheckLib** | `zlib.h` | `..\MZLib` | Debug, Release |
| **Frame Library** | `vfstream.h`, `CSetManager.h` | `..\VirtualFileSystem;..\SpriteLib` | Debug, Release |
| **OggLib** | `ogg/ogg.h` | `.` | Debug, Release |
| **RarLib** | `vfstream.h` | `..\VirtualFileSystem` | Debug, Release |
| **SpriteLib** | `Client_PCH.h`, `CDirectDrawSurface.h`, `vfstream.h` | `..;..\VirtualFileSystem` | Debug, Release |
| **VirtualFileSystem** | `WarningKiller.h` | `..` | Debug, Release, ReleaseLog |

**Causa:**
Durante a migração, os projetos de biblioteca tiveram suas seções `<ClCompile>` geradas vazias (`<ClCompile></ClCompile>`), perdendo os `AdditionalIncludeDirectories` que estavam configurados no `.vcproj` antigo.

**Correção Aplicada:**
Adicionado `AdditionalIncludeDirectories` em cada projeto conforme as dependências identificadas. Os caminhos relativos são calculados a partir do diretório do `.vcxproj` para os diretórios de origem dos headers.

**Exemplo (SpriteLib):**
```xml
<ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
  <ClCompile>
    <AdditionalIncludeDirectories>..;..\VirtualFileSystem;%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
  </ClCompile>
  ...
</ItemDefinitionGroup>
```

**Nota:** `..` referencia o diretório `Client\` (diretório pai), permitindo incluir headers como `Client_PCH.h` e `CDirectDrawSurface.h`.

**Por Que Funcionava Antes:**
No `.vcproj` antigo, os `AdditionalIncludeDirectories` eram capturados e convertidos durante a migração, mas o script não estava adicionando esses diretórios aos projetos gerados, deixando as seções `<ClCompile>` vazias.

#### Problema 3: Client_PCH.h no Projeto lib

**Erro:**
```
Error C1083: Cannot open include file: 'client_PCH.h': No such file or directory
```

**Projeto:** lib (`Designed_Chs\Project\NEW - VS_UI\lib\`)

**Causa:**
O projeto `lib` usa seu próprio `Client_PCH.h` localizado em `Designed_Common\Project\NEW - VS_UI\lib\Client_PCH.h`, e esse arquivo inclui `AtlTypes/atltypes.h` e `ContentsFilter.h` que estão em `Designed_Common\Project\Client\`.

**Correção Aplicada:**
Adicionado `AdditionalIncludeDirectories` no `lib.vcxproj`:
- `..\..\..\..\Designed_Common\Project\NEW - VS_UI\lib` - para encontrar `Client_PCH.h`
- `..\..\..\..\Designed_Common\Project\Client` - para encontrar `AtlTypes/atltypes.h` e `ContentsFilter.h`

**Script Atualizado:**
O script `scripts\add_common_sdk.ps1` foi atualizado para detectar o projeto `lib` e adicionar ambos os diretórios automaticamente.

**Nota sobre Múltiplos Client_PCH.h:**
Existem múltiplos arquivos `Client_PCH.h` no projeto:
- `Designed_Common\Project\Client\Client_PCH.h` - usado pelo projeto `Client` (com PCH ativo)
- `Designed_Common\Project\NEW - VS_UI\lib\Client_PCH.h` - usado pelo projeto `lib` (apenas include normal, PCH desabilitado)
- `Designed_Common\Project\Client\CppUnitTestApp\Client_PCH.h` - usado pelo CppUnitTestApp

Não há conflito: cada projeto usa seu próprio `Client_PCH.h` apropriado.

#### Problema 4: Headers VS_UI e Dependências Faltando no Projeto lib (46 erros C1083)

**Erro:**
```
Error C1083: Cannot open include file: 'VS_UI.h': No such file or directory
Error C1083: Cannot open include file: 'VS_UI_Base.h': No such file or directory
Error C1083: Cannot open include file: 'VS_UI_GameCommon.h': No such file or directory
Error C1083: Cannot open include file: 'Basics.h': No such file or directory
Error C1083: Cannot open include file: 'FL2.h': No such file or directory
Error C1083: Cannot open include file: 'vfstream.h': No such file or directory
Error C1083: Cannot open include file: 'DX3D.h': No such file or directory
[... total de 46 erros similares]
```

**Projeto:** lib (`Designed_Chs\Project\NEW - VS_UI\lib\`)

**Causa:**
O projeto `lib` compila arquivos que dependem de headers localizados em múltiplos diretórios:
1. Headers VS_UI (`VS_UI.h`, `VS_UI_Base.h`, `VS_UI_GameCommon.h`, etc.) - localizados em `Designed_Common\Project\NEW - VS_UI\src\header\`
2. Headers de widget (`Basics.h`, `FL2.h`) - `Basics.h` em `Designed_Common\Lib\ui\`, `FL2.h` em `Designed_Common\Project\NEW - VS_UI\src\hangul\`
3. Headers do Client (`vfstream.h`, `DX3D.h`) - `vfstream.h` em `Designed_Common\Project\Client\VirtualFileSystem\`, `DX3D.h` em `Designed_Common\Project\Client\D3DLib\`

O `lib.vcxproj` originalmente tinha apenas 2 diretórios configurados:
- `..\..\..\..\Designed_Common\Project\NEW - VS_UI\lib` (para `Client_PCH.h`)
- `..\..\..\..\Designed_Common\Project\Client` (para `AtlTypes/atltypes.h` e `ContentsFilter.h`)

Faltavam 5 diretórios críticos para encontrar os headers usados pelos arquivos fonte do projeto.

**Correção Aplicada:**
Adicionados 5 diretórios adicionais ao `AdditionalIncludeDirectories` no `lib.vcxproj` para todas as configurações (Debug, Release, ReleaseLog):

1. `..\..\..\..\Designed_Common\Project\NEW - VS_UI\src\header` - para headers VS_UI_*.h
2. `..\..\..\..\Designed_Common\Project\NEW - VS_UI\src\hangul` - para `FL2.h`
3. `..\..\..\..\Designed_Common\Lib\ui` - para `Basics.h`
4. `..\..\..\..\Designed_Common\Project\Client\VirtualFileSystem` - para `vfstream.h`
5. `..\..\..\..\Designed_Common\Project\Client\D3DLib` - para `DX3D.h`

**Valor Final do AdditionalIncludeDirectories:**
```xml
<AdditionalIncludeDirectories>..\..\..\..\Designed_Common\Project\NEW - VS_UI\lib;..\..\..\..\Designed_Common\Project\NEW - VS_UI\src\header;..\..\..\..\Designed_Common\Project\NEW - VS_UI\src\hangul;..\..\..\..\Designed_Common\Lib\ui;..\..\..\..\Designed_Common\Project\Client;..\..\..\..\Designed_Common\Project\Client\VirtualFileSystem;..\..\..\..\Designed_Common\Project\Client\D3DLib;%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
```

**Correção Adicional Aplicada (Extensão do Problema 4):**
Após resolver os 46 erros iniciais, foram identificados mais 5 tipos de erros C1083 restantes:

1. **`Unicorn.h`** (usado como `Unicorn.h` mas arquivo real é `unicorn.h`) - faltava diretório `Designed_Common\Project\NEW - VS_UI\src\widget\`
2. **`SP.h` e `CSpriteSurface.h`** - faltava diretório `Designed_Common\Project\Client\SpriteLib\`
3. **`DMusicI.h`** (usado como `DMusicI.h` mas arquivo real é `dmusici.h`) - faltava diretório `common_sdk\Include\`
4. **`FR.h`** - faltava diretório `Designed_Common\Project\Client\FrameLib\`
5. **`CImm.h`** - faltava diretório `Designed_Common\Project\NEW - VS_UI\src\Imm\` (erro crítico após resolver includes anteriores)

**Diretórios Finais Adicionados (Total: 12 diretórios):**
1. `..\..\..\..\Designed_Common\Project\NEW - VS_UI\lib` - para `Client_PCH.h`
2. `..\..\..\..\Designed_Common\Project\NEW - VS_UI\src\header` - para headers VS_UI_*.h
3. `..\..\..\..\Designed_Common\Project\NEW - VS_UI\src\hangul` - para `FL2.h`
4. `..\..\..\..\Designed_Common\Project\NEW - VS_UI\src\widget` - para `unicorn.h` (Unicorn.h)
5. `..\..\..\..\Designed_Common\Project\NEW - VS_UI\src\Imm` - para `CImm.h` ⭐ NOVO
6. `..\..\..\..\Designed_Common\Lib\ui` - para `Basics.h`
7. `..\..\..\..\Designed_Common\Project\Client` - para `AtlTypes/atltypes.h`, `ContentsFilter.h`
8. `..\..\..\..\Designed_Common\Project\Client\VirtualFileSystem` - para `vfstream.h`
9. `..\..\..\..\Designed_Common\Project\Client\D3DLib` - para `DX3D.h`
10. `..\..\..\..\Designed_Common\Project\Client\SpriteLib` - para `SP.h`, `CSpriteSurface.h`
11. `..\..\..\..\Designed_Common\Project\Client\FrameLib` - para `FR.h`
12. `..\..\..\..\common_sdk\Include` - para `dmusici.h` (DMusicI.h)

**Script Atualizado:**
O script `scripts\add_common_sdk.ps1` foi atualizado para incluir todos os 12 diretórios necessários quando processar o projeto `lib` (`-IsLibProject`). O script agora verifica cada diretório individualmente e adiciona apenas os que faltam.

**Análise Comparativa .vcproj vs .vcxproj:**
Uma comparação entre o `.vcproj` antigo do projeto `lib` e o `.vcxproj` novo revelou que o diretório `Imm` estava presente no original mas não foi migrado inicialmente. Esse diretório contém headers relacionados a Input Method Manager (IMM) e é referenciado por `VS_UI_widget.h` que inclui `CImm.h`.

**Nota sobre Case Sensitivity:**
Alguns includes usam case diferente do arquivo real:
- `Unicorn.h` vs `unicorn.h` - Windows não é case-sensitive, mas o compilador procura no diretório `widget` que estava faltando
- `DMusicI.h` vs `dmusici.h` - Windows não é case-sensitive, mas o diretório `common_sdk\Include` estava faltando

**Por Que Funcionava Antes:**
No `.vcproj` antigo (VS2003/2005), provavelmente esses diretórios estavam configurados ou o compilador VC6 usava caminhos absolutos baseados na estrutura do computador do desenvolvedor. Durante a migração para `.vcxproj`, apenas os diretórios básicos (`lib` e `Client`) foram inicialmente migrados, deixando de fora os diretórios específicos de headers VS_UI, widgets, SpriteLib e common_sdk.

#### Problema 5: CAnimationFrame.h Faltando no Projeto Client

**Erro:**
```
Error E1696: cannot open source file "CAnimationFrame.h"
```

**Projeto:** Client (`Designed_Chs\Project\Client\`)

**Arquivo:** `MItem.h` (linha 69)

**Causa:**
O arquivo `MItem.h` inclui `CAnimationFrame.h` e a classe `MItem` herda de `CAnimationFrame`:
```cpp
// MItem.h linha 69
#include "CAnimationFrame.h"

// MItem.h linha 77
class MItem : public MObject, public CAnimationFrame {
```

O header `CAnimationFrame.h` está localizado em `Designed_Common\Project\Client\FrameLib\CAnimationFrame.h`, que é compilado pelo projeto `Frame Library` (biblioteca estática separada).

O `Client.vcxproj` não tinha `FrameLib` nos `AdditionalIncludeDirectories`, então o compilador não conseguia encontrar `CAnimationFrame.h` ao processar `MItem.h`.

**Correção Aplicada:**
Adicionado `..\..\..\Designed_Common\Project\Client\FrameLib` ao `AdditionalIncludeDirectories` no `Client.vcxproj` para todas as configurações (Debug, Release, ReleaseLog).

**Configuração Final do Client.vcxproj (linhas 82, 102, 122):**
```xml
<AdditionalIncludeDirectories>
  ..\..\..\..\common_sdk\Include;
  ..\..\..\Designed_Common\Project\Client\VirtualFileSystem;
  ..\..\..\Designed_Common\Project\Client;
  ..\..\..\Designed_Common\Project\Client\Packet;
  ..\..\..\Designed_Common\Project\Client\WinLib;
  ..\..\..\Designed_Common\Project\Client\FrameLib;
  %(AdditionalIncludeDirectories)
</AdditionalIncludeDirectories>
```

**Script Atualizado:**
O script `scripts\add_common_sdk.ps1` foi atualizado para incluir `FrameLib` no array `$includeDirs` quando processar o `Client.vcxproj` (linha 177).

**Cadeia de Dependências:**
```
Client (projeto)
  └─> MItem.h (linha 69)
       └─> #include "CAnimationFrame.h"
            └─> Localização: Designed_Common\Project\Client\FrameLib\CAnimationFrame.h
                 └─> #include "vfstream.h" (VirtualFileSystem - já configurado)
                 └─> #include "DrawTypeDef.h" (precisa estar acessível via FrameLib ou Client)
```

**Por Que Funcionava Antes:**
No `.vcproj` antigo, o diretório `FrameLib` provavelmente estava incluído nos `AdditionalIncludeDirectories` ou o compilador VC6/VC2003 tinha acesso automático aos subdiretórios do projeto Client. Durante a migração, o `FrameLib` não foi adicionado explicitamente ao `Client.vcxproj`.

#### Problema 6: RarFile.h e VS_UI_filepath.h Faltando no Projeto Client

**Erro:**
```
Error E1696: cannot open source file "RarFile.h"
Error E1696: cannot open source file "VS_UI_filepath.h"
```

**Projeto:** Client (`Designed_Chs\Project\Client\`)

**Arquivo:** `MHelpMessageManager.h` (linhas 20-21)

**Causa:**
O arquivo `MHelpMessageManager.h` inclui dois headers:
```cpp
// MHelpMessageManager.h linhas 20-21
#include "RarFile.h"
#include "VS_UI_filepath.h"
```

O projeto usa `CRarFile m_pack_file` (linha 114) e as macros `RPK_HELP` e `RPK_PASSWORD` definidas em `VS_UI_filepath.h` (usadas em `MHelpMessageManager.cpp` linha 64).

- `RarFile.h` está localizado em `Designed_Common\Project\Client\RarLib\RarFile.h`
- `VS_UI_filepath.h` está localizado em `Designed_Common\Project\NEW - VS_UI\src\header\VS_UI_filepath.h`

O `Client.vcxproj` não tinha esses diretórios nos `AdditionalIncludeDirectories`, então o compilador não conseguia encontrar os headers ao processar `MHelpMessageManager.h`.

**Correção Aplicada:**
Adicionados dois novos diretórios ao `AdditionalIncludeDirectories` no `Client.vcxproj` para todas as configurações (Debug, Release, ReleaseLog):
- `..\..\..\Designed_Common\Project\Client\RarLib` - Para `RarFile.h`
- `..\..\..\Designed_Common\Project\NEW - VS_UI\src\header` - Para `VS_UI_filepath.h`

**Configuração Atualizada do Client.vcxproj (linhas 82, 102, 122):**
```xml
<AdditionalIncludeDirectories>
  ..\..\..\..\common_sdk\Include;
  ..\..\..\Designed_Common\Project\Client\VirtualFileSystem;
  ..\..\..\Designed_Common\Project\Client;
  ..\..\..\Designed_Common\Project\Client\Packet;
  ..\..\..\Designed_Common\Project\Client\WinLib;
  ..\..\..\Designed_Common\Project\Client\FrameLib;
  ..\..\..\Designed_Common\Project\Client\RarLib;
  ..\..\..\Designed_Common\Project\NEW - VS_UI\src\header;
  %(AdditionalIncludeDirectories)
</AdditionalIncludeDirectories>
```

**Script Atualizado:**
O script `scripts\add_common_sdk.ps1` foi atualizado para incluir `RarLib` e `NEW - VS_UI\src\header` no array `$includeDirs` quando processar o `Client.vcxproj` (linhas 178-179).

**Cadeia de Dependências:**
```
Client (projeto)
  └─> MHelpMessageManager.h (linhas 20-21)
       ├─> #include "RarFile.h"
       │    └─> Localização: Designed_Common\Project\Client\RarLib\RarFile.h
       │         └─> Define classe CRarFile
       └─> #include "VS_UI_filepath.h"
            └─> Localização: Designed_Common\Project\NEW - VS_UI\src\header\VS_UI_filepath.h
                 └─> Define macros: RPK_HELP, RPK_PASSWORD, etc.

MHelpMessageManager.cpp (linha 64)
  └─> Usa RPK_HELP e RPK_PASSWORD (definidos em VS_UI_filepath.h)
```

**Por Que Funcionava Antes:**
No `.vcproj` antigo, esses diretórios provavelmente estavam incluídos nos `AdditionalIncludeDirectories` ou o compilador VC6/VC2003 tinha acesso automático aos subdiretórios do projeto Client e do projeto VS_UI. Durante a migração, `RarLib` e `NEW - VS_UI\src\header` não foram adicionados explicitamente ao `Client.vcxproj`.

### Correções de Código Aplicadas

#### Correção 1: Variável `bHighResolution` Não Declarada em `VS_UI_Title.cpp`

**Erro:**
```
Error C2065: 'bHighResolution': undeclared identifier
```

**Arquivo:** `Designed_Common\Project\NEW - VS_UI\src\VS_UI_Title.cpp` (linha 5076)

**Função:** `C_VS_UI_SERVER_SELECT::GroupView()`

**Causa:**
A variável `bHighResolution` estava declarada dentro de um bloco `#if` (linha 5052), mas era usada em um bloco `#else` subsequente (linha 5076), fazendo com que estivesse fora de escopo.

**Correção Aplicada:**
Adicionada declaração `bool bHighResolution = g_pUserInformation->iResolution_x > 800;` diretamente dentro do bloco `#else` antes de seu uso (linha 5076).

**Nota:** Outras funções no mesmo arquivo (`C_VS_UI_NEWCHAR::Show()`, `C_VS_UI_TITLE::Show()`, `C_VS_UI_TITLE::Start()`) já declaram `bHighResolution` corretamente no escopo da função.

#### Correção 2: Variável `i` Não Declarada em Loops `for` em `VS_UI_Title.cpp`

**Erro:**
```
Error C2065: 'i': undeclared identifier (múltiplas linhas: 5390, 5395, 5401, 5410, 5419)
```

**Arquivo:** `Designed_Common\Project\NEW - VS_UI\src\VS_UI_Title.cpp` (função `C_VS_UI_SERVER_SELECT::CharBarCount()`)

**Causa:**
A variável `i` foi declarada como `for(int i = 0; ...)` no primeiro loop (linha 5385), tornando-a local apenas àquele loop. Loops subsequentes na mesma função tentaram usar `i` sem redeclaração, causando erro de `undeclared identifier`.

**Correção Aplicada:**
- Declarado `int i;` antes do primeiro loop (linha 5385) no escopo da função
- Alterado `for(int i = 0; ...)` para `for(i = 0; ...)` no primeiro loop e em todos os loops subsequentes, garantindo que `i` seja declarada uma vez para todo o escopo da função

**Contexto:** Modern C++ (C++99+) torna a variável de loop `for(int i = ...)` local ao loop, diferentemente do comportamento antigo (C89) onde a variável permanecia no escopo da função.

#### Correção 3: Vírgula Faltando em Chamada de Função em `VS_UI_Title.cpp`

**Erro:**
```
Error de sintaxe na chamada de função
```

**Arquivo:** `Designed_Common\Project\NEW - VS_UI\src\VS_UI_Title.cpp` (linha 3868)

**Função:** `C_VS_UI_CHAR_MANAGER::Show()`

**Causa:**
Faltava vírgula entre dois argumentos na chamada `m_common_spk.BltLockedAlpha()`: `21+convy LEFT_ANIMATION_TITLE`.

**Correção Aplicada:**
Inserida vírgula: `21+convy, LEFT_ANIMATION_TITLE`.

#### Correção 4: Substituição de `push_back` por `insert(begin() + size())` em `VS_UI_Title.cpp`

**Arquivo:** `Designed_Common\Project\NEW - VS_UI\src\VS_UI_Title.cpp`

**Função:** `C_VS_UI_SERVER_SELECT::SetServerList()` (duas implementações: linhas 4808-4825 e 4846-4857)

**Mudança:**
Substituídos todos os 10 usos de `vector.push_back(element)` por `vector.insert(vector.begin() + vector.size(), element)` para manter padrão consistente do projeto.

**Razão:**
Padrão de codificação do projeto exige uso de `insert(begin() + index)` ao invés de `push_back`, mesmo quando funcionalmente equivalente, para consistência de estilo.

#### Correção 5: Sintaxe Inválida em Struct `S_SLOT` em `VS_UI_title.h`

**Erro:**
```
Erro de sintaxe: chamada de método diretamente na definição da struct
```

**Arquivo:** `Designed_Common\Project\NEW - VS_UI\src\header\VS_UI_title.h` (linha 135)

**Causa:**
A linha `Init();` estava presente diretamente na definição da struct `S_SLOT`, o que é sintaxe inválida. Deveria ser uma declaração de função (`void Init();`) ou uma chamada dentro de um construtor.

**Correção Aplicada:**
Alterado `Init();` para `void Init();` (declaração de método).

**Contexto:**
```cpp
struct S_SLOT
{
    S_SLOT() { m_AdvancementLevel = 0; }
    void Init();  // ✅ CORRIGIDO: declaração de método
    // ... resto da struct
};
```

#### Correção 6: Método `ExecuteObject()` Declarado mas Não Implementado

**Arquivo:** 
- `Designed_Common\Project\NEW - VS_UI\src\header\VS_UI_title.h` (linha 322)
- `Designed_Common\Project\NEW - VS_UI\src\header\VS_UI_Newtitle.h` (linha 327)

**Classe:** `C_VS_UI_LOGIN`

**Problema:**
O método `void ExecuteObject();` está declarado na seção pública de `C_VS_UI_LOGIN` em múltiplos headers, mas não há implementação correspondente em nenhum arquivo `.cpp`, nem há chamadas a esse método.

**Status:**
Identificado como código legado/morto. Recomendação: remover a declaração ou fornecer implementação vazia. Nenhuma ação foi tomada por enquanto, pois não causa erro de compilação (apenas potencial erro de linker se fosse chamado).

**Investigação:**
Verificação em backups antigos e código histórico confirmou que `ExecuteObject()` nunca foi implementado ou chamado, mesmo no código original.

#### Correção 7: Declarações Duplicadas de `int i` em `VS_UI_ExtraDialog.cpp`

**Arquivo:** `Designed_Common\Project\NEW - VS_UI\src\VS_UI_ExtraDialog.cpp`

**Problema:**
Declaração duplicada de `int i` em linhas próximas (ex: linha 3684 e linha 3688).

**Correção Aplicada:**
Removida declaração duplicada. A declaração `int i, j;` na linha 3688 foi separada em `int i;` e `int j;` para clareza, e a declaração anterior foi removida.

**Nota sobre `std::vector::insert`:**
Todas as chamadas `std::vector::insert` no arquivo já usavam `begin() + index` ou `begin() + size()` corretamente, então nenhuma correção foi necessária para uso de iteradores vs. ponteiros.

### Padrões de Codificação Aplicados

#### Uso de `std::vector::insert` vs `std::vector::push_back`

**Padrão do Projeto:**
- **Usar:** `vector.insert(vector.begin() + index, element)` ou `vector.insert(vector.begin() + vector.size(), element)`
- **Evitar:** `vector.push_back(element)`

**Razão:**
Padrão de codificação consistente do projeto, mesmo quando `push_back` seria funcionalmente equivalente ou mais eficiente.

#### Declaração de Variáveis em Loops `for`

**Padrão Moderno C++ (C++99+):**
- `for(int i = 0; ...)` declara `i` local apenas ao loop
- Variável não está acessível após o loop

**Padrão Antigo C++ (C89):**
- `for(int i = 0; ...)` declara `i` no escopo da função
- Variável permanece acessível após o loop

**Aproximação Segura:**
1. Declarar variável no escopo da função antes do loop: `int i;`
2. Usar no loop: `for(i = 0; ...)`
3. Variável acessível em todos os loops no mesmo escopo

**Exemplo Aplicado:**
```cpp
void C_VS_UI_SERVER_SELECT::CharBarCount()
{
    int i;  // ✅ Declarado no escopo da função
    for(i = 0; i < size; i++) { ... }  // ✅ Reutilizado nos loops
    for(i = 0; i < count; i++) { ... }
}
```

#### Métodos Modernos de Iteração e Algoritmos STL (C++11+)

**Contexto:**
Para código novo ou refatorações, existem alternativas modernas em C++11+ que substituem loops `for` manuais por algoritmos STL. Essas abordagens oferecem melhor legibilidade, funcionalidade e segurança.

**Exemplo de Código Antigo:**
```cpp
// FL2.cpp - g_GetByteLenth()
int g_GetByteLenth(const char_t * p_dbcs, int dbcs_len)
{
	if (p_dbcs == NULL || dbcs_len <= 0)
		return 0;
	
	int i = 0;
	int c = 0;
	for (; i < dbcs_len; i++)
	{
		if ((p_dbcs[i]&0xFF00) != 0)
			c += 2;
		else
			c++;
	}
	return c;
}
```

**Alternativas Modernas (C++11+):**

**1. `std::accumulate` com Lambda (Recomendado):**
```cpp
#include <numeric>
#include <algorithm>

int g_GetByteLenth(const char_t * p_dbcs, int dbcs_len)
{
	if (p_dbcs == NULL || dbcs_len <= 0)
		return 0;
	
	return std::accumulate(p_dbcs, p_dbcs + dbcs_len, 0,
		[](int sum, char_t c) {
			return sum + ((c & 0xFF00) != 0 ? 2 : 1);
		});
}
```

**Vantagens:**
- Funcional (sem variável mutável)
- Mais legível (expressa a intenção diretamente)
- Menos propenso a erros de escopo
- Padrão C++ moderno

**2. `std::for_each` com Lambda:**
```cpp
#include <algorithm>

int g_GetByteLenth(const char_t * p_dbcs, int dbcs_len)
{
	if (p_dbcs == NULL || dbcs_len <= 0)
		return 0;
	
	int c = 0;
	std::for_each(p_dbcs, p_dbcs + dbcs_len,
		[&c](char_t ch) {
			c += ((ch & 0xFF00) != 0) ? 2 : 1;
		});
	return c;
}
```

**Vantagens:**
- Mais expressivo que loop `for` manual
- Lambda captura variáveis explicitamente

**3. Range-Based For (C++11+):**
```cpp
int g_GetByteLenth(const char_t * p_dbcs, int dbcs_len)
{
	if (p_dbcs == NULL || dbcs_len <= 0)
		return 0;
	
	int c = 0;
	for (const char_t* it = p_dbcs; it < p_dbcs + dbcs_len; ++it) {
		c += ((*it & 0xFF00) != 0) ? 2 : 1;
	}
	return c;
}
```

**Vantagens:**
- Mais legível que loop tradicional com índice
- Evita problemas de escopo de variáveis

**Quando Usar:**
- **Código novo:** Prefira `std::accumulate` ou `std::for_each` com lambda
- **Código legado:** Mantenha o estilo existente para consistência
- **Refatorações:** Considere modernizar loops complexos para algoritmos STL

**Nota:**
O projeto atual mantém loops `for` tradicionais por questões de compatibilidade e consistência com código legado. As alternativas modernas são documentadas aqui como referência para desenvolvimento futuro.

#### Encoding e Preservação de Arquivos Fonte

**Regra Crítica:**
- Todos os arquivos fonte (.cpp, .h) **DEVEM** permanecer em CP949 (EUC-KR)
- **PROIBIDO** UTF-8 BOM em arquivos fonte
- Arquivos de projeto (.vcxproj, .filters) também em CP949 (sem BOM)

**Atenção:**
Durante correções automáticas, houve um incidente onde o encoding de `VS_UI_Title.cpp` foi quebrado. O arquivo foi restaurado do backup e as correções foram aplicadas manualmente para preservar o encoding CP949.

#### Correção 7: `strcmp` vs `wcscmp` e Cast de `char_t *` para `char *`

**Erro:**
```
Error C2065: 'i': undeclared identifier (múltiplas linhas)
Error E0167: argument of type "const char_t *" is incompatible with parameter of type "const char *"
```

**Arquivo:** `Designed_Common\Project\NEW - VS_UI\src\VS_UI_Title.cpp` (função `C_VS_UI_CHAR_DELETE::Run()`)

**Causa:**
O código usava `wcscmp()` (wide string compare) com `m_lev_ssn_part1.GetString()` que retorna `const char_t *` (onde `char_t` é `WORD` = `unsigned short`, 16 bits), não `wchar_t *`. Além disso, a macro `_L()` não estava definida.

**Correção Aplicada:**
Substituído `wcscmp()` por `strcmp()` com cast explícito:
- `wcscmp(m_lev_ssn_part1.GetString(), _L("delete"))` → `strcmp((const char*)m_lev_ssn_part1.GetString(), "delete")`
- `wcscmp(m_lev_ssn_part1.GetString(), _L("yes"))` → `strcmp((const char*)m_lev_ssn_part1.GetString(), "yes")`

**Explicação Técnica:**
- `char_t` é `typedef WORD char_t` (16 bits) usado para DBCS (Double-Byte Character Set)
- Para strings ASCII simples ("delete", "yes"), o byte baixo contém o valor correto
- Cast `(const char*)` converte `char_t *` → `char *` permitindo uso com `strcmp()`

**Padrão de Código:**
- `strcmp()` para comparação de strings narrow (`char *`)
- `wcscmp()` para comparação de strings wide (`wchar_t *`)
- Cast necessário quando `GetString()` retorna `char_t *` mas função espera `char *`

#### Métodos de Comparação de Strings em C++

**Resumo:**
O C++ oferece múltiplas formas de comparar strings. A escolha depende do tipo de string (C-style `char*`, `std::string`, `char_t*`, `wchar_t*`) e da operação desejada (igualdade, ordem lexicográfica, busca de substring).

##### 1. Funções C (C-Style Strings `char*` e `wchar_t*`)

**`strcmp(const char* s1, const char* s2)` - Narrow Strings:**
- **Retorna:** `int`
  - `< 0` se `s1 < s2` (lexicograficamente)
  - `== 0` se `s1 == s2`
  - `> 0` se `s1 > s2`
- **Uso:** Comparação de strings C (`char*`)
- **Exemplo:**
  ```cpp
  const char* str1 = "delete";
  const char* str2 = "yes";
  if (strcmp(str1, str2) == 0)  // Igualdade
      // strings são iguais
  if (strcmp(str1, str2) < 0)   // Menor que
      // str1 vem antes de str2
  ```

**`wcscmp(const wchar_t* s1, const wchar_t* s2)` - Wide Strings:**
- **Retorna:** `int` (mesmo formato que `strcmp`)
- **Uso:** Comparação de strings wide (`wchar_t*`) para Unicode/UTF-16
- **Exemplo:**
  ```cpp
  const wchar_t* wstr1 = L"delete";
  const wchar_t* wstr2 = L"yes";
  if (wcscmp(wstr1, wstr2) == 0)
      // strings são iguais
  ```

**Comparação com `char_t*` (DBCS - Double-Byte Character Set):**
- **Problema:** `char_t` é `typedef WORD` (16 bits), não `char` nem `wchar_t`
- **Solução:** Cast para `char*` quando valores são ASCII:
  ```cpp
  const char_t* str = GetString();  // Retorna char_t*
  if (strcmp((const char*)str, "delete") == 0)  // ✅ Cast necessário
      // Comparação funciona para ASCII
  ```
- **Limitação:** Cast só funciona para strings ASCII. Para DBCS completo, usar funções específicas como `g_Convert_DBCS_Ascii2SingleByte`.

##### 2. Operadores C++ (`std::string`)

**`operator==` e `operator!=` - Igualdade:**
- **Retorna:** `bool`
- **Uso:** Mais legível e moderno que `strcmp() == 0`
- **Exemplos:**
  ```cpp
  std::string str1 = "delete";
  std::string str2 = "yes";
  
  if (str1 == str2)        // ✅ Igualdade (mais legível)
      // strings são iguais
  
  if (str1 != "delete")    // ✅ Desigualdade
      // strings são diferentes
  
  if (str1 == "delete")    // ✅ Comparação com literal C-string
      // OK: std::string::operator== aceita const char*
  ```

**`operator<`, `operator>`, `operator<=`, `operator>=` - Ordem Lexicográfica:**
- **Retorna:** `bool`
- **Uso:** Comparação de ordem (útil para ordenação, `std::map`, `std::set`)
- **Exemplos:**
  ```cpp
  std::string str1 = "apple";
  std::string str2 = "banana";
  
  if (str1 < str2)         // ✅ true (apple vem antes de banana)
      // str1 é lexicograficamente menor
  
  // Útil para ordenação:
  std::vector<std::string> vec = {"banana", "apple", "cherry"};
  std::sort(vec.begin(), vec.end());  // Ordena lexicograficamente
  ```

##### 3. Métodos de `std::string`

**`compare(const string& str)` - Comparação com Retorno Detalhado:**
- **Retorna:** `int` (similar a `strcmp`)
  - `< 0` se `this < str`
  - `== 0` se `this == str`
  - `> 0` se `this > str`
- **Uso:** Quando precisa do valor de comparação (não apenas igualdade)
- **Exemplos:**
  ```cpp
  std::string str1 = "delete";
  std::string str2 = "yes";
  
  int result = str1.compare(str2);
  if (result == 0)
      // strings são iguais
  else if (result < 0)
      // str1 vem antes de str2
  else
      // str1 vem depois de str2
  
  // Comparação com substring:
  std::string str = "hello world";
  if (str.compare(0, 5, "hello") == 0)  // Compara 5 caracteres a partir do índice 0
      // prefixo "hello" encontrado
  ```

**`find(const string& str)` - Busca de Substring:**
- **Retorna:** `size_type` (índice) ou `npos` (não encontrado)
- **Uso:** Verificar se uma string contém outra substring
- **Exemplos:**
  ```cpp
  std::string str = "delete item";
  
  if (str.find("delete") != std::string::npos)  // ✅ Substring encontrada
      // "delete" está em str
  
  if (str.find("yes") == std::string::npos)     // ✅ Substring não encontrada
      // "yes" não está em str
  
  // Padrão antigo (C-style):
  if (str.find("delete") != -1)  // ❌ Evitar: -1 é dependente de implementação
      // Use npos ao invés de -1
  ```

**`find_first_of()`, `find_last_of()`, etc. - Busca de Caracteres:**
- **Uso:** Busca de caracteres individuais ou conjunto de caracteres
- **Exemplo:**
  ```cpp
  std::string str = "hello world";
  size_t pos = str.find_first_of("aeiou");  // Encontra primeira vogal (e na posição 1)
  ```

##### 4. Comparação com Literais e C-Strings

**`std::string` vs Literal C-String (`const char*`):**
- **Funciona automaticamente:** `std::string::operator==` aceita `const char*`
- **Exemplo:**
  ```cpp
  std::string str = "delete";
  if (str == "delete")           // ✅ OK: conversão implícita
      // Igualdade verifica corretamente
  
  if (str == std::string("delete"))  // ✅ OK: mais explícito
      // Mesmo resultado
  ```

**Comparação C-String vs C-String (sem `std::string`):**
- **Requer `strcmp()`:** C-strings não podem usar `==` para comparação de conteúdo
- **Exemplo:**
  ```cpp
  const char* str1 = "delete";
  const char* str2 = "delete";
  
  if (str1 == str2)              // ❌ ERRADO: Compara ponteiros, não conteúdo!
      // Pode ser false mesmo que strings sejam iguais
  
  if (strcmp(str1, str2) == 0)   // ✅ CORRETO: Compara conteúdo
      // Strings são iguais
  ```

##### 5. Recomendações por Situação

**Igualdade de `std::string`:**
```cpp
// ✅ RECOMENDADO: Moderno e legível
if (str1 == str2) { ... }
if (str == "literal") { ... }

// ❌ EVITAR: Verboso e desnecessário
if (strcmp(str1.c_str(), str2.c_str()) == 0) { ... }
if (str1.compare(str2) == 0) { ... }  // OK, mas menos legível que ==
```

**Ordem Lexicográfica de `std::string`:**
```cpp
// ✅ RECOMENDADO: Operadores de comparação
if (str1 < str2) { ... }
std::sort(vec.begin(), vec.end());  // Usa operator< automaticamente

// ⚠️ ACEITÁVEL: Se precisar do valor de comparação
int cmp = str1.compare(str2);
if (cmp < 0) { ... }
```

**C-Strings (`char*`) - Quando não usar `std::string`:**
```cpp
// ✅ OBRIGATÓRIO: Função C
if (strcmp(cstr1, cstr2) == 0) { ... }

// ❌ ERRADO: Compara ponteiros, não conteúdo
if (cstr1 == cstr2) { ... }
```

**Busca de Substring:**
```cpp
// ✅ RECOMENDADO: std::string::find
if (str.find("substring") != std::string::npos) { ... }

// ❌ EVITAR: C-style manual
// char* p = strstr(cstr, "substring");
// if (p != NULL) { ... }
```

**Comparação Case-Insensitive:**
```cpp
// ⚠️ ATENÇÃO: std::string::operator== é case-sensitive
std::string str1 = "Delete";
std::string str2 = "delete";
if (str1 == str2)  // false: case-sensitive

// Para case-insensitive, usar:
// - std::transform + std::tolower (convert ambos para lowercase)
// - Funções específicas do projeto (se existirem)
// - Biblioteca de terceiros (Boost, etc.)
```

##### 6. Exemplos de Uso no Projeto

**Código Antigo (Corrigido):**
```cpp
// VS_UI_Title.cpp - Antes
if (wcscmp(m_lev_ssn_part1.GetString(), _L("delete")) == 0)  // ❌ Tipo incompatível

// VS_UI_Title.cpp - Depois
if (strcmp((const char*)m_lev_ssn_part1.GetString(), "delete") == 0)  // ✅ Cast explícito
    SendCharacterDeleteToClient();
```

**Código com `std::string` (Moderno):**
```cpp
// Exemplo hipotético: uso preferido para std::string
std::string command = GetUserInput();
if (command == "delete")           // ✅ Mais legível que strcmp
    DeleteCharacter();
else if (command == "create")
    CreateCharacter();
```

**Uso em Containers (`std::map`, `std::set`):**
```cpp
// std::string pode ser usado diretamente como chave (usa operator<)
std::map<std::string, int> scoreMap;
scoreMap["player1"] = 100;
scoreMap["player2"] = 200;

// Busca:
auto it = scoreMap.find("player1");  // ✅ Usa operator< internamente
if (it != scoreMap.end())
    int score = it->second;
```

#### Correção 8: `MODE1024_X` e `MODE1024_Y` Indefinidos em `C_VS_UI_SERVER_SELECT::GroupView()`

**Erro:**
```
Error C2065: 'MODE1024_X': undeclared identifier
Error C2065: 'MODE1024_Y': undeclared identifier
```

**Arquivo:** `Designed_Common\Project\NEW - VS_UI\src\VS_UI_Title.cpp` (função `C_VS_UI_SERVER_SELECT::GroupView()`)

**Causa:**
As constantes `MODE1024_X` e `MODE1024_Y` não estavam definidas no código antigo (`VS_UI_Title.cpp`). No código novo (`VS_UI_NewTitle.cpp` com `VS_UI_Newtitle.h`), elas estão definidas como enum na classe (linhas 1744-1745), mas no código antigo usado pelo projeto `lib`, não existiam.

**Correção Aplicada:**
Calculadas dinamicamente dentro de `GroupView()` como variáveis locais, seguindo o padrão já usado no construtor com `convx`/`convy`:

```cpp
void C_VS_UI_SERVER_SELECT::GroupView()
{
	bool bHighResolution = g_pUserInformation->iResolution_x > 800;
	int MODE1024_X = bHighResolution ? (g_pUserInformation->iResolution_x - 800) / 2 : 0;
	int MODE1024_Y = bHighResolution ? (g_pUserInformation->iResolution_y - 600) / 2 : 0;
	// ... resto do código
}
```

**Explicação Técnica:**
- `MODE1024_X/Y` são offsets para ajustar posições de elementos internos (sprites) em resoluções maiores que 800x600
- `(res_x - 800) / 2` calcula o offset para centralizar baseado em 800x600
- Solução dinâmica permite suportar qualquer resolução (1024x768, 1280x720, 1920x1080, etc.)

**Padrão do Projeto:**
O projeto usa cálculos dinâmicos de offsets baseados em `g_pUserInformation->iResolution_x/y` para suportar múltiplas resoluções sem valores hardcoded. Outros exemplos no código:
- `convx = (g_pUserInformation->iResolution_x - 800) / 2` (linha 4344)
- `convy = (g_pUserInformation->iResolution_y - 600) / 2` (linha 4345)
- `m_server_x = 350+convx` (linha 4348)
- `m_server_y = 191+convy` (linha 4349)

#### Correção 9: Uso Correto de `erase` em Containers STL (`std::vector`, `std::string`, `std::list`, `std::set`, `std::map`)

**Problema:**
Código antigo usava ponteiros (`&container[index]` ou `&container.front()`) com `erase()`, mas containers STL modernos exigem iteradores.

**Erro Comum:**
```cpp
// ❌ ERRADO - Não compila em C++ moderno
m_desc.erase(&m_desc[0]);
m_desc.erase(&m_desc.front());
m_string.erase(&m_string[m_cursor]);
```

**Correção Aplicada:**
```cpp
// ✅ CORRETO - Usa iteradores
m_desc.erase(m_desc.begin());                    // Primeiro elemento
m_desc.erase(m_desc.begin() + i);                // Elemento na posição i
m_desc.erase(m_desc.end() - 1);                  // Último elemento
m_string.erase(m_string.begin() + cursor);       // String na posição cursor
```

**Explicação Técnica:**

1. **`std::vector<T>` e `std::deque<T>`:**
   - `erase()` aceita iterador: `erase(iterator)` ou `erase(iterator_first, iterator_last)`
   - **Primeiro elemento:** `erase(begin())`
   - **Último elemento:** `erase(end() - 1)`
   - **Elemento na posição `i`:** `erase(begin() + i)`
   - **Intervalo [i, j):** `erase(begin() + i, begin() + j)`

2. **`std::string` (alias de `std::basic_string<char>`):**
   - **Igual a `std::vector<char>`:**
   - `erase(begin())` - primeiro caractere
   - `erase(begin() + i)` - caractere na posição `i`
   - `erase(end() - 1)` - último caractere
   - `erase(begin() + i, begin() + j)` - intervalo de caracteres

3. **`std::list<T>`:**
   - **Apenas iteradores** (não suporta acesso por índice `[i]`):
   - `erase(iterator)` - remove elemento no iterador
   - `erase(iterator_first, iterator_last)` - remove intervalo
   - **Exemplo:** `m_list.erase(iData);` onde `iData` é `std::list<T>::iterator`

4. **`std::set<T>` e `std::multiset<T>`:**
   - **Apenas iteradores** (não suporta acesso por índice):
   - `erase(iterator)` - remove elemento no iterador
   - `erase(key)` - remove elemento por valor (retorna `size_type` count)
   - **Exemplo:** 
     ```cpp
     std::set<int> frameSet;
     std::set<int>::iterator it = frameSet.find(value);
     if (it != frameSet.end())
         frameSet.erase(it);  // ✅ Usa iterador
     // OU:
     frameSet.erase(value);   // ✅ Remove por valor (retorna 1 ou 0)
     ```

5. **`std::map<K, V>` e `std::multimap<K, V>`:**
   - **Apenas iteradores ou keys:**
   - `erase(iterator)` - remove elemento no iterador
   - `erase(key)` - remove elemento por chave (retorna `size_type` count)
   - **Exemplo:**
     ```cpp
     std::map<int, Object*> m_mapImageObject;
     IMAGEOBJECT_OUTPUT_MAP::iterator iDelete = m_mapImageObject.find(id);
     if (iDelete != m_mapImageObject.end())
         m_mapImageObject.erase(iDelete);  // ✅ Usa iterador
     // OU:
     m_mapImageObject.erase(id);  // ✅ Remove por chave
     ```

**Exemplos de Código no Projeto:**

**Antes (Incorreto):**
```cpp
// VS_UI_GameCommon.cpp
m_history.erase(&m_history[0]);                    // ❌ Ponteiro
m_history.erase(&m_history[m_history_line]);       // ❌ Ponteiro
temp_history.m_timer.erase(&temp_history.m_timer[0]); // ❌ Ponteiro

// MHelpMessageManager.h
m_SenderVector.erase(&m_SenderVector[senderIndex]);  // ❌ Ponteiro
m_MessageVector.erase(&m_MessageVector[messageIndex]); // ❌ Ponteiro

// U_edit.cpp
m_string.erase(&m_string[m_cursor]);               // ❌ Ponteiro
```

**Depois (Correto):**
```cpp
// std::vector
m_history.erase(m_history.begin());                // ✅ Iterador
m_history.erase(m_history.begin() + m_history_line); // ✅ Iterador
temp_history.m_timer.erase(temp_history.m_timer.begin()); // ✅ Iterador

// std::vector com índice
m_SenderVector.erase(m_SenderVector.begin() + senderIndex);   // ✅ Iterador
m_MessageVector.erase(m_MessageVector.begin() + messageIndex); // ✅ Iterador

// std::string
m_string.erase(m_string.begin() + m_cursor);       // ✅ Iterador
```

**Casos Corretos no Projeto (Já Implementados):**

- **`CSetManager.h` (linha 174):** Usa `m_List.erase(iData);` corretamente com iterador de `std::list`
- **`MTopView.cpp` (linhas 13890, 14176):** Usa `m_mapImageObject.erase(iDelete);` corretamente com iterador de `std::map`
- **`VS_UI_DESC.cpp` (linhas 262, 488, 495, 546, 750, 757):** Usa `m_rep_string.erase(m_rep_string.begin() + i);` e `m_desc.erase(m_desc.begin());` corretamente

**Padrão do Projeto:**
- **Sempre usar iteradores** com `erase()` em containers STL
- **Nunca usar ponteiros** (`&container[index]`, `&container.front()`, etc.)
- Para acesso por índice, converter para iterador: `container.begin() + index`
- Para último elemento: `container.end() - 1`

### Seleção de UI e Configuração de Design

O projeto suporta múltiplas versões de UI/configuração para diferentes regiões e idiomas. A seleção é feita em **tempo de compilação** (não runtime) por segurança.

#### Como Mudar de UI

**Método: Definir Macro de Design no Visual Studio**

1. Abrir **Project Properties** do `Client`:
   - Botão direito no projeto → `Properties`

2. Navegar até **C/C++ → Preprocessor**:
   - `Configuration Properties` → `C/C++` → `Preprocessor`

3. Editar **Preprocessor Definitions**:
   - Adicionar uma das macros: `__DESIGNED_KOREA`, `__DESIGNED_CHS`, `__DESIGNED_INTERNATION`, `__DESIGNED_CHINA`, `__DESIGNED_JAPAN`, ou `__DESIGNED_ITEMMANIA`
   - Remover outras macros `__DESIGNED_*` se existirem

4. Recompilar o projeto

**Exemplo (via .vcxproj):**
```xml
<ClCompile>
  <PreprocessorDefinitions>
    WIN32;
    _DEBUG;
    _CONSOLE;
    __DESIGNED_KOREA;  <!-- Definir apenas UMA macro de design -->
    %(PreprocessorDefinitions)
  </PreprocessorDefinitions>
</ClCompile>
```

**Método Alternativo: Editar `ContentsFilter.h`**

Não recomendado. O arquivo `ContentsFilter.h` já contém configurações para todos os designs. A seleção é feita via `#ifdef __DESIGNED_*`:

```cpp
#ifdef __DESIGNED_KOREA
  // Configurações Korea
#elif defined(__DESIGNED_CHS)
  // Configurações CHS
#elif defined(__DESIGNED_INTERNATION)
  // Configurações International
// ... etc
#endif
```

#### UIs Disponíveis

O projeto possui 6 designs/configurações disponíveis:

1. **`__DESIGNED_KOREA`** - "Designed Korea"
   - **Idioma:** Coreano
   - **UI:** `__INTERNATIONAL_UI = __OFF`, `__CHINESE_UI = __OFF`, `__JAPAN_UI = __OFF`
   - **Características:** Configuração padrão/completa com todos os sistemas habilitados
   - **Principais Flags:**
     - `__SERVER_SELECT_REVEWAL = __ON`
     - `__HERO_SYSTEM = __ON`
     - `__CHAR_DELETE = __OFF`

2. **`__DESIGNED_CHS`** - "Designed CHS"
   - **Idioma:** Chinês Simplificado
   - **UI:** Similar a Korea, mas com configurações específicas para CHS
   - **Principais Flags:**
     - `__SERVER_SELECT_REVEWAL = __ON`
     - `__CHINESE_UI = __OFF` (mas pode ter ajustes específicos)
     - `__HERO_SYSTEM = __ON`

3. **`__DESIGNED_INTERNATION`** - "Designed Internation"
   - **Idioma:** Inglês/Internacional
   - **UI:** `__INTERNATIONAL_UI = __ON`, `__ENGLISH_STRFILTER = __ON`
   - **Características:** Versão internacional com menos eventos regionais
   - **Principais Flags:**
     - `__SERVER_SELECT_REVEWAL = __OFF` (usa UI antiga de seleção de servidor)
     - `__CHAR_DELETE = __ON`
     - `__INTERNATIONAL_PREMIUM_SYSTEM = __ON`
     - `__ID_PASSWORD = __ON`

4. **`__DESIGNED_CHINA`** - "Designed China"
   - **Idioma:** Chinês
   - **UI:** `__CHINESE_UI = __ON` (fontes maiores e ajustes de posição para chinês)
   - **Características:** Configuração específica para mercado chinês
   - **Principais Flags:**
     - `__SERVER_SELECT_REVEWAL = __ON`
     - `__CHINESE_UI = __ON`
     - `__CHAR_DELETE = __ON`

5. **`__DESIGNED_JAPAN`** - "Designed Japan"
   - **Idioma:** Japonês
   - **UI:** `__JAPAN_UI = __ON` (ajustes de posição/estilo para japonês)
   - **Características:** Configuração específica para mercado japonês
   - **Principais Flags:**
     - `__SERVER_SELECT_REVEWAL = __ON`
     - `__JAPAN_UI = __ON`
     - `__LOCALIZING_LONGNAME = __ON` (nomes longos de monstros)
     - `__CHAR_DELETE = __ON`

6. **`__DESIGNED_ITEMMANIA`** - "Designed IMI"
   - **Idioma:** Varia
   - **Características:** Configuração específica para ItemMania/IMI
   - **Principais Flags:**
     - `__SERVER_SELECT_REVEWAL = __ON`
     - `__IMI_INTERFACE = __ON`
     - `__IMI_LOW_LEVEL_ITEM = __OFF`

#### O Que Muda Entre UIs

**1. Idioma e Localização:**
- Textos em diferentes idiomas (coreano, chinês, japonês, inglês)
- `__ENGLISH_STRFILTER = __ON` ativa filtros de strings em inglês

**2. Posição e Tamanho de Elementos:**
- `__CHINESE_UI = __ON` → Ajusta fontes e posições para chinês (fontes maiores)
- `__JAPAN_UI = __ON` → Ajusta posições/estilo para japonês
- `__INTERNATIONAL_UI = __ON` → Layout internacional

**3. Funcionalidades Habilitadas/Desabilitadas:**
- `__CHAR_DELETE` → Deletar personagens (OFF em Korea, ON em International)
- `__SERVER_SELECT_REVEWAL` → Nova UI de seleção de servidor (ON na maioria, OFF em International)
- `__HERO_SYSTEM` → Sistema de heróis
- `__INTERNATIONAL_PREMIUM_SYSTEM` → Sistema premium internacional

**4. Eventos e Itens Regionais:**
- `__2008_NEW_YEAR_EVENT`, `__HALLOWEEN`, `__CHRISTMAS_SOCKS_EVENT`, etc.
- Diferentes eventos habilitados por região

**5. Sistemas de Segurança:**
- `__NPROTECT` → NProtect anti-cheat (varia por região)
- `__XTRAP` → XTrap anti-cheat

#### Processo de Compilação para Múltiplas UIs

**Exemplo: Compilar versões para Korea e CHS:**

1. **Configuração Korea:**
   - Adicionar `__DESIGNED_KOREA` em `Preprocessor Definitions`
   - Compilar → Gerar `Client_Korea.exe`

2. **Configuração CHS:**
   - Remover `__DESIGNED_KOREA`
   - Adicionar `__DESIGNED_CHS` em `Preprocessor Definitions`
   - Compilar → Gerar `Client_CHS.exe`

**Nota sobre Múltiplas Configurações no Visual Studio:**
É possível criar múltiplas configurações (Debug, Release, ReleaseLog) com diferentes `__DESIGNED_*` definidos, ou usar scripts de build que alternam a macro e recompilam.

#### Limitações

- **Compile-time only:** Não é possível mudar UI em runtime
- **Recompilação obrigatória:** Cada mudança requer recompilação completa
- **Motivo:** Segurança - flags em compile-time previnem alterações via hacking

**Arquivo de Configuração:**
`Designed_Common\Project\Client\ContentsFilter.h`

Este arquivo contém todas as configurações de feature flags para cada design, organizadas por blocos `#ifdef __DESIGNED_*`.

### Clean vs Build: Quando Limpar o Projeto

**Regra Geral:**
Na maioria dos casos, apenas **Build** é suficiente. O Visual Studio detecta automaticamente quais arquivos precisam ser recompilados. **Clean + Build** é necessário apenas em situações específicas.

#### Quando Fazer Apenas Build

**Alterações em código fonte:**
- Mudanças em arquivos `.cpp` ou `.h`
- Correções de código
- Adição/remoção de funções ou classes
- O Visual Studio recompila automaticamente apenas os arquivos afetados

**Alterações em configurações simples:**
- Mudanças em `#define` locais
- Alterações em código que não afetam dependências globais

**Vantagem:**
- Mais rápido (recompila apenas o necessário)
- Preserva objetos (`.obj`) não afetados

#### Quando Fazer Clean + Build

**1. Alterações em Arquivos de Projeto (`.vcxproj`, `.vcxproj.filters`):**
- Mudanças em `AdditionalIncludeDirectories`
- Mudanças em `PreprocessorDefinitions`
- Mudanças em configurações de compilação (`/std:c++`, flags, etc.)
- Adição/remoção de arquivos do projeto
- Mudanças em `AdditionalLibraryDirectories`

**Por quê:**
O Visual Studio pode não detectar corretamente que todos os arquivos precisam ser recompilados quando configurações globais mudam.

**2. Alterações em Arquivos de Pré-compilação (PCH):**
- Mudanças em `Client_PCH.h` ou headers incluídos no PCH
- Alterações em `PrecompiledHeaderFile` no `.vcxproj`
- Mudanças em headers globais incluídos no PCH

**Por quê:**
O PCH é usado por todos os arquivos. Se mudar, todos precisam ser recompilados.

**3. Alterações em Headers Globais:**
- Mudanças em `ContentsFilter.h` (afeta todo o projeto)
- Mudanças em headers incluídos em muitos arquivos
- Mudanças em macros globais que alteram estrutura de código

**Por quê:**
Múltiplos arquivos dependem desses headers. O sistema de dependências pode não detectar todas as dependências.

**4. Problemas de Cache/Linkagem:**
- Erros estranhos de linker que não fazem sentido
- Arquivos `.obj` corrompidos ou desatualizados
- Dependências quebradas entre projetos
- Erros de "symbol not found" após mudanças em headers

**Por quê:**
O cache de build pode estar desatualizado ou corrompido.

**5. Após Executar Scripts de Migração:**
- Após executar `scripts\add_common_sdk.ps1`
- Após modificar `.vcxproj` manualmente
- Após mudanças em estrutura de diretórios

**Por quê:**
Scripts podem alterar configurações que não são detectadas automaticamente.

#### Workaround Rápido (Sem Clean Completo)

Se não quiser fazer Clean completo do projeto:

1. **Delete manualmente a pasta de output:**
   - Delete a pasta `Debug` ou `Release` dentro do diretório do projeto
   - Exemplo: `Designed_Chs\Project\Client\Debug\` ou `Release\`
   - Faça Build normalmente

2. **Rebuild do projeto específico:**
   - Botão direito no projeto → `Rebuild`
   - Isso limpa e reconstrói apenas aquele projeto

#### Regras Práticas para Migração VS2022

**Durante a migração, faça Clean + Build após:**
- ✅ Modificar `Client.vcxproj` (adicionar includes, paths, etc.)
- ✅ Executar scripts que modificam `.vcxproj`
- ✅ Alterar `ContentsFilter.h` ou headers globais
- ✅ Mudar configurações de pré-compilação
- ✅ Encontrar erros estranhos de linker/compilação

**Durante desenvolvimento normal, apenas Build:**
- ✅ Alterações em código fonte (`.cpp`, `.h`)
- ✅ Correções de bugs
- ✅ Adição de novas funções/classes

#### Exemplo de Fluxo de Trabalho

**Cenário 1: Adicionar novo diretório de include**
```
1. Modificar Client.vcxproj (adicionar AdditionalIncludeDirectories)
2. Clean + Build  ← NECESSÁRIO
3. Verificar se compila
```

**Cenário 2: Corrigir bug em função**
```
1. Editar arquivo .cpp
2. Build  ← SUFICIENTE
3. Testar
```

**Cenário 3: Mudar macro global em ContentsFilter.h**
```
1. Editar ContentsFilter.h
2. Clean + Build  ← NECESSÁRIO (afeta PCH)
3. Verificar se compila
```

**Cenário 4: Erro estranho de linker**
```
1. Tentar Build normal
2. Se erro persistir: Clean + Build  ← TENTAR
3. Se ainda falhar: verificar dependências entre projetos
```

#### Resumo

| Tipo de Mudança | Ação Necessária |
|----------------|-----------------|
| Código fonte (`.cpp`, `.h`) | **Build** apenas |
| Configurações de projeto (`.vcxproj`) | **Clean + Build** |
| Headers de pré-compilação (PCH) | **Clean + Build** |
| Headers globais (`ContentsFilter.h`) | **Clean + Build** |
| Scripts de migração | **Clean + Build** |
| Erros estranhos de linker | **Clean + Build** |

**Dica:**
Quando em dúvida, especialmente durante migração, prefira **Clean + Build** para garantir que tudo está atualizado. É mais lento, mas evita problemas de cache desatualizado.

---

## CORREÇÃO CRÍTICA: Inconsistência entre `__HERO_SYSTEM` e `__CONTRIBUTE_SYSTEM`

### Problema Identificado

**Data:** Durante migração para VS2022  
**Severidade:** CRÍTICA  
**Arquivos Afetados:**
- `Designed_Common\Project\NEW - VS_UI\src\vs_ui_gamecommon2.cpp` (linha 120)
- `Designed_Common\Project\NEW - VS_UI\src\VS_UI_GameCommon.cpp` (linha 3749-3757)
- `Designed_Common\Project\NEW - VS_UI\src\header\VS_UI_GameCommon2.h` (linha 34-41)

### Descrição do Bug

Foi identificada uma **inconsistência crítica** entre as macros `__HERO_SYSTEM` e `__CONTRIBUTE_SYSTEM`:

1. **Declaração da função** (`VS_UI_GameCommon2.h` linha 34-41):
   ```cpp
   #if __CONTENTS(__CONTRIBUTE_SYSTEM)
   #define CONTRIBUTE_MAX					100000
   #define CONTRIBUTE_GRADE_MAX			8
   int countContributeGrade(int contributePoint);
   #endif //__CONTRIBUTE_SYSTEM
   ```

2. **Implementação da função** (`vs_ui_gamecommon2.cpp` linha 120):
   ```cpp
   #if __CONTENTS(__HERO_SYSTEM)  // ← BUG: Deveria ser __CONTRIBUTE_SYSTEM
   int countContributeGrade(int contributePoint)
   {
       // ... implementação ...
   }
   #endif //__HERO_SYSTEM
   ```

3. **Uso da função** (`VS_UI_GameCommon.cpp` linha 3750):
   ```cpp
   // ← BUG: Não está protegido por #if __CONTENTS(__CONTRIBUTE_SYSTEM)
   int contributeGrade = countContributeGrade(g_char_slot_ingame.ContributePoint);
   ```

### Por Que É Crítico

1. **Erro de Compilação:**
   - Se `__CONTRIBUTE_SYSTEM = __ON` mas `__HERO_SYSTEM = __OFF` (ex: Internation), a função `countContributeGrade()` não será compilada, mas o código tenta usá-la.
   - Erro: `'countContributeGrade': identifier not found`

2. **Erro de Membro:**
   - Se `__CONTRIBUTE_SYSTEM = __OFF`, o membro `ContributePoint` não existe em `S_SLOT`, mas o código tenta acessá-lo.
   - Erro: `'ContributePoint': is not a member of 'S_SLOT'`

3. **Inconsistência de Lógica:**
   - A função `countContributeGrade()` calcula **graus de contribuição**, não graus de herói.
   - Deveria usar `__CONTRIBUTE_SYSTEM`, não `__HERO_SYSTEM`.

### Correções Aplicadas

#### Correção 1: Implementação da Função

**Arquivo:** `Designed_Common\Project\NEW - VS_UI\src\vs_ui_gamecommon2.cpp`  
**Linha:** 120

**Antes:**
```cpp
#if __CONTENTS(__HERO_SYSTEM)
int countContributeGrade(int contributePoint)
```

**Depois:**
```cpp
#if __CONTENTS(__CONTRIBUTE_SYSTEM)
int countContributeGrade(int contributePoint)
```

**Também atualizar o `#endif` correspondente (linha 151):**
```cpp
#endif //__CONTRIBUTE_SYSTEM
```

#### Correção 2: Proteção do Uso

**Arquivo:** `Designed_Common\Project\NEW - VS_UI\src\VS_UI_GameCommon.cpp`  
**Linhas:** 3749-3757

**Antes:**
```cpp
int contributeGrade = countContributeGrade(g_char_slot_ingame.ContributePoint);
char sz_temp[512];
if (contributeGrade >= 0 || contributeGrade < 8)
{
    wsprintf(sz_temp, "µãÊý:%d %s:%d", g_char_slot_ingame.ContributePoint, (*g_pGameStringTable)[UI_STRING_CONTRIBUTE_GRADE].GetString(),contributeGrade);
    int realAttrWith20 = attrWith-g_GetStringWidth(sz_temp,gpC_base->m_gearinfo_pi.hfont)-6;
    g_PrintColorStr(x+realAttrWith20,y+30+20+23+13+celHight+gap,sz_temp,gpC_base->m_gearinfo_pi,RGB_WHITE);
}
```

**Depois:**
```cpp
#if __CONTENTS(__CONTRIBUTE_SYSTEM)
	int contributeGrade = countContributeGrade(g_char_slot_ingame.ContributePoint);
	char sz_temp[512];
	if (contributeGrade >= 0 || contributeGrade < 8)
	{
		wsprintf(sz_temp, "µãÊý:%d %s:%d", g_char_slot_ingame.ContributePoint, (*g_pGameStringTable)[UI_STRING_CONTRIBUTE_GRADE].GetString(),contributeGrade);
		int realAttrWith20 = attrWith-g_GetStringWidth(sz_temp,gpC_base->m_gearinfo_pi.hfont)-6;
		g_PrintColorStr(x+realAttrWith20,y+30+20+23+13+celHight+gap,sz_temp,gpC_base->m_gearinfo_pi,RGB_WHITE);
	}
#endif //__CONTRIBUTE_SYSTEM
```

### Diferença Entre os Sistemas

- **`__HERO_SYSTEM`**: Sistema de status/efeitos visuais de "herói" (eventos, Level War)
  - Status: `EFFECTSTATUS_SLAYER_HERO`, `EFFECTSTATUS_VAMPIRE_HERO`, etc.
  - Efeitos visuais: `EFFECTSPRITETYPE_SLAYER_HERO`, etc.
  - Skills: `SKILL_CLIENT_SLAYER_HERO`

- **`__CONTRIBUTE_SYSTEM`**: Sistema de pontos de contribuição e graus (ranking/prestígio)
  - Pontos: `ContributePoint` em `S_SLOT`
  - Função: `countContributeGrade()` calcula graus baseados em pontos
  - UI: Exibe graus de contribuição por raça

**São sistemas independentes**, mas relacionados. A função `countContributeGrade()` pertence ao sistema de contribuição, não ao de herói.

### Configurações por País

| País | `__HERO_SYSTEM` | `__CONTRIBUTE_SYSTEM` | `__HERO_SYSTEM_ITEM` | `__CONTRIBUTE_SYSTEM_ITEM` |
|------|------------------|----------------------|----------------------|---------------------------|
| **Korea** | `__ON` | `__ON` | `__ON` | `__ON` |
| **CHS (Chinese)** | `__ON` | `__ON` | `__ON` | `__ON` |
| **Internation** | `__OFF` | `__ON` | `__ON` | `__OFF` |
| **China** | `__ON` | `__ON` | `__OFF` | `__OFF` |
| **Japan** | `__ON` | `__ON` | `__ON` | `__ON` |
| **ItemMania** | `__ON` | `__ON` | `__ON` | `__ON` |

**Nota:** A inconsistência causaria erro de compilação especialmente em configurações onde `__HERO_SYSTEM = __OFF` mas `__CONTRIBUTE_SYSTEM = __ON` (ex: Internation).

### Impacto

- **Antes da correção:** Erro de compilação quando `__HERO_SYSTEM ≠ __CONTRIBUTE_SYSTEM`
- **Depois da correção:** Código compila corretamente independente da configuração das macros
- **Compatibilidade:** Mantém compatibilidade com todas as configurações regionais

### Validação

Após a correção, validar que:
1. ✅ A função `countContributeGrade()` compila quando `__CONTRIBUTE_SYSTEM = __ON`
2. ✅ O uso da função está protegido por `#if __CONTENTS(__CONTRIBUTE_SYSTEM)`
3. ✅ Não há erros de compilação em nenhuma configuração regional
4. ✅ O código funciona corretamente quando `__CONTRIBUTE_SYSTEM = __OFF` (código não compilado)

### Referências Relacionadas

- `Designed_Common\Project\Client\ContentsFilter.h` - Definições das macros por país
- `Designed_Common\Project\NEW - VS_UI\src\header\VS_UI_title.h` - Definição de `S_SLOT` com `ContributePoint`
- `Designed_Common\Project\Client\ModifyStatusManager.cpp` - Handler `Function_MODIFY_CONTRIBUTE_POINT()`

---

## Sistema de Macros e Filtragem de Conteúdo

### Visão Geral

O projeto usa um sistema extensivo de macros de pré-processador para controlar quais funcionalidades estão habilitadas em diferentes versões regionais do jogo. Este sistema foi implementado para:

1. **Segurança:** Filtrar conteúdo em tempo de compilação reduz risco de hack (conforme comentário em `ContentsFilter.h`)
2. **Versões Regionais:** Diferentes países/regiões têm funcionalidades diferentes
3. **Licenciamento:** Controlar o que cada versão pode fazer
4. **Manutenção:** Um único código base para múltiplas versões

### Arquivo Principal

**Localização:** `Designed_Common\Project\Client\ContentsFilter.h`

**Comentário Crítico (linhas 4-6):**
```cpp
// define을 사용하여 컨텐츠를 필터링한다.
// 실행 시간에 필터링하는 것은 해킹의 위험이 있기 때문에
// 컴파일 시간에 필터링되도록 한다.
```

**Tradução:**
- "Usa `#define` para filtrar conteúdo"
- "Filtrar em tempo de execução tem risco de hack"
- "Por isso, filtra em tempo de compilação"

### Principais Sistemas Controlados por Macros

#### 1. `__HERO_SYSTEM` vs `__CONTRIBUTE_SYSTEM`

**`__HERO_SYSTEM`:**
- **Função:** Sistema de status/efeitos visuais de "herói"
- **Componentes:**
  - Status: `EFFECTSTATUS_SLAYER_HERO`, `EFFECTSTATUS_VAMPIRE_HERO`, `EFFECTSTATUS_OUSTERS_HERO`
  - Efeitos visuais: `EFFECTSPRITETYPE_SLAYER_HERO`, etc.
  - Skills: `SKILL_CLIENT_SLAYER_HERO`
  - Level War: `EFFECTSTATUS_LEVELWAR_SLAYER_HERO`, etc.
- **Uso:** Eventos especiais, Level War, efeitos visuais de prestígio

**`__CONTRIBUTE_SYSTEM`:**
- **Função:** Sistema de pontos de contribuição e graus (ranking/prestígio)
- **Componentes:**
  - Pontos: `ContributePoint` em `S_SLOT`
  - Função: `countContributeGrade()` calcula graus baseados em pontos
  - UI: Exibe graus de contribuição por raça
  - Limites: 6000, 9000, 15000, 27000, 45000, 69000, 99000 (7 graus)
- **Uso:** Sistema de ranking/prestígio baseado em contribuição

**Diferença:**
- São sistemas **independentes** mas relacionados
- `__HERO_SYSTEM` = efeitos visuais/status
- `__CONTRIBUTE_SYSTEM` = ranking/prestígio

#### 2. `__TUNING_ITEM`

**Função:** Sistema de itens de tuning (modificação de itens)

**Itens de Tuning:**
- **Tipo 87** (`ITEM_CLASS_PERSONA`): Upgrade nível 51 (201→211)
- **Tipo 88** (`ITEM_CLASS_FASCIA`): Upgrade nível 61 (211→221)
- **Tipo 89** (`ITEM_CLASS_MITTEN`): Upgrade nível 71 (221→231)
- **Tipo 90** (`ITEM_CLASS_SUB_INVENTORY`): Upgrade nível 81 (231→241)
- **Tipo 92** (`ITEM_CLASS_ETHEREAL_CHAIN`): Upgrade nível 91 (241→251)

**Itens de Evento:**
- **Tipo 93** (`ITEM_CLASS_OUSTERS_HARMONIC_PENDENT`): Evento "Happy New Year" (+5% chance)
- **Tipo 94** (`ITEM_CLASS_CHECK_MONEY`): Evento "Happy New Year"

**Métodos Relacionados:**
- `RunTuningConfirm1()`: Diálogo de confirmação para tuning possível
- `RunTuningConfirm2()`: Diálogo para tuning impossível
- `IsTuningItem()`: Verifica se item é de tuning

**Proteção no Código:**
- Declaração: `VS_UI.h` linha 535 (dentro de `#if __CONTENTS(__TUNING_ITEM)`)
- Implementação: `Vs_ui.cpp` linha 4413 (dentro de `#if __CONTENTS(__TUNING_ITEM)`)
- Uso: Deve estar protegido por `#if __CONTENTS(__TUNING_ITEM)`

### Configurações por País

| País | `__HERO_SYSTEM` | `__CONTRIBUTE_SYSTEM` | `__HERO_SYSTEM_ITEM` | `__CONTRIBUTE_SYSTEM_ITEM` | `__TUNING_ITEM` |
|------|------------------|----------------------|----------------------|---------------------------|-----------------|
| **Korea** | `__ON` | `__ON` | `__ON` | `__ON` | `__ON` |
| **CHS (Chinese)** | `__ON` | `__ON` | `__ON` | `__ON` | `__ON` |
| **Internation** | `__OFF` | `__ON` | `__ON` | `__OFF` | `__OFF` |
| **China** | `__ON` | `__ON` | `__OFF` | `__OFF` | `__OFF` |
| **Japan** | `__ON` | `__ON` | `__ON` | `__ON` | `__ON` |
| **ItemMania** | `__ON` | `__ON` | `__ON` | `__ON` | `__ON` |

### Regras de Uso de Macros

1. **Declaração e Implementação devem usar a mesma macro:**
   ```cpp
   // Header
   #if __CONTENTS(__TUNING_ITEM)
   void RunTuningConfirm1(int value, char *name1, char *name2);
   #endif
   
   // Implementação
   #if __CONTENTS(__TUNING_ITEM)  // ← MESMA macro
   void C_VS_UI::RunTuningConfirm1(...) { ... }
   #endif
   ```

2. **Uso deve estar protegido pela mesma macro:**
   ```cpp
   #if __CONTENTS(__TUNING_ITEM)
   gC_vs_ui.RunTuningConfirm1(10, "nome1", "nome2");
   #endif
   ```

3. **Inconsistências causam erros de compilação:**
   - Se declaração usa `__CONTRIBUTE_SYSTEM` mas implementação usa `__HERO_SYSTEM` → erro
   - Se uso não está protegido mas método está → erro quando macro está OFF

---

## Sistema de Itens de Tuning

### Visão Geral

Itens de tuning permitem modificar/upgradar outros itens no jogo. O sistema funciona tanto no cliente (UI) quanto no servidor (validação e processamento).

### Itens de Tuning - Upgrade de Nível

#### Tipo 87 - PERSONA
- **Classe:** `ITEM_CLASS_PERSONA`
- **Função:** Upgrade de itens de nível 51 para 61
- **Validação Servidor:** `level == 51 && itemType == 87`
- **Efeito:** Muda `itemType` de item alvo para `getNextItemType()` (201→211)
- **Localização Servidor:** `CGAddItemToItemHandler.cpp` linha 3124

#### Tipo 88 - FASCIA
- **Classe:** `ITEM_CLASS_FASCIA`
- **Função:** Upgrade de itens de nível 61 para 71
- **Validação Servidor:** `level == 61 && itemType == 88`
- **Efeito:** Upgrade 211→221
- **Localização Servidor:** `CGAddItemToItemHandler.cpp` linha 3128

#### Tipo 89 - MITTEN
- **Classe:** `ITEM_CLASS_MITTEN`
- **Função:** Upgrade de itens de nível 71 para 81
- **Validação Servidor:** `level == 71 && itemType == 89`
- **Efeito:** Upgrade 221→231
- **Localização Servidor:** `CGAddItemToItemHandler.cpp` linha 3132

#### Tipo 90 - SUB_INVENTORY
- **Classe:** `ITEM_CLASS_SUB_INVENTORY`
- **Função:** Upgrade de itens de nível 81 para 91
- **Validação Servidor:** `level == 81 && itemType == 90`
- **Efeito:** Upgrade 231→241
- **Localização Servidor:** `CGAddItemToItemHandler.cpp` linha 3136

#### Tipo 92 - ETHEREAL_CHAIN
- **Classe:** `ITEM_CLASS_ETHEREAL_CHAIN`
- **Função:** Upgrade de itens de nível 91 para próximo nível
- **Validação Servidor:** `level == 91 && itemType == 92`
- **Efeito:** Upgrade 241→251
- **Localização Servidor:** `CGAddItemToItemHandler.cpp` linha 3141

### Itens de Evento "Happy New Year"

#### Tipo 93 - OUSTERS_HARMONIC_PENDENT
- **Classe:** `ITEM_CLASS_OUSTERS_HARMONIC_PENDENT`
- **Função:** Item de evento que aumenta chance de upgrade
- **Validação Servidor:** `executeHappyNewYear()` linha 3247
- **Efeito:** Adiciona +5% de chance de sucesso (`ratio += 5`)
- **Uso:** Funciona com itens de nível 3-11 (201-211)
- **Chances Base (sem item 93):**
  - Nível 3 (201): 90%
  - Nível 4 (202): 70%
  - Nível 5 (203): 60%
  - Nível 6 (204): 30%
  - Nível 7 (205): 10%
  - Nível 8 (206): 5%
  - Nível 9 (207): 3%
  - Nível 10 (208): 2%
  - Nível 11 (209): 1%
- **Com item 93:** Adiciona +5% a todas as chances acima

#### Tipo 94 - CHECK_MONEY
- **Classe:** `ITEM_CLASS_CHECK_MONEY`
- **Função:** Item de evento (similar ao tipo 93)
- **Validação Servidor:** `executeHappyNewYear()`
- **Efeito:** Similar ao tipo 93

### Validação no Servidor

**Para tipos 87-90, 92 (`executeNewTunning`):**

1. **Item não pode ser TimeLimitItem:**
   ```cpp
   if (pItem->isTimeLimitItem()) {
       return ERROR;
   }
   ```

2. **Verifica se upgrade é possível:**
   ```cpp
   if (!g_pItemInfoManager->isPossibleItem(pItem->getItemClass(), pItemInfo->getNextItemType(), options)) {
       return ERROR;
   }
   ```

3. **Verifica se já está no nível máximo:**
   ```cpp
   if (pItemInfo->getNextItemType() == pItem->getItemType()) {
       return ERROR;
   }
   ```

4. **Valida nível do item alvo:**
   - Tipo 87: `level == 51`
   - Tipo 88: `level == 61`
   - Tipo 89: `level == 71`
   - Tipo 90: `level == 81`
   - Tipo 92: `level == 91`

5. **Se válido:**
   - Remove item de tuning do inventário
   - Muda `itemType` do item alvo para `getNextItemType()`
   - Envia packet de confirmação

**Para tipos 93-94 (`executeHappyNewYear`):**

1. **Item não pode ser TimeLimitItem**

2. **Item alvo deve ter `itemType >= 3 && <= 11` (níveis 201-211)**

3. **Calcula chance baseada no nível:**
   - Nível 3: 90% base
   - Nível 4: 70% base
   - ... (ver tabela acima)

4. **Tipo 93 adiciona +5% de chance**

5. **Rola random (1-100) e aplica upgrade se sucesso**

### Fluxo Cliente-Servidor

1. **Cliente (UI):**
   - Player arrasta item de tuning sobre item alvo
   - Se `__TUNING_ITEM = __ON`: Mostra diálogo `RunTuningConfirm1()`
   - Player confirma
   - Cliente envia packet `CGAddItemToItem` com IDs dos itens

2. **Servidor:**
   - Recebe packet `CGAddItemToItem`
   - Valida se itens existem no inventário do player
   - Valida se item de tuning pode ser usado no item alvo
   - Executa `executeNewTunning()` ou `executeHappyNewYear()`
   - Se sucesso: Modifica item alvo e remove item de tuning
   - Envia packet `GCAddItemToItemVerify` com resultado

3. **Cliente:**
   - Recebe packet de confirmação
   - Atualiza UI (remove item de tuning, atualiza item modificado)

### Arquivos Relacionados

**Cliente:**
- `Designed_Common\Project\NEW - VS_UI\src\header\VS_UI.h` - Declaração `RunTuningConfirm1/2`
- `Designed_Common\Project\NEW - VS_UI\src\Vs_ui.cpp` - Implementação
- `Designed_Common\Project\NEW - VS_UI\src\VS_UI_Game.cpp` - Implementação `C_VS_UI_GAME`
- `Designed_Common\Project\NEW - VS_UI\src\VS_UI_GameCommon.cpp` - Uso (linhas 11705-11712)
- `Designed_Common\Project\Client\MItem.h` - `IsTuningItem()` método
- `Designed_Common\Project\Client\ItemClassDef.h` - Definições de classes de itens

**Servidor:**
- `server\darkeden\vs\src\Core\Cpackets\CGAddItemToItemHandler.cpp` - Handler principal
  - Linha 280-286: Roteamento para `executeNewTunning` ou `executeHappyNewYear`
  - Linha 3088-3170: `executeNewTunning()` implementação
  - Linha 3171-3300: `executeHappyNewYear()` implementação
  - Linha 3124-3145: Validações de nível para tipos 87-92

---

## Questões de Segurança e Vantagem Competitiva

### Problema Identificado

**Questão:** Se diferentes clientes (com diferentes macros habilitadas) se conectarem ao mesmo servidor, isso pode dar vantagens desleais?

**Resposta:** Sim, potencialmente, dependendo de como o servidor valida.

### Como Funciona

#### Cliente (UI)
- As macros do cliente controlam apenas a **interface do usuário**
- Se `__TUNING_ITEM = __OFF`, o diálogo não aparece
- Mas o código pode ainda enviar pacotes se não estiver protegido adequadamente

#### Servidor (Validação)
- O servidor processa itens de tuning **independentemente do cliente**
- Valida se o item existe, se o player pode usar, etc.
- **NÃO verifica** se o cliente tem a macro habilitada (não deveria confiar no cliente)

### Cenários de Vantagem

**Cenário 1: Cliente Modificado**
- Cliente com `__TUNING_ITEM = __OFF` (não mostra UI)
- Mas se alguém modificar o cliente para enviar pacotes manualmente
- Servidor pode processar se validações passarem
- **Vantagem:** Player usa funcionalidade que não deveria ter acesso

**Cenário 2: Servidor Não Valida Adequadamente**
- Se servidor não verifica se item de tuning existe no banco de dados
- Se servidor não verifica se funcionalidade está habilitada para aquela versão
- Cliente modificado pode enviar pacotes que servidor aceita
- **Vantagem:** Funcionalidades não licenciadas podem ser usadas

**Cenário 3: Diferentes Versões no Mesmo Servidor**
- Cliente CHS (`__TUNING_ITEM = __ON`) vs Cliente Internation (`__TUNING_ITEM = __OFF`)
- Ambos conectados ao mesmo servidor
- Se servidor processa tuning para ambos → Cliente CHS tem vantagem (vê UI, pode usar)
- Se servidor valida versão → Ambos têm acesso igual (servidor decide)

### O Que o Servidor Valida

**Validações Encontradas no Código:**

1. **Item existe no inventário:**
   ```cpp
   Item* pItem = pInventory->getItem(InvenX, InvenY);
   if (pItem == NULL) return ERROR;
   ```

2. **Item pode ser usado:**
   ```cpp
   if (!isUsableItem(pItem, pCreature)) return ERROR;
   ```

3. **Nível do item alvo:**
   ```cpp
   if(level == 51 && pMouseItem->getItemType() == 87) { ... }
   ```

4. **Item não é TimeLimitItem:**
   ```cpp
   if (pItem->isTimeLimitItem()) return ERROR;
   ```

**O Que o Servidor NÃO Valida (Potencial Problema):**

1. **Se funcionalidade está habilitada para aquela versão regional**
2. **Se cliente tem permissão para usar aquela funcionalidade**
3. **Se item de tuning existe no banco de dados daquela versão**

### Por Que Isso É um Problema

**Comentário no `ContentsFilter.h`:**
```cpp
// 실행 시간에 필터링하는 것은 해킹의 위험이 있기 때문에
// 컴파일 시간에 필터링되도록 한다.
```

**Tradução:** "Filtrar em tempo de execução tem risco de hack, por isso filtra em tempo de compilação"

**Problema:**
- Filtragem em tempo de compilação no cliente **não impede hack**
- Cliente modificado pode enviar pacotes que servidor aceita
- Servidor deveria validar independentemente, mas pode não estar validando tudo

### Solução Correta (Servidor)

O servidor deveria:

1. **Validar se funcionalidade está habilitada para aquela versão/região:**
   - Verificar no banco de dados se item de tuning existe
   - Verificar configuração de servidor para aquela versão

2. **Validar se item existe e é válido:**
   - Verificar se item está na tabela de itens
   - Verificar se item pode ser usado naquela versão

3. **Não confiar no cliente:**
   - Validar tudo server-side
   - Cliente é apenas UI, servidor é autoridade

### Exemplo Prático

**Cenário:**
- Servidor aceita clientes CHS e Internation
- CHS tem `__TUNING_ITEM = __ON` (vê UI, pode usar)
- Internation tem `__TUNING_ITEM = __OFF` (não vê UI)

**Se servidor não valida versão:**
- Ambos podem usar tuning (se enviarem pacote correto)
- Cliente modificado Internation pode usar tuning
- **Vantagem desleal:** Cliente com UI tem melhor experiência, mas ambos têm acesso

**Se servidor valida versão:**
- Apenas clientes CHS podem usar tuning
- Servidor rejeita pacotes de clientes Internation
- **Sem vantagem:** Servidor controla acesso

### Resumo de Segurança

**Macros do Cliente:**
- Controlam apenas **UI/UX**
- **NÃO são segurança**
- Podem ser contornadas com cliente modificado

**Segurança Real:**
- Depende de **validação no servidor**
- Servidor deve validar tudo independentemente
- Servidor é autoridade, cliente é apenas interface

**Risco:**
- Se servidor não valida adequadamente → **Pode haver vantagem desleal**
- Cliente modificado pode usar funcionalidades não licenciadas
- Diferentes versões no mesmo servidor podem ter acesso diferente

**Recomendação:**
- Verificar se servidor valida adequadamente essas funcionalidades
- Implementar validação server-side para versões regionais
- Não confiar em validação apenas no cliente

---

## Sistema de Ousters e Desabilitação de Raças

### Visão Geral

O sistema de Ousters é uma terceira raça jogável no jogo DarkEden, além de Slayer e Vampire. O sistema permite habilitar ou desabilitar Ousters através de macros de compilação condicional, controlando tanto a interface de criação de personagem quanto o processamento de dados relacionados.

### Arquitetura de Controle

O controle de Ousters é feito através da macro `__RACE_OUSTERS`, que atualmente **não está definida** no arquivo `ContentsFilter.h`. Esta macro controla:

1. **Interface de Criação de Personagem:**
   - Exibição do botão de seleção de raça Ousters
   - Processamento de seleção de raça durante criação
   - Validação de atributos específicos de Ousters

2. **Processamento de Packets:**
   - Recepção e processamento de dados de personagens Ousters
   - Renderização de criaturas Ousters no jogo
   - Exibição de informações de status relacionadas

3. **Elementos de UI:**
   - Exibição de contadores em eventos CTF (Capture The Flag)
   - Ajustes de posicionamento em interfaces específicas
   - Mensagens e tooltips relacionados

### Localização de Código Relacionado a Ousters

#### Arquivos de Interface de Criação de Personagem

**Arquivo: `VS_UI_NewTitle.cpp`**

- **Linha 1814:** Seleção aleatória inicial de raça
  ```cpp
  #if __CONTENTS(__RACE_OUSTERS)
      m_btRace_Select = rand()%3;  // Inclui Ousters (0=Slayer, 1=Vampire, 2=Ousters)
  #else
      m_btRace_Select = rand()%2;  // Apenas Slayer e Vampire
  #endif
  ```

- **Linha 1835-1839:** Atribuição de raça Ousters no switch
  ```cpp
  default:
      m_p_slot->Race = RACE_OUSTERS;
      m_p_slot->man_info.face = M_FACE3;
      m_p_slot->man_info.hair = M_HAIR3;
      break;
  ```

- **Linha 1853:** Configuração de cor de pele específica para Ousters
  ```cpp
  if(m_p_slot->Race == RACE_OUSTERS)
      m_p_slot->skin_color = 377;
  ```

- **Linha 1905:** Validação de atributos durante criação
  ```cpp
  if((id >= STR_PLUS_ID && id <= INT_MINUS_ID && m_p_slot->Race != RACE_OUSTERS) ||
     (id == REROLL_ID && m_p_slot->Race != RACE_SLAYER))
      return;
  ```

- **Linha 1949-1961:** Handler do botão de seleção Ousters
  ```cpp
  case OUSTERS_ID:
      m_p_slot->Race = RACE_OUSTERS;
      m_p_slot->man_info.coat = (CHAR_MAN)1;
      m_p_slot->man_info.right = (CHAR_MAN)0;
      // ... configuração de cores e atributos
      break;
  ```

**Arquivo: `VS_UI_Title.cpp`**

- **Linha 2118-2127:** Handler do botão de seleção Ousters (versão antiga da UI)
  ```cpp
  case OUSTERS_ID:
      m_p_slot->Race = RACE_OUSTERS;
      m_p_slot->man_info.coat = (CHAR_MAN)1;
      // ... configuração adicional
      break;
  ```

- **Linha 2146:** Validação de bonus points para Ousters
  ```cpp
  else if(m_p_slot->Race == RACE_OUSTERS && m_p_slot->bonus_point != 0)
  {
      g_msg_left_bonus_point->Start();
  }
  ```

#### Arquivos de Processamento de Packets

**Arquivo: `LCPCListHandler.cpp`**

- **Linha 333-352:** Processamento de lista de personagens Ousters
  ```cpp
  case PC_OUSTERS:
  {
      PCOustersInfo * pPCOustersInfo = dynamic_cast<PCOustersInfo*>(pInfo);
      g_pUserInformation->Character[i] = pPCOustersInfo->getName().c_str();
      g_pUserInformation->Race[i] = RACE_OUSTERS;
      UI_SetCharacter( i, pPCOustersInfo );
  }
  break;
  ```

**Arquivo: `GCAddOustersHandler.cpp`**

- **Linhas 19-218:** Handler completo para adicionar criatura Ousters ao jogo
  - Criação de objeto `MCreatureWear`
  - Configuração de tipo de criatura (`CREATURETYPE_OUSTERS_OPERATOR` ou baseado em `coatType`)
  - Configuração de cores, efeitos, status
  - Adição à zona do jogo

**Arquivo: `GCAddOustersCorpseHandler.cpp`**

- **Linhas 169-218:** Handler para adicionar cadáver de Ousters
  - Processamento similar ao handler de criatura viva
  - Configuração de estado de morte
  - Aplicação de itens e efeitos

#### Arquivos de Interface de Jogo

**Arquivo: `VS_UI_GameCommon.cpp`**

- **Linha 369:** Verificação de raça para diálogo de aprendizado de skill
  ```cpp
  if(g_eRaceInterface == RACE_OUSTERS && C_VS_UI_MILITARYDLG::m_ousters_Magic == -1)
  ```

- **Linhas 1170, 1201, 1234, 1269, 1358, 1393, 1432, 1579:** Múltiplos `case RACE_OUSTERS:` em switches relacionados a UI de jogo

**Arquivo: `vs_ui_gamecommon2.cpp`**

- **Linha 1900:** Ajuste de posição Y para level up
  ```cpp
  case RACE_OUSTERS:
      m_image_spk.Open(SPK_LEVELUP);
      _y = g_pUserInformation->iResolution_y - 218;
      break;
  ```

- **Linha 1952:** Imagem de ressurreição para Ousters
  ```cpp
  case RACE_OUSTERS: rImageIdx = RESURRECT_OUSTERS; break;
  ```

- **Linha 1961:** Imagem de skill de outros Ousters
  ```cpp
  case RACE_OUSTERS: rImageIdx = SKILL_FROM_OTHER_OUSTERS; break;
  ```

- **Linha 2056:** Processamento adicional relacionado a Ousters

- **Linha 2233:** Outro case de RACE_OUSTERS

**Arquivo: `VS_UI_GameCommon.cpp` (Team Member List)**

- **Linhas 30892-30895:** Ajuste de posicionamento de nome de guilda
  ```cpp
  int guildNameY = 6;
  if(g_eRaceInterface == RACE_OUSTERS)
  {
      guildNameY = 8;
  }
  ```

- **Linhas 30906-30910:** Ajuste de posicionamento de emblema de guilda
  ```cpp
  POINT guild_mark_position={x+2,y+2};
  if(g_eRaceInterface == RACE_OUSTERS)
  {
      guild_mark_position.x += 3;
      guild_mark_position.y += 3;
  }
  ```

**Arquivo: `vs_ui_gamecommon2.cpp` (CTF Status)**

- **Linhas 9763-9767:** Loop condicional para exibição de contadores de flags
  ```cpp
  #if __CONTENTS(__RACE_OUSTERS)
      for( i =0 ; i< 3; i++ )  // Slayer, Vampire, Ousters
  #else
      for( i =0 ; i< 2; i++ )  // Apenas Slayer e Vampire
  #endif
  ```

- **Linha 9725:** Definição de retângulo para flag de Ousters
  ```cpp
  RECT rectFlag[3] = {
      {101,9, 129,23},  // SLAYER
      {151,9, 179,23},  // VAMPIRE
      {200,9, 228,23}   // OUSTERS
  };
  ```

**Arquivo: `VS_UI_WorldMap.cpp`**

- **Linha 263:** Proteção condicional relacionada a Ousters
  ```cpp
  #if __CONTENTS(__RACE_OUSTERS)
      // Código específico de Ousters
  #endif
  ```

### Como Desabilitar Ousters

#### Passo 1: Adicionar Macro em ContentsFilter.h

A macro `__RACE_OUSTERS` não está atualmente definida em `ContentsFilter.h`. Para desabilitar Ousters, adicione na seção do país desejado:

```cpp
#ifdef __DESIGNED_CHS  // ou __DESIGNED_KOREA, __DESIGNED_JAPAN, etc.
    // ... outras definições ...
    #define __RACE_OUSTERS    __OFF
#endif
```

#### Passo 2: Verificar Handlers de Packet

Os seguintes arquivos de handlers de packet precisam ser protegidos com `#if __CONTENTS(__RACE_OUSTERS)`:

1. **GCAddOustersHandler.cpp:**
   - Todo o handler `GCAddOustersHandler::execute()` deve estar protegido
   - Caso contrário, o cliente tentará processar packets de Ousters mesmo com a UI desabilitada

2. **GCAddOustersCorpseHandler.cpp:**
   - Handler de cadáveres de Ousters deve estar protegido

3. **LCPCListHandler.cpp (linha 333):**
   - O case `PC_OUSTERS` deve estar protegido
   - Caso contrário, a lista de personagens pode falhar ao carregar personagens Ousters existentes

#### Passo 3: Verificar Interface de Criação

Os arquivos de criação de personagem já possuem algumas proteções condicionais, mas devem ser verificados:

1. **VS_UI_NewTitle.cpp:**
   - Linha 1814: Já protegido
   - Linha 1949: Handler `OUSTERS_ID` deve estar protegido
   - Linha 1853: Verificação de `RACE_OUSTERS` deve estar protegida

2. **VS_UI_Title.cpp:**
   - Linha 2118: Handler `OUSTERS_ID` deve estar protegido

#### Passo 4: Verificar Elementos de UI

Elementos de UI que referenciam Ousters devem ser protegidos ou removidos condicionalmente:

1. **vs_ui_gamecommon2.cpp:**
   - Linha 9763: Já protegido com `#if __CONTENTS(__RACE_OUSTERS)`
   - Outros cases de `RACE_OUSTERS` devem ser verificados

2. **VS_UI_GameCommon.cpp:**
   - Múltiplos `case RACE_OUSTERS:` devem ser verificados
   - Ajustes de posicionamento (linhas 30892, 30906) podem permanecer, mas devem ser testados

### Impacto de Desabilitar Ousters

#### Problemas Potenciais com Dados Existentes no Servidor

Se o servidor ainda contém personagens Ousters e o cliente é compilado sem suporte a Ousters:

1. **Lista de Personagens:**
   - O servidor envia `PC_OUSTERS` na lista de personagens (`LCPCList`)
   - Se o handler não estiver protegido, o cliente tentará processar
   - Se o handler estiver protegido mas o código de processamento falhar, a lista pode não carregar corretamente
   - **Resultado:** Erro ao carregar lista de personagens ou crash

2. **Criaturas Ousters no Jogo:**
   - O servidor envia packets `GCAddOusters` para personagens Ousters na zona
   - Se o handler não estiver protegido, o cliente tentará criar objetos `MCreatureWear` com tipo Ousters
   - Se o código de renderização não suportar Ousters, pode haver:
     - Personagens invisíveis
     - Renderização incorreta
     - Crash ao tentar renderizar
   - **Resultado:** Personagens Ousters não aparecem ou causam crash

3. **Packets Relacionados:**
   - `GCAddOustersCorpse` (cadáveres)
   - Outros packets específicos de Ousters
   - **Resultado:** Comportamento indefinido ou crash

#### Solução Recomendada

Para desabilitar Ousters completamente:

1. **Cliente:**
   - Adicionar `#define __RACE_OUSTERS __OFF` em `ContentsFilter.h`
   - Proteger todos os handlers de packet relacionados
   - Proteger todos os elementos de UI relacionados
   - Compilar e testar

2. **Servidor (Recomendado):**
   - Modificar servidor para não enviar dados de Ousters
   - Ou manter código de recepção no cliente mesmo com UI desabilitada
   - Validar que servidor não envia packets de Ousters para clientes sem suporte

3. **Banco de Dados:**
   - Migrar ou remover personagens Ousters existentes
   - Ou garantir que servidor não os carregue/envie

### Variável de Escopo em C_VS_UI_STATUS_CTF::Show()

**Arquivo:** `vs_ui_gamecommon2.cpp`  
**Função:** `C_VS_UI_STATUS_CTF::Show()`  
**Linha do Problema:** 9766

**Problema:**
A variável `i` é declarada dentro do primeiro loop `for` (linha 9734), mas é reutilizada em um segundo loop condicional (linhas 9764-9767) que está fora do escopo da declaração original.

**Código Problemático:**
```cpp
void C_VS_UI_STATUS_CTF::Show()
{
    // ... código anterior ...
    
    if( g_FL2_GetDC() )
    {
        int topscore = 1;
        for(int i=0;i<3;i++)  // ← i declarado aqui, escopo limitado ao for
        {
            if( topscore < m_num_flag[i] )
                topscore = m_num_flag[i];			
        }
        
        // ... código do tempo ...
        
#if __CONTENTS(__RACE_OUSTERS)
        for( i =0 ; i< 3; i++ )  // ← ERRO: i não está no escopo
#else
        for( i =0 ; i< 2; i++ )  // ← ERRO: i não está no escopo
#endif
        {
            // ... código de exibição ...
        }
    }
}
```

**Solução:**
Declarar `int i;` no início do bloco `if( g_FL2_GetDC() )` para que ambos os loops possam usar a mesma variável:

```cpp
void C_VS_UI_STATUS_CTF::Show()
{
    // ... código anterior ...
    
    if( g_FL2_GetDC() )
    {
        int i;  // ← DECLARAR AQUI, no início do bloco if
        
        int topscore = 1;
        for(i=0;i<3;i++)  // ← Agora usa i (sem redeclarar)
        {
            if( topscore < m_num_flag[i] )
                topscore = m_num_flag[i];			
        }
        
        // ... código do tempo ...
        
#if __CONTENTS(__RACE_OUSTERS)
        for( i =0 ; i< 3; i++ )  // ← Agora funciona: i está no escopo
#else
        for( i =0 ; i< 2; i++ )  // ← Agora funciona: i está no escopo
#endif
        {
            // ... código de exibição ...
        }
    }
}
```

**Explicação Técnica:**
Em C++ moderno, variáveis declaradas dentro de um `for` têm escopo limitado ao próprio loop. Para reutilizar a variável em múltiplos loops dentro do mesmo escopo de função, ela deve ser declarada no escopo da função ou do bloco que contém todos os loops.

### Função de C_VS_UI_STATUS_CTF

A classe `C_VS_UI_STATUS_CTF` exibe o status do modo CTF (Capture The Flag):

1. **Tempo Restante:**
   - Calcula e exibe o tempo restante até o fim do evento
   - Formato: `HH:MM:SS`

2. **Contadores de Flags:**
   - Exibe quantas flags cada raça capturou:
     - Slayer (índice 0)
     - Vampire (índice 1)
     - Ousters (índice 2) - apenas se `__RACE_OUSTERS` estiver definido

3. **Destaque Visual:**
   - A raça com mais flags é exibida em amarelo (topscore)
   - Outras raças são exibidas em branco

4. **Tooltips:**
   - Ao passar o mouse sobre o tempo, exibe detalhes do tempo restante
   - Ao passar o mouse sobre cada contador, exibe nome da raça e quantidade de flags

**Por que Ousters é diferente:**
- Se `__RACE_OUSTERS` não estiver definido, o loop itera apenas 2 vezes (Slayer e Vampire)
- Se `__RACE_OUSTERS` estiver definido, o loop itera 3 vezes (inclui Ousters)
- O array `rectFlag[3]` sempre tem 3 elementos, mas apenas os relevantes são exibidos

---

## Correções de Compatibilidade C++ Moderno (VS2022)

### Problema: Const Correctness com strstr()

**Arquivos Afetados:**
- `NEW - VS_UI\src\vs_ui_gamecommon2.cpp`
- `NEW - VS_UI\lib\vs_ui_gamecommon2.cpp`

**Problema:**
Em C++ moderno (VS2022), `strstr()` quando recebe `const char*` retorna `const char*`, mas o código estava atribuindo a variáveis `char*`, causando erro de const correctness.

**Código Problemático:**
```cpp
char *istag = NULL;
char *isfont = NULL;
// ...
istag = strstr(str.c_str(), "<");  // ERRO: strstr retorna const char*
isfont = strstr(str.c_str(), "#"); // ERRO: strstr retorna const char*
```

**Locais Afetados:**
1. `C_VS_UI_HELPDESC::Show()` - linhas 12044-12045, 12062-12063, 12136-12137
2. `C_VS_UI_HELPDESC::HelpDescPasing()` - linhas 12584-12585, 12614-12615, 12708-12710

**Solução Aplicada:**
Substituir uso de ponteiros por métodos de `std::string`:

```cpp
// ANTES:
char *istag = NULL;
char *isfont = NULL;
istag = strstr(str.c_str(), "<");
isfont = strstr(str.c_str(), "#");
if(istag) { ... }
if(isfont) { ... }

// DEPOIS:
bool hasTag = (str.find("<") != std::string::npos);
bool hasFont = (str.find("#") != std::string::npos);
if(hasTag) { ... }
if(hasFont) { ... }
```

**Vantagens da Solução:**
- Sem problemas de const correctness
- Sem problemas de escopo (variáveis locais em cada loop)
- Mais seguro (sem ponteiros)
- Mais idiomático em C++ moderno
- Performance similar ou melhor

**Nota sobre `pCur`:**
A variável `char *pCur` não tem o mesmo problema porque recebe `sztemp` que é um array de char (`char[]`), não uma string constante. Arrays de char decaem para `char*`, não `const char*`, então não há problema de const correctness.

### Problema: Sintaxe de Ponteiros para Função Membro

**Arquivo Afetado:**
- `NEW - VS_UI\src\VS_UI_GameCommon.cpp`

**Problema:**
Em C++ moderno (VS2022), para criar ponteiros para funções membro, é necessário usar explicitamente o operador `&`. O código antigo usava sintaxe que era aceita em compiladores mais antigos, mas o VS2022 exige sintaxe moderna.

**Código Problemático:**
```cpp
void (C_VS_UI::*pHotkeyFunction[ChatCommandCnt])() = {
    C_VS_UI::HotKey_NormalChat,  // ERRO: falta &
    C_VS_UI::HotKey_ZoneChat,     // ERRO: falta &
    // ...
};
```

**Locais Afetados:**
1. Linha 5391-5405: Array de 14 elementos
2. Linha 5686-5691: Array de 6 elementos

**Solução Aplicada:**
Adicionar `&` antes de cada função membro:

```cpp
void (C_VS_UI::*pHotkeyFunction[ChatCommandCnt])() = {
    &C_VS_UI::HotKey_NormalChat,
    &C_VS_UI::HotKey_ZoneChat,
    &C_VS_UI::HotKey_Whisper,
    &C_VS_UI::HotKey_PartyChat,
    &C_VS_UI::HotKey_GuildChat,
    &C_VS_UI::HotKey_UnionChat,
    &C_VS_UI::HotKey_Chat_Help,
    &C_VS_UI::HotKey_Chat_Help,
    &C_VS_UI::HotKey_Help,
    &C_VS_UI::HotKey_Help,
    &C_VS_UI::HotKey_Help,
    &C_VS_UI::HotKey_Help,
    &C_VS_UI::HotKey_Background_Music,
    &C_VS_UI::HotKey_Effect_Music,
};
```

**Explicação Técnica:**
- Em C++ antigo, o nome da função membro podia ser usado diretamente
- Em C++ moderno (C++11+), o operador `&` é obrigatório para criar ponteiros para funções membro
- A sintaxe `&Classe::Funcao` cria explicitamente um ponteiro para função membro

### Problema: Const Correctness na Função findkey()

**Arquivos Afetados:**
- `NEW - VS_UI\src\vs_ui_gamecommon2.cpp` (linha 12868)
- `NEW - VS_UI\lib\vs_ui_gamecommon2.cpp` (linha 11306)

**Problema:**
A função `findkey()` recebe `const char*` mas usa ponteiros `char*` para manipular strings constantes, causando erro de const correctness.

**Código Problemático:**
```cpp
char* C_VS_UI_HELPDESC::findkey(const char* tagstr, char* keyword)
{
    char *s = strstr(tagstr, keyword);  // ERRO: strstr retorna const char*
    // ...
    char *start = strstr(s, "'");       // ERRO: strstr retorna const char*
    char *end = strstr(start, "'");     // ERRO: strstr retorna const char*
    // ...
}
```

**Problemas Identificados:**
1. Assinatura inconsistente: header declara `const char* keyword`, mas implementação no `lib` usa `char* keyword`
2. Ponteiros intermediários deveriam ser `const char*` pois não modificam a string original
3. Falta verificações de segurança (NULL checks)

**Solução Aplicada:**
```cpp
char* C_VS_UI_HELPDESC::findkey(const char* tagstr, const char* keyword)
{
    if(tagstr == NULL || keyword == NULL) return NULL;
    
    const char *s = strstr(tagstr, keyword);
    if(s == NULL)
        return NULL;
    
    static char Buffer[512];
    memset(Buffer, 0, 512);
    
    const char *start = strstr(s, "'");
    if(start == NULL) return NULL;
    start++;  // Pula a primeira aspas
    
    const char *end = strstr(start, "'");
    if(end == NULL || end <= start) return NULL;
    
    size_t len = end - start;
    if(len >= 512) len = 511;  // Proteção contra buffer overflow
    memcpy(Buffer, start, len);
    Buffer[len] = '\0';
    
    return Buffer;
}
```

**Correções Aplicadas:**
1. Assinatura: `char* keyword` → `const char* keyword` (consistente com header)
2. Ponteiros intermediários: `char*` → `const char*`
3. Verificações de segurança: NULL checks e validação de tamanho
4. Garantia de null terminator no buffer

**Nota sobre Implementações:**
- O projeto `lib` compila o arquivo do diretório `src`, não do `lib`
- O arquivo `lib\vs_ui_gamecommon2.cpp` não é usado pelo projeto `lib`
- A correção foi aplicada apenas no arquivo `src\vs_ui_gamecommon2.cpp`

### Problema: Uso de ITEM_CLASS_RANK_GEM sem Proteção Condicional

**Arquivo Afetado:**
- `NEW - VS_UI\src\VS_UI_Description.cpp`

**Problema:**
`ITEM_CLASS_RANK_GEM` está definido apenas dentro de `#if __CONTENTS(__GLOBAL_NPC)` em `ItemClassDef.h`, mas está sendo usado em `VS_UI_Description.cpp` sem proteção condicional, causando erro de compilação quando `__GLOBAL_NPC` não está definido.

**Definição em ItemClassDef.h:**
```cpp
#if __CONTENTS(__GLOBAL_NPC)
    ITEM_CLASS_CALLNPC_CARD,    // 103
    ITEM_CLASS_RANK_GEM,        // 104
#endif //__GLOBAL_NPC
```

**Locais Afetados em VS_UI_Description.cpp:**
1. Linha 700: `else if ( p_item->GetItemClass() == ITEM_CLASS_RANK_GEM )`
2. Linha 1202: `if ( itemClass == ITEM_CLASS_RANK_GEM && itemType >=0 && itemType < 104 )`
3. Linha 4513: `else if ( itemClass == ITEM_CLASS_RANK_GEM )`

**Solução Aplicada:**
Proteger cada uso com `#if __CONTENTS(__GLOBAL_NPC)`:

**Correção 1 - Linha 700:**
```cpp
// ANTES:
}
else if ( p_item->GetItemClass() == ITEM_CLASS_RANK_GEM )
{
    // ... código ...
}
else

// DEPOIS:
}
#if __CONTENTS(__GLOBAL_NPC)
else if ( p_item->GetItemClass() == ITEM_CLASS_RANK_GEM )
{
    // ... código ...
}
#endif //__GLOBAL_NPC
else
```

**Correção 2 - Linha 1202:**
```cpp
// ANTES:
}

if ( itemClass == ITEM_CLASS_RANK_GEM && itemType >=0 && itemType < 104 )
{
    // ... código ...
}

// DEPOIS:
}

#if __CONTENTS(__GLOBAL_NPC)
if ( itemClass == ITEM_CLASS_RANK_GEM && itemType >=0 && itemType < 104 )
{
    // ... código ...
}
#endif //__GLOBAL_NPC
```

**Correção 3 - Linha 4513:**
```cpp
// ANTES:
}
else if ( itemClass == ITEM_CLASS_RANK_GEM )
{
    line_count ++;
}
else if(itemClass == ITEM_CLASS_ETHEREAL_CHAIN

// DEPOIS:
}
#if __CONTENTS(__GLOBAL_NPC)
else if ( itemClass == ITEM_CLASS_RANK_GEM )
{
    line_count ++;
}
#endif //__GLOBAL_NPC
else if(itemClass == ITEM_CLASS_ETHEREAL_CHAIN
```

**Explicação Técnica:**
- `ITEM_CLASS_RANK_GEM` é uma feature condicional que depende de `__GLOBAL_NPC`
- Se `__GLOBAL_NPC` não estiver definido, o enum não contém `ITEM_CLASS_RANK_GEM`
- O código que usa `ITEM_CLASS_RANK_GEM` deve estar protegido pela mesma macro
- Isso garante que o código só seja compilado quando a feature estiver disponível

**Status de __GLOBAL_NPC:**
Atualmente `__GLOBAL_NPC` está definido como `__ON` para todos os países (Korea, CHS, Internation, Japan, China, ItemMania) em `ContentsFilter.h`. No entanto, a proteção condicional é necessária para:
1. Compatibilidade com builds futuros onde a feature pode ser desabilitada
2. Consistência com o padrão de código do projeto
3. Prevenção de erros de compilação em diferentes configurações

### Problema: ConfigurationType Incorreto em Projetos de Biblioteca

**Arquivo Afetado:**
- `Designed_Chs\Project\NEW - VS_UI\lib\lib.vcxproj`

**Problema:**
O projeto `lib` foi migrado com `ConfigurationType` definido como `Application` (executável) quando deveria ser `StaticLibrary` (biblioteca estática). Isso causa o erro de linker `LNK1561: entry point must be defined`, pois o linker espera encontrar uma função `main()` ou `WinMain()` para executáveis, mas bibliotecas não têm entry point.

**Erro:**
```
Error LNK1561 entry point must be defined
```

**Causa:**
Durante a migração de `.vcproj` para `.vcxproj`, o `ConfigurationType` pode ter sido convertido incorretamente se:
1. O arquivo `.vcproj` original tinha `ConfigurationType="1"` (Application) quando deveria ser `"4"` (StaticLibrary)
2. O script de migração não detectou corretamente que o projeto é uma biblioteca pelo nome

**Solução Aplicada:**
Correção manual do arquivo `.vcxproj`, alterando `ConfigurationType` de `Application` para `StaticLibrary` em todas as três configurações:

```xml
<!-- ANTES (INCORRETO): -->
<PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'" Label="Configuration">
  <ConfigurationType>Application</ConfigurationType>
  ...
</PropertyGroup>

<!-- DEPOIS (CORRETO): -->
<PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'" Label="Configuration">
  <ConfigurationType>StaticLibrary</ConfigurationType>
  ...
</PropertyGroup>
```

**Configurações Corrigidas:**
1. `Debug|Win32` - linha 37
2. `Release|Win32` - linha 31
3. `ReleaseLog|Win32` - linha 25

**Prevenção Futura:**
Foi adicionada a função `Fix-LibraryConfigurationType` ao módulo `ProjectModernization.psm1` que:
1. Detecta projetos de biblioteca pelo nome (lista: `lib`, `CWinMain Library`, `D3DLib`, `DEUtil`, `DirectXLib`, `FileCheckLib`, `Frame Library`, `MZLib`, `MiniLZO`, `OggLib`, `RarLib`, `SpriteLib`, `VirtualFileSystem`, `VolumeLib`)
2. Verifica se `ConfigurationType` está como `Application`
3. Corrige automaticamente para `StaticLibrary` se necessário
4. Preserva encoding CP949 durante a correção

A função é executada automaticamente no passo 4 do script `scripts\migrate_all_projects_to_vs2022.ps1` após a migração de cada projeto.

**Explicação Técnica:**
- **Application**: Gera um executável (`.exe`) que requer um entry point (`main()` ou `WinMain()`)
- **StaticLibrary**: Gera uma biblioteca estática (`.lib`) que não requer entry point, apenas contém código compilado para ser linkado com outros projetos
- **DynamicLibrary**: Gera uma DLL (`.dll`) que pode ter um entry point opcional (`DllMain()`)

O projeto `lib` é uma biblioteca estática usada pelo projeto `Client`, portanto deve ter `ConfigurationType` como `StaticLibrary`.

### Problema: Erro "Cannot open include file: 'unistd.h'" em nfs_iio.cpp

**Arquivo Afetado:**
- `Designed_Common\Project\Client\VirtualFileSystem\nFS\nfs_iio.cpp`
- `Designed_Common\Project\Client\VirtualFileSystem\VirtualFileSystem.vcxproj`

**Problema:**
O arquivo `nfs_iio.cpp` contém código condicional que verifica `WIN32` para decidir qual header incluir:

```cpp
#if defined(WIN32) && !defined(CYGWIN) && !defined(CYGNUS)
#include <windows.h> /* for GetSystemInfo() */
#include <io.h>      /* for chsize() */
#else
#include <unistd.h>  /* for getpagesize() */
#endif
```

Se `WIN32` não estiver definido nas definições de pré-processador do projeto, o compilador tenta incluir `<unistd.h>`, que não existe no Windows, causando erro de compilação.

**Erro:**
```
Error C1083: Cannot open include file: 'unistd.h': No such file or directory
```

**Causa:**
O projeto `VirtualFileSystem.vcxproj` não tinha `WIN32` definido nas `PreprocessorDefinitions` do `ClCompile`, fazendo com que o código compilasse a branch `#else` que inclui `<unistd.h>` (header do Linux/Unix).

**Solução Aplicada:**
1. Adicionado `WIN32` nas definições de pré-processador de todas as configurações (Debug, Release, ReleaseLog) no `VirtualFileSystem.vcxproj`:
   ```xml
   <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
     <ClCompile>
       <AdditionalIncludeDirectories>..;%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
       <PreprocessorDefinitions>WIN32;%(PreprocessorDefinitions)</PreprocessorDefinitions>
     </ClCompile>
     ...
   </ItemDefinitionGroup>
   ```

2. Corrigido `ConfigurationType` de `Application` para `StaticLibrary` (o projeto gera `VFS.lib`, uma biblioteca estática).

3. Atualizado o script `scripts\add_common_sdk.ps1` para adicionar automaticamente `WIN32` nas definições de pré-processador quando processar projetos `.vcxproj`, prevenindo o problema em futuras migrações.

**Explicação Técnica:**
- `<unistd.h>` é um header do padrão POSIX disponível em sistemas Unix/Linux, mas não no Windows
- No Windows, as funções equivalentes estão em `<windows.h>` e `<io.h>`
- O código usa compilação condicional para suportar múltiplas plataformas
- `WIN32` é uma macro tradicionalmente definida pelo compilador Microsoft Visual C++ para builds Windows, mas pode não estar presente em projetos migrados se não for explicitamente adicionada

**Prevenção Futura:**
O script `scripts\add_common_sdk.ps1` agora verifica e adiciona `WIN32` automaticamente em todos os projetos processados, garantindo que código condicional baseado em `WIN32` funcione corretamente.

### Problema: ConfigurationType Incorreto em VirtualFileSystem

**Arquivo Afetado:**
- `Designed_Common\Project\Client\VirtualFileSystem\VirtualFileSystem.vcxproj`

**Problema:**
O projeto `VirtualFileSystem` foi migrado com `ConfigurationType` definido como `Application` (executável) quando deveria ser `StaticLibrary` (biblioteca estática). O projeto gera `VFS.lib`, não um executável.

**Causa:**
Durante a migração de `.vcproj` para `.vcxproj`, o `ConfigurationType` foi convertido incorretamente.

**Solução Aplicada:**
Alterado `ConfigurationType` de `Application` para `StaticLibrary` nas três configurações (Debug, Release, ReleaseLog).

**Nota:**
A função `Fix-LibraryConfigurationType` no módulo `ProjectModernization.psm1` já cobre este caso, mas a correção foi aplicada manualmente para resolver o problema imediatamente.

### Problema: Includes Faltantes em FileCheckLib, DirectXLib e OggLib

**Arquivos Afetados:**
- `Designed_Common\Project\Client\FileCheckLib\FileCheckLib.vcxproj`
- `Designed_Common\Project\Client\DXLib\DirectXLib.vcxproj`
- `Designed_Common\Project\Client\OggLib\OggLib.vcxproj`

**Problemas Identificados:**

1. **FileCheckLib:**
   - Erro: `Cannot open include file: 'VFS_Macro.h'`
   - Causa: Faltava diretório `..\VirtualFileSystem` nos includes
   - Faltava `WIN32` nas definições de pré-processador
   - `ConfigurationType` estava como `Application` (deveria ser `StaticLibrary`)

2. **DirectXLib:**
   - Erro: `Cannot open include file: 'vfstream.h'`
   - Erro: `Cannot open include file: 'dmusici.h'` e `'DMusicI.h'`
   - Causa: Faltavam diretórios `..\VirtualFileSystem` e `..\..\..\..\common_sdk\Include` nos includes
   - Faltava `WIN32` nas definições de pré-processador
   - `ConfigurationType` estava como `Application` (deveria ser `StaticLibrary`)

3. **OggLib:**
   - Erro: `LNK1104: cannot open file 'ogg.lib'`
   - Causa: Biblioteca `ogg.lib` não encontrada (não é problema de `.vcxproj`, mas de biblioteca faltando)
   - Faltava `WIN32` nas definições de pré-processador
   - `ConfigurationType` estava como `Application` (deveria ser `StaticLibrary`)

**Soluções Aplicadas:**

**FileCheckLib.vcxproj:**
- Adicionado `..\VirtualFileSystem` em `AdditionalIncludeDirectories` (Debug e Release)
- Adicionado `WIN32` em `PreprocessorDefinitions` (Debug e Release)
- Alterado `ConfigurationType` de `Application` para `StaticLibrary` (Debug e Release)

**DirectXLib.vcxproj:**
- Adicionado `..\VirtualFileSystem` e `..\..\..\..\common_sdk\Include` em `AdditionalIncludeDirectories` (Debug e Release)
- Adicionado `WIN32` em `PreprocessorDefinitions` (Debug e Release)
- Alterado `ConfigurationType` de `Application` para `StaticLibrary` (Debug e Release)

**OggLib.vcxproj:**
- Adicionado `WIN32` em `PreprocessorDefinitions` (Debug e Release)
- Alterado `ConfigurationType` de `Application` para `StaticLibrary` (Debug e Release)
- **Nota sobre `ogg.lib`:** O erro `LNK1104` indica que a biblioteca `ogg.lib` não foi encontrada. Isso não é problema de `.vcxproj`, mas sim:
  - A biblioteca pode não existir no sistema
  - O diretório de bibliotecas pode não estar configurado corretamente
  - A biblioteca pode precisar ser compilada separadamente ou obtida de uma fonte externa

**Explicação Técnica:**

- **VFS_Macro.h e vfstream.h:** Estão localizados em `VirtualFileSystem\`, portanto projetos que os utilizam precisam incluir esse diretório
- **dmusici.h e DMusicI.h:** São headers do DirectX SDK, localizados em `common_sdk\Include\`. O código usa `#include <DMusicI.h>` mas o arquivo real é `dmusici.h` (case-sensitive no compilador, mas não no filesystem Windows)
- **ConfigurationType:** Todos esses projetos geram bibliotecas estáticas (`.lib`), não executáveis, portanto devem ser `StaticLibrary`

**Prevenção Futura:**
O script `scripts\add_common_sdk.ps1` foi atualizado para suportar parâmetros adicionais (`-NeedsVirtualFileSystem`, `-NeedsDirectXSDK`) que podem ser usados para adicionar automaticamente esses diretórios quando necessário.

### Problema: ConfigurationType Incorreto em Frame Library, RarLib e SpriteLib

**Arquivos Afetados:**
- `Designed_Common\Project\Client\FrameLib\Frame Library.vcxproj`
- `Designed_Common\Project\Client\RarLib\RarLib.vcxproj`
- `Designed_Common\Project\Client\SpriteLib\SpriteLib.vcxproj`

**Problema:**
Os três projetos foram migrados com `ConfigurationType` definido como `Application` (executável) quando deveriam ser `StaticLibrary` (biblioteca estática). Isso causa o erro de linker `LNK1561: entry point must be defined`, pois o linker espera encontrar uma função `main()` ou `WinMain()` para executáveis, mas bibliotecas não têm entry point.

**Erro:**
```
Error LNK1561 entry point must be defined
```

**Causa:**
Durante a migração de `.vcproj` para `.vcxproj`, o `ConfigurationType` foi convertido incorretamente. Todos esses projetos geram bibliotecas estáticas (`.lib`), não executáveis.

**Soluções Aplicadas:**

**Frame Library.vcxproj:**
- Alterado `ConfigurationType` de `Application` para `StaticLibrary` (Debug e Release)
- Adicionado `WIN32` em `PreprocessorDefinitions` (Debug e Release)

**RarLib.vcxproj:**
- Alterado `ConfigurationType` de `Application` para `StaticLibrary` (Debug e Release)
- Adicionado `WIN32` em `PreprocessorDefinitions` (Debug e Release)

**SpriteLib.vcxproj:**
- Alterado `ConfigurationType` de `Application` para `StaticLibrary` (Debug e Release)
- Adicionado `WIN32` em `PreprocessorDefinitions` (Debug e Release)

**Nota:**
A função `Fix-LibraryConfigurationType` no módulo `ProjectModernization.psm1` deveria ter detectado e corrigido esses casos automaticamente, mas a lista de nomes de bibliotecas pode não ter incluído todos os projetos. A correção foi aplicada manualmente para resolver o problema imediatamente.

**Projetos Corrigidos (Total de 10):**
1. `lib` - corrigido anteriormente
2. `VirtualFileSystem` - corrigido anteriormente
3. `FileCheckLib` - corrigido anteriormente
4. `DirectXLib` - corrigido anteriormente
5. `OggLib` - corrigido anteriormente
6. `Frame Library` - corrigido anteriormente
7. `RarLib` - corrigido anteriormente
8. `SpriteLib` - corrigido anteriormente
9. `D3DLib` - corrigido agora
10. `CWinMain Library` - corrigido agora

---

### Erro LNK1561: D3DLib e CWinMain Library

**Erro:**
```
Error LNK1561 entry point must be defined D3DLib
Error LNK1561 entry point must be defined CWinMain Library
```

**Causa:**
Ambos os projetos estavam configurados como `Application` (tipo de saída executável) quando deveriam ser `StaticLibrary` (biblioteca estática). O erro LNK1561 ocorre porque o linker espera encontrar um ponto de entrada (`main` ou `WinMain`) em projetos do tipo `Application`, mas esses projetos são bibliotecas que não possuem ponto de entrada.

**Correção Aplicada:**
1. **D3DLib.vcxproj:**
   - Alterado `<ConfigurationType>Application</ConfigurationType>` para `<ConfigurationType>StaticLibrary</ConfigurationType>` em ambas as configurações (Release|Win32 e Debug|Win32).
   - Adicionado `<PreprocessorDefinitions>WIN32;%(PreprocessorDefinitions)</PreprocessorDefinitions>` em ambas as configurações dentro de `<ClCompile>`.
   - O projeto já tinha `..\VirtualFileSystem` em `AdditionalIncludeDirectories` (corrigido anteriormente).

2. **CWinMain Library.vcxproj:**
   - Alterado `<ConfigurationType>Application</ConfigurationType>` para `<ConfigurationType>StaticLibrary</ConfigurationType>` em ambas as configurações (Release|Win32 e Debug|Win32).
   - Adicionado `<PreprocessorDefinitions>WIN32;%(PreprocessorDefinitions)</PreprocessorDefinitions>` em ambas as configurações dentro de `<ClCompile>`.

**Atualização do Script:**
O script `scripts\add_common_sdk.ps1` foi atualizado para:
1. Detectar automaticamente projetos `D3DLib` pelo caminho do arquivo e adicionar `VirtualFileSystem` aos includes automaticamente.
2. Melhorar a lógica de adição de `WIN32` para garantir que seja adicionado em TODAS as configurações (Release e Debug) usando regex para encontrar cada `ItemDefinitionGroup` individualmente.

**Arquivos Modificados:**
- `Designed_Common\Project\Client\D3DLib\D3DLib.vcxproj`
- `Designed_Common\Project\Client\CWinMain Library\CWinMain Library.vcxproj`
- `scripts\add_common_sdk.ps1`

---

## BasicS.lib e o Problema do _set_new_handler

### Visão Geral do BasicS

**BasicS** é uma biblioteca pré-compilada de utilitários básicos do Dark Eden, originalmente compilada com Visual Studio 6/2003 (circa 2000-2011). Ela fornece:

1. **Tratamento de Exceções** (`BasicException.h`)
   - Sistema de exceções customizado para o jogo
   - Macros: `_Error()`, `_ErrorStr()`, `CheckMemAlloc()`
   - Tipos de exceção: `MEM_ALLOC`, `FILE_OPEN`, `FILE_LOAD`, `FAILED_JOB`, `NULL_REF`

2. **Gerenciamento de Memória** (`BasicMemory.h`)
   - Macros: `DeleteNew()`, `DeleteNewArray()`

3. **Estruturas de Dados Básicas** (`BasicData.h`)
   - Classes: `Point`, `Rect`

4. **Funções de Sistema** (`PlatformUtil.h`, `Directory.h`, etc.)

### Localização do BasicS.lib

O `BasicS.lib` está localizado em:
- `Designed_Common\Lib\BasicS.lib`
- `Designed_Common\Lib\ui\BasicS.lib`

**Importante:** O código-fonte do BasicS **não está disponível** nos pacotes de código-fonte distribuídos. Apenas os headers (`.h`) estão presentes, mas não as implementações (`.cpp`).

### O Problema do _set_new_handler

#### Erro de Linker

Durante a migração para VS2022, o seguinte erro ocorreu:

```
Error LNK2019: unresolved external symbol "int (__cdecl*__cdecl _set_new_handler(int (__cdecl*)(unsigned int)))(unsigned int)" (?_set_new_handler@@YAP6AHI@ZP6AHI@Z@Z) referenced in function "void __cdecl g_SetNewHandler(void)" (?g_SetNewHandler@@YAXXZ)
Client C:\darkeden-nostaugia\client\Designed_Chs\Project\Client\BasicS.lib(BasicException.obj) 1
```

#### Causa Raiz

1. **Assinatura Antiga vs. Moderna:**
   - O `BasicS.lib` foi compilado com Visual Studio 6/2003, onde `_set_new_handler()` tinha uma assinatura diferente
   - Visual Studio 2022 usa uma assinatura atualizada da função
   - O linker não consegue resolver o símbolo porque a assinatura não corresponde

2. **Onde o Problema Ocorre:**
   - `BasicS.lib` contém uma função `g_SetNewHandler()` (em `BasicException.obj`)
   - Esta função internamente chama `_set_new_handler()` com a assinatura antiga
   - O VS2022 não fornece essa assinatura antiga por padrão

3. **Por Que Não Podemos Recompilar:**
   - O código-fonte do BasicS não está disponível
   - Apenas o `.lib` pré-compilado existe
   - Não há como recompilar com a assinatura moderna

### Solução Aplicada

#### Estratégia: Override com Stub

Em vez de tentar corrigir o `BasicS.lib` (impossível sem código-fonte), criamos uma implementação própria de `g_SetNewHandler()` que **não chama** `_set_new_handler()`.

#### Arquivo Criado

**Localização:** `Designed_Chs\Project\Client\src\a_ida_BasicException.cpp`

**Conteúdo Principal:**

```cpp
void __cdecl g_SetNewHandler(void)
{
    // In the original code, this would set the C++ new handler
    // For C compatibility, we'll leave this as a stub or implement
    // alternative memory management if needed
}
```

**Por Que Funciona:**

1. O linker encontra `g_SetNewHandler()` no código compilado do Client
2. Como a função não chama `_set_new_handler()`, não há conflito de assinatura
3. O `BasicS.lib` fica satisfeito porque `g_SetNewHandler()` está definida
4. O erro de linker é resolvido

#### Adição ao Projeto

O arquivo foi adicionado ao `Client.vcxproj`:

```xml
<ClCompile Include="src\a_ida_BasicException.cpp" />
```

**Localização no projeto:** Após `Client_PCH.cpp` (linha 244)

### Implementação Completa

O arquivo `a_ida_BasicException.cpp` também implementa:

1. **`g_BasicException()`** - Exibe MessageBox e termina o programa
2. **`HandleMemoryDepletion()`** - Tratamento de falta de memória
3. **Enum `EXCEPTION_CODE`** - Códigos de exceção compatíveis

**Nota:** A implementação é compatível com o header `BasicException.h` existente em `Designed_Common\Lib\ui\`.

### Tipos de Exceção Tratados pelo BasicS

O BasicS trata os seguintes tipos de exceção:

| Código | Descrição | Uso Típico |
|--------|-----------|------------|
| `MEM_ALLOC` | Falha na alocação de memória | Quando `new` ou `malloc` falha |
| `FILE_OPEN` | Falha ao abrir arquivo | Quando `fopen` ou `CreateFile` falha |
| `FILE_LOAD` | Falha ao carregar arquivo | Quando leitura de arquivo falha |
| `FAILED_JOB` | Falha em operação/trabalho | Operações genéricas que falharam |
| `NULL_REF` | Referência nula | Quando ponteiro é NULL inesperadamente |

### Macros de Uso

```cpp
// Verifica alocação de memória
char* ptr = new char[100];
CheckMemAlloc(ptr);  // Se ptr == NULL, lança MEM_ALLOC

// Lança exceção genérica
if (error_condition) {
    _Error(MEM_ALLOC);  // ou _Error(NULL_REF), etc.
}

// Lança exceção com mensagem customizada
_ErrorStr("Erro customizado");
```

### Exemplo de Uso Real

No arquivo `FL2.cpp`:

```cpp
char * p_temp = new char[max_size];
CheckMemAlloc(p_temp);  // Verifica se new foi bem-sucedido

if (p_dbcs == NULL) {
    _Error(NULL_REF);  // Lança exceção de referência nula
}
```

### Arquivos Relacionados

- **Header:** `Designed_Common\Lib\ui\BasicException.h`
- **Header Master:** `Designed_Common\Lib\ui\Basics.h`
- **Implementação:** `Designed_Chs\Project\Client\src\a_ida_BasicException.cpp`
- **Biblioteca:** `Designed_Common\Lib\BasicS.lib`

### Notas Técnicas

1. **Encoding:** O arquivo `a_ida_BasicException.cpp` foi criado em UTF-8 (sem BOM), pois contém apenas código em inglês.

2. **Compatibilidade:** A implementação é compatível com o código existente que usa `BasicException.h`.

3. **Performance:** O stub de `g_SetNewHandler()` não tem impacto de performance, pois é uma função vazia.

4. **Futuro:** Se o código-fonte do BasicS for encontrado no futuro, pode-se recompilar a biblioteca com VS2022 e remover este workaround.

### Referências Externas

- **Projeto de Referência:** `client-project-compiling\client-project\Designed_Chs\Project\Client\src\a_ida_BasicException.cpp`
- **Documentação Microsoft:** [set_new_handler](https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/set-new-handler) - Mudanças de assinatura entre versões do Visual Studio

---

## Correções Adicionais de Linker e Runtime

### Problema: Funções C Runtime Antigas (_vsprintf, __snprintf)

**Erro:**
```
LNK2019: unresolved external symbol _vsprintf referenced in NPGAMELIB.LIB(NPGameLib.obj)
LNK2019: unresolved external symbol __snprintf referenced in NPGAMELIB.LIB(NPGameLib.obj)
```

**Causa:**
- `NPGAMELIB.LIB` (pré-compilado) usa nomes antigos de funções C runtime
- VS2022 não expõe essas funções diretamente
- Funções foram renomeadas/removidas em versões mais recentes

**Solução:**
Adicionado `legacy_stdio_definitions.lib` às dependências do linker em `Client.vcxproj`:

**Configurações Afetadas:**
- `Release|Win32`
- `ReleaseLog|Win32`

**Mudança Aplicada:**
```xml
<AdditionalDependencies>
  ...
  legacy_stdio_definitions.lib
  ...
</AdditionalDependencies>
```

**Arquivo Modificado:**
- `Designed_Chs\Project\Client\Client.vcxproj`

**Status:** ✅ Resolvido

---

### Automação: Post-Build Event para Cópia de DLLs

**Problema:**
- DLLs necessárias precisavam ser copiadas manualmente para `client\nostaugia\`
- Processo manual propenso a erros
- Fácil esquecer de copiar alguma DLL

**Solução:**
Adicionado `PostBuildEvent` em `Client.vcxproj` para todas as configurações (Debug, Release, ReleaseLog).

**O que faz:**
1. Copia DLLs externas de `Designed_Common\Lib\` para `$(OutDir)`
2. Copia DLLs geradas por projetos (ex: `DEUtil.dll`) para `$(OutDir)`
3. Copia executável e todas as DLLs para `client\nostaugia\`

**DLLs Copiadas Automaticamente:**
- `IFC22.dll` / `ifc22.dll`
- `GL.dll` / `gl.dll`
- `Timer.dll` / `timer.dll`
- `BasicS.dll` / `basics.dll`
- `vorbisfile.dll`, `vorbis.dll`, `vorbisenc.dll`, `ogg.dll`
- `DEUtil.dll`
- `gmp.dll`, `pcre.dll`
- `msvcrt.dll`, `msvcr71.dll`, `msvcirt.dll`

**Arquivo Modificado:**
- `Designed_Chs\Project\Client\Client.vcxproj`

**Status:** ✅ Implementado e funcionando

---

### Problema: Exportação de Símbolos DLL (g_StatusManager)

**Erro Runtime:**
```
fk.exe - Ponto de entrada não encontrado
Não foi possível localizar o ponto de entrada do procedimento 
?g_StatusManager@@3VMStatusManager@@A 
na biblioteca de vínculo dinâmico C:\darkeden-nostaugia\client\nostaugia\fk.exe
```

**Causa:**
- `DEUtil.vcxproj` não tinha definições de pré-processador necessárias
- Faltava `__MK_DLL__` → `__EX` não se tornava `__declspec(dllexport)`
- `g_StatusManager` não era exportado pela `DEUtil.dll`
- `fk.exe` não conseguia encontrar o símbolo em runtime

**Solução:**
Adicionadas definições de pré-processador em `DEUtil.vcxproj`:

**Debug Configuration:**
```xml
<ClCompile>
  <PreprocessorDefinitions>WIN32;_DEBUG;_WINDOWS;_USRDLL;DEUTIL_EXPORTS;__MK_DLL__;%(PreprocessorDefinitions)</PreprocessorDefinitions>
  <RuntimeLibrary>MultiThreadedDebug</RuntimeLibrary>
</ClCompile>
<Link>
  <OutputFile>$(OutDir)$(TargetName).dll</OutputFile>
  <ImportLibrary>$(OutDir)$(TargetName).lib</ImportLibrary>
</Link>
```

**Release Configuration:**
```xml
<ClCompile>
  <PreprocessorDefinitions>WIN32;NDEBUG;_WINDOWS;_USRDLL;DEUTIL_EXPORTS;__MK_DLL__;%(PreprocessorDefinitions)</PreprocessorDefinitions>
  <RuntimeLibrary>MultiThreaded</RuntimeLibrary>
  <Optimization>MaxSpeed</Optimization>
  <InlineFunctionExpansion>AnySuitable</InlineFunctionExpansion>
  <FunctionLevelLinking>true</FunctionLevelLinking>
  <StringPooling>true</StringPooling>
</ClCompile>
<Link>
  <OutputFile>$(OutDir)$(TargetName).dll</OutputFile>
  <ImportLibrary>$(OutDir)$(TargetName).lib</ImportLibrary>
</Link>
```

**Arquivo Modificado:**
- `Designed_Common\Project\Client\DEUtil\DEUtil.vcxproj`

**Documentação Completa:**
- Ver `client\docs\FIX_DEUTIL_EXPORT_ERROR.md` para detalhes técnicos completos

**Status:** ✅ Resolvido

---

## Resumo de Todas as Correções Aplicadas

### Erros de Linker Resolvidos

1. ✅ **`_set_new_handler`** - Conflito de assinatura (stub implementation)
2. ✅ **`_vsprintf` e `__snprintf`** - Funções C runtime antigas (`legacy_stdio_definitions.lib`)
3. ✅ **`g_StatusManager`** - Exportação de símbolos DLL (definições de pré-processador)

### Automação Implementada

4. ✅ **Post-Build Event** - Cópia automática de DLLs para `client\nostaugia\`

### Documentação Criada

5. ✅ **`ARCHITECTURE.md`** - Arquitetura multi-variante
6. ✅ **`PROJECT_COMPARISON.md`** - Comparação técnica de projetos
7. ✅ **`WHY_STUB_SOLUTION_FOUND_FASTER.md`** - Explicação técnica
8. ✅ **`FIX_DEUTIL_EXPORT_ERROR.md`** - Erro de exportação DLL
9. ✅ **`UPDATE_SYSTEM_COMPONENTS.md`** - Componentes de update
10. ✅ **`SETUP_AND_DISTRIBUTION.md`** - Setup e distribuição
11. ✅ **`NEXT_STEPS_INSTALLER.md`** - Guia de instalador
12. ✅ **`COMPLETE_FIXES_SUMMARY.md`** - Resumo completo de todas as correções

### Scripts Criados

13. ✅ **`organize_for_distribution.bat`** - Organização de binários
14. ✅ **`prepare_setup.bat`** - Preparação de distribuição
15. ✅ **`setup_template.iss`** - Template Inno Setup

**Status Final:** ✅ **MIGRAÇÃO COMPLETA E FUNCIONAL**

Para detalhes completos de todas as correções, consulte: `client\docs\COMPLETE_FIXES_SUMMARY.md`

---

## Referências

- `modernization\docs\ENCODING_RULES.md` - Regras de encoding
- `modernization\docs\ENCODING_SPECIFICATION.md` - Especificação de encoding
- `modernization\scripts\Modules\EncodingHelpers.psm1` - Funções de encoding
- `client\docs\COMPLETE_FIXES_SUMMARY.md` - Resumo completo de todas as correções
- `client\docs\FIX_DEUTIL_EXPORT_ERROR.md` - Detalhes do erro de exportação DLL
