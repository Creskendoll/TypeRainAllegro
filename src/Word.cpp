#include "headers/Word.h"

ALLEGRO_BITMAP *load_bitmap_at_size(const char *filename, int w, int h)
{
  ALLEGRO_BITMAP *resized_bmp, *loaded_bmp, *prev_target;

  // 1. create a temporary bitmap of size we want
  resized_bmp = al_create_bitmap(w, h);
  if (!resized_bmp) return NULL;

  // 2. load the bitmap at the original size
  loaded_bmp = al_load_bitmap(filename);
  if (!loaded_bmp)
  {
     al_destroy_bitmap(resized_bmp);
     return NULL;
  }

  // 3. set the target bitmap to the resized bmp
  prev_target = al_get_target_bitmap();
  al_set_target_bitmap(resized_bmp);

  // 4. copy the loaded bitmap to the resized bmp
  al_draw_scaled_bitmap(loaded_bmp,
     0, 0,                                // source origin
     al_get_bitmap_width(loaded_bmp),     // source width
     al_get_bitmap_height(loaded_bmp),    // source height
     0, 0,                                // target origin
     w, h,                                // target dimensions
     0                                    // flags
  );

  // 5. restore the previous target and clean up
  al_set_target_bitmap(prev_target);
  al_destroy_bitmap(loaded_bmp);

  return resized_bmp;      
}

Word::Word(string _data, double _x, double _y, double _speed, ALLEGRO_COLOR _color) {
    position = Point(_x, _y);
    size = _data.size() * 20; // ????
    setBoundingBox(_x, _y);
    data = _data;
    speed = _speed;
    color = _color;

    heading = Vector(Point(0, 1));
    string fileName ("media/paper");
    string randNo = std::to_string( rand()%3 );
    fileName = fileName.append(randNo).append(".png");

    int imgW = size;
    int imgH = 30;

    image = load_bitmap_at_size(fileName.c_str(), imgW, imgH);
    
    // score
    point = _data.size();
}

void Word::setBoundingBox(double _x, double _y) {
    boundingBox = BoundingBox(_x - size/2.0, _y, _x + size/2.0, _y + bBox_height);
}

void Word::setPosition(double _x, double _y){
    position.set(_x, _y);
    setBoundingBox(_x, _y);
}

void Word::move() {
    setPosition(position.getX() + heading.direction.getX()*speed,
        position.getY() + heading.direction.getY()*speed);
}
