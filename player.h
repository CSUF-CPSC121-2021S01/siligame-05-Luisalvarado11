#include "cpputils/graphics/image.h"
#include "opponent.h"
#include <iostream>

#ifndef PLAYER_H
#define PLAYER_H

class Player : public GameElement {
 public:
  Player() : Player(0, 0) {}
  Player(int x, int y) : GameElement(x, y, 50, 50) {}

  void Draw(graphics::Image &playerimage) override;
  void Move(const graphics::Image &playerimage) override;
};

class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile() : PlayerProjectile(0, 0) {}
  PlayerProjectile(int x, int y) : GameElement(x, y, 5, 5) {}

  void Draw(graphics::Image &p_projectileimage) override;
  void Move(const graphics::Image &p_projectileimage) override;
};
#endif
