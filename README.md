# SCC_CH3-8
## UE5 CPP - 점프 게임 (ui 구현)
### 1. 과제 개요
#### 필수 과제
* 멀티웨이브 구현
  * 3 번의 레벨 전환
  * 레벨이 증가할수록 스폰되는 아이템 개수 변경
* HUD & UI 리뉴얼
  * HUD
    * 점수, 시간, 체력 등의 정보 출력
    * 메인 메뉴, 게임 오버 메뉴
#### 도전 과제
* 아이템 상호작용
  * 부정적 아이템 추가
  * 디버프가 풀리는지 ui를 통해 보여주기
* 레벨별 환경 변화
  * 레벨이 올라갈수록 난이도 변경
* 고급 UI 연출
  * UI 애니메이션 구현
  * 3D 위젯 구현

### 2. 구현 내용
#### 필수 과제
##### 1. 멀티웨이브 구현
  * 3개의 레벨 구현<div/>
    * 레벨1의 모습<div/>
    ![image](https://github.com/user-attachments/assets/6377fd60-2fdc-4ca7-a127-0914a65b9bbd)
    * 레벨3의 모습<div/>
    ![image](https://github.com/user-attachments/assets/11a3f2f9-7904-4686-bd7f-ca0009af8432)
  * 레벨 마다 다른 Data Table을 통해 스폰되는 아이템의 확률 변경 <div/>
    * 레벨 1의 Data Table 모습 <div/>
    ![image](https://github.com/user-attachments/assets/902732a1-2f49-4c0e-a8b6-7cc5daf658d0)
    * 레벨 3의 Data Table 모습 <div/>
    ![image](https://github.com/user-attachments/assets/d9766f16-36e6-45b8-b1ca-aa43da20658f)

    * DataTable에서 데이터를 가져와 스폰할 아이템의 정보를 return 하는 함수
```
FItemSpawnRow* AItemSpawnVolume::GetRandomItem() const
{
	if (!ItemDataTable)
		return nullptr;

	TArray<FItemSpawnRow*> AllRows;
	static const FString ContextString(TEXT("ItemSpawnContext"));

	ItemDataTable->GetAllRows(ContextString, AllRows);

	if (AllRows.IsEmpty())
		return nullptr;

	float TotalChance = 0.f;
	for (const FItemSpawnRow* Row : AllRows)
	{
		if (Row)
		{
			TotalChance += Row->SpawnChance;
		}
	}

	const float RandValue = FMath::FRandRange(0.f, TotalChance);

	float AccumulateChance = 0.f;
	for (FItemSpawnRow* Row : AllRows)
	{
		AccumulateChance += Row->SpawnChance;
		if (RandValue <= AccumulateChance)
		{
			return Row;
		}
	}
	return nullptr;
}
```
##### 2. HUD & UI 리뉴얼
* HUD
  * 점수, 레벨, 남은 시간 출력 (구현 내용 정리글: https://gbleem.tistory.com/78)<div/>
  ![image](https://github.com/user-attachments/assets/6275d3ca-7b0f-4dae-840e-a3097a6c56de)
* Main Menu
  * 게임 시작 및 게임 재시작 버튼 구현 (구현 내용 정리글: https://gbleem.tistory.com/79) <div/>
    ![image](https://github.com/user-attachments/assets/8363ab05-443c-4f85-b7cc-1608c5cc1749)

#### 도전 과제
##### 1. 아이템 상호작용 추가
* **디버프 아이템 1: 캐릭터를 뒤로 밀치는 아이템**
  * 캐릭터가 해당 아이템에 닿은 후, 범위안에 있었다면 아래의 함수를 실행하는 로직
    ```
    void AMineItem::Explode()
    {
    	TArray<AActor*> OverlappingActors;
    
    	ExplosionCollisionComp->GetOverlappingActors(OverlappingActors);
    
    	for (AActor* Activator : OverlappingActors)
    	{
    		if (Activator && Activator->ActorHasTag("Player"))
    		{
    			APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Activator);
    			if (PlayerCharacter)
    			{
    				FVector LaunchVelocity = FVector(-LaunchVector * MinePower);
    				PlayerCharacter->LaunchCharacter(LaunchVelocity, true, true);
    			}
    
    		}
    	}
    	DestroyItem();
    }
    ```
    ![ue 디버프1](https://github.com/user-attachments/assets/20ea0042-2f9f-4e66-afc6-e144f625ef32)<div/>
    
* **디버프 아이템 2: 캐릭터의 움직임을 반대로 바꿔주는 아이템**
  * 캐릭터가 해당 아이템에 닿으면, 캐릭터의 움직임을 반대로 바꿔주는 효과
    * Character가 가지는 bool 변수(bIsReverseMove)를 true로 바꿔준 후
    * true인 경우 enhanced input으로 bind 한 move함수에서 방향을 반대로 만들어줌
    ```
    void APlayerCharacter::Move(const FInputActionValue& value)
    {
      ...
    	if (bIsReverseMove)
    	{
    		MoveInput.X *= -1;
    		MoveInput.Y *= -1;
    	}
    }
    ```
 * 추가적으로 3D UI를 통해 캐릭터의 상태이상 효과 출력
![ue 디버프2](https://github.com/user-attachments/assets/3c7e1380-e6cb-44a3-bc9d-154cd1fbfd53)

##### 2. 레벨 난이도 설정
* 레벨별로 다른 Data Table을 통한 난이도 설정
  
##### 3. 고급 UI
* UI 애니메이션 (구현 내용 정리 글: https://gbleem.tistory.com/80)
  * 타이머를 bar형태의 UI로 구현 후, 남은 시간이 30% 보다 낮아지면 UI 애니메이션 실행
  * 점수를 획득할 때 마다 점수 UI의 애니메이션 실행
![ue 고급ui](https://github.com/user-attachments/assets/a2ade266-1ec7-4da2-ab49-937db7ff78c3)
