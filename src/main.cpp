#include "ui/main_window/main_window.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QApplication::setApplicationName("NerdFontsIconBrowser");
  QApplication::setApplicationVersion("1.0.0");

  MainWindow window;
  window.show();

  return QApplication::exec();
}
