#include "PreCompile.h"
#include "EngineFile.h"
#include "EngineDebug.h"
#include "EngineSerializer.h"


UEngineFile::UEngineFile()
{
}

UEngineFile::UEngineFile(const UEnginePath& _Path)
	: UEnginePath(_Path)
{
}

UEngineFile::UEngineFile(const std::string& _Path)
	: UEnginePath(std::string_view(_Path.c_str()))
{
}

UEngineFile::UEngineFile(std::string_view _Path)
	: UEnginePath(_Path)
{
}

UEngineFile::UEngineFile(std::filesystem::path _Path)
	: UEnginePath(_Path)
{
}

UEngineFile::~UEngineFile()
{
	Close();
}

void UEngineFile::FileOpen(const char* _Mode)
{
	fopen_s(&File, GetPathToString().c_str(), _Mode);

	if (nullptr == File)
	{
		MSGASSERT(GetPathToString() + + "���� ���¿� �����߽��ϴ�");
	}
}

void UEngineFile::Write(UEngineSerializer& _Ser)
{
	Write(_Ser.GetDataPtr(), _Ser.GetWriteOffset());
}

int UEngineFile::GetFileSize()
{
	if (false == IsFile())
	{
		MSGASSERT(Path.string() + "������ �ƴ� ������ ũ�⸦ �˼��� �����ϴ�.");
		return -1;
	}

	return static_cast<int>(std::filesystem::file_size(Path));
}

void UEngineFile::Read(class UEngineSerializer& _Ser)
{
	int FileSize = GetFileSize();

	_Ser.DataResize(FileSize);

	Read(_Ser.GetDataPtr(), FileSize);
}

void UEngineFile::Write(const void* _Ptr, size_t _Size)
{
	if (0 == _Size)
	{
		MSGASSERT("ũ�Ⱑ 0�� �����͸� ������ �����ϴ�.");
	}

	if (nullptr == _Ptr)
	{
		MSGASSERT("�������� �ʴ� �޸𸮸� ����Ϸ��� �߽��ϴ�.");
	}

	if (nullptr == File)
	{
		MSGASSERT("���� ���� ���Ͽ� ������ ������ �߽��ϴ�");
		return;
	}

	fwrite(_Ptr, _Size, 1, File);
}

void UEngineFile::Read(void* _Ptr, size_t _Size)
{
	if (0 == _Size)
	{
		MSGASSERT("ũ�Ⱑ 0�� �����͸� �������� �����ϴ�.");
	}

	if (nullptr == _Ptr)
	{
		MSGASSERT("�������� �ʴ� �޸𸮸� �������� �߽��ϴ�.");
	}

	if (nullptr == File)
	{
		MSGASSERT("���� ���� ���Ͽ� ������ ������ �߽��ϴ�");
		return;
	}

	fread(_Ptr, _Size, 1, File);
}

void UEngineFile::Close()
{
	if (nullptr != File)
	{
		fclose(File);
		File = nullptr;
	}
}

std::string UEngineFile::GetAllFileText()
{
	UEngineSerializer Ser;
	Read(Ser);

	return reinterpret_cast<const char*>(Ser.GetDataPtr());
}