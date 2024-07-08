// Project UID db1f506d06d84ab787baf250c265e24e
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <math.h>
#include "csvstream.h"

using namespace std;

class Classifier{
private:
    int post_count = 0;
    set<string> vocab;
    map<string, int> word_count;
    map<string, int> label_count;
    map<string, map<string,int>> label_word_count;
    set<string> tag;
    
public:
    void print_error(){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
    }

    // EFFECTS: Return a set of unique whitespace delimited words.x
    set<string> unique_words(const string &str) {
        istringstream source(str);
        set<string> words;
        string word;
        while (source >> word) {
            words.insert(word);
        }
        return words;
    }

    void train_debug(string trainfile){
        post_count = 0;
        csvstream csvin(trainfile);
        map<string, string> row;
        
        cout << "training data:" << endl;

        while(csvin >> row){
            set<string> vocabs = unique_words(row["content"]);
            tag.insert(row["tag"]);
            label_count[row["tag"]]++;

            auto it = vocabs.begin();
            while(it != vocabs.end()){
                word_count[*it]++;
                label_word_count[row["tag"]][*it]++;
                vocab.insert(*it);
                it++;
            }

            cout << "  label = " << row["tag"] << ", content = " 
            << row["content"] << endl;

            post_count++;
        }
        
        cout << "trained on " << post_count << " examples" << endl;
        cout << "vocabulary size = " << vocab.size() << endl;
        cout << endl;
    }

    void train(string trainfile){
        post_count = 0;
        csvstream csvin(trainfile);
        map<string, string> row;
        
        //cout << "training data:" << endl;

        while(csvin >> row){
            vocab = unique_words(row["content"]);

            auto it = vocab.begin();
            while(it != vocab.end()){
                word_count[*it]++;
                label_word_count[row["tag"]][*it]++;
                it++;
            }

            tag.insert(row["tag"]);
            label_count[row["tag"]]++;

            post_count++;
        }
        
        cout << "trained on " << post_count << " examples" << endl;
        // cout << "vocabulary size = " << vocab.size() << endl;
        cout << endl;
    }

    void print_log_prior(){
        cout << "classes:" << endl;
        auto it = tag.begin();
        while(it != tag.end()){
            cout << "  " << *it << ", " << label_count[*it] <<
            " examples, log-prior = " << 
            log((double)label_count[*it] / post_count) << endl;
            it++; 
        }
    }

    void print_log_likelihood(){
        cout << "classifier parameters:" << endl;

        auto it = tag.begin();
        while(it != tag.end()){
            auto i2 = vocab.begin();
            while(i2 != vocab.end()){
                if(label_word_count[*it][*i2] != 0){
                    cout << "  " << *it << ":" << *i2 << ", count = " << 
                    label_word_count[*it][*i2]
                    << ", log-likelihood = " << 
                    log((double)label_word_count[*it][*i2] / label_count[*it]) 
                    << endl;
                }
                i2++;
            }
            it++;
        }
        cout << endl;
    }

    pair<string, double> predicted_label_prob(string post){
        set<string> new_vocab = unique_words(post);
        vector<pair<string, double>> tag_prob;
        auto it = tag.begin();
        
        while(it != tag.end()){
            double prob_score = 0;

            // log prior 
            prob_score += log((double)label_count[*it] / post_count);

            auto i2 = new_vocab.begin();
            while(i2 != new_vocab.end()){
                //Use when  does not occur anywhere at all in the training set.
                if(word_count[*i2] == 0){
                    prob_score += log((double) 1 / post_count);
                }
                //Use when  does not occur in posts labeled  
                //but does occur in the training data overall.
                else if(label_word_count[*it][*i2] == 0){
                    prob_score += log((double)word_count[*i2] / post_count);
                }
                else{
                    prob_score += log((double)label_word_count[*it][*i2] 
                    / label_count[*it]);
                }
                i2++;
            }
            tag_prob.push_back(make_pair(*it, prob_score));
            it++;
        }

        int max_index = 0;
        double max_prob = tag_prob[0].second;
        for(size_t i=0; i<tag_prob.size(); i++){
            if(max_prob < tag_prob[i].second){
                max_prob = tag_prob[i].second;
                max_index = i;
            }
        }

        return tag_prob[max_index];
    }

    void print_test_data(string testfile){
        csvstream csvin(testfile);
        map<string, string> row;

        cout << "test data:" << endl;

        int total = 0;
        int correct = 0;

        while(csvin >> row){
            cout << "  correct = " << row["tag"] << ", predicted = " <<
            predicted_label_prob(row["content"]).first << 
            ", log-probability score = " << 
            predicted_label_prob(row["content"]).second << endl;

            cout << "  content = " << row["content"] <<endl;

            if(row["tag"] == predicted_label_prob(row["content"]).first){
                correct++;
            }
            total++;
            cout << endl;
        }

        cout << "performance: " << correct << " / " << total <<
            " posts predicted correctly" << endl;
    }
};

int main(int argc, char* argv[]){
    cout.precision(3);
    Classifier c;
    string train_file = argv[1];
    string test_file = argv[2];
    string debug = "";

    if(argc == 4){
        debug = argv[3];
    }

    if(argc == 4 && debug != "--debug"){
        c.print_error();
        return 1;
    }

    if(debug == "--debug"){
        c.train_debug(train_file);
        c.print_log_prior();
        c.print_log_likelihood();
        c.print_test_data(test_file);
    }
    else{
        c.train(train_file);
        c.print_test_data(test_file);
    }
   

    return 0;
}
