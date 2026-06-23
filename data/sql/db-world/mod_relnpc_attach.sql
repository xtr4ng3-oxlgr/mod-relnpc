-- mod-relnpc
-- Attach script to an existing creature_template.
--
-- Recommended:
-- 1. Create or choose your NPC entry.
-- 2. Set @RELNPC_ENTRY to that entry.
-- 3. Apply this SQL to acore_world.
-- 4. Spawn with .npc add @RELNPC_ENTRY

SET @RELNPC_ENTRY := 601900;

UPDATE `creature_template`
SET `ScriptName` = 'npc_relnpc',
    `npcflag` = `npcflag` | 1
WHERE `entry` = @RELNPC_ENTRY;
