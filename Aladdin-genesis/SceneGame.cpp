#include "SceneGame.h"
#include <cstdlib>
#include <ctime>
#include "Sound.h"
#include "SceneDealth.h"
#include "SceneLevelCompleted.h"
#include "SceneWin.h"
void SceneGame::KeyState(BYTE * state)
{
	float vx;
	float vy;
	aladdin->GetSpeed(vx, vy);
	float x, y;
	aladdin->GetPosition(x, y);
	if (Game::GetInstance()->IsKeyDown(DIK_A))
		aladdin->SetPosition(x, y - 100);

	if (Game::GetInstance()->IsKeyDown(DIK_RIGHT) || Game::GetInstance()->IsKeyDown(DIK_LEFT))
	{
		if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
			aladdin->SetNx(1);
		else
			aladdin->SetNx(-1);
		if (!aladdin->isClimbing)
			aladdin->SetSpeed(ALADDIN_WALK_SPEED, vy);
		aladdin->isRunning = true;
		if (!aladdin->isAttacking)
		{
			if (!aladdin->isClimbing)
				if (!aladdin->isJumping)
					if (!Game::GetInstance()->IsKeyDown(DIK_C))
					{
						if (!aladdin->isCollisionWithWall) {
							aladdin->SetCurrentState(ALADDIN_RUNNING1);
						}
						else
						{
							aladdin->SetCurrentState(ALADDIN_PUSHING);
						}

					}
					else
					{
						aladdin->isJumping = true;
						aladdin->SetCurrentState(ALADDIN_JUMPING_FOWARD);
						if (level == 2)
						{

							aladdin->GetSpeed(vx, vy);
							aladdin->SetSpeed(vx*2, vy);

						}
					}
		}
	}
	else
	{
		if (!aladdin->isClimbing)
			aladdin->SetSpeed(0, vy);
		else
			aladdin->SetSpeed(0, 0);
		aladdin->isRunning = false;
		if (Game::GetInstance()->IsKeyDown(DIK_DOWN))
		{
			if (!aladdin->isClimbing)
			{
				if (!aladdin->isJumping && !(aladdin->isSitting &&aladdin->isAttacking))
				{
					aladdin->isSitting = true;
					aladdin->SetCurrentState(ALADDIN_IDLE_SIT);
				}

			}
			else
			{
				aladdin->SetSpeed(0, ALADDIN_CLIMB_SPEED);
				aladdin->SetCurrentState(ALADDIN_CLIMBING);
			}
		}
		else if (Game::GetInstance()->IsKeyDown(DIK_UP))
		{
			if (aladdin->isClimbing)
			{
				aladdin->SetSpeed(0, -ALADDIN_CLIMB_SPEED);
				aladdin->SetCurrentState(ALADDIN_CLIMBING);
			}
			else if (!aladdin->isJumping && !aladdin->isSitting && !aladdin->isAttacking)
			{
				aladdin->SetCurrentState(ALADDIN_IDLE_LOOK_UP);
			}
		}
		else if (Game::GetInstance()->IsKeyDown(DIK_C))
		{
			if (!aladdin->isJumping)
			{
				aladdin->isJumping = true;
				aladdin->SetCurrentState(ALADDIN_JUMPING);
			}
		}
		else
		{
			int curState = aladdin->GetCurrentState();
			if (curState == ALADDIN_IDLE1 || curState == ALADDIN_IDLE2 || curState == ALADDIN_IDLE3)
			{
				int tolFrame = aladdin->GetAnimations(curState)->GetCountFrame();
				int curFrame = aladdin->GetAnimations(curState)->GetCurrentFrame();
				if (curFrame == tolFrame - 1)
				{
					srand(time(NULL));
					int result = rand() % 3 + 1;
					switch (result)
					{
					case 1:
						aladdin->SetCurrentState(ALADDIN_IDLE1);
						break;
					case 2:
						aladdin->SetCurrentState(ALADDIN_IDLE2);
						break;
					case 3:
						aladdin->SetCurrentState(ALADDIN_IDLE3);
						break;
					}
				}
				else
					aladdin->SetCurrentState(curState);
			}
			else
			{
				aladdin->SetCurrentState(ALADDIN_IDLE1);
			}
		}
	}
}

void SceneGame::OnKeyDown(int KeyCode)
{
	DebugOut((wchar_t*)L"nhan key %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_V:
		DebugOut((wchar_t*)L"nhan key X");
		aladdin->isAttacking = true;
		if (aladdin->isJumping)
			aladdin->SetCurrentState(ALADDIN_JUMPING_ATTACKING);
		else if (aladdin->isClimbing)
			aladdin->SetCurrentState(ALADDIN_CLIMBING_ATTACKING);
		else if (aladdin->isRunning)
			aladdin->SetCurrentState(ALADDIN_RUNING_ATTACKING);
		else if (aladdin->isSitting)
			aladdin->SetCurrentState(ALADDIN_SITTING_ATTACKING);
		else if (aladdin->GetCurrentState() == ALADDIN_IDLE_LOOK_UP)
			aladdin->SetCurrentState(ALADDIN_STAYING_COMBO_ATTACKING);
		else aladdin->SetCurrentState(ALADDIN_STAYING_ATTACKING);
		break;
	case DIK_B:
		aladdin->isAttacking = true;
		if (aladdin->isJumping)
			aladdin->SetCurrentState(ALADDIN_JUMPING_ATTACKING_BY_APPLE);
		else if (aladdin->isClimbing)
			aladdin->SetCurrentState(ALADDIN_CLIMBING_ATTACKING_BY_APPLE);
		else if (aladdin->isRunning)
			aladdin->SetCurrentState(ALADDIN_RUNNING_ATTACKING_BY_APPLE);
		else if (aladdin->isSitting)
			aladdin->SetCurrentState(ALADDIN_SITTING_ATACKING_BY_APPLE);
		else aladdin->SetCurrentState(ALADDIN_STAYING_ATTACKING_BY_APPLE);
		break;
	case DIK_Q:
		aladdin->SetHealth(9);
		break;
	case DIK_W:
		aladdin->SetApplesCount(15);
		break;
	}

}

void SceneGame::OnKeyUp(int KeyCode)
{
}

void SceneGame::LoadResources()
{
	textures->LoadResources();
	map->SetMap(MAP1);
	map->LoadMap();
	camera->SetMap(map->GetMapWidth(), map->GetMapHeight());
	camera->SetPosition(0.0f, 0.0f);
	grid = Grid::GetInstance();
	grid->LoadGrid(MAP1);
	
	aladdin = new Aladdin();
	pointReset = NULL;
	aladdin->LoadResource();
	dyc = 0;

	// load resource cho foreground
	Sprites * sprites = Sprites::GetInstance();
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_RESOURCE_MAP1);
	sprites->Add(51056, 208, 13, 248, 357, texture);
	sprites->Add(51057, 528, 13, 560, 173, texture);
	sprites->Add(51058, 848, 13, 880, 748, texture);
	sprites->Add(51059, 977, 210, 1009, 402, texture);
	sprites->Add(51060, 1068, 210, 1146, 418, texture);
	texture = Textures::GetInstance()->Get(ID_TEX_RESOURCE_MAP1A);
	sprites->Add(51064, 220, 316, 739, 572, texture);
	texture = Textures::GetInstance()->Get(ID_TEX_BOSSBACKGROUND);
	sprites->Add(51065, 0, 0, 830, 450, texture);

	foreground = new Foreground();
	foreground->list_foregroundObject.push_back(new ForegroundObject(51056, 176, 768));
	foreground->list_foregroundObject.push_back(new ForegroundObject(51057, 497, 952));
	foreground->list_foregroundObject.push_back(new ForegroundObject(51058, 817, 377));
	foreground->list_foregroundObject.push_back(new ForegroundObject(51059, 1168, 920));
	foreground->list_foregroundObject.push_back(new ForegroundObject(51060, 2192, 65));
	// SetLevel(2);
	foregroundx = new ForegroundObject(51064, 0, 0, 519, 256);
	foregroundxboss = new ForegroundObject(51065, 0, 0, 830, 450);
	Sound::GetInstance()->Play(eSound::sound_Story);
}

void SceneGame::Update(DWORD dt)
{
	float x;
	float y;

	switch (level)
	{
	case 2:
		if (aladdin->GetHealth() < 0)
		{
			aladdin->SetHeart(aladdin->GetHeart()-1);
			if (aladdin->GetHeart() <= 0)
			{
				SetLevel(1);
				SceneManager::GetInstance()->SetScene(new SceneDealth());
				return;
			}
			else
			{
				aladdin->SetHealth(9);
				aladdin->SetPosition(20, 250);
			}
		}

		for (auto x : obj)
		{
			if (x->GetType() == JAFAR)
			{
				Jafar * e = (Jafar *)x;
				float ax, ay;
				aladdin->GetPosition(ax, ay);
				e->aladdinPoint.x = ax;
				e->aladdinPoint.y = ay;

				if (e->GetHealth() <= 0)
				{
					SetLevel(1);
					SceneManager::GetInstance()->SetScene(new SceneWin());
					return;
				}
				float ex, ey;
				e->GetPosition(ex, ey);

				if (ax < ex)
				{
					e->SetNx(-1);
					obj[9]->SetCurrentState(1);
					obj[10]->SetCurrentState(1);
					obj[11]->SetCurrentState(1);
					obj[12]->SetCurrentState(1);

				}
				else
				{
					e->SetNx(1);
					obj[5]->SetCurrentState(1);
					obj[6]->SetCurrentState(1);
					obj[7]->SetCurrentState(1);
					obj[8]->SetCurrentState(1);
				}
			}
			x->Update(dt);

		}
		aladdin->GetPosition(x, y);
		aladdin->Update(dt, &obj);
		
		camera->SetPosition(x - 140, y);
		break;
	case 1:
		grid->Update(dt);
		grid->GetObjects(obj);

		for (auto x : obj)
		{
			if (x->GetType() == ENEMYBAT)
			{
				EnemyBat * e = (EnemyBat *)x;
				float ax, ay;
				aladdin->GetPosition(ax, ay);
				e->aladdinPosition.x = ax;
				e->aladdinPosition.y = ay;
			}
			if (x->GetType() == ENEMYSKELETON)
			{
				EnemySkeleton * e = (EnemySkeleton *)x;
				float ax, ay;
				float ex, ey;
				aladdin->GetPosition(ax, ay);
				e->GetPosition(ex, ey);
				e->aladdinPoint.x = ax;
				e->aladdinPoint.y = ay;
				if (ax < ex)
					e->SetNx(-1);
				else
					e->SetNx(1);
			}
			x->Update(dt, &obj);
			if (x->GetType() == ENEMYFAT)
			{
				EnemyBig * e = (EnemyBig *)x;
				float x, y;
				aladdin->GetPosition(x, y);
				if (x < e->LeftMargin)
					e->SetNx(-1);
				if (x > e->RightMargin)
					e->SetNx(1);
			}
			if (x->GetType() == ENEMYTHIN)
			{
				EnemySmall * e = (EnemySmall *)x;
				float ax, ay;
				aladdin->GetPosition(ax, ay);
				if (ax < e->LeftMargin)
					e->SetNx(-1);
				if (ax > e->RightMargin)
					e->SetNx(1);
			}

		}
		// update aladdin
		aladdin->Update(dt, &obj);
		
		aladdin->GetPosition(x, y);

		// tạo hiệu ứng chuyển động của cam
		if (aladdin->isCollisionWithNextLevelPoint)
		{
			SetLevel(2);
			SceneManager::GetInstance()->SetScene(new SceneLevelCompleted());
			aladdin->isCollisionWithNextLevelPoint = false;
			return;
		}
		if (aladdin->GetCurrentState() == ALADDIN_IDLE_LOOK_UP)
		{
			if (dyc > -80)
				dyc -= 4;
		}
		else if (aladdin->isSitting)
		{
			if (dyc < 80)
				dyc += 4;
		}
		else
			if (dyc > 0)
				dyc -= 4;
			else if (dyc < 0)
				dyc += 4;
		camera->SetPosition(x - 140, y - 110 + dyc);

		if (aladdin->isCollsionWithRestartPoint)
		{
			if (pointReset == NULL)
				pointReset = new PointReset();

			vector<LPGAMEOBJECT> gridObject;
			grid->GetAllObject(gridObject);
			pointReset->SetPointReset(gridObject, aladdin);

			aladdin->isCollsionWithRestartPoint = false;
		}

		if (aladdin->GetHealth() <= 0)
		{
			aladdin->SetHeart(aladdin->GetHeart() - 1);

			if (aladdin->GetHeart() <= 0)
			{
				// isGameOver = true;
				Aladdin * a = aladdin;
				delete a;
				aladdin = new Aladdin();
				aladdin->LoadResource();
				grid->ResetState();
				if (pointReset != NULL)
				{
					delete pointReset;
					pointReset = NULL;
				}

				SceneManager::GetInstance()->SetScene(new SceneDealth());
				return;
			}
			else if (pointReset == NULL)
			{
				/*Aladdin * a = aladdin;
				delete a;
				aladdin = new Aladdin();*/
				aladdin->LoadResource();
				aladdin->SetPosition(100, 1000);
				grid->ResetState();
				aladdin->SetHealth(9);

			}
			else
			{
				vector<LPGAMEOBJECT> gridObject;
				grid->GetAllObject(gridObject);
				pointReset->ResetState(gridObject, aladdin);
				aladdin->SetHealth(9);
			}
		}
		break;
	}
	
	Board::GetInstance()->Update(dt, aladdin->GetHealth(), aladdin->GetHeart(), aladdin->GetScore(), aladdin->GetRedJewelCount(), aladdin->GetApplesCount());
}

void SceneGame::Render()
{
	int oCount;
	float a;
	float b;
	int w;
	int h;
	switch (level)
	{
	case 1:
		map->DrawMap();

		// vẽ object trong grid
		for (int i = 0; i < obj.size(); i++)
		{
			obj[i]->Render();
		}
		aladdin->Render();

		oCount = 0;

		// render lop tren cung
		for (int i = 0; i < foreground->list_foregroundObject.size(); i++)
			foreground->list_foregroundObject[i]->Render();

		if (foregroundx->x > Camera::GetInstance()->GetXCam() + Camera::GetInstance()->GetWidth())
			foregroundx->x -= foregroundx->width;
		if (foregroundx->x + foregroundx->width < Camera::GetInstance()->GetXCam())
			foregroundx->x += foregroundx->width;
		if (foregroundx->y > Camera::GetInstance()->GetYCam() + Camera::GetInstance()->GetHeight())
			foregroundx->y -= foregroundx->height;
		if (foregroundx->y + foregroundx->height < Camera::GetInstance()->GetYCam())
			foregroundx->y += foregroundx->height;

		a = foregroundx->x;
		b = foregroundx->y;
		w = foregroundx->width;
		h = foregroundx->height;

		foregroundx->RenderWithEffect(a, b - h);
		foregroundx->RenderWithEffect();
		foregroundx->RenderWithEffect(a, b + h);
		foregroundx->RenderWithEffect(a, b + 2 * h);

		foregroundx->RenderWithEffect(a + w, b - h);
		foregroundx->RenderWithEffect(a + w, b);
		foregroundx->RenderWithEffect(a + w, b + h);
		foregroundx->RenderWithEffect(a + w, b + 2 * h);

		foregroundx->RenderWithEffect(a - w, b - h);
		foregroundx->RenderWithEffect(a - w, b);
		foregroundx->RenderWithEffect(a - w, b + h);
		foregroundx->RenderWithEffect(a - w, b + 2 * h);
		Board::GetInstance()->Render();
		break;
	case 2:
		//Sprites::GetInstance()->Get(51065)->Draw(0,0);
		map->DrawMap();
		for (int i = 0; i < obj.size(); i++)
		{
			obj[i]->Render();
		}
		aladdin->Render();
		aladdin->SetGravity(0.0012);
		Board::GetInstance()->Render();
		break;
	}
	
}

void SceneGame::SetLevel(int level)
{
	obj.clear();
	Sprites * sprites = Sprites::GetInstance();
	GameObject * o;
	switch (level)
	{
	case 1:
		this->level = 1;
		aladdin->SetHealth(9);
		aladdin->SetApplesCount(15);
		aladdin->SetHeart(3);
		aladdin->SetScore(0);
		aladdin->SetPosition(100, 1000);
		map->SetMap(MAP1);
		map->LoadMap();
		aladdin->SetGravity(ALADDIN_GRAVITY);
		camera->SetMap(map->GetMapWidth(), map->GetMapHeight());
		camera->SetPosition(0.0f, 0.0f);
		if (pointReset != nullptr || pointReset != NULL)
			delete pointReset;
		pointReset = NULL;
		Sound::GetInstance()->StopAll();
		Sound::GetInstance()->Play(eSound::sound_Story);
		grid->ResetState();
		break;
	case 2:
		this->level = 2;
		map->SetMap(MAP2);
		map->LoadMap();
		
		camera->SetMap(map->GetMapWidth(), map->GetMapHeight());
		camera->SetPosition(0.0f, 0.0f);
		o = new Brick(3, 260, 300, 105, 16, oType::BRICK);
		obj.push_back(o);
		o = new Brick(4, 470, 300, 105, 16, oType::BRICK);
		obj.push_back(o);
		o = new Brick(0, 0, 360, 832, 16, oType::BRICK);
		obj.push_back(o);
		o = new Wall(1, 0, 0, 4, 448, oType::WALL);
		obj.push_back(o);
		o = new Wall(2, 790, 0, 4, 448, oType::WALL);
		obj.push_back(o);
		aladdin->SetPosition(20, 250);

		o = new Apple(5, 296, 265, 10, 10, oType::APPLE);
		obj.push_back(o);
		o = new Apple(6, 286, 278, 10, 10, oType::APPLE);
		obj.push_back(o);
		o = new Apple(7, 311, 278, 10, 10, oType::APPLE);
		obj.push_back(o);
		o = new Apple(8, 296, 288, 10, 10, oType::APPLE);
		obj.push_back(o);

		o = new Apple(9, 505, 265, 10, 10, oType::APPLE);
		obj.push_back(o);
		o = new Apple(10, 496, 278, 10, 10, oType::APPLE);
		obj.push_back(o);
		o = new Apple(11, 517, 278, 10, 10, oType::APPLE);
		obj.push_back(o);
		o = new Apple(12, 505, 288, 10, 10, oType::APPLE);
		obj.push_back(o);
		o = new Jafar();
		obj.push_back(o);
		Sound::GetInstance()->StopAll();
		Sound::GetInstance()->Play(eSound::sound_BossTune);
		break;
	default:
		break;
	}
}

SceneGame::SceneGame()
{
	level = 1;
	textures = Textures::GetInstance();
	camera = Camera::GetInstance();
	map = Map::GetInstance();
	LoadResources();
	isGameOver = false;
}

SceneGame::~SceneGame()
{
	delete aladdin;
	delete pointReset;
	delete foreground;
}