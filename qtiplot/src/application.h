/***************************************************************************
    File                 : application.h
    Project              : QtiPlot
    --------------------------------------------------------------------
    Copyright            : (C) 2006 by Ion Vasilief, Tilman Hoener zu Siederdissen
    Email                : ion_vasilief@yahoo.fr, thzs@gmx.net
    Description          : QtiPlot's main window
                           
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation; either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor,                    *
 *   Boston, MA  02110-1301  USA                                           *
 *                                                                         *
 ***************************************************************************/
#ifndef APPLICATION_H
#define APPLICATION_H

#include <q3mainwindow.h>
#include <q3listview.h> 
//Added by qt3to4:
#include <Q3ActionGroup>
#include <QPixmap>
#include <QCloseEvent>
#include <QDropEvent>
#include <Q3ValueList>
#include <QTimerEvent>
#include <Q3PopupMenu>
#include <QDragEnterEvent>
#include <QTranslator>

#include "graph3D.h"
#include "plot3DDialog.h"

class Q3Action;
class Q3ActionGroup;
class Q3TextEdit;
class Q3ToolBar;
class QToolButton;
class Q3PopupMenu;
class QWorkspace;
class Q3PopupMenu;
class QToolButton;
class Q3ListBoxItem;
class Q3TextBrowser;
class QLineEdit;
class Q3DockWindow;
class QTranslator;
class Q3NetworkOperation;

class Matrix;
class Table;
class Graph;
class ScalePicker;
class Graph3D;
class Note;
class MultiLayer;
class fDialog;
class Folder;
class FolderListItem;
class FolderListView;

//! QtiPlot's main window
class ApplicationWindow: public Q3MainWindow
{
    Q_OBJECT
public:
    ApplicationWindow();
	ApplicationWindow(const QStringList& l);
	~ApplicationWindow();

	enum ShowWindowsPolicy{HideAll, ActiveFolder, SubFolders};

	QTranslator *appTranslator, *qtTranslator;
	Q3DockWindow *logWindow, *explorerWindow;
	Q3TextEdit *results;
	QWorkspace* ws;
    Q3ToolBar *fileTools, *plotTools, *tableTools, *plot3DTools, *displayBar, *editTools;
    Q3PopupMenu *windowsMenu,*view,*graph,*file,*format,*calcul,*edit,*dataMenu,*recent, *exportPlot;
	Q3PopupMenu *help,*type,*import,*plot2D,*plot3D, *specialPlot, *panels,*stat,*decay, *filter;
	Q3PopupMenu *matrixMenu, *plot3DMenu, *plotDataMenu, *tableMenu, *tablesDepend; 
	Q3PopupMenu *smooth, *normMenu, *translateMenu, *fillMenu, *setAsMenu, *multiPeakMenu;
	FolderListView *lv, *folders;
	QToolButton *btnResults;
	QWidgetList *hiddenWindows, *outWindows;
	Q3TextBrowser *browser;
	QLineEdit *info;
	QWidget *lastModified;

	Q3ActionGroup* dataTools;
	Q3Action *btnCursor, *btnSelect, *btnPicker, *btnRemovePoints, *btnMovePoints;
	Q3Action  *btnZoom, *btnPointer, *btnLine;
	
	Q3ActionGroup* coord;
	Q3Action* Box;
    Q3Action* Frame;
    Q3Action* None;

	Q3ActionGroup* grids;
    Q3Action* front;
    Q3Action* back;
    Q3Action* right;
    Q3Action* left;
    Q3Action* ceil;
    Q3Action* floor;

	Q3ActionGroup* floorstyle;
    Q3Action* floordata;
    Q3Action* flooriso;
    Q3Action* floornone;

	Q3ActionGroup* plotstyle;
    Q3Action* wireframe;
    Q3Action* hiddenline;
    Q3Action* polygon;
    Q3Action* filledmesh;
    Q3Action* pointstyle;
	Q3Action* barstyle;
	Q3Action *conestyle, *crossHairStyle;
	Graph *activeGraph,  *lastCopiedLayer;

public slots:
	void open();
	ApplicationWindow* open(const QString& fn);
	ApplicationWindow* openProject(const QString& fn);
	ApplicationWindow* importOPJ(const QString& filename);

	ApplicationWindow * plotFile(const QString& fn);
	void updatePlotsTransparency();

	QList<QWidget *> * windowsList();
	void updateWindowLists(QWidget *w);

	void setSaveSettings(bool autoSaving, int min);
	void changeAppStyle(const QString& s);
	void changeAppFont(const QFont& f);
	void updateAppFonts();
	void setAppColors(const QColor& wc,const QColor& pc,const QColor& tpc);

	//multilayer plots
	MultiLayer* plot(const QString& name);
	MultiLayer* copyGraph();
	MultiLayer* multilayerPlot(int c, int r, int style);
	MultiLayer* multilayerPlot(Table* w,const QStringList& colList, int style);
	//!used when restoring a plot from a project file
	MultiLayer* multilayerPlot(const QString& caption);
	//!used by the plot wizard
	MultiLayer* multilayerPlot(const QStringList& colList); 
	void connectMultilayerPlot(MultiLayer *g);
	void addLayer();
	void deleteLayer();
	void initMultilayerPlot(MultiLayer* g, const QString& name);
	void polishGraph(Graph *g, int style);
	void plot2VerticalLayers();
	void plot2HorizontalLayers();
	void plot4Layers();
	void plotStackedLayers();
	void plotStackedHistograms();

	//3D data plots
	Graph3D* openMatrixPlot3D(const QString& caption, const QString& matrix_name,
							 double xl,double xr,double yl,double yr,double zl,double zr);
	Graph3D* dataPlot3D(Table* table,const QString& colName);
	Graph3D* dataPlotXYZ(Table* table,const QString& zColName, int type);
		//when reading from .qti file
	Graph3D* dataPlot3D(const QString& caption,const QString& formula,
						double xl, double xr, double yl, double yr, double zl, double zr);
	Graph3D* dataPlotXYZ(const QString& caption,const QString& formula,
 						double xl, double xr, double yl, double yr, double zl, double zr);
	/*!
	* used when plotting from the wizard
	*/
	Graph3D* dataPlotXYZ(const QString& formula);
	Graph3D* dataPlot3D(const QString& formula);

	//surface plots
	Graph3D* newPlot3D(const QString& formula, double xl, double xr,
					   double yl, double yr, double zl, double zr);
	Graph3D* newPlot3D(const QString& caption,const QString& formula, 
					   double xl, double xr,double yl, double yr, double zl, double zr);
	Graph3D* copySurfacePlot();
	Graph3D* surfacePlot(const QString& name);
	void connectSurfacePlot(Graph3D *plot);
	void newSurfacePlot();
	void editSurfacePlot();
	void remove3DMatrixPlots(Matrix *m);
	void update3DMatrixPlots(QWidget *w);
	void add3DData();
	void change3DData();
	void change3DData(const QString& colName);
	void change3DMatrix();
	void change3DMatrix(const QString& matrix_name);
	void insertNew3DData(const QString& colName);
	void add3DMatrixPlot();
	void insert3DMatrixPlot(const QString& matrix_name);
	void initPlot3D(Graph3D *plot);
	void customPlot3D(Graph3D *plot);
	void setPlot3DOptions();

	//user-defined functions
	void newFunctionPlot();
	void newFunctionPlot(QString& type,QStringList &formulas,QStringList &vars,Q3ValueList<double> &ranges,Q3ValueList<int> &points);

	fDialog* functionDialog();
	void showFunctionDialog(const QString& function, int curve);
	void addFunctionCurve();
	void clearFunctionsList();
	void clearFitFunctionsList();
	void saveFitFunctionsList(const QStringList& l);
	void clearSurfaceFunctionsList();
	void clearLogInfo();
	void clearParamFunctionsList();
	void clearPolarFunctionsList();
	void updateFunctionLists(QString& type,QStringList &formulas);
	void updateSurfaceFuncList(const QString& s);

	Matrix* cloneMatrix();
	Matrix* newMatrix();
	Matrix* newMatrix(const QString& caption, int r, int c);
	Matrix* matrix(const QString& name);
	Matrix* createIntensityMatrix(const QPixmap& pic);
	Matrix* convertTableToMatrix();
	void initMatrix(Matrix* m, const QString& caption);
	void transposeMatrix();
	void invertMatrix();
	void matrixDeterminant();
	
	//! Creates an empty table
	Table* newTable();
	//! Used when importing an ASCII file
	Table* newTable(const QString& fname, const QString &sep, int lines, 
		            bool renameCols, bool stripSpaces, bool simplifySpaces);
	//! Used when loading a table from a project file 
	Table* newTable(const QString& caption,int r, int c);
	Table* newTable(const QString& caption, int r, int c, const QString& text);
	Table* newHiddenTable(const QString& caption, int r, int c, const QString& text);
	Table* table(const QString& name);
	Table* copyTable();
	Table* convertMatrixToTable();
	QWidgetList* tableList();

	void connectTable(Table* w);
	void newWrksheetPlot(const QString& caption,int r, int c, const QString& text);
	void showHistogramTable(const QString& caption, int r, int c, const QString& text);
	void initTable(Table* w, const QString& caption);
	void customTable(Table* w);
	void customizeTables(const QColor& bgColor,const QColor& textColor,
						const QColor& headerColor,const QFont& textFont, const QFont& headerFont);
	
	void customGraph(Graph* g);
	void setGraphDefaultSettings(bool autoscale,bool scaleFonts,bool resizeLayers);

	void plot3DWireframe();
	void plot3DHiddenLine();
	void plot3DPolygons();
	void plot3DWireSurface();

	void plot3DMatrix(int style);

	void plot3DRibbon();
	void plot3DScatter();
	void plot3DTrajectory();
	void plot3DBars();

	void plotL();
	void plotP();
	void plotLP();
	void plotPie();
	void plotVerticalBars();
	void plotHorizontalBars();
	void plotArea();
	void plotSteps();
	void plotSpline();
	void plotVerticalDropLines();
	void plotHistogram();
	void plotVectXYXY();
	void plotVectXYAM();
	void plotBoxDiagram();
	
	//image analysis
	void intensityTable();
	void pixelLineProfile();
	void loadImage();
	void loadImage(const QString& fn);
	void importImage();
	
    void loadASCII();
	void loadMultiple();
	void loadMultipleASCIIFiles(const QStringList& fileNames, int importFileAs);
	void exportAllTables(const QString& sep, bool colNames, bool expSelection);
	void exportASCII(const QString& tableName, const QString& sep, bool colNames, bool expSelection);

	void exportLayer();
    void exportGraph();
	void exportAllGraphs();
	void exportAllGraphs(const QString& dir, const QString& format, 
									int quality, bool transparency);
	void export2DPlotToFile(MultiLayer *plot, const QString& fileName, const QString& format, 
										int quality, bool transparency);
	void export3DPlotToFile(Graph3D *plot, const QString& fileName, 
										const QString& format);

	void saveProjectAs();
	bool saveProject();

	void readSettings();
	void saveSettings();
	void applyUserSettings();
	void modifiedProject();
	void modifiedProject(QWidget *w);
    void print();
	void print(QWidget* w);
	void printAllPlots();
	void printHelp();
	void setImportOptions(const QString& sep, int lines, bool rename, bool strip, bool simplify);
    
	void showExplorer();
	QStringList columnsList(Table::PlotDesignation plotType);
	
	void undo();
	void redo();
	
	myWidget* copyWindow();
	void rename();
	void renameWindow();

	//! This slot is called when the user presses F2 and an item is selected in lv.
	void renameWindow(Q3ListViewItem *item, int, const QString &s);

	//! This slot checks whether the new window name is valid and modifies the name. 
	bool renameWindow(myWidget *w, const QString &text);

	void maximizeWindow(Q3ListViewItem * lbi);
	void maximizeWindow();
	void minimizeWindow();

	void updateWindowStatus(myWidget* );

	bool hidden(QWidget* window);
	void closeActiveWindow();
	void closeWindow(QWidget* window);

	//! This slot does all the cleaning work before actually deleting a window!
	void removeWindowFromLists(QWidget* w);

	void hideWindow(myWidget* window);
	void hideWindow();
	void hideActiveWindow();
	void activateWindow();
	void activateWindow(QWidget *);
	void printWindow();
	void updateTable(const QString& caption,int row,const QString& text);
	void updateTableColumn(const QString& colName, double *dat, int rows);
    void about();
    void windowsMenuAboutToShow();
    void windowsMenuActivated( int id );
	void removeCurves(const QString& name);
	QStringList dependingPlots(const QString& caption);
	QStringList depending3DPlots(Matrix *m);
	QStringList multilayerDependencies(QWidget *w);

	void saveAsTemplate();
	void openTemplate();

	QString windowGeometryInfo(QWidget *w);
	void restoreWindowGeometry(ApplicationWindow *app, QWidget *w, const QString s);

	void resizeActiveWindow();
	void resizeWindow();
	
	// list view in project explorer
	void updateListView(const QString& caption);
	void setListView(const QString& caption,const QString& view);
	void renameListViewItem(const QString& oldName,const QString& newName);
	void setListViewDate(const QString& caption,const QString& date);
	QString listViewDate(const QString& caption);
	void setListViewSize(const QString& caption,const QString& size);
	void setListViewLabel(const QString& caption,const QString& label);
	
	void updateColNames(const QString& oldName, const QString& newName);
	void updateTableNames(const QString& oldName, const QString& newName);
	void changeMatrixName(const QString& oldName, const QString& newName);
	void updateCurves(const QString& name);
	
	void showTable(const QString& curve);
	void showTable(int i);

	void addColToTable();
	void cutSelection();
	void copySelection();
	void copyMarker();
	void pasteSelection();
	void clearSelection();
	void clearCellFromTable(const QString& name,double value);
	void copyActiveLayer();
	
	void newProject();
	void newGraph();

	Matrix* openMatrix(ApplicationWindow* app, const QStringList &flist);
	Table* openTable(ApplicationWindow* app, const QStringList &flist);
	Graph3D* openSurfacePlot(ApplicationWindow* app, const QStringList &lst);
	void openGraph(ApplicationWindow* app, MultiLayer *plot, const QStringList &list);

	void openRecentProject(int index);
	void insertTranslatedStrings();
	void translateActionsStrings();
	void init();
	void initGlobalConstants();
	void createActions();
	void initMainMenu();
	void initPlotMenu();
	void initTableMenu();
	void initTableAnalysisMenu();
	void initPlotDataMenu();
	void initToolBars();
	void initPlot3DToolBar();
	void disableActions();
	void hideToolbars();
	void customToolBars(QWidget* w);
	void customMenu(QWidget* w);
	void windowActivated(QWidget *w);

	//table tools
	void sortSelection();
	void sortActiveTable();
	void normalizeSelection();
	void normalizeActiveTable();
	void correlate();
	void convolute();
	void deconvolute();

	// plot tools 
	void newLegend();
	void addTimeStamp();
	void drawLine();
	void addText();
	void disableAddText();
	void addImage();
	void zoom();
	void unzoom();
	void showRangeSelectors();	
	void showCursor();
	void showScreenReader();
	void pickPointerCursor();
	void disableTools();
	void pickDataTool( Q3Action* action );
	
	void updateLog(const QString& result);

	//fitting
	void deleteFitTables();
	void fitLinear();
	void fitSigmoidal();
	void fitGauss();
	void fitLorentz();
	void fitMultiPeakGauss();
	void fitMultiPeakLorentz();
				 
	//calculus
	void differentiate();
	void analysis(const QString& whichFit);
	void analyzeCurve(const QString& whichFit, const QString& curveTitle);
	void showAnalysisDialog(const QString& whichFit);

	void addErrorBars();
	void defineErrorBars(const QString& name,int type,const QString& percent,int direction);
	void defineErrorBars(const QString& curveName,const QString& errColumnName, int direction);
	void movePoints();
	void removePoints();

	// event handlers 
	void closeEvent( QCloseEvent*);
	void timerEvent ( QTimerEvent *e);
	void dragEnterEvent( QDragEnterEvent* e );
	void dropEvent( QDropEvent* e );

	//dialogs
	void showFindDialogue();	
	void showPlotDialog();
	void showPlotDialog(long curveKey);
	QDialog* showScaleDialog();
	QDialog* showPieDialog();
	QDialog* showPlot3dDialog();
	axesDialog* showScalePageFromAxisDialog(int axisPos);
	axesDialog* showAxisPageFromAxisDialog(int axisPos);
	void showAxisDialog();
	void showGridDialog();
	void showGeneralPlotDialog();
	void showResults(bool ok);
	void showResults(const QString& s);
	void showTextDialog();
	void showLineDialog();
	void showTitleDialog();
	void showExportASCIIDialog();
	void showCurvesDialog();
	void showPlotAssociations(int curve);

	void showXAxisTitleDialog();
	void showYAxisTitleDialog();
	void showRightAxisTitleDialog();
	void showTopAxisTitleDialog();
	void showColumnOptionsDialog();
	void showRowsDialog();
	void showColsDialog();
	void showColMenu(int c);
	void showColumnValuesDialog();	
	void showGraphContextMenu();
	void showWindowContextMenu();
	void showWindowPopupMenu(Q3ListViewItem *it, const QPoint &p, int);

	//!This slot is connected to the context menu signal from lv; it's called when there are several items selected in the list
	void showListViewSelectionMenu(const QPoint &p);

	//!This slot is connected to the context menu signal from lv; it's called when there are no items selected in the list
	void showListViewPopupMenu(const QPoint &p);

	void showMoreWindows();
	void showImportDialog();
	void showMarkerPopupMenu();
	void showHelp();
	void chooseHelpFolder();
	void showPlotWizard();
	void showFitPolynomDialog();
	void showIntDialog();
	void showInterpolationDialog();
	void showExpGrowthDialog();
	void showExpDecayDialog();
	void showExpDecayDialog(int type);
	void showTwoExpDecayDialog();	
	void showExpDecay3Dialog();
	void showRowStatistics();
	void showColStatistics();
	void showFitDialog();
	void showImageDialog();
	void showPlotGeometryDialog();
	void showLayerDialog();
	void showPreferencesDialog();
	void showMatrixDialog();
	void showMatrixSizeDialog();
	void showMatrixValuesDialog();
	void showSmoothSavGolDialog();
	void showSmoothFFTDialog();
	void showSmoothAverageDialog();
	void lowPassFilterDialog();
	void highPassFilterDialog();
	void bandPassFilterDialog();
	void bandBlockFilterDialog();
	void showFFTDialog();

	void translateCurveHor();
	void translateCurveVert();

	void setAscValues();
	void setRandomValues();
	void setXCol();
	void setYCol();
	void setZCol();
	void disregardCol();

	void updateConfirmOptions(bool askTables, bool askMatrixes, bool askPlots2D, bool askPlots3D, bool askNotes);
	void showAxis(int axis, int type, const QString& labelsColName, bool axisOn, int ticksType,
		bool labelsOn, const QColor& c, int format, int prec, int rotation, int baselineDist, const QString& formula);
	
	//plot3D tools	
	void setFramed3DPlot();
	void setBoxed3DPlot();
	void removeAxes3DPlot();
	void removeGrid3DPlot();
	void setHiddenLineGrid3DPlot();
	void setLineGrid3DPlot();
	void setPoints3DPlot();
	void setCrosses3DPlot();
	void setCones3DPlot();
	void setBars3DPlot();
	void setFilledMesh3DPlot();
	void setEmptyFloor3DPlot();
	void setFloorData3DPlot();
	void setFloorIso3DPlot();
	void setFloorGrid3DPlot(bool on);
	void setCeilGrid3DPlot(bool on);
	void setRightGrid3DPlot(bool on);
	void setLeftGrid3DPlot(bool on);
	void setFrontGrid3DPlot(bool on);
	void setBackGrid3DPlot(bool on);
	void pickPlotStyle( Q3Action* action );
	void pickCoordSystem( Q3Action* action);
	void pickFloorStyle( Q3Action* action);
	void custom3DActions(QWidget *w);
	void custom3DGrids(int grids);

	void updateRecentProjectsList();
	
	//open internet browser
	void checkUpdates();
	void checkUpdates(Q3NetworkOperation *op);
	void showDonationDialog();
	void showSupportPage();
	void showDonationsPage();
	void showHomePage();
	void downloadManual();
	void downloadTranslation();
	bool open_browser(QWidget* parent, const QString& rUrl);

	void parseCommandLineArgument(const QString& s, int args);
	void createLanguagesList();
	void switchToLanguage(int param);
	void switchToLanguage(const QString& locale);

	bool alreadyUsedName(const QString& label);

	Note* newNote(const QString& caption = QString::null);
	Note* openNote(ApplicationWindow* app, const QStringList &flist);
	void initNote(Note* m, const QString& caption);
	
	//! Adds a new folder to the project
	void addFolder();
	//! Deletes the current folder
	void deleteFolder();

	//! Ask confirmation from user, deletes the folder f if user confirms and returns true, otherwise returns false;
	bool deleteFolder(Folder *f);

	//! Deletes the currently selected items from the list view lv
	void deleteSelectedItems();

	//! Sets all items in the folders list view to be desactivated (QPixmap = folder_closed_xpm)
	void desactivateFolders();

	//! Changes the current folder
	void changeFolder(Folder *newFolder, bool force = FALSE);

	//! Changes the current folder when the user changes the current item in the QListView "folders"
	void folderItemChanged(Q3ListViewItem *it);
	//! Changes the current folder when the user double-clicks on a folder item in the QListView "lv"
	void folderItemDoubleClicked(Q3ListViewItem *it);

	//! This slot creates and opens the context menu of a folder list view item
	/**
	 * \param it list view item
	 * \param p mouse global position
	 * \param fromFolders: TRUE means that the user clicked right mouse buttom on an item from QListView "folders"
	 *					   FALSE means that the user clicked right mouse buttom on an item from QListView "lv"
	 */
	void showFolderPopupMenu(Q3ListViewItem *it, const QPoint &p, bool fromFolders);

	//! This slot is connected to the SIGNAL contextMenuRequested from the list views
	void showFolderPopupMenu(Q3ListViewItem *it, const QPoint &p, int);
	
	//! This slot starts renaming the selected folder by creating a built-in text editor
	void startRenameFolder();

	//! This slot starts renaming the selected folder by creating a built-in text editor
	void startRenameFolder(Q3ListViewItem *item);

	//! This slot checks weather the new folder name is valid and modifies the name
	void renameFolder(Q3ListViewItem *it, int col, const QString &text);

	//! This slot forces showing all windows in the current folder and subfolders, depending on the user's viewing policy
	void showAllFolderWindows();

	//! This slot forces hidding all windows in the current folder and subfolders, depending on the user's viewing policy
	void hideAllFolderWindows();

	//! This slot hides all windows in folder f
	void hideFolderWindows(Folder *f);

	//! This slot pops up folder information
	void folderProperties();

	//! This slot pops up information about the selected window item
	void windowProperties();

	//! This slot pops up information about the current project
	void projectProperties();

	void appendProject();
	void saveAsProject();
	void saveFolderAsProject(Folder *f);
	void saveFolder(Folder *folder, const QString& fn);

	//! This slot adds a folder list item to the list view "lv"
	void addFolderListViewItem(Folder *f);

	//! This slot adds a widget list item to the list view "lv"
	void addListViewItem(myWidget *w);

	//! This slot hides or shows windows in the current folder and changes the view windows policy
	void setShowWindowsPolicy(int p);

	//! This slot returns a pointer to the root project folder
	Folder* projectFolder();

	//! This slot is used by the findDialog
	void find(const QString& s, bool windowNames, bool labels, bool folderNames, 
			  bool caseSensitive, bool partialMatch, bool subfolders);

	//! This slot initializes the list of items dragged by the user
	void dragFolderItems(QList<Q3ListViewItem*> items){draggedItems = items;};

	//! This slot is used to drop the objects in the list draggedItems to the folder of the destination item 
	void dropFolderItems(Q3ListViewItem *dest);

	//! This slot moves a folder item to another
	/**
	 * \param src source folder item
	 * \param dest destination folder item
	 */
	void moveFolder(FolderListItem *src, FolderListItem *dest);

signals:
	void windowClosed(const QString&);
	void modified();
	
public:
	//! pointer to the current folder in the project
	Folder *current_folder;
	//! Describes which windows are shown when the folder becomes the current folder
	ShowWindowsPolicy show_windows_policy;
	enum {MaxRecentProjects = 5};
	int fileVersion;
	int majVersion, minVersion, patchVersion;
	//! Extra suffix to the version string like "rc1", "beta7" or similar
	QString versionSuffix;
	QColor workspaceColor, panelsColor, panelsTextColor;
	QString appStyle, workingDir;
	bool smooth3DMesh, autoScaleFonts, autoResizeLayers, askForSupport;
	bool confirmCloseTable, confirmCloseMatrix, confirmClosePlot2D, confirmClosePlot3D;
	bool confirmCloseFolder, confirmCloseNotes;
	bool canvasFrameOn, titleOn, autoSave, drawBackbones, allAxesOn, autoscale2DPlots;
	int ticksStyle, legendFrameStyle, autoSaveTime, axesLineWidth, canvasFrameWidth;
	int majTicksLength, minTicksLength, defaultPlotMargin;
	int defaultCurveStyle, defaultCurveLineWidth, defaultSymbolSize;
	QFont appFont, plot3DTitleFont, plot3DNumbersFont, plot3DAxesFont;
	QFont tableTextFont, tableHeaderFont, plotAxesFont, plotLegendFont, plotNumbersFont, plotTitleFont;
	QColor tableBkgdColor, tableTextColor, tableHeaderColor;
	QString projectname,separator, helpFilePath, appLanguage;
	QString configFilePath, logInfo, fitPluginsPath;
	int logID,asciiID,closeID;
	int exportID, printAllID;
	int notes, graphs,tables, matrixes, fitNumber, ignoredLines, savingTimerId;
	bool renameColumns, copiedLayer, strip_spaces, simplify_spaces;
	QStringList plotWindows,tableWindows, recentProjects, plot3DWindows, matrixWindows, noteWindows;
	bool saved, showPlot3DProjection, showPlot3DLegend;
	int plot3DResolution;
	QStringList plot3DColors, locales;
	QStringList functions; //user-defined functions;
	QStringList xFunctions, yFunctions, rFunctions,tetaFunctions; // user functions for parametric and polar plots
	QStringList fitFunctions; //user-defined fit functions;
	QStringList surfaceFunc; //user-defined surface functions;

	//! List of tables and matrixes renamed in order to avoid conflicts when appending a project to a folder
	QStringList renamedTables;
	//! active window
	QWidget *aw; 
	Graph::MarkerType copiedMarkerType;
	
//variables used when user copy/paste markers
	QString auxMrkText;
	QFont auxMrkFont;
	QColor auxMrkColor, auxMrkBkgColor;
	QPoint auxMrkStart,auxMrkEnd;
	Qt::PenStyle auxMrkStyle;
	QString auxMrkFileName;
	int auxMrkBkg,auxMrkWidth;
	bool startArrowOn, endArrowOn, fillArrowHead;
	int arrowHeadLength, arrowHeadAngle, specialPlotMenuID, statMenuID, panelMenuID, plot3dID;
	int plotMenuID, importMenuID, newMenuID, recentMenuID, setAsMenuID, fillMenuID, normMenuID;
	int translateMenuID, smoothMenuID, filterMenuID, fitExpMenuID, multiPeakMenuID; 

    Q3Action *actionNewProject, *actionNewNote, *actionNewTable, *actionNewFunctionPlot, *actionNewSurfacePlot, *actionNewMatrix, *actionNewGraph;
    Q3Action *actionOpen, *actionLoadImage, *actionSaveProject, *actionSaveProjectAs, *actionImportImage;
    Q3Action *actionLoad, *actionLoadMultiple, *actionUndo, *actionRedo;
    Q3Action *actionCopyWindow;
    Q3Action *actionCutSelection, *actionCopySelection, *actionPasteSelection, *actionClearSelection;
    Q3Action *actionShowExplorer, *actionShowLog, *actionAddLayer, *actionShowLayerDialog;

    Q3Action *actionExportGraph, *actionExportAllGraphs, *actionPrint, *actionPrintAllPlots, *actionShowExportASCIIDialog;
    Q3Action *actionShowImportDialog;
    Q3Action *actionCloseAllWindows, *actionClearLogInfo, *actionShowPlotWizard, *actionShowConfigureDialog;
    Q3Action *actionShowCurvesDialog, *actionAddErrorBars, *actionAddFunctionCurve, *actionUnzoom, *actionNewLegend, *actionAddImage, *actionAddText;
    Q3Action *actionPlotL, *actionPlotP, *actionPlotLP, *actionPlotVerticalDropLines, *actionPlotSpline, *actionPlotSteps, *actionPlotVerticalBars;
	Q3Action *actionPlotHorizontalBars, *actionPlotArea, *actionPlotPie, *actionPlotVectXYAM, *actionPlotVectXYXY;
    Q3Action *actionPlotHistogram, *actionPlotStackedHistograms, *actionPlot2VerticalLayers, *actionPlot2HorizontalLayers, *actionPlot4Layers, *actionPlotStackedLayers;
    Q3Action *actionPlot3DRibbon, *actionPlot3DBars, *actionPlot3DScatter, *actionPlot3DTrajectory;
    Q3Action *actionShowColStatistics, *actionShowRowStatistics, *actionShowIntDialog;
    Q3Action *actionDifferentiate, *actionFitLinear, *actionShowFitPolynomDialog;
    Q3Action *actionShowExpDecayDialog, *actionShowTwoExpDecayDialog, *actionShowExpDecay3Dialog;
    Q3Action *actionFitExpGrowth, *actionFitSigmoidal, *actionFitGauss, *actionFitLorentz, *actionShowFitDialog;
    Q3Action *actionShowLayoutDialog, *actionShowAxisDialog, *actionShowTitleDialog;
    Q3Action *actionShowColumnOptionsDialog, *actionShowColumnValuesDialog, *actionShowColsDialog, *actionShowRowsDialog;
    Q3Action *actionAbout, *actionShowHelp, *actionChooseHelpFolder;
    Q3Action *actionRename, *actionCloseWindow, *actionConvertTable;
    Q3Action *actionAddColToTable, *actionDeleteLayer, *actionInterpolate;
    Q3Action *actionPrintHelp, *actionResizeActiveWindow, *actionHideActiveWindow;
    Q3Action *actionShowMoreWindows, *actionPixelLineProfile, *actionIntensityTable;
    Q3Action *actionShowLineDialog, *actionShowImageDialog, *actionShowTextDialog;
    Q3Action *actionActivateWindow, *actionMinimizeWindow, *actionMaximizeWindow, *actionHideWindow, *actionResizeWindow, *actionPrintWindow;
    Q3Action *actionShowPlotGeometryDialog, *actionEditSurfacePlot, *actionAdd3DData;
	Q3Action *actionMatrixDeterminant, *actionSetMatrixProperties;
	Q3Action *actionSetMatrixDimensions, *actionConvertMatrix, *actionSetMatrixValues, *actionTransposeMatrix, *actionInvertMatrix;
	Q3Action *actionPlot3DWireFrame, *actionPlot3DHiddenLine, *actionPlot3DPolygons, *actionPlot3DWireSurface;
	Q3Action *actionDeleteFitTables, *actionShowGridDialog, *actionTimeStamp;
	Q3Action *actionSmoothSavGol, *actionSmoothFFT, *actionSmoothAverage, *actionFFT;
	Q3Action *actionLowPassFilter, *actionHighPassFilter, *actionBandPassFilter, *actionBandBlockFilter;
	Q3Action *actionSortTable, *actionSortSelection, *actionNormalizeSelection;
	Q3Action *actionNormalizeTable, *actionConvolute, *actionDeconvolute, *actionCorrelate;
	Q3Action *actionTranslateHor, *actionTranslateVert, *actionSetAscValues, *actionSetRandomValues;
	Q3Action *actionSetXCol, *actionSetYCol, *actionSetZCol, *actionDisregardCol;
	Q3Action *actionBoxPlot, *actionMultiPeakGauss, *actionMultiPeakLorentz, *actionCheckUpdates;
	Q3Action *actionDonate, *actionHomePage, *actionDownloadManual, *actionTechnicalSupport, *actionTranslations;
	Q3Action *actionShowPlotDialog, *actionShowScaleDialog, *actionOpenTemplate, *actionSaveTemplate;

private:
	//!Stores the pointers to the dragged items from the FolderListViews objects
	QList<Q3ListViewItem *> draggedItems;
};

#endif
