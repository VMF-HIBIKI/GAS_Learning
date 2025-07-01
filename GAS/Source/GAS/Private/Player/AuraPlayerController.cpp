// Copyright GAS


#include "Player/AuraPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/HighlightInterface.h"


AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}


void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IHighlightInterface>(CursorHit.GetActor());

	/*
	 * 分情况判断
	 * A：如果上一个对象和现在的对象都为空
	 * do nothing
	 * B: 如果上一个对象为空，现在的对象不为空
	 * 现在的对象显示高光
	 * C:如果上一个对象存在，现在的对象为空
	 * 上个对象取消显示高光
	 * D:如果上一个对象和现在的对象都存在，那么判断两者是否是一个对象，如果不是
	 * 取消上一个对象的高光，显示这个对象的高光
	 * E:如果上一个对象和现在的对象都存在，那么判断两者是否是一个对象，如果是
	 * do nothing
	 */
	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			//case B
			ThisActor->HighlightActor();
		}
		else
		{
			//case A
			//do nothing
		}
	}
	else //上个对象存在
	{
		if (ThisActor == nullptr)
		{
			//case C
			LastActor->UnHighlightActor();
		}
		else 
		{
			if (LastActor != ThisActor)
			{
				//case D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				//case E
				//do nothing
			}
		}
	}
	
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);
	
	/*获取本地增加输入系统（用于管理输入和输入上下文）并添加需要的上下文
	 */
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext , 0);

	//鼠标光标设置
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	//输入模式配置
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction , ETriggerEvent::Triggered , this , &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	//获取输入器的偏航旋转
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	// 转换为世界空间方向
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlleredPawn = GetPawn())
	{
		ControlleredPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		ControlleredPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}

