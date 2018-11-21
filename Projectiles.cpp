#include "headers/Projectiles.h"
#include "headers/Projectile.h"
#include "headers/Word.h"
#include "headers/Words.h"
#include <math.h>
#include <bits/stdc++.h> 

Projectiles::Projectiles(Words* _words)
{
    words = _words;
    updateProjectilesTask = thread(&Projectiles::updateProjectiles, this, 20);
}

vector<Projectile*> Projectiles::getProjectiles() {
    return projectiles_on_screen;
}
void Projectiles::spawnProjectile(Projectile* p){
    mtx.lock();
    projectiles_on_screen.push_back(p);
    mtx.unlock();
}
void Projectiles::clearProjectiles(){
    mtx.lock();
    projectiles_on_screen.clear();
    mtx.unlock();
}
void Projectiles::removeProjectile(Projectile* p){
    if(!mtx.try_lock()) {
        projectiles_on_screen.erase(std::remove(projectiles_on_screen.begin(), projectiles_on_screen.end(), p), projectiles_on_screen.end());
    } else {
        mtx.lock();
        projectiles_on_screen.erase(std::remove(projectiles_on_screen.begin(), projectiles_on_screen.end(), p), projectiles_on_screen.end());
        mtx.unlock();
    }
}
void Projectiles::updateProjectiles(unsigned int update_time) {
    while(true) {
        mtx.lock();
        for (Projectile* p : projectiles_on_screen) {
            p->move();

            // Make projectiles bounce

            // Remove if target collided
            for (Word* w : words->words_on_screen) {
                if (p->checkCollision(w)) {
                    removeProjectile(p);
                }
            }
        }
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(update_time));
    }
}

Projectiles::~Projectiles()
{
}
