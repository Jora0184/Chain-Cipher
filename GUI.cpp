#include "Main.h"
#include "GUI.h"
#include <wx/wx.h>
#include <wx/image.h> // Для wxImage


wxIMPLEMENT_APP(GUI);


bool GUI::OnInit() {
    MainFrame* mainFrame = new MainFrame("GUI Продалжения Винжинери");
    mainFrame->SetClientSize(1000, 500);
    mainFrame->Center();
    mainFrame->Show();
    return true;
}

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    wxPanel* panel = new wxPanel(this);


    // Создаём шрифт с увеличенным размером (например, 12   пунктов)
    wxFont largeFont(14, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxFont largeFont2(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    // Текст "Write with file format (for example: text.txt)"
    wxStaticText* staticText1 = new wxStaticText(panel, wxID_ANY, "Write with file format (for example: text.txt)", wxPoint(25, 30));
    staticText1->SetFont(largeFont); // Применяем шрифт
    textCtrl1 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(245, 50), wxSize(180, 25));
    textCtrl1->SetFont(largeFont); 

    // Кнопка Encode
    wxStaticText* staticText2 = new wxStaticText(panel, wxID_ANY, "Click the button to encode", wxPoint(200, 80));
    staticText2->SetFont(largeFont);
    wxButton* button1 = new wxButton(panel, wxID_ANY, "Encode", wxPoint(291, 101), wxSize(70, 30));
    button1->SetFont(largeFont);
    button1->Bind(wxEVT_BUTTON, &MainFrame::Button1Clicked, this);

    // Mixed ascii alphabet
    wxStaticText* staticText3 = new wxStaticText(panel, wxID_ANY, "Mixed ascii alphabet", wxPoint(25, 130));
    staticText3->SetFont(largeFont);
    textCtrl3 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(20, 150), wxSize(620, 25));
    textCtrl3->SetFont(largeFont2);
    textCtrl4 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(20, 180), wxSize(620, 25));
    textCtrl4->SetFont(largeFont2);

    // Random Key
    wxStaticText* staticText5 = new wxStaticText(panel, wxID_ANY, "Random Key", wxPoint(25, 205));
    staticText5->SetFont(largeFont);
    textCtrl5 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(20, 225), wxSize(620, 25));
    textCtrl5->SetFont(largeFont2);

    // Кнопка Decode
    wxStaticText* staticText6 = new wxStaticText(panel, wxID_ANY, "Click the button to decode", wxPoint(200, 250));
    staticText6->SetFont(largeFont);
    wxButton* button2 = new wxButton(panel, wxID_ANY, "Decode", wxPoint(291, 271), wxSize(70, 30));
    button2->SetFont(largeFont);
    button2->Bind(wxEVT_BUTTON, &MainFrame::Button2Clicked, this);
 
    // Mixed ascii alphabet
    wxStaticText* staticText7 = new wxStaticText(panel, wxID_ANY, "Mixed ascii alphabet", wxPoint(25, 300));
    staticText7->SetFont(largeFont);
    textCtrl7 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(20, 320), wxSize(620, 25));
    textCtrl7->SetFont(largeFont2);
    textCtrl8 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(20, 350), wxSize(620, 25));
    textCtrl8->SetFont(largeFont2);

    // Random Key
    wxStaticText* staticText9 = new wxStaticText(panel, wxID_ANY, "Random Key", wxPoint(25, 375));
    staticText9->SetFont(largeFont);
    textCtrl9 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(20, 400), wxSize(620, 25));
    textCtrl9->SetFont(largeFont2);



    // Процесс XOR
    wxStaticText* staticText10 = new wxStaticText(panel, wxID_ANY, "XOR Process", wxPoint(700, 20));
    staticText10->SetFont(largeFont2);
    textCtrl10 = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(650, 40), wxSize(350, 450), wxTE_MULTILINE | wxTE_READONLY);
    textCtrl10->SetFont(largeFont2);

    // Новая кнопка "Clear" (справа от "Encode")
    wxButton* clearButton = new wxButton(panel, wxID_ANY, "Clear", wxPoint(130, 450), wxSize(400, 30));
    clearButton->SetFont(largeFont);
    clearButton->Bind(wxEVT_BUTTON, &MainFrame::OnClearButtonClicked, this);

}