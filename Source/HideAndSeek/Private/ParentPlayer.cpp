// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentPlayer.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BushComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AParentPlayer::AParentPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;

	// Mesh
	ConstructorHelpers::FObjectFinder<USkeletalMesh> Mannequin(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin_Female.SK_Mannequin_Female'"));
	GetMesh()->SetSkeletalMesh(Mannequin.Object);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -85.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, -0.f));
	ConstructorHelpers::FClassFinder<UAnimInstance> AnimBP(TEXT("AnimBlueprint'/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP_C'"));
	GetMesh()->SetAnimInstanceClass(AnimBP.Class);

	// SpringArm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	SpringArm->SetRelativeLocation(FVector(0.f, 0.f, 70.f));
	SpringArm->TargetArmLength = 400.f;
	SpringArm->SocketOffset = FVector(0.f, 0.f, 150.f);
	SpringArm->bUsePawnControlRotation = true;

	// Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::SnapToTargetIncludingScale);
	Camera->SetRelativeRotation(FRotator(-20.f, 0.f, 0.f));

	// Character Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// Bush Component
	Bush = CreateDefaultSubobject<UBushComponent>(TEXT("Bush"));
	Bush->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void AParentPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

// Called when the game starts or when spawned
void AParentPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AParentPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AParentPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveForward", this, &AParentPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AParentPlayer::MoveRight);
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
}

void AParentPlayer::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AParentPlayer::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}