#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/Collision.h>
#include <EngineCore/SpriteRenderer.h>


class AInteractObject :public AActor
{
public:
	AInteractObject();
	~AInteractObject();

	AInteractObject(const AInteractObject& _Other) = delete;
	AInteractObject(AInteractObject&& _Other) noexcept = delete;
	AInteractObject& operator=(const AInteractObject& _Other) = delete;
	AInteractObject& operator=(AInteractObject&& _Other) noexcept = delete;

	void BeginPlay();
	void Tick(float _DeltaTime);

	void Serialize(UEngineSerializer& _Ser) override;
	void DeSerialize(UEngineSerializer& _Ser) override;

	void SetSprite(std::shared_ptr<class USpriteRenderer> _Sprite)
	{
		Sprite = _Sprite;
	}

	std::shared_ptr<class USpriteRenderer>& GetSprite()
	{
		return Sprite;
	}

	void SetCollision(std::shared_ptr<class UCollision> _Collision)
	{
		Collision = _Collision;
	}

	std::shared_ptr<class UCollision>& GetCollision()
	{
		return Collision;
	}

	void SetSpriteIndex(int _SpriteIndex)
	{
		SpriteIndex = _SpriteIndex;
	}

	int GetSpriteIndex()
	{
		return SpriteIndex;
	}

	void SetSpriteName(std::string _SpriteName)
	{
		SpriteName = _SpriteName;
	}

	std::string GetSpriteName()
	{
		return SpriteName;
	}

	void SetSpritePivot(float4 _SpritePivot)
	{
		Sprite->SpriteData.Pivot = _SpritePivot;
	}

	float4 GetSpritePivot()
	{
		return Sprite->SpriteData.Pivot;
	}

	void SetColActive(bool _Value)
	{
		IsColActive = _Value;
		Collision->SetActive(IsColActive);
	}

	bool GetColActive()
	{
		return IsColActive;
	}

	void SetColPos(FVector _Pos)
	{
		ColPos = _Pos;
	}

	FVector GetColPos()
	{
		return ColPos;
	}
	
	void SetColScale(FVector _Scale)
	{
		ColScale = _Scale;
	}

	FVector GetColScale()
	{
		return ColScale;
	}

	void SetObjectName(std::string _ObjectName)
	{
		ObjectName = _ObjectName;
	}

	std::string& GetObjectName()
	{
		return ObjectName;
	}

protected:

private:
	std::shared_ptr<USpriteRenderer> Sprite;
	std::shared_ptr<UCollision> Collision;

	int SpriteIndex;
	std::string SpriteName;
	//float4 SpritePivot;

	bool IsColActive = false;
	FVector ColPos;
	FVector ColScale;

	std::string ObjectName;
};

