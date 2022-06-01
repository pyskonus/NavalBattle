// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattlefieldActor.generated.h"

UCLASS()
class NAVALBATTLE_API ABattlefieldActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattlefieldActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*UFUNCTION(BlueprintCallable)
	void SliceCube();*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Root;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MeshToCopyFrom_Root;*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TransparentMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* OpaqueMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* TranslucentMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* OpaqueMaterial;

	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomProps")
	UMaterialInterface* MaterialTop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomProps")
	UMaterialInterface* MaterialSide;
	
	void RefreshCuboid();

	TArray<FVector> Vertices;
	TArray<int32> TopTriangles;
	TArray<int32> BottomTriangles;
	TArray<int32> FrontTriangles;
	TArray<int32> RearTriangles;
	TArray<int32> LeftTriangles;
	TArray<int32> RightTriangles;
	TArray<FVector2D> UVs;
	*/

	/*FTimerHandle TimerHandle;*/

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
