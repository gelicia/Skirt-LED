
struct Pos {
  int x, y;
};

struct Piece {
  int rotationCount;
  Pos **rotations;
};

struct Pos oPiece_rotations [][4] = {
  {{0,0}, {0,-1}, {1,0}, {1,-1}}
};

struct Pos lPiece_rotations [][4] = {
  {{0,0}, {1,0}, {-1,0}, {-1,1}},
  {{0,0}, {0,1}, {0,-1}, {-1,-1}},
  {{0,0}, {-1,0}, {1,0}, {1,-1}},
  {{0,0}, {0,-1}, {0,1}, {1,1}},
};

struct Pos jPiece_rotations [][4] = {
  {{0,0}, {-1,0}, {1,0}, {1,1}},
  {{0,0}, {0,-1}, {0,1}, {-1,1}},
  {{0,0}, {1,0}, {-1,0}, {-1,-1}},
  {{0,0}, {0,1}, {0,-1}, {1,-1}}
};

struct Pos iPiece_rotations [][4] = {
  {{0,0}, {-1,0}, {1,0}, {2,0}},
  {{0,0}, {0,1}, {0,-1}, {0,-2}}
};

struct Pos sPiece_rotations [][4] = {
  {{0,0}, {1,0}, {0,1}, {-1,1}},
  {{0,0}, {0,1}, {1,1}, {1,2}}
};

struct Pos zPiece_rotations [][4] = {
  {{0,0}, {-1,0}, {0,1}, {1,1}},
  {{0,0}, {0,-1}, {-1,0}, {-1,1}}
};

struct Pos tPiece_rotations [][4] = {
  {{0,0}, {-1,0}, {1,0}, {0,-1}},
  {{0,0}, {0,-1}, {1,0}, {0,1}},
  {{0,0}, {-1,0}, {0,1}, {1,0}},
  {{0,0}, {0,-1}, {-1,0}, {0,1}}
};

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
