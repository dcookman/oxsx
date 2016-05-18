#ifndef __OXSX_COUNTING_RESULT__
#define __OXSX_COUNTING_RESULT__
#include <CutLog.h>
#include <vector>
#include <string>

class CountingResult{
 public:
    CountingResult() : fObservedCounts(-1), fSignalEfficiency(-1) {}
    void AddBackground(double expectedRate_, const std::string& name_,
                       const CutLog&);
    void SetSignal(double sigEff_, const std::string& name_, const CutLog&);

    void SetDataLog(const CutLog&);
    void SetObservedCounts(int counts_);

    int    GetObservedCounts() const;
    double GetExpectedCounts() const;

    const std::vector<double>& GetExpectedRates() const;

    void Print() const;
    void SaveAs(const std::string& filename_) const;
    std::string AsString() const;

 private:
    int  fObservedCounts;
    double fSignalEfficiency;
    std::vector<CutLog>      fBackgroundLogs;
    std::vector<double>      fExpectedRates;
    std::vector<std::string> fBackgroundNames;
    std::string              fSignalName;
    CutLog fDataLog;
    CutLog fSignalLog;
};
#endif
