# 이득우의 언리얼 c++ 게임 개발의 정석 공부



## Ch1. 개발 환경 설정

### 기본 프로그램의 설치

#### 언리얼 엔진의 설치

#### 비주얼 스튜디오 2017의 설치

언리얼 엔진은 5.1.0 버젼과 젯브레인사의 라이더 사용

### 언리얼 프로젝트의 생성

#### 기본 프로젝트의 생성

삼인칭 템플릿에 C++ 프로젝트로 시작용 콘텐츠 체크 해제 후 생성

#### 게임 프로젝트의 구동

#### C++ 프로젝트로의 확장

툴바->툴->새로운 C++ 클래스 선택 해서 C++ 클래스 생성

### 언리얼 C++ 개발 환경 설정

#### 언리얼 모듈의 빌드 설정

#### 비주얼 스튜디오의 환경 설정

### 예제 프로젝트의 준비

#### 예제 패키지의 추가

에픽 게임즈 런처->언리얼 엔진->마켓플레이스->Infinity Blade: Grass Lands 프로젝트에 추가

#### 예제 레벨의 제작

http://acornpub.co.kr/book/unreal-c#c. 예제 코드 파일 다운로드 후
Resource->Chapter1->Book 을 Content 폴더로 복사
새 레벨 생성, 에셋 배치



## Ch2. 액터의 설계

### 언리얼 콘텐츠의 구성 요소

#### 월드

#### 액터

#### 레벨

#### 컴포넌트

### 액터의 설계

스태틱 메시 컴포넌트를 가지기위해 Fountain.h에서 
액터의 멤버 변수로 2개의 스태틱 메시 컴포넌트 클래스의 포인터를 추가 선언
선언된 CoreMinimal.h(최소기능만 선언)을 EngineMinimal.h(다양한 엔진 기능 클래스 선언 모아둠) 변경

선언한 객체 자동으로 관리하게 만들기 위한 UPROPERITY 매크로 객체 지정

Fountain.cpp에서 컴포넌트를 실제로 생성하는 로직 구현. new가 아닌 CreateDefaultSubobject API라는 함수로 생성
루트 컴포넌트를 지정 후 자식 설정

### 액터와 에디터 연동

Fountain.h에서 UPROPERTY 매크로 안에 VisibleAnywhere 키워드 추가
배치된 c++ 클래스 에셋에 스태틱 메시 컴포넌트 지정

### 액터 기능의 확장

Fountain.cpp에 스태틱 메시 컴포넌트에 상대좌표위치 추가

프로젝트.build.cs에서 Niagara 모듈 추가-나이가라 컴포넌트를 사용하기 위해서
그 후 프로젝트 재구축 Generate Visual Studio project files 해준다.
나이아가라 관련 헤더파일 추가
포인트 라이트 컴포넌터, 나이가라 컴포넌트 클래스 포인터 추가
추가 컴포넌트들 생성 로직 구현, 자식 설정, 위치 설정

에디터 플로그인에서 Cascade To Niagara Converter 체크
P_Water_Fountain_Splash_Base_01 우클릭 나이아가라 시스템으로 변환했으나 컴파일 문제 발생
P_Buff_Shout_Freeze_02로 대신 사용이 에셋을 나이아가라 시스템으로 변환
변환된 시스템으로 Fountain에 Splash 에셋 지정

### 객체 유형과 값 유형

정수 유형 멤버 변수 추가



VisibleAnywhere 볼 수 있음. 편집하지 못하고 읽을 수만

EditAnywhere 편집 가능

Category=분류명 규칙 키워드

### 애셋의 지정

에디터에서 레퍼런스를 복사한 후 그 에셋을 가리키는 애셋의 포인터 변수를 선언 후
SetStaticMesh와 SetAsset 함수에 전달하여 에셋을 로딩하는 기능 완성
에셋 경로 정보 같은 경우는 게임 실행 중에 변경 될 일이 없기 때문에 static 선언

## Ch3. 움직이는 액터의 제작

### 로깅 환경의 설정

#### 출력 로그 윈도우

하단 툴바 출력 로그 창이나 창->출력 로그로 창을 뛰움
에디터 개인설정->일반->출력 로그->Output Log->Category Colorization Mode로 원하는 컬러모드 선택

로깅을 위한 공용 매크로 설정
게임 모듈명으로 된 헤더 파일과 소스 파일에 로그 매크로 선언과 정의
Fountain.h에서 포함한 EngineMinimal.h를 게임 모듈 헤더 파일로 변경
Fountain.cpp에서 로그 남김

추가로 ABLOG_S, ABLOG로 로그 매크로를 정의하고 지정하여 로그 남김

### 어설션

어설션Assertion은 반드시 확인하고 넘어가야 하는 점검 코드 의미

### 액터의 주요 이벤트 함수

EndPlay, PostInitializeComponents 함수 선언
선언한 이벤트 함수 정의 후 함수마다 로그를 남김

### 움직이는 액터의 설계

액터를 회전 시키기 위한 멤버변수 추가
데이터 은닉을 위해 private로 만들었으나 에디터에서 접근을 위해
UPROPERTY 매크로 메타키워드 AllowPrivateAccess 추가

프레임 타임 정보인 DeltaTime을 사용하여 초당 일정한 속도로 분수대를 회전시키는 코드를
틱 이벤트에 추가

### 무브먼트 컴포넌트의 활용

언리얼 엔진에서는 움직임이라는 요소를 분리해 액터와 별도로 관리하도록 프레임워크를 구성.
이것이 무브먼트 컴포넌트
무브 컴포넌트를 이용하여 움직임 구현

RotationMovementComponent 헤더파일 추가, 선언, 정의, 회전동작 추가

### 프로젝트의 재구성

분수대 액터 제거
액터 추가는 메뉴에서 가능하나 제거는 수동으로 해야한다.
소스폴더에서 관련 파일 지우고 비주얼 스튜디오 프로젝트 재생성함.



## Ch4. 게임플레이 프레임워크

### 게임 모드

게임 모드와 폰을 제작해볼 새로운 레벨 생성
게임 모드와 폰 생성 후 세팅
게임모드 생성자 코드에 DefaultPawn 속성 생성한 폰으로 지정

### 플레이어의 입장

Possess 함수 사용해서 빌드가 되지않음. OnPossess 함수 사용

4.22버전부터 OnPossess 함수 상속받도록 구조 변경됨



플레이어컨트롤러 클래스 생성
게임모드 생성자에서 플레이어컨트롤러 속성 값 생성한 클래스로 변경

생성과 빙의되는 과정을 알기 위해
게임 모드에서 플레이어 로그인 완료시 호출되는 PostLogin 선언 및 정의
플레이어 컨트롤러에서는 PostInitializeComponents, OnPossess 선언 및 정의
폰에서는 PostInitializeComponents, PossessedBy 선언 및 정의
그 함수 안에 로그 매크로 추가

에디터에서 삼인칭 캐릭터 블루프린트 배치 후 Auto Possess Player로 Player 0 설정
Player 0은 로컬 플레이어 의미. 레벨에 배치된 캐릭터 블루프린테에 빙의하게 됨.



수정할 때 모든 Possess 함수 변경하지 않아 에디터에서 플레이가 되지않는 문제 발생함.



## Ch5. 폰의 제작과 조작

### 폰의 구성 요소

마켓플레이스->InfinityBlade: Warriors 패키지를 프로젝트에 추가
폰 클래스에 캡슐컴포넌트, 스켈레탈메시컴포넌트, 플로팅폰무브먼트, 스프링암컴포넌트,
카메라컴포넌트 추가 선언
각각의 상대좌표와 회전, 해당 메시 할당등 선언한 멤버변수들 정의.

### 폰의 조작

5.10 부터는 축 및 액션 패밍은 폐기되었다고 하니 입력매핑컨텍스트와 입력액션을 활용

Book 폴더 안에 Input 폴더 생성하고 IMC_Default_AB 입력매핑컨텍스트 생성, Actions 폴더 생성 후 

폴더 안에 IA_LeftRight_AB, IA_UpDown_AB 입력 액션 생성 후 더블 클릭하여 둘다 값 타입 Axis1D(float)로 설정

상위 폴더 IMC_Default_AB를 더블클릭하고 매핑을 2개로 만들어 IA_LeftRight_AB, IA_UpDown_AB 할당

각각 액션 매핑 컨트롤 바인딩을 2개씩 추가하고 IA_LeftRight_AB는 키값을 A, D로  IA_UpDown_AB는 W와 S로 할당 S와 A는 Modifiers 배열 엘리먼트를 추가하여 인덱스 [0] Negate로 설정한다.



폰 헤더파일에 입력매핑콘텍스트 선언 추가 -  바인딩 키 설정을 입력 매핑콘텍스트에서 가져오기 위해서 이다.

앞 뒤로 이동하는 UpDown, 왼쪽 오른쪽으로 이동하는 LeftRight 함수 선언 추가 - 키를 눌렀을 때 움직임 동작을 구현하기 위한 함수이다.

생성자에서 ConstructorHelpers를 이용하여 에디터에서 입력매핑콘테스트에 레퍼런스를 복사하여 찾는다.

그리고 헤더파일에 할당한 입력매핑콘테스트를 가져온 레퍼런스로 정의한다.



비긴플레이 이벤트함수에서 플레이어컨트롤러를 가져와 향상된 입력 시스템을 이용하여 매핑콘텍스트를 추가함. 



입력신호를 자동으로 폼의 멤버 함수의 인자로 전달한다.  향상된 입력 컴포넌트를 이용하여 매핑콘텍스트에서 입력 액션들을 꺼내서 연동한다.



무브먼트를 이용하여 이동함수 구현.



플레이어 컨트롤러에게 UI를 배제하고 게임에게만 입력을 전달하도록 명령



### 애니메이션

에러 발생

비긴플레이에 잘못 씀



예제 코드의 애니메이션 파일 추가, 임포트
애니메이션 블루프린트 생성.
애님 인스턴스 속성 지정.



## Ch6. 캐릭터의 제작과 컨트롤

### 캐릭터 모델

캐릭터 클래스를 부모로 삼는 C++ 클래스 생성
폰클래스 제작할 때 처럼 스프링암, 카메라 추가
스켈레탈 메시 지정, 애님인스턴스 지정.
향상된 입력을 이용하여 키 바인딩. 
게임모드 디폴트 폰 클래스를 제작한 클래스로 변경.



### 컨트롤 회전의 활용

마우스가 바인딩이 안되는 현상 발생 왜일까?

향상된 입력을 사용하는 데 입력매핑콘텍스트만 활용하여 바인딩 하였는 데 입력 액션에

설정한 키를 키가 생성된 순서로 집어넣어 뒤죽박죽 들어가는 현상이 발생함.

입력 에셋 또한 헤더파일과 소스코드파일에서 선언과 정의, 에셋 지정을 해주어 문제를 해결함.



입력매핑컨텍스트로 입력액션을 접근하였는데 키바인딩 문제가 발생하여
각각의 입력 액션들도 추가로 선언, 정의, 에셋 지정하고 입력 액션에 바인딩하게 구현하였다.
Turn과 LookUp 동작 추가.



### 삼인칭 컨트롤 구현(GTA 방식)

스프링암을 다룰 SetControlMode 멤버함수 추가
움직임 동작 함수에 회전 값으로부터 방향 벡터 가져오는 코드 추가하여
시선 방향으로 동작하게 함.
캐릭터가 움직이는 방향으로 자동으로 회전시켜주는 캐릭터 무브먼트 컴포넌트의
OrientRotationToMovement 기능 사용하여 이동방향으로 캐릭터가 회전하게 함.

### 삼인칭 컨트롤 구현(디아블로 방식)

클래스 내부에 Enum 열거형 선언 해 SetControlMode의 인자 값을 분리해
현재 입력 모드를 보관할 멤버 변수 추가. 각 축의 입력을 조합해 보관할 벡터 유형의 변수 추가.

축 입력 이벤트가 발생할 때 새로 선언한 DirectionToMove 멤버 변수 업데이트하고
이후에 발생하는 Tick 로직에서 최종 멤버 변수 참고해 이동.
기존 GTA 방식처럼 디아블로 방식도 스프링암 속성 정의. 컨트롤러의 회전 속성, 움직임 정의.

UseControllerRotationYaw 속성 해제하고
캐릭터 무브먼트의 UseControllerDesiredRotation 속성을 체크하여 부드럽게 회전시킴.



### 컨트롤 설정의 변경

향상된 입력은 두 개의 입력컨텍스트매핑과 Chorded Action으로 다중키 구현
하나의 입력컨텍스트매핑과 2개의 입력액션 추가
SetControlMode를 바꾸는 함수 추가하고 바인딩.

플로트변수들과 회전변수를 추가하고 FMath::RInterpTo로 부드럽게 변하는 기능 추가.



## Ch7. 애니메이션 시스템의 설계

### 애니메이션 블루프린트

C++ 애님인스턴스 클래스 생성. 블루프린트에서 읽을 수 있는 변수 추가.
기존 애니메이션 블루프린트에 부모 클래스를 생성한 클래스로 변경.
상속 받은 변수를 이용하여 조건을 걸어 포즈를 하게함. 

### 폰과 데이터 연동

NativeUpdateAnimation 함수 선언.
이 함수는 애님 인스턴스 클래스 틱 마다 호출되는 함수
함수를 이용하여 폰에 접근해 폰의 속력 값 얻어와 변수에 저장
이 과정에서 TryGetPawnOwner 함수로 유효한 Pawn 오브젝트 포인터 받아와 속력 구함.

### 스테이트 머신의 제작

애님 그래프에서 기존 연결된 노드들 끊음.
새로운 스테이트 머신 추가 후 스테이트를 추가하여 연결 후.
그 스테이트에 기존 포즈 블렌딩 노드들 추가.



### 점프 기능의 구현

점프 입력 세팅 추가
캐릭터 무브먼트 컴포넌트를 이용하여 JumpZVelocity 기본값 변경.
점프 입력을 바인딩해서 동작할 함수를 기본 제공 Jump함수 이용
점프 모션 구현을 위해서 공기중에 있는 지 체크하는 부울 변수 추가.
IsFalling함수를 이용하여 현재 공중에 떠있는 체크.

스테이트머신에서 새로운 점프 스테이트 추가
기존 Ground 스테이트와 양방향 트랜지션 추가한 후 발생 조건을
기존 추가한 부울 변수로 결정한다.
새로운 스테이트에는 어떤 애니메이션도 할당이 안되어있기 때문에
점프 할 시 기본 포즈를 취한다.



### 애니메이션 리타겟

책과는 다르게 진행 애니메이션 폴더에서 우클릭->애니메이션->IK 릭->IK 릭 생성

스켈레탈 메시 선택->SK_CharM_Cardboard 스켈레탈 메시로 선택

우선 리타겟하기 위해 IK 리타기팅 체인을 추가해야함.

콘텐츠 브라우저에 IK_Mannequin을 찾아 오픈함. 

이 구성을 따라할거임

다시 아까 만든 IK 릭 에디터로 들어가 솔버 스택->새 솔버 추가->풀 바디 IK

pelvis, spine_01, spine_02, spine_03, clavicle_l, lowerarm_l, clavicle_r, lowerarm_r, thigh_l, calf_l, thigh_r, calf_r 선택 후 우클릭->선택된 본에 세팅 추가

pelvis 우클릭->리타깃 루트 설정, 또 우클릭->선택된 솔버의 루트 본 설정

root 선택 후->IK 리타기팅->새 체인 추가->체인 이름->Root->확인->새 체인 목표추가->목표 없음

spine_01, spine_02, spine_03 선택 후->IK 리타기팅->새 체인 추가->체인 이름->Spine>확인->새 체인 목표추가->목표 없음



clavicle_l 선택 후->IK 리타기팅->새 체인 추가->체인 이름->LeftClavicle>확인->새 체인 목표추가->목표 없음

clavicle_l, upperarm_l, lowerarm_l, hand_l 선택 후->IK 리타기팅->새 체인 추가->체인 이름->LeftIArm->확인->새 체인 목표추가->목표 추가->목표 할당->생긴 LeftArm_목표 이름 hand_l_Goal로 수정

index_01_l, index_02_l 선택 후->IK 리타기팅->새 체인 추가->체인 이름->LeftIndex>확인->새 체인 목표추가->목표 없음

ring_01_l, ring_02_l 선택 후->IK 리타기팅->새 체인 추가->체인 이름->LeftRing>확인->새 체인 목표추가->목표 없음

thumb_01_l, thumb_02_l 선택 후->IK 리타기팅->새 체인 추가->체인 이름->LeftThumb>확인->새 체인 목표추가->목표 없음

lowerarm_twist_01_l 선택 후->IK 리타기팅->새 체인 추가->체인 이름->LeftLowerArmTwist01>확인->새 체인 목표추가->목표 없음

upperarm_twist_01_l 선택 후->IK 리타기팅->새 체인 추가->체인 이름->LeftUpperArmTwist01>확인->새 체인 목표추가->목표 없음

오른 쪽도 똑같이 체인이름만 Right로 바꿔서 진행



neck_01, head 선택 후->IK 리타기팅->새 체인 추가->체인 이름->Head->확인->새 체인 목표추가->목표 없음



thigh_l, calf_l, foot_l, ball_l 선택 후->IK 리타기팅->새 체인 추가->체인 이름->LeftILeg->확인->새 체인 목표추가->목표 추가->목표 할당->생긴 LeftLeg_목표 이름 foot_l_Goal로 수정

calf_twist_01_l 선택 후->IK 리타기팅->새 체인 추가->체인 이름->LeftCalfTwist01>확인->새 체인 목표추가->목표 없음

thigh_twist_01_l 선택 후->IK 리타기팅->새 체인 추가->체인 이름->LeftThighTwist01>확인->새 체인 목표추가->목표 없음

오른 쪽도 똑같이 체인이름만 Right로 바꿔서 진행

전부 할당을 했으면 애니메이션 폴더에서 우클릭->애니메이션->IK 릭->IK 리타기터 생성

IK 릭을 선택하여 다음에서 애니메이션 복사->IK_Mannequin 선택

만든 IK 리타기터로 들어가 디테일->타깃->타깃 IK 릭 에셋->만든 IK 릭 선택->타깃 프리뷰 메시->SK_CharM_Cardboard 선택

똑같이 겹쳐있기에 디테일->프리뷰 세팅->타깃 메시 오프셋을 수정->X값 200정도 적당함

체인 매핑이 자동으로 됨. 타깃 체인과 소스 체인의 이름이 같게 맞춰줌(Twist는 조금 다를 수 있음)

에셋 브라우저에서 MM_Fall_Loop, MM_Jump, MM_Land를 이용할거임

MM_Fall_Loop를 클릭하면 재생이 됨. 체인매핑->글로벌 세팅 클릭->디테일->Global Settings->글로벌 리타깃 페이즈에서 IK 활성화 체크해제하면 좀 더 자연스러움->하단 에셋 브라우저-> 선택된 애니메이션 익스포트

에셋 브라우저에서 MM_Jump 를 클릭하면 재생이 됨. 체인매핑->글로벌 세팅 클릭->디테일->Global Settings->글로벌 리타깃 페이즈에서 모두 활성화 체크하면 좀 더 자연스러움->하단 에셋 브라우저-> 선택된 애니메이션 익스포트

에셋 브라우저에서 MM_Land를 클릭하면 재생이 됨. 체인매핑->글로벌 세팅 클릭->디테일->Global Settings->글로벌 리타깃 페이즈에서 IK 활성화 체크해제하면 좀 더 자연스러움->하단 에셋 브라우저-> 선택된 애니메이션 익스포트

리타겟한 애니메이션들은 애니메이션 폴더에 익스포트한다.

### 점프 구현

스테이트를 총 4개로 추가 Ground, JumpStart, JumpLoop, JumpEnd.
JumpStart, JumpLoop, JumpEnd 스테이트 애니메이션 시퀀스 할당.
Warrior_Land 시퀀스가 에디티브 시퀀스여서 No additive로 변경.
트랙잭션을 이어주고 JumpStart->JumpLoop와 JumpEnd->Ground 트랙잭션은
Time Remaining 노드를 이용해 0.1보다 작으면 넘어가게 진행
또한 Automatic Rule Based on Sequence Player in State 조건으로 해도 되나.
JumpEnd 같은 경우 이미 하늘에 있지 않을 때 작동하는 애니메이션이라 어색하게 느껴짐.



Land 애니메이션이 동작할때 사라지는 현상이 발생

이유가 뭔가 보니 Land 애니메이션만 노드로 배치하면 초록색이였다.

초록색은 에디티브 시퀀스 플레이어이다. 

애니메이션 시퀀스 에디터로 이동하여->에셋 디테일->에디티브 세팅->No additive로 바꾼다.

출처: <https://velog.io/@myverytinybrain/%EC%96%B8%EB%A6%AC%EC%96%BC-%EC%95%A0%EB%8B%88%EB%A9%94%EC%9D%B4%EC%85%98-%EB%B8%94%EB%A3%A8%ED%94%84%EB%A6%B0%ED%8A%B83>



## Ch8. 애니메이션 시스템 활용

### 애니메이션 몽타주

공격 연계 동작을 넣기 위해 몽타주 에셋 생성
섹션 설정. 사용할 애니메이션들 지정 후 끝 시간 수정.
Attack 액션 입력 생성. 캐릭터 소스코드에 Attack 함수와 키 바인딩.
애님인스턴스 클래스에서 몽타주 에셋 지정.
Montage_IsPlaying 함수를 사용해 현재 몽타주가 재생하는 지 파악하고
재생 중이 아니면 Montage_Play함수로 재생하는 로직 구현

애니메이션 블루프린트에서 몽타주 재생노드를 애님 그래프에 추가
캐릭터 소스코드에서 Attack 함수에서 애님인스턴스로 접근해 몽타주를 재생.

### 델리게이트

애님 인스턴스에 애니메이션 몽타주 재생이 끝나면 발동하는
OnMontageEnded라는 델리게이트 제공함.
어떤 언리얼 오브젝트라도 UAnimMontage * 인자와 bool 인자를 가진 멤버 함수를 가지면
이를 OnMontageEnded 델리게이트에 등록해 몽타주 재생 끝나는 타이밍 파악가능.

캐릭터 헤더파일에 PostInitializeComponents() 함수 선언.

애님 인스턴스에 애니메이션 몽타주 재생이 끝나면 발동하는
OnMontageEnded라는 델리게이트가 접근할 수 있게
UFUNTION 매크로 추가 선언과 UAnimMontage * 인자와 bool 인자를 가진
멤버 함수 추가 선언.
bool 인자 멤버 변수로 선언.

check나 ensure 어설션 대신 런타임에서 문제 발생 시
붉은색 에러 로그를 뿌리고 바로 함수를 반환하는 매크로를 프로젝트 헤더 파일에 추가

애님 인스턴스는 캐릭터 클래스에서 자주 사용하기 때문에 멤버 변수로 전방 선언
PostInitializeComponents() 함수를 정의할 때
매크로를 활용해 애님 인스턴스의 OnMontageEnded 델리게이트와
선언한 OnAttackMontageEnded를 연결, 델리게이트가 발동할 때까지 애니메이션 시스템에
몽타주 재생 명령을 내리지 못하게 폰 로직 막아줌.

폰 로직에서 입력이 들어오면 애님 인스턴스의 PlayAttack을 호출하도록 로직을 추가

델리게이트에 의해 공격의 시작과 종료가 감지되므로 AnimInstance에
Montage_IsPlaying 함수 더 이상 사용하지 않는다. 



### 애니메이션 노티파이

몽타주 에셋에 AttackHitCheck 노티파이 추가
애님 인스턴스 클래스에서 AnimNotify_노티피아명 멤버함수 선언 및 정의
해당 멤버 함수는 언리얼 엔진이 자동으로 해당 노티파이가 호출되면
자동으로 호출함.

### 콤보 공격의 구현

몽타주 에셋에서 추가로 몽타주 섹션을 추가하고 해당 색션에 각각 애니메이션 시퀀스 배치.
추가 노티파이를 트랙과 노티파이를 추가하여 다음 시퀀스로 넘어갈 부분에 마크함.
노티파이의 몽타주 틱 타입을 Branching Point로 바꿈.
캐릭터 클래스에 최대콤보, 콤보카운터, 콤보이동가능여부, 콤보입력여부 변수 선언 추가.
공격이 시작할 때 관련속성 지정 함수, 공격이 종료할 때 함수를 선언 추가
각각을 정의해줌.

애님인스턴스 클래스에서 애니메이션 노티파이가 발생할 때마다 
캐릭터에 전달할 반환 값과 인자 값이 없는 함수 유형으로 델리게이트를 선언하되,
여러 개의 함수가 등록되도록 멀티캐스트로 선언.
애니메이션 노티파이 함수에서 Broadcast라는 멀티캐스트 델리게이트에 등록된
모든 함수를 호출하는 멀티캐스트 델리게이트 명령을 이용하여 이를 호출.
콤보 카운트를 전달받으면 해당 몽타주 섹션을 재생하도록 기능을 하는 함수 구현.

캐릭터 클래스에서 
PostInitializeComponents 함수에서
OnNextAttackCheck 델리게이트와
다음 콤보 가능 여부를 false로 
콤보 입력 온이 true면 콤보시작상태함수 출력하고
해당 콤보 몽타주 섹션으로 점프하는 로직을
람다식으로 선언하고 등록 구현.

공격 함수에서 공격 중이라면 콤보 입력을 가능 상태로 바꾸고
공격 중이 아니라면 콤보 상태를 시작하고 몽타주를 시작하고 기타 설정.
몽타주가 끝나면 호출되는 함수에 공격중 false로, 콤보가 끝난 상태 함수 호출.



## Ch9. 충돌 설정과 대미지 전달

### 콜리전 설정

오브젝트 채널 추가, 프리셋 추가.
각 프리셋에 새로 추가한 오브젝트 채널에 맞는 설정으로 변경.
캐릭터 클래스에서 캡슐컴포넌트의 콜리진 프로파일을 새 프리셋으로 변경.
콜리전 프리셋을 확인하기 위해 레벨에 캐릭터 클래스 배치.

### 트레이스 채널의 활용

트레이스 채널 추가.
기존 만든 프리셋에 새로 만든 트레이스 블록 지정.
캐릭터 클래스에서 공격체크함수 추가 선언.
포스트이니셜라이즈컴포넌트스 함수에서
멀티캐스트 듀플리케이트 매크로로 선언된
어택힛체크에 공격체크함수 바인딩.
공격체크함수 정의를 할 때
GetWorld를 이용해 월드에 명령을 내리는 데
트레이스 채널을 사용해 물리적 충돌 여부를 가리는 함수 중
하나인 SweepSingleByChannel로 파라미터 설정 인자 값들을 넣고
FHitResult라는 구조체에 충돌 정보를 담는다.
결과가 트루고 힛리졸트가 있으면 로그를 남긴다.



트레이스 채널을 사용해 물리적 충돌 여부를 가리는 함수 중 하나로 SweepSingleByChannel이 있다. 물리는 월드의 기능이므로 GetWorld() 함수를 사용해 월드에게 명령을 내려야 한다. 

해당 함수는 기본 도형을 인자로 받은 후 시작 지점에서 끝 지점까지 쓸면서 Sweep 해당 영역 내에 물리 판정이 있어났는지를 조사한다. 이 함수에서 사용할 파라미터 설정은 꽤나 복잡한데, 인자로 넣은 요소들은 다음과 같다.

- HitResult: 물리적 충돌이 탐지된 경우 관련된 정보를 담을 구조체
- Start: 탐색을 시작할 위치
- End: 탐색을 끝낼 위치
- Rot: 탐색에 사용할 도형의 회전
- TraceChannel: 물리 충돌 감지에 사용할 트레이스 채널 정보
- CollisionShape: 탐색에 사용할 기본 도형 정보. 구체, 캡슐, 박스를 사용한다.
- Params: 탐색 방법에 대한 설정 값을 모아둔 구조체
- ResponseParams: 탐색 반응을 설정하기 위한 구조체



### 디버그 드로잉
캐릭터 클레스 헤더 파일에 공격 길이, 공격 반지름 변수 선언.
클래스 파일에 DrawDebugHelper 헤더파일을 포함하고
생성자에 공격 길이와 공격 반지름 변수 정의.
공격체크함수에서 전처리기 조건문을 이용해 드로우디버그가 가능하면
길이와 반지름을 이용해 캡슐의 필요한 인자 값들을 만들고
DrawDebugCapsule 함수를 이용하여 안맞으면 빨간색, 맞은면 초록색으로
그리고 하고 조건이 끝나면 똑같이 로그 출력하게 함.



- 멈추지 않고 계속 가는 현상 발생

디아블로 시점일 시에 무브가 멈추지 않는 문제 발생
무브 입력 액션 바인딩에 트리거드 이벤트말고도
컴플리트라는 트리거링 되었을 때 이벤트에 움직임 관련 함수를 바인딩해서
호출하게 하여 움직임 함수 인자로 마지막에 0을 더하게 만들어 해결하였다.

#### 대미지 프레임워크

캐릭터 클래스 헤더파일에서
액터 클래스 구현돼 있는 액터에 데미지 전달하는 TakeDamage 함수 선언.

캐릭터 클래스 소스코드파일에서
선언한 TakeDamage 함수를 정의 우선 부모 클래스에 대미지 관련 로직이 구현돼
있기 때문에 부모 클래스의 로직을 먼저 실행하고 로그 매크로 추가한 후
받은 데미지를 리턴하는 코드 구현.

공격체크함수 정의에서 인자 값으로 쓰기 위한 데미지이벤트를 선언하고
맞은 액터의 테이크데미지함수에 인자값을 넣어 호출.

애님인스턴스 클래스 헤더파일에서
죽는 애니메이션 재생을 위한 SetDeadAnim 함수 선언
그걸 판단할 부울 변수 IsDead 선언

소스코드에서 생성자일 때 
IsDead 거짓으로 정의.
네이티브업데이트애니메이션 함수에서 폰클래스가 없으면 리턴바로하고
폰이 존재하면 코드 죽지 않으면 조건으로 바꿈.
몽타주 관련 함수에 죽었는지 체크 매크로 추가.

다시 캐릭터 클래스 소스코드로 가서
맞으면 바로 죽게하게 하기 위해 받은 데미지가 0보다 크면
애님인스터스에 죽은 상태로 만드는 함수 호출하고
액터 자신을 콜리전이 불가능하게 만듬.

에디터에서 애니메이션 블루프린트로 이동하여
부울로 포즈 블렌딩을 추가하여 Is Dead 변수로
죽는 애니메이션 포즈와 기존 베이스 액션을 설정.



## Ch10. 아이템 상자와 무기 제작

### 캐릭터 소켓 설정

마켓플레이스에서 InfinityBlade Weapons를 프로젝트에 추가.
안에 무기 스켈레탈 메시를 위해 스켈레탈 메시에서 소켓 hands_rSocket 트랜스폼 재조정.
캐릭터 헤더 파일에서 무기에 해당하는 스켈레탈메시컴포넌트 멤버변수 선언.
캐릭터 소스코드 생성자에서 무기 소켓이 존재하면
무기 에셋의 레퍼런스를 복사한 후 컴포넌트 로딩 후 SetAttachment 함수에
소켓 이름을 인자로 넘겨 소켓 위치를 기준으로 트랜스폰이 자동으로 설정되게 함.

### 무기 액터의 제작

무기를 바꿀 수 있게 무기를 액터로 분리하기 위한
부모클래스를 액터로 갖는 C++ 무기 클래스 생성.
무기 헤더 파일에 프로젝트 헤더파일 포함하고
스켈레탈메시컴포넌트로 무기 멤버변수 선언.
무시 소스코드 파일에서 생성자에서
무기 멤버변수를 루트 컴포넌트로 지정하고
에셋을 지정하여 정의하고
캐릭터가 드는 무기는 실제로 충돌을 발생시키지 않고
플레이어의 악세서리로만 사용하기에 충돌 설정 NoCollision으로 지정.
무기 클래스는 틱이벤트를 지우고 틱사용을 false로 한다.

캐릭터 클래스 소스코드에서 비긴플레이시
월드에서 새롭게 무기 액터를 생성한 후
소켓에 붙인다.

### 아이템 상자의 제작

부모를 액터로 같는 아이템상자 C++ 클래스 생성.
모델로 삼을 에셋의 크기가 작아 LOD0 섹션에서 빌드 스케일 옵션 설정.
아이템상자에 사용할 오브젝트 채널과 프리셋 생성.
아이템상자 오브젝트 채널은 기본으로 무시로 설정.
프리셋 또한 전부 무시나 AB캐릭터만 겹침으로 설정하고
콜리전 켜짐 메뉴의 값을 Query Only(No Physics Collision)으로 지정.
AB캐릭터 프리셋에서도 아이템 박스를 겹침으로 설정.

아이템 박스 헤더파일에
프로젝트 헤더파일 포함시키고
포스트이니셜라이즈컴포넌트스 함수 오버라이드 선언.
OnComponentBeginOverlap 멀티캐스트 다이내믹 델리게이트에 
바인딩해 콜백할 OnCharacterOverlap 함수 선언.
콜리전을 위한 박스컴포넌트 Trigger멤버변수와
에셋으로 박스를 보여줄 스태틱메시컴포넌트 Box 멤버 변수를 선언.

아이템 박스 소스코드로 가서 틱이벤트는 사용하지 않느다.
생성자에서 트리거와 박스의 오브젝트를 정의하고
계층 관계를 설정하고 박스 영역 크기를 설정하고
에셋을 지정하고 위치를 정해준다.
그 다음 생성자에서 트리거와 박스의 콜리전프로파일세팅.

포스트이니셜라이즈컴포넌트스 함수에서
부모 함수 동작 후 OnCharacterOverlap을 OnComponentBeginOverlap에 콜백함수로
바인딩 해주는 코드 추가.

OnCharacterOverlap 함수를 정의해서
일단 로그만 출력하게 함.

### 아이템의 습득

프로젝트 헤더파일에서
나이가라컴포넌트 헤더파일 포함-나이가라 컴포넌트를 사용하기 위해서

아이템 헤더파일에서
나이가라컴포넌트 선언
웨폰클래스 선언-특정 클래스와 상속 받는 클래스들로 목록을 한정하는
TSubclassof란는 키워드 이용
OnEffectFinished 함수 선언-효과 시스템에서 제공하는 이팩트 재생때 호출되는 델리게이트
OnSystemFinished에 재생 종료시 동작 로직을 위한 함수이다.

소스파일
웨폰헤더파일, 캐릭터헤더파일 포함
생성자에서 나이가라컴포넌트 에셋지 지정및 속성 설정하고
웨폰클래스의 기본 클래스 값을 지정

OnCharacterOverlap 함수에서 아이템상잦에 설정된 클래스 정보로부터
무기 생성하고 이를 캐릭터에게 장착시키는 기능 구현+
캐릭터가 아이템 셋이 가능하면
이펙트를 발동시키고 재생 종료시에 호출할 함수 바인딩.

OnEffectFinished 함수에서 액터를 파괴 코드 추가.

캐릭터 헤더파일에서
무기세팅가능한지 판단 함수 선언, 무기를 세팅하는 함수 추가
현재 무기를 가리키는 멤버 변수로 무기클래스포인터 선언.

소스파일에서
비긴플레이함수에서 기존 무기세팅하는 코드 지움.
무기세팅가능한지 판단함수 정의는 현재무기가 널이면 true 리턴.
무기세팅함수는 세팅할려는 무기가 널이 아니면
새로운 무기로 현재 무기를 바꾼다.



## Ch11. 게임 데이터와 UI 위젯

### 엑셀 데이터의 활용

부모를 GameInstance로 갖는 C++ 클래스 생성
프로젝트 세팅->맵모드->게임인스턴스를 새로 생성한 게임인스턴스로 변경

헤더파일로 이동해 프로젝트 헤더 파일, 데이터테이블 헤더파일 포함
FTableRowBase 를 상속받은 FABCharacterData라는 이름의 구조체 선언
임포트할 CSV 파일의 각 열의 이름과 동일한 멤버 변수를 타입에 맞춰 선언.

생성자 선언과 초기화 함수 선언
캐릭터데이터를 반환하는 함수 선언
데이터테이블 타입의 캐릭터 테이블 선언

게임인스터스 소스코드에서는 
생성자에 선언한 데이터테이블 타입 캐릭터 테이블 지정
초기화함수에 부모 초기화함수 호출
캐릭터 데이터 반환하는 함수는 레벨 값을 반환.

## 액터 컴포넌트의 제작

액터 컴포넌트를 부모로 가지는 캐릭터 스텟관련 C++ 클래스 생성

- 헤더 파일로 이동 후
필요 없기에 틱이벤트 제거

캐릭터 클래스에서 이를 바인딩 시키는 형태로 구조설계하기 위해
캐릭터에 의존성을 가지지 않도록,FOnHPIsZeroDelegate 멀티캐스트 델리게이트 선언

생성자 선언
액터의 포스트이니셜라이즈컴포넌트가 호출되기전 
컴포넌트에서 바로 호출되는 InitializeCompoment 함수 선언.

레벨이 변경되면 해당 스텟이 바뀌도록 하는 SetNewLevel 함수 선언

대미지는 캐릭터의 TakeDamage 함수에서 직접 처리했는ep
이제 스탯컴포넌트에 SetDamage를 TakeDamage에서 호출하는 방식으로 하기 위해
현재체력에 대미지를 더하는 SetDamage 함수 선언.
현재스텟데이터에서 공격력(대미지)를 가져오는 GetAttack 함수 선언.

위에 선언한 델리게이트를 OnHPIsZero로 선언.
캐릭터데이터타입의 현재스텟정보, 레벨, 현재 HP정보 변수들을 private로 한정해 선언.

- 스탯컴포넌트 소스코드에서
생성자에 Tick 관련 false로 변경.
bWantsInitializeComponent=true로 지정-InitializeCompoment 함수 사용할려면 해야함
이니셜 라이즈 컴포넌트를 원하냐는 것.
레벨은 1로 지정.

InitializeCompoment 함수에서
부모 InitializeCompoment 함수 호출하고
SetNewLevel 호출해서 인자값 레벨을 넣어 그에 맞는 스텟을 가지게함.

SetNewLevel 함수정의
게임인스턴스를 지정해 캐릭터스텟데이터를 불러들여
인자 값으로 받은 레벨에 맞는 체력으로 현재 체력을 바꿈.

SetDamage 함수 정의
현재체력에서 데미지를 빼는데 0과 최대체력 사이로 한다.
현재 체력이 0보다 작게되면 브로드캐스트함수 호출
델리게이트에 붙은 모두를 동시에 실행한다.-현재 체력이 0일때 함수 작동일 위해
예로 죽는 애니메이션 재생 등

GetAttack 함수 정의
현재스텟데이터에서 공격력을 반환함.

- 캐릭터 클래스 헤더파일에서
캐릭터스텟컴포넌트 타입 변수 선언.

- 캐릭터 소스코드에서
생성자 함수에 캐릭터스텟컴포넌트 변수 지정 추가.

포스트이니셜라이즈컴포넌트 함수에서 OnHPIsZero 델리게이트에 람다함수 추가
호출시 죽는 애니메이션이 재생하게 하고 콜리전이 불가능하게하는 함수

테이크대미지함수에서 기존 데미지가 0보다 크면 죽는 조건과 코드를 지우고
캐릭터 클래스에서 정의하고 선언한 스탯컴포넌트에서 셋데이터 인자값 대미지를 넣고 호출.

어택체크함수에서
데미지를 줄때 데미자 값을 스탯컴포넌트에서 공격력을 구해서 테이크함수에 인자값으로 넣고 호출.

### 캐릭터 위젯 UI 제작

Fil Scereen->Custom 변경 후 150X50으로 공간 크기 변경
세로박스 추가 ->세로박스 하위 계층으로 Spacer, 프로그레스바, Spacer 추가 후
각각 40, 20, 40 씩 영역을 차지하게 한다. Spacer들을 채우기를 하면됨.
프로그래스바 이름을 PB_HPBar로 짓고 색을 빨간색으로 지정.

### 모듈과 빌드 설정

- 위젯을 사용하기 위해 프로젝트.Build.cs 파일로 이동하여
UMG 모듈을 추가.
- 캐릭터 클래스 헤더파일에 
위젯 컴포넌트 변수 추가 선언
- 캐릭터 소스코드에서
위젯 컴포넌트을 지정하고 계층구조를 정함.
위젯의 위치와 위젯 모드를 설정.
위젯 컴포넌트에 에셋을 지정하고 크기를 정함.

### UI와 데이터의 연동

UesrWidget을 부모로 삼는 C++ 클래스 생성

-스탯컴포넌트 헤더파일에서
멀티캐스트 딜리게이트 FOnHPChangedDelgate 선언
인자값으로 현재 피를 만드는 SetHP 선언
현재 체력/최대 체력 비율을 반환하는 GetHPRatio 선언
FOnHPChangedDelgate를 OnHPChanged로 선언



-스탯컴포넌트 소스코드에서
기존 SetNewLevel, SetDamage 함수들
SetHP 이용하여 체력관리로 변경.

SetHP 함수 정의
현재 체력을 인자값으로 바꾸고
OnHPChanged 브로드캐스트 호출
0과 비교할 때 미세한 오차범위 사실상 0인 
KINDA_SMALL_NUMBER 보다 작으면
OnHPIsZero 브로드 캐스트하고 현재 체력 0으로 만듬.

GetHPRatio 함수 정의
현재 체력/최대 체력 비율을 반환



-캐릭터 위젯 헤더파일에서
위젯에서 캐릭터의 스텟을 사용할 수 있고 체력이 바뀔시 
HPRatio 업데이트할 것을 델리게이트에 바인딩하는 로직이 있는
BindCharacterStat 함수 선언

UI 시스템이 준비되면 호출되는 NativeConstruct 함수 선언
UI는 PostInitializeComponent 함수에서 발생한 명령 반영하지 않는다.

NativeConstruct 함수 내에서 위젯 내용을 
업데이트하는 로직을 구현하기 위한 UpdateHPWidget 함수 선언.

클래스스탯 컴포넌트 접근할 TWeakObjectPtr 약 포인터 선언
UI와 캐릭터가 서로 다른 액터일 경우를 위해서.

프로그레스바를 다루기 위한 변수 선언.



-캐릭터 위젯 소스코드에서
BindCharacterStat 함수 정의
현재캐릭터스탯을 받아온 인자값으로 바꾸고
OnHPChanged 델리게이트에 위젯을 업데이트 함수를 바인딩함.

NativeConstruct 함수정의
부모 생성자 호출
프로그레스 바를 지정
위젯을 업데이트함.

UpdateHPWidget 함수 정의
현재캐릭터스텟이 존재하고
프로그레스바가 널이 아니라면
캐릭터스텟에서 구한 체력 비율로
프로그레스바의 퍼센트를 세팅한다.

-캐릭터 클래스 소스코드에서
기존에 생성자에서 무기 장착 코드 지우고
그 안에 있는 위젯의 클래스 지정 코드 밖으로 빼냄.

비긴플레이 함수 코드에
HPBar위젯의 BindCharaterStat 호출
:여기서 문제 발생햇음.
PostInitializeComponents()에 추가 할 시 위젯의 초기화 시점은 BeginPlay로 변경되어
널을 가르켜 바인딩이 안되는 문제 발생.

### AIController와 내비게이션 시스템

부모로 AIController 클래스를 가지는 C++ 클래스 생성
빌드 툴 모듈 세팅에서 "NavigaitionSystem" 추가

-캐릭터 클래스 소스코드
생성자에서 AI컨트롤러클래스 만든 클래스로 지정
AI 생성 옵션 지정-레벨에 배치되거나 새롭게 생성된 캐릭터마다 AI컨트롤러 액터 생성.

-AI 컨트롤러 헤더파일에서
AI컨트롤러 생성자 선언, 빙의 함수 선언, 빙의 해제 함수 선언
타이머에 반복할 OnRepeatTimer 함수 선언
타미어를 구별할 타이머핸들과 실수형 반복시간 선언.

-AI 컨트롤러 소스코드에서
생성자에서 반복하는 시간 3초로 지정.

빙의함수에서
부모 빙의 함수를 호출하고
월드에 있는 타임매니저를 호출하여 타이머를 세팅하는데
인자 값으로 선언한 타이머핸들, AI컨트롤러, 반복할 OnRepeatTimer, 반복 트루로 전달하고 호출.

빙의해제함수에서
부모 빙의해제함수 호출 후
타임매니저에서 타이머핸들이 가리키는 타이머 지움.

OnRepeatTimer 함수에서
현재 폰 클래스를 받아오고
네비게이션 시스템을 이용해
다음 랜덤한 다음 목적지를 뽑아 이동하게 이동하게 함.

### 비헤이비어 트리 시스템

-빌드 세팅에서 GameplayTasks 추가
-에디터에서 블랙보드와 비헤이비어 트리 생성
블랙보드에서 HomePos와 PatrolPos 벡터 타입 키 추가

-AI 컨트롤러 헤더파일에서 
리피터타임에 관련된 함수와 변수, 언포제스 함수 선언들을 지우고
블랙보드와 비헤이비어트리 선언, 또한 참조하기 편하게 하기위해 블랙보드 키 값들 하드코딩 선언.

-AI 컨트롤러 소스코드에서 
선언한 키 값들의 FName을 TEXT로 정의.

생성자에서 기존 코드 지우고 블랙보드와 비헤이비어트리 에셋지정.

빙의 함수에서 부모 함수 호출 이후 다 지우고
블랙보드컴포넌트를 새로 선언하고 정의함.-UseBlackboard를 사용하기 위해서
지정한 에셋과 컴포넌트로 블랙보드를 이용할 수 있게 하고 트루면
현재 컨트롤러가 통제하는 폰의 위치를 받아와 블랙보드 HomePosKey에 폰이 현재 위치 나타내는 벡터 값에 대입 후
컨트롤러가 지정한 비헤비어트리를 런한다. 실패하면 로그를 띄게한다.

-BTTaskNode를 부모 클래스로 하는 C++ 클래스 생성
순찰할 포지션을 찾는 태스크 클래스 헤더파일에서
생성잔 선언, 실행태스크 선언.

-소스코드에서
생성자에서 노드이름을 지정.

실행 테스크에서
비헤이비어 컴포넌트를 통해 현재 통제중인 폰을 추출
널 일시 리턴 페일드.
통제중인 폰으로 네이비게이션 시스템 얻음
널 일시 리턴 페일드.
비헤이비어 컴포넌트를 통해 HomePosKey 가리키는 값을 구함
이 값과 네비게이션 시스템을 이용하요 범위 안에 갈 수있는 랜덤값 구함
이 값을 블랙보드 PatrolPosKey 벡터가 가리키는 값으로 지정.
그리고 성공 리턴.

-비헤이비어 트리에서
시퀀스 배치 후
Wait(5초), FindPatrolPos, Move To(PatrolPos)로 배치하여
5초마다 랜덤한 장소로 가게하는 행동하게 한다.



ABAIController.cpp 에서

```c++
const FName AABAIController::HomePosKey(TEXT("HomePos"));
const FName AABAIController::PatrolPosKey(TEXT("HomePos"));
```

이렇게 정의되어 있어 C++ 소스코드에서 같은 키를 가리키고 있어 다음 순찰할 목적지를 안내하지 않는 문제가 발생했다. 이것을 못찾아 시간을 매우 많이 허비함. 키 값들을 코드 중간 일일히 로그를 출력하여 언제 값들이 변하고 안변하지 확인해 홈키와 패트롤키가 동시에 바뀌는 걸 확인하고 원인을 찾았다. 다음부터는 오타나 잘못된 레퍼런스가 없는 지 더 철저히 확인해야 겠다.

### NPC의 추격 기능 구현

-블랙보드에서 Target 타입은 오브젝트 기반 클래스는 ABCharacter로 하는 키 추가

-BTSevice를 부모로하는 C++ 클래스 BTService_Detect 생성
헤더파일에서 
생성자 선언, 컴포짓 활성화될 경우 주기적으로 호출하는 틱노드 함수 선언.

-소스코드에서
노드 이름 지정. 인터벌(간격) 지정.

틱노드 함수에서
부모 함수 호출, 통제중인 폰 지정, 
통제중인 폰으로 월드와 폰의 위치 가져옴,
감지 범위 지정, 월드 값이나 폰이 널이면 리턴해버림,
TArray<FOverlapResult> OverlapResults 선언 후
콜리전 관련 변수 정의.
반경내 모든 캐릭터를 감지하는 OverlapMultiByChannel 함수를 사용하여 
반경 내에 감지된 모든 캐릭터 정보를 TArray로 전달 구현.
감지가 되었다면
오버랩리졸트를 하나 검출해서
캐릭터 클래스형으로 캐스트하고 그것이 플레이어컨트롤러가 맞다면
블랙보드의 컴포넌트로 타겟키로 셋하고, 디텍트 범위 초록색 원 그림,
파란색 점과 캐릭터까지의 파란색 선을 그리고 리턴.
결과에 없으면 빨강색 데틱트 디버그 원 그리기.

-AI 컨트롤러 헤더파일에서
참조위한 타겟키 선언
-소스코드에서
타겟키 정의

-캐릭터 헤더파일에서
컨트롤모드 NPC 추가, PossessBy 함수 선언.
-소스코드에
셋컨트롤모드 함수에서
NPC일때 회전비율 등 세팅.
선언한 PossessBy 함수를
플레이어 빙의시 디아블로컨트롤모드, 이동속도 600,
아닐시 NPC모드, 이동속도 380으로 하게함.

-비헤이비어 트리에서 셀렉터 추가 후 타겟을 향해 무브 투 하는 시퀀스와 테스크 추가(기존 시퀀스보다 우선)
Detect 서비스 추가, 각 시퀀스에 블랙보드 데코레이터 추가 후 블랙보드 키, 관찰자 등 디테일 설정.

### NPC의 공격

-캐릭터 헤더파일에서
FOnAttackEndDelegate 멀티캐스트 듀플리케이트 선언-어택 종료시 브로드캐스트하기 위해
FOnAttackEndDelegate를 OnAttackEnd로 선언하고 Attack()로 같이 public으로 옮겨줌.-다른 클래스에서 접근하기 호출하기 위해
-소스코드에서
OnAttackMontageEnded함수에서
함수 안에서 끝에 OnAttackEnd.Broadcast() 공격몽타주가 끝나면 브로드캐스트.

-BTDecorator를 부모로 하는 BTDecorator_IsInAttackRange C++ 클래스 생성
헤더파일에서 생성자 선언, CalculateRawConditionValue 함수 선언
소스코드에서 생성자에서 노드이름 지정.
CalculateRawConditionValue 함수
공격 범위 내에 있는 판단하는 코드 구현.

-BTTaskNode를 부모로하는 BTTask_Attack C++ 클래스 생성
헤더파일에서 생성자 선언, 실행테스크선언 함수선언, 틱태스크선언. 부울 변수 IsAttacking=false 선언 및 정의.
소스코드에서 생성자에서 bNotifyTick 트루, IsAttacking false,
실행 태스크에서 캐릭터 공격함수 실행, 공격중 트루, 공격끝나면델리게이트에 람다식 공격중 false 바인딩 하고 인프로그래스 리턴.
틱태스크에서 공격중이 아니면 석시드함.

-BTTaskNode를 부모로하는 BTTask_TurnToTarget C++ 클래스 생성
헤더파일에서 생성자 선언, 실행 테스크 함수 선언.
소스코드에서 생성자에서 노드이름 지정.
실행 태스크에서 타겟의 현재 위치에서 내 위치를 이용해서
쳐다봐야할 회전 값을 구해서 회전함.

-비헤이비어트리에서 컴포짓과 태스크와 데코레이터를 이용해서
마저 구현.



## Ch13. 프로젝트 설정과 무한 맵의 제작

### 프로젝트의 정리와 모듈의 추가

프로젝트 폴더로 이동하여 소스/프로젝트 폴더에서 .cpp 파일은 Private 폴더, .h 파일은 Public폴더들 생성 후 모두 옮김.
비주얼 스튜디오 프로젝트 파일 재성성.

별도의 게임 모듈을 위해 예제 코드 파일에서 ArenaBattleSetting 모듈 폴더 가져와 소스 폴더로 옮김.
프로젝트.Taget.cs, 프로젝트Editor.Target.cs 파일에 모듈 이름 추가. 
프로젝트.uproject에도 모듈 추가 후 PreDefault로 설정.

에디터에서 Object를 부모로 같는 C++ ArenaBattleSetting 클래스를 생성하여
ArenaBattleSetting 모듈로 지정하여 생성. 

### INI 설정과 애셋의 지연 로딩

-Config 폴더에 예제코드 제공한 ini 파일 추가

-ABCharacterSetting 헤더파일에서 UCLASS 매크로 config 키워드 추가-불러들일 INI 파일 지정
생성자 선언, 애셋 경로 정보를 보관하기 위해 TArray<FSoftObjectPath> 클래스 CharacterAssets 선언-속성 config 선언.
-소스코드에서 생성자 정의.-함수만 구현하고 아무것도 구현하지 않음

-빌드 설정(프로젝트.Build.cs)에서 Private 폴더에서 모듈 사용하도록 PrivateDependencyModule 항목 추가.

-ABGameInstance.h 헤더파일에서
게임 진행 중 비동기 방식으로 애셋을 로딩하는 FStreamableManager 선언.

-ABCharacter.h 헤더파일에서
FStremableDelegate 로딩 완료시 호출하기 위한 연동할 OnAssetLoadCompleted 함수 선언.
애셋 경로 정보를 보관하기 위한 FSoftObjectPath 클래스 타입 변수 널로 선언 및 정의.
스레드에 안전하고 C++ 객체를 참조 카운팅하는  TShardPtr 클래스
비동기또는 동기 로드하는 핸들 (로드된 에셋 메모리 유지하는 )FStreamableHandle클래스
TShardPtr<strunct FStreambleHandle>타입 변수 선언.

-ABCharacter.cpp 소스코드에서
캐릭터세팅 헤더파일 포함하고
생성자에 캐릭터세팅에서 가져온 에셋 경로 목록 호출,

비긴플레이 함수에서 플레이어가 컨트롤 중이지 않으면
세팅에서 랜덤한 캐릭터에셋 가져와 게임인스턴스가 널이 아닐시
메모리를 유지하는 핸들 변수 AssetStreamingHandle에 
게임 에셋을 로딩하는 StreambleManager를 이용하여
비동기방식으로 에셋을 로딩하는 AsyncLoad 함수를 명령하고
(해당 함수에 FStremableDelegate 형식의 델리게이트 넘겨줄 경우, 로딩 완료하면 해당 델리게이트 연결된 함수 호출)
(또는 CreateUObject 명령을 사용해 즉석에서 델리게이트 생성함으로써 함수와 연동시킨 후 넘겨주기도 가능)
AsyncLoad 요청하고  FStremableDelegate 형식 즉석에서 만듬. 연동할 함수는 OnAssetLoadCompleted로 함.

OnAssetLoadCompleted 함수 정의
메모리 유지한 핸들로 로드된 에셋 가져오고
핸들을 리셋하고 로드된 에셋이 널이 아니면 스켈레탈메시 로드된 에셋으로 지정.

[[UE4\] 스마트포인터 - TSharedPtr, TWeakPtr, TUniquePtr (tistory.com)](https://devjino.tistory.com/254)

[FStreamableHandle | Unreal Engine 5.1 Documentation](https://docs.unrealengine.com/5.1/en-US/API/Runtime/Engine/Engine/FStreamableHandle/)

http://egloos.zum.com/sweeper/v/3208656

### 무한 맵의 생성

액터 클래스를 부모로 갖는 C++ ABSection 클래스 생성
-헤더 파일에서
생성된 틱 함수 지움,
생성자 선언, 
OnConstruction 함수 선언, BeginPlay 함수 선언,
enum 클래스 ESectionState라 이름 짓고 uint8 타입으로 READY, BATTLE, COMPLETE 생성.
SetState 함수 선언, ESectionState 타입 CurrentState 선언 후 READY로 정의
OnTriggerBeginOverlap 함수 선언, OnGateTriggerBegineOverlap 함수 선언,
스태틱메시컴포넌트 배열 GateMeshes 선언, 박스컴포넌트 배열 GateTriggers 선언,
스태틱메시컴포넌트 Mesh 선언, 박스컴포넌트 Trigger 선언
부울 bNoBattle 변수 선언.

-소스코드에서
생성자에서 틱을 사용하지 않는다.
스태틱메시 Mesh에 에셋 지정하고 루트컴포넌트로 지정.
박스컴포넌트 Trigger의 스태틱메시 크기만큼 늘리고
콜리전 프리셋은 ABTrigger(캐릭터에만 반응함)
이 컴포넌트와 겹침 발생시 OnTriggerBeginOverlap 함수 호출하게 바인딩.
게이트에셋을 콘스트럭터헬퍼 오브젝트파인더로 찾아놓음.
스태틱메시 Mesh에 해당 소켓에
게이트 에셋을 지정하고 추가하고 이 메시들을  GateMeshes 배열에도 추가,
소켓마다 박스컴포넌트 또한 추가하고 콜리전 프리셋은 ABTrigger(캐릭터에만 반응함)
GateTriggers 배열에도 추가 이 컴포넌트와 겹침 발생시 
OnGateTriggerBegineOverlap 함수 호출하게 바인딩하고 
어떤 문(소켓)에 있는 컴포넌트인지 구분하도록 컴포넌트에 소켓 이름으로 태그를 설정.
bNoBattle=false로 지정.

에디터 작업에서 액터의 속성이나 트랜스폼 정보가 변경될 때 실행되는 OnConstruction 함수 정의
부모함수 호출 후
bNoBattle이 true면 COMPLETE 상태로 세팅하고 false면 READY 상태로 세팅한다.

BeginPlay 함수 정의
부모함수 호출하고
bNoBattle이 true면 COMPLETE 상태로 세팅하고 false면 READY 상태로 세팅한다.

SetState 함수 정의
세팅할 상태가
READY이면 
트리거의 콜리전 프리셋은 ABTrigger로 하고
게이트들의 콜리전 프리셋은 NoCollision으로 세팅하고
게이트의 문을 연다.
BATTLE이면 
트리거의 콜리전 프리셋은 NoCollision로 하고
게이트들의 콜리전 프리셋은 NoCollision으로 세팅하고
게이트의 문을 닫는다.
COMPLETE이면 
트리거의 콜리전 프리셋은 NoCollision로 하고
게이트들의 콜리전 프리셋은 ABTrigger으로 세팅하고
게이트의 문을 연다.
현재 상태를 세팅할 상태로 바꾼다.

OperateGates 함수 정의
bOpen이 true면 게이트 메시들을 90도 회전 시켜 문열고
false면 제로 회전 값을 넣어 문을 닫는다. 

OnTriggerBeginOverlap 함수 정의
현재 상태가 READY 상태면
BATTLE 상태로 바뀐다.

OnGateTriggerBeginOverlap 함수 정의
정확하지는 않으나
컴포넌트 태그로 소켓의 이름과 좌표를 추출하고
해당 좌표로 월드의 OverlapMultiByObjectType을 실시하여
충돌하는게 없다면 bResult가 false가 되어
bResult가 false면 섹션 엑터 생성.

### 내비게이션 메시 시스템 설정

-ABSection.h 헤더파일에서
NPC 액터를 생성하는 OnNPCSpawn 함수 선언, 
스폰시간을 담을 float 타입 EnemySpawnTime, ItemBoxSpawnTime 변수 선언
타이머에서 구분하기 위한 핸들 FTimerHandle 타입 SpawnNPCTimerHandle, SpawnItemBoxTimerHandle 선언

-ABSection.cpp 소스코드에서
생성자에서 EnemySpawnTime, ItemBoxSpawnTime 시간 지정.

SetState 함수에서 BATTLE 상태에
월드 타임 매니저에 바인딩할 스폰 함수을 지정하거나 생성하고 시간 지정 반복하지는 않는다.
아이템 생성은 람다식으로 바로 만듬. NPC는 OnNPCSpawn 함수로 지정. 

OnNPCSpawn 함수
월드에 AABCharacter 액터를 섹션 액터 위에 회전없이 생성.

프로젝트 세팅>엔진>내비게이션 메시>런타임>런타임 생성>드롭다운리스트 Dynamic으로 변경.



## Ch14. 게임플레이 제작

### 캐릭터의 스테이트 설정

-프로젝트명 헤더파일에서
캐릭터의 스테이트를 구분할 enum 클래스 ECharacterState : uint8 선언하고
PREINT, LOADING, READY, DEAD 지정.

-ABAIController.h 헤더파일에서
RunAI 함수 선언, StopAI 함수 선언.

-ABAIController.cpp 소스코드에서
스테이트에 맞게 비헤이비어 트리 로직을 수동으로 구동하고 중지할 수 있게 구조 변경
OnPossess 함수에서 블랙보드 관련 부분지움. 함수에 부모함수 호출만 남긴다.
RunAI 함수
기존 Possess 함수에 있던 블랙보드 이용해서 비헤비어트리 동작하는 부분을 여길로 옮겨 정의.
StopAI 함수
호출시 비헤이비어트리 컴포넌트를 멈추게함.

-ABCharacter.h 헤더파일에서
스테이트 머신 제작을 위한 SetCharacterState 함수선언, GetCharacterState 함수선언,
인트형 AssetIndex=0 변수 선언 및 정의
현재 캐릭터 상태를 나타내는 ECharacterState 타입 CurrentState 변수 선언 
bIsPlayer 부울 변수 선언
AI컨트롤러 타입 ABAIController 선언
플레이어컨트롤러타입 ABPlayerController 선언
실수형 DeadTimer 선언
타임핸들 DeadTimerHandle 선언

-ABCharacter.cpp 소스코드에서
생성자에서 AssetIndex는 4로
캐릭터 액터와 체력바 위젯을 숨기고 데미지는 받지 않게 설정하고
DeadTimer를 5로 지정.

PostInitializeComponets 함수
캐릭터스텟 OnHPIsZero 델리게이트에 람다식 바인딩함수를 뺀다.

PossessedBy 함수
플레이어가 컨트롤중이면 컨트롤모드와 캐릭터의 속도를 결정하는 로직을 뺀다. 

SetCharacterState 함수
우선 현재 상태를 세팅할 상태로 바꾸고

로딩상태라면
플레이어라면 입력을 불가능하게 만든다.
캐릭터와 HP바를 숨기고 데미지를 못받게 만든다.

레디상태라면
캐릭터와 HP바를 보이게하고
데미지를 받을 수 있게 한후
기존 PostInitializeComponets 함수에서 뺀 코드를 수정하여
OnHPIsZero(체력이 0이면 호출되는) 델리게이트에
데드 상태로 세팅하는 람다식을 바인딩한 후
위젯에 캐릭터스텟을 바인딩한다.
PossessedBy 함수에서 뺀 플레이어 여부에 따른 컨트롤모드와 속도 결정 로직을
추가한다.

데드 상태라면
콜리전을 이용못하게하고 메시는 그대로 보이게하고
HP바는 숨기고 죽는애니메이션을 진행시키고 데미지를 받을 수 없게한 후
플레이어라면 입력을 못하게하고 AI컨트롤러면 StopAI를 호출하게 한다.
또 월드에서 타임매니져를 가져와 DeadTimeHandle로 람다식을 동작하게 하는데
플레이어라면 레벨을 리스타트하고 아니라면 액터를 제거한다. 시간은 DeadTimer이후로 진행하고 반복하지 않는다.


GetCharacterState 함수
현재 상태를 반환해준다.

BeginPlay 함수
기존 구조를 수정한다
플레이어라면 플레이어 컨트롤러를 ABPlayerController로 현재 컨트롤러에서 형변환해서 지정하고 입력매핑을 진행하고
아니라면 ABAIController를 현재 컨트롤러에서 현변환해서 지정한다.
플레이어라면 에셋인덱스를 4번으로하고 아니면 인덱스를 랜덤으로 정한다.
지정한 인덱스를 토대로 캐릭터 에셋을 로드하고 캐릭터상태를 로딩으로 세팅한다.
위젯에 캐릭터스텟을 바인딩하는 코드를 빼준다.

OnAssetLoadCompleted 함수
에셋이 로드됬는지 널 체크하는 로그 추가, 기존 로드되는 코드 이후 캐릭터상태를 레디로 세팅하는 코드 추가.



### 플레이어 데이터와 UI 연동

플레이어의 정보를 관리하기 위한
부모를 PlayerState 클래스로 갖는 C++ ABPlayerState 생성 
-ABPlayerState.h 헤더파일에서
멀티캐스트 델리게이트 FOnPlayerStateChangedDelegate 선언
생성자 선언, GetGameScore 선언, GetCharacterLevel 함수 선언,
GetExpRatio 함수 선언, AddExp 함수 선언, InitPlayerData 함수 선언,
FOnPlayerStateChangedDelegate를 OnPlayerStateChanged 선언,
int32타입 게임 진행상황을 기록하도록 GameScore, CharacterLevel, Exp 변수 선언
SetCharacterLevel 함수 선언, (게임인스턴스에 선언된)구조체 FABCharacterData 타입 CurrentStatData 선언.

-ABPlayerState.cpp 소스코드에서
생성자에서 캐릭터레벨 1로 게임스코어와 경험치는 0으로 한다.
GetGameScore 함수 게임스코어를 반환.
GetCharacterLevel 함수 캐릭터레벨을 반환.
GetExpRatio 함수 현재 경험치와 현재캐릭터스텟이 가르치는 다음경험치량 비율을 반환.
AddExp 함수 
현재 경험치에 인자값 경험치를 더하고
다음경험치량을 넘을시 현재 경험치는 다음 경험치량 만큼 뺀 후
레벨을 하나올려 세팅하고 레벨업여부를 트루로하고 
OnPlayerStateChanged(캐릭터 상태변화)를 브로드캐스트 후
레벨업여부를 반환한다.
SetCharacterLevel 함수
현재스텟데이터를 게임인스턴스에서 가져온 해당 인자값 레벨에 데이터로 바꾸고
현재레벨을 인자값으로 바꾼다. 
InitPlayerData 함수(플레이어 데이터 초기화함수)
플레이어이름은 Destiny로 지정, 캐릭터레벨은 5로 지정,
게임스코어와 경험치는 0으로한다.


-ABGameMod.cpp 소스코드에서
생성자에서 PlayerStateClass를 AABPlayerStat::StaticClass()로 지정.
PostLogin 함수에서 기존 로그들 지우고
플레이어의 인자값이 들어오면 그 플레이어의 플레이어 데이터를 초기값을 세팅하는
InitPlayerData 호출.


예제코드 리소스에서 UI_HUD.uasset 콘텐츠에 넣고
부모로 UserWidget클래스를 삼는 C++ ABHUDWidget 클래스 생성 후 
UI_HUD 클래스 세팅에서 부모 클래스를 ABHUDWidget로 변경한다.


-ABHUDWidget.h 헤더파일에서
BindCharacterStat 함수 선언, BindPlayerState 함수 선언
NativeConstruct 함수 선언, UpdateCharacterStat 함수 선언, UpdatePlayerState 함수 선언,
TWeakObjectPtr UABCharacterStatComponent 타입 CurrentCharacterStat 변수 선언,
TWeakObjectPtr AABPlayerState 타입 CurrentPlayerState 변수 선언,
프로그레스바 타입 HPBar, ExpBar 선언,
텍스트블록 타입 PlayerName, PlayerLevel, CurrentScore, HighScore 선언.

-ABHUDWidget.cpp 소스코드에서
BindCharacterStat함수
현재 캐릭터 스텟을 인자값 캐릭터 스텟으로 바꾸고
그 캐릭터스텟의 OnHPChanged 델리게이트에 UPdateCharaterStat 함수 바인딩추가.
BindPlayerState 함수
현재캐릭터상태를 인자값 캐릭터 상태로 바꾸고
그 캐릭터 상태 OnPlayerStateChanged 델리게이트에 UpdatePlayerState 함수 바인딩추가.
NativeConstruct 함수
UI와 플레이어스테이트와 캐릭터스텟을 연동하기 위해
변수로 선언한 프로그레스바와 텍스트블록을 정의?지정?(정확한 의미를 모르겠음).
UpdateCharacterStat 함수
현재캐릭터스텟에서 가져온 체력 비율로 HPBar 퍼센트 세팅.
UpdatePlayerState 함수
현재플레이어상태에서 가져운 경험치 비율로 ExpBar 퍼센트 세팅하고
현재플레이어상태에서 가져운 이름, 레벨, 게임스코어로 각각의 텍스트블록 세팅한다.


-ABPlayerController.h 헤더파일에서
생성자 선언, GetHUDWidget 함수 선언,
NPCKill 함수선언,
UABHUDWidget 타입 HUDWidget 변수 선언,
서브클래스UABHUDWidget 타입 HUDWidgetClass 변수 선언,
AABPlayerState타입 ABPlayerState 변수 선언

-ABPlayerController.cpp 소스코드에서
생성자에서 콘스트럭터헬퍼를 통해 HUDWidgetClass의 에셋을 지정한다.
GetHUDWidget 함수 HUD 위젯을 반환.
NPCKill 함수 죽인 NPC에 캐릭터 클래스에서 경험치를 받고 현재 플레이어에게 경험치를 추가한다. 
BeginPlay 함수에서
HUD 위젯을 생성하고 뷰포트에 추가하고 ABPlayerState를 지정한 후
HUD 위젯에 ABPlayerState를 바인딩한 후 ABPlayerState의 OnPlayerStateChanged 브로드캐스트함.
(HUD위젯에 PlayerState를 동기화하기 위해 데이터를 바인딩한 후 업데이트 한 것임)


-ABCharacterStatComponent.h 헤더파일에서
GetDropExp 함수 선언.

-ABCharacterStatComponent.cpp 소스코드에서
GetDropExp 함수 현재 캐릭터스텟데이터에서 DropExp를 반환.


-ABCharacter.h 헤더파일에서
GetExp 함수 선언.

-ABCharacter.cpp 소스코드에서
플레이어의 레벨 정보를 반영할 SetCharacterState 함수에
로딩 상태 부분에서 현재 플레이어의 플레이어상태에 접근해 레벨을 얻어오고
그 레벨로 스탯컴포넌트의 레벨을 세팅하는 코드 추가.
GetExp 함수
캐릭터스테에서 GetDropExp 함수 호출 후 반환.
TakeDamage 함수 수정
기존 로그 지우고
현재 상태가 데드이고 EventInstigator(가해자)가 플레이어컨트롤러가 맞다면
플레이어컨트롤러의 NPCKill(NPC 캐릭터 자기자신) 호출-해당 가해자에게 경험치추가하는 함수호출.

### 게임 데이터의 관리

-ABGameState.h
생성자 선언,
GetTotalGameScore 함수 선언,
AddGameScore 함수 선언,
int32 타입 TotalGameScore 변수 선언.
-ABGameState.cpp
생성자에 TotalGameScroe를 0으로 지정.
GetTotalGameScore 함수에서 TotalGameScroe 반환.
AddGameScore 함수 호출 시 TotalGameScroe++해줌.


-ABPlayerController.h
AddGameScore 함수 선언.
-ABPlayerController.cpp
AddGameScore 함수 호출 시 플레이어스테이트에서 AddGameScore호출.


-ABPlayerState.h
AddGameScore 함수 선언.
-ABPlayerState.cpp
AddGameScore 함수 
GameScore++ 한 후 OnPlayerStateChanged를 브로드캐스트함.


-ABGameMode.h
PostInitializeComponents() 함수 선언,
AddScore 함수 선언,
AABGameState 타입 ABGameState 변수 선언.

-ABGameMode.cpp
생성자에 GamStateClass 지정 추가.
PostInitializeComponents() 함수
선언한 ABGameState 지정.
AddScore 함수
월드를 통해 현재 게임에 참여 중인 플레이어 컨트롤러의 목록을 제공하는
GetPlayerControllerIterator를 이용해 for 문을 돌려
플레이어 컨트롤러를 임시로 받아와 캐스팅한 후
이 받아온 값이 널이 아니고 인자값과 같다면
그 컨트롤러에 AddGameScore 함수를 호출하고
게임상태에 AddGameScore를 호출한다.


-ABSection.h
OnKeyNPCDestroyed 함수 선언.
-ABSection.cpp
OnNPCSpawn 함수에서
월드 타임매니저에서 SpawnNPCTimerHandle이 다루는 타이머를 지운다.
NPC 캐릭터를 스폰하고 
NPC가 파괴딜시 OnDestroyed 델리게이트에 OnKeyNPCDestroyed 함수를 바인딩한다.

OnKeyNPCDestroyed 함수에서
파괴된 액터를 캐릭터 클래스로 캐스팅하고
캐릭터를 마지막 때린 대상에 플레이어컨트롤러도 받아오고
현재 캐스팅된 게임모드를 가져와서
게임모드 AddScore(마지막에 때린 플레이어컨트롤러)를 호출한다.
(NPC가 파괴되면 NPC를 죽인 플레이어컨트롤러에 게임스코어가 증가한다) 

## Ch15. 게임의 완성

### 게임 데이터의 저장과 로딩

게임 세이브 기능에는 각 저장 파일에 접근할 수 있는 고유 이름인 슬롯 이름이 필요함.

Player1이라는 슬롯 이름을 사용해 하나의 세이브 파일만 관리한다.

처음에는 세이브된 게임 데이터가 없으므로 기본 세이브 데이터를 생성하는 로직을 플레이어 스테이트의 InitPlayerData에 구현함.

-부모가 SaveGame 클래스인 C++ ABSaveGame 클래스 생성 

-ABSaveGame.h 헤더파일에서
생성자 선언, int32 타입 Level, Exp, HighScore 변수 선언,
FString 타입 PlayerName 선언.
-ABSaveGame.cpp 소스코드에
생성자에서 Level은 값 1로, Exp는 0으로, PlayerName은 Guest, HighScore는 0으로 지정.

-ABPlayerState.h 헤더파일에서
GetGameHighScore 함수 선언 추가, FString 타입 SaveSlotName 변수 선언 추가,
SavePlayerData() 함수 선언 추가, int32 타입 GameHighScore 변수 선언 추가.
-ABPlayerState.cpp 소스코드에서
생성자에서 GameHighScore는 0으로, SaveSlotName은 Player1으로 지정하는 코드 추가.
GetGameHighScore 함수 GameHighScore를 반환하게 정의함.
AddExp 함수에서 브로드캐스트 후 SavePlayerData 함수 호출하는 코드 추가.

AddGameScore 함수에서 게임스코어를 증가 후 최고점수보다 현재게임스코어가 높다면
최고 스코어를 현재게임스코어로 변경하는 로직 추가 후 브로드 캐스트 후 
SavePlayerData 함수 호출하는 코드 추가.

기본 세이브 데이터를 생성하는 InitPlayerData 함수에서
Player1 슬롯을 로드하고 널포인터이면 UABSaveGame 클래스의 변경 가능한 기본 객체를 가져와 지정하고
플레이어스테이트의 이름과 레벨을 로드하거나 생성한 SaveGame의 이름과 레벨로 지정한 후
게임스코어는 0으로 지정하고 최고 점수와 경험치도 SaveGame의 최고 점수와 경험치로 지정한다. 

플레이어 관련된 데이터가 변경될 때마다 이를 저장하기 위한 SavePlayerData 함수에서
임시 세이브게임 클래스를 선언하고 객체 생성 후 스테이트의 이름, 레벨, 경험치, 최고점수로 객체의 멤버변수를 지정하고
SaveSlotName이 가리키는 슬롯에 저장한다. 

-ABHUDWidget.cpp 소스코드에서
UPdatePlayerState 함수에서 플레이어 스테이트의 하이스코어 값을 HUD UI에 연동시키는 코드 추가.

### 전투 시스템의 설계

-ABWeapon.h 헤더파일에서
GetAttackRange 함수 선언, GetAttackDamage 함수 선언, GetAttackModifier 함수 선언,
무기 속성을 추가하기 위한 float 타입 AttackRange, AttackDamageMin, AttackDamageMax,
AttackModifierMin, AttackModifierMax, AttackDamge, AttackModifier 변수 선언. 
-ABWeapon.cpp 소스코드에서
생성자에서 무기 속성에 대한 공격범위 150.0f, 
무기에 랜덤한 순수 공격력과 효과치 속성 설정하기 위한 
공격데미지최소 -2.5f, 최대 10.0f, 공격모디파이어(수식)최소 0.85f, 최대 1.25f로 지정.
GetAttackRange 함수는 AttackRange 반환하게 정의.
GetAttackDamage 함수는 AttackDamage 반환하게 정의.
GetAttackModifier 함수는 AttackModifier 반환하게 정의.
BeginPlay 함수에 Min과 Max안에 랜덤한 숫자 뽑아
AttackDamage와 Modifier 지정하는 로직 추가. 

-BTDecorator_IsInAttackRange.cpp 소스코드에서
CalculateRawConditionValue 함수 수정
ControllingPawn에 지정된 클래스를 AABCharacterz클래스로 캐스트한 후 지정되게하고
bResult가 200보다 작거나 같은 값이 아닌 ControllingPawn의 GetFinalAttackRange 함수 호출 
반환값보다 작거나 같은 로직으로 변경.

-ABGameMode.h 헤더파일에서
GetScore 함수 선언.
-ABGameMode.cpp 소스코드에서
GetScore 함수는 게임스테이트에서 GetTotalGameScore 함수를 호출해서 반환 값을 반환하게 함.

-ABCharacter.h 헤더파일에서
GetFinalAttackRange 함수 선언, GetFinalAttackDamage 함수 선언.
-ABCharacter.cpp 소스코드에서
생성자 AttackRange 값 80 지정-무기가 없는 기본 캐릭터 공격 범위 줄임.
SetCharacterState 함수에서 캐릭터 상태가 로딩이고 플레이어가 아니라면
현재 게임스코어(지나온 스테이지)*0.8f의 해당하는 인트값으로 NPC 레벨을 세팅.-깨면 깰수록 적 레벨 상승.
GetFinalAttackDamage 함수 현재 무기포인터가 널이면 현재사정거리를 아니면 무기사정거리를 반환.
GetFinalAttackModifier 함수 현재 무기포인터가 널이 아니면 캐릭터공격력과 무기공격력을 더하고 
무기의 공격모디파이어를 가져오고 아니라면 캐릭터의 공격력과 기본모디파이어 값을 1.0f로 세팅 한 후
공격데미지에 모디파이어를 곱한 값을 반환.
CanSetWeapon 함수 수정-항상 무기들이 속성이 랜덤이기에 무기 세팅 가능은 true로 반환하도록 수정. 
SetWeapon 함수 수정-현재 무기가 널이 아니라면 현재 무기를 소멸시키고 널을 가리키게 함.
AttackCheck 함수 수정-지역 변수 float 타입 FinalAttackRange 변수 선언하고 GetFinalAttackRange 호출 후 반환값으로 지정
함수안에서 기존 AttackRange 변수가 들어가는 자리를 FinalAttackRange로 변경.

게임 실행 중에 게임 모드의 포인터 가져올 때는 월드의 GetAuthGameMode 함수를 사용.
멀티 플레이 게임에서 게임 모드는 게임을 관리하는 방장 역할을 하며 게임에서 중요한 데이터를 인증하는 권한 가짐.

### 타이틀 화면의 제작

예제코드 Resource>Chapter15>Book>UI>UI_Title.usasset 파일 추가
새 레벨>빈 레벨 생성 후 Title이라는 이름으로 저장.
Title 레벨에서만 사용할 UI를 띄울 PlayerController를 부모로 하는
C++ ABUIPlayerController 클래스 생성.
-ABUIPlayerController.h 헤더파일에서
BeginPlay함수 선언, TSubClassOf<UUserWidget> 타입 UIWidgetClass 선언, UUserWidget 타입 UIWidgetInstance 선언.
-ABUIPlayerController.cpp 소스코드에서
BeginPlay함수 정의
부모 BeginPlay함수 호출, 멤버 변수의 UI 인스턴스를 생성하고, 이를 뷰포트에 띄우고(AddToViewport),
입력은 UI에만 전달하도록 로직을 구현.-이 클래스를 블루프린트로 상속받아 UI만 지정해주면 된다.

ABUIPlayerController 클래스를 부모로 갖는 블루프린트 클래스 BP_TitleUIPlayerController 생성
디테일>UI>UIWidgetClass를 UI_Title로 지정.
플레이어 컨트롤러 띄울 게임모드를 Game Mode Base를 부모로 갖는 블루프린트 BP_TitleGameMode 생성
디테일>클래스>Player Controller Class를 BP_TitleUIPlayerController로 지정
디폴트 폰 클래스는 아무 기능이 없는 Pawn 으로 지정.
Title 레벨의 월드 세팅>Game Mode>게임모드 오버라이드를 BP_TitleGameMode로 지정.

예제코드 Resource>Chapter15>Book>UI>UI_Select.usasset 파일 추가
예제코드 Resource>Chapter15>Book>Maps>Select.umap 파일 추가
ABUIPlayerController 클래스를 부모로 갖는 블루프린트 클래스 BP_SelectUIPlayerController 생성
디테일>UI>UIWidgetClass를 UI_Select로 지정.
플레이어 컨트롤러 띄울 게임모드를 Game Mode Base를 부모로 갖는 블루프린트 BP_SelectGameMode 생성
디테일>클래스>Player Controller Class를 BP_SelectUIPlayerController로 지정
디폴트 폰 클래스는 아무 기능이 없는 Pawn 으로 지정.
Select 레벨의 월드 세팅>Game Mode>게임모드 오버라이드를 BP_SelectGameMode로 지정.

버튼을 누를 때마다 스켈레탈 메시를 변경하는 기능을 구현하기 위한 UserWidget 클래스를 부모로 갖는
ABCharacterSelectWidget C++ 클래스 생성
-ABCharacterSelectWidget.h 헤더파일에서
NextCharacter 함수 선언, NativeConstruct 함수 선언,
int32 타입 CurrentIndex, MaxIndex 변수 선언, TWeakObjectPtr<USkeletalMeshComponent> 타입 TargetComponent 선언,
UButton 타입 PrevButton, NextButton, ConfirmButtom, UEditableTextBox 타입 TextBox 선언,
OnPrevClicked 함수, OnNextClicked 함수, OnConfirmClicked 함수 선언. 
-ABCharacterSelectWidget.cpp 소스코드에서
NextCharacter 함수 정의
인자값 bForward 함수 트루면 CurrentIndex 1 증가, false면 1 감소하고
캐릭터세팅과 게임인스턴스를 이용하여 현재 인덱스가 가리키는 스켈레탈 메시 에셋을 가져와
타겟컴포넌트를 가져온 에셋으로 지정. 

NativeConstruct 함수 정의
부모함수 호출 후 현재 인덱스 0으로 지정
캐릭터세팅 생성 후 최대인덱스 값을 캐릭테에셋들의 숫자로 지정
월드에 있는 스켈레탈메시액터를 찾아 그 액터의 스켈레탈메시 컴포넌트를 타겟컴포넌트로 지정
버튼과 텍스트박스들을 위젯에 해당 값들로 지정
버튼들에 해당하는 함수들 바인딩해준다.

OnPrevClicked 함수 정의-NextCharacter함수를 인자값 false 넣어 호출.
OnNextClicked 함수 정의-NextCharacter함수를 인자값 true 넣어 호출.
OnConfirmClicked 함수 정의
캐릭터 이름을 텍스트 박스에 적힌 문자열로 지정,
새로운 세이브게임 만들고 플레이어데이터로 짓고
해당 멤버 변수들 초기값 지정해주고 플레이어스테이트를 기본값으로 얻고
게임을 저장하고 게임플레이 레벨을 연다.

UI_Select 애셋의 부모클래스를 ABCharacterSelectWidget으로 변경

-ABSaveGame.h 헤더파일에서 
int32 타입 CharacterIndex 변수 선언.
-ABSaveGame.cpp
생성자에서 CharacterIndex를 0으로 지정 코드 추가.

-ABCharacterSelectWidget.cpp 소스코드에서
생성자에서 CharacterIndex를 0으로 지정 코드 추가.

-ABPlayerState.h
GetCharacterIndex 함수 선언, int32 타입의 CharacterIndex 변수 선언.
-ABPlayerState.cpp
생성자에서 CharacterIndex를 0으로 지정하는 코드 추가.
GetCharacterIndex 함수 CharacterIndex 반환하게 정의.
InitPlayerData 함수 캐릭터인덱스도 세이브게임에서 얻는 로직 추가.
SavePlayerData 함수 플레이어데이터에 캐릭터 인덱스를 플레이어스테이트의 캐릭터인덱스로 하는 로직 추가.

-ABCharacter.cpp 소스코드에서
BeginPlay함수에서 플레이어면 에셋인덱스를 4로 했던 것을 플레이어스테이트에서 캐릭터 인덱스로 하는 로직으로 변경.

프로젝트 세팅>프로젝트>맵&모드>Default Maps>에디터 시작 맵과 게임 기본 맵을 Title로 변경.



UEditalbeTextBox 오타 UEditableTextBox인데 albe라고 able인데 오타 조심.



버튼을 눌러도 캐릭터가 변하지 않는 문제 발생

```
bForward ? CurrentIndex : CurrentIndex++;
```

NextCharacter 함수에서 현재 인덱스를 증가 시키는 부분이 잘못되었음.

```
bForward ? CurrentIndex++ : CurrentIndex--;
```



### 게임의 중지와 결과 화면

예제코드 Resource>Chapter15>Book>UI>UI_Result.usasset, UI_Menu.usasset 파일 추가
입력액션 IA_GamePasuse_AB 생성, 플레이어컨트롤러 전용 입력매핑컨텍스트 IMC_PlayerController_AB 생성.

-ABCharacter.cpp
BeginPlay 함수 플레이어이면 플레이어컨트롤러 서브시스템에 입력매핑컨텍스트를 추가하는 로직에서
추가 전에 ClearAllMappings 과정을 없애고 RemoveMppaingContext로 DefaultMappingContext와 KeboardMappingContext
제거하는 과정으로 바꾼다.-플레이어컨트롤러에서 할당한 입력매핑 사라지는 걸 방지하기 위해서다.

-ABPlayerController.h
UInputAction 타입 GamePauseAction 선언, UInputMappingContext 타입 PlayerControllerMappingContext 선언,
SetupInputComponent 함수 선언, OnGamePause 함수 선언.
-ABPlayerController.cpp
생성자에서 GamePauseAction과 PlayerControllerMappingContext에 대한 애셋 지정.
SetupInputComponent함수 정의
부모 함수 호출하고 인풋컴포넌트를 향상된입력으로 캐스팅하고 입력 액션에 OnGamePause 함수 바인딩.
BeginPlay 함수에서 서브시스템에 모든매핑지우고 PlayerControllerMappingContext 추가하는 로직 구현.

UserWidget 클래스를 부모로 갖는 ABGameplayWidget C++ 클래스 생성.
UI_Menu 애셋의 부모 클래스를 ABGameplayWidget으로 변경.

-ABGameplayWidget.h 헤더파일에서
NativeConstruct 함수 선언, OnResumeClicked 함수 선언, OnReturnToTitleClicked 함수 선언,
OnRetryGameClicked 함수 선언, UButton 타입 ResumeButton, ReturnToTitleButton, RetryGameButton 선언.
-ABGameplayWidget.cpp 소스코드에서
NativeConstruct 함수 정의
ResumeButton, ReturnToTitleButton, RetryGameButton의 위젯에 해당하는 버튼으로 지정하고
해당 버튼에 해당하는 OnResumeClicked 함수, OnReturnToTitleClicked 함수, OnRetryGameClicked 함수들을
바인딩한다.
OnResumeClicked 함수 정의 현재소유중인 플레이어의 플레이어컨트롤러를 통해 RemoveFromParent() 함수를 통해
상위위젯에 지금 위젯을 제거하고 입력모드를 변경하고 Pause를 풀어 게임을 재개한다.
OnReturnToTitleClicked 함수 정의 호출 시 Title 레벨 오픈.
OnRetryGameClicked 함수 정의 호출 시 현재소유중인 플레이어의 플레이어컨트롤러를 통해 레벨을 재시작한다.

ABGameplayWidget 클래스를 부모로 갖는 ABGameplayResultWidget C++ 클래스 생성.

-ABGameplayResultWidget.h
BindGameState 함수 선언, NativeConstruct 함수 선언, TWeakObjectPtr<class AABGameState> 타입 CurrentGameState 선언.
-ABGameplayResultWidget.cpp
BindGameState 함수 정의 현재게임상태를 인자값으로 받은 GameState로 지정.
NativeConstruct 함수 정의
부모 함수 호출 후 
위젯의 txtResult 텍스트 박스에 게임이 현재 게임상태를 통해 게임이 클리어 여부를 확인해 미션성공과 미션실패 텍스트를 지정,
위젯의 txtTotalScore 텍스트박스에 현재 게임상태를 통해 총게임점수를 받고 텍스트로 지정.

-ABGameState.h
SetGameCleared 함수 선언, IsGameCleared 함수 선언,
Int32타입 TotalGameScore 변수 선언, bool타입 bGameCleared 변수 선언. 
-ABGameState.cpp
생성자에서 bGameCleared 값 false로 지정.
SetGameCleared 함수 정의 bGameCleared 값 true로 지정.
IsGameCleared 함수 정의 bGameCleared 값 반환.

-ABGameMode.h
Int32타입 ScoreToClear 변수 선언.
-ABGameMode.cpp
생성자에서 ScoreToClear 값 2로 지정.-스코어가 2가 되면 클리어.
AddScore 함수에서 
GetScore 함수 호출한 값이 ScoreToClear 값보다 크거나 같으면
게임상태에서 SetGameCleared 함수를 호출하고 월드에 폰들을 가져와 TurnOff 함수 호출.
월드에서 플레이어함수를 가져와 ShowResultUI 함수 호출하는 로직 추가.

-ABCharacter.cpp
SetCharacterState 함수에서 DEAD 상태라면 DeadTimerHandle을 통해 타이머에 람다식 바인딩하는 부분 람다식에서
DeadTimerHandle 핸들에 타이머를 지우는 로직으로 추가하고
플레이어라면 RestartLevel()부분을 지우고 플레이어컨트롤러의 ShowResultUI() 함수를 호출하게 변경.-죽으면 레벨을 재시작하지 않고 UI를 띄움.

-ABPlayerController.h
ChangeInputMode 함수 선언, ShowResultUI 함수 선언, TSubclassOf<class UABGameplayWidget>타입 MenuWidgetClass 선언,
TSubclassOf<class UABGameplayResultWidget> 타입 ResultWidgetClass 선언, UABGameplayWidget 타입 MenuWidget 선언,
UABGameplayResultWidget 타입 ResultWidget 선언, FInputModeGameOnly 타입 GameInputMode 선언, FInputModeUIOnly 타입 UIInputMode 선언.
-ABPlayerController.cpp
생성자에서 MenuWidgetClass와 ResultWidgetClass 애셋 지정.
ChangeInputMode 함수 정의 
인자값 bGameMode가 true면 SetInputMode함수를 호출하고 GameInputMode 전달하고 마우스커서를 false로 함,
bGameMode가 false면 SetInputMode함수를 호출하고 UIInputMode 전달하고 마우스커서를 true로 함.
ShowResultUI 함수 정의 플레이어컨트롤러가 가진 게임상태를 ResultWidget에 바인드하고 뷰포트에 추가하고 ChangeInputMode를 false로 호출.
OnGamePause 함수 정의 MenuWidget을 MenuWidgetClass통해 생성하고 지정하고 뷰포트에 추가 게임을 멈추고 ChangeInputMode를 false로 호출.
BeginPlay 함수에서
ChangeInputMode를 true로 호출하는 로직 추가 후
ResultWidget을 ResultWidgetClass통해 생성하고 지정하고 Widget들에 대한 로그 추가.



입력 매핑 컨테스트를 추가하였는 데

```c++
ConstructorHelpers::FObjectFinder<UInputMappingContext>
```

입력매핑컨텍스트를 반환하지 못하는 문제 발생

```
ConstructorHelpers.h(110): [C2664] 'void ConstructorHelpers::ValidateObject(UObject *,const FString &,const TCHAR *)': 인수 1을(를) 'T *'에서 'UObject *'(으)로 변환할 수 없습니다.
```

[[Unreal Engine 4\] Error - 'void ConstructorHelpers::ValidateObject(...) :인수 1을(를) 'T *'에서 'UObject *'(으)로 변환할 수 없습니다.' (tistory.com)](https://sheep-adult.tistory.com/41)

```
#include "InputMappingContext.h"
```

추가해서 문제 해결.

