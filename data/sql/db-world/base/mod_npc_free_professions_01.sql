-- --------------------------------------------------------------------------------------
-- Profession NPC
-- --------------------------------------------------------------------------------------
DELETE FROM `creature_template` WHERE (`entry` = 199999);
INSERT INTO `creature_template`(`entry`,`difficulty_entry_1`,`difficulty_entry_2`,`difficulty_entry_3`,`KillCredit1`,`KillCredit2`,`name`,`subname`,`IconName`,`gossip_menu_id`,`minlevel`,`maxlevel`,`exp`,`faction`,`npcflag`,`speed_walk`,`speed_run`,`speed_swim`,`speed_flight`,`detection_range`,`scale`,`rank`,`dmgschool`,`DamageModifier`,`BaseAttackTime`,`RangeAttackTime`,`BaseVariance`,`RangeVariance`,`unit_class`,`unit_flags`,`unit_flags2`,`dynamicflags`,`family`,`trainer_type`,`trainer_spell`,`trainer_class`,`trainer_race`,`type`,`type_flags`,`lootid`,`pickpocketloot`,`skinloot`,`PetSpellDataId`,`VehicleId`,`mingold`,`maxgold`,`AIName`,`MovementType`,`HoverHeight`,`HealthModifier`,`ManaModifier`,`ArmorModifier`,`ExperienceModifier`,`RacialLeader`,`movementId`,`RegenHealth`,`mechanic_immune_mask`,`spell_school_immune_mask`,`flags_extra`,`ScriptName`,`VerifiedBuild`) values 
(199999, 0, 0, 0, 0, 0, 'Kaylub', '|cff00ccffProfessions NPC|r', 'Speak', 0, 80, 80, 0, 35, 1, 1, 1.14286, 1, 1, 20, 1.5, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 'npc_free_professions', NULL);
DELETE FROM `creature_template_model` WHERE (`CreatureID` = 199999);
INSERT INTO `creature_template_model`(`CreatureID`,`Idx`,`CreatureDisplayID`,`DisplayScale`,`Probability`,`VerifiedBuild`) values 
(199999,0,31833,1,1,0);

UPDATE `creature_template` SET `npcflag`=`npcflag`|1, `scale`=1, `flags_extra`=`flags_extra`|16777216 WHERE `entry`=199999;
