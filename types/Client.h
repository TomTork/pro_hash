#ifndef CLIENT_H
#define CLIENT_H
#include <string>

using namespace std;

/**
 * @brief Структура, описывающая клиента
 */
struct Client {
    /**
     * @brief Номер паспорта формата "NNNN-NNNNNN"
     */
    string passport;
    /**
     * @brief Место и дата выдачи паспорта
     */
    string placeAndDateOfIssue;
    /**
     * @brief ФИО
     */
    string fio;
    /**
     * @brief Год рождения
     */
    int year = 0;
    /**
     * @brief Адрес
     */
    string address;
};

#endif //CLIENT_H
