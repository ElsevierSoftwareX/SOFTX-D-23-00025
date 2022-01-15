#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <map>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <memory>

namespace soot {

    // universal constants
    const double Na = 6.02214086E26;    ///< Avogadro's constant: #/kmol
    const double kb = 1.38064852E-23;   ///< Boltzmann constant = Rg/Na: J/#*K
    const double Rg = 8314.46;          ///< Universal gas constant
    const double eps_c = 2.2;           ///< coagulation constant/van der Waals enhancement factor
    const double Df = 1.8;              ///< soot fractal dimension
    const double rhoSoot = 1850;        ///< soot particle density
    const double bCoag = 0.8536;        ///< coagulation constant, bounded 1/sqrt(2) < bCoag < 1

    // gas species list and properties

    enum class gasSp { C2H2, O, O2, H, H2, OH, H2O, CO, C, C6H6 };
    inline gasSp str2gasSp(const std::string& str) {
        if(str == "C2H2")       return gasSp::C2H2;
        else if(str == "O")     return gasSp::O;
        else if(str == "O2")    return gasSp::O2;
        else if(str == "H")     return gasSp::H;
        else if(str == "H2")    return gasSp::H2;
        else if(str == "OH")    return gasSp::OH;
        else if(str == "H2O")   return gasSp::H2O;
        else if(str == "CO")    return gasSp::CO;
        else if(str == "C")     return gasSp::C;
        else if(str == "C6H6")  return gasSp::C6H6;
        else throw std::domain_error ("Invalid value provided to str2gasSp function");
    };

    const std::map<gasSp, double> gasSpMW = {{gasSp::C2H2, 26.038},      ///< molar weight (kg/kmol)
                                             {gasSp::O,    15.999},
                                             {gasSp::O2,   31.998},
                                             {gasSp::H,    1.008},
                                             {gasSp::H2,   2.016},
                                             {gasSp::OH,   17.007},
                                             {gasSp::H2O,  18.015},
                                             {gasSp::CO,   28.010},
                                             {gasSp::C,    12.011},
                                             {gasSp::C6H6, 78.114}};

    // PAH species list and properties for PAH nucleation and condensation
    // See Blanquart & Pitsch (2009) "A joint volume-surface-hydrogen
    // multi-variate model for soot formation"

    enum class pahSp { C10H8, C12H8, C12H10, C14H10, C16H10, C18H10 };
    inline pahSp str2pahSp(const std::string& str) {
        if(str == "C10H8")       return pahSp::C10H8;
        else if(str == "C12H8")  return pahSp::C12H8;
        else if(str == "C12H10") return pahSp::C12H10;
        else if(str == "C14H10") return pahSp::C14H10;
        else if(str == "C16H10") return pahSp::C16H10;
        else if(str == "C18H10") return pahSp::C18H10;
        else throw std::domain_error ("Invalid value provided to str2gasSp function");
    };

    const std::map<pahSp, double> pahSpMW = {{pahSp::C10H8,  128},      ///< molar weight (kg/kmol)
                                             {pahSp::C12H8,  152},
                                             {pahSp::C12H10, 154},
                                             {pahSp::C14H10, 178},
                                             {pahSp::C16H10, 202},
                                             {pahSp::C18H10, 226}};

    const std::map<pahSp, int> pahSpNC = {{pahSp::C10H8,  10},      ///< number of carbon atoms per PAH species
                                          {pahSp::C12H8,  12},
                                          {pahSp::C12H10, 12},
                                          {pahSp::C14H10, 14},
                                          {pahSp::C16H10, 16},
                                          {pahSp::C18H10, 18}};

    const std::map<pahSp, double> pahSpGamma = {{pahSp::C10H8,  0.0010},      ///< unitless sticking coefficient
                                                {pahSp::C12H8,  0.0030},
                                                {pahSp::C12H10, 0.0085},
                                                {pahSp::C14H10, 0.0150},
                                                {pahSp::C16H10, 0.0250},
                                                {pahSp::C18H10, 0.0390}};

    // custom structures

    struct sourceTermStruct {
        std::vector<double>     sootSourceTerms{0, 0};      // default to 2 moments
        std::map<gasSp, double> gasSourceTerms = {{gasSp::C2H2,0},
                                                  {gasSp::O,   0},
                                                  {gasSp::O2,  0},
                                                  {gasSp::H,   0},
                                                  {gasSp::H2,  0},
                                                  {gasSp::OH,  0},
                                                  {gasSp::H2O, 0},
                                                  {gasSp::CO,  0},
                                                  {gasSp::C,   0},
                                                  {gasSp::C6H6,0}};
        std::map<pahSp, double> pahSourceTerms = {{pahSp::C10H8,  0},
                                                  {pahSp::C12H8,  0},
                                                  {pahSp::C12H10, 0},
                                                  {pahSp::C14H10, 0},
                                                  {pahSp::C16H10, 0},
                                                  {pahSp::C18H10, 0}};
    };

    struct dimerStruct {
        double mDimer = 0;
        double nDimer = 0;
        double wDotD  = 0;
    };

    // model options and string conversion functions

    enum class nucleationMech { NONE, LL, LIN, PAH };
    inline nucleationMech str2nucMech(const std::string& str) {
        if(str == "NONE")     return nucleationMech::NONE;
        else if(str == "LL")  return nucleationMech::LL;
        else if(str == "LIN") return nucleationMech::LIN;
        else if(str == "PAH") return nucleationMech::PAH;
        else throw std::domain_error ("Invalid value provided to str2nucMech function");
    };

    enum class growthMech { NONE, LL, LIN, HACA };
    inline growthMech str2grwMech(const std::string& str) {
        if(str == "NONE")     return growthMech::NONE;
        else if(str == "LL")  return growthMech::LL;
        else if(str == "LIN") return growthMech::LIN;
        else if(str == "HACA") return growthMech::HACA;
        else throw std::domain_error ("Invalid value provided to str2grwMech function");
    };

    enum class oxidationMech { NONE, LL, LEE_NEOH, NSC_NEOH, HACA };
    inline oxidationMech str2oxiMech(const std::string& str) {
        if(str == "NONE")           return oxidationMech::NONE;
        else if(str == "LL")        return oxidationMech::LL;
        else if(str == "LEE_NEOH")  return oxidationMech::LEE_NEOH;
        else if(str == "NSC_NEOH")  return oxidationMech::NSC_NEOH;
        else if(str == "HACA")      return oxidationMech::HACA;
        else throw std::domain_error ("Invalid value provided to str2oxiMech function");
    };

    enum class coagulationMech { NONE, LL, FUCHS, FRENK };
    inline coagulationMech str2coaMech(const std::string& str) {
        if(str == "NONE")       return coagulationMech::NONE;
        else if(str == "LL")    return coagulationMech::LL;
        else if(str == "FUCHS") return coagulationMech::FUCHS;
        else if(str == "FRENK") return coagulationMech::FRENK;
        else throw std::domain_error ("Invalid value provided to str2coaMech function");
    };

    enum class psdMech { MONO, LOGN, QMOM, MOMIC, SECT };
    inline psdMech str2psdMech(const std::string& str) {
        if(str == "MONO")       return psdMech::MONO;
        else if(str == "LOGN")  return psdMech::LOGN;
        else if(str == "QMOM")  return psdMech::QMOM;
        else if(str == "MOMIC") return psdMech::MOMIC;
        else if(str == "SECT")  return psdMech::SECT;
        else throw std::domain_error ("Invalid value provided to str2psdMech function");
    };

}

#endif //CONSTANTS_H