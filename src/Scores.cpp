#include "headers/Scores.h"

Score::Score(int _score, Point p, double _screen_time) {
    score = _score;
    position = p;
    screen_time = _screen_time;
}
int Score::getScore(){ return score; }
void Score::setScore (int _point) { score = _point; }
unsigned int Score::getScreenTime(){ return screen_time; }
void Score::setScreenTime(unsigned int _screen_time) { screen_time = _screen_time; }

Scores::Scores() {
    updatePointsTask = std::thread(&Scores::updatePoints, this, 100);
}

void Scores::removeScore(Score* s) {
    mtx.lock();
    scores_on_screen.erase(std::remove(scores_on_screen.begin(), scores_on_screen.end(), s), scores_on_screen.end());
    mtx.unlock();
}
void Scores::addScore(Score* s) {
    mtx.lock();
    scores_on_screen.push_back(s);
    mtx.unlock();
}

void Scores::updatePoints(unsigned int update_time) {
    while (true) {
        for (Score* s : scores_on_screen) {
            if (s->getScreenTime() <= 0){
                removeScore(s);
            } else {
                s->setScreenTime(s->getScreenTime()-update_time);
            }
        }
     
        std::this_thread::sleep_for(std::chrono::milliseconds(update_time));
    }
}