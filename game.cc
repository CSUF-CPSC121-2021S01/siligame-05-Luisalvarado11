#include "game.h"
#include <iostream>
#include <vector>

std::vector<std::unique_ptr<Opponent>> &Game::GetOpponents() {
  return Villian_;
}
std::vector<std::unique_ptr<OpponentProjectile>>
    &Game::GetOpponentProjectiles() {
  return Beam_;
}
std::vector<std::unique_ptr<PlayerProjectile>> &Game::GetPlayerProjectiles() {
  return Hero_Projectile_;
}
Player &Game::GetPlayer() { return Hero_; }
graphics::Image &Game::GetGameScreen() { return GameBoard_; }

int Game::GetScore() { return score_; }
bool Game::HasLost() { return lost_; }

void Game::CreateOpponents() {
  Opponent Villian;
  Villian.SetX(345);
  Villian.SetY(75);
  Villian_.push_back(std::make_unique<Opponent>(Villian));
}

void Game::Init() {
  Hero_.SetX(350);
  Hero_.SetY(500);

  GameBoard_.AddMouseEventListener(*this);
  GameBoard_.AddAnimationEventListener(*this);
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < Villian_.size(); i++) {
    std::unique_ptr<OpponentProjectile> Opponent_P =
        Villian_[i]->LaunchProjectile();
    if (Opponent_P != nullptr) {
      Beam_.push_back(std::move(Opponent_P));
    }
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < Villian_.size(); i++) {
    if (Villian_[i]->GetIsActive() && Hero_.GetIsActive() &&
        Hero_.IntersectsWith(Villian_[i].get())) {
      Villian_[i]->SetIsActive(false);
      Hero_.SetIsActive(false);
      lost_ = true;
    } else {
      for (int j = 0; j < Hero_Projectile_.size(); j++) {
        if (Beam_[i]->GetIsActive() && Hero_Projectile_[j]->GetIsActive() &&
            Hero_Projectile_[j]->IntersectsWith(Villian_[i].get())) {
          Villian_[i]->SetIsActive(false);
          Hero_Projectile_[j]->SetIsActive(false);
          if (Hero_.GetIsActive()) {
            score_ += 1;
          }
        }
      }
    }
  }
  for (int i = 0; i < Beam_.size(); i++) {
    if (Beam_[i]->GetIsActive() && Hero_.GetIsActive() &&
        Hero_.IntersectsWith(Beam_[i].get())) {
      Beam_[i]->SetIsActive(false);
      Hero_.SetIsActive(false);
      lost_ = true;
    }
  }
}

void Game::UpdateScreen() {
  GameBoard_.DrawRectangle(0, 0, 800, 600, 255, 255, 255);
  GameBoard_.DrawText(10, 10, "Score: " + std::to_string(score_), 25, 0, 0, 0);
  GameBoard_.DrawText(250, 250, "GAME OVER", 70,
                      graphics::Color(255, 255, 255));

  if (Hero_.GetIsActive()) {
    Hero_.Draw(GameBoard_);
  }

  for (int i = 0; i < Villian_.size(); i++) {
    if (Villian_[i]->GetIsActive()) {
      Villian_[i]->Draw(GameBoard_);
    }
  }

  for (int i = 0; i < Beam_.size(); i++) {
    if (Beam_[i]->GetIsActive()) {
      Beam_[i]->Draw(GameBoard_);
    }
  }

  for (int i = 0; i < Hero_Projectile_.size(); i++) {
    if (Hero_Projectile_[i]->GetIsActive()) {
      Hero_Projectile_[i]->Draw(GameBoard_);
    }
  }
}

void Game::MoveGameElements() {
  for (int i = 0; i < Villian_.size(); i++) {
    Villian_[i]->Move(GameBoard_);
  }
  for (int j = 0; j < Beam_.size(); j++) {
    Beam_[j]->Move(GameBoard_);
  }
  for (int i = 0; i < Hero_Projectile_.size(); i++) {
    Hero_Projectile_[i]->Move(GameBoard_);
  }
}

void Game::RemoveInactive() {
  for (int i = 0; i < Villian_.size(); i++) {
    if (Villian_[i]->GetIsActive() == false) {
      Villian_.erase(Villian_.begin() + i);
      i--;
    }
  }
  for (int j = 0; j < Beam_.size(); j++) {
    if (Beam_[j]->GetIsActive() == false) {
      Beam_.erase(Beam_.begin() + j);
      j--;
    }
  }
  for (int k = 0; k < Hero_Projectile_.size(); k++) {
    if (Hero_Projectile_[k]->GetIsActive() == false) {
      Hero_Projectile_.erase(Hero_Projectile_.begin() + k);
      k--;
    }
  }
}

void Game::Start() { GameBoard_.ShowUntilClosed("Canvas"); }

void Game::OnMouseEvent(const graphics::MouseEvent &mouse) {
  if (mouse.GetMouseAction() == graphics::MouseAction::kMoved ||
      mouse.GetMouseAction() == graphics::MouseAction::kDragged) {
    if (mouse.GetX() < GameBoard_.GetWidth() &&
        mouse.GetY() < GameBoard_.GetHeight()) {
      Hero_.SetX(mouse.GetX() - Hero_.GetWidth() / 2);
      Hero_.SetY(mouse.GetY() - Hero_.GetHeight() / 2);
    }
  }
  if (mouse.GetMouseAction() == graphics::MouseAction::kPressed ||
      mouse.GetMouseAction() == graphics::MouseAction::kDragged) {
    std::unique_ptr<PlayerProjectile> Opp_ =
        std::make_unique<PlayerProjectile>(mouse.GetX(), mouse.GetY());
    Hero_Projectile_.push_back(std::move(Opp_));
  }
}

void Game::OnAnimationStep() {
  if (Villian_.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  GameBoard_.Flush();
}
