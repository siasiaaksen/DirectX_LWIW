#include "PreCompile.h"
#include "EngineShaderResources.h"
#include "EngineBase/EngineDebug.h"


UEngineShaderResources::UEngineShaderResources()
{
}

UEngineShaderResources::~UEngineShaderResources()
{
}

void UEngineShaderResources::CreateSamplerRes(std::string_view _Name, UEngineSamplerRes _Res)
{
	std::string UpperString = UEngineString::ToUpper(_Name);

	if (true == SamplerRes.contains(UpperString))
	{
		MSGASSERT("같은 이름 상수버퍼가 한 쉐이더에 2개가 존재합니다");
		return;
	}

	SamplerRes[UpperString] = _Res;
}

void UEngineShaderResources::CreateTextureRes(std::string_view _Name, UEngineTextureRes _Res)
{
	std::string UpperString = UEngineString::ToUpper(_Name);

	if (true == TextureRes.contains(UpperString))
	{
		MSGASSERT("같은 이름 상수버퍼가 한 쉐이더에 2개가 존재합니다");
		return;
	}

	TextureRes[UpperString] = _Res;
}

void UEngineShaderResources::CreateConstantBufferRes(std::string_view _Name, UEngineConstantBufferRes _Res)
{
	std::string UpperString = UEngineString::ToUpper(_Name);

	if (true == ConstantBufferRes.contains(UpperString))
	{
		MSGASSERT("같은 이름 상수버퍼가 한 쉐이더에 2개가 존재합니다");
		return;
	}

	ConstantBufferRes[UpperString] = _Res;
}

void UEngineShaderResources::CreateStructuredBufferRes(std::string_view _Name, UEngineStructuredBufferRes _Res)
{
	std::string UpperString = UEngineString::ToUpper(_Name);

	if (true == StructuredBufferRes.contains(UpperString))
	{
		MSGASSERT("같은 이름 상수버퍼가 한 쉐이더에 2개가 존재합니다");
		return;
	}

	StructuredBufferRes[UpperString] = _Res;
}

void UEngineShaderResources::Reset()
{
	for (std::pair<const std::string, UEngineTextureRes>& Res : TextureRes)
	{
		Res.second.Reset();
	}

	for (std::pair<const std::string, UEngineSamplerRes>& Res : SamplerRes)
	{
		Res.second.Reset();
	}
}

void UEngineShaderResources::Setting()
{
	for (std::pair<const std::string, UEngineConstantBufferRes>& Res : ConstantBufferRes)
	{
		Res.second.Setting();
	}

	for (std::pair<const std::string, UEngineTextureRes>& Res : TextureRes)
	{
		Res.second.Setting();
	}

	for (std::pair<const std::string, UEngineSamplerRes>& Res : SamplerRes)
	{
		Res.second.Setting();
	}

	for (std::pair<const std::string, UEngineStructuredBufferRes>& Res : StructuredBufferRes)
	{
		Res.second.Setting();
	}
}

bool UEngineShaderResources::IsSampler(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);
	return SamplerRes.contains(UpperName);
}

bool UEngineShaderResources::IsTexture(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);
	return TextureRes.contains(UpperName);
}

bool UEngineShaderResources::IsConstantBuffer(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);
	return ConstantBufferRes.contains(UpperName);
}

bool UEngineShaderResources::IsStructuredBuffer(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);
	return StructuredBufferRes.contains(UpperName);
}

void UEngineShaderResources::ConstantBufferLinkData(std::string_view _Name, void* _Data)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == ConstantBufferRes.contains(UpperName))
	{
		UEngineDebug::OutPutString("ConstantBufferRes.contains " + UpperName);
		return;
	}

	ConstantBufferRes[UpperName].Data = _Data;
}

void UEngineShaderResources::StructuredBufferLinkData(std::string_view _Name, UINT _Count, void* _Data)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == StructuredBufferRes.contains(UpperName))
	{
		UEngineDebug::OutPutString("StructuredBufferRes.contains " + UpperName);
		return;
	}

	if (StructuredBufferRes[UpperName].Res->DataCount < _Count)
	{
		int DataSize = StructuredBufferRes[UpperName].Res->DataSize;
		StructuredBufferRes[UpperName].Res->ResCreate(DataSize, _Count);
	}

	StructuredBufferRes[UpperName].DataCount = _Count;
	StructuredBufferRes[UpperName].Data = _Data;
}

void UEngineShaderResources::SamplerSetting(std::string_view _Name, std::string_view _ResName)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == SamplerRes.contains(UpperName))
	{
		UEngineDebug::OutPutString("ConstantBufferRes.contains " + UpperName);
		return;
	}

	SamplerRes[UpperName].Res = UEngineSampler::Find<UEngineSampler>(_ResName);
}

void UEngineShaderResources::TextureSetting(std::string_view _Name, std::string_view _ResName)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == TextureRes.contains(UpperName))
	{
		UEngineDebug::OutPutString("TextureRes.contains " + UpperName);
		return;
	}

	TextureRes[UpperName].Res = UEngineTexture::Find<UEngineTexture>(_ResName).get();
}

void UEngineShaderResources::TextureSetting(std::string_view _Name, std::shared_ptr<UEngineTexture> _Texture)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == TextureRes.contains(UpperName))
	{
		UEngineDebug::OutPutString("TextureRes.contains " + UpperName);
		return;
	}

	TextureRes[UpperName].Res = _Texture.get();
}

void UEngineShaderResources::TextureSetting(std::string_view _Name, UEngineTexture* _Texture)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == TextureRes.contains(UpperName))
	{
		UEngineDebug::OutPutString("TextureRes.contains " + UpperName);
		return;
	}

	TextureRes[UpperName].Res = _Texture;
}