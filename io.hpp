/*  
 *  Copyright (C)  2013  George Wong
 *  GNU General Public License
 *
 */

namespace IO {
  
  // Forward declaration
  bool load_macro (const char *fname,
                   uint32_t *repeats, 
                   uint32_t *steps,
                   uint32_t *wait,
                   std::vector<MStep> *msteps);
  
  // Load file
  bool load_macro (const char *fname, uint32_t *repeats, uint32_t *steps,
                     uint32_t *wait, std::vector<MStep> *msteps) {
    
    std::cout << "Loading macro from: " << fname << std::endl;
    
    uint32_t lineno = 1;
    std::string line;
    std::ifstream fptr(fname);
    
    if (fptr.is_open()) {
      while (! fptr.eof() ) {
        std::getline(fptr, line);
        lineno++;
        if (lineno==3) {
          std::istringstream buffer( line.substr(8,line.length()) );
          uint32_t val;
          buffer >> val;
          *repeats = val;
        }
        if (lineno==4) {
          std::istringstream buffer( line.substr(5,line.length()) );
          uint32_t val;
          buffer >> val;
          *wait = val;
        }
        if (lineno>6) {
          if (line.length()==0) break;
          const char *line_str = line.c_str();
          // The below is a stupid way to do this
          size_t sidx = 0; // Starting index
          std::vector<std::string> argvs;
          for (size_t i=0; i<strlen(line_str); i++) {
            if (line_str[i]==' ') {
              argvs.push_back(line.substr(sidx,i-sidx));
              if (argvs.size()==1) {
                // Special case for TYP, so that we can handle cases
                if (argvs.at(0).compare("TYP")==0) {
                  argvs.push_back(line.substr(++i,strlen(line_str)-i-2));
                  i = strlen(line_str);
                }
              }
              sidx = ++i;
            }
          }
          
          if (argvs.size()==1) {
            msteps->push_back(MStep(argvs.at(0)));
          } else if (argvs.size()==2) {
            msteps->push_back(MStep(argvs.at(0),argvs.at(1)));
          } else {
            msteps->push_back(MStep(argvs.at(0),argvs.at(1),argvs.at(2)));
          }
          *steps = *steps+1;
        }
      }
      fptr.close();
      std::cout << "Success!" << std::endl;
    } else {
      std::cout << "Unable to load file." << std::endl;
      return 1;
    }
    
    return 0;
  }

}
