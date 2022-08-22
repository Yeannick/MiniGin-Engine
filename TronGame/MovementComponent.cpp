#include "MovementComponent.h"
#include "GameObject.h"
#include "RigidBody2D.h"
#include "GameTime.h"
#include "BoxCollider2D.h"
#include "PhysicsManager.h"
#include "SpriteComponent.h"
#include "TankComponent.h"
#include <iostream>

MovementComponent::MovementComponent(const std::weak_ptr<GameObject> owner): BaseComponent(owner)
{
}

// movement involves RigidBody Component , we get the movementSpeed from here and calculate whether a GO with this component can move in a given Direction and then let the rigidbody Move the GO to the desired Position
void MovementComponent::Movement(glm::vec3 MovementVector) const
{
    if (m_Owner.expired())
    {
        return;
    }
    if (!m_Owner.lock().get())
    {
        return;
    }
    // Get RB component
    const auto rigidBody = m_Owner.lock()->GetComponent<RigidBody2D>();
    // if no rigidbody is found (no rigidbody is present in GO) than we cant move so why do the rest of the Calculations
    if (!rigidBody.lock().get())
    {
        return;
    }

    // Calculate Velocity

    glm::vec3 velocity = MovementVector * GameTime::GetInstance().GetDeltaTime() * rigidBody.lock()->GetMovementSpeed();

    CheckMovement(velocity, MovementVector);


    rigidBody.lock()->Movement(MovementVector);


    float angle{};
    if (MovementVector.x != 0)// 90 or 270 degrees
    {
        if (MovementVector.x > 0)
            angle = 90;
        else
            angle = -90;
    }
    else if (MovementVector.y < 0)
        angle = 180;
    m_Owner.lock()->SetRotation(angle);
}
void MovementComponent::CheckMovement(glm::vec3& velocity, glm::vec3& movementVector)const
{

    if (velocity.x > 0 && CanMoveInDirection(MovementDirection::Right, velocity))
    {
        movementVector.x = 0;
    }
    else if (velocity.x < 0 && CanMoveInDirection(MovementDirection::Left, velocity))
    {
        movementVector.x = 0;
    }
    if (velocity.y > 0 && CanMoveInDirection(MovementDirection::Down, velocity))
    {
        movementVector.y = 0;
    }
    else if (velocity.y < 0 && CanMoveInDirection(MovementDirection::Up, velocity))
    {
        movementVector.y = 0;
    }
    if (movementVector.x == 0 && movementVector.y == 0)
        return;
}
bool MovementComponent::CanMoveInDirection(MovementDirection direction, glm::vec3 velocity) const
{
    const auto rigidBody = m_Owner.lock()->GetComponent<RigidBody2D>();
    // if no rigidbody is found (no rigidbody is present in GO) than we cant move so why do the rest of the Calculations
    if (!rigidBody.lock().get())
    {
        return false;
    }
    const auto Collider = m_Owner.lock()->GetComponent<BoxCollider2D>();
    SDL_Rect box = Collider.lock()->GetBoxCollider();
    const int left = box.x;
    const int bottom = box.y;
    const int width = box.w;
    const int height = box.h;

    // simulate Move of our boxCollider , if we hit something return false

    // --- Switch case has lots of same Code // #ToDo Find better way of doing this  
    switch (direction)
    {
    case MovementDirection::Left:
        velocity *= glm::vec3{ -1,0,0 };
        box.x += static_cast<int>(velocity.x) - 1;
        Collider.lock()->SetBoxCollider(box);

        if (PhysicsManager::GetInstance().IsOverlapping(Collider.lock(),true))
        {
            const std::vector<BoxCollider2D*> overlappingColliders = PhysicsManager::GetInstance().GetOverlappers(Collider.lock().get(), false);
            bool IsOverlapWall = false;

            for (const auto& o :overlappingColliders)
            {
                if (o->GetGameObject()->GetName() == "Walls")
                {
                    IsOverlapWall = true;
                }
                if (o->GetGameObject()->GetName() == "Teleporter")
                {
                    m_Owner.lock()->GetComponent<TankComponent>().lock()->Teleport();
                }
            }
            box.x = left;
            Collider.lock()->SetBoxCollider(box);
            return !IsOverlapWall;
        }
        box.x = left;
        Collider.lock()->SetBoxCollider(box);
        break;
    case MovementDirection::Right:
        velocity *= glm::vec3{ 1,0,0 };
        box.x += static_cast<int>(velocity.x) + 1;
        Collider.lock()->SetBoxCollider(box);

        if (PhysicsManager::GetInstance().IsOverlapping(Collider.lock(), false))
        {
            const std::vector<BoxCollider2D*> overlappingColliders = PhysicsManager::GetInstance().GetOverlappers(Collider.lock().get(), false);
            bool IsOverlapWall = false;

            for (const auto& o : overlappingColliders)
            {
                if (o->GetGameObject()->GetName() == "Walls")
                {
                    IsOverlapWall = true;
                }
                if (o->GetGameObject()->GetName() == "Teleporter")
                {
                    m_Owner.lock()->GetComponent<TankComponent>().lock()->Teleport();
                }
            }
            box.x = left;
            Collider.lock()->SetBoxCollider(box);
            return !IsOverlapWall;
        }
        box.x = left;
        Collider.lock()->SetBoxCollider(box);
        break;
    case MovementDirection::Up:
        velocity *= glm::vec3{ 0,-1,0 };
        box.y += static_cast<int>(velocity.y) - 1;
        Collider.lock()->SetBoxCollider(box);

        if (PhysicsManager::GetInstance().IsOverlapping(Collider.lock(), true))
        {
            
            const std::vector<BoxCollider2D*> overlappingColliders = PhysicsManager::GetInstance().GetOverlappers(Collider.lock().get(), false);
            bool IsOverlapWall = false;

            for (const auto& o : overlappingColliders)
            {
                if (o->GetGameObject()->GetName() == "Walls")
                {
                    IsOverlapWall = true;
                   
                }
                if (o->GetGameObject()->GetName() == "Teleporter")
                {
                    m_Owner.lock()->GetComponent<TankComponent>().lock()->Teleport();
                }
            }
            box.y = bottom;
            Collider.lock()->SetBoxCollider(box);
            return !IsOverlapWall;
        }
        box.y = bottom;
        Collider.lock()->SetBoxCollider(box);
        break;
    case MovementDirection::Down:
        velocity *= glm::vec3{ 0,1,0 };
        box.y += static_cast<int>(velocity.y) + 1;
        Collider.lock()->SetBoxCollider(box);

        if (PhysicsManager::GetInstance().IsOverlapping(Collider.lock(), true))
        {
            const std::vector<BoxCollider2D*> overlappingColliders = PhysicsManager::GetInstance().GetOverlappers(Collider.lock().get(), false);
            bool IsOverlapWall = false;

            for (const auto& o : overlappingColliders)
            {
                if (o->GetGameObject()->GetName() == "Walls")
                {
                    IsOverlapWall = true;
                }
                if (o->GetGameObject()->GetName() == "Teleporter")
                {
                    //o->GetGameObject()->GetComponent<TankComponent>().lock()->Teleport();
                    m_Owner.lock()->GetComponent<TankComponent>().lock()->Teleport();
                }
            }
            box.y = bottom;
            Collider.lock()->SetBoxCollider(box);
            return !IsOverlapWall;
        }
        box.y = bottom;
        Collider.lock()->SetBoxCollider(box);
        break;
    case MovementDirection::Horizontal:
        return CanMoveInDirection(MovementDirection::Left , velocity) || CanMoveInDirection(MovementDirection::Right,velocity);
        break;
    case MovementDirection::Vertical:
        return CanMoveInDirection(MovementDirection::Up, velocity) || CanMoveInDirection(MovementDirection::Down, velocity);
        break;
    default:
        break;
    }


    return false;
}
