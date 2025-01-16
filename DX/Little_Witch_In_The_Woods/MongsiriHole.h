#pragma once
#include <EngineCore/Actor.h>


class AMongsiriHole : public AActor
{
public:
	AMongsiriHole();
	~AMongsiriHole();

	AMongsiriHole(const AMongsiriHole& _Other) = delete;
	AMongsiriHole(AMongsiriHole&& _Other) noexcept = delete;
	AMongsiriHole& operator=(const AMongsiriHole& _Other) = delete;
	AMongsiriHole& operator=(AMongsiriHole&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void YSorting();

protected:

private:

};

