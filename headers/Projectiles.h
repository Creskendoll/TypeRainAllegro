#ifndef PROJECTILES_H
#define PROJECTILES_H

#include<vector>
#include<mutex>
#include<thread>

using std::vector;
using std::mutex;
using std::thread;

class Word;
class Words;
class Projectile;
class Projectiles
{
private:
    Words* words;
    vector<Projectile*> projectiles_on_screen;
    thread updateProjectilesTask;
    void setBoundingBox(double _x, double _y);
    void updateProjectile(Projectile* p, unsigned int update_time);
    Word* checkCollision(Projectile* p, vector<Word*>* words);
    mutex mtx;
public:
    Projectiles(Words* _words);
    ~Projectiles();
    void spawnProjectile(Projectile* p);
    void updateProjectiles(unsigned int update_time);
    void removeProjectile(Projectile* p);
    void clearProjectiles();
    Projectile getProjectile(int index);
    vector<Projectile*> getProjectiles();
};

#endif