
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <memory>
#include <string>
#include <unordered_map>


class TireNode;

template <class T>
using Ref = std::shared_ptr<T>;

using Children = std::unordered_map<char, Ref<const TireNode>>;


class TrieNode
{
  public:
    Children _children;
    bool     bEndOfWorld = false;

    TrieNode()          = default;
    virtual ~TrieNode() = default;
    explicit TrieNode(Children children) : _children(std::move(children)) {}

    virtual std::unique_ptr<TrieNode> copy() const
    {
        return std::make_unique<TrieNode>(_children);
    }
};

template <class T>
class TrieValueNode : public TrieNode
{
  public:
    Ref<T> _value;

    TrieValueNode() = delete;
    explicit TrieValueNode(Ref<T> value)
        : _value(std::move(value))
    {
        bEndOfWorld = true;
    }

    explicit TrieValueNode(Children chilren, Ref<T> value)
        : TrieNode(std::move(chilren)),
          _value(std::move(value))
    {
        bEndOfWorld = true;
    }

    std::unique_ptr<TrieNode> copy() const override
    {
        return std::make_unique<TrieValueNode>(_children, _value);
    }
};


class Trie
{
  public:
    Ref<const TrieNode> _root = nullptr;

    Trie() = default;

    template <class T>
    const T *search(std::string key) const;

    template <class T>
    Trie insert(std::string key, T value) const;

    template <class T>
    Trie remove(std::string key) const;

  private:
    explicit Trie(Ref<const TrieNode> root) : _root(std::move(root)) {}
};

template <class T>
inline const T *Trie::search(std::string key) const
{
    size_t size = key.size();
    auto   cur  = _root;

    for (int i = 0; i < size; ++i) {
        char ch = key[i];
        if (cur && cur->_children.find(ch) != cur->_children.end()) {
            // why it err but can compile?
            auto next = cur->_children.at(ch);
            cur       = next;
        }
        else {
            return nullptr;
        }

        auto cur_node = dynamic_cast<const TrieValueNode<T> *>(cur.get());

        if (cur && cur->bEndOfWorld) {
            return cur_node->_value.get();
        }

        return nullptr;
    }
}

template <class T>
inline Trie Trie::insert(std::string key, T value) const
{
    size_t size = key.size();

    auto dfs = [&](auto self, size_t idx, Ref<const TrieNode> cur) -> Ref<const TrieNode> {
        // end
        if (idx == size) {
            auto value_ptr = std::make_shared<T>(std::move(value));
            if (cur) {
                return std::make_shared<TrieValueNode<T>>(cur->_children, value_ptr);
            }
            else
            {
                return std::make_shared<TrieValueNode<T>>(value_ptr);
            }
        }

        auto temp = cur;
        char ch   = key[idx];

        if (cur && cur->_children.find(ch) != cur->_children.end())
        {
            cur = cur->_children.at(ch);
        }
        else {
            cur = nullptr;
        }

        // if not null, find the next node and copy it
        auto next = self(self, idx + 1, cur);

        Ref<TrieNode> ret;

        if (temp) {
            ret = temp->copy();
        }
        else {
            // or just create (nullptr)
            ret = std::make_shared<TrieNode>();
        }

        ret.get()->_children[ch] = next;
        return ret;
    };

    auto new_root = dfs(dfs, 0, this->_root);
    return Trie(new_root);
}


template <class T>
inline Trie Trie::remove(std::string key) const
{
    size_t size = key.size();
    auto   dfs  = [&](auto self, size_t idx, Ref<const TrieNode> cur) -> Ref<const TrieNode> {
        // end
        if (idx == size) {
            return std::make_shared<const TrieNode>(cur->_children);
        }

        char ch = key[idx];

        std::unique_ptr<TrieNode> ret = cur->copy();
        if (cur && cur->_children.find(ch) != cur->_children.end())
        {
            cur = cur->_children.at(ch);
        }
        else {
            return nullptr;
        }

        Ref<const TrieNode> next = self(self, idx + 1, cur);
        if (!next) {
            return nullptr;
        }


        if (next->_children.empty() && !next->bEndOfWorld) {
            ret->_children.erase(ch);
        }
        else {
            ret->_children[ch] = next;
        }

        return ret;
    };

    auto ret = dfs(dfs, 0, _root);
    if (ret && ret->_children.empty() && !ret->bEndOfWorld) {
        return Trie(nullptr);
    }
    else if (!ret) {
        return Trie(_root);
    }

    return Trie(ret);
}


int main()
{
    Trie t;
    t.insert("ab", 1);
    t.insert("abc", 3);
    t.insert("aca", 2);

    auto ret = t.search<int>("abc");
    printf("%d\n", *ret);
}