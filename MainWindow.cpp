#include "MainWindow.h"
#include "ModelTreeModel.h"
#include <QMenu>
#include <QMenuBar>
#include <QHeaderView>
#include <QSplitter>

MainWindow::MainWindow() {
    setWindowTitle("Gazebo World Designer");

    createActions();
    createMenus();

    ModelTreeModel *treeModel = new ModelTreeModel;
    modelTreeView.setModel(treeModel);
    modelTreeView.header()->hide();
    modelTreeView.setDragEnabled(true);
    modelTreeView.viewport()->setAcceptDrops(false);
    modelTreeView.setDragDropMode(QAbstractItemView::DragOnly);

    connect(&worldView, &WorldView::showProperties, &propertyPane, &PropertyPane::showProperties);

    connect(&worldView, &WorldView::showSceneProperties, &scenePropertyPane, &PropertyPane::showProperties);

    QVBoxLayout *propertyPanesLayout = new QVBoxLayout;
    propertyPanesLayout->addWidget(new QLabel{"Object Properties"});
    propertyPanesLayout->addWidget(&propertyPane);
    propertyPanesLayout->addStretch();
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Plain);
    propertyPanesLayout->addWidget(line);
    propertyPanesLayout->addWidget(new QLabel{"Scene Properties"});
    propertyPanesLayout->addWidget(&scenePropertyPane);

    QWidget *propertPanesWidget = new QWidget;
    propertPanesWidget->setLayout(propertyPanesLayout);

    QSplitter *splitter = new QSplitter{this};
    splitter->addWidget(&modelTreeView);
    splitter->addWidget(&worldView);
    splitter->addWidget(propertPanesWidget);

    setCentralWidget(splitter);

    worldView.newFile();
}

void MainWindow::createActions() {
    closeAct = new QAction{"&Close", this};
    closeAct->setShortcuts(QKeySequence::Close);
    connect(closeAct, &QAction::triggered, this, &QMainWindow::close);
    addAction(closeAct);

    newFileAct = new QAction{"&New", this};
    newFileAct->setShortcuts(QKeySequence::New);
    connect(newFileAct, &QAction::triggered, &worldView, &WorldView::newFile);
    addAction(newFileAct);

    openFileAct = new QAction{"&Open", this};
    openFileAct->setShortcuts(QKeySequence::Open);
    connect(openFileAct, &QAction::triggered, &worldView, &WorldView::openFile);
    addAction(openFileAct);

    saveFileAct = new QAction{"&Save", this};
    saveFileAct->setShortcuts(QKeySequence::Save);
    connect(saveFileAct, &QAction::triggered, &worldView, &WorldView::saveFile);
    addAction(saveFileAct);

    saveFileAsAct = new QAction{"&Save As", this};
    saveFileAsAct->setShortcuts(QKeySequence::SaveAs);
    connect(saveFileAsAct, &QAction::triggered, &worldView, &WorldView::saveFileAs);
    addAction(saveFileAsAct);
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(newFileAct);
    fileMenu->addAction(openFileAct);
    fileMenu->addAction(saveFileAct);
    fileMenu->addAction(saveFileAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAct);
}
