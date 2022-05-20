void loadMacro(const TString macro_name){
    // load
    const int ret = gROOT->LoadMacro(macro_name);

    if (ret == 0){
        // load success
        cout << "loaded " + macro_name << endl;
    } else {
        //load failed
        cout << "faild " + macro_name << endl;
        exit(1);
    }
}

TString get_project_root() {
    TString project_root = TString(std::getenv("PROJECT_ROOT"));
    if (project_root == "") {
        std::cerr << "enviroment variant error: PROJECT_ROOT is empty" << std::endl;
        exit(1);
    }
    return project_root;
}

void rootlogon(){
    // message
    cout << "executed rootlogon" << endl;
    TString project_root = get_project_root();
    loadMacro(Form("%s/macros/getTree.C", project_root.Data()));
}