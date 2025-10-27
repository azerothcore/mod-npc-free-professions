#include "Chat.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "SpellMgr.h"
#include <Config.h>

bool ModConfigEnable = 1;
uint16 ModConfigGivenCraftLevel = 450;
bool ModConfigEnableAlchemy = 1;
bool ModConfigEnableBlacksmithing = 1;
bool ModConfigEnableLeatherworking = 1;
bool ModConfigEnableTailoring = 1;
bool ModConfigEnableEngineering = 1;
bool ModConfigEnableEnchanting = 1;
bool ModConfigEnableJewelcrafting = 1;
bool ModConfigEnableInscription = 1;
bool ModConfigEnableHerbalism = 1;
bool ModConfigEnableSkinning = 1;
bool ModConfigEnableMining = 1;
bool ModConfigEnableCooking = 1;
bool ModConfigEnableFirstAid = 1;
bool ModConfigEnableFishing = 1;

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
        ModConfigEnableAlchemy = sConfigMgr->GetOption<bool>("NpcFreeProfessions.Enable.Alchemy", 1);
        ModConfigEnableBlacksmithing = sConfigMgr->GetOption<bool>("NpcFreeProfessions.Enable.Blacksmithing", 1);
        ModConfigEnableLeatherworking = sConfigMgr->GetOption<bool>("NpcFreeProfessions.Enable.Leatherworking", 1);
        ModConfigEnableTailoring = sConfigMgr->GetOption<bool>("NpcFreeProfessions.Enable.Tailoring", 1);
        ModConfigEnableEngineering = sConfigMgr->GetOption<bool>("NpcFreeProfessions.Enable.Engineering", 1);
        ModConfigEnableEnchanting = sConfigMgr->GetOption<bool>("NpcFreeProfessions.Enable.Enchanting", 1);
        ModConfigEnableJewelcrafting = sConfigMgr->GetOption<bool>("NpcFreeProfessions.Enable.Jewelcrafting", 1);
        ModConfigEnableInscription = sConfigMgr->GetOption<bool>("NpcFreeProfessions.Enable.Inscription", 1);
        ModConfigEnableHerbalism = sConfigMgr->GetOption<bool>("NpcFreeProfessions.Enable.Herbalism", 1);
        ModConfigEnableSkinning = sConfigMgr->GetOption<bool>("NpcFreeProfessions.Enable.Skinning", 1);
        ModConfigEnableMining = sConfigMgr->GetOption<bool>("NpcFreeProfessions.Enable.Mining", 1);
        ModConfigEnableCooking = sConfigMgr->GetOption<bool>("NpcFreeProfessions.Enable.Cooking", 1);
        ModConfigEnableFirstAid = sConfigMgr->GetOption<bool>("NpcFreeProfessions.Enable.FirstAid", 1);
        ModConfigEnableFishing = sConfigMgr->GetOption<bool>("NpcFreeProfessions.Enable.Fishing", 1);
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
            AddGossipItemForProfession(ModConfigEnableAlchemy, player, "Alchemy", SKILL_ALCHEMY);
            AddGossipItemForProfession(ModConfigEnableBlacksmithing, player, "Blacksmithing", SKILL_BLACKSMITHING);
            AddGossipItemForProfession(ModConfigEnableLeatherworking, player, "Leatherworking", SKILL_LEATHERWORKING);
            AddGossipItemForProfession(ModConfigEnableTailoring, player, "Tailoring", SKILL_TAILORING);
            AddGossipItemForProfession(ModConfigEnableEngineering, player, "Engineering", SKILL_ENGINEERING);
            AddGossipItemForProfession(ModConfigEnableEnchanting, player, "Enchanting", SKILL_ENCHANTING);
            AddGossipItemForProfession(ModConfigEnableJewelcrafting, player, "Jewelcrafting", SKILL_JEWELCRAFTING);
            AddGossipItemForProfession(ModConfigEnableInscription, player, "Inscription", SKILL_INSCRIPTION);
            AddGossipItemForProfession(ModConfigEnableHerbalism, player, "Herbalism", SKILL_HERBALISM);
            AddGossipItemForProfession(ModConfigEnableSkinning, player, "Skinning", SKILL_SKINNING);
            AddGossipItemForProfession(ModConfigEnableMining, player, "Mining", SKILL_MINING);
            AddGossipItemForProfession(ModConfigEnableCooking, player, "Cooking", SKILL_COOKING);
            AddGossipItemForProfession(ModConfigEnableFirstAid, player, "First Aid", SKILL_FIRST_AID);
            AddGossipItemForProfession(ModConfigEnableFishing, player, "Fishing", SKILL_FISHING);
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
                    player->learnSpell(2550);
                    player->learnSpell(3102);
                    player->learnSpell(3413);
                    player->learnSpell(18260);
                    player->learnSpell(33359);
                    player->learnSpell(51296);
                    break;
                case SKILL_FIRST_AID:
                    player->learnSpell(3273);
                    player->learnSpell(3274);
                    player->learnSpell(7924);
                    player->learnSpell(10846);
                    player->learnSpell(27028);
                    player->learnSpell(45542);
                    break;
                case SKILL_FISHING:
                    player->learnSpell(7620);
                    player->learnSpell(7731);
                    player->learnSpell(7732);
                    player->learnSpell(18248);
                    player->learnSpell(33095);
                    player->learnSpell(51294);
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

                        if (!SpellInfo2 || !SpellMgr::IsSpellValid(SpellInfo2) || SpellInfo2->Id == 62734)
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

    static void AddGossipItemForProfession(bool enabled, Player* player, const std::string& name, SkillType skill) {
        if (enabled) {
            AddGossipItemFor(player, GOSSIP_ICON_TRAINER, name, GOSSIP_SENDER_MAIN, skill);
        }
    }
};

void AddSC_Professions()
{
    new NpcFreeProfessionsConfig();
    new NpcFreeProfessionsCreatureScript();
}