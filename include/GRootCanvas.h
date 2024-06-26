#ifndef ROOT_GRootCanvas
#define ROOT_GRootCanvas

/** \addtogroup GROOT
 *  @{
 */

///////////////////////////////////////////////////////////////////////////
///
/// \class GRootCanvas
///
/// This class creates a main window with menubar, scrollbars and a
/// drawing area. The widgets used are the new native ROOT GUI widgets.
///
/// A slightly edited version of the the GRootCanvas
/// file in the default root source.  The reason for
/// the swap was take more control over the keyboard
/// interface to the canvas (particularly the arrow
/// keys).
///
///////////////////////////////////////////////////////////////////////////

#ifndef ROOT_TCanvasImp
#include "TCanvasImp.h"
#endif
#ifndef ROOT_TGFrame
#include "TGFrame.h"
#endif

class TGCanvas;
class TGMenuBar;
class TGPopupMenu;
class TGLayoutHints;
class TGStatusBar;
class GRootContainer;
class TGToolBar;
class TGHorizontal3DLine;
class TGVertical3DLine;
class TVirtualPadEditor;
class TGDockableFrame;
class TGDNDManager;
class TGToolTip;

class GCanvas;

class GRootCanvas : public TGMainFrame, public TCanvasImp {

   friend class GRootContainer;

private:
   TGCanvas*       fCanvasWindow;        ///< canvas widget
   GRootContainer* fCanvasContainer;     ///< container in canvas widget
   TGMenuBar*      fMenuBar;             ///< menubar
   TGPopupMenu*    fFileMenu;            ///< file menu
   TGPopupMenu*    fFileSaveMenu;        ///< save cascade submenu
   TGPopupMenu*    fEditMenu;            ///< edit menu
   TGPopupMenu*    fEditClearMenu;       ///< clear cascade submenu
   TGPopupMenu*    fViewMenu;            ///< view menu
   TGPopupMenu*    fViewWithMenu;        ///< view with... cascade submenu
   TGPopupMenu*    fOptionMenu;          ///< option menu
   TGPopupMenu*    fToolsMenu;           ///< tools menu
   TGPopupMenu*    fHelpMenu;            ///< help menu
   TGLayoutHints*  fMenuBarLayout;       ///< menubar layout hints
   TGLayoutHints*  fMenuBarItemLayout;   ///< layout hints for menu in menubar
   TGLayoutHints*  fMenuBarHelpLayout;   ///< layout hint for help menu in menubar
   TGLayoutHints*  fCanvasLayout;        ///< layout for canvas widget
   TGStatusBar*    fStatusBar;           ///< statusbar widget
   TGLayoutHints*  fStatusBarLayout;     ///< layout hints for statusbar

   TGCompositeFrame*   fEditorFrame;         ///< side frame for current pad editor
   TGLayoutHints*      fEditorLayout;        ///< layout for editor frame
   TGCompositeFrame*   fMainFrame;           ///< main frame containing canvas and side frame
   TGLayoutHints*      fToolBarLayout;       ///< layout for toolbar widget
   TGToolBar*          fToolBar;             ///< icon button toolbar
   TGHorizontal3DLine* fToolBarSep;          ///< toolbar separator
   TGLayoutHints*      fMainFrameLayout;     ///< layout for main frame
   TGVertical3DLine*   fVertical1;           ///< toolbar vertical separator
   TGVertical3DLine*   fVertical2;           ///< toolbar vertical separator
   TGHorizontal3DLine* fHorizontal1;         ///< toolbar sepatator
   TGLayoutHints*      fVertical1Layout;     ///< layout hints for separator
   TGLayoutHints*      fVertical2Layout;     ///< layout hints for separator
   TGLayoutHints*      fHorizontal1Layout;   ///< layout hints for separator
   TGDockableFrame*    fToolDock;            ///< dockable frame holding the toolbar
   TGLayoutHints*      fDockLayout;          ///< layout hints for dockable frame widget
   const TGPicture*    fIconPic;             ///< icon picture
   TGToolTip*          fToolTip;             ///< tooltip for object info

   TVirtualPadEditor* fEditor;     ///< pointer to currently loaded pad editor
   Bool_t             fEmbedded;   ///< true if embedded in any other frame (e.g. in the browser)
   Int_t              fCanvasID;   ///< index in fWindows array of TGX11
   Bool_t             fAutoFit;    ///< when true canvas container keeps same size as canvas
   Int_t              fButton;     ///< currently pressed button

   GRootCanvas(const GRootCanvas&);              // Not implemented
   GRootCanvas& operator=(const GRootCanvas&);   // Not implemented
   void         CreateCanvas(const char* name);
   void         CreateEditor();

   Bool_t HandleContainerButton(Event_t* event);
   Bool_t HandleContainerDoubleClick(Event_t* event);
   Bool_t HandleContainerConfigure(Event_t* ev);
   Bool_t HandleContainerKey(Event_t* event);
   Bool_t HandleContainerMotion(Event_t* event);
   Bool_t HandleContainerExpose(Event_t* event);
   Bool_t HandleContainerCrossing(Event_t* event);

   Bool_t HandleDNDDrop(TDNDData* data) override;
   Atom_t HandleDNDPosition(Int_t x, Int_t y, Atom_t action, Int_t xroot, Int_t yroot) override;
   Atom_t HandleDNDEnter(Atom_t* typelist) override;
   Bool_t HandleDNDLeave() override;

public:
   GRootCanvas(GCanvas* c = nullptr, const char* name = "ROOT Canvas", UInt_t width = 500, UInt_t height = 300);
   GRootCanvas(GCanvas* c, const char* name, Int_t x, Int_t y, UInt_t width, UInt_t height);
   ~GRootCanvas() override;

   void   AdjustSize();
   void   Close() override;
   void   ForceUpdate() override { Layout(); }
   void   FitCanvas();
   void   EventInfo(Int_t event, Int_t px, Int_t py, TObject* selected);
   UInt_t GetWindowGeometry(Int_t& x, Int_t& y, UInt_t& w, UInt_t& h) override;
   UInt_t GetCwidth() const;
   UInt_t GetCheight() const;
   void   Iconify() override { IconifyWindow(); }
   Int_t  InitWindow() override;
   void   PrintCanvas();
   void   RaiseWindow() override;
   void   SetWindowPosition(Int_t x, Int_t y) override;
   void   SetWindowSize(UInt_t w, UInt_t h) override;
   void   SetWindowTitle(const char* title) override;
   void   SetCanvasSize(UInt_t w, UInt_t h) override;
   void   SetStatusText(const char* txt = nullptr, Int_t partidx = 0) override;

   void Show() override { MapRaised(); }
   void ShowMenuBar(Bool_t show = kTRUE) override;
   void ShowStatusBar(Bool_t show = kTRUE) override;
   void ShowEditor(Bool_t show = kTRUE) override;
   void ShowToolBar(Bool_t show = kTRUE) override;
   void ShowToolTips(Bool_t show = kTRUE) override;

   Bool_t HasEditor() const override;
   Bool_t HasMenuBar() const override;
   Bool_t HasStatusBar() const override;
   Bool_t HasToolBar() const override;
   Bool_t HasToolTips() const override;

   void Activated(Int_t id);

   TGMenuBar*       GetMenuBar() const { return fMenuBar; }
   TGLayoutHints*   GetMenuBarItemLayout() const { return fMenuBarItemLayout; }
   TGStatusBar*     GetStatusBar() const { return fStatusBar; }
   TGDockableFrame* GetToolDock() const { return fToolDock; }

   // overridden from TGMainFrame
   void   CloseWindow() override;
   Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2) override;
   void   ReallyDelete() override;

   /// \cond CLASSIMP
   ClassDefOverride(GRootCanvas, 0)   // GRSI native GUI version of main window with menubar and drawing area
   /// \endcond
};
/*! @} */
#endif
