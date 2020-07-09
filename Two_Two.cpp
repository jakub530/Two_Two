#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>

using namespace std;


class Node
{
public:
    std::map<char, Node*> node_map;
    bool active = false;
};

void create_tree(Node* root, const vector<vector<char>>& input_data)
{
    for (const auto& line : input_data)
    {
        Node* active_node = root;
        for (const auto& c : line)
        {
            if (active_node->node_map.find(c) == active_node->node_map.end())
            {
                active_node->node_map[c] = new Node;
            }
            active_node = active_node->node_map[c];
        }
        active_node->active = true;
    }
}


vector<vector<char>> create_vectors()
{
    //Checked create vector from 2^0 up to 2^800 now need to create a treee a
    vector<vector<char>> output;
    vector<char> start(1, '1');
    output.push_back(start);
    for (int i = 0; i < 800; i++)
    {
        vector<char> new_char = output[i];
        int addition = 0;
        int size = new_char.size();
        for (int ch = 0; ch < size; ch++)
        {
            int tmp = (new_char[ch] - '0') * 2 + addition;
            if (tmp < 10)
            {
                new_char[ch] = '0'+tmp;
                addition = 0;
            }
            else
            {
                addition = 1;
                new_char[ch] = '0'+tmp - 10;
                if (ch == new_char.size() - 1)
                {
                    new_char.push_back('1');
                }
            }
        }
        output.push_back(new_char);
    }
    return output;
}

void output_data(const vector <vector<char>> &data)
{
    for (int line = 0; line < data.size(); line++)
    {
        std::cout << line << " ";
        for (int ch = data[line].size()-1; ch >= 0  ; ch--)
        {
            std::cout << data[line][ch] << " ";
        }
        std::cout << "\n";
    }
}

int twoTwo(string a,int answer,Node* root)
{
    
    
    int sum = 0;
    
    for (int i = a.size() - 1; i >= 0; i--)
    {
        Node* tmp_node = root;
        int delta = 0;
        while (true)
        {
            if (tmp_node->node_map.find(a[i-delta]) == tmp_node->node_map.end())
            {
                break;
            }
            else
            {
                tmp_node = tmp_node->node_map[a[i - delta]];
                if (tmp_node->active)
                {
                    sum++;
                }

            }
            if (i - delta == 0)
            {
                break;
            }
            else
            {
                delta++;
            }
        }
    }
    //output_data(data);
    return sum;
}


int main()
{
    //ofstream fout(getenv("OUTPUT_PATH"));
    fstream Answers;
    Answers.open("model_answer_t11.txt");
    fstream inFile;
    inFile.open("testcase_t11.txt");
    string t_string;
    getline(inFile, t_string);
    int t = stoi(t_string);
    //int t;
    //cin >> t;
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<vector<char>> data = create_vectors();
    Node* root = new Node;
    create_tree(root, data);

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string input;
        string answer;
        getline(inFile, input);
        getline(Answers, answer);
        int i_answer = stoi(answer);
        int result = twoTwo(input, i_answer,root);

        std::cout << result << "\n";
    }

    //fout.close();

    return 0;
}


