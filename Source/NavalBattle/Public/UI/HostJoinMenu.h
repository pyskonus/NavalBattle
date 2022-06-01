// UCU diploma Bohdan Pysko.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HostJoinMenu.generated.h"

class UWidgetSwitcher;
class UScrollBox;
class FOnlineSessionSearchResult;
class UServerRowUserWidget;

UCLASS()
class NAVALBATTLE_API UHostJoinMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void MakeScrollboxVisibleAndEmpty();
	
	void AddServerRow(const FOnlineSessionSearchResult& SearchResult);

protected:
	virtual bool Initialize() override;
	
	UFUNCTION(BlueprintCallable)
	void HostButtonCallback();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	TSubclassOf<UServerRowUserWidget> ServerRowBPClass;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* ServerListWidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ServerList;
};