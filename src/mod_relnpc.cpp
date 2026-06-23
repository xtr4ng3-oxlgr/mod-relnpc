/*
 * mod-relnpc
 *
 * Utility gossip NPC for AzerothCore WotLK.
 *
 * Created by xtr4ng3.
 * Defensive/server-side utility module.
 */

#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "Config.h"
#include "Chat.h"
#include "Creature.h"
#include "Player.h"
#include "WorldSession.h"

namespace RelNPC
{
    enum Actions : uint32
    {
        ACTION_INFO             = 100,
        ACTION_REPAIR           = 101,
        ACTION_HEAL             = 102,
        ACTION_REMOVE_SICKNESS  = 103,
        ACTION_CLOSE            = 199
    };

    static bool Enabled()
    {
        return sConfigMgr->GetOption<bool>("RelNPC.Enable", true);
    }

    static uint32 NpcEntry()
    {
        return sConfigMgr->GetOption<uint32>("RelNPC.Entry", 601900);
    }

    static bool AllowInCombat()
    {
        return sConfigMgr->GetOption<bool>("RelNPC.AllowInCombat", false);
    }

    static bool EnableRepair()
    {
        return sConfigMgr->GetOption<bool>("RelNPC.EnableRepair", true);
    }

    static bool EnableHeal()
    {
        return sConfigMgr->GetOption<bool>("RelNPC.EnableHeal", true);
    }

    static bool EnableRemoveSickness()
    {
        return sConfigMgr->GetOption<bool>("RelNPC.EnableRemoveSickness", true);
    }

    static bool Announce()
    {
        return sConfigMgr->GetOption<bool>("RelNPC.Announce", true);
    }

    static void Send(Player* player, char const* text)
    {
        if (!player || !player->GetSession())
            return;

        ChatHandler(player->GetSession()).SendSysMessage(text);
    }

    static bool BlockedByCombat(Player* player)
    {
        return player && player->IsInCombat() && !AllowInCombat();
    }
}

class mod_relnpc_player : public PlayerScript
{
public:
    mod_relnpc_player() : PlayerScript("mod_relnpc_player") { }

    void OnLogin(Player* player) override
    {
        if (!RelNPC::Enabled() || !RelNPC::Announce())
            return;

        RelNPC::Send(player, "|cff7ef9ff[RelNPC]|r module loaded.");
    }
};

class npc_relnpc : public CreatureScript
{
public:
    npc_relnpc() : CreatureScript("npc_relnpc") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (!player || !creature)
            return false;

        if (!RelNPC::Enabled())
            return false;

        if (creature->GetEntry() != RelNPC::NpcEntry())
            return false;

        ClearGossipMenuFor(player);

        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "|cff7ef9ffRelNPC|r - server utility", GOSSIP_SENDER_MAIN, RelNPC::ACTION_INFO);

        if (RelNPC::EnableRepair())
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Repair equipment", GOSSIP_SENDER_MAIN, RelNPC::ACTION_REPAIR);

        if (RelNPC::EnableHeal())
            AddGossipItemFor(player, GOSSIP_ICON_HEALER, "Recover health and mana", GOSSIP_SENDER_MAIN, RelNPC::ACTION_HEAL);

        if (RelNPC::EnableRemoveSickness())
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Remove resurrection sickness", GOSSIP_SENDER_MAIN, RelNPC::ACTION_REMOVE_SICKNESS);

        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Close", GOSSIP_SENDER_MAIN, RelNPC::ACTION_CLOSE);

        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        if (!player || !creature)
            return false;

        ClearGossipMenuFor(player);

        if (!RelNPC::Enabled())
        {
            CloseGossipMenuFor(player);
            return true;
        }

        if (RelNPC::BlockedByCombat(player))
        {
            RelNPC::Send(player, "|cffff304f[RelNPC]|r You cannot use this NPC while in combat.");
            CloseGossipMenuFor(player);
            return true;
        }

        switch (action)
        {
            case RelNPC::ACTION_INFO:
                RelNPC::Send(player, "|cff7ef9ff[RelNPC]|r Local server utility NPC.");
                OnGossipHello(player, creature);
                return true;

            case RelNPC::ACTION_REPAIR:
                if (!RelNPC::EnableRepair())
                    break;

                player->DurabilityRepairAll(false, 0, false);
                RelNPC::Send(player, "|cff5dff8b[RelNPC]|r Equipment repaired.");
                OnGossipHello(player, creature);
                return true;

            case RelNPC::ACTION_HEAL:
                if (!RelNPC::EnableHeal())
                    break;

                player->SetHealth(player->GetMaxHealth());

                if (player->GetPowerType() == POWER_MANA)
                    player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));

                RelNPC::Send(player, "|cff5dff8b[RelNPC]|r Health restored.");
                OnGossipHello(player, creature);
                return true;

            case RelNPC::ACTION_REMOVE_SICKNESS:
                if (!RelNPC::EnableRemoveSickness())
                    break;

                player->RemoveAurasDueToSpell(15007); // Resurrection Sickness
                RelNPC::Send(player, "|cff5dff8b[RelNPC]|r Resurrection sickness removed.");
                OnGossipHello(player, creature);
                return true;

            case RelNPC::ACTION_CLOSE:
            default:
                CloseGossipMenuFor(player);
                return true;
        }

        CloseGossipMenuFor(player);
        return true;
    }
};

void AddSC_mod_relnpc()
{
    new mod_relnpc_player();
    new npc_relnpc();
}
