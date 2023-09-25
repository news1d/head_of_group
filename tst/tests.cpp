#include <iostream>
#include "gtest/gtest.h"
#include "../src/Function.h"

using namespace std;

// Функция для имитации пользовательского ввода
std::istringstream simulateUserInput(const std::string& input) {
    return std::istringstream(input);
}

// Тест для проверки создания структуры Candidate
TEST(CandidateTest, Creation) {
    Candidate candidate("John Doe");
    EXPECT_EQ(candidate.name, "John Doe");
    EXPECT_EQ(candidate.votes, 0);
}

// Тест для проверки правильности проведения голосования
TEST(ElectionTest, ConductElection) {
    // Создаем вектор кандидатов
    vector<Candidate> candidates;
    candidates.push_back(Candidate("Candidate1"));
    candidates.push_back(Candidate("Candidate2"));

    // Имитируем пользовательский ввод
    std::istringstream input_stream("Artur\n1\nAndrey\n2\nSergey\n1\n0\n");
    std::cin.rdbuf(input_stream.rdbuf());  // Перенаправляем ввод

    // Вызываем функцию проведения голосования
    conductElection(candidates);

    // Проверяем результаты голосования
    EXPECT_EQ(candidates[0].votes + candidates[1].votes, 3);
    EXPECT_GT(candidates[0].votes, 0);  // Проверяем, что хотя бы у одного кандидата есть голоса
}

// Тест для проверки сортировки кандидатов по голосам
TEST(ElectionTest, SortCandidatesByVotes) {
    vector<Candidate> candidates;
    candidates.push_back(Candidate("Candidate1"));
    candidates.push_back(Candidate("Candidate2"));
    candidates[0].votes = 5;
    candidates[1].votes = 10;

    // Вызываем функцию сортировки кандидатов
    sortCandidatesByVotes(candidates);

    // Проверяем, что кандидаты отсортированы в правильном порядке
    EXPECT_GT(candidates[0].votes, candidates[1].votes);  // Проверяем, что первый кандидат имеет больше голосов
}

// Тест для проверки правильности добавления голосов кандидату
TEST(ElectionTest, VoteForCandidate) {
    vector<Candidate> candidates;
    candidates.push_back(Candidate("Candidate1"));
    candidates.push_back(Candidate("Candidate2"));

    // Голосуем за первого кандидата
    voteForCandidate(candidates, 1);

    // Проверяем, что голоса были правильно добавлены
    EXPECT_EQ(candidates[0].votes, 1);
    EXPECT_EQ(candidates[1].votes, 0);
}

// Тест для проверки сценария без кандидатов
TEST(ElectionTest, NoCandidates) {
    vector<Candidate> candidates;

    // Имитируем пользовательский ввод
    std::istringstream input_stream("0\n");
    // Перенаправляем ввод
    std::cin.rdbuf(input_stream.rdbuf());

    // Вызываем функцию проведения голосования
    conductElection(candidates);

    // Проверяем, что функция не вызывает ошибок при отсутствии кандидатов
    // Ожидаем, что результаты голосования будут пустыми
    EXPECT_TRUE(candidates.empty());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
