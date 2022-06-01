// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Need to create the components when the player pawn is constructed.
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	//Then we make the Sphere Collider the Root Component.
	RootComponent = SphereComponent;
	//Next we construct the Static Mesh Component for the Base Mesh.
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	//We need to attach the Base Mesh to the Root Component.
	BaseMesh->SetupAttachment(RootComponent);
	
	//The Spring Arm that controls the camera is next.
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	//Now we attach the SpringArm to the Root Component.
	SpringArmComponent->SetupAttachment(RootComponent);
	//The camera also needs to be constructed.
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Cam"));
	//We can't forget to attach the camera TO the SpringArm.
	CameraComponent->SetupAttachment(SpringArmComponent);
	
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	//We should find the player controller and make sure it's there using our GetPlayerPawnController method.
	PlayerPawnController = Cast<APlayerController>(GetPlayerPawnController());
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//The Input Axis Binding Names need to be set manually if you didn't use a project template.
	PlayerInputComponent->BindAxis(TEXT("Vertical"),this,&APlayerPawn::MoveX);
	PlayerInputComponent->BindAxis(TEXT("Horizontal"),this,&APlayerPawn::MoveY);
}

void APlayerPawn::MoveX(float X)
{
	FVector DeltaLocation(0.f);
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	DeltaLocation.X = X * Speed * DeltaTime;

	AddActorLocalOffset(DeltaLocation,true);
}

void APlayerPawn::MoveY(float Y)
{
	FVector DeltaLocation(0.f);
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	
	DeltaLocation.Y = Y * Speed * DeltaTime;

	AddActorLocalOffset(DeltaLocation,true);
}

