#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>  // Добавлено для использования std::map

using namespace std;

// Структура для хранения информации о кандидате
struct Candidate {
    string name;
    int votes;

    Candidate(string n) {
        name = n;
        votes = 0;
    }
};

// Функция для сортировки кандидатов по убыванию голосов
void sortCandidatesByVotes(vector<Candidate>& candidates){
    sort(candidates.begin(), candidates.end(), [](const Candidate& a, const Candidate& b) {
        return a.votes > b.votes;
    });
}

// Функция для голосования за кандидата
void voteForCandidate(vector<Candidate>& candidates, int choice) {
    candidates[choice - 1].votes++;
}

// Функция для проведения голосования
void conductElection(vector<Candidate>& candidates) {
    cout << "Голосование за выбор старосты!" << endl;

    // Вывод списка кандидатов
    cout << "Кандидаты:" << endl;
    for (int i = 0; i < candidates.size(); i++) {
        cout << i + 1 << ". " << candidates[i].name << endl;
    }

    // Создаем map для хранения истории голосования (студент -> выбранный кандидат)
    map<string, string> votingHistory;

    // Цикл голосования
    while (true) {
        string studentName;
        cout << "Введите ваше имя (0 - закончить голосование): ";
        cin >> studentName;

        if (studentName == "0") {
            break;
        }

        cout << "Введите номер кандидата, за которого хотите проголосовать (0 - закончить голосование): ";
        int choice;
        cin >> choice;

        if (choice < 0 || choice > candidates.size()) {
            cout << "Недопустимый выбор!" << endl;
            continue;
        }
        else if (choice == 0) {
            break;
        }

        // Увеличение количества голосов кандидата
        voteForCandidate(candidates, choice);

        // Сохраняем голосование в истории
        votingHistory[studentName] = candidates[choice - 1].name;
    }

    // Сортировка кандидатов по убыванию голосов
    sortCandidatesByVotes(candidates);

    // Вывод результатов голосования
    cout << "Результаты голосования:" << endl;
    for (int i = 0; i < candidates.size(); i++) {
        cout << i + 1 << ". " << candidates[i].name << ": " << candidates[i].votes << " голосов" << endl;
    }

    // Вывод истории голосования
    cout << "\nИстория голосования:" << endl;
    for (const auto& entry : votingHistory) {
        cout << "Студент: " << entry.first << ", Голосовал за: " << entry.second << endl;
    }
}

int main() {
    // Ввод количества кандидатов
    int numCandidates;
    cout << "Введите количество кандидатов: ";
    cin >> numCandidates;

    // Ввод имён кандидатов
    vector<Candidate> candidates;
    for (int i = 0; i < numCandidates; i++) {
        string name;
        cout << "Введите имя кандидата #" << i + 1 << ": ";
        cin >> name;
        candidates.push_back(Candidate(name));
    }

    // Проведение голосования
    conductElection(candidates);

    return 0;
}