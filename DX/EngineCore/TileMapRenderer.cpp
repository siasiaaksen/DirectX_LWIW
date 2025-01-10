#include "PreCompile.h"
#include "TileMapRenderer.h"
#include "EngineCamera.h"
#include "EngineSprite.h"


UTileMapRenderer::UTileMapRenderer()
{
	CreateRenderUnit();
	SetMesh("Rect");
	SetMaterial("TileMap");

	//GetRenderUnit().ConstantBufferLinkData("ResultColor", ColorData);
	//GetRenderUnit().ConstantBufferLinkData("FSpriteData", SpriteData);
	//GetRenderUnit().ConstantBufferLinkData("FUVValue", UVValue);
}

UTileMapRenderer::~UTileMapRenderer()
{
}

void UTileMapRenderer::SetTileSetting(std::string_view _Name, FVector _TileSize, FVector _ImageSize, FVector _Pivot)
{
	Sprite = UEngineSprite::Find<UEngineSprite>(_Name).get();

	TileSize = _TileSize;
	ImageSize = _ImageSize;
	TilePivot = _Pivot;
}

void UTileMapRenderer::BeginPlay()
{
	URenderer::BeginPlay();
}

void UTileMapRenderer::Render(UEngineCamera* _Camera, float _DeltaTime)
{
	FTransform& CameraTrans = _Camera->GetTransformRef();
	FTransform& RendererTrans = GetTransformRef();

	RendererTrans.View = CameraTrans.View;
	RendererTrans.Projection = CameraTrans.Projection;
	RendererTrans.WVP = RendererTrans.World * RendererTrans.View * RendererTrans.Projection;

	if (0 == Tiles.size())
	{
		return;
	}

	URenderUnit& Unit = GetRenderUnit();

	FTransform Trans;
	FMatrix Scale;
	FMatrix Pos;

	Scale.Scale(ImageSize);

	for (std::pair<const __int64, FTileData>& TilePair : Tiles)
	{
		//if (화면 바깥에 나간 타일은)
		//{
		//	continue;
		//}

		FTileData& Tile = TilePair.second;
		FTileIndex Index;

		GetRenderUnit().SetTexture("TileMapTex", Sprite->GetTexture(Tile.SpriteIndex));
		Tile.SpriteData = Sprite->GetSpriteData(Tile.SpriteIndex);
		Tile.SpriteData.Pivot = { 0.0f, 0.0f };

		Index.Key = TilePair.first;

		Pos.Position({ Index.X * TileSize.X, Index.Y * TileSize.Y });

		Trans.WVP = Scale * Pos * RendererTrans.View * RendererTrans.Projection;

		GetRenderUnit().ConstantBufferLinkData("FTransform", Trans);

		GetRenderUnit().ConstantBufferLinkData("ResultColor", Tile.ColorData);
		GetRenderUnit().ConstantBufferLinkData("FSpriteData", Tile.SpriteData);

		Unit.Render(_Camera, _DeltaTime);
	}
}

void UTileMapRenderer::SetTile(FVector _Pos, int _Spriteindex)
{
	_Pos /= TileSize;

	SetTile(_Pos.iX(), _Pos.iY(), _Spriteindex);
}

void UTileMapRenderer::SetTile(int _X, int _Y, int _Spriteindex)
{
	FTileIndex Index = { _X,  _Y };

	FTileData& NewTile = Tiles[Index.Key];

	NewTile.SpriteIndex = _Spriteindex;
	NewTile.SpriteData.CuttingPos = { 0.0f, 0.0f };
	NewTile.SpriteData.CuttingSize = { 1.0f, 1.0f };
	NewTile.SpriteData.Pivot = { 0.5f, 0.5f };
	NewTile.ColorData.PlusColor = { 0.0f, 0.0f, 0.0f, 0.0f };
	NewTile.ColorData.MulColor = { 1.0f, 1.0f, 1.0f, 1.0f };
}

void UTileMapRenderer::RemoveTile(FVector _Pos)
{
	_Pos /= TileSize;

	RemoveTile(_Pos.iX(), _Pos.iY());
}

void UTileMapRenderer::RemoveTile(int _X, int _Y)
{
	FTileIndex Index = { _X,  _Y };

	if (false == Tiles.contains(Index.Key))
	{
		return;
	}

	Tiles.erase(Index.Key);
}

void UTileMapRenderer::RenderTransUpdate(UEngineCamera* _Camera)
{
}

void UTileMapRenderer::ComponentTick(float _DeltaTime)
{
	URenderer::ComponentTick(_DeltaTime);
}

