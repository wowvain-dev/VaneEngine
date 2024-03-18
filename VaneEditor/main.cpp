#define SDL_MAIN_HANDLED

#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.resize(320, 240);
    window.show();
    window.setWindowTitle(
        QApplication::translate("toplevel", "Vane Editor"));
    return app.exec();
}