#include "ProfessionNPC.h"

bool ModConfigEnable = 1;
uint16 ModConfigApprenticeRankCharacterLevelRequirement = 1;
uint16 ModConfigJourneymanRankCharacterLevelRequirement = 15;
uint16 ModConfigExpertRankCharacterLevelRequirement = 30;
uint16 ModConfigArtisanRankCharacterLevelRequirement = 45;
uint16 ModConfigMasterRankCharacterLevelRequirement = 60;
uint16 ModConfigGrandMasterRankCharacterLevelRequirement = 70;
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
        ModConfigApprenticeRankCharacterLevelRequirement = sConfigMgr->GetOption<uint16>("NpcFreeProfessions.ApprenticeRankCharacterLevelRequirement", 1);
        ModConfigJourneymanRankCharacterLevelRequirement = sConfigMgr->GetOption<uint16>("NpcFreeProfessions.JourneymanRankCharacterLevelRequirement", 15);
        ModConfigExpertRankCharacterLevelRequirement = sConfigMgr->GetOption<uint16>("NpcFreeProfessions.ExpertRankCharacterLevelRequirement", 30);
        ModConfigArtisanRankCharacterLevelRequirement = sConfigMgr->GetOption<uint16>("NpcFreeProfessions.ArtisanRankCharacterLevelRequirement", 45);
        ModConfigMasterRankCharacterLevelRequirement = sConfigMgr->GetOption<uint16>("NpcFreeProfessions.MasterRankCharacterLevelRequirement", 60);
        ModConfigGrandMasterRankCharacterLevelRequirement = sConfigMgr->GetOption<uint16>("NpcFreeProfessions.GrandMasterRankCharacterLevelRequirement", 70);
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
            std::string message =
                "I can teach you professions and help you advance through higher ranks as your character levels up. "
                "Learning a new rank will also raise your profession skill to its maximum for that rank.|n|n"

                "Apprentice (75) Requires Level " +
                std::to_string(ModConfigApprenticeRankCharacterLevelRequirement) + "|n" +

                "Journeyman (150) Requires Level " +
                std::to_string(ModConfigJourneymanRankCharacterLevelRequirement) + "|n" +

                "Expert (225) Requires Level " +
                std::to_string(ModConfigExpertRankCharacterLevelRequirement) + "|n" +

                "Artisan (300) Requires Level " +
                std::to_string(ModConfigArtisanRankCharacterLevelRequirement) + "|n" +

                "Master (375) Requires Level " +
                std::to_string(ModConfigMasterRankCharacterLevelRequirement) + "|n" +

                "Grand Master (450) Requires Level " +
                std::to_string(ModConfigGrandMasterRankCharacterLevelRequirement);

            GossipSetText(player, message, DEFAULT_GOSSIP_MESSAGE);
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
                if (GetGivenCraftLevel(player) >= MAX_SKILL_LEVEL_APPRENTICE){
                    LearnAllRecipesInProfession(player, GetGivenCraftLevel(player), (SkillType)SKILL);
                    CloseGossipMenuFor(player);
                }
            }
        }

        return true;
    }

    static void LearnAllRecipesInProfession(Player *player, uint16 GivenCraftLevel, SkillType skill)
    {
        if (HasFreeProfession(player, skill))
        {
            switch (skill)
            {
                case SKILL_ALCHEMY:
                    LearnProfessionSpells(player, 
                        GivenCraftLevel, {
                        SPELL_APPRENTICE_ALCHEMY, 
                        SPELL_JOURNEYMAN_ALCHEMY, 
                        SPELL_EXPERT_ALCHEMY, 
                        SPELL_ARTISAN_ALCHEMY, 
                        SPELL_MASTER_ALCHEMY, 
                        SPELL_GRAND_MASTER_ALCHEMY});
                    break;
                case SKILL_BLACKSMITHING:
                    LearnProfessionSpells(player, 
                        GivenCraftLevel, {
                        SPELL_APPRENTICE_BLACKSMITHING, 
                        SPELL_JOURNEYMAN_BLACKSMITHING, 
                        SPELL_EXPERT_BLACKSMITHING, 
                        SPELL_ARTISAN_BLACKSMITHING, 
                        SPELL_MASTER_BLACKSMITHING, 
                        SPELL_GRAND_MASTER_BLACKSMITHING});
                    break;
                case SKILL_ENCHANTING:
                    LearnProfessionSpells(player, 
                        GivenCraftLevel, {
                        SPELL_APPRENTICE_ENCHANTING, 
                        SPELL_JOURNEYMAN_ENCHANTING, 
                        SPELL_EXPERT_ENCHANTING, 
                        SPELL_ARTISAN_ENCHANTING, 
                        SPELL_MASTER_ENCHANTING, 
                        SPELL_GRAND_MASTER_ENCHANTING});
                    break;
                case SKILL_ENGINEERING:
                    LearnProfessionSpells(player, 
                        GivenCraftLevel, {
                        SPELL_APPRENTICE_ENGINEERING, 
                        SPELL_JOURNEYMAN_ENGINEERING, 
                        SPELL_EXPERT_ENGINEERING, 
                        SPELL_ARTISAN_ENGINEERING, 
                        SPELL_MASTER_ENGINEERING, 
                        SPELL_GRAND_MASTER_ENGINEERING});
                    break;
                case SKILL_INSCRIPTION:
                    LearnProfessionSpells(player, 
                        GivenCraftLevel, {
                        SPELL_APPRENTICE_INSCRIPTION, 
                        SPELL_JOURNEYMAN_INSCRIPTION, 
                        SPELL_EXPERT_INSCRIPTION, 
                        SPELL_ARTISAN_INSCRIPTION, 
                        SPELL_MASTER_INSCRIPTION, 
                        SPELL_GRAND_MASTER_INSCRIPTION});
                    break;
                case SKILL_JEWELCRAFTING:
                    LearnProfessionSpells(player, 
                        GivenCraftLevel, {
                        SPELL_APPRENTICE_JEWELCRAFTING, 
                        SPELL_JOURNEYMAN_JEWELCRAFTING, 
                        SPELL_EXPERT_JEWELCRAFTING, 
                        SPELL_ARTISAN_JEWELCRAFTING, 
                        SPELL_MASTER_JEWELCRAFTING, 
                        SPELL_GRAND_MASTER_JEWELCRAFTING});
                    break;
                case SKILL_LEATHERWORKING:
                    LearnProfessionSpells(player, 
                        GivenCraftLevel, {
                        SPELL_APPRENTICE_LEATHERWORKING, 
                        SPELL_JOURNEYMAN_LEATHERWORKING, 
                        SPELL_EXPERT_LEATHERWORKING, 
                        SPELL_ARTISAN_LEATHERWORKING, 
                        SPELL_MASTER_LEATHERWORKING, 
                        SPELL_GRAND_MASTER_LEATHERWORKING});
                    break;
                case SKILL_TAILORING:
                    LearnProfessionSpells(player, 
                        GivenCraftLevel, {
                        SPELL_APPRENTICE_TAILORING, 
                        SPELL_JOURNEYMAN_TAILORING, 
                        SPELL_EXPERT_TAILORING, 
                        SPELL_ARTISAN_TAILORING, 
                        SPELL_MASTER_TAILORING, 
                        SPELL_GRAND_MASTER_TAILORING});
                    break;
                case SKILL_COOKING:
                    LearnProfessionSpells(player, 
                        GivenCraftLevel, {
                        SPELL_APPRENTICE_COOKING, 
                        SPELL_JOURNEYMAN_COOKING, 
                        SPELL_EXPERT_COOKING, 
                        SPELL_ARTISAN_COOKING, 
                        SPELL_MASTER_COOKING, 
                        SPELL_GRAND_MASTER_COOKING});
                    break;
                case SKILL_FIRST_AID:
                    LearnProfessionSpells(player, 
                        GivenCraftLevel, {
                        SPELL_APPRENTICE_FIRST_AID, 
                        SPELL_JOURNEYMAN_FIRST_AID, 
                        SPELL_EXPERT_FIRST_AID, 
                        SPELL_ARTISAN_FIRST_AID, 
                        SPELL_MASTER_FIRST_AID, 
                        SPELL_GRAND_MASTER_FIRST_AID});
                    break;
                case SKILL_FISHING:
                    LearnProfessionSpells(player, 
                        GivenCraftLevel, {
                        SPELL_APPRENTICE_FISHING, 
                        SPELL_JOURNEYMAN_FISHING, 
                        SPELL_EXPERT_FISHING, 
                        SPELL_ARTISAN_FISHING, 
                        SPELL_MASTER_FISHING, 
                        SPELL_GRAND_MASTER_FISHING});
                    break;
                case SKILL_MINING:
                    LearnProfessionSpells(player, 
                        GivenCraftLevel, {
                        SPELL_APPRENTICE_MINING, 
                        SPELL_JOURNEYMAN_MINING, 
                        SPELL_EXPERT_MINING, 
                        SPELL_ARTISAN_MINING, 
                        SPELL_MASTER_MINING, 
                        SPELL_GRAND_MASTER_MINING});
                    break;
                case SKILL_SKINNING:
                    LearnProfessionSpells(player, 
                        GivenCraftLevel, {
                        SPELL_APPRENTICE_SKINNING, 
                        SPELL_JOURNEYMAN_SKINNING, 
                        SPELL_EXPERT_SKINNING, 
                        SPELL_ARTISAN_SKINNING, 
                        SPELL_MASTER_SKINNING, 
                        SPELL_GRAND_MASTER_SKINNING});
                    break;
                case SKILL_HERBALISM:
                    LearnProfessionSpells(player, 
                        GivenCraftLevel, {
                        SPELL_APPRENTICE_HERBALISM, 
                        SPELL_JOURNEYMAN_HERBALISM, 
                        SPELL_EXPERT_HERBALISM, 
                        SPELL_ARTISAN_HERBALISM, 
                        SPELL_MASTER_HERBALISM, 
                        SPELL_GRAND_MASTER_HERBALISM});
                    break;
                default:
                    break;
            }

            if (SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(skill))
            {
                uint16 CurrentCraftLevel = player->GetSkillValue(SkillInfo->id);
                uint16 CurrentMaxCraftLevel = player->GetMaxSkillValue(SkillInfo->id);

                uint16 NewGivenCraftLevel = std::max(CurrentCraftLevel, GivenCraftLevel);
                uint16 NewMaxCraftLevel = std::max(CurrentMaxCraftLevel, GivenCraftLevel);

                player->SetSkill(SkillInfo->id, player->GetSkillStep(SkillInfo->id), NewGivenCraftLevel, NewMaxCraftLevel);

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

                        if(SpellInfo2->Id == SPELL_APPRENTICE_FISHING_DUPLICATE || 
                            SpellInfo2->Id == SPELL_GRAND_MASTER_ALCHEMY || 
                            SpellInfo2->Id == SPELL_GRAND_MASTER_BLACKSMITHING || 
                            SpellInfo2->Id == SPELL_GRAND_MASTER_ENCHANTING || 
                            SpellInfo2->Id == SPELL_GRAND_MASTER_ENGINEERING || 
                            SpellInfo2->Id == SPELL_GRAND_MASTER_INSCRIPTION || 
                            SpellInfo2->Id == SPELL_GRAND_MASTER_JEWELCRAFTING || 
                            SpellInfo2->Id == SPELL_GRAND_MASTER_LEATHERWORKING || 
                            SpellInfo2->Id == SPELL_GRAND_MASTER_TAILORING || 
                            SpellInfo2->Id == SPELL_GRAND_MASTER_COOKING || 
                            SpellInfo2->Id == SPELL_GRAND_MASTER_FIRST_AID || 
                            SpellInfo2->Id == SPELL_GRAND_MASTER_FISHING || 
                            SpellInfo2->Id == SPELL_GRAND_MASTER_MINING || 
                            SpellInfo2->Id == SPELL_GRAND_MASTER_SKINNING || 
                            SpellInfo2->Id == SPELL_GRAND_MASTER_HERBALISM
                        )
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

    static void LearnProfessionSpells(Player* player, uint16 GivenCraftLevel, std::initializer_list<uint32> spellIds) {
        uint16 CraftLevelCount = 0;
        for (uint32 spellId : spellIds){
            if (CraftLevelCount >= GivenCraftLevel)
                break;
            player->learnSpell(spellId);
            CraftLevelCount += MAX_SKILL_LEVEL_APPRENTICE;
        }
    }

    static uint16 GetGivenCraftLevel(Player* player){
        uint16 GivenCraftLevel = 0;
        if (player->GetLevel() >= ModConfigGrandMasterRankCharacterLevelRequirement){
            GivenCraftLevel = MAX_SKILL_LEVEL_GRAND_MASTER;
        }else if (player->GetLevel() >= ModConfigMasterRankCharacterLevelRequirement){
            GivenCraftLevel = MAX_SKILL_LEVEL_MASTER;
        }else if (player->GetLevel() >= ModConfigArtisanRankCharacterLevelRequirement){
            GivenCraftLevel = MAX_SKILL_LEVEL_ARTISAN;
        }else if (player->GetLevel() >= ModConfigExpertRankCharacterLevelRequirement){
            GivenCraftLevel = MAX_SKILL_LEVEL_EXPERT;
        }else if (player->GetLevel() >= ModConfigJourneymanRankCharacterLevelRequirement){
            GivenCraftLevel = MAX_SKILL_LEVEL_JOURNEYMAN;
        }else if (player->GetLevel() >= ModConfigApprenticeRankCharacterLevelRequirement){
            GivenCraftLevel = MAX_SKILL_LEVEL_APPRENTICE;
        }
        return GivenCraftLevel;
    }

    /*
    * Originally from the GossipSetText() helper in mod-instance-reset.
    * This method is used to override the npc_text
    * Without resorting to the database, since it is a module.
    * And we want to avoid adding information that is not blizzlike.
    */
    void GossipSetText(Player* player, std::string message, uint32 textID)
    {
        WorldPacket data(SMSG_NPC_TEXT_UPDATE, 100);
        data << textID;
        for (uint8 i = 0; i < MAX_GOSSIP_TEXT_OPTIONS; ++i)
        {
            data << float(0);
            data << message;
            data << message;
            data << uint32(0);
            data << uint32(0);
            data << uint32(0);
            data << uint32(0);
            data << uint32(0);
            data << uint32(0);
            data << uint32(0);
        }
        player->GetSession()->SendPacket(&data);
    }
};

void AddSC_Professions()
{
    new NpcFreeProfessionsConfig();
    new NpcFreeProfessionsCreatureScript();
}