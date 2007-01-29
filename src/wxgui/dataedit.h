// This file is part of fityk program. Copyright (C) Marcin Wojdyr
// $Id$

#ifndef FITYK__WX_DATAEDIT__H__
#define FITYK__WX_DATAEDIT__H__

#include <vector>
#include <wx/grid.h>

class Data;

struct DataTransExample
{
    std::string name;
    std::string category;
    std::string description;
    std::string code;
    bool in_menu;

    DataTransExample(const std::string& name_, const std::string& category_, 
                     const std::string& description_, const std::string& code_,
                     bool in_menu_=false)
        : name(name_), category(category_), description(description_),
          code(code_), in_menu(in_menu_) {}
   DataTransExample(std::string line);
   std::string as_fileline() const;
};


class DataEditorDlg : public wxDialog
{
    friend class DataTable;
    typedef std::vector<std::pair<int,Data*> > ndnd_type;
public:
    DataEditorDlg (wxWindow* parent, wxWindowID id, ndnd_type const& dd);
    void OnRevert (wxCommandEvent& event);
    void OnSaveAs (wxCommandEvent& event);
    void OnAdd (wxCommandEvent& event);
    void OnRemove (wxCommandEvent& event);
    void OnUp (wxCommandEvent& event);
    void OnDown (wxCommandEvent& event);
    void OnSave (wxCommandEvent& event);
    void OnReset (wxCommandEvent& event);
    void OnApply (wxCommandEvent& event);
    void OnReZoom (wxCommandEvent& event);
    void OnHelp (wxCommandEvent& event);
    void OnClose (wxCommandEvent& event);
    void OnCodeText (wxCommandEvent&) { CodeText(); }
    void CodeText();
    void OnESelected (wxListEvent&) { ESelected(); }
    void ESelected();
    void OnEActivated (wxListEvent& event);
    void update_data(ndnd_type const& dd);
    static std::vector<DataTransExample> const& get_examples() 
                                                    { return examples; }
    static void read_examples(bool reset=false);
    static void execute_tranform(std::string code);
protected:
    static std::vector<DataTransExample> examples;
    wxGrid *grid;
    ndnd_type ndnd;
    wxStaticText *filename_label, *title_label, *description;
    wxListCtrl *example_list; 
    wxTextCtrl *code;
    wxButton *revert_btn, *save_as_btn, *apply_btn, *rezoom_btn, *help_btn,
             *add_btn, *remove_btn, *up_btn, *down_btn, 
             *save_btn, *reset_btn;

    void initialize_examples(bool reset=false);
    int get_selected_item();
    void insert_example_list_item(int n);
    void select_example(int item);
    void refresh_grid();
    DECLARE_EVENT_TABLE()
};


class ExampleEditorDlg : public wxDialog
{
public:
    ExampleEditorDlg(wxWindow* parent, wxWindowID id, DataTransExample& ex_,
                     const std::vector<DataTransExample>& examples_, int pos_);
    void OnOK(wxCommandEvent &event);
protected:
    DataTransExample& ex;
    const std::vector<DataTransExample>& examples;
    int pos;
    wxTextCtrl *name_tc, *description_tc, *code_tc;
    wxComboBox *category_c;
    wxCheckBox *inmenu_cb;

    DECLARE_EVENT_TABLE()
};

#endif
