#include "LesFightPhysicsObject.h"

void ULesFightPhysicsObject::Initialize(ULesFightArenaWorldManager* InManager)
{
    OwnerManager = InManager;
}

void ULesFightPhysicsObject::InitializePhysics(AActor* Actor, float InMass, bool bSimulatePhysics)
{
    OwnerActor = Actor;
    Mass = InMass;
    bPhysicsEnabled = bSimulatePhysics;
    bAsleep = false;
    AccumulatedForces = FVector::ZeroVector;
}

void ULesFightPhysicsObject::ApplyForce(FVector Force)
{
    if (!bPhysicsEnabled)
    {
        return;
    }
    AccumulatedForces += Force;
}

void ULesFightPhysicsObject::ApplyImpulse(FVector Impulse, FVector Location)
{
}

void ULesFightPhysicsObject::ApplyTorque(FVector Torque)
{
}

void ULesFightPhysicsObject::EnablePhysics(bool bEnabled)
{
    bPhysicsEnabled = bEnabled;
}

bool ULesFightPhysicsObject::IsPhysicsEnabled() const
{
    return bPhysicsEnabled;
}

float ULesFightPhysicsObject::GetMass() const
{
    return Mass;
}

void ULesFightPhysicsObject::SetMass(float InMass)
{
    Mass = InMass;
}

void ULesFightPhysicsObject::SetLinearDamping(float Damping)
{
    LinearDamping = Damping;
}

void ULesFightPhysicsObject::SetAngularDamping(float Damping)
{
    AngularDamping = Damping;
}

void ULesFightPhysicsObject::Sleep()
{
    bAsleep = true;
}

void ULesFightPhysicsObject::WakeUp()
{
    bAsleep = false;
}

bool ULesFightPhysicsObject::IsAsleep() const
{
    return bAsleep;
}

void ULesFightPhysicsObject::ResetPhysicsState()
{
    AccumulatedForces = FVector::ZeroVector;
    bAsleep = false;
}
