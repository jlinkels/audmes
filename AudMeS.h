// -*- C++ -*- generated by wxGlade 0.3.1 on Wed Sep 29 16:09:00 2004
/*
 * Copyright (C) 2008 Vaclav Peroutka <vaclavpe@seznam.cz>
 *
 * Licensed under the GNU General Public License Version 2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <wx/image.h>
#include <wx/wx.h>
// begin wxGlade: ::dependencies
#include <wx/notebook.h>
// end wxGlade
#include <wx/tglbtn.h>

#include "CtrlOScope.h"
#include "RWAudio_IO.h"

#ifndef AUDMES_H
#define AUDMES_H

#define AUDMES_VERSION_STRING "2023-04-09"

class MainFrame : public wxFrame {
  DECLARE_CLASS(MainFrame)
  DECLARE_EVENT_TABLE()

 public:
  // begin wxGlade: MainFrame::ids
  // end wxGlade

  MainFrame(wxWindow* parent, int id, const wxString& title, const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxDEFAULT_FRAME_STYLE | wxFULL_REPAINT_ON_RESIZE);

 private:
  // begin wxGlade: MainFrame::methods
  void set_properties();
  void set_custom_props();
  void do_layout();
  // end wxGlade

  void OnSpanStart(wxCommandEvent& event);
  void OnGenStart(wxCommandEvent& event);
  void OnOscStart(wxCommandEvent& event);
  void OnFrmStart(wxCommandEvent& event);
  void OnAboutClick(wxCommandEvent& event);
  void OnExitClick(wxCommandEvent& event);
  void OnClose(wxCloseEvent& event);
  void OnSoundInput(wxEvent& event);
  void OnTimer(wxTimerEvent& event);
  void OnGeneratorChanged(wxCommandEvent& event);
  void OnGenScrollChanged(wxScrollEvent& event);
  void OnGenScrollLChanged(wxScrollEvent& event);
  void OnGenScrollRChanged(wxScrollEvent& event);
  void OnOscChoiceChanged(wxCommandEvent& event);
  void SendGenSettings(void);
  void OnSelectSndCard(wxCommandEvent& event);
  void OnTxtFreqLChanged(wxCommandEvent& event);
  void OnTxtFreqRChanged(wxCommandEvent& event);
  void OnOpenClick(wxCommandEvent& event);
  void OnSaveClick(wxCommandEvent& event);
  void OnSaveAsClick(wxCommandEvent& event);
  void OnLoadFRM(wxCommandEvent& event);
  void OnSaveFRM(wxCommandEvent& event);
  void OnAutoCalClick(wxCommandEvent& event);
  void OnOscXScaleChanged(wxCommandEvent& event);
  void DrawFreqResponse(void);
  void CalcFreqResponse(void);
  void DrawOscilloscope(void);
  void DrawSpectrum(void);

  void sleep(int ms);

 protected:
  // begin wxGlade: MainFrame::attributes
  wxStaticBox* sizer_12_copy_staticbox;
  wxStaticBox* sizer_12_staticbox;
  wxStaticBox* sizer_4_copy_staticbox;
  wxStaticBox* sizer_4_staticbox;
  wxMenuBar* frame_1_menubar;
  wxStatusBar* frame_1_statusbar;
  wxCheckBox* checkbox_l_en;
  wxStaticText* label_1;
  wxChoice* choice_l_wav;
  wxStaticText* label_2;
  wxSlider* slide_l_fr;
  wxStaticText* label_3;
  wxSlider* slide_l_am;
  wxCheckBox* checkbox_r_en;
  wxStaticText* label_1_copy_1;
  wxChoice* choice_r_wav;
  wxStaticText* label_2_copy_1;
  wxSlider* slide_r_fr;
  wxStaticText* label_3_copy_1;
  wxSlider* slide_r_am;
  wxToggleButton* button_gen_start;

  wxPanel* notebook_1_gen;
  CtrlOScope* window_1;
  wxStaticText* label_5_copy;
  wxChoice* choice_osc_l_swp_copy;
  wxStaticText* label_6;
  wxChoice* choice_osc_l_res;
  wxStaticText* label_7;
  wxChoice* choice_osc_l_off;
  wxStaticText* label_8;
  wxChoice* choice_osc_trig_source;
  wxStaticText* label_6_copy;
  wxChoice* choice_osc_l_res_copy;
  wxStaticText* label_7_copy;
  wxChoice* choice_osc_l_off_copy;
  wxStaticText* label_8_copy;
  wxChoice* choice_osc_trig_edge;
  wxToggleButton* button_osc_start;
  wxPanel* notebook_1_osc;
  wxStaticText* label_5;
  wxChoice* choice_fft;
  wxStaticText* label_9;
  wxChoice* choice_fftlength;
  wxStaticText* label_rx;
  wxChoice* choice_fftrx;
  CtrlOScope* window_1_spe;
  wxToggleButton* button_spe_start;
  wxPanel* notebook_1_spe;
  wxNotebook* notebook_1;
  wxTextCtrl* txt_freq_l;
  wxTextCtrl* txt_freq_r;

  wxCheckBox* checkbox_gen_sync;
  wxStaticText* label_gen_sync;
  wxTextCtrl* text_gen_sync;
  // end wxGlade
  wxPanel* notebook_1_frm;
  wxStaticText* label_1_frm;
  wxStaticText* label_2_frm;
  wxTextCtrl* text_ctrl1_frm;
  wxTextCtrl* text_ctrl2_frm;
  wxToggleButton* button_frm_start;
  CtrlOScope* window_1_frm;

  RWAudio* m_RWAudio;
  wxTimer* m_timer;

  bool frm_running;
  int frm_ipoints;
  int frm_istep;
  int frm_measure;

  wxArrayDouble m_frm_freqs;
  wxArrayDouble m_frm_lgains;
  wxArrayDouble m_frm_rgains;

  wxButton* button_autocalibrate;
  wxString m_configfilename;
  std::string m_rtinfo;

  unsigned long int m_OscBufferLength;
  unsigned long int m_SpeBufferLength;

  unsigned long int m_SamplingFreq;
};

#endif  // AUDMES_H
