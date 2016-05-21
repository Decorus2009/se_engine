#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

int main() {

    ifstream aver_res_for_all_incorrect("texts/incorrect/averaged_results/aver_res_for_all_incorrect.txt");
    ifstream aver_res_for_all_correct("texts/correct/averaged_results/aver_res_for_all_correct.txt");

    stringstream aver_res_for_all_incorrect_ss;
    stringstream aver_res_for_all_correct_ss;

    aver_res_for_all_incorrect_ss << aver_res_for_all_incorrect.rdbuf();
    aver_res_for_all_correct_ss << aver_res_for_all_correct.rdbuf();

    cout << endl << "Calculating average value for INCORRECT texts" << endl << endl;

    int num_incorr_texts = 11;

    string line;
    double aver_poss_mist_to_full_req_ratio = 0.0;
    double aver_remaining = 0.0;
    for (int i = 0; i < num_incorr_texts; ++i)
    {
        getline(aver_res_for_all_incorrect_ss, line);
        aver_poss_mist_to_full_req_ratio += stod(line);

        getline(aver_res_for_all_incorrect_ss, line);
        // хотя, можно просто 1 - poss_mist_to_full_req_ratio
        aver_remaining += stod(line);
    }


    cout << "RATIO: POSS MIST NUM TO FULL REQS NUM:"
         << setprecision(1) << setw(10)
         << fixed << aver_poss_mist_to_full_req_ratio / num_incorr_texts << "%" << endl;
    cout << "RATIO: REMAINING"
         << setprecision(1) << setw(32)
         << fixed << aver_remaining / num_incorr_texts << "%" << endl;


//    cout << setprecision(1) << fixed << aver_poss_mist_to_full_req_ratio / num_incorr_texts << "%" << endl;
//    cout << setprecision(1) << fixed << aver_remaining / num_incorr_texts << "%" << endl;

    cout << endl << "Calculating average for CORRECT texts" << endl << endl;

    int num_corr_texts = 17;
    aver_poss_mist_to_full_req_ratio = 0.0;
    aver_remaining = 0.0;
    for (int i = 0; i < num_corr_texts; ++i)
    {
        getline(aver_res_for_all_correct_ss, line);
        aver_poss_mist_to_full_req_ratio += stod(line);

        getline(aver_res_for_all_correct_ss, line);
        // хотя, можно просто 1 - poss_mist_to_full_req_ratio
        aver_remaining += stod(line);
    }


    cout << "RATIO: POSS MIST NUM TO FULL REQS NUM:"
    << setprecision(1) << setw(10) << fixed << aver_poss_mist_to_full_req_ratio / num_corr_texts << "%" << endl;
    cout << "RATIO: REMAINING"
    << setprecision(1) << setw(32) << fixed << aver_remaining / num_corr_texts << "%" << endl;

//    cout << setprecision(1) << fixed << aver_poss_mist_to_full_req_ratio / num_corr_texts << "%" << endl;
//    cout << setprecision(1) << fixed << aver_remaining / num_corr_texts << "%" << endl;

    return 0;
}