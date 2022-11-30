#include <EResSqrtFunc.h>

Function* EResSqrtFunc::Clone() const {
    return static_cast<Function*> (new EResSqrtFunc(*this));
}

double EResSqrtFunc::operator()(const std::vector<double>& vals_) const {
    return fGradient*sqrt(abs(vals_.at(0)));
}

// FitComponent class interface
void EResSqrtFunc::SetParameter(const std::string& name_, double value_) {
    if(name_ != fParamName)
        throw ParameterError("Scale: can't set " + name_ + ", " + fParamName + " is the only parameter" );
    fGradient = value_;
}

double EResSqrtFunc::GetParameter(const std::string& name_) const {
    if(name_ != fParamName)
        throw ParameterError("Scale: can't get " + name_ + ", " + fParamName + " is the only parameter" );
    return fGradient;
}

void EResSqrtFunc::SetParameters(const ParameterDict& paraDict_) {
    try { fGradient = paraDict_.at(fParamName); }
    catch(const std::out_of_range& e_){
        throw ParameterError("Set dictionary is missing " + fParamName + ". I did contain: \n" + ContainerTools::ToString(ContainerTools::GetKeys(paraDict_)));
    }
}

ParameterDict EResSqrtFunc::GetParameters() const {
    ParameterDict d;
    d[fParamName] = fGradient;
    std::cout << "Hi!\n";
    return d;
}

std::set<std::string> EResSqrtFunc::GetParameterNames() const {
    std::set<std::string> names_ = {fParamName};
    return names_;
}

void EResSqrtFunc::RenameParameter(const std::string& old_, const std::string& new_) {
    if(old_ != fParamName)
        throw ParameterError("Scale: can't rename " + old_ + ", " + fParamName + " is the only parameter" );
    fParamName = new_;
}
