#pragma once
#include "framework.h"
class DwriteFontSet{

    bool GetApplicationPath(std::wstring& applicationPath)
    {
        wchar_t buffer[MAX_PATH];
        if (!GetModuleFileName(nullptr, buffer, ARRAYSIZE(buffer)))
            return false;

        applicationPath.assign(buffer);
        size_t pos = applicationPath.find_last_of(L"\\/");
        if (pos == std::wstring::npos)
            return false;

        applicationPath.resize(pos + 1);
        return true;
    }

    bool GetFilesInSelectedFolder(const std::wstring& inFolderName, std::vector<std::wstring>& selectedFilePaths)
    {
        // Start with an empty vector.
        selectedFilePaths.clear();

        // Early return if input is empty string.
        if (inFolderName.empty())
        {
            return false;
        }

        //fs::path absPath = fs::system_complete(inFolderName);
        //fs::file_status pathStatus = fs::status(absPath);
        std::wstring path = inFolderName;

        // Confirm input path is a folder.
        /*if (pathStatus.type() != fs::file_type::directory)
        {
            return false;
        }*/

        // Add all the files in the folder to the vector.
        for (auto& file : fs::directory_iterator(absPath))
        {
            selectedFilePaths.push_back(file.path().wstring());
        }

        return true;
    }
};

