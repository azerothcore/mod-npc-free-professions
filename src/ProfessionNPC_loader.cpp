
/*
 * Copyright (С) since 2019 Andrei Guluaev (Winfidonarleyan/Kargatum) https://github.com/Winfidonarleyan
 * Copyright (С) since 2019+ AzerothCore <www.azerothcore.org>
 * Licence MIT https://opensource.org/MIT
 */

// From SC
void AddSC_Professions();

// Add all (module entrypoint expected by scriptloader)
void Addmod_npc_free_professions_vipScripts()
{
    AddSC_Professions();
}

// Backward-compatible alias for older naming.
void Addmod_npc_free_professionsScripts()
{
    Addmod_npc_free_professions_vipScripts();
}
