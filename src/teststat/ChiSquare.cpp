#include <ChiSquare.h>
#include <DataSet.h>
#include <sstream>
#include <Exceptions.h>

double
ChiSquare::Evaluate()
{
    // the first time this is called, bin data into a pdf
    if (!fCalculatedDataDist)
    {
        BinData();
        fCalculatedDataDist = true;
    }

    // Construct
    fSystematicManager.Construct();

    // Apply systematics
    fPdfManager.ApplySystematics(fSystematicManager);

    // Now calculate the ChiSquared
    double chiSquare = 0;
    std::vector<double> binCentre(fDataDist.GetNDims());
    for (size_t i = 0; i < fDataDist.GetNBins(); i++)
    {
        fDataDist.GetAxes().GetBinCentres(i, binCentre);
        double expected = fPdfManager.Probability(binCentre);
        double deviation = fDataDist.GetBinContent(i) - expected;
        chiSquare += deviation * deviation / expected; // poisson errors
    }

    return chiSquare;
}

void ChiSquare::BinData()
{

    BinnedED dataDist(fPdfManager.GetOriginalPdf(0)); // make a copy for same binning and data rep
    dataDist.Empty();

    for (size_t i = 0; i < fDataSet->GetNEntries(); i++)
    {
        dataDist.Fill(fDataSet->GetEntry(i));
    }

    fDataDist = dataDist;
}

void ChiSquare::RegisterFitComponents()
{
    fComponentManager.AddComponent(&fPdfManager);

    // Because the limits are set by name you only need to make sure you add the systematic once.
    const std::map<std::string, std::vector<Systematic *>> sys_ = fSystematicManager.GetSystematicsGroup();
    std::vector<std::string> alreadyAdded;
    for (const auto &group_ : sys_)
    {
        for (const auto &item : group_.second)
        {
            if (std::find(alreadyAdded.begin(), alreadyAdded.end(), item->GetName()) == alreadyAdded.end())
            {
                fComponentManager.AddComponent(item);
                alreadyAdded.push_back(item->GetName());
            }
        }
    }
}

void ChiSquare::SetParameters(const ParameterDict &params_)
{
    try
    {
        fComponentManager.SetParameters(params_);
    }
    catch (const ParameterError &e_)
    {
        throw ParameterError(std::string("ChiSquare: ") + e_.what());
    }
}

ParameterDict
ChiSquare::GetParameters() const
{
    return fComponentManager.GetParameters();
}

size_t
ChiSquare::GetParameterCount() const
{
    return fComponentManager.GetTotalParameterCount();
}

std::set<std::string>
ChiSquare::GetParameterNames() const
{
    return fComponentManager.GetParameterNames();
}

void ChiSquare::SetDataSet(DataSet *dataSet_)
{
    fDataSet = dataSet_;
}

DataSet *
ChiSquare::GetDataSet()
{
    return fDataSet;
}
