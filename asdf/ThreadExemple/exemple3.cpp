#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <map>
#include <vector>
#include <functional> //std::function
using namespace std;

#include <thread>
#include <concurrent_queue.h>
using namespace Concurrency;

// ¹» ÁÖ¹®Çß´Â°¡.
enum class CMD_TYPE : unsigned short
{
    NONE = 0,
    EÄ¿ÇÇ = 1,
    E»÷µåÀ§Ä¡,
    E¶±ººÀÌ
};

// ÁÖ¹®¼­ Å¸ÀÔ
class CmdMsg
{
public:
    CMD_TYPE cmdType;

protected:
    CmdMsg() { cmdType = CMD_TYPE::NONE; }
};

class CmdÄ¿ÇÇ : public CmdMsg
{
public:
    CmdÄ¿ÇÇ(const char* type)
    {
        cmdType = CMD_TYPE::EÄ¿ÇÇ;
        m_type = type;
    }

    string m_type;

private:
    CmdÄ¿ÇÇ() = delete;
};

class Cmd»÷µåÀ§Ä¡ : public CmdMsg
{
public:
    Cmd»÷µåÀ§Ä¡(int type)
    {
        cmdType = CMD_TYPE::E»÷µåÀ§Ä¡;
        m_type = type;
    }

    int m_type;

private:
    Cmd»÷µåÀ§Ä¡() = delete;
};

class Cmd¶±ººÀÌ : public CmdMsg
{
public:
    Cmd¶±ººÀÌ(int param1, int param2)
    {
        cmdType = CMD_TYPE::E¶±ººÀÌ;
        m_param1 = param1;
        m_param2 = param2;
    }

    int m_param1;
    int m_param2;

private:
    Cmd¶±ººÀÌ() = delete;
};


// Ã³¸® = ÇÔ¼ö
void MakeÄ¿ÇÇ(string param)
{
    cout << param << " Ä¿ÇÇ ½ÃÅ°½Å ºÐ?" << endl;
}

void Make»÷µåÀ§Ä¡(int nParam1)
{
    if (nParam1 < 0 || nParam1 >= 2)
    {
        cout << "¾ÈÆÈ¾Æ" << endl;
        return;
    }

    string »÷µåÀ§Ä¡Á¾·ù[2] = { "ÇÜ»÷µåÀ§Ä¡", "Ä¡Å²»÷µåÀ§Ä¡" };

    cout << »÷µåÀ§Ä¡Á¾·ù[nParam1] << "½ÃÅ°½Å ºÐ?" << endl;
}

void Make¶±ººÀÌ(int nParam1, int nParam2)
{
    if (nParam1 < 0 || nParam1 >= 2 || nParam2 < 0 || nParam2 >= 2)
    {
        cout << "¾ÈÆÈ¾Æ" << endl;
        return;
    }

    string ¶±ººÀÌÁ¾·ù[2] = { "¸Å¿î¶±ººÀÌ", "·ÎÁ¦¶±ººÀÌ" };
    string »çÀÌÁî[2] = { "º¸Åë", "Æ¯´ë" };

    cout << ¶±ººÀÌÁ¾·ù[nParam1] << " " << »çÀÌÁî[nParam2] << " ½ÃÅ°½Å ºÐ?" << endl;

}

// °¢ ¸í·É¾î¿¡ µû¶ó Ã³¸®ÇÏ´Â Å¬·¡½º
class CmdDiapatcher
{
public:
    void InitCommand()
    {
        m_cmdMap.emplace(CMD_TYPE::EÄ¿ÇÇ, [](CmdMsg* cmdMsg) {
            CmdÄ¿ÇÇ* pCmd = static_cast<CmdÄ¿ÇÇ*>(cmdMsg);
            MakeÄ¿ÇÇ(pCmd->m_type);
            });

        m_cmdMap.emplace(CMD_TYPE::E»÷µåÀ§Ä¡, [](CmdMsg* cmdMsg) {
            Cmd»÷µåÀ§Ä¡* pCmd = static_cast<Cmd»÷µåÀ§Ä¡*>(cmdMsg);
            Make»÷µåÀ§Ä¡(pCmd->m_type);
            });

        m_cmdMap.emplace(CMD_TYPE::E¶±ººÀÌ, [](CmdMsg* cmdMsg) {
            Cmd¶±ººÀÌ* pCmd = static_cast<Cmd¶±ººÀÌ*>(cmdMsg);
            Make¶±ººÀÌ(pCmd->m_param1, pCmd->m_param2);
            });
    }

    void DispatchCommand(CmdMsg* cmdMsg)
    {
        auto cmdFun = FindCommand(cmdMsg);
        cmdFun(cmdMsg);
    }


    std::function<void(CmdMsg*)> FindCommand(CmdMsg* cmdMsg)
    {
        CmdMsg* cmd = static_cast<CmdMsg*>(cmdMsg);

        auto it = m_cmdMap.find(cmd->cmdType);
        if (it == m_cmdMap.end()) std::terminate();
        return it->second;
    }

private:
    std::map<CMD_TYPE, std::function<void(CmdMsg*)> > m_cmdMap;
};

//__declspec(thread) int g_tlsCount = 0;
thread_local int g_tlsCount = 0;

int main()
{

    int nConcurrency = 2;

    // ÇÔ¼ö °´Ã¼ È°¿ë
    CmdDiapatcher _cmdDispatcher;
    _cmdDispatcher.InitCommand();


    concurrent_queue<shared_ptr<CmdMsg>> msgQueue;

    auto workFun = ([&_cmdDispatcher, &msgQueue]
        {
            std::thread::id thisThreadId = std::this_thread::get_id();


            int count = 0;
            while (count < 10)
            {
                shared_ptr<CmdMsg> Cmd;
                if (msgQueue.try_pop(Cmd))
                {

                    cout << thisThreadId << ": ÁÖ¼Ò " << &g_tlsCount << " : Á¢¼ö ¹øÈ£ " << ++g_tlsCount << " ÁÖ¹® È®ÀÎ : ";

                    _cmdDispatcher.DispatchCommand(Cmd.get());
                    ++count;
                }
            }

            cout << "Àå»ç ³¡!" << endl;

        } // ´Ù¸¥ ½º·¹µå!!
        );

    vector<std::thread> workerThreads;
    workerThreads.resize(nConcurrency);

    for (auto& e : workerThreads)
    {
        e = std::thread(workFun);
    }

    // ¿©±ä ¸ÞÀÎ ½º·¹µå
    int KeyInfo;

    do
    {
        KeyInfo = _getch();

        if (tolower(KeyInfo) == '1')
        {
            shared_ptr<CmdMsg> cmdMsg(std::make_shared<CmdÄ¿ÇÇ>("¾Æ¾Æ"));
            msgQueue.push(cmdMsg);
        }
        else if (tolower(KeyInfo) == '2')
        {
            shared_ptr<CmdMsg> cmdMsg(std::make_shared<Cmd»÷µåÀ§Ä¡>(1));
            msgQueue.push(cmdMsg);
        }
        else if (tolower(KeyInfo) == '3')
        {
            shared_ptr<CmdMsg> cmdMsg(std::make_shared<Cmd¶±ººÀÌ>(1, 1));
            msgQueue.push(cmdMsg);
        }

    } while (tolower(KeyInfo) != 'q');


    for (auto& worker : workerThreads)
    {
        if (worker.joinable())
            worker.join();
    }

    system("pause");
}