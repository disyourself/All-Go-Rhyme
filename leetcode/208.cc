#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Trie
{
  private:
    struct TrieNode
    {
        char                  ch;
        map<char, TrieNode *> nodes;

        TrieNode () {}
        TrieNode (char c) : ch (c) {}
    };

  public:

    TrieNode *m_root;
    TrieNode *current;

  public:

    Trie ()
    {
        m_root  = new TrieNode ();
        current = m_root;
    }

    void
    insert (string word)
    {
        current = m_root;

        for (int i = 0; i < word.size (); ++i) {
            char ch = word[i];
            if (current->nodes[ch] == nullptr) {
                current->nodes[ch] = new TrieNode (ch);
            }
            else {
                current = current->nodes[ch];
            }
        }
    }

    bool
    search (string word)
    {
        current = m_root;

        for (int i = 0; i < word.size (); ++i) {
            char ch = word[i];
            if (current->nodes[ch] == nullptr) {
                return false;
            }
            else {
                current = current->nodes[ch];
            }
        }

        return current->nodes.empty () ? false : true;
    }

    bool
    startsWith (string prefix)
    {
        current = m_root;

        for (int i = 0; i < prefix.size (); ++i) {
            char ch = prefix[i];
            if (current->nodes[ch] == nullptr) {
                return false;
            }
            else {
                current = current->nodes[ch];
            }
        }

        return current->nodes.empty () ? true : false;
    }

    void
    PreOrderPrint (map<char, TrieNode *> &node)
    {
        for (auto &i : node) {
            if (i.second != nullptr) {
                cout << i.first << "->";
                PreOrderPrint (i.second->nodes);
                cout << endl;
            }
        }
    }
    void
    LayerPrint (map<char, TrieNode *> &node)
    {
        vector<char> buffer;

        for (auto &i : node) {
            if (i.second != nullptr) {
                cout << i.first << "->";
                buffer.push_back (i.first);
            }
        }
        cout << endl;
        for (auto i : buffer)
            LayerPrint (node[i]->nodes);
    }

    void
    PrintTree ()
    {
        PreOrderPrint (this->m_root->nodes);
    }
};


int
main ()
{
    Trie tree;

    tree.insert ("hello");
    tree.insert ("hbllo");

    // tree.PrintTree();
    tree.LayerPrint (tree.m_root->nodes);

    return 0;
}

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
