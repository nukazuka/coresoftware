#ifndef TOWERINFOV1_H
#define TOWERINFOV1_H

#include "TowerInfo.h"

class TowerInfov1 : public TowerInfo
{
 public:
  TowerInfov1() {}
  TowerInfov1(TowerInfo& tower);
  ~TowerInfov1() override {}
  void Reset() override;

  //! Clear is used by TClonesArray to reset the tower to initial state without calling destructor/constructor
  void Clear(Option_t* = "") override;

  void set_time(short t) override { _time = t; }
  short get_time() override { return _time; }
  void set_energy(float energy) override { _energy = energy; }
  float get_energy() override { return _energy; }
  void copy_tower(TowerInfo* tower) override;

 private:
  short _time{0};
  float _energy{0};

  ClassDefOverride(TowerInfov1, 1);
};

#endif
