#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <unordered_map>
#include <functional>
#include <stdexcept>
#include <limits>
#include "json.hpp"

class Contact{
    public:
        Contact()=default;
        Contact(std::string n, std::string p, std::string a, std::string sn):
            name(std::move(n)), phone(std::move(p)), addr(std::move(a)), searchName(std::move(sn)){};
        const std::string nameIs()const{return name;}
        const std::string phoneIs()const{return phone;}
        const std::string addrIs()const{return addr;}
        const std::string searchNameIs()const{return searchName;}

        void changeName(const std::string &new_name){name = new_name;}
        void changePhone(const std::string &new_phone){phone = new_phone;}
        void changeAddr(const std::string &new_addr){addr = new_addr;}

    private:
        std::string name;
        std::string phone;
        std::string addr;
        std::string searchName;
};

//类的接口函数

void addContact(std::unordered_map<std::string, Contact>&, std::vector<Contact>&,
                const std::string&, const std::string&, const std::string&);
const Contact* searchContact(const std::unordered_map<std::string, Contact>&, const std::string&);
void delContact(std::vector<Contact>&, const Contact&);

//命令
void add(std::unordered_map<std::string, Contact>&, std::vector<Contact>&);
void search(const std::unordered_map<std::string, Contact>&);
void del(std::unordered_map<std::string, Contact>&, std::vector<Contact>&);
void update(std::vector<Contact>&, std::unordered_map<std::string, Contact>&);
inline void list(const std::vector<Contact>&);
inline void esc(bool& running);

//读写文件部分

void addToJson(const std::vector<Contact>&, nlohmann::json&);
void storeContact(const nlohmann::json&, const std::string&);
void readContact(std::ifstream& ifs, std::unordered_map<std::string, Contact>& contacts_umap,
                std::vector<Contact>& contacts_sort_vec, const std::string& file_name);
//GUI

void startHelpScreen();
void displayDynamic(const Contact&);
void displayDynamic(const std::vector<Contact>& input_contacts);

//其他函数
inline std::string toLower(std::string);
inline int getBigger(int, int);


//主函数
int main(){
    //准备阶段
    std::vector<Contact> contacts_sort_vec;
    std::unordered_map<std::string, Contact> contacts_umap;
    std::string cmd;
    bool running = true;
    std::string file_name = "Contacts.json";
    std::unordered_map<std::string, std::function<void()>> commands={
        {"a", [&]() {add(contacts_umap, contacts_sort_vec);}},
        {"s", [&](){search(contacts_umap);}},
        {"d", [&](){del(contacts_umap, contacts_sort_vec);}},
        {"l", [&](){list(contacts_sort_vec);}},
    	{"u", [&](){update(contacts_sort_vec, contacts_umap);}},
        {"h", startHelpScreen},
        {"e", [&](){esc(running);}}
    };

    //读取文件
    std::ifstream ifs;
    nlohmann::json j = {};
    readContact(ifs, contacts_umap, contacts_sort_vec, file_name);
    //开始交互
    startHelpScreen();

    while(running){
        std::cout << ">";
        std::cin >> cmd;
        cmd = toLower(cmd);

        auto item = commands.find(cmd);
        if(item != commands.end()){item -> second();}
        else{std::cout << "Invalid Input." << std::endl;}
    }
    std::cout << "Saving and closing console...\n";

    //存储文件
    std::ranges::sort(contacts_sort_vec, [](Contact& c1, Contact& c2){
        return (c1.nameIs() < c2.nameIs());
    });

    addToJson(contacts_sort_vec, j);
    storeContact(j, file_name);

    std::cout << "Completed.\n" << "Bye!" << std::endl;
    return 0;
}


//命令定义
void add(std::unordered_map<std::string, Contact>& contacts_umap, std::vector<Contact>& contacts_vec) {
    std::string name, phone, addr;
    std::cout << "Adding a contact..." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Name: ";
    if(std::cin)std::getline(std::cin, name);

    std::cout << "Phone Number: ";
    if(std::cin)std::getline(std::cin, phone);

    std::cout << "Address: ";
    if(std::cin)std::getline(std::cin, addr);

    addContact(contacts_umap, contacts_vec, name, phone, addr);
}

void search(const std::unordered_map<std::string, Contact>& contacts_umap){
    std::string searchName;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Name: ";
    std::getline(std::cin, searchName);
    searchName = toLower(searchName);

    const Contact* target = searchContact(contacts_umap, searchName);
    if(!target){
        return;
    }
    else{
        displayDynamic(*target);
    }

}

void del(std::unordered_map<std::string, Contact>& contacts_umap, std::vector<Contact>& contacts_sort_vec){
    std::string name;
    std::cout << "Type name to delete the contact: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);

    std::string searchName = toLower(name);

    auto it = contacts_umap.find(searchName);
    if(it != contacts_umap.end()){
        // 从vector中删除
        contacts_sort_vec.erase(std::remove_if(contacts_sort_vec.begin(), contacts_sort_vec.end(),
            [&](const Contact& c) { return toLower(c.nameIs()) == searchName; }),
            contacts_sort_vec.end());
        // 从unordered_map中删除
        contacts_umap.erase(it);
        std::cout << "Deleted." << std::endl;
    } else {
        std::cout << "Not found." << std::endl;
    }
}

void update(std::vector<Contact>& contacts_vec, std::unordered_map<std::string, Contact>& contacts_umap){
	
    std::string new_name, new_phone, new_addr;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "New name: ";
    if(std::cin)std::getline(std::cin, new_name);

    std::cout << "\nNew phone: ";
    if(std::cin)std::getline(std::cin, new_phone);

    std::cout << "\nNew address: ";
    if(std::cin)std::getline(std::cin, new_addr);
    std::cout << std::endl;
}

inline void list(const std::vector<Contact>& contacts_vec) {
    displayDynamic(contacts_vec);
}

inline void esc(bool& running){
 running = false;
}

//接口定义
void addContact(std::unordered_map<std::string, Contact>& contacts_umap, std::vector<Contact>& contacts_vec,
    const std::string& target_name, const std::string& target_phone, const std::string& target_addr){

    const std::string searchName = toLower(target_name);
    const Contact new_contact(target_name, target_phone, target_addr, searchName);
    contacts_umap [searchName] = new_contact;
    contacts_vec.push_back(new_contact);
    std::cout << "\nContact " << target_name << " has been created." << std::endl;
}

const Contact* searchContact(const std::unordered_map<std::string, Contact>& contacts_umap,
    const std::string& searchName){
    
    try{
        const Contact* targetContact = &(contacts_umap.at(searchName));
        //若执行失败则抛出out_of_range异常

        return targetContact;
    }catch(const std::out_of_range& oor){
        std::cerr << "Invalid Input. Please try again. "  << std::endl;
        return nullptr;
    }
}

//读写函数定义

void addToJson(const std::vector<Contact>& contacts_vec, nlohmann::json& j){
    j["Contacts"] = nlohmann::json::array();
    for(const auto & i : contacts_vec){
        nlohmann::json contact_json;
        contact_json["name"] = i.nameIs();
        contact_json["phone"] = i.phoneIs();
        contact_json["addr"] = i.addrIs();
        j["Contacts"].push_back(contact_json);
    }
}

void storeContact(const nlohmann::json& j, const std::string& file_name){
    //json文件写
    std::ofstream ofs(file_name);
    if(!ofs.is_open()){
        throw std::runtime_error("Could not open file for writing.");
        //抛出异常runtime_error

        std::cerr << "Failed to save the contacts." << std::endl;
        return;
    }
    ofs << j.dump(4) << std::endl;
    ofs.close();
    std::cout << "Contacts saved."  << std::endl;
}

void readContact(std::ifstream& ifs, std::unordered_map<std::string, Contact>& contacts_umap,
                std::vector<Contact>& contacts_sort_vec, const std::string& file_name){
    //json文件读
    nlohmann::json j{};
    ifs.open(file_name);
    if(!ifs.is_open()){
        std::cerr << "No existing contact file found. A new one will be created." << std::endl;
        return;
    }
    ifs >> j;
    for(auto & i : j["Contacts"]){
        std::string name = i.at("name");
        std::string phone = i.at("phone");
        std::string addr = i.at("addr");
        std::string searchName = toLower(name);
        Contact new_contact(name, phone, addr, searchName);
        contacts_umap[searchName] = new_contact;
        contacts_sort_vec.push_back(new_contact);
    }
    ifs.close();
    std::cout << "Contacts loaded." << std::endl;
}

//GUI定义

void startHelpScreen(){
    std::cout << "+-------------------------------------------------------------+\n" 
              << "|                        Contact v0.1                         |\n" 
              << "+-------------------------------------------------------------+\n" 
              << "|                          Help Menu                          |\n"
              << "+-----------+-------------+-----------------------------------+\n"
              << "|    Key    |   Function  |            Descriptions           |\n" 
              << "+-----------+-------------+-----------------------------------+\n" 
              << "|    A/a    |     Add     |     Add a person into contact.    |\n"
              << "+-----------+-------------+-----------------------------------+\n" 
              << "|    S/s    |    Search   |        Search and call back.      |\n" 
              << "+-----------+-------------+-----------------------------------+\n" 
              << "|    D/d    |    Delete   | Delete the contact form the list. |\n"
              << "+-----------+-------------+-----------------------------------+\n"
              << "|    L/l    |     list    |      List all of the contacts.    |\n"
              << "+-----------+-------------+-----------------------------------+\n"
              << "|    H/h    |     Help    |         Print this screen.        |\n"
              << "+-----------+-------------+-----------------------------------+\n"
              << "|    E/e    |     Exit    |         Exit the progress.        |\n"
              << "+-----------+-------------+-----------------------------------+" << std::endl;
}

void displayDynamic(const Contact& input_contact) {
    std::string name = input_contact.nameIs();
    std::string phone = input_contact.phoneIs();
    std::string addr = input_contact.addrIs();

    int name_w = std::max(static_cast<int>(name.size()), 10);
    int phone_w = std::max(static_cast<int>(phone.size()), 10);
    int addr_w = std::max(static_cast<int>(addr.size()), 15);

    auto line = "+-" + std::string(name_w, '-') + "-+-" 
                    + std::string(phone_w, '-') + "-+-"
                    + std::string(addr_w, '-') + "-+";

    std::cout << line << "\n";
    std::cout << "| " << std::setw(name_w) << std::left << "Name" 
              << " | " << std::setw(phone_w) << std::left << "Phone" 
              << " | " << std::setw(addr_w) << std::left << "Address" << " |\n";
    std::cout << line << "\n";
    std::cout << "| " << std::setw(name_w) << std::left << name
              << " | " << std::setw(phone_w) << std::left << phone
              << " | " << std::setw(addr_w) << std::left << addr << " |\n";
    std::cout << line << std::endl;
}

void displayDynamic(const std::vector<Contact>& input_contacts) {
    int name_w = 10;
    int phone_w = 10;
    int addr_w = 15;

    for(auto& contact : input_contacts) {
        std::string name = contact.nameIs();
        std::string phone = contact.phoneIs();
        std::string addr = contact.addrIs();

        name_w = std::max(static_cast<int>(name.size()), name_w);
        phone_w = std::max(static_cast<int>(phone.size()), phone_w);
        addr_w = std::max(static_cast<int>(addr.size()), addr_w);
    }

    auto line = "+-" + std::string(name_w, '-') + "-+-"
                    + std::string(phone_w, '-') + "-+-"
                    + std::string(addr_w, '-') + "-+";

    std::cout << line << "\n";
    std::cout << "| " << std::setw(name_w) << std::left << "Name"
              << " | " << std::setw(phone_w) << std::left << "Phone"
              << " | " << std::setw(addr_w) << std::left << "Address" << " |\n";
    std::cout << line << "\n";
    for(auto& contact : input_contacts) {
        std::cout << "| " << std::setw(name_w) << std::left << contact.nameIs()
              << " | " << std::setw(phone_w) << std::left << contact.phoneIs()
              << " | " << std::setw(addr_w) << std::left << contact.addrIs() << " |\n";
        std::cout << line << std::endl;
    }

}


//其他函数
inline std::string toLower(std::string s){
    std::ranges::transform(s, s.begin(),
                           [](unsigned char c){ return std::tolower(c); });
    return s;
}

inline int getBigger(int a, int b) {
    if(a > b) { return a;}
    return b;
}

//inline void sort(std::vector<Contact>& contacts_sort_vec){
//    std::sort(contacts_sort_vec.begin(), contacts_sort_vec.end(), [&](){
//        return ((*contacts_sort_vec.begin()).seachNameIs()) < ((*contacts_sort_vec.begin()).seachNameIs());
//    });
//}
