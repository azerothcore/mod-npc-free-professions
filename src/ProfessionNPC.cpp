#include "ProfessionNPC.h"

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
                    player->learnSpell(SPELL_APPRENTICE_ALCHEMY);
                    player->learnSpell(SPELL_JOURNEYMAN_ALCHEMY);
                    player->learnSpell(SPELL_EXPERT_ALCHEMY);
                    player->learnSpell(SPELL_ARTISAN_ALCHEMY);
                    player->learnSpell(SPELL_MASTER_ALCHEMY);
                    player->learnSpell(SPELL_GRAND_MASTER_ALCHEMY);
                    break;
                case SKILL_BLACKSMITHING:
                    player->learnSpell(SPELL_APPRENTICE_BLACKSMITHING);
                    player->learnSpell(SPELL_JOURNEYMAN_BLACKSMITHING);
                    player->learnSpell(SPELL_EXPERT_BLACKSMITHING);
                    player->learnSpell(SPELL_ARTISAN_BLACKSMITHING);
                    player->learnSpell(SPELL_MASTER_BLACKSMITHING);
                    player->learnSpell(SPELL_GRAND_MASTER_BLACKSMITHING);
                    break;
                case SKILL_ENCHANTING:
                    player->learnSpell(SPELL_APPRENTICE_ENCHANTING);
                    player->learnSpell(SPELL_JOURNEYMAN_ENCHANTING);
                    player->learnSpell(SPELL_EXPERT_ENCHANTING);
                    player->learnSpell(SPELL_ARTISAN_ENCHANTING);
                    player->learnSpell(SPELL_MASTER_ENCHANTING);
                    player->learnSpell(SPELL_GRAND_MASTER_ENCHANTING);
                    break;
                case SKILL_ENGINEERING:
                    player->learnSpell(SPELL_APPRENTICE_ENGINEERING);
                    player->learnSpell(SPELL_JOURNEYMAN_ENGINEERING);
                    player->learnSpell(SPELL_EXPERT_ENGINEERING);
                    player->learnSpell(SPELL_ARTISAN_ENGINEERING);
                    player->learnSpell(SPELL_MASTER_ENGINEERING);
                    player->learnSpell(SPELL_GRAND_MASTER_ENGINEERING);
                    break;
                case SKILL_INSCRIPTION:
                    player->learnSpell(SPELL_APPRENTICE_INSCRIPTION);
                    player->learnSpell(SPELL_JOURNEYMAN_INSCRIPTION);
                    player->learnSpell(SPELL_EXPERT_INSCRIPTION);
                    player->learnSpell(SPELL_ARTISAN_INSCRIPTION);
                    player->learnSpell(SPELL_MASTER_INSCRIPTION);
                    player->learnSpell(SPELL_GRAND_MASTER_INSCRIPTION);
                    break;
                case SKILL_JEWELCRAFTING:
                    player->learnSpell(SPELL_APPRENTICE_JEWELCRAFTING);
                    player->learnSpell(SPELL_JOURNEYMAN_JEWELCRAFTING);
                    player->learnSpell(SPELL_EXPERT_JEWELCRAFTING);
                    player->learnSpell(SPELL_ARTISAN_JEWELCRAFTING);
                    player->learnSpell(SPELL_MASTER_JEWELCRAFTING);
                    player->learnSpell(SPELL_GRAND_MASTER_JEWELCRAFTING);
                    break;
                case SKILL_LEATHERWORKING:
                    player->learnSpell(SPELL_APPRENTICE_LEATHERWORKING);
                    player->learnSpell(SPELL_JOURNEYMAN_LEATHERWORKING);
                    player->learnSpell(SPELL_EXPERT_LEATHERWORKING);
                    player->learnSpell(SPELL_ARTISAN_LEATHERWORKING);
                    player->learnSpell(SPELL_MASTER_LEATHERWORKING);
                    player->learnSpell(SPELL_GRAND_MASTER_LEATHERWORKING);
                    break;
                case SKILL_TAILORING:
                    player->learnSpell(SPELL_APPRENTICE_TAILORING);
                    player->learnSpell(SPELL_JOURNEYMAN_TAILORING);
                    player->learnSpell(SPELL_EXPERT_TAILORING);
                    player->learnSpell(SPELL_ARTISAN_TAILORING);
                    player->learnSpell(SPELL_MASTER_TAILORING);
                    player->learnSpell(SPELL_GRAND_MASTER_TAILORING);
                    break;
                case SKILL_COOKING:
                    player->learnSpell(SPELL_APPRENTICE_COOKING);
                    player->learnSpell(SPELL_JOURNEYMAN_COOKING);
                    player->learnSpell(SPELL_EXPERT_COOKING);
                    player->learnSpell(SPELL_ARTISAN_COOKING);
                    player->learnSpell(SPELL_MASTER_COOKING);
                    player->learnSpell(SPELL_GRAND_MASTER_COOKING);
                    break;
                case SKILL_FIRST_AID:
                    player->learnSpell(SPELL_APPRENTICE_FIRST_AID);
                    player->learnSpell(SPELL_JOURNEYMAN_FIRST_AID);
                    player->learnSpell(SPELL_EXPERT_FIRST_AID);
                    player->learnSpell(SPELL_ARTISAN_FIRST_AID);
                    player->learnSpell(SPELL_MASTER_FIRST_AID);
                    player->learnSpell(SPELL_GRAND_MASTER_FIRST_AID);
                    break;
                case SKILL_FISHING:
                    player->learnSpell(SPELL_APPRENTICE_FISHING);
                    player->learnSpell(SPELL_JOURNEYMAN_FISHING);
                    player->learnSpell(SPELL_EXPERT_FISHING);
                    player->learnSpell(SPELL_ARTISAN_FISHING);
                    player->learnSpell(SPELL_MASTER_FISHING);
                    player->learnSpell(SPELL_GRAND_MASTER_FISHING);
                    break;
                case SKILL_MINING:
                    player->learnSpell(SPELL_APPRENTICE_MINING);
                    player->learnSpell(SPELL_JOURNEYMAN_MINING);
                    player->learnSpell(SPELL_EXPERT_MINING);
                    player->learnSpell(SPELL_ARTISAN_MINING);
                    player->learnSpell(SPELL_MASTER_MINING);
                    player->learnSpell(SPELL_GRAND_MASTER_MINING);
                    break;
                case SKILL_SKINNING:
                    player->learnSpell(SPELL_APPRENTICE_SKINNING);
                    player->learnSpell(SPELL_JOURNEYMAN_SKINNING);
                    player->learnSpell(SPELL_EXPERT_SKINNING);
                    player->learnSpell(SPELL_ARTISAN_SKINNING);
                    player->learnSpell(SPELL_MASTER_SKINNING);
                    player->learnSpell(SPELL_GRAND_MASTER_SKINNING);
                    break;
                case SKILL_HERBALISM:
                    player->learnSpell(SPELL_APPRENTICE_HERBALISM);
                    player->learnSpell(SPELL_JOURNEYMAN_HERBALISM);
                    player->learnSpell(SPELL_EXPERT_HERBALISM);
                    player->learnSpell(SPELL_ARTISAN_HERBALISM);
                    player->learnSpell(SPELL_MASTER_HERBALISM);
                    player->learnSpell(SPELL_GRAND_MASTER_HERBALISM);
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