// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

//Forward Declarations
class UCameraComponent;
class USpringArmComponent;
class USphereComponent;

UCLASS()
class DEMOARTICLEPROJECT_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	APlayerController* GetPlayerPawnController() const {return PlayerPawnController;}

private:
	//Camera to see the player
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;
	//SpringArm to control the camera
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmComponent;
	//Collider to detect collisions
	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComponent;
	//The Base Mesh to represent the character. Preferably Sphere-shaped.
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;
	//Movement Variables
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate;
	APlayerController* PlayerPawnController;

	//Movement Methods
	void MoveX(float X);
	void MoveY(float Y);
	void Turn(float value);

};
