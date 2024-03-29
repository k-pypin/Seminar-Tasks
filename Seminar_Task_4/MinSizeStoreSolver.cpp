//
// Created by trojan52.
//

#include "MinSizeStoreSolver.h"
#include "FordFulkersonSolver.h"

std::pair<bool, int> CMinSizeStoreSolver::SolveFlowTask(std::shared_ptr<CFlowNetwork> pNetwork, TaskData Data)
{
    int nUBound = Data.nU;
    int nLBound = 0;

    while (nUBound > nLBound)
    {
        int nCap = nLBound + (nUBound - nLBound) / 2;
        if (SolveCapTask(pNetwork, Data, nCap))
        {
            nUBound = nCap;
        }
        else
        {
            nLBound = nCap + 1;
        }
    }

    return {true, nLBound };

}

bool CMinSizeStoreSolver::SolveCapTask(std::shared_ptr<CFlowNetwork>& pNetwork, TaskData& rData, int nStoreCap)
{
    pNetwork->SaveNodes();

    for (int i = 0; i < rData.nConsumersCount; ++i)
    {
        for (int t = 0; t < rData.nTactsCount - 1; ++t)
        {
            int nFrom = rData.nSuppliersCount * rData.nTactsCount + rData.nSuppliersCount + 1 + rData.nTactsCount * i + t;
            int nTo = nFrom + 1;

            auto pFArc = new CFlowArc(nFrom, nTo, nStoreCap);
            auto pBArc = new CFlowArc(nTo, nFrom, 0);

            pNetwork->GetNodeByIndex(nFrom)->AddArc(pFArc, pBArc);
            pNetwork->GetNodeByIndex(nTo)->AddArc(pBArc, pFArc);
        }
    }
    CFordFulkersonSolver alg;
    bool bRes = alg.SolveFlowTask(pNetwork, rData).first;

    pNetwork->RestoreNetwork();
    return bRes;
}
