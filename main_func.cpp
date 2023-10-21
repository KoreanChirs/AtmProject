#include "atm.h"

int main() {
    int who;
    int lan = 1;
    int atm_index;
    int bank_index;
    long long account_num;
    string command;
    string cash_type[4] = { "KRW1000 : ", "KRW5000 : ", "KRW10000 : ", "KRW50000 : " };

    string path = "./ATM_history/";

    Bank* Kakao = new Bank("Kakao", 111);
    Bank* Daegu = new Bank("Daegu", 222);

    User* user_1 = new User("David");
    User* user_2 = new User("Jane");
    User* user_3 = new User("Kate");

    Account* a1 = new Account(Kakao, 111111111111, 5000, 1234, user_1);
    Account* a2 = new Account(Daegu, 222222222222, 5000, 1234, user_2);
    Account* a3 = new Account(Kakao, 111333333333, 5000, 1234, user_3); 

    Card* c1 = new Card(111222333444, 1234);
    Card* c2 = new Card(222222333444, 1234);
    Card* c3 = new Card(111222333555, 1234);

    Account_Card* ac1 = new Account_Card{ Kakao, a1, c1 };
    Account_Card* ac2 = new Account_Card{ Daegu, a2, c2 };
    Account_Card* ac3 = new Account_Card{ Kakao, a3, c3 };

    // Kakao->Account_Card_array.push_back(ac1);
    // Daegu->Account_Card_array.push_back(ac2);
    // Kakao->Account_Card_array.push_back(ac3);

    Atm* atm1 = new Atm(Kakao, UNI, SINGLE, 111111, 12345678, 0, "atm1", 4000);
    Atm* atm2 = new Atm(Daegu, BI, MULTI, 222222, 23456789, 1, "atm2", 4000);
    Atm* atm3 = new Atm(Daegu, BI, MULTI, 333333, 34567890, 2, "atm3", 4000);

    ofstream b;
    for (int i = 0; i < Atm::Atm_list.size(); i++) {
        b.open((path + Atm::Atm_list[i]->getfilename()).c_str(), fstream::out);
        b.close();
    }
    
    while (true) {
        lan = 1;
        Main:
            cout << "┏━━━━━━━━━━━ MAIN ━━━━━━━━━━┓" << endl;
            cout << "┃ Please enter a user type. ┃" << endl;
            cout << "┃---------------------------┃" << endl;
            cout << "┃ 1 : ATM Administrator     ┃" << endl;
            cout << "┃ 2 : ATM Client            ┃" << endl;
            cout << "┃ 3 : Bank Administarator   ┃" << endl;
            cout << "┃                           ┃" << endl;
            cout << "┃ 0 : Exit Program          ┃" << endl;
            cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
            cin >> who;
            if (cin_fail(cin) || (who != 0 && who != 1 && who != 2 && who != 3)) {
                display_Enter_Valid_Number();
                goto Main;
            }

        if ((who == 1) || (who == 2)) {
            Select_ATM:
                cout << "┏━━━━━━━━━━ MAIN ━━━━━━━━━━┓" << endl;
                cout << "┃ Please select a ATM.     ┃" << endl;
                cout << "┃--------------------------┃" << endl;
                cout << "┃ Primary Bank             ┃" << endl;
                for (int i = 0; i < Atm::Atm_list.size(); i++)
                    cout << "┃   " << i + 1 << " : " << left << setw(19) << Atm::Atm_list[i]->getPrimaryBank()->getBankName() << "┃" << endl;
                cout << "┃                          ┃" << endl;
                cout << "┃ 0 : Cancel               ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                cin >> atm_index;
                atm_index--;
            if (cin_fail(cin)) {
                display_Enter_Valid_Number();
                goto Select_ATM;
            }
            else if (atm_index == -1)
                goto Main;
            else if (!Atm::Atm_list.empty() && !(atm_index >= 0 && atm_index < Atm::Atm_list.size())) {
                display_Enter_Valid_Number();
                goto Select_ATM;
            }
            else if (who == 2 && Atm::Atm_list[atm_index]->getLanguage_Type() == BI) {
                Select_Language:
                    cout << "┏━━━━━━━━━━━ ATM ━━━━━━━━━━━┓" << endl;
                    cout << "┃ Please select a language. ┃" << endl;
                    cout << "┃---------------------------┃" << endl;
                    cout << "┃ 1 : English               ┃" << endl;
                    cout << "┃ 2 : Korean                ┃" << endl;
                    cout << "┃                           ┃" << endl;
                    cout << "┃ 0 : Cancel                ┃" << endl;
                    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                    cin >> lan;
                if (cin_fail(cin) || (lan != 0 && lan != 1 && lan != 2)) {
                    display_Enter_Valid_Number();
                    goto Select_Language;
                }
                else if (lan == 0)
                    goto Main;
                Atm::Atm_list[atm_index]->start(lan - 1);
            }
            else
                Atm::Atm_list[atm_index]->start(lan - 1);
        }
        else if (who == 3) {
            bool verify = false;
            Select_Admin_Bank:
                cout << "┏━━━━━━━━━━━━━ MAIN ━━━━━━━━━━━━━┓" << endl;
                cout << "┃ Please select a bank to admin. ┃" << endl;
                cout << "┃--------------------------------┃" << endl;
                for (int i = 0; i < Bank::bank_array.size(); i++)
                    cout << "┃ " << i + 1 << " : " << left << setw(27) << Bank::bank_array[i]->getBankName() << "┃" << endl;
                cout << "┃                                ┃" << endl;
                cout << "┃ 0 : Cancel                     ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                cin >> bank_index;
                bank_index--;
            if (cin_fail(cin)) {
                display_Enter_Valid_Number();
                goto Select_Admin_Bank;
            }
            else if (bank_index == -1)
                goto Main;
            else if (!Bank::bank_array.empty() && !(bank_index >= 0 && bank_index < Bank::bank_array.size())) {
                display_Enter_Valid_Number();
                goto Select_Admin_Bank;
            }

            int select;
            long long amount;
            vector<int> filter;
            int find_ok = false;

            Select_Bank_Menu:
                cout << "┏━━━━━━━━━━ BANK ━━━━━━━━━━┓" << endl;
                cout << "┃ Please select a mode.    ┃" << endl;
                cout << "┃--------------------------┃" << endl;
                cout << "┃ 1 : Admin User's Account ┃" << endl;
                cout << "┃ 2 : Deposit to ATM       ┃" << endl;
                cout << "┃ 3 : Display ATM Info     ┃" << endl;
                cout << "┃                          ┃" << endl;
                cout << "┃ 0 : Cancel               ┃" << endl;
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                cin >> select;
                if (cin_fail(cin) || (select != 1 && select != 2 && select != 3 && select != 0)) {
                    display_Enter_Valid_Number();
                    goto Select_Bank_Menu;
                } 

            if (select == 1) {
                Enter_Account_Number:
                    cout << "┏━━━━━━━━━━━━━ BANK ━━━━━━━━━━━━━┓" << endl;
                    cout << "┃ Please enter a account number. ┃" << endl;
                    cout << "┃                                ┃" << endl;
                    cout << "┃ 0 : Cancel                     ┃" << endl;
                    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                    cin >> account_num;
                if (cin_fail(cin) || (amount < 0 && (amount % KRW_1000 != 0))) {
                    display_Enter_Valid_Number();
                    goto Enter_Account_Number;
                }
                else if (account_num == 0) 
                    goto Main;

                for (int i = 0; i < Bank::bank_array[bank_index]->Account_Card_array.size(); i++) {
                    if (account_num == Bank::bank_array[bank_index]->Account_Card_array[i]->account->getAccountNumber()) {
                        Bank::bank_array[bank_index]->Open_account_info(Bank::bank_array[bank_index]->Account_Card_array[i]->account);
                        verify = true;
                        break;
                    }
                }
                if (!verify) {
                    cout << "┏━━━━━━━━━━━━━ BANK ━━━━━━━━━━━━━┓" << endl;
                    cout << "┃ ERROR : Invalid Account Number ┃" << endl;
                    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                    goto Select_Bank_Menu;
                }
            }
            else if (select == 2 || select == 3) {
                Select_ATM_in_Bank:
                    cout << "┏━━━━━━━━━━ BANK ━━━━━━━━━━┓" << endl;
                    cout << "┃ Please select a ATM.     ┃" << endl;
                    cout << "┃--------------------------┃" << endl;
                    cout << "┃ Manageable ATM           ┃" << endl;
                    for (int i = 0; i < Atm::Atm_list.size(); i++) {
                        if (Bank::bank_array[bank_index]->getBankID() == Atm::Atm_list[i]->getPrimaryBank()->getBankID()) {
                            cout << "┃    " << i + 1 << " : " << left << setw(17) << Atm::Atm_list[i]->getPrimaryBank()->getBankName() << " ┃" << endl;
                            filter.push_back(i);
                        }
                    }
                    cout << "┃                          ┃" << endl;
                    cout << "┃ 0 : Cancel               ┃" << endl;
                    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";
                cin >> atm_index;
                atm_index--;
                if (cin_fail(cin)) {
                    display_Enter_Valid_Number();
                    goto Select_ATM_in_Bank;
                }

                else if (atm_index == -1)
                    goto Main;

                for (int i : filter) {
                    if(i == atm_index){
                        find_ok = true;
                    }
                }
                if (find_ok == false) {
                    display_Enter_Valid_Number();
                    goto Select_ATM_in_Bank;
                }

                if (select == 3)
                    Atm::Atm_list[atm_index]->displayATMInfo();

                else {
                    AMOUNT:
                        cout << "┏━━━━━━━━━━━ ATM ━━━━━━━━━━━┓" << endl;
                        cout << "┃ Enter the deposit amount. ┃" << endl;
                        cout << "┃                           ┃" << endl; 
                        cout << "┃ 0 : Cancel                ┃" << endl;
                        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n> ";        
                        cin >> amount;

                    if (amount < 0 || (amount % KRW_1000 != 0)) {
                        display_Enter_Valid_Number();
                        goto AMOUNT;
                    }
                    else if (amount == 0)
                        goto Main;
                
                    Bank::bank_array[bank_index]->operation_Deposit(0, amount, CASH, 0, Atm::Atm_list[atm_index], Bank::bank_array[bank_index]);
                    cout << "┏━━━━━━ ATM ━━━━━━┓" << endl;
                    cout << "┃ Deposit Success ┃" << endl;
                    cout << "┃-----------------┃" << endl;
                    int* temp = Atm::Atm_list[atm_index]->getUpdateCash();
                    for (int i = 0; i < 4; i++)
                        cout << "┃ " << cash_type[i] << (i < 2 ? " " : "") << left << setw(5) << temp[i] << "┃" << endl;
                    cout << "┗━━━━━━━━━━━━━━━━━┛" << endl;
                    delete [] temp;
                }
            }
            else
                goto Main;
        }
        else if (who == 0)
            break;
    }

    // for (Bank* del_bank : Bank::bank_array) {
    //     for (Account_Card* del_account_card : del_bank->Account_Card_array) {
    //         for (int i = 0; i < del_account_card->account->Transaction_history_in_Account.size(); i++) {
    //             delete del_account_card->account->Transaction_history_in_Account[i];
    //             del_account_card->account->Transaction_history_in_Account[i] = nullptr;
    //         }
    //         delete del_account_card->account;
    //         del_account_card->account = nullptr;
    //         delete del_account_card->card;
    //         del_account_card->card = nullptr;
    //         delete del_account_card;
    //     }
    //     for (int i = 0; i < del_bank->Transaction_history_in_Bank.size(); i++) {
    //         delete del_bank->Transaction_history_in_Bank[i];
    //         del_bank->Transaction_history_in_Bank[i] = nullptr;
    //     }
    //     delete del_bank;
    //     del_bank = nullptr;
    // }

    // for (Atm* del_atm : Atm::Atm_list) {
    //     for (Session* del_session : del_atm->Session_array) {
    //         for (int i = 0; i < del_session->Transaction_array.size(); i++) {
    //             delete del_session->Transaction_array[i];
    //             del_session->Transaction_array[i] = nullptr;
    //         }
    //         delete del_session;
    //         del_session = nullptr;
    //     }
    //     delete del_atm;
    //     del_atm = nullptr;
    // }

    // delete user_1;
    // delete user_2;

    return 0;
}