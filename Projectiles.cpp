#include "headers/Projectiles.h"
#include "headers/Projectile.h"
#include "headers/Word.h"
#include "headers/Words.h"
#include <math.h>
#include <bits/stdc++.h> 

Projectiles::Projectiles(Words* _words)
{
    words = _words;
    updateProjectilesTask = thread(&Projectiles::updateProjectiles, this, 30);
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
            for (Word* w : words->getWordsOnScreen()) {
                if (p->checkCollision(w)) {
                    // remove letters from word on screen
                    words->removeNLetters(w, 1);
                    string inputStr = words->getInputWord();

                    if (p->getY() > words->screen_height || p->getY() < 0 || p->getX() > words->screen_width || p->getX() < 0) {
                        removeProjectile(p);
                    } else if (p->type == PROJECTILE_BOUNCE) {
                        // TODO: only works with horizontal lines
                        
                        Point pDir = p->heading.direction;
                        // Push the projectile opposite the way its headed
                        p->setX(p->getX() - pDir.getX()*5);
                        p->setY(p->getY() + pDir.getY()*5);
                        
                        Vector normal = w->boundingBox.getRelativeNormal(p->getPosition());
                        
                        p->heading = p->heading.reflect(normal);
                    } else {
                        removeProjectile(p);
                    }

                    //check if collided word is the target word
                    if (p->targetWord == w) {
                        if (inputStr.length() > 1) {
                            words->setInputWord(inputStr.substr(1, inputStr.length()));
                        } else {
                            words->setInputWord("");
                        }
                    }
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
