//
// Created by trojan52.
//

#ifndef SPECSEM_LAB1_HTMLLOGGER_H
#define SPECSEM_LAB1_HTMLLOGGER_H

#include "BaseLogger.h"

class HTMLLogger : public BaseLogger
{
    public:
        explicit HTMLLogger(const std::string& rFileName);
        void PrintData() override;

    private:
        [[nodiscard]] std::string AddHeaders();
        [[nodiscard]] std::string AddRow(std::vector<std::string>& vRow);
        [[nodiscard]] std::string AddValue(std::string& sValue, size_t colspan = 1, size_t rowspan = 1);
        std::string m_sFileName;
};


#endif //SPECSEM_LAB1_HTMLLOGGER_H
