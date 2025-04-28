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

    // Client() {
    //     if (passport.length() != 11) throw invalid_argument("Passport length mismatch: " + passport);
    //     if (passport[4] != '-') throw invalid_argument("Passport must have a valid symbol on position 4: " + passport);
    //     const string valid = "1234567890-";
    //     for (int i = 0; i < 11; i++) {
    //         if (!valid.contains(passport[i])) throw invalid_argument("Passport invalid: " + passport);
    //     }
    // }
};

#endif //CLIENT_H
