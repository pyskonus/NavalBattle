// UCU diploma Bohdan Pysko.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HostJoinHUD.generated.h"


class UHostJoinMenu;
class FOnlineSessionSearchResult;

UCLASS()
class NAVALBATTLE_API AHostJoinHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "References")
	TSubclassOf<UHostJoinMenu> HostJoinMenuClass;
	
	void PopulateServerList(const TArray<FOnlineSessionSearchResult>& SearchResults);

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	UHostJoinMenu* MainWidget;
};
