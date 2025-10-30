#include <fstream>
#include <string>

int main(){
    std::fstream ouf;
    const std::string s1 = "if(in_num == ";
    const std::string s2 = "){return true;}";
    const std::string s3 = "){return false;}";
    ouf.open("test1.txt", std::ios::out);
    for(int i = 1; i != 3001; ++i){
        std::string c = std::to_string(i);
        if(i % 2 == 0){
            std::string s = s1+c+s2;
            ouf << s;
            ouf << std::endl;
        }else{
            std::string s = s1+c+s3;
            ouf << s;
            ouf << std::endl;
        }
    }
    ouf.close();
}

