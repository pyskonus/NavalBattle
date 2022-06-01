// UCU diploma Bohdan Pysko.


#include "UI/ServerRowUserWidget.h"
#include "OnlineSessionSettings.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


bool UServerRowUserWidget::Initialize()
{
	if (!Super::Initialize()) return false;

	Button_0->OnClicked.AddDynamic(this, &UServerRowUserWidget::OnClicked);
	
	return true;	
}

void UServerRowUserWidget::SetFields(const FOnlineSessionSearchResult& SearchResult)
{
	ServerName->SetText(FText::FromString(SearchResult.GetSessionIdStr().Left(5)));

	PingInMs->SetText(FText::FromString(SearchResult.PingInMs + " ms"));
}

void UServerRowUserWidget::OnClicked()
{
	
}
