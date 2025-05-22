#include <iostream>
#include <string>

#include "client-avl-tree/ClientAvlTree.h"
#include "helper/checkNumber.h"
#include "helper/checkPassport.h"
#include "helper/checkTariff.h"
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
        simCardHashTable->insert(simCard);
    }
    for (const auto& status : statuses) {
        statusList->push_back(status);
    }
    // === END INIT ===

    bool status;
    string commandString, typeCommand;
    Client inputClient;
    SimCard inputSimCard;
    Status inputStatus;
    vector<Client*> results; // для команды №6 клиентов
    vector<Status*> resultsStatus;
    vector<SimCard> resultsSimCards;
    while (true) {
        cout << "Management:\n1 — Client\n2 — Sim-card\n3 — Status\n0 — Exit" << endl;
        typeCommand.clear();
        cin >> typeCommand;
        if (typeCommand == "exit" || typeCommand == "0") break;
        switch (typeCommand[0] - '0') {
            case 1:
                while (true) {
                    cout <<
                        "Enter command:\n1 — Add new Client\n2 — Delete Client\n3 — Display all Clients\n4 — Delete all Clients"
                        "\n5 — Search Client by passport\n6 — Search Client by fragment FIO or address\n0 — Exit"
                    << endl;
                    cin >> commandString;
                    if (commandString == "exit" || commandString.empty() || commandString == "0") break;
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
                                cout << find->passport << " " << find->fio << " " << find->placeAndDateOfIssue << " " << find->address << " " << find->year << endl;
                                if (const vector<Status*> _statuses = statusList->getByPassport(find->passport); !_statuses.empty()) {
                                    for (const auto& _status : _statuses) {
                                        if (const optional<SimCard> simCard = simCardHashTable->find(_status->number); simCard && !simCard->exists) {
                                            cout << _status->number << endl;
                                        }
                                    }
                                }
                            }
                            break;
                        case 6:
                            input(inputClient.fio, "Input FIO or address fragment:");
                            if (results = clientAvlTree->findByFragment(inputClient.fio, results); results.empty()) {
                                cerr << "Clients does not exists!" << endl;
                            } else {
                                for (const auto& client : results) {
                                    cout << client->passport << " " << client->fio << " " << client->placeAndDateOfIssue << " " << client->address << " " <<  client->year << endl;
                                }
                                results.clear();
                            }
                            break;
                        default:
                            cerr << "Incorrect command: " + commandString << endl;
                            break;
                    }
                }
                break;
            case 2:
                while (true) {
                    cout << "Enter command:\n1 — Add new sim-card\n2 — Delete sim-card\n3 — Get all sim-cards\n4 — Delete all sim-cards"
                            "\n5 — Search sim-card by number\n6 — Search sim-cards by tariffs\n0 — Exit" << endl;
                    cin >> commandString;
                    if (commandString == "exit" || commandString.empty() || commandString == "0") break;
                    switch (commandString[0] - '0') {
                        case 1:
                            if (!checkNumber(inputSimCard.number)) break;
                            if (!checkTariff(inputSimCard.tariff)) break;
                            input(inputSimCard.year, "Year of release:");
                            input(inputSimCard.exists, "Availability:");
                            simCardHashTable->insert(inputSimCard);
                            break;
                        case 2:
                            input(inputSimCard.number, "Input number for delete:");
                            if (simCardHashTable->remove(inputSimCard.number)) {
                                resultsStatus = statusList->get(inputSimCard.number);
                                for (const auto& _status : resultsStatus) {
                                    if (clientAvlTree->remove(_status->passport)) {
                                        cout << "Client " << _status->passport << " deleted" << endl;
                                    } else {
                                        cerr << "Client " << _status->passport << " deleted failed!" << endl;
                                    }
                                    statusList->remove(_status->number);
                                }
                                resultsStatus.clear();
                                cout << "Successfully deleted" << endl;
                            } else {
                                cerr << "Error deleting! Check number: " << inputSimCard.number << endl;
                            }
                            break;
                        case 3:
                            simCardHashTable->display();
                            break;
                        case 4:
                            resultsSimCards = simCardHashTable->getAll();
                            for (const auto& simCard : resultsSimCards) {
                                if (simCardHashTable->remove(simCard.number)) {
                                    resultsStatus = statusList->get(simCard.number);
                                    for (const auto& _status : resultsStatus) {
                                        if (clientAvlTree->remove(_status->passport)) {
                                            cout << "Client " << _status->passport << " deleted" << endl;
                                        } else {
                                            cerr << "Client " << _status->passport << " deleted failed!" << endl;
                                        }
                                        statusList->remove(_status->number);
                                    }
                                    resultsStatus.clear();
                                    cout << "Successfully deleted" << endl;
                                } else {
                                    cerr << "Error deleting! Check number: " << simCard.number << endl;
                                }
                            }
                            break;
                        case 5:
                            input(inputSimCard.number, "Input number for search:");
                            if (const optional<SimCard> find = simCardHashTable->find(inputSimCard.number)) {
                                cout << find->number << " " << find->tariff << " " << find->year << " " << find->exists << endl;
                                resultsStatus = statusList->get(find->number);
                                if (!resultsStatus.empty()) {
                                    for (const auto& _status : resultsStatus) {
                                        if (const optional<SimCard> simCard = simCardHashTable->find(_status->number); simCard && !simCard->exists) {
                                            const Client* _client = clientAvlTree->find(_status->passport);
                                            cout << "Client: " << _client->fio << " " << _client->passport << endl;
                                        }
                                    }
                                } else {
                                    cerr << "Clients not found!" << endl;
                                }
                            } else {
                                cerr << "SimCard does not found!" << endl;
                            }
                            break;
                        case 6:
                            if (!checkTariff(inputSimCard.tariff)) break;
                            simCardHashTable->displayByTariff(inputSimCard.tariff);
                            break;
                        default:
                            break;
                    }
                }
                break;
            case 3:
                while (true) {
                    cout << "Enter command:\n1 — Create status\n2 — Update status\n3 — Get All Statuses\n0 — Exit" << endl;
                    cin >> commandString;
                    if (commandString == "exit" || commandString.empty() || commandString == "0") break;
                    switch (commandString[0] - '0') {
                        case 1:
                            if (!checkPassport(inputStatus.passport)) break;
                            if (clientAvlTree->find(inputStatus.passport)) {
                                if (!checkNumber(inputStatus.number)) break;
                                if (const optional<SimCard> simCard = simCardHashTable->find(inputStatus.number); simCard && simCard->exists) {
                                    simCardHashTable->updateExists(inputStatus.number, false);
                                    input(inputStatus.dateStart, "Date of issue:");
                                    input(inputStatus.dateEnd, "Issue end date:");
                                    statusList->push_back(inputStatus);
                                } else {
                                    cerr << "Sim card via number " << inputStatus.number << " does not exist" << endl;
                                }
                            } else {
                                cerr << "Client via passport " << inputStatus.passport << " does not exist!" << endl;
                            }
                            break;
                        case 2:
                            if (!checkNumber(inputSimCard.number)) break;
                            if (simCardHashTable->find(inputSimCard.number)) {
                                input(status, "Input status of sim-card:");
                                if (!status) {
                                    if (statusList->remove(inputSimCard.number)) {
                                        cout << "Successfully" << endl;
                                    } else {
                                        cerr << "Sim card not in status list!" << endl;
                                    }
                                }
                                simCardHashTable->updateExists(inputSimCard.number, status);
                            } else {
                                cerr << "Sim card not found!" << endl;
                            }
                            break;
                        case 3:
                            statusList->print();
                            break;
                        default:
                            break;
                    }
                }
                break;
            default:
                cerr << "Incorrect command: " << typeCommand << endl;
                break;
        }

    }
}