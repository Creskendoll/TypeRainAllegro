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
    int frames;
    unsigned int screen_time;
public:
    Point position;
    Score(int _score, Point pos, double _screen_time);
    void setScore(int _score);
    int getScore();
    void setScreenTime(unsigned int _screen_time);
    unsigned int getScreenTime();
    void setFrameCount(int _frame_count);
    int getFrameCount();
};

class Scores
{
private:
    std::thread updatePointsTask;
    void updatePointsAsync(unsigned int update_time);
    std::mutex mtx;
    int totalScore = 0;
public:
    std::vector<Score*> scores_on_screen;
    void updatePoints();
    Scores();
    int getTotalScore();
    void removeScoreAsync(Score* s);
    void addScoreAsync(Score* s);
    void setTotalScoreAsync(int score);

    void removeScore(Score* s);
    void addScore(Score* s);
    void setTotalScore(int score);
};

#endif