# Sistema de Vision (Sight) - Cliente e Servidor

## Visão Geral

O sistema de `vision` (também chamado de `Sight` no código) controla o **alcance de visão** do player no cliente, determinando quais objetos são renderizados na tela e o alcance do filtro de iluminação (dia/noite).

---

## Conceitos Importantes

### 1. Sight (Vision) vs LightSight

**Sight (`m_Sight`, `g_char_slot_ingame.vision`):**
- **Tipo:** `char` (BYTE)
- **Função:** Controla o **alcance de visão** - quais objetos são mantidos na zona e renderizados
- **Fonte:** Calculado no **servidor**, enviado via packet `MODIFY_VISION`
- **Uso no cliente:**
  - `KeepObjectInSight()` - Remove objetos fora do alcance
  - `AddLightFilter2D/3D()` - Limita range do filtro de luz (`GetSight()-3`)

**LightSight (`m_LightSight`):**
- **Tipo:** `int`
- **Função:** Controla a **iluminação** - quanto de luz o player tem (afeta escuridão/clareza)
- **Fonte:** Calculado no **cliente** baseado em:
  - `m_TimeLightSight` (hora do dia, vem do servidor via `GCChangeDarkLight`)
  - `m_ItemLightSight` (bônus de itens com `PART_VISION`, calculado no cliente)
  - Skills e efeitos de status

**Resumo:**
- `Sight` = **O que você vê** (alcance de objetos renderizados)
- `LightSight` = **Quanto você vê** (iluminação/clareza)

---

## Como Vision Funciona no Cliente

### 1. Recebimento do Valor do Servidor

**Packet:** `GCModifyInformation` com tipo `MODIFY_VISION`

**Handler:** `GCModifyInformationHandler::execute()`
```cpp
// PacketFunction.cpp linha 28
AffectModifyInfo(g_pPlayer, pPacket);
```

**Processamento:** `AffectModifyInfo()` → `ModifyStatusManager::Function_MODIFY_VISION()`
```cpp
// ModifyStatusManager.cpp linhas 554-568
void ModifyStatusManager::Function_MODIFY_VISION(void* pVoid)
{
    EXTRACT_MODIFY_VALUE( pVoid )
    
    // Atualiza o alcance de visão do player
    g_pPlayer->SetSight( value );
    
    // Remove objetos fora do alcance de visão
    g_pZone->KeepObjectInSight(g_pPlayer->GetServerX(), 
                                g_pPlayer->GetServerY(), 
                                g_pPlayer->GetSight());
    
    // Armazena para exibição na UI
    g_char_slot_ingame.vision = value;
}
```

### 2. Controle de Objetos Renderizados

**Função:** `MZone::KeepObjectInSight()`
- **Localização:** `MZone.cpp` linhas 2643-2740
- **Função:** Remove criaturas/objetos que estão fora do alcance de visão
- **Alcance:** Baseado em `NEW_VISION_SECTOR_WIDTH_HALF`, `NEW_VISION_SECTOR_HEIGHT_HALF_UP`, `NEW_VISION_SECTOR_HEIGHT_HALF_DOWN`
- **Lógica:** Objetos fora do retângulo `(sX1, sY1)` a `(sX2, sY2)` são removidos da zona

**Código relevante:**
```cpp
// MZone.cpp linha 2643
void MZone::KeepObjectInSight(TYPE_SECTORPOSITION x, TYPE_SECTORPOSITION y, BYTE sight)
{
    int minX = NEW_VISION_SECTOR_WIDTH_HALF;
    int minY = NEW_VISION_SECTOR_HEIGHT_HALF_UP;
    int minY2 = NEW_VISION_SECTOR_HEIGHT_HALF_DOWN;
    
    int sX1 = x-minX;
    int sY1 = y-minY;
    int sX2 = x+minX;
    int sY2 = y+minY2;
    
    // Remove criaturas fora do retângulo de visão
    // ...
}
```

### 3. Controle do Filtro de Iluminação (Dia/Noite)

**Funções:** `MTopView::AddLightFilter2D()` e `MTopView::AddLightFilter3D()`
- **Localização:** `MTopView.cpp` linhas 11296 e 11372
- **Função:** Aplica filtro de luz na tela (controla escuridão/clareza)
- **Range limitado por:** `g_pPlayer->GetSight()-3`

**Código relevante:**
```cpp
// MTopView.cpp linha 11300 (AddLightFilter2D)
range = min( max(g_pPlayer->GetSight()-3, 0), range );

// MTopView.cpp linha 11376 (AddLightFilter3D)
range = min( max(g_pPlayer->GetSight()-3, 0), range );
```

**Efeito visual:**
- `Sight` maior = área iluminada maior na tela
- `Sight` menor = área iluminada menor (mais escuro nas bordas)
- O filtro de luz é aplicado durante o dia e especialmente à noite

### 4. Exibição na UI

**Arquivo:** `VS_UI_GameCommon.cpp` linha 3646
```cpp
wsprintf(sz_Vis,"%d",g_char_slot_ingame.vision);
```

O valor é exibido na interface do jogo para o player ver seu alcance de visão atual.

---

## Diferença: Vision (Sight) vs LightSight

### Vision (Sight) - Alcance de Visão
- **Calculado no servidor**
- **Enviado via:** `MODIFY_VISION` packet
- **Armazenado em:** `MPlayer::m_Sight` (char)
- **Usado para:**
  - Determinar quais objetos são renderizados (`KeepObjectInSight`)
  - Limitar range do filtro de luz (`GetSight()-3`)

### LightSight - Iluminação
- **Calculado no cliente**
- **Componentes:**
  - `m_TimeLightSight` - Hora do dia (vem do servidor via `GCChangeDarkLight`)
  - `m_ItemLightSight` - Bônus de itens com `PART_VISION` (calculado no cliente)
  - Bônus de skills/efeitos
- **Usado para:**
  - Renderização do filtro de luz (`AddLightFilter2D/3D`)
  - Cálculo de escuridão/clareza na tela

**Nota:** `PART_VISION` em itens afeta `LightSight` (iluminação), **não** `Sight` (alcance). O alcance de visão (`Sight`) é calculado exclusivamente no servidor.

---

## Como o Servidor Calcula Vision (Implementação Real)

### Como o Servidor Funciona

**Arquivo:** `Slayer.cpp`, `Vampire.cpp`, `Ousters.cpp`

O servidor **não calcula** vision dinamicamente. Vision é um **valor fixo** que vem do banco de dados:

1. **Vision base do personagem:**
   - **Slayer:** Fixado em `13` no código (linha 951 de `Slayer.cpp`)
   - **Vampire/Ousters:** Vem do banco de dados via `pResult->getInt(++i)` (linhas 790, 974)

2. **OPTION_VISION em itens:**
   - **NÃO é processado** - Apenas `break` no switch (linha 2627 de `InitAllStat.cpp`)
   - Itens com `OPTION_VISION` **não afetam** o alcance de visão no servidor

3. **Skills que modificam vision:**
   - Skills específicas alteram vision **temporariamente**:
     - **Flare** - Reduz para `FLARE_SIGHT`
     - **Light** - Aumenta temporariamente
     - **Lightness** - Aumenta temporariamente
     - **YellowPoison** - Reduz temporariamente
     - **BloodDrain** - Restaura vision original
     - Outras skills podem modificar vision durante o efeito

4. **ObservingEye skill:**
   - Tem método `getVisionBonus()` mas está **comentado** no código (linha 1425 de `InitAllStat.cpp`)
   - Não afeta vision atualmente, apenas permite ver invisibilidade

### Packet que o Servidor Envia

**Packet:** `GCModifyInformation`
- **Tipo:** `MODIFY_VISION`
- **Valor:** `BYTE` (Vision_t) enviado via `addShortData()`

**Estrutura do packet:**
```cpp
// Servidor (EffectFlare.cpp, EffectLight.cpp, etc.)
GCModifyInformation _GCModifyInformation;
_GCModifyInformation.addShortData(MODIFY_VISION, NewSight);  // BYTE (Vision_t)
pPlayer->sendPacket(&_GCModifyInformation);
```

**Valores fixos por raça:**
- **Slayer:** 13 (fixado no código)
- **Vampire/Ousters:** Vem do banco de dados (variável)

### Quando o Servidor Envia

O servidor envia `MODIFY_VISION` quando:
1. **Skill que modifica vision é ativada/desativada:**
   - **Flare** - Quando ativado/desativado (`EffectFlare.cpp` linhas 102, 126)
   - **Light** - Quando ativado/desativado (`EffectLight.cpp` linha 82)
   - **Lightness** - Quando ativado/desativado (`EffectLightness.cpp` linha 69)
   - **YellowPoison** - Quando aplicado (`EffectYellowPoison.cpp` linha 130)
   - **BloodDrain** - Quando aplicado (`EffectBloodDrain.cpp` linha 109)
   - Outras skills que modificam vision temporariamente

**Nota importante:** O servidor **não envia** `MODIFY_VISION` quando:
- Player faz login (vision inicial não é enviado via MODIFY_VISION)
- Player equipa/desequipa item (OPTION_VISION não é processado)
- Player muda de zona (vision não muda por zona)

---

## O que Mudar no Servidor para Alterar Padrões

### 1. Cálculo Base de Vision

**Onde alterar:** Sistema de cálculo de status do servidor

**O que alterar:**
- Vision base por raça/classe
- Fórmulas de cálculo
- Valores máximos/mínimos

**Exemplo:**
```cpp
// Servidor (pseudocódigo)
BYTE CalculateVision(Player* pPlayer)
{
    BYTE baseVision = GetBaseVision(pPlayer->GetRace(), pPlayer->GetClass());
    BYTE itemVision = CalculateItemVisionBonus(pPlayer);
    BYTE skillVision = CalculateSkillVisionBonus(pPlayer);
    BYTE statusVision = CalculateStatusVisionBonus(pPlayer);
    
    BYTE totalVision = baseVision + itemVision + skillVision + statusVision;
    
    // Limites
    totalVision = min(totalVision, MAX_VISION);
    totalVision = max(totalVision, MIN_VISION);
    
    return totalVision;
}
```

### 2. Bônus de Itens (OPTION_VISION)

**Onde alterar:** `InitAllStat.cpp` linha 2627

**Situação atual:**
- `OPTION_VISION` **não é processado** no servidor
- Apenas `break` no switch, sem adicionar bônus

**Para habilitar bônus de itens:**
```cpp
// Servidor (InitAllStat.cpp)
// Atualmente:
case OPTION_VISION:
    break;  // Não faz nada

// Para habilitar:
case OPTION_VISION:
    // Adicionar lógica para calcular bônus de vision
    // Nota: Vision é BYTE, então precisa de cuidado com overflow
    break;
```

**Nota:** Se habilitar `OPTION_VISION`, será necessário:
1. Calcular vision total incluindo bônus de itens
2. Enviar `MODIFY_VISION` quando itens são equipados/desequipados
3. Garantir que vision não ultrapasse limites (BYTE = 0-255)

### 3. Bônus de Skills

**Onde alterar:** Arquivos de skills específicas

**Skills que modificam vision:**

1. **Flare** (`EffectFlare.cpp`):
   - Reduz vision para `FLARE_SIGHT` quando ativo
   - Restaura vision original quando desativado

2. **Light** (`EffectLight.cpp`):
   - Aumenta vision temporariamente quando ativo
   - Restaura vision original quando desativado

3. **Lightness** (`EffectLightness.cpp`):
   - Aumenta vision temporariamente quando ativo
   - Restaura vision original quando desativado

4. **YellowPoison** (`EffectYellowPoison.cpp`):
   - Reduz vision temporariamente quando aplicado
   - Restaura vision original quando removido

5. **BloodDrain** (`EffectBloodDrain.cpp`):
   - Restaura vision original do alvo

6. **ObservingEye** (`InitAllStat.cpp` linha 1425):
   - Tem `getVisionBonus()` mas está **comentado**
   - Atualmente não afeta vision, apenas permite ver invisibilidade

**Para modificar valores:**
- Editar constantes de vision em cada skill (ex: `FLARE_SIGHT`, etc.)
- Modificar lógica de cálculo em cada `Effect*.cpp`

### 4. Valores Padrão e Limites

**Onde alterar:** 
- `Slayer.cpp` linha 951 - Vision fixo do Slayer
- Banco de dados - Vision de Vampire/Ousters

**Valores atuais:**
- **Slayer:** 13 (fixado no código: `setSight(13);`)
- **Vampire/Ousters:** Vem do banco de dados (variável por personagem)

**Para modificar:**
```cpp
// Servidor (Slayer.cpp)
// Atualmente:
setSight(13);  // Fixo em 13

// Para modificar:
setSight(15);  // Mudar para 15, ou calcular dinamicamente
```

**Limites:**
- Vision é `BYTE` (Vision_t) = 0-255
- Não há limites explícitos no código, mas valores típicos são 5-20

### 5. Envio do Packet

**Onde alterar:** Arquivos de skills que modificam vision

**Implementação atual:**
```cpp
// Servidor (EffectFlare.cpp, EffectLight.cpp, etc.)
GCModifyInformation _GCModifyInformation;
_GCModifyInformation.addShortData(MODIFY_VISION, NewSight);
pPlayer->sendPacket(&_GCModifyInformation);
```

**Arquivos que enviam MODIFY_VISION:**
- `EffectFlare.cpp` - Linhas 102, 126
- `EffectLight.cpp` - Linha 82
- `EffectLightness.cpp` - Linha 69
- `EffectYellowPoison.cpp` - Linha 130
- `EffectYellowPoisonToCreature.cpp` - Linha 72
- `EffectBloodDrain.cpp` - Linha 109
- `EffectFLAMESIGHT.cpp` - Linha 77
- `Light.cpp` - Linhas 95, 222
- `Flare.cpp` - Linha 112

**Nota:** Vision inicial do player **não é enviado** via `MODIFY_VISION` no login. O cliente recebe vision através de outros packets (ex: `GCPlayerInfo`).

---

## Resumo: Fluxo Completo

### Servidor → Cliente

1. **Servidor define vision inicial:**
   - **Slayer:** Fixado em 13 (`Slayer.cpp` linha 951)
   - **Vampire/Ousters:** Vem do banco de dados (`Vampire.cpp` linha 790, `Ousters.cpp` linha 974)
   - Vision inicial **não é enviado** via `MODIFY_VISION` no login
   
2. **Servidor modifica vision temporariamente:**
   - Quando skill é ativada (ex: Flare, Light, etc.)
   - Calcula novo valor de vision
   - Envia `GCModifyInformation` com `addShortData(MODIFY_VISION, NewSight)`
   
3. **Cliente recebe e processa:**
   - `GCModifyInformationHandler` → `AffectModifyInfo()` → `Function_MODIFY_VISION()`
   
4. **Cliente atualiza:**
   - `g_pPlayer->SetSight(value)` - Atualiza alcance
   - `g_pZone->KeepObjectInSight()` - Remove objetos fora do alcance
   - `g_char_slot_ingame.vision = value` - Armazena para UI
   
5. **Cliente renderiza:**
   - Apenas objetos dentro do alcance são renderizados
   - Filtro de luz usa `GetSight()-3` para limitar range

### Cliente (LightSight - Iluminação)

1. **Cliente calcula LightSight:**
   - `m_TimeLightSight` (hora do dia, do servidor)
   - `m_ItemLightSight` (bônus de itens com `PART_VISION`, calculado no cliente)
   - Skills/efeitos locais
   
2. **Cliente renderiza filtro de luz:**
   - `AddLightFilter2D/3D()` usa `GetLightSight()` para iluminação
   - `GetSight()-3` limita o range do filtro

---

## Arquivos Relevantes

### Servidor

**Cálculo e Definição de Vision:**
- `server\gameserver\Slayer.cpp` - Vision fixo do Slayer (linha 951: `setSight(13)`)
- `server\gameserver\Vampire.cpp` - Vision do Vampire do banco (linha 790)
- `server\gameserver\Ousters.cpp` - Vision do Ousters do banco (linha 974)
- `server\gameserver\InitAllStat.cpp` - OPTION_VISION não processado (linha 2627)
- `server\gameserver\OptionInfo.h` - Definição de `OPTION_VISION` (linha 51)

**Skills que Modificam Vision:**
- `server\gameserver\skill\EffectFlare.cpp` - Modifica vision (linhas 102, 126)
- `server\gameserver\skill\EffectLight.cpp` - Modifica vision (linha 82)
- `server\gameserver\skill\EffectLightness.cpp` - Modifica vision (linha 69)
- `server\gameserver\skill\EffectYellowPoison.cpp` - Modifica vision (linha 130)
- `server\gameserver\skill\EffectBloodDrain.cpp` - Modifica vision (linha 109)
- `server\gameserver\skill\Light.cpp` - Modifica vision (linhas 95, 222)
- `server\gameserver\skill\Flare.cpp` - Modifica vision (linha 112)

**Packets:**
- `Core\ModifyInfo.h` - Definição de `MODIFY_VISION` (enum)
- `Core\types\CreatureTypes.h` - `Vision_t` typedef (BYTE, linha 665)

### Cliente

**Processamento de Packets:**
- `Client\Packet\Gpackets\GCModifyInformationHandler.cpp` - Handler do packet
- `Client\PacketFunction.cpp` - `AffectModifyInfo()` função que processa valores
- `Client\ModifyStatusManager.cpp` - `Function_MODIFY_VISION()` atualiza valores

**Renderização:**
- `Client\MZone.cpp` - `KeepObjectInSight()` remove objetos fora do alcance
- `Client\MTopView.cpp` - `AddLightFilter2D/3D()` aplica filtro de luz
- `Client\MPlayer.cpp` - `SetSight()`, `GetSight()`, `CalculateSight()`, `CalculateLightSight()`

**UI:**
- `NEW - VS_UI\src\VS_UI_GameCommon.cpp` - Exibe valor na interface
- `NEW - VS_UI\src\header\VS_UI_title.h` / `VS_UI_Newtitle.h` - Struct `S_SLOT` com campo `vision`

**Definições:**
- `Client\Packet\Types\ModifyDef.h` - `MODIFY_VISION` enum
- `Client\Packet\Types\CreatureTypes.h` - `Sight_t` typedef (BYTE)
- `Client\MItemOptionTable.h` - `PART_VISION` enum (afeta `LightSight`, não `Sight`)

---

## Notas Importantes

1. **`PART_VISION` em itens afeta `LightSight` (iluminação), não `Sight` (alcance)**
   - Itens com `PART_VISION` são processados no cliente via `CalculateSight()` e `CalculateLightSight()`
   - Isso afeta apenas a iluminação, não o alcance de objetos renderizados
   - O alcance (`Sight`) é calculado exclusivamente no servidor
   - **No servidor:** `OPTION_VISION` não é processado (apenas `break` no switch)

2. **`Sight` controla renderização de objetos**
   - Objetos fora do alcance são removidos da zona (`KeepObjectInSight`)
   - Isso economiza memória e processamento no cliente

3. **`Sight` limita filtro de luz**
   - `GetSight()-3` é usado para limitar o range do filtro de iluminação
   - Isso cria o efeito visual de escuridão nas bordas da tela

4. **Valores são independentes**
   - `Sight` (alcance) vem do servidor
   - `LightSight` (iluminação) é calculado no cliente
   - Ambos afetam o que o player vê, mas de formas diferentes

5. **Vision é fixo por raça/classe**
   - **Slayer:** Sempre 13 (fixado no código)
   - **Vampire/Ousters:** Vem do banco de dados (variável por personagem)
   - Vision **não é calculado dinamicamente** no servidor
   - Apenas skills específicas modificam vision temporariamente

6. **ObservingEye não afeta vision**
   - Skill "ObservingEye" tem `getVisionBonus()` mas está comentado
   - Atualmente apenas permite ver invisibilidade, não aumenta vision

---

## Para Alterar Padrões no Servidor

### Checklist de Alterações Necessárias

1. **Sistema de Cálculo de Vision:**
   - [ ] Modificar função que calcula vision total
   - [ ] Ajustar valores base por raça/classe
   - [ ] Definir limites mínimo/máximo

2. **Sistema de Itens:**
   - [ ] Adicionar/modificar bônus de vision em itens
   - [ ] Ajustar fórmulas de cálculo (grade, encantamento)
   - [ ] Verificar opções de itens que afetam vision

3. **Sistema de Skills:**
   - [ ] Adicionar/modificar skills que afetam vision
   - [ ] Ajustar valores de bônus por nível
   - [ ] Verificar efeitos temporários

4. **Sistema de Packets:**
   - [ ] Garantir que `GCModifyInformation` com `MODIFY_VISION` é enviado quando necessário
   - [ ] Verificar que o valor está correto no packet
   - [ ] Testar envio em todos os casos relevantes

5. **Testes:**
   - [ ] Verificar que vision é atualizado corretamente no cliente
   - [ ] Testar com diferentes valores (mínimo, máximo, intermediários)
   - [ ] Verificar que objetos são renderizados/removidos corretamente
   - [ ] Testar filtro de luz com diferentes valores de vision

---

## Exemplo de Implementação no Servidor

```cpp
// Servidor (pseudocódigo - exemplo de implementação)

// 1. Calcular vision total
BYTE Player::CalculateVision()
{
    BYTE vision = GetBaseVision();
    
    // Bônus de itens
    vision += CalculateItemVisionBonus();
    
    // Bônus de skills
    vision += CalculateSkillVisionBonus();
    
    // Bônus de efeitos de status
    vision += CalculateStatusVisionBonus();
    
    // Limites
    vision = min(vision, MAX_VISION);
    vision = max(vision, MIN_VISION);
    
    return vision;
}

// 2. Enviar atualização quando necessário
void Player::UpdateVision()
{
    BYTE newVision = CalculateVision();
    
    if (newVision != m_CurrentVision)
    {
        m_CurrentVision = newVision;
        SendVisionUpdate();
    }
}

// 3. Enviar packet
void Player::SendVisionUpdate()
{
    GCModifyInformation* pPacket = new GCModifyInformation();
    pPacket->addShortData(MODIFY_VISION, m_CurrentVision);
    sendPacket(pPacket);
    delete pPacket;
}

// 4. Chamar quando necessário
void Player::OnEquipItem(Item* pItem)
{
    // ... lógica de equipar ...
    
    if (pItem->AffectsVision())
        UpdateVision();
}

void Player::OnSkillActivate(SkillID skillID)
{
    // ... lógica de skill ...
    
    if (GetSkillInfo(skillID)->AffectsVision())
        UpdateVision();
}
```

---

## Conclusão

O sistema de `vision` (Sight) é **definido no servidor** e **afeta diretamente a renderização no cliente**:
- Controla quais objetos são renderizados
- Limita o alcance do filtro de iluminação
- Afeta a experiência visual do player

**Características importantes:**
- Vision é **fixo por raça/classe** (Slayer = 13, Vampire/Ousters = banco de dados)
- **Não é calculado dinamicamente** - apenas modificado temporariamente por skills
- `OPTION_VISION` em itens **não é processado** no servidor
- Apenas skills específicas modificam vision temporariamente

Para alterar padrões, é necessário modificar:
1. **Valores fixos** no código (`Slayer.cpp`) ou banco de dados (Vampire/Ousters)
2. **Skills que modificam vision** (valores e lógica em `Effect*.cpp`)
3. **Habilitar OPTION_VISION** se desejar que itens afetem vision (requer implementação)
