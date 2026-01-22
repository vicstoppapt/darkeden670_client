# Documentação - Migração VS2022

Índice de toda a documentação técnica criada durante a migração para Visual Studio 2022.

---

## 📋 Documentos Principais

### [TECHNICAL_KNOWLEDGE_BASE.md](./TECHNICAL_KNOWLEDGE_BASE.md) ⭐
**Base de Conhecimento Técnico Completo**
- Tudo que a próxima IA precisa saber
- Estrutura, encoding, problemas resolvidos
- Troubleshooting e referências rápidas
- **LEIA PRIMEIRO se for nova IA!**

---

### [COMPLETE_FIXES_SUMMARY.md](./COMPLETE_FIXES_SUMMARY.md)
**Resumo completo de todas as correções aplicadas**
- Lista todas as correções de linker, runtime e automação
- Status de cada correção
- Referências rápidas

### [ARCHITECTURE.md](./ARCHITECTURE.md)
**Arquitetura do Projeto**
- Estrutura multi-variante (`Designed_Common` vs `Designed_Chs`)
- Fluxo de compilação
- Por que compilar em `Designed_Chs`

### [PROJECT_COMPARISON.md](./PROJECT_COMPARISON.md)
**Comparação Técnica de Projetos**
- Comparação entre `client` atual e `client-project-compiling`
- Encoding, configurações, bibliotecas, caminhos
- Conclusão técnica

---

## 🔧 Correções e Fixes

### [FIX_DEUTIL_EXPORT_ERROR.md](./FIX_DEUTIL_EXPORT_ERROR.md)
**Erro: g_StatusManager não encontrado**
- Causa raiz do erro de exportação DLL
- Solução aplicada em `DEUtil.vcxproj`
- Como funciona sistema de exportação
- Verificação com `dumpbin`

### [WHY_STUB_SOLUTION_FOUND_FASTER.md](./WHY_STUB_SOLUTION_FOUND_FASTER.md)
**Por que a solução do stub foi encontrada mais rápido no projeto de referência**
- Explicação técnica das diferenças
- Comparação de abordagens
- Reafirma superioridade técnica do projeto atual

---

## 📦 Distribuição e Setup

### [SETUP_AND_DISTRIBUTION.md](./SETUP_AND_DISTRIBUTION.md)
**Organização de Arquivos e Distribuição**
- Estrutura de distribuição (`dist/bin`, `dist/data`)
- Scripts helper (`organize_for_distribution.bat`, `prepare_setup.bat`)
- Workflow de distribuição manual

### [NEXT_STEPS_INSTALLER.md](./NEXT_STEPS_INSTALLER.md)
**Guia Completo para Criar Instalador**
- Microsoft Visual Studio Installer Projects 2022
- Configuração passo a passo
- Troubleshooting

---

## 🎮 Componentes do Sistema

### [UPDATE_SYSTEM_COMPONENTS.md](./UPDATE_SYSTEM_COMPONENTS.md)
**Componentes do Sistema de Update**
- `DpkUnpacker` - Ferramenta de desenvolvedor
- `GameUpdater` - Aplicação MFC para updates
- `AutoPatchManager` - Criador de patches
- Formatos de arquivo (`.dpk`, `.dpi`, `.dp2`)

---

## 📚 Documentação Principal

### [MIGRATION_TO_VS2022.md](./MIGRATION_TO_VS2022.md)
**Documento Principal de Migração**
- Processo completo de migração
- Todas as correções aplicadas
- Histórico de mudanças
- Referências técnicas

---

## 🗂️ Estrutura de Documentação

```
client/
├── docs/
│   ├── README.md                    # Este arquivo (índice)
│   ├── MIGRATION_TO_VS2022.md       # Documento principal de migração
│   ├── COMPLETE_FIXES_SUMMARY.md    # Resumo de todas as correções
│   ├── ARCHITECTURE.md              # Arquitetura do projeto
│   ├── PROJECT_COMPARISON.md        # Comparação técnica
│   ├── FIX_DEUTIL_EXPORT_ERROR.md   # Fix: g_StatusManager
│   ├── WHY_STUB_SOLUTION_FOUND_FASTER.md  # Explicação técnica
│   ├── SETUP_AND_DISTRIBUTION.md    # Setup e distribuição
│   ├── NEXT_STEPS_INSTALLER.md      # Guia de instalador
│   ├── UPDATE_SYSTEM_COMPONENTS.md  # Componentes de update
│   ├── ITEM_GENERATION_SYSTEM.md    # Sistema de geração de itens
│   ├── VISION_SYSTEM.md            # Sistema de visão
│   └── LUCK_SYSTEM.md              # Sistema de sorte
└── scripts/
    ├── migrate_all_projects_to_vs2022.ps1  # Migração de projetos
    ├── run_full_migration.ps1              # Migração completa
    ├── add_common_sdk.ps1                  # Adicionar SDK comum
    ├── configure_precompiled_header.ps1    # Configurar PCH
    ├── organize_for_distribution.bat       # Organizar distribuição
    ├── prepare_setup.bat                   # Preparar setup
    └── setup_template.iss                   # Template Inno Setup
```

---

## 🔍 Busca Rápida

**Procurando por:**
- **Erros de linker?** → `COMPLETE_FIXES_SUMMARY.md`
- **Erro `g_StatusManager`?** → `FIX_DEUTIL_EXPORT_ERROR.md`
- **Erro `_set_new_handler`?** → `MIGRATION_TO_VS2022.md` (seção "BasicS.lib")
- **Scripts de migração?** → `../scripts/`
- **Scripts de distribuição?** → `../scripts/`
- **Erro `_vsprintf`/`__snprintf`?** → `COMPLETE_FIXES_SUMMARY.md` (seção 2)
- **Como criar instalador?** → `NEXT_STEPS_INSTALLER.md`
- **Estrutura do projeto?** → `ARCHITECTURE.md`
- **Comparação de projetos?** → `PROJECT_COMPARISON.md`

---

---

## 📁 Estrutura de Pastas

```
client/
├── docs/                    # Toda a documentação
│   ├── TECHNICAL_KNOWLEDGE_BASE.md  # ⭐ Base de conhecimento (LEIA PRIMEIRO)
│   ├── README.md            # Este arquivo (índice)
│   ├── MIGRATION_TO_VS2022.md
│   ├── COMPLETE_FIXES_SUMMARY.md
│   ├── ARCHITECTURE.md
│   ├── PROJECT_COMPARISON.md
│   ├── FIX_DEUTIL_EXPORT_ERROR.md
│   ├── WHY_STUB_SOLUTION_FOUND_FASTER.md
│   ├── SETUP_AND_DISTRIBUTION.md
│   ├── NEXT_STEPS_INSTALLER.md
│   ├── UPDATE_SYSTEM_COMPONENTS.md
│   ├── ITEM_GENERATION_SYSTEM.md
│   ├── VISION_SYSTEM.md
│   └── LUCK_SYSTEM.md
└── scripts/                 # Scripts utilitários
    ├── README.md             # Documentação dos scripts
    ├── migrate_all_projects_to_vs2022.ps1
    ├── run_full_migration.ps1
    ├── add_common_sdk.ps1
    ├── configure_precompiled_header.ps1
    ├── organize_for_distribution.bat
    ├── prepare_setup.bat
    └── setup_template.iss
```

---

**Última Atualização:** Janeiro 2025  
**Status:** ✅ Documentação completa e atualizada
