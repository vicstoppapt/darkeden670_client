# DarkEden 670 Client - Código Fonte

Repositório do código fonte do cliente DarkEden v670.

---

## 📦 Arquivos Pesados

**Este repositório contém apenas o código fonte** devido ao limite de 100MB do GitHub.

**Arquivos de dados, binários e builds estão disponíveis no Google Drive:**

### 📁 Dados do Jogo

🔗 **[Download: nostaugia.zip](https://drive.google.com/file/d/1uR6iOeT7ACrCSvfsLGQHqJMQDcW1l92M/view?usp=sharing)**

O arquivo `nostaugia.zip` contém:
- Arquivos de dados do jogo (`.rpk`, `.bin`, `.smp`, `.ssi`)
- Arquivos de áudio (`.ogg`, `.wav`)
- Configurações e dados do cliente
- Arquivos necessários para executar o cliente

**Instalação:** Extraia na pasta `client/nostaugia/`

### 📚 Bibliotecas Comuns

🔗 **[Download: common_libs.zip](https://drive.google.com/file/d/1TjAiGVlJgrxB60qXa5It27zuPiEoafSo/view?usp=sharing)**

O arquivo `common_libs.zip` contém:
- Bibliotecas pré-compiladas (`.lib`, `.dll`)
- Binários necessários para compilação
- Arquivos de build que não podem ser gerados facilmente

**Instalação:** Extraia na pasta `client/common_libs/`

**Nota:** O repositório contém apenas o código fonte de `common_libs/`. Os binários devem ser baixados do Drive.

---

## 📁 Estrutura do Projeto

```
client/
├── Designed_Common/          # Código comum (Coreia/Internacional)
│   └── Project/
│       ├── Client/           # Cliente principal
│       ├── ClientInfo/       # Ferramentas de info
│       ├── GameUpdater/      # Sistema de atualização
│       └── NEW - VS_UI/      # Interface do usuário
├── Designed_Chs/             # Variante chinesa
├── common_libs/              # Bibliotecas comuns
├── docs/                     # Documentação técnica
├── scripts/                  # Scripts de build e setup
└── nostaugia/                # Dados do jogo (vazio - baixar do Drive)
```

---

## 🛠️ Compilação

### Pré-requisitos

- **Visual Studio 2022** (Community ou superior)
- **Windows SDK** 10.0 ou superior
- **DirectX SDK** (junho 2010)
- Arquivos de dados do Google Drive extraídos em `nostaugia/`

### Passos

1. **Baixar arquivos necessários:**
   - Baixe `nostaugia.zip` do [Google Drive](https://drive.google.com/file/d/1uR6iOeT7ACrCSvfsLGQHqJMQDcW1l92M/view?usp=sharing)
   - Extraia na pasta `client/nostaugia/`
   - Baixe `common_libs.zip` do [Google Drive](https://drive.google.com/file/d/1TjAiGVlJgrxB60qXa5It27zuPiEoafSo/view?usp=sharing)
   - Extraia na pasta `client/common_libs/`

2. **Abrir projeto:**
   - Abra `Designed_Chs/Project/Client/Client.sln` no Visual Studio 2022

3. **Compilar:**
   - Selecione configuração `Release` ou `Debug`
   - Build → Build Solution (F7)

### Variantes de Build

- **Designed_Common**: Versão coreana/internacional
- **Designed_Chs**: Versão chinesa (recomendada para compilação)

---

## 🌍 Internacionalização (i18n)

O cliente possui suporte completo para múltiplos idiomas:

### Idiomas Suportados

- Coreano (padrão)
- Chinês
- Japonês
- Inglês
- Taiwan

### Sistema de Detecção

O idioma é detectado automaticamente através do arquivo `DATA\INFO\Infodata.rpk`:

```cpp
DARKEDEN_LANGUAGE CheckDarkEdenLanguage()
{
    // Lê LANGUAGE=X do Infodata.rpk
    // Retorna: DARKEDEN_KOREAN, DARKEDEN_CHINESE, etc.
}
```

### Classes de Conteúdo

- `CI_KOREAN` - Coreano
- `CI_CHINESE` - Chinês
- `CI_JAPAN` - Japonês
- (Provavelmente `CI_ENGLISH` também)

### Adicionar Novo Idioma

1. Adicionar enum em `Client.cpp`:
   ```cpp
   enum DARKEDEN_LANGUAGE {
       // ...
       DARKEDEN_PORTUGUESE,  // Novo
   };
   ```

2. Criar classe `CI_PORTUGUESE` (baseada em `CI_KOREAN`)

3. Adicionar case no switch:
   ```cpp
   case DARKEDEN_PORTUGUESE:
       gC_ci = new CI_PORTUGUESE;
       break;
   ```

4. Adicionar recursos visuais em `GameUpdater/Resource/`

---

## 📚 Documentação

Documentação técnica completa está em `docs/`:

- **[TECHNICAL_KNOWLEDGE_BASE.md](docs/TECHNICAL_KNOWLEDGE_BASE.md)** ⭐ - Base de conhecimento completo
- **[ARCHITECTURE.md](docs/ARCHITECTURE.md)** - Arquitetura do projeto
- **[COMPLETE_FIXES_SUMMARY.md](docs/COMPLETE_FIXES_SUMMARY.md)** - Correções aplicadas
- **[MIGRATION_TO_VS2022.md](docs/MIGRATION_TO_VS2022.md)** - Migração para VS2022

---

## 🔧 Configuração

### Encoding

- **Arquivos fonte**: EUC-KR (CP949) - **NÃO ALTERAR**
- **Banco de dados**: euckr (EUC-Korean)
- **Compilação**: UTF-8 BOM é proibido

### Flags de Compilação

Configuradas em `Designed_Common/Project/Client/ContentsFilter.h`:

- `__DESIGNED_KOREA` - Versão coreana
- `__DESIGNED_CHS` - Versão chinesa
- `__LANGUAGE_CHANGE` - Suporte a mudança de idioma
- `__INTERNATIONAL_UI` - UI internacional

---

## 📝 Notas Importantes

1. **Encoding**: Arquivos `.cpp` e `.h` devem permanecer em EUC-KR (CP949)
2. **Build**: Compilar em `Designed_Chs` (não em `Designed_Common`)
3. **Dados**: Arquivos de dados devem estar em `nostaugia/` (baixar do Drive)
4. **Bibliotecas**: Binários de `common_libs/` devem ser baixados do Drive
5. **Limite Git**: Repositório contém apenas código fonte (max 100MB)

---

## 🚀 Próximos Passos

- [ ] Extrair strings traduzíveis do código
- [ ] Criar sistema de tradução para português
- [ ] Documentar processo de adicionar novos idiomas
- [ ] Criar scripts de build automatizado

---

## 📄 Licença

Código fonte do cliente DarkEden v670.

---

**Última Atualização:** Janeiro 2025
