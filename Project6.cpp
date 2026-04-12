#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

struct File {
    string name;
};

struct Directory {
    string name;
    Directory* parent;
    vector<Directory*> subdirs;
    vector<File*> files;
};

class Shell {
private:
    Directory* root;
    Directory* current;

public:
    Shell() {
        root = new Directory{"/", nullptr, {}, {}};
        current = root;

        root->files.push_back(new File{"run1"});
        root->files.push_back(new File{"run2"});
        root->files.push_back(new File{"run3"});
    }

    void run() {
        string line;

        cout << "File System Shell\n";
        cout << "Type help for commands\n";

        while (true) {
            cout << getPath(current) << "$ ";
            getline(cin, line);

            if (line.empty()) continue;

            vector<string> tokens = split(line);
            string cmd = tokens[0];

            if (cmd == "exit" || cmd == "quit") {
                cout << "bye!\n";
                break;
            }
            else if (cmd == "help") {
                showHelp();
            }
            else if (cmd == "mkdir") {
                mkdirCmd(tokens);
            }
            else if (cmd == "ls") {
                lsCmd();
            }
            else if (cmd == "cd") {
                cdCmd(tokens);
            }
            else if (cmd == "touch") {
                touchCmd(tokens);
            }
            else if (cmd == "rm") {
                rmCmd(tokens);
            }
            else if (cmd == "rmdir") {
                rmdirCmd(tokens);
            }
            else if (cmd == "pwd") {
                cout << getPath(current) << "\n";
            }
            else {
                cout << cmd << ": command not found\n";
            }
        }
    }

private:
    vector<string> split(const string& line) {
        vector<string> tokens;
        string word;
        stringstream ss(line);

        while (ss >> word) {
            tokens.push_back(word);
        }

        return tokens;
    }

    string getPath(Directory* dir) {
        if (dir == root) return "/";

        vector<string> parts;
        while (dir != root) {
            parts.push_back(dir->name);
            dir = dir->parent;
        }

        reverse(parts.begin(), parts.end());

        string path = "";
        for (string part : parts) {
            path += "/" + part;
        }
        return path;
    }

    Directory* findSubdir(Directory* dir, const string& name) {
        for (Directory* d : dir->subdirs) {
            if (d->name == name) return d;
        }
        return nullptr;
    }

    File* findFile(Directory* dir, const string& name) {
        for (File* f : dir->files) {
            if (f->name == name) return f;
        }
        return nullptr;
    }

    bool nameExists(Directory* dir, const string& name) {
        return findSubdir(dir, name) != nullptr || findFile(dir, name) != nullptr;
    }

    void mkdirCmd(const vector<string>& tokens) {
        if (tokens.size() != 2) {
            cout << "mkdir: missing operand\n";
            return;
        }

        string name = tokens[1];

        if (nameExists(current, name)) {
            cout << "mkdir: " << name << " already exists\n";
            return;
        }

        Directory* newDir = new Directory{name, current, {}, {}};
        current->subdirs.push_back(newDir);
    }

    void lsCmd() {
        vector<string> items;

        for (File* f : current->files) {
            items.push_back(f->name);
        }

        for (Directory* d : current->subdirs) {
            items.push_back(d->name + "/");
        }

        sort(items.begin(), items.end());

        for (string item : items) {
            cout << item << " ";
        }
        cout << "\n";
    }

    void cdCmd(const vector<string>& tokens) {
        if (tokens.size() != 2) {
            cout << "cd: missing operand\n";
            return;
        }

        string name = tokens[1];

        if (name == "..") {
            if (current->parent != nullptr) {
                current = current->parent;
            }
            return;
        }

        if (name == "/") {
            current = root;
            return;
        }

        Directory* next = findSubdir(current, name);
        if (next == nullptr) {
            cout << "cd: no such directory\n";
            return;
        }

        current = next;
    }

    void touchCmd(const vector<string>& tokens) {
        if (tokens.size() != 2) {
            cout << "touch: missing file operand\n";
            return;
        }

        string name = tokens[1];

        if (nameExists(current, name)) {
            cout << "touch: " << name << " already exists\n";
            return;
        }

        File* newFile = new File{name};
        current->files.push_back(newFile);
    }

    void rmCmd(const vector<string>& tokens) {
        if (tokens.size() != 2) {
            cout << "rm: missing operand\n";
            return;
        }

        string name = tokens[1];

        for (int i = 0; i < current->files.size(); i++) {
            if (current->files[i]->name == name) {
                delete current->files[i];
                current->files.erase(current->files.begin() + i);
                return;
            }
        }

        cout << "rm: file not found\n";
    }

    void rmdirCmd(const vector<string>& tokens) {
        if (tokens.size() != 2) {
            cout << "rmdir: missing operand\n";
            return;
        }

        string name = tokens[1];

        for (int i = 0; i < current->subdirs.size(); i++) {
            if (current->subdirs[i]->name == name) {
                if (!current->subdirs[i]->files.empty() || !current->subdirs[i]->subdirs.empty()) {
                    cout << "rmdir: directory not empty\n";
                    return;
                }

                delete current->subdirs[i];
                current->subdirs.erase(current->subdirs.begin() + i);
                return;
            }
        }

        cout << "rmdir: directory not found\n";
    }

    void showHelp() {
        cout << "Commands:\n";
        cout << "mkdir <dir>\n";
        cout << "ls\n";
        cout << "cd <dir>\n";
        cout << "cd ..\n";
        cout << "cd /\n";
        cout << "touch <file>\n";
        cout << "rm <file>\n";
        cout << "rmdir <dir>\n";
        cout << "pwd\n";
        cout << "help\n";
        cout << "exit\n";
    }
};

int main() {
    Shell shell;
    shell.run();
    return 0;
}
