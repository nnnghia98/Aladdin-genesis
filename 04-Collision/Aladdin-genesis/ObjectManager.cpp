#include "ObjectManager.h"
#include "string.h"

ObjectManager::ObjectManager()
{
}
ObjectManager::~ObjectManager()
{

	delete map;
	delete viewport;
}

//Load Game
void ObjectManager::Init(Graphic* graphic)
{

	this->sound = new Sound(graphic->GetHwnd());
	this->sound->Init_DirectSound();
	soundGame = this->sound->LoadSound("./Sound/PrinceAli.wav");



	//
	spriteAladdin = new Sprite(graphic, "Aladdin_Sprite.png", D3DCOLOR_XRGB(255, 0, 255));
	infoAlddin = new SpriteSheet("Aladdin-Animations.xml");

	spriteBrick = new Sprite(graphic, "./Resource Files/Brick.png", D3DCOLOR_XRGB(163, 73, 164));
	infoBrick = new SpriteSheet("./Resource Files/Brickxml.xml");
	//
	spritePendu = new Sprite(graphic, "./Resource Files/pendulum.png", D3DCOLOR_XRGB(163, 73, 164));
	infoPendu = new SpriteSheet("./Resource Files/ballxml.xml");

	spriteDrill = new Sprite(graphic, "./Resource Files/arrow.png", D3DCOLOR_XRGB(163, 73, 164));
	infoDrill = new SpriteSheet("./Resource Files/arrow.xml");

	spriteBat = new Sprite(graphic, "./Resource Files/Batxml.png", D3DCOLOR_XRGB(163, 73, 164));
	infoBat = new SpriteSheet("./Resource Files/Batsprite.xml");

	spriteGuard = new Sprite(graphic, "./Resource Files/Guard.png", D3DCOLOR_XRGB(163, 73, 164));
	infoGuard = new SpriteSheet("./Resource Files/Guard.xml");


	pendu = new pendulum(spritePendu, infoPendu, D3DXVECTOR2(900, 180));

	brick = new Brick(spriteBrick, infoBrick, D3DXVECTOR2(350, 621));

	drill = new Drill(spriteDrill, infoDrill, D3DXVECTOR2(320, 521));
	brick = new Brick(spriteBrick, infoBrick, D3DXVECTOR2(350,621));
	brick2 = new Brick(spriteBrick, infoBrick, D3DXVECTOR2(600, 100));

	

	point = new PointMap();

	brick2->setstate(Brick::close);
	aladin = new Aladdin(spriteAladdin, infoAlddin);

	bat = new Bat(spriteBat, infoBat, D3DXVECTOR2(-100, 621), aladin);
	guard = new Guard(spriteGuard, infoGuard, D3DXVECTOR2(650, 80), aladin);
	guard->GetState();


	viewport = new Viewport(0, 1152);
	map = new Map(graphic, MapXML, TileSetPNG);
	map2 = new Map(graphic, MapXML2, TileSetPNG);
	map3 = new Map3D(graphic, MapXML3, TileSetPNG3);
	grid = new Grid();
	TiXmlDocument doc(GridXML);
	if (!doc.LoadFile())
	{
		MessageBox(NULL, "Can't load QuadTree.xml file", "Error", MB_OK);
		return;
	}
	TiXmlElement* root = doc.RootElement();
	ReadGrid(root, grid);
	objects = grid->GetCell(2, 1)->objects;
	prePosView = viewport->GetPosition();
	prePosAla = point->GetPosition();

}

//Update Game
void ObjectManager::Update(float dt, Keyboard* keyboard)
{
	aladin->ChangeAnimation(dt, keyboard);
	//aladin->SetVelocityY(-1);
	//Kiểm tra dịch chuyển
	if (prePosView != viewport->GetPosition())
	{
		prePosView = viewport->GetPosition();

	}

	point->Update(dt, keyboard);
	
	aladin->Update(dt, keyboard);

	printf("x = %f \t y= %f\n ", aladin->GetPosition().x, aladin->GetPosition().y);
	//
	//brick->SetPosition(D3DXVECTOR2(aladin->GetPosition().x,aladin->GetPosition().y-45));

	brick->Update(dt, keyboard);
	brick2->Update(dt, keyboard);
	pendu->Update(dt, keyboard);

	pendu->Update(dt,keyboard);
	drill->Update(dt, keyboard);

	guard->Update(dt, keyboard);

	bat->Update(dt, keyboard);
	for (auto o : objects) {
		o->Update(dt, keyboard);
	}
	viewport->Update(dt, keyboard, aladin->GetPosition(), aladin->GetVelocity(), map->listStage);
	

	sound->LoopSound(soundGame);
}

//Vẽ
void ObjectManager::Render()
{
	map->Render(viewport);

	brick->Render(viewport);
	brick2->Render(viewport);
	pendu->Render(viewport);

	guard->Render(viewport);

	for (auto o : objects) {
		o->Render(viewport);
	}

	drill->Render(viewport);

	aladin->Render(viewport);
	bat->Render(viewport);
	map2->Render(viewport);
	map3->Render(viewport, D3DXVECTOR2(-50, 70),point->GetPosition());
}

void ObjectManager::ReadGrid(TiXmlElement * root, Grid * grid)
{
	if (!root)
		return;
	TiXmlElement *cell = root->FirstChildElement();

	while (cell != NULL)
	{
		float x, y, numobject;
		cell->QueryFloatAttribute("x", &x);
		cell->QueryFloatAttribute("y", &y);
		cell->QueryFloatAttribute("numobject", &numobject);
		if (numobject > 0) {
			TiXmlElement *obj = cell->FirstChildElement();
			for (int i = 0; i < numobject; i++) {
				string name = (char*)obj->Attribute("name");
				float posX, posY;
				int alow = 0;
				obj->QueryIntAttribute("alow", &alow);
				obj->QueryFloatAttribute("x", &posX);
				obj->QueryFloatAttribute("y", &posY);
				Brick* bat2 = new Brick(spriteBrick, infoBrick, D3DXVECTOR2(posX, posY));
				bat2->SetName(name);
				if (alow) {
					bat2->setstate(Brick::oppen);
				}
				else {
					bat2->setstate(Brick::close);
				}


				grid->GetCell(x, y)->Add(bat2);
				obj = obj->NextSiblingElement();
			}
		}

		cell = cell->NextSiblingElement();
	}


}



