#pragma once
#include <EngineCore/Actor.h>


class ATitleBridge : public AActor
{
public:
	ATitleBridge();
	~ATitleBridge();

	ATitleBridge(const ATitleBridge& _Other) = delete;
	ATitleBridge(ATitleBridge&& _Other) noexcept = delete;
	ATitleBridge& operator=(const ATitleBridge& _Other) = delete;
	ATitleBridge& operator=(ATitleBridge&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> BridgeRenderer;
};

