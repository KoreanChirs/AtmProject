#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>
#include <sys/stat.h>
using namespace std;

enum os_t { UNIX, WINDOW };

enum transfer_t { TRANSFER_CANCEL, CASH_TRANSFER, ACCOUNT_TRANSFER };
enum paper_t { PAPER_CANCEL, CASH, CHECK };
enum transaction_t { CANCEL, TRANSFER, DEPOSIT, WITHDRAWAL };
enum language_t { UNI, BI };
enum available_t { SINGLE, MULTI };

enum card_verification_t { SUCCESS, WRONG_CARD, WRONG_PASSWORD, WRONG_ATM };
enum transfer_condition_t { TRANS_SUCCESS, NO_DST, TRANS_NO_MONEY, NO_SRC_ACCOUNT };
enum deposit_condition_t { DEPO_SUCCESS, INVALID_DEPOSIT_TYPE, EXCEED_DEPO };
enum withdrawal_condition_t { WITH_SUCCESS, WITH_NO_MONEY, EXCEED_LIMIT, ATM_NO_MONEY, INVALID_AMOUNT, EXCEED_WITH };

void display_Enter_Valid_Number();

bool cin_fail(istream& i);

template<typename T>
istream& operator>> (istream& i, T& t) {
    int temp_type;
    if (i >> temp_type)
        t = static_cast<T>(temp_type);
    return i;
}

template<typename T>
bool operator|= (T& a, T& b) {
    bool result = a;
    result = (result || b);
    return result;
}

template<typename T>
bool isIn_enum(T t) {
    bool result = false;
    if (typeid(t).name() == typeid(transaction_t).name()) {
        transaction_t t_a[4] = { CANCEL, TRANSFER, DEPOSIT, WITHDRAWAL };
        for (auto i : t_a)
            result |= ((transaction_t)t == i);
        return result;
    }
    else if (typeid(t).name() == typeid(transfer_t).name()) {
        transfer_t t_a[3] = { TRANSFER_CANCEL, CASH_TRANSFER, ACCOUNT_TRANSFER };
        for (auto i : t_a)
            result |= ((transfer_t)t == i);
        return result;
    }
    else if (typeid(t).name() == typeid(paper_t).name()) {
        paper_t t_a[3] = { PAPER_CANCEL, CASH, CHECK };
        for (auto i : t_a)
            result |= ((paper_t)t == i);
        return result;
    }
    return result;
}

class Transaction {
protected:
    string condition;
    int transactionID;
    long long Amount;
    int fee;
    long long card_number;
public:
    static int transaction_count;
    Transaction();
    Transaction(const Transaction& other);
    virtual ~Transaction();
    int getTransactionID() const { return transactionID; }
    void setTransactionID(int id) { transactionID = id; }
    void setFee(int fee) { this->fee = fee; }
    void setTransaction_Condition(string condition) { this->condition = condition; }
    virtual void displayTransactionInfo() const;
    virtual void fileTransactioninfo(ofstream* ofile) const;
};

class Transaction_transfer : public Transaction {
private:
    long long srcAccount, dstAccount;
    transfer_t Transfer_type;
public:
    Transaction_transfer(long long srcAccount, long long dstAccount, transfer_t Transfer_type, long long Amount, long long card_number);
    Transaction_transfer(const Transaction_transfer& other);
    virtual ~Transaction_transfer() override;
    virtual void displayTransactionInfo() const override;
    virtual void fileTransactioninfo(ofstream* ofile) const override;
};

class Transaction_deposit : public Transaction {
private:
    paper_t Paper_type;
public:
    Transaction_deposit(paper_t Paper_type, long long Amount, long long card_number);
    Transaction_deposit(const Transaction_deposit& other);
    virtual ~Transaction_deposit() override;
    virtual void displayTransactionInfo() const override;
    virtual void fileTransactioninfo(ofstream* ofile) const override;
};

class Transaction_withdrawal : public Transaction {
public:
    Transaction_withdrawal(long long amount, long long card_number);
    Transaction_withdrawal(const Transaction_withdrawal& other);
    virtual ~Transaction_withdrawal() override;
    virtual void displayTransactionInfo() const override;
    virtual void fileTransactioninfo(ofstream* ofile) const override;
};

// account에 bank name 필요, user name 필요, transaction history 필요

class Bank;
class User;
class Account {
private:
    Bank* bank;
    User* user;
    long long Account_number;
    long long Account_balance;
    long long Account_password;
public:
    vector<Transaction*> Transaction_history_in_Account;
    Account(Bank* bank, long long Account_number, long long Account_balance, long long Account_password, User* user);
    ~Account();
    long long getAccountBalance() const { return Account_balance; }
    long long getAccountNumber() const { return Account_number; }
    Bank* getBank() const { return bank; }
    void setAccountBalance(long long account_balance) { this->Account_balance = account_balance; }
    void displayAccountInfo() const;
};

class Card {
private:
    long long Card_number;
    long long Card_password;
public:
    Card(long long Card_number, long long Card_password);
    ~Card();
    long long getCardNumber() const { return Card_number; }
    long long getCardPassword() const { return Card_password; }
};

// struct Account_Card {
//     Bank* bank;
//     Account* account;
//     Card* card;
// };

class User {
private:
    string user_name;
public:
    User(string user_name);
    ~User();
    string getUserName() const { return user_name; }
};

struct Account_Card;
class Atm;
class Bank {
private:
    string Bank_name;
    int bankID;
public:
    static vector<Bank*> bank_array;
    vector<Account_Card*> Account_Card_array;
    vector<Transaction*> Transaction_history_in_Bank;
    Bank(string Bank_name, int bankID);
    ~Bank();
    int getBankID() const { return bankID; }
    string getBankName() { return Bank_name; }

    card_verification_t Verification(long long card_num);
    transfer_condition_t operation_Transfer(long long src_account_num, long long destination_account_num, long long amount, int fee, transfer_t transfer_type);
    deposit_condition_t operation_Deposit(long long user_card_number, long long amount, paper_t paper_type, int fee, Atm* current_atm, Bank* bank = nullptr);
    withdrawal_condition_t operation_Withdrawal(long long user_card_number, long long amount, int fee, Atm* current_atm);
    void Open_account_info(Account* account);
};

struct Account_Card {
    Bank* bank;
    Account* account;
    Card* card;
    Account_Card(Bank* bank, Account* account, Card* card) : bank(bank), account(account), card(card) { bank->Account_Card_array.push_back(this); }
};

class Session {
private:
    static int session_count;
    int sessionID;
    long long user_card_number;
    bool isVerification;
    int withdrawal_count;
    string Condition;
    Bank* access_Bank;
    User* user;
public:
    vector<Transaction*> Transaction_array;
    Session(long long user_card_number);
    ~Session();
    // void setVerification(bool veri);
    string getCondition() { return Condition; }
    Bank* getAccessedBank() { return access_Bank; }
    int getWithdrawalCount() { return withdrawal_count; }
    void setCondition(const string& cnd) { Condition = cnd; }
    void increase_withdrawal_count() { withdrawal_count++; }
    card_verification_t requestVerification(long long user_card_number, Atm* using_atm);
    void displayTransaction() const;
    void Transactionhistory_file(ofstream* ofile) const;
};

enum cash_t { KRW_1000 = 1000, KRW_5000 = 5000, KRW_10000 = 10000, KRW_50000 = 50000 };

class Atm {
private:
    string filename;
    int index;
    long long admin_card_number;
    Bank* primary_bank;
    language_t language_type;
    available_t availablity;
    long long serial_number;
    long long atm_balance;
    int how_many_sessions;
    int update_cash[4] = { 0, };
    const cash_t cash[4] = { KRW_1000, KRW_5000, KRW_10000, KRW_50000 };
public:
    int number_of_cash[4] = { 0, };
    static vector<Atm*> Atm_list;
    vector<Session*> Session_array;
    Atm(Bank* primary_bank, language_t language_type, available_t availablity, int serial_number, long long admin_card_number, 
        int index, string filename, long long atm_balance = 10000000, int system_call_count = 0);
    ~Atm();
    available_t getAvailability() const { return availablity; }
    Bank* getPrimaryBank() const { return primary_bank; }
    long long getAtmBalance() const { return atm_balance; }
    language_t getLanguage_Type() const { return language_type; }
    string getfilename(){ return filename; }
    int* getUpdateCash() const {
        int* temp = new int[4];
        for (int i = 0; i < 4; i++)
            temp[i] = update_cash[i];
        return temp;
    }
    void setAtmBalance(long long amount) { this->atm_balance = amount; }
    void setUpdateCash(int* updating) { for (int i = 0; i < 4; i++) update_cash[i] = updating[i]; }
    void init_update_cash() { for (int i = 0; i < 4; i++) update_cash[i] = 0; }

    void start(int language);
    void go_Transfer(Bank* bank, long long src_account, long long destination_account, long long transfer_amount, transfer_t transfer_type, long long card_num, Session* current_session);
    void go_Deposit(Bank* bank, long long user_card_number, long long amount, paper_t paper_type, Session* current_session);
    void deposit_NumberOfCash(long long amount, int* cash_updating, Bank* bank = nullptr);
    void go_Withdrawal(Bank* bank, long long user_card_number, long long amount, Session* current_session);
    void withdrawal_NumberOfCash(long long amount, int* cash_updating);
    void update_number_of_cash(int* updating, transaction_t t) {
        for (int i = 0; i < 4; i++)
            number_of_cash[i] = (t == DEPOSIT || t == TRANSFER) ? number_of_cash[i] + update_cash[i] : number_of_cash[i] - update_cash[i];
    }
    void displayATMInfo() const;

    int want_end(int temp, ofstream* ofile, long long admin = 0) const;
};