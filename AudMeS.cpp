// -*- C++ -*- generated by wxGlade 0.3.1 on Wed Sep 29 16:09:00 2004

#include "AudMeS.h"

#include <math.h>

#ifdef __WXMSW__
#include <windows.h>
#endif

#include "fourier.h"
#include "dlg_audiointerface.h"
#include "event_ids.h"

//#define XSCALEINTIME 1

IMPLEMENT_CLASS( MainFrame, wxFrame )

BEGIN_EVENT_TABLE( MainFrame, wxFrame )
  EVT_TOGGLEBUTTON( ID_SPANSTART, MainFrame::OnSpanStart )
  EVT_TOGGLEBUTTON( ID_GENSTART, MainFrame::OnGenStart )
  EVT_TOGGLEBUTTON( ID_OSCSTART, MainFrame::OnOscStart )
  EVT_TOGGLEBUTTON( ID_FRMSTART, MainFrame::OnFrmStart )
  EVT_MENU( wxID_ABOUT, MainFrame::OnAboutClick )
  EVT_MENU( wxID_EXIT, MainFrame::OnExitClick )
  EVT_MENU( ID_SNDCARD, MainFrame::OnSelectSndCard )
  EVT_TIMER( ID_TIMERID, MainFrame::OnTimer)
  EVT_CHECKBOX(ID_GENLENB , MainFrame::OnGeneratorChanged)
  EVT_CHECKBOX(ID_GENRENB , MainFrame::OnGeneratorChanged)
  EVT_CHECKBOX(ID_GENSYNC , MainFrame::OnGeneratorChanged)
  EVT_TEXT_ENTER(ID_GENPHASE , MainFrame::OnGeneratorChanged)
  EVT_COMMAND_SCROLL(ID_GENLFREQ , MainFrame::OnGenScrollLChanged)
  EVT_COMMAND_SCROLL(ID_GENRFREQ , MainFrame::OnGenScrollRChanged)
  EVT_COMMAND_SCROLL(ID_GENLAMP , MainFrame::OnGenScrollChanged)
  EVT_COMMAND_SCROLL(ID_GENRAMP , MainFrame::OnGenScrollChanged)
  EVT_CHOICE(ID_OSCLTRIG, MainFrame::OnOscChoiceChanged)
  EVT_CHOICE(ID_OSCRTRIG, MainFrame::OnOscChoiceChanged)
  EVT_TEXT_ENTER(ID_TXT_FREQ_L, MainFrame::OnTxtFreqLChanged)
  EVT_TEXT_ENTER(ID_TXT_FREQ_R, MainFrame::OnTxtFreqRChanged)
  EVT_CHOICE(ID_GENSHP_L, MainFrame::OnGeneratorChanged)
  EVT_CHOICE(ID_GENSHP_R, MainFrame::OnGeneratorChanged)
  EVT_MENU( wxID_OPEN, MainFrame::OnOpenClick )
  EVT_MENU( wxID_SAVE, MainFrame::OnSaveClick )
  EVT_MENU( wxID_SAVEAS, MainFrame::OnSaveAsClick )
  EVT_BUTTON( ID_AUTOCAL, MainFrame::OnAutoCalClick )
  EVT_CHOICE( ID_OSCXSCALE, MainFrame::OnOscXScaleChanged)
  EVT_CHOICE( ID_FFTLENGTH, MainFrame::OnOscXScaleChanged)
END_EVENT_TABLE()

short * g_OscBuffer_Left;
short * g_OscBuffer_Right;
long int g_OscBufferPosition;

short * g_SpeBuffer_Left;
short * g_SpeBuffer_Right;
long int g_SpeBufferPosition;

int g_OscBufferChanged;
int g_SpeBufferChanged;

///////////////////////////////////////////////////////////////////////
MainFrame::MainFrame(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE|wxFULL_REPAINT_ON_RESIZE)
{
    // begin wxGlade: MainFrame::MainFrame
    notebook_1 = new wxNotebook(this, -1, wxDefaultPosition, wxDefaultSize, wxNB_BOTTOM);
    notebook_1_spe = new wxPanel(notebook_1, -1);
    notebook_1_osc = new wxPanel(notebook_1, -1);
    notebook_1_gen = new wxPanel(notebook_1, -1);
    notebook_1_frm = new wxPanel(notebook_1, -1);
    sizer_4_copy_staticbox = new wxStaticBox(notebook_1_gen, -1, wxT("Right channel"));
    sizer_12_staticbox = new wxStaticBox(notebook_1_osc, -1, wxT("Left channel (Red)"));
    sizer_12_copy_staticbox = new wxStaticBox(notebook_1_osc, -1, wxT("Right channel (Green)"));
    sizer_4_staticbox = new wxStaticBox(notebook_1_gen, -1, wxT("Left channel"));
    frame_1_menubar = new wxMenuBar();
    SetMenuBar(frame_1_menubar);
    wxMenu* wxglade_tmp_menu_1 = new wxMenu();
    wxglade_tmp_menu_1->Append(wxID_OPEN, wxT("&Open config...\tAlt+O"), wxT(""), wxITEM_NORMAL);
    wxglade_tmp_menu_1->Append(wxID_SAVE, wxT("&Save config...\tAlt+S"), wxT(""), wxITEM_NORMAL);
    wxglade_tmp_menu_1->Append(wxID_SAVEAS, wxT("Save &As"), wxT(""), wxITEM_NORMAL);
    wxglade_tmp_menu_1->AppendSeparator();
    wxglade_tmp_menu_1->Append(wxID_EXIT, wxT("&Close\tAlt+F4"), wxT(""), wxITEM_NORMAL);
    frame_1_menubar->Append(wxglade_tmp_menu_1, wxT("&File"));
    wxMenu* wxglade_tmp_menu_2 = new wxMenu();
    wxglade_tmp_menu_2->Append(ID_SNDCARD, wxT("Audio &Interface Configuration..."), wxT(""), wxITEM_NORMAL);
    frame_1_menubar->Append(wxglade_tmp_menu_2, wxT("&Tools"));
    wxMenu* wxglade_tmp_menu_3 = new wxMenu();
    wxglade_tmp_menu_3->Append(wxID_ABOUT, wxT("&About..."), wxT(""), wxITEM_NORMAL);
    frame_1_menubar->Append(wxglade_tmp_menu_3, wxT("&Help"));
    frame_1_statusbar = CreateStatusBar(1, 0);

    /* generator panel */
    checkbox_l_en = new wxCheckBox(notebook_1_gen, ID_GENLENB, wxT("Enable Output"));
    label_1 = new wxStaticText(notebook_1_gen, -1, wxT("Waveform: "));
    const wxString choice_l_wav_choices[] = {
        wxT("Sine"),
        wxT("Rectangular"),
        wxT("Triangle"),
        wxT("Saw")
    };
    choice_l_wav = new wxChoice(notebook_1_gen, ID_GENSHP_L, wxDefaultPosition, wxDefaultSize, 4, choice_l_wav_choices, 0);
    label_2 = new wxStaticText(notebook_1_gen, -1, wxT("Frequency [20..20000Hz]: "));
    slide_l_fr = new wxSlider(notebook_1_gen, ID_GENLFREQ, 80, 0, 200);
    label_3 = new wxStaticText(notebook_1_gen, -1, wxT("Amplitude [0..-60dB]: "));
    slide_l_am = new wxSlider(notebook_1_gen, ID_GENLAMP, 0, -60, 0);

    checkbox_r_en = new wxCheckBox(notebook_1_gen, ID_GENRENB, wxT("Enable Output"));
    label_1_copy_1 = new wxStaticText(notebook_1_gen, -1, wxT("Waveform: "));
    const wxString choice_r_wav_choices[] = {
        wxT("Sine"),
        wxT("Rectangular"),
        wxT("Triangle"),
        wxT("Saw")
    };
    choice_r_wav = new wxChoice(notebook_1_gen, ID_GENSHP_R, wxDefaultPosition, wxDefaultSize, 4, choice_r_wav_choices, 0);
    label_2_copy_1 = new wxStaticText(notebook_1_gen, -1, wxT("Frequency [20..20000Hz]: "));
    slide_r_fr = new wxSlider(notebook_1_gen, ID_GENRFREQ, 80, 0, 200);
    label_3_copy_1 = new wxStaticText(notebook_1_gen, -1, wxT("Amplitude [0..-60dB]: "));
    slide_r_am = new wxSlider(notebook_1_gen, ID_GENRAMP, 0, -60, 0);
    button_gen_start = new wxToggleButton(notebook_1_gen, ID_GENSTART, wxT("Start"));

    checkbox_gen_sync = new wxCheckBox(notebook_1_gen, ID_GENSYNC, wxT("L and R are synchronized"));
    label_gen_sync = new wxStaticText(notebook_1_gen, -1, wxT("Phase between L and R [0..360 degrees]: "));
    text_gen_sync = new wxTextCtrl(notebook_1_gen, ID_GENPHASE, wxT("0"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

    txt_freq_l = new wxTextCtrl(notebook_1_gen, ID_TXT_FREQ_L, wxT("315.0"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    txt_freq_r = new wxTextCtrl(notebook_1_gen, ID_TXT_FREQ_R, wxT("315.0"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

    /* oscilloscope panel */
    window_1 = new CtrlOScope(notebook_1_osc, _T(""), _T(""), 1);
    label_5_copy = new wxStaticText(notebook_1_osc, -1, wxT("X Scale [samples/div]: "));
    const wxString choice_osc_l_swp_copy_choices[] = {
      wxT("20"),wxT("50"),wxT("100"),wxT("200"),wxT("500"),wxT("1000"),wxT("2000"),wxT("5000"),wxT("10000"),wxT("20000"),wxT("50000"),
    };
    choice_osc_l_swp_copy = new wxChoice(notebook_1_osc, ID_OSCXSCALE, wxDefaultPosition, wxDefaultSize, 11, choice_osc_l_swp_copy_choices, 0);
    label_6 = new wxStaticText(notebook_1_osc, -1, wxT("Res [V/div]: "));
    const wxString choice_osc_l_res_choices[] = {
      wxT("1"),wxT("2"),wxT("4"),wxT("8"),wxT("16"),wxT("32"),wxT("64"),wxT("128"),wxT("256"),wxT("512"),wxT("1024"),wxT("2048"),wxT("4096"),wxT("8192"),wxT("16384"),wxT("32768")
    };
    choice_osc_l_res = new wxChoice(notebook_1_osc, -1, wxDefaultPosition, wxDefaultSize, 16, choice_osc_l_res_choices, 0);
    label_7 = new wxStaticText(notebook_1_osc, -1, wxT("Offset [V/div]: "));
    const wxString choice_osc_l_off_choices[] = {
      wxT("100"),wxT("80"),wxT("60"),wxT("40"),wxT("20"),wxT("0"),wxT("-20"),wxT("-40"),wxT("-60"),wxT("-80"),wxT("-100")
    };
    choice_osc_l_off = new wxChoice(notebook_1_osc, -1, wxDefaultPosition, wxDefaultSize, 11, choice_osc_l_off_choices, 0);

    label_6_copy = new wxStaticText(notebook_1_osc, -1, wxT("Res [V/div]: "));
    const wxString choice_osc_l_res_copy_choices[] = {
      wxT("1"),wxT("2"),wxT("4"),wxT("8"),wxT("16"),wxT("32"),wxT("64"),wxT("128"),wxT("256"),wxT("512"),wxT("1024"),wxT("2048"),wxT("4096"),wxT("8192"),wxT("16384"),wxT("32768")
    };
    choice_osc_l_res_copy = new wxChoice(notebook_1_osc, -1, wxDefaultPosition, wxDefaultSize, 16, choice_osc_l_res_copy_choices, 0);
    label_7_copy = new wxStaticText(notebook_1_osc, -1, wxT("Offset [V/div]: "));
    const wxString choice_osc_l_off_copy_choices[] = {
      wxT("100"),wxT("80"),wxT("60"),wxT("40"),wxT("20"),wxT("0"),wxT("-20"),wxT("-40"),wxT("-60"),wxT("-80"),wxT("-100")
    };
    choice_osc_l_off_copy = new wxChoice(notebook_1_osc, -1, wxDefaultPosition, wxDefaultSize, 11, choice_osc_l_off_copy_choices, 0);

    button_osc_start = new wxToggleButton(notebook_1_osc, ID_OSCSTART, wxT("Start"));

    button_autocalibrate = new wxButton(notebook_1_osc, ID_AUTOCAL, wxT("Auto Cal"));
    /// triggering control
    label_8 = new wxStaticText(notebook_1_osc, -1, wxT("Trigger: "));
    const wxString choice_osc_trig_source_choices[] = {
        wxT("Off"),
        wxT("Left channel"),
        wxT("Right channel")
    };
    choice_osc_trig_source = new wxChoice(notebook_1_osc, ID_OSCLTRIG, wxDefaultPosition, wxDefaultSize, 3, choice_osc_trig_source_choices, 0);
    label_8_copy = new wxStaticText(notebook_1_osc, -1, wxT("Trigger edge: "));
    const wxString choice_osc_trig_edge_choices[] = {
        wxT("Rising edge"),
        wxT("Falling edge")
    };
    choice_osc_trig_edge = new wxChoice(notebook_1_osc, ID_OSCRTRIG, wxDefaultPosition, wxDefaultSize, 2, choice_osc_trig_edge_choices, 0);

    // Spectrum analyzer
    label_5 = new wxStaticText(notebook_1_spe, -1, wxT("FFT Window Type:"));
    const wxString combo_box_fft_choices[] = {
        
    };
    combo_box_fft = new wxComboBox(notebook_1_spe, -1, wxT(""), wxDefaultPosition, wxDefaultSize, 0, combo_box_fft_choices, wxCB_DROPDOWN);
    label_9 = new wxStaticText(notebook_1_spe, -1, wxT("Number of samples:"));

    const wxString choice_fftlength_choices[] = {
      wxT("128"),wxT("256"),wxT("512"),wxT("1024"),wxT("2048"),wxT("4096"),wxT("8192"),wxT("16384"),wxT("32768"),wxT("64536")
    };
    choice_fftlength = new wxChoice(notebook_1_spe, ID_FFTLENGTH, wxDefaultPosition, wxDefaultSize, 10, choice_fftlength_choices, 0);

    window_1_spe = new CtrlOScope(notebook_1_spe, _T("Hz"), _T("dB"), 1);
    button_osc_start_copy = new wxToggleButton(notebook_1_spe, ID_SPANSTART, wxT("Start"));

    //Frequency response
    label_1_frm = new wxStaticText(notebook_1_frm, -1, wxT("Number of points:"));
    text_ctrl1_frm = new wxTextCtrl(notebook_1_frm, -1, wxT("100"));
    label_2_frm = new wxStaticText(notebook_1_frm, -1, wxT("TBD:"));
    text_ctrl2_frm = new wxTextCtrl(notebook_1_frm, -1, wxT(""));
    button_frm_start = new wxToggleButton(notebook_1_frm, ID_FRMSTART, wxT("Start"));
    window_1_frm = new CtrlOScope(notebook_1_frm, _T("Hz"), _T("dB"), 1);


    set_properties();
    do_layout();
    // end wxGlade
    set_custom_props();
}


void MainFrame::set_properties()
{
    // begin wxGlade: MainFrame::set_properties
    SetTitle(wxT("AUDio MEasurement System"));
    int frame_1_statusbar_widths[] = { -1 };
    frame_1_statusbar->SetStatusWidths(1, frame_1_statusbar_widths);
    const wxString frame_1_statusbar_fields[] = {
      wxT("AUDio MEasurement System - version ") wxT(AUDMES_VERSION_STRING)
    };
    for(int i = 0; i < frame_1_statusbar->GetFieldsCount(); ++i) {
        frame_1_statusbar->SetStatusText(frame_1_statusbar_fields[i], i);
    }
    choice_l_wav->SetSelection(0);
    choice_r_wav->SetSelection(0);
    choice_osc_l_swp_copy->SetSelection(0);
    choice_osc_l_res->SetSelection(0);
    choice_osc_l_off->SetSelection(0);
    choice_osc_trig_source->SetSelection(0);
    choice_osc_l_res_copy->SetSelection(0);
    choice_osc_l_off_copy->SetSelection(0);
    choice_osc_trig_edge->SetSelection(0);
    combo_box_fft->SetSelection(-1);
    choice_fftlength->SetSelection(4);
    // end wxGlade
}


void MainFrame::do_layout()
{
    // begin wxGlade: MainFrame::do_layout
    wxBoxSizer* sizer_1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_9_copy = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_10_copy = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_17 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_9 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_10 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_11 = new wxBoxSizer(wxVERTICAL);
    wxStaticBoxSizer* sizer_12_copy = new wxStaticBoxSizer(sizer_12_copy_staticbox, wxVERTICAL);
    wxBoxSizer* sizer_16_copy = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_15_copy = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_14_copy = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBoxSizer* sizer_12 = new wxStaticBoxSizer(sizer_12_staticbox, wxVERTICAL);
    wxBoxSizer* sizer_16 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_15 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_14 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_13 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_2 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_3 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBoxSizer* sizer_4_copy = new wxStaticBoxSizer(sizer_4_copy_staticbox, wxVERTICAL);
    wxStaticBoxSizer* sizer_4 = new wxStaticBoxSizer(sizer_4_staticbox, wxVERTICAL);
    wxBoxSizer* sizer_gen_sync = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_gen_sync2 = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer* sizer_9_frm = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_10_frm = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_17_frm = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer* sizer_txtfreql = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_txtfreqr = new wxBoxSizer(wxVERTICAL);

    wxFlexGridSizer * sizer_GenL = new wxFlexGridSizer( 3, 2, 5, 5);
    wxFlexGridSizer * sizer_GenR = new wxFlexGridSizer( 3, 2, 5, 5);

    // generator
    sizer_4->Add(checkbox_l_en, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_GenL->Add(label_1, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    sizer_GenL->Add(choice_l_wav, 1, wxALL|wxEXPAND, 5);
    sizer_GenL->Add(label_2, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    sizer_txtfreql->Add(slide_l_fr, 0, wxEXPAND, 5);
    sizer_txtfreql->Add(txt_freq_l, wxALL|wxEXPAND, 5);
    sizer_GenL->Add(sizer_txtfreql, 1, wxALL|wxEXPAND, 5);
    sizer_GenL->Add(label_3, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    sizer_GenL->Add(slide_l_am, 1, wxEXPAND, 5);
    sizer_4->Add(sizer_GenL, 0, wxALL|wxEXPAND, 5);
    sizer_3->Add(sizer_4, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    sizer_4_copy->Add(checkbox_r_en, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_GenR->Add(label_1_copy_1, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    sizer_GenR->Add(choice_r_wav, 1, wxALL|wxEXPAND, 5);
    sizer_GenR->Add(label_2_copy_1, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    sizer_txtfreqr->Add(slide_r_fr, 0, wxEXPAND, 5);
    sizer_txtfreqr->Add(txt_freq_r, wxALL|wxEXPAND, 5);
    sizer_GenR->Add(sizer_txtfreqr, 1, wxALL|wxEXPAND, 5);
    sizer_GenR->Add(label_3_copy_1, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    sizer_GenR->Add(slide_r_am, 1, wxEXPAND, 5);
    sizer_4_copy->Add(sizer_GenR, 0, wxALL|wxEXPAND, 5);
    sizer_3->Add(sizer_4_copy, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    sizer_2->Add(sizer_3, 0, wxALIGN_CENTER_HORIZONTAL, 0);
    sizer_gen_sync->Add(checkbox_gen_sync, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_gen_sync2->Add(label_gen_sync, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_gen_sync2->Add(text_gen_sync, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_2->Add(sizer_gen_sync, 0, wxALIGN_CENTER_HORIZONTAL, 0);
    sizer_2->Add(sizer_gen_sync2, 0, wxALIGN_CENTER_HORIZONTAL, 0);
    sizer_2->Add(button_gen_start, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    notebook_1_gen->SetAutoLayout(true);
    notebook_1_gen->SetSizer(sizer_2);
    sizer_2->Fit(notebook_1_gen);
    sizer_2->SetSizeHints(notebook_1_gen);

    //oscilloscope
    sizer_10->Add(window_1, 1, wxEXPAND, 0);
    sizer_13->Add(label_5_copy, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_13->Add(choice_osc_l_swp_copy, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    sizer_11->Add(sizer_13, 0, wxALIGN_CENTER_HORIZONTAL, 0);

    sizer_14->Add(label_6, 0, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_14->Add(5, 5, 1, 0, 0);
    sizer_14->Add(choice_osc_l_res, 0, wxALL, 5);
    sizer_12->Add(sizer_14, 1, wxEXPAND, 0);
    sizer_15->Add(label_7, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_15->Add(5, 5, 1, 0, 0);
    sizer_15->Add(choice_osc_l_off, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL, 5);
    sizer_12->Add(sizer_15, 1, wxEXPAND, 0);
    sizer_11->Add(sizer_12, 0, wxALL|wxEXPAND, 5);

    sizer_11->Add(button_autocalibrate, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5); // autocalibrate

    sizer_14_copy->Add(label_6_copy, 0, wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_14_copy->Add(5, 5, 1, 0, 0);
    sizer_14_copy->Add(choice_osc_l_res_copy, 0, wxALL, 5);
    sizer_12_copy->Add(sizer_14_copy, 1, wxEXPAND, 0);
    sizer_15_copy->Add(label_7_copy, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_15_copy->Add(5, 5, 1, 0, 0);
    sizer_15_copy->Add(choice_osc_l_off_copy, 0, wxLEFT|wxRIGHT|wxALIGN_CENTER_VERTICAL, 5);
    sizer_12_copy->Add(sizer_15_copy, 1, wxEXPAND, 0);
    sizer_11->Add(sizer_12_copy, 0, wxALL|wxEXPAND, 5);

    sizer_16->Add(label_8, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_16->Add(5, 5, 1, 0, 0);
    sizer_16->Add(choice_osc_trig_source, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_11->Add(sizer_16, 1, wxEXPAND, 0);

    sizer_16_copy->Add(label_8_copy, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_16_copy->Add(5, 5, 1, 0, 0);
    sizer_16_copy->Add(choice_osc_trig_edge, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_11->Add(sizer_16_copy, 1, wxEXPAND, 0);

    sizer_10->Add(sizer_11, 0, 0, 0);
    sizer_9->Add(sizer_10, 1, wxEXPAND, 0);
    sizer_9->Add(button_osc_start, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    notebook_1_osc->SetAutoLayout(true);
    notebook_1_osc->SetSizer(sizer_9);
    sizer_9->Fit(notebook_1_osc);
    sizer_9->SetSizeHints(notebook_1_osc);
    // analyzer
    sizer_17->Add(label_5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_17->Add(combo_box_fft, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_17->Add(20, 20, 0, 0, 0);
    sizer_17->Add(label_9, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_17->Add(choice_fftlength, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_17->Add(20, 20, 0, 0, 0);
    sizer_10_copy->Add(sizer_17, 0, wxEXPAND, 0);
    sizer_10_copy->Add(window_1_spe, 1, wxEXPAND, 0);
    sizer_9_copy->Add(sizer_10_copy, 1, wxEXPAND, 0);
    sizer_9_copy->Add(button_osc_start_copy, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    notebook_1_spe->SetAutoLayout(true);
    notebook_1_spe->SetSizer(sizer_9_copy);
    sizer_9_copy->Fit(notebook_1_spe);
    sizer_9_copy->SetSizeHints(notebook_1_spe);
    //frequency response
    sizer_17_frm->Add(label_1_frm, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_17_frm->Add(text_ctrl1_frm, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_17_frm->Add(20, 20, 0, 0, 0);
    sizer_17_frm->Add(label_2_frm, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_17_frm->Add(text_ctrl2_frm, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer_17_frm->Add(20, 20, 0, 0, 0);
    sizer_10_frm->Add(sizer_17_frm, 0, wxEXPAND, 0);
    sizer_10_frm->Add(window_1_frm, 1, wxEXPAND, 0);
    sizer_9_frm->Add(sizer_10_frm, 1, wxEXPAND, 0);
    sizer_9_frm->Add(button_frm_start, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    notebook_1_frm->SetAutoLayout(true);
    notebook_1_frm->SetSizer(sizer_9_frm);
    sizer_9_frm->Fit(notebook_1_frm);
    sizer_9_frm->SetSizeHints(notebook_1_frm);

    //main notebook
    notebook_1->AddPage(notebook_1_gen, wxT("Generator"));
    notebook_1->AddPage(notebook_1_osc, wxT("Oscilloscope"));
    notebook_1->AddPage(notebook_1_spe, wxT("Spectrum Analyzer"));
    notebook_1->AddPage(notebook_1_frm, wxT("Frequency Response"));
    sizer_1->Add( notebook_1, 1, wxEXPAND, 0);
    SetAutoLayout(true);
    SetSizer(sizer_1);
    sizer_1->Fit(this);
    sizer_1->SetSizeHints(this);
    Layout();
    // end wxGlade
}

void MainFrame::set_custom_props()
{
  double sweep_div;

#ifdef __WXMSW__
  SetIcon(wxICON(AudMeSIcon));
#endif
  m_SamplingFreq = 44100;

  choice_osc_l_res->SetSelection( 15);
  choice_osc_l_res_copy->SetSelection( 15);
  choice_osc_l_off->SetSelection( 5);
  choice_osc_l_off_copy->SetSelection( 5);

  choice_osc_l_swp_copy->GetString(choice_osc_l_swp_copy->GetCurrentSelection()).ToDouble( &sweep_div);
  m_OscBufferLength = (long) (10*sweep_div);
  window_1->SetXRange( 0, sweep_div*10, 0);
  window_1->SetYRange( -1, 1, 0, 1);
  window_1->SetNumOfVerticals( 10);

  /* analyzer */
  window_1_spe->SetXRange( 10, m_SamplingFreq/2, 1);
  window_1_spe->SetYRange( -100, 0, 0, 1);

  /* freq response */
  window_1_frm->SetXRange( 10, 10000, 1);
  window_1_frm->SetYRange( -100, 0, 0, 1);

  g_OscBufferChanged = 0;
  g_SpeBufferChanged = 0;

  m_timer = new wxTimer( this, ID_TIMERID);
  m_timer->Start( 200);

  choice_fftlength->GetString(choice_fftlength->GetCurrentSelection()).ToDouble( &sweep_div);
  m_SpeBufferLength = (long) (sweep_div);

#ifdef XSCALEINTIME
  m_RWAudio = new RWAudio( (long int)( 1.5 * m_OscBufferLength*m_SamplingFreq/10000 + 10), m_SpeBufferLength );
#else
  m_RWAudio = new RWAudio( (long int)( 1.5 * m_OscBufferLength), m_SpeBufferLength );
#endif
  m_configfilename = wxT("");

}

void MainFrame::OnAboutClick( wxCommandEvent& event )
{
  wxString s;
  s << wxT("Tiny audio laboratory version ") wxT(AUDMES_VERSION_STRING) wxT("\nVaclav Peroutka - vaclavpe@seznam.cz\n\n");

  wxMessageBox( s, _T("About application"),wxICON_INFORMATION | wxOK ); 
}

void MainFrame::OnExitClick( wxCommandEvent& event )
{
  Close();
}

void MainFrame::OnOpenClick( wxCommandEvent& event )
{
wxMessageBox( wxT("Not yet implemented"), _T("About application"),wxICON_INFORMATION | wxOK );
}

void MainFrame::OnSaveClick( wxCommandEvent& event )
{
wxMessageBox( wxT("Not yet implemented"), _T("About application"),wxICON_INFORMATION | wxOK );
}

void MainFrame::OnSaveAsClick( wxCommandEvent& event )
{
wxMessageBox( wxT("Not yet implemented"), _T("About application"),wxICON_INFORMATION | wxOK );
}

void MainFrame::OnAutoCalClick( wxCommandEvent& event )
{
 if ( button_osc_start->GetValue()) {
   short minValueL= 32767;
   short maxValueL= -32767;
   short minValueR= 32767;
   short maxValueR= -32767;

   for (unsigned long int i = 0 ; i < m_OscBufferLength; i++) {
     if ( minValueL > g_OscBuffer_Left[i]) minValueL = g_OscBuffer_Left[i];
     if ( maxValueL < g_OscBuffer_Left[i]) maxValueL = g_OscBuffer_Left[i];
     if ( minValueR > g_OscBuffer_Right[i]) minValueR = g_OscBuffer_Right[i];
     if ( maxValueR < g_OscBuffer_Right[i]) maxValueR = g_OscBuffer_Right[i];
   }
   int diff = maxValueL - minValueL;
   float lgdiff = log(diff)/log(2) ;
   if (lgdiff > 15) lgdiff = 15;
   choice_osc_l_res->SetSelection((int) lgdiff);

   diff =  maxValueR - minValueR;
   lgdiff = log(diff)/log(2) ;
   if (lgdiff > 15) lgdiff = 15;
   choice_osc_l_res_copy->SetSelection((int) lgdiff);

   // then center the wave - peaks must be located symetrically from the centre

 } else {
   wxMessageBox( wxT("Please start recording"), _T("Could not auto calibrate"),wxICON_INFORMATION | wxOK );
 }
   
}

void MainFrame::OnTimer( wxTimerEvent & ev)
{
  double tmpval;

  // oscilloscope
    if ((button_osc_start->GetValue())&&(0 != g_OscBufferChanged)) {
      
      wxArrayDouble ardbl, ardbl2;
      unsigned long int i;
      double trigger_edge;
      double trigger_level;
      double hysteresis_level = 10;
      long scope_resolution;

      double range_div = pow(2,choice_osc_l_res->GetCurrentSelection());
      double shft_val = 20.0*(choice_osc_l_off->GetCurrentSelection()-5)/128.0;
      double range_div2 = pow(2,choice_osc_l_res_copy->GetCurrentSelection());
      double shft_val2 = 20.0*(choice_osc_l_off_copy->GetCurrentSelection()-5)/128.0;
      i = 0;

      // triggering - re-done a little bit, more or less ...
      trigger_edge = (0 == choice_osc_trig_edge->GetCurrentSelection()) ? 1.0 : -1.0;
      trigger_level = 0.0; // later it will be maybe settable in the control
      switch ( choice_osc_trig_source->GetCurrentSelection()) {
      case 1 :
	// left channel - look for the value under hysteresis point and then over 0
	choice_osc_l_res->GetString(choice_osc_l_res->GetCurrentSelection()).ToLong( &scope_resolution);
	hysteresis_level = scope_resolution/10.0; // later the hysteresis percent will be maybe settable in the control
	while (i < m_OscBufferLength) {
	  if ((trigger_level-hysteresis_level) > (trigger_edge * g_OscBuffer_Left[i])) {
	    break;
	  }
	  i++;
	}
	while (i < m_OscBufferLength) {
	  if (trigger_level < (trigger_edge * g_OscBuffer_Left[i])) {
	    break;
	  }
	  i++;
	}

	break;
      case 2 :
	// right channel
	choice_osc_l_res_copy->GetString(choice_osc_l_res_copy->GetCurrentSelection()).ToLong( &scope_resolution);
	hysteresis_level = scope_resolution/10.0; // later the hysteresis percent will be maybe settable in the control
	while (i < m_OscBufferLength) {
	  if ((trigger_level-hysteresis_level) > (trigger_edge * g_OscBuffer_Right[i])) {
	    break;
	  }
	  i++;
	}
	while (i < m_OscBufferLength) {
	  if (trigger_level < (trigger_edge * g_OscBuffer_Right[i])) {
	    break;
	  }
	  i++;
	}
	break;
      default :
	// no trigger
	break;
      }

      // Add the frequency measurement feature - FFT
      {
	int nsampl;

	m_OscBufferLength > 16384 ? nsampl = 16384 : nsampl = m_OscBufferLength;
	nsampl = (int)( pow(2, (int)(log10(nsampl)/log10(2))));

	if (nsampl > 0 ) {
	  double * realin = (double*) malloc( nsampl*sizeof( double));
	  double * realout = (double*) malloc( nsampl*sizeof( double));
	  double * imagout = (double*) malloc( nsampl*sizeof( double));

	  for( int i=0; i<nsampl;i++){
	    realin[i] = g_OscBuffer_Left[i]/2048.0;
	  }
	  if (fft_double( nsampl, 0, realin, NULL, realout, imagout)) {
	    int i;
	    double dmax = realout[0]*realout[0]+imagout[0]*imagout[0];
	    int imax = 0;
	    for( i = 1; i < nsampl/2 ; i++){
	      double dval = realout[i]*realout[i]+imagout[i]*imagout[i];
	      if ( dval > dmax) {
		dmax = dval;
		imax = i;
	      }
	    }
	    // recompute the frequency
	    double freq = 1.0*imax*m_SamplingFreq/nsampl;
	    wxString bla;
	    bla.Printf(wxT("Frequency : %.1f "),freq);
	    window_1->ShowUserText( bla, 100, 20);
	  }
	  free( realin);
	  free( realout);
	  free( imagout);
	}


      }


      // here it is necessary to recompute the length of data packet to show just micro/miliseconds and not samples
      unsigned long int finalBufferPoint = i + m_OscBufferLength;  // wrapped exactly for the OScopeCtrl X range
      if (finalBufferPoint > 1.5*m_OscBufferLength) { finalBufferPoint = (unsigned long)( 1.5*m_OscBufferLength); }

#ifdef XSCALEINTIME
      // new copy function for microseconds/div XScale
      while ( i < finalBufferPoint) {
	long int newpos = (long int) (i*m_SamplingFreq/10000.f);
	ardbl.Add( g_OscBuffer_Left[newpos]/range_div-shft_val);
	ardbl2.Add( g_OscBuffer_Right[newpos]/range_div2-shft_val2);
	i++;
      }
#else
      // old copy function for samples/div XScale
      while ( i < finalBufferPoint) {
	ardbl.Add( g_OscBuffer_Left[i]/range_div-shft_val);
	ardbl2.Add( g_OscBuffer_Right[i]/range_div2-shft_val2);
	i++;
      }
#endif

      window_1->SetTrack( ardbl);
      window_1->SetTrack2( ardbl2);

      g_OscBufferChanged = 0;

    }

    // Spectrum analyzer
    if (0 != g_SpeBufferChanged) {
      if (button_osc_start_copy->GetValue()) {
      
	double *realin, *realout, *imagout;
	int nsampl = m_SpeBufferLength;
	realin = (double*) malloc( nsampl*sizeof( double));
	realout = (double*) malloc( nsampl*sizeof( double));
	imagout = (double*) malloc( nsampl*sizeof( double));
	wxArrayDouble ardbl;
	wxArrayDouble ardbl2;

	// left channel
	for( int i=0; i<nsampl;i++){
	  realin[i] = g_SpeBuffer_Left[i]/2048.0;
	}

	if (fft_double( nsampl, 0, realin, NULL, realout, imagout)) {
	  /* everything is correct */
	  for( unsigned long int i=0; i<m_SamplingFreq/2;i++){
	    /* zobrazeni jen poloviny, tzn. nsampl/2 odpovida fvz/2 */
	    float ffcomp = 1.0*i*nsampl/m_SamplingFreq;
	    int ifcomp = (int) (ffcomp);
	    // make an averaging
	    float wt_low = ffcomp - 1.0*ifcomp;
	    float wt_hig = 1.0+ 1.0*ifcomp - ffcomp;
	    float outval_low = sqrt(realout[ifcomp]*realout[ifcomp]+imagout[ifcomp]*imagout[ifcomp]);
	    float outval_hig = sqrt(realout[ifcomp+1]*realout[ifcomp+1]+imagout[ifcomp+1]*imagout[ifcomp+1]);
	    ardbl.Add( 20.0*log10( wt_hig*outval_low + wt_low*outval_hig )-90);
	  }
	} else {
	  /* wrong computation */
	  for( int i=0; i<nsampl;i++){
	    ardbl.Add( 25*(sin(0.01*i)+sin(0.012*i)));
	  }
	}
	// right channel
	for( int i=0; i<nsampl;i++){
	  realin[i] = g_SpeBuffer_Right[i]/2048.0;
	}

	if (fft_double( nsampl, 0, realin, NULL, realout, imagout)) {
	  /* everything is correct */
	  for( unsigned long int i=0; i<m_SamplingFreq/2;i++){
	    /* zobrazeni jen poloviny, tzn. nsampl/2 odpovida fvz/2 */
	    float ffcomp = 1.0*i*nsampl/m_SamplingFreq;
	    int ifcomp = (int) (ffcomp);
	    // make an averaging
	    float wt_low = ffcomp - 1.0*ifcomp;
	    float wt_hig = 1.0+ 1.0*ifcomp - ffcomp;
	    float outval_low = sqrt(realout[ifcomp]*realout[ifcomp]+imagout[ifcomp]*imagout[ifcomp]);
	    float outval_hig = sqrt(realout[ifcomp+1]*realout[ifcomp+1]+imagout[ifcomp+1]*imagout[ifcomp+1]);
	    ardbl2.Add( 20.0*log10( wt_hig*outval_low + wt_low*outval_hig )-90);
	  }
	} else {
	  /* wrong computation */
	  for( int i=0; i<nsampl;i++){
	    ardbl2.Add( 25*(sin(0.01*i)+sin(0.012*i)));
	  }
	}



	window_1_spe->SetTrack( ardbl);
	window_1_spe->SetTrack2( ardbl2);

	free (realin);
	free (realout);
	free (imagout);
      }
      /* a tady frekvencni analyzer */
      if (button_frm_start->GetValue()) {
	wxArrayDouble ardbl;

	/* udelat linearni prolozeni bodu pro kazdy 1 Hz */
	/* prvnim krokem vezmeme pocatecni hodnoty */
	double upfreq = m_frm_freqs[0];
	double upgain = m_frm_gains[0];
	double botfreq = 0;
	double botgain = m_frm_gains[0];
	unsigned long int arrpointer = 1;
	ardbl.Clear();
	for( unsigned long int i=0; i<m_SamplingFreq/2;i++){
	  if (i > (unsigned long int) upfreq) {
	    /* dalsi hodnota z poli */
	    if ( (arrpointer+1) > m_frm_freqs.GetCount()) {
	      /* ukoncit */
	      break;
	    } else {
	      botfreq = upfreq; botgain = upgain;
	      upfreq = m_frm_freqs[arrpointer];
	      upgain = m_frm_gains[arrpointer];
	      arrpointer++;
	    }
	  }
	  tmpval = botgain + (upgain-botgain)/(upfreq-botfreq)*(1.0*i-botfreq);
	  ardbl.Add( 20.0*log10(tmpval));
	}
	window_1_frm->SetTrack( ardbl);

      }
      g_SpeBufferChanged = 0;
    }
    //wxMessageBox( _T("Idle event caught"), _T("About application"),wxICON_INFORMATION | wxOK ); 
}
  
void MainFrame::OnOscXScaleChanged( wxCommandEvent& ev )
{
  double sweep_div;
  choice_osc_l_swp_copy->GetString(choice_osc_l_swp_copy->GetCurrentSelection()).ToDouble( &sweep_div);
  m_OscBufferLength = (long) (10*sweep_div);
  window_1->SetXRange( 0, sweep_div*10, 0);

  choice_fftlength->GetString(choice_fftlength->GetCurrentSelection()).ToDouble( &sweep_div);
  m_SpeBufferLength = (long) (sweep_div);

#ifdef XSCALEINTIME
  m_RWAudio->ChangeBufLen( (unsigned long) (1.5 * m_OscBufferLength*m_SamplingFreq/10000 + 10), m_SpeBufferLength); // we need bigger buffer because of synchronization
#else
  m_RWAudio->ChangeBufLen( (unsigned long) (1.5 * m_OscBufferLength), m_SpeBufferLength); // we need bigger buffer because of synchronization
#endif

}
 
void MainFrame::OnSpanStart( wxCommandEvent& ev )
{
  //  int buf[4096];

  if (button_osc_start_copy->GetValue()) {
    button_osc_start_copy->SetLabel(_T("Stop"));
  } else {
    button_osc_start_copy->SetLabel(_T("Start"));
  }

}

void MainFrame::OnGenStart( wxCommandEvent& ev )
{

  if (button_gen_start->GetValue()) {
    button_gen_start->SetLabel(_T("Stop"));
  } else {
    button_gen_start->SetLabel(_T("Start"));
  }
  SendGenSettings();

}

void MainFrame::OnOscStart( wxCommandEvent& ev )
{
  if (button_osc_start->GetValue()) {
    button_osc_start->SetLabel(_T("Stop"));
  } else {
    button_osc_start->SetLabel(_T("Start"));
  }
}

void MainFrame::OnFrmStart( wxCommandEvent& ev )
{
  long ipoints;

  if (button_frm_start->GetValue()) {
    button_frm_start->SetLabel(_T("Stop"));

    // make steppings and measurement
    wxString tpoints = text_ctrl1_frm->GetValue();

    tpoints.ToLong( &ipoints, 10);
    if (ipoints > 100) ipoints = 100;
    if (ipoints < 1) ipoints = 1;

    frm_running = 1;

      m_frm_freqs.Clear();
      m_frm_gains.Clear();
    for(int i=0; i<= (int)ipoints; i++) {
      // from 20Hz to 20kHz
      float freq = 20.0*pow(10.0, 3.0*i/ipoints)+50.0;
      m_RWAudio->PlaySetGenerator( freq, freq, 0, 0, pow(10,slide_l_am->GetValue()/20.0), pow(10,slide_r_am->GetValue()/20.0));
#ifdef __WXMSW__
      Sleep( 400);
      wxYield();
      Sleep( 400);
#else
      usleep(400000);
      wxYield();
      usleep(400000);
#endif
      wxYield();
      // find maximum value in the grabbed wave and store it as a result
      m_frm_freqs.Add( freq);
      double i_min = g_SpeBuffer_Left[0];
      double i_max = g_SpeBuffer_Left[0];
      for( unsigned long int ii = 1; ii < m_SpeBufferLength; ii++){
	/* zatim pouze prvni kanal */
	if (g_SpeBuffer_Left[ii] > i_max ) i_max = g_SpeBuffer_Left[ii];
	if (g_SpeBuffer_Left[ii] < i_min ) i_min = g_SpeBuffer_Left[ii];
      }
      m_frm_gains.Add( (i_max-i_min)/65536.0);

      if ( 0 == frm_running) break;
    }

    button_frm_start->SetLabel(_T("Start"));
    button_frm_start->SetValue( false);

  } else {
    button_frm_start->SetLabel(_T("Start"));
    frm_running = 0;
  }
}


void MainFrame::OnGeneratorChanged( wxCommandEvent& ev )
{
  if( checkbox_gen_sync->IsChecked()){
    slide_r_fr->Enable( false);
    label_2_copy_1->Enable( false);
  } else {
    slide_r_fr->Enable( true);
    label_2_copy_1->Enable( true);
  }

  if (button_gen_start->GetValue()) {
    SendGenSettings();
  }
}

void MainFrame::OnOscChoiceChanged( wxCommandEvent& ev )
{
}

void MainFrame::OnGenScrollLChanged( wxScrollEvent& ev )
{
  wxString bla;

  bla.Printf(wxT("%.1f"), floor(20.0*pow(10.0, 3.0*slide_l_fr->GetValue()/200.0)));
  txt_freq_l->SetValue( bla);
  if (button_gen_start->GetValue()) {
    SendGenSettings();
  }
}

void MainFrame::OnGenScrollRChanged( wxScrollEvent& ev )
{
  wxString bla;

  bla.Printf(wxT("%.1f"), floor(20.0*pow(10.0, 3.0*slide_r_fr->GetValue()/200.0)));
  txt_freq_r->SetValue( bla);
  if (button_gen_start->GetValue()) {
    SendGenSettings();
  }
}

void MainFrame::OnGenScrollChanged( wxScrollEvent& ev )
{
  wxString bla;

  bla.Printf(wxT("Amplitude: %d dB"), slide_l_am->GetValue());
  label_3->SetLabel( bla);

  bla.Printf(wxT("Amplitude: %d dB"), slide_r_am->GetValue());
  label_3_copy_1->SetLabel( bla);


  if (button_gen_start->GetValue()) {
    SendGenSettings();
  }
}

void MainFrame::SendGenSettings( )
{
  float freq_l, freq_r;
  double phas2;
  double doubleToFreq;

  if((checkbox_l_en->IsChecked())&&(button_gen_start->GetValue())) {
    txt_freq_l->GetValue().ToDouble(& doubleToFreq);
    freq_l = (float)doubleToFreq;
  } else {
    freq_l = 0.0;
  }
  if((checkbox_r_en->IsChecked())&&(button_gen_start->GetValue())) {
    txt_freq_r->GetValue().ToDouble(& doubleToFreq);
    freq_r = (float)doubleToFreq;
  } else {
    freq_r = 0.0;
  }

  text_gen_sync->GetValue().ToDouble( &phas2);

  if( checkbox_gen_sync->IsChecked()){
    freq_r = freq_l;
  } else {
    phas2 = 0.0;
  }

  int shapeleft = choice_l_wav->GetCurrentSelection() ;
  int shaperight = choice_r_wav->GetCurrentSelection() ;
  m_RWAudio->PlaySetGenerator( freq_l, freq_r, shapeleft, shaperight, 1.0*pow(10,slide_l_am->GetValue()/20.0), 1.0*pow(10,slide_r_am->GetValue()/20.0));
  if( checkbox_gen_sync->IsChecked()){
    m_RWAudio->PlaySetPhaseDiff( phas2*3.14159/180.0); // should be in degrees now
  }
}


void MainFrame::OnSelectSndCard( wxCommandEvent& ev )
{
  wxArrayString arrplstr, arrrecstr, freqsstr;
  wxString bla;
  int recdev, pldev;
  unsigned int i;
  RWAudioDevList play;
  RWAudioDevList record;
  std::vector<unsigned long int> freqs;

  m_RWAudio->GetRWAudioDevices( & play, & record, & freqs);


  bla = _T("Devices: ");
  for (i = 0; i < play.card_name.size(); i++) {
      wxString newstr(play.card_name[i].c_str(), wxConvUTF8);
      arrplstr.Add(newstr);
  }

  for (i = 0; i < record.card_name.size(); i++) {
      wxString newstr(record.card_name[i].c_str(), wxConvUTF8);
      arrrecstr.Add(newstr);
  }

  for (i = 0; i < freqs.size(); i++) {
    if ( 0 !=  freqs[i]) {
      freqsstr.Add(wxString::Format(wxT("%ld "),freqs[i]));
    }
  }

  AudioInterfaceDialog dlg( this);

  dlg.SetDevices( arrrecstr, arrplstr, freqsstr);
  if (wxID_OK == dlg.ShowModal()) {
    // poslat nastaveni do RW_AUDIO
    dlg.GetSelectedDevs( &recdev, &pldev);
    m_RWAudio->SetSndDevices( record.card_position[recdev], play.card_position[pldev]);
  }
}

void MainFrame::OnTxtFreqLChanged( wxCommandEvent& ev )
{
  if (button_gen_start->GetValue()) {
    SendGenSettings();
  }
}

void MainFrame::OnTxtFreqRChanged( wxCommandEvent& ev )
{
  if (button_gen_start->GetValue()) {
    SendGenSettings();
  }
}


class AudMeSApp: public wxApp {
public:
    bool OnInit();
};

IMPLEMENT_APP(AudMeSApp)

bool AudMeSApp::OnInit()
{
    wxInitAllImageHandlers();
    MainFrame* frame_1 = new MainFrame(NULL, -1, wxT(""));
    SetTopWindow(frame_1);
    frame_1->Show();
    return true;
}






