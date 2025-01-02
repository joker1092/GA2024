#include "pch.h"
#include "FruitFactory.h"
#include <iostream>

//--------------------------------------------------

#pragma data_seg("SHARDATA")

int g_shared_count = 0;

#pragma data_seg()

#pragma comment(linker, "/SECTION:SHARDATA,RWS")


int TomatoFactory::stCount;
__declspec(dllexport) TomatoFactory g_TomatoFactory;

//--------------------------------------------------
Banana::Banana(std::string owner)
{
    this->m_owner = owner;
}

void Banana::ShowOwner()
{
    std::cout << "??��?��? ?????? " << m_owner.c_str() << std::endl;
}

Banana* CreateBanana(const char* owner)
{
    std::cout << "??��?��? �Ƣ�?? ????" << std::endl;
    return new Banana(owner);
}

void ShowOwner(Banana* obj)
{
    obj->ShowOwner();
}

void DeleteBanana(Banana* obj)
{
    delete obj;
    obj = nullptr;

    std::cout << "??��?��? �Ƣ�?? ????" << std::endl;
}

//----------------------------------------------------

Tomato::Tomato(std::string owner)
{
    this->m_owner = owner;
}

void Tomato::ShowOwner()
{
    std::cout << "??����?? ?????? " << m_owner.c_str() << std::endl;
}

TomatoFactory::TomatoFactory()
{
    m_count = 0;
}

void TomatoFactory::ShowCount()
{
    std::cout << "??����?? �Ʃ�??(m_count) " << m_count << std::endl;
    std::cout << "??����?? �Ʃ�??(stCount) " << TomatoFactory::stCount << std::endl;
    std::cout << "??����?? �Ʃ�??(g_shared_count) " << g_shared_count << std::endl;
}

Tomato* TomatoFactory::CreateTomato(const char* owner)
{
    std::cout << "??����?? �Ƣ�?? ????" << std::endl;

    m_count++;
    TomatoFactory::stCount++;
    g_shared_count++;

    return new Tomato(owner);
}

void TomatoFactory::DeleteTomato(Tomato* obj)
{
    delete obj;
    obj = nullptr;

    std::cout << "??����?? �Ƣ�?? ????" << std::endl;

    m_count--;
    TomatoFactory::stCount--;
    g_shared_count--;
}

//--------------------------------------------------