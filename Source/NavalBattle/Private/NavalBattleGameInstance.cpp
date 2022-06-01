// UCU diploma Bohdan Pysko.


#include "NavalBattleGameInstance.h"
/*#include "UI/HostJoinGameMode.h"*/
#include "UI/HostJoinHUD.h"

/*const static FName SESSION_NAME = TEXT("My Session Game");*/

void UNavalBattleGameInstance::Init()
{
	Super::Init();
	
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (!ensure(Subsystem)) return;
	UE_LOG(LogTemp, Warning, TEXT("Found subsystem %s"), *Subsystem->GetSubsystemName().ToString());
	
	SessionInterface = Subsystem->GetSessionInterface();
	if (!ensure(SessionInterface.IsValid())) return;
	
	SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UNavalBattleGameInstance::OnCreateSessionComplete);
	SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UNavalBattleGameInstance::OnDestroySessionComplete);
	SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UNavalBattleGameInstance::OnFindSessionComplete);
	SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UNavalBattleGameInstance::OnJoinSessionComplete);

	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		SessionSearch->bIsLanQuery = true;
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
		UE_LOG(LogTemp, Warning, TEXT("Looking for sessions"))
	}
}


void UNavalBattleGameInstance::Host()
{
	if (SessionInterface.IsValid())
	{
		auto ExistingSession = SessionInterface->GetNamedSession(*OSS_SessionHash);
		if (ExistingSession != nullptr)
			SessionInterface->DestroySession(*OSS_SessionHash);
		else
			CreateSession();
	}
}

void UNavalBattleGameInstance::Join(int32 Index)
{
	UE_LOG(LogTemp, Warning, TEXT("GI Join called"))
	SessionInterface->JoinSession(0, *OSS_SessionHash, SessionSearch->SearchResults[Index]);
}

void UNavalBattleGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogTemp, Warning, TEXT("JS complete called"))
	bStillLookingForSessions = false;
	if (!SessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("SInterface invalid"))
		return;
	}
	
	FString Address;
	if (!SessionInterface->GetResolvedConnectString(SessionName, Address))
		UE_LOG(LogTemp, Warning, TEXT("Could not get connect string"))

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Could not get the connect string"));
	
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController)) return;
	UE_LOG(LogTemp, Warning, TEXT("Client travel here"))
	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	UE_LOG(LogTemp, Warning, TEXT("After client trave"))
}

void UNavalBattleGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = true;
		SessionSettings.NumPublicConnections = 2;
		SessionSettings.bShouldAdvertise = true;
		OSS_SessionHash = FString::FromInt(GetTypeHash(this));
		SessionInterface->CreateSession(0, *OSS_SessionHash, SessionSettings);
		UE_LOG(LogTemp, Warning, TEXT("Creating session %s"), *OSS_SessionHash)
	}
}


void UNavalBattleGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	if (!Success)
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to create session"))
		return;
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("Created session %s with hash %s"), *SessionName.ToString(), *OSS_SessionHash)	
	}
	
	UWorld* World = GetWorld();
	if (!ensure(World)) return;

	bStillLookingForSessions = false;
	
	World->ServerTravel("/Game/HostJoinMenu/TestLevel?listen");
} // /Game/HandheldAR/Maps/HandheldARBlankMap

void UNavalBattleGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	/*if (Success)
		CreateSession();*/
	UE_LOG(LogTemp, Warning, TEXT("Destroyed session %s with hash %s"), *SessionName.ToString(), *OSS_SessionHash)
}

void UNavalBattleGameInstance::OnFindSessionComplete(bool Success)
{
	if (Success && SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Find session complete"))

		/*|| (SessionSearch->SearchResults.Num() == 1 && SessionSearch->SearchResults[0].GetSessionIdStr()==OSS_SessionHash)*/
		if (SessionSearch->SearchResults.Num() == 0) {
			UE_LOG(LogTemp, Warning, TEXT("No sessions found"))
		} else
		{
			AHostJoinHUD* MenuHUD = Cast<AHostJoinHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
			if (!MenuHUD) return;
			
			MenuHUD->PopulateServerList(SessionSearch->SearchResults);
		}

	}

	/// start new session search to refresh
	if (bStillLookingForSessions)
	{
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
		UE_LOG(LogTemp, Warning, TEXT("Looking for sessions"))
	}
}

void UNavalBattleGameInstance::Shutdown()
{
	SessionInterface->DestroySession(*OSS_SessionHash);

	Super::Shutdown();
}

