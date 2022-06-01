// UCU diploma Bohdan Pysko.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRowUserWidget.generated.h"

class UButton;
class UTextBlock;
class FOnlineSessionSearchResult;

UCLASS()
class NAVALBATTLE_API UServerRowUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetFields(const FOnlineSessionSearchResult& SearchResult);

	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	UButton* Button_0;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ServerName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PingInMs;

	void OnClicked();
};
