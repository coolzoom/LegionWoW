////////////////////////////////////////////////////////////////////////////////
//
//  MILLENIUM-STUDIO
//  Copyright 2015 Millenium-studio SARL
//  All Rights Reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include "AshranMgr.hpp"

/// Blade Twister - 178795
class spell_ashran_blade_twister: public SpellScriptLoader
{
    public:
        spell_ashran_blade_twister() : SpellScriptLoader("spell_ashran_blade_twister") { }

        class spell_ashran_blade_twister_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_ashran_blade_twister_AuraScript);

            enum eSpells
            {
                BladeTwisterDamage = 177167
            };

            void OnTick(constAuraEffectPtr p_AurEff)
            {
                if (Unit* l_Target = GetTarget())
                {
                    std::list<Creature*> l_Blades;
                    l_Target->GetCreatureListWithEntryInGrid(l_Blades, eCreatures::BladeTwisterTrigger, 50.0f);

                    if (l_Blades.empty())
                    {
                        p_AurEff->GetBase()->Remove();
                        return;
                    }

                    l_Blades.remove_if([this, l_Target](Creature* p_Creature) -> bool
                    {
                        if (!p_Creature->GetOwner())
                            return true;

                        if (p_Creature->GetOwner() != l_Target)
                            return true;

                        return false;
                    });

                    for (Creature* l_Creature : l_Blades)
                        l_Target->CastSpell(l_Creature, eSpells::BladeTwisterDamage, true);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_ashran_blade_twister_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_ashran_blade_twister_AuraScript();
        }
};

/// Living Bomb - 176670
class spell_ashran_emberfall_living_bomb: public SpellScriptLoader
{
    public:
        spell_ashran_emberfall_living_bomb() : SpellScriptLoader("spell_ashran_emberfall_living_bomb") { }

        class spell_ashran_emberfall_living_bomb_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_ashran_emberfall_living_bomb_AuraScript);

            enum eSpells
            {
                LivingBombTriggered = 176673
            };

            void AfterRemove(constAuraEffectPtr, AuraEffectHandleModes)
            {
                AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                if (removeMode != AuraRemoveMode::AURA_REMOVE_BY_DEATH && removeMode != AuraRemoveMode::AURA_REMOVE_BY_EXPIRE)
                    return;

                if (Unit* l_Caster = GetCaster())
                {
                    if (Unit* l_Target = GetTarget())
                        l_Caster->CastSpell(l_Target, eSpells::LivingBombTriggered, true);
                }
            }

            void Register()
            {
                AfterEffectRemove += AuraEffectRemoveFn(spell_ashran_emberfall_living_bomb_AuraScript::AfterRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_ashran_emberfall_living_bomb_AuraScript();
        }
};

/// Alliance Reward - 178531
/// Horde Reward - 178533
class spell_ashran_faction_rewards : public SpellScriptLoader
{
    public:
        spell_ashran_faction_rewards() : SpellScriptLoader("spell_ashran_faction_rewards") { }

        class spell_ashran_faction_rewards_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ashran_faction_rewards_SpellScript);

            enum Items
            {
                StrongboxHorde      = 120151,
                StrongboxAlliance   = 118065
            };

            void CorrectTargets(std::list<WorldObject*>& p_Targets)
            {
                if (p_Targets.empty())
                    return;

                p_Targets.remove_if([this](WorldObject* p_Object) -> bool
                {
                    if (p_Object == nullptr || p_Object->GetTypeId() != TypeID::TYPEID_PLAYER)
                        return true;

                    Player* l_Player = p_Object->ToPlayer();
                    if (l_Player == nullptr)
                        return true;

                    /// Only one strongbox per day
                    if (!l_Player->CanHaveDailyLootForItem(Items::StrongboxAlliance) ||
                        !l_Player->CanHaveDailyLootForItem(Items::StrongboxHorde))
                        return true;

                    return false;
                });
            }

            void HandleOnHit()
            {
                if (GetHitUnit() == nullptr)
                    return;

                if (Player* l_Player = GetHitUnit()->ToPlayer())
                {
                    if (GetSpellInfo()->Id == eAshranSpells::SpellAllianceReward)
                        l_Player->AddDailyLootCooldown(Items::StrongboxHorde);
                    else
                        l_Player->AddDailyLootCooldown(Items::StrongboxAlliance);
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ashran_faction_rewards_SpellScript::CorrectTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
                OnHit += SpellHitFn(spell_ashran_faction_rewards_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_ashran_faction_rewards_SpellScript();
        }
};

/// Booming Shout - 177150
class spell_ashran_booming_shout : public SpellScriptLoader
{
    public:
        spell_ashran_booming_shout() : SpellScriptLoader("spell_ashran_booming_shout") { }

        class spell_ashran_booming_shout_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ashran_booming_shout_SpellScript);

            void CorrectTargets(std::list<WorldObject*>& p_Targets)
            {
                if (p_Targets.empty())
                    return;

                p_Targets.remove_if([this](WorldObject* p_Object) -> bool
                {
                    if (p_Object == nullptr)
                        return true;

                    if (p_Object->GetEntry() == eCreatures::GaulDunFirok ||
                        p_Object->GetEntry() == eCreatures::MukmarRaz ||
                        p_Object->GetEntry() == eCreatures::KorlokTheOgreKing)
                        return true;

                    return false;
                });
            }

            void HandleDamage(SpellEffIndex p_EffIndex)
            {
                if (Unit* l_Caster = GetCaster())
                {
                    if (Unit* l_Target = GetHitUnit())
                    {
                        float l_MaxRadius = GetSpellInfo()->Effects[p_EffIndex].CalcRadius(l_Caster, GetSpell());
                        float l_Dist = l_Caster->GetDistance(l_Target);
                        float l_Pct = l_Dist / l_MaxRadius;
                        SetHitDamage(int32(GetHitDamage() * l_Pct));
                    }
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ashran_booming_shout_SpellScript::CorrectTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ashran_booming_shout_SpellScript::CorrectTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
                OnEffectHitTarget += SpellEffectFn(spell_ashran_booming_shout_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_ashran_booming_shout_SpellScript();
        }
};

/// Curse of Krong - 165134
class spell_ashran_curse_of_krong : public SpellScriptLoader
{
    public:
        spell_ashran_curse_of_krong() : SpellScriptLoader("spell_ashran_curse_of_krong") { }

        class spell_ashran_curse_of_krong_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_ashran_curse_of_krong_AuraScript);

            void OnTick(constAuraEffectPtr p_AurEff)
            {
                if (Unit* l_Target = GetTarget())
                    l_Target->DealDamage(l_Target, l_Target->CountPctFromMaxHealth(p_AurEff->GetAmount()), nullptr, DOT);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_ashran_curse_of_krong_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_ashran_curse_of_krong_AuraScript();
        }
};

/// Artifacts Collected - 177393
class spell_ashran_artifacts_collected : public SpellScriptLoader
{
    public:
        spell_ashran_artifacts_collected() : SpellScriptLoader("spell_ashran_artifacts_collected") { }

        class spell_ashran_artifacts_collected_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_ashran_artifacts_collected_AuraScript);

            void UpdateCurrentCount(uint32, AuraEffectPtr p_AurEff)
            {
                if (GetCaster() == nullptr)
                    return;

                if (Creature* l_Caster = GetCaster()->ToCreature())
                {
                    ZoneScript* l_ZoneScript = sOutdoorPvPMgr->GetZoneScript(l_Caster->GetZoneId());
                    if (l_ZoneScript == nullptr)
                        return;

                    uint8 l_Type = eArtifactsDatas::CountForMage;
                    uint8 l_TeamID = TeamId::TEAM_ALLIANCE;
                    switch (l_Caster->GetEntry())
                    {
                        case eCreatures::Nisstyr:
                            l_Type = eArtifactsDatas::CountForWarlock;
                            l_TeamID = TeamId::TEAM_HORDE;
                            break;
                        case eCreatures::Marketa:
                            l_Type = eArtifactsDatas::CountForWarlock;
                            break;
                        case eCreatures::Fura:
                            l_TeamID = TeamId::TEAM_HORDE;
                            break;
                        case eCreatures::Kalgan:
                            l_Type = eArtifactsDatas::CountForWarriorPaladin;
                            l_TeamID = TeamId::TEAM_HORDE;
                            break;
                        case eCreatures::ValantBrightsworn:
                            l_Type = eArtifactsDatas::CountForWarriorPaladin;
                            break;
                        case eCreatures::Atomik:
                            l_Type = eArtifactsDatas::CountForDruidShaman;
                            l_TeamID = TeamId::TEAM_HORDE;
                            break;
                        case eCreatures::Anenga:
                            l_Type = eArtifactsDatas::CountForDruidShaman;
                            break;
                        case eCreatures::Ecilam:
                        default:
                            break;
                    }

                    if (OutdoorPvPAshran* l_Ashran = (OutdoorPvPAshran*)l_ZoneScript)
                    {
                        uint32 l_Count = l_Ashran->GetArtifactCollected(l_TeamID, l_Type);
                        p_AurEff->ChangeAmount(l_Count);
                    }
                }
            }

            void SetMaxCount(constAuraEffectPtr p_AurEff, int32& p_Amount, bool& p_CanBeRecalculated)
            {
                if (GetCaster() == nullptr)
                    return;

                if (Creature* l_Caster = GetCaster()->ToCreature())
                {
                    switch (l_Caster->GetEntry())
                    {
                        case eCreatures::Marketa:
                        case eCreatures::Nisstyr:
                            p_Amount = eArtifactsDatas::MaxCountForWarlock;
                            break;
                        case eCreatures::Ecilam:
                        case eCreatures::Fura:
                            p_Amount = eArtifactsDatas::MaxCountForMage;
                            break;
                        case eCreatures::Kalgan:
                        case eCreatures::ValantBrightsworn:
                            p_Amount = eArtifactsDatas::MaxCountForWarriorPaladin;
                            break;
                        case eCreatures::Atomik:
                        case eCreatures::Anenga:
                            p_Amount = eArtifactsDatas::MaxCountForDruidShaman;
                            break;
                        default:
                            break;
                    }
                }
            }

            void Register()
            {
                OnEffectUpdate += AuraEffectUpdateFn(spell_ashran_artifacts_collected_AuraScript::UpdateCurrentCount, EFFECT_0, SPELL_AURA_DUMMY);
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_ashran_artifacts_collected_AuraScript::SetMaxCount, EFFECT_1, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_ashran_artifacts_collected_AuraScript();
        }
};

/// Stone Empowerment - 170896
class spell_ashran_stone_empowerment : public SpellScriptLoader
{
    public:
        spell_ashran_stone_empowerment() : SpellScriptLoader("spell_ashran_stone_empowerment") { }

        enum eSpell
        {
            StoneEmpowermentProc = 170897
        };

        class spell_ashran_stone_empowerment_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_ashran_stone_empowerment_AuraScript);

            void OnProc(constAuraEffectPtr p_AurEff, ProcEventInfo& p_EventInfo)
            {
                PreventDefaultAction();

                /// Caster is Kronus, target are enemies
                Unit* l_Caster = GetCaster();
                if (!l_Caster)
                    return;

                if (p_EventInfo.GetActionTarget() == l_Caster)
                    return;

                l_Caster->CastSpell(l_Caster, eSpell::StoneEmpowermentProc, true);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_ashran_stone_empowerment_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_ashran_stone_empowerment_AuraScript();
        }
};

/// Summon Disposable Pocket Flying Machine - 168232 (Alliance)
/// Summon Disposable Pocket Flying Machine - 170407 (Horde)
class spell_ashran_pocket_flying_machine : public SpellScriptLoader
{
    public:
        spell_ashran_pocket_flying_machine() : SpellScriptLoader("spell_ashran_pocket_flying_machine") { }

        class spell_ashran_pocket_flying_machine_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_ashran_pocket_flying_machine_SpellScript);

            enum eSpells
            {
                DistrubutionAlliance    = 168232,
                DistrubitionHorde       = 170407
            };

            void HandleScriptEffect()
            {
                if (GetHitUnit() == nullptr)
                    return;

                if (Player* l_Player = GetHitUnit()->ToPlayer())
                {
                    ZoneScript* l_ZoneScript = sOutdoorPvPMgr->GetOutdoorPvPToZoneId(l_Player->GetZoneId());
                    if (l_ZoneScript == nullptr)
                        return;

                    if (OutdoorPvPAshran* l_Ashran = (OutdoorPvPAshran*)l_ZoneScript)
                    {
                        uint32 l_ArtifactCount = l_Player->GetCurrency(CurrencyTypes::CURRENCY_TYPE_ARTIFACT_FRAGEMENT, true);
                        l_Player->ModifyCurrency(CurrencyTypes::CURRENCY_TYPE_ARTIFACT_FRAGEMENT, -int32(l_ArtifactCount * CURRENCY_PRECISION), false);

                        uint32 l_Modulo = l_ArtifactCount % eArtifactsDatas::MaxArtifactCounts;
                        uint32 l_Count = l_ArtifactCount / eArtifactsDatas::MaxArtifactCounts;
                        uint8 l_Rand = urand(0, eArtifactsDatas::MaxArtifactCounts - 1);

                        uint32 l_SpellID = GetSpellInfo()->Id;
                        for (uint8 l_I = 0; l_I < eArtifactsDatas::MaxArtifactCounts; ++l_I)
                        {
                            if (l_SpellID == eSpells::DistrubutionAlliance)
                            {
                                if (l_I == l_Rand)
                                    l_Ashran->AddCollectedArtifacts(TeamId::TEAM_ALLIANCE, l_I, l_Count + l_Modulo);
                                else
                                    l_Ashran->AddCollectedArtifacts(TeamId::TEAM_ALLIANCE, l_I, l_Count);
                            }
                            else
                            {
                                if (l_I == l_Rand)
                                    l_Ashran->AddCollectedArtifacts(TeamId::TEAM_HORDE, l_I, l_Count + l_Modulo);
                                else
                                    l_Ashran->AddCollectedArtifacts(TeamId::TEAM_HORDE, l_I, l_Count);
                            }
                        }

                        l_Ashran->RewardHonorAndReputation(l_ArtifactCount, l_Player);
                    }
                }
            }

            void Register() override
            {
                OnHit += SpellHitFn(spell_ashran_pocket_flying_machine_SpellScript::HandleScriptEffect);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_ashran_pocket_flying_machine_SpellScript();
        }
};

void AddSC_AshranSpells()
{
    new spell_ashran_blade_twister();
    new spell_ashran_emberfall_living_bomb();
    new spell_ashran_faction_rewards();
    new spell_ashran_booming_shout();
    new spell_ashran_curse_of_krong();
    new spell_ashran_artifacts_collected();
    new spell_ashran_stone_empowerment();
    new spell_ashran_pocket_flying_machine();
}