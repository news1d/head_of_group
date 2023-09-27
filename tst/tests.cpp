#include <iostream>
#include "gtest/gtest.h"
#include "../src/Function.h"

using namespace std;


// Тест для проверки сортировки кандидатов по голосам
TEST(ElectionTest, SortCandidatesByVotes) {
    // Создаем вектор кандидатов
    vector<Candidate> candidates = {Candidate("Candidate1"), Candidate("Candidate2"), Candidate("Candidate3")};
    // Добавляем голоса кандидатам
    candidates[0].votes = 5;
    candidates[1].votes = 10;
    candidates[2].votes = 7;

    // Вызываем функцию сортировки кандидатов
    sortCandidatesByVotes(candidates);

    // Проверяем сортировку кандидатов
    EXPECT_EQ(candidates[0].name, "Candidate2");
    EXPECT_EQ(candidates[1].name, "Candidate3");
    EXPECT_EQ(candidates[2].name, "Candidate1");
}

// Тест для проверки правильности проведения голосования
TEST(ElectionTest, ConductElection) {
    // Создаем вектор кандидатов
    vector<Candidate> candidates = {Candidate("Candidate1"), Candidate("Candidate2")};

    // Имитируем пользовательский ввод (т.к. запрашивается ввод имени голосующего и его выбор)
    std::istringstream input_stream("Artur\n1\nAndrey\n2\nSergey\n1\n0\n");
    std::cin.rdbuf(input_stream.rdbuf());

    // Проверяем победителя голосвания
    EXPECT_EQ("Candidate1", conductElection(candidates));
}

// Тест для проверки наличия кандидатов
TEST(ElectionTest, NoCandidates) {
    // Создаем вектор кандидатов
    vector<Candidate> candidates;

    // Проверяем, что кандидаты отсуствуют
    EXPECT_EQ("Нет кандидатов для голосования!", conductElection(candidates));
}

// Тест для проверки наличия более одного кандидата
TEST(ElectionTest, SingleCandidate) {
    // Создаем вектор кандидатов
    vector<Candidate> candidates = {Candidate("Candidate1")};

    // Проверяем, что кандидатов недостаточно
    EXPECT_EQ("Недостаточно кандидатов!", conductElection(candidates));
}

// Тест для проверки наличия голосов
TEST(ElectionTest, NoVotes) {
    // Создаем вектор кандидатов
    vector<Candidate> candidates = {Candidate("Candidate1"), Candidate("Candidate2")};

    // Имитируем пользовательский ввод (т.к. запрашивается ввод имени голосующего и его выбор)
    std::istringstream input_stream("0\n");
    std::cin.rdbuf(input_stream.rdbuf());

    // Проверяем наличие голосов
    EXPECT_EQ("Голоса отсутствуют!", conductElection(candidates));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}