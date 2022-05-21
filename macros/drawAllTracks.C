void drawAllTracks() {
    TTree* tree = getTree();
    std::vector<double>* x_xz = nullptr;
    std::vector<double>* z_xz = nullptr;
    std::vector<double>* y_yz = nullptr;
    std::vector<double>* z_yz = nullptr;
    //double ene_high;
    tree->SetBranchAddress("x_xz", &x_xz);
    tree->SetBranchAddress("z_xz", &z_xz);
    tree->SetBranchAddress("y_yz", &y_yz);
    tree->SetBranchAddress("z_yz", &z_yz);
    //tree->SetBranchAddress("ene_high", &ene_high);
    TH2D* hist_xz = new TH2D(
        "hist_xz",
        "hist_xz",
        768,
        -15,
        15,
        1000,
        -40,
        60
    );
    TH2D* hist_yz = new TH2D(
        "hist_yz",
        "hist_yz",
        768,
        -15,
        15,
        1000,
        -40,
        60
    );
    int n_entries = tree->GetEntries();
    for (int i_event = 0; i_event < n_entries; i_event++) {
        tree->GetEntry(i_event);
        if (x_xz == nullptr || z_xz == nullptr) continue;
        if (y_yz == nullptr || z_yz == nullptr) continue;
        if (x_xz->size() != z_xz->size()) { continue; }
        if (y_yz->size() != y_yz->size()) { continue; }
        for (int j = 0; j < z_xz->size(); j++) { hist_xz->Fill(x_xz->at(j), z_xz->at(j)); }
        for (int j = 0; j < z_yz->size(); j++) { hist_yz->Fill(y_yz->at(j), z_yz->at(j)); }
    }

    TCanvas* canvas = new TCanvas("c", "c", 800, 1200);
    canvas->Divide(1, 2);
    canvas->cd(1);
    hist_xz->Draw("colz");
    canvas->cd(2);
    hist_yz->Draw("colz");

}