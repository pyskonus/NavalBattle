// UCU diploma Bohdan Pysko.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "NavalBattleGameInstance.generated.h"


UCLASS()
class NAVALBATTLE_API UNavalBattleGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	virtual void Shutdown() override;
	
	UFUNCTION()
	void Host();

	UFUNCTION()
	void Join(const FString& Address);

private:
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	
	void OnCreateSessionComplete(FName SessionName, bool Success);
	void OnDestroySessionComplete(FName SessionName, bool Success);
	void OnFindSessionComplete(bool Success);

	void CreateSession();

	FString OSS_SessionHash;

	bool bStillLookingForSessions = true;
};
