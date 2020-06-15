#ifndef RDM1
#define RDM1
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Constraint_RDM1{
private:
    string m_type, m_Cfilename, m_Jfilename;
    std::vector<string> m_A;
    std::vector<string> m_B;
    std::vector<string> m_C;
    std::vector<string> m_J;
    int m_nmos, m_elec;
    double m_curr;
public:
    Constraint_RDM1(int nmos, int elec, string type): m_nmos(nmos), m_elec(elec), m_type(type){}
    Constraint_RDM1(int nmos, int elec, string type, double curr): m_nmos(nmos), m_elec(elec), m_type(type), m_curr(curr){}
    void printSDP(string);
    void print4num(string);
    void printA(string);
    void printB(string);
    void setCmat(string);
    void setJmat(string);
    void printC(string);
    void add_Constraint();
    void add_TraceConstraint();
    void add_TraceConstraint_Real();
    void add_TraceConstraint_Imag();
    void add_DQConstraint();
    void add_DQConstraint_Real();
    void add_DQConstraint_Imag();
    void add_OffdiagConstraint();
    void add_OffdiagConstraint_Real();
    void add_OffdiagConstraint_Imag();
    void add_HermrealConstraint();
    void add_HermimagConstraint();
    void add_HermdiagConstraint();
    void add_CurrConstraint();
};

void Constraint_RDM1::add_Constraint(){
    if(m_type == "Real" || m_type == "real" || m_type == "r"){
        add_TraceConstraint_Real();
        add_DQConstraint_Real();
        add_OffdiagConstraint_Real();
    }
    else{
        add_TraceConstraint_Imag();
        add_DQConstraint_Imag();
        add_OffdiagConstraint_Imag();
        add_HermrealConstraint();
        add_HermimagConstraint();
        add_HermdiagConstraint();
        add_CurrConstraint();
    }
}

void Constraint_RDM1::add_TraceConstraint(){
    if(m_type == "Real" || m_type == "real" || m_type == "r") add_TraceConstraint_Real();
    else add_TraceConstraint_Imag();
}

void Constraint_RDM1::add_DQConstraint(){
    if(m_type == "Real" || m_type == "real" || m_type == "r") add_DQConstraint_Real();
    else add_DQConstraint_Imag();
}

void Constraint_RDM1::add_OffdiagConstraint(){
    if(m_type == "Real" || m_type == "real" || m_type == "r") add_OffdiagConstraint_Real();
    else add_OffdiagConstraint_Imag();
}

void Constraint_RDM1::add_TraceConstraint_Real(){
    m_B.push_back(std::to_string(m_elec));
    for(int i=1; i<=m_nmos; i++)
        m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*m_nmos+i)+" "+std::to_string(1.00000));
}

void Constraint_RDM1::add_TraceConstraint_Imag(){
    m_B.push_back(std::to_string(m_elec*2));
    for(int i=1; i<=(m_nmos*2); i++)
        m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*2*m_nmos+i)+" "+"1.00000");
}

void Constraint_RDM1::add_DQConstraint_Real(){
    for(int i=1; i<=m_nmos; i++){
        m_B.push_back("1.00000");
        m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*m_nmos+i)+" "+"1.00000");
        m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*m_nmos+i+m_nmos*m_nmos)+" "+"1.00000");
    }
}

void Constraint_RDM1::add_DQConstraint_Imag(){
    for(int i=1; i<=m_nmos; i++){
        m_B.push_back("2.00000");
        m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*2*m_nmos+i)+" "+"1.00000");
        m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i+m_nmos-1)*2*m_nmos+i+m_nmos)+" "+"1.00000");
        m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*2*m_nmos+i+4*m_nmos*m_nmos)+" "+"1.00000");
        m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i+m_nmos-1)*2*m_nmos+i+m_nmos+4*m_nmos*m_nmos)+" "+"1.00000");
    }
}

void Constraint_RDM1::add_OffdiagConstraint_Real(){
    for(int i=1; i<=m_nmos; i++)
        for(int j=1; j < i; j++){
            m_B.push_back("1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((j-1)*m_nmos+i)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*m_nmos+j)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((j-1)*m_nmos+i+m_nmos*m_nmos)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*m_nmos+j+m_nmos*m_nmos)+" "+"1.00000");
        }
}

void Constraint_RDM1::add_OffdiagConstraint_Imag(){
    for(int i=1; i<=m_nmos; i++)
        for(int j=1; j < i; j++){
            m_B.push_back("0.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((j-1)*2*m_nmos+i)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*2*m_nmos+j)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((j+m_nmos-1)*2*m_nmos+i+m_nmos)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i+m_nmos-1)*2*m_nmos+j+m_nmos)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((j-1)*2*m_nmos+i+4*m_nmos*m_nmos)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*2*m_nmos+j+4*m_nmos*m_nmos)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((j+m_nmos-1)*2*m_nmos+i+m_nmos+4*m_nmos*m_nmos)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i+m_nmos-1)*2*m_nmos+j+m_nmos+4*m_nmos*m_nmos)+" "+"1.00000");

            m_B.push_back("0.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((j-1)*2*m_nmos+i+m_nmos)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*2*m_nmos+j+m_nmos)+" "+"-1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((j+m_nmos-1)*2*m_nmos+i)+" "+"-1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i+m_nmos-1)*2*m_nmos+j)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((j-1)*2*m_nmos+i+m_nmos+4*m_nmos*m_nmos)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*2*m_nmos+j+m_nmos+4*m_nmos*m_nmos)+" "+"-1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((j+m_nmos-1)*2*m_nmos+i+4*m_nmos*m_nmos)+" "+"-1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i+m_nmos-1)*2*m_nmos+j+4*m_nmos*m_nmos)+" "+"1.00000");
        }
}

void Constraint_RDM1::add_HermrealConstraint(){
    for(int i=1; i<=m_nmos; i++)
        for(int j=1; j < i; j++){
            m_B.push_back("0.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((j-1)*2*m_nmos+i)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*2*m_nmos+j)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((j+m_nmos-1)*2*m_nmos+i+m_nmos)+" "+"-1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i+m_nmos-1)*2*m_nmos+j+m_nmos)+" "+"-1.00000");

            m_B.push_back("0.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((j-1)*2*m_nmos+i+4*m_nmos*m_nmos)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*2*m_nmos+j+4*m_nmos*m_nmos)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((j+m_nmos-1)*2*m_nmos+i+m_nmos+4*m_nmos*m_nmos)+" "+"-1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i+m_nmos-1)*2*m_nmos+j+m_nmos+4*m_nmos*m_nmos)+" "+"-1.00000");
        }
}

void Constraint_RDM1::add_HermimagConstraint(){
    for(int i=1; i<=m_nmos; i++)
        for(int j=1; j < i; j++){
            m_B.push_back("0.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((j-1)*2*m_nmos+i+m_nmos)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*2*m_nmos+j+m_nmos)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((j+m_nmos-1)*2*m_nmos+i)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i+m_nmos-1)*2*m_nmos+j)+" "+"1.00000");

            m_B.push_back("0.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((j-1)*2*m_nmos+i+m_nmos+4*m_nmos*m_nmos)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*2*m_nmos+j+m_nmos+4*m_nmos*m_nmos)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((j+m_nmos-1)*2*m_nmos+i+4*m_nmos*m_nmos)+" "+"1.00000");
            m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i+m_nmos-1)*2*m_nmos+j+4*m_nmos*m_nmos)+" "+"1.00000");
        }
}

void Constraint_RDM1::add_HermdiagConstraint(){
    for(int i=1; i<=m_nmos; i++){
        /*D*/
        m_B.push_back("0.00000");
        m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*2*m_nmos+i)+" "+"1.00000");
        m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i+m_nmos-1)*2*m_nmos+i+m_nmos)+" "+"-1.00000");

        m_B.push_back("0.00000");
        m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*2*m_nmos+i+m_nmos)+" "+"1.00000");
        m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i+m_nmos-1)*2*m_nmos+i)+" "+"1.00000");

        /*Q*/
        m_B.push_back("0.00000");
        m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*2*m_nmos+i+4*m_nmos*m_nmos)+" "+"1.00000");
        m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i+m_nmos-1)*2*m_nmos+i+m_nmos+4*m_nmos*m_nmos)+" "+"-1.00000");

        m_B.push_back("0.00000");
        m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*2*m_nmos+i+m_nmos+4*m_nmos*m_nmos)+" "+"1.00000");
        m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i+m_nmos-1)*2*m_nmos+i+4*m_nmos*m_nmos)+" "+"1.00000");

    }
}

void Constraint_RDM1::add_CurrConstraint(){
    ifstream in(m_Jfilename);
    string val="";
    while (in >> val)
	    m_J.push_back(val);
    in.close();
    m_B.push_back(std::to_string(m_curr));

    for(int i=1; i<=m_nmos; i++){
        for(int j=1; j<i; j++){
            if(std::stod(m_J[(i-1)*m_nmos+j-1]) != 0){
                std::cout<<m_J[(i-1)*m_nmos+j-1]<<std::endl;
                m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*2*m_nmos+j+m_nmos)+" "+m_J[(i-1)*m_nmos+j-1]); //Upper Im Mat
                m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((j-1)*2*m_nmos+i+m_nmos)+" "+m_J[(j-1)*m_nmos+i-1]); //Upper Im Mat
                m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((i-1)*2*m_nmos+j+2*m_nmos*m_nmos)+" "+m_J[(j-1)*m_nmos+i-1]); //Lower Im Mat
                m_A.push_back(std::to_string(m_B.size())+" "+std::to_string((j-1)*2*m_nmos+i+2*m_nmos*m_nmos)+" "+m_J[(i-1)*m_nmos+j-1]); //Lower Im Mat
            }
        }
    }
}

void Constraint_RDM1::printSDP(string filename){
    ofstream out(filename);
    print4num(filename);
    printA(filename);
    printB(filename);
    printC(filename);
}

void Constraint_RDM1::print4num(string filename){
    ofstream out(filename, std::ios::app);
    if(m_type == "Real") out<<std::to_string(m_B.size())<<" "<<std::to_string(2*m_nmos*m_nmos)<<" "<<std::to_string(m_A.size())<<" "
                            <<2<<endl<<std::to_string(m_nmos)<<endl<<std::to_string(m_nmos)<<endl;
    else out<<std::to_string(m_B.size())<<" "<<std::to_string(8*m_nmos*m_nmos)<<" "<<std::to_string(m_A.size())<<" "
            <<2<<endl<<std::to_string(2*m_nmos)<<endl<<std::to_string(2*m_nmos)<<endl;
    out.close();
}

void Constraint_RDM1::printA(string filename){
    ofstream out(filename, std::ios::app);
    for(auto it = m_A.cbegin(); it != m_A.cend() && !it->empty(); ++it)
        out << *it <<endl;
    out.close();
}

void Constraint_RDM1::printB(string filename){
    ofstream out(filename, std::ios::app);
    for(auto it = m_B.cbegin(); it != m_A.cend() && !it->empty(); ++it)
        out << *it <<endl;
    out.close();
}

void Constraint_RDM1::setCmat(string cfilename){
    m_Cfilename = cfilename;
}

void Constraint_RDM1::setJmat(string Jfilename){
    m_Jfilename = Jfilename;
}

void Constraint_RDM1::printC(string filename){
    ifstream in(m_Cfilename);
    string val="";
    while (in >> val)
	    m_C.push_back(val);
    in.close();

    ofstream out(filename, std::ios::app);

    for(int i=0; i<2*m_nmos; i++)
        for(int j=0; j<2*m_nmos; j++)
            out << (i==j ? m_C[i%m_nmos]: "0.00000") << endl;
    
    for(int i=0; i<4*m_nmos*m_nmos; i++)
        out << "0.00000" << endl;
    out.close();
}
#endif
