#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;


class QueryReader {
public:
    QueryReader() = default;

    void ProcessQueries(int Q) {
        for (int i = 0; i < Q; ++i) {
            string query;
            cin >> query;

            if (query == "READ") {
                ProcessReadQuery();
            }
            else if (query == "CHEER") {
                ProcessCheerQuery();
            }
        }
    }

private:
    const int MAX_USERS = 100000;
    const int MAX_PAGES = 1000;

    vector<int> user_progress_ = vector<int>(MAX_USERS + 1);
    vector<int> page_readers_ = vector<int>(MAX_PAGES + 1);

    int total_users_ = 0;

    void ProcessReadQuery() {
        int user, page;
        cin >> user >> page;

        int last_page = user_progress_[user];

        // Зарегистрирован ли пользователь в системе?
        if (last_page == 0) {
            ++total_users_;
        }

        user_progress_[user] = page;  // Обновление прогресс пользователя

        // Увеличиваем количество пользователей для всех страниц, начиная с новой страницы
        for (int p = last_page + 1; p <= page; p++) {
            ++page_readers_[p];
        }
    }

    void ProcessCheerQuery() {
        int user;
        cin >> user;

        int user_page = user_progress_[user];

        if (user_page == 0) { //Обратка события, когда страницу никто не читал
            cout << 0 << endl;
        }
        else if (total_users_ == 1) { // Обработка события, когда только 1 пользователь читал страницу
            cout << 1 << endl;
        }
        else {
            // Количество пользователей, прочитавших меньше страниц, чем текущий
            int less_readers = total_users_ - page_readers_[user_page];

            // Доля пользователей, прочитавших меньше
            double cheer_ratio = static_cast<double>(less_readers) / (total_users_ - 1);
            cout << cheer_ratio << endl;
        }
    }
};

int main() {

    QueryReader reader;

	int Q;
	cin >> Q;
    
    reader.ProcessQueries(Q);

    return 0;
}