#pragma once
//  database.h
//  snake
#include <string>
#include <sqlite3.h>

struct ScoreRecord
{
    std::string nickname;
    int score;
};

class Database
{
private:
    
    sqlite3* db;
    
public:
    
    Database();
    ~Database();
    
    void initTable();
    
    void saveScore(const std::string& name, int score);
    
    int getTopScores(ScoreRecord* records, int maxCount);
};

