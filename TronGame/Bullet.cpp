#include "Bullet.h"
#include "GameObject.h"
#include "RigidBody2D.h"
#include "PhysicsManager.h"
#include "TankComponent.h"
#include "PlayerControllerComponent.h"


BulletComponent::BulletComponent(const std::weak_ptr<GameObject> owner, GameObject* pParentGO, const glm::vec3& direction):
    BaseComponent(owner),
    m_pParent(pParentGO),
    m_Direction(direction)
{
}

void BulletComponent::Update()
{
    
    m_Owner.lock()->GetComponent<RigidBody2D>().lock()->Movement(m_Direction);
   
    CheckOverlap();
}

void BulletComponent::LateUpdate()
{
    if (m_Owner.lock()->GetTransform().GetPosition().x > 640 || m_Owner.lock()->GetTransform().GetPosition().x < 0 || m_Owner.lock()->GetTransform().GetPosition().y > 480 || m_Owner.lock()->GetTransform().GetPosition().y < 0)
    {
        m_IsDestroyed = true;
    }
    if (IsDestroyed())
    {
        m_Owner.lock()->MarkForDestruction();
        return;
    }
}

bool BulletComponent::IsDestroyed() const
{
    return m_IsDestroyed;
  
}

void BulletComponent::Bounce(const BoxCollider2D* overlappingBox)
{
    float leftX = overlappingBox->GetBoxCollider().x;
    float rightX = overlappingBox->GetBoxCollider().x + overlappingBox->GetBoxCollider().w;
    float PosX = m_Owner.lock()->GetTransform().GetPosition().x;
    if (leftX >= PosX && rightX > PosX)
    {
        m_Direction.x *= -1;
    }
    if (leftX < PosX && rightX-1 <= PosX )
    {
        m_Direction.x *= -1;
    }
    float TopY = overlappingBox->GetBoxCollider().y;
    float BotY = overlappingBox->GetBoxCollider().y + overlappingBox->GetBoxCollider().h;
    float PosY = m_Owner.lock()->GetTransform().GetPosition().y;
    if (TopY >= PosY && BotY > PosY)
    {
        m_Direction.y *= -1;
    }
    if (TopY< PosY && BotY-1 <= PosY)
    {
        m_Direction.y *= -1;
    }
   
}

void BulletComponent::CheckOverlap()
{
    const auto BulletCollider = m_Owner.lock()->GetComponent<BoxCollider2D>().lock().get();
    BulletCollider->SetBoxCollider(SDL_Rect{ int(m_Owner.lock()->GetTransform().GetPosition().x),int(m_Owner.lock()->GetTransform().GetPosition().y), BulletCollider->GetBoxCollider().w,BulletCollider->GetBoxCollider().h });

    if (BulletCollider == nullptr)
    {
        return;
    }
  
    const std::vector<BoxCollider2D*> overlappingColliders = PhysicsManager::GetInstance().GetOverlappers(BulletCollider , true);
    if (overlappingColliders.empty())
    {
        return;
    }
    for (auto collider : overlappingColliders)
    {
        std::string name = collider->GetGameObject()->GetName();
        if (name == "Wall" || name == "Teleporter")
        {
            if (m_pPreviousCollision != collider)
            {

                m_pPreviousCollision = collider;
                ++m_AmountOfBounces;
              
                Bounce(collider);
                m_Owner.lock()->GetComponent<RigidBody2D>().lock()->Movement(m_Direction);

                if (m_AmountOfBounces >= m_MaxBounces)
                {
                    m_IsDestroyed = true;
                }
                return;
            }
            
        }
        if (collider->GetGameObject().get() != m_pParent) // bullet cannot harm the tank that shot this bullet
        {
            

            if (name == "Enemy")
            {
                if (m_pParent->GetName() == "Player")
                {
                    if (m_Owner.lock()->IsMarkedForDestruction())
                    {
                        return;
                    }
                    if (m_Owner.expired())
                    {
                        return;
                    }
                    auto Go = collider->GetGameObject();
                    Go->GetComponent<TankComponent>().lock()->TakeDamage();
                    m_IsDestroyed = true;
                    m_pParent->GetComponent<PlayerController>().lock()->NotifyAll(EventType::KILL, std::make_shared<GameObjectArgs>(Go.get()));
                   
                }
            }
            if (name == "Player")
            {

                collider->GetGameObject()->GetComponent<TankComponent>().lock()->TakeDamage();
                m_IsDestroyed = true;
            }
            return;
        }
    }
}
