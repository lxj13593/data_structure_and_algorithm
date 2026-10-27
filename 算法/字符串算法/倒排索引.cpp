#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <list>
#include <string>
#include <map>
#include <unordered_map>
#include <cstring>
#include <cstdio>

#undef UNICODE
#include <Windows.h>

using namespace std;

struct InvertedEntry
{
    InvertedEntry(string doc_id, int position) : doc_id(doc_id)
    {
        position_list.emplace_back(position);
        freqs = 1;
    }

    bool operator<(const InvertedEntry &other)
    {
        return this->doc_id < other.doc_id;
    }

    bool operator==(const InvertedEntry &other)
    {
        return this->doc_id == other.doc_id;
    }

    string doc_id;
    int freqs;
    list<int> position_list;
};

class InvertedList
{
public:
    void add(string doc_id, int position)
    {
        for (auto &entry : inverted_list)
        {
            if (entry.doc_id == doc_id)
            {
                entry.freqs++;
                entry.position_list.emplace_back(position);
                return;
            }
        }

        inverted_list.emplace_back(doc_id, position);
    }

    const list<InvertedEntry> get_inverted_list()
    {
        return inverted_list;
    }

private:
    list<InvertedEntry> inverted_list;
};

class InvertedIndex
{
public:
    void set_search_path(string path)
    {
        setSuffix(".cpp");
        getAllFile(path.c_str());
        make_index();
        cout << "Inverted index created successfully!" << endl;
    }

    void setSuffix(string suffix)
    {
        suffix_ = suffix;
    }

    int getAllFile(const char *Path)
    {
        char szFind[MAX_PATH];
        WIN32_FIND_DATA FindFileData;

        strcpy(szFind, Path);
        strcat(szFind, "\\*.*");

        HANDLE hFind = FindFirstFile(szFind, &FindFileData);

        if (INVALID_HANDLE_VALUE == hFind)
            return -1;

        do
        {
            if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if (strcmp(FindFileData.cFileName, ".") != 0 &&
                    strcmp(FindFileData.cFileName, "..") != 0)
                {
                    char szFile[MAX_PATH] = {0};

                    strcpy(szFile, Path);
                    strcat(szFile, "\\");
                    strcat(szFile, FindFileData.cFileName);

                    getAllFile(szFile);
                }
            }
            else
            {
                string fileName(FindFileData.cFileName);

                int pos = fileName.find(suffix_);

                if (pos != string::npos &&
                    pos + suffix_.size() == fileName.size())
                {
                    string filePath(Path);
                    filePath.append("\\");
                    filePath.append(fileName);

                    file_list.emplace_back(filePath);
                }
            }

        } while (FindNextFile(hFind, &FindFileData));

        FindClose(hFind);

        return 0;
    }

    void make_index()
    {
        for (const auto &file : file_list)
        {
            FILE *fp = fopen(file.c_str(), "r");

            if (fp == nullptr)
            {
                cout << "Failed to open file: " << file << endl;
                continue;
            }

            char buf[2048];
            int position = 0;

            while (fgets(buf, sizeof(buf), fp) != nullptr)
            {
                map<int, string> m;

                char *word = strtok(buf, " \t\r\n");

                while (word != nullptr)
                {
                    position++;
                    m.emplace(position, word);
                    word = strtok(nullptr, " \t\r\n");
                }

                for (const auto &word : m)
                {
                    auto it = inverted_index.find(word.second);

                    if (it != inverted_index.end())
                    {
                        it->second.add(file, word.first);
                    }
                    else
                    {
                        InvertedList il;
                        il.add(file, word.first);
                        inverted_index[word.second] = il;
                    }
                }
            }

            fclose(fp);
        }
    }

    void query(string phrase)
    {
        string temp = phrase;

        char *word = strtok(temp.data(), " \t\r\n");

        vector<string> v1;

        while (word != nullptr)
        {
            v1.push_back(word);
            word = strtok(nullptr, " \t\r\n");
        }

        if (v1.size() == 0)
        {
            return;
        }

        if (v1.size() == 1)
        {
            auto it = inverted_index.find(v1.front());

            if (it != inverted_index.end())
            {
                cout << "Found in "
                     << it->second.get_inverted_list().size()
                     << " file(s)." << endl;

                for (auto val : it->second.get_inverted_list())
                {
                    cout << val.doc_id << " " << val.freqs << endl;
                }
            }
            else
            {
                cout << "Word not found." << endl;
            }
        }
        else
        {
            vector<InvertedList> ll;

            for (int i = 0; i < v1.size(); i++)
            {
                auto it = inverted_index.find(v1[i]);

                if (it != inverted_index.end())
                {
                    ll.emplace_back(it->second);
                }
                else
                {
                    cout << "No document contains all query words." << endl;
                    return;
                }
            }

            list<InvertedEntry> l1 = ll[0].get_inverted_list();
            vector<InvertedEntry> vv1(l1.begin(), l1.end());
            vector<InvertedEntry> temp;

            for (int i = 1; i < ll.size(); i++)
            {
                list<InvertedEntry> l2 = ll[i].get_inverted_list();
                vector<InvertedEntry> vv2(l2.begin(), l2.end());

                sort(vv1.begin(), vv1.end());
                sort(vv2.begin(), vv2.end());

                set_intersection(
                    vv1.begin(), vv1.end(),
                    vv2.begin(), vv2.end(),
                    back_inserter(temp)
                );

                temp.swap(vv1);
                temp.clear();
            }

            cout << "Found in "
                     << vv1.size()
                     << " file(s)." << endl;

            for (auto val : vv1)
            {
                cout << val.doc_id << endl;
            }
        }
    }

private:
    string suffix_;
    list<string> file_list;
    unordered_map<string, InvertedList> inverted_index;
};

int main()
{
    SetConsoleOutputCP(GetACP());

    InvertedIndex l;

    l.set_search_path("E:\\project\\data_structure_and_algorithm");

    l.query("a");

    return 0;
}