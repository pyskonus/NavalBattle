// UCU diploma Bohdan Pysko.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSessionSettings.h"
#include "ServerRowUserWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class NAVALBATTLE_API UServerRowUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetFields(const FOnlineSessionSearchResult& SearchResult);

	virtual bool Initialize() override;

	int32 Index;

private:
	UPROPERTY(meta = (BindWidget))
	UButton* Button_0;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ServerName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PingInMs;

	UFUNCTION()
	void OnClicked();
};
