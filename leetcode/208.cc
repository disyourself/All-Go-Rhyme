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
        char ch;
        bool flag;

        map<char, TrieNode *> nodes;

        TrieNode () : ch (0) {}
        TrieNode (char c) : ch (c), flag (false) {}
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
            current = current->nodes[ch];
        }
        current->flag = true;
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
            current = current->nodes[ch];
        }

        return current->flag;
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
            current = current->nodes[ch];
        }

        // 脑残逻辑 1
        {
            //        // 节点的nodes为空(无后续)
            //        if (current->nodes.empty ()) {
            //            return true;
            //        }
            //        // 节点不是终止节点
            //        if (current->flag == false) {
            //            return true;
            //        }
            //        else {
            //            // 节点的nodes的指针全部为空
            //
            //			bool tf = true;
            //
            //            for (std::pair<char, TrieNode *> i : current->nodes) {
            //                // 只要有一个不会 null, 则视为 current 的 nodes 不为空
            //				// 即 当前节点还有后续节点， 而end flag 为 true
            //                // 所以  startsWith 为 false
            //                if (i.second != nullptr) {
            //					tf= false;
            //					break;
            //                }
            //            }
            //
            //			return tf;
            //        }
        }


        // 脑残逻辑 2
        {
            //            // 无后续 nodes, ret true
            //            if (current->nodes.empty ()) {
            //                return true;
            //            }
            //            // 为 end node，flag 为true, ret true
            //            if (current->flag) {
            //                return true;
            //            }
            //
            //            return true;
        }


        // 只需要 return true 就行了， 不需要判断
        return true;
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

    //    tree.insert ("apple");
    //
    //    tree.PrintTree ();
    //    // tree.LayerPrint (tree.m_root->nodes);
    //
    //    cout << (tree.search ("apple") ? "true" : "false") << std::endl;
    //    cout << (tree.search ("app") ? "true" : "false") << std::endl;
    //    cout << (tree.startsWith ("app") ? "true" : "false") << std::endl;
    //
    //    tree.insert ("app");
    //
    //    cout << (tree.search ("app") ? "true" : "false") << std::endl;

    tree.insert ("hello");
    tree.PrintTree ();

    cout << (tree.search ("hello") ? "true" : "false") << endl;
    cout << (tree.startsWith ("hell") ? "true" : "false") << endl;
    cout << (tree.startsWith ("helloa") ? "true" : "false") << endl;
    cout << (tree.startsWith ("hello") ? "true" : "false") << endl;
    return 0;
}

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
