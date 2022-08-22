#pragma once
#include <memory>
#include "GameObject.h"
#include "BoxCollider2D.h"
#include "TankComponent.h"
#include "RigidBody2D.h"
#include "MovementComponent.h"
#include "SpriteComponent.h"
#include "InputManager.h"


std::shared_ptr<GameObject> PlayerPrefab(Scene& scene);
std::shared_ptr<GameObject> BlueTankEnemyPrefab(Scene& scene);
std::shared_ptr<GameObject> BlueTankPlayerPrefab(Scene& scene);
std::shared_ptr<GameObject> GreenTankPlayerPrefab(Scene& scene);
std::shared_ptr<GameObject> BulletPrefab(GameObject* parent, const glm::vec3& direction);