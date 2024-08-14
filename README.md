## 프로젝트 요약

- Unreal Engine 5와 GAS를 이용하여 개발한 미니 게임
- 몬스터를 목표 수 만큼 처치하면 클리어, HP가 0이 되면 실패
- Blueprint로 선구현, 동작 확인 후 C++로 재구현하는 방식으로 개발
- GameplayAbilities, GameplayEffect, GameplayTags 등 GAS를 사용

## 상세 개발사항

### 이동

- 탑다운 방식으로 이동은 우클릭 시 해당 지점으로 이동하는 방식으로 구현하였습니다.
- 이동할 때는 현재 지점에서 도착지점까지의 경로를 녹색 점으로 표시하도록 구현하였습니다.

![Move1](https://github.com/user-attachments/assets/32150f93-46fa-4293-9a5f-2714b81aeb2e)

- 네비게이션 매시를 적용하여 갈 수 있는 곳이라면 이동하고 그렇지 않으면 클릭한 지점과 최대한 가까운 곳으로 이동한다.

![Move2](https://github.com/user-attachments/assets/d7d90b67-d4f5-436f-882e-5d929c4b3826)

- 우클릭을 누르고 이동하면 마우스 커서를 따라가도록 구현하였습니다.

---

### 공격

- 좌클릭 시 클릭한 방향으로 캐릭터가 회전하고 공격을 시작하도록 구현하였습니다.
- 공격 시에는 화염구 모양의 투사체가 발사되고 콤보 수치에 따라 다른 모션이 재생되도록 구현하였습니다.

![Attack1](https://github.com/user-attachments/assets/28cc5049-c084-4f07-b915-589aec637513)

---

### 몬스터 생성 및 파괴

- `GameMode`에 랜덤한 위치에 몬스터를 Spawn 하는 기능을 추가하였습니다.
- 몬스터의 `BeginPlay` 단계에서 사망하면 `GameMode`의 점수를 올리는 함수를 `OnHealthIsZero` 라는 Delegate에 연결해주었습니다.
- `GameMode`는 `BeginPlay` 단계에서 `WorldTimerManager` 를 이용하여 주기적으로 몬스터를 Spawn하는 함수를 등록하고 게임 상태를 나타내는 Enum 값에 따라 해당 타이머가 종료되거나 재시작하게 함수를 Delegate에 연결해주었습니다.

---

### 몬스터 AI

- 몬스터의 AI는 `Behavior Tree` 와 `Black Board`를 활용하여 구현하였습니다.
- 생성된 몬스터는 몬스터를 중심으로 `Collision`을 이용하여 주기적으로 플레이어를 탐색합니다.
- 탐색에 성공하면 몬스터는 플레이어 방향으로 이동하여 공격합니다.

![AI1](https://github.com/user-attachments/assets/bb209817-33d6-4590-8f53-50638984f72d)

- HP가 0이 된 몬스터는 사망 애니메이션을 출력하고 월드에서 소멸합니다.

![AI2](https://github.com/user-attachments/assets/604b5227-440d-4639-b97b-f69cf88261b1)

---

### 월드 요소

- 월드에 배치할 수 있는 포션과 트랩을 구현해두었습니다.
- 해당 요소들은 `Gameplay Ability System`을 기반으로 구현하였습니다.

![Object1](https://github.com/user-attachments/assets/d9f6bcd0-00ac-468c-ad33-83651e6b665c)

- 트랩은 Collision을 가지고 있고 플레이어와 Overlap 되면 HP가 지속적으로 감소합니다.

![Object2](https://github.com/user-attachments/assets/4383f99f-aafe-4239-a401-ba9f9c925c22)

- 포션도 같은 방식으로 구현하였지만 포션은 HP를 회복시키고 사라집니다.

![Object3](https://github.com/user-attachments/assets/c5f24695-a80b-460e-bd98-ef6ff376fb86)

---

### UI

- HUD 상단에는 현재 캐릭터의 HP, MP 정보, 현재 필드의 몬스터 수, 목표 달성 현황을 나타내는 Widget을 추가하였습니다.
- 상단의 HP Bar와 MP Bar는 각각 캐릭터에 추가된 `Attribute`의 `Health` 와 `Mana` 값의 변경에 따라 수치가 변경되며 이에 대한 내용은 `Attribute`의 속성값이 변경될 때 호출되는 Delegate에 Widget의 함수를 연결하여 값이 자동으로 변경하게 해두었습니다.
- 현재 몬스터의 수치와 달성 현황도 Widget의 함수를 `GameMode`의 Delegate에 연결해두어 자동으로 변경되게 하였습니다.

![UI1](https://github.com/user-attachments/assets/ebfc15e8-ee11-4fe6-b9fc-ea028fb9efbe)

- HUD 하단에는 현재 캐릭터의 스텟을 나타내는 상태창을 열 수 있는 버튼을 추가하였습니다.

![UI2](https://github.com/user-attachments/assets/e0147fc1-35a1-4dc2-986c-382756887497)

---

### 상태창

- HUD 좌측 하단의 X버튼을 누르면 현재 캐릭터의 스텟을 알 수 있는 상태창이 열립니다.
- 상태창에 표시되는 값들은 실제 캐릭터에 적용된 `Attribute` 의 속성값들입니다.

![Status1](https://github.com/user-attachments/assets/946195b1-eac6-4a9b-ace3-e441993d663a)
