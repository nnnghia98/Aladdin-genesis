#include "Characters.h"

Characters * Characters::instance = NULL;

Characters::Characters()
{
	LPDIRECT3DTEXTURE9 texture = Textures::GetInstance()->Get(ID_TEX_ALADDIN);
	Sprites * sprites = Sprites::GetInstance();
	sprites->Add(-1, 359, 3594, 366, 3601, texture);
	sprites->Add(-2, 371, 3594, 374, 3601, texture);
	sprites->Add(-3, 379, 3594, 384, 3601, texture);
	sprites->Add(-4, 389, 3594, 393, 3601, texture);
	sprites->Add(-5, 398, 3594, 404, 3601, texture);
	sprites->Add(-6, 409, 3594, 414, 3601, texture);
	sprites->Add(-7, 419, 3594, 425, 3601, texture);
	sprites->Add(-8, 430, 3594, 435, 3601, texture);
	sprites->Add(-9, 439, 3594, 444, 3601, texture);
	sprites->Add(-10, 449, 3594, 455, 3601, texture);
	sprites->Add(-11, 359, 3566, 366, 3573, texture);
	sprites->Add(-12, 371, 3566, 378, 3573, texture);
	sprites->Add(-13, 383, 3566, 390, 3573, texture);
	sprites->Add(-14, 395, 3566, 402, 3573, texture);
	sprites->Add(-15, 407, 3566, 414, 3573, texture);
	sprites->Add(-16, 419, 3566, 426, 3573, texture);
	sprites->Add(-17, 431, 3566, 438, 3573, texture);
	sprites->Add(-18, 443, 3566, 450, 3573, texture);
	sprites->Add(-19, 455, 3566, 458, 3574, texture);
	sprites->Add(-20, 463, 3566, 467, 3574, texture);
	sprites->Add(-21, 472, 3566, 479, 3574, texture);
	sprites->Add(-22, 484, 3566, 491, 3573, texture);
	sprites->Add(-23, 496, 3566, 503, 3573, texture);
	sprites->Add(-24, 360, 3581, 367, 3588, texture);
	sprites->Add(-25, 372, 3581, 379, 3588, texture);
	sprites->Add(-26, 384, 3581, 391, 3588, texture);
	sprites->Add(-27, 396, 3581, 403, 3589, texture);
	sprites->Add(-28, 408, 3581, 415, 3589, texture);
	sprites->Add(-29, 420, 3581, 426, 3589, texture);
	sprites->Add(-30, 431, 3581, 437, 3588, texture);
	sprites->Add(-31, 442, 3581, 449, 3589, texture);
	sprites->Add(-32, 454, 3581, 461, 3588, texture);
	sprites->Add(-33, 466, 3581, 473, 3588, texture);
	sprites->Add(-34, 487, 3581, 494, 3588, texture);
	sprites->Add(-35, 490, 3581, 497, 3588, texture);
	sprites->Add(-36, 502, 3581, 508, 3588, texture);
	sprites->Add(-37, 459, 3599, 461, 3601, texture);
	sprites->Add(-38, 514, 3581, 518, 3589, texture);
	sprites->Add(-39, 520, 3581, 524, 3589, texture);
}


Characters * Characters::GetInstance()
{
	if (instance == NULL)
		instance = new Characters();
	return instance;
}

Characters::~Characters()
{
}
