// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controller/WJCultController.h"
#include "GameFramework/Character.h"
#include "Gameplay/WJPointOfInterestAssistant.h"
#include "WJCultCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCultArrestedDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConvertedToCult);

UCLASS()
class WONDERJAM2023_API AWJCultCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWJCultCharacter();

	UPROPERTY(EditAnywhere, Category="AI")
	class UBehaviorTree* BehaviorTree;

	//set up sphere collider to seek for non converted;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Collider")
	class USphereComponent* ChaseSphereCollider;

	//set up sphere collider to seek for non converted;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeshCustom")
	USkeletalMeshComponent* MeshComponent;

	UFUNCTION()
	void OnNonConvertedDetected(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly)
	USkeletalMesh* CultMesh;
	UPROPERTY(EditAnywhere)
	int	Food = 100;
	UPROPERTY(EditAnywhere)
	int	Health = 3;
	UPROPERTY(EditAnywhere)
	int	Faith = 0;
	UPROPERTY(EditAnywhere)
	float DecreaseNeedTime = 5.0f;
	UPROPERTY(EditAnywhere)
	int FoodRateModifier = 5;
	UPROPERTY(EditAnywhere)
	int FaithRateModifier = 5;

	bool bIsTargeted = false;

	bool bisLuckyToConvert = false;

	UFUNCTION(BlueprintNativeEvent)
	void OnPray(float time);
	UFUNCTION(BlueprintNativeEvent)
	void OnTalk(float time);
	UFUNCTION(BlueprintNativeEvent)
	void OnIdle(float time);
	AWJPointOfInterestAssistant* PointOfInterestAssistant;
	UPROPERTY(EditAnywhere)
	bool bIsArrested = false;


	void Arrest();
	void HasEaten();
	void ResetFoodModifier();
	void ResetPrayingModifier();
	void HasPrayed();
	bool GetIsConverted();
	void Heal();
	void Hurt();
	void ConvertToCult();
	UFUNCTION(BlueprintCallable)
	void ResetArrestedStatus();

	UPROPERTY(BlueprintAssignable)
	FOnCultArrestedDelegate OnCultArrestedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnConvertedToCult OnConvertedToCult;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	/* Handle to manage the timer */
	FTimerHandle NeedTimerHandle;
	FTimerHandle EatenBuffTimerHandle;
	FTimerHandle PrayedBuffTimerHandle;
	FTimerHandle ArrestDebuffTimerHandle;
	FTimerDelegate TimerDelegate;
	UWorld* world;
	TArray<AActor*> FoundPointOfInterest;
	AWJCultController* AIController; 


	void UpdateNeed();
	bool CharacterNeedToEat() const;
	void GoToRestaurant();
	bool CharacterNeedToPray() const;
	void GoToBaseToPray();
	bool CharacterIsHurt() const;
	void GoToHospitalToHeal();
	void UpdateBehaviourToNeed();
	

	
	UPROPERTY(EditAnywhere)
	bool bIsConvertedToCult = false;
};
