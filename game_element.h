#include "cpputils/graphics/image.h"
#include <iostream>

#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H
class GameElement {
 private:
  int x_;
  int y_;

  int width_;
  int height_;

  bool is_active = true;

 public:
  // accessors and mutatators
  int GetX() const;
  int GetY() const;

  void SetX(int x);
  void SetY(int y);

  // accessors
  int GetWidth();
  int GetHeight();

  // default constructor
  GameElement() : x_(0), y_(0), width_(50), height_(50) {}

  // nondefault constructor:
  GameElement(int x, int y, int width, int height)
      : x_(x), y_(y), width_(width), height_(height) {}

  //@breif: function draws a 5x5 black rectangle at the game elements current x
  // and y position.
  //@param: accepts a graphics::Image Refererence
  //@returns: void
  virtual void Draw(graphics::Image &Rect) = 0;

  //@brief: pure virtual function that all the classes will derive from.
  //@param: accepts a const graphics::Image
  virtual void Move(const graphics::Image &move) = 0;

  // setters and getters for IsActive
  bool GetIsActive();
  void SetIsActive(bool IsActive);

  //@breif: function should check if the GameElement intersects with a
  // parameter.
  //@param: accepts a reference to GameElement
  //@returns: true if the game elemenet intersects with a parameter.
  bool IntersectsWith(GameElement *intersect);

  //@brief: function checks to see if the GameElement is outside the bounds of
  // the game screen.
  //@param:takes in a graphics::Image object
  //@return: true if the GameElement is outside the bounds of the game screen,
  // otherwise function should return false.
  bool IsOutOfBounds(const graphics::Image &bounds);
};
#endif
