{

  gROOT->Reset();
  gROOT->SetStyle("Plain");
  //gROOT->SetStyle("color2D");
  gStyle->SetHistLineWidth(1);
  gStyle->SetPalette(1);
  gStyle->SetPaperSize(20,26);
  
  // Turn off some borders
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetDrawBorder(0);
  gStyle->SetCanvasBorderSize(0);
  gStyle->SetFrameBorderSize(0);
  gStyle->SetPadBorderSize(1);
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleFontSize(0.07); // 0.05

  // Say it in black and white!
  gStyle->SetAxisColor(1, "xyz");
  gStyle->SetCanvasColor(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetFrameLineColor(1);
  gStyle->SetHistFillColor(0);
  gStyle->SetHistLineColor(1);

  //gStyle->SetPadColor(1);
  gStyle->SetPadColor(kWhite);
  gStyle->SetStatColor(0);
  gStyle->SetStatTextColor(1);
  gStyle->SetTitleColor(1);
  gStyle->SetTitleTextColor(1);
  gStyle->SetLabelColor(1,"xyz");
  // Show functions in red...
  gStyle->SetFuncColor(2);
  gStyle->SetOptStat(00000);  

  ///////////////////////////////////////////////////////////////////

  // Read input files

  int nlines = 0;
  string line;
  ifstream myfile("files.list");

  while(getline(myfile,line)){ ++nlines; }
  TFile *rootfile[nlines];

  TString fileName("files.list");
  ifstream inputFile(fileName.Data(), std::ios::in);
  
  if (!inputFile) {
    std::cerr << "Can not open input file: " << fileName.Data() << endl;
    return;
  }  

  std::string inputString;
  int i = 0;
  while(inputFile >> inputString) {
    cout << "Adding file: " << inputString << endl;
    rootfile[i] = new TFile(inputString.c_str());
    i++;
  }

  // // --- Create a new canvas.
  int canwidth = 800;
  int canheight = 400;
  
  TCanvas c0("c0","--c0--",canwidth,canheight);
  c0->ToggleEventStatus();
  c0->Clear();
  
  // Read detector information
  std::string det = "";

  if (inputString.find("ECAL") != std::string::npos)
    {det = "ECal";}
  else if (inputString.find("P0D") != std::string::npos)
    {det = "P0D";}
  else if (inputString.find("SMRD") != std::string::npos)
    {det = "SMRD";}
  else
    std::cout<<"Detector name not found in input file";

  ///////////////////////////////////////////////////////////////////

  // TGraph *DeadCh[nlines];
  
  // if ((TFile*)rootfile[0]->GetListOfKeys()->Contains("DeadChGraph"))
  //   for(int k = 0; k < nlines; k++) DeadCh[k] = (TGraph*)rootfile[k]->Get("DeadChGraph");
  // else break;

  DeadChGraph.SetTitle(Form("%s Number of Dead Channels", det.c_str()));
  DeadChGraph.GetXaxis().SetTimeDisplay(1);
  DeadChGraph.GetXaxis().SetTimeFormat("%d\/%m");
  DeadChGraph->Draw("APL");
  DeadChGraph.GetYaxis().SetNoExponent();
  DeadChGraph.GetXaxis().SetTitle("Date GMT");
  DeadChGraph.GetXaxis().SetTitleOffset(0.75);
  DeadChGraph.GetXaxis().SetLabelSize(0.05);
  DeadChGraph.GetXaxis().SetTitleSize(0.055);
  DeadChGraph.GetYaxis().SetLabelSize(0.055);
  DeadChGraph.GetYaxis().SetTitleSize(0.0);
  c0->SaveAs(Form("DeadChannels%s.png",det.c_str()));

  BadChGraph.SetTitle(Form("%s Number of Bad Channels", det.c_str()));
  BadChGraph.GetXaxis().SetTimeDisplay(1);
  BadChGraph.GetXaxis().SetTimeFormat("%d\/%m");
  BadChGraph->Draw("APL");
  BadChGraph.GetYaxis().SetNoExponent();
  BadChGraph.GetXaxis().SetTitle("Date GMT");
  BadChGraph.GetXaxis().SetTitleOffset(0.75);
  BadChGraph.GetXaxis().SetLabelSize(0.05);
  BadChGraph.GetXaxis().SetTitleSize(0.055);
  BadChGraph.GetYaxis().SetLabelSize(0.055);
  BadChGraph.GetYaxis().SetTitleSize(0.0);
  c0->SaveAs(Form("BadChannels%s.png",det.c_str()));

  OverChGraph.SetTitle(Form("%s Number of Overflow Channels", det.c_str()));
  OverChGraph.GetXaxis().SetTimeDisplay(1);
  OverChGraph.GetXaxis().SetTimeFormat("%d\/%m");
  OverChGraph->Draw("APL");
  OverChGraph.GetYaxis().SetNoExponent();
  OverChGraph.GetXaxis().SetTitle("Date GMT");
  OverChGraph.GetXaxis().SetTitleOffset(0.75);
  OverChGraph.GetXaxis().SetLabelSize(0.05);
  OverChGraph.GetXaxis().SetTitleSize(0.055);
  OverChGraph.GetYaxis().SetLabelSize(0.055);
  OverChGraph.GetYaxis().SetTitleSize(0.0);
  c0->SaveAs(Form("OverChannels%s.png",det.c_str()));

  UnderChGraph.SetTitle(Form("%s Number of Underflow Channels", det.c_str()));
  UnderChGraph.GetXaxis().SetTimeDisplay(1);
  UnderChGraph.GetXaxis().SetTimeFormat("%d\/%m");
  UnderChGraph->Draw("APL");
  UnderChGraph.GetYaxis().SetNoExponent();
  UnderChGraph.GetXaxis().SetTitle("Date GMT");
  UnderChGraph.GetXaxis().SetTitleOffset(0.75);
  UnderChGraph.GetXaxis().SetLabelSize(0.05);
  UnderChGraph.GetXaxis().SetTitleSize(0.055);
  UnderChGraph.GetYaxis().SetLabelSize(0.055);
  UnderChGraph.GetYaxis().SetTitleSize(0.0);
  c0->SaveAs(Form("underChannels%s.png",det.c_str()));

  TotChGraph.SetTitle(Form("%s Number of Channels scanned", det.c_str()));
  TotChGraph.GetXaxis().SetTimeDisplay(1);
  TotChGraph.GetXaxis().SetTimeFormat("%d\/%m");
  TotChGraph->Draw("APL");
  TotChGraph.GetYaxis().SetNoExponent(false);
  TotChGraph.GetXaxis().SetTitle("Date GMT");
  TotChGraph.GetXaxis().SetTitleOffset(0.75);
  TotChGraph.GetXaxis().SetLabelSize(0.05);
  TotChGraph.GetXaxis().SetTitleSize(0.055);
  TotChGraph.GetYaxis().SetLabelSize(0.055);
  TotChGraph.GetYaxis().SetTitleSize(0.0);
  c0->SaveAs(Form("totChannels%s.png",det.c_str()));
}
