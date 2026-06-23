# mod-relnpc

**mod-relnpc** is a lightweight AzerothCore WotLK module that adds a configurable utility gossip NPC.

Created by **xtr4ng3**.

---

## Features

- configurable NPC entry,
- gossip menu,
- repair equipment,
- recover health and mana,
- remove resurrection sickness,
- combat restriction,
- login announce option,
- no database changes required by the C++ module itself,
- optional SQL included for attaching the script to a creature template.

---

## Default NPC

```text
Entry: 601900
ScriptName: npc_relnpc
```

The entry can be changed in:

```text
conf/mod_relnpc.conf.dist
```

---

## Installation

Clone or copy the module into your AzerothCore modules directory:

```bash
cd /home/azeroth/azerothcore-wotlk/modules
git clone https://github.com/xtr4ng3-oxlgr/mod-relnpc.git
```

Rebuild AzerothCore:

```bash
cd /home/azeroth/azerothcore-wotlk
./acore.sh compiler build
```

Copy the config:

```bash
cp modules/mod-relnpc/conf/mod_relnpc.conf.dist env/dist/etc/modules/mod_relnpc.conf
```

Apply the SQL that fits your setup:

```text
data/sql/db-world/mod_relnpc_attach.sql
```

Then spawn the NPC in game:

```text
.npc add 601900
```

---

## SQL notes

`mod_relnpc_attach.sql` is the safest option.  
It only attaches the C++ script to an existing `creature_template`.

`mod_relnpc_optional_template.sql` is included as a starting template.  
Some AzerothCore revisions have different `creature_template` columns, so review it before applying.

---

## Configuration

```ini
RelNPC.Enable = 1
RelNPC.Entry = 601900
RelNPC.Announce = 1
RelNPC.AllowInCombat = 0
RelNPC.EnableRepair = 1
RelNPC.EnableHeal = 1
RelNPC.EnableRemoveSickness = 1
```

---

## Safety

This module is server-side and does not modify client files.

It does not add commands, does not give items, does not grant GM permissions and does not execute external programs.

---

# Licencia

<img width="300" height="159" alt="giphy (25)" src="https://github.com/user-attachments/assets/021720ff-3aec-4916-9a93-25d47afd7d97" />

**xtr4ng3**

MIT.
