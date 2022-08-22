#include "MiniginPCH.h"
#include "JsonFileReader.h"
#include <fstream>
#include "../3rdParty/rapidjson/document.h"
#include "../3rdParty/rapidjson/istreamwrapper.h"
#include <memory>
#include "GameObject.h"
#include "BoxCollider2D.h"
#include "SpriteComponent.h"
#include "PhysicsManager.h"

void JsonFileReader::ReadFile(Scene& scene, const std::string& path)
{
	if (std::ifstream istream {"../Data/" + path})
	{
		rapidjson::IStreamWrapper isw{ istream };
		rapidjson::Document jsonDoc;

		jsonDoc.ParseStream(isw);

		const rapidjson::Value& valName = jsonDoc["LevelColliders"];
		for ( const auto& c : valName.GetArray() )
		{
			const bool IsWall = c["IsWall"].GetBool();
			const auto WallDim = c["WallDimensions"].GetArray();

			int arr[4];

			for (int i = 0; i < static_cast<int>(WallDim.Size()); i++)
			{
				arr[i] = WallDim[i].GetInt();
			}
			SDL_Rect collider{ arr[0],arr[1],arr[2],arr[3] };
			std::string name;
			if (IsWall)
			{
				name = "Wall";
				const auto go = std::make_shared<GameObject>(name);
				go->SetPosition((float)arr[0], (float)arr[1] , 1.f);
				go->AddComponent<BoxCollider2D>(std::make_shared<BoxCollider2D>(go, collider));
				go->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(go));
				PhysicsManager::GetInstance().AddBoxCollider2D(go->GetComponent<BoxCollider2D>().lock());
				auto sprite = go->GetComponent<SpriteComponent>();
				sprite.lock()->SetTexture("Wall.jpg");
				sprite.lock()->SetSpriteRect(collider);
				scene.Add(go);
			}
			else
			{
				name = "Teleporter";
				const auto go = std::make_shared<GameObject>(name);
				go->SetPosition((float)arr[0]-arr[2]/2, (float)arr[1],1.f);
				go->AddComponent<BoxCollider2D>(std::make_shared<BoxCollider2D>(go, collider));
				go->AddComponent<SpriteComponent>(std::make_shared<SpriteComponent>(go));
				PhysicsManager::GetInstance().AddBoxCollider2D(go->GetComponent<BoxCollider2D>().lock());
				auto sprite = go->GetComponent<SpriteComponent>();
				sprite.lock()->SetTexture("Teleporter.png");
				sprite.lock()->SetSpriteRect(0,0, 64, 66);
				scene.Add(go);
			}

			
			

		}
	}
}
