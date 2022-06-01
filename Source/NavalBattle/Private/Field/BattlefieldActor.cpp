// Fill out your copyright notice in the Description page of Project Settings.


#include "Field/BattlefieldActor.h"

#include "UObject/ConstructorHelpers.h"

// Sets default values
ABattlefieldActor::ABattlefieldActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*MeshToCopyFrom_Root = CreateDefaultSubobject<UStaticMeshComponent>("SMToCopyFromAKARoot");
	SetRootComponent(MeshToCopyFrom_Root);
	MeshToCopyFrom_Root->SetVisibility(false);*/

	Root = CreateDefaultSubobject<USceneComponent>("RootComponent");
	SetRootComponent(Root);
	
	TransparentMesh = CreateDefaultSubobject<UStaticMeshComponent>("MyPartOfField");
	TransparentMesh->SetupAttachment(GetRootComponent());
	OpaqueMesh = CreateDefaultSubobject<UStaticMeshComponent>("OpponentsPartOfField");
	OpaqueMesh->SetupAttachment(GetRootComponent());

	const auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Meshes/Cube2.Cube2'"));
	if (MeshAsset.Object == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Cube mesh not found"))
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cube mesh not found"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cube mesh not found"));
	}
    
	TransparentMesh->SetStaticMesh(MeshAsset.Object);
	OpaqueMesh->SetStaticMesh(MeshAsset.Object);
}

// Called when the game starts or when spawned
void ABattlefieldActor::BeginPlay()
{
	Super::BeginPlay();

	/*GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABattlefieldActor::SliceCube, 5.f, false);*/
}

// Called every frame
void ABattlefieldActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*void ABattlefieldActor::RefreshCuboid()
{
	
	// Vertices.Add(FVector(-Size.X/2, -Size.Y/2, -Size.Z/2));	/// A	0
	// Vertices.Add(FVector(-Size.X/2, -Size.Y/2, Size.Z/2));	/// A'	1
	// Vertices.Add(FVector(-Size.X/2, Size.Y/2, -Size.Z/2));	/// B	2
	// Vertices.Add(FVector(-Size.X/2, Size.Y/2, Size.Z/2));		/// B'	3
 //
	// Vertices.Add(FVector(Size.X/2, -Size.Y/2, -Size.Z/2));	/// D	4
	// Vertices.Add(FVector(Size.X/2, -Size.Y/2, Size.Z/2));		/// D'	5
	// Vertices.Add(FVector(Size.X/2, Size.Y/2, -Size.Z/2));		/// C	6
	// Vertices.Add(FVector(Size.X/2, Size.Y/2, Size.Z/2));		/// C'	7
 //
	// // top
	// TopTriangles.Add(5);
	// TopTriangles.Add(1);
	// TopTriangles.Add(7);
	// // D'A'C' => C'A'B'
	// TopTriangles.Add(7);
	// TopTriangles.Add(1);
	// TopTriangles.Add(3);
	// TransparentMesh->CreateMeshSection(0, Vertices, TopTriangles, TArray<FVector>(), UVs, TArray<FColor>(), TArray<FProcMeshTangent>(), false);
 //
	// // bottom
	// BottomTriangles.Add(0);
	// BottomTriangles.Add(4);
	// BottomTriangles.Add(2);
	// // ADB => BDC
 //    BottomTriangles.Add(2);
	// BottomTriangles.Add(4);
	// BottomTriangles.Add(6);
	// TransparentMesh->CreateMeshSection(1, Vertices, BottomTriangles, TArray<FVector>(), UVs, TArray<FColor>(), TArray<FProcMeshTangent>(), false);
	//
	// // front
	// FrontTriangles.Add(1);
	// FrontTriangles.Add(0);
	// FrontTriangles.Add(3);
	// // A'AB' => B'AB
	// FrontTriangles.Add(3);
	// FrontTriangles.Add(0);
	// FrontTriangles.Add(2);
	// TransparentMesh->CreateMeshSection(2, Vertices, FrontTriangles, TArray<FVector>(), UVs, TArray<FColor>(), TArray<FProcMeshTangent>(), false);
 //
	// // rear
	// RearTriangles.Add(7);
	// RearTriangles.Add(6);
	// RearTriangles.Add(5);
	// // C'CD' => D'CD
	// RearTriangles.Add(5);
	// RearTriangles.Add(6);
	// RearTriangles.Add(4);
	// TransparentMesh->CreateMeshSection(3, Vertices, RearTriangles, TArray<FVector>(), UVs, TArray<FColor>(), TArray<FProcMeshTangent>(), false);
 //
	// // left
	// LeftTriangles.Add(5);
	// LeftTriangles.Add(4);
	// LeftTriangles.Add(1);
	// // D'DA' => A'DA
	// LeftTriangles.Add(1);
	// LeftTriangles.Add(4);
	// LeftTriangles.Add(0);
	// TransparentMesh->CreateMeshSection(4, Vertices, LeftTriangles, TArray<FVector>(), UVs, TArray<FColor>(), TArray<FProcMeshTangent>(), false);
 //
	// // right
	// RightTriangles.Add(3);
	// RightTriangles.Add(2);
	// RightTriangles.Add(7);
	// // B'BC' => C'BC
	// RightTriangles.Add(7);
	// RightTriangles.Add(2);
	// RightTriangles.Add(6);
	// TransparentMesh->CreateMeshSection(5, Vertices, RightTriangles, TArray<FVector>(), UVs, TArray<FColor>(), TArray<FProcMeshTangent>(), false);
	
	// TransparentMesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UVs, TArray<FColor>(), TArray<FProcMeshTangent>(), false);

	// if (!ensure(MaterialTop)) return;
	// MeshToCopyFrom_Root->SetMaterial(0, MaterialTop);
	//
	// UKismetProceduralMeshLibrary::CopyProceduralMeshFromStaticMeshComponent(MeshToCopyFrom_Root, 0, TransparentMesh, false);
	// UE_LOG(LogTemp, Error, TEXT("Mesh copied"))
	// TransparentMesh->SetVisibility(true);
	// UE_LOG(LogTemp, Error, TEXT("Procedural mesh visible"))
	// MeshToCopyFrom_Root->SetVisibility(false);
	// UE_LOG(LogTemp, Error, TEXT("Static mesh invisible"))

	// if (MaterialTop && MaterialSide)
	// {
	// 	TransparentMesh->SetMaterial(0, MaterialTop);
	// 	TransparentMesh->SetMaterial(1, MaterialTop);
	// 	TransparentMesh->SetMaterial(2, MaterialSide);
	// 	TransparentMesh->SetMaterial(3, MaterialSide);
	// 	TransparentMesh->SetMaterial(4, MaterialSide);
	// 	TransparentMesh->SetMaterial(5, MaterialSide);
	// }
} */

/*void ABattlefieldActor::SliceCube()
{
	UProceduralMeshComponent* CutPart;
	UKismetProceduralMeshLibrary::SliceProceduralMesh(TransparentMesh, GetActorLocation() + FVector(10, 10, 10), FVector(-1,-1,-1), false, CutPart, EProcMeshSliceCapOption::UseLastSectionForCap, MaterialSide);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Looks like timer fired at location %s"), *GetActorLocation().ToString()));
}*/
