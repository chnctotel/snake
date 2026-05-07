//
//  database.cpp
//  snake
//
//  Created by chnctotel on 07.05.2026.
//
#include <iostream>
#include "database.h"

Database::Database()
{
    if (sqlite3_open("snake.db", &db) != SQLITE_OK)
    {
        std::cerr << "Database error!" << std::endl;
    }
    initTable();
};

Database::~Database()
{
    sqlite3_close(db);
}

void Database::initTable()
{
    const char* sql = "CREATE TABLE IF NOT EXISTS high_scores ("
                      "nickname TEXT PRIMARY KEY, "
                      "score INTEGER);";
    sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
}

void Database::saveScore(const std::string& nickname, int score)
{
    std::string sql = "INSERT INTO high_scores (nickname, score) VALUES ('" + nickname + "', " + std::to_string(score) + ") "
                      "ON CONFLICT(nickname) DO UPDATE SET score = excluded.score "
                      "WHERE excluded.score > high_scores.score;";
    
    sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
}

int Database::getTopScores(ScoreRecord* records, int maxCount)
{
    const char* sql = "SELECT nickname, score FROM high_scores ORDER BY score DESC LIMIT 10;";
    
    sqlite3_stmt* stmt;
    
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    
    int count = 0;
    
    while (sqlite3_step(stmt) == SQLITE_ROW && count < maxCount)
    {
        const char* dbNickname = (const char*)sqlite3_column_text(stmt, 0);
        int dbScore = sqlite3_column_int(stmt, 1);
        
        records[count].nickname = dbNickname;
        records[count].score = dbScore;
        
        count++;
    }
    
    sqlite3_finalize(stmt);
    return count;
};
