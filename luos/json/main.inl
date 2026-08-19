namespace Gnik_luos {
    Json::Json() { 
        buffer = std::vector<char>(65536);
    };
    Json::~Json() { 
        clear(); 
    };
}