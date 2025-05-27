#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h" //for stamina widget
#include "StaminaComponent.h"
#include "Projekt_AYAYACharacter.generated.h"

class UStaminaComponent; //stamina component class
UCLASS()
class AProjekt_AYAYACharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

protected:

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* DodgeAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* SprintAction;

	//Stamina widget on screen
	UPROPERTY(EditAnywhere, Category = "UI") TSubclassOf<UUserWidget> PlayerStaminaWidgetClass;
	UUserWidget* PlayerStaminaWidget;

public:
	AProjekt_AYAYACharacter();
	//Attaching stamina component to player
	UPROPERTY(BlueprintReadOnly) UStaminaComponent* StaminaComponent;

protected:
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:

	void Move(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);
	FVector LastMovementInput;
	void Dodge();
	void Sprint();
	void StopSprint();

};