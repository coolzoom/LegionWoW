
////////////////////////////////////////////////////////////////////////////////
///
///  MILLENIUM-STUDIO
///  Copyright 2015 Millenium-studio SARL
///  All Rights Reserved.
///
////////////////////////////////////////////////////////////////////////////////

#include "ScriptedCreature.h"
#include "auchindon.hpp"

enum eTerongorSpells
{
    SpellAgony                              = 156925,
    SpellChaosBolt                          = 156975,
    SpellChaosWaveDummy                     = 157001,
    SpellChaosWaveDmg                       = 157002,
    SpellConflagrate                        = 154083,
    SpellCorruptionDummy                    = 170608,
    SpellCorruptionDmg                      = 156842,
    SpellCurseOfExhaustionDebuff            = 164841,
    SpellDemonicLeapDummy                   = 157039,
    SpellDemonicLeapAreatriger              = 157040,
    SpellDoomBuff                           = 156965,
    SpellDrainLife                          = 156854,
    SpellImmolate                           = 156964,
    SpellIncinrate                          = 156963,
    SpellRainOfFire                         = 165757,
    SpellSeedOfMalevolenceApplyAura         = 156921,
    SpellSeedOfMalevolenceBuff              = 166451,
    SpellSeedOfMalevolenceDmg               = 156924,
    SpellSeedOfMalevolenceVisualTriger      = 166462,
    SpellShadowBolt                         = 156829,
    SpellTouchOfChaosDummy                  = 169028,
    SpellTouchOfChaosDmg                    = 156968,
    SpellUnstableAffliction                 = 156954,
    SpellWrathCleave                        = 159035,
    SpellWrathStorm                         = 159033,
    SpellTranscend                          = 164009,
    SpellAfflictionTransform                = 156863,
    SpellDestructionTransform               = 156866,
    SpellDemonologyTransform                = 156919,
    SpellSummonAbyssalMeteor                = 164508,
    SpellSummonAbyssalGroundEffect          = 159681,
    SpellSummonAbyssalDummy                 = 157214,
    SpellSummonAbyssalSummonSpell           = 157216,
    SpellDemonicCircleVisual                = 149133,
    SpellTeronogorShield                    = 157017
};

enum eTerongorEvents
{
    EventAgony = 1,
    EventChaosBolt,
    EventChaosWave,
    EventConflagrate,
    EventCorruption,
    EventCurseOfExhaustion,
    EventDemonicLeap,
    EventDoom,
    EventDrainLife,
    EventImmolate,
    EventIncinrate,
    EventRainOfFire,
    EventSeedOfMalevolence,
    EventTouchOfChaos,
    EventUnstableAffliction,
    EventShadowBolt,
    EventWrathcleave,
    EventWrathstorm,
    EventBloomOfMalevolence,
    EventDepassive,
    EventTransform,
    EventTransformRemovePassive
};

enum eTerongorTalks
{
    TERONGOR_INTRO_01 = 42, ///< p_Who know the draenei held such...delicious treasure in their temple?  (44423)
    TERONGOR_INTRO_02 = 43, ///< Do you dare challenge me,defenders of Auchindoun?!(44424)
    TERONGOR_INTRO_03 = 44, ///< Such decadence...it will all burn. (44425)
    TERONGOR_INTRO_05 = 45, ///< Gul'dan, such foolshness. This gift...so much more you could ever know...(44427)
    TERONGOR_INTRO_06 = 46, ///< Long have i waited...(44428)
    TERONGOR_INTRO_07 = 47, ///< ...hungered... to be more... (44429)
    TERONGOR_INTRO_08 = 48, ///<  And now, all shall bow before me!(44430)
    TERONGOR_KILL_01  = 49, ///< All will fall before me!(44431)
    TERONGOR_AGGRO_01 = 50, ///< This power. you will be the first to know it.(44418)
    TERONGOR_SPELL_01 = 52, ///< Destruction!(44433)
    TERONGOR_SPELL_02 = 53, ///< Wither.. away! (44434)
    TERONGOR_SPELL_03 = 53, ///< I become something greater!(44435)
    TERONGOR_SPELL_04 = 54, ///< Die! (44436)
    TERONGOR_SPELL_05 = 55, ///< Your demise awaits! (44437)
    TERONGOR_SPELL_06 = 56, ///< Quickly now. (44438)
    TERONGOR_SPELL_07 = 57, ///< More! I...need...more!(44439)
    TERONGOR_EVENT_01 = 60, ///< Jorrun.. p_Who battle demons in life, in death.. your power will feed them! (44420)
    TERONGOR_EVENT_02 = 61, ///< Joraa, paragon of order - i shall twist your soul to power Destruction!(44421)
    TERONGOR_EVENT_03 = 61, ///< Elum, life time of healing... now, you shall fuel Deziz and Decay!(44422)
    TERONGOR_DEATH    = 100 ///< (44419)
};

enum eTeronogorActions
{
    ActionTransport = 1,
    ActionChoosePower
};

enum eTreonogorTriggers
{
    TriggerSummonAbyssal = 213593,
};

enum eTeronogorTransformations
{
    TransformationAffliction  = 0,
    TransformationDestruction = 1,
    TransformationDemonology  = 2,
    TransformationPreChannel  = 3,
    TransformationOccur       = 4,
    TransformationOccured     = 5
};

Position g_PositionFirstPlatformFirstMove   = { 1910.91f, 2810.94f, 119.795f }; // DURAG
Position g_PositionFirstPlatormSecondMove   = { 1959.16f, 2907.14f, 41.030f };
Position g_PositionFirstPlatformThirdMove   = { 2003.36f, 2863.18f, 35.212f };
Position g_PositionSecondPlatformFirstMove  = { 1981.34f, 2877.99f, 53.373f }; // GULKOSH
Position g_PositionSecondPlatformSecondMove = { 1959.05f, 2999.68f, 75.242f };
Position g_PositionSecondPlatformThirdMove  = { 2003.70f, 3043.89f, 35.212f };
Position g_PositionThirdPlatformFirstMove   = { 2003.70f, 3043.89f, 56.912f }; // GROMTASH
Position g_PositionThirdPlatformsSecondMove = { 1914.66f, 2991.45f, 77.863f };
Position g_PositionThirdPlatformThirdMove   = { 1817.49f, 3046.65f, 35.212f };
Position g_PositionFourthMovement           = { 1846.60f, 2950.43f, 15.170f };
Position g_PositionPlatform_3               = { 1838.42f, 3027.05f, 35.283f, 2.149401f }; // CREATURE_GROMTASH_THE_DESTRUCTOR
Position g_PositionDrain                    = { 1960.20f, 3000.69f, 16.236f, 0.847815f };
Position g_PositionTeronogorStartingPoint[1]=
{
    { 1923.63f, 2974.06f, 16.844f, 1.104046f }
};
Position g_PositionPlatform_01[2] =
{
    { 1985.33f, 2876.17f, 35.282f, 5.431586f }, // CREATURE_ZIPTEQ 
    { 1987.57f, 2880.12f, 35.282f, 5.169260f }, //CREATURE_DURAG_THE_DOMINATOR
};
Position g_PositionPlatform_02[2] =
{
    { 1983.61f, 3030.35f, 35.280f, 0.613946f }, // CREATURE_SHAADUM  
    { 1987.36f, 3023.54f, 35.282f, 0.747463f }, //CREATURE_GULKOSH
};
Position g_Positionsoul_move[4] =
{
    { 2010.29f, 2855.26f, 35.213f, 2.397908f },
    { 2011.11f, 3051.70f, 35.212f, 4.003247f },
    { 1812.13f, 3052.10f, 35.212f, 5.536366f },
    { 1812.37f, 2854.15f, 35.212f, 0.796488f },
};
Position g_Positiondead_souls[3] =
{
    { 1922.36f, 2988.91f, 27.743f, 4.405081f },
    { 1946.59f, 2973.00f, 30.193f, 3.678247f },
    { 1963.11f, 3003.42f, 22.359f, 3.904775f },
};

class teronogor_secondphase_transformation : public BasicEvent
{
public:
    explicit teronogor_secondphase_transformation(Unit* p_Unit, int32 p_Value, int32 p_TransformationType) : m_Obj(p_Unit), m_Modifier(p_Value), m_tType(p_TransformationType)
    {
    }

    bool Execute(uint64 /*p_CurrTime*/, uint32 /*p_p_Diff*/)
    {
        if (m_Obj)
        {
            if (InstanceScript* l_Instance = m_Obj->GetInstanceScript())
            {
                if (Creature* l_Teronogor = l_Instance->instance->GetCreature(l_Instance->GetData64(eDataAuchindonDatas::DataBossTeronogor)))
                {
                    if (Creature* l_Iruun = l_Instance->instance->GetCreature(l_Instance->GetData64(eDataAuchindonDatas::DataIruun)))
                    {
                        if (Creature* l_Jorra = l_Instance->instance->GetCreature(l_Instance->GetData64(eDataAuchindonDatas::DataJorra)))
                        {
                            if (Creature* l_Elum = l_Instance->instance->GetCreature(l_Instance->GetData64(eDataAuchindonDatas::DataElum)))
                            {
                                if (l_Teronogor->GetAI())
                                {
                                    switch (m_Modifier)
                                    {
                                        case eTeronogorTransformations::TransformationPreChannel:
                                        {
                                            switch (m_tType)
                                            {
                                                case eTeronogorTransformations::TransformationAffliction:
                                                    l_Teronogor->CastSpell(l_Elum, SpellDrainSoulVisual);
                                                    break;
                                                case eTeronogorTransformations::TransformationDestruction:
                                                    l_Teronogor->CastSpell(l_Elum, SpellDrainSoulVisual);
                                                    break;
                                                case eTeronogorTransformations::TransformationDemonology:
                                                    l_Teronogor->CastSpell(l_Elum, SpellDrainSoulVisual);
                                                    break;
                                            }

                                            l_Teronogor->m_Events.AddEvent(new teronogor_secondphase_transformation(l_Teronogor, eTeronogorTransformations::TransformationOccur, 0), l_Teronogor->m_Events.CalculateTime(5 * TimeConstants::IN_MILLISECONDS));
                                            break;
                                        }
                                        case eTeronogorTransformations::TransformationOccur:
                                        {
                                            switch (m_tType)
                                            {
                                                case eTeronogorTransformations::TransformationAffliction:
                                                    l_Teronogor->CastSpell(l_Teronogor, SpellAfflictionTransform);
                                                    break;
                                                case eTeronogorTransformations::TransformationDestruction:
                                                    l_Teronogor->CastSpell(l_Teronogor, SpellDestructionTransform);
                                                    break;
                                                case eTeronogorTransformations::TransformationDemonology:
                                                    l_Teronogor->CastSpell(l_Teronogor, SpellDemonologyTransform);
                                                    break;
                                            }

                                            l_Teronogor->CastStop();
                                            l_Teronogor->RemoveFlag(EUnitFields::UNIT_FIELD_FLAGS, eUnitFlags::UNIT_FLAG_IMMUNE_TO_PC);
                                            l_Teronogor->UpdatePosition(l_Teronogor->GetPositionX(), l_Teronogor->GetPositionY(), l_Teronogor->GetPositionZ(), l_Teronogor->GetOrientation());
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }

                    return true;
                }
            }
        }
    }

private:
    Unit* m_Obj;
    int32 m_Modifier;
    int32 m_tType;
    int32 m_Event;
};

/// Teronogor - 
class auchindon_boss_terongor : public CreatureScript
{
public:
    auchindon_boss_terongor() : CreatureScript("auchindon_boss_terongor") { }

    struct boss_terongorAI : public BossAI
    {
        boss_terongorAI(Creature* p_Creature) : BossAI(p_Creature, DataBossTeronogor)
        {
            m_Instance = me->GetInstanceScript();
            m_Intro = false;

            Reset();
            me->Respawn(true);

            m_SoulTransport01 = false;
            m_SoulTransport02 = false;
            m_SoulTransport03 = false;
            m_SoulTransport04 = false;
            m_SoulTransport05 = false;

            me->GetMap()->SetObjectVisibility(1000.0f);
        }

        InstanceScript* m_Instance;
        bool m_SecondPhase;
        bool m_Intro;
        bool m_SoulTransport01;
        bool m_SoulTransport02;
        bool m_SoulTransport03;
        bool m_SoulTransport04;
        bool m_SoulTransport05;

        void Reset() override
        {
            _Reset();
            events.Reset();
          
            me->SetReactState(REACT_DEFENSIVE);
            me->SetCurrentEquipmentId(1);
            m_SecondPhase = false;

            me->CastSpell(me, eTerongorSpells::SpellDemonicCircleVisual); 
            me->AddAura(eTerongorSpells::SpellTeronogorShield, me);
       
            if (Creature* l_Jorra = m_Instance->instance->GetCreature(m_Instance->GetData64(eDataAuchindonDatas::DataJorra)))
            {
                me->CastSpell(l_Jorra, eAuchindonSpells::SpellDrainSoulVisual);
            }
        }

        void MoveInLineOfSight(Unit* p_Who) override
        {
            if (p_Who && p_Who->IsInWorld() && p_Who->GetTypeId() == TypeID::TYPEID_PLAYER && me->IsWithinDistInMap(p_Who, 18.0f) && !m_Intro)
            {
                m_Intro = true;
                Talk(eTerongorTalks::TERONGOR_INTRO_01);
            }
        }

        void JustReachedHome() override
        {
            summons.DespawnAll();
            DespawnCreaturesInArea(eAuchindonCreatures::CreatureFelborneAbyssal, me);

            if (m_Instance != nullptr)
            {
                instance->SetBossState(eDataAuchindonDatas::DataBossTeronogor, EncounterState::FAIL);
            }
        }

        void DamageTaken(Unit* p_Attacker, uint32 &p_Damage, SpellInfo const* p_SpellInfo) override
        {
            if (me->GetHealthPct() <= 75 && !m_SecondPhase)
            {
                m_SecondPhase = true;
                events.Reset();

                me->SetFlag(EUnitFields::UNIT_FIELD_FLAGS, eUnitFlags::UNIT_FLAG_NON_ATTACKABLE | eUnitFlags::UNIT_FLAG_IMMUNE_TO_PC);
                me->SetReactState(ReactStates::REACT_PASSIVE);

                DoAction(eTeronogorActions::ActionChoosePower);
            }
        }

        void DoAction(int32 const p_Action) override
        {
            switch (p_Action)
            {
                case ActionSoulMove1:
                    m_SoulTransport01 = true;
                    break;
                case ActionSoulMove2:
                    m_SoulTransport02 = true;
                    break;
                case ActionSoulMove3:
                    m_SoulTransport03 = true;
                    break;
                case ActionSoulMove4:
                    m_SoulTransport04 = true;
                    break;
                case ActionChoosePower:
                    events.Reset();

                    switch (urand(eTeronogorTransformations::TransformationAffliction, eTeronogorTransformations::TransformationDemonology))
                    {
                        case eTeronogorTransformations::TransformationAffliction: // Mender Elum - Affliction
                            events.ScheduleEvent(eTerongorEvents::EventShadowBolt, urand(8 * TimeConstants::IN_MILLISECONDS, 10 * TimeConstants::IN_MILLISECONDS));
                            events.ScheduleEvent(eTerongorEvents::EventCurseOfExhaustion, 13 * TimeConstants::IN_MILLISECONDS);
                            events.ScheduleEvent(eTerongorEvents::EventSeedOfMalevolence, urand(22 * TimeConstants::IN_MILLISECONDS, 25 * TimeConstants::IN_MILLISECONDS));
                            events.ScheduleEvent(eTerongorEvents::EventAgony, 16 * TimeConstants::IN_MILLISECONDS);
                            events.ScheduleEvent(eTerongorEvents::EventDrainLife, urand(13 * TimeConstants::IN_MILLISECONDS, 16 * TimeConstants::IN_MILLISECONDS));
                            events.ScheduleEvent(eTerongorEvents::EventUnstableAffliction, 20 * TimeConstants::IN_MILLISECONDS);

                            me->m_Events.AddEvent(new teronogor_secondphase_transformation(me, eTeronogorTransformations::TransformationPreChannel, 0), me->m_Events.CalculateTime(2 * TimeConstants::IN_MILLISECONDS));
                            Talk(eTerongorTalks::TERONGOR_EVENT_03);
                            break;
                        case eTeronogorTransformations::TransformationDestruction: // Arcanist Jorra's - destruction
                            events.ScheduleEvent(eTerongorEvents::EventChaosBolt, 20 * TimeConstants::IN_MILLISECONDS);
                            events.ScheduleEvent(eTerongorEvents::EventImmolate, urand(10 * TimeConstants::IN_MILLISECONDS, 14 * TimeConstants::IN_MILLISECONDS));
                            events.ScheduleEvent(eTerongorEvents::EventConflagrate, urand(8 * TimeConstants::IN_MILLISECONDS, 10 * TimeConstants::IN_MILLISECONDS));
                            events.ScheduleEvent(eTerongorEvents::EventRainOfFire, 24 * TimeConstants::IN_MILLISECONDS);
                            events.ScheduleEvent(eTerongorEvents::EventIncinrate, 16 * TimeConstants::IN_MILLISECONDS);

                            me->m_Events.AddEvent(new teronogor_secondphase_transformation(me, eTeronogorTransformations::TransformationPreChannel, 1), me->m_Events.CalculateTime(2 * TimeConstants::IN_MILLISECONDS));
                            Talk(eTerongorTalks::TERONGOR_EVENT_01);
                            break;
                        case eTeronogorTransformations::TransformationDemonology: // Vindication Iruun's - demonology
                            events.ScheduleEvent(eTerongorEvents::EventDoom, urand(8 * TimeConstants::IN_MILLISECONDS, 12 * TimeConstants::IN_MILLISECONDS));
                            events.ScheduleEvent(eTerongorEvents::EventDemonicLeap, urand(10 * TimeConstants::IN_MILLISECONDS, 14 * TimeConstants::IN_MILLISECONDS));
                            events.ScheduleEvent(eTerongorEvents::EventCurseOfExhaustion, 18 * TimeConstants::IN_MILLISECONDS);
                            events.ScheduleEvent(eTerongorEvents::EventCorruption, urand(10 * TimeConstants::IN_MILLISECONDS, 14 * TimeConstants::IN_MILLISECONDS));
                            events.ScheduleEvent(eTerongorEvents::EventChaosBolt, 25 * TimeConstants::IN_MILLISECONDS);
                            events.ScheduleEvent(eTerongorEvents::EventTouchOfChaos, 16 * TimeConstants::IN_MILLISECONDS);

                            me->m_Events.AddEvent(new teronogor_secondphase_transformation(me, eTeronogorTransformations::TransformationPreChannel, 2), me->m_Events.CalculateTime(2 * TimeConstants::IN_MILLISECONDS));
                            Talk(eTerongorTalks::TERONGOR_EVENT_02);
                            break;
                }
                break;
            }
        }

        void EnterCombat(Unit* /*p_Who*/) override
        {
            _EnterCombat();
            me->RemoveAura(eTerongorSpells::SpellTeronogorShield);

            events.ScheduleEvent(eTerongorEvents::EventShadowBolt, urand(8 * TimeConstants::IN_MILLISECONDS, 16 * TimeConstants::IN_MILLISECONDS));
            events.ScheduleEvent(eTerongorEvents::EventCorruption, urand(10 * TimeConstants::IN_MILLISECONDS, 12 * TimeConstants::IN_MILLISECONDS));
            events.ScheduleEvent(eTerongorEvents::EventRainOfFire, 21 * TimeConstants::IN_MILLISECONDS);
            events.ScheduleEvent(eTerongorEvents::EventDrainLife, 16 * TimeConstants::IN_MILLISECONDS);

            if (m_Instance != nullptr)
            {
                m_Instance->SetBossState(eDataAuchindonDatas::DataBossTeronogor, EncounterState::IN_PROGRESS);
                m_Instance->SendEncounterUnit(EncounterFrameType::ENCOUNTER_FRAME_ENGAGE, me);
                DoZoneInCombat();

                if (me->GetMap() && me->GetMap()->IsHeroic())
                {
                    Position l_Position;
                    me->GetRandomNearPosition(l_Position, 10.0f);

                    me->SummonCreature(TriggerSummonAbyssal, l_Position, TempSummonType::TEMPSUMMON_MANUAL_DESPAWN);
                }
            }

            Talk(eTerongorTalks::TERONGOR_AGGRO_01);
        }

        void KilledUnit(Unit* p_Who) override
        {
            if (p_Who->GetTypeId() == TypeID::TYPEID_PLAYER)
                 Talk(eTerongorTalks::TERONGOR_KILL_01);
        }

        void JustDied(Unit* /*p_Killer*/) override
        {
            _JustDied();

            if (m_Instance != nullptr)
                m_Instance->SetBossState(eDataAuchindonDatas::DataBossTeronogor, EncounterState::DONE);


            DespawnCreaturesInArea(eAuchindonCreatures::CreatureFelborneAbyssal, me); 
            Talk(eTerongorTalks::TERONGOR_DEATH);

            me->SummonGameObject(GameobjectChestAucheni, 1891.84f, 2973.80f, 16.844f, 5.664811f, 0,0,0,0,0);
        }

        void UpdateAI(uint32 const p_Diff) override
        {
            events.Update(p_Diff);

            if (!UpdateVictim())
                return;

            if (me->HasUnitState(UnitState::UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
                    case EventShadowBolt:
                    {
                        if (Unit* l_Target = me->getVictim())
                            me->CastSpell(l_Target, SpellShadowBolt);

                        events.ScheduleEvent(EventShadowBolt, urand(6 * TimeConstants::IN_MILLISECONDS, 8 * TimeConstants::IN_MILLISECONDS));
                        break;
                    }
                    case EventCorruption:
                    {
                        if (Unit* l_Random = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 50.0f, true))
                        {
                            me->CastSpell(l_Random, SpellCorruptionDummy);

                            events.ScheduleEvent(EventCorruption, urand(10 * TimeConstants::IN_MILLISECONDS, 15 * TimeConstants::IN_MILLISECONDS));
                        }
                        break;
                    }
                    case EventDrainLife:
                    {
                        if (Unit* l_Target = me->getVictim())
                            me->CastSpell(l_Target, SpellDrainLife);

                        events.ScheduleEvent(EventDrainLife, 16 * TimeConstants::IN_MILLISECONDS);
                        break;
                    }
                    case EventCurseOfExhaustion:
                    {
                        if (Unit* l_Random = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 50.0f, true))
                        {
                            me->CastSpell(l_Random, SpellCurseOfExhaustionDebuff);

                            events.ScheduleEvent(EventCurseOfExhaustion, 13 * TimeConstants::IN_MILLISECONDS);
                        }
                        break;
                    }
                    case EventAgony:
                    {
                        if (Unit* l_Random = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 50.0f, true))
                        {
                            me->CastSpell(l_Random, SpellAgony);

                            events.ScheduleEvent(EventAgony, 16 * TimeConstants::IN_MILLISECONDS);
                        }
                        break;
                    }
                    case EventUnstableAffliction:
                    {
                        if (Unit* l_Random = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 50.0f, true))
                        {
                            me->CastSpell(l_Random, SpellUnstableAffliction);
                            events.ScheduleEvent(EventUnstableAffliction, 20 * TimeConstants::IN_MILLISECONDS);
                        }
                        break;
                    }
                    case EventSeedOfMalevolence:
                    {
                        if (Unit* l_Random = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 50.0f, true))
                        {
                            me->CastSpell(l_Random, SpellSeedOfMalevolenceApplyAura);
                            events.ScheduleEvent(EventSeedOfMalevolence, urand(22 * TimeConstants::IN_MILLISECONDS, 25 * TimeConstants::IN_MILLISECONDS));
                        }
                        break;
                    }
                    case EventChaosBolt:
                    {
                        if (Unit* l_Target = me->getVictim())
                        me->CastSpell(me->getVictim(), SpellChaosBolt);

                        events.ScheduleEvent(EventChaosBolt, 20 * TimeConstants::IN_MILLISECONDS);
                        break;
                    }
                    case EventImmolate:
                    {
                        if (Unit* l_Random = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 50.0f, true))
                        {
                            me->CastSpell(l_Random, SpellImmolate);
                            events.ScheduleEvent(EventImmolate, 20 * TimeConstants::IN_MILLISECONDS);
                            break;
                        }
                    }
                    case EventConflagrate:
                    {
                        if (Unit* l_Target = me->getVictim())
                            me->CastSpell(l_Target, SpellConflagrate);

                        events.ScheduleEvent(EventConflagrate, urand(15 * TimeConstants::IN_MILLISECONDS, 20 * TimeConstants::IN_MILLISECONDS));
                        break;
                    }
                    case EventIncinrate:
                    {
                        if (Unit* l_Target = me->getVictim())
                            me->CastSpell(l_Target, SpellIncinrate);

                        events.ScheduleEvent(EventIncinrate, 16 * TimeConstants::IN_MILLISECONDS);
                        break;
                    }
                    case EventRainOfFire:
                        if (Unit* l_Random = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 50.0f, true))
                        {
                            me->CastSpell(l_Random, SpellRainOfFire);

                            events.ScheduleEvent(EventRainOfFire, 25 * TimeConstants::IN_MILLISECONDS);
                            break;
                        }
                    case EventDoom:
                    {
                        if (Unit* l_Random = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 50.0f, true))
                        {
                            me->CastSpell(l_Random, SpellDoomBuff);
                            events.ScheduleEvent(EventDoom, urand(8 * TimeConstants::IN_MILLISECONDS, 12 * TimeConstants::IN_MILLISECONDS));
                            break;
                        }
                    }
                    case EventDemonicLeap:
                    {
                        if (Unit* l_Random = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 50.0f, true))
                        {
                            me->CastSpell(l_Random, SpellDemonicLeapDummy);

                            events.ScheduleEvent(EventDemonicLeap, urand(18 * TimeConstants::IN_MILLISECONDS, 30 * TimeConstants::IN_MILLISECONDS));
                            break;
                        }
                    }
                    case EventChaosWave:
                    {
                        if (Unit* l_Target = me->getVictim())
                            me->CastSpell(l_Target, SpellChaosWaveDummy);

                        events.ScheduleEvent(EventChaosWave, urand(8 * TimeConstants::IN_MILLISECONDS, 10 * TimeConstants::IN_MILLISECONDS));
                        break;
                    }
                    case EventTouchOfChaos:
                    {
                        if (Unit* l_Target = me->getVictim())
                            me->CastSpell(l_Target, SpellTouchOfChaosDummy);

                        events.ScheduleEvent(EventTouchOfChaos, 16 * TimeConstants::IN_MILLISECONDS);
                        break;
                    }
                }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* p_Creature) const override
    {
        return new boss_terongorAI(p_Creature);
    }
};

/// Durag - 
class auchindon_teronogor_durag : public CreatureScript
{
public:
    auchindon_teronogor_durag() : CreatureScript("auchindon_teronogor_durag") { }

    struct auchindon_creaturesAI : public ScriptedAI
    {
        auchindon_creaturesAI(Creature* p_Creature) : ScriptedAI(p_Creature)
        {
            m_Instance = me->GetInstanceScript();

            if (me->GetMap())
            me->GetMap()->SetObjectVisibility(1000.0f);
        }

        InstanceScript* m_Instance;

        void Reset() override
        {
            events.Reset();

            if (Creature* l_Zipteq = me->FindNearestCreature(CreatureZipteq, 20.0f, true))
                l_Zipteq->Respawn(true);

            // Cosmetic channel - 
            if (Creature* l_Teronogor = m_Instance->instance->GetCreature(m_Instance->GetData64(eDataAuchindonDatas::DataBossTeronogor)))
            {
                
            }
        }

        void EnterCombat(Unit* p_Attacker) override
        { 
            me->CastSpell(me, 159021);

            events.ScheduleEvent(eTerongorEvents::EventShadowBolt, urand(8 * TimeConstants::IN_MILLISECONDS, 16 * TimeConstants::IN_MILLISECONDS));
            events.ScheduleEvent(eTerongorEvents::EventCorruption, urand(10 * TimeConstants::IN_MILLISECONDS, 14 * TimeConstants::IN_MILLISECONDS));
            events.ScheduleEvent(eTerongorEvents::EventChaosWave, urand(8 * TimeConstants::IN_MILLISECONDS, 10 * TimeConstants::IN_MILLISECONDS));
        }

        void UpdateAI(const uint32 p_Diff) override
        {
            events.Update(p_Diff);

            if (!UpdateVictim())
                return;

            switch (events.ExecuteEvent())
            {
                case eTerongorEvents::EventShadowBolt:
                    if (Unit* l_Target = me->getVictim())
                        me->CastSpell(l_Target, eTerongorSpells::SpellShadowBolt);

                    events.ScheduleEvent(eTerongorEvents::EventShadowBolt, urand(8 * TimeConstants::IN_MILLISECONDS, 10 * TimeConstants::IN_MILLISECONDS));
                    break;
                case eTerongorEvents::EventCorruption:
                    if (Unit* l_Random = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 50.0f, true))
                    {
                        me->CastSpell(l_Random, eTerongorSpells::SpellCorruptionDummy);
                        
                        events.ScheduleEvent(eTerongorEvents::EventCorruption, urand(10 * TimeConstants::IN_MILLISECONDS, 14 * TimeConstants::IN_MILLISECONDS));
                    }
                    break;
                case eTerongorEvents::EventChaosWave:
                    if (Unit* l_Target = me->getVictim())
                        me->CastSpell(l_Target, eTerongorSpells::SpellChaosWaveDummy);

                    events.ScheduleEvent(eTerongorEvents::EventChaosWave, urand(8 * TimeConstants::IN_MILLISECONDS, 10 * TimeConstants::IN_MILLISECONDS));
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* p_Creature) const override
    {
        return new auchindon_creaturesAI(p_Creature);
    }
};

/// Gulkosh - 
class auchindon_teronogor_gulkosh : public CreatureScript
{
public:
    auchindon_teronogor_gulkosh() : CreatureScript("auchindon_teronogor_gulkosh") { }

    struct auchindon_creaturesAI : public ScriptedAI
    {
        auchindon_creaturesAI(Creature* p_Creature) : ScriptedAI(p_Creature)
        {
            m_Instance = me->GetInstanceScript();

            if (me->GetMap())
            me->GetMap()->SetObjectVisibility(1000.0f);
        }

        InstanceScript* m_Instance;

        void Reset() override
        {
            if (Creature* l_Shaddum = me->FindNearestCreature(eAuchindonCreatures::CreatureShaadum, 20.0f, true))
                l_Shaddum->Respawn(true);

            if (Creature* l_Teronogor = m_Instance->instance->GetCreature(m_Instance->GetData64(eDataAuchindonDatas::DataBossTeronogor)))
            {
            }
        }

        void EnterCombat(Unit* p_Attacker) override
        {
            events.ScheduleEvent(EventShadowBolt, 8 * TimeConstants::IN_MILLISECONDS);
            events.ScheduleEvent(EventUnstableAffliction, urand(10 * TimeConstants::IN_MILLISECONDS, 12 * TimeConstants::IN_MILLISECONDS));
            events.ScheduleEvent(EventDrainLife, 16 * TimeConstants::IN_MILLISECONDS);
        }

        void UpdateAI(const uint32 p_Diff) override
        {
            events.Update(p_Diff);

            if (!UpdateVictim())
                return;

            switch (events.ExecuteEvent())
            {
                case EventShadowBolt:
                    if (Unit* l_Target = me->getVictim())
                        me->CastSpell(l_Target, SpellShadowBolt);

                    events.ScheduleEvent(EventShadowBolt, urand(8 * TimeConstants::IN_MILLISECONDS, 10 * TimeConstants::IN_MILLISECONDS));
                    break;
                case EventUnstableAffliction:
                    if (Unit* l_Random = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 50.0f, true))
                    {
                        me->CastSpell(l_Random, SpellUnstableAffliction);
                        events.ScheduleEvent(EventUnstableAffliction, urand(10 * TimeConstants::IN_MILLISECONDS, 14 * TimeConstants::IN_MILLISECONDS));
                    }
                    break;
                case EventDrainLife:
                    if (Unit* l_Target = me->getVictim())
                        me->CastSpell(l_Target, SpellDrainLife);

                    events.ScheduleEvent(EventDrainLife, 16 * TimeConstants::IN_MILLISECONDS);
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* p_Creature) const override
    {
        return new auchindon_creaturesAI(p_Creature);
    }
};

/// Shaduum - 
class auchindon_teronogor_shaadum : public CreatureScript
{
public:
    auchindon_teronogor_shaadum() : CreatureScript("auchindon_teronogor_shaadum") { }

    struct auchindon_creaturesAI : public ScriptedAI
    {
        auchindon_creaturesAI(Creature* p_Creature) : ScriptedAI(p_Creature) {}
     
        void Reset() override
        {
            events.Reset();
        }

        void EnterCombat(Unit* p_Attacker) override
        {
            events.ScheduleEvent(eTerongorEvents::EventWrathcleave, 10 * TimeConstants::IN_MILLISECONDS);
            events.ScheduleEvent(eTerongorEvents::EventWrathstorm, urand(14 * TimeConstants::IN_MILLISECONDS, 16 * TimeConstants::IN_MILLISECONDS));
        }

        void UpdateAI(const uint32 p_Diff) override
        {
            if (!UpdateVictim())
                return;

            events.Update(p_Diff);

            switch (events.ExecuteEvent())
            {
               case eTerongorEvents::EventWrathstorm:
                    if (Unit* l_Target = me->getVictim())
                        me->CastSpell(l_Target, eTerongorSpells::SpellWrathStorm);

                    events.ScheduleEvent(EventWrathstorm, urand(8 * TimeConstants::IN_MILLISECONDS, 10 * TimeConstants::IN_MILLISECONDS));
                    break;
               case eTerongorEvents::EventWrathcleave:
                    if (Unit* l_Random = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 50.0f, true))
                    {
                        me->CastSpell(l_Random, eTerongorSpells::SpellWrathCleave);

                        events.ScheduleEvent(EventWrathcleave, urand(10 * TimeConstants::IN_MILLISECONDS, 14 * TimeConstants::IN_MILLISECONDS));
                    }
                    break;
            }

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* p_Creature) const override
    {
        return new auchindon_creaturesAI(p_Creature);
    }
};

/// Gromkash - 
class auchindon_teronogor_gromkash : public CreatureScript
{
public:
    auchindon_teronogor_gromkash() : CreatureScript("auchindon_teronogor_gromkash") { }

    struct auchindon_creatures : public ScriptedAI
    {
        auchindon_creatures(Creature* p_Creature) : ScriptedAI(p_Creature)
        {
            m_Instance = me->GetInstanceScript();

            if (me->GetMap())
            me->GetMap()->SetObjectVisibility(1000.0f);
        }

        InstanceScript* m_Instance;

        void Reset() override
        {
            events.Reset();

            if (m_Instance != nullptr)
            {
                if (Creature* l_Teronogor = m_Instance->instance->GetCreature(m_Instance->GetData64(DataBossTeronogor)))
                {

                }
            }

              // Zashoo, Gromkash's pet.
            if (Creature* l_Zashoo = me->FindNearestCreature(eAuchindonCreatures::CreatureZashoo, 20.0f, true))
                l_Zashoo->Respawn(true);
        }

        void EnterCombat(Unit* p_Attacker) override
        {
            events.ScheduleEvent(eTerongorEvents::EventImmolate, 8 * TimeConstants::IN_MILLISECONDS);
            events.ScheduleEvent(eTerongorEvents::EventIncinrate, urand(10 * TimeConstants::IN_MILLISECONDS, 12 * TimeConstants::IN_MILLISECONDS));
            events.ScheduleEvent(eTerongorEvents::EventRainOfFire, 18 * TimeConstants::IN_MILLISECONDS);

            if (Creature* l_Zashoo = me->FindNearestCreature(CreatureZashoo, 20.0f, true))
                me->CastSpell(l_Zashoo, 159024); // GOS
        }

        void JustDied(Unit* p_Killer) override
        {
            if (m_Instance != nullptr)
            {
                if (Creature* Teronogor = m_Instance->instance->GetCreature(m_Instance->GetData64(eDataAuchindonDatas::DataBossTeronogor)))
                {
                    Teronogor->RemoveAura(eTerongorSpells::SpellTeronogorShield);
                }
            }
        }

        void UpdateAI(const uint32 p_Diff) override
        {
            events.Update(p_Diff);

            if (!UpdateVictim())
                return;

            switch (events.ExecuteEvent())
            {
            case eTerongorEvents::EventImmolate:
                    if (Unit* l_Target = me->getVictim())
                        me->CastSpell(l_Target, eTerongorSpells::SpellImmolate);

                    events.ScheduleEvent(eTerongorEvents::EventImmolate, 8 * TimeConstants::IN_MILLISECONDS);
                    break;
            case eTerongorEvents::EventIncinrate:
                    if (Unit* l_Random = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 50.0f, true))
                    {
                        me->CastSpell(l_Random, eTerongorSpells::SpellIncinrate);
                        events.ScheduleEvent(eTerongorEvents::EventIncinrate, urand(10 * TimeConstants::IN_MILLISECONDS, 12 * TimeConstants::IN_MILLISECONDS));
                    }
                    break;
            case eTerongorEvents::EventRainOfFire:
                    if (Unit* l_Random = SelectTarget(SelectAggroTarget::SELECT_TARGET_RANDOM, 0, 50.0f, true))
                    {
                        me->CastSpell(l_Random, eTerongorSpells::SpellRainOfFire);
                        events.ScheduleEvent(eTerongorEvents::EventRainOfFire, 18 * TimeConstants::IN_MILLISECONDS);
                        break;
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* p_Creature) const override
    {
        return new auchindon_creatures(p_Creature);
    }
};

/// Abyssal Dummy - 
class auchindon_terongor_abyssal_dummy : public CreatureScript
{
public:
    auchindon_terongor_abyssal_dummy() : CreatureScript("auchindon_terongor_abyssal_dummy") { }

    struct auchindon_creaturesAI : public ScriptedAI
    {
        auchindon_creaturesAI(Creature* p_Creature) : ScriptedAI(p_Creature)
        {
            m_Instance = me->GetInstanceScript();
        }

        InstanceScript* m_Instance;
        uint32 m_AbyssalSummon;
        uint32 m_Explosion;
        bool m_HasSummoned;
        bool m_HasExploded;

        void Reset() override
        {
            m_AbyssalSummon = 4 * TimeConstants::IN_MILLISECONDS;
            m_Explosion = 2 * TimeConstants::IN_MILLISECONDS;

            m_HasExploded = false;
            m_HasSummoned = false;

            me->CastSpell(me, eTerongorSpells::SpellSummonAbyssalMeteor);
        }

        void UpdateAI(const uint32 p_Diff) override
        {
            if (m_AbyssalSummon <= p_Diff)
            {
                if (!m_HasSummoned)
                {
                    m_HasSummoned = true;

                    me->CastSpell(me, eTerongorSpells::SpellSummonAbyssalSummonSpell);
                    me->DespawnOrUnsummon(1 * TimeConstants::IN_MILLISECONDS);
                }
            }
            else
                m_AbyssalSummon -= p_Diff;

            if (m_Explosion)
            {
                if (!m_HasExploded)
                {
                    m_HasExploded = true;
                    me->CastSpell(me, eTerongorSpells::SpellSummonAbyssalGroundEffect);
                }
            }
            else
                m_Explosion -= p_Diff;
            
        }
    };

    CreatureAI* GetAI(Creature* p_Creature) const override
    {
        return new auchindon_creaturesAI(p_Creature);
    }
};

/// Chaos Wave - 
class auchindon_teronogor_spell_chaos_wave : public SpellScriptLoader
{
public:
    auchindon_teronogor_spell_chaos_wave() : SpellScriptLoader("auchindon_teronogor_spell_chaos_wave") { }

    class auchindon_spells : public SpellScript
    {
        PrepareSpellScript(auchindon_spells);

        void HandleDummy(SpellEffIndex effIndex)
        {
            if (!GetCaster() && !GetExplTargetUnit())
                return;

            GetCaster()->CastSpell(GetExplTargetUnit(), eTerongorSpells::SpellChaosWaveDmg);
        }

        void Register()
        {
            OnEffectLaunch += SpellEffectFn(auchindon_spells::HandleDummy, SpellEffIndex::EFFECT_0, SpellEffects::SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new auchindon_spells();
    }
};

/// Demonic Leap - 
class auchindon_teronogor_spell_demonic_leap : public SpellScriptLoader
{
public:
    auchindon_teronogor_spell_demonic_leap() : SpellScriptLoader("auchindon_teronogor_spell_demonic_leap") { }

    class auchindon_spells : public SpellScript
    {
        PrepareSpellScript(auchindon_spells);

        void HandleAfterHit()
        {
            if (!GetCaster() && !GetHitUnit())
                return;

            GetCaster()->CastSpell(GetHitUnit(), eTerongorSpells::SpellDemonicLeapAreatriger);
        }

        void Register()
        {
            AfterHit += SpellHitFn(auchindon_spells::HandleAfterHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new auchindon_spells();
    }
};

/// Teleportation Event
class auchindon_soul_transportation_event : public BasicEvent
{
public:
    explicit auchindon_soul_transportation_event(Unit* p_Unit, int p_Value) : m_Obj(p_Unit), m_Modifier(p_Value)
    {
    }

    bool Execute(uint64 /*p_CurrTime*/, uint32 /*p_Diff*/)
    {
        if (m_Obj)
        {
            if (InstanceScript* m_Instance = m_Obj->GetInstanceScript())
            {
                switch (m_Modifier)
                {
                    // first soul transport
                    case 0:
                        m_Obj->GetMotionMaster()->MoveCharge(g_PositionFirstPlatformFirstMove.GetPositionX(), g_PositionFirstPlatformFirstMove.GetPositionY(), g_PositionFirstPlatformFirstMove.GetPositionZ(), 60.0f);
                        m_Obj->m_Events.AddEvent(new auchindon_soul_transportation_event(m_Obj, 1), m_Obj->m_Events.CalculateTime(3 * TimeConstants::IN_MILLISECONDS));

                        break;
                    case 1:
                        m_Obj->GetMotionMaster()->MoveCharge(g_PositionFirstPlatormSecondMove.GetPositionX(), g_PositionFirstPlatormSecondMove.GetPositionY(), g_PositionFirstPlatormSecondMove.GetPositionZ(), 60.0f);
                        m_Obj->m_Events.AddEvent(new auchindon_soul_transportation_event(obj, 2), obj->m_Events.CalculateTime(3 * TimeConstants::IN_MILLISECONDS));
                        break;
                    case 2:
                        m_Obj->GetMotionMaster()->MoveCharge(g_PositionFirstPlatformThirdMove.GetPositionX(), g_PositionFirstPlatformThirdMove.GetPositionY(), g_PositionFirstPlatformThirdMove.GetPositionZ(), 60.0f);
                        m_Obj->m_Events.AddEvent(new auchindon_soul_transportation_event(obj, 100), obj->m_Events.CalculateTime(3 * TimeConstants::IN_MILLISECONDS));
                        break;

                        // second soul transport
                    case 4:
                        m_Obj->GetMotionMaster()->MoveCharge(g_PositionSecondPlatformFirstMove.GetPositionX(), g_PositionSecondPlatformFirstMove.GetPositionY(), g_PositionSecondPlatformFirstMove.GetPositionZ(), 60.0f);
                        m_Obj->m_Events.AddEvent(new auchindon_soul_transportation_event(m_Obj, 5), m_Obj->m_Events.CalculateTime(3 * TimeConstants::IN_MILLISECONDS));
                        break;
                    case 5:
                        m_Obj->GetMotionMaster()->MoveCharge(g_PositionSecondPlatformSecondMove.GetPositionX(), g_PositionSecondPlatformSecondMove.GetPositionY(), g_PositionSecondPlatformSecondMove.GetPositionZ(), 60.0f);
                        m_Obj->m_Events.AddEvent(new auchindon_soul_transportation_event(m_Obj, 6), m_Obj->m_Events.CalculateTime(3 * TimeConstants::IN_MILLISECONDS));
                        break;
                    case 6:
                        m_Obj->GetMotionMaster()->MoveCharge(g_PositionSecondPlatformThirdMove.GetPositionX(), g_PositionSecondPlatformThirdMove.GetPositionY(), g_PositionSecondPlatformThirdMove.GetPositionZ(), 60.0f);
                        m_Obj->m_Events.AddEvent(new auchindon_soul_transportation_event(m_Obj, 100), m_Obj->m_Events.CalculateTime(3 * TimeConstants::IN_MILLISECONDS));
                        break;

                        // third soul transport
                    case 7:
                        m_Obj->GetMotionMaster()->MoveCharge(g_PositionThirdPlatformFirstMove.GetPositionX(), g_PositionThirdPlatformFirstMove.GetPositionY(), g_PositionThirdPlatformFirstMove.GetPositionZ(), 60.0f);
                        m_Obj->m_Events.AddEvent(new auchindon_soul_transportation_event(m_Obj, 8), m_Obj->m_Events.CalculateTime(3 * TimeConstants::IN_MILLISECONDS));
                        break;
                    case 8:
                        m_Obj->GetMotionMaster()->MoveCharge(g_PositionThirdPlatformsSecondMove.GetPositionX(), g_PositionThirdPlatformsSecondMove.GetPositionY(), g_PositionThirdPlatformsSecondMove.GetPositionZ(), 60.0f);
                        m_Obj->m_Events.AddEvent(new auchindon_soul_transportation_event(m_Obj, 9), m_Obj->m_Events.CalculateTime(3 * TimeConstants::IN_MILLISECONDS));
                        break;
                    case 9:
                        m_Obj->GetMotionMaster()->MoveCharge(g_PositionThirdPlatformThirdMove.GetPositionX(), g_PositionThirdPlatformThirdMove.GetPositionY(), g_PositionThirdPlatformThirdMove.GetPositionZ(), 60.0f);
                        m_Obj->m_Events.AddEvent(new auchindon_soul_transportation_event(m_Obj, 100), m_Obj->m_Events.CalculateTime(3 * TimeConstants::IN_MILLISECONDS));
                        break;

                        // fourth soul transport and last
                    case 10:
                        m_Obj->GetMotionMaster()->MoveCharge(g_PositionFourthMovement.GetPositionX(), g_PositionFourthMovement.GetPositionY(), g_PositionFourthMovement.GetPositionZ(), 60.0f);
                        m_Obj->m_Events.AddEvent(new auchindon_soul_transportation_event(m_Obj, 100), m_Obj->m_Events.CalculateTime(3 * TimeConstants::IN_MILLISECONDS));
                        break;
                    case 100:
                        m_Obj->RemoveUnitMovementFlag(MovementFlags::MOVEMENTFLAG_ROOT);

                        m_Obj->RemoveFlag(EUnitFields::UNIT_FIELD_FLAGS, eUnitFlags::UNIT_FLAG_DISABLE_MOVE);
                        m_Obj->RemoveFlag(EUnitFields::UNIT_FIELD_FLAGS2, eUnitFlags2::UNIT_FLAG2_DISABLE_TURN);
                        m_Obj->RemoveAura(SpellTranscend);
                        break;
                }
            }
        }
        return true;
    }

private:
    Unit* m_Obj;
    int m_Modifier;
    int m_Event;
};

/// Soul Transport Object I
class auchindon_teronogor_soul_transporter_gulkosh_first : public GameObjectScript
{
public:
    auchindon_teronogor_soul_transporter_gulkosh_first() : GameObjectScript("auchindon_teronogor_soul_transporter_gulkosh_first") { }

    bool OnGossipHello(Player* player, GameObject* gobject)
    {
        if (InstanceScript* m_Instance = gobject->GetInstanceScript())
        {
            if (Creature* m_Teronogor = m_Instance->instance->GetCreature(m_Instance->GetData64(eDataAuchindonDatas::DataBossTeronogor)))
            {
                if (auchindon_boss_terongor::boss_terongorAI* l_LinkAI = CAST_AI(auchindon_boss_terongor::boss_terongorAI, m_Teronogor->GetAI()))
                {
                    if (l_LinkAI->m_SoulTransport01)
                    {
                        player->AddUnitMovementFlag(MovementFlags::MOVEMENTFLAG_ROOT);
                        player->SetFlag(EUnitFields::UNIT_FIELD_FLAGS, eUnitFlags::UNIT_FLAG_DISABLE_MOVE | eUnitFlags::UNIT_FLAG_IMMUNE_TO_NPC);
                        player->SetFlag(EUnitFields::UNIT_FIELD_FLAGS2, eUnitFlags2::UNIT_FLAG2_DISABLE_TURN);
                        player->AddAura(eTerongorSpells::SpellTranscend, player);

                        player->m_Events.AddEvent(new auchindon_soul_transportation_event(player, 0), player->m_Events.CalculateTime(1 * TimeConstants::IN_MILLISECONDS));
                        return true;
                    }
                }
            }
        }
        return true;
    }
};

/// Soul Transport Object II
class auchindon_teronogor_soul_transporter_gulkosh_second : public GameObjectScript
{
public:
    auchindon_teronogor_soul_transporter_gulkosh_second() : GameObjectScript("auchindon_teronogor_soul_transporter_gulkosh_second") { }

    bool OnGossipHello(Player* player, GameObject* gobject)
    {
        if (InstanceScript* m_Instance = gobject->GetInstanceScript())
        {
            if (Creature* m_Teronogor = m_Instance->instance->GetCreature(m_Instance->GetData64(eDataAuchindonDatas::DataBossTeronogor)))
            {
                if (auchindon_boss_terongor::boss_terongorAI* l_LinkAI = CAST_AI(auchindon_boss_terongor::boss_terongorAI, m_Teronogor->GetAI()))
                {
                    if (l_LinkAI->m_SoulTransport01)
                    {
                        player->AddUnitMovementFlag(MovementFlags::MOVEMENTFLAG_ROOT);
                        player->SetFlag(EUnitFields::UNIT_FIELD_FLAGS, eUnitFlags::UNIT_FLAG_DISABLE_MOVE | eUnitFlags::UNIT_FLAG_IMMUNE_TO_NPC);
                        player->SetFlag(EUnitFields::UNIT_FIELD_FLAGS2, eUnitFlags2::UNIT_FLAG2_DISABLE_TURN);
                        player->AddAura(eTerongorSpells::SpellTranscend, player);

                        player->m_Events.AddEvent(new auchindon_soul_transportation_event(player, 4), player->m_Events.CalculateTime(1 * TimeConstants::IN_MILLISECONDS));
                        return true;
                    }
                }
            }
        }
        return true;
    }
};

/// Soul Transport Object III
class auchindon_teronogor_soul_transporter_gulkosh_third : public GameObjectScript
{
public:
    auchindon_teronogor_soul_transporter_gulkosh_third() : GameObjectScript("auchindon_teronogor_soul_transporter_gulkosh_third") { }

    bool OnGossipHello(Player* player, GameObject* gobject)
    {
        if (InstanceScript* m_Instance = gobject->GetInstanceScript())
        {
            if (Creature* m_Teronogor = m_Instance->instance->GetCreature(m_Instance->GetData64(eDataAuchindonDatas::DataBossTeronogor)))
            {
                if (auchindon_boss_terongor::boss_terongorAI* l_LinkAI = CAST_AI(auchindon_boss_terongor::boss_terongorAI, m_Teronogor->GetAI()))
                {
                    if (l_LinkAI->m_SoulTransport01)
                    {
                        player->AddUnitMovementFlag(MovementFlags::MOVEMENTFLAG_ROOT);
                        player->SetFlag(EUnitFields::UNIT_FIELD_FLAGS, eUnitFlags::UNIT_FLAG_DISABLE_MOVE | eUnitFlags::UNIT_FLAG_IMMUNE_TO_NPC);
                        player->SetFlag(EUnitFields::UNIT_FIELD_FLAGS2, eUnitFlags2::UNIT_FLAG2_DISABLE_TURN);
                        player->AddAura(eTerongorSpells::SpellTranscend, player);

                        player->m_Events.AddEvent(new auchindon_soul_transportation_event(player, 7), player->m_Events.CalculateTime(1 * TimeConstants::IN_MILLISECONDS));
                        return true;
                    }
                }
            }
        }
        return true;
    }
};

/// Soul Transport Object IIII
class auchindon_teronogor_soul_transporter_gulkosh_fourth : public GameObjectScript
{
public:
    auchindon_teronogor_soul_transporter_gulkosh_fourth() : GameObjectScript("auchindon_teronogor_soul_transporter_gulkosh_fourth") { }

    bool OnGossipHello(Player* player, GameObject* gobject)
    {
        if (InstanceScript* m_Instance = gobject->GetInstanceScript())
        {
            if (Creature* m_Teronogor = m_Instance->instance->GetCreature(m_Instance->GetData64(eDataAuchindonDatas::DataBossTeronogor)))
            {
                if (auchindon_boss_terongor::boss_terongorAI* l_LinkAI = CAST_AI(auchindon_boss_terongor::boss_terongorAI, m_Teronogor->GetAI()))
                {
                    if (l_LinkAI->m_SoulTransport01)
                    {
                        player->AddUnitMovementFlag(MovementFlags::MOVEMENTFLAG_ROOT);
                        player->SetFlag(EUnitFields::UNIT_FIELD_FLAGS, eUnitFlags::UNIT_FLAG_DISABLE_MOVE | eUnitFlags::UNIT_FLAG_IMMUNE_TO_NPC);
                        player->SetFlag(EUnitFields::UNIT_FIELD_FLAGS2, eUnitFlags2::UNIT_FLAG2_DISABLE_TURN);
                        player->AddAura(eTerongorSpells::SpellTranscend, player);

                        player->m_Events.AddEvent(new auchindon_soul_transportation_event(player, 0), player->m_Events.CalculateTime(1 * TimeConstants::IN_MILLISECONDS));
                        return true;
                    }
                }
            }
        }
        return true;
    }
};

void AddSC_teronogoer()
{
    new auchindon_boss_terongor();
    new auchindon_teronogor_gromkash();
    new auchindon_terongor_abyssal_dummy();
    new auchindon_teronogor_durag();
    new auchindon_teronogor_gulkosh();
    new auchindon_teronogor_shaadum();
    new auchindon_teronogor_soul_transporter_gulkosh_first();
    new auchindon_teronogor_soul_transporter_gulkosh_second();
    new auchindon_teronogor_soul_transporter_gulkosh_third();
    new auchindon_teronogor_soul_transporter_gulkosh_fourth();
    new auchindon_teronogor_spell_chaos_wave();
    new auchindon_teronogor_spell_demonic_leap();
}