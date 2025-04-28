#ifndef GETINITIALDATA_H
#define GETINITIALDATA_H

#include <tuple>
#include <vector>

#include "split.h"
#include "../types/Client.h"
#include "../types/SimCard.h"
#include "../types/Status.h"
#include "../helper/readLinesFromFile.h"

using namespace std;

inline tuple<vector<Client>, vector<SimCard>, vector<Status>> getInitialData() {
    vector<Client> clients;
    vector<SimCard> simCards;
    vector<Status> statuses;
    vector<string> inLine = {};

    Client client;
    for (const string& line : readLinesFromFile("../initial/clients.csv")) {
        inLine = split(line, ";");
        client.passport = inLine[0];
        client.placeAndDateOfIssue = inLine[1];
        client.fio = inLine[2];
        client.year = stoi(inLine[3]);
        client.address = inLine[4];
        clients.push_back(client);
    }

    SimCard simCard;
    for (const string& line : readLinesFromFile("../initial/sim-cards.csv")) {
        inLine = split(line, ";");
        simCard.number = inLine[0];
        simCard.tariff = inLine[1];
        simCard.year = stoi(inLine[2]);
        simCard.exists = stoi(inLine[3]);
        simCards.push_back(simCard);
    }

    Status status;
    for (const string& line : readLinesFromFile("../initial/statuses.csv")) {
        inLine = split(line, ";");
        status.passport = inLine[0];
        status.number = inLine[1];
        status.dateStart = inLine[2];
        status.dateEnd = inLine[3];
        statuses.push_back(status);
    }

    return {clients, simCards, statuses};
}

#endif //GETINITIALDATA_H
