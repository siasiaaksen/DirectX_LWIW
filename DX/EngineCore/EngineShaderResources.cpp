#include "PreCompile.h"
#include "EngineShaderResources.h"


UEngineShaderResources::UEngineShaderResources()
{
}

UEngineShaderResources::~UEngineShaderResources()
{
}

void UEngineShaderResources::CreateConstantBufferRes(std::string_view _Name, UEngineConstantBufferRes _Res)
{
	if (true == ConstantBufferRess.contains(_Name.data()))
	{
		MSGASSERT("���� �̸� ������۰� �� ���̴��� 2���� �����մϴ�");
		return;
	}

	ConstantBufferRess[_Name.data()] = _Res;
}