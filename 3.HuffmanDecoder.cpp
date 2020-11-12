#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<queue>
#include<map>
#include<string>
using namespace std;

struct symbol_table
{
    char symbol;
    int weight;
    bool operator < (symbol_table x) const
    {
        if(weight != x.weight)
            return weight < x.weight;
        else
            return symbol < x.symbol;
    }
};

struct HTNode
{
    symbol_table data;
    HTNode *left, *right;
    HTNode(char s, int w)
    {
        data.symbol = s;
        data.weight = w;
        left = NULL;
        right = NULL;
    }

    HTNode(HTNode *lc, HTNode *rc)
    {
        left = lc;
        right = rc;
        data.weight = lc->data.weight + rc->data.weight;
        data.symbol = '\0';
    }
};

struct cmp  //for pque
{
    bool operator()(HTNode *x, HTNode *y) const
    {
        return x->data.weight > y->data.weight;
    }
};

char menu_select();
HTNode* initialization();
HTNode* read_hfmTreefile();
HTNode* tree_build(vector<symbol_table> data);
void encoding(HTNode *root);
void mapping(HTNode *root, vector<pair<char, string>> &code_table, string s = "");
void decoding(HTNode *root);

int main()
{
    char c;
    HTNode* root = NULL;
    while(c = menu_select())
    {
        if(c == 'I' || c == 'i')
            root = initialization();
        if(c == 'E' || c == 'e')
        {
            if(root == NULL)
                root = read_hfmTreefile();
            encoding(root);
        }
        if(c == 'D' || c == 'd')
        {
            if(root == NULL)
                root = read_hfmTreefile();
            decoding(root);
        }
            /*
        if(c == 'P' || c == 'p')
            print();
        if(c == 'T' || c == 't')
            tree_printing();*/
        if(c == 'Q' || c == 'q')
            break;
    }
}

char menu_select()
{
    cout << "---------MainMenu---------" << endl;
    cout << "Press 'I' -> Initialization" << endl;
    cout << "Press 'E' -> Encoding" << endl;
    cout << "Press 'D' -> Decoding" << endl;
    cout << "Press 'P' -> Print" << endl;
    cout << "Press 'T' -> Tree printing" << endl;
    cout << "Press 'Q' -> Quit" << endl;
    char c;
    cin >> c;
    return c;
}

HTNode* initialization()
{
    int size;
    cin >> size;
    vector<symbol_table> data(size);
    for(int i = 0; i < size; i++)
    {
        getchar();
        data[i].symbol = getchar();
        cin >> data[i].weight;
    }
    HTNode *root = tree_build(data);
    ofstream out("hfmTree");
    out << data.size() << endl;
    for(int i = 0; i < size; i++)
        out << data[i].symbol << data[i].weight << endl;
    out.close();
    return root;
}

HTNode* tree_build(vector<symbol_table> data)
{
    priority_queue<HTNode*, vector<HTNode*>, cmp> pque;
    for(auto i = data.begin(); i != data.end(); i++)
    {
        HTNode *tmp = new HTNode(i->symbol, i->weight);
        pque.push(tmp);
    }
    while(pque.size() != 1)
    {
        HTNode *tmp1, *tmp2;
        tmp1 = pque.top();
        pque.pop();
        tmp2 = pque.top();
        pque.pop();
        HTNode *parent = new HTNode(tmp1,tmp2);
        pque.push(parent);
    }
    return pque.top();
}

HTNode* read_hfmTreefile()
{
    ifstream in("hfmTree");
        int size;
        char tmp;
        in >> noskipws >> size;
        vector<symbol_table> data(size);
        for(int i = 0; i < size; i++)
        {
            in >> tmp;
            in >> data[i].symbol;
            in >> data[i].weight;
        }
        return tree_build(data);
}

void encoding(HTNode *root)
{
    map<char,string> to_code;
    vector<pair<char, string>> code_table;
    mapping(root, code_table);
    for(auto i = code_table.begin(); i != code_table.end(); i++)
        to_code.insert(*i);
    ifstream uncoded("ToBeTran");
    ofstream encoded("CodeFile");
    string text;
    getline(uncoded, text);
    for(int i = 0; i < text.length(); i++)
        encoded << to_code[text[i]];
    uncoded.close();
    encoded.close();
}

void mapping(HTNode *root, vector<pair<char, string>> &code_table, string s)
{
    if(root->data.symbol != '\0')
    {
        code_table.push_back(make_pair(root->data.symbol, s));
        return;
    }
    mapping(root->left, code_table, s + "0");
    mapping(root->right, code_table, s + "1");
}

void decoding(HTNode *root)
{
    map<string, char> to_text;
    vector<pair<char, string>> code_table;
    mapping(root, code_table);
    for(auto i = code_table.begin(); i != code_table.end(); i++)
        to_text.insert(make_pair(i->second, i->first));
    ifstream encoded("CodeFile");
    ofstream decoded("TextFile");
    string code, tmp;
    encoded >> code;
    for(int i = 0; i < code.length(); i++)
    {
        tmp += code[i];
        if(to_text.find(tmp) != to_text.end())
        {
            decoded << to_text.find(tmp)->second;
            tmp = "";
        }
    }
    encoded.close();
    decoded.close();
}