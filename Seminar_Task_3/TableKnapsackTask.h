//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_3_TABLEKNAPSACKTASK_H
#define SEMINAR_TASK_3_TABLEKNAPSACKTASK_H

#include <map>

#include "BaseKnapsackTask.h"

typedef std::pair<int, int> wPosition;

class TableKnapsackTask : public BaseKnapsackTask
{
    public:
        explicit TableKnapsackTask(const std::string& sTaskPath)
        : BaseKnapsackTask(sTaskPath),
          m_pPrevious(nullptr),
          m_pNext(nullptr)
        {}
    protected:
        void doSolve(int k) override;

    private:
        void PrepareTaskForSolving();

        std::vector<int> m_vFirstColumn;
        std::vector<int> m_vSecondColumn;
        std::vector<int>* m_pPrevious;
        std::vector<int>* m_pNext;

        std::map<wPosition, std::vector<bool>> m_mXToWPositions;
};


#endif //SEMINAR_TASK_3_TABLEKNAPSACKTASK_H
