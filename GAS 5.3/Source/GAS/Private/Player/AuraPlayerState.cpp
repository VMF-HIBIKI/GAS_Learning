// Copyright GAS


#include "Player/AuraPlayerState.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"


AAuraPlayerState::AAuraPlayerState()
{
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraPlayerState::BeginPlay()
{
	Super::BeginPlay();
	if (AttributeSet)
	{
		UE_LOG(LogTemp, Warning, TEXT("AttributeSet initialized: %s"), *AttributeSet->GetName());
        
		// 验证 Mana 属性是否存在
		if (UAuraAttributeSet* AuraAS = Cast<UAuraAttributeSet>(AttributeSet))
		{
			UE_LOG(LogTemp, Warning, TEXT("Mana Value: %f"), AuraAS->GetMana());
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AttributeSet is null!"));
	}
}
