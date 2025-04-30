#include <iostream>
#include <string>

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

    bool work = true;
    int typeCommand, command;
    char commandString;
    while (work) {
        cout << "Management:\n1 — Client\n2 — Sim-card\n3 — Status\nOther for exit" << endl;
        cin >> typeCommand;
        switch (typeCommand) {
            case 1:
                cout << "Enter command:\n1 — Add new Client\n2 — Delete Client\n3 — Get all Clients\n4 — Delete all Clients"
                        "\n5 — Search Client by passport\n6 — Search Client by fragment FIO or address\nOther for exit" << endl;
                cin >> commandString;
                if (isdigit(commandString)) {
                    switch (static_cast<int>(commandString)) {
                        case 1:
                            cout << "Entered 1" << endl;
                            break;
                        case 2:
                            break;
                        case 3:
                            break;
                        case 4:
                            break;
                        case 5:
                            break;
                        case 6:
                            break;
                        default:
                            break;
                    }
                }
                break;
            case 2:
                cout << "Enter command:\n1 — Add new sim-card\n2 — Delete sim-card\n3 — Get all sim-cards\n4 — Delete all sim-cards"
                        "\n5 — Search sim-card by number\n6 — Search sim-cards by tariffs\nOther for exit" << endl;
                cin >> command;
                switch (command) {
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        break;
                    case 6:
                        break;
                    default:
                        break;
                }
                break;
            case 3:
                cout << "Enter command:\n1 — Create status\n2 — Update status\nOther for exit" << endl;
                cin >> command;
                switch (command) {
                    case 1:
                        break;
                    case 2:
                        break;
                    default:
                        break;
                }
                break;
            default:
                work = false;
                break;
        }
    }

    // for (const auto &client : clients) {
    //     cout << client.passport << " " << client.fio << " " << client.address << " " << client.year << " " << client.placeAndDateOfIssue << endl;
    // }
    // cout << endl;
    // for (const auto &simCard : simCards) {
    //     cout << simCard.number << " " << simCard.tariff << " " << simCard.year << " " << simCard.exists << endl;
    // }
    // cout << endl;
    // for (const auto &status : statuses) {
    //     cout << status.passport << " " << status.number << " " << status.dateStart << " " << status.dateEnd << endl;
    // }
    return 0;
}