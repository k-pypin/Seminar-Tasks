//
// Created by trojan52.
//

#ifndef SEMINAR_TASK_4_SUPPLIERTASK_H
#define SEMINAR_TASK_4_SUPPLIERTASK_H

#include "Definitions.h"
#include "FordFulkersonSolver.h"

class CSupplierTask
{
    public:
        CSupplierTask()
        : m_nSuppliersCount(-1),
          m_nConsumersCount(-1),
          m_nTactsCount(-1),
          m_nSolution(-1),
          m_nBandwidth(-1),
          m_pSolver(new CFordFulkersonSolver)
        { }

        void PopulateTaskFromFile(const std::string& sFile);
        virtual void SolveTask();

        [[nodiscard]] int GetSolutionValue() const
        {
            return m_nSolution;
        }

    protected:
        int m_nSuppliersCount;
        int m_nConsumersCount;
        int m_nTactsCount;
        int m_nSolution;
        int m_nBandwidth;
        std::shared_ptr<CFlowNetwork> m_pFlowNetwork;
        std::unique_ptr<IFlowTaskSolver> m_pSolver;

        // Vectors and matrices
        std::vector<int> m_vSuppliersTotalProduct;
        Matrix m_mSuppliersProductPerTact;
        Matrix m_mConsumersUsedProductPerTact;
        SetsList m_slSuppliers;


        void ClearTaskData();
        void ValidateTask() const;
        void CreateFlowNetwork();
        int GetMaxFlow() const;
};


#endif //SEMINAR_TASK_4_SUPPLIERTASK_H