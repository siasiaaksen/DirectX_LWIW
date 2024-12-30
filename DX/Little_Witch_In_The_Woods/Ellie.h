#pragma once
#include <EngineCore/Pawn.h>
#include <EngineCore/SpriteRenderer.h>


class AEllie : public APawn
{
public:
	AEllie();
	~AEllie();

	AEllie(const AEllie& _Other) = delete;
	AEllie(AEllie&& _Other) noexcept = delete;
	AEllie& operator=(const AEllie& _Other) = delete;
	AEllie& operator=(AEllie&& _Other) noexcept = delete;

	std::shared_ptr<USpriteRenderer> GetRenderer()
	{
		return EllieRenderer;
	}
	
protected:

private:
	std::shared_ptr<USpriteRenderer> EllieRenderer;
};

