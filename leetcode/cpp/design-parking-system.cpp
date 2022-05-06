class ParkingSystem {
public:
  int sz[3];
  ParkingSystem(int big, int medium, int small) {
    sz[0] = big, sz[1] = medium, sz[2] = small;
  }

  bool addCar(int carType) {
    if (sz[carType-1] == 0) return false;
    --sz[carType-1];
    return true;
  }
};

/**
 * Your ParkingSystem object will be instantiated and called as such:
 * ParkingSystem* obj = new ParkingSystem(big, medium, small);
 * bool param_1 = obj->addCar(carType);
 */