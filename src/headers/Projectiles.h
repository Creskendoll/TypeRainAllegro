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
    void updateProjectiles();
    void updateProjectilesAsync(unsigned int update_time);
    
    void spawnProjectile(Projectile* p);
    void spawnProjectileAsync(Projectile* p);
    
    void clearProjectiles();
    void clearProjectilesAsync();

    void removeProjectile(Projectile* p);
    void removeProjectileAsync(Projectile* p);
    
    Projectile getProjectile(int index);
    vector<Projectile*> getProjectiles();
};

#endif