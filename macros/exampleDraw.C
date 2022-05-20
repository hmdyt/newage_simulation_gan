void exampleDraw( const int& eventID = 1)
{   
    TString project_root = std::getenv("PROJECT_ROOT");
    TString input_file_path = project_root + "/rootfile/cvvar.root";
    TFile file( input_file_path );
    TTree* pTree = dynamic_cast< TTree* >( file.Get( "cvvar_tree" ) );
    if( pTree == nullptr ) return;

    std::vector< double >* x_xz = nullptr;
    std::vector< double >* z_xz = nullptr;
    pTree->SetBranchAddress( "x_xz", &x_xz );
    pTree->SetBranchAddress( "z_xz", &z_xz );
    
    TH2F histXZ( "histXZ", "histXZ", 768, -15, 15, 1000, -40, 60 );
    pTree->GetEntry( eventID );

    if( x_xz == nullptr || z_xz == nullptr ) return;
    if( x_xz->size( ) != z_xz->size( ) ) return;
    for( int idx = 0; idx < x_xz->size( ); ++idx )
        histXZ.Fill( x_xz->at( idx ), z_xz->at( idx ) );

    TCanvas cvs( "cvs", "cvs", 800, 600 );

    const Int_t NRGBs = 5;
    const Int_t NCont = 255;
    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 1.00 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.80, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable( NRGBs, stops, red, green, blue, NCont );
    gStyle->SetNumberContours( NCont );

    gPad->SetRightMargin( 0.2 );


    histXZ.SetXTitle( "X [cm]" );
    histXZ.SetYTitle( "Z [cm]" );
    histXZ.SetZTitle( "Counts" );
    histXZ.Draw("colz");

    cvs.SaveAs( project_root + Form("/img/exampleDraw/hitmap_%d.png", eventID) );
    
    return;
}

void drawAllEvents() {
    TString project_root = std::getenv("PROJECT_ROOT");
    TString input_file_path = project_root + "/rootfile/cvvar.root";
    TFile file( input_file_path );
    TTree* pTree = dynamic_cast< TTree* >( file.Get( "cvvar_tree" ) );
    if( pTree == nullptr ) return;
    long long int n_entries = pTree->GetEntries();
    for (int i_event = 0; i_event < n_entries; i_event++){
        exampleDraw(i_event);
    }
}