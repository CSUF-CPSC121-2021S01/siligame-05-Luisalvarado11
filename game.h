#include "cpputils/graphics/image_event.h"
#include "game_element.h"
#include "opponent.h"
#include "player.h"
#include <iostream>
#include <vector>

#ifndef GAME_H
#define GAME_H

class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 private:
  graphics::Image GameBoard_;
  std::vector<std::unique_ptr<Opponent>> Villian_;
  std::vector<std::unique_ptr<OpponentProjectile>> Beam_;
  std::vector<std::unique_ptr<PlayerProjectile>> Hero_Projectile_;
  Player Hero_;

  int width_;
  int height_;
  int score_ = 0;
  bool lost_;

 public:
  // default constructor and non-default constructor
  Game() : GameBoard_(800, 600) {}
  Game(int width, int height)
      : width_(width), height_(height), GameBoard_(width, height) {}

  std::vector<std::unique_ptr<Opponent>> &GetOpponents();
  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles();
  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles();
  Player &GetPlayer();
  graphics::Image &GetGameScreen();

  void CreateOpponents();
  void CreateOpponentProjectiles();
  void CreatePlayerProjectiles();
  void Init();
  void UpdateScreen();
  void Start();

  int GetScore();
  bool HasLost();

  // added part 4
  //@breif: Function should call the move function of every Opponent,
  // OpponentProjectile, and PlayerProjectile object if it is active
  //@param: does not accept any parameters
  //@return: returns void
  void MoveGameElements();

  void LaunchProjectiles();

  //@breif: Function deactivates opponents that intersect with the player and
  // player projectiles that intersect with the opponents and players.
  //@param: function does not accept any parameters.
  //@return: nothing, void
  void FilterIntersections();

  void RemoveInactive();

  //@breif:Function will be called everytime you move or click the mouse and
  // will be used to control the player. The function accepts a
  // graphics::MouseEvent object that describes the action.
  //@param: nothing
  //@return void.
  void OnAnimationStep();

  //@breif: FUnction will be called every time you move or click the mouse and
  // will be used to control the player.
  //@param:accepts a graphics::MouseEvent object
  //@return: void type. returns a graphics::MouseAction enumeration that
  // indicates whether the mouse was moved.
  void OnMouseEvent(const graphics::MouseEvent &mouse);
};
#endif
