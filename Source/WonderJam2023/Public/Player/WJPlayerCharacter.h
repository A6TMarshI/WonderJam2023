// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Characters/WJCultCharacter.h"
#include "GameFramework/Pawn.h"
#include "WJPlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClickedCultArested, AWJCultCharacter*, CultCharacter);

UCLASS()
class WONDERJAM2023_API AWJPlayerCharacter : public APawn
{
	GENERATED_BODY()

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereCollision;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Movement Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UFloatingPawnMovement* MovementComponent;


	

public:
	// Sets default values for this pawn's properties
	AWJPlayerCharacter();

	/** Called for movement input */
	UFUNCTION()
	void InputMove(const FInputActionValue& Value);

	/** Called for movement input */
	UFUNCTION()
	void InputZoom(const FInputActionValue& Value);
	
	UFUNCTION()
	void InputInteract(const FInputActionValue& Value);

	UPROPERTY(BlueprintAssignable)
	FOnClickedCultArested OnClickedCultArested;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Input config*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	class UWJInputConfig* InputConfig;

	UFUNCTION()
	void BoxTrace(const FVector& MouseLocation);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};


