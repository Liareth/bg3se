BEGIN_CLS(lua::EmptyEventParams)
END_CLS()

BEGIN_CLS(ecl::lua::GameStateChangeEventParams)
P_RO(FromState)
P_RO(ToState)
END_CLS()

BEGIN_CLS(esv::lua::GameStateChangeEventParams)
P_RO(FromState)
P_RO(ToState)
END_CLS()

BEGIN_CLS(lua::TickEventParams)
P_REF(Time)
END_CLS()

BEGIN_CLS(esv::lua::DoConsoleCommandEventParams)
P_RO(Command)
END_CLS()

BEGIN_CLS(esv::lua::DealDamageEvent)
P_REF_PTR(Functor)
P(Caster)
P(Target)
P(Position)
P(IsFromItem)
P_REF_PTR(SpellId)
P(StoryActionId)
P_REF_PTR(Originator)
P_REF_PTR(Hit)
P_REF_PTR(DamageSums)
P(HitWith)
END_CLS()

BEGIN_CLS(esv::lua::ExecuteFunctorEventParams)
P_REF_PTR(Functor)
P_REF_PTR(Params)
END_CLS()

BEGIN_CLS(esv::lua::AfterExecuteFunctorEventParams)
P_REF_PTR(Functor)
P_REF_PTR(Params)
P_REF_PTR(Hit)
END_CLS()
