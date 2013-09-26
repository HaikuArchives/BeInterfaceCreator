#include "proto.h"
#include "SFTexts.h"

//----------------------------------------------------------------------------
static const char	*mText[SF_LAST_ID] = 
{
	"Editor",
	"Delete",
	"Bic",
	"Ok",
	"Save",
	"Cancel",
	"Error number %d !"	,
	"Gadget",
	"Focus",
	"Border",

	"Label"	,
	"Default",
	"Enabled",
	"Select All",
	"Select None",
	"Inverse Selection",
	"Left",
	"Top",
	"Width",
	"Height",

	"Name",
	"Title",
	"Editor - Gadget",
	"Alignment",
	"Alignment X",
	"Alignment Y",
	"Editor - Window",
	"Type",
	"Workspace",
	"Message",

	"Constructor",
	"Proprieties",
	"Events",
	"Value",		
	"Layout",
	"CellSize",
	"BufferedDrawing",
	"SetValue",
	"List",
	"Selection",

	"Divider",
	"Min Range",
	"Max Range",
	"Min Steps",
	"Max Steps",
	"HashMarks",
	"Style",
	"Min",
	"Max",
	"BarThickness",

	"HashMarkCount",
	"KeyIncrementValue",
	"MinLabel",
	"MasLabel",
	"TrailText",
	"MaxValue",
	"BarHeight",
	"BarColor",
	"Alignment Label",
	"Alignment Text",

	"TabWidth",
	"TabHeight",
	"Selected",		
	"Change Color",
	"Selectable",
	"Editable",
	"WordWrap",
	"SetStylable",
	"AutoIndent",
	"MaxBytes",

	"Number",
	"Look",
	"Feel",
	"Min Horizontal",
	"Max Horizontal",
	"Min Vertical",
	"Max Vertical",
	"Cut",
	"Copy",
	"Paste",

	"Grid",
	"Espacement X",
	"Espacement Y",
	"Use Grid",
	"confirm Quit the program ?",
	"Yes|No",
	"Save projet before quit ?",
	"No|Yes",
	"Add Form",
	"Cascade",

	"Arrange Vertical",
	"Arrange Horizontal",
	"File",
	"New",
	"Open",
	"Open Recent",
	"Save As",
	"Generate Code",
	"Language Basic",
	"Language C",

	"Language C++",
	"Information",
	"Quit",
	"Edition",
	"Undelete",
	"Right",
	"Up",
	"Down",
	"Center",
	"All",

	"Uniform",
	"Spacement",
	"Tools",
	"Window Projet",
	"Window Gadget",
	"Window Placement",
	"Window Search",
	"Window Proprieties",
	"Window Grid",
	"Window",

	"Help",
	"Html help",
	"Tips",
	"Create Menu",
	"Shortcut",
	"Add Menu",
	"Add Item",
	"Enabled",
	"Checked",
	"Radio mode",

	"Placement",
	"Select: %d gadget%s",
	"None Selection",
	"Language",
	"Save automatic",
	"Open last projet",
	"Confirm quit program",
	"Confirm delete action",
	"Disable SUPPR key",
	"Preferences",

	"Prefs",
	"New project",
	"Name project",
	"Directory",
	"Type project",
	"Untitled",
	"Choose Directory",
	"Save projet before Quit program ?",
	"Save|No|Cancel",
	"Project",
	"Loading",

	"Saving",
	"Saving As",
	"Search",
	"You Know This....",
	"Tips number %d",
	"Next",
	"Precedent",
	"Show at startup program",
	"Confirm delete Window ?",
	"Only one menu in Window !",

	"List Gadget",
	"Derived Class",
	"Empty",
	"Change Font",
	"Show All",
	"Hide All",
	"ViewColor",
	"HighColor",
	"LowColor",
	"Espacement",

	"Espacement X",
	"Espacement Y",
	"Fonte",
	"Invalid BccKeyFile Information!",
	"Can't Find BccKeyFile!",
	"BeInterfaceCreator (Release Candidate 2)\nBic (c) 2001 Devulder Jpaul mail:rgb@free.fr\nIcone made by Thierry Caland mail:thierry.caland@free.fr\n",
	"Error writing prefs file!",
	"Executable",
	"Addon/Shared Library",
	"Static Library",

	"Kernel Driver",
	"(Void) default",
	"Default routine",
	"Write name",
	"None",
	"Some",
	"More",
	"Full",
	"English",
	"French",

	"Application Name",
	"Application Type",
	"Compiler Flags",
	"Linker Flags",
	"Optimisation",
	"Warning",
	"Debug",
	"Code",
	"Makefile",
	"Auto create",

	"Create gadget", 
	"White",
	"Black",
	"Red",
	"Blue",
	"Grey",
	"Green",
	"Turquoise",
	"Cyan",

//************************* FRENCH ******************************************

	"Editeur",
	"Détruire",
	"Bic",
	"Ok",
	"Enregistrer",
	"Annuler",
	"Erreur numero %d !",
	"Objet",
	"Activé",
	"Bordure",

	"Label"	,
	"par Defaut",
	"Activé",
	"Tous sélectionnés",
	"Aucune sélection",
	"Inverser la selection",
	"Droite",
	"Haut",
	"Hauteur",
	"Largeur",

	"Nom",
	"Titre",
	"Editeur - Objet",
	"Alignement",
	"Alignement X",
	"Alignement Y",
	"Editeur - Fenetre",
	"Type",
	"Ecran de travail",
	"Message",

	"Constructeur",
	"Proprietés",
	"Evenements",
	"Valeur",		
	"Layout",
	"CellSize",
	"Double buffet",
	"Change valeur",
	"Listde",
	"Selection",

	"Diviseur",
	"Min Range",
	"Max Range",
	"Min Steps",
	"Max Steps",
	"HashMarks",
	"Style",
	"Min",
	"Max",
	"BarThickness",

	"HashMarkCount",
	"KeyIncrementValue",
	"MinLabel",
	"MasLabel",
	"TrailText",
	"MaxValue",
	"BarHeight",
	"BarColor",
	"Alignement Label",
	"Alignement Texte",

	"TabWidth",
	"TabHeight",
	"Selected",		
	"Changer Couleur",
	"Selectionnable",
	"Editable",
	"WordWrap",
	"SetStylable",
	"AutoIndent",
	"MaxBytes",

	"Nombre",
	"Look",
	"Feel",
	"Min Horizontal",
	"Max Horizontal",
	"Min Vertical",
	"Max Vertical",
	"Couper",
	"Copier",
	"Coller",

	"Grille",
	"Espacement X",
	"Espacement Y",
	"Utilisation grille",
	"Confirmation quitter le programme ?",
	"Oui|Non",
	"Sauver projet avant de quitter ?",
	"Non|Oui",
	"Ajouter Fenetre",
	"Cascade",

	"Arrangement Vertical",
	"Arrangement Horizontal",
	"Fichier",
	"Nouveau",
	"Ouvrir",
	"Ouvrir Récent",
	"Sauver sous",
	"Generation code",
	"Langage Basic",
	"Langage C",

	"Langage C++",
	"Information",
	"Quitter",
	"Edition",
	"Undelete",
	"Gauche",
	"Haut",
	"Bas",
	"Centre",
	"Tous",

	"Uniformisation",
	"Espacement",
	"Outils",
	"Fenetre Projet",
	"Fenetre Objet",
	"Fenetre Placement",
	"Fenetre Recherche",
	"Fenetre Proprietes",
	"Fenetre Grille",
	"Fenetre",

	"Aide",
	"Html help",
	"Tips",
	"Creation Menu",
	"Raccourci",
	"Add Menu",
	"Add Item",
	"Enabled",
	"Checked",
	"Radio mode",

	"Placement",
	"Selection: %d Objet%s",
	"Pas de selection",
	"Langage",
	"Sauvegarde automatique",
	"Ouvrir dernier projet",
	"Confirmation quitter le programe",
	"Confirmation action de destruction",
	"Desactivé la touche SUPPR",
	"Preferences",

	"Preferences",
	"Nouveau projet",
	"Nom projet",
	"Répertoire",
	"Type projet",
	"SansNom",
	"Choisir répertoire",
	"Sauver projet avant de quitter le programme ?",
	"Sauver|Non|Annuler",
	"Projet",
	"Chargement",

	"Enregistrer",
	"Enregistrer sous",
	"Recherche",
	"Connaisez vous ca....",
	"Astuces numero %d",
	"Suivant",
	"Precedent",
	"Affichage au demarrage du programme",
	"Confirmation destruction de la fenetre ?",
	"Uniquement un menu dans chaque fenetre !",

	"Liste Objet",
	"Classe dérivé",
	"Vide",
	"Changer Fonte",
	"Tous montrer",
	"Rien montrer",
	"Couleur de fond",
	"Couleur haute",
	"Couleur basse",
	"Espacement",

	"Espacement X",
	"Espacement Y",
	"Fonte",
	"Invalide BccKeyFile Information!",
	"Je ne trouve pas le fichier BccKeyFile!",
	"BeInterfaceCreator (Release Candidate 2)\nBic (c) 2001 Devulder Jpaul couriel:rgb@free.fr\nIcone made by Thierry Caland couriel:thierry.caland@free.fr\n",
	"Erreur durant l'ecriture du fichier de préférences!",
	"Executable",
	"Librarie partagée ou Extension",
	"Librarie statique",

	"Kernel Driver",
	"(Void) default",
	"Default routine",
	"Ecrine nom",
	"Aucun",
	"Quelques",
	"Plus",
	"Tous",
	"Anglais",
	"Francais",

	"Nom de l'application",
	"Type de l'application",
	"Option compilateur",
	"Option lieur",
	"Optimisation",
	"Warning",
	"Debug",
	"Code",
	"Makefile",
	"Auto creation",

	"Creation Objet", 
	"Blanc",
	"Noir",
	"Rouge",
	"Bleue",
	"Gris",
	"Vert",
	"Turquoise",
	"Ocre",

	"????",
};
