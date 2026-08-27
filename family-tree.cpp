#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

/* ================= NODE ================= */
class TNode {
public:
    string name;
    TNode* child;
    TNode* sibling;

    TNode(string n) {
        name = n;
        child = NULL;
        sibling = NULL;
    }
};

/* ================= TREE ================= */
class Tree {
private:
    TNode* root;

    bool isValidName(const string& s) {
        if (s.empty()) return false;
        for (char c : s) {
            if (!isalpha(c) && c != ' ')
                return false;
        }
        return true;
    }

    string trim(string s) {
        int i = 0, j = s.length() - 1;
        while (i < s.length() && s[i] == ' ') i++;
        while (j >= 0 && s[j] == ' ') j--;
        if (j < i) return "";
        return s.substr(i, j - i + 1);
    }

    TNode* searchNode(TNode* node, const string& key) {
        if (!node) return NULL;
        if (node->name == key) return node;

        TNode* found = searchNode(node->child, key);
        if (found) return found;

        return searchNode(node->sibling, key);
    }

    void preorder(TNode* node) {
        if (!node) return;
        cout << "[" << node->name << "] ";
        preorder(node->child);
        preorder(node->sibling);
    }

    void postorder(TNode* node) {
        if (!node) return;
        postorder(node->child);
        postorder(node->sibling);
        cout << "[" << node->name << "] ";
    }

    void saveRecursive(TNode* node, ofstream& file) {
        if (!node) return;

        if (node->child) {
            file << node->name << ":";
            TNode* temp = node->child;
            while (temp) {
                file << temp->name;
                if (temp->sibling) file << ",";
                temp = temp->sibling;
            }
            file << endl;
        }

        saveRecursive(node->child, file);
        saveRecursive(node->sibling, file);
    }

public:
    Tree() {
        root = NULL;
    }

    void insertChild(string parent, string child) {
        parent = trim(parent);
        child = trim(child);

        if (!root) {
            root = new TNode(parent);
            root->child = new TNode(child);
            return;
        }

        TNode* p = searchNode(root, parent);
        if (!p) return;

        if (!p->child) {
            p->child = new TNode(child);
            return;
        }

        TNode* temp = p->child;
        while (temp->sibling) {
            if (temp->name == child) return;
            temp = temp->sibling;
        }

        if (temp->name != child)
            temp->sibling = new TNode(child);
    }

    void addMembers() {
        string parent, children;

        while (true) {
            cout << "Provide parent name: ";
            getline(cin, parent);
            parent = trim(parent);

            if (isValidName(parent)) break;
            cout << "Input rejected! Letters only, please.\n";
        }

        if (!root) {
            root = new TNode(parent);
            cout << "New family tree initialized.\n";
        }
        else if (!searchNode(root, parent)) {
            cout << "Operation failed: parent not found.\n";
            return;
        }

        cout << "List children (use commas): ";
        getline(cin, children);

        parseChildren(parent, children);
        cout << "Children processed successfully.\n";
    }

    void parseChildren(const string& parent, string line) {
        int start = 0;

        for (int i = 0; i <= line.length(); i++) {
            if (i == line.length() || line[i] == ',') {
                string child = trim(line.substr(start, i - start));

                if (!child.empty()) {
                    if (isValidName(child))
                        insertChild(parent, child);
                    else
                        cout << "Skipped invalid entry: " << child << endl;
                }
                start = i + 1;
            }
        }
    }

    void saveToFile(const string& fname) {
        ofstream file(fname);
        if (!file) {
            cout << "Saving failed. File not accessible.\n";
            return;
        }
        saveRecursive(root, file);
        file.close();
        cout << "Tree state saved to disk.\n";
    }

    void loadFromFile(const string& fname) {
        ifstream file(fname);
        if (!file) return;

        string line;
        while (getline(file, line)) {
            int pos = line.find(':');
            if (pos == string::npos) continue;

            string parent = trim(line.substr(0, pos));
            string children = line.substr(pos + 1);

            if (!root)
                root = new TNode(parent);

            parseChildren(parent, children);
        }
        file.close();
        cout << "Previous tree restored from file.\n";
    }

    void showPreorder() {
        if (!root) {
            cout << "Nothing to display. Tree is empty.\n";
            return;
        }
        cout << "Preorder sequence: ";
        preorder(root);
        cout << endl;
    }

    void showPostorder() {
        if (!root) {
            cout << "Tree has no data yet.\n";
            return;
        }
        cout << "Postorder sequence: ";
        postorder(root);
        cout << endl;
    }

    void searchDescendants(string name) {
        if (!isValidName(name)) {
            cout << "Search failed due to invalid input.\n";
            return;
        }

        TNode* p = searchNode(root, name);
        if (!p) {
            cout << "Requested person does not exist.\n";
            return;
        }

        if (!p->child) {
            cout << name << " has no recorded descendants.\n";
            return;
        }

        cout << "Descendant list of " << name << ": ";
        preorder(p->child);
        cout << endl;
    }
};

/* ================= MAIN ================= */
int main() {
    Tree family;
    string input, name;
    int choice = 0;

    const string FILE_NAME = "family.txt";
    family.loadFromFile(FILE_NAME);

    do {
        cout << "\n========== FAMILY TREE MENU ==========\n";
        cout << "1) Insert parent & children\n";
        cout << "2) Show preorder traversal\n";
        cout << "3) Show postorder traversal\n";
        cout << "4) Find descendants of a person\n";
        cout << "5) Quit application\n";
        cout << "Select an option: ";

        getline(cin, input);
        choice = (input.size() == 1 && isdigit(input[0])) ? stoi(input) : -1;

        switch (choice) {
        case 1:
            family.addMembers();
            family.saveToFile(FILE_NAME);
            break;

        case 2:
            family.showPreorder();
            break;

        case 3:
            family.showPostorder();
            break;

        case 4:
            cout << "Enter name to search: ";
            getline(cin, name);
            family.searchDescendants(name);
            break;

        case 5:
            cout << "Program terminated by user.\n";
            break;

        default:
            cout << "Invalid menu selection. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
