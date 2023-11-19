#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

map<string, int> createAnswerMapping() {
    map<string, int> answerMapping;
    answerMapping.insert(make_pair("A", 1));
    answerMapping.insert(make_pair("B", 2));
    answerMapping.insert(make_pair("C", 3));
    answerMapping.insert(make_pair("D", 4));
    return answerMapping;
}

struct SurveyResponse {
    vector<int> answers;
    int party;
};

void writeUserResponse(const vector<int>& userResponses, int predictedParty) {
    string partyFileName;

    switch (predictedParty) {
        case 1:
            partyFileName = "Republican.txt";
            break;
        case 2:
            partyFileName = "Democrat.txt";
            break;
        case 3:
            partyFileName = "GreenParty.txt";
            break;
        case 4:
            partyFileName = "Libertarian.txt";
            break;
        default:
            partyFileName = "Unknown.txt";
            break;
    }

    ofstream outFile(partyFileName.c_str(), ios::app);

    if (!outFile) {
        cerr << "Error opening " << partyFileName << " file for writing." << endl;
        return;
    }

    for (int i = 0; i < userResponses.size(); i++) {
        outFile << userResponses[i] << " ";
    }
    outFile << endl;

    outFile.close();
}

int main() {
    vector<string> partyNames;
    partyNames.push_back("Republican");
    partyNames.push_back("Democrat");
    partyNames.push_back("GreenParty");
    partyNames.push_back("Libertarian");

    vector<SurveyResponse> trainingData;
    SurveyResponse response;

    // =========== TRAINING DATA ================
    response.answers.push_back(2);  // Support work requirements and reduced government assistance
    response.answers.push_back(4);  // Favor lower taxes, especially for high-income earners
    response.answers.push_back(3);  // Support balanced environmental policies
    response.answers.push_back(4);  // Favor free-market competition and limited government involvement in healthcare
    response.answers.push_back(1);  // Promote school choice and voucher programs
    response.answers.push_back(2);  // Support gun rights and oppose stricter gun control laws
    response.party = 1; // Republican
    trainingData.push_back(response);
    response.answers.clear();

    response.answers.push_back(1);  // Build on welfare programs to address poverty
    response.answers.push_back(3);  // Favor a balanced approach to taxation based on income and wealth
    response.answers.push_back(1);  // Advocate for stronger environmental regulations to protect the planet
    response.answers.push_back(2);  // Support a public healthcare system with expanded access and affordability
    response.answers.push_back(2);  // Support increased funding for public schools and teacher training
    response.answers.push_back(4);  // Support stricter gun control laws to enhance public safety
    response.party = 2; // Democrat
    trainingData.push_back(response);
    response.answers.clear();

    response.answers.push_back(3);  // Promote private charity initiatives
    response.answers.push_back(1);  // Advocate for progressive taxation to address income inequality
    response.answers.push_back(4);  // Oppose strict environmental regulations to promote economic growth
    response.answers.push_back(1);  // Favor a single-payer healthcare system for universal coverage
    response.answers.push_back(3);  // Advocate for comprehensive education reform
    response.answers.push_back(3);  // Advocate for moderate gun control measures to balance public safety and gun rights
    response.party = 3; // GreenParty
    trainingData.push_back(response);
    response.answers.clear();

    response.answers.push_back(4);  // Oppose government intervention in poverty alleviation
    response.answers.push_back(2);  // Oppose government intervention in the economy, such as that government taxation is considered theft
    response.answers.push_back(2);  // Promote market-based solutions for environmental challenges
    response.answers.push_back(3);  // Oppose government-run healthcare and support individual responsibility.
    response.answers.push_back(4);  // Oppose government involvement in education and advocate for school choice
    response.answers.push_back(1);  // Favor the unrestricted right to bear arms and oppose most gun control laws
    response.party = 4; // Libertarian
    trainingData.push_back(response);

    map<string, int> answerMapping = createAnswerMapping();

    cout << "Welcome to the Political Party Survey!" << endl;
    cout << "Please answer the following questions to determine your political affiliation." << endl;
    cout << endl;
    
    // ============== QUESTIONS ==============
    vector<string> questions;
    questions.push_back("Q1: What should the government do to help the poor?");
    questions.push_back("Q2: What is your stance on taxation?");
    questions.push_back("Q3: What is your position on environmental regulations?");
    questions.push_back("Q4: What is your view on healthcare?");
    questions.push_back("Q5: What are your thoughts on education reform?");
    questions.push_back("Q6: How do you feel about gun control laws?");
    
    // ============== ANSWERS ===============
    vector<vector<string> > answerOptions;
    
    vector<string> q1Options;
    q1Options.push_back("Build on welfare programs, increasing government assistance to address poverty."); // D
    q1Options.push_back("Support work requirements and reduced government assistance."); // R
    q1Options.push_back("Promote private charity initiatives."); // G
    q1Options.push_back("Oppose government intervention."); // L
    answerOptions.push_back(q1Options);
    
    vector<string> q2Options;
    q2Options.push_back("Advocate for progressive taxation so that higher earners pay more, to address income inequality."); // G
    q2Options.push_back("Oppose government intervention in the economy, such as that government taxation is considered theft."); // L
    q2Options.push_back("Favor a balanced approach to taxation based on income and wealth."); // D
    q2Options.push_back("Support lower taxes, especially for high-income earners."); // R
    answerOptions.push_back(q2Options);

    vector<string> q3Options;
    q3Options.push_back("Advocate for stronger environmental regulations to protect the planet."); // D
    q3Options.push_back("Promote market-based solutions for environmental challenges."); // L
    q3Options.push_back("Support balanced environmental policies that consider both economic and environmental concerns."); // R
    q3Options.push_back("Oppose strict environmental regulations to promote economic growth."); // G
    answerOptions.push_back(q3Options);

    vector<string> q4Options;
    q4Options.push_back("Favor a single-payer healthcare system for universal coverage."); // G
    q4Options.push_back("Support a public healthcare system with expanded access and affordability."); // D
    q4Options.push_back("Oppose government involvement in healthcare and support individual responsibility."); // L
    q4Options.push_back("Advocate for free-market competition and limited government involvement in healthcare."); // R
    answerOptions.push_back(q4Options);

    vector<string> q5Options;
    q5Options.push_back("Promote school choice and voucher programs to increase competition and parental control."); // R
    q5Options.push_back("Support increased funding for public schools and teacher training."); // D
    q5Options.push_back("Advocate for comprehensive education reform, including increased funding and better teacher training."); // G
    q5Options.push_back("Oppose government involvement in education and advocate forschool choice."); // L
    answerOptions.push_back(q5Options);

    vector<string> q6Options;
    q6Options.push_back("Favor the unrestricted right to bear arms and oppose most gun control laws."); // L
    q6Options.push_back("Support gun rights and oppose stricter gun control laws."); // R
    q6Options.push_back("Advocate for moderate gun control measures to balance public safety and gun rights."); // G
    q6Options.push_back("Support stricter gun control laws to enhance public safety."); // D
    answerOptions.push_back(q6Options);
    
    vector<int> userResponses;

    for (int i = 0; i < questions.size(); i++) {
        cout << questions[i] << endl;
        for (int j = 0; j < answerOptions[i].size(); j++) {
            cout << static_cast<char>('A' + j) << ". " << answerOptions[i][j] << endl;
        }

        string answer;
        cin >> answer;
        
        while (cin.fail() ||  answer < 1 || answer > 4)
        {
        	cout << "Please enter a number between 1 and 4: " << endl;
        	cin.clear();
        	cin.ignore(100000000, '\n');
        	cin >> answer
		}

        userResponses.push_back(answerMapping[answer]);
    }

    int predictedParty = -1;
    int maxMatches = 0;

    for (int i = 0; i < trainingData.size(); ++i) {
        const SurveyResponse& response = trainingData[i];
        int matches = 0;
        for (int j = 0; j < response.answers.size(); ++j) {
            if (response.answers[j] == userResponses[j]) {
                matches++;
            }
        }

        if (matches > maxMatches) {
            predictedParty = response.party;
            maxMatches = matches;
        }
    }

    string party = (predictedParty > 0 && predictedParty <= partyNames.size()) ? partyNames[predictedParty - 1] : "Unknown";

    cout << "Based on your responses, your predicted political party affiliation is: " << party << endl;

    writeUserResponse(userResponses, predictedParty);

    return 0;
}


