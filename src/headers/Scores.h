#ifndef SCORES_H
#define SCORES_H

#include <bits/stdc++.h>
#include <vector>
#include <thread>
#include <mutex>
#include "GameObject.h"

class Point;
class Score
{
private:
    int score;
    unsigned int screen_time;
public:
    Point position;
    Score(int _score, Point pos, double _screen_time);
    void setScore(int _score);
    int getScore();
    void setScreenTime(unsigned int _screen_time);
    unsigned int getScreenTime();
};

class Scores
{
private:
    std::thread updatePointsTask;
    void updatePoints(unsigned int update_time);
    std::mutex mtx;
public:
    std::vector<Score*> scores_on_screen;
    Scores();
    void removeScore(Score* s);
    void addScore(Score* s);
};

#endif