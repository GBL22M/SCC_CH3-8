#include "BaseItem.h"

#include "Components/SphereComponent.h"

ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComp;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	CollisionComp->SetupAttachment(RootComponent);
	CollisionComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMeshComp->SetupAttachment(CollisionComp);
	StaticMeshComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnItemOverlap);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnItemEndOverlap);
}

void ABaseItem::OnItemOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		ActivateItem(OtherActor);
	}
}

void ABaseItem::OnItemEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ABaseItem::ActivateItem(AActor* Activator)
{

}

FName ABaseItem::GetItemType() const
{
	return ItemType;
}

void ABaseItem::DestroyItem()
{
	Destroy();
}

