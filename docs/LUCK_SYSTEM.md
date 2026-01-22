# Sistema de Luck (Sorte) - Cliente e Servidor

## Visão Geral

O sistema de `luck` (sorte) controla a **probabilidade de loot** - chances de obter itens melhores ao derrotar monstros. Diferente de `vision`, `luck` é um atributo **puramente calculado no servidor** e usado apenas para **exibição no cliente**. O cliente não processa `luck` localmente para cálculos de loot.

---

## Conceitos Importantes

### 1. Luck como Atributo (MODIFY_LUCK)

**Tipo:** `short` (Luck_t) - Enviado via `addShortData(MODIFY_LUCK, value)` no servidor
- No cliente: Armazenado em `MStatus::m_Status[MODIFY_LUCK]` como `DWORD` para compatibilidade

**Função:** Representa o **valor total de luck** do personagem, calculado no servidor

**Fonte:** Calculado no **servidor**, enviado via packet `GCModifyInformation` com tipo `MODIFY_LUCK`

**Uso no cliente:**
- Apenas **exibição na UI** (`g_char_slot_ingame.luck`)
- **Não afeta cálculos locais** de loot ou drop

### 2. Luck em Itens (PART_LUCK)

**Tipo:** Opção de item (`ITEMOPTION_TABLE::PART_LUCK`)

**Função:** Bônus de luck que um item fornece

**Processamento:**
- **Servidor:** Calcula o bônus total de todos os itens com `PART_LUCK` e inclui no cálculo final de `MODIFY_LUCK`
- **Cliente:** Apenas **exibe o nome da opção** no item (ex: "Luck +5"), mas **não processa o valor**

**Diferença importante:**
- `PART_LUCK` em itens é **apenas informativo no cliente**
- O servidor deve somar todos os bônus de `PART_LUCK` e enviar o total via `MODIFY_LUCK`
- O cliente não calcula luck localmente baseado em itens

### 3. Base Luck (m_BaseLuck)

**Tipo:** `Luck_t` (short)

**Função:** Luck base do personagem, inicializado como `0` por padrão

**Modificadores:**
- **Luck Charm (Item tipo 30):** Define `m_BaseLuck = 10` quando equipado
  - Localização: `EventItem.cpp` linhas 352, 385, 408
  - Aplicado quando item é equipado em `STORAGE_INVENTORY`, `STORAGE_EXTRASLOT`, ou `STORAGE_STASH`

**Nota:** "Lucky Extra" não existe como atributo separado. O que pode ser confundido são os **bônus de Rank** (RankBonus) que também afetam luck.

---

## Como Luck Funciona no Cliente

### 1. Recebimento do Valor do Servidor

**Packet:** `GCModifyInformation` com tipo `MODIFY_LUCK`

**Handler:** `GCModifyInformationHandler::execute()`
```cpp
// PacketFunction.cpp linha 28
AffectModifyInfo(g_pPlayer, pPacket);
```

**Processamento:** `AffectModifyInfo()` → `ModifyStatusManager::Function_MODIFY_LUCK()`
```cpp
// ModifyStatusManager.cpp linhas 1548-1554
void ModifyStatusManager::Function_MODIFY_LUCK(void *pVoid)
{
    EXTRACT_MODIFY_VALUE( pVoid )
    
    // Apenas atualiza a UI - não afeta cálculos locais
    UI_SetCharInfoLuck( value );
}
```

**Atualização da UI:**
```cpp
// GameUI.cpp linha 1338
void UI_SetCharInfoLuck(int value)
{
    g_char_slot_ingame.luck = value;
}
```

### 2. Exibição na Interface

**Arquivo:** `VS_UI_GameCommon.cpp` linha 3645
```cpp
wsprintf(sz_Luck,"%d",g_char_slot_ingame.luck);
// ... renderiza na tela ...
g_PrintColorStr(x+realAttrWith4, y+30+20+23+13+22+22+22+22+15+22+2+15*3, sz_Luck, ...);
```

O valor é exibido na interface do jogo para o player ver seu luck atual.

### 3. Exibição de Opções de Itens (PART_LUCK)

**Arquivo:** `MItem.cpp` linhas 4917-4920, 4966-4969

Quando um item tem a opção `PART_LUCK`, o cliente exibe o nome da opção:
```cpp
case ITEMOPTION_TABLE::PART_LUCK:
    petOptionName = (*g_pGameStringTable)[STRING_MESSAGE_OPTION_NAME_LUCK_3+optionLevel].GetString();
    petOptionName += " ";
    break;
```

**Importante:** O cliente **não processa** o valor de `PART_LUCK` para calcular luck total. Apenas exibe que o item tem a opção.

---

## Diferença: MODIFY_LUCK vs PART_LUCK vs BaseLuck

### MODIFY_LUCK - Atributo Total
- **Calculado no servidor**
- **Enviado via:** `GCModifyInformation` com `MODIFY_LUCK`
- **Armazenado em:** `MStatus::m_Status[MODIFY_LUCK]` (DWORD no cliente)
- **Usado para:**
  - Exibição na UI
  - Cálculo de loot no servidor (não no cliente)

### PART_LUCK - Opção de Item
- **Definido em itens** como opção
- **Processado no servidor** (somado ao luck total)
- **Exibido no cliente** apenas como nome da opção
- **Não processado no cliente** para cálculos

### BaseLuck (m_BaseLuck)
- **Luck base** do personagem (inicial = 0)
- **Modificado por:** Luck Charm (item tipo 30) → define para 10
- **Processado no servidor** e incluído no cálculo total

**Resumo:**
- `BaseLuck` = Luck **base** do personagem (0, ou 10 com Luck Charm)
- `PART_LUCK` = Bônus de luck que um item **dá** (processado no servidor)
- `MODIFY_LUCK` = Luck **total** do personagem (vem do servidor, exibido no cliente)

---

## Como o Servidor Calcula Luck (Implementação Real)

### Cálculo no Servidor

**Arquivo:** `InitAllStat.cpp`

O servidor calcula luck da seguinte forma:

1. **Inicialização:**
   ```cpp
   // InitAllStat.cpp linha 354
   m_Luck = m_BaseLuck;  // Inicializa com luck base (0, ou 10 se tiver Luck Charm)
   ```

2. **Bônus de Itens:**
   ```cpp
   // InitAllStat.cpp linha 2447, 4652, 7232
   m_Luck += pItem->getLuck();  // Soma luck de cada item equipado
   ```

3. **Opções de Itens (OPTION_LUCK):**
   ```cpp
   // InitAllStat.cpp linha 2659, 4861, 7437
   case OPTION_LUCK:
       m_Luck += PlusPoint;  // Soma bônus de opções de luck
       break;
   ```

4. **Bônus de Rank:**
   ```cpp
   // InitAllStat.cpp linha 1881 (RANK_BONUS_FORTUNE_HAND)
   // InitAllStat.cpp linha 6477 (RANK_BONUS_MYSTIC_RULE)
   int LuckBonus = pRankBonus->getPoint();
   m_Luck += LuckBonus;
   ```

5. **Bônus de Party Aura:**
   ```cpp
   // InitAllStat.cpp linha 1337
   if ( pPartyAura->isLuck() )
   {
       Luck_t amount = (Luck_t)( ( 28 + ( level / 10 ) ) / ( 1.0 + ( 0.2 * partySize ) ) );
       m_Luck += amount;
   }
   ```

6. **Envio ao Cliente:**
   ```cpp
   // InitAllStat.cpp linha 3043, 5077, 7663
   if (prev.Luck != m_Luck)
   {
       pkt.addShortData(MODIFY_LUCK, m_Luck);
   }
   ```

### Packet que o Servidor Envia

**Packet:** `GCModifyInformation`
- **Tipo:** `MODIFY_LUCK`
- **Valor:** `short` (Luck_t) enviado via `addShortData()`

**Estrutura do packet:**
```cpp
// Servidor (InitAllStat.cpp)
GCModifyInformation pkt;
pkt.addShortData(MODIFY_LUCK, m_Luck);  // short (Luck_t)
```

### Quando o Servidor Envia

O servidor envia `MODIFY_LUCK` quando:
1. **Player faz login** - Durante `InitAllStat()` (linha 3043)
2. **Player equipa/desequipa item** - Recalcula e envia se mudou (linha 5077)
3. **Player muda de classe** - Recalcula e envia (linha 7663)
4. **Qualquer mudança** que altere `m_Luck` e seja diferente de `prev.Luck`

---

## O que Mudar no Servidor para Alterar Padrões

### 1. Cálculo Base de Luck

**Onde alterar:** `InitAllStat.cpp` linha 354

**O que alterar:**
- Valor inicial de `m_BaseLuck` (atualmente 0)
- Valores por raça/classe/nível

**Exemplo:**
```cpp
// Servidor (InitAllStat.cpp)
// Atualmente:
m_Luck = m_BaseLuck;  // 0 por padrão

// Para modificar:
m_Luck = m_BaseLuck + GetBaseLuckByRace(pPlayer->GetRace());
```

### 2. Luck Charm (Item tipo 30)

**Onde alterar:** `EventItem.cpp` linhas 352, 385, 408

**O que alterar:**
- Valor que Luck Charm define (atualmente 10)
- Condições para aplicar o bônus

**Exemplo:**
```cpp
// Servidor (EventItem.cpp)
// Atualmente:
if ( itemType == 30 ) pPC->setBaseLuck(10);

// Para modificar:
if ( itemType == 30 ) pPC->setBaseLuck(15);  // Aumentar para 15
```

### 3. Bônus de Itens (getLuck())

**Onde alterar:** Sistema de itens do servidor

**O que alterar:**
- Valores de `getLuck()` em itens
- Fórmulas de cálculo baseadas em grade/encantamento

**Arquivos relevantes:**
- `Item.h` linha 766 - `virtual Luck_t getLuck() const { return 0; }`
- `ConcreteItem.h` linha 93 - `Luck_t getLuck() const { return m_Grade.getLuck(); }`
- `ItemPolicies.h` linha 234 - `Luck_t getLuck() const { return (getValue()-4); }`

### 4. Opções de Itens (OPTION_LUCK)

**Onde alterar:** `InitAllStat.cpp` linhas 2659, 4861, 7437

**O que alterar:**
- Valores de `PlusPoint` para `OPTION_LUCK`
- Fórmulas de cálculo de bônus

**Exemplo:**
```cpp
// Servidor (InitAllStat.cpp)
case OPTION_LUCK:
    m_Luck += PlusPoint;  // PlusPoint vem de OptionInfo
    break;
```

### 5. Bônus de Rank

**Onde alterar:** `InitAllStat.cpp` linhas 1875-1881, 6470-6477

**O que alterar:**
- Valores de bônus de rank
- Quais ranks dão bônus de luck

**Ranks que afetam luck:**
- `RANK_BONUS_FORTUNE_HAND` (linha 1876)
- `RANK_BONUS_MYSTIC_RULE` (linha 6472)
- Outros ranks podem existir

### 6. Bônus de Party Aura

**Onde alterar:** `InitAllStat.cpp` linha 1334-1338

**O que alterar:**
- Fórmula de cálculo do bônus
- Valores base e por nível

**Fórmula atual:**
```cpp
// Servidor (InitAllStat.cpp)
Luck_t amount = (Luck_t)( ( 28 + ( level / 10 ) ) / ( 1.0 + ( 0.2 * partySize ) ) );
```

**Explicação:**
- Base: 28 + (level / 10)
- Dividido por: 1.0 + (0.2 * tamanho da party)
- Quanto maior a party, menor o bônus individual

---

## Resumo: Fluxo Completo

### Servidor → Cliente

1. **Servidor inicializa:**
   - `m_Luck = m_BaseLuck` (0, ou 10 com Luck Charm)
   
2. **Servidor calcula luck total:**
   - `+ pItem->getLuck()` (bônus de itens)
   - `+ OPTION_LUCK` (opções de itens)
   - `+ RankBonus` (bônus de rank)
   - `+ PartyAura` (bônus de party se `isLuck()` ativo)
   
3. **Servidor envia packet:**
   - `GCModifyInformation` com `addShortData(MODIFY_LUCK, m_Luck)`
   
4. **Cliente recebe e processa:**
   - `GCModifyInformationHandler` → `AffectModifyInfo()` → `Function_MODIFY_LUCK()`
   
5. **Cliente atualiza:**
   - `UI_SetCharInfoLuck(value)` → `g_char_slot_ingame.luck = value`
   
6. **Cliente exibe:**
   - Valor é renderizado na interface do jogo

### Servidor (Cálculo de Loot)

1. **Servidor calcula luck total** (mesmo processo acima)

2. **Servidor usa luck em cálculos de loot:**
   - Ao derrotar monstro, usa `getLuck()` para:
     - Aumentar chance de drop
     - Aumentar qualidade de itens
     - Aumentar quantidade de itens
     - Desbloquear drops especiais

3. **Servidor envia itens dropados:**
   - Player recebe itens baseados no luck calculado

---

## Arquivos Relevantes

### Servidor

**Cálculo de Luck:**
- `server\gameserver\InitAllStat.cpp` - Cálculo principal de luck (linhas 354, 2447, 2659, 3043, etc.)
- `server\gameserver\PlayerCreature.h` - Definição de `m_BaseLuck` (linha 636)
- `server\gameserver\item\EventItem.cpp` - Luck Charm (linhas 352, 385, 408)
- `server\gameserver\Item.h` - Interface `getLuck()` (linha 766)
- `server\gameserver\ConcreteItem.h` - Implementação `getLuck()` (linha 93)
- `server\gameserver\OptionInfo.h` - Definição de `OPTION_LUCK` (linha 54)

**Packets:**
- `Core\ModifyInfo.h` - Definição de `MODIFY_LUCK` (linha 115)

### Cliente

**Processamento de Packets:**
- `Client\Packet\Gpackets\GCModifyInformationHandler.cpp` - Handler do packet
- `Client\PacketFunction.cpp` - `AffectModifyInfo()` função que processa valores
- `Client\ModifyStatusManager.cpp` - `Function_MODIFY_LUCK()` atualiza valores

**UI:**
- `Client\GameUI.cpp` - `UI_SetCharInfoLuck()` atualiza valor na UI
- `NEW - VS_UI\src\VS_UI_GameCommon.cpp` - Exibe valor na interface (linha 3645)
- `NEW - VS_UI\src\header\VS_UI_title.h` / `VS_UI_Newtitle.h` - Struct `S_SLOT` com campo `luck`

**Itens:**
- `Client\MItem.cpp` - Exibe nome da opção `PART_LUCK` em itens (linhas 4917, 4966)
- `Client\MItemOptionTable.h` - Definição de `PART_LUCK` enum (linha 93)

**Definições:**
- `Client\Packet\Types\ModifyDef.h` - `MODIFY_LUCK` enum (linha 118)
- `Client\MStatus.h` - `GetLuck()` método (linha 129)
- `Client\Packet\Types\CreatureTypes.h` - `Luck_t` typedef (short, linha 564)

---

## Notas Importantes

1. **`PART_LUCK` em itens não é processado no cliente**
   - O cliente apenas **exibe** que o item tem a opção
   - O servidor deve **somar todos os bônus** e enviar o total via `MODIFY_LUCK`
   - Diferente de `PART_VISION` que afeta `LightSight` no cliente, `PART_LUCK` não tem processamento local

2. **Luck não afeta cálculos no cliente**
   - O cliente **não calcula loot** localmente
   - Luck é **apenas exibido** na UI
   - Todos os cálculos de loot são feitos no **servidor**

3. **Tipo de dados:**
   - `MODIFY_LUCK` usa `short` (Luck_t) no servidor
   - Enviado via `addShortData()` no servidor
   - No cliente, armazenado como `DWORD` em `MStatus::m_Status[MODIFY_LUCK]` para compatibilidade

4. **BaseLuck vs MODIFY_LUCK:**
   - `BaseLuck` (m_BaseLuck) = Luck base do personagem (0, ou 10 com Luck Charm)
   - `MODIFY_LUCK` = Luck total calculado (BaseLuck + itens + opções + rank + party)

5. **"Lucky Extra" não existe:**
   - Não há atributo separado chamado "Lucky Extra"
   - O que pode ser confundido são os bônus de Rank (RankBonus) que também afetam luck

---

## Conclusão

O sistema de `luck` é **calculado exclusivamente no servidor** e usado para:
- **Cálculo de loot** (chances de drop, qualidade, quantidade)
- **Exibição no cliente** (valor mostrado na UI)

Diferente de `vision`, `luck` **não afeta renderização ou processamento visual** no cliente. É um atributo puramente relacionado a **mecânicas de jogo** (loot) que são processadas no servidor.

Para alterar padrões, é necessário modificar:
1. **Cálculo no servidor** (`InitAllStat.cpp`) - valores base, bônus, limites
2. **Fórmulas de loot** (como luck afeta drops) - no sistema de loot do servidor
3. **Garantir envio correto** via `MODIFY_LUCK` packet - já implementado no código
