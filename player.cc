#include "player.h"
#include <iostream>
#include "cpputils/graphics/image.h"
#include "opponent.h"

//@breif: Function that draws the Image, based on its width(50) and height(50);
//@param: Takes an Referance Image
//@return: void
void Player::Draw(graphics::Image &playerimage) {
  graphics::Image Hero;
  Hero.Load("player.bmp");
  for (int i = 0; i < GetWidth(); i++) {
    for (int j = 0; j < GetHeight(); j++) {
      playerimage.SetColor(GetX() + i, GetY() + j, Hero.GetColor(i, j));
    }
  }
}

void Player::Move(const graphics::Image &playerimage) {}

//@breif: Function that draws the Image, based on its width(50) and height(50);
//@param: Takes an Referance Image
//@return: void
void PlayerProjectile::Draw(graphics::Image &p_projectileimage) {
  graphics::Image Hero_projectile;
  Hero_projectile.Load("p_projectile.bmp");
  for (int i = 0; i < GetWidth(); i++) {
    for (int j = 0; j < GetHeight(); j++) {
      p_projectileimage.SetColor(GetX() + i, GetY() + j,
                                 Hero_projectile.GetColor(i, j));
    }
  }
}

void PlayerProjectile::Move(const graphics::Image &p_projectileimage) {
  SetX(GetX() - 3);
  SetY(GetY() - 3);

  if (IsOutOfBounds(p_projectileimage)) {
    SetIsActive(false);
  } else {
    SetIsActive(true);
  }
}
