// UCU diploma Bohdan Pysko.


#include "UI/ServerRowUserWidget.h"

#include "NavalBattleGameInstance.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


bool UServerRowUserWidget::Initialize()
{
	UE_LOG(LogTemp, Warning, TEXT("Initialize started"))
	if (!Super::Initialize()) return false;

	Button_0->OnClicked.AddDynamic(this, &UServerRowUserWidget::OnClicked);

	UE_LOG(LogTemp, Warning, TEXT("Bind successful"))
	
	return true;
}

void UServerRowUserWidget::SetFields(const FOnlineSessionSearchResult& SearchResult)
{
	ServerName->SetText(FText::FromString(SearchResult.GetSessionIdStr().Left(5)));

	PingInMs->SetText(FText::FromString(FString::FromInt(SearchResult.PingInMs) + " ms"));
}

void UServerRowUserWidget::OnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("OnClicked event fired"))
	Cast<UNavalBattleGameInstance>(GetGameInstance())->Join(Index);
}
