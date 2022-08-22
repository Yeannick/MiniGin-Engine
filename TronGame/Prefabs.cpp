#include "Prefabs.h"
#include "GameCommands.h"
#include "Scene.h"
#include "Bullet.h"
#include "EnemyController.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "PhysicsManager.h"
#include "TextComponent.h"
#include "GameManager.h"

std::shared_ptr<GameObject> PlayerPrefab(Scene& scene)
{
	const auto GO = std::make_shared<GameObject>("Player");

	GO->AddComponent<BoxCollider2D>(std::make_shared<BoxCollider2D>(GO, 25));
	PhysicsManager::GetInstance().AddBoxCollider2D(GO->GetComponent<BoxCollider2D>().lock());
	GO->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(GO));
	auto sprite = GO->GetComponent<SpriteComponent>();
	//sprite.lock()->SetColumns(1);
	//sprite.lock()->SetRows(1);
	sprite.lock()->SetTexture("TronSpriteSheet.png");
	sprite.lock()->SetSpriteRect(32*11,0,32,32);
	//sprite.lock()->SetRotationPivot(float2{ 0.5f,.5f });
	//sprite.lock()->SetFrameRect(32*9, 0, 32, 32);
	GO->AddComponent<TankComponent>(std::make_shared<TankComponent>(GO, 100, SDL_Rect{ 16,16,448,416 }));
	GO->AddComponent<MovementComponent>(std::make_shared<MovementComponent>(GO));
	GO->AddComponent<RigidBody2D>(std::make_shared<RigidBody2D>(GO, glm::vec3{20,20,20}));
	GO->AddComponent<PlayerController>(std::make_shared<PlayerController>(GO));

	const unsigned int ID = InputManager::GetInstance().AddPlayer();
	const auto kbID{ InputManager::GetInstance().AddPlayer(true) };

	InputManager::GetInstance().AddCommand(Controller::ControllerButton::ButtonA, std::make_shared<AttackCommand>(GO.get()), ID,InputState::Down);
	InputManager::GetInstance().AddCommand(Controller::ControllerButton::LeftShoulder, std::make_shared<RotateCommand>(GO.get(),true), ID,InputState::Pressed);
	InputManager::GetInstance().AddCommand(Controller::ControllerButton::RightShoulder, std::make_shared<RotateCommand>(GO.get(),false), ID,InputState::Pressed);
	InputManager::GetInstance().AddCommand(Controller::ControllerButton::DPADLeft, std::make_shared<MovementCommand>(GO.get(), glm::vec3{-1,0,0}), ID, InputState::Pressed);
	InputManager::GetInstance().AddCommand(Controller::ControllerButton::DPADRight, std::make_shared<MovementCommand>(GO.get(), glm::vec3{1,0,0}), ID, InputState::Pressed);
	InputManager::GetInstance().AddCommand(Controller::ControllerButton::DPADUp, std::make_shared<MovementCommand>(GO.get(), glm::vec3{ 0,-1,0 }), ID, InputState::Pressed);
	InputManager::GetInstance().AddCommand(Controller::ControllerButton::DPADDown, std::make_shared<MovementCommand>(GO.get(), glm::vec3{0,1,0}), ID, InputState::Pressed);

	InputManager::GetInstance().AddCommand(SDL_SCANCODE_SPACE, std::make_shared<AttackCommand>(GO.get()), InputState::Down);
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_Q, std::make_shared<RotateCommand>(GO.get(), true), InputState::Pressed);
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_E, std::make_shared<RotateCommand>(GO.get(), false), InputState::Pressed);
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_A, std::make_shared<MovementCommand>(GO.get(), glm::vec3{ -1,0,0 }), InputState::Pressed);
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_D, std::make_shared<MovementCommand>(GO.get(), glm::vec3{ 1,0,0 }),  InputState::Pressed);
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_W, std::make_shared<MovementCommand>(GO.get(), glm::vec3{ 0,-1,0 }), InputState::Pressed);
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_S, std::make_shared<MovementCommand>(GO.get(), glm::vec3{ 0,1,0 }), InputState::Pressed);
	

	//GO->SetPosition(19, 19);
	GO->SetScale(0.9f, 0.9f);


	const auto pHealth{ std::make_shared<GameObject>("Health")};

	pHealth->AddComponent<HealthComponent>(std::make_shared<HealthComponent>(pHealth, 1));

	pHealth->GetComponent<HealthComponent>().lock()->AddObserver(GO->GetComponent<PlayerController>().lock().get());
	GO->GetComponent<TankComponent>().lock()->AddObserver(pHealth->GetComponent<HealthComponent>().lock().get());

	scene.AddDefault(pHealth);

	if (scene.GetGameObjectsByTag("Player").empty())
	{
		const auto pScore{ std::make_shared<GameObject>("Score")};
		pScore->SetPosition(500, 80);
		pScore->AddComponent<TextComponent>(std::make_shared<TextComponent>(pScore));
		pScore->AddComponent<ScoreComponent>(std::make_shared<ScoreComponent>(pScore));
		GO->GetComponent<PlayerController>().lock().get()->AddObserver(pScore->GetComponent<ScoreComponent>().lock().get());
		scene.AddDefault(pScore);
	}
	else
	{
		auto go = scene.GetGameObjectsByTag("Player");
		
	
		GO->GetComponent<PlayerController>().lock().get()->AddObserver(go.front()->GetComponent<ScoreComponent>().lock().get());
	}

	//GameManager
	const auto gamemanager = scene.GetGameObject("GameManager");
	
	GO->GetComponent<PlayerController>().lock().get()->AddObserver(gamemanager->GetComponent<GameManager>().lock().get());

	const auto pTurret = std::make_shared<GameObject>("TankTop");
	pTurret->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(pTurret));
	auto turretSprite = pTurret->GetComponent<SpriteComponent>();
	turretSprite.lock()->SetTexture("TronSpriteSheet.png");
	turretSprite.lock()->SetSpriteRect(32 * 6, 32, 32, 32);
	
	pTurret->SetPosition(5.f, -11.f,0.f);
	turretSprite.lock()->SetRotationPivot(float2{ 0.296875f,0.765625f });
//	turretSprite.lock()->SetPivot(float2{ 0.25f, 0.75f });

	scene.Add(pTurret);
	GO->AddChild(pTurret.get());
	return GO;

}

std::shared_ptr<GameObject> BlueTankEnemyPrefab(Scene& scene)
{
	const auto pGO{ std::make_shared<GameObject>("Enemy") };

	pGO->AddComponent<BoxCollider2D>(std::make_shared<BoxCollider2D>(pGO,25));
	PhysicsManager::GetInstance().AddBoxCollider2D(pGO->GetComponent<BoxCollider2D>().lock());
	pGO->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(pGO));
	auto sprite = pGO->GetComponent<SpriteComponent>();
	//sprite.lock()->SetColumns(1);
	//sprite.lock()->SetRows(1);
	sprite.lock()->SetTexture("TronSpriteSheet.png");
	sprite.lock()->SetSpriteRect(32 * 9, 0, 32, 32);

	
	pGO->AddComponent<TankComponent>(std::make_shared<TankComponent>(pGO, 100, SDL_Rect{ 16,16,448,416 }));
	pGO->AddComponent<MovementComponent>(std::make_shared<MovementComponent>(pGO));
	pGO->AddComponent<RigidBody2D>(std::make_shared<RigidBody2D>(pGO, glm::vec3{ 15,15,15 }));
	
	
	 pGO->AddComponent<EnemyController>(std::make_shared<EnemyController>(pGO)) ;

	const auto pHealth{ std::make_shared<GameObject>() };
	
	pHealth->AddComponent<HealthComponent>(std::make_shared<HealthComponent>(pHealth, 3));

	pHealth->GetComponent<HealthComponent>().lock()->AddObserver(pGO->GetComponent<EnemyController>().lock().get());
	pGO->GetComponent<TankComponent>().lock()->AddObserver(pHealth->GetComponent<HealthComponent>().lock().get());

	scene.Add(pHealth);

	const auto controllers = scene.GetGameObjectsByTag("Player");
	for (size_t i = 0; i < controllers.size(); i++)
	{
		pGO->GetComponent<EnemyController>().lock().get()->AddTarget(controllers[i].get());
	}
	const auto gamemanager = scene.GetGameObject("GameManager");
	pGO->GetComponent<EnemyController>().lock().get()->AddObserver(gamemanager->GetComponent<GameManager>().lock().get());

	//Turret

	const auto pTurret = std::make_shared<GameObject>("TankTop");
	pTurret->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(pTurret));
	auto turretSprite = pTurret->GetComponent<SpriteComponent>();
	turretSprite.lock()->SetTexture("TronSpriteSheet.png");
	turretSprite.lock()->SetSpriteRect(32 * 6, 32, 32, 32);

	pTurret->SetPosition(5.f, -11.f, 0.f);
	turretSprite.lock()->SetRotationPivot(float2{ 0.296875f,0.765625f });
	//	turretSprite.lock()->SetPivot(float2{ 0.25f, 0.75f });

	scene.Add(pTurret);
	pGO->AddChild(pTurret.get());
	pGO->SetScale(0.9f, 0.9f);
	return pGO;
}

std::shared_ptr<GameObject> BlueTankPlayerPrefab(Scene& scene)
{
	const auto GO = std::make_shared<GameObject>("Enemy");

	GO->AddComponent<BoxCollider2D>(std::make_shared<BoxCollider2D>(GO, 25));
	PhysicsManager::GetInstance().AddBoxCollider2D(GO->GetComponent<BoxCollider2D>().lock());
	GO->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(GO));
	auto sprite = GO->GetComponent<SpriteComponent>();
	//sprite.lock()->SetColumns(1);
	//sprite.lock()->SetRows(1);
	sprite.lock()->SetTexture("TronSpriteSheet.png");
	sprite.lock()->SetSpriteRect(32 * 9, 0, 32, 32);
	//sprite.lock()->SetRotationPivot(float2{ 0.5f,.5f });
	//sprite.lock()->SetFrameRect(32*9, 0, 32, 32);
	GO->AddComponent<TankComponent>(std::make_shared<TankComponent>(GO, 100, SDL_Rect{ 16,16,448,416 }));
	GO->AddComponent<MovementComponent>(std::make_shared<MovementComponent>(GO));
	GO->AddComponent<RigidBody2D>(std::make_shared<RigidBody2D>(GO, glm::vec3{ 20,20,20 }));
	GO->AddComponent<PlayerController>(std::make_shared<PlayerController>(GO));

	const unsigned int ID = InputManager::GetInstance().AddPlayer();
	InputManager::GetInstance().AddPlayer(true);

	InputManager::GetInstance().AddCommand(Controller::ControllerButton::ButtonA, std::make_shared<AttackCommand>(GO.get()), ID, InputState::Down);
	InputManager::GetInstance().AddCommand(Controller::ControllerButton::LeftShoulder, std::make_shared<RotateCommand>(GO.get(), true), ID, InputState::Pressed);
	InputManager::GetInstance().AddCommand(Controller::ControllerButton::RightShoulder, std::make_shared<RotateCommand>(GO.get(), false), ID, InputState::Pressed);
	InputManager::GetInstance().AddCommand(Controller::ControllerButton::DPADLeft, std::make_shared<MovementCommand>(GO.get(), glm::vec3{ -1,0,0 }), ID, InputState::Pressed);
	InputManager::GetInstance().AddCommand(Controller::ControllerButton::DPADRight, std::make_shared<MovementCommand>(GO.get(), glm::vec3{ 1,0,0 }), ID, InputState::Pressed);
	InputManager::GetInstance().AddCommand(Controller::ControllerButton::DPADUp, std::make_shared<MovementCommand>(GO.get(), glm::vec3{ 0,-1,0 }), ID, InputState::Pressed);
	InputManager::GetInstance().AddCommand(Controller::ControllerButton::DPADDown, std::make_shared<MovementCommand>(GO.get(), glm::vec3{ 0,1,0 }), ID, InputState::Pressed);

	InputManager::GetInstance().AddCommand(SDL_SCANCODE_RCTRL, std::make_shared<AttackCommand>(GO.get()), InputState::Down);
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_SLASH, std::make_shared<RotateCommand>(GO.get(), true), InputState::Pressed);
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_RSHIFT, std::make_shared<RotateCommand>(GO.get(), false), InputState::Pressed);
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_LEFT, std::make_shared<MovementCommand>(GO.get(), glm::vec3{ -1,0,0 }), InputState::Pressed);
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_RIGHT, std::make_shared<MovementCommand>(GO.get(), glm::vec3{ 1,0,0 }), InputState::Pressed);
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_UP, std::make_shared<MovementCommand>(GO.get(), glm::vec3{ 0,-1,0 }), InputState::Pressed);
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_DOWN, std::make_shared<MovementCommand>(GO.get(), glm::vec3{ 0,1,0 }), InputState::Pressed);


	//GO->SetPosition(19, 19);
	GO->SetScale(0.9f, 0.9f);


	const auto pHealth{ std::make_shared<GameObject>() };

	pHealth->AddComponent<HealthComponent>(std::make_shared<HealthComponent>(pHealth, 1));

	pHealth->GetComponent<HealthComponent>().lock()->AddObserver(GO->GetComponent<PlayerController>().lock().get());
	GO->GetComponent<TankComponent>().lock()->AddObserver(pHealth->GetComponent<HealthComponent>().lock().get());

	scene.AddDefault(pHealth);


	const auto pTurret = std::make_shared<GameObject>("TankTop");
	pTurret->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(pTurret));
	auto turretSprite = pTurret->GetComponent<SpriteComponent>();
	turretSprite.lock()->SetTexture("TronSpriteSheet.png");
	turretSprite.lock()->SetSpriteRect(32 * 6, 32, 32, 32);

	pTurret->SetPosition(5.f, -11.f, 0.f);
	turretSprite.lock()->SetRotationPivot(float2{ 0.296875f,0.765625f });
	//	turretSprite.lock()->SetPivot(float2{ 0.25f, 0.75f });

	scene.Add(pTurret);
	GO->AddChild(pTurret.get());
	return GO;
}

std::shared_ptr<GameObject> GreenTankPlayerPrefab(Scene& scene)
{
	const auto GO = std::make_shared<GameObject>("Player");

	GO->AddComponent<BoxCollider2D>(std::make_shared<BoxCollider2D>(GO, 25));
	PhysicsManager::GetInstance().AddBoxCollider2D(GO->GetComponent<BoxCollider2D>().lock());
	GO->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(GO));
	auto sprite = GO->GetComponent<SpriteComponent>();
	//sprite.lock()->SetColumns(1);
	//sprite.lock()->SetRows(1);
	sprite.lock()->SetTexture("TronSpriteSheet.png");
	sprite.lock()->SetSpriteRect(32 * 8, 0, 32, 32);
	//sprite.lock()->SetRotationPivot(float2{ 0.5f,.5f });
	//sprite.lock()->SetFrameRect(32*9, 0, 32, 32);
	GO->AddComponent<TankComponent>(std::make_shared<TankComponent>(GO, 100, SDL_Rect{ 16,16,448,416 }));
	GO->AddComponent<MovementComponent>(std::make_shared<MovementComponent>(GO));
	GO->AddComponent<RigidBody2D>(std::make_shared<RigidBody2D>(GO, glm::vec3{ 20,20,20 }));
	GO->AddComponent<PlayerController>(std::make_shared<PlayerController>(GO));

	const unsigned int ID = InputManager::GetInstance().AddPlayer();
	InputManager::GetInstance().AddPlayer(true) ;

	InputManager::GetInstance().AddCommand(Controller::ControllerButton::ButtonA, std::make_shared<AttackCommand>(GO.get()), ID, InputState::Down);
	InputManager::GetInstance().AddCommand(Controller::ControllerButton::LeftShoulder, std::make_shared<RotateCommand>(GO.get(), true), ID, InputState::Pressed);
	InputManager::GetInstance().AddCommand(Controller::ControllerButton::RightShoulder, std::make_shared<RotateCommand>(GO.get(), false), ID, InputState::Pressed);
	InputManager::GetInstance().AddCommand(Controller::ControllerButton::DPADLeft, std::make_shared<MovementCommand>(GO.get(), glm::vec3{ -1,0,0 }), ID, InputState::Pressed);
	InputManager::GetInstance().AddCommand(Controller::ControllerButton::DPADRight, std::make_shared<MovementCommand>(GO.get(), glm::vec3{ 1,0,0 }), ID, InputState::Pressed);
	InputManager::GetInstance().AddCommand(Controller::ControllerButton::DPADUp, std::make_shared<MovementCommand>(GO.get(), glm::vec3{ 0,-1,0 }), ID, InputState::Pressed);
	InputManager::GetInstance().AddCommand(Controller::ControllerButton::DPADDown, std::make_shared<MovementCommand>(GO.get(), glm::vec3{ 0,1,0 }), ID, InputState::Pressed);

	InputManager::GetInstance().AddCommand(SDL_SCANCODE_RCTRL, std::make_shared<AttackCommand>(GO.get()), InputState::Down);
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_SLASH, std::make_shared<RotateCommand>(GO.get(), true), InputState::Pressed);
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_RSHIFT, std::make_shared<RotateCommand>(GO.get(), false), InputState::Pressed);
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_LEFT, std::make_shared<MovementCommand>(GO.get(), glm::vec3{ -1,0,0 }), InputState::Pressed);
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_RIGHT, std::make_shared<MovementCommand>(GO.get(), glm::vec3{ 1,0,0 }), InputState::Pressed);
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_UP, std::make_shared<MovementCommand>(GO.get(), glm::vec3{ 0,-1,0 }), InputState::Pressed);
	InputManager::GetInstance().AddCommand(SDL_SCANCODE_DOWN, std::make_shared<MovementCommand>(GO.get(), glm::vec3{ 0,1,0 }), InputState::Pressed);


	//GO->SetPosition(19, 19);
	GO->SetScale(0.9f, 0.9f);


	const auto pHealth{ std::make_shared<GameObject>() };

	pHealth->AddComponent<HealthComponent>(std::make_shared<HealthComponent>(pHealth, 1));

	pHealth->GetComponent<HealthComponent>().lock()->AddObserver(GO->GetComponent<PlayerController>().lock().get());
	GO->GetComponent<TankComponent>().lock()->AddObserver(pHealth->GetComponent<HealthComponent>().lock().get());

	scene.AddDefault(pHealth);


	const auto pTurret = std::make_shared<GameObject>("TankTop");
	pTurret->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(pTurret));
	auto turretSprite = pTurret->GetComponent<SpriteComponent>();
	turretSprite.lock()->SetTexture("TronSpriteSheet.png");
	turretSprite.lock()->SetSpriteRect(32 * 6, 32, 32, 32);

	pTurret->SetPosition(5.f, -11.f, 0.f);
	turretSprite.lock()->SetRotationPivot(float2{ 0.296875f,0.765625f });
	//	turretSprite.lock()->SetPivot(float2{ 0.25f, 0.75f });

	scene.Add(pTurret);
	GO->AddChild(pTurret.get());
	return GO;
}

std::shared_ptr<GameObject> BulletPrefab(GameObject* parent, const glm::vec3& direction)
{
	const auto GO = std::make_shared<GameObject>("Bullet");

	GO->AddComponent<BulletComponent>(std::make_shared<BulletComponent>(GO, parent, direction));
	GO->AddComponent<BoxCollider2D>(std::make_shared<BoxCollider2D>(GO,4));
	GO->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(GO));
	

	auto sprite = GO->GetComponent<SpriteComponent>();

	sprite.lock()->SetTexture("TronSpriteSheet.png");
	sprite.lock()->SetSpriteRect(32 * 6, 0, 4, 4);
	GO->AddComponent<RigidBody2D>(std::make_shared<RigidBody2D>(GO, glm::vec3{50,50,50}));
	return GO;
}
