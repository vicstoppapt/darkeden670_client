# Sistema de Geração de Itens - Servidor

## Visão Geral

Este documento explica como o servidor gera itens quando monstros são derrotados, incluindo como `luck` afeta a geração, quantos atributos um item pode ter, e como modificar as regras de geração.

---

## Conceitos Importantes

### 1. Luck Level vs Luck Attribute

**Luck Level (luckLevel):**
- **Tipo:** `int`
- **Fonte:** `pItemOwnerCreature->getLuck()` (atributo do player)
- **Uso:** Usado em cálculos de upgrade de itens
- **Limite:** `MAX_LUCK_LEVEL = 140` (definido em código)
- **Localização:** `LuckInfo.h` linha 14

**Luck Attribute (m_Luck):**
- **Tipo:** `short` (Luck_t)
- **Fonte:** Calculado no servidor (BaseLuck + itens + opções + rank + party)
- **Uso:** Valor exibido no cliente, usado em cálculos de loot
- **Limite:** Não há limite explícito no código (teoricamente limitado pelo tipo `short`)

**Diferença:**
- `luckLevel` = Valor usado internamente para cálculos de upgrade (limitado a 140)
- `m_Luck` = Valor do atributo do player (enviado ao cliente)

---

## Limite de Luck Level

### Valor Máximo

**Definição:** `MAX_LUCK_LEVEL = 140`

**Localização:** `server\gameserver\LuckInfo.h` linha 14
```cpp
const int MAX_LUCK_LEVEL = 140;
```

**Aplicação:**
- `MonsterManager.cpp` linha 2987: `luckLevel = min(MAX_LUCK_LEVEL, luckLevel);`
- `MonsterManager.cpp` linha 3077: `luckLevel = min(MAX_LUCK_LEVEL, luckLevel);`

**Quando é aplicado:**
- Antes de calcular upgrade de tipo de item (`upgradeItemTypeByLuck`)
- Antes de calcular upgrade de opções (`upgradeOptionByLuck`)

**Nota:** Este limite é aplicado **após** adicionar variação aleatória:
```cpp
luckLevel = luckLevel + (rand()%20) - 10;  // Variação de -10 a +10
luckLevel = min(MAX_LUCK_LEVEL, luckLevel); // Limita a 140
```

**Para modificar:**
- Alterar `MAX_LUCK_LEVEL` em `LuckInfo.h`
- Recompilar o servidor

---

## Quantidade de Atributos em Itens

### Limite Máximo

**Máximo:** 2 atributos por item

**Localização:** `ItemUtil.cpp` linha 1344
```cpp
// 현재는 옵션이 2개까지밖에 안 붙는다.
// (Atualmente apenas 2 opções podem ser anexadas)
if (pTemplate->OptionType.size()>=2)
    return false;
```

**Função:** `isPossibleNextOption()` verifica se pode adicionar mais um atributo

**Lógica:**
1. Se já tem 2 atributos → retorna `false` (não pode adicionar mais)
2. Se está vazio → retorna `true` (pode adicionar o primeiro)
3. Se tem 1 atributo → calcula probabilidade baseada em `NextOptionRatio`

### Como os Atributos São Gerados

**Fluxo de geração:**

1. **Primeiro atributo:**
   - Baseado em `m_OptionRatio` do Treasure
   - `Treasure.cpp` linha 849-858:
   ```cpp
   int OptionRatio = rand()%TREASURE_RATIO_MODULUS;
   if (OptionRatio < m_OptionRatio)
       pTemplate->bCreateOption = true;  // Item terá atributo
   ```

2. **Seleção do primeiro atributo:**
   - `TreasureItemType::getRandomOption()` seleciona aleatoriamente
   - Baseado em `m_TreasureOptionTypes` e seus ratios

3. **Segundo atributo:**
   - Verifica `isPossibleNextOption()` (linha 1341)
   - Calcula probabilidade baseada em:
     - `NextOptionRatio` do item
     - `NextOptionRatio` do primeiro atributo
     - `RareItemRatio` (variável global)

4. **Seleção do segundo atributo:**
   - Loop `for (int k=0; k<2; k++)` em `Treasure.cpp` linha 298
   - Verifica se já existe atributo da mesma `OptionClass` (`hasOptionClass`)
   - Se não existe conflito, adiciona o segundo atributo

**Fórmula de probabilidade do segundo atributo:**
```cpp
// ItemUtil.cpp linha 1373-1403
nextOptionRatio = nextItemRatio * nextOptionRatio1 * nextOptionRatio2
baseMultiplier = 100 * 100 * 100 = 1000000
selectRatio = rand() % baseMultiplier
success = selectRatio < (nextOptionRatio * rareItemRatio / 100)
```

---

## Como Luck Afeta Geração de Itens

### O que Luck NÃO Afeta

**Luck NÃO afeta:**
- **Quantidade de atributos** - Sempre máximo 2 (definido em código)
- **Quais atributos podem aparecer** - Definido por `getPossibleOptionVector()` baseado na classe do item
- **Probabilidade de item ter atributo** - Controlada por `m_OptionRatio` do Treasure

### O que Luck AFETA

**Luck afeta:**

1. **Upgrade de Tipo de Item** (`upgradeItemTypeByLuck`)
   - **Localização:** `MonsterManager.cpp` linha 2977-3064
   - **Função:** Melhora o tipo do item (ex: tipo 1 → tipo 2)
   - **Fórmula:** Varia por raça/classe do player
   ```cpp
   // Slayer (linha 2998)
   ratio = (luckLevel / (4.254 + (1.0 + ItemType)/5.0)) * 100;
   
   // Vampire (linha 3010)
   ratio = (luckLevel / (6.03 + (1.0 + ItemType)/5.0)) * 100;
   
   // Ousters (linha 3022)
   ratio = (luckLevel / (4.936 + (1.0 + ItemType)/5.0)) * 100;
   ```
   - **Resultado:** Se `rand()%10000 < ratio`, item é upgradeado

2. **Upgrade de Opções** (`upgradeOptionByLuck`)
   - **Localização:** `MonsterManager.cpp` linha 3066-3155
   - **Função:** Melhora o nível/grade da opção existente
   - **Fórmula:** Varia por raça/classe e grade da opção
   ```cpp
   // Slayer (linha 3091)
   ratio = (luckLevel / (grade*25.0 - 15.2)) * 100;
   
   // Vampire (linha 3103)
   ratio = (luckLevel / (grade*25.0 - 11.3)) * 100;
   
   // Ousters (linha 3115)
   ratio = (luckLevel / (grade/25.0 - 13.7)) * 100;
   ```
   - **Resultado:** Se `rand()%10000 < ratio`, opção é upgradeada para nível superior

**Variação aleatória:**
- Antes de usar luck, adiciona variação: `luckLevel = luckLevel + (rand()%20) - 10`
- Isso adiciona -10 a +10 de variação aleatória

**Multiplicadores de evento:**
- `DOUBLE_LUCKY_EVENT`: `luckLevel *= 2` (linha 2447)
- `TIME_PERIOD_LUCK_UP`: `luckLevel *= 2` (linha 2449)

---

## Sistema de OptionClass e OptionGroup

### OptionClass

**Definição:** Tipo específico de atributo (ex: STR, DEX, MP, HP)

**Localização:** `OptionInfo.h` linhas 31-73

**Exemplos:**
- `OPTION_STR` = Força
- `OPTION_DEX` = Destreza
- `OPTION_MP` = Mana Points
- `OPTION_HP` = Health Points
- `OPTION_LUCK` = Sorte
- etc.

**Regra:** Um item **não pode ter dois atributos da mesma OptionClass**

**Verificação:** `ItemUtil.cpp` linha 1205-1234 (`hasOptionClass`)
```cpp
bool hasOptionClass(const list<OptionType_t>& optionTypes, OptionType_t optionType)
{
    OptionClass newOptionClass = pOptionInfo->getClass();
    
    for (auto existingOption : optionTypes)
    {
        if (pExistingOption->getClass() == newOptionClass)
            return true;  // Conflito - mesma OptionClass
    }
    return false;
}
```

### OptionGroup

**Definição:** Grupo de atributos relacionados

**Localização:** `OptionInfo.h` linhas 119-127

**Grupos:**
- `OPTION_GROUP_ATTR` = Atributos básicos (STR, DEX, INT)
- `OPTION_GROUP_STAT` = Estatísticas (HP, MP, HP_STEAL, MP_STEAL, HP_REGEN, MP_REGEN)
- `OPTION_GROUP_SPECIAL` = Opções especiais
- `OPTION_GROUP_RESIST` = Resistências (POISON, ACID, CURSE, BLOOD)
- `OPTION_GROUP_ETC` = Outros
- `OPTION_GROUP_NOT` = Sem grupo

**Uso atual:** OptionGroup é armazenado mas **não é usado** na verificação de conflitos

**Carregamento:** `OptionInfo.cpp` linha 709 - Carregado do banco de dados (`OptionClassInfo`)

---

## Como Impedir MP e HP no Mesmo Item

### Situação Atual

**MP e HP podem aparecer juntos** porque:
- São `OptionClass` diferentes (`OPTION_MP` vs `OPTION_HP`)
- A verificação atual (`hasOptionClass`) só impede mesma `OptionClass`
- Ambos estão no mesmo `OptionGroup` (`OPTION_GROUP_STAT`), mas isso não é verificado

### Solução 1: Modificar hasOptionClass (Recomendado)

**Arquivo:** `ItemUtil.cpp` linha 1205

**Modificação:**
```cpp
bool hasOptionClass(const list<OptionType_t>& optionTypes, OptionType_t optionType)
{
    if (optionTypes.empty())
        return false;

    try {
        OptionInfo* pNewOptionInfo = g_pOptionInfoManager->getOptionInfo( optionType );
        if (pNewOptionInfo==NULL)
            return false;

        OptionClass newOptionClass = pNewOptionInfo->getClass();
        OptionGroup newOptionGroup = pNewOptionInfo->getOptionGroup();
            
        list<OptionType_t>::const_iterator itr;

        for (itr=optionTypes.begin(); itr!=optionTypes.end(); itr++)
        {
            OptionInfo* pExistingOptionInfo = g_pOptionInfoManager->getOptionInfo( *itr );
            if (pExistingOptionInfo==NULL) return false;
            
            // Verificação existente: mesma OptionClass
            if (pExistingOptionInfo->getClass()==newOptionClass)
                return true;
            
            // NOVA VERIFICAÇÃO: Impedir MP e HP juntos
            if (newOptionGroup == OPTION_GROUP_STAT && 
                pExistingOptionInfo->getOptionGroup() == OPTION_GROUP_STAT)
            {
                // Verificar se é MP e HP (ou vice-versa)
                if ((newOptionClass == OPTION_MP && 
                     pExistingOptionInfo->getClass() == OPTION_HP) ||
                    (newOptionClass == OPTION_HP && 
                     pExistingOptionInfo->getClass() == OPTION_MP))
                {
                    return true;  // Conflito - MP e HP não podem estar juntos
                }
            }
        }
    } catch (Throwable& t) {
        filelog("hasOptionClassBug.txt", "%s", t.toString().c_str());
    }

    return false;
}
```

### Solução 2: Modificar getRandomOption

**Arquivo:** `Treasure.cpp` linha 286

**Modificação:** Adicionar verificação antes de adicionar atributo (linha 326-330)
```cpp
if (pTOT->getOptionType()!=0)
{
    // Verificação existente: hasOptionClass
    if (hasOptionClass( pTemplate->OptionType, pTOT->getOptionType() ))
    {
        return true;
    }
    
    // NOVA VERIFICAÇÃO: Impedir MP e HP juntos
    OptionInfo* pNewOption = g_pOptionInfoManager->getOptionInfo(pTOT->getOptionType());
    bool canAdd = true;
    
    for (auto existingOption : pTemplate->OptionType)
    {
        OptionInfo* pExisting = g_pOptionInfoManager->getOptionInfo(existingOption);
        
        // Impedir MP e HP juntos
        if ((pNewOption->getClass() == OPTION_MP && 
             pExisting->getClass() == OPTION_HP) ||
            (pNewOption->getClass() == OPTION_HP && 
             pExisting->getClass() == OPTION_MP))
        {
            canAdd = false;
            break;
        }
    }
    
    if (canAdd)
    {
        pTemplate->OptionType.push_back( pTOT->getOptionType() );
    }
}
```

### Solução 3: Modificar OptionGroup no Banco de Dados

**Arquivo:** Banco de dados - Tabela `OptionClassInfo`

**Coluna:** `OptionGroup`

**Modificação:**
- Separar MP e HP em grupos diferentes
- Exemplo: MP em `OPTION_GROUP_STAT_MP`, HP em `OPTION_GROUP_STAT_HP`
- Modificar `hasOptionClass` para verificar OptionGroup também

**Carregamento:** `OptionInfo.cpp` linha 709

---

## Fluxo Completo de Geração de Item

### 1. Monstro é Derrotado

**Arquivo:** `MonsterManager.cpp` linha 2439

**Processo:**
```cpp
// 1. Obter luck do player que derrotou o monstro
int luckLevel = pItemOwnerCreature->getLuck();

// 2. Aplicar multiplicadores de evento
if (DOUBLE_LUCKY_EVENT) luckLevel *= 2;
if (TIME_PERIOD_LUCK_UP) luckLevel *= 2;

// 3. Obter lista de tesouros do monstro
TreasureList* pTreasureList = pMonsterInfo->getSlayerTreasureList(); // ou Vampire/Ousters
```

### 2. Seleção de Item

**Arquivo:** `Treasure.cpp` linha 819

**Processo:**
```cpp
// 1. Verificar se item será dropado
int ItemRatio = rand()%TREASURE_RATIO_MODULUS;
if (ItemRatio < m_ItemRatio * EventMultiplier)
{
    // 2. Verificar se item terá atributo
    int OptionRatio = rand()%TREASURE_RATIO_MODULUS;
    if (OptionRatio < m_OptionRatio)
        pTemplate->bCreateOption = true;
    
    // 3. Selecionar classe de item
    int itemClassRatio = rand()%m_ItemClassTotalRatio;
    // ... seleciona TreasureItemClass ...
    
    // 4. Selecionar tipo de item
    // ... chama TreasureItemClass::getRandomItem() ...
}
```

### 3. Geração de Atributos

**Arquivo:** `Treasure.cpp` linha 286 (`getRandomOption`)

**Processo:**
```cpp
// Loop para até 2 atributos
for (int k=0; k<2; k++)
{
    // 1. Selecionar atributo aleatório
    int optionRatio = rand()%m_OptionTypeTotalRatio;
    // ... seleciona TreasureOptionType ...
    
    // 2. Verificar conflito (mesma OptionClass)
    if (hasOptionClass(pTemplate->OptionType, newOptionType))
        return true;  // Já existe, não adiciona
    
    // 3. Adicionar atributo
    pTemplate->OptionType.push_back(newOptionType);
    
    // 4. Verificar se pode adicionar mais um
    if (!isPossibleNextOption(pTemplate))
        break;  // Não pode adicionar mais
}
```

### 4. Aplicação de Luck (Upgrade)

**Arquivo:** `MonsterManager.cpp` linha 2549-2581

**Processo:**
```cpp
// 1. Upgrade de tipo de item
int upgradeLevel = upgradeItemTypeByLuck(luckLevel, ownerCreatureClass, it);
// Se upgradeLevel > 0: item melhorado
// Se upgradeLevel < 0: item piorado (luck negativo)

// 2. Upgrade de opções (se item tem atributos)
if (!it.OptionType.empty())
{
    upgradeOptionByLuck(luckLevel, ownerCreatureClass, it);
    // Melhora o nível/grade da opção existente
}
```

### 5. Criação do Item

**Arquivo:** `MonsterManager.cpp` linha 2601

**Processo:**
```cpp
// 1. Criar item com tipo e atributos
pItem = g_pItemFactoryManager->createItem(
    it.ItemClass, 
    it.ItemType, 
    it.OptionType
);

// 2. Definir grade do item
if (pItem->isUnique()) 
    pItem->setGrade(6);
else 
    pItem->setGrade(ItemGradeManager::Instance().getRandomGrade());

// 3. Definir durabilidade
pItem->setDurability(computeMaxDurability(pItem));

// 4. Adicionar ao corpse do monstro
pMonsterCorpse->addTreasure(pItem);
```

---

## Arquivos Relevantes

### Geração de Itens
- `server\gameserver\MonsterManager.cpp` - Geração principal (linhas 2439-2670)
- `server\gameserver\Treasure.cpp` - Seleção de itens e atributos (linhas 286-363, 819-889)
- `server\gameserver\Treasure.h` - Definições de estruturas

### Cálculo de Luck
- `server\gameserver\MonsterManager.cpp` - `upgradeItemTypeByLuck()` (linha 2977)
- `server\gameserver\MonsterManager.cpp` - `upgradeOptionByLuck()` (linha 3066)
- `server\gameserver\LuckInfo.h` - `MAX_LUCK_LEVEL` (linha 14)

### Verificação de Atributos
- `server\gameserver\ItemUtil.cpp` - `hasOptionClass()` (linha 1205)
- `server\gameserver\ItemUtil.cpp` - `isPossibleNextOption()` (linha 1341)
- `server\gameserver\OptionInfo.h` - Definições de `OptionClass` e `OptionGroup`
- `server\gameserver\OptionInfo.cpp` - Carregamento de opções do banco

### Definições de Opções
- `server\gameserver\OptionInfo.h` - Enum `OptionClass` (linhas 31-73)
- `server\gameserver\OptionInfo.h` - Enum `OptionGroup` (linhas 119-127)
- `server\gameserver\OptionInfo.cpp` - `getPossibleOptionVector()` (linha 982)

---

## Resumo de Limites e Regras

### Limites Definidos em Código

1. **MAX_LUCK_LEVEL = 140**
   - Limite para `luckLevel` usado em cálculos de upgrade
   - Localização: `LuckInfo.h` linha 14

2. **Máximo 2 atributos por item**
   - Localização: `ItemUtil.cpp` linha 1344
   - Não depende de luck

3. **Atributos da mesma OptionClass não podem aparecer juntos**
   - Verificação: `hasOptionClass()` em `ItemUtil.cpp` linha 1205

### O que Luck Afeta

1. **Upgrade de tipo de item** - Melhora o tipo (ex: tipo 1 → tipo 2)
2. **Upgrade de opções** - Melhora o nível/grade da opção existente
3. **NÃO afeta quantidade de atributos** - Sempre máximo 2
4. **NÃO afeta quais atributos podem aparecer** - Definido por classe de item

### Regras de Atributos

1. **Primeiro atributo:** Baseado em `m_OptionRatio` do Treasure
2. **Segundo atributo:** Baseado em `NextOptionRatio` (item + primeiro atributo)
3. **Conflitos:** Mesma `OptionClass` não pode aparecer duas vezes
4. **MP e HP:** Atualmente podem aparecer juntos (mesma `OptionGroup` mas `OptionClass` diferente)

---

## Para Modificar o Sistema

### 1. Alterar Limite de Luck

**Arquivo:** `LuckInfo.h` linha 14
```cpp
const int MAX_LUCK_LEVEL = 200;  // Aumentar de 140 para 200
```

### 2. Alterar Quantidade Máxima de Atributos

**Arquivo:** `ItemUtil.cpp` linha 1344
```cpp
// Mudar de 2 para 3
if (pTemplate->OptionType.size()>=3)  // Era >=2
    return false;
```

**Também modificar:** `Treasure.cpp` linha 298
```cpp
// Aumentar loop para permitir 3 atributos
for (int k=0; k<3; k++)  // Era k<2
```

### 3. Impedir MP e HP Juntos

Ver seção "Como Impedir MP e HP no Mesmo Item" acima.

### 4. Modificar Fórmulas de Upgrade por Luck

**Arquivo:** `MonsterManager.cpp`

**Upgrade de tipo:**
- Linha 2998 (Slayer)
- Linha 3010 (Vampire)
- Linha 3022 (Ousters)

**Upgrade de opções:**
- Linha 3091 (Slayer)
- Linha 3103 (Vampire)
- Linha 3115 (Ousters)

### 5. Modificar Probabilidade de Atributos

**Arquivo:** Banco de dados ou arquivos de configuração Treasure

**Valores:**
- `m_OptionRatio` - Probabilidade de item ter atributo
- `NextOptionRatio` - Probabilidade de segundo atributo (por item e por opção)
- `RareItemRatio` - Multiplicador global (variável)

---

## Exemplo de Fluxo Completo

### Cenário: Player com Luck 50 derrota um monstro

1. **Obter luck:**
   ```
   luckLevel = 50
   ```

2. **Aplicar variação aleatória:**
   ```
   luckLevel = 50 + (rand()%20) - 10  // Resultado: 45-65
   luckLevel = min(140, luckLevel)     // Limita a 140
   ```

3. **Selecionar item:**
   ```
   ItemRatio = rand()%10000
   if (ItemRatio < m_ItemRatio) {
       // Item será dropado
   }
   ```

4. **Verificar atributo:**
   ```
   OptionRatio = rand()%10000
   if (OptionRatio < m_OptionRatio) {
       bCreateOption = true  // Item terá atributo
   }
   ```

5. **Gerar primeiro atributo:**
   ```
   optionRatio = rand()%m_OptionTypeTotalRatio
   // Seleciona aleatoriamente (ex: OPTION_STR)
   OptionType.push_back(OPTION_STR)
   ```

6. **Verificar segundo atributo:**
   ```
   if (isPossibleNextOption()) {
       // Calcula probabilidade baseada em NextOptionRatio
       if (rand()%1000000 < nextOptionRatio) {
           // Seleciona segundo atributo (ex: OPTION_DEX)
           OptionType.push_back(OPTION_DEX)
       }
   }
   ```

7. **Aplicar luck (upgrade tipo):**
   ```
   ratio = (luckLevel / (4.254 + (1.0 + ItemType)/5.0)) * 100
   if (rand()%10000 < ratio) {
       ItemType = getUpgradeItemType(ItemClass, ItemType, 1)
       // Item melhorado!
   }
   ```

8. **Aplicar luck (upgrade opções):**
   ```
   ratio = (luckLevel / (grade*25.0 - 15.2)) * 100
   if (rand()%10000 < ratio) {
       OptionType[0] = getUpgradeType(OptionType[0])
       // Opção melhorada!
   }
   ```

9. **Criar item:**
   ```
   pItem = createItem(ItemClass, ItemType, OptionType)
   pItem->setGrade(randomGrade())
   pItem->setDurability(computeMaxDurability())
   ```

---

## Notas Importantes

1. **Luck não garante itens melhores**
   - Apenas aumenta **probabilidade** de upgrade
   - Valores altos de luck aumentam a chance, mas não garantem sucesso

2. **Quantidade de atributos é fixa**
   - Sempre máximo 2, independente de luck
   - Luck apenas melhora a qualidade dos atributos existentes

3. **MP e HP podem aparecer juntos**
   - São `OptionClass` diferentes
   - Para impedir, é necessário modificar código (ver seção específica)

4. **Variação aleatória em luck**
   - Luck tem variação de -10 a +10 antes de usar
   - Isso adiciona aleatoriedade mesmo com luck fixo

5. **Multiplicadores de evento**
   - `DOUBLE_LUCKY_EVENT` e `TIME_PERIOD_LUCK_UP` dobram luck
   - Aplicados antes de usar em cálculos

---

## Conclusão

O sistema de geração de itens é complexo e envolve múltiplas etapas:
- Seleção de item baseada em Treasure
- Geração de atributos (máximo 2)
- Aplicação de luck para upgrades
- Verificação de conflitos entre atributos

**Principais pontos:**
- Luck máximo: 140 (código)
- Atributos máximo: 2 (código)
- Luck afeta upgrade, não quantidade
- MP e HP podem aparecer juntos (modificável)

Para modificar o sistema, é necessário alterar código do servidor e possivelmente banco de dados (para OptionGroup).
