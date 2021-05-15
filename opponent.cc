#include "opponent.h"
#include "game_element.h"

//@breif: Function that draws the image of "opponent"
//@param: takes a refrence of the image.
//@returns: Void type.
void Opponent::Draw(graphics::Image &opponentimage) {
  graphics::Image villian;
  villian.Load("opponent.bmp");
  for (int i = 0; i < GetWidth(); i++) {
    for (int j = 0; j < GetHeight(); j++) {
      opponentimage.SetColor(GetX() + i, GetY() + j, villian.GetColor(i, j));
    }
  }
}

void Opponent::Move(const graphics::Image &opponentimage) {
  SetX(GetX() + 1);
  SetY(GetY() + 1);

  if (IsOutOfBounds(opponentimage)) {
    SetIsActive(false);
  } else {
    SetIsActive(true);
  }
}

std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  std::unique_ptr<OpponentProjectile> OpponentProjectile_ =
      std::make_unique<OpponentProjectile>(GetX(), GetY());
  counter++;
  if (counter < 10) {
    return nullptr;
  } else {
    counter = 0;
    return std::move(OpponentProjectile_);
  }
}

//@brief: Function that draws the opponent projectile and sets its width and
// height to 50.
//@param: Takes a Reference image
//@return: void, return nothing
void OpponentProjectile::Draw(graphics::Image &o_projectileimage) {
  graphics::Image beam;
  beam.Load("o_projectile.bmp");
  for (int i = 0; i < GetWidth(); i++) {
    for (int j = 0; j < GetHeight(); j++) {
      o_projectileimage.SetColor(GetX() + i, GetY() + j, beam.GetColor(i, j));
    }
  }
}

void OpponentProjectile::Move(const graphics::Image &o_projectileimage) {
  SetX(GetX() + 3);
  SetY(GetY() + 3);

  if (IsOutOfBounds(o_projectileimage)) {
    SetIsActive(false);
  } else {
    SetIsActive(true);
  }
}
