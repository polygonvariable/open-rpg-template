// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagsManager.h"
#include "GameplayTagContainer.h"
#include "InstancedStruct.h"
#include "EActorComponent.generated.h"


UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RPGTEMPLATE_API UEActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:


#pragma region Properties

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EActorComponent", Meta = (ExposeOnSpawn = true))
	FInstancedStruct Arguments;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EActorComponent", Meta = (ExposeOnSpawn = true))
	FGameplayTagContainer GameplayTags;

#pragma endregion Properties

#pragma region Arbitrary

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Server, Reliable, WithValidation, DisplayName = "Arbitrary Request", Category = "EActorComponent")
	void SArbitraryRequest(FGameplayTag ChannelID, FInstancedStruct Parameters);
	void SArbitraryRequest_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);
	bool SArbitraryRequest_Validate(FGameplayTag ChannelID, FInstancedStruct Parameters);

	UFUNCTION(NetMulticast, Reliable, DisplayName = "Enhanced Actor Component|@Client ArbitraryRequest", Category = "EActorComponent")
	void CArbitraryRequest(FGameplayTag ChannelID, FInstancedStruct Parameters);
	void CArbitraryRequest_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Server, Reliable, WithValidation, DisplayName = "Arbitrary Response", Category = "EActorComponent")
	void SArbitraryResponse(FGameplayTag ChannelID, FInstancedStruct Parameters);
	void SArbitraryResponse_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);
	bool SArbitraryResponse_Validate(FGameplayTag ChannelID, FInstancedStruct Parameters);

	UFUNCTION(NetMulticast, Reliable, DisplayName = "Enhanced Actor Component|@Client ArbitraryResponse", Category = "EActorComponent")
	void CArbitraryResponse(FGameplayTag ChannelID, FInstancedStruct Parameters);
	void CArbitraryResponse_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);



	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "EActorComponent")
	void ArbitraryChannel(FGameplayTag ChannelID, FInstancedStruct Parameters, FGameplayTag& Out_ChannelID, FInstancedStruct& Out_Parameters);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EActorComponent")
	void OnArbitraryRequested(FGameplayTag ChannelID, FInstancedStruct Parameters);
	virtual void OnArbitraryRequested_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EActorComponent")
	void OnArbitraryResponded(FGameplayTag ChannelID, FInstancedStruct Parameters);
	virtual void OnArbitraryResponded_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryRequest, FGameplayTag, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "EActorComponent|Event Dispatcher")
	FOnArbitraryRequest OnArbitraryRequest;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryResponse, FGameplayTag, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "EActorComponent|Event Dispatcher")
	FOnArbitraryResponse OnArbitraryResponse;

#pragma endregion Arbitrary


	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Server, Reliable, WithValidation, DisplayName = "Add Gameplay Tag", Category = "EActorComponent|Gameplay Tag")
	void SAddGameplayTag(FGameplayTag Tag);
	void SAddGameplayTag_Implementation(FGameplayTag Tag);
	bool SAddGameplayTag_Validate(FGameplayTag Tag);

	UFUNCTION(NetMulticast, Reliable, Category = "EActorComponent|Gameplay Tag")
	void CAddGameplayTag(FGameplayTag Tag);
	void CAddGameplayTag_Implementation(FGameplayTag Tag);


	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Server, Reliable, WithValidation, DisplayName = "Remove Gameplay Tag", Category = "EActorComponent|Gameplay Tag")
	void SRemoveGameplayTag(FGameplayTag Tag);
	void SRemoveGameplayTag_Implementation(FGameplayTag Tag);
	bool SRemoveGameplayTag_Validate(FGameplayTag Tag);

	UFUNCTION(NetMulticast, Reliable, Category = "EActorComponent|Gameplay Tag")
	void CRemoveGameplayTag(FGameplayTag Tag);
	void CRemoveGameplayTag_Implementation(FGameplayTag Tag);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagAdded, FGameplayTag, Tag);
	UPROPERTY(BlueprintAssignable, Category = "EActorComponent|Event Dispatcher")
	FOnTagAdded OnTagAdded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagRemoved, FGameplayTag, Tag);
	UPROPERTY(BlueprintAssignable, Category = "EActorComponent|Event Dispatcher")
	FOnTagRemoved OnTagRemoved;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
