# Installation

```bash
cd /home/azeroth/azerothcore-wotlk/modules
git clone https://github.com/YOUR-USER/mod-relnpc.git
cd /home/azeroth/azerothcore-wotlk
./acore.sh compiler build
```

Copy config:

```bash
cp modules/mod-relnpc/conf/mod_relnpc.conf.dist env/dist/etc/modules/mod_relnpc.conf
```

Apply SQL:

```sql
SOURCE modules/mod-relnpc/data/sql/db-world/mod_relnpc_attach.sql;
```

Spawn:

```text
.npc add 601900
```
