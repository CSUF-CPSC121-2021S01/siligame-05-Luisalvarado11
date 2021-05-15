#include "game_element.h"
#include <iostream>

int GameElement::GetX() const { return x_; }
int GameElement::GetY() const { return y_; }

void GameElement::SetX(int x) { x_ = x; }
void GameElement::SetY(int y) { y_ = y; }

int GameElement::GetWidth() { return width_; }
int GameElement::GetHeight() { return height_; }

void GameElement::Draw(graphics::Image &Rect) {
  Rect.DrawRectangle(x_, y_, width_, height_, 0, 0, 0);
}

bool GameElement::GetIsActive() { return is_active; }
void GameElement::SetIsActive(bool IsActive) { is_active = IsActive; }

bool GameElement::IntersectsWith(GameElement *intersect) {
  if (GetX() > intersect->GetX() + intersect->GetWidth() ||
      intersect->GetX() > GetX() + GetWidth() ||
      GetY() > intersect->GetY() + intersect->GetHeight() ||
      intersect->GetY() > GetY() + GetHeight()) {
    return false;
  }
  return true;
}

bool GameElement::IsOutOfBounds(const graphics::Image &bounds) {
  if ((GetX() < 0 || GetX() + GetWidth() > bounds.GetWidth()) ||
      (GetY() < 0 || GetY() + GetHeight() > bounds.GetHeight())) {
    return true;
  } else {
    return false;
  }
}
