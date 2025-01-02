#pragma once
#include <string>
#include <vector>

#ifdef MYTESTDLL_EXPORTS
#define MYDLL_DECLSPEC __declspec(dllexport)
#else
#define MYDLL_DECLSPEC __declspec(dllimport)
#endif

class Banana
{
public:
    Banana(std::string owner);
    void ShowOwner();

private:
    std::string m_owner;
};

#ifdef __cplusplus
extern "C" {
    MYDLL_DECLSPEC Banana* CreateBanana(const char* owner);
    MYDLL_DECLSPEC void ShowOwner(Banana* obj);
    MYDLL_DECLSPEC void DeleteBanana(Banana* obj);
}
#endif

class Tomato
{
public:
    Tomato(std::string owner);
    MYDLL_DECLSPEC void ShowOwner();

private:
    std::string m_owner;
};


class MYDLL_DECLSPEC TomatoFactory
{
public:
    TomatoFactory();

    void ShowCount();


    Tomato* CreateTomato(const char* owner);
    void DeleteTomato(Tomato* obj);


    static int stCount;

private:
    int m_count;

};

extern MYDLL_DECLSPEC TomatoFactory g_TomatoFactory;

