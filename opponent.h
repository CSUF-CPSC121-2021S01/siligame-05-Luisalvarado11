#include "cpputils/graphics/image.h"
#include "game_element.h"
#include <iostream>
#include <memory>

#ifndef OPPONENT_H
#define OPPONENT_H
class OpponentProjectile : public GameElement {
 public:
  OpponentProjectile() : OpponentProjectile(0, 0) {}
  OpponentProjectile(int x, int y) : GameElement(x, y, 5, 5) {}

  void Draw(graphics::Image &o_projectileimage) override;
  void Move(const graphics::Image &o_projectileimage) override;
};

class Opponent : public GameElement {
 private:
  int counter = 0;

 public:
  Opponent() : Opponent(0, 0) {}
  Opponent(int x, int y) : GameElement(x, y, 50, 50) {}

  void Draw(graphics::Image &opponentimage) override;
  void Move(const graphics::Image &opponentimage) override;
  std::unique_ptr<OpponentProjectile> LaunchProjectile();
};
#endif
