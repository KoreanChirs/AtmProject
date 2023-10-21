#include "atm.h"
using namespace std;

int lan = 0;
string cash_type[4] = { "KRW1000 : ", "KRW5000 : ", "KRW10000 : ", "KRW50000 : " };

void display_Enter_Valid_Number() {
    if (lan == 0) {
        cout << "┏━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
        cout << "┃ ERROR : Invalid Input ┃" << endl;
        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    } else {
        cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl; // end
        cout << "┃ 오류 : 잘못된 입력입니다. ┃" << endl;
        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    }
}

bool cin_fail(istream& i) {
    if (i.fail()) {
        cin.clear();
        cin.ignore(256, '\n');
        return true;
    }
    return false;
}

int Transaction::transaction_count = 0;
Transaction::Transaction() : transactionID(transaction_count) { transaction_count += 2; }

Transaction::Transaction(const Transaction& other) {
    condition = other.condition;
    transaction_count = other.transaction_count;
    transactionID = other.transactionID;
    Amount = other.Amount;
    fee = other.fee;
    card_number = other.card_number;
}

Transaction::~Transaction() {}

void Transaction::displayTransactionInfo() const {
    if (lan == 0) {
        cout << "┃      ──────────────────────────────────── ┃" << endl;
        cout << "┃      Transaction ID : " << left << setw(20) << transactionID << "┃" << endl;
        cout << "┃      Card Number : " << left << setw(23) << card_number << "┃" << endl;
        cout << "┃      Transacted Amount : " << left << setw(17) << Amount << "┃" << endl;
        cout << "┃      Transacted Fee : " << left << setw(20) << fee << "┃" << endl;
        cout << "┃      Transaction condition :              ┃" << endl; //수정
        cout << "┃ " << right << setw(41) << condition << " ┃" << endl; //수정
    } else {
        cout << "┃      ────────────────────────────" << endl;
        cout << "┃      거래 번호 : " << transactionID << endl;
        cout << "┃      카드 번호 : " << card_number << endl;
        cout << "┃      거래 금액 : " << Amount << endl;
        cout << "┃         수수료 : " << fee << endl;
        cout << "┃      거래 결과 : " << condition << endl; //수정
    }
}

void Transaction::fileTransactioninfo(ofstream* ofile) const {
    if (lan == 0) {
        *ofile << "┃      ──────────────────────────────────── ┃" << endl;
        *ofile << "┃      Transaction ID : " << left << setw(20) << transactionID << "┃" << endl;
        *ofile << "┃      Card Number : " << left << setw(23) << card_number << "┃" << endl;
        *ofile << "┃      Transacted Amount : " << left << setw(17) << Amount << "┃" << endl;
        *ofile << "┃      Transacted Fee : " << left << setw(20) << fee << "┃" << endl;
        *ofile << "┃      Transaction condition :              ┃" << endl; //수정
        *ofile << "┃ " << right << setw(41) << condition << " ┃" << endl; //수정
    } else {
        *ofile << "┃      ────────────────────────────" << endl;
        *ofile << "┃      거래 번호 : " << transactionID << endl;
        *ofile << "┃      카드 번호 : " << card_number << endl;
        *ofile << "┃      거래 금액 : " << Amount << endl;
        *ofile << "┃         수수료 : " << fee << endl;
        *ofile << "┃      거래 결과 : " << condition << endl; //수정   
    }
}

Transaction_transfer::Transaction_transfer(long long srcAccount, long long dstAccount, transfer_t Transfer_type, long long Amount, long long card_number)
    : srcAccount(srcAccount), dstAccount(dstAccount), Transfer_type(Transfer_type) { this->Amount = Amount; this->card_number = card_number; }

Transaction_transfer::Transaction_transfer(const Transaction_transfer& other) : Transaction(other) {
    srcAccount = other.srcAccount;
    dstAccount = other.dstAccount;
    Transfer_type = other.Transfer_type;
}

Transaction_transfer::~Transaction_transfer() {}

void Transaction_transfer::displayTransactionInfo() const {
    Transaction::displayTransactionInfo();
    if (lan == 0) {
        cout << left << setw(46) << "┃      Transaction Type : Transfer" << "┃" << endl;
        cout << "┃      Transfer Type : " << left << setw(21) << (Transfer_type == CASH_TRANSFER ? "Cash Transfer" : "Account Transfer") << "┃" << endl;
        cout << (Transfer_type == CASH_TRANSFER ? "┃      Source Acc : None                    ┃\n" : "┃      Source Acc : ");
        if (srcAccount != -1)
            cout << left << setw(24) << srcAccount << "┃" << endl;
        cout << "┃      Destination Acc : " << left << setw(19) << dstAccount << "┃" << endl;
        cout << "┃      ──────────────────────────────────── ┃" << endl;
    } else {
        cout << left << setw(41) << "┃      거래 유형 : 이체" << endl;
        cout << "┃      이체 유형 : " << (Transfer_type == CASH_TRANSFER ? "현금 이체" : "계좌 이체") << endl;
        cout << (Transfer_type == CASH_TRANSFER ? "┃      보낸 계좌 : 없음\n" : "┃      보낸 계좌 : ");
        if (srcAccount != -1)
            cout << srcAccount << endl;
        cout << "┃      받는 계좌 : " << dstAccount << endl;
        cout << "┃      ────────────────────────────" << endl;
    }
}

void Transaction_transfer::fileTransactioninfo(ofstream* ofile) const {
    Transaction::fileTransactioninfo(ofile);
    if (lan == 0) {
        *ofile << left << setw(46) << "┃      Transaction Type : Transfer" << "┃" << endl;
        *ofile << "┃      Transfer Type : " << left << setw(21) << (Transfer_type == CASH_TRANSFER ? "Cash Transfer" : "Account Transfer") << "┃" << endl;
        *ofile << (Transfer_type == CASH_TRANSFER ? "┃      Source Acc : None                    ┃\n" : "┃      Source Acc : ");
        if (srcAccount != -1)
            *ofile << left << setw(24) << srcAccount << "┃" << endl;
        *ofile << "┃      Destination Acc : " << left << setw(19) << dstAccount << "┃" << endl;
        *ofile << "┃      ──────────────────────────────────── ┃" << endl;
    } else {
        *ofile << "┃      거래 유형 : 이체" << endl;
        *ofile << "┃      이체 유형 : " << (Transfer_type == CASH_TRANSFER ? "현금 이체" : "계좌 이체") << endl;
        *ofile << (Transfer_type == CASH_TRANSFER ? "┃      보낸 계좌 : 없음\n" : "┃      보낸 계좌 : ");
        if (srcAccount != -1)
            *ofile << srcAccount << endl;
        *ofile << "┃      받는 계좌 : " << dstAccount << endl;
        *ofile << "┃      ────────────────────────────" << endl;
    }
}

Transaction_deposit::Transaction_deposit(paper_t Paper_type, long long Amount, long long card_number)
    : Paper_type(Paper_type) { this->Amount = Amount; this->card_number = card_number; }

Transaction_deposit::Transaction_deposit(const Transaction_deposit& other) : Transaction(other) { Paper_type = other.Paper_type; }

Transaction_deposit::~Transaction_deposit() {}

void Transaction_deposit::displayTransactionInfo() const {
    Transaction::displayTransactionInfo();
    if (lan == 0) {
        cout << "┃      Transaction Type : Deposit           ┃" << endl;
        cout << "┃      Deposit Paper Type : " << (Paper_type == CASH ? "Cash            ┃" : "Check           ┃") << endl;
        cout << "┃      ──────────────────────────────────── ┃" << endl;
    } else {
        cout << "┃      거래 유형 : 입금" << endl;
        cout << "┃      입금 유형 : " << (Paper_type == CASH ? "현금" : "수표") << endl;
        cout << "┃      ────────────────────────────" << endl;
    }
}

void Transaction_deposit::fileTransactioninfo(ofstream* ofile) const {
    Transaction::fileTransactioninfo(ofile);
    if (lan == 0) {
        *ofile << "┃      Transaction Type : Deposit           ┃" << endl;
        *ofile << "┃      Deposit Paper Type : " << (Paper_type == CASH ? "Cash            ┃" : "Check           ┃") << endl;
        *ofile << "┃      ──────────────────────────────────── ┃" << endl;
    } else {
        *ofile << "┃      거래 유형 : 입금" << endl;
        *ofile << "┃      입금 유형 : " << (Paper_type == CASH ? "현금" : "수표") << endl;
        *ofile << "┃      ────────────────────────────" << endl;
    }
}

Transaction_withdrawal::Transaction_withdrawal(long long amount, long long card_number) { this->Amount = amount; this->card_number = card_number; }

Transaction_withdrawal::Transaction_withdrawal(const Transaction_withdrawal& other) : Transaction(other) {}

Transaction_withdrawal::~Transaction_withdrawal() {}

void Transaction_withdrawal::displayTransactionInfo() const {
    Transaction::displayTransactionInfo();
    if (lan == 0) {
        cout << "┃      Transaction Type : Withdrawal        ┃" << endl;
        cout << "┃      ──────────────────────────────────── ┃" << endl;
    } else {
        cout << "┃      거래 유형 : 출금" << endl;
        cout << "┃      ────────────────────────────" << endl;
    }
}

void Transaction_withdrawal::fileTransactioninfo(ofstream* ofile) const{
    Transaction::fileTransactioninfo(ofile);
    if (lan == 0) {
        *ofile << "┃      Transaction Type : Withdrawal        ┃" << endl;
        *ofile << "┃      ──────────────────────────────────── ┃" << endl;
    } else {
        *ofile << "┃      거래 유형 : 출금" << endl;
        *ofile << "┃      ────────────────────────────" << endl;
    }
} 

Account::Account(Bank* bank, long long account_number, long long account_balance, long long account_password, User* user)
    : bank(bank), Account_number(account_number), Account_balance(account_balance), Account_password(account_password), user(user) {}

Account::~Account() {}

void Account::displayAccountInfo() const {
    if (lan == 0) {
        cout << "┏━━━━━━━━━━━━━━━━━━━ BANK ━━━━━━━━━━━━━━━━━━┓" << endl;
        cout << "┃ Bank Name : " << left << setw(30) << bank->getBankName() << "┃" << endl;
        cout << "┃ User Name : " << left << setw(30) << user->getUserName() << "┃" << endl;
        cout << "┃ Account Number : " << left << setw(25) << Account_number << "┃" << endl;
        cout << "┃ Available Funds : " << left << setw(24) << Account_balance << "┃" << endl;
        cout << "┃ Transaction History : " << right << setw(23) << "┃" << endl;
        for (int i = 0; i < Transaction_history_in_Account.size(); i++)
            Transaction_history_in_Account[i]->displayTransactionInfo();
        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    } else {
        cout << "┏━━━━━━━━━━━━━━ BANK ━━━━━━━━━━━━━━" << endl;
        cout << "┃ 은행 이름 : " << bank->getBankName() << endl;
        cout << "┃ 고객 이름 : " << user->getUserName() << endl;
        cout << "┃ 계좌 번호 : " << Account_number << endl;
        cout << "┃ 남은 잔액 : " << Account_balance << endl;
        cout << "┃ 거래 내역 : " << endl;
        for (int i = 0; i < Transaction_history_in_Account.size(); i++)
            Transaction_history_in_Account[i]->displayTransactionInfo();
        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    }
}

Card::Card(long long Card_number, long long Card_password) : Card_number(Card_number), Card_password(Card_password) {}

Card::~Card() {}

User::User(string user_name) : user_name(user_name) {}

User::~User() {}

vector<Bank*> Bank::bank_array;
Bank::Bank(string Bank_name, int bankID) : Bank_name(Bank_name), bankID(bankID) { bank_array.push_back(this); }

Bank::~Bank() {}

card_verification_t Bank::Verification(long long card_num) {
    for (int i = 0; i < Account_Card_array.size(); i++) {
        if (card_num == Account_Card_array[i]->card->getCardNumber()) {
            long long password;
            for (int k = 0; k < 3; k++) {
                if (lan == 0) {
                    cout << "┏━━━━━━━━━━━━ ATM ━━━━━━━━━━━━┓" << endl;
                    cout << "┃ Please enter your password. ┃" << endl;
                    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                } else {
                    cout << "┏━━━━━━━━━━━━ ATM ━━━━━━━━━━┓" << endl; // end
                    cout << "┃ 비밀번호를 입력해 주세요. ┃" << endl;
                    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                }
                cin >> password;
                if (cin_fail(cin)) {
                    k--;
                    continue;
                }

                if (password == Account_Card_array[i]->card->getCardPassword())
                    return SUCCESS;
                else {
                    if (lan == 0) {
                        cout << "┏━━━━━━━━━━━ ATM ━━━━━━━━━━┓" << endl;
                        cout << "┃ ERROR : Invalid Password ┃" << endl;
                        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                    } else {
                        cout << "┏━━━━━━━━━━ ATM ━━━━━━━━━━┓" << endl; // end
                        cout << "┃ 잘못된 비밀번호 입니다. ┃" << endl;
                        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                    }
                }
            }
            return WRONG_PASSWORD;
        }
    }
    return WRONG_CARD;
}

void append_AccountHistory(Bank* accessed_bank, long long card_num, long long account_num, Transaction* transaction) {
    for (int i = 0; i < accessed_bank->Account_Card_array.size(); i++) {
        if (accessed_bank->Account_Card_array[i]->card->getCardNumber() == card_num 
        || accessed_bank->Account_Card_array[i]->account->getAccountNumber() == account_num) {
            accessed_bank->Account_Card_array[i]->account->Transaction_history_in_Account.push_back(transaction);
            break;
        }
    }
}

transfer_condition_t Bank::operation_Transfer(long long src_account_num, long long destination_account_num, long long amount, int fee, transfer_t transfer_type) {
    Account* src_account = nullptr;
    Account* des_account = nullptr;
    for (int i = 0; i < Bank::bank_array.size(); i++) {
        if (static_cast<int>(destination_account_num / pow(10, 9)) == Bank::bank_array[i]->bankID) {
            for (int j = 0; j < Bank::bank_array[i]->Account_Card_array.size(); j++) {
                if (destination_account_num == Bank::bank_array[i]->Account_Card_array[j]->account->getAccountNumber()) {
                    des_account = Bank::bank_array[i]->Account_Card_array[j]->account;
                    break;
                }
            }
            break;
        }
    }
    if (des_account == nullptr)
        return NO_DST;

    if (transfer_type == ACCOUNT_TRANSFER) {
        for (int i = 0; i < Account_Card_array.size(); i++) {
            if (src_account_num == Account_Card_array[i]->account->getAccountNumber()) {
                src_account = Account_Card_array[i]->account;
                if (src_account->getAccountBalance() >= (amount + fee)) {
                    long long now_balance = src_account->getAccountBalance() - amount - fee;
                    src_account->setAccountBalance(now_balance);
                    break;
                }
                else
                    return TRANS_NO_MONEY;
            }
        }
    }
    if (transfer_type == ACCOUNT_TRANSFER && src_account == nullptr)
        return NO_SRC_ACCOUNT;

    long long new_balance = des_account->getAccountBalance() + amount;//dst
    des_account->setAccountBalance(new_balance);
    return TRANS_SUCCESS;
}

deposit_condition_t Bank::operation_Deposit(long long user_card_number, long long amount, paper_t paper_type, int fee, Atm* current_atm, Bank* bank) {
    int sum = 0;
    long long temp_amount = amount;
    if (paper_type == CHECK) {
        if (amount % 100000 != 0)
            return INVALID_DEPOSIT_TYPE;
        else {
            sum += (amount / 1000000);
            amount %= 1000000;
            sum += (amount / 500000);
            amount %= 500000;
            sum += (amount / 100000);
            if (sum > 30)
                return EXCEED_DEPO;
        }
    }
    else if (paper_type == CASH) {
        int cash_updating[4] = { 0, };
        current_atm->deposit_NumberOfCash(amount, cash_updating, bank);
        for (int i = 0; i < 4; i++) 
            sum += cash_updating[i];
        if (sum > 50 && user_card_number != 0)
            return EXCEED_DEPO;
        else {
            current_atm->setUpdateCash(cash_updating);
            current_atm->setAtmBalance(temp_amount + current_atm->getAtmBalance());
            current_atm->update_number_of_cash(cash_updating, DEPOSIT);
        }
    }

    if (user_card_number != 0) {
        for (int i = 0; i < Account_Card_array.size(); i++) {
            if (user_card_number == Account_Card_array[i]->card->getCardNumber()){
                long long now_balance = Account_Card_array[i]->account->getAccountBalance() + amount - fee;
                Account_Card_array[i]->account->setAccountBalance(now_balance);
                break;
            }
        }
    }
    return DEPO_SUCCESS;
}

withdrawal_condition_t Bank::operation_Withdrawal(long long user_card_number, long long amount, int fee, Atm* current_atm) {
    if ((amount % KRW_1000) != 0)
        return INVALID_AMOUNT;
    if (amount > 500000) 
        return EXCEED_LIMIT;

    int num_cash[4] = { 0, };
    int sum = 0;
    for (int i = 0; i < Account_Card_array.size(); i++) {
        if (user_card_number == Account_Card_array[i]->card->getCardNumber()) {
            if (Account_Card_array[i]->account->getAccountBalance() >= (amount + fee)) { 
                current_atm->withdrawal_NumberOfCash(amount, num_cash);
                for (int i : num_cash) 
                    sum += i;
                if (sum > 50) 
                    return EXCEED_WITH;
                else {
                    if (amount > current_atm->getAtmBalance() || current_atm->number_of_cash[0] <= num_cash[0])
                        return ATM_NO_MONEY;
                    else {
                        long long new_balance = Account_Card_array[i]->account->getAccountBalance() - (amount + fee);
                        Account_Card_array[i]->account->setAccountBalance(new_balance);
                        current_atm->setAtmBalance(current_atm->getAtmBalance() - amount);
                        current_atm->setUpdateCash(num_cash);
                        current_atm->update_number_of_cash(num_cash, WITHDRAWAL);
                        break;
                    }
                }
            }
            else
                return WITH_NO_MONEY; // 있는 돈 보다 더 뽑으려고 함.
        }
    }
    return WITH_SUCCESS;
}

void Bank::Open_account_info(Account* account) {
    if (account->getBank()->getBankID() == bankID) {
        account->displayAccountInfo();
    } else {
        if (lan == 0) {
            cout << "┏━━━━━━━━━ BANK ━━━━━━━━━┓" << endl;
            cout << "┃ ERROR : Invalid Access ┃" << endl;
            cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
        } else {
            cout << "┏━━━━━━━━━━━━ BANK ━━━━━━━━━━━━┓" << endl;
            cout << "┃ 오류 : 잘못된 접근입니다. ┃" << endl;
            cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
        }
        return;
    }
}

int Session::session_count = 1;
Session::Session(long long user_card_number) 
    : sessionID(session_count), user_card_number(user_card_number), isVerification(false), withdrawal_count(0) { 
        if (lan == 0) {
            cout << "┏━━━━━━ ATM ━━━━━━┓" << endl;
            cout << "┃ Session Begins. ┃" << endl;
            cout << "┃                 ┃" << endl;
            cout << "┃ -> Verifying... ┃" << endl;
            cout << "┗━━━━━━━━━━━━━━━━━┛" << endl;
        } else {
            cout << "┏━━━━━━━━━━ ATM ━━━━━━━━━┓" << endl;
            cout << "┃ 세션이 시작되었습니다. ┃" << endl;
            cout << "┃                        ┃" << endl;
            cout << "┃ -> 카드 확인중...      ┃" << endl;
            cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
        }
        session_count += 2; 
    }

Session::~Session() {}

card_verification_t Session::requestVerification(long long user_card_number, Atm* using_atm) {
    int bank_id = static_cast<int>(user_card_number / pow(10, 9));
    card_verification_t verify;
    bool isVerification = false;
    for (int i = 0; i < Bank::bank_array.size(); i++) {
        if (bank_id == Bank::bank_array[i]->getBankID()) {
            if (using_atm->getAvailability() == SINGLE && using_atm->getPrimaryBank()->getBankID() != bank_id) {
                if (lan == 0) {
                    setCondition("ERROR : Single Availability");
                    cout << "┏━━━━━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━━━━━┓" << endl;
                    cout << "┃ ERROR : Single Availability (Session Ends) ┃" << endl;
                    cout << "┃                                            ┃" << endl;
                    cout << "┃ Please use another card.                   ┃" << endl;
                    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                } else {
                    setCondition("오류 : 주거래 은행만 사용 가능");
                    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━━━━━━━━━┓" << endl; // end
                    cout << "┃ 오류 : 주거래 은행만 사용 가능합니다. (세션 종료) ┃" << endl;
                    cout << "┃                                                   ┃" << endl;
                    cout << "┃ 다른 카드를 사용해 주세요.                        ┃" << endl;
                    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                }
                return WRONG_ATM;
            } // single availablity error
            verify = Bank::bank_array[i]->Verification(user_card_number);
            isVerification = (verify == SUCCESS) ? true : false;
            access_Bank = Bank::bank_array[i];
            return verify;
        }
    }
    return WRONG_CARD;
}

void Session::displayTransaction() const {
    if (lan == 0) {
        cout << "┏━━━━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━━━━━┓" << endl;
        if (Transaction_array.empty())
            cout << "┃ Transaction History : There is No History ┃" << endl;
        else {
            cout << "┃ Transaction History :                     ┃" << endl;
            for (int i = 0; i < Transaction_array.size(); i++)
                Transaction_array[i]->displayTransactionInfo();
        }
        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    } else {
        cout << "┏━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━" << endl;
        if (Transaction_array.empty())
            cout << "┃ 거래 내역 : 내역 없음" << endl;
        else {
            cout << "┃ 거래 내역 : " << endl;
            for (int i = 0; i < Transaction_array.size(); i++)
                Transaction_array[i]->displayTransactionInfo();
        }
        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    }
}

void Session::Transactionhistory_file(ofstream* ofile) const{
    if (lan == 0) {
        *ofile << "┏━━━━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━━━━━┓" << endl;
        if (Transaction_array.empty())
            *ofile << "┃ Transaction Histroy : There is No History ┃" << endl;
        else {
            *ofile << "┃ Transaction History :                     ┃" << endl;
            for (int i = 0; i < Transaction_array.size(); i++)
                Transaction_array[i]->fileTransactioninfo(ofile);
        }
        *ofile << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    } else {
        *ofile << "┏━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━" << endl;
        if (Transaction_array.empty())
            *ofile << "┃ 거래 내역 : 내역 없음" << endl;
        else {
            *ofile << "┃ 거래 내역 : " << endl;
            for (int i = 0; i < Transaction_array.size(); i++)
                Transaction_array[i]->fileTransactioninfo(ofile);
        }
        *ofile << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;    
    }
}

vector<Atm*> Atm::Atm_list;
Atm::Atm(Bank* primary_bank, language_t language_type, available_t availablity, int serial_number, long long admin_card_num,
    int index, string filename, long long atm_balance, int system_call_count)
    : primary_bank(primary_bank), atm_balance(atm_balance), language_type(language_type), availablity(availablity), filename(filename +(string)(".txt")), 
    serial_number(serial_number), how_many_sessions(0), index(index), admin_card_number(admin_card_num) {
        Atm_list.push_back(this);
        int number[4] = { 0, };
        deposit_NumberOfCash(atm_balance, number, primary_bank);
        for (int i = 0; i < 4; i++)
            number_of_cash[i] = number[i];
    }

Atm::~Atm() {}

int Atm::want_end(int temp, ofstream* ofile, long long admin) const {
    int want_finish = 0;
    while (!want_finish) {
        if (lan == 0) {
            cout << "┏━━━━━━━━━━━━ ATM ━━━━━━━━━━━┓" << endl;
            cout << "┃ Do you want to finish ATM? ┃" << endl;
            cout << "┃----------------------------┃" << endl;
            cout << "┃ 0 : No                     ┃" << endl;
            cout << "┃ 1 : Yes                    ┃" << endl;
            cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
        } else {
            cout << "┏━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━┓" << endl;
            cout << "┃ ATM 사용을 그만두시겠습니까? ┃" << endl;
            cout << "┃------------------------------┃" << endl;
            cout << "┃ 0 : 아니오                   ┃" << endl;
            cout << "┃ 1 : 예                       ┃" << endl;
            cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
        }
        cin >> want_finish;
        if (cin_fail(cin) || (want_finish != 0 && want_finish != 1)) {
            display_Enter_Valid_Number();
            continue;
        }
        else if (!want_finish)
            return want_finish;
    }

    if (how_many_sessions > 0 && (!Session_array[how_many_sessions - 1]->Transaction_array.empty())) {
        int receipt;
        Receipt:
            if (lan == 0) {
                cout << "┏━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━┓" << endl;
                cout << "┃ Do you want to print reciept? ┃" << endl;
                cout << "┃-------------------------------┃" << endl;
                cout << "┃ 0 : No                        ┃" << endl;
                cout << "┃ 1 : Yes                       ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
            } else {
                cout << "┏━━━━━━━━━━━━ ATM ━━━━━━━━━━━━┓" << endl;
                cout << "┃ 명세표를 출력 하시겠습니까? ┃" << endl;
                cout << "┃-----------------------------┃" << endl;
                cout << "┃ 0 : 아니오                  ┃" << endl;
                cout << "┃ 1 : 예                      ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
            }
            cin >> receipt;
            if (cin_fail(cin) || (receipt != 0 && receipt != 1)) {
                display_Enter_Valid_Number();
                goto Receipt;
            }
            
        if (receipt) {
            for (int i = temp; i < how_many_sessions; i++)
                Session_array[i]->displayTransaction();
        }
        if (admin == 0)
            Session_array[how_many_sessions - 1]->Transactionhistory_file(ofile);
    }
    ofile->close();
    return want_finish;
}

int fee;
void Atm::start(int language) {
    lan = language;
    long long card_num;
    Session* new_session = nullptr;
    Transaction* transaction_for_session = nullptr;
    Transaction* transaction_for_bank = nullptr;
    Transaction* transaction_for_account = nullptr;
    int want_transaction;
    bool is_session_end = false;
    int temp = how_many_sessions;
    
    string path = "./ATM_history/";

    ofstream a;
    ofstream* ofile = &a;
    ofile->open((path + filename).c_str(), fstream::out | fstream::app);
    
    Beginning :
        if (is_session_end == true) {
            if (lan == 0) {
                cout << "┏━━━━━ ATM ━━━━━┓" << endl;
                cout << "┃ Session Ends. ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━┛" << endl;
            } else {
                cout << "┏━━━━━━━━━━ ATM ━━━━━━━━━┓" << endl;
                cout << "┃ 세션이 종료되었습니다. ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
            }
            Session_array[how_many_sessions - 1]->displayTransaction();
            Session_array[how_many_sessions - 1]->Transactionhistory_file(ofile); // session 끝났을 때 내역 보여주는 친구
        }

        while (true) {
            if (lan == 0) {
                cout << "┏━━━━━━━━━━━━ ATM ━━━━━━━━━━━━┓" << endl;
                cout << "┃ Please enter a card number. ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
            } else {
                cout << "┏━━━━━━━━━━━━ ATM ━━━━━━━━━━━━┓" << endl; // end
                cout << "┃ 카드 번호를 입력해 주세요.  ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
            }
            cin >> card_num;
            if (cin_fail(cin)) { display_Enter_Valid_Number(); continue; }

            if (card_num == admin_card_number) {
                ADMIN_TRAN:
                    if (lan == 0) {
                        cout << "┏━━━━━━━━━━ ATM ━━━━━━━━━━━┓" << endl;
                        cout << "┃ 1 : Transaction History  ┃" << endl;
                        cout << "┃                          ┃" << endl;
                        cout << "┃ 0 : Cancel               ┃" << endl;
                        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                    } else {
                        cout << "┏━━━━━ ATM ━━━━━┓" << endl; // end
                        cout << "┃ 1 : 거래 내역 ┃" << endl;
                        cout << "┃               ┃" << endl;
                        cout << "┃ 0 : 취소      ┃" << endl;
                        cout << "┗━━━━━━━━━━━━━━━┛\n> ";
                    }
                    cin >> want_transaction;
                if (cin_fail(cin) || (want_transaction != 0 && want_transaction != 1)) {
                    display_Enter_Valid_Number();
                    goto ADMIN_TRAN;
                }
                if (want_transaction) {
                    struct stat st{};
                    stat((path + filename).c_str(), &st);
                    if (st.st_size == 0) {
                        if (lan == 0) {
                            cout << "┏━━━━━━━━━━ ATM ━━━━━━━━━┓" << endl;
                            cout << "┃ No transaction history ┃" << endl;
                            cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                        } else {
                            cout << "┏━━━━━━━━━ ATM ━━━━━━━━━┓" << endl; // end
                            cout << "┃ 거래 내역이 없습니다. ┃" << endl;
                            cout << "┗━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                        }
                    } 
                    else {
                        string line;
                        ifstream file(path + filename);
                        if (file.is_open()) {
                            while (getline(file, line))
                                cout << line << endl;
                            file.close();
                        }
                        cout.clear();
                    }
                }
                if (want_end(how_many_sessions, ofile, card_num)) 
                    return;
                else 
                    goto Beginning;
            }

            new_session = new Session(card_num); // session (동적 할당)
            init_update_cash();
            is_session_end = true;
            Session_array.push_back(new_session);
            how_many_sessions++;
            card_verification_t verify = new_session->requestVerification(card_num, this);
            if (verify == SUCCESS) {
                if (lan == 0) {
                    cout << "┏━━━━━━ ATM ━━━━━┓" << endl;
                    cout << "┃ Verified Card. ┃" << endl;
                    cout << "┗━━━━━━━━━━━━━━━━┛" << endl;
                } else {
                    cout << "┏━━━━━━━━━━ ATM ━━━━━━━━━┓" << endl; // end
                    cout << "┃ 카드가 확인되었습니다. ┃" << endl;
                    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                }
                break;
            }
            else if (verify == WRONG_CARD) {
                if (lan == 0) {
                    cout << "┏━━━━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━━━━━┓" << endl;
                    cout << "┃ ERROR : Wrong card number. (Session Ends) ┃" << endl;
                    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                } else {
                    cout << "┏━━━━━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━━━━━━┓" << endl; // end
                    cout << "┃ 오류 : 잘못된 카드 번호 입니다. (세션 종료) ┃" << endl;
                    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                }
                continue;
            }
            else if (verify == WRONG_PASSWORD) {
                if (lan == 0) {
                    cout << "┏━━━━━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━━━━━━┓" << endl;
                    cout << "┃ ERROR : Wrong card Password. (Session Ends) ┃" << endl;
                    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                } else {
                    cout << "┏━━━━━━━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━━━━━━━━┓" << endl; // end
                    cout << "┃ 오류 : 잘못된 카드 비밀번호 입니다. (세션 종료) ┃" << endl;
                    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                }
                continue;
            }
        }
    
    Bank* accessed_bank = new_session->getAccessedBank();
    transaction_t trans_t;
    int out = 0;
    while (!out) {
        init_update_cash();
        bool isIn = false;
        // select transaction
        while (!isIn) {
            if (lan == 0) {
                cout << "┏━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━┓" << endl;
                cout << "┃ Please enter a transaction type. ┃" << endl;
                cout << "┃----------------------------------┃" << endl;
                cout << "┃ 1 : Transfer                     ┃" << endl;
                cout << "┃ 2 : Deposit                      ┃" << endl;
                cout << "┃ 3 : Withdrawal                   ┃" << endl;
                cout << "┃                                  ┃" << endl; 
                cout << "┃ 0 : Cancel                       ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
            } else {
                cout << "┏━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━┓" << endl; // end
                cout << "┃ 원하시는 거래를 선택해 주세요. ┃" << endl;
                cout << "┃--------------------------------┃" << endl;
                cout << "┃ 1 : 이체                       ┃" << endl;
                cout << "┃ 2 : 입금                       ┃" << endl;
                cout << "┃ 3 : 출금                       ┃" << endl;
                cout << "┃                                ┃" << endl; 
                cout << "┃ 0 : 취소                       ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
            }
            cin >> trans_t;
            isIn = isIn_enum(trans_t);
            if (cin_fail(cin) || !isIn)
                display_Enter_Valid_Number();
        }
        // selected and switch
        switch (trans_t) {
            long long amount;
            case transaction_t::TRANSFER:
                transfer_t transfer_type;
                isIn = false;
                while (!isIn) {
                    if (lan == 0) {
                        cout << "┏━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━┓" << endl;
                        cout << "┃ Please enter a transfer type. ┃" << endl;
                        cout << "┃-------------------------------┃" << endl;
                        cout << "┃ 1 : Cash                      ┃" << endl;
                        cout << "┃ 2 : Account                   ┃" << endl;
                        cout << "┃                               ┃" << endl; 
                        cout << "┃ 0 : Cancel                    ┃" << endl;
                        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                    } else {
                        cout << "┏━━━━━━━━━━━━ ATM ━━━━━━━━━━━━┓" << endl; // end
                        cout << "┃ 이체 형식을 선택해 주세요.  ┃" << endl;
                        cout << "┃-----------------------------┃" << endl;
                        cout << "┃ 1 : 현금                    ┃" << endl;
                        cout << "┃ 2 : 계좌                    ┃" << endl;
                        cout << "┃                             ┃" << endl; 
                        cout << "┃ 0 : 취소                    ┃" << endl;
                        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                    }
                    cin >> transfer_type;
                    isIn = isIn_enum(transfer_type);
                    if (cin_fail(cin) || !isIn)
                        display_Enter_Valid_Number();
                }

                if (transfer_type == TRANSFER_CANCEL) {
                    Transfer_Cancel:
                        if (lan == 0) {
                            new_session->setCondition("Transfer Cancel");
                            cout << "┏━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━┓" << endl;
                            cout << "┃ Transfer Canceled. (Session Ends) ┃" << endl;
                            cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                        } else {
                            new_session->setCondition("이체 취소");
                            cout << "┏━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━┓" << endl; // end
                            cout << "┃ 이체가 취소되었습니다. (세션 종료) ┃" << endl;
                            cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                        }
                        new_session->displayTransaction();
                        is_session_end = false;
                        
                    if (want_end(temp, ofile))
                        return;
                    else {
                        Session_array[how_many_sessions - 1]->Transactionhistory_file(ofile);
                        goto Beginning;
                    }
                }

                long long dst_account;
                Enter_Dst_Account:
                    if (lan == 0) {
                        cout << "┏━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━┓" << endl;
                        cout << "┃ Enter the destination accont. ┃" << endl;
                        cout << "┃                               ┃" << endl; 
                        cout << "┃ 0 : Cancel                    ┃" << endl;
                        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                    } else {
                        cout << "┏━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━┓" << endl; // end
                        cout << "┃ 받는 사람의 계좌를 입력해 주세요. ┃" << endl;
                        cout << "┃                                   ┃" << endl; 
                        cout << "┃ 0 : 취소                          ┃" << endl;
                        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                    }
                    cin >> dst_account;
                    if (cin_fail(cin)) { display_Enter_Valid_Number(); goto Enter_Dst_Account; }

                if (dst_account == 0) goto Transfer_Cancel;

                long long src_account;
                src_account = -1;
                if (transfer_type == ACCOUNT_TRANSFER) {
                    Enter_Src_Account:
                        if (lan == 0) {
                            cout << "┏━━━━━━━━━━━ ATM ━━━━━━━━━━┓" << endl;
                            cout << "┃ Enter the source accont. ┃" << endl;
                            cout << "┃                          ┃" << endl;
                            cout << "┃ 0 : Cancel               ┃" << endl;
                            cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                        } else {
                            cout << "┏━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━┓" << endl; // end
                            cout << "┃ 보낼 사람의 계좌를 입력해 주새요. ┃" << endl;
                            cout << "┃                                   ┃" << endl;
                            cout << "┃ 0 : 취소                          ┃" << endl;
                            cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                        }
                        cin >> src_account;
                        if (cin_fail(cin)) { display_Enter_Valid_Number(); goto Enter_Src_Account; }

                    if (src_account == 0) goto Transfer_Cancel;
                }
                
                while (true) {
                    if (lan == 0) {
                        cout << "┏━━━━━━━━━━━━ ATM ━━━━━━━━━━━┓" << endl;
                        cout << "┃ Enter the transfer amount. ┃" << endl;
                        cout << "┃                            ┃" << endl; 
                        cout << "┃ 0 : Cancel                 ┃" << endl;
                        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                    } else {
                        cout << "┏━━━━━━━━━━━━ ATM ━━━━━━━━━━━━┓" << endl; // end
                        cout << "┃ 보낼 금액을 입력해 주세요.  ┃" << endl;
                        cout << "┃                             ┃" << endl; 
                        cout << "┃ 0 : 취소                    ┃" << endl;
                        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                    }
                    cin >> amount;
                    if (cin_fail(cin)) { display_Enter_Valid_Number(); continue; }
                    
                    if (amount == 0) 
                        goto Transfer_Cancel;
                    else if (amount < 0 || (transfer_type == CASH_TRANSFER && (amount % KRW_1000 != 0)))
                        display_Enter_Valid_Number();
                    else
                        break;
                }

                transaction_for_session = new Transaction_transfer(src_account, dst_account, transfer_type, amount, card_num); // 동적 할당
                this->go_Transfer(accessed_bank, src_account, dst_account, amount, transfer_type, card_num, new_session);
                transaction_for_session->setFee(fee);
                Session_array[how_many_sessions - 1]->Transaction_array.push_back(transaction_for_session);

                if (new_session->getCondition() == "Transfer Cancel" || new_session->getCondition() == "이체 취소") {
                    transaction_for_session->setTransaction_Condition(new_session->getCondition());
                    goto Transfer_Cancel;
                }

                transaction_for_session->setTransaction_Condition(new_session->getCondition());
                transaction_for_bank = new Transaction_transfer(*(dynamic_cast<Transaction_transfer*>(transaction_for_session)));
                transaction_for_account = new Transaction_transfer(*(dynamic_cast<Transaction_transfer*>(transaction_for_session)));
                transaction_for_bank->setTransaction_Condition(new_session->getCondition());
                transaction_for_account->setTransaction_Condition(new_session->getCondition());
                accessed_bank->Transaction_history_in_Bank.push_back(transaction_for_bank);

                int dst_bank_id;
                dst_bank_id = static_cast<int>(dst_account / pow(10, 9));
                for (int i = 0; i < Bank::bank_array.size(); i++) {
                    if (Bank::bank_array[i]->getBankID() == dst_bank_id) {
                        Transaction_transfer *transaction_for_bank_2, *transaction_for_account_2;
                        transaction_for_bank_2 = new Transaction_transfer(*(dynamic_cast<Transaction_transfer*>(transaction_for_session)));
                        transaction_for_account_2 = new Transaction_transfer(*(dynamic_cast<Transaction_transfer*>(transaction_for_session)));
                        Bank::bank_array[i]->Transaction_history_in_Bank.push_back(transaction_for_bank_2);
                        append_AccountHistory(Bank::bank_array[i], 0, dst_account, transaction_for_account_2);
                    }
                }
                append_AccountHistory(accessed_bank, card_num, 0, transaction_for_account);
                if (new_session->getCondition() != "Transfer Success" && new_session->getCondition() != "이체 성공")
                    goto Beginning; 
                // destination account valid check
                break;
            case transaction_t::DEPOSIT:
                paper_t paper_type;
                isIn = false;
                while (!isIn) {
                    if (lan == 0) {
                        cout << "┏━━━━━━━━━━ ATM ━━━━━━━━━┓" << endl;
                        cout << "┃ Enter your paper type. ┃" << endl;
                        cout << "┃------------------------┃" << endl;
                        cout << "┃ 1 : Cash               ┃" << endl; 
                        cout << "┃ 2 : Check              ┃" << endl;
                        cout << "┃                        ┃" << endl; 
                        cout << "┃ 0 : Cancel             ┃" << endl;
                        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                    } else {
                        cout << "┏━━━━━━━━━━━━ ATM ━━━━━━━━━━━┓" << endl; // end
                        cout << "┃ 입금 유형을 선택해 주세요. ┃" << endl;
                        cout << "┃----------------------------┃" << endl;
                        cout << "┃ 1 : 현금                   ┃" << endl; 
                        cout << "┃ 2 : 수표                   ┃" << endl;
                        cout << "┃                            ┃" << endl; 
                        cout << "┃ 0 : 취소                   ┃" << endl;
                        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                    }
                    cin >> paper_type;
                    isIn = isIn_enum(paper_type);
                    if (cin_fail(cin) || !isIn)
                        display_Enter_Valid_Number();
                }

                if (paper_type == PAPER_CANCEL) {
                    Deposit_Cancel:
                        if (lan == 0) {
                            new_session->setCondition("Deposit Cancel");
                            cout << "┏━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━┓" << endl;
                            cout << "┃ Deposit Canceled. (Session Ends) ┃" << endl;
                            cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                        } else {
                            new_session->setCondition("입금 취소");
                            cout << "┏━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━┓" << endl; // end
                            cout << "┃ 입금이 취소되었습니다. (세션 종료) ┃" << endl;
                            cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                        }
                        new_session->displayTransaction();
                        is_session_end = false;

                    if (want_end(temp, ofile))
                        return;
                    else {
                        Session_array[how_many_sessions - 1]->Transactionhistory_file(ofile);
                        goto Beginning;
                    }
                }
                
                while (true) {
                    if (lan == 0) {
                        cout << "┏━━━━━━━━━━━ ATM ━━━━━━━━━━━┓" << endl;
                        cout << "┃ Enter the deposit amount. ┃" << endl;
                        cout << "┃                           ┃" << endl; 
                        cout << "┃ 0 : Cancel                ┃" << endl;
                        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                    } else {
                        cout << "┏━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━┓" << endl; // end
                        cout << "┃ 입금할 금액을 입력해 주세요. ┃" << endl;
                        cout << "┃                              ┃" << endl; 
                        cout << "┃ 0 : 취소                     ┃" << endl;
                        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                    }
                    cin >> amount;
                    if (cin_fail(cin)) { display_Enter_Valid_Number(); continue; }

                    if (amount == 0)
                        goto Deposit_Cancel;
                    else if (amount < 0 || (amount % KRW_1000 != 0))
                        display_Enter_Valid_Number();
                    else
                        break;
                }

                transaction_for_session = new Transaction_deposit(paper_type, amount, card_num); // 동적 할당
                this->go_Deposit(accessed_bank, card_num, amount, paper_type, new_session);
                transaction_for_session->setFee(fee);
                transaction_for_session->setTransaction_Condition(new_session->getCondition());

                transaction_for_bank = new Transaction_deposit(*(dynamic_cast<Transaction_deposit*>(transaction_for_session)));
                transaction_for_account = new Transaction_deposit(*(dynamic_cast<Transaction_deposit*>(transaction_for_session)));
                transaction_for_bank->setTransaction_Condition(new_session->getCondition());
                transaction_for_account->setTransaction_Condition(new_session->getCondition());
                
                accessed_bank->Transaction_history_in_Bank.push_back(transaction_for_bank);
                Session_array[how_many_sessions - 1]->Transaction_array.push_back(transaction_for_session);
                append_AccountHistory(accessed_bank, card_num, 0, transaction_for_account);
                if (new_session->getCondition() != "Deposit Success" && new_session->getCondition() != "입금 성공")
                    goto Beginning;
                break;
            case transaction_t::WITHDRAWAL:
                if (new_session->getWithdrawalCount() >= 3) {
                    if (lan == 0) {
                        cout << "┏━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━┓" << endl;
                        cout << "┃ Withdraw only 3 times per Session. ┃" << endl;
                        cout << "┃                                    ┃" << endl;
                        cout << "┃ --> Session Sucessfully Ends.      ┃" << endl;
                        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                    } else {
                        cout << "┏━━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━━━┓" << endl;
                        cout << "┃ 출금은 한 세션에 3번까지 가능합니다.  ┃" << endl;
                        cout << "┃                                       ┃" << endl;
                        cout << "┃ --> 세션이 성공적으로 종료되었습니다. ┃" << endl;
                        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                    }
                    if (want_end(temp, ofile))
                        return;
                    else {
                        Session_array[how_many_sessions - 1]->Transactionhistory_file(ofile);
                        goto Beginning;
                    }
                }

                while (true) {
                    if (lan == 0) {
                        cout << "┏━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━┓" << endl;
                        cout << "┃ Enter the withdrawal amount. " << "(" << new_session->getWithdrawalCount() + 1 << "/3)" << " ┃" << endl;
                        cout << "┃                                    ┃" << endl;
                        cout << "┃ Limit : 500,000                    ┃" << endl;
                        cout << "┃                                    ┃" << endl; 
                        cout << "┃ 0 : Cancel                         ┃" << endl;
                        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                    } else {
                        cout << "┏━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━┓" << endl; // end
                        cout << "┃ 출금할 금액할 입력해 주세요. " << "(" << new_session->getWithdrawalCount() + 1 << "/3)" << "┃" << endl;
                        cout << "┃                                   ┃" << endl;
                        cout << "┃ 한도 : 500,000                    ┃" << endl;
                        cout << "┃                                   ┃" << endl; 
                        cout << "┃ 0 : 취소                          ┃" << endl;
                        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                    }
                    cin >> amount;
                    if (cin_fail(cin)) { display_Enter_Valid_Number(); continue; }

                    if (amount < 0 || (amount % KRW_1000 != 0))
                        display_Enter_Valid_Number();
                    else
                        break;
                }

                if (amount == 0) {
                    if (lan == 0) {
                        new_session->setCondition("Withdrawal Cancel");
                        cout << "┏━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━━┓" << endl;
                        cout << "┃ Withdrawal Canceled. (Session Ends) ┃" << endl;
                        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                    } else {
                        new_session->setCondition("출금 취소");
                        cout << "┏━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━┓" << endl; // end
                        cout << "┃ 출금이 취소되었습니다. (세션 종료) ┃" << endl;
                        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                    }
                    new_session->displayTransaction();
                    is_session_end = false;

                    if (want_end(temp, ofile))
                        return;
                    else {
                        Session_array[how_many_sessions - 1]->Transactionhistory_file(ofile);
                        goto Beginning;
                    }
                }       

                transaction_for_session = new Transaction_withdrawal(amount, card_num); // 동적 할당
                this->go_Withdrawal(accessed_bank, card_num, amount, new_session);
                transaction_for_session->setFee(fee);
                transaction_for_session->setTransaction_Condition(new_session->getCondition());

                transaction_for_bank = new Transaction_withdrawal(*(dynamic_cast<Transaction_withdrawal*>(transaction_for_session)));
                transaction_for_account = new Transaction_withdrawal(*(dynamic_cast<Transaction_withdrawal*>(transaction_for_session)));
                transaction_for_bank->setTransaction_Condition(new_session->getCondition());
                transaction_for_account->setTransaction_Condition(new_session->getCondition());
                accessed_bank->Transaction_history_in_Bank.push_back(transaction_for_bank);
                Session_array[how_many_sessions - 1]->Transaction_array.push_back(transaction_for_session);

                append_AccountHistory(accessed_bank, card_num, 0, transaction_for_account);
                if (new_session->getCondition() != "Withdrawal Success" && new_session->getCondition() != "출금 성공") 
                    goto Beginning;
                new_session->increase_withdrawal_count();
                break;
            case transaction_t::CANCEL:
                if (lan == 0) {
                    new_session->setCondition("Transaction Cancel");
                    cout << "┏━━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━━┓" << endl;
                    cout << "┃ Transaction Canceled. (Session Ends) ┃" << endl;
                    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                } else {
                    new_session->setCondition("거래 취소");
                    cout << "┏━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━┓" << endl;
                    cout << "┃ 거래가 취소되었습니다. (세션 종료) ┃" << endl;
                    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                }
                new_session->displayTransaction();
                is_session_end = false;
                if (want_end(temp, ofile))
                    return;
                else {
                    Session_array[how_many_sessions - 1]->Transactionhistory_file(ofile);
                    goto Beginning;
                }
        }

        Continue_Stop :
            if (lan == 0) {
                cout << "┏━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━┓" << endl;
                cout << "┃ Do you want to stop transaction? ┃" << endl;
                cout << "┃----------------------------------┃" << endl;
                cout << "┃ 0 : No                           ┃" << endl;
                cout << "┃ 1 : Yes                          ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
            } else {
                cout << "┏━━━━━━━━━━━ ATM ━━━━━━━━━━━┓" << endl;
                cout << "┃ 거래를 종료 하시겠습니까? ┃" << endl;
                cout << "┃---------------------------┃" << endl;
                cout << "┃ 0 : 아니오                ┃" << endl;
                cout << "┃ 1 : 예                    ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
            }
            cin >> out;
            if (cin_fail(cin) || (out != 0 && out != 1)) {
                display_Enter_Valid_Number();
                goto Continue_Stop;
            }

        if (out) {
            if (lan == 0) {
                cout << "┏━━━━━━━━━━━━ ATM ━━━━━━━━━━━┓" << endl;
                cout << "┃ Session Successfully Ends. ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
            } else {
                cout << "┏━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━┓" << endl;
                cout << "┃ 세션이 성공적으로 종료되었습니다. ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
            }
            new_session->displayTransaction();
            is_session_end = false;
        }
    }

    if (want_end(temp, ofile))
        return;
    else {
        Session_array[how_many_sessions-1]->Transactionhistory_file(ofile);
        goto Beginning;
    }
}

void Atm::go_Transfer(Bank* card_bank, long long src_account, long long destination_account, long long amount, transfer_t transfer_type, long long card_num, Session* current_session) {
    int src_bank_id = static_cast<int>((transfer_type == CASH_TRANSFER) ? card_num / pow(10, 9) : src_account / pow(10, 9));
    int des_bank_id = static_cast<int>(destination_account / pow(10,9));
    long long insert_cash;
    fee = 3000;
    if ((primary_bank->getBankID() == src_bank_id && primary_bank->getBankID() == des_bank_id)) 
        fee = 2000;
    else if ((primary_bank->getBankID() != src_bank_id && primary_bank->getBankID() != des_bank_id))
        fee = 4000;

    if (transfer_type == CASH_TRANSFER) {
        while (true) {
            if (lan == 0) {
                cout << "┏━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━┓" << endl;
                cout << "┃ Please insert cashes " << left << setw(8) << setfill('_') << amount + fee << " ┃" << endl; // 돈 적절히 넣었는지 예외처리
                cout << setfill(' ');
                cout << "┃                               ┃" << endl;
                cout << "┃ 0 : Cancel                    ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
            } else {
                cout << "┏━━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━━┓" << endl; // end
                cout << "┃ " << left << setw(8) << setfill('_') << amount + fee << left << setw(36) << "원을 현금 창구에 넣어주세요." << " ┃" << endl;
                cout << setfill(' ');
                cout << "┃                                      ┃" << endl;
                cout << "┃ 0 : 취소                             ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
            }
            cin >> insert_cash;
            if (cin_fail(cin)) {
                display_Enter_Valid_Number();
                continue;
            }

            else if (insert_cash == 0) {
                if (lan == 0)
                    current_session->setCondition("Transfer Cancel");
                else
                    current_session->setCondition("이체 취소");
                return;
            }
            if (insert_cash != amount + fee) {
                if (lan == 0) {
                    cout << "┏━━━━━━━━━━ ATM ━━━━━━━━━┓" << endl;
                    cout << "┃ ERROR : Invalid Amount ┃" << endl;
                    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                } else {
                    cout << "┏━━━━━━━━━━━ ATM ━━━━━━━━━━━┓" << endl; // end
                    cout << "┃ 오류 : 잘못된 금액입니다. ┃" << endl;
                    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                }
            }
            else
                break;
        }
    }

    transfer_condition_t issuccess = card_bank->operation_Transfer(src_account, destination_account, amount, fee, transfer_type);
    switch (issuccess) {
        case transfer_condition_t::TRANS_SUCCESS:
            if (transfer_type == CASH_TRANSFER) {
                int number[4] = { 0, };
                deposit_NumberOfCash(amount + fee, number);
                update_number_of_cash(number, TRANSFER);
                setAtmBalance(amount + fee + getAtmBalance());
            }
            if (lan == 0) {
                cout << "┏━━━━━━━ ATM ━━━━━━┓" << endl;
                cout << "┃ Transfer Success ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("Transfer Success");
            } else {
                cout << "┏━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━┓" << endl; // end
                cout << "┃ 이체가 성공적으로 이루어졌습니다. ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("이체 성공");
            }
            break;
        case transfer_condition_t::NO_DST:
            if (lan == 0) {
                cout << "┏━━━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━━┓" << endl;
                cout << "┃ ERROR : Incorrect Destination Account ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("ERROR - Incorrect destination account");
            } else {
                cout << "┏━━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━┓" << endl; // end
                cout << "┃ 오류 : 받는 계좌가 없는 계좌입니다. ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("오류 - 받는 계좌가 없는 계좌입니다.");
            }
            break;
        case transfer_condition_t::TRANS_NO_MONEY:
            if (lan == 0) {
                cout << "┏━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━┓" << endl;
                cout << "┃ ERROR : Not Enough Account Balance ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("ERROR - Not Enough Account Balance");
            } else {
                cout << "┏━━━━━━━━━━━ ATM ━━━━━━━━━━━┓" << endl; // end
                cout << "┃ 오류 : 잔액이 부족합니다. ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("오류 - 잔액이 부족합니다.");
            }
            break;
        case transfer_condition_t::NO_SRC_ACCOUNT:
            if (lan == 0) {
                cout << "┏━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━┓" << endl;
                cout << "┃ ERROR : Incorrect Source Account ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("ERROR - Incorrect Source Account");
            } else {
                cout << "┏━━━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━━┓" << endl; // end
                cout << "┃ 오류 : 보내는 계좌가 없는 계좌입니다. ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("오류 - 보내는 계좌가 없는 계좌입니다.");
            }
            break;
    }
}

void Atm::go_Deposit(Bank* card_bank, long long user_card_number, long long amount, paper_t paper_type, Session* current_session) {
    fee = (card_bank->getBankID() == primary_bank->getBankID()) ? 0 : 1000;
    deposit_condition_t issuccess = card_bank->operation_Deposit(user_card_number, amount, paper_type, fee, this);
    switch (issuccess) {
        case deposit_condition_t::INVALID_DEPOSIT_TYPE:
            if (lan == 0) {
                cout << "┏━━━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━━━━┓" << endl;
                cout << "┃ ERROR : Invalid Deposit Type(Not Check) ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("ERROR - Invalid Deposit Type(Not Check)");
            } else {
                cout << "┏━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━┓" << endl; // end
                cout << "┃ 오류 : 잘못된 입금 유형입니다. ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("오류 - 잘못된 입금 유형입니다.");
            }
            break;
        case deposit_condition_t::DEPO_SUCCESS:
            if (lan == 0) {
                cout << "┏━━━━━━━ ATM ━━━━━┓" << endl;
                cout << "┃ Deposit Success ┃" << endl;
                cout << "┃-----------------┃" << endl;
                for (int i = 0; i < 4; i++)
                    cout << "┃ " << cash_type[i] << (i < 2 ? " " : "") << left << setw(5) << update_cash[i] << "┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("Deposit Success");
            } else {
                cout << "┏━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━┓" << endl; // end
                cout << "┃ 입금이 성공적으로 이루어졌습니다. ┃" << endl;
                cout << "┃-----------------------------------┃" << endl;
                for (int i = 0; i < 4; i++)
                    cout << "┃ " << cash_type[i] << (i < 2 ? " " : "") << left << setw(23) << update_cash[i] << "┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("입금 성공");
            }
            break;
        case deposit_condition_t::EXCEED_DEPO:
            if (lan == 0) {
                cout << "┏━━━━━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━━━━┓" << endl;
                cout << "┃ ERROR : Exceeded Cash/Check Slot Capacity ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("ERROR - Exceeded Cash/Check Slot Capacity");
            } else {
                cout << "┏━━━━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━━━┓" << endl; // end
                cout << "┃ 오류 : 현금 창구의 용량을 초과했습니다. ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("오류 - 현금 창구의 용량을 초과했습니다.");
            }
            break;
    }
}

void Atm::deposit_NumberOfCash(long long amount, int* cash_updating, Bank* bank) {
    double count;
    if (amount < 1000) 
        return;
    else if (amount < 5000) {
        cash_updating[0] += amount / KRW_1000;
        return;
    }
    else if (amount < 10000) {
        cash_updating[1] += amount / KRW_5000; 
        amount %= KRW_5000;
        deposit_NumberOfCash(amount, cash_updating);
    }
    else if (amount < 25000) {
        cash_updating[2] += amount / KRW_10000; 
        amount %= KRW_10000;
        deposit_NumberOfCash(amount, cash_updating);
    }
    else if (amount < 50000) {
        count = amount / (4.3 * pow(10, 4));
        cash_updating[0] += floor(count * 0.5);
        cash_updating[1] += floor(count * 0.5);
        cash_updating[2] += floor(count * 4);
        amount -= (KRW_1000 * floor(count * 0.5) + KRW_5000 * floor(count * 0.5) + KRW_10000 * floor(count * 4));
        deposit_NumberOfCash(amount, cash_updating);
    }
    else if (amount < 250000) {
        cash_updating[3] += amount / KRW_50000;
        amount %= 50000;
        deposit_NumberOfCash(amount, cash_updating);
    }
    else if (amount < 500000 || bank != nullptr) {
        double w = (bank == nullptr) ? 1 : 0.7;
        count = amount / ((2.6 + 30 * w) * pow(10, 4));
        cash_updating[0] += floor(count * 1);
        cash_updating[1] += floor(count * 1);
        cash_updating[2] += floor(count * 2);
        cash_updating[3] += floor(count * 6 * w);
        amount -= (KRW_1000 * floor(count) + KRW_5000 * floor(count) + KRW_10000 * floor(count * 2) + KRW_50000 * floor(count * (6 * w)));
        deposit_NumberOfCash(amount, cash_updating);
    }
    else {
        cash_updating[3] += amount / KRW_50000;
        amount %= KRW_50000;
        deposit_NumberOfCash(amount, cash_updating);
    }
    return;
}

void Atm::go_Withdrawal(Bank* card_bank, long long user_card_number, long long amount, Session* current_session) {
    fee = (card_bank->getBankID() == primary_bank->getBankID()) ? 1000 : 2000;
    withdrawal_condition_t issuccess = card_bank->operation_Withdrawal(user_card_number, amount, fee, this);
    if (lan == 0) {
        switch (issuccess) {
            case withdrawal_condition_t::WITH_SUCCESS:
                cout << "┏━━━━━━━━ ATM ━━━━━━━┓" << endl;
                cout << "┃ Withdrawal Success ┃" << endl;
                cout << "┃--------------------┃" << endl;
                for (int i = 0; i < 4; i++)
                    cout << "┃ " << cash_type[i] << (i < 2 ? " " : "") << left << setw(8) << update_cash[i] << "┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("Withdrawal Success");
                break;
            case withdrawal_condition_t::WITH_NO_MONEY:
                cout << "┏━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━┓" << endl;
                cout << "┃ ERROR : Not Enough Account Balance ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("ERROR - Not Enough Account Balance");
                break;
            case withdrawal_condition_t::EXCEED_LIMIT:
                cout << "┏━━━━━━━━━ ATM ━━━━━━━━┓" << endl;
                cout << "┃ ERROR : Exceed Limit ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("ERROR - Exceed Limit");
                break;
            case withdrawal_condition_t::ATM_NO_MONEY:
                cout << "┏━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━┓" << endl;
                cout << "┃ ERROR : Not Enough ATM Balance ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("ERROR - Not Enough ATM Balance");
                break;
            case withdrawal_condition_t::INVALID_AMOUNT:
                cout << "┏━━━━━━━━━━ ATM ━━━━━━━━━┓" << endl;
                cout << "┃ ERROR : Invalid Amount ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("ERROR - Invalid Amount");
                break;
            case withdrawal_condition_t::EXCEED_WITH:
                cout << "┏━━━━━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━━━━┓" << endl;
                cout << "┃ ERROR : Exceeded Cash/Check Slot Capacity ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("ERROR - Exceeded Cash/Check Slot Capacity");
                break;
        }
    } else {
        switch (issuccess) {
            case withdrawal_condition_t::WITH_SUCCESS:
                cout << "┏━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━┓" << endl; // end
                cout << "┃ 출금이 성공적으로 이루어졌습니다. ┃" << endl;
                cout << "┃-----------------------------------┃" << endl;
                for (int i = 0; i < 4; i++)
                    cout << "┃ " << cash_type[i] << (i < 2 ? " " : "") << left << setw(23) << update_cash[i] << "┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("출금 성공");
                break;
            case withdrawal_condition_t::WITH_NO_MONEY:
                cout << "┏━━━━━━━━━━━ ATM ━━━━━━━━━━━┓" << endl; // end
                cout << "┃ 오류 : 잔액이 부족합니다. ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("오류 - 잔액이 부족합니다.");
                break;
            case withdrawal_condition_t::EXCEED_LIMIT:
                cout << "┏━━━━━━━━━━━━ ATM ━━━━━━━━━━━━┓" << endl; // end
                cout << "┃ 오류 : 한도를 초과했습니다. ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("오류 - 한도를 초과했습니다.");
                break;
            case withdrawal_condition_t::ATM_NO_MONEY:
                cout << "┏━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━┓" << endl; // end
                cout << "┃ 오류 : ATM 잔액이 부족합니다. ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("오류 - ATM 잔액이 부족합니다.");
                break;
            case withdrawal_condition_t::INVALID_AMOUNT:
                cout << "┏━━━━━━━━━━━ ATM ━━━━━━━━━━━┓" << endl; // end
                cout << "┃ 오류 : 잘못된 금액입니다. ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("오류 - 잘못된 금액입니다.");
                break;
            case withdrawal_condition_t::EXCEED_WITH:
                cout << "┏━━━━━━━━━━━━━━━━━━━ ATM ━━━━━━━━━━━━━━━━━┓" << endl; // end
                cout << "┃ 오류 : 현금 창구의 용량을 초과했습니다. ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                current_session->setCondition("오류 - 현금 창구의 용량을 초과했습니다.");
                break;
        }
    }
}

void Atm::withdrawal_NumberOfCash(long long amount, int* cash_updating) {
    int desired[4] = { 0, };
    int is_desired[4] = { 0, };
    
    for (int i = 3; i >= 0; i--) {
        desired[i] = amount / cash[i];
        amount -= ((number_of_cash[i] >= desired[i]) ? cash[i] * desired[i] : cash[i] * number_of_cash[i]);
        if (i != 0) {
            cash_updating[i] = (number_of_cash[i] >= desired[i]) ? desired[i] : number_of_cash[i];
        } else {
            cash_updating[i] = desired[i];
        }
    }
}


void Atm::displayATMInfo() const {
    cout << "┏━━━━━━━━ ATM INFO ━━━━━━━━┓" << endl;
    cout << "┃ Primary Bank : " << left << setw(10) << primary_bank->getBankName() << "┃" << endl;
    cout << "┃ Available : " << left << setw(13) << ((availablity == SINGLE) ? "Single" : "Multi") << "┃" << endl;
    cout << "┃ Serial Number : " << left << setw(9) << serial_number << "┃" << endl;
    cout << "┃ ATM balance : " << left << setw(11) << atm_balance << "┃" << endl;
    cout << "┃ Number Of Money :        ┃" << endl;
    for (int i = 0; i < 4; i++)
        cout << "┃      " << cash_type[i] << (i < 2 ? " " : "") << setw(9) << number_of_cash[i] << "┃" << endl;
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
}