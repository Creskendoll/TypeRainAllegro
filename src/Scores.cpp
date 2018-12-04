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
int Score::getFrameCount(){ return frames; }
void Score::setFrameCount(int _frame_count) { frames = _frame_count; }

Scores::Scores() {
    // updatePointsTask = std::thread(&Scores::updatePointsAsync, this, 100);
}

int Scores::getTotalScore() {
    return totalScore;
}
void Scores::removeScoreAsync(Score* s) {
    mtx.lock();
    scores_on_screen.erase(std::remove(scores_on_screen.begin(), scores_on_screen.end(), s), scores_on_screen.end());
    mtx.unlock();
}
void Scores::addScoreAsync(Score* s) {
    mtx.lock();
    totalScore += s->getScore();
    scores_on_screen.push_back(s);
    mtx.unlock();
}
void Scores::setTotalScoreAsync(int score) {
    mtx.lock();
    totalScore += score;
    mtx.unlock();
}

void Scores::removeScore(Score* s) {
    scores_on_screen.erase(std::remove(scores_on_screen.begin(), scores_on_screen.end(), s), scores_on_screen.end());
}
void Scores::addScore(Score* s) {
    totalScore += s->getScore();
    scores_on_screen.push_back(s);
}
void Scores::setTotalScore(int score) {
    totalScore += score;
}


void Scores::updatePointsAsync(unsigned int update_time) {
    while (true) {
        for (Score* s : scores_on_screen) {
            if (s->getScreenTime() <= 0){
                removeScoreAsync(s);
            } else {
                s->setScreenTime(s->getScreenTime()-update_time);
            }
        }
     
        std::this_thread::sleep_for(std::chrono::milliseconds(update_time));
    }
}

void Scores::updatePoints() {
    for (Score* s : scores_on_screen) {
        if (s->getScreenTime() <= 0){
            removeScore(s);
        } else {
            s->setScreenTime(s->getScreenTime() - 1);
        }
    }
}