#include "om_data_model.h"
#include "om_data_provider_injector.h"

#include <QApplication>
#include <QTreeView>
#include <QLayout>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto* container = new QWidget();
    container->setWindowTitle("OM TreeView");
    container->resize(800, 600);

    auto* layout = new QVBoxLayout(container);
    layout->setContentsMargins(0, 0, 0, 0);

    auto omDataProvider = getOMDataProvider();
    auto* omDataModel = new OMDataModel(omDataProvider.get(), container);

    auto* treeView = new QTreeView(container);
    treeView->setModel(omDataModel);
    treeView->setHeaderHidden(true);

    layout->addWidget(treeView);

    container->show();

    return app.exec();
}