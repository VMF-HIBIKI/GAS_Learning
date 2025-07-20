// Copyright GAS


#include "Character/AuraCharacterBase.h"


// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick =false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");//创建组件到父Actor
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket")); // 附加到角色网格的武器插槽
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);//设置为无体积碰撞
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}
