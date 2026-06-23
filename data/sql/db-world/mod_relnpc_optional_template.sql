-- mod-relnpc optional template
--
-- AzerothCore creature_template schemas can vary between revisions.
-- If this INSERT fails in your core, create the NPC from an existing template
-- and then apply mod_relnpc_attach.sql.

SET @RELNPC_ENTRY := 601900;

DELETE FROM `creature_template` WHERE `entry` = @RELNPC_ENTRY;

INSERT INTO `creature_template`
(`entry`, `name`, `subname`, `IconName`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `dmgschool`, `BaseAttackTime`, `RangeAttackTime`, `unit_class`, `unit_flags`, `type`, `type_flags`, `AIName`, `ScriptName`)
VALUES
(@RELNPC_ENTRY, 'RelNPC', 'Server Utility', 'Speak', 80, 80, 35, 1, 1, 1.14286, 1, 0, 0, 2000, 2000, 1, 0, 7, 0, '', 'npc_relnpc');
