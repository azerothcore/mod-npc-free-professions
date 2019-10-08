/*

# Enchanter NPC #

#### A module for AzerothCore by [Renatokeys](https://github.com/renatokeys/modules)
------------------------------------------------------------------------------------------------------------------


### Description ###
------------------------------------------------------------------------------------------------------------------
NPC professions give 2 professions free


### Data ###
------------------------------------------------------------------------------------------------------------------
- Type: NPC
- Script: ProfessionNPC
- Config: Yes
    - Enable Module Announce
- SQL: Yes
    - NPC ID: 99999


### Version ###
------------------------------------------------------------------------------------------------------------------
- v2011-05-26 - Release


### Credits ###
------------------------------------------------------------------------------------------------------------------
- [LordPsyan](https://bitbucket.org/lordpsyan/lordpsyan-patches)
- [Blizzard Entertainment](http://blizzard.com)
- [TrinityCore](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/THANKS)
- [SunwellCore](http://www.azerothcore.org/pages/sunwell.pl/)
- [AzerothCore](https://github.com/AzerothCore/azerothcore-wotlk/graphs/contributors)
- [AzerothCore Discord](https://discord.gg/gkt4y2x)
- [EMUDevs](https://youtube.com/user/EmuDevs)
- [AC-Web](http://ac-web.org/)
- [ModCraft.io](http://modcraft.io/)
- [OwnedCore](http://ownedcore.com/)
- [OregonCore](https://wiki.oregon-core.net/)
- [Wowhead.com](http://wowhead.com)
- [AoWoW](https://wotlk.evowow.com/)


### License ###
------------------------------------------------------------------------------------------------------------------
- This code and content is released under the [GNU AGPL v3](https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3).

*/

#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "Language.h"
#include "Player.h"
#include "Chat.h"

class ProfessionNPC : public CreatureScript
{
public:
	ProfessionNPC() : CreatureScript("ProfessionNPC") {}

	void CreatureWhisperBasedOnBool(const char *text, Creature *_creature, Player *pPlayer, bool value)
	{
		if (value)
			_creature->MonsterWhisper(text, pPlayer, 0);
	}

	uint32 PlayerMaxLevel() const
	{
		return sWorld->getIntConfig(CONFIG_MAX_PLAYER_LEVEL);
	}

	bool PlayerHasItemOrSpell(const Player *plr, uint32 itemId, uint32 spellId) const
	{
		return plr->HasItemCount(itemId, 1, true) || plr->HasSpell(spellId);
	}

	bool OnGossipHello(Player *pPlayer, Creature* _creature)
	{
		AddGossipItemFor(pPlayer, 9, "[Professions] ->", GOSSIP_SENDER_MAIN, 196);
		SendGossipMenuFor(pPlayer, 907, _creature->GetGUID());
		return true;
	}

	bool PlayerAlreadyHasTwoProfessions(const Player *pPlayer) const
	{
		uint32 skillCount = 0;

		if (pPlayer->HasSkill(SKILL_MINING))
			skillCount++;
		if (pPlayer->HasSkill(SKILL_SKINNING))
			skillCount++;
		if (pPlayer->HasSkill(SKILL_HERBALISM))
			skillCount++;

		if (skillCount >= 2)
			return true;

		for (uint32 i = 1; i < sSkillLineStore.GetNumRows(); ++i)
		{
			SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(i);
			if (!SkillInfo)
				continue;

			if (SkillInfo->categoryId == SKILL_CATEGORY_SECONDARY)
				continue;

			if ((SkillInfo->categoryId != SKILL_CATEGORY_PROFESSION) || !SkillInfo->canLink)
				continue;

			const uint32 skillID = SkillInfo->id;
			if (pPlayer->HasSkill(skillID))
				skillCount++;

			if (skillCount >= 2)
				return true;
		}
		return false;
	}

	bool LearnAllRecipesInProfession(Player *pPlayer, SkillType skill)
	{
		ChatHandler handler(pPlayer->GetSession());
		char* skill_name;

		SkillLineEntry const *SkillInfo = sSkillLineStore.LookupEntry(skill);
		skill_name = SkillInfo->name[handler.GetSessionDbcLocale()];


		LearnSkillRecipesHelper(pPlayer, SkillInfo->id);

		pPlayer->SetSkill(SkillInfo->id, pPlayer->GetSkillStep(SkillInfo->id), 450, 450);
		handler.PSendSysMessage(LANG_COMMAND_LEARN_ALL_RECIPES, skill_name);

		return true;
	}

	void LearnSkillRecipesHelper(Player *player, uint32 skill_id)
	{
		uint32 classmask = player->getClassMask();

		for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
		{
			SkillLineAbilityEntry const *skillLine = sSkillLineAbilityStore.LookupEntry(j);
			if (!skillLine)
				continue;

			// wrong skill
			if (skillLine->skillId != skill_id)
				continue;

			// not high rank
			if (skillLine->forward_spellid)
				continue;

			// skip racial skills
			if (skillLine->racemask != 0)
				continue;

			// skip wrong class skills
			if (skillLine->classmask && (skillLine->classmask & classmask) == 0)
				continue;

			SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(skillLine->spellId);
            if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo))
                continue;
			player->learnSpell(skillLine->spellId);
		}
	}

	bool IsSecondarySkill(SkillType skill) const
	{
		return skill == SKILL_COOKING || skill == SKILL_FIRST_AID || skill == SKILL_FISHING;
	}

	void CompleteLearnProfession(Player *pPlayer, Creature *pCreature, SkillType skill)
	{
		if (PlayerAlreadyHasTwoProfessions(pPlayer) && !IsSecondarySkill(skill))
			pCreature->MonsterWhisper("You already know two professions!", pPlayer, 0);
		else
		{
			if (!LearnAllRecipesInProfession(pPlayer, skill))
				pCreature->MonsterWhisper("Internal error occured!", pPlayer, 0);
		}
	}

	bool OnGossipSelect(Player* pPlayer, Creature* _creature, uint32 uiSender, uint32 uiAction)
	{
		pPlayer->PlayerTalkClass->ClearMenus();

		if (uiSender == GOSSIP_SENDER_MAIN)
		{

			switch (uiAction)
			{
			case 196:
				AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\trade_alchemy:30|t Alchemy.", GOSSIP_SENDER_MAIN, 1);
				AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\INV_Ingot_05:30|t Blacksmithing.", GOSSIP_SENDER_MAIN, 2);
				AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\INV_Misc_LeatherScrap_02:30|t Leatherworking.", GOSSIP_SENDER_MAIN, 3);
				AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\INV_Fabric_Felcloth_Ebon:30|t Tailoring.", GOSSIP_SENDER_MAIN, 4);
				AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\inv_misc_wrench_01:30|t Engineering.", GOSSIP_SENDER_MAIN, 5);
				AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\trade_engraving:30|t Enchanting.", GOSSIP_SENDER_MAIN, 6);
				AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\inv_misc_gem_01:30|t Jewelcrafting.", GOSSIP_SENDER_MAIN, 7);
				AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\INV_Scroll_08:30|t Inscription.", GOSSIP_SENDER_MAIN, 8);
				AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\INV_Misc_Herb_07:30|t Herbalism.", GOSSIP_SENDER_MAIN, 9);
				AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\inv_misc_pelt_wolf_01:30|t Skinning.", GOSSIP_SENDER_MAIN, 10);
				AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\trade_mining:30|t Mining.", GOSSIP_SENDER_MAIN, 11);
				AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\spell_holy_sealofsacrifice:30|t First Aid.", GOSSIP_SENDER_MAIN, 12);
				AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\Inv_misc_food_65:30|t Cooking.", GOSSIP_SENDER_MAIN, 13);
				AddGossipItemFor(pPlayer, GOSSIP_ICON_INTERACT_2, "|TInterface\\icons\\Inv_fishingpole_01:30|t Fishing.", GOSSIP_SENDER_MAIN, 14);
				AddGossipItemFor(pPlayer, GOSSIP_ICON_TALK, "|TInterface/ICONS/Thrown_1H_Harpoon_D_01Blue:30|t Nevermind!", GOSSIP_SENDER_MAIN, 15);
				SendGossipMenuFor(pPlayer, 1, _creature->GetGUID());
				break;
			case 1:
				if (pPlayer->HasSkill(SKILL_ALCHEMY))
				{
					CloseGossipMenuFor(pPlayer);
					break;
				}

				CompleteLearnProfession(pPlayer, _creature, SKILL_ALCHEMY);

				CloseGossipMenuFor(pPlayer);
				break;
			case 2:
				if (pPlayer->HasSkill(SKILL_BLACKSMITHING))
				{
					CloseGossipMenuFor(pPlayer);
					break;
				}
				CompleteLearnProfession(pPlayer, _creature, SKILL_BLACKSMITHING);

				CloseGossipMenuFor(pPlayer);
				break;
			case 3:
				if (pPlayer->HasSkill(SKILL_LEATHERWORKING))
				{
					CloseGossipMenuFor(pPlayer);
					break;
				}
				CompleteLearnProfession(pPlayer, _creature, SKILL_LEATHERWORKING);

				CloseGossipMenuFor(pPlayer);
				break;
			case 4:
				if (pPlayer->HasSkill(SKILL_TAILORING))
				{
					CloseGossipMenuFor(pPlayer);
					break;
				}
				CompleteLearnProfession(pPlayer, _creature, SKILL_TAILORING);

				CloseGossipMenuFor(pPlayer);
				break;
			case 5:
				if (pPlayer->HasSkill(SKILL_ENGINEERING))
				{
					CloseGossipMenuFor(pPlayer);
					break;
				}
				CompleteLearnProfession(pPlayer, _creature, SKILL_ENGINEERING);

				CloseGossipMenuFor(pPlayer);
				break;
			case 6:
				if (pPlayer->HasSkill(SKILL_ENCHANTING))
				{
					CloseGossipMenuFor(pPlayer);
					break;
				}
				CompleteLearnProfession(pPlayer, _creature, SKILL_ENCHANTING);

				CloseGossipMenuFor(pPlayer);
				break;
			case 7:
				if (pPlayer->HasSkill(SKILL_JEWELCRAFTING))
				{
					CloseGossipMenuFor(pPlayer);
					break;
				}
				CompleteLearnProfession(pPlayer, _creature, SKILL_JEWELCRAFTING);

				CloseGossipMenuFor(pPlayer);
				break;
			case 8:
				if (pPlayer->HasSkill(SKILL_INSCRIPTION))
				{
					CloseGossipMenuFor(pPlayer);
					break;
				}
				CompleteLearnProfession(pPlayer, _creature, SKILL_INSCRIPTION);

				CloseGossipMenuFor(pPlayer);
				break;
			case 9:
				if (pPlayer->HasSkill(SKILL_HERBALISM))
				{
					CloseGossipMenuFor(pPlayer);
					break;
				}

				CompleteLearnProfession(pPlayer, _creature, SKILL_HERBALISM);
				CloseGossipMenuFor(pPlayer);
				break;
			case 10:
				if (pPlayer->HasSkill(SKILL_SKINNING))
				{
					CloseGossipMenuFor(pPlayer);
					break;
				}

				CompleteLearnProfession(pPlayer, _creature, SKILL_SKINNING);
				CloseGossipMenuFor(pPlayer);
				break;
			case 11:
				if (pPlayer->HasSkill(SKILL_MINING))
				{
					CloseGossipMenuFor(pPlayer);
					break;
				}

				CompleteLearnProfession(pPlayer, _creature, SKILL_MINING);
				CloseGossipMenuFor(pPlayer);
				break;
			case 12:
				if (pPlayer->HasSkill(SKILL_FIRST_AID))
				{
					CloseGossipMenuFor(pPlayer);
					break;
				}

				CompleteLearnProfession(pPlayer, _creature, SKILL_FIRST_AID);
				CloseGossipMenuFor(pPlayer);
				break;
			case 13:
				if (pPlayer->HasSkill(SKILL_COOKING))
				{
					CloseGossipMenuFor(pPlayer);
					break;
				}

				CompleteLearnProfession(pPlayer, _creature, SKILL_COOKING);
				CloseGossipMenuFor(pPlayer);
				break;
			case 14:
				if (pPlayer->HasSkill(SKILL_FISHING))
				{
					CloseGossipMenuFor(pPlayer);
					break;
				}

				CompleteLearnProfession(pPlayer, _creature, SKILL_FISHING);
				CloseGossipMenuFor(pPlayer);
				break;
			case 15:
				CloseGossipMenuFor(pPlayer);
				break;
			}


		}
		return true;
	}
};

void AddSC_ProfessionNPC()
{
	new ProfessionNPC();
}
