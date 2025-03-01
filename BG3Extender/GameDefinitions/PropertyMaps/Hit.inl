BEGIN_CLS(DamageSums)
P(TotalDamageDone)
P(TotalHealDone)
P(DamagePercentage)
END_CLS()


BEGIN_CLS(DamagePair)
P(Amount)
P(DamageType)
END_CLS()


BEGIN_CLS(DiceValues)
P(DiceValue)
P(AmountOfDices)
P(DiceAdditionalValue)
END_CLS()


BEGIN_CLS(DamageModifierMetadata)
P(MetadataType)
P(Value)
P(DamageType)
P(SourceType)
P_REF(Dice)
P(Source)
END_CLS()


BEGIN_CLS(StatsRollRoll)
P_REF(Roll)
P(RollType)
P(Advantage)
P(Disadvantage)
END_CLS()


BEGIN_CLS(StatsRollResult)
P(Total)
P(DiceTotal)
P(DiscardedDiceTotal)
P(Critical)
END_CLS()


BEGIN_CLS(ResolvedRollBonus)
P(DiceSetType)
P(NumDice)
P(ResolvedRollBonus)
END_CLS()


BEGIN_CLS(StatsRollMetadata)
P(ProficiencyBonus)
P(RollBonus)
P_REF(AbilityBoosts)
P_REF(SkillBonuses)
P(AutoSkillCheckFail)
P(AutoAbilityCheckFail)
P(AutoAbilitySavingThrowFail)
P(HasCustomMetadata)
P(IsCritical)
P_REF(ResolvedRollBonuses)
END_CLS()


BEGIN_CLS(StatsRollBase)
P_REF(Roll)
P_REF(Result)
P_REF(Metadata)
END_CLS()


BEGIN_CLS(StatsRollType0)
INHERIT(StatsRollBase)
P(Type)
END_CLS()


BEGIN_CLS(StatsRollType1)
P(StatExpression)
P_REF(IntParams)
P_REF(RollParams)
P(DamageTypeParams)
P(IntIndex)
P(RollIndex)
P(DamageTypeIndex)
END_CLS()


BEGIN_CLS(ConditionRoll)
P(DataType)
P(RollType)
P_REF(Roll)
P(Difficulty)
END_CLS()


BEGIN_CLS(DamageResistance)
P(ResistanceType)
P(DamageType)
P(Damage)
END_CLS()


BEGIN_CLS(Hit::Subobj)
P_REF(DamageRolls)
P_REF(ModifierMetadata)
P_REF(ConditionRoll)
P_REF(ModifierMetadata2)
P_REF(Resistances)
P(AdditionalDamage)
P(TotalDamage)
P(FinalDamage)
P(TotalDamagePerType) // FIXME - ref map?
P(FinalDamagePerType) // FIXME - ref map?
END_CLS()


BEGIN_CLS(Hit)
P(TotalDamageDone)
P(DeathType)
P(DamageType)
P(CauseType)
P(ImpactPosition)
P(ImpactDirection)
P(ImpactForce)
P(ArmorAbsorption)
P(LifeSteal)
P(EffectFlags)
P(HitWith)
P(AttackRollAbility)
P(SaveAbility)
P(Inflicter)
P(InflicterOwner)
P(Throwing)
P(StoryActionId)
P_REF(ConditionRolls)
P_REF(SomeSubobj)
P(SpellAttackType)
P(SpellId)
P(field_180)
P(field_188)
P(field_190)
P(SpellSchool)
P(SpellLevel)
P(SpellPowerLevel)
P(TotalHealDone)
P(HitDescFlags)
P_REF(DamageList)
END_CLS()


BEGIN_CLS(NewHit)
INHERIT(Hit)
P_REF(DamageSums)
END_CLS()
