// UCU diploma Bohdan Pysko.


#include "UI/HostJoinMenu.h"

/*#include "Components/Button.h"*/
#include "Components/WidgetSwitcher.h"
#include "Components/ScrollBox.h"
#include "OnlineSessionSettings.h"
#include "UI/ServerRowUserWidget.h"
#include "NavalBattleGameInstance.h"


bool UHostJoinMenu::Initialize()
{
	if (!Super::Initialize()) return false;
	
	return true;
}

void UHostJoinMenu::HostButtonCallback()
{
	UNavalBattleGameInstance* GameInstance = Cast<UNavalBattleGameInstance>(GetGameInstance());
	if (!ensure(GameInstance)) return;

	GameInstance->Host();
}

void UHostJoinMenu::MakeScrollboxVisibleAndEmpty()
{
	ServerList->ClearChildren();
	ServerListWidgetSwitcher->SetActiveWidget(ServerList);
}

void UHostJoinMenu::AddServerRow(const FOnlineSessionSearchResult& SearchResult, int32 Index)
{
	UServerRowUserWidget* Row = CreateWidget<UServerRowUserWidget>(this, ServerRowBPClass);
	if (!ensure(Row)) return;

	Row->SetFields(SearchResult);
	Row->Index = Index;

	ServerList->AddChild(Row);
}

