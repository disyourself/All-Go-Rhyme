#include <map>
#include <string>
#include <variant>
#include <vector>


using IntString = std::variant<int, std::string>;

typedef struct ItemType
{
    std::map<std::string, IntString> mMap{};

    void
    Set (const std::string &key, int v)
    {
        auto data    = IntString{};
        data.intData = v;
        mMap[key]    = data;
    }
    void
    Set (const std::string &key, const std::string &v)
    {
        auto data    = IntString{};
        data.strData = v;
        mMap[key]    = data;
    }


    void
    Get (const std::string &key, int &data)
    {
        data = mMap[key].intData;
    }
    void
    Get (const std::string &key, std::string &data)
    {
        data = mMap[key].strData;
    }

    bool
    Has (const std::string &key)
    {
        return mMap.find (key) == mMap.end ();
    }
    std::vector<std::string>
    GetKeys ()
    {
        std::vector<std::string> keys;
        for (auto &it : mMap) {
            keys.push_back (it.first);
        }
        return keys;
    }
} ItemType;

class Solution
{
  public:
    std::vector<ItemType>
    PivotFn (const std::vector<ItemType> &data,
             const std::string           &groupBy,
             const std::string           &key,
             const std::string           &value)
    {
        std::vector<int>      uniqueKeys{};
        std::vector<ItemType> pivotedData{};

        // dode here
        for (int i = 0; i < data.size (); ++i) {
        }

        return pivotedData;
    }
};
