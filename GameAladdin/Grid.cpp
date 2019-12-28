#include "Grid.h"
#include "NextLevelPoint.h"

Grid * Grid::instance = NULL;

void Grid::AddObject(GameObject * gobj)
{
	if (gobj->GetType() == ENEMYBAT)
	{
		for (int i = 0; i < rows*columns; i++)
			grid[i]->object.push_back(gobj);
	}
	Point p1;
	float x;
	float y;
	gobj->GetPosition(x, y);
	p1.x = (int)x;
	p1.y = (int)y;
	Point p2;
	int w;
	int h;
	gobj->GetSize(w, h);
	p2.x = (int)x + w;
	p2.y = (int)y + h;
	int c1 = GetIdCellContainPoint(p1);
	int c2 = GetIdCellContainPoint(p2);

	int cs = c1 % columns; // column start
	int ce = c2 % columns; // column end
	int rs = c1 / columns; // row start
	int re = c2 / columns; // row end

	for (int i = rs; i <= re; i++)
	{
		for (int j = cs; j <= ce; j++)
		{
			grid[i*columns + j]->object.push_back(gobj);
		}
	}
}

Grid::Grid()
{
	rows = 0;
	columns = 0;
}

Grid * Grid::GetInstance()
{
	if (instance == NULL)
		instance = new Grid();
	return instance;
}

Cell * Grid::GetCell(int id)
{
	return grid[id];
}

void Grid::LoadGrid(int idMap)
{
	// delete dữ liệu grid cũ nếu có
	for (int i = 0; i < columns * rows; i++)
	{
		delete grid[i];
	}
	grid.clear();

	string path;
	switch (idMap) {
	case MAP1:
		path = "Resources/grid/grid1.txt";
		break;
	case MAP2:
		path = "Resources/grid/grid2.txt";
		break;
	}

	ifstream input = ifstream(path, ios::in);
	// Lấy dữ liệu hàng đầu tiên
	input >> columns;
	input >> rows;
	input >> cellWidth;
	input >> cellHeight;

	int totalCells = columns * rows;

	// Khởi tạo cell, đọc dữ liệu của từng cell lên
	int id;
	int x;
	int y;
	for (int i = 0; i < totalCells; i++)
	{
		input >> id >> x >> y;
		Cell * cell = new Cell(id, x, y);
		grid[id] = cell;
	}

	int type;
	int width;
	int height;
	oType obj;
	int lm, rm;
	while (!input.eof())
	{
		input >> id;
		if (id == -1)
			break;
		input >> type >> x >> y >> width >> height;
		GameObject * gobj = NULL;
		switch (type)
		{
		case WALL:
			gobj = new Wall(id, x, y, width, height, WALL);
			break;
		case BRICK:
			gobj = new Brick(id, x, y, width, height, BRICK);
			break;
		case ROPE:
			gobj = new Rope(id, x, y, width, height, ROPE);
			break;
		case APPLE:
			gobj = new Apple(id, x, y, width, height, APPLE);
			break;
		case MOVINGBRICK:
			gobj = new MovingBrick(id, x, y, width, height, MOVINGBRICK);
			break;
		case ARROW:
			gobj = new Arrow(id, x, y, width, height, ARROW);
			break;
		case REDJEWEL:
			gobj = new RedJewel(id, x, y, width, height, REDJEWEL);
			break;
		case GENIE:
			gobj = new Genie(id, x, y, width, height, GENIE);
			break;
		case HEART:
			gobj = new Heart(id, x, y, width, height, HEART);
			break;
		case RESTARTPOINT:
			gobj = new RestartPoint(id, x, y, width, height, RESTARTPOINT);
			break;
		case BOB:
			gobj = new Bob(id, x, y, width, height, BOB);
			break;
		case ENEMYFAT:
			input >> lm >> rm;
			gobj = new EnemyFat(id, x, y, width, height, ENEMYFAT, lm, rm);
			break;
		case ENEMYTHIN:
			input >> lm >> rm;
			gobj = new EnemyThin(id, x, y, width, height, ENEMYTHIN, lm, rm);
			break;
		case ENEMYBAT:
			gobj = new EnemyBat(id, x, y, width, height, ENEMYBAT);
			break;
		case ENEMYSKELETON:
			gobj = new EnemySkeleton(id, x, y, width, height, ENEMYSKELETON);
			break;
		case NEXTLEVELPOINT:
			gobj = new NextLevelPoint(id, x, y);
		}
		AddObject(gobj);
	}
}

void Grid::Update(DWORD dt)
{
	Camera * cam = Camera::GetInstance();

	Point a;
	a.x = (int)cam->GetXCam();
	a.y = (int)cam->GetYCam();

	Point b;
	b.x = (int)cam->GetXCam() + cam->GetWidth();
	b.y = (int)cam->GetYCam() + cam->GetHeight();

	int c1 = GetIdCellContainPoint(a);
	int c2 = GetIdCellContainPoint(b);

	if (c1 == -1 || c2 == -1) {
		//OutputDebugString(L"Grid:Camera nam ngoai grid\n");
		return;
	}
	cellShowing.clear();

	// Thêm cell hiển thị vào cellShowing
	// Kết thúc đoạn code dưới sẽ có danh sách id những cell đang nằm trong camera
	int cs = c1 % columns; // column start
	int ce = c2 % columns; // column end
	int rs = c1 / columns; // row start
	int re = c2 / columns; // row end

	for (int i = rs; i <= re; i++)
	{
		for (int j = cs; j <= ce; j++)
		{
			cellShowing.push_back(i*columns + j);
		}
	}
	// Update các đối tượng trong Grid
}

int Grid::GetIdCellContainPoint(Point p)
{
	int total = rows * columns;
	for (int id = 0; id < total; id++)
	{
		if (grid[id]->isCheckContainPoint(p))
			return id;
	}
	return -1;
}

void Grid::GetObjects(vector<LPGAMEOBJECT>& obj)
{
	obj.clear();
	unordered_map<int, LPGAMEOBJECT> listObjTemp;
	listObjTemp.clear();
	int s = cellShowing.size();
	for (int i = 0; i < s; i++)
	{
		Cell * c = GetCell(cellShowing[i]);
		int sCell = c->object.size();
		for (int j = 0; j < sCell; j++)
		{
			if (sCell > 0)
				if (listObjTemp[c->object[j]->GetId()] == nullptr)
				{
					listObjTemp[c->object[j]->GetId()] = c->object[j];
					obj.push_back(c->object[j]);
				}
		}
	}
}

void Grid::GetAllObject(vector<LPGAMEOBJECT>& obj)
{
	for (int i = 0; i < rows * columns; i++)
	{
		Cell * cell = GetCell(i);
		for (int j = 0; j < cell->object.size(); j++)
		{
			obj.push_back(cell->object[j]);
		}
	}
}

void Grid::ResetState()
{
	for (int i = 0; i < rows * columns; i++)
	{
		Cell * cell = GetCell(i);
		for (int j = 0; j < cell->object.size(); j++)
		{
			cell->object[j]->SetCurrentState(1);
			if (cell->object[j]->GetType() == oType::ENEMYTHIN
				|| cell->object[j]->GetType() == oType::ENEMYFAT)
				cell->object[j]->SetHealth(2);
			if (cell->object[j]->GetType() == oType::ENEMYBAT)
				cell->object[j]->SetHealth(1);
		}
	}
}

Grid::~Grid()
{
	for (int i = 0; i < columns * rows; i++)
	{
		delete grid[i];
	}
	grid.clear();
	if (instance != NULL)
		delete instance;
}