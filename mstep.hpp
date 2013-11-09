/*  
 *  Copyright (C)  2013  George Wong
 *  GNU General Public License
 *
 */

// Macro Step "MStep" class def
class MStep {
  
  public:
    MStep (std::string ins, std::string arg1, std::string arg2) {
      this->size = 3;
      this->INS = ins;
      this->ARG1 = arg1;
      this->ARG2 = arg2;
    }
    MStep (std::string ins, std::string arg1) {
      this->size = 2;
      this->INS = ins;
      this->ARG1 = arg1;
      this->ARG2 = std::string("");
    }
    MStep (std::string ins) {
      this->size = 1;
      this->INS = ins;
      this->ARG1 = std::string("");
      this->ARG2 = std::string("");
    }
    
    // Returns number corresponding to instruction or 0 if unknown
    size_t ins_t () {
      if (this->INS.compare(std::string("MOV"))==0) return 1;
      if (this->INS.compare(std::string("CLK"))==0) return 2;
      if (this->INS.compare(std::string("TYP"))==0) return 3;
      if (this->INS.compare(std::string("PAU"))==0) return 4;
      return 0;
    }
    
    // Returns argument `n' as a string
    std::string arg_s (uint32_t n) {
      if (n==1) {
        return this->ARG1;
      } else if (n==2) {
        return this->ARG2;
      }
      return std::string("NULL");
    }
    
    // Returns argument `n' as a uint32_t
    uint32_t arg_ui (uint32_t n) {
      try {
        std::istringstream buffer;
        if (n==1) {
          buffer.str(this->ARG1);
        } else if (n==2) {
          buffer.str(this->ARG2);
        }
        uint32_t val;
        buffer >> val;
        return val;
      } catch (...) {
        std::cout << "Unable to read argument in ui32 form.\n" << std::endl;
        return 0;
      }
      return 0;
    }
    
    // Returns argument `n' as a double
    double arg_d (uint32_t n) {
      try {
        std::istringstream buffer;
        if (n==1) {
          buffer.str(this->ARG1);
        } else if (n==2) {
          buffer.str(this->ARG2);
        }
        double val;
        buffer >> val;
        return val;
      } catch (...) {
        std::cout << "Unable to read argument in double form.\n" << std::endl;
        return 0;
      }
      return 0;
    }
    
    // Prints full information
    void print () {
      std::cout << "INSTRUCTION: " << this->INS;
      if (size>1) {
        std::cout << "\nARG1: " << this->ARG1;
        if (size>2) {
          std::cout << "\nARG2: " << this->ARG2 << std::endl;
        }
      }
    }
    
    // Prints information on one line
    void print_short() {
      if (size==1)
        std::cout << this->INS << std::endl;
      else if (size==2)
        std::cout << this->INS << ":" << this->ARG1 << std::endl;
      else 
        std::cout << this->INS << ":" << this->ARG1 <<
          ":" << this->ARG2 << std::endl; 
    }
  
  private:
    size_t size;
    std::string INS;
    std::string ARG1;
    std::string ARG2;
};
