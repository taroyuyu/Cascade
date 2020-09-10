#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    windowManager = &WindowManager::getInstance();
    windowManager->setUp(ui->vulkanView->getVulkanWindow(), ui->nodeGraph, ui->propertiesView);

    connect(ui->vulkanView->getVulkanWindow(), &VulkanWindow::rendererHasBeenCreated,
            this, &MainWindow::handleRendererHasBeenCreated);
    connect(ui->vulkanView->getVulkanWindow(), &VulkanWindow::rendererHasBeenCreated,
            windowManager, &WindowManager::handleRendererHasBeenCreated);
}

void MainWindow::handleRendererHasBeenCreated()
{
    // We are waiting for the renderer to be fully initialized here
    // before assigning it
    renderManager = &RenderManager::getInstance();
    renderManager->setUp(ui->vulkanView->getVulkanWindow()->getRenderer(), ui->nodeGraph);
}

MainWindow::~MainWindow()
{
    delete ui;
}

