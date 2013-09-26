/*****************************************************************************

	SFTextIDs.h
	
	Copyright 2001, Siegfried Soft.   All Rights Reserved.

*****************************************************************************/
#ifndef _SFTEXTIDS
#define _SFTEXTIDS

#define SF_DEFAULT_LANGUAGE     "English"
#define SF_TEXT_APP_ID          "bic locale"

#define MSG_SFLANGUAGE          'sflg'
//----------------------------------------------------------------------------
// Defintitions for all used text data
//----------------------------------------------------------------------------

enum gSFTextID
{
	msg_editor,
	msg_delete,
	msg_about,
	msg_ok,
	msg_save,
	msg_cancel,
	msg_error_number,
	msg_gadget,
	msg_focus,
	msg_border,

	msg_label,
	msg_default,
	msg_enabled,
	msg_selectall,
	msg_selectnone,
	msg_inverseselection,
	msg_left,
	msg_top,
	msg_width,
	msg_height,
	msg_name,
	msg_title,
	msg_editeur_gadget,

	msg_alignment,
	msg_alignment_x,
	msg_alignment_y,
	msg_editeur_window,
	msg_type,
	msg_workspace,
	msg_message,	
	msg_constructor,
	msg_proprieties,
	msg_events,
	msg_value,
	msg_layout,
	msg_cellsize,
	msg_buffereddraw,

	msg_setvalue,
	msg_list,
	msg_selection,
	msg_divider,
	msg_minrange,
	msg_maxrange,
	msg_minstep,
	msg_maxstep,
	msg_hashmarks,
	msg_style,
	msg_min,
	msg_max,
	msg_thickness,
	msg_hashcount,
	msg_keyinc,
	msg_minlabel,
	msg_maxlabel,

	msg_trail,
	msg_maxvalue,
	msg_barheight,
	msg_barcolor,
	msg_align_label,
	msg_align_text,
	msg_tabwidth,
	msg_tabheight,
	msg_selected,
	msg_color,
	msg_selectable,
	msg_editable,
	msg_wordwrap,
	msg_setstylable,
	msg_autoindent,
	msg_maxbytes,
	msg_number,
	msg_look,
	msg_feel,
	msg_minhoriz,
	msg_maxhoriz,
	msg_minvert,
	msg_maxvert,

	msg_cut,
	msg_copy,
	msg_paste,
	msg_grid,
	msg_espacex,
	msg_espacey,
	msg_usegrid,
	msg_confirmquit,
	msg_yesno,
	msg_confirmsave,
	msg_noyes,
	msg_addform,
	msg_cascade,
	msg_vertical,
	msg_horizontal,

	msg_file,
	msg_new,
	msg_open,
	msg_openrecent,
	msg_saveas,
	msg_gencode,
	msg_gencode_basic,
	msg_gencode_c,
	msg_gencode_ccplus,
	msg_information,
	msg_quit,
	msg_edition,
	msg_undelete,
	msg_right,
	msg_up,
	msg_down,
	msg_center,
	msg_all,
	msg_uniform,
	msg_spacement,
	msg_tools,

	msg_list_projet,
	msg_list_gadget,
	msg_list_placement,
	msg_list_search,
	msg_list_proprietes,
	msg_list_grid,
	msg_window,
	msg_help,
	msg_html,
	msg_tips,
	msg_create_menu,
	msg_raccourci,
	msg_addmenu,
	msg_additem,
	msg_actived,
	msg_checked,
	msg_radiomode,
	msg_placement,

	msg_selection2,
	msg_selection_none,
	msg_prefs_language,
	msg_prefs_saveauto,
	msg_prefs_openlastprojet,
	msg_prefs_confirmquit,
	msg_prefs_delete,
	msg_prefs_kill_del,
	msg_preferences,
	msg_prefs,

	msg_newprojet,
	msg_nameprj,
	msg_directory,
	msg_typeprj,
	msg_untitled,
	msg_choosedir,
	msg_quitprogsave,
	msg_savecancel,
	msg_project,
	msg_loading,

	msg_saving,
	msg_savingas,
	msg_search,
	msg_knowis,
	msg_tips_no,
	msg_next,
	msg_pred,
	msg_showstartup,
	msg_killwindow,
	msg_onemenu,
	msg_listegadget,
	msg_derived,
	msg_empty,
	msg_changefont,
	msg_showall,
	msg_hideall,
	msg_viewcolor,
	msg_highcolor,
	msg_lowcolor,
	msg_espacement,
	msg_spacex,
	msg_spacey,
	msg_font,
	msg_bcckeyfile_invalid,
	msg_bcckeyfile_notfound,
	msg_copyright,
	msg_errorwriting,
	msg_executable,
	msg_addon,
	msg_library,
	msg_kernel,
	msg_void_default,
	msg_default_rtn,
	msg_write_name,
	msg_none,
	msg_some,
	msg_more,
	msg_full,
	msg_english,
	msg_french,
	msg_application_name,
	msg_application_type,
	msg_comp_flag,
	msg_link_flag,
	msg_optimisation,
	msg_warning,
	msg_debug,
	msg_code,
	msg_makefile,
	msg_autocreate,
	msg_creategadget,
	msg_white,
	msg_black,
	msg_red,
	msg_blue,
	msg_grey,
	msg_green,
	msg_turquoise,
	msg_cyan,

	msg_locale_french,//***FRENCH

	fmsg_editor,
	fmsg_delete,
	fmsg_about,
	fmsg_ok,
	fmsg_save,
	fmsg_cancel,
	fmsg_error_number,
	fmsg_gadget,
	fmsg_focus,
	fmsg_border,

	fmsg_label,
	fmsg_default,
	fmsg_enabled,
	fmsg_selectall,
	fmsg_selectnone,
	fmsg_inverseselection,
	fmsg_left,
	fmsg_top,
	fmsg_width,
	fmsg_height,
	fmsg_name,
	fmsg_title,
	fmsg_editeur_gadget,

	fmsg_alignment,
	fmsg_alignment_x,
	fmsg_alignment_y,
	fmsg_editeur_window,
	fmsg_type,
	fmsg_workspace,
	fmsg_message,	
	fmsg_constructor,
	fmsg_proprieties,
	fmsg_events,
	fmsg_value,
	fmsg_layout,
	fmsg_cellsize,
	fmsg_buffereddraw,

	fmsg_setvalue,
	fmsg_list,
	fmsg_selection,
	fmsg_divider,
	fmsg_minrange,
	fmsg_maxrange,
	fmsg_minstep,
	fmsg_maxstep,
	fmsg_hashmarks,
	fmsg_style,
	fmsg_min,
	fmsg_max,
	fmsg_thickness,
	fmsg_hashcount,
	fmsg_keyinc,
	fmsg_minlabel,
	fmsg_maxlabel,

	fmsg_trail,
	fmsg_maxvalue,
	fmsg_barheight,
	fmsg_barcolor,
	fmsg_align_label,
	fmsg_align_text,
	fmsg_tabwidth,
	fmsg_tabheight,
	fmsg_selected,
	fmsg_color,
	fmsg_selectable,
	fmsg_editable,
	fmsg_wordwrap,
	fmsg_setstylable,
	fmsg_autoindent,
	fmsg_maxbytes,
	fmsg_number,
	fmsg_look,
	fmsg_feel,
	fmsg_minhoriz,
	fmsg_maxhoriz,
	fmsg_minvert,
	fmsg_maxvert,

	fmsg_cut,
	fmsg_copy,
	fmsg_paste,
	fmsg_grid,
	fmsg_espacex,
	fmsg_espacey,
	fmsg_usegrid,
	fmsg_confirmquit,
	fmsg_yesno,
	fmsg_confirmsave,
	fmsg_noyes,
	fmsg_addform,
	fmsg_cascade,
	fmsg_vertical,
	fmsg_horizontal,

	fmsg_file,
	fmsg_new,
	fmsg_open,
	fmsg_openrecent,
	fmsg_saveas,
	fmsg_gencode,
	fmsg_gencode_basic,
	fmsg_gencode_c,
	fmsg_gencode_ccplus,
	fmsg_information,
	fmsg_quit,
	fmsg_edition,
	fmsg_undelete,
	fmsg_right,
	fmsg_up,
	fmsg_down,
	fmsg_center,
	fmsg_all,
	fmsg_uniform,
	fmsg_spacement,
	fmsg_tools,

	fmsg_list_projet,
	fmsg_list_gadget,
	fmsg_list_placement,
	fmsg_list_search,
	fmsg_list_proprietes,
	fmsg_list_grid,
	fmsg_window,
	fmsg_help,
	fmsg_html,
	fmsg_tips,
	fmsg_create_menu,
	fmsg_raccourci,
	fmsg_addmenu,
	fmsg_additem,
	fmsg_actived,
	fmsg_checked,
	fmsg_radiomode,
	fmsg_placement,

	fmsg_selection2,
	fmsg_selection_none,
	fmsg_prefs_language,
	fmsg_prefs_saveauto,
	fmsg_prefs_openlastprojet,
	fmsg_prefs_confirmquit,
	fmsg_prefs_delete,
	fmsg_prefs_kill_del,
	fmsg_preferences,
	fmsg_prefs,

	fmsg_newprojet,
	fmsg_nameprj,
	fmsg_directory,
	fmsg_typeprj,
	fmsg_untitled,
	fmsg_choosedir,
	fmsg_quitprogsave,
	fmsg_savecancel,
	fmsg_project,
	fmsg_loading,

	fmsg_saving,
	fmsg_savingas,
	fmsg_search,
	fmsg_knowis,
	fmsg_tips_no,
	fmsg_next,
	fmsg_pred,
	fmsg_showstartup,
	fmsg_killwindow,
	fmsg_onemenu,
	fmsg_listegadget,
	fmsg_derived,
	fmsg_empty,
	fmsg_changefont,
	fmsg_showall,
	fmsg_hideall,
	fmsg_viewcolor,
	fmsg_highcolor,
	fmsg_lowcolor,
	fmsg_espacement,
	fmsg_spacex,
	fmsg_spacey,
	fmsg_font,
	fmsg_bcckeyfile_invalid,
	fmsg_bcckeyfile_notfound,
	fmsg_copyright,
	fmsg_errorwriting,
	fmsg_executable,
	fmsg_addon,
	fmsg_library,
	fmsg_kernel,
	fmsg_void_default,
	fmsg_default_rtn,
	fmsg_write_name,
	fmsg_none,
	fmsg_some,
	fmsg_more,
	fmsg_full,
	fmsg_english,
	fmsg_french,
	fmsg_application_name,
	fmsg_application_type,
	fmsg_comp_flag,
	fmsg_link_flag,
	fmsg_optimisation,
	fmsg_warning,
	fmsg_debug,
	fmsg_code,
	fmsg_makefile,
	fmsg_autocreate,
	fmsg_creategadget,
	fmsg_white,
	fmsg_black,
	fmsg_red,
	fmsg_blue,
	fmsg_grey,
	fmsg_green,
	fmsg_turquoise,
	fmsg_cyan,

SF_LAST_ID							// MUST be always the last ID!!!
};

#endif