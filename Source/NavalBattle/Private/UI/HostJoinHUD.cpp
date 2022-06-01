// UCU diploma Bohdan Pysko.


#include "UI/HostJoinHUD.h"

#include "UI/HostJoinMenu.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSessionSettings.h"

void AHostJoinHUD::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* World = GetWorld();
	if (!ensure(World)) return;
	
	MainWidget = CreateWidget<UHostJoinMenu>(World, HostJoinMenuClass);
	MainWidget->AddToViewport();
	GetOwningPlayerController()->SetInputMode(FInputModeUIOnly());
	GetOwningPlayerController()->SetShowMouseCursor(true);
}

void AHostJoinHUD::PopulateServerList(const TArray<FOnlineSessionSearchResult>& SearchResults)
{
	MainWidget->MakeScrollboxVisibleAndEmpty();
	
	for (const FOnlineSessionSearchResult& SearchResult: SearchResults)
	{
		MainWidget->AddServerRow(SearchResult);
		UE_LOG(LogTemp, Error, TEXT("Found session %s"), *SearchResult.GetSessionIdStr())
	}
}