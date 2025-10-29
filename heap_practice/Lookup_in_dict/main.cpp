#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <vector>

class Editor{

    std::string name;

public:
    Editor(std::string n):name(n){}
    ~Editor() = default;

    const std::string getName() const {return name;}
    
};

class Document{

    std::string filename;
    std::string content{};
    int count_user = 0;

public:
    Document(std::string f): filename(f){}
    ~Document() = default;

    void write(std::string new_content, Editor editor){
        content = new_content;
        std::cout << editor.getName() << "edited." << std::endl;
    }

    void save(std::string filename){
        std::fstream ouf;
        auto beg = content.begin();
        auto end = content.end();
        ouf.open(filename, std::ios::out);
        for(std::string line{}; beg != end; ++beg){
            ouf << *beg;
        }
        ouf.close();
        std::cout << filename << " has saved." << std::endl;
    }

};

class ManagerSystem{

    std::vector<std::shared_ptr<Document>> all_docs;

public:
    ManagerSystem() = default;
    ~ManagerSystem() = default;

    void createDoc(std::string filename){
        auto s_ptr = std::make_shared<Document>(filename);
    }
    void delDoc(std::string filename){
        //
    }
};





int main(){
    std::fstream inf;
    std::string test_title{};
    std::string test_content{};

    inf.open("Oxford 5000.txt", std::ios::in);
    if(!inf){
        std::cerr << "Can not open!" <<std::endl;
        return 1;
    }
    std::string line{};
    while(getline(inf, line)){
        test_content += line;
        test_content += "\n";
    }
    std::cout << test_content;

    auto editor = Editor("Neuroil");
    auto doc = Document(test_title);
    doc.save("test_output.txt");

}