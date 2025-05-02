#include <iostream>
#include <string>

#include "client-avl-tree/ClientAvlTree.h"
#include "helper/checkPassport.h"
#include "helper/getInitialData.h"
#include "helper/input.h"
#include "simcard-hash-table/SimCardHashTable.h"
#include "status-list/StatusList.h"
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
    const vector<Client> clients = get<0>(initial);
    vector<SimCard> simCards = get<1>(initial);
    vector<Status> statuses = get<2>(initial);
    const auto clientAvlTree = new ClientAvlTree();
    const auto simCardHashTable = new SimCardHashTable();
    const auto statusList = new StatusList();

    // === START INIT ===
    for (const auto& client : clients) {
        clientAvlTree->insert(client);
    }
    for (const auto& simCard : simCards) {

    }
    for (const auto& status : statuses) {

    }
    // === END INIT ===

    bool work2 = true, work3 = true, work4 = true;
    string commandString, typeCommand;
    Client inputClient;
    while (true) {
        cout << "Management:\n1 — Client\n2 — Sim-card\n3 — Status\nOther for exit" << endl;
        cin >> typeCommand;
        if (typeCommand == "exit") break;
        switch (typeCommand[0] - '0') {
            case 1:
                // НЕ ВЫПОЛНЕНЫ В ПОЛНОЙ МЕРЕ УСЛОВИЯ ПОИСКА КЛИЕНТА ПО НОМЕРУ ПАСПОРТА, ВЕДЬ СИМ-КАРТЫ ДОЛЖНЫ БЫТЬ ВЫДАНЫ
                while (work2) {
                    cout <<
                        "Enter command:\n1 — Add new Client\n2 — Delete Client\n3 — Display all Clients\n4 — Delete all Clients"
                        "\n5 — Search Client by passport\n6 — Search Client by fragment FIO or address\nOther for exit"
                    << endl;
                    cin >> commandString;
                    if (commandString == "exit" || commandString.empty()) { work2 = false; break; }
                    switch (commandString[0] - '0') {
                        case 1:
                            if (!checkPassport(inputClient.passport)) break;
                            input(inputClient.placeAndDateOfIssue, "Input place & date of issue:");
                            input(inputClient.fio, "Input FIO:");
                            input(inputClient.year, "Input year of birthday:");
                            input(inputClient.address, "Input address:");
                            clientAvlTree->insert(inputClient);
                            cout << "Successfully added!" << endl;
                            break;
                        case 2:
                            input(inputClient.passport, "Input passport for delete:");
                            if (clientAvlTree->remove(inputClient.passport)) {
                                cout << "Successfully deleted" << endl;
                            } else {
                                cerr << "Error deleting! Check passport number: " + inputClient.passport << endl;
                            }
                            break;
                        case 3:
                            clientAvlTree->preOrder();
                            break;
                        case 4:
                            clientAvlTree->clear();
                            cout << "Successfully cleared!" << endl;
                            break;
                        case 5:
                            input(inputClient.passport, "Input passport for search:");
                            if (const Client* find = clientAvlTree->find(inputClient.passport); find == nullptr) {
                                cerr << "Client does not found!" << endl;
                            } else {
                                cout << find->passport << " " << find->fio << " " << find->placeAndDateOfIssue << " " << find->address << find->year << endl;
                            }
                            break;
                        case 6:
                            input(inputClient.fio, "Input FIO or address fragment:");
                            if (const Client* find = clientAvlTree->findByFragment(inputClient.fio); find == nullptr) {
                                cerr << "Client does not exist!" << endl;
                            } else {
                                cout << find->passport << " " << find->fio << " " << find->placeAndDateOfIssue << " " << find->address << find->year << endl;
                            }
                            break;
                        default:
                            cerr << "Incorrect command: " + commandString << endl;
                            break;
                    }
                }
                break;
            case 2:
                while (work3) {
                    cout << "Enter command:\n1 — Add new sim-card\n2 — Delete sim-card\n3 — Get all sim-cards\n4 — Delete all sim-cards"
                            "\n5 — Search sim-card by number\n6 — Search sim-cards by tariffs\nOther for exit" << endl;
                    cin >> commandString;
                    if (commandString == "exit" || commandString.empty()) { work3 = false; break; }
                    switch (commandString[0] - '0') {
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
                }
                break;
            case 3:
                while (work4) {
                    cout << "Enter command:\n1 — Create status\n2 — Update status\nOther for exit" << endl;
                    cin >> commandString;
                    if (commandString == "exit" || commandString.empty()) { work4 = false; break; }
                    switch (commandString[0] - '0') {
                        case 1:
                            break;
                        case 2:
                            break;
                        default:
                            break;
                    }
                }
                break;
            default:
                cerr << "Incorrect command: " + typeCommand << endl;
                break;
        }

    }
}