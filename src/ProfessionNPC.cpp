#include "Chat.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "SpellMgr.h"
#include <Config.h>

bool ModConfigEnable = 1;
uint16 ModConfigGivenCraftLevel = 450;

class NpcFreeProfessionsConfig : public WorldScript
{
public:
    NpcFreeProfessionsConfig() : WorldScript("NpcFreeProfessionsConfig") {}

    void OnBeforeConfigLoad(bool /*reload*/) override
    {
        SetInitialWorldSettings();
    }

    void SetInitialWorldSettings()
    {
        ModConfigEnable = sConfigMgr->GetOption<bool>("NpcFreeProfessions.Enable", 1);
        ModConfigGivenCraftLevel = sConfigMgr->GetOption<uint16>("NpcFreeProfessions.GivenCraftLevel", 450);
    }
};

class NpcFreeProfessionsCreatureScript : public CreatureScript
{
public:
    NpcFreeProfessionsCreatureScript() : CreatureScript("npc_free_professions") {}

    bool OnGossipHello(Player *player, Creature *creature) override
    {
        if (ModConfigEnable)
        {
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Alchemy", GOSSIP_SENDER_MAIN, SKILL_ALCHEMY);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Blacksmithing", GOSSIP_SENDER_MAIN, SKILL_BLACKSMITHING);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Leatherworking", GOSSIP_SENDER_MAIN, SKILL_LEATHERWORKING);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Tailoring", GOSSIP_SENDER_MAIN, SKILL_TAILORING);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Engineering", GOSSIP_SENDER_MAIN, SKILL_ENGINEERING);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Enchanting", GOSSIP_SENDER_MAIN, SKILL_ENCHANTING);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Jewelcrafting", GOSSIP_SENDER_MAIN, SKILL_JEWELCRAFTING);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Inscription", GOSSIP_SENDER_MAIN, SKILL_INSCRIPTION);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Herbalism", GOSSIP_SENDER_MAIN, SKILL_HERBALISM);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Skinning", GOSSIP_SENDER_MAIN, SKILL_SKINNING);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Mining", GOSSIP_SENDER_MAIN, SKILL_MINING);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Cooking", GOSSIP_SENDER_MAIN, SKILL_COOKING);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "First Aid", GOSSIP_SENDER_MAIN, SKILL_FIRST_AID);
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "Fishing", GOSSIP_SENDER_MAIN, SKILL_FISHING);

            SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature);
        }

        return true;
    }

    bool OnGossipSelect(Player *player, Creature */*creature*/, uint32 Sender, uint32 SKILL) override
    {
        if (ModConfigEnable)
        {
            player->PlayerTalkClass->ClearMenus();

            if (Sender == GOSSIP_SENDER_MAIN)
            {
                if (player->HasSkill(SKILL))
                {
                    ChatHandler(player->GetSession()).SendNotification("You already have this work!");
                    CloseGossipMenuFor(player);
                }
                else
                {
                    LearnAllRecipesInProfession(player, (SkillType)SKILL);
                    CloseGossipMenuFor(player);
                }
            }
        }

        return true;
    }

    static void LearnAllRecipesInProfession(Player *player, SkillType skill)
    {
        if (HasFreeProfession(player, skill))
        {
            switch (skill)
            {
                case SKILL_ALCHEMY:
                    player->learnSpell(2259);
                    player->learnSpell(3101);
                    player->learnSpell(3464);
                    player->learnSpell(11611);
                    player->learnSpell(28596);
                    player->learnSpell(51304);
                    break;
                case SKILL_BLACKSMITHING:
                    player->learnSpell(2018);
                    player->learnSpell(3100);
                    player->learnSpell(3538);
                    player->learnSpell(9785);
                    player->learnSpell(29844);
                    player->learnSpell(51300);
                    break;
                case SKILL_ENCHANTING:
                    player->learnSpell(7411);
                    player->learnSpell(7412);
                    player->learnSpell(7413);
                    player->learnSpell(13920);
                    player->learnSpell(28029);
                    player->learnSpell(51313);
                    break;
                case SKILL_ENGINEERING:
                    player->learnSpell(4036);
                    player->learnSpell(4037);
                    player->learnSpell(4038);
                    player->learnSpell(12656);
                    player->learnSpell(30350);
                    player->learnSpell(51306);
                    break;
                case SKILL_INSCRIPTION:
                    player->learnSpell(45357);
                    player->learnSpell(45358);
                    player->learnSpell(45359);
                    player->learnSpell(45360);
                    player->learnSpell(45361);
                    player->learnSpell(45363);
                    break;
                case SKILL_JEWELCRAFTING:
                    player->learnSpell(25229);
                    player->learnSpell(25230);
                    player->learnSpell(28894);
                    player->learnSpell(28895);
                    player->learnSpell(28897);
                    player->learnSpell(51311);
                    break;
                case SKILL_LEATHERWORKING:
                    player->learnSpell(2108);
                    player->learnSpell(3104);
                    player->learnSpell(3811);
                    player->learnSpell(10662);
                    player->learnSpell(32549);
                    player->learnSpell(51302);
                    break;
                case SKILL_TAILORING:
                    player->learnSpell(3908);
                    player->learnSpell(3909);
                    player->learnSpell(3910);
                    player->learnSpell(12180);
                    player->learnSpell(26790);
                    player->learnSpell(51309);
                    break;
                case SKILL_COOKING:
                    player->learnSpell(51296);
                    break;
                case SKILL_FIRST_AID:
                    player->learnSpell(45542);
                    break;
                case SKILL_FISHING:
                    player->learnSpell(65293);
                    break;
                case SKILL_MINING:
                    player->learnSpell(2575);
                    player->learnSpell(2576);
                    player->learnSpell(3564);
                    player->learnSpell(10248);
                    player->learnSpell(29354);
                    player->learnSpell(50310);
                    break;
                case SKILL_SKINNING:
                    player->learnSpell(8613);
                    player->learnSpell(8617);
                    player->learnSpell(8618);
                    player->learnSpell(10768);
                    player->learnSpell(32678);
                    player->learnSpell(50305);
                    break;
                case SKILL_HERBALISM:
                    player->learnSpell(2366);
                    player->learnSpell(2368);
                    player->learnSpell(3570);
                    player->learnSpell(11993);
                    player->learnSpell(28695);
                    player->learnSpell(50300);
                    break;
                default:
                    break;
            }

            if (SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(skill))
            {
                player->SetSkill(SkillInfo->id, player->GetSkillStep(SkillInfo->id), ModConfigGivenCraftLevel, 450);

                uint32 ClassMask = player->getClassMask();

                for (uint32 i = 0; i < sSkillLineAbilityStore.GetNumRows(); ++i)
                {
                    if (SkillLineAbilityEntry const *SkillLine = sSkillLineAbilityStore.LookupEntry(i))
                    {
                        if (SkillLine->SkillLine != SkillInfo->id)
                            continue;

                        if (SkillLine->SupercededBySpell)
                            continue;

                        if (SkillLine->RaceMask != 0)
                            continue;

                        if (SkillLine->ClassMask && (SkillLine->ClassMask & ClassMask) == 0)
                            continue;

                        SpellInfo const *SpellInfo2 = sSpellMgr->GetSpellInfo(SkillLine->Spell);

                        if (!SpellInfo2 || !SpellMgr::IsSpellValid(SpellInfo2))
                            continue;

                        player->learnSpell(SkillLine->Spell);
                    }
                }
            }
        }
    }

    static bool HasFreeProfession(Player *player, SkillType Skill)
    {
        if (Skill == SKILL_FISHING || Skill == SKILL_COOKING || Skill == SKILL_FIRST_AID)
            return true;

        uint8 SkillCount = 0;

        if (player->HasSkill(SKILL_MINING))
            SkillCount++;
        if (player->HasSkill(SKILL_SKINNING))
            SkillCount++;
        if (player->HasSkill(SKILL_HERBALISM))
            SkillCount++;

        for (uint32 i = 1; i < sSkillLineStore.GetNumRows(); ++i)
        {
            if (SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(i))
            {
                if (SkillInfo->categoryId == SKILL_CATEGORY_SECONDARY)
                    continue;

                if ((SkillInfo->categoryId != SKILL_CATEGORY_PROFESSION) || !SkillInfo->canLink)
                    continue;

                if (player->HasSkill(SkillInfo->id))
                    SkillCount++;
            }
        }

        if (SkillCount > 0 && player->HasSkill(Skill))
            SkillCount--;

        return SkillCount < sWorld->getIntConfig(CONFIG_MAX_PRIMARY_TRADE_SKILL);
    }
};

void AddSC_Professions()
{
    new NpcFreeProfessionsConfig();
    new NpcFreeProfessionsCreatureScript();
}
