#include <bits/stdc++.h>
#include <iostream>
#include <utility>

using namespace std;

class Directory;

class File {
protected:
    const int size_;

public:
    const string name_;
    const shared_ptr<Directory> parent_;

    explicit File(string n, int s, shared_ptr<Directory> p = nullptr);
    [[nodiscard]] virtual int GetSize() const;
    [[nodiscard]] virtual int GetIndent() const;
    virtual void Print() const;
};

class Directory : public File {
public:
    set<shared_ptr<File>> files;
    set<shared_ptr<Directory>> subdirs;

    explicit Directory(string name, shared_ptr<Directory> p = nullptr);
    [[nodiscard]] int GetSize() const override;
    void Print() const override;
    [[nodiscard]] int GetSumOfSizes() const;
    [[nodiscard]] shared_ptr<Directory> FindSmallestSubDirectoryWithMinSize(int size) const;
};

File::File(string n, int s, shared_ptr<Directory> p) : name_(std::move(n)), size_(s), parent_(std::move(p)) {
}

int File::GetSize() const {
    return size_;
}

int File::GetIndent() const {
    if (parent_) {
        return parent_->GetIndent() + 2;
    }
    return 0;
}

void File::Print() const {
    for (auto i = 0; i < GetIndent(); i++) {
        cout << " ";
    }
    cout << "- " << name_ << " (file, size=" << size_ << ")" << endl;
}

Directory::Directory(string name, shared_ptr<Directory> p) : File(std::move(name), 0, std::move(p)) {
}

int Directory::GetSize() const {
    auto size = 0;
    for (const auto& f : files) {
        size += f->GetSize();
    }
    for (const auto& s : subdirs) {
        size += s->GetSize();
    }
    return size;
}

void Directory::Print() const {
    auto indent = GetIndent();
    for (auto i = 0; i < indent; i++) {
        cout << " ";
    }
    cout << "- " << name_ << " (dir)" << endl;
    for (const auto& f : files) {
        f->Print();
    }
    for (const auto& s : subdirs) {
        s->Print();
    }
}

int Directory::GetSumOfSizes() const {
    auto size = GetSize();
    if (size > 100000) {  // ignore directory bigger than 100000
        size = 0;
    }
    for (const auto& s : subdirs) {
        size += s->GetSumOfSizes();
    }
    return size;
}

shared_ptr<Directory> Directory::FindSmallestSubDirectoryWithMinSize(int size) const {
    auto min_size = INT_MAX;
    shared_ptr<Directory> min_dir;
    for (const auto& subdir : subdirs) {
        auto subdir_size = subdir->GetSize();
        if (subdir_size < min_size && subdir_size >= size) {
            min_dir = subdir;
            min_size = subdir_size;
        }
    }
    if (min_dir != nullptr) {
        auto min_subdir = min_dir->FindSmallestSubDirectoryWithMinSize(size);
        if (min_subdir != nullptr) {
            min_dir = min_subdir;
        }
    }

    return min_dir;
}


int day7() {
    ifstream input("./day7.txt");
    if (!input.is_open()) {
        cout << "Unable to open file";
        return -1;
    }

    auto root = make_shared<Directory>("/");
    shared_ptr<Directory> current_dir = root;

    string line;
    while (getline(input,line)) {
        auto ss = stringstream(line);
        vector<std::string> words((istream_iterator<string> (ss)), istream_iterator<string>());
        if (words[0] == "$") {  // command
            if (words[1] == "cd") {  // cd
                if (words[2] == "/") {  // root
                    current_dir = root;
                }
                else if (words[2] == "..") {  // upper
                    current_dir = current_dir->parent_;
                }
                else {  // directory name_
                    auto name = words[2];
                    shared_ptr<Directory> subdir;
                    for (const auto& c : current_dir->subdirs) {
                        if (c->name_ == name) {
                            subdir = c;
                            break;
                        }
                    }
                    if (subdir == nullptr) {
                        auto new_dir = make_shared<Directory>(name, current_dir);
                        current_dir->subdirs.insert(new_dir);
                        subdir = new_dir;
                    }
                    current_dir = subdir;
                }
            }
            else if (words[1] == "ls") {  // ls - ignore
            }
        }
        else if (words[0] == "dir") {  // listed subdirectory
            auto name = words[1];
            shared_ptr<Directory> subdir;
            for (const auto& c : current_dir->subdirs) {
                if (c->name_ == name) {
                    subdir = c;
                    break;
                }
            }
            if (subdir == nullptr) {
                auto new_dir = make_shared<Directory>(name, current_dir);
                current_dir->subdirs.insert(new_dir);
            }
        }
        else {  // listed file
            auto size = stoi(words[0]);
            auto name = words[1];
            shared_ptr<File> file;
            for (const auto& f : current_dir->files) {
                if (f->name_ == name) {
                    file = f;
                    break;
                }
            }
            if (file == nullptr) {
                file = make_shared<File>(name, size, current_dir);
                current_dir->files.insert(file);
            }
        }
    }
    input.close();

    // PART 1
    root->Print();
    cout << endl << "Sum of sizes: " << root->GetSumOfSizes() << endl;

    // PART 2
    const auto space_to_free = 30000000 - (70000000 - root->GetSize());
    auto min_dir = root->FindSmallestSubDirectoryWithMinSize(space_to_free);
    cout << "Needed space to free: " << space_to_free << endl;
    cout << "Found dir: " << min_dir->name_ << " (size: " << min_dir->GetSize() << ")" << endl;

    return 0;

}
