// Fill out your copyright notice in the Description page of Project Settings.
#include "Library/UtilityLibrary.h"
#include "DataType/Enum/ELogType.h"
#include "DataType/Enum/EBranchType.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "InputActionValue.h"
#include "Component/ReplicatedAction.h"
#include "GameFramework/Character.h"

void UUtilityLibrary::PrintLog(FString Text, ELogType logType, UObject* Object, float Time)
{
	if (GEngine) {

		FString name = " ";
		if (IsValid(Object) && Object->GetClass()) {
			name = "[" + Object->GetClass()->GetName() + "] ";
		}
		
		FColor color = FColor::Blue;

		FString prefix;
		switch (logType) {
			case ELogType::Message:
				color = FColor::Blue;
				prefix = "[MESSAGE]";
				break;
			case ELogType::Warning:
				color = FColor::Yellow;
				prefix = "[WARNING]";
				break;
			case ELogType::Success:
				color = FColor::Green;
				prefix = "[SUCCESS]";
				break;
			case ELogType::Error:
				color = FColor::Red;
				prefix = "[ERROR]";
				break;
		}

		FString content = prefix + name + Text;

		GEngine->AddOnScreenDebugMessage(-1, Time, color, content);

	}
}

FString UUtilityLibrary::GetRandomAlphaDigit(int Length)
{
	const char letters[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	const int lettersSize = 62;

	FString randomString;

	for (int i = 0; i < Length; i++) {
		randomString += letters[FMath::RandRange(0, lettersSize - 1)];
	}

	return randomString;

}

void UUtilityLibrary::NBranch(bool Condition, TEnumAsByte<EBranchType>& Branches)
{
	if(!Condition)
	{
		Branches = EBranchType::OnTrue;
	}
	else
	{
		Branches = EBranchType::OnFalse;
	}
}

int32 UUtilityLibrary::GetLargestInteger(const TArray<int32>& TargetArray)
{
	int32 num = 0;

	for (int32 x : TargetArray)
	{
		if (x > num)
		{
			num = x;
		}
	}

	return num;
}

FName UUtilityLibrary::TextToName(const FText& Text)
{
	return FName(*Text.ToString());
}

UGameInstanceSubsystem* UUtilityLibrary::GetGameInstanceSubsystemOfClass(const UObject* WorldContextObject, TSubclassOf<UGameInstanceSubsystem> SubsystemClass)
{
	if (!WorldContextObject || !SubsystemClass)
	{
		return nullptr;
	}

	const UGameInstance* GameInstance = WorldContextObject->GetWorld()->GetGameInstance();
	if (!GameInstance)
	{
		return nullptr;
	}
	
	return GameInstance->GetSubsystemBase(SubsystemClass);

}

FGameplayEffectContextHandle UUtilityLibrary::GetContext(const FGameplayEffectSpec& InEffectSpec)
{
	return InEffectSpec.GetContext();
}

FGameplayTag UUtilityLibrary::MakeGameplayTagFromText(FText Text)
{
	FGameplayTag tag = FGameplayTag::RequestGameplayTag(FName(*Text.ToString()));
	if (tag.IsValid()) {
		return tag;
	}
	return FGameplayTag();
}

float UUtilityLibrary::GetActionValueFloat(const FInputActionValue& ActionValue)
{
	return ActionValue.Get<float>();
}

FVector UUtilityLibrary::GetActionValueVector(const FInputActionValue& ActionValue)
{
	return ActionValue.Get<FVector>();
}

bool UUtilityLibrary::HasReplicatedActionComponent(ACharacter* Character)
{
	if (!Character) {
		return false;
	}

	UActorComponent* actionComponent = Character->GetComponentByClass(UReplicatedAction::StaticClass());

	if (!actionComponent) {
		return false;
	}

	return true;
}

UReplicatedAction* UUtilityLibrary::GetReplicatedActionComponent(ACharacter* Character)
{
	if (!Character) {
		return nullptr;
	}

	UActorComponent* actionComponent = Character->GetComponentByClass(UReplicatedAction::StaticClass());

	if (!actionComponent) {
		return nullptr;
	}

	UReplicatedAction* replicatedAction = Cast<UReplicatedAction>(actionComponent);

	if (!replicatedAction) {
		return nullptr;
	}

	return replicatedAction;
}

bool UUtilityLibrary::GetActionValueBool(const FInputActionValue& ActionValue)
{
	return ActionValue.Get<bool>();
}