
#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <stdlib.h>
#include <crtdbg.h>

#include "json.hpp"


#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif


using namespace std;

constexpr int MAX_NAME_LENGTH = 16;
constexpr int MAX_DESCRIPTION_LENGTH = 64;


struct ItemDetail
{
    int price;
    int stock;
    std::string description;
};

struct ItemInfo
{
    std::string name;

    std::shared_ptr<ItemDetail> detail;
};

using json = nlohmann::json;


void WriteJSONTest()
{
    std::vector<ItemInfo> items;

    std::shared_ptr<ItemDetail> detail = std::make_shared<ItemDetail>();
    detail->price = 100;
    detail->stock = 10;
    detail->description = "item1 description";
    items.push_back(ItemInfo{ "item1", detail });

    std::shared_ptr<ItemDetail> detail2 = std::make_shared<ItemDetail>();
    detail2->price = 200;
    detail2->stock = 20;
    detail2->description = "item2 description";
    items.push_back(ItemInfo{ "item2", detail2 });

    // Serialize
    json jdata;
    for (auto& item : items)
    {
        json jitem;
        jitem["name"] = item.name;
        jitem["detail"]["price"] = item.detail->price;
        jitem["detail"]["stock"] = item.detail->stock;
        jitem["detail"]["description"] = item.detail->description;
        jdata.push_back(jitem);
    }

    std::ofstream ofs("items.json");
    ofs << jdata.dump(4);
    ofs.close();
}

void ReadJSONFileTest()
{
    std::ifstream ifs("items.json");
    json jdata;
    ifs >> jdata;
    ifs.close();

    // Deserialize
    std::vector<ItemInfo> items;
    for (auto& jitem : jdata)
    {
        std::shared_ptr<ItemDetail> detail = std::make_shared<ItemDetail>();
        detail->price = jitem["detail"]["price"];
        detail->stock = jitem["detail"]["stock"];
        detail->description = jitem["detail"]["description"];
        items.push_back(ItemInfo{ jitem["name"], detail });
    }

    for (auto& item : items)
    {
        cout << "name: " << item.name << endl;
        cout << "price: " << item.detail->price << endl;
        cout << "stock: " << item.detail->stock << endl;
        cout << "description: " << item.detail->description << endl;
    }
}

size_t GetFileSize(const std::string& fileName)
{
    std::ifstream file(fileName, std::ios::binary | std::ios::ate);

    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return 0;
    }
    return static_cast<size_t>(file.tellg());
}

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);

    WriteJSONTest();

    ReadJSONFileTest();


    std::cout << GetFileSize("items.json") << std::endl;

    _CrtDumpMemoryLeaks();

    return 0;
}
