//
// Created by Daniel Cookman on 25/11/2022.
//

#ifndef __EResSqrtFunc__
#define __EResSqrtFunc__

// C headers
#include <math.h>
// C++ headers
#include <Exceptions.h>
// OXO headers
#include <Function.h>
#include <ContainerTools.hpp>

class EResSqrtFunc : public Function{
    public:
        // Constructor
        EResSqrtFunc(const std::string& name_) : fName(name_), fParamName("grad"), fGradient(1.) {}
        // Get/Set gradient directly
        void SetGradient(double grad) { fGradient = grad; }
        double GetGradient() const { return fGradient; }
        // Function class interface
        Function* Clone() const;
        double operator()(const std::vector<double>& vals_) const;
        size_t GetNDims() const { return 1; }
        // FitComponent class interface
        void SetParameter(const std::string& name_, double value_);
        double GetParameter(const std::string& name_) const;
        void SetParameters(const ParameterDict& paraDict_);
        ParameterDict GetParameters() const;
        size_t GetParameterCount() const { return 1; }
        std::set<std::string> GetParameterNames() const;
        void RenameParameter(const std::string& old_, const std::string& new_);
        std::string GetName() const { return fName; }
        void SetName(const std::string& name_) { fName= name_; }

    private:
        std::string fName;
        std::string fParamName;
        double fGradient;
};


#endif // __EResSqrtFunc__
