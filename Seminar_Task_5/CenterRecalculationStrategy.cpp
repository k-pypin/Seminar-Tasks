//
// Created by trojan52.
//

#include "CenterRecalculationStrategy.h"
#include "Cluster.h"
#include "SalesmanTask.h"

ClusterList CCenterRecalculationStrategy::GetClusters(const std::vector<CCity> &rCities, const std::vector<int> &rCenters) const
{
    ClusterList Clusters(rCenters.size());
    for (int i = 0; i < rCenters.size(); ++i)
    {
        auto pCurrentClaster = std::make_shared<Cluster>();
        pCurrentClaster->pCenter = CPoint(rCities[rCenters[i]].m_Location.m_X,
                                          rCities[rCenters[i]].m_Location.m_Y);
        pCurrentClaster->vCitiesIds.push_back(rCenters[i]);
        Clusters[i] = pCurrentClaster;
    }
    auto contains_in_centers = [&rCenters](int nIndex) -> bool
    {
        bool bFound = false;
        for (int nCenter : rCenters)
        {
            if (nCenter == nIndex)
            {
                bFound = true;
                break;
            }
        }
        return bFound;
    };

    for (int i = 0; i < rCities.size(); ++i)
    {
        double dMin = std::numeric_limits<double>::max();
        int nNearestCluster = INCORRECT_VALUE;
        CPoint pCurrent = CPoint(rCities[i].m_Location.m_X, rCities[i].m_Location.m_Y);
        if (contains_in_centers(i))
        {
            continue;
        }

        for (int j = 0; j < Clusters.size(); ++j)
        {
            double dDist = pCurrent.DistanceTo(Clusters[j]->pCenter);
            if (dDist < dMin)
            {
                dMin = dDist;
                nNearestCluster = j;
            }
        }
        Clusters[nNearestCluster]->vCitiesIds.push_back(i);
        Clusters[nNearestCluster]->pCenter = CenterPoint(Clusters[nNearestCluster]->vCitiesIds, rCities);
    }

    return Clusters;
}

CPoint CCenterRecalculationStrategy::CenterPoint(const std::vector<int> &vIndexes, const std::vector<CCity>& rCities) const
{
    double SumX = 0.0;
    double SumY = 0.0;

    for (int id : vIndexes)
    {
        SumX += rCities[id].m_Location.m_X;
        SumY += rCities[id].m_Location.m_Y;
    }
    int nSize = vIndexes.size();
    return CPoint((SumX / nSize), (SumY / nSize));
}

