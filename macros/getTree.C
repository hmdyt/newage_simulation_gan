TTree* getTree() {
    TString project_root = get_project_root();
    TString input_file_path = project_root + "/rootfile/cvvar.root";
    TFile* file = TFile::Open(input_file_path);
    TTree* pTree = dynamic_cast< TTree* >( file->Get( "cvvar_tree" ) );
    if( pTree == nullptr ){
        std::cerr << "cant get ttree" << std::endl;
        exit(1);
    }
    return pTree;
}