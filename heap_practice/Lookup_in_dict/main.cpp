#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <unordered_map>
#include <vector>

class Document;

// 编辑者类
class Editor{

    std::string name;
    std::vector<std::shared_ptr<Document>> opened_docs;

public:
    Editor(std::string n):name(n){}
    ~Editor() = default;

    const std::string getName() const {return name;}
    void openDoc(std::shared_ptr<Document> filename);
    void delDoc(std::shared_ptr<Document> filename);
    void editDoc(std::shared_ptr<Document> filename);
    void saveDoc(std::shared_ptr<Document> filename);
    void saveAsDoc(std::shared_ptr<Document> filename, const std::string new_filename);

    void listOpenedDocs();

};

// 文档类
class Document{

    std::string filename;
    std::string content{};
    int count_user = 0;

public:
    Document(std::string f): filename(f){}
    ~Document() = default;


    // getter
    const std::string getFilename() const {return filename;}
    const std::string getContent() const {return content;}


    // 老实说，我不知道这段代码应该给谁
    // 感觉给Editor也行，感觉给ManagerSystem也行
    std::string read() {
        std::ifstream inf(filename);
        if (!inf.is_open()) {
            std::cout << "Can not open the file: " << filename 
                      << ".\nCreating a new file." << std::endl;
            return "";
        }
        
        std::string rstring;
        std::string line;
        while (std::getline(inf, line)) {
            rstring += line + "\n";
        }
        inf.close();
        return rstring;
    }

    void write(std::string new_content, Editor editor){
        content = new_content;
        std::cout << editor.getName() << "edited." << std::endl;
    }

    void save() {
        std::ofstream ouf(filename);
        if (!ouf.is_open()) {
            std::cerr << "Can not save the file: " << filename << std::endl;
            return;
        }
        ouf << content;
        ouf.close();
        std::cout << filename << " has saved." << std::endl;
    }

    void saveAs(const std::string& new_filename) {
        std::ofstream ouf(new_filename);
        if (!ouf.is_open()) {
            std::cerr << "Can not save the file: " << new_filename << std::endl;
            return;
        }
        ouf << content;
        ouf.close();
        std::cout << "Saved as: " << new_filename << std::endl;
    }

    void addUser(){count_user += 1;}
    void removeUser(){
        count_user -= 1;
        if(count_user == 0){save();}
    }

};





// 编辑者类函数定义

void Editor::openDoc(std::shared_ptr<Document> filename){
    filename->addUser();
    opened_docs.push_back(filename);
    std::cout << filename->getFilename() << " has opened." << std::endl;
}

void Editor::delDoc(std::shared_ptr<Document> filename){
    auto beg = opened_docs.begin();
    auto end = opened_docs.end();
    bool find = 1;
    for(;beg != end; ++beg){
        if(*beg == filename){
            break;
        }
        find = 0;
    }

    if(!find){
        std::cout << filename->getFilename() << " did not open." << std::endl;
        return;
    }
    auto it = beg;
    filename->removeUser();
    opened_docs.erase(it);
}

void Editor::editDoc(std::shared_ptr<Document> filename){
    //
}

void Editor::saveDoc(std::shared_ptr<Document> filename){
    filename->save();
}

void Editor::saveAsDoc(std::shared_ptr<Document> filename, const std::string new_filename){
    filename->saveAs(new_filename);
}

void Editor::listOpenedDocs(){
    for(auto it: opened_docs){
        std::cout << it->getFilename();
    }
    std::cout << std::endl;
}





// 文档管理器类
class ManagerSystem{

    std::unordered_map<std::string, std::shared_ptr<Document>> all_docs;

public:
    ManagerSystem() = default;
    ~ManagerSystem() = default;

    std::shared_ptr<Document> createDoc(const std::string& filename){
        auto doc = std::make_shared<Document>(filename);
        all_docs[filename] = doc;
        return doc;
    }

    std::shared_ptr<Document> selectDoc(const std::string filename){
        if(auto r_ptr = all_docs[filename]){
            return r_ptr;
        }
        return nullptr;
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
    
    inf.close();

    auto editor = Editor("Neuroil");
    auto managersys = ManagerSystem();
    managersys.createDoc("test_doc");
    
    (*managersys.selectDoc("test_doc")).save();

}