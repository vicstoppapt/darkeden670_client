# Guia de Setup do Repositório Git

Instruções para limpar e fazer push do código fonte para o GitHub.

---

## 🔧 Pré-requisitos

1. **Git instalado** e configurado
2. **Acesso ao repositório**: https://github.com/vicstoppapt/darkeden670_client
3. **Arquivos de dados** já no Google Drive (link no README.md)

---

## 📋 Passo a Passo

### 1. Clonar o Repositório (se ainda não tiver)

```bash
cd c:\darkeden-nostaugia
git clone https://github.com/vicstoppapt/darkeden670_client.git client-git
cd client-git
```

### 2. Limpar Repositório Existente

**⚠️ ATENÇÃO: Isso vai apagar tudo que está no repositório!**

```bash
# Remover todos os arquivos do repositório (exceto .git)
git rm -r --cached .
git clean -fdx

# Remover todos os arquivos do working directory
# (Cuidado: isso apaga arquivos não rastreados também)
Remove-Item -Recurse -Force * -Exclude .git
```

### 3. Copiar Código Fonte do Projeto

```bash
# Voltar para o diretório do projeto
cd c:\darkeden-nostaugia\client-git

# Copiar apenas código fonte (respeitando .gitignore)
# O .gitignore já está configurado para excluir arquivos pesados
xcopy /E /I /Y ..\client\* .
```

**OU manualmente:**
- Copiar `Designed_Common/`
- Copiar `Designed_Chs/`
- Copiar `common_libs/` (apenas código fonte, não .lib/.dll - binários no Drive)
- Copiar `docs/`
- Copiar `scripts/`
- **NÃO copiar** `nostaugia/` (vazio, dados no Drive)
- **NÃO copiar** binários de `common_libs/` (`.lib`, `.dll` - no Drive)
- Copiar `.gitignore`
- Copiar `README.md`

### 4. Verificar Tamanho Antes do Commit

```bash
# Verificar tamanho dos arquivos que serão commitados
git add .
git status

# Ver tamanho total
git count-objects -vH
```

**Limite do GitHub:** 100MB por arquivo, recomendado < 50MB total para repositório.

### 5. Fazer Commit

```bash
# Adicionar todos os arquivos (respeitando .gitignore)
git add .

# Verificar o que será commitado
git status

# Commit inicial
git commit -m "Initial commit: DarkEden 670 Client source code

- Código fonte completo do cliente
- Suporte a múltiplos idiomas (i18n)
- Documentação técnica completa
- Arquivos de dados disponíveis no Google Drive:
  - nostaugia.zip: https://drive.google.com/file/d/1uR6iOeT7ACrCSvfsLGQHqJMQDcW1l92M/view?usp=sharing
  - common_libs.zip: https://drive.google.com/file/d/1TjAiGVlJgrxB60qXa5It27zuPiEoafSo/view?usp=sharing"
```

### 6. Fazer Push (Forçar se necessário)

```bash
# Se o repositório já tinha conteúdo, forçar push
git push -f origin main

# OU se for primeira vez
git push -u origin main
```

---

## ✅ Verificação Pós-Push

1. **Verificar no GitHub:**
   - Acesse: https://github.com/vicstoppapt/darkeden670_client
   - Confirme que apenas código fonte está presente
   - Verifique se README.md está visível com link do Drive

2. **Verificar tamanho:**
   - GitHub mostra tamanho do repositório
   - Deve estar < 100MB

3. **Testar clone:**
   ```bash
   cd c:\temp
   git clone https://github.com/vicstoppapt/darkeden670_client.git test-clone
   # Verificar se clona corretamente
   ```

---

## 🚨 Troubleshooting

### Erro: "file too large"

Se algum arquivo for muito grande (> 100MB):

```bash
# Encontrar arquivos grandes
git ls-files | ForEach-Object { Get-Item $_ } | Where-Object { $_.Length -gt 50MB } | Select-Object FullName, Length

# Remover do commit
git rm --cached <arquivo-grande>
# Adicionar ao .gitignore
echo "<arquivo-grande>" >> .gitignore
```

### Erro: "repository size too large"

Se o repositório inteiro for muito grande:

1. Verificar o que está sendo commitado:
   ```bash
   git add .
   git status
   ```

2. Ajustar `.gitignore` para excluir mais arquivos

3. Limpar histórico (se necessário):
   ```bash
   # Criar branch limpa
   git checkout --orphan new-main
   git add .
   git commit -m "Clean history"
   git branch -D main
   git branch -m main
   git push -f origin main
   ```

---

## 📝 Checklist Final

- [ ] `.gitignore` configurado corretamente
- [ ] `README.md` criado com link do Drive
- [ ] Apenas código fonte no repositório
- [ ] Tamanho < 100MB
- [ ] Commit feito
- [ ] Push realizado
- [ ] Verificado no GitHub
- [ ] Link do Drive funcionando

---

**Última Atualização:** Janeiro 2025
