#include <iostream>

#include "helper/getInitialData.h"
#include "types/Client.h"
#include "types/SimCard.h"
#include "types/Status.h"

using namespace std;

// обслуживание клиентов оператора сотовой связи
// закрытое хэширование с двойным хэшированием
// метод сортировки включением
// вид списка: линейный двунаправленный
// метод обхода дерева — прямой
// алгоритм поиска слова в тексте — прямой

int main() {
    const auto initial = getInitialData();
    vector<Client> clients = get<0>(initial);
    vector<SimCard> simCards = get<1>(initial);
    vector<Status> statuses = get<2>(initial);

    for (const auto &client : clients) {
        cout << client.passport << " " << client.fio << " " << client.address << " " << client.year << " " << client.placeAndDateOfIssue << endl;
    }
    cout << endl;
    for (const auto &simCard : simCards) {
        cout << simCard.number << " " << simCard.tariff << " " << simCard.year << " " << simCard.exists << endl;
    }
    cout << endl;
    for (const auto &status : statuses) {
        cout << status.passport << " " << status.number << " " << status.dateStart << " " << status.dateEnd << endl;
    }
    return 0;
}