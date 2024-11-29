// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagsManager.h"
#include "GameplayTagContainer.h"
#include "InstancedStruct.h"
#include "EActor.generated.h"


UCLASS()
class RPGTEMPLATE_API AEActor : public AActor
{

	GENERATED_BODY()

public:	

	// Sets default values for this actor's properties
	AEActor();
	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

#pragma region Properties

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EActor", Meta = (ExposeOnSpawn = true))
	FInstancedStruct Arguments;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EActor", Meta = (ExposeOnSpawn = true))
	FGameplayTagContainer GameplayTags;

#pragma endregion Properties

#pragma region Arbitrary

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "EActor")
	void ArbitraryChannel(FGameplayTag ChannelID, FInstancedStruct Parameters, FGameplayTag&Out_ChannelID, FInstancedStruct &Out_Parameters);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EActor")
	void OnArbitraryRequested(FGameplayTag ChannelID, FInstancedStruct Parameters);
	virtual void OnArbitraryRequested_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EActor")
	void OnArbitraryResponded(FGameplayTag ChannelID, FInstancedStruct Parameters);
	virtual void OnArbitraryResponded_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryRequest, FGameplayTag, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "EActor|Event Dispatcher")
	FOnArbitraryRequest OnArbitraryRequest;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryResponse, FGameplayTag, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, Category = "EActor|Event Dispatcher")
	FOnArbitraryResponse OnArbitraryResponse;

#pragma endregion Arbitrary

#pragma region GameplayTags

	UFUNCTION(BlueprintCallable, Category = "EActor|Gameplay Tag")
	bool AddTag(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "EActor|Gameplay Tag")
	bool RemoveTag(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "EActor|Gameplay Tag")
	bool HasAnyTags(FGameplayTagContainer Tag, bool ExactMatch);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EActor|Gameplay Tag")
	void OnTagAdded(FGameplayTag Tag);
	virtual void OnTagAdded_Implementation(FGameplayTag Tag);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "EActor|Gameplay Tag")
	void OnTagRemoved(FGameplayTag Tag);
	virtual void OnTagRemoved_Implementation(FGameplayTag Tag);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagAdd, FGameplayTag, Tag);
	UPROPERTY(BlueprintAssignable, Category = "EActor|Event Dispatcher")
	FOnTagAdd OnTagAdd;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagRemove, FGameplayTag, Tag);
	UPROPERTY(BlueprintAssignable, Category = "EActor|Event Dispatcher")
	FOnTagRemove OnTagRemove;
	
#pragma endregion GameplayTags

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
