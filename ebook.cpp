#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

const int MAX_USERS = 100000; // Макс номера пользователей
const int MAX_PAGES = 1000; // Макс номера страниц

class EbookReader {
public:
    EbookReader(int size) : m_tree(size + 1, 0) {}

    // Добавляет значение delta к элементу по индексу idx    
    void add(int idx, int delta) {
        for (; idx < m_tree.size(); idx += idx & -idx) {
            m_tree[idx] += delta;
        }
    }

    // Возвращает сумму элементов от 1 до idx включительно    
    int query(int idx) {
        int sum = 0;
        for (; idx > 0; idx -= idx & -idx) {
            sum += m_tree[idx];
        }
        return sum;
    }

private:
    std::vector<int> m_tree;
};

int main() {
    
    int q;
    std::cin >> q;
    
    std::vector<int> user_pages(MAX_USERS + 1, 0);   
    EbookReader page_stats(MAX_PAGES + 2);

    int total_readers = 0;

    for (int i = 0; i < q; ++i) {
        std::string command;
        std::cin >> command;

        // Используем switch по первому символу команды.
        // 'R' для "READ", 'C' для "CHEER".
        switch (command[0]) {
            case 'R': { 
                int user_id, page_num;
                std::cin >> user_id >> page_num;

                int old_page = user_pages[user_id];
                
                if (old_page == 0) {                    
                    total_readers++;
                } else {                    
                    page_stats.add(old_page, -1);
                }

                user_pages[user_id] = page_num;                
                page_stats.add(page_num, 1);
                break;
            }

            case 'C': {
                int user_id;
                std::cin >> user_id;

                int my_page = user_pages[user_id];

                if (my_page == 0) {
                    std::cout << 0 << std::endl;
                    continue;
                }

                if (total_readers <= 1) {                    
                    std::cout << 1 << std::endl;
                    continue;
                }
                
                int less_readers_count = page_stats.query(my_page - 1);                
                double cheer_value = static_cast<double>(less_readers_count) / (total_readers - 1);                
                std::cout << cheer_value << '\n';
                break;
            }
        }
    }

    return 0;
}
