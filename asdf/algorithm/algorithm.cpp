
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

int Hash(const char* str, const int len) // 문자열을 해시값으로 변환
{
    int hash = 0;
    for (int i = 0; i < len; ++i)
    {
        hash = hash * 31 + str[i];
    }

    return hash;
}

int Hash(const std::string_view str) // 문자열을 해시값으로 변환
{
    return Hash(str.data(), str.size());
}

int RollingHash(const char* str, const int len, const int prevHash, const int prevChar, const int nextChar) // 롤링 해시값으로 변환
{
    int prevCharhash = prevChar; 
    for (size_t i = 0; i < len; i++)// 이전 문자의 해시값을 구함
    {
        prevCharhash *= 31;
    }
    int hash = prevHash - prevCharhash; // 이전 해시값에서 이전 문자의 해시값을 빼줌
    hash = hash * 31 + nextChar; // 이전 해시값에 다음 문자의 해시값을 더해줌

    return hash;
}

int RollingSearch(std::string_view pattern, std::string_view text, const int idxStartPos) {
    const int patternLen = pattern.size();
    const int textLen = text.size();

    const int patternHash = Hash(pattern);
    int textHash = Hash(text.substr(idxStartPos, patternLen));

    if (patternHash == textHash) { // 패턴과 텍스트의 해시값이 같다면
        return idxStartPos; // 해당 인덱스 반환
    }

    for (int i = idxStartPos + 1; i <= textLen - patternLen; ++i) {     // 텍스트의 길이에서 패턴의 길이를 뺀 만큼 반복
        textHash = RollingHash(text.data() + i - 1, patternLen, textHash, text[i - 1], text[i + patternLen - 1]); // 롤링 해시값으로 변환

        if (patternHash == textHash) {  // 패턴과 텍스트의 해시값이 같다면
            //해시 값이 같은 경우에만 문자열을 비교
            std::string_view subText = text.substr(i, patternLen); // 해당 인덱스부터 패턴의 길이만큼의 문자열을 가져옴
            if (pattern == subText) // 패턴과 일치한다면
            return i; // 해당 인덱스 반환
        }
    }

    return -1;

}



int BruteForce(std::string_view pattern, std::string_view text, const int idxStartPos)
{
    const int patternLen = pattern.size(); // 패턴의 길이
    const int textLen = text.size(); // 텍스트의 길이
    
    for (int i = idxStartPos; i <= textLen - patternLen; ++i) // 텍스트의 길이에서 패턴의 길이를 뺀 만큼 반복
    {
        int j = 0;
        while (j < patternLen && pattern[j] == text[i + j]) // 해당구간을 패턴길이만큼 비교
        {
            ++j;
        }

        if (j == patternLen) // 패턴의 길이만큼 비교했을 때 같다면
        {
            return i; // 해당 인덱스 반환
        }
    }

    return -1; // 일치하는 패턴이 없다면 -1 반환
}


void TestPatternMatching(const std::vector<std::string>& text)
{
    std::vector<std::pair<int, int>> matchingIndexTable;

    const int patternLen = strlen("APPLE");

    int lineIndex = 0;
    for (auto line : text)
    {
        int stringIndex = 0;
        while ((stringIndex = RollingSearch("APPLE", line.c_str(), stringIndex)) >= 0)
        {
            matchingIndexTable.push_back(std::make_pair(lineIndex, stringIndex));
            stringIndex += patternLen;
        }
        lineIndex++;
    }

    std::cout << "매칭 개수 : " << matchingIndexTable.size() << std::endl;

    for (auto [lineIndex, stringIndex] : matchingIndexTable)
    {
        std::cout << "Line: " << lineIndex << ", Index: " << stringIndex << std::endl;
    }
}

int main()
{
    std::ifstream file("sample.txt");

    if (!file.is_open())
    {
        std::cout << "파일 오픈 실패" << std::endl;
        return 1;
    }

    // 1K 크기의 버퍼를 설정
    constexpr size_t bufferSize = 1024;
    char buffer[bufferSize];

    // 스트림 버퍼 설정
    file.rdbuf()->pubsetbuf(buffer, bufferSize);

    std::vector<std::string> text;

    std::string line;
    line.reserve(bufferSize);

    while (std::getline(file, line))
    {
        text.push_back(line);
    }

    file.close();

    auto start = std::chrono::steady_clock::now();

    TestPatternMatching(text);

    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "경과 시간: " << elapsed_seconds.count() << "s\n";

    return 0;
}