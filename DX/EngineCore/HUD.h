#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/EngineCamera.h>


class AHUD : public AActor
{
	friend class ULevel;

public:
	ENGINEAPI AHUD();
	ENGINEAPI ~AHUD();

	AHUD(const AHUD& _Other) = delete;
	AHUD(AHUD&& _Other) noexcept = delete;
	AHUD& operator=(const AHUD& _Other) = delete;
	AHUD& operator=(AHUD&& _Other) noexcept = delete;

	template<typename WidgetType>
	std::shared_ptr<WidgetType> CreateWidget(int _ZOrder, std::string_view _Name = "NONE")
	{
		static_assert(std::is_base_of_v<UWidget, WidgetType>, "���͸� ��ӹ��� ���� Ŭ������ SpawnActor�Ϸ��� �߽��ϴ�.");

		if (false == std::is_base_of_v<UWidget, WidgetType>)
		{
			MSGASSERT("������ ��ӹ��� ���� Ŭ������ CreateWidget�Ϸ��� �߽��ϴ�.");
			return nullptr;
		}

		char* Memory = new char[sizeof(WidgetType)];

		UWidget* WidgetPtr = reinterpret_cast<WidgetType*>(Memory);
		WidgetPtr->HUD = this;

		WidgetType* NewPtr = reinterpret_cast<WidgetType*>(Memory);
		std::shared_ptr<WidgetType> NewWidgetPtr(NewPtr = new(Memory) WidgetType());
		WidgetPtr->HUD = this;
		NewWidgetPtr->SetName(_Name);
		NewWidgetPtr->SetOrder(_ZOrder);
		Widgets[NewWidgetPtr->GetOrder()].push_back(NewWidgetPtr);

		return NewWidgetPtr;
	}

protected:

private:
	std::map<int, std::list<std::shared_ptr<class UWidget>>> Widgets;

	void UIRender(UEngineCamera* _Camera, float _DeltaTime);
};

